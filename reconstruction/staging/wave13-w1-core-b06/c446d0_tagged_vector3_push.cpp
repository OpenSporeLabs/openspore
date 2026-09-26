// 0x00c446d0 — push a tagged Vector3 onto the front or back of a member vector.
//
// Original bytes (ghidra_read_memory 0x00c446d0,152 =
// 83 ec 10 8b 44 24 14 f3 0f 10 00 f3 0f 10 48 04 f3 0f 10 48 08 88 44 24 18
// 33 d2 84 c0 0f 95 c2 81 c1 f0 00 00 00 f3 0f 11 04 24 f3 0f 11 4c 24 04
// f3 0f 11 54 24 08 89 54 24 0c 84 c0 74 12 8b 11 8d 04 24 50 52 e8 05 f8
// ff ff 83 c4 10 c2 08 00 8b 41 04 3b 41 08 73 23 56 8d 70 10 89 71 04 5e
// 85 c0 74 21 f3 0f 11 00 f3 0f 11 48 04 f3 0f 11 48 08 89 50 0c 83 c4 10
// c2 08 00 8d 14 24 52 50 e8 6a f5 ff ff 83 c4 10 c2 08 00 cc cc cc cc):
//   0x00c446d0  83 ec 10                    SUB ESP, 0x10
//   0x00c446d3  8b 44 24 14                MOV EAX, dword ptr [ESP + 0x14]
//   0x00c446d7  f3 0f 10 00                MOVSS XMM0, dword ptr [EAX]
//   0x00c446db  f3 0f 10 48 04             MOVSS XMM1, dword ptr [EAX + 0x4]
//   0x00c446e0  f3 0f 10 48 08             MOVSS XMM2, dword ptr [EAX + 0x8]
//   0x00c446e5  88 44 24 18                MOV AL, byte ptr [ESP + 0x18]
//   0x00c446e9  33 d2                       XOR EDX, EDX
//   0x00c446eb  84 c0                       TEST AL, AL
//   0x00c446ed  0f 95 c2                    SETNZ DL
//   0x00c446f0  81 c1 f0 00 00 00           ADD ECX, 0xF0
//   0x00c446f6  f3 0f 11 04 24             MOVSS dword ptr [ESP], XMM0
//   0x00c446fb  f3 0f 11 4c 24 04          MOVSS dword ptr [ESP + 0x4], XMM1
//   0x00c44701  f3 0f 11 54 24 08          MOVSS dword ptr [ESP + 0x8], XMM2
//   0x00c44707  89 54 24 0c                MOV dword ptr [ESP + 0xC], EDX
//   0x00c4470b  84 c0                       TEST AL, AL
//   0x00c4470d  74 12                       JZ 0x00c44721
//   0x00c4470f  8b 11                       MOV EDX, dword ptr [ECX]
//   0x00c44711  8d 04 24                    LEA EAX, [ESP]
//   0x00c44714  50                          PUSH EAX
//   0x00c44715  52                          PUSH EDX
//   0x00c44716  e8 05f8ffff                CALL 0x00c43f20
//   0x00c4471b  83 c4 10                    ADD ESP, 0x10
//   0x00c4471e  c2 08 00                    RET 0x8
//   0x00c44721  8b 41 04                    MOV EAX, dword ptr [ECX + 0x4]
//   0x00c44724  3b 41 08                    CMP EAX, dword ptr [ECX + 0x8]
//   0x00c44727  73 23                       JNC 0x00c4474c
//   0x00c44729  56                          PUSH ESI
//   0x00c4472a  8d 70 10                    LEA ESI, [EAX + 0x10]
//   0x00c4472d  89 71 04                    MOV dword ptr [ECX + 0x4], ESI
//   0x00c44730  5e                          POP ESI
//   0x00c44731  85 c0                       TEST EAX, EAX
//   0x00c44733  74 21                       JZ 0x00c44756
//   0x00c44735  f3 0f 11 00                 MOVSS dword ptr [EAX], XMM0
//   0x00c44739  f3 0f 11 48 04              MOVSS dword ptr [EAX + 0x4], XMM1
//   0x00c4473e  f3 0f 11 48 08              MOVSS dword ptr [EAX + 0x8], XMM2
//   0x00c44743  89 50 0c                    MOV dword ptr [EAX + 0xC], EDX
//   0x00c44746  83 c4 10                    ADD ESP, 0x10
//   0x00c44749  c2 08 00                    RET 0x8
//   0x00c4474c  8d 14 24                    LEA EDX, [ESP]
//   0x00c4474f  52                          PUSH EDX
//   0x00c44750  50                          PUSH EAX
//   0x00c44751  e8 6af5ffff                CALL 0x00c43cc0
//   0x00c44756  83 c4 10                    ADD ESP, 0x10
//   0x00c44759  c2 08 00                    RET 0x8
//
// The element is 16 bytes: three floats copied verbatim from the caller's
// triple, plus a fourth dword that is EXACTLY (front != 0) ? 1 : 0 — SETNZ at
// 0x00c446ed after XOR EDX,EDX at 0x00c446e9 guarantees 0 or 1, never a
// byte-restored value.  That dword is written on both the front and the back
// path, so "front" is recorded in the element, not just used as a direction.
//
// ECX is advanced to this+0xF0 at 0x00c446f0 and every subsequent access is
// relative to that, so the container is the member at +0xF0.  Its three
// cursors are +0x00 (mpFirst), +0x04 (mpCur), +0x08 (mpEnd):
//   * 0x00c44721/0x00c44724 read mpCur and mpEnd and JNC (unsigned) to the
//     grow path, so "full" is mpCur >= mpEnd, not an equality test.
//   * the inline back path bumps mpCur to mpCur+0x10 FIRST (0x00c4472a/2d)
//     and only then writes the element, and it skips the write entirely when
//     mpCur was null (0x00c44731 TEST EAX,EAX ; 0x00c44733 JZ 0x00c44756).
//   * the front path passes mpFirst as the insertion position to 0x00c43f20.
//
// 0x00c43cc0 and 0x00c43f20 are the vector's own insert helpers.  Their bodies
// were read (ghidra_decompile_function): 0x00c43cc0 grows to
// max(1, 2*(mpCur-mpFirst)/0x10) elements and allocates capacity<<4 bytes via
// 0x00f473a0 with the literal "Simulator" and the source path
// "c:\BuildAgent\max-spore001-spore\CMBuild\SporeEP1_RL\Core\UTFKernel\EASTL\include\EASTL/allocator.h",
// and 0x00c43f20 has a fast path when pos == mpCur && mpCur != mpEnd and
// otherwise delegates to 0x00c43cc0, returning mpFirst + index*0x10.  Both end
// in RET 0x8, so this function's own RET 0x8 hands its two arguments to them
// one-for-one.  The container is therefore an EASTL vector of 0x10-byte
// elements; the owning class is NOT identified by this batch.

#include "sim_core_b06_opaque.hpp"

namespace sim_core_b06 {

// Appends or prepends `{xyz, front ? 1 : 0}` to the 0x10-byte-element vector
// member at this+0xF0.
//
// One receiver in ECX, two callee-cleaned stack dwords (`RET 0x8`), no return
// value.  `at_front != 0` selects the prepend direction and is also stored in
// the element's fourth word.
void SimCore_00c446d0_pushTaggedVector3(OpaqueOwner_C446D0* owner, const float (&xyz)[3],
                                       std::uint8_t at_front) {
    // 0x00c446d7..0x00c446e0: the three floats are loaded into XMM0..XMM2
    // before the branch, so they are live across both paths.
    // 0x00c446e9 + 0x00c446ed: tag := (at_front != 0) ? 1 : 0, always 0 or 1.
    // 0x00c44706/0x00c44707: the 16-byte element is materialised on the stack.
    const TaggedVector3 item = {xyz[0], xyz[1], xyz[2], at_front != 0u ? 1u : 0u};

    // 0x00c446f0: ECX := this + 0xF0.
    EastlVector16& vec = owner->taggedVector3s;

    // 0x00c4470b TEST AL,AL / 0x00c4470d JZ 0x00c44721 — non-zero goes to the
    // prepend path at 0x00c4470f.
    if (at_front != 0u) {
        // 0x00c4470f: EDX := vec.mpFirst is the insertion position.
        port_00c43f20_insertAtFront(&vec, vec.mpFirst, &item);
        return;
    }

    // ---- append path, 0x00c44721 ----
    // 0x00c44721/0x00c44724: unsigned compare; JNC means "cur >= end".
    if (vec.mpCur >= vec.mpEnd) {
        // 0x00c4474c..0x00c44751: grow via the vector's own insert helper with
        // pos = mpCur.
        port_00c43cc0_insertAt(&vec, vec.mpCur, &item);
        return;
    }

    // 0x00c4472a/0x00c4472d: the cursor is advanced BEFORE the payload write.
    TaggedVector3* const slot = vec.mpCur;
    vec.mpCur = slot + 1;

    // 0x00c44731/0x00c44733: a null cursor means there is nowhere to write, and
    // the function returns without touching memory.
    if (slot == nullptr) {
        return;
    }

    // 0x00c44735..0x00c44743: four dwords written, tag included.
    *slot = item;
}

}  // namespace sim_core_b06
