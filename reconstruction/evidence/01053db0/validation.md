# Validation 0x01053db0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dfw-01053db0/dfw_01053db0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 23-instruction listing name the same 4 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 4 distinct address(es) for 0x01053db0; the source span names 4 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 23-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x01053db0; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `WARN` | `partial` | 2 source field-offset declaration(s) (displacement 0x124, displacement 0x4) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (23 of 23 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 23-instruction listing lie inside the recovered body span 0x01053db0..0x01053df9, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 23-instruction body names 1 indirect transfer(s): 0x01053ddd dispatches slot 0x4 through the table word in EAX; the machine parse consumed 23 of 23 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 6 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7873fecaed9f37ddc25e1a878eac1f4ab8c59045adcdc63af21b188c62947492`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `73d3523f318a8be15a74fd91f71a700657b0ec5890fbf7b30bbac4b387c34a53`
- Pack digest quoted by the briefing: `7873fecaed9f37ddc25e1a878eac1f4ab8c59045adcdc63af21b188c62947492`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can the callee at 0x00cb3c70 change the receiver's word at 0x124? The listing re-reads and re-tests the slot three instructions after the call, which tolerates it, and its own body is only `MOV byte ptr [ECX + 0x155],0x1 / RET` so there is no evidence either way. The second test is therefore modelled as a plain re-read guard, and the model test exercises both behaviours.
- FUN_00cb3c70 could in principle clear the +0x124 slot, which the defensive second null test would absorb; no evidence shows that it does, so the second test is staged as a plain re-read guard.
- No canonical Ghidra structure exists for OpaqueBeamToolState, OpaqueBeamTarget or OpaqueRelationshipState; the layouts are assembled from the observed offsets and corroborated by the pkg-sim-tool-wave9 staging package rather than promoted from a live type.
- The SDK export's two extra parameters, cSpaceToolData * and Vector3 *, are refuted by the listing and the ret 0x4, but the reason the SDK import attached them is not established; the interface this virtual actually overrides is not named.
- The behaviour of the 0x00b77aa0 drain, which is tail-called with the relationship manager as receiver, is outside this package.
- The concrete implementation behind the owned target's vtable word at +0x04 is not resolved, and calling it a refcount release is an inference from the null-then-release idiom rather than an observed decrement.
- The meaning of gate bit 4 in the word at +0x174 is not determined; only the bit selection is proven. The decompiler's two-bit 0xffffff01 reading is a byte-mask artifact and is rejected in favour of the listing.
- The slot index and owning class of the three .rdata pointer sites at 0x0149b810, 0x0149b900 and 0x0149ba30 are not established, because the region interleaves non-code words (0x00b7d400, 0x00c6a960, 0x007b86e0) and no RTTI complete-object locator is confirmed; the briefing's four vtable addresses are therefore reported as function pointers, not verified vtable bases.
- What is behind the table word at displacement 0x4? The body proves the two-level shape, the displacement and the ECX-receiver shape of the callee. It does not identify the implementation, the owning class or the slot index, and calling it a refcount release would be an inference from the null-then-release idiom rather than an observed decrement.
- What is the receiver's total size? The largest displacement this body's own listing touches on the receiver is 0x124, so 0x128 is the smallest extent covering its accesses and nothing more. The prior package asserts 0x178, resting on the +0x174 access that happens inside 0x0104cd50's body; no record for this target gives a size, so none is claimed here.
- What is the semantic role of the whole sequence? The body releases whatever the receiver's 0x124 word points at when the gate byte is set, and returns a constant. Nothing in any record for this target says what the owned object represents, what the gate bit means, or what the relationship path accomplishes, so none of it is claimed.
- Which interface does this virtual override, and what are its three .rdata pointer sites? fan_in is 0 and the callers list is empty; the six vtable ids on the record are transitive classifier associations with vtable_reference_count 0. No RTTI and no vtable pass exist for this binary.
- Which member of the receiver is the word at displacement 0x124? The listing proves the displacement, the three accesses and the clear; no record says what the member is called, whether it is owned, borrowed or a smart handle, or what type it really has. The model reads it as a pointer only because 0x01053dd8 dereferences it.
- Why is a virtual whose receiver is passed on the stack and popped by the callee compiled the way MSVC compiles a member function? A pointer-to-member trampoline taking self explicitly, a __stdcall free function reached through a hand-built table, and a mismatched declaration in the original headers all compile to these bytes, and nothing in this body or in any record for this target distinguishes them. __stdcall is the smallest declaration that reproduces the observed machine, not a claim about how the original was written.
