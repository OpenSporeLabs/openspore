# Validation 0x007c3ba0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg14-a1-world-state/world_state.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 28-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x007c3ba0; 51 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 2 outgoing call edge row(s) and 2 distinct callee(s) the export records; 2 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00f47380, 0x00f47410; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 2 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 28-instruction listing names 3 data address(es) (0x16f6dac, 0x16f8a38, 0x16f9110) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field active_object, camera_170, flags_8a38, flags_9110 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (28 of 28 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 28-instruction listing lie inside the recovered body span 0x007c3ba0..0x007c3c0a, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 28-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1ee180d8d4b26e43002937796c85d8ce8cd50a1fc37daba032cc565be0c9e90d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6865e0f59481141abc7e8f7d7881c11a7b90d29abf29037ce514edaf0eb93c2c`
- Pack digest quoted by the briefing: `1ee180d8d4b26e43002937796c85d8ce8cd50a1fc37daba032cc565be0c9e90d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No runtime trace of the original exists (categories.runtime MISSING), so every behavioural claim here is static-evidence only.
- Subsystem attribution conflicts: the worker assignment says Editors (cEditor teardown neighbourhood, with Editors::cEditor::Dispose among the callers) while the persisted triage record and the briefing both say Terrain. The evidence does not settle it.
- The bodies of 0x00f47380 and 0x00f47410 are not in the evidence pack, so they remain declared cdecl ports with inert defaults rather than reconstructed routines. What they release, and whether the release is refcount-aware, is unknown.
- The concrete type and ownership of the 32-bit word at receiver+0x158 are not established. It is only ever loaded, compared, pushed to 0x00f47380 and zeroed; the decompiler types the call argument as undefined4, so the model keeps it an opaque std::uint32_t rather than asserting a pointer.
- The concrete type and ownership of the 32-bit word at receiver+0x170 are likewise not established; it is loaded, tested, pushed to 0x00f47410 and zeroed.
- The concrete type and ownership of the object at receiver+0x158 are not established by this body.
- The decompiler prints __fastcall with a single ECX-assigned parameter while the derived and persisted ABI both say thiscall; the listing is followed, but the decompiler's own convention for this function was never corrected in Ghidra, so any downstream tool reading Ghidra's signature for 0x007c3ba0 will still see __fastcall.
- The real names, types and owners of the three data addresses 0x016f6dac, 0x016f8a38 and 0x016f9110 are not in the evidence pack (categories.globals is MISSING), so the reconstruction uses neutral g_editor_slot_007c3ba0_N names and asserts no meaning for them. The identity compare and the two OR bits are reproduced exactly; the semantics of 'identity', of bit 0x2 and of bit 0x8 are unknown.
- The receiver is treated as an opaque this pointer of at least 0x174 bytes because 0x170 is the largest observed displacement (abi_derived.receiver.max_offset 368, written_through 2). Whether the real object is exactly 0x174 bytes or larger is not settled by this body. The persisted SDK type for the receiver is OpaqueWorldViewer* / cViewer, but the evidence pack for this target carries no structure confirming that.
- The release routines remain package-local ports rather than promoted concrete classes.
- The upper three bytes of EAX at each RET are callee residue and are not determined by this body; only AL is claimed.
