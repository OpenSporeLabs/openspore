#pragma once

// Bounded clean-room reconstruction of SporeApp.exe 0x0067e6f0
// (App::cCheatManager::func40h), build 3.1.0.22, image base 0x00400000.
//
// Scope. Twenty-six instructions, 0x0067e6f0..0x0067e726, no writes anywhere:
// every access this body makes is a read, so nothing here can mutate the
// receiver or a chain node. The body is a gate, a chain walk, one indirect call
// per node and one direct call per step.
//
// Deliberately absent: any struct with named members. The evidence for this
// function is a displacement set and a call graph, never a field layout, so
// every receiver word is addressed by its machine displacement and the only
// named things in this file are the two call shapes and the one direct call
// target the listing actually shows.
//
// Provenance: the 26-instruction listing and the openspore-abi-inference-1
// record in reconstruction/evidence/0067e6f0/evidence.json. The sibling entry
// 0x0067e730 is the same walk without the gate and is used only as contrast.

#include <cstddef>
#include <cstdint>
#include <cstring>

#if defined(_MSC_VER)
#define PKG_CHEAT_DISPATCH_0067E6F0_CDECL __cdecl
#else
#define PKG_CHEAT_DISPATCH_0067E6F0_CDECL __attribute__((cdecl))
#endif

#if defined(_MSC_VER)
#define PKG_CHEAT_DISPATCH_0067E6F0_THISCALL __thiscall
#else
#define PKG_CHEAT_DISPATCH_0067E6F0_THISCALL __attribute__((thiscall))
#endif

#if !defined(__i386__) && !defined(_M_IX86)
#error "cheat dispatch 0067e6f0 reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_cheat_dispatch_0067e6f0 {

static_assert(sizeof(void*) == 4, "this reconstruction is 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "opaque words are 32-bit");

// One machine word. The body never states what any word it reads means, so no
// structure is asserted for it and none is invented.
using OpaqueWord = std::uint32_t;

// ---------------------------------------------------------------------------
// Displacements
// ---------------------------------------------------------------------------
// Receiver-relative (base ECX on entry). These three are the whole of what the
// body touches in the receiver: 0x0067e6f0, 0x0067e6f7 and 0x0067e6fb.
//
//   0x0067e6f0  CMP byte ptr [ECX + 0x64],0x0    one byte, tested, never written
//   0x0067e6f7  MOV ESI,dword ptr [ECX + 0x50]    a chain link, loaded once
//   0x0067e6fb  LEA EDI,[ECX + 0x4c]              the ADDRESS of the terminator
//
// 0x4c is an address computation, never a load: no instruction in the body reads
// the four bytes stored there. It is the chain's end marker, and it is the
// receiver's own storage, which is why the walk needs no separate sentinel
// pointer.
//
// Node-relative and call-table-relative displacements are deliberately NOT
// spelled inline in the entry function. They belong to objects the body only
// ever holds through a pointer, so writing them next to the receiver
// displacements would read as claims about the receiver, which the listing does
// not support.

// 0x0067e707  MOV ECX,dword ptr [ESI + 0x10] -- the word each node holds.
constexpr std::size_t kNodeWordOffset = 0x10;

// 0x0067e70a  MOV EAX,dword ptr [ECX] -- the receiver's first word, a level of
// its own. The slot below is read out of THIS word, not out of the receiver, so
// the dispatch is a two-level load; both loads are inside the loop and are
// reloaded on every step.
constexpr std::size_t kReceiverTableOffset = 0x0;

// 0x0067e70c  MOV EDX,dword ptr [EAX + 0x1c] -- the word the body calls through.
constexpr std::size_t kCallTableEntryOffset = 0x1c;

// ---------------------------------------------------------------------------
// Call shapes
// ---------------------------------------------------------------------------
// 0x0067e715  CALL 0x00921580, with the current node pushed as the single
// argument, followed by 0x0067e71c ADD ESP,0x4. The callee therefore returns
// through a plain RET and the caller drops the argument itself: cdecl, one
// argument in, the next link out.
//
// The callee lives outside this module, so it is modelled as an unresolved
// function pointer rather than a defined body. The value the listing resolves
// is 0x00921580; where that pointer is stored is not shown by this body, and no
// global is invented for it.
using ChainStepper = OpaqueWord* (PKG_CHEAT_DISPATCH_0067E6F0_CDECL*)(OpaqueWord* node);
extern ChainStepper const next_node_00921580;

// The single indirect call, 0x0067e712 CALL EDX. The receiver arrives in ECX
// (0x0067e707 loaded it from the node) and two words are pushed, so this is a
// member-shaped call with a two-argument stack. The loop is stack-balanced only
// if this callee removes its own eight bytes: each iteration pushes four bytes
// for this call and four for 0x00921580 and drops only four with ADD ESP,0x4.
// Which concrete function the slot holds, and whether the table it is read from
// is a dispatch table in the strict sense, is not established by the listing --
// no machine record names the slot.
using DispatchEntry = void (PKG_CHEAT_DISPATCH_0067E6F0_THISCALL*)(OpaqueWord* receiver,
                                         int leading_word,
                                         OpaqueWord event_argument);

// Read one machine word at a displacement from an opaque base. memcpy keeps the
// read well defined whatever the alignment of the base word turns out to be.
inline OpaqueWord word_at(const void* base, std::size_t offset) {
  OpaqueWord value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset,
              sizeof(value));
  return value;
}

// The target. ECX is the receiver (0x0067e6f0 CMP byte ptr [ECX + 0x64],0x0 and
// 0x0067e6f4 JZ 0x0067e726 return before anything else), one ordinary stack
// argument of four bytes is read at entry_ESP+0x4 (0x0067e703 MOV EBX,
// dword ptr [ESP + 0x10], with three register saves already pushed), and the
// body returns through RET 0x4, so the callee removes that argument.
extern "C" void PKG_CHEAT_DISPATCH_0067E6F0_THISCALL cCheatManager_func40h_0067e6f0(
    OpaqueWord* manager, OpaqueWord event_argument);

}

// Both conventions are spelled with the plain __thiscall / __cdecl keywords
// rather than through package macros: MSVC and clang both accept them on an
// i386 target, and a reconstruction that hides its own calling convention
// behind a macro nobody can resolve is harder to review than one that states it.
