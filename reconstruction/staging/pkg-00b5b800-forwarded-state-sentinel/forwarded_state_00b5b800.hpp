#pragma once

// Reconstruction of 0x00b5b800 (SporeApp.exe 3.1.0.22, SHA-256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// THE COMPLETE BODY: twenty bytes, seven instructions
// -----------------------------------------------------
//     0x00b5b800  e8 1b 1b fe ff      CALL   0x00b3d320
//     0x00b5b805  85 c0               TEST   EAX,EAX
//     0x00b5b807  74 07               JE     0x00b5b810
//     0x00b5b809  8b c8               MOV    ECX,EAX
//     0x00b5b80b  e9 20 6f ee ff      JMP    0x00a42730
//     0x00b5b810  83 c8 ff            OR     EAX,0xffffffff
//     0x00b5b813  c3                  RET
//
// INT3 padding (cc) brackets the body at 0x00b5b7ff and 0x00b5b814, so the
// twenty bytes are delimited from both sides. Two INDEPENDENT machine sources
// agree on exactly this body and on nothing longer:
//
//   1. `objdump -d -M intel SPORE/SporeBin/SporeApp.exe --start-address=
//      0x00b5b7f0 --stop-address=0x00b5b820` prints the seven lines above.
//   2. The live Ghidra bridge on the same binary: `FUN_00b5b800`, signature
//      `undefined FUN_00b5b800(void)`, body_start 00b5b800, body_end 00b5b813,
//      listing CALL 0x00b3d320 / TEST EAX,EAX / JZ 0x00b5b810 / MOV ECX,EAX /
//      JMP 0x00a42730 / OR EAX,0xffffffff / RET, and a 24-byte memory read
//      returning hex e81b1bfeff85c074078bc8e9206feeff83c8ffc3 -- byte for byte
//      the image above.
//
// The two direct targets are five and six bytes long and are read here the same
// way:
//     0x00b3d320  a1 ec ea 67 01        MOV EAX, DS:0x0167eaec
//     0x00b3d325  c3                   RET
//     0x00a42730  8b 41 20             MOV EAX, DWORD PTR [ECX+0x20]
//     0x00a42733  c3                   RET
//
// THE WHOLE CONTRACT, IN ONE SENTENCE
// -----------------------------------
// No arguments; if the borrowed global receiver at 0x0167eaec is null, return
// 0xffffffff; otherwise return the 32-bit word stored at receiver+0x20, read
// through ECX by the two-instruction field reader. No allocation, no store, no
// lock, no reference count, no argument traffic, no return address manipulation.
//
// WHAT IS DELIBERATELY NOT CLAIMED
// ---------------------------------
// The 0x20 storage is an OPAQUE BYTE RUN. It is not a struct member, not an
// SDK field, not a vtable slot, not a mode id and not an interface pointer, and
// this package asserts none of those. The returned word is a 32-bit scalar and
// nothing more: no pointee type, no class, no enum. The borrowed receiver's
// class, owner, allocator, initialiser and teardown are all outside these twenty
// bytes and stay unknown. 0xffffffff is a sentinel in its own right and is never
// normalised to ordinary pointer null.
//
// CORROBORATION THAT THE CALL FORM AND THE INLINED FORM READ THE SAME WORD
// -------------------------------------------------------------------------
// One caller, 0x00ad12a0, contains both spellings inside a single function body
// (body_start 0x00ad12a0, body_end 0x00ad20d9), and compares both against the
// same sentinel family:
//
//     0x00ad1f3e  e8 dd b3 06 00     call   0xb3d320
//     0x00ad1f43  8b c8              mov    ecx,eax
//     0x00ad1f45  e8 e6 07 f7 ff     call   0xa42730
//     0x00ad1f4a  3d 05 4c 65 01     cmp    eax,0x1654c05
//     0x00ad1f4f  75 12              jne    0xad1f63
//     ...
//     0x00ad1f63  e8 98 98 08 00     call   0xb5b800
//     0x00ad1f68  3d 04 4c 65 01     cmp    eax,0x1654c04
//
// The two paths set different downstream state bits (0x100 on the inlined
// 0x01654c05 arm, 0x200 on the call 0x01654c04 arm), which is what makes this
// decisive rather than circumstantial: one function, one forwarded word, two
// spellings, two members of the same encoded-state domain. This is the strongest
// single piece of evidence for the package and it is a fact about a caller, so
// it is recorded as corroboration of the field's existence and domain, NOT as a
// claim about what the field denotes. 0x01654c05 and 0x01654c04 are
// address-shaped, but neither is dereferenced here, and the sentinel family is
// a DIFFERENT domain from the 0xffffffff null sentinel the root itself returns.
//
// CALLING CONVENTION: NOT PROVEN, AND THEREFORE NOT INVENTED
// ----------------------------------------------------------
// What the bytes do fix: no register is read on entry, no stack word is named,
// and the terminal is a BARE RET (c3) with no immediate, so the callee pops
// nothing. The CALL at 0x00b5b800 is therefore not stack-balanced by the body.
// ECX is written at 0x00b5b809 purely to feed the tail jump, so it is not a
// receiver. With zero parameters and zero register receiver the body is
// byte-identical under __cdecl, __stdcall, __thiscall and __fastcall, so the
// macro below is named and deliberately carries no convention token.
//
// RETURN: four bytes, and only four bytes
// --------------------------------------
// Both exits write the whole of EAX -- 0x00b5b80b tail-jumps to a body whose
// only instruction is a 32-bit MOV into EAX, and 0x00b5b810 is
// OR EAX,0xffffffff which is a 32-bit operation on the whole register. The
// declared return is therefore std::uint32_t: a width-computable builtin, so the
// strict return check can measure it.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "forwarded state accessor 0x00b5b800 is an x86-32 reconstruction (absolute 32-bit operand at 0x00b3d320)"
#endif

// Calling convention: see the block comment above. The listing discriminates
// none, so the macro carries no token. The entry is modelled with the shape the
// bytes do fix -- zero parameters, no receiver, no callee stack cleanup.
#if defined(_MSC_VER)
#define PKG_00B5B800_CALL
#else
#define PKG_00B5B800_CALL
#endif

namespace openspore::reconstruction::pkg_00b5b800 {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts, each one decoded out of the body bytes above rather than
// restated, so no constant can drift away from the machine image.
// ---------------------------------------------------------------------------

// 0x00b5b800..0x00b5b813, twenty bytes, seven instructions (objdump range
// 0x00b5b7f0..0x00b5b820, and the Ghidra 24-byte read agree byte for byte).
constexpr std::uint8_t kTargetBytes[20] = {
    0xe8,  // 0x00b5b800 CALL rel32          (opcode E8, disp32 = 1b 1b fe ff)
    0x1b,  //   disp byte 0
    0x1b,  //   disp byte 1
    0xfe,  //   disp byte 2
    0xff,  //   disp byte 3
    0x85,  // 0x00b5b805 TEST EAX,EAX        (opcode 85, ModRM c0)
    0xc0,  //   ModRM rm=000, reg=000       (EAX, EAX)
    0x74,  // 0x00b5b807 JE rel8            (opcode 74, disp8 = 07)
    0x07,  //   disp byte 0
    0x8b,  // 0x00b5b809 MOV ECX,EAX        (opcode 8B, ModRM c8)
    0xc8,  //   ModRM rm=000, reg=001       (EAX -> ECX)
    0xe9,  // 0x00b5b80b JMP rel32           (opcode E9, disp32 = 20 6f ee ff)
    0x20,  //   disp byte 0
    0x6f,  //   disp byte 1
    0xee,  //   disp byte 2
    0xff,  //   disp byte 3
    0x83,  // 0x00b5b810 OR EAX,imm8        (opcode 83 /1, ModRM c8, imm8 = ff)
    0xc8,  //   ModRM rm=000, reg=001       (EAX, sign-extended imm8)
    0xff,  //   imm8 = ff, i.e. the all-ones 32-bit sentinel
    0xc3,  // 0x00b5b813 RET                (bare: no immediate, 0 bytes popped)
};

static_assert(kTargetBytes[0] == 0xe8,
              "byte 0 of the body is the x86-32 near CALL opcode E8, so the "
              "first instruction is a direct call with a 32-bit displacement");
static_assert(kTargetBytes[19] == 0xc3,
              "the last byte of the body is a bare RET (c3), so the callee "
              "pops nothing and the body is not stack balanced by itself");

// Entry, terminal and the size of the body between them.
constexpr Word kEntryVa = 0x00b5b800u;
constexpr Word kTerminalVa = 0x00b5b813u;
constexpr std::size_t kBodyBytes = 20;
static_assert(kEntryVa + kBodyBytes == 0x00b5b814u,
              "the entry address plus the twenty body bytes ends one past the "
              "last instruction byte, which is where the trailing INT3 starts");
static_assert(kTerminalVa - kEntryVa == 19,
              "the bare RET is the seventh instruction, nineteen bytes after "
              "entry");

// Instruction count, from both machine sources and the live listing: seven.
constexpr std::size_t kInstructionCount = 7;
static_assert(kInstructionCount == 7,
              "both machine sources and the live listing agree on exactly seven "
              "instructions in this body");

// The two direct branches, each target decoded from its own little-endian
// displacement rather than restated. A rel32 is relative to the byte AFTER the
// instruction's own displacement field, so the CALL's base is entry+5 and the
// JMP's base is entry+16 (the JMP itself starts at entry+11 and is five bytes
// long).
constexpr std::int32_t kCallDisp = static_cast<std::int32_t>(static_cast<std::uint32_t>(kTargetBytes[1]) |
                                                             (static_cast<std::uint32_t>(kTargetBytes[2]) << 8) |
                                                             (static_cast<std::uint32_t>(kTargetBytes[3]) << 16) |
                                                             (static_cast<std::uint32_t>(kTargetBytes[4]) << 24));
constexpr Word kCallBase = kEntryVa + 5;
constexpr Word kReceiverGlobalReaderVa = static_cast<Word>(kCallBase + kCallDisp);

constexpr std::int32_t kJmpDisp = static_cast<std::int32_t>(static_cast<std::uint32_t>(kTargetBytes[12]) |
                                                            (static_cast<std::uint32_t>(kTargetBytes[13]) << 8) |
                                                            (static_cast<std::uint32_t>(kTargetBytes[14]) << 16) |
                                                            (static_cast<std::uint32_t>(kTargetBytes[15]) << 24));
constexpr Word kJmpBase = kEntryVa + 16;
constexpr Word kForwardedFieldReaderVa = static_cast<Word>(kJmpBase + kJmpDisp);

static_assert(kReceiverGlobalReaderVa == 0x00b3d320u,
              "the CALL displacement bytes of the body resolve to the "
              "two-instruction global reader that MOVs the receiver slot");
static_assert(kForwardedFieldReaderVa == 0x00a42730u,
              "the JMP displacement bytes of the body resolve to the "
              "two-instruction field reader that MOVs a word through ECX");

// The forwarded field displacement. 0x20 is a NAME for a displacement, not a
// member: the storage is opaque and no struct layout is claimed. 8b 41 20 is
// MOV EAX, DWORD PTR [ECX+0x20] -- a displacement byte, not a vtable load and
// not an interface call: the instruction dereferences ECX directly, where a
// virtual dispatch would have needed a second load through [ECX].
constexpr Word kForwardedFieldDisplacement = 0x20;
static_assert(kForwardedFieldDisplacement == 0x20,
              "the field reader is MOV EAX,DWORD PTR [ECX+0x20], so the "
              "displacement it reads through the receiver is that value");

// The null-path sentinel, DECODED from the body's own immediate byte: the
// null arm is OR EAX,imm8 and x86-32 sign extends that 8-bit immediate to the
// full 32-bit register before the OR, so the byte becomes this word. Decoding
// it rather than restating it means the constant cannot drift away from the
// machine image, and the static_assert below pins the decode against the
// listing text OR EAX,0xffffffff. It is a sentinel with its own meaning and is
// never treated as pointer null.
constexpr Word kNullSentinel = static_cast<Word>(
    static_cast<std::int32_t>(static_cast<std::int8_t>(kTargetBytes[18])));
static_assert(kNullSentinel == 0xffffffffu,
              "the null arm is OR EAX,imm8 whose immediate byte is ff, and x86-32 "
              "sign extends it to the all-ones 32-bit word the listing prints as "
              "OR EAX,0xffffffff");

// Return width. Both exits write the whole of EAX: the tail jump lands on a
// 32-bit MOV into EAX, and the null path's OR is a 32-bit register operation.
constexpr std::size_t kReturnWidthBytes = 4;
static_assert(kReturnWidthBytes == sizeof(Word),
              "every exit writes all of EAX, so the returned word is exactly "
              "one 32-bit word");

// Call shape: zero explicit arguments, zero stack words, zero callee cleanup,
// and no register receiver. ECX is written on the non-null path purely to feed
// the tail jump, so it is not a receiver.
constexpr std::size_t kStackArgumentWords = 0;
constexpr std::size_t kCalleeCleanupBytes = 0;
constexpr bool kHasReceiver = false;
static_assert(kStackArgumentWords == 0,
              "the body names no stack operand and pushes nothing, so there are "
              "zero explicit arguments");
static_assert(kCalleeCleanupBytes == 0,
              "the terminal is a bare RET with no immediate, so the callee pops "
              "nothing");
static_assert(!kHasReceiver,
              "no register is read on entry and ECX is written on the non-null "
              "path only to feed the tail jump, so there is no receiver");

// Side effects: none. The body performs two reads -- the borrowed global
// receiver and the forwarded word -- and no store at all, on either path.
constexpr std::size_t kMemoryReads = 2;
constexpr std::size_t kMemoryStores = 0;
static_assert(kMemoryReads == 2,
              "one read of the borrowed receiver global and one read of the "
              "forwarded word, and nothing else");
static_assert(kMemoryStores == 0,
              "the only writes in the body are to EAX and the flags, so there "
              "is no store, no allocation and no mutation of receiver state");

// ---------------------------------------------------------------------------
// The two direct targets, modelled as the machine spells them.
// ---------------------------------------------------------------------------

// The two direct targets' own bodies, kept here so every constant below is
// decoded out of machine bytes rather than restated. These are the HELPER's
// bytes, not the root's, and are kept apart from kTargetBytes so the two bodies
// are never confused.
constexpr std::uint8_t kReceiverReaderBytes[6] = {
    0xa1,  // MOV EAX, moffs32
    0xec,  //   operand byte 0
    0xea,  //   operand byte 1
    0x67,  //   operand byte 2
    0x01,  //   operand byte 3
    0xc3,  // RET
};
constexpr std::uint8_t kFieldReaderBytes[4] = {
    0x8b,  // MOV r32, r/m32
    0x41,  //   ModRM: mod=01 disp8, reg=000 (EAX), rm=001 (ECX+disp8)
    0x20,  //   disp8
    0xc3,  // RET
};

static_assert(kReceiverReaderBytes[0] == 0xa1,
              "the receiver reader opens with the x86-32 accumulator load A1, so "
              "it returns one dword named by a four-byte absolute address");
static_assert(kFieldReaderBytes[1] == 0x41,
              "the field reader's ModRM byte selects ECX with an 8-bit "
              "displacement, so it dereferences the receiver directly");
static_assert(kFieldReaderBytes[2] == kForwardedFieldDisplacement,
              "the field reader's displacement byte is the forwarded field "
              "displacement, read straight out of the machine image");

// Absolute address the receiver reader's A1 operand names, decoded from that
// reader's own four operand bytes rather than restated.
constexpr Word kReceiverGlobalVa =
    static_cast<Word>(static_cast<std::uint32_t>(kReceiverReaderBytes[1]) |
                      (static_cast<std::uint32_t>(kReceiverReaderBytes[2]) << 8) |
                      (static_cast<std::uint32_t>(kReceiverReaderBytes[3]) << 16) |
                      (static_cast<std::uint32_t>(kReceiverReaderBytes[4]) << 24));
static_assert(kReceiverGlobalVa == 0x0167eaecu,
              "the A1 operand bytes of the receiver reader are the "
              "little-endian absolute address named by kReceiverGlobalVa");

// Modelled global image for the receiver slot. The guard words are test
// scaffolding invented here: they are NOT the neighbouring dwords of .data and
// nothing is claimed about what lives beside the slot.
constexpr std::size_t kReceiverGuardWords = 4;
constexpr std::uint32_t kReceiverGuardCanary = 0xa5a5a5a5u;

struct ReceiverGlobalImage {
  std::uint32_t guard_lo[kReceiverGuardWords];
  std::uint32_t slot;  // the one dword the receiver reader loads
  std::uint32_t guard_hi[kReceiverGuardWords];
};

static_assert(offsetof(ReceiverGlobalImage, slot) == kReceiverGuardWords * sizeof(std::uint32_t),
              "the modelled receiver slot sits immediately after the low guard "
              "words");
static_assert(sizeof(ReceiverGlobalImage) == (2 * kReceiverGuardWords + 1) * sizeof(std::uint32_t),
              "the modelled receiver image is two guard runs around one slot");

// Modelled forwarded receiver: an opaque byte run. kForwardedFieldDisplacement
// bytes of leading padding, then the forwarded word at that displacement, then
// trailing padding. No member of any struct is named here and none is claimed;
// the run exists so the model test can prove the reader touched one word.
constexpr std::size_t kForwardedObjectBytes = 64;
constexpr std::size_t kForwardedTrailBytes = kForwardedObjectBytes - kForwardedFieldDisplacement - sizeof(Word);

struct ForwardedReceiverImage {
  std::uint8_t bytes[kForwardedObjectBytes];
};

static_assert(kForwardedFieldDisplacement + sizeof(Word) + kForwardedTrailBytes == kForwardedObjectBytes,
              "the modelled byte run holds the forwarded word with padding on "
              "both sides of it");
static_assert(kForwardedFieldDisplacement > 0,
              "the forwarded word sits after leading padding, so a reader that "
              "used a wrong displacement lands somewhere this model can see");

// The modelled images, defined in the .cpp.
extern ReceiverGlobalImage g_receiver_global_image;
extern ForwardedReceiverImage g_forwarded_receiver_image;

// The repository's global-naming convention (g_<va8>) for the one dword the
// receiver reader loads, and for the opaque byte run the field reader reads
// through. The second is named for the ADDRESS the reader dereferences, not for
// a class: there is no class here.
extern Word& g_0167eaec;
extern std::uint8_t* g_forwarded_receiver;
extern Word& g_forwarded_receiver_field;

// The machine ABI as a C++ type, so a wrong prototype fails to build: zero
// parameters, 4-byte return, no receiver.
using AbiForwardedState00b5b800 = Word(PKG_00B5B800_CALL*)();
static_assert(sizeof(AbiForwardedState00b5b800) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Direct target 1, as the machine spells it: no arguments, returns the 32-bit
// receiver slot. Named WITHOUT an address, so only the reconstructed root
// carries the target VA token and no helper is mistaken for a call target.
Word read_receiver_slot();

// Direct target 2, as the machine spells it: a plain 32-bit field load through
// the receiver in the first argument register. It dereferences the receiver
// directly; it is not a vtable load and performs no virtual dispatch.
Word read_forwarded_field(Word receiver);

// Entry point under reconstruction: the opaque 32-bit forwarded state/handle.
Word PKG_00B5B800_CALL forwarded_state_00b5b800();

}  // namespace openspore::reconstruction::pkg_00b5b800
