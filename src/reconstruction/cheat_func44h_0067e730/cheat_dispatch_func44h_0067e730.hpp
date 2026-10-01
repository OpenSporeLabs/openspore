#pragma once

// Bounded clean-room reconstruction of SporeApp.exe 0x0067e730
// (App::cCheatManager::func44h), build 3.1.0.22, image base 0x00400000.
//
// Scope. Twenty-four instructions, 0x0067e730..0x0067e762 (51 body bytes,
// then five CC pad bytes at 0x0067e763..0x0067e768). The body writes nothing:
// every access it makes is a read, so nothing in this file can mutate the
// receiver, a chain node, or a call table. What it does is walk one chain and
// make one indirect call per node.
//
// Machine transcript (live Ghidra 12.1.2 /disassemble_function, corroborated by
// /read_memory @ 0x0067e730, hex
// 568b7150578d794c3bf77422538b5c24108b4e108b018b501c536a00ffd256e82c2e2a008bf083c4043bf775e45b5f5ec20400):
//
//   0x0067e730  56              PUSH ESI
//   0x0067e731  8B 71 50        MOV ESI,dword ptr [ECX + 0x50]
//   0x0067e734  57              PUSH EDI
//   0x0067e735  8D 79 4C        LEA EDI,dword ptr [ECX + 0x4C]
//   0x0067e738  3B F7           CMP ESI,EDI
//   0x0067e73a  74 22           JZ 0x0067e75e
//   0x0067e73c  53              PUSH EBX
//   0x0067e73d  8B 5C 24 10     MOV EBX,dword ptr [ESP + 0x10]
//   0x0067e741  8B 4E 10        MOV ECX,dword ptr [ESI + 0x10]
//   0x0067e744  8B 01           MOV EAX,dword ptr [ECX]
//   0x0067e746  8B 50 1C        MOV EDX,dword ptr [EAX + 0x1C]
//   0x0067e749  53              PUSH EBX
//   0x0067e74a  6A 00           PUSH 0x0
//   0x0067e74c  FF D2           CALL EDX
//   0x0067e74e  56              PUSH ESI
//   0x0067e74f  E8 2C 2E 2A 00  CALL 0x00921580
//   0x0067e754  8B F0           MOV ESI,EAX
//   0x0067e756  83 C4 04        ADD ESP,0x4
//   0x0067e759  3B F7           CMP ESI,EDI
//   0x0067e75b  75 E4           JNZ 0x0067e741
//   0x0067e75d  5B              POP EBX
//   0x0067e75e  5F              POP EDI
//   0x0067e75f  5E              POP ESI
//   0x0067e760  C2 04 00        RET 0x4
//
// Three structural facts the listing fixes and this file must not blur:
//
//  1. The chain end marker is the ADDRESS of the receiver word at +0x4C, never
//     its value. 0x0067e735 is a LEA, and no instruction in the body loads the
//     four bytes stored at +0x4C. The sentinel therefore lives inside the
//     manager itself; the walk needs no separate terminator pointer and the
//     contents of that word are inert.
//  2. The empty-chain exit at 0x0067e73a targets 0x0067e75E, which is POP EDI
//     -- it deliberately skips 0x0067e75D POP EBX, because PUSH EBX at
//     0x0067e73c is on the fall-through path only. On the empty-chain exit EBX
//     is neither saved nor restored, and the loop head's argument hoist never
//     runs.
//  3. The loop keeps no state. EBX is loaded once at 0x0067e73D, before the
//     loop head at 0x0067e741, and the back edge at 0x0067e75B targets the
//     head -- so the single stack argument is hoisted exactly as the machine
//     hoists it, and every iteration reuses the same word.
//
// Deliberately absent: any structure with named members. The evidence for this
// function is a displacement set and a call graph, never a field layout, so
// every word it touches is addressed by its machine displacement and the only
// named things here are the two call shapes the listing shows.
//
// Provenance: the 24-instruction listing and decompilation read live during
// this session, the 0x00921580 listing, /read_memory @ 0x01401b74 (the
// containing vtable) and the sibling entries 0x0067e6f0 and 0x0067e6b0, whose
// packages supply the receiver tail and the port-table convention. The
// decompilation disagrees with the listing about the receiver (it prints
// 'this' where the listing keeps a node word) and is not used as a source here;
// see the metadata sidecar's corroboration block.

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(__i386__) && !defined(_M_IX86)
#error "cheat dispatch func44h 0067e730 reconstruction requires an x86-32 target"
#endif

// The two conventions this body uses, spelled per compiler. MSVC has __thiscall
// and __cdecl as keywords; gcc and clang only have the attribute forms, and a
// reconstruction that hides its calling convention behind a macro nobody can
// resolve is harder to review than one that states it.
#if defined(_MSC_VER)
#define PKG_CHEAT44_CDECL __cdecl
#define PKG_CHEAT44_THISCALL __thiscall
#else
#define PKG_CHEAT44_CDECL __attribute__((cdecl))
#define PKG_CHEAT44_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::cheat_func44h_0067e730 {

static_assert(sizeof(void*) == 4, "this reconstruction is 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "opaque words are 32-bit");

// One machine word. The body never states what any word it reads means, so it
// is carried opaquely and no structure is asserted for it.
using OpaqueWord = std::uint32_t;

// ---------------------------------------------------------------------------
// Displacements
// ---------------------------------------------------------------------------
// Receiver-relative, base ECX on entry. These two are the whole of what the
// body touches in the receiver:
//   0x0067e731  MOV ESI,dword ptr [ECX + 0x50]   the chain head, loaded once
//   0x0067e735  LEA EDI,dword ptr [ECX + 0x4C]   the ADDRESS of the terminator
constexpr std::size_t kManagerTerminatorOffset = 0x4c;
constexpr std::size_t kManagerHeadOffset = 0x50;

// Node-relative, base ESI inside the loop. 0x0067e741 MOV ECX,dword ptr
// [ESI + 0x10]: the word each node holds, reloaded every iteration.
constexpr std::size_t kNodeReceiverOffset = 0x10;

// Receiver-relative, base ECX after the node word is loaded. 0x0067e744
// MOV EAX,dword ptr [ECX]: the receiver's first word, the table pointer. It is
// reloaded every iteration, so a node and the next may dispatch through
// different tables.
constexpr std::size_t kReceiverTableOffset = 0x0;

// Table-relative, base EAX. 0x0067e746 MOV EDX,dword ptr [EAX + 0x1C]: the
// eighth dword of the receiver's first word, and the only transfer target the
// body computes. No machine record names this slot.
constexpr std::size_t kTableEntryOffset = 0x1c;

// 0x0067e74a  PUSH 0x0 -- the leading argument is the literal zero. The
// sibling entry 0x0067e6f0 pushes 0x1 at 0x0067e710 from the same walk; the
// listing fixes both values and neither of their meanings.
constexpr OpaqueWord kLeadingWord = 0u;

// ---------------------------------------------------------------------------
// Call shapes
// ---------------------------------------------------------------------------
// 0x0067e74C  CALL EDX. ECX is the receiver word (0x0067e741), two words are
// pushed -- 0x0067e749 PUSH EBX then 0x0067e74a PUSH 0x0, so the leading word
// lands at [ESP+0] and the hoisted event word at [ESP+0x4] -- and nothing
// follows the call except 0x0067e74e PUSH ESI. Each iteration therefore nets
// eight bytes of stack unless the callee removes its own, so a member-shaped
// call with a callee-cleaned two-word stack is forced by the loop, not assumed
// from a prototype: this is the reading that keeps ESP constant across
// iterations. Which concrete function the slot holds is not established.
using DispatchEntry = void (PKG_CHEAT44_THISCALL*)(
    OpaqueWord* receiver, int leading_word, OpaqueWord event_argument);

// 0x0067e74F  CALL 0x00921580 with the current node pushed (0x0067e74E PUSH
// ESI) and dropped by the caller (0x0067e756 ADD ESP,0x4), so the callee ends
// in a plain RET: cdecl, one argument in, one word out. The 23-instruction
// listing of 0x00921580 reads dword ptr [ESP + 0x4] into ECX and branches on
// it -- if the node's first word is non-null it walks the +0x4 chain to its
// last element, otherwise it walks +0x8 -- so the routine is a node resolver,
// not a fixed "next" field read. Its semantics are not reconstructed here; the
// call is routed through a port so the model test can substitute a stub.
using ChainStepper = OpaqueWord* (PKG_CHEAT44_CDECL*)(OpaqueWord* node);

// Both callees live outside this body, so both are reached through a port
// table. The VA of each is kept in its field name and no pointer value is
// invented.
struct Ports {
  ChainStepper next_00921580 = nullptr;
};

extern Ports* g_cheat_func44h_ports;

// Read one machine word at a displacement from an opaque base. memcpy keeps the
// read well defined whatever the alignment of the base word turns out to be,
// and it is a read: this helper cannot write.
inline OpaqueWord word_at(const void* base, std::size_t offset) {
  OpaqueWord value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset,
              sizeof(value));
  return value;
}

// The address the chain is compared against: the receiver word at +0x4C, taken
// as an address and never dereferenced by this body.
inline OpaqueWord* chain_terminator(OpaqueWord* manager) {
  return reinterpret_cast<OpaqueWord*>(reinterpret_cast<unsigned char*>(manager) +
                                       kManagerTerminatorOffset);
}

// 0x0067e731: the first chain link, read once before the loop.
inline OpaqueWord* chain_first(OpaqueWord* manager) {
  return reinterpret_cast<OpaqueWord*>(
      word_at(manager, kManagerHeadOffset));
}

// 0x0067e741: the receiver this node dispatches through.
inline OpaqueWord* node_receiver(OpaqueWord* node) {
  return reinterpret_cast<OpaqueWord*>(word_at(node, kNodeReceiverOffset));
}

// 0x0067e744 / 0x0067e746: the table word of the receiver, then the entry at
// +0x1C of that table. Returned by value so the call site reads as a dispatch
// rather than a field walk.
inline DispatchEntry receiver_entry(OpaqueWord* receiver) {
  OpaqueWord* const table =
      reinterpret_cast<OpaqueWord*>(word_at(receiver, kReceiverTableOffset));
  return reinterpret_cast<DispatchEntry>(word_at(table, kTableEntryOffset));
}

// The target. ECX is the receiver and the function is a procedure: no exit path
// writes a defined value to EAX, so nothing is produced. One ordinary stack
// argument of four bytes is read at entry_ESP+0x4 -- 0x0067e73d MOV EBX,dword
// ptr [ESP + 0x10] once PUSH ESI, PUSH EDI and PUSH EBX have moved ESP from
// entry_ESP to entry_ESP-0xC -- and 0x0067e760 RET 0x4 shows the callee
// removes it.
extern "C" void PKG_CHEAT44_THISCALL func44h_0067e730(
    OpaqueWord* manager, OpaqueWord event_argument);

}

#undef PKG_CHEAT44_CDECL
#undef PKG_CHEAT44_THISCALL
