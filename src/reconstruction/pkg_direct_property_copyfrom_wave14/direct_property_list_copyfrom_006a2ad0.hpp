// PKG-DIRECT-PROPERTY-COPYFROM-WAVE14 -- VA 0x006a2ad0
// App::DirectPropertyList::CopyFrom
//
// Boundary declarations for the bounded reconstruction staged at
// reconstruction/staging/pkg-direct-property-copyfrom-wave14/. The body itself
// lives in the package's own translation unit
// (direct_property_list_copyfrom_006a2ad0.cpp) and is NOT included from here:
// that unit is pinned by sha256 in reconstruction/evidence/006a2ad0/validation.json
// and must keep compiling unchanged. This header is purely additive and is
// included only by the behavioural model test.
//
//   VA            0x006a2ad0
//   Program       SPORE/SporeBin/SporeApp.exe 3.1.0.22
//                 (sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//   Body          0x006a2ad0 .. 0x006a2b15, 33 instructions, machine parse 33/33
//   Terminator    0x006a2b15  RET 0x4 -- the callee drops the one 4-byte
//                 stack argument, which is what rules out cdecl and fastcall
//   Vtable        vtable:0x01408870, this function reached through the word at
//                 0x0140889c (the only function xref the record carries)
//
// ABI, as the derived record states it: __thiscall, receiver in ECX aliased to
// EDI at 0x006a2ad6, one ordinary stack argument read at entry_ESP+0x4 by
// 0x006a2ad1 (MOV EBX,[ESP + 0x8]) and reused as the source-list pointer,
// return type void, EBX/EDI/ESI saved. The record's own calling-convention
// confidence is INFERRED, not proven, and it abstained on flow ("the linear ESP
// walk ends at +12"), so nothing here upgrades either.
//
// NO NAMES ARE INVENTED. No machine record in this package names a struct
// member, an element type, a slot index or a slot target, so every word the
// body touches is stated as the machine displacement it appears at, on the
// object the listing shows it on. Concretely:
//
//   * The slot target is UNRESOLVED. The 33-instruction listing and the ABI
//     envelope name the displacement 0x14 and nothing else; nothing names the
//     function that word points at. The type below is the shape the transfer
//     itself forces, not a symbol.
//   * The vtable address 0x01408870 is deliberately NOT written as a literal
//     anywhere in this package. The record associates this body with it and the
//     single xref from 0x0140889c supports reading the receiver's word 0 as a
//     table pointer, but the derived ABI record's own vtable_shaped_loads count
//     is 0, so that reading is INFERRED. The body reads the word indirectly; a
//     literal here would assert more than the evidence carries.
//   * Whether the receiver's word 0 is a vtable pointer, and which slot index
//     displacement 0x14 corresponds to, is an open question in the metadata.
//   * The exact element type of the 0x18-stride range is unresolved. Only the
//     stride, the first word at +0x0 and the address at +0x4 are observed;
//     nothing establishes the bytes between them, so the test's element fixture
//     is opaque padding and no field of it is named after a meaning.
//   * The derived receiver record (abi_derived.receiver) is `bounds_only` and
//     enumerates only displacements 0x0 and 0x30, observed through the EDI alias
//     of the receiver. bounds_only is that record's statement about itself: it
//     says where the body was SEEN REACHING and nothing more. It is not an
//     enumeration of the receiver's words and not a statement about the object,
//     so the receiver displacement 0x18 (LEA ECX,[EDI + 0x18] at 0x006a2add),
//     which it does not enumerate, is UNCORROBORATED BY that record -- not
//     contradicted by it. A bounds_only record cannot refute anything, and its
//     observation criteria are not documented in this repository, so it is not
//     established that it would have listed 0x18 had 0x18 been reached
//     identically to 0x0 and 0x30. All three are reached through the same EDI
//     alias, which is what makes the omission worth a question rather than a
//     shrug. The receiver's layout is unresolved in both directions.
//   * Separately, of the displacements declared below, only 0x18 and 0x30 sit on
//     the receiver at all: 0x00 and 0x18-on-the-element and 0x04 are on the
//     element, 0x14 is on the receiver's table word, and 0x1c is on the argument
//     object. A receiver record's silence about those is not a statement about
//     the receiver.
//   * Nothing here asserts what 0x006a28f0 does beyond the ordering the listing
//     fixes, and nothing asserts what the receiver's word at 0x30 means. The
//     record names 0x006a1710 App::PropertyList::SetParent; that name is the
//     Ghidra record's and is not repeated as a claim about semantics here.
//
// All five transfers the body makes are declared below in the shape the listing
// forces: two direct relative CALLs and one two-level table load ending in
// CALL EAX at 0x006a2afe.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-direct-property-copyfrom-wave14 requires an x86-32 target"
#endif

// The two conventions this package uses, spelled per toolchain. The x86-32
// attribute is what the machine-derived ABI record asserts, and it is not the
// same token on both compilers: MSVC spells the convention as a keyword
// (__thiscall/__cdecl) while gcc and clang only accept the __attribute__ form
// and reject the keywords outright. 0x006a2b15 is RET 0x4, so the callee drops
// the single 4-byte stack argument -- that is why the entry point and both
// direct callees are __thiscall and not __cdecl.
#if defined(_MSC_VER)
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL __thiscall
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_CDECL __cdecl
#else
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL __attribute__((thiscall))
#define PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_direct_property_copyfrom_wave14 {

static_assert(sizeof(void *) == 4,
              "this reconstruction is x86-32: every word it moves is 4 bytes");
static_assert(sizeof(std::uint32_t) == 4, "one machine word is 32 bits");

// One machine word. The body never states what any word it reads means, so the
// word is carried opaquely and no structure is asserted for it.
using Word = std::uint32_t;

// The word the slot transfer pushes as its first ordinary argument
// (0x006a2afb PUSH EDX, EDX loaded by 0x006a2af2 MOV EDX,dword ptr [ESI]).
// Distinctly named so it is never confused with the *address* of the element's
// second field, which is what the second argument is. No meaning is claimed for
// the value.
using TargetWord = Word;

// ---------------------------------------------------------------------------
// Displacements
// ---------------------------------------------------------------------------
// Every constant below is a displacement that appears verbatim in the
// 33-instruction listing, quoted with the instruction that shows it. They are
// grouped by the object the listing puts them on, because the derived receiver
// record speaks only to the receiver group and must not be charged with the
// rest.

// Receiver (EDI, the ECX receiver alias set at 0x006a2ad6).
//
// 0x006a2af0  MOV EAX,dword ptr [EDI]  -- the receiver's first word, loaded
// inside the loop and then indexed. One of the two displacements the
// bounds_only receiver record does enumerate.
constexpr std::size_t kReceiverTableWordOffset = 0x00u;

// 0x006a2add  LEA ECX,[EDI + 0x18]  -- the address formed and handed to
// 0x006a28f0 as the sub-object's own receiver. NO ADDRESS IS DEREFERENCED HERE:
// it is LEA, so the body forms the address and passes it, and this package says
// nothing about the bytes at 0x18. This is the one receiver displacement the
// bounds_only record does not enumerate; see the header comment.
constexpr std::size_t kReceiverRangeSubObjectOffset = 0x18u;

// 0x006a2b07  MOV ECX,dword ptr [EDI + 0x30]  -- the word loaded into ECX and
// pushed at 0x006a2b0a, in the tail block 0x006a2b07..0x006a2b0d. The body
// pushes the VALUE of that word, not its address. The other receiver
// displacement the bounds_only record enumerates.
constexpr std::size_t kReceiverParentWordOffset = 0x30u;

// Argument object (EBX, the source-list pointer).
//
// 0x006a2ae5  MOV ESI,dword ptr [EBX + 0x18]  -- source range begin pointer,
// read AFTER the 0x006a28f0 call at 0x006a2ae0.
constexpr std::size_t kSourceRangeBeginOffset = 0x18u;

// 0x006a2ae8  MOV EBX,dword ptr [EBX + 0x1c]  -- source range end pointer, also
// read after that call.
constexpr std::size_t kSourceRangeEndOffset = 0x1cu;

// Element (ESI, the walk cursor).
//
// 0x006a2af2  MOV EDX,dword ptr [ESI]  -- the element's first word, the value
// the slot transfer receives as its first ordinary argument.
constexpr std::size_t kElementFirstWordOffset = 0x00u;

// 0x006a2af7  LEA ECX,[ESI + 0x4]  -- the ADDRESS of the element's second
// field, pushed at 0x006a2afa. The body takes the address and does not load the
// word there. The element's internal split is not established by any record.
constexpr std::size_t kElementSecondFieldOffset = 0x04u;

// 0x006a2b00  ADD ESI,0x18  -- the element stride, and the value the loop
// compares its cursor against. The same 0x18 is the step 0x006a28f0 advances its
// own end word by per element, which is how the resize callee and this body's
// walk agree on the element size.
constexpr std::size_t kElementStride = 0x18u;

// The receiver's table word (EAX after 0x006a2af0), not the receiver itself.
//
// 0x006a2af4  MOV EAX,dword ptr [EAX + 0x14]  -- the function pointer the body
// transfers through at 0x006a2afe CALL EAX. The single indirect transfer site
// of the body. No machine record names the function this word holds, so the
// target is UNRESOLVED; 0x14 is a table displacement and says nothing about an
// element size or a slot index.
constexpr std::size_t kTableEntryOffset = 0x14u;

// ---------------------------------------------------------------------------
// Transfer shapes
// ---------------------------------------------------------------------------
// 0x006a2afe CALL EAX. The shape is forced by the pushes and the register
// writes around it, not by any prototype: 0x006a2af7 forms the second argument
// in ECX, 0x006a2afa PUSH ECX, 0x006a2afb PUSH EDX, 0x006a2afc MOV ECX,EDI, and
// the call follows with no stack adjustment anywhere after it in the body -- so
// the receiver is the hidden ECX argument, the two words are the callee's to
// drop (a __thiscall member shape), and the call is made through a
// function-pointer local re-read on every iteration.
//
// The names of the three parameters are the listing's own. The first ordinary
// argument is the element's first word, whose meaning no record establishes;
// the second is the ADDRESS of the element's second field, not its value. The
// declared type is therefore the only thing asserted, and the target itself is
// left unresolved by design.
//
// NOTE ON THE NAME: this typedef lives inside this namespace on purpose. The
// reconstructed body spells the same shape at global scope as
// `SlotTarget_006a2ad0`; defining a second global typedef with that name would
// clash with the pinned translation unit.
using SlotTarget_006a2ad0 =
    void (PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL *)(void *receiver,
                                                          TargetWord first_word,
                                                          void *second_argument);

// 0x006a28f0, called at 0x006a2ae0 on the receiver-only sub-object at
// displacement 0x18. Nothing is pushed and the address arrives in ECX, so the
// shape is a one-word __thiscall with no ordinary argument. Its own body reads
// the two words at +0x0 and +0x4 of that sub-object, calls 0x00612b20 and
// 0x00685a30, and advances the word at +0x4 by 0x18 per element -- i.e. it sizes
// a 0x18-stride element range to an element count. That is a reading of the
// callee's own listing; what it does beyond sizing is not characterised here.
//
// Declared, not defined: it lives outside this package. The model test supplies
// it as an observer.
extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL
App_unmodelled_element_range_resize_006a28f0(void *element_range);

// 0x006a1710, the address the Ghidra record names
// App::PropertyList::SetParent, called at 0x006a2b0d. ECX is the receiver
// (0x006a2b0b MOV ECX,EDI) and one word is pushed (0x006a2b0a PUSH ECX, the
// value read at 0x006a2b07 from receiver displacement 0x30). The name is the
// record's; no semantics beyond that push are claimed.
//
// Declared, not defined: it lives outside this package. The model test supplies
// it as an observer.
extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL
App_PropertyList_SetParent_006a1710(void *receiver, void *parent_word);

// 0x006a2ad0 itself, defined in the package's own pinned translation unit.
//
// The body is declared at global scope there. C language linkage is a property
// of the name, not of the scope it is declared in, so this declaration inside
// openspore::reconstruction::pkg_direct_property_copyfrom_wave14 names the same
// entity and the pinned unit still compiles unchanged.
extern "C" void PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL
App_DirectPropertyList_CopyFrom_006a2ad0(void *self, void *p_other);

// Read one machine word at a displacement from an opaque base. memcpy keeps the
// read well defined whatever the alignment of the base word turns out to be, and
// it is a read: this helper cannot write.
inline Word word_at(const void *base, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, static_cast<const unsigned char *>(base) + offset,
              sizeof(value));
  return value;
}

}  // namespace openspore::reconstruction::pkg_direct_property_copyfrom_wave14

#undef PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_CDECL
#undef PKG_DIRECT_PROPERTY_COPYFROM_WAVE14_THISCALL
