# Validation 0x007d9410

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-app-mouse-camera-keydown/mouse_camera_on_key_down_007d9410.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x007d9410; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=2, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b1f792d20c11922aace3a8ba0b2bdf070d7d7df3b93efd01bfdf3aecc1492769`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `04b4e76a6ae16f82e18268ae245c6d6d27b0321537d65114710a01df6f6b9f28`
- Pack digest quoted by the briefing: `b1f792d20c11922aace3a8ba0b2bdf070d7d7df3b93efd01bfdf3aecc1492769`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Ordinary-argument arity and identity. The SDK/Ghidra prototype stored on this symbol declares two four-byte stack slots, (int virtualKey, KeyModifiers modifiers), while the machine shows one word being dropped by the tail target's RET 0x4. The model implements the single machine-observed word and types it as an opaque Word. Whether a preceding virtualKey argument exists in the original source and is simply unconsumed, and which declared parameter this word is, is not established by anything in this pack.
- Ordinary-argument arity conflict: the SDK/Ghidra prototype stored on this symbol declares (int virtualKey, KeyModifiers modifiers) - two four-byte stack slots - but the callee reached through the tail jump ends in `RET 0x4` and reads only [ESP+0x4]. The model implements the machine-observed single argument and names it after the SDK parameter that bit 0 is tested against. Whether a preceding virtualKey argument exists in the original source and is simply unconsumed is unresolved.
- The class and interface identities behind the three associated vtable words 0x007d93a0, 0x01412890 and 0x01412894, and the meaning of the single data-segment xref at 0x01412894. The binary carries no MSVC RTTI and the word at 0x014128a8 is not a code address in this image.
- The class names and interface identities behind the three vtable pointers at +0x00, +0x04 and +0x08; the binary carries no MSVC RTTI and the word at 0x014128a8 is not a code address in this image.
- The concrete routines behind the IAT words 0x013cc2d8 and 0x013cc2dc, and the work performed by 0x00926fd0.
- The identity of the argument bit 0: no SDK enum, string or disassembly context fixes whether it is a KeyModifiers flag, a lifetime/ownership flag or a raw boolean.
- The source-level role of 0x007d93a0 (constructor, unload, reset or restore) and the meaning of the three stub vtable words 0x013ef094 / 0x013eb394 / 0x013eb938 it installs last.
- What 0x007d9bb0 does. Its body is outside this package's evidence. Read live during this session it calls 0x007d93a0, tests bit 0 of the caller's argument, conditionally calls 0x00f47380 with the receiver, and returns the receiver in EAX -- but none of that is claimed here, and the record for 0x007d9bb0 is not in this repository's index for this VA.
- What the entry register points at. The persisted ABI record calls it a subobject of cMouseCamera that the body rewinds to the object start; the derived record declines to call ECX a receiver at all, because the body only ever writes it. The two readings are compatible with the two instructions and neither is established by them.
- Whether the bool return is ever observed as false by a real caller, given the machine always returns the non-null receiver in EAX.
- Whether the forwarded word is a bool. The declaration site says bool; the body cannot produce one. If a caller really does test the slot as a boolean, the observable truth is that the machine always returns a non-zero pointer-shaped word -- but nothing here establishes that any caller observes it as false, and this model does not claim it does.
- Whether the two staged packages for this VA (this one and reconstruction/staging/pkg-app-mouse-camera-keydown/) should be merged or kept apart. They agree on every machine fact about the two instructions; they differ in scope (this one reconstructs the entry alone, the other reconstructs a wider neighbourhood) and in the return-type choice recorded under return_semantics. Reconciling them is an integrator decision and was not attempted here.
