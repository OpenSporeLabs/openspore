# Validation 0x00451e50

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b05/editor_rigblock_00451e50.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 17-instruction listing names through ECX (0x18c) are all within the machine-derived receiver bounds (0x18c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 17-instruction listing lie inside the recovered body span 0x00451e50..0x00451e80, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7e877ab5c4073431fa21e3ead608d45c836bdd1f72230fba3126598e247e1c5d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `eca09c46b63b6f215e01dfbcdc38a9fb8c2e281d9cfbe17073805a2522f7ba0c`
- Pack digest quoted by the briefing: `7e877ab5c4073431fa21e3ead608d45c836bdd1f72230fba3126598e247e1c5d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace is required to determine the runtime value of receiver->[+0x18C] in each editor mode, the runtime class of the nested object, and the runtime content of the +0x38 dword.`, `No original-process trace has been captured for 0x00451e50. Every claim in this record is static.`, `The Cell stage has never been entered in any recorded run, so no editor path has a runtime oracle.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace is required to determine the runtime value of receiver->[+0x18C] in each editor mode, the runtime class of the nested object, and the runtime content of the +0x38 dword.
- Do the two flag bits 7 and 11 of the dword array at rigblock + 0xdc8, read at 0x004a6aa7 and 0x004a6b15 by the caller, correlate with this value? The correlation was not analysed.
- Is the +0x18C slot a parent, a child, a detour or a sub-asset? The EditorRigblock.h comments around that offset mention 'remove parent?' and a detour helper, but nothing observed here settles it.
- Is the propagated value an ordinal, a level, a draw order or a state code? The 1..N assignment at 0x004ad4e0 is consistent with all four and proves only that it is a small non-negative integer in the observed callers.
- No original-process trace has been captured for 0x00451e50. Every claim in this record is static.
- The Cell stage has never been entered in any recorded run, so no editor path has a runtime oracle.
- What class does receiver->[+0x18C] point to? At 0x00495d5x the same pointer is used as `field_18C + 0x1c` for a transform-style call and at 0x0048d010 `*(field_18C + 0x1c)` is dereferenced as a vtable for a slot +0x0c call taking a static and two out-parameters, while `*(field_18C + 0x58)` is used as a further sub-object. None of that identifies the class.
- What does the +0x38 dword mean? The observed width rules out the SDK's two-bool layout, and nothing in the read evidence names it.
- What is the class of the receiver? +0x33C and +0x3E0 match documented Editors::EditorRigblock members, but the SDK types +0x18C as int, its +0x18/+0x1C are not a vector, and the class is never named by any other evidence.
