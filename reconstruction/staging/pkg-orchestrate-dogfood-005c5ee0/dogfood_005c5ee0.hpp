#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-orchestrate-dogfood-005c5ee0 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-005c5ee0 requires MSVC or GCC CCs"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_005c5ee0 {

using OpaqueWord = std::uint32_t;

// The class name is taken from the imported SDK symbol
// `Palettes::PaletteMain::GetCategory` recorded by Ghidra for 0x005c5ee0. The
// body itself never names a class: SporeApp.exe carries no MSVC RTTI, so no
// hierarchy, base list, or object size is claimed. The modeled extent below is
// limited to the three words the binary itself touches, nothing more.
struct OpaquePaletteMain;
struct alignas(4) OpaquePaletteMainVtable;
struct alignas(4) OpaquePaletteMainSubobjectVtable;

// Direct callee 0x005c5e90. Its 78 raw bytes, 0x005c5e90 through the RET at
// 0x005c5edd, are `PUSH EBX; PUSH EBP; MOV EBP,ECX` ... `MOV dword ptr
// [EBP+0x0],0x013ec458; MOV dword ptr [EBP+0x8],0x013eb938; POP EBP; POP EBX;
// RET`, so the convention is thiscall with the receiver in ECX, no ordinary
// stack word, a plain RET and no callee-side stack cleanup. It overwrites the
// two vtable words of its receiver with 0x013f7fd4 and 0x013f7fc4 at entry and
// with 0x013ec458 and 0x013eb938 before returning, which is destructor-shaped
// behaviour. The EAX result of the call is never read by the caller because
// 0x005c5ef8 overwrites EAX.
using OpaquePaletteMainTeardown005c5e90 =
    void(PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL*)(OpaquePaletteMain*);

// Direct callee 0x00f47380, reached by `PUSH ESI; CALL 0x00f47380; ADD ESP,0x4`
// at 0x005c5eef-0x005c5ef5, so the convention is cdecl and the caller reclaims
// the single pushed word. The callee body is `if (param_1 != 0) FUN_009276c0
// (param_1);` with a void return, so the port is a null-guarded release of the
// receiver word.
using OpaquePaletteMainRelease00f47380 =
    void(PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL*)(void*);

// The entry occupies slot 0x00 of the vtable word stored at receiver+0x00. The
// shape is the one observed at 0x005c5ee0: ECX receiver, one ordinary stack
// word whose low byte is the only part read, and EAX returning the receiver
// word unchanged.
using OpaquePaletteMainGetCategory005c5ee0 = OpaquePaletteMain*(
    PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL*)(OpaquePaletteMain*, OpaqueWord);

// Live read of 0x013f7fc0 through 0x013f7fdf from SporeApp.exe gives
// 0x013f7fc0 = 0x34000000, 0x013f7fc4 = 0x00ae4340, 0x013f7fc8 = 0x00ae4330,
// 0x013f7fcc = 0x005c5e80, 0x013f7fd0 = 0x005c5bf0, 0x013f7fd4 = 0x005c5ee0 and
// 0x013f7fd8 = 0x00804901. Slot 0x00 is the only proven slot: the single DATA
// reference to 0x005c5ee0 is from 0x013f7fd4. The adjacent word is kept as an
// opaque slot because 0x00804900 is an instruction-aligned `SUB ECX,0x8; JMP
// 0x00804e70` thunk, so 0x00804901 is not an instruction start and the role of
// the second word is not proven.
struct alignas(4) OpaquePaletteMainVtable {
  OpaquePaletteMainGetCategory005c5ee0 slot_00;
  std::uintptr_t slot_04;
};

// Live read of 0x013f7fc4 through 0x013f7fd3 gives four words, each proven by
// disassembly to be an ECX-relative adjusting thunk: 0x00ae4340 and 0x00ae4330
// and 0x005c5e80 each start with `SUB ECX,0x8`, and 0x005c5e80 tail-jumps to
// the entry at 0x005c5ee0. That thunk is why the receiver may arrive as the
// address of the subobject at receiver+0x08 and be normalized by -8 before the
// entry body runs. No slot meaning is claimed for any of the four words.
struct alignas(4) OpaquePaletteMainSubobjectVtable {
  std::uintptr_t slot_00;
  std::uintptr_t slot_04;
  std::uintptr_t slot_08;
  std::uintptr_t slot_0c;
};

// Only the words the binary itself publishes are modeled. 0x005c5e90 stores
// 0x013f7fd4 at receiver+0x00 and 0x013f7fc4 at receiver+0x08, and the
// 0x005c5e80 thunk subtracts 8 from ECX before reaching the entry, so both
// words are vtable pointers of one object. The word at +0x04 is read by
// 0x005c5e90 through `MOV ESI,[EBP+0x04]` and is then subtracted against the
// word at +0x0c, so it is kept as an opaque word: neither its value nor the
// type of the pointer it may hold is claimed. The 0x0c extent is a modeling
// bound: the entry body dereferences no receiver word at all and the allocation
// size is unknown.
struct alignas(4) OpaquePaletteMain {
  OpaquePaletteMainVtable* vtable_00;
  std::uintptr_t word_04;
  std::uintptr_t vtable_08;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(offsetof(OpaquePaletteMainVtable, slot_00) == 0x00,
              "entry slot offset from the live 0x013f7fd4 table read");
static_assert(sizeof(OpaquePaletteMainVtable) == 8,
              "vtable modeled window through the adjacent 0x013f7fd8 word");
static_assert(offsetof(OpaquePaletteMainSubobjectVtable, slot_08) == 0x08,
              "thunk slot offset from the live 0x013f7fc4 table read");
static_assert(sizeof(OpaquePaletteMainSubobjectVtable) == 0x10,
              "subobject vtable modeled window extent");
static_assert(offsetof(OpaquePaletteMain, vtable_00) == 0x00,
              "primary vtable word offset from the 0x005c5e90 stores");
static_assert(offsetof(OpaquePaletteMain, word_04) == 0x04,
              "receiver word offset read by 0x005c5e90");
static_assert(offsetof(OpaquePaletteMain, vtable_08) == 0x08,
              "subobject vtable word offset from the 0x005c5e90 stores");
static_assert(sizeof(OpaquePaletteMain) == 0x0c,
              "receiver modeled prefix extent, not a recovered object size");
static_assert(sizeof(OpaquePaletteMainTeardown005c5e90) == 4,
              "teardown port width");
static_assert(sizeof(OpaquePaletteMainRelease00f47380) == 4,
              "release port width");
static_assert(sizeof(OpaquePaletteMainGetCategory005c5ee0) == 4,
              "entry slot width");
static_assert(std::is_same<OpaquePaletteMainTeardown005c5e90,
                           void(PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL*)(
                               OpaquePaletteMain*)>::value,
              "0x005c5e90 keeps thiscall and takes no ordinary stack word");
static_assert(
    std::is_same<OpaquePaletteMainRelease00f47380,
                 void(PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL*)(void*)>::value,
    "0x00f47380 is a cdecl one-word release whose caller reclaims the word");
static_assert(
    std::is_same<
        OpaquePaletteMainGetCategory005c5ee0,
        OpaquePaletteMain*(
            PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL*)(OpaquePaletteMain*,
                                                        OpaqueWord)>::value,
    "entry slot matches the entry point shape");

struct GetCategoryPorts {
  OpaquePaletteMainTeardown005c5e90 teardown_005c5e90 = nullptr;
  OpaquePaletteMainRelease00f47380 release_00f47380 = nullptr;
};

static_assert(sizeof(GetCategoryPorts) == 8,
              "port table holds two 32-bit slots");

extern GetCategoryPorts g_dogfood_005c5ee0_ports;

extern "C" OpaquePaletteMain* PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL
palettes_palette_main_get_category_005c5ee0(OpaquePaletteMain* main,
                                            OpaqueWord stack_word);

}

#undef PKG_ORCHESTRATE_DOGFOOD_005C5EE0_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_005C5EE0_THISCALL
