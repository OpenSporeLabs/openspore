#include "dogfood_008db310.hpp"

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL __attribute__((thiscall))
#else
#error \
    "pkg-orchestrate-dogfood-008db310 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_008db310 {

OpaquePorts g_pf_index_write_008db310_ports{};

// Every receiver and node access below is a DISPLACEMENT and not a member
// access. The machine-derived receiver record for this VA is a set of
// displacements (offsets=[0x2c, 0x30, 0x34, 0x38], bounds_only) and the
// complete listing shows the body reaching exactly two of them through ECX,
// 0x2c and 0x30. A record of that shape cannot say which member is which, so no
// member is named here - not on the carrier and not on the node. What each
// displacement is *for* is stated in the comments, as a reading of the
// instructions rather than as a type.
extern "C" bool PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
pf_index_write_bounds_008db310(OpaqueWriteCarrier* index, void* destination,
                               OpaqueWord destination_size) {
  // 008db310  MOV EAX,dword ptr [ESP + 0x8]
  // 008db314  PUSH EBX / PUSH EBP / PUSH ESI / PUSH EDI
  // 008db318  TEST EAX,EAX
  // 008db31a  JZ 0x008db37e
  //
  // The first ordinary argument, tested for zero before anything else. The
  // early return goes to the block that ends in `MOV AL,0x1`, so a zero extent
  // reports true - and it does so without reading either receiver word, which is
  // what the test's null-carrier case pins.
  if (destination_size == 0u) {
    return true;
  }

  // 008db31c  MOV EBX,dword ptr [ESP + 0x14]   the second ordinary argument
  // 008db320  MOV EDX,dword ptr [ECX + 0x2c]   the word EDX indexes over
  // 008db323  LEA EBP,[EBX + EAX*0x1]          destination_begin + extent
  //
  // The word at receiver+0x2c is an ADDRESS, not a datum: 0x008db32f and
  // 0x008db33b dereference EDX with a 4-byte scale, and 0x008db343 does the
  // same for the terminator.
  OpaqueItemNode* const* const slots =
      *reinterpret_cast<OpaqueItemNode* const* const*>(
          reinterpret_cast<const std::uint8_t*>(index) + 0x2c);
  // 008db33d  MOV ESI,dword ptr [ECX + 0x30]   the slot the terminator lives in
  const OpaqueWord end_slot = *reinterpret_cast<const OpaqueWord*>(
      reinterpret_cast<const std::uint8_t*>(index) + 0x30);
  // 32-bit unsigned arithmetic throughout: EBX, EBP, ECX and ESI are 32-bit
  // registers, the two compares are unsigned, and EBP is formed by a 32-bit
  // add (0x008db323 LEA EBP,[EBX + EAX*0x1]). Truncating the argument pointer
  // to 32 bits is what makes the model agree with the machine on a host whose
  // pointers are wider.
  const OpaqueWord destination_begin = static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(destination));
  const OpaqueWord destination_end = destination_begin + destination_size;

  // 008db326  MOV EAX,dword ptr [EDX]          first slot
  // 008db328  TEST EAX,EAX
  // 008db32a  JNZ 0x008db33d                   occupied -> use it
  // 008db32c  ADD EDX,0x4                      else step one slot on ...
  // 008db32f  CMP dword ptr [EDX],EAX          ... and test the NEW one
  // 008db331  JNZ 0x008db33b
  // 008db333  ADD EDX,0x4                      both empty: keep stepping
  // 008db336  CMP dword ptr [EDX],0x0
  // 008db339  JZ 0x008db333
  // 008db33b  MOV EAX,dword ptr [EDX]
  //
  // The skip runs over empty slots with a 4-byte stride, i.e. one pointer per
  // slot, and it stops at the first occupied one. Note the first step is
  // unconditional (0x008db32c) while the later ones are guarded, so the walk
  // always examines the slot AFTER the one it just found empty - the model below
  // reproduces that shape rather than a plain `while (empty)`.
  OpaqueWord cursor = 0u;
  OpaqueItemNode* node;

  while (cursor <= end_slot && slots[cursor] == nullptr) {
    ++cursor;
  }
  if (cursor > end_slot) {
    // Reached only through 0x008db37e from the earlier JZ, i.e. the whole slot
    // range is empty: nothing to compare against, so true.
    return true;
  }
  node = slots[cursor];

  // 008db340  MOV ECX,dword ptr [ECX + 0x2c]   the same word, read again
  // 008db343  MOV EDI,dword ptr [ECX + ESI*0x4] slots[end_slot]
  // 008db346  CMP EAX,EDI
  // 008db348  JZ 0x008db37e
  //
  // The terminator is the POINTER stored in the end slot, compared by identity
  // with the pointer being visited. Nothing about the node it points at takes
  // part in the test, and the same word is re-loaded at 0x008db340 rather than
  // reused from EDX, so the reconstruction reads it twice as well.
  OpaqueItemNode* const end_node = slots[end_slot];

  for (;;) {
    // 008db346 / 008db348, re-tested at the top of every iteration
    if (node == end_node) {
      return true;
    }
    // 008db34a  LEA EBX,[EBX]   a zero-displacement LEA: it changes nothing
    // 008db350  MOV ESI,dword ptr [EAX + 0x10]
    // 008db353  TEST ESI,ESI
    // 008db355  JZ 0x008db364
    //
    // A zero word skips the range test entirely - no compare, no branch into it.
    if (*reinterpret_cast<const OpaqueWord*>(
            reinterpret_cast<const std::uint8_t*>(node) + 0x10) != 0u) {
      // 008db357  MOV ECX,dword ptr [EAX + 0xc]
      // 008db35a  CMP ECX,EBP
      // 008db35c  JNC 0x008db364
      // 008db35e  ADD ECX,ESI
      // 008db360  CMP EBX,ECX
      // 008db362  JC 0x008db387
      //
      // Two UNSIGNED half-open range tests. `CMP a,b` / `JNC` skips when
      // record_begin >= destination_end; `CMP a,b` / `JC` reports false when
      // destination_begin < record_end. Both are unsigned: the second is a
      // `JB rel8` (0x72/0x73) and the first a `JAE`, and the operands are
      // 32-bit addresses. The two together are exactly
      // record_begin < destination_end && destination_begin < record_end, which
      // is a half-open overlap test: touching endpoints are NOT an overlap.
      const OpaqueWord record_begin = *reinterpret_cast<const OpaqueWord*>(
          reinterpret_cast<const std::uint8_t*>(node) + 0xc);
      const OpaqueWord record_size = *reinterpret_cast<const OpaqueWord*>(
          reinterpret_cast<const std::uint8_t*>(node) + 0x10);
      const OpaqueWord record_end = record_begin + record_size;
      if (record_begin < destination_end && destination_begin < record_end) {
        return false;  // 008db387 ... XOR AL,AL
      }
    }
    // 008db364  MOV EAX,dword ptr [EAX + 0x1c]
    // 008db367  TEST EAX,EAX
    // 008db369  JNZ 0x008db37a
    // 008db36b  JMP 0x008db370
    // 008db370  MOV EAX,dword ptr [EDX + 0x4]   next slot, 4-byte stride
    // 008db373  ADD EDX,0x4
    // 008db376  TEST EAX,EAX
    // 008db378  JZ 0x008db370
    // 008db37a  CMP EAX,EDI
    // 008db37c  JNZ 0x008db350
    //
    // The chain word, then: a null chain resumes the slot walk from the slot
    // after the one the chain started in. A non-null chain is followed, and the
    // terminator test runs again at 0x008db37a.
    node = reinterpret_cast<OpaqueItemNode*>(
        *reinterpret_cast<const OpaqueWord*>(
            reinterpret_cast<const std::uint8_t*>(node) + 0x1c));
    if (node == nullptr) {
      ++cursor;
      while (cursor <= end_slot && slots[cursor] == nullptr) {
        ++cursor;
      }
      if (cursor > end_slot) {
        return true;
      }
      node = slots[cursor];
    }
  }
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_008DB310_THISCALL
