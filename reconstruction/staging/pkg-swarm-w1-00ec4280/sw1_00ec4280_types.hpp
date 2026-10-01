// PKG-SWARM-W1-00EC4280 -- VA 0x00ec4280
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, offsets and call-boundary declarations for the Sporepedia online
// deleting destructor at 0x00ec4280 (Ghidra: FUN_00ec4280).
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM. The whole
// target is 14 instructions / 50 bytes, so the split between "this body's own
// listing" and "some other body's listing" is short enough to state in full:
//
// 1. IN THIS BODY'S OWN 14-INSTRUCTION LISTING (the complete body span is
//    0x00ec4280..0x00ec42b1, 50 bytes, raw hex re-read for this package):
//
//      0x00ec4280  56                    PUSH ESI
//      0x00ec4281  8B F1                 MOV ESI,ECX
//      0x00ec4283  C7 06 90 90 48 01     MOV dword ptr [ESI],0x01489090
//      0x00ec4289  C7 46 10 7C 90 48 01  MOV dword ptr [ESI+0x10],0x0148907C
//      0x00ec4290  C7 46 14 6C 90 48 01  MOV dword ptr [ESI+0x14],0x0148906C
//      0x00ec4297  E8 F4 DE 77 FF        CALL 0x00642190
//      0x00ec429C  F6 44 24 08 01        TEST byte ptr [ESP+0x8],0x1
//      0x00ec42A1  74 09                 JZ 0x00ec42AC
//      0x00ec42A3  56                    PUSH ESI
//      0x00ec42A4  E8 D7 30 80 00        CALL 0x00F47380
//      0x00ec42A9  83 C4 04              ADD ESP,0x4
//      0x00ec42AC  8B C6                 MOV EAX,ESI
//      0x00ec42AE  5E                    POP ESI
//      0x00ec42AF  C2 04 00              RET 0x4
//
//    From those fourteen instructions this header takes, and nothing else:
//
//      * the three vptr displacements  0x00, 0x10, 0x14
//        (the machine-derived receiver record agrees exactly: offsets [0, 16,
//        20], max_offset 20, register ECX, shape R-ALIAS, written_through 3)
//      * the three vptr immediates     0x01489090, 0x0148907C, 0x0148906C
//      * the tested mask                0x01, and that it is tested on a BYTE
//      * the two direct call targets    0x00642190 and 0x00F47380
//      * the terminator                 RET 0x4, i.e. callee-owned 4-byte
//                                       cleanup of exactly one stack word
//      * the return                     EAX = ESI = the receiver
//      * the single saved register      ESI
//      * the ONE conditional branch, and its polarity (JZ = do NOT free when
//        the mask is clear)
//
// 2. FROM THE IMAGE AT THE VTABLE ADDRESSES (128 bytes read at 0x01489040 and
//    walked). This is what licenses the word "vtable" and fixes the slot:
//
//      0x01489090  = 0x00EC4280   <-- this body, slot +0x00
//      0x01489094  = 0x00641340
//      0x01489098  = 0x00C2E4E0
//      0x0148909C  = 0x00641810   ... (the Sporepedia accessors the analogue
//                                     records 0x00641400/0x00641770/0x00641810/
//                                     0x00641820/0x00641850 also point at)
//
//    So the immediate 0x01489090 is not a bare constant: it is the address of
//    a virtual function table whose slot +0x00 holds this very body's entry
//    point. That is the machine's own definition of the vtable-destructor slot
//    on an x86-32 MSVC-style ABI, and it is the reason this body is modelled
//    as a destructor rather than as "a function that writes three words".
//
//    The same image read also shows the SAME address 0x00EC4280 at two further
//    slots of the other two tables this body installs:
//
//      0x0148907C + 0x14 = 0x01489090 = 0x00EC4280   (the table stored at +0x10)
//      0x0148906C + 0x24 = 0x01489090 = 0x00EC4280   (the table stored at +0x14)
//
//    Those two extra hits are recorded here as OBSERVED offsets and are NOT
//    interpreted. Nothing in the machine says whether they are this class's own
//    destructor reachable through two base subobjects, or a shared tail of
//    overlapping tables. See unresolved_questions.
//
// 3. FROM THE TWO NEIGHBOURING THUNKS, 0x00ec4230 and 0x00ec4240 (bytes read at
//    0x00ec4220; these are the two Ghidra "callers" 0x00ec4233 / 0x00ec4243,
//    which are the displacement bytes INSIDE the JMPs, not call sites):
//
//      0x00ec4230  83 E9 10              SUB ECX,0x10
//      0x00ec4233  E9 48 00 00 00        JMP 0x00ec4280
//      0x00ec4240  83 E9 14              SUB ECX,0x14
//      0x00ec4243  E9 38 00 00 00        JMP 0x00ec4280
//
//    Both tail-jump here after adjusting the receiver DOWN by 0x10 / 0x14 --
//    exactly the two displacements this body writes vptrs at besides +0x00.
//    That is corroboration for the 0x10 / 0x14 displacements from a second,
//    independent direction, and it is why the model calls this a deleting
//    destructor of a class reached at three subobject positions. The two
//    thunks are stored at 0x01489084 and 0x0148906C respectively (image read).
//
// 4. FROM THE TWO DIRECT CALLEES' OWN BYTES, for the calling conventions only:
//
//      0x00642190  46 instructions, ends `8B CE 5E E9 96 F0 FF FF`
//                  (MOV ECX,ESI / POP ESI / JMP 0x006412A0) -- a TAIL transfer,
//                  so the RET that actually runs belongs to 0x006412A0, and
//                  0x006412A0 is 4 instructions ending in a bare `C3` with no
//                  immediate. Zero stack words, zero cleanup: __thiscall,
//                  receiver only.
//      0x00F47380  8B 44 24 04 / 85 C0 / 74 0C / 8B 0D 44 8B 6C 01 / 50 /
//                  E8 2C 03 9E FF / C3 -- ends in a bare `C3` with no
//                  immediate, and the caller drops the word itself with
//                  `ADD ESP,0x4` at 0x00ec42a9: cdecl, one stack word, and
//                  that word is read at its own [ESP+0x4], i.e. it is the
//                  receiver that 0x00ec42a3 pushed.
//
// 5. NOT CLAIMED, ANYWHERE, BY THIS HEADER:
//
//      * the size of the object. This body never reads past +0x14 and never
//        writes past +0x17, so the model's receiver is exactly 0x18 bytes. The
//        real 0x00642190 reads up to +0x74, so the real object is larger; that
//        is a fact about the CALLEE and the test gives its observer room rather
//        than inflating the type.
//      * a class name. The triage cluster says "sporepedia-online" and the
//        subsystem says "Sporepedia", but no MSVC RTTI survives in this binary
//        and no record names the class. The type below is called
//        SporepediaOnlineAsset for readability and nothing more.
//      * what the delete-flag byte's OTHER seven bits mean. Only bit 0 is
//        tested. Bits 1..7 are never examined by this body.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00ec4280 requires an x86-32 target"
#endif

// Both spellings are fixed by machine bytes, not chosen for convenience:
//
//   SW1_00EC4280_THISCALL  0x00642190 (no stack word, tail-transfers to a
//                          bare-RET 4-instruction body) and this body itself,
//                          whose terminator is C2 04 00 -- RET 0x4, so the
//                          callee eats its one stack argument.
//   SW1_00EC4280_CDECL     0x00F47380, bare `C3` terminator, and the caller
//                          drops the pushed word itself with ADD ESP,0x4.
#if defined(_MSC_VER)
#define SW1_00EC4280_THISCALL __thiscall
#define SW1_00EC4280_CDECL __cdecl
#else
#define SW1_00EC4280_THISCALL __attribute__((thiscall))
#define SW1_00EC4280_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00ec4280 {

using Word = std::uint32_t;

// -- the three vptr displacements this body writes -------------------------
// 0x00ec4283 MOV dword ptr [ESI],0x01489090      -> +0x00
// 0x00ec4289 MOV dword ptr [ESI+0x10],0x0148907C -> +0x10
// 0x00ec4290 MOV dword ptr [ESI+0x14],0x0148906C -> +0x14
constexpr std::size_t kVptrDisplacementPrimary = 0x00;
constexpr std::size_t kVptrDisplacementSecondary = 0x10;
constexpr std::size_t kVptrDisplacementTertiary = 0x14;

// -- the three vptr immediates ---------------------------------------------
// Read straight out of the three C7-prefixed MOV immediates above. The primary
// one is additionally pinned by the image word at 0x01489090, which equals this
// body's own entry point -- see the header's note (2).
constexpr Word kVptrPrimary = 0x01489090u;
constexpr Word kVptrSecondary = 0x0148907Cu;
constexpr Word kVptrTertiary = 0x0148906Cu;

// -- the tested mask --------------------------------------------------------
// 0x00ec429C F6 44 24 08 01  TEST byte ptr [ESP+0x8],0x1
constexpr std::uint8_t kDeleteFlagMask = 0x01;

// The absolute entry point of the table at kVptrPrimary, kept as a value so a
// reviewer can check it against the image without running anything.
constexpr Word kThisBodyEntryPoint = 0x00EC4280u;

// The receiver. Declared as an opaque run with NO members, on purpose.
//
// The body reaches exactly three displacements on it and writes all three. The
// machine-derived receiver record enumerates the same three and carries
// bounds_only - it says where the body was seen reaching, not which member is
// which. Naming them "vptr" here is a statement about the VALUES stored (three
// image addresses that are vftable bases) and not a claim that the type has
// those members; the accessor below is used instead, so a displacement error in
// the .cpp shows up as a wrong address rather than as a plausible field write.
//
// The run is 0x18 bytes: 0x14 is the largest displacement this body touches
// and the stores are 4 bytes wide, so 0x14 + 4 == 0x18 is the last byte it can
// possibly write. Bytes 0x04..0x0f are between the first and second store and
// bytes 0x18.. do not exist as far as THIS body is concerned; the model test
// fills both with sentinels and asserts they are never touched.
struct alignas(4) SporepediaOnlineAsset {
  std::array<std::uint8_t, 0x18> opaque_00{};
};

static_assert(sizeof(SporepediaOnlineAsset) == 0x18,
              "0x14 + a 4-byte store is the last byte this body can write");

// Displacement accessors. Using these instead of named members is what keeps
// the model's three vptr writes falsifiable: a wrong displacement in the .cpp
// lands the store somewhere the test planted a decoy and the test sees it.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

// -- the two direct callees --------------------------------------------------
// Both are declared here and neither is defined here: this package's own model
// test defines both as observers.

// 0x00642190, called at 0x00ec4297 with NOTHING pushed. __thiscall, receiver in
// ECX, zero stack words. Its 46th instruction is a tail JMP into 0x006412A0,
// whose 4 instructions end in a bare C3.
//
// The name is the one already persisted for this address by
// reconstruction/metadata/pkg-sporepedia-safe-wave10/00642190.json
// (normalized_symbol "sporepedia_asset_destroy_00642190"). This package asserts
// nothing about that body's interior beyond the calling convention and the fact
// that it overwrites the same three vptr displacements -- both re-read from the
// image here, not taken on trust.
extern "C" void SW1_00EC4280_THISCALL sporepedia_asset_destroy_00642190(
    SporepediaOnlineAsset* asset);

// 0x00F47380, called at 0x00ec42A4 with the receiver pushed by 0x00ec42A3.
// cdecl, one stack word, caller cleanup (ADD ESP,0x4 at 0x00ec42A9). Its own
// first instruction reads that word back at [ESP+0x4] and its own body
// null-checks it before forwarding to 0x009376C0.
//
// The name is the one already used across the corpus for this address
// ("deallocate_00f47380", e.g. reconstruction/staging/pkg-app-services-wave6/
// app_services.hpp:39). Nothing this package claims about 0x00642190's
// semantics transfers to it; it is only a free-shaped port here.
extern "C" void SW1_00EC4280_CDECL deallocate_00f47380(void* block);

// -- model instrumentation ---------------------------------------------------
// The machine reads the caller's flag byte at 0x00ec429C, i.e. AFTER the
// 0x00642190 call at 0x00ec4297 has already returned. A callee (or the caller,
// through an aliased pointer) that overwrites the flag slot between those two
// addresses changes what this body does -- the original would see the new
// value, a source-level `if (delete_flags & 1)` need not.
//
// A C++ compiler is free to hoist the read of a by-value parameter, so the
// model calls this hook at exactly the machine's read point instead of reading
// the parameter inline. Left null, the hook is skipped and the parameter is
// used, which is the ordinary path. The model test installs a hook to (a) prove
// the read happens after the callee, and (b) return a different value, which is
// the only way to falsify "the body tests the incoming parameter" as opposed to
// "the body tests whatever is in the slot at 0x00ec429C".
//
// THIS IS INSTRUMENTATION, NOT A MACHINE GLOBAL. It is declared in the header
// so the test can install and read it; nothing at 0x00ec4280 touches a data
// segment, and the complete 14-instruction listing names no global address.
extern std::uint8_t (*sw1_delete_flag_read_hook)(std::uint8_t incoming);

// The body under reconstruction.
//
// __thiscall: receiver in ECX, exactly ONE ordinary stack argument occupying the
// 4-byte slot at entry_ESP+0x4, of which only its LOW BYTE is read, and
// `RET 0x4` (0xC2 04 00) proving the callee owns the cleanup. That combination
// rules out cdecl (which would need an ADD ESP in the body and a bare RET) and
// rules out fastcall (which would put the first ordinary argument in EDX).
//
// The argument is `std::uint8_t` and not `Word` because the machine reads a
// BYTE: 0x00ec429C is F6 44 24 08 01, an 0xF6 /0 form (TEST r/m8, imm8) whose
// ModRM byte 0x44 encodes a byte operand with a disp8 of +0x8. The slot is still
// four bytes wide on the stack -- RET 0x4 proves that -- but the three bytes at
// entry_ESP+0x5..0x7 are never examined by anything in this body.
//
// Return type is the receiver pointer, and that is machine-fixed rather than
// chosen: 0x00ec42AC MOV EAX,ESI is on the single exit path taken by BOTH arms
// of the branch, and ESI has held the receiver since 0x00ec4281. Ghidra's own
// decompilation agrees (`return param_1`) while its record
// (ghidra_function.return_type) says "undefined"; the listing wins.
extern "C" SporepediaOnlineAsset* SW1_00EC4280_THISCALL re_00ec4280(
    SporepediaOnlineAsset* receiver, std::uint8_t delete_flags);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ec4280
