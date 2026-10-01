#pragma once

// UTFWin::GlideEffect::func88h @ 0x0096ff70 -- reconstruct_0096ff70
//
// Live machine bytes (SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e):
//
//   0096ff70  83 E9 0C          SUB  ECX,0x0C
//   0096ff73  E9 58 00 00 00    JMP  0x0096FFD0
//   0096ff78  CC CC ... CC      INT3 padding through 0x0096ff7f
//
// The function is eight bytes long and is a pure MSVC-style adjustor thunk:
// it rewrites the hidden ECX receiver by -0x0C and tail-transfers, without
// touching the stack, EAX, or any flag. The single ordinary stack word it
// forwards is the compiler-inserted scalar-deleting flag, which is only
// inspected by the tail target.
//
// The only reference to 0x0096ff70 in the whole image is a DATA pointer at
// 0x0144258c, which is byte offset +0x08 of the pointer run based at
// 0x01442584 (the run Ghidra and the session briefing both name
// "vtable:0x01442584"). There is no code caller.
//
// The tail target 0x0096FFD0 (extent 0x0096ffd0..0x00970008) is the shared
// deleting destructor of the GlideEffect family; the four words it writes are
// exactly four of the vptr/field slots the SDK documents for
// UTFWin::GlideEffect (size 0x70): +0x00 BiStateEffect, +0x04
// ILayoutElement, +0x0C IBiStateEffect and +0x60 IGlideEffect.
//
// The -0x0C adjustment therefore lands the callee on the most-derived object
// whose subobject the caller's vptr was reached through sits at +0x0C, and
// +0x0C is exactly the SDK offset of GlideEffect's IBiStateEffect subobject.
// This is the same shape as the already-reconstructed sibling
// UTFWin::InflateEffect::func88h @ 0x0097e550, which is byte-for-byte
// "SUB ECX,0x0C / JMP 0x0097E4A0".

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UTFWin GlideEffect func88h requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_utfwin_glideeffect_func88h {

using Opaque = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_G8_THISCALL __thiscall
#else
#define PKG_G8_THISCALL __attribute__((thiscall))
#endif

// ---------------------------------------------------------------------------
// Layout, transcribed from .spore-analysis/ghidra-exports/spore_sdk.xml
// (UTFWin::GlideEffect, SIZE 0x70). Only the words the machine actually
// touches are named; the gaps are reproduced as opaque padding so the
// static_asserts below pin the real offsets.
// ---------------------------------------------------------------------------

struct OpaqueVtable {
  Opaque slot_00;
  Opaque slot_04;
  Opaque slot_08;
  Opaque slot_0c;
};

// UTFWin::GlideEffect, as documented by the ModAPI SDK.
struct GlideEffect {
  OpaqueVtable* bi_state_effect_vtable_00;     // SDK _vftable0, offset 0x00
  OpaqueVtable* layout_element_vtable_04;      // SDK _vftable1, offset 0x04
  std::int32_t reference_count_08;             // SDK mnRefCount,  offset 0x08
  OpaqueVtable* bi_state_interface_vtable_0c;  // SDK _vftable2, offset 0x0c
  std::uint8_t opaque_10[0x50];                // SDK 0x10..0x5f
  OpaqueVtable* glide_interface_vtable_60;     // SDK _vftable3, offset 0x60
  std::uint8_t opaque_64[0x0c];  // SDK mOffset 0x64, field_6C 0x6c
};

// The receiver the thunk actually receives: a pointer to the subobject that
// lives 0x0C bytes above the most-derived object. For UTFWin::GlideEffect that
// is the IBiStateEffect subobject at SDK offset 0x0C. The relationship is
// computed, never stored: 0x0096ff70 derives it from ECX with SUB ECX,0x0C.
inline constexpr Opaque kFunc88hReceiverAdjustment = 0x0cu;

struct GlideEffectBiStateSubobject {
  std::uint8_t opaque_00[0x0c];
};

// Tail target of 0x0096ff70, modelled as a contract because its own VA
// (0x0096FFD0) belongs to a different target. The machine reads one stack
// word and ends in RET 0x4, and it materialises its receiver in EAX.
using TailDeletingDestructor =
    Opaque(PKG_G8_THISCALL*)(GlideEffect*, std::uint32_t deleting_flag);

// Tail target of the sibling vector-deleting thunk 0x0096ff90, kept for the
// dispatch table that the leaf block at 0x0096ff20..0x00970008 populates.
using VectorDeletingThunk = GlideEffect*(PKG_G8_THISCALL*)(GlideEffect*,
                                                           std::uint32_t);

struct GlideEffectVTableRun {
  Opaque slot_00;
  Opaque slot_04;
  Opaque slot_08;  // 0x0096ff70 -- this target
  Opaque slot_0c;
};

static_assert(sizeof(void*) == 4, "UTFWin GlideEffect pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "UTFWin opaque words are 32-bit");
static_assert(offsetof(GlideEffect, reference_count_08) == 0x08,
              "GlideEffect mnRefCount offset");
static_assert(offsetof(GlideEffect, bi_state_interface_vtable_0c) == 0x0c,
              "GlideEffect IBiStateEffect subobject offset");
static_assert(offsetof(GlideEffect, glide_interface_vtable_60) == 0x60,
              "GlideEffect IGlideEffect subobject offset");
static_assert(sizeof(GlideEffect) == 0x70, "GlideEffect extent");
static_assert(sizeof(GlideEffectBiStateSubobject) == 0x0c,
              "receiver subobject prefix extent");
static_assert(offsetof(GlideEffectVTableRun, slot_08) == 0x08,
              "vtable run slot holding 0x0096ff70");

// Observed ABI of 0x0096ff70.
//
//   return_type  void
//   receiver     ECX, a pointer to the subobject at most_derived + 0x0C
//   stack        exactly one ordinary word, [ESP+0x08] on entry
//   cleanup      the callee's RET 0x4 removes that single word
//   flags        none written before the tail transfer
//   result       EAX is never written by the thunk itself
//
// The SDK and the Ghidra import both spell the signature as
// void UTFWin::GlideEffect::func88h(GlideEffect*, int, int, int), i.e. three
// int stack words. The machine reads one. The return type is taken from the
// SDK (void) and is consistent with the thunk never writing EAX.
struct Func88hAbi {
  int receiver_register;
  int receiver_shift_bytes;
  int ordinary_stack_words;
  int stack_cleanup_bytes;
  const char* return_type;
  const char* return_type_rationale;
};

extern const Func88hAbi kFunc88hAbi;

// Observed constants, all read directly out of the listing.
struct Func88hConstants {
  Opaque receiver_adjustment;  // SUB ECX,0x0C
  Opaque tail_target;          // JMP 0x0096FFD0
  Opaque body_end_inclusive;   // 0x0096ff77
  Opaque int3_pad_end;         // 0x0096ff7f
  Opaque sole_data_xref;       // 0x0144258c
  Opaque vtable_run_base;      // 0x01442584
  Opaque dtor_primary_vtable;  // [this+0x00] = 0x014425d8
  Opaque dtor_layout_vtable;   // [this+0x04] = 0x014425c0
  Opaque dtor_bistate_vtable;  // [this+0x0c] = 0x01442584
  Opaque dtor_field_60_value;  // [this+0x60] = 0x013eb938
  Opaque delete_flag_mask;     // TEST byte [ESP+0x08],0x01
};

extern const Func88hConstants kFunc88hConstants;

// The pointer run based at 0x01442584, as read from .rdata. Slot +0x08 is the
// sole reference to 0x0096ff70 in the binary.
extern const GlideEffectVTableRun kGlideEffectVTableRun;

// SUB ECX,0x0C: the object 0x0096FFD0 operates on is this far below the
// receiver the thunk was handed.
GlideEffect* most_derived_below(const GlideEffectBiStateSubobject* self);

extern "C" void PKG_G8_THISCALL func88h_0096ff70(
    GlideEffectBiStateSubobject* self, std::uint32_t deleting_flag);
extern "C" Opaque PKG_G8_THISCALL func88h_vector_0096ff90(
    GlideEffectBiStateSubobject* self, std::uint32_t vector_delete_flag);

}
