# Validation 0x005a2320

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_camera_wave8/camera_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x005a2320; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=2, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'OpaqueEditorCamera*': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 2-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f046c26f7cc694261b9e92b0fd006fbaf077e7ad262c4feec2a577364f479f71`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8ba423d76309db55406d64d439767d9de71a461b5570875b5a6d2bc94c74ed9d`
- Pack digest quoted by the briefing: `f046c26f7cc694261b9e92b0fd006fbaf077e7ad262c4feec2a577364f479f71`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original Wine deletion trace was captured for this object, property list or virtual destructor callback.`, `No original Wine deletion trace was captured for this object, property list or virtual destructor callback.; The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.; The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk.`, `The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.`, `The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original Wine deletion trace was captured for this object, property list or virtual destructor callback.
- No original Wine deletion trace was captured for this object, property list or virtual destructor callback.; The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.; The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk.
- The exact runtime owner of the 0x013f69b8 secondary vtable requires indirect-dispatch confirmation before promotion.
- The imported func54h semantic name remains unresolved because the exact entry is a deleting-destructor thunk.
- concrete runtime owners and values remain unresolved
