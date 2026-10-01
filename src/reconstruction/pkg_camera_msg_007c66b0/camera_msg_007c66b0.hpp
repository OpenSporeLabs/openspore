#pragma once

// Target VA : 0x007c66b0  App::cCameraManager::HandleMessage
// Binary    : SPORE/SporeBin/SporeApp.exe 3.1.0.22
// Basis     : live Ghidra decompile + raw disassembly of 0x007c66b0, the
//             registry helper 0x00645ed0, the constructor 0x007c75e0, the
//             destructor 0x007c74a0, the vtable at 0x014106a4 and the raw
//             listing of the slot callees 0x007c6420 / 0x007c6480.
//
// Every offset, slot byte offset and call target below is copied from that
// evidence. Nothing here is inferred from SDK naming alone.
//
// WHAT THE RECEIVER EVIDENCE CARRIES FOR THIS BODY, AND WHAT IT DOES NOT.
// The machine-derived receiver record for 0x007c66b0 enumerates offsets=[0]
// and is bounds_only: it saw the body reach the receiver's word at displacement
// 0 and could say no more. The complete 32-instruction listing says more, and
// the reconstruction follows the listing:
//
//   0x007c66b5  MOV EDI,ECX                     receiver aliased into EDI
//   0x007c66c0  LEA ESI,[EDI + 0x60]            ESI := receiver + 0x60
//   0x007c66c4  MOV ECX,ESI                     ... and is passed as `this`
//   0x007c66c6  CALL 0x00645ed0                 ESI is callee-saved, so it
//   0x007c66cb  MOV EDX,dword ptr [ESI + 0x8]      survives the call
//   0x007c66ce  MOV ECX,dword ptr [ESI + 0x4]
//   0x007c66da  MOV EDX,dword ptr [EDI]          receiver + 0x00, the vptr
//
// so the receiver displacements the body reaches are 0x00, 0x60, 0x64 and
// 0x68. Every one of them is expressed here as a displacement, because a
// displacement is all the evidence supplies: the record is a set of offsets and
// states nothing about which member is which. The subobject at +0x60 is
// therefore NOT declared as a struct - `messages_060`, `buckets_004` and
// `bucket_count_008` were names this body's evidence cannot corroborate, and a
// second vtable pointer at +0x04, a camera vector at +0x80 and an active index
// at +0xa8 were never read here at all. What the receiver is given instead is
// an opaque run of 0x6c bytes and the word_at / pointer_at accessors.
//
// The node the helper returns is a different matter and a different object: the
// helper's own decompilation exposes its three words, so OpaqueMessageNode keeps
// the names its own evidence supplies. Even so, the body reads that node's
// second word through a displacement, because 0x007c66dc is a displacement and
// the reconstruction states it as one.

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-camera-msg-007c66b0 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_CMSG_CDECL __cdecl
#define PKG_CMSG_THISCALL __thiscall
#else
#define PKG_CMSG_CDECL __attribute__((cdecl))
#define PKG_CMSG_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_camera_msg_007c66b0 {

static_assert(sizeof(void*) == 4, "pkg-camera-msg-007c66b0 requires 32-bit pointers");
static_assert(sizeof(float) == 4, "pkg-camera-msg-007c66b0 requires 32-bit floats");

using OpaqueWord = std::uint32_t;

struct OpaqueCameraManager;

// Registry node, exactly the 12 bytes the walked chain exposes.
//   +0x00  compared by the 0x00645ed0 hash lookup against the requested id
//   +0x04  forwarded to the receiver's virtual slot at byte offset 0x54
//   +0x08  chain link
struct OpaqueMessageNode {
  OpaqueWord id_000 = 0;
  OpaqueWord payload_004 = 0;
  OpaqueMessageNode* next_008 = nullptr;
};

static_assert(sizeof(OpaqueMessageNode) == 12, "registry node stride");

// The displacement of the node word this body forwards, from
// `MOV EAX,dword ptr [EAX + 0x4]` at 0x007c66dc.
constexpr std::size_t kNodePayloadDisplacement = 0x4;

// Slot table read through the receiver's first vptr. Only byte offset 0x54 is
// dispatched by 0x007c66b0; it is 0x007c6420 for instances built by the
// constructor 0x007c75e0, which stores 0x014106a8 in the word at receiver+0x00.
// 0x007c6420 leaves EAX undefined, so the slot is modelled as returning void.
struct OpaqueCameraManagerVTable {
  void* slots_00[21]{};  // byte offsets 0x00 .. 0x50
  void(PKG_CMSG_THISCALL* select_camera_by_index_54)(OpaqueCameraManager*,
                                                     OpaqueWord) = nullptr;
  void* slots_58[6]{};
};

static_assert(offsetof(OpaqueCameraManagerVTable, select_camera_by_index_54) == 0x54,
              "the only slot this body dispatches is at byte offset 0x54");

// Receiver of 0x007c66b0, modelled at the four displacements the body reaches
// and no further: 0x6c bytes, 4-byte aligned, the prefix through the last word
// it reads. No member is declared. The extent is a modelling bound, not a
// recovered allocation size.
struct alignas(4) OpaqueCameraManager {
  std::array<std::uint8_t, 0x6c> opaque_00{};
};

// The receiver displacements 0x007c66b0 was observed reaching, as values.
// 0x00 is the dispatch word (`MOV EDX,dword ptr [EDI]`, written with no
// immediate); 0x60 is the subobject handed to the lookup; 0x64 and 0x68 are
// the two words read back out of it through ESI, and are reached in the body
// as +0x4 and +0x8 from the address 0x60 points at.
constexpr std::size_t kVtableDisplacement = 0x0;
constexpr std::size_t kRegistryDisplacement = 0x60;
constexpr std::size_t kRegistryFirstWordDisplacement = 0x4;   // receiver + 0x64
constexpr std::size_t kRegistrySecondWordDisplacement = 0x8;  // receiver + 0x68

// The only way this package touches the receiver: a 4-byte word at a stated
// displacement. A member access would assert an identity the receiver record
// (offsets=[0], bounds_only) cannot confirm.
inline std::uint32_t* word_at(OpaqueCameraManager* manager,
                              std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(manager) + displacement);
}

inline const std::uint32_t* word_at(const OpaqueCameraManager* manager,
                                    std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(manager) + displacement);
}

// The same word, read as the address it holds. 0x007c66da loads the receiver
// word at displacement 0 into EDX and 0x007c66df indexes it, so that word is an
// address and not a datum.
inline OpaqueCameraManagerVTable* pointer_at(const OpaqueCameraManager* manager,
                                              std::size_t displacement) {
  return reinterpret_cast<OpaqueCameraManagerVTable*>(
      static_cast<std::uintptr_t>(*word_at(manager, displacement)));
}

static_assert(sizeof(OpaqueCameraManager) == 0x6c,
              "modeled receiver extent through the last word the body reads");
static_assert(kRegistryDisplacement == 0x60, "LEA ESI,[EDI + 0x60]");
static_assert(kRegistryFirstWordDisplacement + 0x60 == 0x64,
              "the registry's first word is receiver + 0x64");
static_assert(kRegistrySecondWordDisplacement + 0x60 == 0x68,
              "the registry's second word is receiver + 0x68");
static_assert(kRegistryDisplacement + kRegistrySecondWordDisplacement +
                      sizeof(OpaqueWord) ==
                  sizeof(OpaqueCameraManager),
              "the last word the body reads ends the modeled extent");

// Out-of-line dependency: the chained hash lookup at 0x00645ed0, reached by a
// single direct call from 0x007c66c6 with ECX = receiver + 0x60. Its second
// argument is a two-word out slot built by `LEA ECX,[ESP + 0xc]` and its third
// is `&message_id` from `LEA EAX,[ESP + 0x14]`; only the FIRST word of the out
// slot is read back, by `MOV EAX,dword ptr [ESP + 0x8]`. The helper takes eight
// bytes of arguments back through its own RET.
struct CameraMessagePorts {
  using RegistryLookup = void(PKG_CMSG_THISCALL*)(std::uint8_t* registry,
                                                  OpaqueWord* out,
                                                  const OpaqueWord* key);
  RegistryLookup registry_lookup_00645ed0 = nullptr;
};

extern CameraMessagePorts g_camera_message_ports;

// App::cCameraManager::HandleMessage @ 0x007c66b0
//   ECX = receiver, [ESP+4] = message id, [ESP+8] = message payload (never read)
//   RET 0x4, AL only.
extern "C" bool PKG_CMSG_THISCALL handle_message_007c66b0(
    OpaqueCameraManager* manager, OpaqueWord message_id, void* p_message);

}

#undef PKG_CMSG_CDECL
#undef PKG_CMSG_THISCALL
