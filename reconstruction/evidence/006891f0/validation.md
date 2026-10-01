# Validation 0x006891f0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 239-instruction listing names 1 data address(es) (0x1403204) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (239 of 239 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 20 conditional branch target(s) in the complete 239-instruction listing lie inside the recovered body span 0x006891f0..0x006894ca, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 239-instruction body names 1 indirect transfer(s): 0x00689220 dispatches slot 0x28 through the table word in EDX; the machine parse consumed 239 of 239 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0745e7d192831a0c3046dfc5e45eab7ba3398bd12df86a4de0933e35753628ec`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `45838f3a4a9ea00935595c64b793fe28cfd115a91356077b2506d5117d4bd18d`
- Pack digest quoted by the briefing: `0745e7d192831a0c3046dfc5e45eab7ba3398bd12df86a4de0933e35753628ec`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A trace must record the return value and the observable effect of 0x00932ae0 on the base path, which is the only way to resolve whether the leading delete is live behaviour or a no-op.`, `A trace must record whether MoveFileExW at 0x00689406 succeeds in practice, because the body discards the result and static analysis cannot predict the filesystem state.`, `No original-process trace exists for this function. A differential trace must record the string returned by the save-area virtual slot +0x28, since the whole path algebra depends on whether it is separator-terminated.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A trace must record the return value and the observable effect of 0x00932ae0 on the base path, which is the only way to resolve whether the leading delete is live behaviour or a no-op.
- A trace must record whether MoveFileExW at 0x00689406 succeeds in practice, because the body discards the result and static analysis cannot predict the filesystem state.
- Do the callers at 0x00580dc9 and 0x00b293d4 pass names with an embedded separator, given that the concatenation inserts none? Their arguments are stack buffers whose contents were not read.
- Is the promote-and-delete sequence ever observed to run with a destination that does not exist, i.e. is the first-time-install path exercised? Static analysis cannot tell.
- No original-process trace exists for this function. A differential trace must record the string returned by the save-area virtual slot +0x28, since the whole path algebra depends on whether it is separator-terminated.
- What does virtual slot +0x28 on the save area return, and does it end with a path separator? The receiver is constructed at runtime so no string was read.
- What is 0x00932960, the routine 0x00932ae0 delegates to for a non-directory path? Not decompiled in this pass.
- What is the original function name and owning class? Nothing in the binary or the SDK names it.
- Why are the two exists/delete branches guarded while the promotion is not? The asymmetry may be deliberate (best-effort cleanup) or an oversight; the binary does not say.
- Why is a recursive delete issued on the save-area base path at 0x00689286, before any file is moved into it? The argument is proven to be that path, but the intent is not recoverable from the binary. Either the path returned by slot +0x28 is a file rather than a directory, or the delete is intended to clear a stale folder whose recreation is handled elsewhere, or the call is dead in the shipping build because its result is discarded.
