// PKG-PROPMANAGER-CREATE-WAVE15 -- VA 0x006a3330
// App::cPropManager::CreateResource
// SPORE/SporeBin/SporeApp.exe, 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// This body dispatches virtually four times and calls two direct targets, and
// it names two data-segment addresses, 0x1408b44 and 0x1408b34, that the xref
// export corroborates with nothing: it records no data-reference edge for this
// target. A direct byte read of the same binary at those two addresses returns
// NUL-terminated ASCII literals at each (see the .cpp), which is a read fact
// about the bytes and not a typed object; no type is declared for either. No
// machine record names a slot member, so every slot is addressed by the byte
// displacement the listing shows and read into a function-pointer local before
// it is called.

#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PROPMANAGER-CREATE-WAVE15 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_propmanager_create_wave15 {

using TargetWord = std::uint32_t;

// categories.abi_derived.value.return = {register EAX, register_class
// "integral", type null, void_possible false} and
// categories.abi_derived.value.abi.return_semantics = "integral_in_EAX".
// The concrete type is adopted from the body itself, which is what the record
// leaves open: the two exits write the result byte explicitly -- MOV AL,0x1 at
// 0x006a33c9 and XOR AL,AL at 0x006a33ec -- so the returned word is 1 on one
// path and 0 on the other and nothing else. Ghidra's decompilation types the
// same function "bool", which is reported beside this and not merged into it.
using OpaqueResource = void;

struct OpaquePropManager;
struct OpaqueSourceObject;
struct OpaqueDescriptor;

// 0x006a3380  MOV EDX,dword ptr [EAX + 0x10]
// 0x006a3383  MOV ECX,EDI
// 0x006a338d  CALL EDX
//   The slot word is read at byte displacement 0x10 of the table word at
//   displacement 0 of the entry_ESP+0x8 object, and the callee's receiver is
//   that same object. Its result is a pointer the body then reads three words
//   out of. No stack word is pushed and the frame is balanced across the
//   transfer, so the callee owns a cleanup of zero bytes -- which both
//   conventions satisfy, so the shape here is a rendering of the observed
//   receiver register and nothing more.
using SlotAt10 = OpaqueDescriptor*(__thiscall*)(OpaqueSourceObject*);

// 0x006a33a8  MOV EDX,dword ptr [EBX]
// 0x006a33aa  MOV EDX,dword ptr [EDX + 0x24]
// 0x006a33ad..0x006a33b0  PUSH EAX / PUSH ECX / PUSH ESI / PUSH EDI
// 0x006a33b1  MOV ECX,EBX
// 0x006a33b3  CALL EDX
//   The slot word is read at byte displacement 0x24 of the receiver's own table
//   word -- the only receiver access in the body, and it is at displacement 0 --
//   and the transfer carries four stack words in this order: the entry_ESP+0x10
//   word, the entry_ESP+0x14 word, the created object, and the entry_ESP+0x8
//   object. The body tests AL of the result, so the return is modelled as an int
//   and only its low byte is claimed to be meaningful.
using SlotAt24 = int(__thiscall*)(OpaquePropManager*,
                                  OpaqueSourceObject*,
                                  OpaqueResource*,
                                  void*,
                                  TargetWord);

// 0x006a33c1  MOV EDX,dword ptr [ESI]
// 0x006a33c3  MOV EAX,dword ptr [EDX]
// 0x006a33c5  CALL EAX
//   The table word at displacement 0, read at byte displacement 0: the shape a
//   first table entry has. The body calls it and then returns 1 without using
//   anything the callee left behind, so no return word is claimed here.
using SlotAt00 = void(__thiscall*)(OpaqueResource*);

// 0x006a33dd  MOV EDX,dword ptr [ESI]
// 0x006a33df  MOV EAX,dword ptr [EDX + 0x8]
// 0x006a33e2  PUSH 0x1
// 0x006a33e4  CALL EAX
//   The same table, one entry further in, handed the single immediate word 1.
//   Called on the failure path only, and the body then returns 0 without
//   inspecting the result.
using SlotAt08 = void(__thiscall*)(OpaqueResource*, int);

// Direct transfers, named by the target VA as the validator requires. The
// xref export records both: 0x006a3358 -> 0x00f473a0 and
// 0x006a3373 -> 0x006a1b90, both as direct-call edges.
//
// 0x006a3358  CALL 0x00f473a0
//   Six stack words, cleaned by the caller at 0x006a335d (ADD ESP,0x18), so
//   the convention is caller-cleanup; the receiver is not in ECX here (ECX
//   carries this function's own receiver, saved to EBX one instruction before),
//   which is consistent with a free function taking six words.
extern "C" void* prop_list_factory_00f473a0(TargetWord,
                                            TargetWord,
                                            TargetWord,
                                            TargetWord,
                                            TargetWord,
                                            TargetWord);

// 0x006a3371  MOV ECX,EAX
// 0x006a3373  CALL 0x006a1b90
//   One stack word and ECX carrying the word the factory returned, so this
//   target takes a receiver. Its return is the object the rest of the body
//   works on. No record in this repository names what it is.
extern "C" void* create_named_006a1b90(void* receiver, TargetWord tag);

// Reconstruction scaffolding, not machine callees. The listing installs a
// two-word record on the FS chain at 0x006a3330..0x006a333e and restores the
// displaced chain word at 0x006a33d0 and 0x006a33ef. There is no portable C++
// spelling for a thread chain, and no record in this repository names the scope
// table or a handler, so these two calls stand for the two machine steps and
// claim nothing about either. `state` is the companion word the body rewrites
// at 0x006a3364 and 0x006a3385 and never reads back.
extern "C" TargetWord enter_scope_frame(TargetWord scope_table, TargetWord state);
extern "C" void leave_scope_frame(TargetWord displaced_chain);

// 0x006a3385  MOV dword ptr [ESP + 0x18],0xffffffff
// The single immediate the body writes into the frame; 0x006a3330 pushes it as
// -0x1, the same value.
inline constexpr TargetWord kScopeStateUnwind = 0xffffffff;

extern "C" bool __thiscall app_prop_manager_create_resource_006a3330(
    OpaquePropManager* receiver,
    OpaqueSourceObject* source,
    void** created_out,
    void* apply_second,
    TargetWord apply_fourth);

}  // namespace openspore::reconstruction::pkg_propmanager_create_wave15
