# Validation 0x00c47cc0

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
| GLOBALS | `WARN` | `partial` | the complete 43-instruction listing names 2 data address(es) (0x13eb844, 0x13eb90c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 5 the complete 43-instruction listing names through ECX (0x84, 0x14c, 0x150, 0x15c, 0x160) are all within the machine-derived receiver bounds (0x84, 0x14c, 0x150, 0x15c, 0x160), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (43 of 43 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 43-instruction listing lie inside the recovered body span 0x00c47cc0..0x00c47d6f, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 43-instruction body names 1 indirect transfer(s): 0x00c47d62 dispatches slot 0x14 through the table word in EDX; the machine parse consumed 43 of 43 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 1 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e62e82e3094b5b86f1040cd9564c1016a352caf0f26760b21f69d711b5d53575`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ea8041ed4c875c7c03bf970779b2af969d3d0ac61ddf35507d32234abe180816`
- Pack digest quoted by the briefing: `e62e82e3094b5b86f1040cd9564c1016a352caf0f26760b21f69d711b5d53575`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential fixture would need a real receiver plus a populated app-system singleton, neither of which static evidence supplies.`, `No original-process trace exists for this address. In particular 0x015fd890 was never observed populated, so the app-system slot +0x14 callee is unknown at runtime as well as statically.`, `The Cell stage has never been entered in any recorded run, so the real distribution of state values and the real contents of the two wide buffers are unverified.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential fixture would need a real receiver plus a populated app-system singleton, neither of which static evidence supplies.
- Is the dead store at 0x00c47d28 (0x013eb90c) meaningful to any runtime patching or vtable interposition scheme, or is it plain compiler residue?
- No original-process trace exists for this address. In particular 0x015fd890 was never observed populated, so the app-system slot +0x14 callee is unknown at runtime as well as statically.
- No original-process trace exists, so the state-value distribution and the buffer contents are unverified.
- The Cell stage has never been entered in any recorded run, so the real distribution of state values and the real contents of the two wide buffers are unverified.
- What are the two wide buffers at receiver+0x14c/+0x150 and +0x15c/+0x160, and what populates them? Only the reset shape is observed; no producer of their contents was located in this batch.
- What class is the stack temporary? Its vtable 0x013eb844 has three dwords and is followed by the 'queuing %ls for bake' format string, and its destructor walks 32 masked pairs, but no class name is asserted.
- What class owns this function? 18 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.
- What do the state values mean? Values 1, 2, 3, 5, 6, 7, 8, 9 and one dynamically forwarded value are attested; 0, 4 and negatives are not excluded. No enum name is claimed.
- What is 0x038cf2fd? It is below the image base so it cannot be a pointer, and it is passed as the callee's first argument. It is a key or id of unknown derivation.
- What is the concrete callee at app-system vtable slot +0x14? 0x015fd890 is zero in the file image, so no table address was ever observable.
- Why does the state-3 path pass 0 as the third argument and a non-null pointer as the second? The callee signature beyond those three dwords is unknown.
