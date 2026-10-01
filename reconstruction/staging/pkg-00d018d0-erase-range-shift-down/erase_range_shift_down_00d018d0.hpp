#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-00D018D0 erase range shift down requires an x86-32 target"
#endif

// 0x00d018d0 is 31 instructions, 0x00d018d0..0x00d0190f inclusive, and every
// one of them is accounted for below. Four machine facts fix the calling
// convention, and each is read from the instruction stream rather than inferred:
//
//   * the only register the body reads that a caller controls is ECX, and it is
//     dereferenced immediately (0x00d018d5 `MOV EBX,dword ptr [ECX + 0x4]`),
//     which is a receiver read rather than an ordinary argument;
//   * two words are read off the incoming stack, at entry ESP+0x4 and, after
//     three pushes, ESP+0x14 == entry ESP+0x8 (0x00d018d0 and 0x00d018da);
//   * the terminator is `RET 0x8` (0x00d0190f), so the callee pops eight bytes
//     -- exactly the two stack arguments -- which excludes __cdecl and
//     __fastcall and leaves __thiscall or __stdcall;
//   * ECX is read as a receiver base and one of the two stack words is read
//     through it, so the frame is __thiscall.
#if defined(_MSC_VER)
#define PKG_00D018D0_THISCALL __thiscall
#else
#define PKG_00D018D0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00d018d0_erase_range_shift_down {

// The receiver. The body reaches exactly one displacement on it -- 0x4, at
// 0x00d018d5 and again at 0x00d01909 -- and the machine-derived receiver record
// enumerates {0x4} as its complete offset set (bounds_only, max_offset 4). That
// is where the body was seen reaching; it does not say WHICH member lives there.
// This type therefore carries no fields and asserts no size, and the word at
// displacement 0x4 is reached by arithmetic in the body rather than named as a
// member. See `not_claimed` in the metadata sidecar.
struct OpaqueReceiver;

// The element the body moves. Its size is not a guess: the copy loop advances
// both cursors by 0x8 (0x00d018f1, 0x00d018f4), copies two 32-bit words per
// iteration (0x00d018e7..0x00d018ee), and the removal count is derived from the
// range length by an arithmetic shift of 0x3 (0x00d018fe) and then scaled back
// up by three doublings (0x00d01903, 0x00d01905, 0x00d01907). 0x8 >> 0x3 is 1,
// so the element is 8 bytes. WHAT those 8 bytes contain is not established: the
// loop moves them as two opaque 32-bit words and never interprets either.
struct OpaqueElement;

// The receiver displacement the body reaches, and the only one the machine
// enumerates for it (0x00d018d5 `MOV EBX,dword ptr [ECX + 0x4]`,
// 0x00d01909 `ADD dword ptr [ECX + 0x4],EDI`). It is stated as a computed
// displacement, not as an offset of a declared member, because the receiver
// record is bounds_only and cannot corroborate a field identity.
inline constexpr std::ptrdiff_t kTailDisplacement = 0x4;

// The stride of both cursors in the shift loop, from `ADD EDX,0x8` at
// 0x00d018f1 and `ADD ESI,0x8` at 0x00d018f4.
inline constexpr std::ptrdiff_t kElementStride = 0x8;

// The arithmetic shift that turns a byte length into an element count,
// `SAR EDI,0x3` at 0x00d018fe. It is an ARITHMETIC shift: on a negative length
// it rounds toward negative infinity, which is why the body gets the negation
// for free from the following `NEG EDI` at 0x00d01901.
inline constexpr unsigned kCountShift = 0x3;

// 0x00d018d0, 31 instructions, body 0x00d018d0..0x00d0190f inclusive.
//
// Reads two stack words and the receiver word at displacement 0x4; copies the
// element range [last, receiver_tail) down over [first, receiver_tail - (last -
// first)); then adds -(last - first) to the receiver word at displacement 0x4.
// No call, no global, no indirect transfer, no branch outside the body.
extern "C" OpaqueElement* PKG_00D018D0_THISCALL erase_range_shift_down_00d018d0(
    OpaqueReceiver* self, OpaqueElement* first, OpaqueElement* last);

}  // namespace openspore::reconstruction::pkg_00d018d0_erase_range_shift_down