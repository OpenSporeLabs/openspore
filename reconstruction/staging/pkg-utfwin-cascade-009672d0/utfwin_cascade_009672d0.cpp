#include "utfwin_cascade_009672d0.hpp"

namespace openspore::reconstruction::pkg_utfwin_cascade_009672d0 {

#if defined(_MSC_VER)
#define LOCAL_THISCALL __thiscall
#else
#define LOCAL_THISCALL __attribute__((thiscall))
#endif

namespace unresolved_contracts {

// The single out-edge of the target body: `e9 cc 9b fe ff` at 0x009672df, a
// near jump to 0x00950eb0 whose displacement resolves to 0x009672e4 - 0x6434.
// The instruction right before it, `89 44 24 04`, stores EAX back into the slot
// the first instruction read from, so the type word is left on the stack
// exactly as the caller pushed it and the tail callee re-reads the same word.
// ECX is untouched across both, so the tail callee has the same thiscall shape
// and consumes the same single 4-byte argument.
extern "C" Opaque* LOCAL_THISCALL cascade_type_fallback_00950eb0(Opaque object,
                                                                Opaque type);

}

// Target VA 0x009672d0, 11 instructions, 0x22 bytes, body 0x009672d0-0x009672f2.
//
//   009672d0  8b 44 24 04        MOV EAX,dword ptr [ESP + 0x4]
//   009672d4  3d 35 a5 90 6f     CMP EAX,0x6f90a535
//   009672d9  74 09              JZ 0x009672e4
//   009672db  89 44 24 04        MOV dword ptr [ESP + 0x4],EAX
//   009672df  e9 cc 9b fe ff     JMP 0x00950eb0
//   009672e4  85 c9              TEST ECX,ECX
//   009672e6  74 06              JZ 0x009672ee
//   009672e8  8d 41 0c           LEA EAX,[ECX + 0xc]
//   009672eb  c2 04 00           RET 0x4
//   009672ee  33 c0              XOR EAX,EAX
//   009672f0  c2 04 00           RET 0x4
//
// One comparison, two exits through the receiver word in ECX, and everything
// else handed to the tail callee. Both returns materialise a full 4-byte EAX,
// not a byte in AL: the taken arm is an LEA, not a load-and-test, so the value
// that leaves this function is the receiver address biased by 0x0c.
Opaque* LOCAL_THISCALL handle_message_009672d0(Opaque object, Opaque type) {
  if (type == kObjectTypeICascadeEffect) {
    if (object == 0u) {
      return nullptr;
    }
    // The bias is the displacement of 0x009672e8 LEA EAX,[ECX + 0xc] and is
    // written with the listing's own spelling of it (0xc, not 0x0c) so the
    // constant here is the token the machine listing actually carries.
    return reinterpret_cast<Opaque*>(object + 0xcu);
  }
  return unresolved_contracts::cascade_type_fallback_00950eb0(object, type);
}

}

#undef LOCAL_THISCALL
