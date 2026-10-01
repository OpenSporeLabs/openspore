#pragma once

// Bounded x86-32 reconstruction of the body at VA 0x005c8bc0.
//
//   VA       0x005c8bc0
//   Program  SPORE/SporeBin/SporeApp.exe 3.1.0.22
//            (sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//   Body     0x005c8bc0 .. 0x005c8be6, 12 instructions, 39 bytes
//   Slot     word 7 of the function-pointer table at 0x013f82fc
//
// The Spore SDK symbol table (SporeGhidra_march2017.xml, line 53122) names this
// address `Palettes::PalettePage::Load`, and the SDK header declares that method
// as CONVENTION="thiscall" with six parameters, which would require an epilogue
// of RET 0x14. The machine body ends in RET 0x4. The SDK name is therefore NOT
// adopted here; see the metadata sidecar, unresolved_questions, and the note on
// the vtable below. What is reconstructed is the body the binary actually ships.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PALETTE-CLASSID-SLOT7 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "PKG-PALETTE-CLASSID-SLOT7 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "PKG-PALETTE-CLASSID-SLOT7 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_PCS7_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_PCS7_THISCALL __attribute__((thiscall))
#else
#error "PKG-PALETTE-CLASSID-SLOT7 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_palette_classid_slot7 {

// The receiver of the slot. The body copies ECX to the return register and never
// dereferences it, so no layout is declared and no field offset is claimed: the
// opaque type exists only to carry the thiscall receiver register, and it is
// never read.
struct alignas(4) OpaqueSlot7Receiver;

// The three constants the body compares the stack argument against. Every one of
// them is a Spore 32-bit class token: the SDK symbol table's ENUM_ENTRY list
// carries
//   Object                  0xee3f516e   (SporeGhidra_march2017.xml line 51581)
//   UTFWin::IWinProc        0x2f009dd0   (line 51651)
//   Palettes::PalettePageUI 0x72deed2b   (line 51714)
// so the single four-byte argument is a class id being asked about, not a
// resource key and not a page/layout id. The names are the SDK's; nothing here
// reinterprets them.
inline constexpr std::uint32_t kClassIdObject = 0xee3f516eU;
inline constexpr std::uint32_t kClassIdUTFWinIWinProc = 0x2f009dd0U;
inline constexpr std::uint32_t kClassIdPalettePageUI = 0x72deed2bU;

// The 39 bytes the binary ships at 0x005c8bc0, in listing order. Kept as a
// constant so the model test can pin the reconstruction's compiled body against
// the original encoding rather than against a paraphrase of it.
inline constexpr std::uint8_t kObservedBody[39] = {
    0x8b, 0xc1,                                     // 005c8bc0  MOV EAX,ECX
    0x8b, 0x4c, 0x24, 0x04,                         // 005c8bc2  MOV ECX,[ESP+0x4]
    0x81, 0xf9, 0x6e, 0x51, 0x3f, 0xee,             // 005c8bc6  CMP ECX,0xee3f516e
    0x74, 0x16,                                     // 005c8bcc  JZ  0x005c8be4
    0x81, 0xf9, 0xd0, 0x9d, 0x00, 0x2f,             // 005c8bce  CMP ECX,0x2f009dd0
    0x74, 0x0e,                                     // 005c8bd4  JZ  0x005c8be4
    0x33, 0xd2,                                     // 005c8bd6  XOR EDX,EDX
    0x81, 0xf9, 0x2b, 0xed, 0xde, 0x72,             // 005c8bd8  CMP ECX,0x72deed2b
    0x0f, 0x95, 0xc2,                               // 005c8bde  SETNZ DL
    0x4a,                                           // 005c8be1  DEC EDX
    0x23, 0xc2,                                     // 005c8be2  AND EAX,EDX
    0xc2, 0x04, 0x00,                               // 005c8be4  RET 0x4
};

// Returns the receiver unchanged when `class_id` is one of the three class ids
// above, and a null pointer for every other value.
//
// The result is declared as the receiver pointer rather than as a bool because
// the body moves the whole 32-bit ECX word into EAX: live decompilation spells
// the return `bool` and renders the test on the low byte, but the machine
// returns four bytes and the RETURN SEMANTICS contract is not settled by this
// body. Spelling it as a pointer is the reading under which all twelve
// instructions are used exactly as written; it is not a claim that the original
// header said so.
//
// The receiver is typed but never dereferenced, so a null receiver and a
// receiver pointing at storage the function has no reason to know about are both
// legal inputs and are both left untouched.
OpaqueSlot7Receiver* PKG_PCS7_THISCALL palette_classid_slot7_005c8bc0(
    OpaqueSlot7Receiver* receiver, std::uint32_t class_id);

}  // namespace openspore::reconstruction::pkg_palette_classid_slot7
