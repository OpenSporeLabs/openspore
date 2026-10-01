#include "utfwin_is_ancestor_of_0095fa30.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_0095FA30_THISCALL __thiscall
#else
#define PKG_0095FA30_THISCALL __attribute__((thiscall))
#endif

// 0x0095fa30 UTFWin::Window::IsAncestorOf - the ModAPI SDK import name.
//
// Raw bytes 0x0095fa30..0x0095fa3c:
//     8b 44 24 04            MOV  EAX,dword ptr [ESP + 0x4]
//     89 81 80 00 00 00      MOV  dword ptr [ECX + 0x80],EAX
//     c2 04 00               RET  0x4
//
// ECX is the receiver and the single ordinary argument is the 4-byte stack word
// at [ESP+4], which 0x0095fa30 copies into EAX and 0x0095fa34 stores verbatim
// at receiver+0x80. The argument is never dereferenced and never compared, so
// the store is unconditional: there is no branch, no call, no flag test, no
// register save and no loop in the body. RET 0x4 pops the argument word, so the
// callee owns the four bytes of stack cleanup.
//
// Return: the model declares void. No instruction after 0x0095fa30 writes EAX,
// so the copied argument word is still sitting in EAX at the RET; the machine
// therefore materialises no result, and nothing here claims the residue as a
// returned value. The SDK symbol table labels this method `bool`, and Ghidra
// renders that label, but no instruction sets AL or the upper bytes of EAX on
// any path, so a bool result is not derivable from the body. That disagreement
// is recorded as an open question in the metadata sidecar rather than modelled,
// because every one of the 33 references to 0x0095fa30 is a DATA vtable entry
// and never a CALL site, so no static caller can be shown to consume AL.
//
// The SDK parameter name is pChildWindow; the machine neither dereferences the
// word nor compares it, so this reconstruction keeps the argument name neutral
// and models no ancestor query, no tree walk and no comparison result.

namespace openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof {

void PKG_0095FA30_THISCALL is_ancestor_of_0095fa30(OpaqueWindow* window,
                                                   OpaqueWindow* argument) {
  // 0x0095fa30 MOV EAX,dword ptr [ESP + 0x4]
  // 0x0095fa34 MOV dword ptr [ECX + 0x80],EAX
  // 0x0095fa3a RET 0x4
  //
  // The one memory access this body makes, transcribed as the machine has it:
  // the 4-byte stack word at [ESP+4] is copied into EAX and stored verbatim
  // into the 4-byte word at receiver+0x80. There is no branch, no call, no flag
  // test, no register save and no loop between the load and the store, so the
  // store happens on every entry.
  //
  // The store is written as a displacement into the opaque receiver, NOT as
  // `window->member = ...`. The disassembly establishes the displacement
  // (0x80), the width (dword) and the base (ECX); it establishes nothing about
  // which member of any type occupies that word, and the receiver record says
  // so itself (`register=ECX offsets=[0x80] bounds_only`). A member name here
  // would be a field-identity assertion with nothing behind it, so the
  // displacement is spelled literally instead and the identity claim is left
  // out - which is also the only way the reconstruction stays true to a body
  // that stores a raw copy of an argument.
  *reinterpret_cast<Opaque*>(reinterpret_cast<std::uintptr_t>(window) + 0x80) =
      as_word(argument);
}

}

#undef PKG_0095FA30_THISCALL
