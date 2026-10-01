# Validation 0x00635760

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-dispatch-b00/utfwin_00635760.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 3 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x00635760..0x0063577f, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names 1 indirect transfer(s): 0x0063577d dispatches slot 0x7c through the table word in EDX; the machine parse consumed 11 of 11 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f3a323343a28a3cbcf4ddf99e3a344101a4874f62e783222be244d6873883c0f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cafff0eb6c85d1b71520314f82a434ed870f1a3e2a01efd58a2ad0cf0fb16e02`
- Pack digest quoted by the briefing: `f3a323343a28a3cbcf4ddf99e3a344101a4874f62e783222be244d6873883c0f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test would have to (a) confirm the lookup returns the same window for a given control id, (b) confirm the +0x7C dispatch reaches an IWindow::SetFlag implementation and not a patched one, and (c) confirm the callee really uses RET 8, which the tail transfer requires but which no in-binary observation of the concrete callee can prove.`, `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test would have to (a) confirm the lookup returns the same window for a given control id, (b) confirm the +0x7C dispatch reaches an IWindow::SetFlag implementation and not a patched one, and (c) confirm the callee really uses RET 8, which the tail transfer requires but which no in-binary observation of the concrete callee can prove.
- Is the vector at +0x14 a list of UTFWin service providers, a list of root windows, or a type registry? The observed protocol (query by type id, then treat the result as a window) fits all three.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- Spore-ModAPI declares Editors::PlayModeUI::SetWindowVisible at 0x635450/0x635750, numerically adjacent to this target. Whether this target is that method could not be confirmed: 0x00635750 is not a function boundary in this image and 0x00634dc0 does not match PlayModeUI::FindWindowByID's described shape. Recorded as a candidate, not a claim.
- The control ids pushed by callers are addresses of string literals in .rdata (0x00406678, 0x004066b8, 0x0044 6a98 and so on). Their character contents were not read, so no caller-level purpose is claimed for any individual window.
- What is the dynamic IWindow subclass of the resolved window, and therefore which concrete SetFlag implementation runs? No receiver was observed at a dispatch site, and no original-process trace exists.
- Which class owns the +0x14 registry vector? The vector's element type and the meaning of its slot +0x0C (a get-object-by-type query) are not established, and no vtable for the receiver was located.
- Why do all 27 callers load ECX from a field and then call a function that would work equally well as a free function? The most likely reading is a source-level member call whose receiver happens to be unused on the fast path, but that is INFERRED, not observed.
