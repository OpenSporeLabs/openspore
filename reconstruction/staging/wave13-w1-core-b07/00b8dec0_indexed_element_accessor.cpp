// reconstruction/staging/wave13-w1-core-b07/00b8dec0_indexed_element_accessor.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00b8dec0 (image base
// 0x00400000). Body 0x00b8dec0..0x00b8dee5, 11 instructions, 40 bytes.
//
// Contract reconstructed from the binary: an unchecked-index accessor over a
// contiguous block of 4-byte elements delimited by begin (+0x15c) and end
// (+0x160). The element count is (end - begin) >> 2 and the index is compared
// against it with a SIGNED comparison, so only the upper bound is enforced: a
// negative index passes the test and reads before the block. The return value
// is the element word itself (zero when the index is at or past the end), not
// a pointer to it.
//
// Not claimed: the element type and the owning class. Caller 0x00c5c860
// passes the result straight back as ECX, and the callee it reaches
// (0x00ff0420) reads +0x14 of it, so at least one element is an object
// pointer; nothing wider is established.

#include "b07_opaque_types.hpp"

namespace openspore {
namespace b07 {
namespace t00b8dec0 {

// 0x00b8dec0 MOV EDX,dword ptr [ECX + 0x160]
// 0x00b8dec6 SUB EDX,dword ptr [ECX + 0x15c]
// 0x00b8ded0 SAR EDX,0x2
// 0x00b8decc MOV EAX,dword ptr [ESP + 0x4]   (the index, sign preserved)
// 0x00b8ded3 CMP EAX,EDX
// 0x00b8ded5 JGE 0x00b8dee3                 (signed: only the upper bound)
// 0x00b8ded7 MOV ECX,dword ptr [ECX + 0x15c]
// 0x00b8dedd MOV EAX,dword ptr [ECX + EAX*0x4]
// 0x00b8dee3 XOR EAX,EAX                     (out of range)
std::int32_t element_at(ElementBlock* block, std::int32_t index) {
    // Read order and the shift mirror 0x00b8dec0/0x00b8dec6/0x00b8ded0 so the
    // emitted code stays SAR EDX,0x2 rather than a signed-division fixup.
    const std::int32_t end = static_cast<std::int32_t>(block->end);
    const std::int32_t begin = static_cast<std::int32_t>(block->begin);
    const std::int32_t count = (end - begin) >> 2;

    if (index >= count) {
        return 0;
    }
    const Word* elements = pointer_at<Word>(block->begin);
    return static_cast<std::int32_t>(elements[index]);
}

}  // namespace t00b8dec0
}  // namespace b07
}  // namespace openspore
