#pragma once

#include <cstddef>
#include <cstdint>

// Observed body of 0x00580cb0, 307 bytes, 91 instructions, read from
// SporeApp.exe 3.1.0.22 at sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e.
//
//   b8 24 10 00 00           MOV EAX,0x1024              ; 0x00580cb0
//   e8 46 fa c5 00           CALL 0x011e0700             ; 0x00580cb5
//   56                       PUSH ESI                    ; 0x00580cba
//   57                       PUSH EDI                    ; 0x00580cbb
//   8d 44 24 18              LEA EAX,[ESP + 0x18]        ; 0x00580cbc
//   50                       PUSH EAX                    ; 0x00580cc0
//   8b f9                    MOV EDI,ECX                 ; 0x00580cc1
//   e8 48 ff ff ff           CALL 0x00580c10             ; 0x00580cc3
//   ...                                                          (see the .cpp)
//   8d 84 24 24 04 00 00     LEA EAX,[ESP + 0x418]       ; 0x00580db9
//   50                       PUSH EAX                    ; 0x00580dc0
//   8d 8c 24 1c 02 00 00     LEA ECX,[ESP + 0x21c]       ; 0x00580dc1
//   51                       PUSH ECX                    ; 0x00580dc8
//   e8 22 84 10 00           CALL 0x006891f0             ; 0x00580dc9
//   8b 16                    MOV EDX,[ESI]               ; 0x00580dce
//   8b 42 04                 MOV EAX,[EDX + 0x4]         ; 0x00580dd0
//   83 c4 08                 ADD ESP,0x8                 ; 0x00580dd3
//   8b ce                    MOV ECX,ESI                 ; 0x00580dd6
//   ff d0                    CALL EAX                    ; 0x00580dd8
//   5f                       POP EDI                     ; 0x00580dda
//   5e                       POP ESI                     ; 0x00580ddb
//   81 c4 24 10 00 00        ADD ESP,0x1024              ; 0x00580ddc
//   c3                       RET                         ; 0x00580de2, bare
//
// Convention. The frame releases zero stack bytes at its own return (bare RET
// at 0x00580de2), and the only register consumed besides the return register is
// ECX, which is copied to EDI at 0x00580cc1 and thereafter used exactly once,
// as the first stack argument of 0x00692f90 at 0x00580d7c. The body reads no
// entry stack slot: every [ESP + k] operand in the 91 instructions resolves
// below the entry stack pointer, into the block 0x011e0700 carved out. So the
// convention is receiver-in-ECX __thiscall with zero ordinary arguments.
//
//   - cdecl is excluded because the receiver would then arrive on the stack and
//     no stack slot above the entry pointer is read.
//   - stdcall is excluded by the receiver register, and by the bare RET: a
//     stdcall frame with arguments would end in RET n.
//   - fastcall is excluded because EDX is never read and never forwarded. That
//     also refutes the __fastcall the Ghidra decompilation attributes to this
//     body.
//
// The receiver is never dereferenced. "MOV EDI,ECX" is the only instruction
// that consumes the incoming ECX, and the single PUSH of EDI at 0x00580d7c is
// the only place its value is used. No word of the receiver is read or written
// anywhere in the span, so nothing about the receiver's size, layout or class
// is asserted below beyond the single opaque word the type needs to exist.
#if defined(_MSC_VER)
#define PKG_DF5_THISCALL __thiscall
#define PKG_DF5_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_DF5_THISCALL __attribute__((thiscall))
#define PKG_DF5_CDECL __attribute__((cdecl))
#else
#error "PKG-DOGFOOD-00580CB0-A1 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_dogfood_00580cb0_a1 {

using OpaqueWord = std::uint32_t;
using OpaqueByte = std::uint8_t;
using OpaqueChar = char16_t;

static_assert(sizeof(void *) == 4, "this package reconstructs x86-32 code");
static_assert(sizeof(OpaqueWord) == 4, "every observed word is 32-bit");
static_assert(sizeof(OpaqueChar) == 2,
              "the two format strings at 0x013f5c68 and 0x013f5c74 are UTF-16");

// The receiver of 0x00580cb0.
//
// The body never dereferences it, so the single word below is a placeholder
// that gives the type a size, NOT a claim that the real object is four bytes.
// Nothing in the 91 instructions bounds the receiver: it is reached only
// through the vtable word at 0x013f57f8, whose class this binary does not name.
struct alignas(4) OpaqueEditorCommitOwner {
  OpaqueWord word_000;
};

// ---------------------------------------------------------------------------
// The block 0x011e0700 carves out, and the geometry inside it.
//
// 0x011e0700 is the MSVC stack probe. Its own 19 instructions were read to fix
// what it does: PUSH ECX / LEA ECX,[ESP+0x4] / SUB ECX,EAX / SBB EAX,EAX / NOT
// EAX / AND ECX,EAX / MOV EAX,ESP / AND EAX,0xfffff000 / CMP ECX,EAX / JC probe
// / MOV EAX,ECX / POP ECX / XCHG EAX,ESP / MOV EAX,[EAX] / MOV [ESP],EAX / RET.
// It copies the caller's return address down to the bottom of the block it is
// reserving and returns to that copy, so the block's top is the original
// return-address slot and its bottom is the word the probe wrote the return
// address into. That bottom word is immediately reused as a local, which is
// what the store of 1 at 0x00580d56 lands on.
//
// Every offset below is the displacement of an observed LEA or [ESP + k]
// operand in the 91 instructions, measured from that bottom word. Three
// independent corroborations fix the base rather than leaving it to assumption:
//
//   1. The three path buffers are computed by six LEA/MOV pairs and come out
//      exactly 0x200 bytes apart (0x010, 0x210, 0x410), each written with the
//      element count 0x100.
//   2. The twelve byte object the constructor 0x00693d60 builds has to start
//      0x004 above the bottom word for its own field at +0x08 to land on the
//      word 0x00580d44 and 0x00580d89 read: 0x00693d60 stores a vtable at +0x00
//      and zeroes +0x04 and +0x08, and 0x00692ea0 dereferences [ECX + 0x8] as a
//      pointer, so +0x08 is the third word of that object.
//   3. Ghidra's independent local analysis of the same body names the same
//      addresses: local_1014, local_e14, local_c14, piStack_1018 and
//      auStack_1024 for the five locations that are named at all.
//
// The frame reconciles exactly, with nothing left over. Read as a whole, the
// prologue spends 0x1024 on the probe at 0x00580cb5 and eight bytes on the two
// pushes at 0x00580cba/0x00580cbb, and the epilogue returns exactly that:
// POP EDI, POP ESI and ADD ESP,0x1024. Every push in between is matched too.
// The body issues 26 pushes; the three ADD ESP instructions at 0x00580d0f,
// 0x00580d6f and 0x00580dd3 reclaim 10, 4 and 2 words, the two POPs reclaim the
// two saved registers, and the remaining eight words are popped by their own
// callees (four by 0x00693d60, three by 0x00692f90, one by 0x00692900, which is
// why those three calls are followed by no ADD ESP). The stack pointer is
// therefore back at the entry value when RET executes, and the return FORM is a
// bare RET releasing zero bytes.
//
// An earlier reading of this body recorded a four byte discrepancy here, on the
// ground that the epilogue releases "two pops plus 0x1024" against a probe that
// only accounts for 0x1024. That compared the epilogue's two pops against the
// probe alone and left the prologue's own two pushes at 0x00580cba/0x00580cbb
// uncounted. With them counted the arithmetic closes, and the same base is the
// one all six of the other frame displacements agree on.
// ---------------------------------------------------------------------------

// The element count pushed for both format calls, at 0x00580cd9 and 0x00580cf5,
// and the count 0x00580c10 pushes for the base buffer at 0x00580cc2c. It is the
// element count, not a byte count: the two format strings are UTF-16, so a
// count of 0x100 units is 0x200 bytes, which is exactly the spacing the six
// LEA/MOV pairs measure between the three buffers. 0x00580c10's own body pushes
// 0x100 next to the same base buffer and writes the wide string
// L"EditorOfflineUser" through an import at 0x013cc4f0 on one of its two paths.
inline constexpr std::size_t kPathUnits = 256;
static_assert(kPathUnits * sizeof(OpaqueChar) == 0x200,
              "the three path buffers are exactly 0x200 bytes apart");

// The object 0x00688fa0 returns, as observed from this body plus that callee's
// own reconstruction record (wave13-w1-dispatch-b02 names it
// gge_user_data_reset_00688fa0 and fixes the width at 0x24 bytes).
//
// Two different vtable words live in it. The body reads [ESI] and dispatches
// slots +0x00 and +0x04 through it (0x00580d1a/0x00580d1c and 0x00580dce/
// 0x00580dd0), and it reads [ESI + 0x4] and dispatches slots +0x1c and +0x08
// through THAT word (0x00580da3/0x00580da6 and 0x00580db0/0x00580db2). So the
// second word is a separate polymorphic sub-object with its own table, not a
// second entry of the first table.
//
// The slots this body dispatches through are declared with their function types
// rather than as void*, so no function pointer is converted and the call the
// model emits is type-checked. The slots it does not dispatch through stay
// void*, because nothing here says what they are.
struct OpaqueHandle;
struct OpaqueHandlePeer;
struct OpaqueContextField08;
struct OpaqueSlot20Result;
struct OpaqueSlot18Result;

struct alignas(4) OpaqueHandleVTable {
  void(PKG_DF5_THISCALL *slot_00)(OpaqueHandle *) = nullptr;
  OpaqueWord(PKG_DF5_THISCALL *slot_04)(OpaqueHandle *) = nullptr;
};

struct alignas(4) OpaqueHandlePeerVTable {
  void *slots_00[2] = {};
  void(PKG_DF5_THISCALL *slot_08)(OpaqueHandlePeer *) = nullptr;
  void *slots_0c[3] = {};
  void *slots_18[1] = {};
  void(PKG_DF5_THISCALL *slot_1c)(OpaqueHandlePeer *) = nullptr;
};

// The peer sub-object. Its address IS handle + 0x4, and its own first word is
// the table the body dispatches through, so it is a separate polymorphic object
// and not a second entry of the handle's table.
struct alignas(4) OpaqueHandlePeer {
  OpaqueHandlePeerVTable *vtable_00 = nullptr;
};

struct alignas(4) OpaqueHandle {
  OpaqueHandleVTable *vtable_00 = nullptr;
  OpaqueHandlePeer *peer_04 = nullptr;
  OpaqueByte opaque_08[0x1c] = {};
};

static_assert(sizeof(OpaqueHandle) == 0x24,
              "0x00688fa0 returns a 0x24-byte object (wave13-w1-dispatch-b02)");
static_assert(offsetof(OpaqueHandle, vtable_00) == 0x00,
              "the table the body reads at [ESI]");
static_assert(offsetof(OpaqueHandle, peer_04) == 0x04,
              "the table the body reads at [ESI + 4]");
static_assert(
    offsetof(OpaqueHandlePeer, vtable_00) == 0x00,
    "ECX for both peer dispatches is handle + 0x4, whose first word is "
    "the table read at 0x00580da3 and 0x00580db0");
static_assert(offsetof(OpaqueHandleVTable, slot_04) == 0x04,
              "dispatch at 0x00580dd0, MOV EAX,[EDX + 0x4]");
static_assert(offsetof(OpaqueHandlePeerVTable, slot_08) == 0x08,
              "dispatch at 0x00580db2, MOV EDX,[EAX + 0x8]");
static_assert(offsetof(OpaqueHandlePeerVTable, slot_1c) == 0x1c,
              "dispatch at 0x00580da6, MOV EDX,[EAX + 0x1c]");

// The twelve byte object the stack builds at frame offset 0x004.
//
// 0x00693d60 is its constructor: it stores 0x01403970 at +0x00, zeroes +0x04
// and +0x08, then tail-calls the base constructor 0x00693aa0 with the four
// arguments this body pushed, and it ends with RET 0x10. 0x00693900 is its
// destructor: it stores 0x01403970 at +0x00 again, the vtable-reset idiom, then
// releases +0x08 and +0x04 through their own tables at slots +0x18, +0x14 and
// +0x04, and it ends with a bare RET. 0x00692ea0 is the predicate this body
// calls between the two: it loads [ECX + 0x8], and if that is non-null
// dispatches slot +0x18 on it and returns the truth of the result.
//
// Field +0x08 is therefore a polymorphic sub-object, and this body reads it
// back out at 0x00580d44 and 0x00580d89 to use as the argument of 0x00692900
// and to dispatch slot +0x20 on.
struct alignas(4) OpaqueContextField08VTable {
  void *slots_00[8] = {};
  OpaqueSlot20Result *(PKG_DF5_THISCALL *slot_20)(OpaqueContextField08 *) =
      nullptr;
};

struct alignas(4) OpaqueContextField08 {
  OpaqueContextField08VTable *vtable_00 = nullptr;
};

// The object 0x00692900's slot +0x20 returns, and the object that one's slot
// +0x18 returns. 0x00580d4a/0x00580d4d call slot +0x20 and
// 0x00580d4f/0x00580d53 immediately read [EAX] and dispatch slot +0x18 of THAT
// word, so the +0x20 result is itself a polymorphic object. Its +0x18 result is
// the first argument of 0x0093aa70, whose body dereferences it at [ESI] and
// dispatches its slots +0x10, +0x14 and +0x38.
struct alignas(4) OpaqueSlot20ResultVTable {
  void *slots_00[6] = {};
  OpaqueSlot18Result *(PKG_DF5_THISCALL *slot_18)(OpaqueSlot20Result *) =
      nullptr;
};

struct alignas(4) OpaqueSlot20Result {
  OpaqueSlot20ResultVTable *vtable_00 = nullptr;
};

struct alignas(4) OpaqueSlot18ResultVTable {
  void *slots_00[2] = {};
  void *slots_08[2] = {};
  void *slot_10 = nullptr;
  void *slot_14 = nullptr;
  void *slots_18[8] = {};
  void *slot_38 = nullptr;
};

struct alignas(4) OpaqueSlot18Result {
  OpaqueSlot18ResultVTable *vtable_00 = nullptr;
};

static_assert(offsetof(OpaqueContextField08VTable, slot_20) == 0x20,
              "dispatch at 0x00580d4a, MOV EDX,[EAX + 0x20]");
static_assert(offsetof(OpaqueSlot20ResultVTable, slot_18) == 0x18,
              "dispatch at 0x00580d53, MOV EAX,[EDX + 0x18]");
static_assert(offsetof(OpaqueSlot18ResultVTable, slot_10) == 0x10,
              "0x0093aa70 reads [EAX + 0x10] at 0x0093aa81");
static_assert(offsetof(OpaqueSlot18ResultVTable, slot_14) == 0x14,
              "0x0093aa70 reads [EAX + 0x14] at 0x0093aa8a");
static_assert(offsetof(OpaqueSlot18ResultVTable, slot_38) == 0x38,
              "0x0093aa70 reads [EAX + 0x38] at 0x0093aab2 and 0x0093aada");

// The twelve byte object itself, built on the stack at frame offset 0x004.
//
// Its three words carry NO default initialisers, and neither does anything else
// that lives only inside the frame. That is deliberate: the original does not
// initialise them either. 0x00693d60 writes +0x00, +0x04 and +0x08 itself, the
// store of 1 at 0x00580d56 writes the word below it, and the two format calls
// and 0x00580c10 write the buffers. A value-initialised frame would model a
// zero-filling prologue the 91 instructions do not contain.
struct alignas(4) OpaqueCommitContext {
  OpaqueWord vtable_00;
  OpaqueWord field_04;
  OpaqueContextField08 *field_08;
};

static_assert(sizeof(OpaqueCommitContext) == 0x0c,
              "0x00693d60 writes +0x00, +0x04 and +0x08 and nothing beyond");
static_assert(offsetof(OpaqueCommitContext, vtable_00) == 0x00,
              "0x00693d60 stores 0x01403970 at 0x00693d7b");
static_assert(offsetof(OpaqueCommitContext, field_04) == 0x04,
              "0x00693d60 zeroes it at 0x00693d85");
static_assert(offsetof(OpaqueCommitContext, field_08) == 0x08,
              "0x00692ea0 dereferences [ECX + 0x8] at 0x00692ea0");

// The object this body addresses at frame offset 0x610 and hands to 0x00692f90
// and 0x00692900 as their receiver.
//
// 0x00692900 is what bounds it. It reads the receiver at +0xa00 (an element
// count), +0xa04 (a cursor), +0xa08 and +0xa0c, and it walks an array of 0x14
// byte elements at +0x10 + index * 0x14 (LEA EDX,[EAX + EAX*0x4] then
// LEA EBX,[EDI + EDX*0x4] at 0x00692a46/0x00692a4d, and the same shape again at
// 0x00692b96/0x00692bf2). The widest offset it reads is +0xa0c, so 0xa10 bytes
// is the minimum width this target can rely on. Nothing in either body bounds
// the element count, so the array length is not described and nothing past
// +0xa0f is asserted.
struct alignas(4) OpaqueCommitSink {
  OpaqueByte opaque_000[0xa10];
};

static_assert(sizeof(OpaqueCommitSink) == 0xa10,
              "0x00692900 reads the receiver as far as +0xa0c");

// The observed contents of the reserved block, in the order the 91 instructions
// address them. Every offset here is a machine-proven displacement; the gaps
// are carried as opaque bytes because nothing in this body touches them.
struct alignas(4) OpaqueCommitFrame {
  // 0x00580d56 stores 1 here and 0x00580d64 takes its address. The word is also
  // where 0x011e0700 left its copy of the return address, so the original
  // reuses the probe's slot as its first local. Nothing writes it before that
  // store.
  OpaqueWord one;
  // 0x004: the twelve byte object, addressed at 0x00580d32 and 0x00580d3b,
  // whose field +0x08 is read at 0x00580d44 and 0x00580d89 and which 0x00693900
  // destroys at 0x00580d9a.
  OpaqueCommitContext context;
  // 0x010: the base name, written by 0x00580c10 at 0x00580cc3 and used as the
  // %s source of both format calls.
  OpaqueChar base_path[kPathUnits];
  // 0x210: the first format destination, written with L"%s.db.tmp" and then
  // passed to 0x00688fa0 and to 0x006891f0.
  OpaqueChar db_tmp_path[kPathUnits];
  // 0x410: the second format destination, written with L"%s.db" and passed to
  // 0x006891f0 as its second argument.
  OpaqueChar db_path[kPathUnits];
  // 0x610: the receiver of 0x00692f90 and 0x00692900, addressed at 0x00580d7d
  // and 0x00580d8e. It abuts db_path directly; there is no untouched band
  // between them, because the third buffer's own 0x200 of spacing ends exactly
  // where this object begins.
  OpaqueCommitSink sink;
};

static_assert(offsetof(OpaqueCommitFrame, one) == 0x000,
              "the word 0x00580d56 stores 1 into");
static_assert(offsetof(OpaqueCommitFrame, context) == 0x004,
              "the object 0x00693d60 constructs, 0x00693900 destroys");
static_assert(offsetof(OpaqueCommitFrame, base_path) == 0x010,
              "the buffer 0x00580c10 fills, LEA EAX,[ESP + 0x18]");
static_assert(offsetof(OpaqueCommitFrame, db_tmp_path) == 0x210,
              "the L\"%s.db.tmp\" destination, LEA EDX,[ESP + 0x224]");
static_assert(offsetof(OpaqueCommitFrame, db_path) == 0x410,
              "the L\"%s.db\" destination, LEA ECX,[ESP + 0x434]");
static_assert(
    offsetof(OpaqueCommitFrame, sink) == 0x610,
    "the receiver 0x00692f90 and 0x00692900 are given. At 0x00580d7d "
    "three pushes are outstanding after ADD ESP,0x10, so ESP is "
    "entry_ESP - 0x1038 and LEA ECX,[ESP + 0x624] is entry_ESP - "
    "0xa14, which is 0x610 above the block base entry_ESP - 0x1024. "
    "0x00580d8e agrees: one push outstanding, LEA ECX,[ESP + 0x61c] is "
    "entry_ESP - 0xa14 as well.");

// The sink's widest read is +0xa0c relative to itself, so the object ends at
// 0x610 + 0xa10 = 0x1020, inside the 0x1024 block with four bytes to spare, and
// its widest byte read is 0x610 + 0xa0c = 0x101c. A sink placed 0x400 higher,
// at 0xa10, would end at 0x1420, which is 0x3fc past the top of the block the
// probe reserved, so that placement is geometrically impossible.
static_assert(offsetof(OpaqueCommitFrame, sink) + 0xa0c <= 0x1024,
              "the sink's widest read stays inside the 0x1024 block");
static_assert(offsetof(OpaqueCommitFrame, sink) + sizeof(OpaqueCommitSink) <=
                  0x1024,
              "the sink ends inside the 0x1024 block the probe reserved");

// The 0x200 byte spacing of the three buffers is what fixes kPathUnits, and it
// is also what places the sink: one(0x4) + context(0xc) + three 0x200 buffers
// comes to exactly 0x610, which is the offset 0x00580d7d and 0x00580d8e address
// the sink at. The two formats write at most 0x100 units each, so the upper
// 0x200 of each buffer's 0x200 spacing is its own and the sink follows the
// third buffer without a gap.
static_assert(offsetof(OpaqueCommitFrame, db_tmp_path) -
                      offsetof(OpaqueCommitFrame, base_path) ==
                  0x200,
              "measured spacing of buffers one and two");
static_assert(offsetof(OpaqueCommitFrame, db_path) -
                      offsetof(OpaqueCommitFrame, db_tmp_path) ==
                  0x200,
              "measured spacing of buffers two and three");

// ---------------------------------------------------------------------------
// The two format strings.
//
// Both are read out of the image this attempt, not inferred from the call
// sites. At 0x013f5c68 the bytes are 25 00 73 00 2e 00 64 00 62 00 00 00, which
// is L"%s.db" and NUL: six units, twelve bytes. The next twelve bytes, at
// 0x013f5c74, are 25 00 73 00 2e 00 64 00 62 00 2e 00 74 00 6d 00 70 00 00 00,
// which is L"%s.db.tmp" and NUL: ten units, twenty bytes. The two are adjacent
// and their gap, 0x13f5c74 - 0x013f5c68, is 0x0c, exactly the size of the
// first, so the widths are corroborated by the layout as well as by the bytes.
//
// 0x00580ccd pushes 0x013f5c74 and 0x00580ce9 pushes 0x013f5c68, both as
// absolute addresses, so this body references these two globals and no other
// string.
// ---------------------------------------------------------------------------
// The declared bounds are the observed widths: ten UTF-16 units including
// the NUL for 0x013f5c74, six for 0x013f5c68.
extern const OpaqueChar kFmtDbTmp[10];  // 0x013f5c74, L"%s.db.tmp"
extern const OpaqueChar kFmtDb[6];      // 0x013f5c68, L"%s.db"

static_assert(sizeof(u"%s.db.tmp") == 0x14,
              "ten UTF-16 units including the NUL, twenty bytes");
static_assert(sizeof(u"%s.db") == 0x0c,
              "six UTF-16 units including the NUL, twelve bytes");

// The two data addresses the body pushes.
//
// 0x01897c18 is pushed three times, at 0x00580d22, 0x00580d27 and 0x00580d2c,
// as three of the four stack arguments of the constructor 0x00693d60. It is
// never dereferenced by this body. The twenty-four bytes read at that address
// this attempt are a dword table whose entries rise in a constant stride of
// eight: 0x36c036bc, 0x36c036c4, 0x36c036c8, 0x36c036cc, 0x36c036d0, 0x36c036d4
// and so on. That fixes the width of an entry and nothing else, so the anchor
// below carries no element type and no length.
//
// 0x0150d100 is pushed once, at 0x00580d77, as the second of the three stack
// arguments of 0x00692f90. It is never dereferenced by this body either. The
// twenty-four bytes read at that address are zero, so if the address is inside
// a zero-initialised region this body only ever takes its address; which region
// it lies in is not decided here.
//
// The immediate 0x1a80d26 pushed at 0x00580d72 is a plain constant, not an
// address, and is carried as a literal in the model.
//
// None of these three is modelled as an object here. The body only ever takes
// their addresses, so what the addresses hold constrains nothing in this
// translation unit, and a translation unit cannot link against the original
// image anyway. The model therefore reproduces each immediate literally at the
// call site that pushes it, which is where the machine encodes it.

// ---------------------------------------------------------------------------
// Ports.
//
// Every signature below was read from the callee's own body this attempt, and
// each entry cites the instruction that fixes it. None of these VAs is promoted
// here: each is separately owned, so this package declares a VA-suffixed name
// and ships no library stub, and the model test supplies recording stand-ins so
// the argument identities and the dispatch sequence are observable without a
// second reconstruction in the way.
// ---------------------------------------------------------------------------

// 0x00580c10: SUB ESP,0x10 / PUSH ESI / CALL 0x00607a60, and it reads its one
// argument at [ESP + 0x18] at 0x00580c28 and PUSHes 0x100 beside it at
// 0x00580c2c. cdecl, one stack word, no callee-side cleanup, bare RET at
// 0x00580c44 and 0x00580cac. It fills the buffer with a base name:
// L"EditorOfflineUser" read from 0x013f5c44 on one path, and a localised string
// built from the hash 0x1667bac on the other.
extern "C" void PKG_DF5_CDECL unresolved_00580c10(OpaqueChar *buffer);

// 0x00939a30: it forwards four arguments plus a va_list marker to 0x00939950
// and ends with ADD ESP,0x10 / RET, so cdecl with no callee-side cleanup. The
// argument order is fixed by its own loads, ECX from [ESP + 0xc] and EDX from
// [ESP + 0x8], and it builds the marker with LEA EAX,[ESP + 0x10] at
// 0x00939a38.
extern "C" OpaqueWord PKG_DF5_CDECL unresolved_00939a30(
    OpaqueChar *destination, std::size_t count, const OpaqueChar *format, ...);

// 0x00688fa0: cdecl, one stack word read at [ESP + 0x5c] at 0x00688fb8, and it
// ends with ADD ESP,0x58 / RET at 0x006891e2, so no callee-side cleanup. It
// returns EBX through MOV EAX,EBX at 0x006891d8, and EBX is the object
// 0x0069fa60 built or zero. Reconstructed separately as
// gge_user_data_reset_00688fa0 by wave13-w1-dispatch-b02, which is where the
// 0x24 byte width comes from.
extern "C" OpaqueHandle *PKG_DF5_CDECL
unresolved_00688fa0(const OpaqueChar *name);

// 0x00693d60: MOV ESI,ECX at 0x00693d77 makes ECX the receiver, it takes four
// stack words and ends with ADD ESP,0x10 / RET 0x10 at 0x00693dc0. It is the
// constructor of the twelve byte frame object.
//
// Its second, third and fourth arguments are typed as pointers because the body
// pushes the ADDRESS 0x01897c18 in all three slots: 0x00693d60 forwards them to
// the base constructor 0x00693aa0 unchanged, and this body never dereferences
// them. The declared type says the value is an address, which is what the
// pushed immediate is; it does not say what the words at that address mean.
extern "C" void PKG_DF5_THISCALL unresolved_00693d60(OpaqueCommitContext *self,
                                                     OpaqueHandle *handle,
                                                     const OpaqueWord *arg2,
                                                     const OpaqueWord *arg3,
                                                     const OpaqueWord *arg4);

// 0x00692ea0: twelve instructions, no frame, MOV ECX,[ECX + 0x8] at 0x00692ea0
// and a bare RET at 0x00692eba and 0x00692eb7. __thiscall, no stack argument,
// dword result in EAX that this body discards.
extern "C" OpaqueWord PKG_DF5_THISCALL
unresolved_00692ea0(OpaqueCommitContext *self);

// 0x0093aa70: PUSH ESI / PUSH EDI and a bare RET at 0x0093aa99, 0x0093aabf,
// 0x0093aafa and 0x0093ab03, so cdecl with four stack words and no callee-side
// cleanup. Its fourth argument is read at [ESP + 0x18] into EDI at 0x0093aa76
// and compared against 1 at 0x0093aa7a, which is what selects between the two
// shapes of the call it makes; this body passes 0 there.
extern "C" OpaqueWord PKG_DF5_CDECL
unresolved_0093aa70(OpaqueSlot18Result *target, const OpaqueWord *source,
                    OpaqueWord count, OpaqueWord mode);

// 0x00692f90: it forwards three stack words to 0x00692880 and ends with
// MOV EAX,ECX / RET 0xc at 0x00692fa4, so __thiscall with three stack words and
// a receiver-shaped result in EAX that this body discards. Its second argument
// is the address 0x0150d100, again never dereferenced here.
extern "C" OpaqueCommitSink *PKG_DF5_THISCALL
unresolved_00692f90(OpaqueCommitSink *self, OpaqueEditorCommitOwner *owner,
                    const OpaqueWord *global, OpaqueWord tag);

// 0x00692900: MOV ESI,[ESP + 0x1c] at 0x00692906 reads the one stack word, and
// it ends with POP EDI / POP ESI / POP EBP / POP EBX / ADD ESP,0xc / RET 0x4 at
// 0x00692c2f/0x00692c3e, so __thiscall with one stack word popped by the callee
// and a dword result in EAX that this body discards.
extern "C" OpaqueWord PKG_DF5_THISCALL
unresolved_00692900(OpaqueCommitSink *self, OpaqueContextField08 *field_08);

// 0x00693900: MOV ESI,ECX at 0x00693917 and ADD ESP,0x10 / RET at 0x006939a9,
// so
// __thiscall with no stack argument and a bare return. It is the destructor of
// the twelve byte frame object.
extern "C" void PKG_DF5_THISCALL unresolved_00693900(OpaqueCommitContext *self);

// 0x006891f0: it reads its first argument at [ESP + 0x94] at 0x0068928b, which
// resolves to the word above the return address, and it ends with ADD ESP,0x6c
// / RET at 0x006894c7, so cdecl with two stack words and no callee-side
// cleanup. This body relies on the cdecl half of that: it cleans the two words
// itself with ADD ESP,0x8 at 0x00580dd3. Reconstructed separately as
// wave13_w1_dispatch_b03_006891f0, whose record already lists 0x00580dc9 as a
// call site.
extern "C" void PKG_DF5_CDECL
unresolved_006891f0(const OpaqueChar *source, const OpaqueChar *destination);

// The immediate the body pushes as the third stack argument of 0x00692f90, at
// 0x00580d72. It is a constant, not an address: it is absent from every symbol
// and data table in the neighbourhood and is carried as a literal.
inline constexpr OpaqueWord kCommitTag = 0x1a80d26u;

// ---------------------------------------------------------------------------
// The vtable this body lives in.
//
// 0x00580cb0 is a table entry, not a directly called function: its only
// incoming reference is the single xref at 0x013f584c, and 0x013f584c -
// 0x013f57f8 is 0x54, so the body occupies byte offset 0x54 of the table at
// 0x013f57f8. The Ghidra xref export agrees independently: it records twelve
// outgoing direct-call edges from 0x00580cb0 and no incoming direct-call edge
// at all.
//
// The table runs 28 consecutive dwords from +0x00 to +0x70, all of them
// addresses in the 0x0057xxxx to 0x00e5xxxx code range, and the four bytes at
// +0x74 spell the narrow ASCII string "Casual", so the pointer run ends at
// +0x70. Six of those entries, at +0x24, +0x28, +0x2c, +0x30, +0x34 and +0x38,
// are the six symbols PKG-EDITOR-INPUT-WAVE6 already reconstructed, and the
// entry at +0x1c is 0x00587a20, which pkg-editor-onexit-smoke01 reconstructed.
// One entry, +0x58 (0x00580df0), is not a defined function in the current
// analysis; that is a gap in the analysis and not evidence that the slot is
// invalid.
//
// The word immediately below the table, at 0x013f57f4, is 0x00000000. In an
// MSVC vftable that word is the RTTI complete-object-locator pointer, so it is
// zero here and this binary carries no RTTI for the class. No class name is
// therefore recoverable from the binary, and none is asserted.
inline constexpr std::ptrdiff_t kVtableSlotOffset = 0x54;

// ---------------------------------------------------------------------------
// Reconstruction of 0x00580cb0.
//
// The symbol carries the Ghidra function label "FUN_00580cb0" as a lowercase
// "fun" token beside the VA, so the record's Ghidra name and this candidate
// span bind to one another deterministically.
// ---------------------------------------------------------------------------
extern "C" OpaqueWord PKG_DF5_THISCALL
dogfood_editor_commit_fun_00580cb0(OpaqueEditorCommitOwner *self);

}  // namespace openspore::reconstruction::pkg_dogfood_00580cb0_a1

#undef PKG_DF5_THISCALL
#undef PKG_DF5_CDECL
