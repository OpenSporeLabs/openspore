// PKG-SWARM-W2-005A2600 -- VA 0x005a2600
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, offsets and call-boundary declarations for FUN_005a2600, the 450-instruction
// property-harvesting member at 0x005a2600 (body span 0x005a2600..0x005a2b20 inclusive,
// 1313 bytes, 5 return sites, 28 indirect transfers and 2 direct ones).
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM. The target is the
// largest single body in the frontier, so the split between "this body's own listing"
// and "some other body's listing" is spelled out in full and every claim is charged
// to one of the four sources below.
//
// 1. IN THIS BODY'S OWN 450-INSTRUCTION LISTING (complete body span
//    0x005a2600..0x005a2b20 inclusive; 450 instructions; re-derived from the image
//    bytes and identical to the committed listing instruction for instruction, at the
//    same addresses -- see the .cpp for the blocks). From those instructions alone:
//
//      * the frame: three pushes and no SUB ESP, so ESP sits at entry-12 for the whole
//        body (0x005a2600 PUSH ECX / 0x005a2601 PUSH EBX / 0x005a2602 PUSH ESI) and
//        returns at entry with POP ESI / POP EBX / POP ECX and a bare RET at each of
//        the five terminators (0x005a2ad5, 0x005a2af1, 0x005a2b0f, 0x005a2b20 and the
//        shared epilogue the other three fall into). Zero bytes of callee cleanup;
//      * the ONE stack slot the body ever addresses: [ESP+0x8] == entry-4, which is
//        exactly where 0x005a2600's PUSH ECX put the incoming receiver. It is taken by
//        address at 0x005a2a34 and 0x005a2a65 (LEA EDX,[ESP+0x8]) and read back at
//        0x005a2a44 and 0x005a2a75 (MOV ECX,[ESP+0x8]). So the two out-parameters of
//        the two +0x24 slot calls are the same word, the clobbered saved receiver;
//      * the receiver displacement set, 23 displacements through the ESI alias that
//        0x005a2603 (MOV ESI,ECX) makes: 0x10 read seventeen times and twenty-two
//        displacements written (twenty-one 4-byte float stores plus one byte store at
//        0x9c). The machine-derived receiver record enumerates exactly those 23
//        ([16,20,24,28,40,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,156],
//        max_offset 156, register ECX, shape R-ALIAS, written_through 18,
//        bounds_only true), so every one of them is grounded and none is named;
//      * the fifteen key-id immediates, the three slot displacements (0x1c, 0x24, 0x28),
//        the two type tags (0xd, 0x10), the indirect mask 0x30, the tag-word
//        displacement 0x12, the flag-byte displacement 0x10 and the record's own
//        leading word;
//      * the four-part shape of the record-reading idiom, repeated verbatim twelve
//        times, and the two data addresses it falls back on (0x015d1168, a 0.0f, and
//        the two .rdata reciprocals 0x013f6960 and 0x013f6964);
//      * the terminator: a bare RET, i.e. caller-owned cleanup of zero bytes.
//
// 2. FROM THE IMAGE AT 0x0041ea70 (0x61 bytes read at file offset 0x1de70). This is
//    this body's ONE direct callee, called twice (0x005a2a4f and 0x005a2a80), and its
//    own bytes are:
//
//      0041ea70  55 8B EC 83 EC 08     PUSH EBP; MOV EBP,ESP; SUB ESP,8
//      0041ea76  89 4D F8              MOV [EBP-8],ECX        <- its argument
//      0041ea7c  0F B7 48 12           MOVZX ECX,WORD [EAX+0x12]
//      0041ea80  83 F9 0D              CMP ECX,0xd      ; JE
//      0041ea8C  83 F8 10              CMP EAX,0x10     ; JNE 0041eac8
//      0041ea94  0F B7 51 10           MOVZX EDX,WORD [ECX+0x10]   <- WORD, not byte
//      0041ea98  83 E2 30              AND EDX,0x30     ; JE
//      0041eaA0  8B 08                 MOV ECX,[EAX]            <- one dereference
//      0041eAAC  0F B7 42 12           MOVZX EAX,WORD [EDX+0x12]
//      0041eAB0  85 C0                 TEST EAX,EAX     ; JE 0041eabc
//      0041eABC  C7 45 FC 00 00 00 00  MOV [EBP-4],0x0
//      0041eac3  8B 45 FC              MOV EAX,[EBP-4]
//      0041eac8  B8 68 11 5D 01        MOV EAX,0x15d1168
//      0041ead0  C3                    RET
//
//    So it is a one-ECX-argument function returning a POINTER TO A FLOAT, it pops no
//    stack argument, and it is the same idiom this body inlines twelve times -- with
//    two differences this package does NOT propagate into the model of 0x005a2600,
//    because this body's own bytes say otherwise and the listing governs:
//
//      (a) 0x0041ea94 tests the WORD at the record's +0x10, while this body tests the
//          BYTE there (TEST BYTE PTR [EAX+0x10],BL at 0x005a2647 and eleven more,
//          with BL = 0x30 from 0x005a261b). The two disagree whenever bit 0x10 or bit
//          0x20 of the byte at the record's +0x11 is set;
//      (b) 0x0041eabc returns NULL when the type word is zero, while this body's
//          inlined copy computes ECX = 0 (MOVZX/NEG/SBB/AND at 0x005a2650..0x005a2657)
//          and would fault on FLD -- unreachable here, because this body only reaches
//          that copy with a type word of 0xd or 0x10, both non-zero.
//
//    The repository already carries a name for this address:
//    reconstruction/staging/pkg-palette-wave11/pkg_palette_wave11.hpp line 377 declares
//    `const float* PKG_PALETTE_W11_THISCALL unresolved_0041ea70(OpaqueProperty*);`.
//    That name and that signature are used here so this package does not invent a
//    competing one. No record in this repository says what it is for.
//
// 3. FROM THE IMAGE AT 0x015d1168 and 0x013f6960/0x013f6964 (section headers walked,
//    then the bytes read at the mapped file offsets 0x11cfb68 and 0xff5d60/0xff5d64):
//
//      0x015d1168 = 0x00000000  -> 0.0f  (the .data word is zero-initialised)
//      0x013f6960  35 FA 8E 3C  ->  0x3C8EFA35  ->  0.01745329238474369f
//      0x013f6964  E1 2E 65 42  ->  0x42652EE1  ->  57.295780181884766f
//
//    Read together with 0x013f6968  54 F8 2D 40  ->  0x402DF854  ->  2.7182817459106445f
//    and 0x013f696c  DB 0F 49 40  ->  0x40490FDB  ->  3.1415927410125732f, these four
//    are a contiguous
//    degrees-to-radians / radians-to-degrees / e / pi block in .rdata, which is the
//    only reason this package is willing to write the two reciprocals down as the
//    constants of the two multiplies rather than as unnamed .rdata words. No record
//    names them.
//
// 4. NOT CLAIMED, ANYWHERE, BY THIS HEADER:
//
//      * a class name. The triage cluster says "editor-core" and the subsystem says
//        "Editor"; no MSVC RTTI survives in this binary and no record names the class.
//        The type below is called EditorTransform005a2600 for readability and nothing
//        more. The machine does place this body at slot +0x64 of the table whose head
//        is 0x013f69b4 (the word at 0x013f6a18 is 0x005a2600), and the two analogue
//        records name that same table for 0x005a2050 and 0x005a2320; that is recorded
//        here for the integrator and is NOT modelled, because the body never reads the
//        receiver's own +0x00 as a table word. What it DOES read as a table word is
//        the object it holds at its +0x10, and the three slot displacements below come
//        from that object's first word, not from this body's own table.
//      * a layout for the twenty-one float displacements. They are 0x14, 0x18, 0x1c,
//        0x28, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0x58, 0x5c,
//        0x60, 0x64, 0x68, 0x6c, 0x70. Ten of them come in pairs a fixed 0x14 apart and
//        one id writes three of them, which is consistent with two or three parallel
//        float runs -- and no record in this repository says so. Each displacement is
//        therefore named after the key id that writes it, and the pairing is reported
//        as an observation in the metadata sidecar, never used by the model.
//      * the size of the object. This body touches no byte beyond +0x9c, so the model
//        gives the run 0x9d bytes and asserts nothing beyond it. Sibling slots of the
//        same table may well read further; nothing here is claimed about that.
//      * what the key ids MEAN. They are 32-bit hashed names and this package has no
//        preimage for any of the fifteen. None is named.
//      * what the byte at the receiver's +0x9c means. It is cleared once, on entry,
//        before any other receiver access, and nothing in this body ever sets it.
//      * the class of the record the +0x28 slot returns. This body reads three
//        displacements of it (0x00, 0x10, 0x12) and nothing else, so the model reaches
//        it by displacement too and calls it a record, not a type.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-005a2600 requires an x86-32 target"
#endif

// One convention is needed and it is fixed by machine bytes, not chosen for
// convenience:
//
//   PKG_SWARM_W2_005A2600_THISCALL  receiver in ECX, no stack argument popped.
//
// This body's own terminator is a bare RET (0x005a2ad5, 0x005a2af1, 0x005a2b0f,
// 0x005a2b20) and the receiver is copied out of ECX at 0x005a2603 before ECX is
// reused as a scratch register sixteen times, so this body's own argument surface is
// the hidden receiver alone. Its one direct callee 0x0041ea70 ends C3 with no
// immediate and takes its only argument in ECX (0x0041ea76). The three slot callees
// the body reaches indirectly are declared with the same convention because each of
// the three is entered as CALL EAX/EDX immediately after a PUSH of its stack word or
// two and the body never adjusts ESP afterwards, which fixes callee-owned cleanup.
#if defined(_MSC_VER)
#define PKG_SWARM_W2_005A2600_THISCALL __thiscall
#else
#define PKG_SWARM_W2_005A2600_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_005a2600 {

using Word = std::uint32_t;
using Half = std::uint16_t;
using Byte = std::uint8_t;

// -- the receiver, as an opaque byte run with NO members ---------------------
//
// Declared without members on purpose. The machine-derived receiver record is
// bounds_only: it says how far the body was seen reaching, not which member is
// which, so naming a member would assert an identity no evidence in this pack can
// confirm. The displacement accessors below are used instead, so that a wrong
// displacement in the .cpp lands a store on a byte the model test filled with a
// decoy rather than looking like a plausible field write.
struct alignas(4) EditorTransform005a2600 {
  std::array<Byte, 0xa0> opaque_run{};
};

// 0x9c plus the one byte written there is 0x9d, the last byte this body can touch;
// the run is rounded to 0xa0 because the receiver type is alignas(4). The three
// bytes above the last one the body writes are padding this model adds, not bytes
// anything in the listing reads or writes.
static_assert(sizeof(EditorTransform005a2600) == 0xa0u,
              "the opaque run covers every byte this body can touch, rounded up to 4");

// The receiver's displacements, each one named after the instruction that fixes it.
// The two that are not written per key id come first.
constexpr std::size_t kOffSourceObject = 0x10u;  // 0x005a2605 MOV ECX,[ESI+0x10]
constexpr std::size_t kOffEntryFlag = 0x9cu;     // 0x005a2608 MOV BYTE [ESI+0x9c],0

constexpr std::size_t kDispForIdC7c4f8 = 0x14u;  // 0x005a265b FSTP [ESI+0x14]
constexpr std::size_t kDispForIdC7c4fa = 0x18u;  // 0x005a26ab FSTP [ESI+0x18]
constexpr std::size_t kDispForIdC7c4f9 = 0x1cu;  // 0x005a26fb FSTP [ESI+0x1c]

constexpr std::size_t kDispForIdC7c4fb = 0x28u;      // 0x005a274d MOVSS [ESI+0x28]
constexpr std::size_t kDisp2ForIdC7c4fb = 0x38u;     // 0x005a2752 MOVSS [ESI+0x38]
constexpr std::size_t kDisp3ForIdC7c4fb = 0x4cu;     // 0x005a2757 MOVSS [ESI+0x4c]
constexpr std::size_t kDispForIdC7c4fc = 0x34u;      // 0x005a27b3 MOVSS [ESI+0x34]
constexpr std::size_t kDisp2ForIdC7c4fc = 0x48u;     // 0x005a27b8 MOVSS [ESI+0x48]
constexpr std::size_t kDispForIdC7c4fd = 0x30u;      // 0x005a2814 MOVSS [ESI+0x30]
constexpr std::size_t kDisp2ForIdC7c4fd = 0x44u;     // 0x005a2819 MOVSS [ESI+0x44]
constexpr std::size_t kDispForId6fda2e1c = 0x3cu;    // 0x005a286d MOVSS [ESI+0x3c]
constexpr std::size_t kDisp2ForId6fda2e1c = 0x50u;   // 0x005a2872 MOVSS [ESI+0x50]
constexpr std::size_t kDispForId8fda2e23 = 0x40u;    // 0x005a28c6 MOVSS [ESI+0x40]
constexpr std::size_t kDisp2ForId8fda2e23 = 0x54u;   // 0x005a28cb MOVSS [ESI+0x54]

constexpr std::size_t kDispForIdFe23b2 = 0x58u;      // 0x005a291d FSTP [ESI+0x58]
constexpr std::size_t kDispForIdFe2437 = 0x5cu;      // 0x005a296d FSTP [ESI+0x5c]
constexpr std::size_t kDispForIdFe243b = 0x60u;      // 0x005a29c7 MOVSS [ESI+0x60]
constexpr std::size_t kDispForIdFe243f = 0x64u;      // 0x005a2a23 MOVSS [ESI+0x64]
constexpr std::size_t kDispForId1102b20 = 0x68u;     // 0x005a2a56 FSTP [ESI+0x68]
constexpr std::size_t kDispForId1102b2f = 0x6cu;     // 0x005a2a87 FSTP [ESI+0x6c]
constexpr std::size_t kDispForId44c6220 = 0x70u;     // 0x005a2acd/0x005a2ae9/0x005a2b07/0x005a2b18

// -- the object's own displacement set (NOT the receiver's) -------------------
//
// The object the receiver holds at its +0x10. The three slot displacements are the
// only three words of its table this body ever reads, and the record-reading idiom
// reaches three displacements of the record the +0x28 slot hands back. All of them
// are the object's or the record's, none is a receiver field, and the model reaches
// all of them through the same displacement accessors for the same reason.
constexpr std::size_t kObjSlotHasQuery = 0x1cu;    // 0x005a2611 MOV EDX,[EAX+0x1c]
constexpr std::size_t kObjSlotFindQuery = 0x24u;   // 0x005a2a31 MOV EAX,[EAX+0x24]
constexpr std::size_t kObjSlotGetQuery = 0x28u;    // 0x005a2626 MOV EDX,[EAX+0x28]
constexpr std::size_t kRecValueWord = 0x00u;       // 0x005a264c MOV ECX,[EAX]
constexpr std::size_t kRecFlagByte = 0x10u;        // 0x005a2647 TEST BYTE [EAX+0x10],BL
constexpr std::size_t kRecTypeWord = 0x12u;        // 0x005a2630 MOVZX ECX,WORD [EAX+0x12]

// -- the record-reading constants --------------------------------------------
//
// The two type tags the body accepts (0x005a2634 CMP CX,0xd / 0x005a263a CMP CX,0x10,
// and eleven identical pairs), and the mask the byte at the record's +0x10 is tested
// against (BL = 0x30 from 0x005a261b, then TEST BYTE PTR [EAX+0x10],BL).
constexpr Half kTagAcceptedFirst = 0x0du;
constexpr Half kTagAcceptedSecond = 0x10u;
constexpr Byte kIndirectMask = 0x30u;
// The only tag the two +0x24 blocks accept (0x005a2a48 CMP WORD [ECX+0x12],0xd).
constexpr Half kTagFloatOnly = 0x0du;

// -- the fifteen key ids, in the order the body asks for them -----------------
// Named without an underscore before the digits on purpose: a reconstruction that
// spells a key id as <name>_<8 hex digits> is read by the validator's callee
// convention as a call target, and these immediates all fall inside the .text address
// range, so such a name would become a phantom callee claim.
constexpr Word kIdC7c4f8 = 0x00c7c4f8u;   // 0x005a2614
constexpr Word kIdC7c4fa = 0x00c7c4fau;   // 0x005a2666
constexpr Word kIdC7c4f9 = 0x00c7c4f9u;   // 0x005a26b6
constexpr Word kIdC7c4fb = 0x00c7c4fbu;   // 0x005a2706
constexpr Word kIdC7c4fc = 0x00c7c4fcu;   // 0x005a2764
constexpr Word kIdC7c4fd = 0x00c7c4fdu;   // 0x005a27c5
constexpr Word kId6fda2e1c = 0x6fda2e1cu;  // 0x005a2826
constexpr Word kId8fda2e23 = 0x8fda2e23u;  // 0x005a287f
constexpr Word kIdFe23b2 = 0x00fe23b2u;    // 0x005a28d8
constexpr Word kIdFe2437 = 0x00fe2437u;    // 0x005a2928
constexpr Word kIdFe243b = 0x00fe243bu;    // 0x005a2978
constexpr Word kIdFe243f = 0x00fe243fu;    // 0x005a29d4
constexpr Word kId1102b20 = 0x01102b20u;   // 0x005a2a39
constexpr Word kId1102b2f = 0x01102b2fu;   // 0x005a2a6a
constexpr Word kId44c6220 = 0x044c6220u;   // 0x005a2a92

// -- the three data addresses the body reads ----------------------------------
//
// Named after the address each one is, and never written as a literal inside the
// reconstructed function's own span: the body reaches all three through a single
// `FLD float ptr [ECX]` / `MOVSS XMM0,[ECX]` / `MOVSS XMM0,[0x013f6964]` operand, and
// the model reaches them by name. Their contents are fixed by the image bytes, which
// are quoted at the top of this file.
extern const float g_unmodelled_15d1168;  // 0.0f
extern const float g_unmodelled_013f6960;  // 0.01745329238474369f
extern const float g_unmodelled_013f6964;  // 57.295780181884766f

// -- displacement accessors ---------------------------------------------------
//
// Every receiver, object and record access in the .cpp goes through these, with the
// displacement written as `base + 0x..` exactly as the listing writes it. They are
// plain typed lvalue views, so a store lands on the byte the listing names and a load
// reads that byte and nothing else.
//
// ALIGNMENT. The x86 listing has no alignment requirement of its own, and the model
// imposes none either beyond what the objects it is handed already guarantee: the
// receiver type is alignas(4) and every displacement the body stores through is a
// multiple of four, and the record the +0x28 slot returns is a caller-owned object
// this package does not describe, so the model test hands it one aligned to eight.
inline std::uint8_t* raw(EditorTransform005a2600* self) {
  return reinterpret_cast<std::uint8_t*>(self);
}
inline std::uint8_t* raw(const EditorTransform005a2600* self) {
  return const_cast<std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(self));
}
inline const std::uint8_t* raw(const std::uint8_t* p) { return p; }
inline std::uint8_t* raw(std::uint8_t* p) { return p; }

inline Byte& byte_at(std::uint8_t* p) { return *p; }
inline const Byte& byte_at(const std::uint8_t* p) { return *p; }
inline Word& word_at(std::uint8_t* p) { return *reinterpret_cast<Word*>(p); }
inline Half& half_at(std::uint8_t* p) { return *reinterpret_cast<Half*>(p); }
inline float& float_at(std::uint8_t* p) { return *reinterpret_cast<float*>(p); }
inline const Word& word_at(const std::uint8_t* p) {
  return *reinterpret_cast<const Word*>(p);
}
inline const Half& half_at(const std::uint8_t* p) {
  return *reinterpret_cast<const Half*>(p);
}
inline const float& float_at(const std::uint8_t* p) {
  return *reinterpret_cast<const float*>(p);
}

// The leading dword of a record read as an ADDRESS, which is what MOV ECX,[EAX] does
// at 0x005a264c and eleven more sites: one level of indirection, never two.
inline const std::uint8_t* indirect_at(const std::uint8_t* record) {
  std::uintptr_t address = 0;
  std::memcpy(&address, record, sizeof address);
  return reinterpret_cast<const std::uint8_t*>(address);
}

// -- the three slots the body reaches indirectly ------------------------------
//
// The object at the receiver's +0x10 is a C++ object with a table: its first word is
// read (0x005a260f MOV EAX,[ECX]) and one of three displacements off that word is
// called (0x005a2611, 0x005a2626, 0x005a2a31). No record names the class, so nothing
// is claimed about it beyond those three slots. The names carry no address suffix on
// purpose: these are not direct calls, and a name ending in eight hex digits would be
// read as a direct call target that the xref export does not record.
struct ParamSource;

// slot +0x1c: PUSH id; CALL EDX; the body's only use of the result is TEST AL,AL
// (0x005a261d and twelve more). One stack word, so callee-owned cleanup.
extern "C" bool PKG_SWARM_W2_005A2600_THISCALL sw2_obj_slot_has_query(
    ParamSource* source, Word id);
// slot +0x28: PUSH id; CALL EDX; EAX is the record this body then reads at +0x00,
// +0x10 and +0x12 (0x005a2630 and eleven more). One stack word.
extern "C" const std::uint8_t* PKG_SWARM_W2_005A2600_THISCALL sw2_obj_slot_get_query(
    ParamSource* source, Word id);
// slot +0x24: PUSH &slot; PUSH id; CALL EAX (0x005a2a38/0x005a2a39/0x005a2a3e). Two
// stack words, callee-owned cleanup, AL tested, and the record handed back through the
// first-pushed pointer.
extern "C" bool PKG_SWARM_W2_005A2600_THISCALL sw2_obj_slot_find_query(
    ParamSource* source, Word id, const std::uint8_t** out);

// -- the one direct callee ----------------------------------------------------
// The repository's own name and signature for 0x0041ea70, from
// reconstruction/staging/pkg-palette-wave11/pkg_palette_wave11.hpp line 377. Its own
// 0x61 bytes (quoted at the top of this file) fix the argument in ECX and a
// pointer-to-float return; nothing in this repository says what it is for.
extern "C" const float* PKG_SWARM_W2_005A2600_THISCALL unresolved_0041ea70(
    const std::uint8_t* record);

// -- the record-reading idiom, factored out of twelve inline copies -----------
//
// Every one of the twelve copies is 21 instructions long and byte-identical apart from
// its two call sites and its one or two stores. The address ranges are
// 0x005a2621..0x005a265b, 0x005a2671..0x005a26ab, 0x005a26c1..0x005a26fb,
// 0x005a2711..0x005a2757, 0x005a276f..0x005a27b8, 0x005a27d0..0x005a2819,
// 0x005a2831..0x005a2872, 0x005a288a..0x005a28cb, 0x005a28e3..0x005a291d,
// 0x005a2933..0x005a296d, 0x005a2983..0x005a29c7 and 0x005a29df..0x005a2a23.
//
// The register the twelve copies happen to use (x87 for five of them, SSE for seven)
// is not a semantic difference: every load is a 32-bit load out of memory and every
// store is a 32-bit store to memory, so no value is ever held in extended precision
// across an operation. The model therefore loads and stores `float` and the metadata
// sidecar records the choice.
inline float param_record_float(const std::uint8_t* record) {
  const std::uint8_t* base = reinterpret_cast<const std::uint8_t*>(&g_unmodelled_15d1168);
  // 0x005a2640 MOV ECX,0x15d1168
  const Half type = half_at(record + kRecTypeWord);   // 0x005a2630
  if (type == kTagAcceptedFirst || type == kTagAcceptedSecond) {
    // 0x005a2647 TEST BYTE PTR [EAX+0x10],BL -- a BYTE test, unlike the WORD test in
    // 0x0041ea94. The two disagree when a bit of the byte at the record's +0x11 is set
    // and the model test drives exactly that case.
    base = ((byte_at(record + kRecFlagByte) & kIndirectMask) != 0) ? indirect_at(record)
                                                                  : record;
    // The other arm, 0x005a2650..0x005a2657: MOVZX ECX,CX; NEG; SBB; AND ECX,EAX is
    // (type != 0) ? record : 0, and this body only reaches it with type 0xd or 0x10,
    // so it is the record itself. The zero arm would fault on the FLD and is not
    // reachable from this body; the model says so instead of reproducing the fault.
  }
  return float_at(base);  // 0x005a2659 FLD float ptr [ECX] / MOVSS XMM0,dword ptr [ECX]
}

// -- the reconstructed entry point --------------------------------------------
// Declared here so the model test can call it; defined once, in the .cpp.
extern "C" void PKG_SWARM_W2_005A2600_THISCALL re_005a2600(EditorTransform005a2600* self);

// -- the object, as an opaque word holding an address ------------------------
inline ParamSource* source_object(std::uint8_t* receiver_base) {
  std::uintptr_t address = 0;
  std::memcpy(&address, receiver_base + kOffSourceObject, sizeof address);
  return reinterpret_cast<ParamSource*>(address);
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_005a2600
