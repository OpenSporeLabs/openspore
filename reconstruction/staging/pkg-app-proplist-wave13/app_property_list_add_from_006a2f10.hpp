#pragma once

// PKG-APP-PROLIST-WAVE13 -- opaque layout and machine-observed call surface for
// VA 0x006a2f10, App::PropertyList::AddPropertiesFrom
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Every displacement in this header is read off the 30-instruction listing of
// 0x006a2f10..0x006a2f51 and nothing else. No member is named after a field:
// the binary carries no MSVC RTTI and no SDK structure for this class is
// published in this repository, so each word is identified by its machine
// displacement alone and no claim is made about which field it is.
//
// The machine-derived receiver record for this target enumerates exactly one
// receiver displacement, 0x34 (INC dword ptr [EBP+0x34] at 0x006a2f4b, reached
// through the EBP alias of ECX). The 0x18/0x1c/0x04/0x18 displacements below are
// read through the single stack argument, not through the receiver, so they are
// not receiver displacements and are kept here rather than attributed to it.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-APP-PROLIST-WAVE13 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "PKG-APP-PROLIST-WAVE13 requires 32-bit pointers");

// The 4-byte word at the head of an element.
//
// Evidence: the first stack dword of the loop call is the element address
// (0x006a2f34, PUSH ESI) and the second is that address plus 0x4
// (0x006a2f30/0x006a2f33, LEA EAX,[ESI+0x4] / PUSH EAX), so the two words handed
// to 0x006a2d30 delimit a one-word range; the loop stride is 0x18
// (0x006a2f43, ADD ESI,0x18).
struct alignas(4) OpaquePropertyWord {
  std::uint32_t value;
};

// One element of the range walked at 0x006a2f1c..0x006a2f48. The stride is
// 0x18 bytes (0x006a2f43); the body never reads further into an element than
// its first 4-byte word, so nothing else in these 0x18 bytes is established.
struct alignas(4) OpaquePropertyElement {
  std::uint8_t opaque_000[0x18];
};

// The address receiver+0x18 (0x006a2f28, LEA EBX,[EBP+0x18]) is passed in ECX
// to 0x006a2d30 for the whole loop. Its extent is not established by this body:
// only the two pointer words at +0x00 and +0x04 are known to be the range, and
// they are read by the callee, not here.
struct alignas(4) OpaquePropertyStorage {
  std::uint8_t opaque_000[0x1c];
};

// The receiver and the single stack argument, by machine displacement.
struct alignas(4) OpaquePropertyList {
  std::uint8_t opaque_000[0x18];
  // 0x006a2f1c  MOV ESI,dword ptr [EAX + 0x18]   (EAX = the stack argument)
  OpaquePropertyElement *range_begin_018;
  // 0x006a2f20  MOV EDI,dword ptr [EAX + 0x1c]
  OpaquePropertyElement *range_end_01c;
  std::uint8_t opaque_020[0x14];
  // 0x006a2f4b  INC dword ptr [EBP + 0x34]   (EBP = the ECX receiver)
  std::uint32_t completed_copies_034;
};

static_assert(offsetof(OpaquePropertyList, range_begin_018) == 0x18,
              "range_begin_018 must sit at displacement 0x18");
static_assert(offsetof(OpaquePropertyList, range_end_01c) == 0x1c,
              "range_end_01c must sit at displacement 0x1c");
static_assert(offsetof(OpaquePropertyList, completed_copies_034) == 0x34,
              "completed_copies_034 must sit at displacement 0x34");
static_assert(sizeof(OpaquePropertyList) == 0x38,
              "OpaquePropertyList must end after displacement 0x34");
static_assert(sizeof(OpaquePropertyElement) == 0x18,
              "the loop stride at 0x006a2f43 is 0x18 bytes");
static_assert(sizeof(OpaquePropertyWord) == 4,
              "the range handed to 0x006a2d30 is one 4-byte word wide");

// --- accessors, one per machine displacement ------------------------------ //
// Each returns exactly what the corresponding instruction reads, so the
// reconstructed body below can be read against the listing line by line.

inline OpaquePropertyElement *
property_list_range_begin(const OpaquePropertyList *list) {
  return list->range_begin_018;
}

inline OpaquePropertyElement *
property_list_range_end(const OpaquePropertyList *list) {
  return list->range_end_01c;
}

// 0x006a2f28: LEA EBX,[EBP + 0x18]. The result is the address of the range
// word, not a pointer to it, and it is what the loop keeps in a register.
inline OpaquePropertyStorage *property_list_storage(OpaquePropertyList *list) {
  return reinterpret_cast<OpaquePropertyStorage *>(
      reinterpret_cast<unsigned char *>(list) + 0x18u);
}

// 0x006a2f43: ADD ESI,0x18.
inline OpaquePropertyElement *
property_element_next(OpaquePropertyElement *element) {
  return reinterpret_cast<OpaquePropertyElement *>(
      reinterpret_cast<unsigned char *>(element) + 0x18u);
}

// 0x006a2f30: LEA EAX,[ESI + 0x4] -- the second stack dword of the loop call.
inline OpaquePropertyWord *
property_element_word_after_first(OpaquePropertyElement *element) {
  return reinterpret_cast<OpaquePropertyWord *>(
      reinterpret_cast<unsigned char *>(element) + 0x4u);
}

// --- machine-observed callees, semantics unresolved ----------------------- //
//
// Both are declared, not defined: this package reconstructs 0x006a2f10 only, and
// neither callee's behaviour is established by anything in the evidence pack.
// Their observable calling surfaces are, and they are what the declarations
// below encode.
//
//   0x006a2d30 -- 78 instructions; installs an SEH frame (PUSH -1 /
//     MOV EAX,FS:[0x0] / PUSH 0x120d6e0 at 0x006a2d30..0x006a2d3e); terminates
//     RET 0x4 at 0x006a2e1a, so it consumes exactly one stack dword. ECX is the
//     receiver's storage word (0x006a2f35, MOV ECX,EBX). Its EAX result is moved
//     straight into ECX at 0x006a2f3c and used there as a receiver, which is the
//     only evidence that the returned word is pointer-shaped; the pointed-to type
//     is inferred from that use and is not established.
//
//   0x00542b80 -- 58 instructions; terminates RET 0x4 at 0x00542c24, so it also
//     consumes exactly one stack dword. ECX is the previous result
//     (0x006a2f3c); the stack dword it consumes is the element address pushed at
//     0x006a2f34 and left there by 0x006a2d30's own RET 0x4. Its return value is
//     not consumed by this body.
//
// The two RET 0x4 terminations are why the loop's two pushed words are modelled
// as one dword per call rather than as a single two-dword argument list.

extern "C" {

// The target itself, machine ABI only: receiver in ECX, one ordinary stack
// dword at entry_ESP+0x4 (`other`), callee-cleaned by RET 0x4 at 0x006a2f51.
// Defined in app_property_list_add_from_006a2f10.cpp.
//
// No result is declared and none is claimed. The body never forwards a value to
// the caller: on the loop path EAX holds 0x00542b80's result and on the
// self-copy early-exit path it holds the incoming stack word, so there is no
// single value the body produces for the caller. The machine return classifier
// reads the two paths as a contested definition of EAX and declines to bound it
// (UNCLASSIFIED), which is recorded as an open dimension in the validation
// report rather than papered over with a source-side return type.
void __thiscall app_property_list_add_properties_from_006a2f10(
    OpaquePropertyList *receiver, OpaquePropertyList *other);

OpaquePropertyElement *__thiscall unresolved_006a2d30(
    OpaquePropertyStorage *storage, OpaquePropertyWord *word_after_first);

void __thiscall unresolved_00542b80(OpaquePropertyElement *element,
                                    OpaquePropertyElement *source);

} // extern "C"
