# runtime-observatory — ptrace INT3 probe tracer

Minimal, dependency-free runtime observatory for OpenSpore: plant `INT3`
software breakpoints at known RVAs in a 32-bit target (Wine-hosted
`SporeApp.exe` or a native `-m32` test binary) and record register snapshots
to JSONL. Built for differential analysis against the original game as an
oracle. 32-bit targets only, MIT.

## Why ptrace (and not Frida)

* The analysis host runs with `yama ptrace_scope=1`: a tracer may only touch
  its own descendants. `probe_tracer --launch` forks + execs the target, so
  the tracee is always a child — no system-wide injection, no sysctl changes.
* Frida would need `ptrace`-equivalent injection plus a JS runtime inside the
  game process; a self-contained C++17 tracer has no runtime, no network, and
  works headless next to Wine.
* Conservative by design: capped breakpoints (`--max-bps`), a per-function
  event cap (`--max-events`), no whole-game tracing.

## Architecture

```
probe_tracer --launch CMD --launch-arg A ... probes.json out.jsonl
             [--duration S] [--wait-module S] [--max-bps N] [--max-events N]
             [--module NAME]
```

1. **fork + exec + seize.** The child execs the target; the parent
   `PTRACE_SEIZE`s it with
   `TRACESYSGOOD | TRACECLONE | TRACEEXEC | TRACEFORK | TRACEVFORK` so the
   whole lineage (Wine preloader chain, thread pools) stays traced. New
   clone/fork/vfork children are auto-attached **and** auto-stopped at birth,
   so the tracer resumes each one (`PTRACE_CONT`) or it would leak stopped.
2. **Module wait (launch mode).** Scans the traced tree's `/proc/*/maps`
   every ~100 ms until a path ending in `--module` appears (Wine needs
   seconds; native ELF maps instantly), while resuming every stopped tracee
   every 10 ms. Bounded by `--wait-module` (default 60 s); an already-exited
   root child prints `target exited before module mapped` and exits 1
   promptly. After discovery, retargets onto the pid hosting the module
   header + contiguous anonymous executable code (Wine maps PE sections
   anonymously in the forked game process) and waits up to 10 s more for an
   executable section before planting.
3. **INT3 plant.** Probe `addr = module_base + (rva - image_base)` is checked
   against an executable mapping, the original byte is saved via
   `/proc/<pid>/mem` (`pread`/`pwrite`, unbuffered — see pitfalls), `0xCC` is
   written.
4. **Event loop.** On `SIGTRAP` with `eip-1` matching a probe: snapshot regs
   (native 64-bit `GETREGS` projected to a 32-bit view), restore the original
   byte, rewind `EIP` onto the probe, single-step it, re-plant `0xCC`, append
   one JSONL event, `CONT`. A 1 s `ITIMER_REAL` heartbeat (handler **without**
   `SA_RESTART`) keeps the blocking `waitpid` responsive so `--duration` is
   honored. A hard stop at `duration + 15 s` latches the interrupt flag; the
   detach path `_exit(3)`s rather than wedge the session.
5. **Detach.** Bounded 3 s stop-wait (exit-reaps shrink the set, `ECHILD`
   breaks immediately — a missing break here once spun at 100 % CPU
   forever), bytes restored, `DETACH`.

All `signal()` usage was replaced with `sigaction()` **without** `SA_RESTART`
(glibc `signal()` sets `SA_RESTART`, which silently resumes blocking
`waitpid` and made `Ctrl+C` / `timeout` look dead). Every wait/poll loop has
an explicit deadline plus an `EINTR` re-check.

## Build

```sh
make -C tools/observatory        # g++, -O2 -g -std=c++17 -Wall -Wextra, no warnings
```

Produces `tools/observatory/probe_tracer` (git-ignored).

## m32 self-test (no Wine, no game)

`test/m32target` (`gcc -m32 -O0`) calls `beta` → `alpha` in a loop;
`test/probes_m32.json` holds their RVAs. **If the binary is rebuilt,
regenerate the RVAs** (`nm test/m32target | grep -E ' (main|alpha|beta)$' —
for this PIE binary `rva == nm address`, `image_base` 0); stale RVAs plant
`INT3` mid-instruction and the child dies with `SIGSEGV`.

```sh
cd tools/observatory
./probe_tracer --launch ./test/m32target --launch-arg 400 test/probes_m32.json /tmp/obs_m32.jsonl --duration 3 --module m32target
# expect: exit 0, "m32target done", ~1800 events (alpha capped at --max-events 1000)
python3 analyze.py /tmp/obs_m32.jsonl
```

Short-target / missing-module behavior (prompt `exit 1`, no hang):

```sh
./probe_tracer --launch ./test/m32target --launch-arg 10 test/probes_m32.json /tmp/x.jsonl --module nonexistent_mod --wait-module 3
# error: target exited before module nonexistent_mod was mapped ...
```

Signal behavior: `SIGINT`/`SIGTERM` to the tracer interrupts the run and
detaches (previously ignored outright by the old handler).

## Wine usage

```sh
timeout -s KILL 25 wine SPORE/SporeBin/SporeApp.exe   # sanity: game renders (d3d fixmes), killed by timeout
python3 tools/observatory/observe.py main_menu --duration 20
# → tools/observatory/out/obs_main_menu.jsonl + analysis table
```

`probes/main_menu.json` targets `SporeApp.exe` 3.1.0.22 startup RVAs
(`image_base 0x400000`; see header comment for provenance).

**Wine status (2026-09-21):** the original preloader wedge is FIXED — the
maps-poll now drains stops from *every* tracee (`waitpid(-1)` + `CONT` on
clone/fork/vfork/exec/SIGSTOP stops), so the game boots to renderer bring-up
under trace (d3d/swapchain fixmes, 13 s event loop observed). Two Wine layout
facts were handled along the way: the loader child maps only the PE header
page, and the game process maps its code sections **anonymously**
(`0x401000-0x13cc000 r-xp`, no file path), contiguous with the header.
**Current blocker:** `wine SporeApp.exe` routes through `start.exe /exec`,
which spawns the game reparented to init/systemd (PPID 845 observed untraced),
outside the traced lineage — so `--module SporeApp.exe` never matches and the
run exits 1 after `--wait-module`. Next lead: fork events survive reparenting,
so scan `attached`-set pids' maps instead of just the ppid tree; or bypass
`start.exe`. Full evidence: `SCENARIO-main_menu.md` §4. Native `-m32` targets
remain the green path (1801-event self-test).

## Pitfalls found while building this (read before touching the code)

* **Stale binary hang:** an old `probe_tracer` (built before the detach
  deadline) spun at 100 % CPU in userspace (`R`, `wchan 0`) in the detach
  `waitpid` loop on `ECHILD` with no `break`. Always `make -C
  tools/observatory` after editing; `ps -o stat,wchan` distinguishes
  userspace spin (`R`/`0`) from `waitpid` block (`do_wait`).
* **Buffered `/proc/pid/mem` writes:** `fwrite` through stdio never reached
  the target before the single-step (no flush in between), so the child
  stepped the stale `0xCC`, re-trapped, then resumed mid-instruction →
  `SIGSEGV`. All target memory I/O is now unbuffered `pread`/`pwrite` on a
  fresh fd per call.
* **Missing EIP rewind:** after `INT3`, `EIP == addr + 1`; single-stepping
  from there executes mid-instruction. The handler rewinds `EIP` to the probe
  via `SETREGS` before stepping.
* **Event-cap drop path:** merely `CONT`inuing past the cap skips the
  function prologue (corrupted frames, late `SIGSEGV`). On cap hit the tracer
  now retires the breakpoint (restore + step once, run free).

## Layout

* `probe_tracer.cpp` — the tracer (single file, C++17, no deps).
* `analyze.py` — stdlib summarizer: per-function count/first/min+median
  interval, thread histogram, 1 s-window rate spikes (>3x), text table +
  `--json`.
* `observe.py` — `observe.py <scenario> [--duration S]`: tracer in
  `--launch wine` mode with `probes/<scenario>.json` →
  `out/obs_<scenario>.jsonl` → `analyze.py`.
* `probes/main_menu.json`, `test/{m32target.c,m32target,probes_m32.json}`.
* `examples/` — `obs_m32_example.jsonl` (13 KB real capture, `--max-events 30`).

## Limitations

* 32-bit little-endian targets only; x86-64 host assumed for reg projection.
* Call `depth` is a nesting heuristic, not a real stack unwind.
* Function-entry probes only; hitting the per-function cap retires the
  breakpoint (later calls run unobserved, `dropped` counts the retiring hit).
* Wine game target blocked: `start.exe /exec` reparents the game out of the
  traced lineage (see blocker above); native `-m32` targets are the green path.
