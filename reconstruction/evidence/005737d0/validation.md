# Validation 0x005737d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_input_wave6/editor_input.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 117-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x005737d0; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 117-instruction listing names 1 data address(es) (0x13f5018) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 117-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x28, 0x397), all of which the record accounts for or the listing is the better witness on; the 117-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=117, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x28, 0x397) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 14 displacement(s) (0x28, 0x2c, 0x30, 0x34, 0x38, 0x7c, 0x98, 0xc0, 0xc4, 0x148, 0x2b3, 0x2b4, 0x31c, 0x397), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 12 of those (0x2c, 0x30, 0x34, 0x38, 0x7c, 0x98, 0xc0, 0xc4, 0x148, 0x2b3, 0x2b4, 0x31c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (117 of 117 instruction(s), 0 unparsed) and all 14 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 13 conditional branch target(s) in the complete 117-instruction listing lie inside the recovered body span 0x005737d0..0x00573942, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 117-instruction body names 4 indirect transfer(s): 0x00573843 dispatches slot 0x18 through the table word in EAX; 0x0057389f dispatches slot 0x18 through the table word in EAX; 0x005738ce dispatches slot 0x1c through the table word in EAX; 0x005738dd dispatches slot 0x28 through the table word in EAX; the machine parse consumed 117 of 117 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7a2f2835e74864a91caac0c2cbe19dff38b55e4db496bdffcd7184d0b02ae1f4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e81ff4eebacf70036c63a1ea6786d6e7254404d1ea4b45ed06fe51f3245b213e`
- Pack digest quoted by the briefing: `7a2f2835e74864a91caac0c2cbe19dff38b55e4db496bdffcd7184d0b02ae1f4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `editor runtime hooks, mode/selection vtable ownership, and mouse coordinate interpretation remain runtime-gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- editor runtime hooks, mode/selection vtable ownership, and mouse coordinate interpretation remain runtime-gated
- runtime validation not run
