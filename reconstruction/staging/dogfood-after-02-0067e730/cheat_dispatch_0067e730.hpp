#pragma once

// Bounded clean-room reconstruction of SporeApp.exe 0x0067e730
// (App::cCheatManager::func44h), 3.1.0.22, image base 0x00400000.
//
// Every offset, slot and constant below is read directly off the 24-instruction
// body at 0x0067e730..0x0067e761 and is pinned by a static_assert so a later
// edit cannot silently drift away from the binary. Nothing here is inferred
// from behaviour: this function performs no writes, so every access is a read.
//
// Provenance: live Ghidra 12.1.2 decompile + /disassemble_function on
// SporeApp.exe, cross-read against the sibling entry 0x0067e6f0.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "cheat dispatch 0067e730 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_CHEAT_CDECL __cdecl
#define PKG_CHEAT_THISCALL __thiscall
#else
#define PKG_CHEAT_CDECL __attribute__((cdecl))
#define PKG_CHEAT_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::dogfood_after_02_0067e730 {

static_assert(sizeof(void*) == 4, "this reconstruction is 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "opaque words are 32-bit");

using OpaqueWord = std::uint32_t;

// The callee at 0x00921580. The body pushes the current node and calls it
// cdecl, then drops the pushed argument itself with "ADD ESP,0x4"; the callee
// therefore returns with a plain RET and does not clean up.
using NextNode = OpaqueWord* (PKG_CHEAT_CDECL*)(OpaqueWord*);

struct DispatchReceiver;

// 0x0067e744  MOV EAX,[ECX]        ; the receiver's slot table
// 0x0067e746  MOV EDX,[EAX+0x1c]   ; the seventh table entry, called indirectly
struct DispatchTable {
  void* prefix_000[7]{};
  void (PKG_CHEAT_THISCALL* entry_1c)(DispatchReceiver*, bool, OpaqueWord) =
      nullptr;
};

// 0x0067e741  MOV ECX,[ESI+0x10]   ; each list node owns one receiver word
struct DispatchReceiver {
  DispatchTable* table_000 = nullptr;
  std::uint32_t opaque_004[6]{};
};

// One link of the manager's observer chain. Only the receiver word at +0x10 is
// touched; the link word this function advances through lives inside 0x00921580
// and is not read here.
struct DispatchNode {
  std::uint32_t opaque_000[4]{};
  DispatchReceiver* receiver_010 = nullptr;
};

// The chain terminator is the ADDRESS of the field at +0x4c, never its value:
// 0x0067e735 LEA EDI,[ECX+0x4c] takes the field's own address, and no instruction
// in the body loads the four bytes stored there. The node is embedded in the
// manager rather than reached through a pointer.
struct CheatManager {
  std::uint32_t opaque_000[19]{};
  DispatchNode sentinel_04c{};
  DispatchNode* first_050 = nullptr;
  std::uint32_t opaque_054[4]{};
  std::uint8_t gate_064 = 0;
};

static_assert(offsetof(DispatchTable, entry_1c) == 0x1c,
              "the indirect call target is read from table+0x1c");
static_assert(offsetof(DispatchReceiver, table_000) == 0x0,
              "the receiver's table pointer is its first word");
static_assert(offsetof(DispatchNode, receiver_010) == 0x10,
              "the node's receiver word sits at +0x10");
static_assert(offsetof(CheatManager, sentinel_04c) == 0x4c,
              "the embedded terminator node sits at +0x4c");
static_assert(offsetof(CheatManager, first_050) == 0x50,
              "the first chain node is read from +0x50");
static_assert(offsetof(CheatManager, gate_064) == 0x64,
              "the sibling entry 0x0067e6f0 gates on this byte");

// 0x0067e6f0 tests byte [ECX+0x64] and returns early when it is clear. This
// entry, 0x0067e730, carries no such test: it reaches the chain unconditionally.
inline bool dispatch_is_gated(const CheatManager* manager) {
  return manager->gate_064 != 0;
}

struct DispatchPorts {
  NextNode next_00921580 = nullptr;
};

extern DispatchPorts* g_dispatch_ports;

inline DispatchNode* chain_first(CheatManager* manager) {
  return manager->first_050;
}

// The terminator is address-taken, never loaded; see the CheatManager comment.
inline DispatchNode* chain_terminator(CheatManager* manager) {
  return &manager->sentinel_04c;
}

inline DispatchReceiver* node_receiver(DispatchNode* node) {
  return node->receiver_010;
}

using DispatchEntry =
    void (PKG_CHEAT_THISCALL*)(DispatchReceiver*, bool, OpaqueWord);

// The single indirect call of the body: table slot +0x1c is loaded once and
// called with the receiver in ECX. Returned by value so the call site reads as
// a dispatch rather than a field walk.
inline DispatchEntry receiver_entry(DispatchReceiver* receiver) {
  return receiver->table_000->entry_1c;
}

// The name carries the SDK class, the SDK ordinal and the target VA.
extern "C" void PKG_CHEAT_THISCALL cCheatManager_func44h_0067e730(
    CheatManager* manager, OpaqueWord event_argument);

}

#undef PKG_CHEAT_CDECL
#undef PKG_CHEAT_THISCALL
