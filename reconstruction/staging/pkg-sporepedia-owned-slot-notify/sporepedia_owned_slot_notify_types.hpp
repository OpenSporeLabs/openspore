// PKG-SPOREPEDIA-OWNED-SLOT-NOTIFY -- VA 0x00ec3bc0
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Opaque boundary types for the reconstruction of FUN_00ec3bc0. No machine
// record for this target names a class, a member, a dispatch table or a slot
// target, so nothing here carries a member name: the receiver is an opaque
// word-addressed block and every access is stated as a machine displacement.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-sporepedia-owned-slot-notify requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_sporepedia_owned_slot_notify {

using Word = std::uint32_t;

// The machine ABI record classifies the word this body leaves in EAX as
// "unclassified_in_EAX" (register_class aggregate_unknown, return.type null,
// void_possible false). The name is the record's own; the spelling below is the
// width the record's own return register implies, and nothing more.
using unclassified_in_EAX = Word;

// The calling conventions below are spelled per toolchain. The x86-32 attribute
// is what this package's machine-derived ABI record actually asserts, and it is
// not the same token on both compilers: MSVC spells the convention as a keyword
// (__thiscall/__cdecl) while GCC and clang only accept the __attribute__ form and
// reject the keywords outright. The 0x00ec3bdd terminator is a bare RET with no
// immediate and no stack adjustment, so the caller owns the stack and the cdecl
// default for x86-32 is already the right reading; both spellings are kept
// explicit so the declaration says what it means on either toolchain.
#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_THISCALL __thiscall
#define PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_CDECL __cdecl
#else
#define PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_THISCALL __attribute__((thiscall))
#define PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_CDECL __attribute__((cdecl))
#endif

// The block the receiver's word at displacement 0x20 points at. The body only
// ever hands that word to 0x00eec760 as a first argument, and that callee's own
// live listing dereferences its first argument (0x00eec78c MOV EAX,[EDI] then
// 0x00eec78e MOV EDX,[EAX + 0x24]), so the word is a pointer to something.
// Nothing in any record for this target names what, so the pointee stays opaque
// and void is the only type claimed for it.
using OpaqueOwnedBlock = void;

// 0x00eec760 writes three consecutive words at its second argument: its listing
// stores 0xffffffff at 0x00eec784, then 0x7fffffff at 0x00eec786 and again at
// 0x00eec789, i.e. offsets 0, 4 and 8 of that address, under its own two
// non-null guards. The type is that observed shape and no more -- the three words
// are not named here, and the values are the callee's constants, not this body's.
using BoundsWords = Word[3];

// 0x00ec3bc3, the one direct callee this body reaches before it reads anything
// of its own. The receiver is passed in ECX and nothing is pushed, and the
// reconstructed candidate for that address
// (reconstruction/staging/pkg-sporepedia-slot-release/, symbol
// sporepedia_dispatch_owned_slot_FUN_00641e10) declares exactly that contract:
// a hidden receiver in ECX, no stack argument, a bare RET and a return word it
// does not classify. The spelling below is this package's local name for the
// same address.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_THISCALL
slot_release_00641e10(void *receiver);

// 0x00eec760, the second direct callee. It is called with two words pushed right
// to left and dropped by the ADD ESP,0x8 at 0x00ec3bd9, so it is caller-cleaned
// and takes exactly two arguments; the order below is the push order at
// 0x00ec3bd2 (second argument) and 0x00ec3bd3 (first argument). That shape is
// corroborated by the callee's own listing, which reads its two words at
// 0x00eec761 (MOV EDI,[ESP + 0x8]) and 0x00eec76e (MOV ESI,[ESP + 0x10]) after
// its own two pushes and then ends in a bare RET at 0x00eec811 with no stack
// adjustment. Its own record ("undefined FUN_00eec760(void)") names neither a
// convention nor a return type, so the caller-cleaned two-word shape is what the
// declaration states; the return type stays this body's own record name because
// this body's record, not the callee's, is what classifies the word.
extern "C" unclassified_in_EAX PKG_SPOREPEDIA_OWNED_SLOT_NOTIFY_CDECL
sporepedia_bounds_fill_00eec760(OpaqueOwnedBlock *object, BoundsWords *bounds);

}  // namespace openspore::reconstruction::pkg_sporepedia_owned_slot_notify
