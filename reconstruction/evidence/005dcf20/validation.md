# Validation 0x005dcf20

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `missing`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 47-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 5 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (47 of 47 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 47-instruction listing lie inside the recovered body span 0x005dcf20..0x005dcf8b, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 47-instruction body names 4 indirect transfer(s): 0x005dcf55 dispatches slot 0xc through the table word in EAX; 0x005dcf67 dispatches slot 0x28 through the table word in EAX; 0x005dcf7a dispatches slot 0x28 through the table word in EAX; 0x005dcf86 dispatches slot 0x94 through the table word in EAX; the machine parse consumed 47 of 47 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `cc1cc3a39c0e705bf57fec90cdb424763ed1280d645a8be55fd72d03f6870bf3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `140da390c4fec396ed62dfdfa9ed2320ddd08191a3db6e5cf7c850183d2eb171`
- Pack digest quoted by the briefing: `cc1cc3a39c0e705bf57fec90cdb424763ed1280d645a8be55fd72d03f6870bf3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the third stack value always a boolean-like flag, or can other values occur?
- What do flag_a and flag_b mean operationally?
- Which opaque target interface owns the 0xc, 0x28, and 0x94 slots?
