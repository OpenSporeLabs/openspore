import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSpace;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.SourceType;

import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * Cautious vtable-detection pass for SporeApp.exe (x86:LE:32, no MSVC RTTI).
 *
 * Evidence-based only; no invented hierarchies:
 *  1. Scan non-code readable segments (.rdata + .data) for aligned runs of 4-byte words
 *     where EVERY word is a pointer into an executable segment. Record maximal runs of
 *     length 5..40 as candidates; runs longer than 40 (merged vtables / large tables) are
 *     recorded separately AND their sub-windows are extracted so a single well-known vtable
 *     embedded in a longer block (e.g. cAppSystem @ 0x01413af0) is still captured.
 *  2. Cross-evidence:
 *       - virtual-call displacements `call [reg+disp]` (disp!=0) over all code. Only the
 *         LARGE displacements (>=0x80, slot>=32) are discriminative; small ones (0x4..0x7c)
 *         are over-represented and treated as weak corroboration.
 *       - SDK-named slot functions (Spore-ModAPI names contain "::").
 *       - sibling families: candidates sharing >=4 slot functions.
 *       - inheritance chains: candidates whose slot list is an element-wise prefix of another.
 *  3. Score + confidence; label ONLY the top high-confidence candidates with
 *     `VTAB_<addr>_<n>slots` and record every label for easy undo.
 *
 * Output: JSON summary to stdout + full artifact to the given path.
 * Defensive: every per-item step is wrapped in try/catch so one bad item never aborts the pass.
 *
 * Run: -postScript VtableDetect.java [outPath]   (outPath defaults to docs/analysis/vtables.json)
 */
public class VtableDetect extends GhidraScript {

    private AddressSpace asm;   // set in runVtableDetect; used by labelCandidate

    static final int MIN_SLOTS = 5;
    static final int MAX_SLOTS = 40;
    static final int LABEL_TOP_N = 20;
    static final int HIGH_CONF = 8;
    static final int CLUSTER_PAIR_CAP = 400;
    static final int JSON_CAND_CAP = 6000;
    static final int LONG_SUB_CAP = 12;
    static final long HIGH_DISP = 0x80;   // slot offset threshold for "rare" vcall displacement

    static class Cand {
        long addr;
        int slots;
        long[] ptrs;
        String[] fnNames;
        boolean[] isFuncStart;
        boolean[] inFunc;
        boolean[] isSdk;
        int funcStartCount;
        int sdkCount;
        int matchedAny;    // slot offsets present in vcall disp set (count>=2)
        int matchedHigh;   // slot offsets >= HIGH_DISP present in vcall disp set (count>=2)
        int sharedWith;
        boolean fromLongRun;
        long longRunId;   // head address of the containing >MAX run, or -1 for a clean run
        String dominantNs = "unattributed"; // most common top-level SDK namespace among slots
        int score;
        String conf;
    }

    @Override
    public void run() throws Exception {
        String outPath = (getScriptArgs().length > 0) ? getScriptArgs()[0]
                : "/home/juanr/Proyectos/OpenSpore/docs/analysis/vtables.json";
        try {
            runVtableDetect(outPath);
        } catch (Throwable t) {
            printf("VtableDetect FATAL: %s\n", t);
            t.printStackTrace();
        }
    }

    void runVtableDetect(String outPath) throws Exception {
        asm = currentProgram.getAddressFactory().getDefaultAddressSpace();
        AddressSpace asm = this.asm;
        Memory mem = currentProgram.getMemory();

        // ---- block ranges ----
        List<long[]> execRanges = new ArrayList<>();
        List<long[]> scanRanges = new ArrayList<>();
        List<String> scanNames = new ArrayList<>();
        for (MemoryBlock b : mem.getBlocks()) {
            long s = b.getStart().getOffset();
            long e = b.getEnd().getOffset();
            if (b.isExecute() && b.isRead()) {
                execRanges.add(new long[]{s, e});
            } else if (!b.isExecute() && b.isRead()
                    && (b.getName().equals(".rdata") || b.getName().equals(".data"))) {
                scanRanges.add(new long[]{s, e});
                scanNames.add(b.getName());
            }
        }

        // ---- function maps ----
        TreeMap<Long, String> entryName = new TreeMap<>();
        long[] spanStart = new long[131072];
        long[] spanEnd = new long[131072];
        int spanCount = 0, funcCount = 0;
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctionsNoStubs(false);
        while (fit.hasNext()) {
            try {
                Function f = fit.next();
                funcCount++;
                entryName.put(f.getEntryPoint().getOffset(), f.getName());
                if (spanCount < spanStart.length) {
                    spanStart[spanCount] = f.getEntryPoint().getOffset();
                    spanEnd[spanCount] = f.getBody().getMaxAddress().getOffset();
                    spanCount++;
                }
            } catch (Throwable t) { }
        }
        Integer[] order = new Integer[spanCount];
        for (int i = 0; i < spanCount; i++) order[i] = i;
        Arrays.sort(order, (a, b) -> Long.compare(spanStart[a], spanStart[b]));
        long[] sStart = new long[spanCount];
        long[] sEnd = new long[spanCount];
        for (int i = 0; i < spanCount; i++) { sStart[i] = spanStart[order[i]]; sEnd[i] = spanEnd[order[i]]; }

        // ---- virtual-call displacement histogram over all code ----
        Map<Long, Integer> vcallDisp = new HashMap<>();
        Map<String, Integer> vcallReg = new HashMap<>();
        long instScanned = 0;
        InstructionIterator iit = currentProgram.getListing().getInstructions(true);
        while (iit.hasNext()) {
            try {
                Instruction ins = iit.next();
                instScanned++;
                if ((instScanned & 0x7ffff) == 0) printf("  ... %d instructions scanned\n", instScanned);
                if (!ins.getMnemonicString().equalsIgnoreCase("call")) continue;
                Object[] ops = ins.getOpObjects(0);
                if (ops == null || ops.length < 2) continue;
                if (!(ops[0] instanceof Register)) continue;
                if (!(ops[1] instanceof Scalar)) continue;
                long disp = ((Scalar) ops[1]).getSignedValue();
                if (disp == 0) continue;
                Integer cur = vcallDisp.get(disp);
                vcallDisp.put(disp, cur == null ? 1 : cur + 1);
                Integer rc = vcallReg.get(((Register) ops[0]).getName());
                vcallReg.put(((Register) ops[0]).getName(), rc == null ? 1 : rc + 1);
            } catch (Throwable t) { }
        }

        // ---- vtable candidate scan ----
        List<Cand> cands = new ArrayList<>();
        List<Map<String, Object>> longRuns = new ArrayList<>();
        long wordsScanned = 0;
        for (int bi = 0; bi < scanRanges.size(); bi++) {
            long base = scanRanges.get(bi)[0];
            long end = scanRanges.get(bi)[1];
            int len = (int) (end - base);
            byte[] data = new byte[len];
            int got = 0;
            try { got = mem.getBytes(asm.getAddress(base), data); }
            catch (Throwable t) { printf("  read %s failed: %s\n", scanNames.get(bi), t); continue; }
            int nwords = got / 4;
            int i = 0;
            while (i < nwords) {
                long w = readLE32(data, i * 4);
                if (isCodePtr(w, execRanges)) {
                    int j = i;
                    while (j < nwords && isCodePtr(readLE32(data, j * 4), execRanges)) j++;
                    int runLen = j - i;
                    if (runLen >= MIN_SLOTS && runLen <= MAX_SLOTS) {
                        cands.add(buildCandidate(base + 4L * i, runLen, data, i, entryName, sStart, sEnd, spanCount, false, -1));
                    } else if (runLen > MAX_SLOTS) {
                        Map<String, Object> lr = new LinkedHashMap<>();
                        lr.put("address", hex(base + 4L * i)); lr.put("length", runLen);
                        longRuns.add(lr);
                        emitLongRunSubs(cands, base, data, i, j, entryName, sStart, sEnd, spanCount);
                    }
                    i = j;
                } else {
                    i++;
                }
                wordsScanned++;
            }
            printf("  scanned %s (0x%x..0x%x, %d words)\n", scanNames.get(bi), base, end, nwords);
        }

        // ---- score candidates ----
        for (Cand c : cands) {
            try {
                int fs = 0, sdk = 0;
                for (int k = 0; k < c.slots; k++) { if (c.isFuncStart[k]) fs++; if (c.isSdk[k]) sdk++; }
                c.funcStartCount = fs; c.sdkCount = sdk;
                double fsf = fs / (double) c.slots;
                c.matchedAny = 0; c.matchedHigh = 0;
                for (int k = 0; k < c.slots; k++) {
                    long off = 4L * k;
                    Integer n = vcallDisp.get(off);
                    if (n != null && n >= 2) {
                        c.matchedAny++;
                        if (off >= HIGH_DISP) c.matchedHigh++;
                    }
                }
                int score = 1; // all slots are code pointers
                if (c.slots >= 6) score++;
                if (c.slots >= 12) score++;
                if (fsf >= 0.8) score += 2; else if (fsf >= 0.5) score += 1;
                score += Math.min(sdk, 3);
                if (c.matchedHigh >= 1) score += 3;
                else if (c.matchedAny >= (int) (0.5 * c.slots)) score += 1;
                c.score = score;
            } catch (Throwable t) { c.score = 0; }
        }

        // ---- clustering among top-N by score ----
        cands.sort((a, b) -> Integer.compare(b.score, a.score));
        int nCluster = Math.min(cands.size(), CLUSTER_PAIR_CAP);
        List<Cand> top = new ArrayList<>(cands.subList(0, nCluster));
        for (int a = 0; a < top.size(); a++) {
            Cand ca = top.get(a);
            Set<Integer> shared = new HashSet<>();
            for (int b = a + 1; b < top.size(); b++) {
                Cand cb = top.get(b);
                if (ca.longRunId >= 0 && ca.longRunId == cb.longRunId) continue; // same merged block
                Set<Long> sb = new HashSet<>();
                for (long p : cb.ptrs) sb.add(p);
                int sh = 0;
                for (long p : ca.ptrs) if (sb.contains(p)) sh++;
                if (sh >= 4) shared.add(b);
            }
            ca.sharedWith = shared.size();
            if (ca.sharedWith > 0) ca.score += Math.min(ca.sharedWith, 3);
        }
        // confidence (recompute after shared bonus)
        for (Cand c : cands) {
            boolean highEv = (c.sdkCount >= 1) || (c.sharedWith >= 2) || (c.matchedHigh >= 2);
            c.conf = (highEv && c.score >= HIGH_CONF) ? "HIGH" : (c.score >= 5 ? "MED" : "LOW");
        }
        cands.sort((a, b) -> Integer.compare(b.score, a.score));

        // sibling-family cluster edges (top-N, shared>=4) + inheritance (prefix) chains
        List<Map<String, Object>> clusters = new ArrayList<>();
        List<Map<String, Object>> chains = new ArrayList<>();
        for (int a = 0; a < top.size(); a++) {
            Cand ca = top.get(a);
            for (int b = a + 1; b < top.size(); b++) {
                Cand cb = top.get(b);
                if (ca.longRunId >= 0 && ca.longRunId == cb.longRunId) continue; // same merged block
                Set<Long> sb = new HashSet<>();
                for (long p : cb.ptrs) sb.add(p);
                int sh = 0;
                List<String> shNames = new ArrayList<>();
                for (int k = 0; k < ca.slots; k++) {
                    if (sb.contains(ca.ptrs[k])) {
                        sh++;
                        if (shNames.size() < 6) {
                            String nm = entryName.get(ca.ptrs[k]);
                            shNames.add(nm != null ? nm : "0x" + Long.toHexString(ca.ptrs[k]));
                        }
                    }
                }
                if (sh >= 4) {
                    Map<String, Object> cl = new LinkedHashMap<>();
                    cl.put("a", hex(ca.addr)); cl.put("b", hex(cb.addr));
                    cl.put("sharedSlots", sh); cl.put("sharedFuncs", shNames);
                    clusters.add(cl);
                }
                if (ca.slots < cb.slots && ca.slots >= 4) {
                    boolean prefix = true;
                    for (int k = 0; k < ca.slots; k++) if (ca.ptrs[k] != cb.ptrs[k]) { prefix = false; break; }
                    if (prefix && (cb.slots - ca.slots) <= 20) {
                        Map<String, Object> ch = new LinkedHashMap<>();
                        ch.put("base", hex(ca.addr)); ch.put("baseSlots", ca.slots);
                        ch.put("derived", hex(cb.addr)); ch.put("derivedSlots", cb.slots);
                        ch.put("sharedPrefixLen", ca.slots);
                        chains.add(ch);
                    }
                }
            }
        }
        clusters.sort((x, y) -> Integer.compare((int) y.get("sharedSlots"), (int) x.get("sharedSlots")));

        // ---- label a DIVERSE set of high-confidence candidates ----
        // Pass 1: one representative per dominant SDK namespace (score order) so the
        //   labels span subsystems instead of 20 near-identical slices of one class family.
        // Pass 2: top up remaining slots by score.
        List<Map<String, Object>> labelsSet = new ArrayList<>();
        List<Cand> selected = new ArrayList<>();
        Set<String> selectedNs = new HashSet<>();
        int labelled = 0;
        for (Cand c : cands) {                       // cands already sorted by score desc
            if (labelled >= LABEL_TOP_N) break;
            if (!c.conf.equals("HIGH")) continue;
            if (selectedNs.contains(c.dominantNs)) continue;
            if (labelCandidate(c, labelsSet)) { labelled++; selected.add(c); selectedNs.add(c.dominantNs); }
        }
        for (Cand c : cands) {
            if (labelled >= LABEL_TOP_N) break;
            if (!c.conf.equals("HIGH")) continue;
            boolean already = false;
            for (Cand s : selected) if (s == c) { already = true; break; }
            if (already) continue;
            if (labelCandidate(c, labelsSet)) { labelled++; selected.add(c); }
        }

        // ---- SDK associations for high-confidence ----
        List<Map<String, Object>> sdkAssoc = new ArrayList<>();
        for (Cand c : cands) {
            if (!c.conf.equals("HIGH")) continue;
            List<String> names = new ArrayList<>();
            Set<String> subsys = new HashSet<>();
            for (int k = 0; k < c.slots; k++) {
                if (c.isSdk[k] && c.fnNames[k] != null) {
                    names.add(c.fnNames[k]);
                    int idx = c.fnNames[k].indexOf("::");
                    subsys.add(idx > 0 ? c.fnNames[k].substring(0, idx) : c.fnNames[k]);
                }
            }
            if (!names.isEmpty()) {
                Map<String, Object> sa = new LinkedHashMap<>();
                sa.put("address", hex(c.addr)); sa.put("slots", c.slots);
                sa.put("subsystems", new ArrayList<>(subsys)); sa.put("sdkFuncs", names);
                sdkAssoc.add(sa);
            }
        }

        // ---- emit JSON ----
        StringBuilder js = new StringBuilder();
        js.append("{\n");
        js.append(" \"meta\": {");
        js.append("\"program\": ").append(jstr(currentProgram.getName()));
        js.append(", \"image_base\": \"").append(hex(currentProgram.getImageBase().getOffset())).append("\"");
        js.append(", \"scan_segments\": ").append(jstr(String.join(",", scanNames)));
        js.append(", \"words_scanned\": ").append(wordsScanned);
        js.append(", \"long_runs_gt_max\": ").append(longRuns.size());
        js.append(", \"functions\": ").append(funcCount);
        js.append(", \"instructions_scanned\": ").append(instScanned);
        js.append(", \"distinct_vcall_disps\": ").append(vcallDisp.size());
        js.append(", \"vcall_regs\": {");
        boolean first = true;
        for (Map.Entry<String, Integer> e : vcallReg.entrySet()) {
            if (!first) js.append(", ");
            first = false;
            js.append(jstr(e.getKey())).append(":").append(e.getValue());
        }
        js.append("}");
        js.append(", \"thresholds\": {\"min\":").append(MIN_SLOTS).append(",\"max\":").append(MAX_SLOTS)
          .append(",\"high_conf\":").append(HIGH_CONF).append(",\"label_top_n\":").append(LABEL_TOP_N)
          .append(",\"high_disp\":").append(HIGH_DISP).append("}");
        js.append(" },\n");

        int hi = 0, med = 0, lo = 0;
        for (Cand c : cands) { if (c.conf.equals("HIGH")) hi++; else if (c.conf.equals("MED")) med++; else lo++; }
        js.append(" \"counts\": {\"total\":").append(cands.size())
          .append(", \"high\":").append(hi).append(", \"med\":").append(med).append(", \"low\":").append(lo)
          .append(", \"labelled\":").append(labelled)
          .append(", \"clusters\":").append(clusters.size())
          .append(", \"chains\":").append(chains.size()).append(" },\n");

        int emit = Math.min(cands.size(), JSON_CAND_CAP);
        js.append(" \"candidates\": [");
        for (int i = 0; i < emit; i++) { if (i > 0) js.append(", "); js.append(candJson(cands.get(i))); }
        js.append("],\n");

        int emitCl = Math.min(clusters.size(), 300);
        js.append(" \"clusters\": [");
        for (int i = 0; i < emitCl; i++) { if (i > 0) js.append(", "); js.append(mapJson(clusters.get(i))); }
        js.append("],\n");

        int emitChain = Math.min(chains.size(), 100);
        js.append(" \"inheritance_chains\": [");
        for (int i = 0; i < emitChain; i++) { if (i > 0) js.append(", "); js.append(mapJson(chains.get(i))); }
        js.append("],\n");

        js.append(" \"sdk_associations\": [");
        for (int i = 0; i < sdkAssoc.size(); i++) { if (i > 0) js.append(", "); js.append(mapJson(sdkAssoc.get(i))); }
        js.append("],\n");

        int emitLr = Math.min(longRuns.size(), 200);
        js.append(" \"long_runs\": [");
        for (int i = 0; i < emitLr; i++) { if (i > 0) js.append(", "); js.append(mapJson(longRuns.get(i))); }
        js.append("],\n");

        js.append(" \"labels_set\": [");
        for (int i = 0; i < labelsSet.size(); i++) { if (i > 0) js.append(", "); js.append(mapJson(labelsSet.get(i))); }
        js.append("]\n");
        js.append("}\n");

        String json = js.toString();
        try {
            FileWriter fw = new FileWriter(outPath);
            fw.write(json);
            fw.close();
            printf("WROTE %s (%d bytes)\n", outPath, json.length());
        } catch (Throwable t) {
            printf("WRITE FAIL %s: %s\n", outPath, t);
        }

        printf("\n=== VTABLE DETECT SUMMARY ===\n");
        printf("segments scanned: %s\n", String.join(", ", scanNames));
        printf("words scanned: %d   long runs(>%d): %d\n", wordsScanned, MAX_SLOTS, longRuns.size());
        printf("functions: %d   instructions scanned: %d   distinct vcall disps: %d\n", funcCount, instScanned, vcallDisp.size());
        printf("candidates: total=%d high=%d med=%d low=%d\n", cands.size(), hi, med, lo);
        printf("labelled (top %d HIGH): %d\n", LABEL_TOP_N, labelled);
        printf("clusters(shared>=4): %d   inheritance chains: %d\n", clusters.size(), chains.size());
        printf("top 12 candidates:\n");
        for (int i = 0; i < Math.min(12, cands.size()); i++) {
            Cand c = cands.get(i);
            printf("  %s  slots=%-2d score=%-2d %-4d fsf=%d%% sdk=%d shared=%d highDisp=%d%s  %s\n",
                    hex(c.addr), c.slots, c.score, c.conf == null ? 0 : c.conf.length(),
                    (int) (100.0 * c.funcStartCount / c.slots), c.sdkCount, c.sharedWith, c.matchedHigh,
                    c.fromLongRun ? " [LR]" : "", exampleNames(c, 4));
        }
        printf("DONE\n");
    }

    void emitLongRunSubs(List<Cand> cands, long base, byte[] data, int i, int j,
                          TreeMap<Long, String> entryName, long[] sStart, long[] sEnd, int spanCount) {
        int runLen = j - i;
        long runHead = base + 4L * i;
        long lastStart = -1;
        int emitted = 0;
        // window at the run start (captures the true vtable head, e.g. cAppSystem)
        int L0 = Math.min(MAX_SLOTS, runLen);
        if (L0 >= MIN_SLOTS) {
            cands.add(buildCandidate(runHead, L0, data, i, entryName, sStart, sEnd, spanCount, true, runHead));
            lastStart = runHead;
            emitted++;
        }
        // further sub-windows only at SDK-named function starts, spaced >=64 bytes apart
        // so a single merged block does not produce many near-identical overlapping windows
        for (int s = i + 1; s < j && emitted < LONG_SUB_CAP; s++) {
            long sa = base + 4L * s;
            if (lastStart >= 0 && sa - lastStart < 64) continue;
            long wp = readLE32(data, s * 4);
            String wn = entryName.get(wp);
            if (wn == null || !wn.contains("::")) continue;
            int L = Math.min(MAX_SLOTS, j - s);
            if (L < MIN_SLOTS) break;
            cands.add(buildCandidate(sa, L, data, s, entryName, sStart, sEnd, spanCount, true, runHead));
            lastStart = sa;
            emitted++;
        }
    }

    boolean isCodePtr(long p, List<long[]> execRanges) {
        for (long[] r : execRanges) if (p >= r[0] && p <= r[1]) return true;
        return false;
    }

    long readLE32(byte[] d, int off) {
        return ((d[off] & 0xffL)) | ((d[off + 1] & 0xffL) << 8)
                | ((d[off + 2] & 0xffL) << 16) | ((d[off + 3] & 0xffL) << 24);
    }

    int spanContaining(long a, long[] sStart, long[] sEnd, int n) {
        int lo = 0, hi = n - 1, ans = -1;
        while (lo <= hi) {
            int mid = (lo + hi) >>> 1;
            if (sStart[mid] <= a) { ans = mid; lo = mid + 1; } else hi = mid - 1;
        }
        if (ans >= 0 && a <= sEnd[ans]) return ans;
        return -1;
    }

    Cand buildCandidate(long base, int runLen, byte[] data, int startWord,
                        TreeMap<Long, String> entryName, long[] sStart, long[] sEnd, int spanCount,
                        boolean fromLongRun, long runId) {
        Cand c = new Cand();
        c.addr = base;
        c.slots = runLen;
        c.fromLongRun = fromLongRun;
        c.longRunId = runId;
        c.ptrs = new long[runLen];
        c.fnNames = new String[runLen];
        c.isFuncStart = new boolean[runLen];
        c.inFunc = new boolean[runLen];
        c.isSdk = new boolean[runLen];
        for (int k = 0; k < runLen; k++) {
            long p = readLE32(data, (startWord + k) * 4);
            c.ptrs[k] = p;
            String nm = entryName.get(p);
            if (nm != null) {
                c.isFuncStart[k] = true;
                c.fnNames[k] = nm;
            } else {
                int sp = spanContaining(p, sStart, sEnd, spanCount);
                if (sp >= 0) {
                    c.inFunc[k] = true;
                    c.fnNames[k] = "infunc@0x" + Long.toHexString(p);
                }
            }
            if (c.fnNames[k] != null && c.fnNames[k].contains("::")) c.isSdk[k] = true;
        }
        // dominant top-level SDK namespace among slots (for cross-subsystem diversity)
        Map<String, Integer> nsCount = new HashMap<>();
        for (int k = 0; k < c.slots; k++) {
            String nm = c.fnNames[k];
            if (nm != null && nm.contains("::")) {
                String top = nm.split("::")[0];
                Integer v = nsCount.get(top);
                nsCount.put(top, v == null ? 1 : v + 1);
            }
        }
        int best = 0;
        for (Map.Entry<String, Integer> e : nsCount.entrySet()) if (e.getValue() > best) { best = e.getValue(); c.dominantNs = e.getKey(); }
        return c;
    }

    boolean labelCandidate(Cand c, List<Map<String, Object>> labelsSet) {
        try {
            String name = String.format("VTAB_%08x_%dslots", c.addr, c.slots);
            Address a = asm.getAddress(c.addr);
            currentProgram.getSymbolTable().createLabel(a, name, SourceType.USER_DEFINED);
            Map<String, Object> lm = new LinkedHashMap<>();
            lm.put("address", hex(c.addr)); lm.put("name", name);
            lm.put("slots", c.slots); lm.put("score", c.score);
            lm.put("namespace", c.dominantNs); lm.put("fromLongRun", c.fromLongRun);
            labelsSet.add(lm);
            printf("  LABEL %s  (%d slots, score %d, ns=%s%s)\n",
                    name, c.slots, c.score, c.dominantNs, c.fromLongRun ? " [longRun-sub]" : "");
            return true;
        } catch (Throwable t) {
            printf("  label fail @ %s: %s\n", hex(c.addr), t);
            return false;
        }
    }

    List<String> exampleNames(Cand c, int n) {
        List<String> out = new ArrayList<>();
        for (int k = 0; k < c.slots && out.size() < n; k++)
            if (c.fnNames[k] != null && c.fnNames[k].contains("::")) out.add(c.fnNames[k]);
        for (int k = 0; k < c.slots && out.size() < n; k++)
            if (c.fnNames[k] != null && !c.fnNames[k].startsWith("infunc")) { out.add(c.fnNames[k]); break; }
        return out;
    }

    String candJson(Cand c) {
        StringBuilder sb = new StringBuilder("{");
        sb.append("\"address\":\"").append(hex(c.addr)).append("\"");
        sb.append(", \"slots\":").append(c.slots);
        sb.append(", \"score\":").append(c.score);
        sb.append(", \"confidence\":\"").append(c.conf).append("\"");
        sb.append(", \"fromLongRun\":").append(c.fromLongRun);
        sb.append(", \"namespace\":\"").append(c.dominantNs).append("\"");
        if (c.longRunId >= 0) sb.append(", \"longRunId\":\"").append(hex(c.longRunId)).append("\"");
        sb.append(", \"firstSlotFunc\":").append(jstr(c.fnNames[0]));
        sb.append(", \"funcStartFrac\":").append(String.format("%.2f", 1.0 * c.funcStartCount / c.slots));
        sb.append(", \"sdkCount\":").append(c.sdkCount);
        sb.append(", \"sharedWith\":").append(c.sharedWith);
        sb.append(", \"matchedAny\":").append(c.matchedAny);
        sb.append(", \"matchedHigh\":").append(c.matchedHigh);
        sb.append(", \"slots\":[");
        for (int k = 0; k < c.slots; k++) {
            if (k > 0) sb.append(", ");
            sb.append("{\"ptr\":\"").append(hex(c.ptrs[k])).append("\"");
            sb.append(", \"func\":").append(jstr(c.fnNames[k]));
            sb.append(", \"funcStart\":").append(c.isFuncStart[k]);
            sb.append(", \"inFunc\":").append(c.inFunc[k]);
            sb.append(", \"sdk\":").append(c.isSdk[k]);
            sb.append("}");
        }
        sb.append("]}");
        return sb.toString();
    }

    String mapJson(Map<String, Object> m) {
        StringBuilder sb = new StringBuilder("{");
        boolean first = true;
        for (Map.Entry<String, Object> e : m.entrySet()) {
            if (!first) sb.append(", ");
            first = false;
            sb.append(jstr(e.getKey())).append(":");
            Object v = e.getValue();
            if (v instanceof List) {
                sb.append("[");
                List<?> l = (List<?>) v;
                for (int i = 0; i < l.size(); i++) {
                    if (i > 0) sb.append(", ");
                    sb.append(jstr(String.valueOf(l.get(i))));
                }
                sb.append("]");
            } else if (v instanceof Number || v instanceof Boolean) {
                sb.append(v);
            } else {
                sb.append(jstr(String.valueOf(v)));
            }
        }
        return sb.append("}").toString();
    }

    String hex(long v) {
        return String.format("0x%08x", v);
    }

    String jstr(String s) {
        if (s == null) return "null";
        StringBuilder sb = new StringBuilder("\"");
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch (c) {
                case '"': sb.append("\\\""); break;
                case '\\': sb.append("\\\\"); break;
                case '\n': sb.append("\\n"); break;
                case '\r': sb.append("\\r"); break;
                case '\t': sb.append("\\t"); break;
                default:
                    if (c < 0x20) sb.append(String.format("\\u%04x", (int) c));
                    else sb.append(c);
            }
        }
        return sb.append("\"").toString();
    }
}
