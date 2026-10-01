# Validation 0x0067e6f0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-cheat-dispatch-0067e6f0/cheat_dispatch_0067e6f0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 26-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x0067e6f0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 26-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 3 displacement(s) (0x4c, 0x50, 0x64) and every one of them is a displacement the complete 26-instruction listing shows: 3 attributed to the receiver ECX as proven (0x4c, 0x50, 0x64); the 26-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=26, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x4c, 0x50, 0x64) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x50, 0x60, 0x64), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x60) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x4c), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (26 of 26 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 26-instruction listing lie inside the recovered body span 0x0067e6f0..0x0067e726, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 26-instruction body names 1 indirect transfer(s): 0x0067e712 dispatches slot 0x1c through the table word in EAX; the machine parse consumed 26 of 26 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ffc36453ffba0906da160810be64a4139e3c5e06daebb7a64cce2ffa943f3e71`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8a425c49b98f618736a3c40c55d0aaea54ed6dc32bfaa863e41b8924cdd061ac`
- Pack digest quoted by the briefing: `ffc36453ffba0906da160810be64a4139e3c5e06daebb7a64cce2ffa943f3e71`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does the dispatched receiver mutate the chain during the walk? This body holds no lock, re-reads nothing, and compares the link it was handed, so a mutation would be its own problem.
- Is the chain intrusive (each node embedding the link word) or does 0x00921580 walk an external structure? The link word is not read by this body either way.
- Is the table reached through the node word at +0x10 and then +0x1c a dispatch table (a vtable) in the strict sense? Nothing in the machine record says so, so the reconstruction calls it a call table and names no slot.
- What are the two stack arguments at the indirect call? The leading word is the literal 1 and the trailing one is this function's own stack argument; their meaning is not established.
- What does the byte at receiver+0x64 gate, and which code path sets it? Nothing in this 26-instruction body writes it.
- What is 0x00921580, where does it live, and what link does it read to return the next node? The body only shows one node in, one word out, caller-cleaned.
- What is the entry_ESP+0x4 argument semantically, and who supplies it? The xref export records no call edge into this function, so the only known reference is the data reference at 0x01401bb4.
- Which concrete receiver types are stored at node+0x10, and which concrete function is at table+0x1c for each of them?
