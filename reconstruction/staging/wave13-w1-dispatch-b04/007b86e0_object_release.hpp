// Reconstruction of 0x007b86e0 - the second virtual of the reference-counted
// root interface, reached at vtable slot +0x04.
//
// Layout proved for this receiver by the disassembly of the body itself and by
// 14 sampled vtables in .rdata/.data:
//
//   +0x00  primary vptr
//   +0x04  vptr of a second, embedded polymorphic sub-object
//   +0x08  std::int32_t reference count
//
// The count at +0x08 is proved by the partner body at 0x00c6a960, which sits
// at slot +0x00 of the same tables and whose whole body is
// `mov eax,[ecx+8]; inc eax; mov [ecx+8],eax; ret`.
//
// The second vptr at +0x04 is proved by 0x0041d780, the scalar deleting
// destructor of the base whose vtable lives at 0x013ef094: the destructor of
// the concrete class stores 0x013ef094 into [this+4] on the way down, and
// 0x0041d780 itself is `*self = 0x013ef094; if (arg & 1) free(self); ret 4`.
//
// Complete body, read live at 0x007b86e0 (8b4108 83c104 83c0ff 894104 7511
// c7410401000000 8b01 8b10 6a01 ffd2 33c0 c3, then cc padding):
//
//   0x007b86e0  8b 41 08          mov eax, [ecx+8]
//   0x007b86e3  83 c1 04          add ecx, 4
//   0x007b86e6  83 c0 ff          add eax, -1
//   0x007b86e9  89 41 04          mov [ecx+4], eax
//   0x007b86ec  75 11             jnz 0x007b86ff
//   0x007b86ee  c7 41 04 01000000 mov [ecx+4], 1
//   0x007b86f5  8b 01             mov eax, [ecx]
//   0x007b86f7  8b 10             mov edx, [eax]
//   0x007b86f9  6a 01             push 1
//   0x007b86fb  ff d2             call edx
//   0x007b86fd  33 c0             xor eax, eax
//   0x007b86ff  c3                ret
//
// The ADD ECX,4 is load-address arithmetic, not an argument: ECX at the CALL is
// `this + 4`, the address of the embedded sub-object, which is exactly the
// receiver a thiscall to slot +0x00 of that sub-object needs. The body never
// dereferences a null, so a receiver whose count is already 0 is not
// dereferenceable and is not modelled.
#pragma once

#include <cstdint>

namespace openspore::reconstruction::wave13_w1_dispatch_b04 {

// The embedded polymorphic sub-object at owner+0x04. Only its vptr is ever
// read; its slot +0x00 is the only slot reached.
struct EmbeddedPolymorphicBase_007b86e0 {
    void** vptr;  // +0x00 of the sub-object
};

// The receiver. Sized to the three observed words; nothing beyond +0x0b is
// read by this body or by the partner at 0x00c6a960.
struct RefCountedObject_007b86e0 {
    void** vptr;                                       // +0x00
    EmbeddedPolymorphicBase_007b86e0 embedded_base;   // +0x04
    std::int32_t ref_count;                            // +0x08
};

// Port for the embedded base's slot +0x00.
//
// The single concrete callee observed for that slot is 0x0041d780, the scalar
// deleting destructor of the base whose vtable is 0x013ef094:
//
//   0x0041d78a  c7 00 9413ef00   mov [eax], 0x013ef094
//   0x0041d793  83 e1 01         and ecx, 1
//   0x0041d79c  e8 ..            call 0x00f47380     ; deallocate(self)
//   0x0041d7aa  c2 04 00         ret 4
//
// so the constant 1 pushed by the body is the deleting-destructor flag: bit 0
// set means "also free the memory". The body is declared, not defined, because
// the concrete destructor is a property of the owning class, not of this one.
extern "C" void __attribute__((thiscall))
PORT_embedded_base_deleting_dtor_0041d780(EmbeddedPolymorphicBase_007b86e0* self,
                                    unsigned int delete_memory);

// The body. See the file comment for the instruction-level derivation.
extern "C" std::int32_t __attribute__((thiscall))
FUN_007b86e0_release(RefCountedObject_007b86e0* self);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b04
