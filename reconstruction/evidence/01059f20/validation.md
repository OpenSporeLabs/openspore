# Validation 0x01059f20

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 106-instruction listing name the same 5 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x01059f20..0x0105a043 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x01059f64; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 5 outgoing call edge row(s) over 5 distinct address(es) for 0x01059f20; the source span names 5 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 106-instruction listing names 1 data address(es) (0x13f94d4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 7 source field-offset declaration(s) (field field_154, field mpBeam, field mpToolOwner, field vtable_00) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (106 of 106 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 106-instruction listing lie inside the recovered body span 0x01059f20..0x0105a043, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 106-instruction body names 7 indirect transfer(s): 0x01059f5e dispatches slot 0xb8 through the table word in EDX; 0x01059f9e dispatches slot 0x0 through the table word in EDX; 0x01059fa9 dispatches slot 0x2c through the table word in EDX; 0x01059fbe dispatches slot 0x48 through the table word in EDX; 0x01059fd8 dispatches slot 0x0 through the table word in EAX; 0x01059fe9 dispatches slot 0x4 through the table word in EAX; 0x0105a038 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 106 of 106 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 7. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 1 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x0, 0x4, 0x2c, 0x48, 0xb8, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2629d06da8316d8deb63b2556ef887032b1e2839f904f4e17c52369223af355f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c88d11a8b9f6a21031fd2afe11c265fb886f6da4979f13574ba6fd4a93daaa57`
- Pack digest quoted by the briefing: `2629d06da8316d8deb63b2556ef887032b1e2839f904f4e17c52369223af355f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00b7c160 has no SDK name. Its effect on cRelationshipManager is described from its twenty instructions; the meaning of the word at +0x20 bits 1 and 2 and of the dword at +0x55a0, and the behaviour of 0x00b7a710, are unresolved. The SDK spells +0x20 as the bool mbIsInitialized, so only bit 0 is named.
- No differential runtime corpus exists for this virtual, so every claim here is static evidence only.
- The behaviour of 0x010568b0 is not reconstructed here; only its ABI, its constant-true return and its use of cSpaceToolData::+0x114 and +0x120 are used. Because it always returns 1, this function's first branch is dead in this build, so the reconstruction cannot say what that branch would have suppressed.
- The behaviour of 0x01059170 is not reconstructed here; only its four-argument cdecl ABI and its use of cSpaceToolData::+0x114 and +0x120 are used.
- The function is unnamed in the Spore-ModAPI symbol table, so no SDK class name is asserted for the receiver. The evidence supports a cToolStrategy-derived virtual whose receiver dispatches cDefaultBeamTool__vftable word 0x48, but the owning class is not identified.
- The meaning of vtable word 0x2c is not settled. The SDK names cGameData__vftable word 0x2c IsDestroyed, but the listing takes the bridge path precisely when that call returns NON-ZERO, which is the opposite of an IsDestroyed guard. Either the concrete override at 0x2c is not the SDK IsDestroyed, or the code deliberately acts on beams it considers destroyed. The source therefore names the slot predicate_2c and stages the branch in the listing's own sense rather than in the SDK name's sense.
- The slot index of 0x01059f20 inside the four .rdata tables at 0x0149b80c, 0x0149b8ac, 0x0149b8fc and 0x0149ba2c is not established. Aligning on the neighbouring SDK-named 0x01053db0 would give 0x48, but the same tables carry none of the other SDK-named cDefaultBeamTool members at their SDK offsets, the SDK address for cDefaultBeamTool::OnHit is demonstrably wrong in this neighbourhood, and this body dispatches its own receiver's word 0x48, which would recurse. The briefing's vtable:0x0149b810 and vtable:0x0149b8b4 are reported as inaccurate: those words hold 0x01053db0 and 0x01052f90.
- The type entry passed to cSpatialObject::Cast at 0x013f94d4 is a bare address into a table of 4-byte entries. Its type is not named in the SDK, so the query is described as a type test and not as any particular cast.
- The virtual callee behind the receiver's word 0x48 is not resolved. The SDK's cDefaultBeamTool::func48h prototype matches the two pushed words, but the SDK address it carries for func48h, 0x01054e70, is not the function this body dispatches when the receiver's table is any of the four found, so the concrete override is unknown.
- The virtual callees behind cDefaultBeamProjectile words 0x00, 0x04 and 0x2c are not resolved to concrete functions. Their slot names come from the SDK's cGameData__vftable, and their receivers are the beam, but no concrete override was identified.
