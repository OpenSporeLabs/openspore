#include "tribe_civilization.hpp"

#if defined(_MSC_VER)
#define PKG13_C2_THISCALL __thiscall
#else
#define PKG13_C2_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg13_c2_tribe_civilization {

NativePorts g_native_ports{nullptr, nullptr};

namespace {

constexpr std::uint32_t kNounProjectionCreateWord = 0x00b21080U;
constexpr std::uint32_t kNounProjectionClearWord = 0x00d3d420U;
constexpr std::uint32_t kNounProjectionAddWord = 0x00b236c0U;
constexpr std::uint32_t kNounProjectionFilterWord = 0x00b1e500U;
constexpr std::uint32_t kNounProjectionIdentity = 0x018c816aU;

}

extern "C" NounObject* PKG13_C2_THISCALL tribe_civilization_resolver_00b25f40(
    NounProjection* receiver, std::uint32_t identity) {
  NounProjectionVector* const vector = g_native_ports.noun_projection_lookup(
      receiver, kNounProjectionCreateWord, kNounProjectionClearWord,
      kNounProjectionAddWord, kNounProjectionFilterWord,
      kNounProjectionIdentity);
  const std::intptr_t byte_span =
      reinterpret_cast<std::intptr_t>(vector->end) -
      reinterpret_cast<std::intptr_t>(vector->begin);
  const std::int32_t count = static_cast<std::int32_t>(byte_span >> 2);
  NounObject* const* const begin = vector->begin;

  for (std::int32_t index = 0; index < count; ++index) {
    NounObject* const object = begin[index];
    const std::uint32_t object_identity = object->vtable->identity(object);
    if (object_identity == identity) {
      return object;
    }
  }
  return nullptr;
}

extern "C" NounObject* PKG13_C2_THISCALL
tribe_civilization_bridge_00b25fb0(NounProjection* receiver) {
  CurrentPlayerStateAccessWindow* const current_player =
      g_native_ports.current_player();
  if (current_player == nullptr) {
    return reinterpret_cast<NounObject*>(receiver);
  }
  return tribe_civilization_resolver_00b25f40(receiver,
                                              current_player->identity);
}

}
