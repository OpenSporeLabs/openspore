# Validation 0x006417d0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-006417d0/swarm_w1_006417d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 23-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 1 distinct address(es) for 0x006417d0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 23-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 1 displacement(s) (0x1c) and every one of them is a displacement the complete 23-instruction listing shows: 1 attributed to the receiver ECX as proven (0x1c); the 23-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=23, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x1c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x1c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (23 of 23 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 23-instruction listing lie inside the recovered body span 0x006417d0..0x00641809, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 23-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3d62abf59c0c65ec9cc3c7da3f8a3388f76e3869cef439c55fde2b1999a77fde`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `404f136cb2f62da38049e930036764b96d0e7e5fd7295c82f3a08207686f33a5`
- Pack digest quoted by the briefing: `3d62abf59c0c65ec9cc3c7da3f8a3388f76e3869cef439c55fde2b1999a77fde`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does 0x005507a0 ever return a null pointer to a real caller? This body does not test the return value, only the receiver word, and the model test deliberately never scripts a null return because the only way to observe the difference would be a fault.
- Does any real callee in the game ever write the receiver's +0x1c word, so that the reload at 0x006417ea differs from the load at 0x006417d3 in practice? The model test proves only that the MODEL re-reads it, which is what the instruction fixes.
- Is the object's class cSPAssetDataOTDB, a derived class, or neither? The body is installed in six distinct tables, which says at least that the layout is shared, but this body has no MSVC RTTI to read and no vtable pass has been run in this image.
- The SDK-imported label Sporepedia::cSPAssetDataOTDB::GetAssetID sits on 0x006417c0, whose live bytes are `FLD DWORD PTR [0x013eb1bc]; RET` -- an x87 constant that cannot implement `bool GetAssetID(uint64_t&)`. This body's shape (byte-sized bool in AL, one out pointer, RET 4, an 8-byte non-sentinel pair) is exactly what that SDK signature describes, and 0x006417c0 sits at dword index 15 of the table at 0x013ff648 while this body sits at index 11 of six other tables. That is suggestive, not decisive: the SDK address map and the vtable orderings could each be off, and this package cannot adjudicate. No name is asserted; the export is re_006417d0.
- The absolute stack distance from the model's entry to the accessor's entry is 16 in the machine but a property of the -O0 frame GCC generates, so it is not asserted; see the model test's not-asserted list for what replaces it.
- What are the two dwords that 0x005507a0 returns? The 0xffffffff/0xffffffff sentinel says only that the pair has an invalid state; the image offers no name, no constant and no string for it in this body.
