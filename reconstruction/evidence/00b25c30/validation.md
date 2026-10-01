# Validation 0x00b25c30

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 39-instruction listing names 1 data address(es) (0x18c43e8) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 5 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (39 of 39 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 39-instruction listing lie inside the recovered body span 0x00b25c30..0x00b25c92, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 39-instruction body names 1 indirect transfer(s): 0x00b25c79 dispatches slot 0x58 through the table word in EDX; the machine parse consumed 39 of 39 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ff0c271096d29e34d933615302582880f358a6937560ee799f9f70045d080790`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5bf3140ebb7f878e929953fefcbf779256009e5c35c8c5b1e32defb319950f23`
- Pack digest quoted by the briefing: `ff0c271096d29e34d933615302582880f358a6937560ee799f9f70045d080790`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential fixture would need a real registry populated through the get-or-create helper, which static evidence alone cannot supply.`, `No original-process trace exists for this address, so the runtime contents of the registry container, the runtime value of the .bss key 0x018c43e8 and the real distribution of predicate answers are all unverified.`, `The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential fixture would need a real registry populated through the get-or-create helper, which static evidence alone cannot supply.
- Is the container returned by the helper ever null? The body dereferences it immediately at 0x00b25c53, so a null return would fault; the reconstruction preserves that rather than adding a guard.
- No original-process trace exists for this address, so the runtime contents of the registry container, the runtime value of the .bss key 0x018c43e8 and the real distribution of predicate answers are all unverified.
- No original-process trace exists, so the runtime contents of the registry and the real distribution of predicate answers are unverified.
- The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.
- What are the four unreported callsites at 0x00cee1f3, 0x00cfd794, 0x00cfd7b7 and 0x00ea72e1, which lie outside any Ghidra function body?
- What class owns this function? 26 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.
- What does the get-or-create helper 0x00b21340 actually do, and what is its element type? Its map at this+0x98 and list at this+0x78 and its five callbacks are observed, but no element type was established, so it is kept as an opaque port rather than guessed.
- What is the concrete callee at vtable slot +0x58 of the element's +0x120 interface? No element instance and therefore no table address was ever observed statically.
- What is the element type, and what is the interface at element+0x120? Only the vtable load and the slot offset are observed. Callers show the element itself is polymorphic with an interface at +0x34 whose slot +0x48 is dispatched at 0x00e08285, so the element carries at least two embedded interfaces.
- What is the runtime value of the .bss key 0x018c43e8? It reads 0 in the file image and is populated only at runtime.
- Which of the five immediates is the lookup key and which are callbacks? The push order and the callee's five-argument frame are established, but the per-argument role assignment inside 0x00b21340 was not fully resolved and is therefore not asserted.
