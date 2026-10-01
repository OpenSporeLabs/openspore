# Validation 0x00980510

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dfw-00980510/dfw_00980510.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00980510; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 2-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `379f2db0db0f8490ce1f95188058cc30574cc7a11d7cbaaedeb77f51bae73a5a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `087eb8d3f25df7bc31b408ed9a2cef48995496238b86fdd865bde398a7be0434`
- Pack digest quoted by the briefing: `379f2db0db0f8490ce1f95188058cc30574cc7a11d7cbaaedeb77f51bae73a5a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Slot +0x18 (0x00980520) has no function record in Ghidra, so the slot immediately after GetProxyID is uncharacterised. It is the most likely place a related per-class override would sit, which makes it the obvious next target for this class.
- Slot +0x18 (0x00980520) has no function record in Ghidra, so the slot immediately after this one is uncharacterised. It is the most likely place a related per-class override would sit.
- The decompiler's `ILayoutElement *` parameter type is not independently confirmed. The binary carries no MSVC RTTI (per the project evidence note), so the base type comes from the imported Spore-ModAPI symbols. This record keeps the receiver opaque (struct PerspectiveEffect) rather than adopting the decompiler's base-class spelling, and flags the disagreement rather than resolving it.
- The exact vtable extent. Slots +0x00..+0x5c are recorded and mutually consistent, but no null terminator appears in that window, and words observed at +0x60..+0x7c (0x010829f0, 0x00951230, 0x006f2f20) may belong to this image or to the next one. Nothing in this target's body depends on the answer.
- The extent of the dispatch-table image. Only the eight words actually read are recorded. Whether the image continues past +0x1c, and where it ends, is unresolved; nothing in this body depends on the answer.
- The receiver convention is inferred, not observed. See observed_original_abi.convention_basis. Nothing in the body can corroborate it, which is why the derived ABI record abstained (verdict ABI_UNKNOWN) while the persisted record asserts __thiscall. The model follows the persisted record, and a behavioural test cannot tell the two apart -- a mutation that downgrades the declaration to __cdecl everywhere still passes every runtime assertion. See validation.mutation_check.limitations.
- The receiver convention is inferred, not observed. The body never reads ECX, so it is byte-identical under __cdecl, __stdcall, __thiscall and __fastcall, and the persisted abi_infer record abstained for exactly that reason (verdict ABI_UNKNOWN). __thiscall here rests on the single fact that 0x00980510 is a vtable slot, plus the MSVC x86-32 convention that virtual members take the receiver in ECX. A direct (non-virtual) call to this address from somewhere outside the image would be indistinguishable in the body; no such call exists in this binary, so the risk is theoretical.
- The receiver's type. The decompiler says ILayoutElement *, which is not independently confirmed in a binary with no MSVC RTTI. The model keeps the receiver opaque (void*) and records the disagreement rather than resolving it.
- The slots holding 0x00e31100, 0x00dde980 and 0x00b267f0 in this image were not characterised -- they lie above the low code range and are recorded as opaque words. Whether they are code, data or imported thunks is unresolved and does not affect this body.
- The slots holding 0x00e31100, 0x00dde980 and 0x00b267f0 were not characterised. They are addresses above the low code range and are recorded as opaque words; whether they are code, data or imported thunks is unresolved here and does not affect this body.
- What 0x202 denotes. It is a per-class identifier in an ID space this body never interprets and never computes, and two instructions cannot fix its meaning, its neighbours, or whether the space is dense. The sibling implementations named in the record (0x0096fec0, 0x0097e7d0) obtain their values from a runtime registry, which is consistent with an interned index but confirms nothing here. The reconstruction names the constant for the immediate it is and assigns it no role.
- What 0x202 denotes. It is a per-class proxy identifier in an ID space this body never interprets, and the ID space is not recoverable from two instructions. The sibling implementations show the space is populated at runtime (0x0096fec0 allocates and tags objects with a class-name string; 0x0097e7d0 dispatches through a manager), which suggests 0x202 is an interned index assigned to UTFWin::PerspectiveEffect, but nothing here confirms that, its neighbours, or whether the space is dense.
- Whether GetProxyID is genuinely virtual in the SDK declaration or a non-virtual method that happens to occupy a slot. Not checkable here: the Spore-ModAPI headers are not present. The machine fact -- a slot at +0x14 of the image at 0x014440d0 -- is not in doubt either way, and the model depends on neither reading.
- Whether GetProxyID is genuinely virtual in the SDK's declaration or a non-virtual method that merely happens to occupy a slot cannot be checked here; the Spore-ModAPI headers are not present in this environment. The machine fact -- a slot at +0x14 -- is not in doubt either way.
