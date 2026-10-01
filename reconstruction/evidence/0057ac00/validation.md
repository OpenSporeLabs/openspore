# Validation 0x0057ac00

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 166-instruction listing names 1 data address(es) (0x15fd918) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 166-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 5 displacement(s) (0x24, 0x98, 0x2a8, 0x4b1, 0x4b2), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (166 of 166 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 15 conditional branch target(s) in the complete 166-instruction listing lie inside the recovered body span 0x0057ac00..0x0057ae01, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 166-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6b7427f646045602fed83d43ddfffc7b5c0cc016b5a69581bf934caa7adb65d0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6d7c37744fe31d1b38e508ce99ddeb7d140c97d1fd4f6f83c99f696678d4142c`
- Pack digest quoted by the briefing: `6b7427f646045602fed83d43ddfffc7b5c0cc016b5a69581bf934caa7adb65d0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential trace that mutates a model with and without a mouth part would be required to confirm the bit-0x400 polarity end to end.`, `A runtime trace is required to read the eight mask globals after initialisation, to observe the actual property values behind ids 0x055D7CA1, 0x7A926123 and 0xF5CBE065, to see which capability bits the evaluator grants in practice, and to confirm the runtime class of the object at cEditor + 0x1CC.`, `No original-process trace has been captured for 0x0057ac00. Every claim in this record is static.`, `The Cell stage has never been entered in any recorded run, so the cll branch of the mouth scan has no runtime oracle.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential trace that mutates a model with and without a mouth part would be required to confirm the bit-0x400 polarity end to end.
- A runtime trace is required to read the eight mask globals after initialisation, to observe the actual property values behind ids 0x055D7CA1, 0x7A926123 and 0xF5CBE065, to see which capability bits the evaluator grants in practice, and to confirm the runtime class of the object at cEditor + 0x1CC.
- Is the SDK's /* 48h */ int field_48 really the same storage this function passes by address to two mutating helpers, or is the SDK's declaration of that offset stale? The address-taken use is observed; the SDK's intent is not confirmed.
- No original-process trace has been captured for 0x0057ac00. Every claim in this record is static.
- The Cell stage has never been entered in any recorded run, so the cll branch of the mouth scan has no runtime oracle.
- What are the 0x14-byte records at rigblock + 0xC0C that 0x00435b60 searches, and what is the meaning of the third dword it returns? Only the stride, the key offset and the result offset are established.
- What do the individual capability bits mean? For bits 0x400, 0x800, 0x40000 and 0x20 the semantics are pinned by the code; for the other fifteen observed inside 0x004F3DE0 nothing beyond their bit positions is known, and this function's own request for them is unobservable for the reason above.
- What does 0x004BAC30 actually hand to 0x004F3DE0? 0x004bac5c pushes dword ptr [EBP + 0x8], which in that frame is the wrapper's own return address, so the hand-off is not understood even though the net effect on the output buffer is observed.
- What is 0x006a1250's exact contract when the property exists but has an unexpected value kind? Its Ghidra body is mis-parameterised and only the null-list and success/failure shape was relied upon here.
- What is argument 4 for? It is pushed as 1 at five call sites and as a caller register at one, is never read, and may be a removed or defaulted parameter.
- What is the concrete type of the edit-history record at cEditor + 0x178 and of its last element, and what do the two 0x1d8-stride arrays that 0x004EFB20 and 0x004EF880 walk actually contain? The traversal was read but not semantically resolved.
- What is the type of the object at cEditor + 0x1CC and what do its +0x24..+0x30 dwords mean? They are the only per-editor contribution to the requested set and nothing in the SDK documents that offset.
- Which capability bits are actually requested in the shipping build? All eight mask globals (0x015DA7EC, 0x015DA7F0, 0x015DA7F4, 0x015DA7F8, 0x015DAA40, 0x015DAA44, 0x015DAA48, 0x015DAA4C) read zero in the static image and are runtime-initialised, and no writer was identified, so the requested set cannot be determined statically.
