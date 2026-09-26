#include "registry_0045ae10.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// 0x0045ae10 -- 42 bytes, 17 instructions, read live.
//
//   0x0045ae10  55                push ebp
//   0x0045ae11  8bec              mov  ebp, esp
//   0x0045ae13  83ec 6c           sub  esp, 0x6c
//   0x0045ae16  894d 94           mov  dword ptr [ebp - 0x6c], ecx
//   0x0045ae19  6a00              push 0x0
//   0x0045ae1b  8d4d c8           lea  ecx, [ebp - 0x38]
//   0x0045ae1e  e81d92fdff        call 0x00434040
//   0x0045ae23  50                push eax
//   0x0045ae24  8b45 0c           mov  eax, dword ptr [ebp + 0xc]
//   0x0045ae27  50                push eax
//   0x0045ae28  8b4d 08           mov  ecx, dword ptr [ebp + 0x8]
//   0x0045ae2b  51                push ecx
//   0x0045ae2c  8b4d 94           mov  ecx, dword ptr [ebp - 0x6c]
//   0x0045ae2f  e8ecfdffff        call 0x0045ac20
//   0x0045ae34  8be5              mov  esp, ebp
//   0x0045ae36  5d                pop  ebp
//   0x0045ae37  c2 0800           ret 0x8
//
// Live bytes: 55 8b ec 83 ec 6c 89 4d 94 6a 00 8d 4d c8 e8 1d 92 fd ff
//             50 8b 45 0c 50 8b 4d 08 51 8b 4d 94 e8 ec fd ff ff 8b e5
//             5d c2 08 00, then cc cc cc cc cc cc cc cc as the INT3 pad.
//
// Contract: build one default transform in the local frame, then hand the
// registry, the caller's key, the caller's mode and the address of that
// transform to 0x0045ac20. Nothing else happens. There is no branch, no
// global read and no field write on this side of the call.
//
// The receiver in every observed call site is the singleton returned by
// 0x00401050, which is a bare `mov eax, [0x015d0c14]; ret`:
//   0x005872f4  e8579de7ff  call 0x00401050
//   0x005872f9  8bc8        mov  ecx, eax
//   0x005872fb  e8503eedff  call 0x0045ae10
// and the first stack argument is the same value that was passed to 0x00401050
// (0x3f1bf51 at 0x005888e9, cEditor->mPlayModeEntryEffectID at 0x00587300).
// The file-image dword at 0x015d0c14 reads 00000000, so the runtime value of
// the registry pointer is not observable from the image.
//
// ABI hazard, recorded rather than smoothed over: 0x0045ac20 ends in
// `ret 0x10` at 0x0045ae03, so it consumes four stack arguments, but this
// wrapper pushes only three. The fourth is therefore read from this frame's
// own uninitialised local at [ebp - 0x68] (0x0045acf6 reads [ebp + 0x14] and
// branches on it when the third argument equals 1). The reconstruction keeps
// the third pushed argument only and names the gap explicitly instead of
// inventing a value for it.

extern "C" void __thiscall FUN_0045ae10_reconstruct(
    Opaque45ae10Registry* registry,
    std::uint32_t key,
    std::uint32_t mode) {
  // 0x0045ae13: SUB ESP,0x6c. The only named local is the transform at
  // [ebp - 0x38], which 0x00434040 fills and overwrites on every call.
  alignas(4) std::uint8_t frame[0x6c] = {};
  auto* transform =
      reinterpret_cast<Opaque45ae10Transform*>(frame + (0x6c - 0x38));

  // 0x0045ae19..0x0045ae1e: PUSH 0x0; LEA ECX,[EBP-0x38];
  // CALL 0x00434040. ECX carries the destination, the literal 0 the single
  // stack argument. The callee returns that same destination in EAX.
  Opaque45ae10Transform* built =
      port_00434040_default_transform(transform, 0u);

  // 0x0045ae23..0x0045ae2f. Push order gives the callee
  // (key, mode, built) in that order, with the receiver reloaded from the
  // prologue's spill slot rather than kept live in ECX.
  port_0045ac20_spawn(registry, key, mode, built, 0u);
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
