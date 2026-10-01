// PKG-SWARM-W2-00642700 -- VA 0x00642700
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00642700, an unnamed Sporepedia member
// function at VA 0x00642700 in the `sporepedia-online` cluster.
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM.
//
//  * 0x04 and 0x08 on the receiver, 0x04 and 0x08 on the ordinary stack
//    argument, the 4-byte element stride, the single comparison word and the six
//    32-bit literals are read straight out of this body's own 114-instruction
//    listing. The listing was re-decoded from the 308 image bytes at
//    0x00642700..0x00642833 for this package and matches the committed record
//    instruction for instruction, address for address and length for length:
//
//      00642700  51                    push   ecx
//      00642701  81 79 08 46 8c 97 2b  cmp    DWORD PTR [ecx+0x8],0x2b978c46
//      00642708  0f 85 20 01 00 00     jne    0x64282e
//      0064270e  56                    push   esi
//      0064270f  57                    push   edi
//      00642710  8d 79 04              lea    edi,[ecx+0x4]
//      00642713  68 0b 73 26 a4        push   0xa426730b
//      00642718  57                    push   edi
//      00642719  e8 22 3a f1 ff        call   0x556140
//      0064271e  8b 74 24 18           mov    esi,DWORD PTR [esp+0x18]
//      00642722  8b 4e 04              mov    ecx,DWORD PTR [esi+0x4]
//      00642725  83 c4 08              add    esp,0x8
//      00642728  89 44 24 08           mov    DWORD PTR [esp+0x8],eax
//      0064272c  3b 4e 08              cmp    ecx,DWORD PTR [esi+0x8]
//      0064272f  73 0e                 jae    0x64273f
//      00642731  8d 51 04              lea    edx,[ecx+0x4]
//      00642734  89 56 04              mov    DWORD PTR [esi+0x4],edx
//      00642737  85 c9                 test   ecx,ecx
//      00642739  74 11                 je     0x64274c
//      0064273b  89 01                 mov    DWORD PTR [ecx],eax
//      0064273d  eb 0d                 jmp    0x64274c
//      0064273f  8d 44 24 08           lea    eax,[esp+0x8]
//      00642743  50                    push   eax
//      00642744  51                    push   ecx
//      00642745  8b ce                 mov    ecx,esi
//      00642747  e8 54 31 e1 ff        call   0x4558a0
//      0064274c  68 0c 08 56 ad        push   0xad56080c
//      00642751  57                    push   edi
//      00642752  e8 e9 39 f1 ff        call   0x556140
//      00642757  8b 4e 04              mov    ecx,DWORD PTR [esi+0x4]
//      0064275a  83 c4 08              add    esp,0x8
//      0064275d  89 44 24 10           mov    DWORD PTR [esp+0x10],eax
//      00642761  3b 4e 08              cmp    ecx,DWORD PTR [esi+0x8]
//      00642764  73 0e                 jae    0x642774
//      00642766  8d 51 04              lea    edx,[ecx+0x4]
//      00642769  89 56 04              mov    DWORD PTR [esi+0x4],edx
//      0064276c  85 c9                 test   ecx,ecx
//      0064276e  74 11                 je     0x642781
//      00642770  89 01                 mov    DWORD PTR [ecx],eax
//      00642772  eb 0d                 jmp    0x642781
//      00642774  8d 44 24 10           lea    eax,[esp+0x10]
//      00642778  50                    push   eax
//      00642779  51                    push   ecx
//      0064277a  8b ce                 mov    ecx,esi
//      0064277c  e8 1f 31 e1 ff        call   0x4558a0
//      00642781  68 11 a3 1f f7        push   0xf71fa311
//      00642786  57                    push   edi
//      00642787  e8 b4 39 f1 ff        call   0x556140
//      0064278c  8b 4e 04              mov    ecx,DWORD PTR [esi+0x4]
//      0064278f  83 c4 08              add    esp,0x8
//      00642792  89 44 24 10           mov    DWORD PTR [esp+0x10],eax
//      00642796  3b 4e 08              cmp    ecx,DWORD PTR [esi+0x8]
//      00642799  73 0e                 jae    0x6427a9
//      0064279b  8d 51 04              lea    edx,[ecx+0x4]
//      0064279e  89 56 04              mov    DWORD PTR [esi+0x4],edx
//      006427a1  85 c9                 test   ecx,ecx
//      006427a3  74 11                 je     0x6427b6
//      006427a5  89 01                 mov    DWORD PTR [ecx],eax
//      006427a7  eb 0d                 jmp    0x6427b6
//      006427a9  8d 44 24 10           lea    eax,[esp+0x10]
//      006427ad  50                    push   eax
//      006427ae  51                    push   ecx
//      006427af  8b ce                 mov    ecx,esi
//      006427b1  e8 ea 30 e1 ff        call   0x4558a0
//      006427b6  68 cb 28 b5 be        push   0xbeb528cb
//      006427bb  57                    push   edi
//      006427bc  e8 7f 39 f1 ff        call   0x556140
//      006427c1  8b 4e 04              mov    ecx,DWORD PTR [esi+0x4]
//      006427c4  83 c4 08              add    esp,0x8
//      006427c7  89 44 24 10           mov    DWORD PTR [esp+0x10],eax
//      006427cb  3b 4e 08              cmp    ecx,DWORD PTR [esi+0x8]
//      006427ce  73 0e                 jae    0x6427de
//      006427d0  8d 51 04              lea    edx,[ecx+0x4]
//      006427d3  89 56 04              mov    DWORD PTR [esi+0x4],edx
//      006427d6  85 c9                 test   ecx,ecx
//      006427d8  74 11                 je     0x6427eb
//      006427da  89 01                 mov    DWORD PTR [ecx],eax
//      006427dc  eb 0d                 jmp    0x6427eb
//      006427de  8d 44 24 10           lea    eax,[esp+0x10]
//      006427e2  50                    push   eax
//      006427e3  51                    push   ecx
//      006427e4  8b ce                 mov    ecx,esi
//      006427e6  e8 b5 30 e1 ff        call   0x4558a0
//      006427eb  68 d3 da b6 2d        push   0x2db6dad3
//      006427f0  57                    push   edi
//      006427f1  e8 4a 39 f1 ff        call   0x556140
//      006427f6  8b 4e 04              mov    ecx,DWORD PTR [esi+0x4]
//      006427f9  83 c4 08              add    esp,0x8
//      006427fc  89 44 24 10           mov    DWORD PTR [esp+0x10],eax
//      00642800  3b 4e 08              cmp    ecx,DWORD PTR [esi+0x8]
//      00642803  73 14                 jae    0x642819
//      00642805  8d 51 04              lea    edx,[ecx+0x4]
//      00642808  89 56 04              mov    DWORD PTR [esi+0x4],edx
//      0064280b  85 c9                 test   ecx,ecx
//      0064280d  74 17                 je     0x642826
//      0064280f  5f                    pop    edi
//      00642810  89 01                 mov    DWORD PTR [ecx],eax
//      00642812  b0 01                 mov    al,0x1
//      00642814  5e                    pop    esi
//      00642815  59                    pop    ecx
//      00642816  c2 04 00              ret    0x4
//      00642819  8d 44 24 10           lea    eax,[esp+0x10]
//      0064281d  50                    push   eax
//      0064281e  51                    push   ecx
//      0064281f  8b ce                 mov    ecx,esi
//      00642821  e8 7a 30 e1 ff        call   0x4558a0
//      00642826  5f                    pop    edi
//      00642827  b0 01                 mov    al,0x1
//      00642829  5e                    pop    esi
//      0064282a  59                    pop    ecx
//      0064282b  c2 04 00              ret    0x4
//      0064282e  32 c0                 xor    al,al
//      00642830  59                    pop    ecx
//      00642831  c2 04 00              ret    0x4
//
//    Those 308 bytes decode to exactly these 114 instructions and stop on
//    0x00642833 + 1, with INT3 padding at 0x00642834 -- which is what fixes the
//    body extent independently of the committed record (body_start 0x00642700,
//    body_end 0x00642833, body_span_bytes 308, size_bytes 308; all four agree).
//    0x00642700 + 308 = 0x00642834 is the first padding byte, and the listing's
//    last instruction, `ret 0x4` at 0x00642831, is 3 bytes long and ends at
//    0x00642833 inclusive. Nothing depends on a correction here; the record and
//    the image agree, and that is stated rather than assumed.
//
//  * The TWO-OBJECT LAYOUT is not shown by this body alone, and the split is
//    worth spelling out because the two objects are read very differently:
//
//    (a) The receiver, reached through ECX and through the EDI alias formed at
//        0x00642710. This body reads exactly two words of it: the word at +0x08,
//        compared against a fixed literal (0x00642701), and the ADDRESS of its
//        own +0x04 (0x00642710, then pushed as the first argument of 0x00556140
//        five times). It writes none of it. So the receiver's run ends one byte
//        past the word at +0x08, i.e. 12 bytes, and NOTHING is named for any
//        byte of it -- not even the two words the body does touch. The
//        machine-derived receiver record enumerates offsets [8] with
//        bounds_only true, so a member name would be a claim the record can
//        neither confirm nor refute. The same record does NOT enumerate 0x04,
//        and a complete listing outranks a record that declares itself
//        incomplete; the model accounts for 0x04 from the listing instead.
//
//    (b) The ordinary stack argument, reached through ESI. This body reads the
//        word at its +0x04, compares it against the word at its +0x08, writes
//        the word at its +0x04, and stores through the value the word at +0x04
//        holds. So its run is also 12 bytes, its +0x04 and +0x08 are the only
//        two words it touches, and neither is named.
//
//  * 0x004558a0 -- the one callee that is handed this argument object as its
//    receiver -- reads and writes +0x00, +0x04 and +0x08 of it. Those offsets
//    are recorded in the sidecar as words, not as members, and are not in the
//    type below. Nothing in this set says what any of the three words is FOR.
//
//  * The two-level argument structure of 0x00556140 is a real finding, not an
//    assumption. 0x00556140's own first two instructions after its frame setup
//    are 0x55614d `MOV EAX,DWORD PTR [EBP+0x8]` and 0x556150
//    `CMP DWORD PTR [EAX+0x4],0x2b978c46` -- it reads the SECOND word of the
//    object it was handed, and compares it against the very literal this body
//    compares its own +0x08 against. Since this body hands it its own +0x04, the
//    receiver's +0x08 IS that object's +0x04, and the two spellings are the same
//    address. The receiver's magic word is therefore the descriptor's second
//    word, and `kDescriptorMagicDisplacement` is that identity rather than a
//    second guess about the receiver.
//
//  * The class name is INFERRED, not machine-fixed. This target's own record
//    carries name "FUN_00642700" and class_type null. The Sporepedia association
//    comes from vtable co-membership: this body's data-side xrefs are at
//    0x013ff6d4, 0x014627e4, 0x0147ca84, 0x0147cb4c, 0x0148911c, 0x0148943c
//    and 0x00dd1209, and the tables at 0x013ff648, 0x013ff6ac and 0x01462764
//    are the same ones the record lists as the match basis for the reconstructed
//    neighbours 0x00641400, 0x00641460, 0x00641770, 0x006417b0, 0x006417c0,
//    0x00641810, 0x00641820 and 0x00641850, every one of which the repository
//    research queue names Sporepedia::cSPAssetDataOTDB::*.
//
//  * Nothing here is read as a value when the machine reads a pointer to it, or
//    as a pointer when the machine reads a value. The two places that could go
//    wrong are the word at the argument's +0x04 -- loaded as a plain word at
//    0x00642722 and then STORED THROUGH at 0x0064273b, so it is a pointer held
//    in a word, not a word -- and the address the body hands 0x00556140, which
//    is formed by `LEA` (0x00642710) and pushed, so it is a pointer to the
//    receiver's own +0x04 and not the word at the receiver's +0x00.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00642700 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare
// MSVC keywords outright on this target, so the x86-32 attribute form is the
// portable spelling and the keyword form is kept for MSVC. Both are asserted by
// machine facts read out of the three bodies' own bytes, not chosen for
// convenience:
//
//   PKG_SWARM_W2_00642700_THISCALL  this body, and 0x004558a0.
//     This body: the receiver arrives in ECX and is dereferenced there at
//     0x00642701 before any definite write, aliased into EDI at 0x00642710, and
//     both exits end in the callee-owned form `C2 04 00` (0x00642816, 0x0064282b
//     and 0x00642831), so the callee pops the one argument word. That is what
//     rules out cdecl: a cdecl body would have to drop the word itself and none
//     of the three exits does an ADD ESP. 0x004558a0 ends `C2 08 00` at
//     0x00455ad4 and takes its receiver in ECX (0x004558a7 stores ECX), so it
//     owns its two argument words too.
//   PKG_SWARM_W2_00642700_CDECL  0x00556140.
//     It ends a bare `C3` at 0x0055620a -- no immediate, so the cleanup is zero
//     bytes -- and its own body drops each of its callees' arguments itself
//     (0x00556172 `ADD ESP,0x4`, 0x005561df `ADD ESP,0x4`), which is cdecl
//     behaviour throughout. It never reads ECX. The caller-side half is
//     0x00642725/0x0064275a/0x0064278f/0x006427c4/0x006427f9, five identical
//     `ADD ESP,0x8`, one per call: two pushed words each, and that is the
//     arithmetic that settles the convention independently of the callee.
#if defined(_MSC_VER)
#define PKG_SWARM_W2_00642700_THISCALL __thiscall
#define PKG_SWARM_W2_00642700_CDECL __cdecl
#else
#define PKG_SWARM_W2_00642700_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W2_00642700_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00642700 {

using Word = std::uint32_t;

// The object the body forms at the receiver's own +0x04 (0x00642710) and hands
// to 0x00556140 as its first argument, five times. Nothing is named: this body
// only ever hands the ADDRESS of the object over, never a word inside it, and
// the one word of it this package's evidence can place (the second, at its own
// +0x04, from 0x00556150) is the receiver's own comparison word, which the
// receiver's displacement already says. Eight bytes is the run the receiver's
// own two displacements span.
struct alignas(4) SporepediaTypeDescriptor {
  std::array<std::uint8_t, 0x08> opaque_00;  // receiver +0x04 .. +0x0b
};

// The receiver. This body reads two words of it and writes none:
//
//   00642701  CMP  DWORD PTR [ECX + 0x8],0x2b978c46   the gate
//   00642710  LEA  EDI,[ECX + 0x4]                    the lookup base, five pushes
//
// The machine-derived receiver record enumerates offsets [8] with register ECX
// and bounds_only true -- it states where the body was seen reaching and not
// which member is which. So this type declares NO member: calling the word at
// +0x08 a "magic", a "type id" or a "tag" would be a member story this body's
// evidence does not carry, even though the comparison word is a fact.
struct alignas(4) SporepediaTypeKeySource {
  std::array<std::uint8_t, 0x0c> opaque_00;  // +0x00 .. +0x0b
};

// The ordinary stack argument -- the object the body appends to. It is reached
// through ESI only, and this body touches two words of it:
//
//   00642722  MOV  ECX,[ESI + 0x4]      the cursor, re-read before EVERY append
//   0064272c  CMP  ECX,[ESI + 0x8]      against the capacity, UNSIGNED (JNC)
//   00642734  MOV  [ESI + 0x4],EDX      the cursor is advanced by one element
//   0064273b  MOV  [ECX],EAX            the element itself, when the cursor is
//                                      not null
//
// The word at +0x04 is read as a plain dword and then STORED THROUGH, so it is a
// pointer held in a word. The word at +0x08 is only ever compared, never stored
// through, so it is a bound and not a pointer. No member is named for either.
struct alignas(4) SporepediaTypeKeyVector {
  std::array<std::uint8_t, 0x0c> opaque_00;  // +0x00 .. +0x0b
};

static_assert(sizeof(void*) == 4, "this package is the 32-bit pointer model");
static_assert(offsetof(SporepediaTypeKeySource, opaque_00) == 0,
              "the receiver starts at its own +0x00");
static_assert(sizeof(SporepediaTypeKeySource) == 0x0c, "0x08 + 4 is the last byte the body touches");
static_assert(sizeof(SporepediaTypeDescriptor) == 0x08, "the descriptor run is the receiver's 0x04..0x0b");
static_assert(sizeof(SporepediaTypeKeyVector) == 0x0c, "0x08 + 4 is the last byte the body touches");

// The displacements this body was seen reaching, as values.
//
//  * On the receiver: 0x08 is the gate word (0x00642701) and 0x04 is the lookup
//    base (0x00642710). Both are the receiver's; the record enumerates only the
//    first and declares itself incomplete.
//  * On the descriptor: 0x04 is the gate word again (0x00556150 in the callee's
//    own body), which is the same address as the receiver's 0x08 because the
//    descriptor is the receiver's own +0x04.
//  * On the vector: 0x04 is the cursor (0x00642722, 0x00642734) and 0x08 is the
//    capacity (0x0064272c, 0x00642761). 0x00 is touched by 0x004558a0 only
//    (0x004558b0, 0x004558f6, 0x004558ab6) and never by this body, so it is
//    recorded as a word and not declared.
//  * The element stride, 4 bytes, is fixed by 0x00642731 `LEA EDX,[ECX + 0x4]`
//    and by the five `MOV DWORD PTR [ECX],EAX` stores that go with it.
constexpr std::size_t kSourceGateDisplacement = 0x08;
constexpr std::size_t kSourceLookupBaseDisplacement = 0x04;
constexpr std::size_t kDescriptorGateDisplacement = 0x04;
constexpr std::size_t kVectorCursorDisplacement = 0x04;
constexpr std::size_t kVectorCapacityDisplacement = 0x08;
constexpr std::size_t kVectorBeginDisplacement = 0x00;
constexpr std::size_t kVectorElementStride = 0x04;

// The one comparison word. It is the immediate of 0x00642701, and it is the
// immediate 0x00556150 compares the descriptor's second word against, so the two
// tests are the same test on the same address reached two ways.
constexpr Word kSourceGateWord = 0x2b978c46u;

// The only way the body under reconstruction touches any of the above: a word at
// a stated displacement. A named member access would assert an identity the
// machine-derived receiver record cannot corroborate -- it is bounds_only, with
// offsets [8] -- so every access below goes through a displacement instead.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// The same read, as an lvalue, for the one store the body makes into the
// argument (the cursor, 0x00642734 and its four siblings).
inline Word& word_ref(void* base, std::size_t displacement) {
  return *word_at(base, displacement);
}

// A word at a displacement, read as the ADDRESS it holds. 0x00642722 loads a
// plain dword and 0x0064273b stores through it, so the model loads a word and
// reinterprets it and does nothing else: no sign extension, no range check, no
// dereference of its own. The value may be null, which is exactly the case
// 0x00642737's `TEST ECX,ECX` exists to survive.
inline Word* load_pointer(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(static_cast<std::uintptr_t>(*word_at(base, displacement)));
}

// -- the two direct callees --------------------------------------------------
// Each is declared here, and neither is defined here: the model test defines
// both as observers. Every signature below is fixed by the callee's own bytes,
// re-read from the image for this package, and by the call site's own push
// sequence -- not by any decompilation.

// 0x00556140, called five times, at 0x00642719, 0x00642752, 0x00642787,
// 0x006427bc and 0x006427f1.
//
// Convention: cdecl. Its body ends a bare `C3` at 0x0055620a, so it pops no
// arguments, and the caller drops the two words itself at 0x00642725 (and at
// 0x0064275a, 0x0064278f, 0x006427c4, 0x006427f9) with `ADD ESP,0x8`.
// ECX is never read.
//
// Arguments, from the push pairs: the SECOND word pushed is the receiver's own
// +0x04 (0x00642710 forms it in EDI and 0x00642718, 0x00642751, 0x00642786,
// 0x006427bb and 0x006427f0 push it) and the FIRST word pushed is the call's
// distinct 32-bit literal, read back by the callee as its second argument
// (0x005561e2 `CMP EAX,DWORD PTR [EBP+0xc]`). So this is
// lookup(descriptor, key) with the key second on the stack, and the descriptor
// first.
//
// Return: one word, returned from the frame slot 0x00556204 reads and
// 0x00556207 hands back in EAX. It is a pointer (or null: the slot is zeroed at
// 0x00556146 and the two rejected magic paths jump straight to the return), and
// THIS body only ever stores it -- it is never dereferenced here, which the
// model test drives with a deliberately unmapped return value.
extern "C" void* PKG_SWARM_W2_00642700_CDECL sporepedia_type_lookup_00556140(
    SporepediaTypeDescriptor* descriptor, Word key);

// 0x004558a0, called on the slow arm of each of the five appends, at
// 0x00642747, 0x0064277c, 0x006427b1, 0x006427e6 and 0x00642821.
//
// Convention: __thiscall. Its body opens `PUSH EBP / MOV EBP,ESP / SUB ESP,0x60
// / PUSH ESI` (0x004558a0..0x004558a6), stashes ECX at 0x004558a7, and ends
// `POP ESI / MOV ESP,EBP / POP EBP / RET 0x8` at 0x00455ad0..0x00455ad4, so it
// owns its two argument words.
//
// Arguments, from the call site: the receiver is the argument object itself,
// not the receiver of this body -- 0x00642745 / 0x0064277a / 0x006427af /
// 0x006427e4 / 0x0064281f all do `MOV ECX,ESI`. The FIRST stack word is the
// vector's own cursor as loaded at 0x00642722 and its four siblings (pushed at
// 0x00642744 and its four siblings), which the callee reads at 0x004558bc
// (`MOV EAX,DWORD PTR [EBP+0x8]`) and STORES THROUGH at 0x00455959
// (`MOV DWORD PTR [EDX],ECX`). The SECOND stack word is the ADDRESS of the
// value, formed by `LEA` at 0x0064273f / 0x00642774 / 0x006427a9 / 0x006427de /
// 0x00642819 and pushed at 0x00642743 and its four siblings, which the callee
// reads at 0x00455957 (`MOV ECX,[EAX]`). The order is therefore
// insert_at_end(self, cursor, &value) and it is fixed by the callee's own two
// reads, not by this body's push order alone.
//
// Return: dead on every arm. The instruction after each of the five calls
// either re-derives a value (0x00642752, 0x00642787, 0x006427bc, 0x006427f1
// are themselves calls) or writes the result byte directly (0x00642827
// `MOV AL,0x1`), so nothing this callee leaves in EAX is ever read. The
// declared return type is void and the model test asserts nothing about it.
extern "C" void PKG_SWARM_W2_00642700_THISCALL sporepedia_vector_insert_004558a0(
    SporepediaTypeKeyVector* self, Word* cursor, const Word* value);

// FUN_00642700 @ 0x00642700.
//
// __thiscall, receiver in ECX, exactly ONE ordinary stack argument, callee-owned
// cleanup of 4 bytes (`RET 0x4` on all three exits: 0x00642816, 0x0064282b,
// 0x00642831), two saved registers (ESI pushed at 0x0064270e and EDI at
// 0x0064270f, both popped on every exit). The argument count is not a guess and
// the frame arithmetic that fixes it is in the .cpp: the body reads its single
// argument with `MOV ESI,[ESP+0x18]` at 0x0064271e, and the value slot the first
// lookup's result is parked in is the slot `PUSH ECX` had just filled, i.e. the
// receiver itself is never recovered and no second argument exists.
//
// Return type is bool. The listing writes ONLY AL on every path -- `XOR AL,AL`
// at 0x0064282e, `MOV AL,0x1` at 0x00642812 and at 0x00642827 -- so the upper
// three bytes of EAX are undefined on every exit and one byte is the width the
// machine actually fixes. The machine ABI record's own claim is the string
// "integral_in_EAX" (abi.return_semantics, and abi_derived inference RT2
// register_class "integral"), which is a claim about the REGISTER rather than
// about a C type and which no C++ type can be spelled to match; the
// disagreement is recorded rather than papered over. See the sidecar's
// unresolved_questions and implementation.return_type.
extern "C" bool PKG_SWARM_W2_00642700_THISCALL sporepedia_append_five_lookups_00642700(
    SporepediaTypeKeySource* receiver, SporepediaTypeKeyVector* vector);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00642700
