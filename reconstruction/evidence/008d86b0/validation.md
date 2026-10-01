# Validation 0x008d86b0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-resource-index-ref-008d86b0/dbp_index_ref_008d86b0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x008d86b0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x260) and the 1 the complete 2-instruction listing names through ECX (0x260) are all within the machine-derived receiver bounds (0x260), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b3ef7a285ef40265a0eb0ab632971c500d6f314061f9ff5cb5520f12d12b445a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d4fa1e9388203a23eadcf4a53072f037e33e75657369116af802441827e65bc7`
- Pack digest quoted by the briefing: `b3ef7a285ef40265a0eb0ab632971c500d6f314061f9ff5cb5520f12d12b445a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No caller-side use of the return value is observable, because the only reference to this address is the vtable slot itself. What consumers do with the non-owning handle is unproven.
- The EA class name of the object stored at +0x260 is unknown. Only its vtable shape is known: slot +0x04 AddRef, slot +0x08 Release, and slot +0x28 called from FUN_008d8c50. No /DatabasePackedFile or /EAIOZoneObject Ghidra structure exists to resolve it.
- The SDK label 'DestroyIndex' and the imported prototype 'void ... (DatabasePackedFile* this, EAIOZoneObject* pObject)' both disagree with the machine: the body is a non-destructive single load, and the bare RET proves there is no stack parameter, so the EAIOZoneObject* parameter is not real for this address. Whether the SDK symbol table mis-mapped this address, or names an unrelated accessor, cannot be settled from the binary.
- The meaning of the +0x14 dword gate is unknown. It is read as a plain zero/non-zero test by 0x008d86c0 only; nothing observed shows who writes it or what state it represents.
- The remaining slots of PTR_FUN_014367b0 are only partly resolved to function entries, so the full class this vtable belongs to is not established. Slot +0x20 resolves to Resource::DatabaseDirectoryFiles::GetRefCount, so the vtable is shared with or adjacent to another class and its owning class is not identified.
