#pragma once

// Reconstruction of FUN_00c772c0 @ 0x00c772c0 (SporeApp.exe 3.1.0.22).
//
// Evidence basis, re-read for this package:
//   * disassembly 0x00c772c0..0x00c772f7, 24 instructions, 56 bytes, read live
//     through GhidraMCP /disassemble_function and corroborated byte-for-byte
//     by GhidraMCP /read_memory:
//       0x00c772c0  56                PUSH ESI
//       0x00c772c1  57                PUSH EDI
//       0x00c772c2  8b 7c 24 0c       MOV  EDI,dword ptr [ESP + 0xc]
//       0x00c772c6  33 d2             XOR  EDX,EDX
//       0x00c772c8  8b c7             MOV  EAX,EDI
//       0x00c772ca  f7 b1 24 11 00 00 DIV  dword ptr [ECX + 0x1124]
//       0x00c772d0  8b 81 20 11 00 00 MOV  EAX,dword ptr [ECX + 0x1120]
//       0x00c772d6  33 f6             XOR  ESI,ESI
//       0x00c772d8  8b 14 90          MOV  EDX,dword ptr [EAX + EDX*0x4]
//       0x00c772db  85 d2             TEST EDX,EDX
//       0x00c772dd  74 0d             JZ   0x00c772ec
//       0x00c772df  90                NOP
//       0x00c772e0  3b 3a             CMP  EDI,dword ptr [EDX]
//       0x00c772e2  75 01             JNZ  0x00c772e5
//       0x00c772e4  46                INC  ESI
//       0x00c772e5  8b 52 04          MOV  EDX,dword ptr [EDX + 0x4]
//       0x00c772e8  85 d2             TEST EDX,EDX
//       0x00c772ea  75 f4             JNZ  0x00c772e0
//       0x00c772ec  33 c0             XOR  EAX,EAX
//       0x00c772ee  85 f6             TEST ESI,ESI
//       0x00c772f0  5f                POP  EDI
//       0x00c772f1  0f 95 c0          SETNZ AL
//       0x00c772f4  5e                POP  ESI
//       0x00c772f5  c2 04 00          RET  0x4
//     followed by 0xcc INT3 padding at 0x00c772f8..0x00c772ff, read live and
//     excluded from the body.
//   * raw bytes at 0x00c772c0 (56):
//       56578b7c240c33d28bc7f7b1241100008b812011000033f68b149085d2740d9
//       03b3a7501468b520485d275f433c085f65f0f95c05ec20400
//   * decompilation:
//       bool __thiscall FUN_00c772c0(int param_1, uint param_2)
//       { uint *puVar1; int iVar2;
//         iVar2 = 0;
//         for (puVar1 = *(uint **)(*(int *)(param_1 + 0x1120) +
//                                  (param_2 % *(uint *)(param_1 + 0x1124)) * 4);
//              puVar1 != (uint *)0x0; puVar1 = (uint *)puVar1[1]) {
//           if (param_2 == *puVar1) { iVar2 = iVar2 + 1; }
//         }
//         return iVar2 != 0; }
//   * receiver record: register=ECX, offsets=[0x1120, 0x1124], bounds_only,
//     distinct_offsets=2, max_offset=0x1124, written_through=0, shape R-DIRECT.
//   * ABI record: __thiscall, receiver ECX, one 4-byte ordinary stack argument
//     at entry_ESP+0x4, ret form RET 0x4, stack cleanup 4 bytes owned by the
//     callee, saved registers EDI and ESI, return register EAX.
//   * GLOBALS: the committed data-reference artifact records no data reference
//     out of 0x00c772c0, and the complete listing names no data-segment
//     address. Every operand is a register, a receiver-relative displacement or
//     a register-relative displacement. The body touches no global.
//   * CONTROL FLOW: all three conditional branch targets (0x00c772ec, 0x00c772e5
//     and 0x00c772e0) lie inside the recovered body span, so the branch graph
//     is closed inside it.
//   * VIRTUAL DISPATCH: the body names no indirect transfer through a register
//     or a memory operand; the machine dispatch record agrees at 0. There is no
//     CALL in the body. This entry is a dispatch TARGET and never a dispatcher.
//
// WHAT IS PROVED AND WHAT IS NOT.
//
// Proved by the 56 bytes above, with nothing added:
//   * the receiver is ECX, __thiscall, with exactly one 4-byte ordinary stack
//     argument that the callee itself pops (RET 0x4);
//   * the 32-bit stack argument is loaded into EDI from [ESP+0xc], which after
//     the two PUSHes is entry_ESP+0x4 - the single recorded stack slot;
//   * EDX is zeroed and EAX is loaded with that argument, so the dividend of
//     the DIV at 0x00c772ca is the 64-bit value 0:argument. DIV is the
//     UNSIGNED 32-bit divide, so EDX afterwards holds argument modulo
//     [ECX+0x1124] and EAX holds the quotient. The quotient is discarded: the
//     very next instruction overwrites EAX with [ECX+0x1120];
//   * [ECX+0x1120] is read as a 32-bit base address and the remainder scales it
//     by four - `MOV EDX,[EAX+EDX*0x4]` - so it is the base of an array of
//     4-byte head pointers, and the index is the unsigned remainder, NOT a
//     mask, NOT the quotient, and with no mixing function applied first: the
//     argument is both the bucket index source and the compared value;
//   * the word at [ECX+0x1124] is the divisor and is therefore the element
//     count of that array;
//   * ESI is a match counter starting at zero, incremented once per chain link
//     whose first dword equals the argument. The whole chain is walked; the
//     counter is never tested inside the loop, so a duplicated key is counted
//     more than once;
//   * the loop-carried pointer is the word at node+0x4 and the compared word is
//     the word at node+0x0, so a chain link is a 2-word, 8-byte record;
//   * an empty chain (head pointer zero) exits the loop without entering it,
//     which is what JZ 0x00c772ec does;
//   * the return value is STRICTLY 0 or 1 in EAX: EAX is zeroed at 0x00c772ec
//     and only AL is then written by SETNZ, so the upper 24 bits are provably
//     zero. The match COUNT is discarded and only its non-zeroness survives.
//     This is a stronger statement than the ABI record's
//     return_semantics=unclassified_in_EAX, and it is corroborated by the
//     sampled call sites, which all do `TEST AL,AL` on the result;
//   * the body writes nothing through ECX, through the bucket array or through
//     any chain link. The receiver record agrees at written_through=0. Every
//     memory operand is a read. The function is a pure predicate.
//
// NOT proved by the 56 bytes, and therefore not claimed below:
//   * WHAT the 32-bit values are. The argument arrives from callers as an
//     immediate constant (0x00ae9a29 pushes 0x4ac8010, 0x00cfa0f3 pushes
//     0x50a2e65, 0x00c8d060 pushes 0x6627823) - 31-bit magnitudes, which is
//     consistent with a pre-computed identifier or hash, but a packed enum and
//     a resource id behave identically here. The package therefore calls the
//     word a KEY, which is what the body does with it, and nothing more.
//   * the container. A chained hash SET, a multimap keyed on the same 32-bit
//     word, and a hand-rolled sparse set are one body. What the body proves is
//     the SHAPE - bucket array, modulo index, singly linked chain, first-word
//     key - and the shape is what the variable names reflect.
//   * the class that owns +0x1120/+0x1124. SporeApp.exe has no MSVC RTTI, so
//     the owning type is not recoverable from these instructions.
//   * the number of buckets in any real instance, and whether that count is
//     ever zero. See the DIVISION note below.
//   * whether any chain can be cyclic. The body has no iteration cap, no
//     pointer-identity check and no counter bound, so a cyclic chain would
//     spin forever. Nothing here establishes that one exists; the model test
//     deliberately does not build one, because a test that hangs is not a test.
//   * the source-level signature. See RETURN SEMANTICS below.
//
// DIVISION. The divisor is read from the receiver and is never tested. On this
// machine a DIV by zero raises #DE and the function does not return, so the
// observed precondition is [ECX+0x1124] != 0. The model below does not
// reproduce the trap - a C++ unsigned division by zero is undefined behaviour,
// not an exception - and the model test never calls the entry with a zero
// count. That divergence is deliberate and is recorded here rather than hidden:
// the machine behaviour is the OBSERVED claim, and the model's behaviour at
// count == 0 is NOT a claim of any kind.
//
// RETURN SEMANTICS. EAX provably carries 0 or 1 at the RET. That fixes the
// VALUE. It does not by itself fix the declared TYPE, because an int-returning
// source that returned only 0 and 1 would compile to the same instruction pair.
// What narrows it is the call sites: all three sampled do `TEST AL,AL` on the
// result, which is the natural consumer of a boolean and wasteful of a general
// int. The package therefore declares `bool`, and records that the machine
// proves the value range rather than the declared type. Ghidra's own
// decompilation agrees (`bool __thiscall`).
//
// CROSS-BODY EVIDENCE, kept separate from the machine evidence above.
//
// Two independently reconstructed callers, 0x00be92e0 and 0x00c8d060, call this
// entry as a query and, on a FALSE answer, immediately call the sibling
// 0x00c77bf0 with the SAME receiver and the SAME argument before proceeding.
// 0x00c8d060's committed metadata records the sequence verbatim: "query
// 0x00c772c0(state, 0x6627823). A true query returns; a false query calls
// 0x00c77bf0(state, 0x6627823)". A membership test whose miss path immediately
// performs a second operation on the same container with the same key is a
// contains() followed by an add(). That is what the local variable names
// reflect. It is a cross-body inference: the 56 bytes above state the predicate
// and nothing about the miss path, and 0x00c77bf0 itself is a separate target
// owned by another worker, whose semantics this package does not assert.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c772c0 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C772C0_THISCALL __thiscall
#else
#define PKG_00C772C0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c772c0_hashset_contains_key {

static_assert(sizeof(void*) == 4,
              "FUN_00c772c0 reconstruction requires 32-bit pointers");
static_assert(sizeof(std::int32_t) == 4,
              "the key the body compares and the counter it keeps are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "the key the body compares and the counter it keeps are 32-bit");

// The two receiver displacements this body names, from `DIV dword ptr
// [ECX + 0x1124]` and `MOV EAX,dword ptr [ECX + 0x1120]`. Stated as values
// rather than as member names: the receiver record enumerates displacements
// (bounds_only) and does not say which member of any type occupies them.
constexpr std::size_t kBucketBaseDisplacement = 0x1120;
constexpr std::size_t kBucketCountDisplacement = 0x1124;

// The two chain-link displacements this body names, from `CMP EDI,dword ptr
// [EDX]` and `MOV EDX,dword ptr [EDX + 0x4]`. Both belong to the heap link,
// not to the receiver, and both are 4 bytes.
constexpr std::size_t kLinkKeyDisplacement = 0x0;
constexpr std::size_t kLinkNextDisplacement = 0x4;

// The scale of the bucket index, from the SIB byte of `MOV EDX,dword ptr
// [EAX + EDX*0x4]`: one bucket is one 4-byte head pointer. The link is the
// head pointer of a chain, not a node.
constexpr std::size_t kBucketScale = 4;

// The receiver, modelled exactly as far as the machine reached and no further.
// The machine-derived receiver record is bounds_only with max_offset 0x1124 and
// written_through 0, so the 0x1120 bytes below the two named words are opaque
// AND unwritten, and the two named words are read-only. The extent is a
// modelling bound, not a recovered allocation size.
struct alignas(4) OpaqueBucketContainer {
  std::uint8_t opaque_000[0x1120];                 // +0x0000..0x111f, never read
  std::uint32_t* bucket_base_1120 = nullptr;       // +0x1120, read only
  std::uint32_t bucket_count_1124 = 0;             // +0x1124, read only
};

static_assert(sizeof(OpaqueBucketContainer) == 0x1128,
              "modeled receiver extent through the last word the body reads");
static_assert(offsetof(OpaqueBucketContainer, opaque_000) == 0x00,
              "the opaque region starts at receiver+0x00");
static_assert(offsetof(OpaqueBucketContainer, bucket_base_1120) == 0x1120,
              "the bucket base is the displacement the DIV/MOV pair names");
static_assert(offsetof(OpaqueBucketContainer, bucket_count_1124) == 0x1124,
              "the bucket count is the divisor displacement the DIV names");
static_assert(kBucketBaseDisplacement ==
                  offsetof(OpaqueBucketContainer, bucket_base_1120),
              "the header constant is the bucket-base displacement");
static_assert(kBucketCountDisplacement ==
                  offsetof(OpaqueBucketContainer, bucket_count_1124),
              "the header constant is the divisor displacement");
static_assert(kBucketBaseDisplacement + sizeof(std::uint32_t) ==
                  kBucketCountDisplacement,
              "the base pointer and the count are adjacent 4-byte words");
static_assert(kBucketCountDisplacement + sizeof(std::uint32_t) ==
                  sizeof(OpaqueBucketContainer),
              "the count ends the modeled receiver extent");
static_assert(kBucketScale == sizeof(std::uint32_t),
              "one bucket is one 4-byte head pointer");

// One link of a bucket's chain. Both words are named by the body: the first is
// the word compared against the argument, the second is the loop-carried
// pointer. The link is a 2-word record and the body reads no third word of it,
// so the extent stops at +0x4 even if the real allocation is larger.
struct alignas(4) OpaqueBucketLink {
  std::uint32_t key_00 = 0;                        // +0x0, compared against the arg
  OpaqueBucketLink* next_04 = nullptr;             // +0x4, the loop-carried link
};

static_assert(sizeof(OpaqueBucketLink) == 0x8,
              "a chain link is the two 4-byte words the body names");
static_assert(kLinkKeyDisplacement == offsetof(OpaqueBucketLink, key_00),
              "the header constant is the compared word's displacement");
static_assert(kLinkNextDisplacement == offsetof(OpaqueBucketLink, next_04),
              "the header constant is the next-link displacement");
static_assert(kLinkNextDisplacement + sizeof(OpaqueBucketLink*) ==
              sizeof(OpaqueBucketLink),
              "the next link ends the modeled link extent");

// The port type of the entry. The value range in EAX is 0 or 1, and every
// sampled call site tests AL, so the port type is the boolean predicate the
// machine computes.
using HashSetContainsKey00c772c0 =
    bool(PKG_00C772C0_THISCALL*)(OpaqueBucketContainer*, std::uint32_t);

// The 56 bytes read live at 0x00c772c0..0x00c772f7. Stated here so the
// reconstruction's instruction sequence is pinned in code and not only in
// prose. The 0xcc INT3 pad at 0x00c772f8 is deliberately excluded.
constexpr std::uint8_t kTargetBytes[56] = {
    0x56, 0x57, 0x8b, 0x7c, 0x24, 0x0c, 0x33, 0xd2, 0x8b, 0xc7, 0xf7, 0xb1,
    0x24, 0x11, 0x00, 0x00, 0x8b, 0x81, 0x20, 0x11, 0x00, 0x00, 0x33, 0xf6,
    0x8b, 0x14, 0x90, 0x85, 0xd2, 0x74, 0x0d, 0x90, 0x3b, 0x3a, 0x75, 0x01,
    0x46, 0x8b, 0x52, 0x04, 0x85, 0xd2, 0x75, 0xf4, 0x33, 0xc0, 0x85, 0xf6,
    0x5f, 0x0f, 0x95, 0xc0, 0x5e, 0xc2, 0x04, 0x00,
};

// 0x00c772c0  PUSH ESI
// 0x00c772c1  PUSH EDI
// 0x00c772c2  MOV  EDI,dword ptr [ESP + 0xc]
// 0x00c772c6  XOR  EDX,EDX
// 0x00c772c8  MOV  EAX,EDI
// 0x00c772ca  DIV  dword ptr [ECX + 0x1124]
// 0x00c772d0  MOV  EAX,dword ptr [ECX + 0x1120]
// 0x00c772d6  XOR  ESI,ESI
// 0x00c772d8  MOV  EDX,dword ptr [EAX + EDX*0x4]
// 0x00c772db  TEST EDX,EDX
// 0x00c772dd  JZ   0x00c772ec
// 0x00c772df  NOP
// 0x00c772e0  CMP  EDI,dword ptr [EDX]
// 0x00c772e2  JNZ  0x00c772e5
// 0x00c772e4  INC  ESI
// 0x00c772e5  MOV  EDX,dword ptr [EDX + 0x4]
// 0x00c772e8  TEST EDX,EDX
// 0x00c772ea  JNZ  0x00c772e0
// 0x00c772ec  XOR  EAX,EAX
// 0x00c772ee  TEST ESI,ESI
// 0x00c772f0  POP  EDI
// 0x00c772f1  SETNZ AL
// 0x00c772f4  POP  ESI
// 0x00c772f5  RET  0x4
//
// Returns true when the unsigned remainder of the argument modulo the bucket
// count selects a chain that contains a link whose first word equals the
// argument. See the header for what that does and does not establish.
extern "C" bool PKG_00C772C0_THISCALL hashset_contains_key_00c772c0(
    OpaqueBucketContainer* container, std::uint32_t key);

}  // namespace openspore::reconstruction::pkg_00c772c0_hashset_contains_key

#undef PKG_00C772C0_THISCALL
