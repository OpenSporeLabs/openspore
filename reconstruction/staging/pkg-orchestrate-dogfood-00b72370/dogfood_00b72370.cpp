#include "dogfood_00b72370.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-00b72370 requires MSVC or GCC CCs"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_00b72370 {

DeleteObjectPorts g_dogfood_00b72370_ports{};
DeleteObjectGlobals g_dogfood_00b72370_globals{};

namespace {

OpaqueWord word_of(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

}

// 0x00b72370 Simulator::cObjectPool_::DeleteObject.
// Prologue saves EBX, ESI and EDI; ECX is the receiver. 0x00883860 is called
// with no argument, its EAX result becomes EDI, and EBX becomes the receiver
// word minus four. The five stores at 0x00b7237f-0x00b72393 are unconditional
// and precede both null tests. The loop at 0x00b723a2-0x00b723bb walks the
// eight words at 0x01465004 and re-reads the target vtable slot +0x24 on every
// iteration. The epilogue restores the saved registers and returns with a
// plain RET, so there is no stack cleanup and no returned value.
extern "C" void PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
simulator_c_object_pool_delete_object_00b72370(OpaqueObjectPoolReceiver* pool) {
  DeleteObjectPorts& ports = g_dogfood_00b72370_ports;
  DeleteObjectGlobals& globals = g_dogfood_00b72370_globals;

  OpaqueDispatchTarget* const dispatch_target =
      ports.acquire_dispatch_target_00883860();
  OpaqueWord* const receiver_minus_four =
      reinterpret_cast<OpaqueWord*>(reinterpret_cast<std::uint8_t*>(pool) - 4);

  pool->dispatch_target_20 = word_of(dispatch_target);
  pool->receiver_minus_four_24 = word_of(receiver_minus_four);
  pool->table_base_28 = 0x01465004u;
  pool->table_word_count_2c = 0x8u;
  pool->zero_word_30 = 0x0u;

  if (dispatch_target == nullptr || receiver_minus_four == nullptr) {
    return;
  }

  for (std::size_t index = 0; index < 8u; ++index) {
    dispatch_target->vtable->operation_24(dispatch_target,
                                          word_of(receiver_minus_four),
                                          globals.word_01465004[index]);
  }
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
