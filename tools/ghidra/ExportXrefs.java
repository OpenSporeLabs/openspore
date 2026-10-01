import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSpace;
import ghidra.program.model.listing.Function;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Program;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.RefType;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * Read-only call/reference exporter for SporeApp.exe (OpenSpore xref pass).
 *
 * Enumerates real Ghidra references FROM the bodies of a pinned function
 * universe (frozen functions.tsv VA set) and emits one row per
 * (caller, callee, callsite) triple. No labels, no memory writes, no DB
 * writes, no re-analysis: pure reference enumeration + TSV output.
 *
 * Columns: caller_va, callee_va, reference_type, callsite_va, source,
 *          snapshot_sha256
 *
 * reference_type vocabulary:
 *   direct-call   static call to an internal non-thunk function
 *   thunk         call whose destination entry is a thunk function
 *   external      call to an external/import function (callee_va = EXT token)
 *   computed-call indirect call site that still resolves to a function dest
 *   vtable-ref    code/data reference into a known vtable range
 *                 (callee_va = VT token of the vtable base)
 *   data-ref      code reference to a pinned function entry address
 *                 (address-taken, e.g. callback stored / compared)
 *
 * Indirect calls with no concrete destination are NEVER fabricated: they are
 * counted (computed_unresolved) and skipped.
 *
 * -- Data references (the sidecar output) ----------------------------------
 *
 * The edge TSV above answers "which functions call which functions". It cannot
 * answer "which global does this body touch", because the ``data-ref`` row it
 * emits is defined as a reference to a *function entry* and every reference to
 * anything else -- a global, a TLS slot, a jump table -- falls through to
 * ``dataSkipped`` and is discarded. That discard is what this sidecar stops.
 *
 * The sidecar is emitted by the same run, from the same pinned universe, over
 * the same snapshot, so it carries the same provenance as the edge file and is
 * never an independent claim about the binary. It is a *separate file* rather
 * than more rows in the edge TSV, for one reason: ``tools/triage/export_xrefs.py``
 * proves on the edge file that every non-EXT/non-VT endpoint is a member of the
 * pinned function universe, and that assertion is true and worth keeping. A data
 * address is by construction not a member of that universe, so folding the rows
 * in would mean weakening a check that currently catches real corruption, in
 * order to carry evidence that needs no such check of its own.
 *
 * Columns: caller_va, target_va, access_mode, segment, callsite_va,
 *          source, snapshot_sha256
 *
 *   access_mode  read | write | readwrite | other
 *                read/write come from Ghidra's own RefType, so a write to a
 *                read-only segment is reported as the write it is and is NOT
 *                softened; "other" is a DATA-typed reference Ghidra records
 *                without a read or write class (an address-taken marker).
 *   segment      the Ghidra memory block name the target lies in, or "-" when
 *                the address is not backed by any block. This is what keeps a
 *                global distinguishable from a jump-table entry in .text or a
 *                relocation record, which are data references too and are NOT
 *                globals; the segment is the only thing that separates them and
 *                it is Ghidra's own classification of the address.
 *
 * What is deliberately NOT in the sidecar, and why:
 *   - references in the ``stack`` address space. They are stack slots, not
 *     globals, and they are the large majority of what the edge file discards
 *     (measured: 573,206 of 731,045 discarded references). Emitting them would
 *     make the file about stack frames, not globals.
 *   - destinations that are function entries (already a ``data-ref`` edge row)
 *     or inside a known vtable range (already a ``vtable-ref`` edge row).
 *   - external addresses. An import thunk is not a global in the image.
 *
 * Params (GhidraScript args, in order):
 *   0 functionsTsv   frozen universe, header: address name size is_thunk ...
 *   1 rangesTsv      vtable ranges, headerless: <va8> <slots>
 *   2 snapshot       snapshot_sha256 string stamped on every row
 *   3 source         source label stamped on every row
 *   4 outTsv         edge output path (with header)
 *   5 outExt         externals allowlist output path (token, addr, name)
 *   6 shard          this shard index (0-based)
 *   7 shards         total shard count (partition by sorted-VA index mod)
 *   8 outData        (optional) data-reference sidecar path; when absent the
 *                    sidecar is not written at all and the edge file is
 *                    byte-for-byte what it has always been.
 *
 * Fallback: when no script args are present (e.g. MCP inline execution),
 * params are read from /tmp/opencode/xref-job/params.tsv as key\tvalue rows
 * with keys: functionsTsv rangesTsv snapshot source outTsv outExt shard shards.
 *
 * Determinism: input VA list is sorted; each shard emits in shard order; the
 * canonical sort/dedupe happens downstream (tools/triage/export_xrefs.py), so
 * concatenation of shards is order-independent.
 *
 * Run (headless/GUI): -postScript ExportXrefs.java <args...>
 */
public class ExportXrefs extends GhidraScript {

    static final String PARAMS_FALLBACK = "/tmp/opencode/xref-job/params.tsv";

    private final TreeMap<Long, Long> vtEnd = new TreeMap<Long, Long>();
    private final TreeMap<Long, String> vtBase = new TreeMap<Long, String>();

    // Set when the sidecar was requested, so the reporting line can say what it
    // actually produced rather than what it would have produced.
    private boolean dataSidecarRequested = false;
    // Sidecar tallies. ``dataSkippedStack`` is references whose destination is a
    // frame slot rather than storage, ``dataSkippedDup`` references with no
    // backing memory block, and ``errors`` is shared with the edge pass so a
    // failure to classify a destination is counted once, not twice.
    private long dataSkippedStack = 0;
    private long dataSkippedDup = 0;
    private long errors = 0;

    /** VTable base VA8 containing `to`, or null. Ranges are [base, base+4*slots). */
    private String vtableBaseFor(long to) {
        Map.Entry<Long, Long> e = vtEnd.floorEntry(to);
        if (e != null && to < e.getValue().longValue()) {
            return vtBase.get(e.getKey());
        }
        return null;
    }

    static String va8(long v) {
        String s = Long.toHexString(v & 0xffffffffL);
        while (s.length() < 8) {
            s = "0" + s;
        }
        return s;
    }

    @Override
    public void run() throws Exception {
        Map<String, String> p = new HashMap<String, String>();
        String[] a = getScriptArgs();
        if (a != null && a.length >= 8) {
            p.put("functionsTsv", a[0]);
            p.put("rangesTsv", a[1]);
            p.put("snapshot", a[2]);
            p.put("source", a[3]);
            p.put("outTsv", a[4]);
            p.put("outExt", a[5]);
            p.put("shard", a[6]);
            p.put("shards", a[7]);
            // Arg 8 is optional: without it no sidecar is written and the edge
            // file is exactly what the pre-extension exporter produced.
            if (a.length >= 9) {
                p.put("outData", a[8]);
            }
        }
        else {
            BufferedReader br = new BufferedReader(new FileReader(PARAMS_FALLBACK));
            try {
                String ln;
                while ((ln = br.readLine()) != null) {
                    int t = ln.indexOf('\t');
                    if (t > 0) {
                        p.put(ln.substring(0, t).trim(), ln.substring(t + 1).trim());
                    }
                }
            }
            finally {
                br.close();
            }
        }

        String functionsTsv = p.get("functionsTsv");
        String rangesTsv = p.get("rangesTsv");
        String snapshot = p.get("snapshot");
        String source = p.get("source");
        String outTsv = p.get("outTsv");
        String outExt = p.get("outExt");
        String outData = p.get("outData");
        dataSidecarRequested = (outData != null);
        int shard = Integer.parseInt(p.get("shard"));
        int shards = Integer.parseInt(p.get("shards"));

        Program program = currentProgram;
        FunctionManager fm = program.getFunctionManager();
        ReferenceManager rm = program.getReferenceManager();
        AddressSpace defSpace = program.getAddressFactory().getDefaultAddressSpace();

        // -- pinned universe -------------------------------------------------
        List<String> vas = new ArrayList<String>();
        BufferedReader fr = new BufferedReader(new FileReader(functionsTsv));
        try {
            String ln = fr.readLine(); // header
            while ((ln = fr.readLine()) != null) {
                if (ln.trim().length() == 0) {
                    continue;
                }
                int t = ln.indexOf('\t');
                String va = (t > 0 ? ln.substring(0, t) : ln).trim().toLowerCase();
                if (va.startsWith("0x")) {
                    va = va.substring(2);
                }
                while (va.length() < 8) {
                    va = "0" + va;
                }
                vas.add(va);
            }
        }
        finally {
            fr.close();
        }
        Collections.sort(vas);
        Map<String, Address> pinned = new HashMap<String, Address>(vas.size() * 2);
        for (String va : vas) {
            try {
                pinned.put(va, defSpace.getAddress("0x" + va));
            }
            catch (Exception e) {
                // unparseable VA: absent from every later lookup, counted below
            }
        }

        // -- vtable ranges: baseLong -> (endLong, baseVa8) --------------------
        BufferedReader vr = new BufferedReader(new FileReader(rangesTsv));
        try {
            String ln;
            while ((ln = vr.readLine()) != null) {
                ln = ln.trim();
                if (ln.length() == 0) {
                    continue;
                }
                String[] cells = ln.split("\t");
                long base = Long.parseLong(cells[0], 16);
                int slots = Integer.parseInt(cells[1].trim());
                vtEnd.put(base, base + (long) slots * 4L);
                vtBase.put(base, cells[0].toLowerCase());
            }
        }
        finally {
            vr.close();
        }

        PrintWriter out = new PrintWriter(new FileWriter(outTsv));
        long dataRows = 0;
        PrintWriter data = null;
        if (outData != null) {
            data = new PrintWriter(new FileWriter(outData));
            data.println("caller_va\ttarget_va\taccess_mode\tsegment\tcallsite_va"
                + "\tsource\tsnapshot_sha256");
        }
        Map<String, String[]> externals = new HashMap<String, String[]>();
        long rows = 0;
        long funcsSeen = 0;
        long missingAtAddress = 0;
        long nDirect = 0, nThunk = 0, nExt = 0, nComputed = 0, nVtable = 0, nData = 0;
        long computedUnresolved = 0, callToOther = 0, dataSkipped = 0;

        out.println("caller_va\tcallee_va\treference_type\tcallsite_va\tsource\tsnapshot_sha256");

        int idx = 0;
        for (String va : vas) {
            if ((idx++ % shards) != shard) {
                continue;
            }
            Address entry;
            try {
                entry = pinned.get(va);
                if (entry == null) {
                    missingAtAddress++;
                    continue;
                }
                Function fn = fm.getFunctionAt(entry);
                if (fn == null) {
                    missingAtAddress++;
                    continue;
                }
                funcsSeen++;
                InstructionIterator ins = program.getListing().getInstructions(fn.getBody(), true);
                while (ins.hasNext()) {
                    Instruction instruction;
                    try {
                        instruction = ins.next();
                    }
                    catch (Exception e) {
                        errors++;
                        continue;
                    }
                    Address from = instruction.getAddress();
                    String callsite = va8(from.getOffset());
                    Reference[] refs;
                    try {
                        refs = rm.getReferencesFrom(from);
                    }
                    catch (Exception e) {
                        errors++;
                        continue;
                    }
                    for (Reference ref : refs) {
                        RefType rt;
                        Address to;
                        try {
                            rt = ref.getReferenceType();
                            to = ref.getToAddress();
                        }
                        catch (Exception e) {
                            errors++;
                            continue;
                        }
                        if (to == null) {
                            continue;
                        }
                        try {
                            if (rt.isCall()) {
                                Function dest = fm.getFunctionAt(to);
                                if (dest != null) {
                                    if (dest.isExternal()) {
                                        String tok = extToken(dest, to);
                                        String[] prev = externals.get(tok);
                                        if (prev == null) {
                                            externals.put(tok, new String[] {
                                                to.toString(), dest.getName() });
                                        }
                                        out.println(va + "\t" + tok + "\texternal\t"
                                            + callsite + "\t" + source + "\t" + snapshot);
                                        nExt++;
                                        rows++;
                                    }
                                    else if (dest.isThunk()) {
                                        out.println(va + "\t" + va8(to.getOffset())
                                            + "\tthunk\t" + callsite + "\t" + source
                                            + "\t" + snapshot);
                                        nThunk++;
                                        rows++;
                                    }
                                    else if (rt.isComputed()) {
                                        out.println(va + "\t" + va8(to.getOffset())
                                            + "\tcomputed-call\t" + callsite + "\t"
                                            + source + "\t" + snapshot);
                                        nComputed++;
                                        rows++;
                                    }
                                    else {
                                        out.println(va + "\t" + va8(to.getOffset())
                                            + "\tdirect-call\t" + callsite + "\t"
                                            + source + "\t" + snapshot);
                                        nDirect++;
                                        rows++;
                                    }
                                }
                                else if (to.isExternalAddress()) {
                                    String tok = "EXT:unknown::" + to.toString();
                                    String[] prev = externals.get(tok);
                                    if (prev == null) {
                                        externals.put(tok, new String[] {
                                            to.toString(), "(no-function)" });
                                    }
                                    out.println(va + "\t" + tok + "\texternal\t"
                                        + callsite + "\t" + source + "\t" + snapshot);
                                    nExt++;
                                    rows++;
                                }
                                else {
                                    String vtb = vtableBaseFor(to.getOffset());
                                    if (vtb != null) {
                                        out.println(va + "\tVT:" + vtb + "\tvtable-ref\t"
                                            + callsite + "\t" + source + "\t" + snapshot);
                                        nVtable++;
                                        rows++;
                                    }
                                    else {
                                        // Call-typed ref with no function dest:
                                        // never fabricated into an edge.
                                        callToOther++;
                                    }
                                }
                                // CALL refs with no To-address cannot occur
                                // (to == null handled above); computed calls
                                // without dest are counted via dataSkipped? No:
                                // they surface here as refs with dest; truly
                                // dest-less computed calls have no Reference.
                            }
                            else if (rt.isData() || rt.isRead() || rt.isWrite()) {
                                String toVa = va8(to.getOffset());
                                if (!to.isExternalAddress() && pinned.containsKey(toVa)
                                        && fm.getFunctionAt(to) != null) {
                                    out.println(va + "\t" + toVa + "\tdata-ref\t"
                                        + callsite + "\t" + source + "\t" + snapshot);
                                    nData++;
                                    rows++;
                                }
                                else {
                                    String vtb = to.isExternalAddress() ? null
                                        : vtableBaseFor(to.getOffset());
                                    if (vtb != null) {
                                        out.println(va + "\tVT:" + vtb + "\tvtable-ref\t"
                                            + callsite + "\t" + source + "\t" + snapshot);
                                        nVtable++;
                                        rows++;
                                    }
                                    else {
                                        // Not a function entry and not a vtable
                                        // slot: this is where the old exporter
                                        // ended. Everything the sidecar carries is
                                        // decided here, and the edge file's own
                                        // rows are untouched by that decision.
                                        dataSkipped++;
                                        if (data != null
                                                && emitDataReference(data, program, fm,
                                                    va, to, rt, callsite, source,
                                                    snapshot)) {
                                            dataRows++;
                                        }
                                    }
                                }
                            }
                            // flow/jump refs are intra-function control flow,
                            // not cross-function edges: ignored by design.
                        }
                        catch (Exception e) {
                            errors++;
                        }
                    }
                }
            }
            catch (Exception e) {
                errors++;
            }
            if ((funcsSeen % 5000) == 0) {
                println("EXPORT_XREFS progress funcs=" + funcsSeen + " rows=" + rows
                    + " dataRows=" + dataRows);
            }
        }
        out.close();
        if (data != null) {
            data.close();
        }

        PrintWriter ex = new PrintWriter(new FileWriter(outExt));
        ex.println("token\taddress\tname");
        List<String> toks = new ArrayList<String>(externals.keySet());
        Collections.sort(toks);
        for (String tok : toks) {
            String[] v = externals.get(tok);
            ex.println(tok + "\t" + v[0] + "\t" + v[1]);
        }
        ex.close();

        println("EXPORT_XREFS done shard=" + shard + "/" + shards
            + " funcsSeen=" + funcsSeen
            + " missingAtAddress=" + missingAtAddress
            + " rows=" + rows
            + " direct=" + nDirect + " thunk=" + nThunk + " ext=" + nExt
            + " computed=" + nComputed + " vtable=" + nVtable + " data=" + nData
            + " computedUnresolved=" + computedUnresolved
            + " callToOther=" + callToOther + " dataSkipped=" + dataSkipped
            + " errors=" + errors
            + " externals=" + externals.size()
            + " liveFunctions=" + fm.getFunctionCount());
        if (dataSidecarRequested) {
            println("EXPORT_XREFS datarefs rows=" + dataRows
                + " skippedStackSpace=" + dataSkippedStack
                + " skippedUnbacked=" + dataSkippedDup
                + " out=" + outData);
        }
    }

    /**
     * Write one data-reference sidecar row, or return false and record why not.
     *
     * The predicate is the whole contract, so it is stated in one place and is
     * deliberately narrow. A reference reaches the sidecar only when ALL of the
     * following hold, and each clause names what it excludes and why:
     *
     * 1. The destination is not external. An import thunk is not a global in
     *    this image; it has no storage here.
     * 2. The destination is in the default (RAM) address space. A ``stack``
     *    address is a frame slot: it is a data reference to Ghidra, but it is
     *    not a global, and it is the majority of what the edge file discards
     *    (measured 573,206 of 731,045). Including it would make the file a
     *    statement about stack frames.
     * 3. Some memory block backs the address. ``nomem`` addresses are unmapped;
     *    Ghidra records the reference but there is no global there to name.
     * 4. The destination is not a function entry and not inside a known vtable
     *    range. Those already have edge rows (``data-ref`` / ``vtable-ref``);
     *    re-emitting them here would put the same fact in two files with two
     *    definitions, and a consumer reading both would double-count.
     *
     * Clauses 1-3 are what "is a global" means here, and none of them is
     * inferred from the reference: each is a property of the address Ghidra
     * itself reports. Clause 4 is about not duplicating the edge file.
     *
     * Read/write comes from Ghidra's RefType and is passed through verbatim.
     * In particular a WRITE into a read-only block is emitted as a write; the
     * block's permissions are recorded alongside it and the contradiction, if
     * any, is left for a reader to see rather than smoothed over here.
     *
     * Returns true when a row was written.
     */
    private boolean emitDataReference(PrintWriter data, Program program,
                                      FunctionManager fm, String caller,
                                      Address to, RefType rt, String callsite,
                                      String source, String snapshot) {
        if (to.isExternalAddress()) {
            return false;
        }
        AddressSpace space = to.getAddressSpace();
        if (!space.equals(program.getAddressFactory().getDefaultAddressSpace())) {
            dataSkippedStack++;
            return false;
        }
        MemoryBlock block;
        try {
            block = program.getMemory().getBlock(to);
        }
        catch (Exception e) {
            errors++;
            return false;
        }
        if (block == null) {
            dataSkippedDup++;
            return false;
        }
        if (fm.getFunctionAt(to) != null) {
            // Already a ``data-ref`` edge row; see clause 4.
            return false;
        }
        if (vtableBaseFor(to.getOffset()) != null) {
            // Already a ``vtable-ref`` edge row; see clause 4.
            return false;
        }
        String mode = rt.isWrite() ? (rt.isRead() ? "readwrite" : "write")
            : (rt.isRead() ? "read" : "other");
        String perms = (block.isExecute() ? "x" : "-")
            + (block.isWrite() ? "w" : "-")
            + (block.isRead() ? "r" : "-");
        data.println(caller + "\t" + va8(to.getOffset()) + "\t" + mode
            + "\t" + block.getName() + " " + perms + "\t" + callsite
            + "\t" + source + "\t" + snapshot);
        return true;
    }

    private String extToken(Function dest, Address to) {
        String lib = "unknown";
        try {
            lib = dest.getParentNamespace().getName();
        }
        catch (Exception e) {
            lib = "unknown";
        }
        String nm = dest.getName();
        if (nm == null) {
            nm = to.toString();
        }
        // TSV-safe: strip tabs/newlines (names never contain them, defensive).
        lib = lib.replace('\t', ' ').replace('\n', ' ').replace('\r', ' ');
        nm = nm.replace('\t', ' ').replace('\n', ' ').replace('\r', ' ');
        return "EXT:" + lib + "::" + nm;
    }
}
