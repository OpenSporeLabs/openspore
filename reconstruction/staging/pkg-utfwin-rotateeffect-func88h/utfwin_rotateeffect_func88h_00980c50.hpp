#pragma once

// UTFWin::RotateEffect::func88h @ 0x00980c50 -- reconstruct_00980c50
//
// Live machine bytes (SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e),
// read with ghidra_read_memory(0x00980c50, 192):
//
//   00980c50  B8 D5 2A 2B CF     MOV  EAX,0xCF2B2AD5
//   00980c55  C3                 RET
//   00980c56  CC CC ... CC       INT3 padding through 0x00980c5f
//
// ghidra_disassemble_function(0x00980c50) agrees exactly: two instructions,
// body 0x00980c50..0x00980c55, and ghidra_get_function_by_address reports
// body_end_inclusive 0x00980c55.
//
// The whole function is six bytes. It builds no stack frame, reads no
// memory, calls nothing, consults no flag, and does not even read the hidden
// ECX receiver. Its single observable effect is to place the immediate
// 0xCF2B2AD5 in EAX and return. The RET is a bare RET, not RET n, so the
// caller -- not this frame -- removes any stack arguments.
//
// The only reference to 0x00980c50 in the whole image is a DATA pointer at
// 0x01444364 (ghidra_get_xrefs_to: one reference, from 0x01444364, type
// DATA). That is slot +0x00 of the pointer run the session briefing and the
// Ghidra long-run detector both label "vtable:0x01444364" (36 slots,
// namespace UTFWin, firstSlotFunc 0x00980c50). There is no code caller; the
// call graph is the single-node SCC scc-0060 with no edges, matching the
// briefing (callers: [], callees: [], xrefs: []).
//
// The constant is not arbitrary. Twelve bytes further on, still inside the
// same 32-byte code block, is an unconditional block that STORES the very
// same immediate into the receiver:
//
//   00980c80  8B 44 24 04          MOV  EAX,[ESP+4]
//   00980c84  85 C0                TEST EAX,EAX
//   00980c86  74 0D                JZ    0x00980c95
//   00980c88  83 7C 24 08 00       CMP  dword [ESP+8],0
//   00980c8d  74 06                JZ    0x00980c95
//   00980c8f  C7 00 D5 2A 2B CF    MOV  dword [EAX],0xCF2B2AD5
//   00980c95  B8 01 00 00 00       MOV  EAX,1
//   00980c99  C2 08 00             RET  0x8
//
// That is: "if (receiver != 0 && word != 0) { *receiver = 0xCF2B2AD5; } return
// 1; else return 0" -- a bool-returning setter of the same 32-bit word this
// target returns unconditionally. An adjacent (get, set) virtual pair over
// one object word is the reading this reconstruction adopts. The block at
// 0x00980c80 is byte-verified but is NOT claimed as reconstructed here: Ghidra
// has no function at or containing 0x00980c80, so its true entry and owner
// are unknown (see unresolved_questions).
//
// The two entries between this target and that block are MSVC adjustor
// thunks, byte-for-byte the shape of the already-reconstructed sibling
// UTFWin::GlideEffect::func88h @ 0x0096ff70 (modelled in
// reconstruction/staging/pkg-utfwin-glideeffect-func88h):
//
//   00980c60  83 E9 04 E9 48 00 00 00    SUB ECX,0x04 / JMP 0x00980cb0
//   00980c70  83 E9 0C E9 38 00 00 00    SUB ECX,0x0C / JMP 0x00980cb0
//
// 0x00980c50 itself is NOT such a thunk: it neither adjusts ECX nor transfers
// control anywhere. Note also that both thunks branch to 0x00980cb0, an
// address the image fills with INT3 padding (0x00980cac..0x00980cb3); the
// nearest real code is 0x00980cb4. That boundary anomaly is recorded, not
// resolved.
//
// 0xCF2B2AD5 is deliberately left unnamed. It is NOT an entry of the ModAPI
// ObjectTYPE enum: 0xEF2B293B is (published simultaneously for
// UTFWin::IGlideEffect, UTFWin::IPerspectiveEffect and UTFWin::IRotateEffect,
// which is why Ghidra warns that some ObjectTYPE values lack unique names),
// and no ObjectTYPE entry carries the 0xCF2B prefix at all. Naming the
// immediate would be invention, so it is exposed as the literal constant
// kFunc88hToken below.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin RotateEffect func88h requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_utfwin_rotateeffect_func88h {

using Opaque = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_R8_THISCALL __thiscall
#define PKG_R8_NAKED __declspec(naked)
#else
#define PKG_R8_THISCALL __attribute__((thiscall))
#define PKG_R8_NAKED __attribute__((naked))
#endif

// ---------------------------------------------------------------------------
// The pointer run based at 0x01444364, transcribed verbatim from
// ghidra_read_memory(0x01444364, 48). Slot +0x00 is the sole reference to
// 0x00980c50 in the binary.
// ---------------------------------------------------------------------------
struct alignas(4) RotateEffectVTableRun {
  Opaque slot_00;  // 0x00980c50 -- this target
  Opaque slot_04;  // 0x00980320 -- JMP 0x0044f5d0 thunk
  Opaque slot_08;  // 0x009800e0 -- JMP 0x0097da80 thunk
  Opaque slot_0c;  // 0x00980cb0 -- INT3 padding in this build; see header
  Opaque slot_10;  // 0x0096ff20 -- vector-deleting entry
                   // (pkg-utfwin-glideeffect-func88h)
  Opaque slot_14;  // 0x00e31100
  Opaque slot_18;  // 0x009634c0
  Opaque slot_1c;  // 0x00963780
  Opaque slot_20;  // 0x006f2f20
  Opaque slot_24;  // 0x006f2f20
  Opaque slot_28;  // 0x006f2f20
  Opaque slot_2c;  // 0x006f2f20
};

// The word this target returns, and the word the block at 0x00980c80 stores
// into the receiver.
inline constexpr Opaque kFunc88hToken = 0xcf2b2ad5u;

// Slot signature as the SDK method header spells it: a thiscall receiver plus
// three int words. The machine consumes none of them, and the bare RET means
// the caller removes them; see the call-site helper in the model test.
using TokenSlot = Opaque(PKG_R8_THISCALL*)(Opaque, Opaque, Opaque, Opaque);
// The shape the machine actually requires: the receiver alone.
using TokenGetSlot = Opaque(PKG_R8_THISCALL*)(Opaque);

static_assert(sizeof(void*) == 4, "UTFWin RotateEffect pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "UTFWin opaque words are 32-bit");
static_assert(offsetof(RotateEffectVTableRun, slot_00) == 0x00,
              "vtable run slot holding 0x00980c50");
static_assert(offsetof(RotateEffectVTableRun, slot_0c) == 0x0c,
              "vtable run slot holding 0x00980cb0");
static_assert(sizeof(RotateEffectVTableRun) == 0x30, "vtable run extent");

// The receiver this slot is reached through. Only its leading word is ever
// touched, and only by the block at 0x00980c80 -- never by 0x00980c50.
struct RotateEffectTokenWord {
  Opaque token_00;
};

// Observed ABI of 0x00980c50.
//
//   return_type  std::uint32_t, carrying the immediate 0xCF2B2AD5
//   receiver     ECX, present by the SDK method header but never read
//   stack        three words per the SDK header; none read, caller-cleaned
//   cleanup      none -- bare RET at 0x00980c55
//   flags        none
//   memory       none read, none written
//
// The SDK and the Ghidra import both spell the return type void. The machine
// unambiguously materialises a 32-bit immediate in EAX, so this span is
// modelled as returning that word and the disagreement is recorded rather than
// papered over.
struct Func88hAbi {
  int receiver_register;
  int ordinary_stack_words;
  int stack_cleanup_bytes;
  const char* return_type;
  const char* return_type_rationale;
};

extern const Func88hAbi kFunc88hAbi;

// Observed constants, all read directly out of the listing or the byte dump.
struct Func88hConstants {
  Opaque token;                    // MOV EAX,0xCF2B2AD5
  Opaque entry;                    // 0x00980c50
  Opaque body_end_inclusive;       // 0x00980c55, the RET
  Opaque int3_pad_end;             // 0x00980c5f
  Opaque sole_data_xref;           // 0x01444364
  Opaque vtable_run_base;          // 0x01444364
  Opaque pairing_store_block;      // 0x00980c80, stores the same immediate
  Opaque pairing_store_end;        // 0x00980c9c, exclusive
  Opaque adjustor_thunk_04;        // 0x00980c60, SUB ECX,0x04
  Opaque adjustor_thunk_0c;        // 0x00980c70, SUB ECX,0x0C
  Opaque adjustor_jump_target;     // 0x00980cb0, INT3 padding in this build
  Opaque vector_delete_entry;      // 0x0096ff20, at run slot +0x10
  Opaque vector_delete_magic;      // 0xEF2B293B, the ObjectTYPE triple
  Opaque objecttype_iperspective;  // 0xEF2B293B, same triple
};

extern const Func88hConstants kFunc88hConstants;

// The pointer run based at 0x01444364. Slot +0x00 is the sole reference to
// 0x00980c50 in the binary.
extern const RotateEffectVTableRun kRotateEffectVTableRun;

// The entry point. Name binding: the validator matches this against the
// record name UTFWin::RotateEffect::func88h, so it carries the words func, 88
// and h plus the 8-hex target VA 00980c50.
extern "C" std::uint32_t PKG_R8_NAKED PKG_R8_THISCALL func88h_00980c50(Opaque,
                                                                       Opaque,
                                                                       Opaque,
                                                                       Opaque);

namespace unresolved_contracts {

// 0x00980C80 .. 0x00980C9B. A different address and not a claimed
// reconstruction; declared so the model test can supply an oracle for the
// constant pairing. Observed semantics, from the bytes:
//
//   MOV EAX,[ESP+4] / TEST EAX,EAX / JZ ret1 / CMP dword [ESP+8],0 / JZ ret1
//   MOV dword [EAX],0xCF2B2AD5 / ret1: MOV EAX,1 / RET 0x8
extern "C" Opaque pkg_r8_re_00980c80(RotateEffectTokenWord* self,
                                     std::uint32_t word);

}

}
