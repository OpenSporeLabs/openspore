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

OpaqueWord word_of(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

// 0x00b7237f-0x00b72393 publish the five words unconditionally, BEFORE either
// null test, so a null dispatch target or a null receiver-minus-four word still
// leaves the receiver fully populated. 0x00b7239a TEST EDI,EDI and
// 0x00b7239e TEST EBX,EBX each skip the whole loop.
//
// The loop at 0x00b723a2-0x00b723bb keeps a byte index in ESI from 0 to 0x20
// in steps of 4 and re-reads BOTH the dispatch object's vtable pointer
// (0x00b723aa MOV EAX,[EDI]) and its slot word at displacement 0x24
// (0x00b723ac MOV EDX,[EAX+0x24]) on every iteration, so replacing the slot
// mid-loop changes which implementation runs. Each call pushes the current
// 0x01465004 word and then the receiver-minus-four word and sets ECX to the
// dispatch object; the callee reclaims the two words, so this loop performs no
// stack cleanup of its own.
void publish_and_dispatch_delete_record(OpaqueObjectPoolReceiver* pool,
                                        OpaqueDispatchTarget* dispatch_target,
                                        void* receiver_minus_four) {
  pool->record_target_20 = dispatch_target;
  pool->record_token_24 = word_of(receiver_minus_four);
  pool->record_source_base_28 = kSourceTableVa;
  pool->record_source_word_count_2c = kSourceTableWordCount;
  pool->record_trailing_30 = 0u;

  if (dispatch_target == nullptr || receiver_minus_four == nullptr) {
    return;
  }

  const OpaqueWord token = word_of(receiver_minus_four);
  for (OpaqueWord byte_index = 0; byte_index < kSourceTableWindowBytes;
       byte_index += 4u) {
    dispatch_target->vtable_00->operation_24(
        dispatch_target, token,
        g_dogfood_00b72370_globals.word_01465004[byte_index / 4u]);
  }
}

// 0x00b72370 Simulator::cObjectPool_::DeleteObject.
//
// 0x00b72370-0x00b72373 PUSH EBX, PUSH ESI, PUSH EDI, MOV ESI,ECX.
// 0x00b72375 CALL 0x00883860 pushes no argument; EAX is taken as an object
// pointer at 0x00b7237a. 0x00b7237c LEA EBX,[ESI + -0x4] derives the only
// other value the body uses, the receiver word minus four. The five stores and
// the loop follow. 0x00b723bd-0x00b723c0 POP EDI, POP ESI, POP EBX, RET is a
// plain RET: this function cleans nothing and returns nothing, and the value
// the dispatched slot leaves in EAX is discarded.
//
// The SDK decompilation renders the signature as (cObjectPool_ *this,
// cObjectPoolIndex index) with the second formal derived from in_ECX - 4. No
// stack word is pushed at entry and the return is a plain RET, so the observed
// ordinary stack argument slot count is zero and that formal is a derived
// word, not a parameter.
extern "C" void PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
delete_object_00b72370(OpaqueObjectPoolReceiver* pool) {
  OpaqueDispatchTarget* const dispatch_target =
      g_dogfood_00b72370_ports.acquire_dispatch_target_00883860();
  void* const receiver_minus_four = reinterpret_cast<void*>(
      reinterpret_cast<std::uint8_t*>(pool) - 4);
  publish_and_dispatch_delete_record(pool, dispatch_target, receiver_minus_four);
}

void delete_object_model(OpaqueObjectPoolReceiver* pool) {
  OpaqueDispatchTarget* const dispatch_target =
      g_dogfood_00b72370_ports.acquire_dispatch_target_00883860();
  void* const receiver_minus_four = reinterpret_cast<void*>(
      reinterpret_cast<std::uint8_t*>(pool) - 4);
  publish_and_dispatch_delete_record(pool, dispatch_target, receiver_minus_four);
}

}
