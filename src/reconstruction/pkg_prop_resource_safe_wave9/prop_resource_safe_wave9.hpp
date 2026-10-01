#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-prop-resource-safe-wave9 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_PROP_SAFE_CDECL __cdecl
#define PKG_PROP_SAFE_THISCALL __thiscall
#else
#define PKG_PROP_SAFE_CDECL __attribute__((cdecl))
#define PKG_PROP_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_safe_wave9 {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Displacement access into an opaque object.
//
// The machine proves a displacement -- "a four-byte word sits at receiver+0x28"
// -- and it never proves a member -- "a field called X lives there". The two
// receiver records in this package both carry ``bounds_only``, which is their own
// statement that they record where the body was *seen* reaching and not an
// enumeration of the receiver, and no record in either evidence pack carries a
// member name. So the receivers below have no layout, no member names and no
// semantic labels, and every access is an address computed from the receiver
// with the displacement written down next to the instruction that shows it.
//
// The imported SDK labels (``cPropManager::SetDevMode``, ``PFRecordWrite::Flush``)
// are candidate names, not evidence -- both records say so in their own
// ``audit_evidence_boundary`` -- so nothing in the code below is named after one.
// ---------------------------------------------------------------------------

// The address of the slot a displacement selects. It yields an address and not
// a value, because the width of an access is a fact of the instruction that
// makes it and no type here states one. The result is a plain `void *` so the
// same helper serves a body reading a slot and a model test filling one.
inline void* slot_at(void* base, std::ptrdiff_t displacement) {
  return static_cast<unsigned char*>(base) + displacement;
}

// A four-byte word read through an address. Every load the bodies below make is
// a whole-word load (``CMP dword ptr``, ``MOV dword ptr``), so this is a word
// and not a byte and not a half.
inline Word load_word(const void* address) {
  Word value = 0;
  std::memcpy(&value, address, sizeof(value));
  return value;
}

// The word a body copies out of one of its object locations is itself the
// address of a slot table: ``MOV EAX,[ESI + 0x28]`` followed by
// ``MOV EDX,[EAX + 0x10]`` is two levels, and the model keeps two levels. The
// first read yields a pointer; the second reads through it. What the table *is*
// is not established by this pack and is not claimed.
inline void* load_slot_table(const void* object_address) {
  void* table = nullptr;
  std::memcpy(&table, object_address, sizeof(table));
  return table;
}

// ---------------------------------------------------------------------------
// 0x006a3300 -- three instructions, one access.
//
//   006a3300  MOV AL,byte ptr [ESP + 0x4]
//   006a3304  MOV byte ptr [ECX + 0x15],AL
//   006a3307  RET 0x4
//
// One access, one byte wide, at displacement 0x15 of the ECX receiver; the
// machine-derived receiver record enumerates 0x15 alone. The value stored is the
// byte the caller wrote in the argument slot -- ``MOV AL`` reads the low byte
// only, and ``RET 0x4`` pops the whole four-byte slot the caller pushed, so the
// three bytes above it are ignored by the body and are not modelled.
//
// The receiver is sized only as far as the body was seen reaching, which is not
// a statement about the receiver's size.
// ---------------------------------------------------------------------------
constexpr std::ptrdiff_t kPropManagerSlotDisplacement = 0x15;
constexpr std::size_t kPropManagerObservedExtent =
    static_cast<std::size_t>(kPropManagerSlotDisplacement) + 1;

struct OpaquePropManagerReceiver {
  std::uint8_t bytes[kPropManagerObservedExtent]{};
};

// ---------------------------------------------------------------------------
// 0x006c0550 -- receiver-relative displacements, each with the instruction that
// shows it. ESI holds the ECX receiver from 006c0551 onward, so every ``[ESI +
// d]`` below is a displacement of the receiver and not of any other object.
//
//   006c0555  CMP dword ptr [ESI + -0x4],0x0   a whole word, compared to zero
//   006c055b  MOV EAX,dword ptr [ESI + 0x28]   the first object, read as a value
//   006c0562  LEA EDI,[ESI + 0x28]            the same location, formed as this
//   006c0585  MOV EDX,dword ptr [ESI + 0x4]    the second object, as a value
//   006c058b  LEA ECX,[ESI + 0x4]              the same location, formed as this
//
// The machine-derived receiver record enumerates exactly {-4, 4, 0x28}. It names
// no member at any of them, so each displacement is named for what the body does
// with it -- one is the word the gate tests, two are the locations the body both
// reads and dispatches through -- and none is named for what a member there
// might be called.
// ---------------------------------------------------------------------------
constexpr std::ptrdiff_t kRecordGateDisplacement = -0x04;
constexpr std::ptrdiff_t kRecordFirstObjectDisplacement = 0x28;
constexpr std::ptrdiff_t kRecordSecondObjectDisplacement = 0x04;

// How far the body was seen reaching past the receiver base: the first object
// location plus the four bytes it reads there. An observation, not a size.
constexpr std::size_t kReceiverObservedExtent =
    static_cast<std::size_t>(kRecordFirstObjectDisplacement) + sizeof(Word);

// Slot displacements inside the object each of those words points at. These are
// offsets of a *second* object, so they are declared apart from the receiver's
// own displacements and are passed to the accessors as named values rather than
// written as literals at the call site: a literal there would be counted as a
// receiver-relative declaration, and it is not one.
//
//   006c055e  MOV EDX,dword ptr [EAX + 0x10]  the first object's +0x10 word
//   006c0577  MOV EAX,dword ptr [EAX + 0x38]  the first object's +0x38 word
//   006c0588  MOV EDX,dword ptr [EDX + 0x38]  the second object's +0x38 word
//
// +0x10 is loaded once and dispatched once (006c0567). +0x38 is loaded twice,
// and the second load follows ``006c0571  MOV EAX,dword ptr [EDI]``, which
// re-reads the table word *after* the +0x10 port has run -- so a port that
// replaced the table word is observed and the earlier load is not reused.
constexpr std::ptrdiff_t kAccessPortSlot = 0x10;
constexpr std::ptrdiff_t kWritePortSlot = 0x38;

// The extent of the table the body can be shown to read: the highest slot it
// touches, plus the four bytes of that word.
constexpr std::size_t kObservedTableExtent =
    static_cast<std::size_t>(kWritePortSlot) + sizeof(Word);

// The ports, typed by the argument shape the listing shows and by nothing else.
// Neither port's body is in this pack, so neither is described: a thiscall
// return in EAX is the only thing either typing claims.
using AccessPort = Word(PKG_PROP_SAFE_THISCALL*)(void*);
using WritePort = std::int32_t(PKG_PROP_SAFE_THISCALL*)(void*, Word, Word);

inline AccessPort load_access_port(const void* slot_address) {
  AccessPort port = nullptr;
  std::memcpy(&port, slot_address, sizeof(port));
  return port;
}

inline WritePort load_write_port(const void* slot_address) {
  WritePort port = nullptr;
  std::memcpy(&port, slot_address, sizeof(port));
  return port;
}

// 006c0553  XOR AL,AL  writes the zero the gate branch returns; the three bytes
// above it in EAX are not touched and are not modelled. The other two paths
// leave a write port's full 32-bit EAX in place (006c057e  CALL EAX, and
// 006c0590  JMP EDX, whose callee is entered with the caller's own frame). So
// what comes back through ``RET 0x8`` is one byte of a 32-bit result. The
// canonical record says the same thing about this body -- "observed as the low
// byte of a 32-bit write result" -- and the model returns that byte and drops
// the rest rather than widening its type over bytes the body never determines.
inline std::uint8_t low_byte(Word value) {
  return static_cast<std::uint8_t>(value & 0xffu);
}

void PKG_PROP_SAFE_THISCALL prop_manager_set_dev_mode_006a3300(
    OpaquePropManagerReceiver* manager, std::uint8_t value);

// 006c0550. The two stack arguments are named for the slots they arrive in and
// typed by their width, which is all the body shows: it copies both words and
// pushes them, and it never dereferences either one. The canonical record names
// them ``const void * data`` and ``uint32_t size`` -- imported candidate names,
// and the audit boundary in that record says so -- so the model does not restate
// them as a pointer and a count. Which of the two arrives first at each port is
// a property of the two call sites and is stated there.
std::uint8_t PKG_PROP_SAFE_THISCALL record_write_flush_006c0550(
    void* receiver, Word argument_at_esp4, Word argument_at_esp8);

}

#undef PKG_PROP_SAFE_CDECL
#undef PKG_PROP_SAFE_THISCALL
