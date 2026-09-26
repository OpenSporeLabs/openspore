#include <cstdint>
#include <iostream>

#include "runtime_services_wave8.hpp"

namespace {

using namespace openspore::reconstruction::pkg_runtime_services_wave8;

int failures = 0;

void check(bool condition, const char* message) {
  if (!condition) {
    ++failures;
    std::cerr << message << '\n';
  }
}

template <typename Pointer>
TargetWord word_from_pointer(Pointer pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

void test_service_publications() {
  std::uint32_t presentation_word = 0x11111111u;
  std::uint32_t animation_word = 0x22222222u;
  std::uint32_t locale_word = 0x33333333u;

  g_presentation_service_publication.manager_015fcc48 =
      word_from_pointer(&presentation_word);
  g_animation_service_publication.manager_015fcc5c =
      word_from_pointer(&animation_word);
  g_locale_service_publication.manager_015fd8f4 =
      word_from_pointer(&locale_word);

  check(
      ui_layer_manager_get_0067ca90() ==
          reinterpret_cast<OpaquePresentationLayerManager*>(&presentation_word),
      "presentation slot identity");
  check(anim_manager_get_0067cae0() ==
            reinterpret_cast<OpaqueAnimationManager*>(&animation_word),
        "animation slot identity");
  check(app_locale_manager_get_0067de00() ==
            reinterpret_cast<OpaqueLocaleManager*>(&locale_word),
        "locale slot identity");

  g_presentation_service_publication.manager_015fcc48 = 0;
  check(ui_layer_manager_get_0067ca90() == nullptr,
        "presentation null publication");
  check(anim_manager_get_0067cae0() != nullptr,
        "animation publication remains independent");
  check(app_locale_manager_get_0067de00() != nullptr,
        "locale publication remains independent");

  g_animation_service_publication.manager_015fcc5c = 0;
  check(anim_manager_get_0067cae0() == nullptr, "animation null publication");
  check(app_locale_manager_get_0067de00() != nullptr,
        "locale publication remains independent");

  g_locale_service_publication.manager_015fd8f4 = 0;
  check(app_locale_manager_get_0067de00() == nullptr,
        "locale null publication");
}

}

int main() {
  test_service_publications();
  if (failures != 0) {
    std::cerr << failures << " failure(s)\n";
    return 1;
  }
  return 0;
}
