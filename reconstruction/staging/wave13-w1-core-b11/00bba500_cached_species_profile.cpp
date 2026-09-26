// reconstruction/staging/wave13-w1-core-b11/00bba500_cached_species_profile.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00bba500 (image base
// 0x00400000). Body 0x00bba500..0x00bba562, 35 instructions, 99 bytes.
//
// Observed contract: return the receiver's cached dword at +0x80, resolving it
// on demand.
//
//   Path A - the key at +0x74 is zero:
//     if (+0x4c > 1) call the fill routine 0x00bba2a0 with the receiver,
//     then return +0x80 as it stands. No global is touched.
//
//   Path B - the key at +0x74 is non-zero:
//     let cached = +0x80.
//     if (cached != 0 && cached->+0x504 == +0x74) return cached  (cache hit,
//     no global touched).
//     otherwise push &receiver->+0x74, call 0x00401090
//     (Editors::cSpeciesManager::Get), then 0x004df550
//     (Editors::cSpeciesManager::GetSpeciesProfile(const ResourceKey&)) on it,
//     store the result into +0x80, and:
//       if the result is 0, call 0x00bba2a0 with the receiver and return +0x80
//       otherwise return the fetched pointer.
//
// Evidence, per branch:
//   0x00bba503: MOV ECX,dword ptr [ESI + 0x74]
//   0x00bba506: LEA EAX,[ESI + 0x74]          <- the address of the key field
//   0x00bba509: TEST ECX,ECX
//   0x00bba50b: JNZ 0x00bba527                <- path B
//   0x00bba50d: CMP dword ptr [ESI + 0x4c],0x1
//   0x00bba511: SETG AL                       <- signed greater-than
//   0x00bba518: MOV ECX,ESI ; 0x00bba51a: CALL 0x00bba2a0
//   0x00bba51f: MOV EAX,dword ptr [ESI + 0x80] ; 0x00bba525: POP ESI ; RET
//   0x00bba527: MOV EDX,dword ptr [ESI + 0x80]
//   0x00bba52d: TEST EDX,EDX ; 0x00bba52f: JZ 0x00bba539
//   0x00bba531: CMP dword ptr [EDX + 0x504],ECX
//   0x00bba537: JZ 0x00bba55f                 <- cache hit, EAX = EDX
//   0x00bba539: PUSH EAX                      <- EAX still holds &[ESI + 0x74]
//   0x00bba53a: CALL 0x00401090
//   0x00bba541: CALL 0x004df550
//   0x00bba546: MOV dword ptr [ESI + 0x80],EAX
//   0x00bba54c: TEST EAX,EAX ; 0x00bba54e: JNZ 0x00bba561
//   0x00bba552: CALL 0x00bba2a0 ; return +0x80
//
// The frame is PUSH ESI / POP ESI only; the return is a bare RET in all three
// exits, so the callee pops nothing and no stack argument is read.
//
// Cache validity is by data comparison, not by a generation counter: the cached
// object itself carries the key back at +0x504 and it is compared against the
// low word of the receiver's key.
//
// SDK correspondence, SUPPORTED but not asserted: the three receiver offsets
// this body touches (0x4c, 0x74, 0x80) coincide exactly with Spore-ModAPI
// Spore/Simulator/cStarRecord.h, where they are mTechLevel, mCitizenSpeciesKey
// and mpSpeciesProfile, and the receiver address at +0x74 is passed to a
// function the SDK names GetSpeciesProfile(const ResourceKey&). No vtable for
// cStarRecord was located and the binary has no MSVC RTTI, so the ownership
// stays a candidate.
//
// The 0x00bba2a0 call is left as an opaque port. Ghidra labels that address
// cStarRecord__ctor, but its body was read in this batch and it is a 166-
// instruction fill/reset routine keyed on [EDI + 0x4c] against 2, 4 and 5, not a
// constructor; the label is a nearest-address artefact and is withheld.

#include <cstdint>

#include "b11_opaque_types.hpp"

namespace openspore {
namespace b11 {
namespace t00bba500 {

// Observed receiver offsets.
inline constexpr std::size_t kTechLevelOffset = 0x4c;
inline constexpr std::size_t kKeyOffset = 0x74;
inline constexpr std::size_t kCachedProfileOffset = 0x80;
// Observed offset of the key back-reference inside the cached object.
inline constexpr std::size_t kCachedKeyBackOffset = 0x504;

Dword cached_species_profile(SpeciesKeyOwner* self, SpeciesManagerGetFn speciesManager,
                             GetSpeciesProfileFn getSpeciesProfile, FillCitizenSpeciesFn fill) {
    // 0x00bba506 LEA EAX,[ESI + 0x74]
    const Dword* const keyAddress = &self->field74;
    // 0x00bba503 / 0x00bba509
    const Dword key = self->field74;
    if (key == 0) {
        // 0x00bba50d CMP dword ptr [ESI + 0x4c],0x1 / 0x00bba511 SETG AL:
        // a SIGNED comparison, so a negative +0x4c does not trigger the fill.
        if (static_cast<std::int32_t>(self->field4c) > 1) {
            // 0x00bba518 MOV ECX,ESI / 0x00bba51a CALL 0x00bba2a0
            fill(self);
        }
        // 0x00bba51f / 0x00bba525 / 0x00bba526
        return self->field80;
    }

    // 0x00bba527 / 0x00bba52d / 0x00bba52f
    Dword cached = self->field80;
    if (cached != 0) {
        // 0x00bba531 CMP dword ptr [EDX + 0x504],ECX / 0x00bba537 JZ
        const Dword* const back = reinterpret_cast<const Dword*>(cached + kCachedKeyBackOffset);
        if (*back == key) {
            // 0x00bba55f MOV EAX,EDX
            return cached;
        }
    }

    // 0x00bba539 PUSH EAX (the key address) / 0x00bba53a CALL 0x00401090
    Ptr manager = speciesManager();
    // 0x00bba541 CALL 0x004df550 - second operand is still the key address.
    Dword fetched = reinterpret_cast<Dword>(getSpeciesProfile(manager, keyAddress));
    // 0x00bba546
    self->field80 = fetched;

    // 0x00bba54c / 0x00bba54e
    if (fetched == 0) {
        // 0x00bba550 MOV ECX,ESI / 0x00bba552 CALL 0x00bba2a0
        fill(self);
        // 0x00bba557
        return self->field80;
    }
    // 0x00bba561 POP ESI / 0x00bba562 RET - EAX already holds the pointer.
    return fetched;
}

}  // namespace t00bba500
}  // namespace b11
}  // namespace openspore
