#include "runtime_services_wave8.hpp"

#include <cstdint>

#if defined(_MSC_VER)
#define RUNTIME_SERVICES_WAVE8_CDECL __cdecl
#else
#define RUNTIME_SERVICES_WAVE8_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_runtime_services_wave8 {

PresentationServicePublication g_presentation_service_publication{};
AnimationServicePublication g_animation_service_publication{};
LocaleServicePublication g_locale_service_publication{};

namespace {

template <typename Pointer>
Pointer pointer_from_word(TargetWord word) {
  return reinterpret_cast<Pointer>(static_cast<std::uintptr_t>(word));
}

}

extern "C" OpaquePresentationLayerManager* RUNTIME_SERVICES_WAVE8_CDECL
ui_layer_manager_get_0067ca90() {
  return pointer_from_word<OpaquePresentationLayerManager*>(
      g_presentation_service_publication.manager_015fcc48);
}

extern "C" OpaqueAnimationManager* RUNTIME_SERVICES_WAVE8_CDECL
anim_manager_get_0067cae0() {
  return pointer_from_word<OpaqueAnimationManager*>(
      g_animation_service_publication.manager_015fcc5c);
}

extern "C" OpaqueLocaleManager* RUNTIME_SERVICES_WAVE8_CDECL
app_locale_manager_get_0067de00() {
  return pointer_from_word<OpaqueLocaleManager*>(
      g_locale_service_publication.manager_015fd8f4);
}

}

#undef RUNTIME_SERVICES_WAVE8_CDECL
