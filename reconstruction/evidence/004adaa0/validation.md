# Validation 0x004adaa0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b00/field38_004adaa0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 9-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x38), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 9-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8e50c7ef8e42f11aa54b0ceb88d49da96515cd333c0a009a72792eb7732f51c2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e65fd3603333cd290e03926f5295dfb4f6f71ad9f6cca826cc4a28bfd90a2844`
- Pack digest quoted by the briefing: `8e50c7ef8e42f11aa54b0ceb88d49da96515cd333c0a009a72792eb7732f51c2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test would be needed to confirm the receiver type and to confirm that no runtime patch retargets this address.`, `No original-process trace exists for 0x004adaa0. The Cell stage has never been entered in any recorded run, so the claim that callers treat the result numerically is a static claim only.`, `The meaning of the +0x38 field can only be settled by observing a write at runtime, which no recorded run does.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test would be needed to confirm the receiver type and to confirm that no runtime patch retargets this address.
- Is 0x004adaa0 also a vtable entry? A pointer scan of the target's address was not performed, so only direct-call sites are recorded.
- No original-process trace exists for 0x004adaa0. The Cell stage has never been entered in any recorded run, so the claim that callers treat the result numerically is a static claim only.
- The 26 caller fan-in is dominated by four functions in the 0x0043xxxx-0x004axxxx range with no subsystem attribution. Their relationship to the owning type is not established.
- The meaning of the +0x38 field can only be settled by observing a write at runtime, which no recorded run does.
- What are the float constants at 0x013eb960 (0x3c23d70a) and 0x013eecd8 (0x41a00000 = 20.0f)? 20.0f is self-evident; the other is not, and neither is named in the SDK.
- What class owns the +0x38 float? No vtable was located for the receiver type and the binary has no RTTI, so the owner is unnamed.
- What does the float mean (scale, radius, alpha, weight, time)? Every inspected consumer only multiplies or divides it by a constant, which is compatible with all of those.
- Why is there no getter for +0x3c or +0x40 when both have setters? Either the getters were inlined at every use or they do not exist; the binary cannot distinguish these.
