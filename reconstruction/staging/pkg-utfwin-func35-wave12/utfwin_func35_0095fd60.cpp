#include "utfwin_func35_0095fd60.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_utfwin_func35_wave12 {
namespace {

template <typename To>
To function_from(Opaque word) {
  static_assert(sizeof(To) == sizeof(Opaque),
                "UTFWin function pointer width mismatch");
  To result{};
  std::memcpy(&result, &word, sizeof(result));
  return result;
}

}

void PKG_UTFWIN_FUNC35_THISCALL func35_0095fd60(OpaqueWindow* object,
                                                Opaque value) {
  // 0x0095fd60 SUB ESP,0x1c / 0x0095fd63 PUSH ESI / 0x0095fd64 MOV ESI,ECX
  //
  // The receiver, aliased into ESI and reached through it for the rest of the
  // body. Every access below is a DISPLACEMENT into the opaque window; none of
  // them names a member, because the receiver record (offsets=[0x0, 0xa8, 0x1dc],
  // bounds_only) states where the body reached and not which member it found.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(object);

  // 0x0095fd66 MOV EAX,dword ptr [ESI + 0xa8]
  const Opaque previous = *reinterpret_cast<const Opaque*>(self + 0xa8);

  // 0x0095fd6c MOV ECX,dword ptr [ESP + 0x24]   the single stack argument
  // 0x0095fd70 CMP ECX,EAX
  // 0x0095fd72 JZ 0x0095fdb0
  //
  // A plain equality test, not an ordering one: the body stores the argument
  // and nothing else, so the only thing that suppresses the work is the two
  // words being equal.
  if (value == previous) {
    // 0x0095fdb0 POP ESI / 0x0095fdb1 ADD ESP,0x1c / 0x0095fdb4 RET 0x4
    return;
  }

  // 0x0095fd74 MOV dword ptr [ESI + 0xa8],ECX
  //
  // The store happens BEFORE either dispatch, so the slot 0x114 call already
  // sees the new value in place. Nothing after this point can be reordered
  // ahead of it, and the model test pins the order by having the slot 0x90
  // observer read the word back.
  *reinterpret_cast<Opaque*>(self + 0xa8) = value;

  // 0x0095fd82 MOV EAX,dword ptr [ESI]        the dispatch word
  // 0x0095fd84 MOV EDX,dword ptr [EAX + 0x114]
  // 0x0095fd8a LEA ECX,[ESP + 0x4]            &record
  // 0x0095fd8e PUSH ECX                      the single stack argument
  // 0x0095fd8f MOV ECX,ESI                   the receiver in ECX
  // 0x0095fd7a MOV [ESP + 0x10],ECX          record + 0x0c, the new value
  // 0x0095fd7e MOV [ESP + 0x14],EAX          record + 0x10, the previous value
  // 0x0095fd91 MOV [ESP + 0x10],0x13          record + 0x08, the code
  // 0x0095fd99 CALL EDX                      (the callee pops the word)
  //
  // The three stores are the ONLY writes into the record, and the body reads
  // none of them back. The record is therefore a bare 0x14-byte run with three
  // words written into it: +0x00 and +0x04 stay indeterminate, which is what an
  // opaque run says and what a zero-initialised struct would not.
  alignas(4) std::uint8_t record[0x14]{};
  *reinterpret_cast<Opaque*>(record + kMessageCodeDisplacement) = kMessageCode;
  *reinterpret_cast<Opaque*>(record + kMessageNewValueDisplacement) = value;
  *reinterpret_cast<Opaque*>(record + 0x10) = previous;

  OpaqueWindowVTable* const table = *reinterpret_cast<
      OpaqueWindowVTable* const*>(self + 0x0);
  const auto message_slot = function_from<WindowSlot114>(
      *reinterpret_cast<const Opaque*>(
          reinterpret_cast<const std::uint8_t*>(table) + 0x114));
  message_slot(object, reinterpret_cast<OpaqueStateMessage*>(record));

  // 0x0095fd9b CMP dword ptr [ESI + 0x1dc],0x0 / 0x0095fda2 JZ 0x0095fdb0
  //
  // Compared against zero and nothing else, so every non-zero word dispatches -
  // the gate is not a flag bit and the test does not narrow it.
  if (*reinterpret_cast<const Opaque*>(self + 0x1dc) != 0u) {
    // 0x0095fda4 MOV EAX,dword ptr [ESI]     the dispatch word, read a second
    // 0x0095fda6 MOV EDX,dword ptr [EAX+0x90]   time - the body reloads it
    // 0x0095fdac MOV ECX,ESI                rather than reusing the first load
    // 0x0095fdae CALL EDX
    const auto pending_slot = function_from<WindowSlot90>(
        *reinterpret_cast<const Opaque*>(
            reinterpret_cast<const std::uint8_t*>(table) + 0x90));
    pending_slot(object);
  }
}

}
