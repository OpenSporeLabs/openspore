# Validation 0x005c0dd0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-005c0dd0/swarm_w1_005c0dd0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x005c0dd0; 2 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x24) and the 1 the complete 2-instruction listing names through ECX (0x24) are all within the machine-derived receiver bounds (0x24), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint8_t' and the machine return state is WIDTH_1_IN_EAX: the complete 2-instruction listing writes EAX at a determinate 1-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4a3bf26efc06859f4cd982d6cbcf446e1c4a2c7be82a213d5bd33fb764190641`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a6985c7415f32a74aa422a35c63b70daccf13392d9e986285df6c39d9abd7dc2`
- Pack digest quoted by the briefing: `4a3bf26efc06859f4cd982d6cbcf446e1c4a2c7be82a213d5bd33fb764190641`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the value's domain {0, 1} or 0..255? Nothing in these two instructions masks anything, and both direct callers are domain-agnostic: 0x00adfeb2 stores the raw byte, and 0x00de5278's TEST AL,AL takes the same branch for 2, 0x80 and 0xff as for 1. The model therefore returns the byte verbatim and the model test REQUIRES 0x80 and 0xff to survive, which is the opposite of asserting a boolean. A bool declaration would be an invented domain.
- The persisted ABI record's calling convention lists __fastcall as a candidate alongside __thiscall and reports corroboration 'not_available'. __thiscall is the one both the persisted and derived records resolve to, and it is the one the listing supports (a base-register receiver, a bare RET, zero stack slots), but the corroboration field is empty and this package does not upgrade that to a claim beyond what the two records already say.
- What class is this receiver? The target record carries subsystem 'Sporepedia' and cluster 'sporepedia-online', and the tables this body sits in have SDK-named Sporepedia::cSPAssetDataOTDB neighbours -- but THIS entry is sdk=false and unnamed, so the class is not claimed and the type is spelled SporepediaByteRecord as a shape only.
- What do bits 8..31 of EAX hold at a real call site? The body does not set them (8A is a partial register write) and no value is claimed. Both known call sites read AL alone, so they are unobservable in this build; a third-party caller that read the full EAX would see whatever it had left there. Settling this needs either an assertion that the upper bytes are dead (not present in this build) or a caller that reads them.
- What is the C++ spelling of the one-byte return -- bool, unsigned char or std::uint8_t? The three compile to the same three bytes and the machine cannot choose between them. std::uint8_t is declared as the least committal option; this is a source-side choice and not a verified type. The validator agrees on the WIDTH (WIDTH_1_IN_EAX) and explicitly not on the spelling.
- What is the byte at 0x24? The receiver record is bounds_only, so nothing here identifies it. Calling it a flag, an enabled-bit, a mode, an is-editable bit or a validity bit would be a member story the evidence does not carry, and the model deliberately names no member. Settling it needs either an SDK declaration for this slot (the SDK tree is not present in this environment; the committed vtables export carries sdk=false for this entry) or a runtime trace that shows what sets the byte.
- Which slot, in which table, is this body's interface position? Twelve tables reference it at six different indices (4, 14, 15, 26, 29, 33), so no single index is right for all of them and none is declared. Settling it needs the class hierarchy these tables belong to; the committed export records the 0x013f7cc0 family as namespace 'unattributed' with sdkCount 0.
