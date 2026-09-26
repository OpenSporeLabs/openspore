// reconstruction/staging/wave13-w1-core-b07/0060d860_resolve_and_submit_keyed_work.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x0060d860 (image base
// 0x00400000). Body 0x0060d860..0x0060d918, 59 instructions, 187 bytes.
//
// Contract reconstructed from the binary: a void two-argument operation whose
// whole body is gated on [this + 0x58] being non-zero. When the gate is closed
// nothing at all happens, not even the release of the resolved object. When it
// is open:
//   1. 0x00552450 turns the mode descriptor (argument 2) into an object; the
//      object pointer is published through a local out-word.
//   2. On success the 8-byte key pair at object+0x18 (0x005507a0) is copied
//      into two frame words that were pre-loaded with 0xffffffff.
//   3. Work is skipped unless (key0 & key1) != 0xffffffff and the global job
//      manager at 0x015f5628 (0x0061df20) is non-null. The empty case is
//      expressed as the AND of the two words, so any key pair whose AND is
//      0xffffffff is skipped, not only the untouched pair.
//   4. A 0x14-byte key descriptor is built in the frame, its flags word and
//      kind word are pre-zeroed, 0x0060cfa0 fills the first two words from the
//      key, and 0x0061fdb0 (job manager, argument 1, descriptor) is invoked.
//      That callee builds a cJob continuation when the descriptor's kind and
//      flags are outside its immediate set.
//   5. If the descriptor's flag bit 0x4 is set, 0x0093db80 is called on it.
//   6. Whatever happened above, the resolved object is released through its
//      vtable slot +0x4 when it is non-null (0x0060d90e/0x0060d910/0x0060d913).
//
// Not claimed: the receiver class, the meaning of the 8-byte key pair, and the
// receiver slot handed to 0x0093db80 (see the metadata sidecar: the static
// stack arithmetic is ambiguous there).

#include "b07_opaque_types.hpp"

namespace openspore {
namespace b07 {
namespace t0060d860 {

// 0x0060d860 SUB ESP,0x20 -- a 0x20-byte frame; the words used below sit at
// frame+0x00 (resolved object), +0x04/+0x08 (the two key halves),
// +0x0c..+0x1f (the key descriptor, whose flags word is at +0x10 and kind
// word at +0x12 relative to the descriptor).
inline constexpr Word kFlagBit4 = 0x4;

void resolve_and_submit_keyed_work(ModeOwner* self, Word arg1, const ModeDescriptor* modeDescriptor,
                                  CreateFromModeDescriptorFn createFromMode,
                                  KeyPairAddrFn keyPairAddr, JobManagerFn jobManager,
                                  MakeKeyDescriptorFn makeKeyDescriptor, SubmitJobFn submitJob,
                                  ReportKeyFlagsFn reportFlags, VirtualReleaseFn releaseSlot1) {
    // 0x0060d863 CMP dword ptr [ECX + 0x58],0x0 / 0x0060d867 JZ 0x0060d915
    if (self->pad58 == 0) {
        return;
    }

    // 0x0060d86d MOV ECX,dword ptr [ESP + 0x28]  (argument 2)
    // 0x0060d872 LEA EAX,[ESP + 0x4]  -> &resolvedObject, pre-zeroed at
    // 0x0060d883 MOV dword ptr [ESP + 0xc],0x0 and passed on the stack.
    Word resolvedObject = 0;
    const bool created =
        createFromMode(modeDescriptor, &resolvedObject) != 0;

    // 0x0060d87b/0x0060d87f MOV dword ptr [ESP + 0x10/0x14],ESI with
    // ESI = 0xffffffff (0x0060d877 OR ESI,0xffffffff)
    Word keyWords[2] = {kInvalidWord, kInvalidWord};

    if (created) {
        // 0x0060d897..0x0060d8a9: read the 8-byte key pair at object+0x18
        const Word* keyPair = pointer_at<Word>(keyPairAddr(resolvedObject));
        keyWords[0] = keyPair[0];  // 0x0060d8a2 MOV dword ptr [ESP+0x8],ECX
        keyWords[1] = keyPair[1];  // 0x0060d8a9 MOV dword ptr [ESP+0xc],EDX
    }

    // 0x0060d8b3 AND ECX,dword ptr [ESP + 0xc]
    // 0x0060d8b7 CMP ECX,ESI / 0x0060d8b9 JZ 0x0060d905
    const Word combined = keyWords[0] & keyWords[1];
    if (combined != kInvalidWord) {
        // 0x0060d8bb CALL 0x0061df20 / 0x0060d8c2 TEST ESI,ESI
        // 0x0060d8c4 JZ 0x0060d905
        const Word manager = jobManager();
        if (manager != 0) {
            // 0x0060d8ce/0x0060d8d8 zero the descriptor's flags and kind words
            KeyDescriptor descriptor;
            for (Word& word : descriptor.head) {
                word = 0;
            }
            descriptor.flags = 0;  // frame + kFlagsOffset
            descriptor.kind = 0;   // frame + kKindOffset

            // 0x0060d8c8 LEA EDX,[ESP + 0x8]  -> the key pair address
            // 0x0060d8d4 LEA ECX,[ESP + 0x14] -> the descriptor address
            // 0x0060d8dd CALL 0x0060cfa0
            makeKeyDescriptor(&descriptor, keyWords);

            // 0x0060d8e2 MOV ECX,dword ptr [ESP + 0x28]  (argument 1)
            // 0x0060d8e6 LEA EAX,[ESP + 0x10]            -> descriptor address
            // 0x0060d8ee CALL 0x0061fdb0
            submitJob(manager, arg1, &descriptor);

            // 0x0060d8f3 TEST byte ptr [ESP + 0x20],0x4
            // 0x0060d8f8 JZ 0x0060d905
            if ((descriptor.flags & kFlagBit4) != 0) {
                // 0x0060d8fa PUSH 0x0
                // 0x0060d8fc LEA ECX,[ESP + 0x4]
                // 0x0060d900 CALL 0x0093db80
                reportFlags(&descriptor, 0);
            }
        }
    }

    // 0x0060d905 MOV ECX,dword ptr [ESP + 0x4] / 0x0060d90a TEST ECX,ECX
    // 0x0060d90c JZ 0x0060d915
    if (resolvedObject != 0) {
        // 0x0060d90e MOV EDX,dword ptr [ECX]
        // 0x0060d910 MOV EAX,dword ptr [EDX + 0x4]
        // 0x0060d913 CALL EAX
        releaseSlot1(resolvedObject);
    }
}

}  // namespace t0060d860
}  // namespace b07
}  // namespace openspore
