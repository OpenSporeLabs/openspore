#include "argscript_createdefsafe_00841440.hpp"

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_CDS_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_CDS_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_createdefsafe_00841440 {

namespace {

// 0x0083c780, exactly as the five bytes read at that address show it:
//
//   0x0083c780  8b 44 24 04        MOV EAX,dword ptr [ESP+0x4]
//   0x0083c784  8b 54 24 08        MOV EDX,dword ptr [ESP+0x8]
//   0x0083c788  89 41 04           MOV dword ptr [ECX+0x4],EAX
//   0x0083c78b  89 51 0c           MOV dword ptr [ECX+0xc],EDX
//   0x0083c78e  c2 08 00           RET 0x8
//
// Two stores and the EAX state at the RET; the callee pops both argument words.
// Not promoted to a function record -- see the header.
bool modelled_tail_0083c780(OpaqueFormatParser* self, char* pName,
                            OpaqueLine* argumentsLine) {
  std::uint8_t* const base = receiver_bytes(self);
  const OpaqueWord first = word_of(pName);
  const OpaqueWord second = word_of(argumentsLine);
  write_word_at(base, 0x04u, first);
  write_word_at(base, 0x0cu, second);
  // No instruction after the two stores touches EAX, so the register the caller
  // reads holds the first argument. The SDK declares the return type bool, so
  // the observed return is that word reduced to its low byte.
  return first != 0u;
}

}  // namespace

bool model_tail_0083c780(OpaqueFormatParser* self, char* pName,
                         OpaqueLine* argumentsLine) {
  return modelled_tail_0083c780(self, pName, argumentsLine);
}

// The default binding is the public model, so the port identity a caller sees
// is the one the header declares.
SharedTail0083c780 g_tail_0083c780 = &model_tail_0083c780;

bool PKG_ARGSCRIPT_CDS_THIS_CALL
argscript_formatparser_create_definition_safe_00841440(
    OpaqueFormatParser* self, char* pName, OpaqueLine* argumentsLine) {
  // 0x00841440  8b 54 24 08        MOV EDX,dword ptr [ESP + 0x8]
  // The second ordinary stack word, read as a bare 32-bit value. Nothing
  // dereferences it in this body.
  const OpaqueWord line = word_of(argumentsLine);
  std::uint8_t* const base = receiver_bytes(self);

  // 0x00841444  85 d2              TEST EDX,EDX
  // 0x00841446  74 0f              JZ 0x00841457
  if (line != 0u) {
    // 0x00841448  8d 42 fc           LEA EAX,[EDX + -0x4]
    // 0x0084144b  89 41 30           MOV dword ptr [ECX + 0x30],EAX
    // 0x0084144e  89 54 24 08        MOV dword ptr [ESP + 0x8],EDX
    // 0x00841452  e9 29 b3 ff ff     JMP 0x0083c780
    write_word_at(base, 0x30u, line - 4u);
  } else {
    // 0x00841457  33 c0              XOR EAX,EAX
    // 0x00841459  89 41 30           MOV dword ptr [ECX + 0x30],EAX
    // 0x0084145c  89 54 24 08        MOV dword ptr [ESP + 0x8],EDX
    // 0x00841460  e9 1b b3 ff ff     JMP 0x0083c780
    write_word_at(base, 0x30u, 0u);
  }

  // The MOV at 0x0084144e and 0x0084145c rewrites [ESP+0x8] with the value
  // that slot already holds -- EDX was loaded from it at 0x00841440 and is
  // unmodified on both arms -- so it is a value-preserving store and is not
  // reproduced as a separate effect. Both JMPs carry ECX and both stack words
  // into the shared tail unchanged, which is why the two arguments are passed
  // on exactly as received.
  return g_tail_0083c780(self, pName, argumentsLine);
}

}  // namespace openspore::reconstruction::pkg_argscript_createdefsafe_00841440

#undef PKG_ARGSCRIPT_CDS_THIS_CALL
