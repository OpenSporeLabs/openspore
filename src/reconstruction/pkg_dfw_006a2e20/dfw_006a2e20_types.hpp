// PKG-DFW-006A2E20 -- VA 0x006a2e20
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for App::PropertyList::SetProperty @ 0x006a2e20.
//
// HONESTY NOTE ON WHERE EVERY OFFSET IN THIS HEADER COMES FROM, because the
// split matters to a reader:
//
//  * The four receiver displacements this body itself shows -- 0x18, 0x1c, 0x2c
//    and 0x34 -- are read straight out of its own 65-instruction listing and are
//    the complete set the machine-derived receiver record enumerates
//    (receiver.offsets = [24, 28, 44, 52], register ECX, bounds_only true).
//
//  * The sub-layouts of the map (begin/end/mode), of a map entry (key, embedded
//    record) and of the embedded record (four opaque words, a flags word, a type
//    word) are NOT shown by this body. They are read off the bodies of the four
//    direct callees in the same image, whose raw bytes were re-read for this
//    package:
//      - 0x006a2c50 reads map+0x00 (MOV ECX,[ESI]), map+0x04 (MOV EDI,[ESI+4])
//        and map+0x14 (MOVZX EAX,BYTE PTR [ESI+0x14]) with ECX = the receiver's
//        own +0x18, so those three are the same bytes this body reads at its
//        +0x18, +0x1c and +0x2c.
//      - 0x006a2940 writes map+0x08 (MOV [ESI+8],capacity) and steps entries by
//        0x18 (LEA ECX,[EAX+0x18]; LEA EDX,[EDI+EDI+2]; LEA EAX,[EAX+EDX*8]).
//      - 0x00612db0 divides the element count by 0x18 and compares the leading
//        dword of each element (CMP/IMUL form: `(last-first)/0x18`, then
//        `*(dword*)(first + i*0x18) < key`).
//      - 0x006a2940 lays a new entry out as key at +0, embedded record at +4,
//        its flags word at +0x14 and its type word at +0x16.
//      - 0x00542b80 copies four dwords from source+0x00..+0x0f into
//        destination+0x00..+0x0f, copies source+0x12 to destination+0x12 and
//        recomposes destination+0x10 as (source.flags & ~0x0002) | (dest.flags &
//        0x0002); nothing at or beyond +0x14 is touched. 0x14 bytes exactly, and
//        0x04 + 0x14 == the 0x18 entry stride, which is what fixes both sizes.
//
//  * No member is named. Every sub-object below is spelled field_<hex offset>,
//  which states where it lives and nothing about what it is for. The two type
//  names themselves (Property, PropertyList) are the ones the target's own
//  record already carries: the SDK-derived Ghidra prototype is
//  `void App::PropertyList::SetProperty(PropertyList *this, uint32_t propertyID,
//  Property *pValue)` and the pack's types category lists Property and
//  PropertyList for this VA.
//
//  * The +0x2c byte and the map's +0x14 byte are the SAME byte, and that is not
//  an assumption: 0x006a2e47 forms ESI = receiver+0x18 and 0x006a2ea8 hands ESI
//  to 0x006a2c50 as its receiver, and 0x006a2c58 then reads that object's +0x14,
//  which is receiver+0x2c -- the byte this body reads at 0x006a2e3d.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-006a2e20 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC 16 rejects the
// bare MSVC keywords outright, so the x86-32 attribute form is the portable
// spelling and the keyword form is kept for MSVC. Both are asserted by machine
// facts, not chosen for convenience:
//
//   PKG_DFW_006A2E20_THISCALL  the four direct callees this body reaches. Three
//     of them are __thiscall by their own terminators: 0x00542b80, 0x006a2c50 and
//     0x0093db80 each end in `C2 imm16` (RET 0x4, RET 0x8, RET 0x4 -- the bytes
//     read directly out of the image) and each takes its receiver in ECX, so the
//     callee owns the argument cleanup.
//   PKG_DFW_006A2E20_CDECL     0x00612db0, whose last three bytes are `5E C3`
//     (POP ESI; RET) with no immediate: it returns without touching ESP, and
//     0x006a2e5b drops the four words with `ADD ESP,0x10` itself.
#if defined(_MSC_VER)
#define PKG_DFW_006A2E20_THISCALL __thiscall
#define PKG_DFW_006A2E20_CDECL __cdecl
#else
#define PKG_DFW_006A2E20_THISCALL __attribute__((thiscall))
#define PKG_DFW_006A2E20_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dfw_006a2e20 {

using Word = std::uint32_t;

// The 0x14-byte record the four direct callees move around. Proven from
// 0x00542b80's own listing, which is the only body in the set that names every
// one of its offsets:
//
//   0x00542bcd MOV EAX,[ECX]        / 0x00542bcf MOV [EDX],EAX   -> +0x00
//   0x00542bd1 MOV EAX,[ECX+0x4]    / 0x00542bd4 MOV [EDX+0x4],EAX -> +0x04
//   0x00542bd7 MOV EAX,[ECX+0x8]    / 0x00542bda MOV [EDX+0x8],EAX -> +0x08
//   0x00542bdd MOV ECX,[ECX+0xc]    / 0x00542be0 MOV [EDX+0xc],ECX -> +0x0c
//   0x00542be9 MOV CX,WORD [EAX+0x12] / 0x00542bed MOV [EDX+0x12],CX -> +0x12
//   0x00542bf4 MOVZX EAX,WORD [EAX+0x10]
//   0x00542bf8 AND EAX,0xfffffffd
//   0x00542bfe MOVZX EDX,WORD [ECX+0x10] / 0x00542c02 AND EDX,0x2
//   0x00542c05 OR EAX,EDX / 0x00542c0a MOV WORD [ECX+0x10],AX      -> +0x10
//
// The two named bits are read straight off that listing and are the only two
// bits any record establishes: 0x0002 is a destination bit 0x00542b80 carries
// across instead of overwriting, and 0x0004 is the bit that makes 0x00542b80
// itself call 0x0093db80 with the argument 1 (0x00542b8e AND ECX,0x4) and the
// bit 0x0093db80 re-tests on its own receiver (0x0093db83 TEST BYTE [ESI+0x10],4).
// Nothing here says what either bit means.
struct Property {
  std::array<Word, 4> field_00_0c;  // 0x00..0x0f, four opaque words
  std::uint16_t field_10;           // bit 0x0002 preserved on assign, bit 0x0004 reported
  std::uint16_t field_12;           // compared and copied whole by 0x00542b80
};
static_assert(sizeof(Property) == 0x14, "0x00542b80 touches no byte past +0x13");
static_assert(offsetof(Property, field_10) == 0x10, "flags word offset");
static_assert(offsetof(Property, field_12) == 0x12, "type word offset");

// One element of the ordered array the receiver embeds. 0x18 stride, key in the
// leading dword, record at +0x04, which is exactly 0x04 + 0x14.
//
// 0x00612db0 (the search) divides by 0x18 and reads the leading dword of the
// element; 0x006a2940 (the splice) does `MOV [EAX],ECX` for the key and
// `LEA ECX,[EAX+0x4]` for the record, then zeroes [ECX+0x10] and [ECX+0x12] and
// calls 0x00542b80 with EDX+4. Both the stride and the two sub-offsets are fixed
// by those listings, not guessed.
struct MapEntry {
  Word field_00;      // the ordered key: compared unsigned against the key word
  Property field_04;  // 0x14 bytes, ends the 0x18 stride exactly
};
static_assert(sizeof(MapEntry) == 0x18, "0x18 element stride");
static_assert(offsetof(MapEntry, field_04) == 0x04, "record offset inside an entry");

// The array object embedded at receiver+0x18. 0x006a2c50 reads +0x00, +0x04 and
// +0x14; 0x006a2940 reads and writes +0x08. 0x0c..0x13 are named as an opaque run
// because no body in this set touches them and no record says what they are. The
// object is 0x15 bytes as observed and the model rounds it to 0x18 with implicit
// tail padding, which is a layout choice of the model and not a claim: nothing
// in this set reads or writes the map at +0x15 or beyond.
struct PropertyMap {
  MapEntry* field_00;                            // begin; 0x00612db0's first argument
  MapEntry* field_04;                            // end; 0x00612db0's second argument
  void* field_08;                                // capacity; written only by 0x006a2940
  std::array<std::uint8_t, 8> field_0c_13;       // untouched by anything in this set
  std::uint8_t field_14;                         // the byte this body reads at receiver+0x2c
};
static_assert(offsetof(PropertyMap, field_14) == 0x14, "mode byte offset inside the map");
static_assert(sizeof(PropertyMap) == 0x18, "map object rounded to 0x18 by the model");

// 0x006a2c50's out record: 8 bytes, written but never read by 0x006a2e20.
// 0x006a2c7e MOV [ECX],EAX then 0x006a2c80 MOV BYTE [ECX+4],0x0 on the
// already-present path; 0x006a2c99 MOV [ECX],EAX then 0x006a2c9b MOV BYTE
// [ECX+4],0x1 after 0x006a2940 ran. The callee also returns the record address
// in EAX (0x006a2c84 / 0x006a2c9f MOV EAX,ECX) and this body never looks at EAX
// again, which is why the record is modelled as a write-only local.
struct FindOrInsertResult {
  MapEntry* field_00;
  std::uint8_t field_04;
  std::uint8_t field_05_07[3];
};
static_assert(sizeof(FindOrInsertResult) == 8, "8-byte out record");

// The receiver. This body reads three of its words and writes one, every one of
// them by displacement, and touches nothing else on it:
//
//   0x006a2e3d MOVZX ECX,byte ptr [EDI + 0x2c]   read
//   0x006a2e41 MOV EBX,dword ptr [EDI + 0x1c]     read
//   0x006a2e44 MOV EAX,dword ptr [EDI + 0x18]     read
//   0x006a2e47 LEA ESI,[EDI + 0x18]               address, not a read
//   0x006a2e74 CMP EAX,dword ptr [EDI + 0x1c]     read
//   0x006a2ed1 INC dword ptr [EDI + 0x34]         write
//
// The machine-derived receiver record enumerates exactly those four
// displacements (0x18, 0x1c, 0x2c, 0x34), register ECX with shape R-ALIAS, and
// carries bounds_only - it states where the body was seen reaching and not which
// member is which. So this type declares NO member: 0x00..0x17 and 0x2d..0x33 are
// never read or written here, and calling any of them a map, a counter, a
// version or a flag would be a member story this body's evidence does not carry.
// The receiver is an opaque 0x38-byte run and the body reaches it as
// displacements.
//
// The embedded PropertyMap layout further down is a different matter and stays:
// it is fixed by OTHER listings (0x006a2c50, 0x006a2940), and this body hands
// the map's address to 0x006a2c50 rather than reading through it.
//
// The vtable association recorded for this VA (vtable 0x01408820, this body at
// its slot +0x14 -- confirmed by reading the table's own bytes and by the xref
// from 0x01408834) is likewise NOT modelled as a member at +0x00, because this
// body's listing contains no read of +0x00 and naming a dispatch word it never
// touches would be a claim the machine does not support.
struct alignas(4) PropertyList {
  std::array<std::uint8_t, 0x38> opaque_00{};  // 0x00..0x37
};

// The receiver displacements this body was seen reaching, as values. 0x18 and
// 0x1c are the two words the ordered array's begin and end live in, 0x2c is the
// single byte the MOVZX reads, and 0x34 is the single word it increments; the
// names in that sentence are descriptions of the two listings, not members.
constexpr std::size_t kReceiverArrayDisplacement = 0x18;
constexpr std::size_t kReceiverEndDisplacement = 0x1c;
constexpr std::size_t kReceiverModeByteDisplacement = 0x2c;
constexpr std::size_t kReceiverCounterDisplacement = 0x34;

// The sub-displacements of one array element and of the 0x14-byte record inside
// it, from the same four callee listings the two structs below are derived
// from. They are offsets, not member names: nothing here says what a word is
// for, only where it sits.
constexpr std::size_t kElementKeyDisplacement = 0x0;
constexpr std::size_t kElementRecordDisplacement = 0x4;
constexpr std::size_t kRecordFlagsDisplacement = 0x10;
constexpr std::size_t kRecordTypeDisplacement = 0x12;

// The only way the body under reconstruction touches any of the above: a word
// or a halfword at a stated displacement. A member access would assert an
// identity the machine-derived record cannot corroborate.
inline std::uint32_t* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                         displacement);
}

inline const std::uint32_t* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline std::uint16_t* halfword_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint16_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

static_assert(sizeof(PropertyList) == 0x38,
              "0x34 + 4 is the last byte the body writes on the receiver");
static_assert(kReceiverCounterDisplacement + sizeof(Word) == sizeof(PropertyList),
              "the counter word ends the modeled receiver");
static_assert(kReceiverArrayDisplacement + 0x14 == kReceiverModeByteDisplacement,
              "the map's own +0x14 byte is the receiver's +0x2c byte");

// -- the four direct callees ------------------------------------------------
// Each is declared here, and none is defined here: the model test defines all
// four as observers. Every signature below is fixed by the callee's own bytes,
// not by its decompilation.

// 0x00612db0, called at 0x006a2e52. cdecl: the body pushes four words
// (0x006a2e4a the zero-extended map byte, 0x006a2e4f the address of the key
// word, 0x006a2e50 the array end, 0x006a2e51 the array begin) and drops them
// itself with ADD ESP,0x10 at 0x006a2e5b, and the callee's terminator is
// `5E C3` (POP ESI; RET) with no immediate. The fourth word is the byte the body
// read at its receiver+0x2c, zero-extended by the MOVZX; the callee's own
// prototype names only three parameters, and its listing never reads the fourth
// slot, so what that word is for is unresolved (see the sidecar). The third word
// is a POINTER to the key: 0x00612db0 dereferences it (`CMP EDX,[EBX]` at
// 0x006a2c72 is the same shape inside 0x006a2c50's copy of the call, and inside
// 0x00612db0 itself it is `*(dword*)(first + i*0x18) < *param_3`).
extern "C" MapEntry* PKG_DFW_006A2E20_CDECL entry_array_lower_bound_00612db0(
    MapEntry* first, MapEntry* last, Word* key, Word mode);

// 0x00542b80, called at 0x006a2e7c and 0x006a2e99. __thiscall, destination in
// ECX, source as the single stack word, terminator `C2 04 00` (RET 0x4). It
// returns its destination argument in EAX (0x00542c1e MOV EAX,[EBP-4]), which
// this body never reads.
extern "C" Property* PKG_DFW_006A2E20_THISCALL property_assign_00542b80(
    Property* destination, Property* source);

// 0x006a2c50, called at 0x006a2eb2. __thiscall, the array object in ECX, two
// stack words, terminator `C2 08 00` (RET 0x8). Argument order is fixed by the
// callee's own frame reads, not by its decompilation: 0x006a2c78
// `MOV ECX,[ESP+0x10]` (the first stack word, after its own three pushes) is the
// record it writes, and 0x006a2c51 `MOV EBX,[ESP+0xc]` (the second stack word) is
// the entry it reads the key from. It returns the record address in EAX.
extern "C" FindOrInsertResult* PKG_DFW_006A2E20_THISCALL property_map_find_or_insert_006a2c50(
    PropertyMap* map, FindOrInsertResult* result, MapEntry* entry);

// 0x0093db80, called at 0x006a2ecc. __thiscall, receiver in ECX, one stack word
// read as a byte (0x0093d9d CMP BYTE [ESP+8],0 after its own PUSH ESI),
// terminator `C2 04 00` (RET 0x4). The name is the one this target's own record
// carries for it (callees_dependencies[0].name =
// "editor_query_clear_flags_0093db80"); what this body uses it for is narrower --
// it always passes the argument 0, and with that argument the callee's own
// listing returns without running the clearing half at 0x0093da4.
extern "C" void PKG_DFW_006A2E20_THISCALL editor_query_clear_flags_0093db80(
    Property* receiver, std::uint8_t argument);

// -- model instrumentation ---------------------------------------------------
// The 4-byte frame slot the body writes 0 at 0x006a2eaa and 0xffffffff at
// 0x006a2ebc, resolved against the entry ESP it is at entry_ESP-4 -- the same
// slot the prologue's `PUSH -1` fills, i.e. the structured-exception try-level
// word of the scope the prologue installed. Nothing in this body ever reads it,
// so it cannot be a parameter, a return value or a receiver field, and it is not
// part of the machine's observable surface.
//
// The model keeps it in a file-scope word purely so the model test can assert
// the ORDER of the two stores relative to the 0x006a2c50 call: the test's
// 0x006a2c50 observer samples try_level_word() and must see 0 (scope active),
// and the test must see 0xffffffff (scope left) once the call has returned. This
// is instrumentation, not a machine global, and it is declared in the header so
// the test can reach it.
std::int32_t try_level_word();

// App::PropertyList::SetProperty @ 0x006a2e20.
//
// __thiscall, receiver in ECX, exactly two ordinary stack arguments, `RET 0x8`.
// The terminator is machine-observed (0x006a2ee5 `C2 08 00`), and the argument
// count is not a guess: the epilogue pops EDI/ESI/EBX (0x006a2ed8..0x006a2eda),
// restores FS:[0] from [ESP+0x2c] (0x006a2ed4) and then `ADD ESP,0x2c`
// (0x006a2ee2) lands ESP back on the entry value, and `RET 0x8` consumes the
// return address plus two argument words. Ghidra's own prototype for this VA
// carries a third parameter, but its decompilation reports "Unknown calling
// convention" and nothing in the body reads a third slot; the two arguments the
// body does touch are fixed by the listing (see the model).
//
// Return type is void. Both records say so (abi.return_type "void" and
// ghidra_function.return_type "void"), and the body bears it out: the receiver is
// copied into EDI at 0x006a2e3b and never moved back into EAX on any path, so
// EAX is dead at 0x006a2ee5. EAX is in fact left holding three different dead
// values depending on the path (the surviving search candidate, the array end,
// or 0x006a2c50's own return word), which is why it is not modelled at all.
extern "C" void PKG_DFW_006A2E20_THISCALL dfw_property_set_006a2e20(
    PropertyList* receiver, Word key, Property* source);

}  // namespace openspore::reconstruction::pkg_dfw_006a2e20
