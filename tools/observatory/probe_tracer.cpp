// probe_tracer — minimal ptrace INT3 software-breakpoint tracer for 32-bit Linux
// processes (Wine game targets or native -m32 test binaries).
//
// Usage:
//   probe_tracer <pid> <probe.json>... <out.jsonl>
//                [--duration SEC] [--max-bps N] [--max-events N] [--module NAME]
//   probe_tracer --launch CMD [--launch-arg A]... <probe.json>... <out.jsonl>
//                [--duration SEC] [--wait-module SEC] [--max-bps N] [--max-events N] [--module NAME]
//
// Behavior:
//   - attach mode: attaches to all threads of <pid> (PTRACE_SEIZE + TRACECLONE)
//   - launch mode: forks a child, execs CMD, becomes its tracer; polls
//     /proc/<child>/maps every 500ms until --module maps (wine needs seconds)
//   - finds the module base in /proc/<pid>/maps (path suffix match on --module)
//   - writes 0xCC at base + (rva - image_base) for each probe
//   - on INT3 at a probe: snapshots regs, records one JSONL event, single-steps
//     the original first byte, restores 0xCC
//   - SIGTRAPs that are not at a probe are resumed without recording
//   - on timeout: stops all threads, restores original bytes, detaches cleanly
//
// Conservative by design: capped breakpoints, per-function event cap, no
// whole-game tracing. 32-bit targets only. MIT.

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <sys/user.h>
#include <sys/time.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

// ------------------------- minimal JSON parser -------------------------

struct JVal {
    enum { NUL, NUM, STR, ARR, OBJ } type = NUL;
    double num = 0;
    std::string str;
    std::vector<JVal> arr;
    std::vector<std::pair<std::string, JVal> > obj;
    const JVal* find(const std::string& k) const {
        for (size_t i = 0; i < obj.size(); i++)
            if (obj[i].first == k) return &obj[i].second;
        return nullptr;
    }
    std::string asHexStr() const {  // "0x400000" or "123" -> decimal
        if (type != STR) return "0";
        const char* p = str.c_str();
        return std::to_string((long long)strtoull(p, nullptr, 0));
    }
};

struct JParser {
    const std::string& s;
    size_t i = 0;
    explicit JParser(const std::string& src) : s(src) {}
    void ws() {
        while (i < s.size() && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'))
            i++;
    }
    JVal parse() { ws(); return value(); }
    JVal value() {
        ws();
        if (i >= s.size()) return JVal();
        char c = s[i];
        if (c == '{') return object();
        if (c == '[') return array();
        if (c == '"') { JVal v; v.type = JVal::STR; v.str = string(); return v; }
        if (c == 't') { i += 4; return JVal(); }
        if (c == 'f') { i += 5; return JVal(); }
        if (c == 'n') { i += 4; return JVal(); }
        return number();
    }
    std::string string() {
        std::string out;
        if (i < s.size() && s[i] == '"') i++;
        while (i < s.size() && s[i] != '"') {
            if (s[i] == '\\' && i + 1 < s.size()) {
                i++;
                char e = s[i];
                switch (e) {
                case 'n': out += '\n'; break;
                case 't': out += '\t'; break;
                case 'r': out += '\r'; break;
                case '"': out += '"'; break;
                case '\\': out += '\\'; break;
                case '/': out += '/'; break;
                case 'u': i += 4; out += '?'; break;
                default: out += e;
                }
                i++;
            } else {
                out += s[i++];
            }
        }
        if (i < s.size()) i++;
        return out;
    }
    JVal number() {
        size_t start = i;
        while (i < s.size() && (isxdigit((unsigned char)s[i]) || s[i] == '-' ||
                                 s[i] == '+' || s[i] == '.' || s[i] == 'e' || s[i] == 'E'))
            i++;
        JVal v;
        v.type = JVal::NUM;
        v.num = (double)strtoull(s.substr(start).c_str(), nullptr, 0);
        return v;
    }
    JVal array() {
        JVal v;
        v.type = JVal::ARR;
        i++;
        ws();
        if (i < s.size() && s[i] == ']') { i++; return v; }
        for (;;) {
            v.arr.push_back(value());
            ws();
            if (i < s.size() && s[i] == ',') { i++; continue; }
            if (i < s.size() && s[i] == ']') { i++; break; }
            break;
        }
        return v;
    }
    JVal object() {
        JVal v;
        v.type = JVal::OBJ;
        i++;
        ws();
        if (i < s.size() && s[i] == '}') { i++; return v; }
        for (;;) {
            ws();
            std::string key = string();
            ws();
            if (i < s.size() && s[i] == ':') i++;
            v.obj.push_back(std::make_pair(key, value()));
            ws();
            if (i < s.size() && s[i] == ',') { i++; continue; }
            if (i < s.size() && s[i] == '}') { i++; break; }
            break;
        }
        return v;
    }
};

// ------------------------- probes -------------------------

struct Probe {
    std::string name;
    uint32_t rva;
    uint32_t imageBase;  // from JSON
    uint32_t addr = 0;   // absolute, filled after base discovery
    uint8_t orig = 0;
    bool set = false;
    bool thiscall = true;
    uint32_t recorded = 0;
    uint32_t dropped = 0;
};

struct ThreadDepth {
    std::vector<std::string> stack;  // heuristic nesting (see README)
};

// The kernel returns the NATIVE x86_64 user_regs_struct (216 bytes, r15..gs)
// for a 32-bit inferior too — reading it with the 32-bit layout misaligns every
// field (e.g. "eip" lands on r11, "esp" on r9). So GETREGS into X64Regs and
// project the low 32 bits into a 32-bit view.
struct X64Regs {
    uint64_t r15, r14, r13, r12;
    uint64_t rbp, rbx, r11, r10, r9, r8;
    uint64_t rax, rcx, rdx, rsi, rdi;
    uint64_t orig_rax, rip, cs, eflags, rsp, ss;
    uint64_t fs_base, gs_base, ds, es, fs, gs;
};

struct I386Regs {
    uint32_t ebx, ecx, edx, esi, edi, ebp, eax;
    uint32_t xds, xes, xfs, xgs;
    uint32_t orig_eax, eip, cs, eflags;
    uint32_t esp, ss;
};

// Fill a 32-bit view from a native 64-bit GETREGS dump.
static inline void fill32(I386Regs* v, const X64Regs* x) {
    v->ebx = (uint32_t)x->rbx;   v->ecx = (uint32_t)x->rcx;
    v->edx = (uint32_t)x->rdx;   v->esi = (uint32_t)x->rsi;
    v->edi = (uint32_t)x->rdi;   v->ebp = (uint32_t)x->rbp;
    v->eax = (uint32_t)x->rax;
    v->xds = (uint32_t)x->ds;    v->xes = (uint32_t)x->es;
    v->xfs = (uint32_t)x->fs;    v->xgs = (uint32_t)x->gs;
    v->orig_eax = (uint32_t)x->orig_rax; v->eip = (uint32_t)x->rip;
    v->cs = (uint32_t)x->cs;     v->eflags = (uint32_t)x->eflags;
    v->esp = (uint32_t)x->rsp;   v->ss = (uint32_t)x->ss;
}

// Read a stopped tracee's registers into a 32-bit view.
static inline bool getRegs32(pid_t pid, I386Regs* v) {
    X64Regs x;
    if (ptrace(PTRACE_GETREGS, pid, 0, &x) != 0) return false;
    fill32(v, &x);
    return true;
}

// Move EIP back to the INT3 site: after the trap EIP == addr + 1, so the
// single-step must start AT addr or it executes mid-instruction (-> SIGILL).
// GETREGS/SETREGS move the native 64-bit struct; only rip is changed.
static inline bool setEip32(pid_t pid, uint32_t eip) {
    X64Regs x;
    if (ptrace(PTRACE_GETREGS, pid, 0, &x) != 0) return false;
    x.rip = eip;
    return ptrace(PTRACE_SETREGS, pid, 0, &x) == 0;
}

static uint64_t nowNs();
static volatile sig_atomic_t g_interrupted = 0;
static volatile uint64_t g_hardDeadlineNs = 0;  // nowNs() value; SIGALRM past it => give up
static void onSigint(int) { g_interrupted = 1; }
// 1s heartbeat: unblocks the (blocking) waitpid in the event loop so the
// --duration deadline is honored even while the target runs freely.
// Past the hard stop (duration + 15s) it also latches g_interrupted so every
// loop with an EINTR re-check drains out promptly (no SA_RESTART anywhere).
static void onAlarm(int) {
    if (g_hardDeadlineNs && nowNs() >= g_hardDeadlineNs) g_interrupted = 1;
}

static uint64_t nowNs() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + ts.tv_nsec;
}

// /proc/<pid>/mem-based access (what gdb uses; works on read-only TEXT where
// process_vm_writev fails with EFAULT). Unbuffered pread/pwrite on a fresh fd
// per call: an earlier stdio (FILE*) version buffered the single-byte breakpoint
// restore and the child single-stepped the stale 0xCC -> instant SIGTRAP loop
// followed by mid-instruction resume -> SIGSEGV. Never cache, never buffer.
static int vmread(pid_t pid, uint32_t addr, void* buf, size_t len) {
    char path[64];
    snprintf(path, sizeof path, "/proc/%d/mem", pid);
    for (int attempt = 0; attempt < 2; attempt++) {
        int fd = open(path, O_RDONLY);
        if (fd < 0) return -1;
        ssize_t n = pread(fd, buf, len, (off_t)addr);
        close(fd);
        if (n >= 0) return (int)n;
    }
    return -1;
}

static int vmwrite(pid_t pid, uint32_t addr, const void* buf, size_t len) {
    char path[64];
    snprintf(path, sizeof path, "/proc/%d/mem", pid);
    for (int attempt = 0; attempt < 2; attempt++) {
        int fd = open(path, O_RDWR);
        if (fd < 0) return -1;
        ssize_t n = pwrite(fd, buf, len, (off_t)addr);
        close(fd);
        if (n >= 0) return (int)n;
    }
    return -1;
}

struct ModMap {
    uint64_t start, end;
    std::string perms;
    std::string path;
};

static std::vector<ModMap> parseMaps(pid_t pid) {
    std::string path = "/proc/" + std::to_string(pid) + "/maps";
    FILE* f = fopen(path.c_str(), "r");
    std::vector<ModMap> out;
    if (!f) return out;
        char line[1024];
    while (fgets(line, sizeof line, f)) {
        size_t ln = strlen(line);
        while (ln > 0 && (line[ln - 1] == '\n' || line[ln - 1] == '\r')) line[--ln] = '\0';
        ModMap m;
        char* dash = strchr(line, '-');
        if (!dash) continue;
        m.start = strtoull(line, nullptr, 16);
        m.end = strtoull(dash + 1, nullptr, 16);
        char* p1 = strchr(dash + 1, ' ');
        if (!p1) continue;
        m.perms.assign(p1 + 1, p1 + 5);
        // path = field 6 (after start-end perms offset dev inode)
        char* cur = line;
        for (int k = 0; k < 5 && *cur; k++)
            cur = strchr(cur + 1, ' ');
        if (cur) {
            cur++;
            while (*cur == ' ') cur++;
            m.path = cur;
        }
        out.push_back(m);
    }
    fclose(f);
    return out;
}

static std::vector<pid_t> threadsOf(pid_t pid) {
    std::string d = "/proc/" + std::to_string(pid) + "/task/";
    std::vector<pid_t> out;
    // simple scandir
    struct dirent* ent;
    DIR* dir = opendir(d.c_str());
    if (!dir) return out;
    while ((ent = readdir(dir)) != nullptr) {
        if (ent->d_name[0] == '.') continue;
        out.push_back((pid_t)atoi(ent->d_name));
    }
    closedir(dir);
    std::sort(out.begin(), out.end());
    return out;
}

static const int OPTS = PTRACE_O_TRACESYSGOOD | PTRACE_O_TRACECLONE |
                        PTRACE_O_TRACEEXEC | PTRACE_O_TRACEFORK | PTRACE_O_TRACEVFORK;

int main(int argc, char** argv) {
    const char* USAGE =
        "usage: %s <pid> <probe.json>... <out.jsonl>\n"
        "       [--duration SEC] [--max-bps N] [--max-events N] [--module NAME]\n"
        "       %s --launch CMD [--launch-arg A]... <probe.json>... <out.jsonl>\n"
        "           [--duration SEC] [--wait-module SEC] [--max-bps N] [--max-events N] [--module NAME]\n";
    if (argc < 3) {
        fprintf(stderr, USAGE, argv[0], argv[0]);
        return 2;
    }
    bool launchMode = false;
    std::string launchCmd;
    std::vector<std::string> launchArgs;
    pid_t target = 0;
    double duration = 15.0;
    double waitModule = 60.0;
    int maxBps = 256;
    uint32_t maxEvents = 1000;
    std::string module = "SporeApp.exe";
    std::vector<std::string> positional;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        if (a == "--launch") {
            launchMode = true;
            if (i + 1 >= argc) { fprintf(stderr, "--launch needs a command\n"); return 2; }
            launchCmd = argv[++i];
        } else if (a == "--launch-arg") {
            if (i + 1 >= argc) { fprintf(stderr, "--launch-arg needs a value\n"); return 2; }
            launchArgs.push_back(argv[++i]);
        } else if (a == "--duration") duration = atof(argv[++i]);
        else if (a == "--wait-module") waitModule = atof(argv[++i]);
        else if (a == "--max-bps") maxBps = atoi(argv[++i]);
        else if (a == "--max-events") maxEvents = (uint32_t)atoi(argv[++i]);
        else if (a == "--module") module = argv[++i];
        else if (a[0] == '-') {
            fprintf(stderr, "unknown option %s\n", a.c_str());
            return 2;
        } else {
            positional.push_back(a);
        }
    }
    if (!launchMode) {
        // positional: <pid> <probe.json>... <out.jsonl>
        if (positional.size() < 3) {
            fprintf(stderr, "attach mode needs: <pid> <probe.json>... <out.jsonl>\n");
            return 2;
        }
        target = (pid_t)atoi(positional[0].c_str());
        positional.erase(positional.begin());
    } else {
        if (positional.size() < 2) {
            fprintf(stderr, "launch mode needs: <probe.json>... <out.jsonl>\n");
            return 2;
        }
    }
    // positional now: <probe.json>... <out.jsonl>
    std::string outPath = positional.back();
    positional.pop_back();
    std::vector<std::string> probeFiles = positional;

    // sigaction WITHOUT SA_RESTART: glibc's signal() sets SA_RESTART, which
    // silently resumes a blocking waitpid and makes --duration unenforceable.
    {
        struct sigaction sa;
        memset(&sa, 0, sizeof sa);
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = onSigint;
        sigaction(SIGINT, &sa, nullptr);
        sigaction(SIGTERM, &sa, nullptr);
        sa.sa_handler = onAlarm;
        sigaction(SIGALRM, &sa, nullptr);
        struct itimerval beat;
        memset(&beat, 0, sizeof beat);
        beat.it_value.tv_sec = beat.it_interval.tv_sec = 1;  // 1s heartbeat
        setitimer(ITIMER_REAL, &beat, nullptr);
        // Hard stop: duration + 15s. Past it, the SIGALRM handler latches
        // g_interrupted; the detach path _exit(3)s as a last resort.
        g_hardDeadlineNs = nowNs() + (uint64_t)((duration + 15.0) * 1000000000.0);
    }

    // ---- load probes ----
    uint32_t imageBase = 0x400000;
    std::vector<Probe> probes;
    for (size_t f = 0; f < probeFiles.size(); f++) {
        FILE* fp = fopen(probeFiles[f].c_str(), "rb");
        if (!fp) {
            fprintf(stderr, "cannot open %s: %s\n", probeFiles[f].c_str(), strerror(errno));
            return 1;
        }
        std::string txt;
        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof buf, fp)) > 0) txt.append(buf, n);
        fclose(fp);
        JVal root;
        { JParser p(txt); root = p.parse(); }
        if (root.type != JVal::OBJ) {
            fprintf(stderr, "%s: bad JSON\n", probeFiles[f].c_str());
            return 1;
        }
        const JVal* ib = root.find("image_base");
        if (ib) imageBase = (uint32_t)strtoull(ib->str.c_str(), nullptr, 0);
        const JVal* pl = root.find("probes");
        if (!pl || pl->type != JVal::ARR) {
            fprintf(stderr, "%s: missing \"probes\" array\n", probeFiles[f].c_str());
            return 1;
        }
        for (size_t k = 0; k < pl->arr.size(); k++) {
            const JVal& e = pl->arr[k];
            if (e.type != JVal::OBJ) continue;
            const JVal* nm = e.find("name");
            const JVal* rv = e.find("rva");
            if (!nm || !rv) continue;
            Probe pr;
            pr.name = nm->str;
            pr.rva = (uint32_t)strtoull(rv->str.c_str(), nullptr, 0);
            pr.imageBase = imageBase;
            const JVal* tc = e.find("thiscall");
            if (tc && tc->type == JVal::NUM) pr.thiscall = tc->num > 0;
            probes.push_back(pr);
        }
    }
    // dedupe by (name,rva)
    std::set<std::pair<std::string, uint32_t> > seen;
    std::vector<Probe> uniq;
    for (size_t i = 0; i < probes.size(); i++) {
        if (seen.insert(std::make_pair(probes[i].name, probes[i].rva)).second)
            uniq.push_back(probes[i]);
    }
    probes.swap(uniq);
    if ((int)probes.size() > maxBps) {
        fprintf(stderr, "warning: %zu probes exceeds --max-bps %d; truncating\n", probes.size(), maxBps);
        probes.resize(maxBps);
    }
    fprintf(stderr, "loaded %zu probes (image_base 0x%x, module %s)\n", probes.size(), imageBase, module.c_str());

    // ---- launch mode: fork child, become its tracer, wait for module map ----
    std::set<pid_t> attached;
    std::vector<ModMap> maps;
    uint64_t loadBase = 0;
    bool baseFound = false;

    if (launchMode) {
        pid_t child = fork();
        if (child < 0) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            return 1;
        }
        if (child == 0) {
            // Child: reset inherited handlers to default, then exec.
            signal(SIGINT, SIG_DFL);
            signal(SIGTERM, SIG_DFL);
            std::vector<const char*> av;
            av.push_back(launchCmd.c_str());
            for (size_t k = 0; k < launchArgs.size(); k++)
                av.push_back(launchArgs[k].c_str());
            av.push_back(nullptr);
            execvp(launchCmd.c_str(), const_cast<char**>(av.data()));
            _exit(127);  // exec failed
        }
        target = child;
        fprintf(stderr, "launch: exec'd %s -> child pid %d\n", launchCmd.c_str(), target);

        // Seize immediately so every later exec/clone (wine preloader chain)
        // stays inside the traced lineage (PTRACE_O_TRACEEXEC/TRACECLONE).
        if (ptrace(PTRACE_SEIZE, target, 0, (void*)(intptr_t)OPTS) == 0)
            attached.insert(target);
        else
            fprintf(stderr, "warn: seize child %d failed: %s\n", target, strerror(errno));
        // Let it run so the PE/ELF actually gets mapped.
        ptrace(PTRACE_CONT, target, 0, 0);

        // Poll /maps every 500ms until --module appears (wine takes seconds).
        uint64_t waitDeadline = nowNs() + (uint64_t)(waitModule * 1000000000.0);
        std::set<std::string> logSeen;
        int polls = 0;
        while (!baseFound && nowNs() < waitDeadline && !g_interrupted) {
            polls++;
            int st;
            pid_t w = waitpid(target, &st, __WALL | WNOHANG);
            if (w == target && (WIFEXITED(st) || WIFSIGNALED(st))) {
                fprintf(stderr, "error: target exited before module %s was mapped "
                                "(child %d, status %d)\n",
                        module.c_str(), target,
                        WIFEXITED(st) ? WEXITSTATUS(st) : -WTERMSIG(st));
                for (auto& t : attached) ptrace(PTRACE_DETACH, t, 0, 0);
                return 1;
            }
            if (w == target && WIFSTOPPED(st)) {
                // ptrace stop (exec/clone event in the wine chain): resume it,
                // or the child stays frozen and the module never maps.
                ptrace(PTRACE_CONT, target, 0, 0);
            }
            maps = parseMaps(target);
            for (size_t k = 0; k < maps.size(); k++) {
                const std::string& p = maps[k].path;
                if (!p.empty() && p[0] == '/' && logSeen.insert(p).second)
                    fprintf(stderr, "  [maps] %s 0x%llx-0x%llx %s\n", p.c_str(),
                            (unsigned long long)maps[k].start,
                            (unsigned long long)maps[k].end, maps[k].perms.c_str());
            }
            for (size_t k = 0; k < maps.size(); k++) {
                const std::string& p = maps[k].path;
                if (p.size() >= module.size() &&
                    p.compare(p.size() - module.size(), module.size(), module) == 0) {
                    if (!baseFound || maps[k].start < loadBase) {
                        loadBase = maps[k].start;
                        baseFound = true;
                    }
                }
            }
            if (polls % 50 == 0)
                fprintf(stderr, "  ... still waiting for %s (%.0fs left)\n",
                        module.c_str(), (double)(waitDeadline - nowNs()) / 1e9);
            if (!baseFound)
                usleep(10000);  // responsive 10ms poll (500ms froze the child at the exec stop)
        }
        if (!baseFound) {
            fprintf(stderr,
                    "error: module %s never appeared in maps of child pid %d within %.0fs.\n"
                    "       Observed mappings were logged above. Likely blockers:\n"
                    "       - wine failed to start (check wine stderr / wineprefix)\n"
                    "       - the PE mapped under a wine-spawned loader pid outside the\n"
                    "         traced lineage (not covered by the child-maps poll)\n",
                    module.c_str(), target, waitModule);
            // Report every live pid whose ppid chain leads to the child.
            std::map<pid_t, pid_t> ppid;
            DIR* pd = opendir("/proc");
            if (pd) {
                struct dirent* e2;
                while ((e2 = readdir(pd)) != nullptr) {
                    if (e2->d_name[0] < '0' || e2->d_name[0] > '9') continue;
                    char st2[1024];
                    FILE* pf = fopen(
                        ("/proc/" + std::string(e2->d_name) + "/stat").c_str(), "r");
                    if (!pf) continue;
                    if (!fgets(st2, sizeof st2, pf)) { fclose(pf); continue; }
                    fclose(pf);
                    char* par = strrchr(st2, ')');  // comm is parenthesized
                    if (!par || par[1] != ' ') continue;
                    par += 2;
                    char state;
                    long parent = 0;
                    if (sscanf(par, "%c %ld", &state, &parent) == 2)
                        ppid[atoi(e2->d_name)] = (pid_t)parent;
                }
                closedir(pd);
            }
            std::vector<pid_t> chain;
            for (auto& kv : ppid) {
                pid_t p = kv.first, up = kv.second;
                std::set<pid_t> visited;
                while (up > 1 && visited.insert(up).second) {
                    if (up == target) { chain.push_back(p); break; }
                    up = ppid[up];
                }
            }
            std::sort(chain.begin(), chain.end());
            if (!chain.empty()) {
                fprintf(stderr, "       pids in the child's process tree:");
                for (pid_t p : chain) fprintf(stderr, " %d", p);
                fprintf(stderr, "\n");
            }
            kill(target, SIGTERM);
            {   // Bounded reap: TERM, grace period, KILL, grace period, give up.
                uint64_t kdl = nowNs() + 2000000000ull;
                int st;
                pid_t r = 0;
                while (nowNs() < kdl && !g_interrupted) {
                    r = waitpid(target, &st, __WALL | WNOHANG);
                    if (r == target || (r < 0 && errno != EINTR)) break;
                    usleep(20000);
                }
                if (r != target) {
                    kill(target, SIGKILL);
                    kdl = nowNs() + 2000000000ull;
                    while (nowNs() < kdl) {
                        r = waitpid(target, &st, __WALL | WNOHANG);
                        if (r == target || (r < 0 && errno != EINTR)) break;
                        usleep(20000);
                    }
                }
            }
            for (auto& t : attached) ptrace(PTRACE_DETACH, t, 0, 0);
            return 1;
        }
    } else {
        maps = parseMaps(target);
        for (size_t i = 0; i < maps.size(); i++) {
            const std::string& p = maps[i].path;
            if (p.size() >= module.size() &&
                p.compare(p.size() - module.size(), module.size(), module) == 0) {
                if (!baseFound || maps[i].start < loadBase) { loadBase = maps[i].start; baseFound = true; }
            }
        }
        if (!baseFound) {
            fprintf(stderr, "error: module %s not found in /maps of pid %d\n", module.c_str(), target);
            return 1;
        }
    }
    fprintf(stderr, "module base: 0x%llx\n", (unsigned long long)loadBase);

    // ---- resolve probe addresses; require an executable module mapping ----
    for (size_t i = 0; i < probes.size(); i++) {
        Probe& pr = probes[i];
        pr.addr = (uint32_t)loadBase + (pr.rva - pr.imageBase);
        bool inX = false;
        for (size_t k = 0; k < maps.size(); k++) {
            const std::string& p = maps[k].path;
            bool sameMod = p.size() >= module.size() &&
                           p.compare(p.size() - module.size(), module.size(), module) == 0;
            if (sameMod && maps[k].perms.find('x') != std::string::npos &&
                (uint64_t)pr.addr >= maps[k].start && (uint64_t)pr.addr < maps[k].end)
                inX = true;
        }
        if (!inX) {
            fprintf(stderr, "  skip %s @0x%x: not in an executable module mapping\n", pr.name.c_str(), pr.addr);
            probes[i].name = "";  // mark inactive
        } else {
            fprintf(stderr, "  %s @0x%x (rva 0x%x)\n", pr.name.c_str(), pr.addr, pr.rva);
        }
    }

    // ---- attach all threads (skip ones already attached, e.g. the launch child) ----
    std::vector<pid_t> tids = threadsOf(target);
    for (size_t i = 0; i < tids.size(); i++) {
        if (attached.count(tids[i])) continue;
        if (ptrace(PTRACE_SEIZE, tids[i], 0, (void*)(intptr_t)OPTS) == 0) {
            attached.insert(tids[i]);
        } else {
            fprintf(stderr, "warn: seize %d failed: %s\n", tids[i], strerror(errno));
        }
    }
    if (attached.empty()) {
        fprintf(stderr, "error: attached no threads\n");
        return 1;
    }

    // ---- stop all threads, set breakpoints ----
    size_t activeBps = 0;
    // PTRACE_INTERRUPT (not sticky SIGSTOP): each thread reports a
    // PTRACE_EVENT_STOP that waitpid() can observe.
    for (auto& t : attached)
        ptrace(PTRACE_INTERRUPT, t, 0, 0);
    std::set<pid_t> stopped;
    {
        uint64_t dl = nowNs() + 5000000000ull;
        while (stopped.size() < attached.size() && nowNs() < dl && !g_interrupted) {
            int st;
            pid_t w = waitpid(-1, &st, __WALL | WNOHANG);
            if (w > 0 && WIFSTOPPED(st))  // any ptrace stop freezes the thread -> safe to patch
                stopped.insert(w);
            else if (w > 0 && (WIFEXITED(st) || WIFSIGNALED(st))) {
                attached.erase(w);  // died while stopping; don't wait for it below
            } else if (w < 0) {
                if (errno != EINTR) break;  // ECHILD: nothing left to stop
            } else {
                usleep(1000);  // w == 0: no stop pending yet; don't tight-spin
            }
        }
    }
    uint8_t tmp[1];
    for (size_t i = 0; i < probes.size(); i++) {
        Probe& pr = probes[i];
        if (pr.name.empty()) continue;
        if (vmread(target, pr.addr, tmp, 1) != 1) {
            fprintf(stderr, "  fail read %s @0x%x\n", pr.name.c_str(), pr.addr);
            pr.name = "";
            continue;
        }
        pr.orig = tmp[0];
        uint8_t cc = 0xCC;
        if (vmwrite(target, pr.addr, &cc, 1) != 1) {
            fprintf(stderr, "  fail write %s @0x%x: %s\n", pr.name.c_str(), pr.addr, strerror(errno));
            pr.name = "";
            continue;
        }
        pr.set = true;
    }
    for (size_t i = 0; i < probes.size(); i++)
        activeBps += probes[i].set ? 1 : 0;
    fprintf(stderr, "active breakpoints: %zu\n", activeBps);

    // ---- resume everything that was stopped (incl. threads born during the stop) ----
    for (auto& t : attached)
        ptrace(PTRACE_CONT, t, 0, 0);

    // ---- event loop ----
    FILE* out = fopen(outPath.c_str(), "w");
    if (!out) {
        fprintf(stderr, "cannot open %s: %s\n", outPath.c_str(), strerror(errno));
        return 1;
    }
    setvbuf(out, nullptr, _IOLBF, 0);

    std::map<pid_t, ThreadDepth> depth;
    std::map<uint32_t, Probe*> byAddr;
    for (size_t i = 0; i < probes.size(); i++)
        if (probes[i].set) byAddr[probes[i].addr] = &probes[i];

    uint64_t t0 = nowNs();
    uint64_t firstEvent = 0;
    uint64_t deadline = t0 + (uint64_t)(duration * 1000000000.0);
    uint32_t totalEvents = 0;
    uint32_t totalTraps = 0;

    I386Regs r;
    while (!g_interrupted && nowNs() < deadline) {
        int st;
        pid_t w = waitpid(-1, &st, __WALL);
        if (w <= 0) {
            if (errno == EINTR) continue;
            break;  // no more tracees
        }
        if (WIFEXITED(st) || WIFSIGNALED(st)) {
            if (WIFSIGNALED(st))
                fprintf(stderr, "tracee %d killed by signal %d\n", w, WTERMSIG(st));
            else
                fprintf(stderr, "tracee %d exited (status %d)\n", w, WEXITSTATUS(st));
            attached.erase(w);
            depth.erase(w);
            if (attached.empty()) break;
            continue;
        }
        if (!WIFSTOPPED(st)) continue;
        int sig = WSTOPSIG(st);
        int ev = (st >> 16) & 0xff;  // ptrace event byte (0 for plain signal stops)
        if (sig == SIGSTOP) {
            // Group-stop (SIGSTOP is sticky: it re-enters once after resume).
            // Resume without re-delivering the signal.
            ptrace(PTRACE_CONT, w, 0, 0);
            continue;
        }
        if (sig == (SIGTRAP | 0x80)) {
            ptrace(PTRACE_CONT, w, 0, 0);  // syscall-stop; not interested
            continue;
        }
        if (sig == SIGTRAP && ev != 0) {
            if (ev == PTRACE_EVENT_CLONE || ev == PTRACE_EVENT_FORK || ev == PTRACE_EVENT_VFORK) {
                unsigned long msg = 0;
                ptrace(PTRACE_GETEVENTMSG, w, 0, &msg);
                if (msg) {
                    pid_t nt = (pid_t)msg;
                    attached.insert(nt);
                    depth[nt] = ThreadDepth();
                    // New threads/tasks are auto-attached AND stopped at birth;
                    // resume them or they leak stopped and never run.
                    ptrace(PTRACE_CONT, nt, 0, 0);
                }
                ptrace(PTRACE_CONT, w, 0, 0);
                continue;
            }
            ptrace(PTRACE_CONT, w, 0, 0);
            continue;
        }
        if (sig == SIGTRAP) {
            if (!getRegs32(w, &r)) {
                ptrace(PTRACE_CONT, w, 0, 0);
                continue;
            }
            uint32_t eip = r.eip;
            Probe* pr = nullptr;
            auto it = byAddr.find(eip - 1);
            if (it != byAddr.end()) pr = it->second;
            if (pr && pr->name.size() >= 2) {
                totalTraps++;
                if (pr->recorded < maxEvents) {
                    // restore orig byte, rewind EIP onto the probe, single-step
                    // it, restore CC
                    uint8_t o = pr->orig;
                    vmwrite(target, pr->addr, &o, 1);
                    setEip32(w, pr->addr);
                    ptrace(PTRACE_SINGLESTEP, w, 0, 0);
                    int st2;
                    {   // Bounded single-step wait: heartbeat EINTRs keep this
                        // responsive; a dead/vanished tracee must not wedge us.
                        uint64_t sdl = nowNs() + 5000000000ull;
                        for (;;) {
                            pid_t r2 = waitpid(w, &st2, __WALL);
                            if (r2 > 0) break;
                            if (r2 < 0 && errno != EINTR) { memset(&st2, 0, sizeof st2); break; }
                            if (nowNs() >= sdl || g_interrupted) { memset(&st2, 0, sizeof st2); break; }
                        }
                    }
                    uint8_t cc = 0xCC;
                    vmwrite(target, pr->addr, &cc, 1);
                    uint64_t t = nowNs();
                    if (!firstEvent) firstEvent = t;
                    // heuristic call depth (see README)
                    ThreadDepth& td = depth[w];
                    if (td.stack.empty() || td.stack.back() != pr->name) {
                        td.stack.clear();
                        td.stack.push_back(pr->name);
                    } else {
                        td.stack.push_back(pr->name);
                    }
                    uint32_t thisPtr = pr->thiscall ? r.ecx : r.eax;
                    char line[512];
                    snprintf(line, sizeof line,
                             "{\"t\": %llu, \"rel\": %llu, \"tid\": %d, \"name\": \"%s\", "
                             "\"rva\": \"0x%x\", \"addr\": \"0x%x\", \"this\": \"0x%08x\", "
                             "\"eax\": \"0x%08x\", \"ebx\": \"0x%08x\", \"ecx\": \"0x%08x\", "
                             "\"edx\": \"0x%08x\", \"depth\": %zu}\n",
                             (unsigned long long)t,
                             (unsigned long long)(t - firstEvent), w, pr->name.c_str(),
                             pr->rva, pr->addr, thisPtr,
                             r.eax, r.ebx, r.ecx, r.edx, td.stack.size());
                    fputs(line, out);
                    pr->recorded++;
                    totalEvents++;
                    ptrace(PTRACE_CONT, w, 0, 0);
                } else {
                    // Cap reached: retire the breakpoint (restore orig, step
                    // the real first instruction once) and run free from here
                    // on. Just CONTinuing would re-execute from addr+1 with a
                    // skipped prologue -> corrupted frames -> SIGSEGV.
                    pr->dropped++;
                    uint8_t o2 = pr->orig;
                    vmwrite(target, pr->addr, &o2, 1);
                    setEip32(w, pr->addr);
                    ptrace(PTRACE_SINGLESTEP, w, 0, 0);
                    {
                        uint64_t sdl = nowNs() + 5000000000ull;
                        int st3 = 0;
                        for (;;) {
                            pid_t r3 = waitpid(w, &st3, __WALL);
                            if (r3 > 0) break;
                            if (r3 < 0 && errno != EINTR) break;
                            if (nowNs() >= sdl || g_interrupted) break;
                        }
                    }
                    pr->set = false;
                    byAddr.erase(pr->addr);
                    ptrace(PTRACE_CONT, w, 0, 0);
                }
                continue;
            }
            // non-probe SIGTRAP: resume without recording
            ptrace(PTRACE_CONT, w, 0, 0);
            continue;
        }
        // signal-delivery stop: deliver the signal
        ptrace(PTRACE_CONT, w, 0, (void*)(intptr_t)sig);
    }

    // ---- clean detach: stop all, restore bytes, detach ----
    fclose(out);
    if (!attached.empty()) {
        fprintf(stderr, "detaching: restoring %zu bytes\n", activeBps);
        for (auto& t : attached)
            ptrace(PTRACE_INTERRUPT, t, 0, 0);
        uint64_t dl = nowNs() + 3000000000ull;  // 3s bounded
        while (!attached.empty() && nowNs() < dl && !g_interrupted) {
            int st;
            pid_t w = waitpid(-1, &st, __WALL | WNOHANG);
            if (w > 0) {
                if (WIFEXITED(st) || WIFSIGNALED(st)) { attached.erase(w); depth.erase(w); }
                else usleep(10000);  // stopped: keep it frozen while we restore
            } else if (w == 0) {
                usleep(20000);  // no stop pending yet; poll gently
            } else {
                if (errno != EINTR) break;  // ECHILD: no tracees left; must not spin
            }
        }
        for (size_t i = 0; i < probes.size(); i++) {
            if (probes[i].set) {
                uint8_t o = probes[i].orig;
                vmwrite(target, probes[i].addr, &o, 1);
            }
        }
        for (auto& t : attached)
            ptrace(PTRACE_DETACH, t, 0, 0);
        if (g_hardDeadlineNs && nowNs() >= g_hardDeadlineNs) {
            // Last resort: the hard stop fired while tracees were still
            // attached. Bytes are restored and DETACH attempted above; never
            // risk wedging the session here.
            _exit(3);
        }
    } else {
        fprintf(stderr, "target already exited; nothing to restore\n");
    }

    fprintf(stderr,
            "done: %u events recorded, %u total traps, over %.1fs\n",
            totalEvents, totalTraps, (double)(nowNs() - t0) / 1e9);
    for (size_t i = 0; i < probes.size(); i++)
        if (!probes[i].name.empty())
            fprintf(stderr, "  %-32s recorded=%u dropped=%u\n", probes[i].name.c_str(), probes[i].recorded, probes[i].dropped);
    _exit(0);
}
