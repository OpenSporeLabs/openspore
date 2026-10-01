# Validation 0x00c772c0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00c772c0-hashset-contains-key/hashset_contains_key_00c772c0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 24-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00c772c0; 75 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `PASS` | `complete` | the complete 24-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00c772c0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field bucket_base_1120, bucket_count_1124, key_00, next_04 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 2 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x1120, 0x1124), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (24 of 24 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 24-instruction listing lie inside the recovered body span 0x00c772c0..0x00c772f5, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 24-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'bool' and the machine return state is WIDTH_1_IN_EAX: the complete 24-instruction listing writes EAX at a determinate 1-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c55780d8f1c814391b6839ced54e9a51944825fd72fc18e10f7af53bc23e22e2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `69282e5495e12ef961a4d0bc7e31f9847f16eb01ea7b4c50d2632dbb805c5541`
- Pack digest quoted by the briefing: `c55780d8f1c814391b6839ced54e9a51944825fd72fc18e10f7af53bc23e22e2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The class that owns the words at +0x1120 and +0x1124. No MSVC RTTI in this binary, and the evidence pack's types and vtables categories are both absent.
- The semantics of the sibling 0x00c77bf0, which two reconstructed callers invoke on this entry's false path with the same receiver and key. That is a separate target owned by another worker; it is the natural next question for this family but it is not answered here.
- What the 32-bit values are: a hashed token, a packed enum and a resource id all index and compare identically here. Caller analysis narrowed them to 31-bit immediate constants but did not identify a kind.
- Whether any real chain can be cyclic. The loop has no cap and no identity check, so a cycle would not terminate.
- Whether the count at +0x1124 is ever zero in a real instance. The body never tests it, so a zero would trap the machine with #DE, and nothing here shows whether the container can be constructed in that state.
