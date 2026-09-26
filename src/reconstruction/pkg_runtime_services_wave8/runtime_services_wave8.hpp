#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "runtime services wave8 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define RUNTIME_SERVICES_WAVE8_CDECL __cdecl
#else
#define RUNTIME_SERVICES_WAVE8_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_runtime_services_wave8 {

using TargetWord = std::uint32_t;

static_assert(sizeof(TargetWord) == 4, "target words are 32-bit");
static_assert(sizeof(void*) == 4, "target pointers are 32-bit");

struct OpaquePresentationLayerManager;
struct OpaqueAnimationManager;
struct OpaqueLocaleManager;

struct PresentationServicePublication {
  TargetWord manager_015fcc48 = 0;
};

struct AnimationServicePublication {
  TargetWord manager_015fcc5c = 0;
};

struct LocaleServicePublication {
  TargetWord manager_015fd8f4 = 0;
};

static_assert(sizeof(PresentationServicePublication) == 4,
              "presentation publication width");
static_assert(sizeof(AnimationServicePublication) == 4,
              "animation publication width");
static_assert(sizeof(LocaleServicePublication) == 4,
              "locale publication width");

extern PresentationServicePublication g_presentation_service_publication;
extern AnimationServicePublication g_animation_service_publication;
extern LocaleServicePublication g_locale_service_publication;

extern "C" OpaquePresentationLayerManager* RUNTIME_SERVICES_WAVE8_CDECL
ui_layer_manager_get_0067ca90();

extern "C" OpaqueAnimationManager* RUNTIME_SERVICES_WAVE8_CDECL
anim_manager_get_0067cae0();

extern "C" OpaqueLocaleManager* RUNTIME_SERVICES_WAVE8_CDECL
app_locale_manager_get_0067de00();

static_assert(!std::is_same<OpaquePresentationLayerManager*,
                            OpaqueAnimationManager*>::value,
              "presentation service type separation");
static_assert(
    !std::is_same<OpaquePresentationLayerManager*, OpaqueLocaleManager*>::value,
    "presentation locale type separation");
static_assert(
    !std::is_same<OpaqueAnimationManager*, OpaqueLocaleManager*>::value,
    "animation locale type separation");

}

#undef RUNTIME_SERVICES_WAVE8_CDECL
