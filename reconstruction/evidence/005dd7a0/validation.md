# Validation 0x005dd7a0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b03/editor_ui_paint_toggle_publish.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 55-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 55-instruction listing nevertheless reaches 5 receiver displacement(s) through ECX (0x14, 0x2c, 0x5c, 0xd1, 0x102), all of which the record accounts for or the listing is the better witness on; the 55-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=55, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 5 displacement(s) to the receiver as proven (0x14, 0x2c, 0x5c, 0xd1, 0x102) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x5c, 0xd1, 0x102), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 2 displacement(s) the record does not enumerate (0x14, 0x2c), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (55 of 55 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 55-instruction listing lie inside the recovered body span 0x005dd7a0..0x005dd83a, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 55-instruction body names 3 indirect transfer(s): 0x005dd7c7 is INDIRECT_NON_VTABLE; 0x005dd820 dispatches slot 0x7c through the table word in EAX; 0x005dd830 dispatches slot 0x7c through the table word in EAX; the machine parse consumed 55 of 55 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3, so the dispatch is visible in the machine listing but is not proven: 1 of the 3 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x005dd7c7), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0x5dd840], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a47fcfc66207c1c5460d0d6b692fce2a581e320c370b69e94c7c98cfa403df9f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `60bd7b386943133491b3ea5df84946bb6a9ca9a57eb6addc22b65106f27a4d1e`
- Pack digest quoted by the briefing: `a47fcfc66207c1c5460d0d6b692fce2a581e320c370b69e94c7c98cfa403df9f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential test must confirm that the two layouts at +0x14 and +0x2c really are alternatives rather than complementary, i.e. that the fallback path is ever taken.`, `A trace must record the live value of the +0x102 enable byte and the +0xd1 inhibit byte, since either can suppress the whole publish step.`, `A trace must resolve the provider that virtual slot +0x7c belongs to, which is the only way to turn 'two named toggle states' into a semantic claim.`, `No original-process trace exists for this function. Static analysis cannot show which of the five classification values actually occurs in a live editor session, so the frequency of each published state is unknown.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential test must confirm that the two layouts at +0x14 and +0x2c really are alternatives rather than complementary, i.e. that the fallback path is ever taken.
- A trace must record the live value of the +0x102 enable byte and the +0xd1 inhibit byte, since either can suppress the whole publish step.
- A trace must resolve the provider that virtual slot +0x7c belongs to, which is the only way to turn 'two named toggle states' into a semantic claim.
- No original-process trace exists for this function. Static analysis cannot show which of the five classification values actually occurs in a live editor session, so the frequency of each published state is unknown.
- The method name; nothing in the binary or the SDK names it.
- The owning class. Six offsets match Spore/Editors/EditorUI.h uniquely and the receiver's provenance is cEditor+0x78 = mpEditorUI, but no vtable exists in the typed program and there is no RTTI, so the class is a candidate and not a claim.
- The twelve uninspected call sites and the flag values their contexts imply, in particular the pair inside cEditor::HandleMessage and the two inside FUN_0058d1c0.
- What element id 0x5b6e484 denotes. It is absent from every SDK header read, and the sibling ids 0x612efea and 0x612efeb used by the tail target are equally unlabelled.
- What object virtual slot +0x7c belongs to, and what that method is called. This is the largest gap: it bounds what the function publishes to 'two named toggle states' without naming either.
- What the +0xd1 and +0x102 fields represent. Their effect on the published flags is read directly, but their intent is not.
- What the five classification values mean individually. Only the 0-2 versus 3-4 partition that the switch performs is established.
- Why only one of the two inspected callers null-checks the receiver.
- Why the same property id 0x55d7ca1 is read both inside the classification port and by the caller at 0x0058a792 immediately after this function returns.
