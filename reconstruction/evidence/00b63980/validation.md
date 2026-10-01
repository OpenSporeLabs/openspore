# Validation 0x00b63980

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_misc_engine/misc_engine.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 12-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00b63980; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field vtable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 12-instruction listing lie inside the recovered body span 0x00b63980..0x00b639a1, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `FAIL` | `partial` | the complete 12-instruction body contains no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, but the source span declares a virtual-slot boundary |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'OpaqueDestructible*' and the machine return state is WIDTH_4_IN_EAX: the complete 12-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0b5eb717d5e43482f006c21d081e7db8c1d7065b06d0355137094ec9c7491d42`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e6a003f47846d1df88340c0280a4e1b8f5b2c53f9d5186e0219f904b29315e8e`
- Pack digest quoted by the briefing: `0b5eb717d5e43482f006c21d081e7db8c1d7065b06d0355137094ec9c7491d42`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-deleting-destructor-vtable-and-global-delete`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the function a scalar deleting destructor, a generated adapter, or a differently named lifecycle thunk?
- What allocator, reference-count, and destruction behavior is hidden in 0x00f47380 and 0x009276c0?
- What object state does 0x005725a0 destroy beyond its vtable write?
- What runtime vtable path reaches the function despite zero direct callers?
- Which concrete class owns the vtable at 0x01464450?
- base and global-delete effects
- concrete vtable owner
- gate-deleting-destructor-vtable-and-global-delete
- runtime vtable reachability
- whether the entry is a scalar deleting destructor or generated lifecycle thunk
