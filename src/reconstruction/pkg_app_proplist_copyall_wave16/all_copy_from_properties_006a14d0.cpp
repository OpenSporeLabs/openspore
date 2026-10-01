// PKG-APP-PROLIST-COPYALL-WAVE16 -- bounded x86-32 reconstruction of
// App::PropertyList::CopyAllPropertiesFrom.
//
//   VA            0x006a14d0
//   Program       SPORE/SporeBin/SporeApp.exe 3.1.0.22
//                 (sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//   Body          0x006a14d0 .. 0x006a1506 inclusive, 25 instructions
//                 (Ghidra body_end 0x006a1508, body span 0x38 bytes)
//
// EVIDENCE. Every claim below comes from two places and nothing else: the
// 25-instruction listing of 0x006a14d0..0x006a1506 read live, and the two raw
// 4-byte vtable images at 0x01408820 and 0x01408870 read live. The Ghidra
// function record (App::PropertyList::CopyAllPropertiesFrom, prototype
// `void (PropertyList *this, PropertyList *pOther)`, body 0x006a14d0..0x006a1508)
// and the decompilation cached in
// .spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__CopyAllPropertiesFrom.c
// corroborate. The briefing carried NO decompilation, disassembly, ABI,
// callee, caller or type section, so all of it was gathered from the bridge.
//
// ABI, machine-derived. __thiscall. The receiver arrives in ECX and is aliased
// into ESI at 0x006a14d6 (MOV ESI,ECX); there is no MOV ESI,ESP, so ESI is a
// general register and it is the base of every receiver access. One ordinary
// stack dword at entry_ESP+0x4, read at 0x006a14d2 as [ESP + 0xc] -- the +8 is
// the two register pushes at 0x006a14d0 and 0x006a14d1, so the operand is
// entry_ESP+0x4. That word is never written. The body ends in RET 0x4 at
// 0x006a1506, so the callee pops it: cdecl and fastcall are both excluded by
// that terminator. The epilogue restores both pushed registers before the
// return, so the register pushes cost the caller nothing.
//
// VTABLE PLACEMENT -- the load-bearing machine fact, and it is why this
// function is interesting. Reading the two vtable images as 4-byte slots from
// their base addresses:
//
//   vtable:0x01408820   slot +0x34 -> 0x006a14d0   (this body)
//                       slot +0x38 -> 0x006a1510
//                       slot +0x48 -> 0x006a2a80
//   vtable:0x01408870   slot +0x34 -> 0x006a14d0   (this body)
//                       slot +0x38 -> 0x006a1510
//                       slot +0x48 -> 0x006a2b20
//
// Slot +0x34 holds 0x006a14d0 in BOTH images, so this is one function shared
// by two classes (App::PropertyList and App::DirectPropertyList, per the
// symbol names the two vtable neighbourhoods carry), not two same-named
// functions. Slot +0x38 also agrees in both. Slot +0x48 DISAGREES, and that is
// the point: the receiver's Clear is dispatched virtually, so the same body
// clears a PropertyList by one code path and a DirectPropertyList by another.
// Both slot targets were decompiled live and both carry Ghidra names that
// agree with that reading -- 0x006a2a80 is App::PropertyList::Clear and
// 0x006a2b20 is App::DirectPropertyList::Clear.
//
// THE VTABLE IS RE-READ. This is the one detail the decompiler hides and it is
// reproduced rather than flattened. The body reads the receiver's vtable word
// twice, not once: at 0x006a14f1 for the slot +0x48 fetch, and again at
// 0x006a14fa for the slot +0x38 fetch -- AFTER the +0x48 call has returned. So
// the AddAllPropertiesFrom target is whatever slot +0x38 holds at that later
// moment, not what it held on entry. The two reads are written out separately
// below for that reason.
//
// THE PARENT IS DETACHED BEFORE IT IS RELEASED. At 0x006a14e3 the word at
// receiver+0x30 is written with zero and only then is the release dispatched
// at 0x006a14ef, with ECX still holding the parent read at 0x006a14dc. The
// order is observable and is preserved: a re-entrant release that inspected the
// child through this word would see it already cleared. The write is inside the
// `parent != null` arm -- the TEST/JZ at 0x006a14df/0x006a14e1 branches around
// the whole store-and-release pair, so a null parent leaves the word untouched
// (it is already zero) and skips the call entirely.
//
// Ghidra's decompilation is evidence but not truth, and it is wrong here in two
// ways that matter: it names the ECX receiver `in_ECX` and the stack argument
// `this`, inverting the machine's naming, and it renders the three dispatches
// as calls on the wrong objects (it shows the release as taking the child in
// EDI and the clear/add as taking the child in ESI/EDX, when the machine puts
// the PARENT in ECX for the release and the RECEIVER in ECX for the other two).
// The reconstruction follows the listing.

#include "all_copy_from_properties_006a14d0.hpp"

#if defined(_MSC_VER)
#define PKG_THISCALL __thiscall
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#define PKG_THISCALL __attribute__((thiscall))
#endif

namespace openspore {
namespace reconstruction {
namespace pkg_app_proplist_copyall_wave16 {
extern "C" void PKG_THISCALL all_copy_from_properties_006a14d0(
    OpaquePropertyList *receiver, OpaquePropertyList *other) {
  // 0x006a14d6  MOV ESI,ECX                 receiver into ESI
  // 0x006a14d8  CMP ESI,EDI
  // 0x006a14da  JZ 0x006a1504
  //
  // Pointer identity, nothing else: no alias, offset or range test appears in
  // the body. A self-copy exits to the epilogue having done nothing at all --
  // the parent is not released, the receiver is not cleared, and no slot is
  // dispatched. Note the two register pushes are already paid for, which is why
  // this arm still runs the POP EDI / POP ESI pair at 0x006a1504.
  if (receiver == other) {
    return;
  }

  // 0x006a14dc  MOV ECX,dword ptr [ESI + 0x30]   the parent word, into ECX
  // 0x006a14df  TEST ECX,ECX
  // 0x006a14e1  JZ 0x006a14f1                    -> skip the whole detach+release
  OpaquePropertyList *const parent = property_list_parent(receiver);
  if (parent != nullptr) {
    // 0x006a14e3  MOV dword ptr [ESI + 0x30],0x0  the store, BEFORE the call
    property_list_detach_parent(receiver);

    // 0x006a14ea  MOV EAX,dword ptr [ECX]         the PARENT's vtable word
    // 0x006a14ec  MOV EDX,dword ptr [EAX + 0x4]   slot +0x04
    // 0x006a14ef  CALL EDX                       ECX is still the parent
    //
    // The receiver of this dispatch is the PARENT, not the child: ECX was
    // loaded with the parent at 0x006a14dc and nothing overwrote it. No stack
    // word is pushed, so the slot takes only the receiver. The target of slot
    // +0x04 is 0x00432b50 in both vtable images. Its result is dead: EAX is
    // overwritten at 0x006a14f1 before anything reads it.
    property_list_vtable_of(parent)->release_04(parent);
  }

  // 0x006a14f1  MOV EAX,dword ptr [ESI]         receiver's vtable word, read 1
  // 0x006a14f3  MOV EDX,dword ptr [EAX + 0x48]  slot +0x48
  // 0x006a14f6  MOV ECX,ESI                      the receiver
  // 0x006a14f8  CALL EDX
  //
  // No stack word is pushed, so this slot takes only the receiver. This is the
  // polymorphic dispatch: the two vtable images put 0x006a2a80
  // (App::PropertyList::Clear) and 0x006a2b20 (App::DirectPropertyList::Clear)
  // in this slot, so the same body clears either kind of list.
  property_list_vtable_of(receiver)->clear_048(receiver);

  // 0x006a14fa  MOV EAX,dword ptr [ESI]         receiver's vtable word, read 2
  // 0x006a14fc  MOV EDX,dword ptr [EAX + 0x38]  slot +0x38
  // 0x006a14ff  PUSH EDI                        the stack argument: `other`
  // 0x006a1500  MOV ECX,ESI                      the receiver
  // 0x006a1502  CALL EDX
  //
  // The vtable is read AGAIN here, after the +0x48 call has returned, so this
  // dispatch is bound at a later moment than the one above. 0x006a1510
  // (App::PropertyList::AddAllPropertiesFrom) sits in slot +0x38 in both
  // vtable images. One ordinary stack dword is pushed, and the target's own
  // terminator is RET 0x4 (0x006a1533), so the callee consumes it and this
  // body does not have to clean it up.
  property_list_vtable_of(receiver)->add_all_properties_from_038(receiver, other);

  // 0x006a1504  POP EDI / 0x006a1505 POP ESI / 0x006a1506 RET 0x4
  //
  // EAX is never given a return value on any path: its last write is the slot
  // fetch at 0x006a14fc or a callee's dead result, so the return is void.
}

}  // namespace pkg_app_proplist_copyall_wave16
}  // namespace reconstruction
}  // namespace openspore
#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

#undef PKG_THISCALL
