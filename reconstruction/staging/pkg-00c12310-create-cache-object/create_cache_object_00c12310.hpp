// PKG-00C12310-CREATE-CACHE-OBJECT -- target VA 0x00c12310
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, displacements and the call boundary for FUN_00c12310.
//
// ===========================================================================
// WHERE EVERY NUMBER IN THIS FILE COMES FROM
// ===========================================================================
//
// The body is 87 instructions / 218 bytes, 0x00c12310..0x00c123e8, and the
// committed Ghidra listing (reconstruction/evidence/00c12310/evidence.json,
// category `disassembly`, state LIVE) holds all 87 with a parse record that
// consumed them in full (declared_count 87, degraded false, unparsed 0). The
// byte encodings quoted below were re-read from the same bridge for this
// package with `ghidra_disassemble_bytes 0x00c12310 length=218`; the listing
// the model test pins as `kTargetBytes` is that re-read, 87 entries, same
// addresses, same lengths.
//
// ---------------------------------------------------------------------------
// 1. THE ENTRY'S ABI, AND WHERE IT COMES FROM
// ---------------------------------------------------------------------------
//
// Four register saves and no frame pointer:
//
//   0x00c12310  53        PUSH EBX
//   0x00c12311  55        PUSH EBP
//   0x00c12312  56        PUSH ESI
//   0x00c12313  57        PUSH EDI
//   ...                     (ESP is entry_ESP-0x10 from here to the epilogue)
//   0x00c123e3  5f        POP EDI
//   0x00c123e4  5e        POP ESI
//   0x00c123e5  5d        POP EBP
//   0x00c123e6  5b        POP EBX
//   0x00c123e7  c2 0c 00  RET 0xc
//
// `RET 0xc` is the whole cleanup story: the callee takes three four-byte stack
// words and pops them itself, so cdecl and fastcall are excluded, and ECX is
// copied into ESI at 0x00c12314 (`8b f1  MOV ESI,ECX`) and used as a base
// register for every receiver access, so this is __thiscall. That is the
// derived ABI record's own claim (`calling_convention __thiscall`,
// `receiver_register ECX`, `stack_cleanup_bytes 12`,
// `stack_cleanup_owner callee`, `ret_form "RET 0xc"`, confidence INFERRED),
// and the listing is what makes it OBSERVED rather than inferred. Note
// `PUSH EBP` here is a plain register save -- there is no `MOV EBP,ESP`, so
// EBP is an ordinary callee-saved register in this body and the ABI record's
// `FRAME` observation is read the same way (`ebp_is_general_register false`
// only says no frame pointer is established).
//
// THREE ORDINARY STACK ARGUMENTS, one per four-byte slot, and the listing is
// the oracle for every one of them. With ESP == entry_ESP-0x10:
//
//   0x00c12324  8b 6c 24 14   MOV EBP,dword ptr [ESP + 0x14]   -> entry_ESP+0x4
//   0x00c12342  8b 7c 24 14   MOV EDI,dword ptr [ESP + 0x14]   -> entry_ESP+0x4
//   0x00c12328  8d 44 24 14   LEA EAX,[ESP + 0x14]              ->
//   entry_ESP+0x4 0x00c123c5  8b 4c 24 18   MOV ECX,dword ptr [ESP + 0x18]   ->
//   entry_ESP+0x8 0x00c1237d  80 7c 24 1c 00 CMP byte ptr [ESP + 0x1c],0x0   ->
//   entry_ESP+0xc
//
// 0x14, 0x18 and 0x1c are 0x10 apart in the frame and 4 apart from each other,
// so the three reads are three DISTINCT words, and 0x1c is a one-byte read
// where the other two are four-byte reads. Three words of stack argument is
// also what `RET 0xc` independently says. This package therefore models three
// arguments: a 32-bit word, a second 32-bit word, and a one-byte flag.
//
//   THIS IS WHERE THE PACK DISAGREES WITH ITSELF, and the listing is right.
//   The derived ABI record's `stack_arguments` enumerates TWO slots totalling
//   EIGHT bytes (`entry_ESP+0x4` size 4, `entry_ESP+0x8` size 1) while its own
//   `cleanup.bytes` says 12, and it records the reason in
//   `abstained_because`: "flow_not_modelled: the linear ESP walk ends at +32,
//   so the listing is not one path". Its slot keys come from that linear walk,
//   which mis-attributes the `CMP byte ptr [ESP + 0x1c]` at 0x00c1237d
//   (observation obs-0032) to entry_ESP+0x8 instead of entry_ESP+0xc. The
//   arithmetic above does not depend on the walk: four PUSHes is 0x10, full
//   stop. See unresolved_questions.
//
// ---------------------------------------------------------------------------
// 2. THE RECEIVER, AND WHY IT HAS NO NAMED MEMBERS
// ---------------------------------------------------------------------------
//
// The derived record is `receiver.register ECX`, `shape R-ALIAS`,
// `bounds_only true`, `offsets [0xb54, 0xe88]`, `max_offset 3720`,
// `written_through 1`, confidence INFERRED. `bounds_only` means the record
// states how far the body was SEEN reaching and nothing about which member is
// which, so no member name is asserted anywhere in this package: `OpaqueOwner`
// is a byte run and every access goes through a displacement accessor, so a
// wrong displacement in the .cpp lands on a byte the model test planted a
// decoy pattern in rather than looking plausible.
//
// The alias is the whole reason the record saw 0xb54 at all: 0x00c12318 is
// `39 be 54 0b 00 00  CMP dword ptr [ESI + 0xb54],EDI` -- displacement under
// ESI, not ECX -- and the ABI inference follows `MOV ESI,ECX` (shape R-ALIAS).
// The listing's own ECX-operand scan finds no receiver displacement beyond the
// bare `[ECX]`, so a source that wrote 0xb54 and a checker that scanned only
// ECX would disagree about a body both of them can see. `evidence_fields`'
// alias-aware scan is what reconciles them, and it reports exactly one aliased
// displacement for this body: 0xb54 through ESI.
//
//   0xb54  0x00c12318  CMP dword ptr [ESI + 0xb54],EDI   read, the null test
//         0x00c1235b  MOV ECX,dword ptr [ESI + 0xb54]   read, the dispatch base
//         0x00c1236b / 0x00c12371 / 0x00c12384 / 0x00c12398 /
//         0x00c123a6 / 0x00c123b5                       read, four more times
//   0xe88  0x00c123db  MOV dword ptr [ESI + 0xe88],EDI  WRITE, the only one
//
// 0xe88 is inside the record's bounds and outside the listing's ECX-operand
// scan for the same alias reason. Both are the only two displacements this
// body reaches through its receiver; 0x1c below is NOT a receiver displacement
// (it is under EBX, a value the manager returned) and this package says so.
//
// ---------------------------------------------------------------------------
// 3. THE TWO TABLES, AND WHY THE SLOT NAMES STOP AT DISPLACEMENTS
// ---------------------------------------------------------------------------
//
// Seven indirect transfers, and every one is a proven vtable-slot call: the
// slot word is loaded out of a table word that was itself read out of an object
// (`MOV EDX,[reg]` then `MOV EAX,[EDX+disp]` then `PUSH`s then `CALL EAX`).
// `evidence_dispatch.classify_sites` reads all seven as VTABLE_SLOT:
//
//   0x00c1234c  CALL EAX  slot +0x40  base EDX   the MANAGER's table
//   0x00c12369  CALL EAX  slot +0x08  base EDX   the PROTOTYPER's table
//   0x00c1237b  CALL EAX  slot +0x0c  base EDX
//   0x00c12396  CALL EAX  slot +0x14  base EDX
//   0x00c123a4  CALL EAX  slot +0x18  base EDX
//   0x00c123b3  CALL EAX  slot +0x40  base EDX
//   0x00c123c3  CALL EAX  slot +0x3c  base EDX
//
// That is six distinct displacements across TWO DIFFERENT tables, and the
// seventh site reuses +0x40 on the second one. The listing does not say what
// any of these methods IS, and no record in this repository names them, so the
// vtable structs below declare members whose names ARE their displacement
// (`slot_08`, `slot_0c`, ...). `evidence_dispatch` reads a member literally
// named `slot_XX` as a declared offset, which makes the source's six offsets
// and the machine's six offsets directly comparable, and there is no
// descriptive word in the package that the listing does not carry.
//
// `OpaqueManagerVTable` and `OpaquePrototyperVTable` are two distinct types
// even though both carry a `slot_40`: the two +0x40 sites are demonstrably
// different objects' tables (0x00c12340 reads `[EAX]` where EAX is what
// 0x0067cb20 returned; 0x00c123ae reads `[ECX]` where ECX is receiver+0xb54),
// and one type would collapse two proven dispatches into one.
//
// ---------------------------------------------------------------------------
// 4. THE FLOAT ARGUMENT, WHICH IS AN ABSENCE OF A NAME
// ---------------------------------------------------------------------------
//
// 0x00c1238a/0x00c12392 is the FLDZ/FSTP idiom for pushing a float immediate:
//
//   0x00c1238a  d9 ee     FLDZ                     push 0.0f on the x87 stack
//   0x00c12391  51        PUSH ECX                 reserve a stack word
//   0x00c12392  d9 1c 24  FSTP float ptr [ESP]     write 0.0f there, pop the
//   x87 0x00c12395  57        PUSH EDI 0x00c12396  ff d0     CALL EAX slot
//   +0x14
//
// The `PUSH ECX` word is overwritten by the `FSTP` and is not an argument. The
// argument the callee sees is the 4-byte float 0.0f, and `FSTP float ptr`
// says it is a `float` and not a `double`. The model test asserts the bits,
// because "the argument is zero" and "the argument is the bits 0x00000000" are
// different claims and only the second is what the machine writes.
//
// THIS IS ALSO WHY THE PACK'S `return_register: ST0` IS NOT A RETURN CLAIM.
// The FLDZ at 0x00c1238a is matched by the FSTP at 0x00c12392, so the x87
// stack is empty again before either RET, and the value every exit leaves is in
// EAX: 0x00c123e1 `8b c7  MOV EAX,EDI` on the success path, and 0 on the two
// early paths (0x00c1231e jumps to 0x00c123e1 with EDI still 0 from `XOR
// EDI,EDI`, and 0x00c12354 falls into the epilogue with EAX holding the null
// the +0x40 call returned). The record's own `return` sub-record agrees on
// nothing else and its `return.type` is null. See unresolved_questions.
//
// ---------------------------------------------------------------------------
// 5. THE THREE DIRECT CALLEES AND THEIR CLEANUP, FROM THIS BODY ALONE
// ---------------------------------------------------------------------------
//
// The cleanup is on the CALLER's side in all three cases, which is what the
// `ADD ESP` after each call says, independently of what the callee's own bytes
// do:
//
//   0x00c12333  e8 78 a2 ff ff  CALL 0x00c0c5b0
//   0x00c12338  83 c4 0c        ADD ESP,0xc      three words, caller cleans
//   0x00c1233b  e8 e0 a7 a6 ff  CALL 0x0067cb20
//                                (nothing pushed, nothing added)  zero words
//   0x00c123cd  e8 7e de ff ff  CALL 0x00c10250
//   0x00c123d2  83 c4 10        ADD ESP,0x10     four words, caller cleans
//
// The argument vectors are fixed by the pushes immediately before each call,
// read right to left (last push is the first argument):
//
//   0x00c0c5b0(this, arg1, &arg1)      0x00c1232c PUSH EAX (&arg1)
//                                     0x00c1232d PUSH EBP (arg1)
//                                     0x00c1232e PUSH ESI (this)
//   0x0067cb20()                      no pushes at all
//   0x00c10250(this, created, arg2, ctx)
//                                     0x00c123c9 PUSH EBX (ctx)
//                                     0x00c123ca PUSH ECX (arg2)
//                                     0x00c123cb PUSH EDI (created)
//                                     0x00c123cc PUSH ESI (this)
//
// 0x00c123c5 reads ECX from `[ESP+0x18]` = entry_ESP+0x8, i.e. the SECOND
// stack argument, and that is the word 0x00c123ca pushes. The committed
// decompilation renders that same read as `uVar5`, a local it had already
// bound to the constant 1 from `PUSH 0x1` at 0x00c12378 -- so its
// `FUN_00c10250(param_1,uVar4,uVar5,iVar3)` claims a literal where the listing
// says a stack read. The listing is authoritative and this package follows it.
// See unresolved_questions.
//
// 0x0067cb20 is corroborated from outside as a zero-argument cdecl accessor
// returning a pointer: reconstruction/staging/pkg-editor-runtime-wave7 declares
// it as `ManagerGet = void*(CDECL*)()` and calls it with no pushes, which is
// the same shape this body uses. That is a cross-package agreement about the
// CALLER side only and is not evidence about the callee's own bytes.
//
// ---------------------------------------------------------------------------
// 6. THE ONE-BYTE FLAG AT receiver+0x1c's SIBLING: NOT A RECEIVER FIELD
// ---------------------------------------------------------------------------
//
// 0x00c123d5 `80 7b 1c 01  CMP byte ptr [EBX + 0x1c],0x1` is under EBX, and
// EBX is what the MANAGER's +0x40 slot returned (0x00c1234e `MOV EBX,EAX`).
// So 0x1c belongs to a value this body did not receive, and it is NOT inside
// the receiver's displacement bounds {[0xb54, 0xe88]}. It is declared here as
// `kManagerResultFlagDisplacement` on the manager's result type, never as a
// receiver member, and the model test keeps it out of the receiver object
// entirely. `evidence_fields` reads a declared displacement that no witness
// corroborates as ungrounded, so attributing it to the receiver would cost a
// verdict for a claim the listing refutes.
//
// ---------------------------------------------------------------------------
// 7. WHAT IS NOT CLAIMED, ANYWHERE, BY THIS PACKAGE
// ---------------------------------------------------------------------------
//
//   * A class name. The triage record says subsystem "Simulator" and cluster
//     "unknown-fun-mass", and no MSVC RTTI survives in this binary, so
//     `OpaqueOwner` is this package's name for the receiver and nothing more.
//   * The size of the receiver. 0xe88 is the largest displacement and it is a
//     plain word store, so 0xe8 + 4 is a floor and not a measurement. The model
//     test keeps a canary past the end and asserts nothing outside the object
//     is ever written.
//   * What the prototyper at receiver+0xb54 IS. Six of its seven virtual slots
//     are called and nothing else about it is observable from this body.
//   * What any of the thirteen callees DOES. This package fixes the call
//     boundaries, the argument vectors, the order, the two exits and the one
//     store; the answers are the callees' business.
//   * Whether the manager returned by 0x0067cb20 is ever null. The body
//     dereferences it immediately (`MOV EDX,[EAX]` at 0x00c12340) with no
//     test, so this package does not invent one.
//   * The value 0x00c0c5b0 writes through `&arg1`. The body re-reads the slot
//     (0x00c12342) and uses the new value for the manager's +0x40 and the
//     prototyper's +0x08, and uses the ORIGINAL value (EBP, read at
//     0x00c12324 before the call) for the prototyper's +0x40 at 0x00c123b1.
//     That split is a fact about this body; what the callee writes is not.

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-00c12310 requires an x86-32 target"
#endif

// One convention macro per role, each spelled once here so the body names a
// token the validator can resolve (validate._convention_defines reads the
// package's own header for the quoted include).
#if defined(_MSC_VER)
#define PKG_00C12310_THISCALL __thiscall
#define PKG_00C12310_CDECL __cdecl
#else
#define PKG_00C12310_THISCALL __attribute__((thiscall))
#define PKG_00C12310_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_00c12310_create_cache_object {

using Word = std::uint32_t;

// The receiver's two displacements, stated before the receiver so the receiver
// can be sized from them.
//
// 0x00c12318 `CMP dword ptr [ESI + 0xb54],EDI` and six later reads.
constexpr std::size_t kReceiverPrototyperDisplacement = 0xb54;
// 0x00c123db `MOV dword ptr [ESI + 0xe88],EDI`, the body's only store through
// its receiver.
constexpr std::size_t kReceiverCachedObjectDisplacement = 0xe88;

// ---------------------------------------------------------------------------
// The receiver. Opaque on purpose (see note 2): the derived receiver record is
// `bounds_only`, so it fixes where the body reached and not which member is
// which, and a named member would be a claim no machine evidence here
// corroborates. Every access goes through a displacement accessor instead, so a
// wrong displacement lands on a byte the model test planted a decoy in rather
// than looking plausible.
// ---------------------------------------------------------------------------
struct alignas(4) OpaqueOwner {
  // Large enough for the body's largest displacement plus the four bytes its
  // store writes there: 0xe88 + 4. That is a FLOOR, not a measurement -- the
  // listing proves the body writes four bytes at 0xe88 and reaches nothing
  // beyond it, and says nothing about how large the real object is. The model
  // test keeps a canary past the end and asserts nothing outside is written.
  std::uint8_t opaque_00[kReceiverCachedObjectDisplacement + sizeof(Word)];
};

// The entry's three stack words, entry_ESP-relative. See note 1.
constexpr std::size_t kArgumentWord0 = 0x04;  // 0x00c12324, 0x00c12342
constexpr std::size_t kArgumentWord1 = 0x08;  // 0x00c123c5
constexpr std::size_t kArgumentByte2 = 0x0c;  // 0x00c1237d, a one-byte read
// Four saved registers, so [ESP+0x14] is entry_ESP+0x4. Stated so the .cpp's
// frame arithmetic and the listing's displacements cannot drift apart.
constexpr std::size_t kSavedRegisterBytes = 0x10;
constexpr std::size_t kStackCleanupBytes = 0x0c;  // RET 0xc at 0x00c123e7

// 0x00c123d5 `CMP byte ptr [EBX + 0x1c],0x1` -- under EBX, which is the
// MANAGER's +0x40 result, NOT the receiver. See note 6.
constexpr std::size_t kManagerResultFlagDisplacement = 0x1c;
constexpr Word kManagerResultFlagSuppress = 1u;  // the CMP immediate

// The 4-byte float 0x00c1238a/0x00c12392 writes into the argument word of the
// +0x14 call. `FLDZ` is a sign-and-exponent-and-mantissa clear, so the stored
// bits are exactly zero -- a POSITIVE zero, not a negative one, and the model
// test asserts the bits rather than the value so "0.0f" and "+0.0f" cannot be
// confused.
constexpr Word kZeroFloatBits = 0x00000000u;

// The four objects the body receives or produces are declared INCOMPLETE here
// and completed further down, once the two tables they point at exist.
struct OpaquePrototyper;     // the object at receiver+0xb54
struct OpaqueManager;        // what 0x0067cb20 returns
struct OpaqueManagerResult;  // what the manager's +0x40 slot returns (EBX)
struct OpaqueCreated;        // what the prototyper's +0x08 slot returns

// ---------------------------------------------------------------------------
// The two tables. Member names ARE their displacement (see note 3): nothing
// here asserts what a method does, only which word of which table the body
// calls and with what argument vector.
//
// The prototypes' observable part is the argument vector and the register the
// value comes back in, both read off the pushes and the following MOV:
//
//   manager  +0x40  (0x00c1234b PUSH EDI)                ->
//   OpaqueManagerResult* proto    +0x08  (0x00c12366 PUSH 0x0, 0x00c12368 PUSH
//   EDI)
//                                                          -> OpaqueCreated*
//   proto    +0x0c  (0x00c12378 PUSH 0x1, 0x00c1237a PUSH EDI)   -> void
//   proto    +0x14  (0x00c12392 FSTP [ESP], 0x00c12395 PUSH EDI) -> void
//   proto    +0x18  (0x00c123a3 PUSH EDI)                        -> void
//   proto    +0x40  (0x00c123b1 PUSH EBP, 0x00c123b2 PUSH EDI)    -> void
//   proto    +0x3c  (0x00c123c0 PUSH 0x0, 0x00c123c2 PUSH EDI)    -> void
//
// Which of the two +0x40 sites belongs to which table is decided by the
// listing, not by this comment: 0x00c12340 `MOV EDX,dword ptr [EAX]` follows
// the 0x0067cb20 call, and 0x00c123ac `MOV EDX,dword ptr [ECX]` follows
// `MOV ECX,dword ptr [ESI + 0xb54]`.
// ---------------------------------------------------------------------------
using ManagerSlot40 =
    OpaqueManagerResult*(PKG_00C12310_THISCALL*)(OpaqueManager*, Word);
using PrototyperSlot08 =
    OpaqueCreated*(PKG_00C12310_THISCALL*)(OpaquePrototyper*, Word, Word);
using PrototyperSlot0c = void(PKG_00C12310_THISCALL*)(OpaquePrototyper*,
                                                      OpaqueCreated*, Word);
using PrototyperSlot14 = void(PKG_00C12310_THISCALL*)(OpaquePrototyper*,
                                                      OpaqueCreated*, float);
using PrototyperSlot18 = void(PKG_00C12310_THISCALL*)(OpaquePrototyper*,
                                                      OpaqueCreated*);
using PrototyperSlot3c = void(PKG_00C12310_THISCALL*)(OpaquePrototyper*,
                                                      OpaqueCreated*, Word);
using PrototyperSlot40 = void(PKG_00C12310_THISCALL*)(OpaquePrototyper*,
                                                      OpaqueCreated*, Word);

struct alignas(4) OpaqueManagerVTable {
  // +0x00..+0x3c: seventeen words the body never reads. Sized so that
  // `slot_40` lands on the displacement 0x00c12348 reads.
  void* unread_00[16];
  ManagerSlot40 slot_40;
};

struct alignas(4) OpaquePrototyperVTable {
  // +0x00, +0x04: two words the body never reads.
  void* unread_00[2];
  // +0x08  0x00c12363
  PrototyperSlot08 slot_08;
  // +0x0c  0x00c12375
  PrototyperSlot0c slot_0c;
  // +0x10: one unread word.
  void* unread_10;
  // +0x14  0x00c1238e
  PrototyperSlot14 slot_14;
  // +0x18  0x00c123a0
  PrototyperSlot18 slot_18;
  // +0x1c..+0x38: eight unread words.
  void* unread_1c[8];
  // +0x3c  0x00c123bd
  PrototyperSlot3c slot_3c;
  // +0x40  0x00c123ae
  PrototyperSlot40 slot_40;
};

// ---------------------------------------------------------------------------
// The objects the body dispatches through. `OpaqueManager` and
// `OpaquePrototyper` are one pointer wide and that pointer IS the table: the
// body reads it with `MOV EDX,dword ptr [reg]` (0x00c12340, 0x00c12361,
// 0x00c12371, 0x00c1238c, 0x00c1239e, 0x00c123ac, 0x00c123bb) and calls
// through it.
//
// `OpaqueManagerResult` is a byte run because the body reads ONE BYTE of it, at
// +0x1c (0x00c123d5) -- that is its only access, and it is not a receiver
// displacement (see note 6). `OpaqueCreated` is never read through at all, so
// its run is only large enough for the model test to tell two of them apart.
// ---------------------------------------------------------------------------
struct alignas(4) OpaqueManager {
  const OpaqueManagerVTable* table;
};

struct alignas(4) OpaquePrototyper {
  const OpaquePrototyperVTable* table;
};

struct alignas(4) OpaqueManagerResult {
  std::uint8_t opaque[0x40];
};

struct alignas(4) OpaqueCreated {
  std::uint8_t opaque[0x40];
};

// The first word of every object the body dispatches through, read by
// `MOV EDX,dword ptr [reg]` (0x00c12340, 0x00c12361, 0x00c12371, 0x00c1238c,
// 0x00c1239e, 0x00c123ac, 0x00c123bb). `table_of` is that bare read: a pointer
// to the table, with NO `0x0` displacement, because `MOV EDX,dword ptr [EAX]`
// encodes as `8b 10` and carries no displacement byte at all -- see note 1 of
// docs/tooling/reconstruction-failure-modes.md, rule 1.
template <typename Table>
inline const Table* table_of(const void* object) {
  return static_cast<const Table*>(*reinterpret_cast<void* const*>(object));
}

// ---------------------------------------------------------------------------
// The entry. Exactly ONE symbol in this package carries the 8-hex target VA --
// this one -- because validate._target_span binds a target by finding that
// token in a symbol name and takes candidates[0] on a tie (docs/tooling/
// reconstruction-failure-modes.md, rule 7). Every helper below is named with
// either a slot displacement or a callee VA, never with 00c12310.
//
// The parameter list is the listing's own: the receiver in ECX (0x00c12314
// MOV ESI,ECX) and three four-byte stack words (entry_ESP+0x4, +0x8, +0xc),
// which the callee pops through `RET 0xc`.
// ---------------------------------------------------------------------------
extern "C" OpaqueCreated* PKG_00C12310_THISCALL create_cached_object_00c12310(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag);

// ---------------------------------------------------------------------------
// The three direct callees, declared with the cleanup THIS BODY performs after
// each one (see note 5). They are `extern "C"` and defined by the model test as
// recording observers, so every claim the body makes about a call is checked
// against what the listing fixes.
// ---------------------------------------------------------------------------
extern "C" void PKG_00C12310_CDECL resolve_prototype_00c0c5b0(
    OpaqueOwner* owner, Word argument, Word* argument_out);
extern "C" OpaqueManager* PKG_00C12310_CDECL manager_root_0067cb20();
extern "C" void PKG_00C12310_CDECL attach_created_object_00c10250(
    OpaqueOwner* owner, OpaqueCreated* created, Word argument1,
    OpaqueManagerResult* manager_result);

// ---------------------------------------------------------------------------
// Displacement accessors. Used INSTEAD of named members, per note 2. `word_at`
// is the four-byte access the listing shows and `byte_at` the one-byte access
// 0x00c1237d and 0x00c123d5 show; keeping them distinct is what stops a
// one-byte flag from being read as a word.
// ---------------------------------------------------------------------------
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                 displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

inline std::uint8_t* byte_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const std::uint8_t* byte_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// A pointer as the four-byte word the body moves it in. The listing never
// converts one spelling to the other, so the package does not either.
inline Word pointer_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The vtable slot offsets this body reaches, as the check reads them: the
// member names in the two table structs above are literally `slot_08`,
// `slot_0c`, `slot_14`, `slot_18`, `slot_3c` and `slot_40`, and
// evidence_dispatch._source_slot_offsets reads a member named `slot_XX` as a
// declared offset. The six values are pinned to the six `MOV EAX,[EDX+disp]`
// instructions in the body beside them, so the source's slot set and the
// machine's slot set are the same six numbers by construction.
static_assert(
    offsetof(OpaqueManagerVTable, slot_40) == 0x40,
    "manager slot_40 is the word 0x00c12348 reads as MOV EAX,[EDX+0x40]");
static_assert(
    offsetof(OpaquePrototyperVTable, slot_08) == 0x08,
    "prototyper slot_08 is the word 0x00c12363 reads as MOV EAX,[EDX+0x8]");
static_assert(
    offsetof(OpaquePrototyperVTable, slot_0c) == 0x0c,
    "prototyper slot_0c is the word 0x00c12375 reads as MOV EAX,[EDX+0xc]");
static_assert(
    offsetof(OpaquePrototyperVTable, slot_14) == 0x14,
    "prototyper slot_14 is the word 0x00c1238e reads as MOV EAX,[EDX+0x14]");
static_assert(
    offsetof(OpaquePrototyperVTable, slot_18) == 0x18,
    "prototyper slot_18 is the word 0x00c123a0 reads as MOV EAX,[EDX+0x18]");
static_assert(
    offsetof(OpaquePrototyperVTable, slot_3c) == 0x3c,
    "prototyper slot_3c is the word 0x00c123bd reads as MOV EAX,[EDX+0x3c]");
static_assert(
    offsetof(OpaquePrototyperVTable, slot_40) == 0x40,
    "prototyper slot_40 is the word 0x00c123ae reads as MOV EAX,[EDX+0x40]");

}  // namespace openspore::reconstruction::pkg_00c12310_create_cache_object
