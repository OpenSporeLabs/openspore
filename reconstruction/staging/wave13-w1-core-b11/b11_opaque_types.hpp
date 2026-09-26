// reconstruction/staging/wave13-w1-core-b11/b11_opaque_types.hpp
//
// Opaque receiver/record declarations for the wave-13 batch b11 reconstruction
// (PKG-11-SIM-CORE, SporeApp.exe 3.1.0.22, image base 0x00400000).
//
// Every type here is declared ONLY to the extent the binary proves it. Field
// offsets that appear below are the offsets the disassembly actually reads or
// writes. Where the owning class was not located, the type is a bare struct
// with named padding holes: no field is invented, and no vtable is declared
// because no vtable was located for any of these receivers.
//
// Nothing here is a claim about Spore's own class names. Names taken from
// Spore-ModAPI appear only where the SDK header offset AND the observed body
// agree, and are always marked as candidates in the metadata sidecar.

#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore {
namespace b11 {

using Word = std::uint32_t;
using Dword = std::uint32_t;
using Float = float;
using Bool = std::uint8_t;
using Ptr = void*;

// Layout padding only. Never instantiated, never read, never written.
template <std::size_t N>
struct BytePad {
    unsigned char opaque[N];
};

// ---------------------------------------------------------------------------
// Globals read by this batch. Both live in .data/.bss and hold zero in the file
// image, so their runtime values are unobserved.
// ---------------------------------------------------------------------------

// 0x0167eae0 - read by 0x00b3d300 (MOV EAX,dword ptr [0x0167eae0] / RET).
// Corroborated by reconstruction/metadata/wave13-w1-dispatch-b02/00b9aa10.json
// as an unnamed singleton whose handle is dereferenced at +0x74 by 0x00f67d90.
// NOT named: the owning subsystem is not established by this batch.
inline Word* const kSingletonHandle0167eae0 = nullptr;

// 0x0167eae4 - read by 0x00b3d2a0 (MOV EAX,dword ptr [0x0167eae4] / RET).
// reconstruction/metadata/pkg11-sim-core/00ba9370.json and
// reconstruction/metadata/wave13-w1-core-b07/00c30c80.json both record this slot
// as the star-manager root. That is INFERRED from those records, re-verified
// here only as far as "two-instruction global getter".
inline Word* const kSingletonHandle0167eae4 = nullptr;

// 0x01654c04 - compared against the return of 0x00b5b800 at 0x00be94b9 and
// again inside 0x00be88d0. Compared only, never dereferenced by this batch.
inline constexpr Dword kTelescopeSentinel01654c04 = 0x01654c04u;

// 0x01654c05 - compared against the return of 0x00b5b800 at 0x00be8960.
inline constexpr Dword kTelescopeSentinel01654c05 = 0x01654c05u;

// ---------------------------------------------------------------------------
// 0x00c37120 receiver.
//
// OBSERVED: ECX is the receiver; the body reads a single float at +0x768.
// 0x00dc0230 passes [ESI + 0x68c] as the receiver, so in at least one call the
// receiver is a sub-object of the caller's own this. 0x00c370e0, the sibling
// body 0x40 bytes earlier, dereferences ECX directly at +0x34 and +0x77e, so
// the object is at least 0x780 bytes. The owning class is NOT located.
// ---------------------------------------------------------------------------
struct FloatField768Owner {
    BytePad<0x768> pad0;
    Float field768;  // 0x00c37120: FLD dword ptr [ECX + 0x768]
};

// ---------------------------------------------------------------------------
// 0x00c0c1a0 receiver.
//
// OBSERVED: ECX is the receiver; the body returns the dword at +0xe84.
// 0x00c0c180, ten bytes earlier, is the matching setter: it stores its stack
// argument at [ECX + 0xe84] and, when non-null, caches [arg + 0x10] at
// [ECX + 0xe80]. So the pair manages one pointer field plus a shadow copy of
// that pointee's +0x10 word. The pointee is read by callers at +0x330, +0x384,
// +0x389, +0x390, +0x3fc..+0x420. No type is claimed for it.
// ---------------------------------------------------------------------------
struct PointerFieldE84Owner {
    BytePad<0xe80> pad0;
    Dword fieldE80;  // 0x00c0c180: shadow of pointee->+0x10
    Dword fieldE84;  // 0x00c0c1a0: MOV EAX,dword ptr [ECX + 0xe84]
};

// ---------------------------------------------------------------------------
// 0x00c308b0 receiver.
//
// OBSERVED: ECX is the receiver; the body compares the dword at +0x84 against
// the dword at +0x1d8 of the object reached through 0x0167eae4. 0x00c301c0
// copies three consecutive dwords from an argument's +0xb28..+0xb30 into
// +0x80/+0x84/+0x88 of a receiver of the same shape, so +0x84 is the middle
// word of a three-dword group starting at +0x80. The group is not named.
// ---------------------------------------------------------------------------
struct Dword84Owner {
    BytePad<0x80> pad0;
    Dword field80;
    Dword field84;  // 0x00c308c1: CMP EAX,dword ptr [ESI + 0x84]
    Dword field88;
};

// ---------------------------------------------------------------------------
// 0x00c30e80 receiver.
//
// OBSERVED: ECX is the receiver; the body reads the dword at +0x58 and passes
// it to the two-argument switch at 0x00c30cc0, which accepts only 0..0x11. The
// sibling 0x00c30eb0 switches on the same field and returns pointers, so +0x58
// is a small enumerated selector. Its domain is NOT established.
// ---------------------------------------------------------------------------
struct EnumField58Owner {
    BytePad<0x58> pad0;
    Dword field58;  // 0x00c30ea0: MOV EAX,dword ptr [ESI + 0x58], range 0..0x11
};

// ---------------------------------------------------------------------------
// 0x00bba500 receiver.
//
// SDK CANDIDATE (SUPPORTED, not confirmed): the three offsets the body touches
// coincide exactly with Spore-ModAPI Spore/Simulator/cStarRecord.h - 0x4c
// mTechLevel, 0x74 mCitizenSpeciesKey, 0x80 mpSpeciesProfile - and 0x00bba506 /
// 0x00bba53a pass the address of the +0x74 field to Editors::cSpeciesManager::
// GetSpeciesProfile(const ResourceKey&). No vtable for cStarRecord was located
// and SporeApp.exe has no MSVC RTTI, so the ownership is not asserted.
// ---------------------------------------------------------------------------
struct SpeciesKeyOwner {
    BytePad<0x4c> pad0;
    Dword field4c;  // compared against 1 (SETG) and against 2/4/5 in 0x00bba2a0
    BytePad<0x74 - 0x50> pad1;
    Dword field74;  // low word of the key; zero means "key empty"
    Dword field78;
    Dword field7c;
    Dword field80;  // cached profile pointer
};

// ---------------------------------------------------------------------------
// 0x00be92e0 receiver. 386 instructions, five stack arguments, RET 0x14.
// Every offset below is one the body itself touches. Nothing is named.
// ---------------------------------------------------------------------------
struct ArrivalOwner {
    BytePad<0x34> pad0;
    Dword field34;    // sub-object pointer; virtual slot +0x04 and +0x2c used
    BytePad<0x120 - 0x38> pad1;
    Dword field120;   // sub-object pointer; virtual slots +0x2c and +0x58 used
    BytePad<0x230 - 0x124> pad2;
    Dword field230;   // sub-object passed to 0x00bc3110
    BytePad<0x29c - 0x234> pad3;
    Dword field29c;   // 0..2 selector stored from stack argument 1
    BytePad<0x2e0 - 0x2a0> pad4;
    Bool field2e0;    // seven byte flags set to 1 at 0x00be9394..0x00be93be
    Bool field2e1;
    Bool field2e2;
    Bool field2e3;
    Bool field2e4;
    Bool field2e5;
    Bool field2e6;
    BytePad<0x320 - 0x2e7> pad5;
    Dword field320;   // null-checked, then +0x34 is passed to 0x00ad7a30
    BytePad<0x33c - 0x324> pad6;
    Bool field33c;
    BytePad<0x340 - 0x33d> pad7;
    Dword field340;   // begin of the array walked at 0x00be9520
    Dword field344;   // end of the same array
    BytePad<0x540 - 0x348> pad8;
    Dword field540;   // second 0..2 selector, compared against field29c
    BytePad<0x590 - 0x544> pad9;
    Dword field590;   // sub-object pointer; virtual slots +0x00, +0x04, +0x4c
    BytePad<0x6c0 - 0x594> pad10;
    Bool field6c0;    // cleared at 0x00be97de
    BytePad<0x6c8 - 0x6c1> pad11;
    Dword field6c8;   // sub-object passed to 0x00bc3130
    BytePad<0x748 - 0x6cc> pad12;
    Float field748;   // three (float, int) pairs reset to (0.0f, -1)
    Dword field74c;
    Float field750;
    Dword field754;
    Float field758;
    Dword field75c;
    BytePad<0x762 - 0x760> pad13;
    Bool field762;
    BytePad<0x7d8 - 0x763> pad14;
    Dword field7d8;   // three words copied from the previous record +0xc4..+0xcc
    Dword field7dc;
    Dword field7e0;
    Dword field7e4;   // three words copied from the new record +0xc4..+0xcc
    Dword field7e8;
    Dword field7ec;
    BytePad<0x810 - 0x7f0> pad15;
    Dword field810;   // sub-object pointer; virtual slots +0x0c and +0x10
};

// The three-word payload copied out of the record at 0x00be943a..0x00be9481 is
// three consecutive dwords at +0xc4, +0xc8, +0xcc, but it is copied with
// MOVSS into a different destination on one path (0x00be93ef..0x00be9413 uses
// MOVSS from +0xc4/+0xc8/+0xcc). The two spellings are recorded, not unified.
struct RecordTriWord {
    Dword c4;
    Dword c8;
    Dword cc;
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared, not implemented. Each is a distinct callee whose
// operation this batch did not establish.
// ---------------------------------------------------------------------------

// 0x00b3d2a0 - two instructions, MOV EAX,dword ptr [0x0167eae4] / RET. Despite
// the __thiscall-looking call shape at its sites it reads no register.
using GlobalGetterEae4Fn = Dword (*)();

// 0x00b3d300 - two instructions, MOV EAX,dword ptr [0x0167eae0] / RET.
using GlobalGetterEae0Fn = Dword (*)();

// 0x00f67d90 - two instructions, MOV EAX,dword ptr [ECX + 0x74] / RET.
using Word74GetterFn = Dword (*)(Ptr);

// 0x00c75420 - two instructions, MOV EAX,dword ptr [ECX + 0x1248] / RET.
using Word1248GetterFn = Dword (*)(Ptr);

// 0x00885c90 - two instructions, MOV EAX,dword ptr [ECX + 0x1d8] / RET.
using Word1d8GetterFn = Dword (*)(Ptr);

// 0x00401090 - named Editors::cSpeciesManager::Get by the SDK import; body
// not re-read in this batch, so the name stays a candidate.
using SpeciesManagerGetFn = Ptr (*)();

// 0x004df550 - named Editors::cSpeciesManager::GetSpeciesProfile by the SDK
// import. Called as GetSpeciesProfile(&receiver->field74).
using GetSpeciesProfileFn = Ptr (*)(Ptr, const void*);

// 0x00bba2a0 - the fill/reset routine called on the no-key and failed-lookup
// paths. 166 instructions. Ghidra labels it cStarRecord__ctor; that label is a
// nearest-address artefact of the SDK import and the body is NOT a constructor,
// so the name is withheld here.
using FillCitizenSpeciesFn = void (*)(SpeciesKeyOwner*);

// 0x00c30cc0 - 110 instructions, two-argument switch, bare RET (caller cleans
// 8 bytes of stack). Returns one of 27 constants.
using SelectorIdLookupFn = Dword (*)(Dword, Dword);

// 0x00b5b800 - compared against 0x01654c04 / 0x01654c05; body not read here.
using ModeProbeFn = Dword (*)();

// 0x00cf74c0 - two instructions, MOV EAX,[0x0169d2c8] / RET.
using SingletonGetter0169d2c8Fn = Ptr (*)();

// 0x00cf75d0, 0x00cf8e00, 0x00cf7520 - all called on the value 0x00cf74c0
// returns; bodies not read in this batch.
using OwnerBoolFn = Bool (*)(Ptr);
using OwnerVoidFn = void (*)(Ptr);

// Virtual slots are dispatched as MOV EDX,[ECX] / MOV EAX,[EDX+slot] /
// CALL EAX with ECX as the receiver, plus whatever stack arguments the
// slot's own body expects. SporeApp.exe has no RTTI, so the owning class of
// each table is not established and the port stays variadic.
using VirtualFn = Dword (*)(Ptr, ...);

// ---- callees of 0x00be92e0 that stay opaque ports -----------------------
using ArrivalVoidFn = void (*)(Ptr, Dword, Dword);                         // 0x00be2440
using ArrivalOneArgFn = void (*)(Ptr, Dword);                            // 0x00be45b0
using ArrivalThreeArgFn = void (*)(Ptr, Dword, Dword, Dword);            // 0x00be88d0
using ArrivalVoidC1Fn = void (*)(Ptr, Ptr);                               // 0x00bc3110
using ArrivalVoidC8Fn = void (*)(Ptr, Dword);                             // 0x00bc3130
using Bfc6a0Fn = void (*)(Ptr, Ptr);                                      // 0x00bfc6a0
using Dc4c60Fn = void (*)(Ptr);                                          // 0x00dc4c60
using Befab0Fn = Dword (*)(Ptr);                                         // 0x00befab0
using B25f40Fn = Ptr (*)(Ptr, Dword);                                    // 0x00b25f40
using B25fb0Fn = Ptr (*)(Ptr);                                           // 0x00b25fb0
using LookupProbeFn = Bool (*)(Ptr, Dword);                               // 0x00c772c0
using LookupReportFn = void (*)(Ptr, Dword);                              // 0x00c77bf0
using SpaceTradingGetFn = Ptr (*)();                                      // Simulator::cSpaceTrading::Get (0x00b3d4d0)
using UIEventLogGetFn = Ptr (*)();                                        // Simulator::cUIEventLog::Get  (0x00b3d4e0)
using SpaceTradingThreeFn = void (*)(Ptr, Dword, const void*, Dword);     // 0x00ae09b0
using SpaceTradingEventFn = void (*)(Ptr, const char*, Dword, Dword, Dword, Dword);  // 0x00ae0930
using Ad79d0Fn = void (*)(void*, const void*, Ptr);                       // 0x00ad79d0
using Ad7a30Fn = void (*)(void*, Ptr);                                    // 0x00ad7a30
using Ad7ad0Fn = void (*)(void*);                                         // 0x00ad7ad0
using Ad7b70Fn = Ptr (*)();                                               // 0x00ad7b70
using Adde90Fn = void (*)(Ptr, Dword, const void*, Dword);                // 0x00adde90
using Bd7f70Fn = void (*)(Ptr, Ptr);                                      // 0x00bd7f70

}  // namespace b11
}  // namespace openspore
