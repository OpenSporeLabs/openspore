# Validation 0x01053790

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg11-i1-tool-onselect/tool_onselect.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x01053790; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 11-instruction listing names 1 data address(es) (0x1403934) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field vftable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x01053790..0x010537ac, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `WARN` | `partial` | the machine return state is WIDTH_4_IN_EAX -- the complete 11-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice -- but the source span declares return type 'bool', which is 1 byte(s) wide. The machine fixes the width of the value in EAX; it does not fix the C type, and a hidden-pointer or aggregate return is one reading in which the two differ without the reconstruction being wrong, so this is a review item rather than a refutation. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b526252678c882174733403d56b391c68d05ad74e392f0b802e2a3a1484996d7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d89c89f8afb45faa2f24deb56b17ee73e5c5cb917fa20a0383535e628c209477`
- Pack digest quoted by the briefing: `b526252678c882174733403d56b391c68d05ad74e392f0b802e2a3a1484996d7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- It is not established whether 0x01053790 is a base-class OnSelect, a base-class state-reset virtual, or a scalar deleting destructor. The mechanics are identical in all three readings.
- No call site is recoverable: the target has zero references from any executable block, so no caller can be shown to pass a known argument and settle the guard's meaning.
- The EAX return is the receiver pointer rather than an observed 0/1, and the ABI analyzer classified it as aggregate_unknown; the bool reading rests on the SDK prototype alone.
- The SDK-documented 18-slot cToolStrategy contract cannot be reconciled with the observed 6-slot vftable at 0x01403934, so slot indices reported by docs/analysis/vtables.json are not treated as authoritative here.
- The class that owns the vftable at 0x01403934 is not identified. It is abstract (three purecall slots) and inherited at many subobject offsets program-wide, which does not match a tool-specific strategy class.
- The single stack argument is typed cSpaceToolData* by the SDK import, but only its bit 0 is tested, so the release branch is unreachable for any 4-byte-aligned pointer. Either the SDK parameter typing at this address is wrong, or the tested word is a flag or a deleting-destructor flags word rather than a pointer.
- Vftable slots 4 and 5 both point at 0x012c6625, which Ghidra has not defined as a function; their role is unknown.
