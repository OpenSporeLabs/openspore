#include "app_lifecycle_wave7.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_APP_LIFECYCLE_THISCALL __thiscall
#define PKG_APP_LIFECYCLE_CDECL __cdecl
#else
#define PKG_APP_LIFECYCLE_THISCALL __attribute__((thiscall))
#define PKG_APP_LIFECYCLE_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_app_lifecycle_wave7 {

AppLifecyclePorts g_app_lifecycle_ports{};
EffectCollectionPorts g_effect_collection_ports{};

namespace {

struct EffectCollectionContinuation {
  const char* saved_input;
  OpaqueWord* saved_output_at_esp_10;
  bool first_compare_equal;

  ~EffectCollectionContinuation() {
    saved_input = nullptr;
    saved_output_at_esp_10 = nullptr;
    first_compare_equal = false;
  }
};

void set_effect_collection_ids(OpaqueWord* group_ids) {
  EffectCollectionPorts& ports = g_effect_collection_ports;
  group_ids[0] = ports.layer_manager_0067ca90();
  group_ids[1] = ports.app_system_0067dcc0();
  group_ids[2] = ports.service_0067caa0();
  group_ids[3] = ports.renderer_0067dd10();
  group_ids[4] = ports.lighting_0067dd50();
  group_ids[5] = ports.shadow_world_0067dd80();
  group_ids[6] = ports.effects_0067dd90();
  group_ids[7] = ports.service_0067ddd0();
  group_ids[8] = ports.service_0067cb20();
  group_ids[9] = ports.object_template_db_0067cb00();
  group_ids[11] = ports.service_0067de30();
  group_ids[12] = ports.service_0067ddb0();
  group_ids[13] = ports.service_0067cb50();
  group_ids[14] = ports.service_0067cb60();
  group_ids[10] = ports.service_0067cb70();
  group_ids[15] = ports.service_0067cb80();
}

std::uint8_t effect_collection_continuation_007e6130(
    const EffectCollectionContinuation& continuation) {
  if (continuation.first_compare_equal) {
    continuation.saved_output_at_esp_10[0] = 0x0153f864u;
    return 1u;
  }
  if (std::strcmp(continuation.saved_input, "GetAppPluginServices") != 0) {
    return 0u;
  }
  set_effect_collection_ids(continuation.saved_output_at_esp_10);
  return 1u;
}

}

extern "C" __attribute__((visibility("hidden"))) std::uint8_t
app_lifecycle_effect_model_007e6100(const char* instance_ids,
                                     OpaqueWord* group_ids) {
  if (std::strcmp(instance_ids, "GetSharedLibraryVersion") == 0) {
    group_ids[0] = 0x0153f864u;
    return 1u;
  }
  EffectCollectionContinuation continuation{instance_ids, group_ids, false};
  return effect_collection_continuation_007e6130(continuation);
}

extern "C" std::uint8_t PKG_APP_LIFECYCLE_THISCALL
app_cAppSystem_hook_windows_007e6080(OpaqueAppSystem* system) {
  return g_app_lifecycle_ports.hook_windows_00929bd0(system);
}

#if defined(_MSC_VER)
extern "C" __declspec(naked) __cdecl std::uint8_t
app_cAppSystem_set_effect_collection_ids_007e6100(const char* instance_ids,
                                                   OpaqueWord* group_ids) {
  __asm {
    push esi
    mov esi, dword ptr [esp + 8]
    mov edx, dword ptr [esp + 12]
    push edx
    push esi
    call app_lifecycle_effect_model_007e6100
    add esp, 8
    pop esi
    ret
  }
}
#elif defined(__GNUC__) || defined(__clang__)
extern "C" __attribute__((naked, cdecl)) std::uint8_t
app_cAppSystem_set_effect_collection_ids_007e6100(const char* instance_ids,
                                                   OpaqueWord* group_ids) {
  __asm__("pushl %esi\n\t"
          "movl 8(%esp), %esi\n\t"
          "movl 12(%esp), %edx\n\t"
          "pushl %edx\n\t"
          "pushl %esi\n\t"
          "call app_lifecycle_effect_model_007e6100\n\t"
          "addl $8, %esp\n\t"
          "popl %esi\n\t"
          "ret\n\t");
}
#endif

#if defined(_MSC_VER)
extern "C" __declspec(naked) std::uint32_t __thiscall
app_cAppSystem_func88h_00a6c940(OpaqueAppSystem* system, std::int32_t index,
                                std::uint8_t enabled) {
  __asm {
    mov edx, ecx
    mov ecx, dword ptr [esp + 4]
    cmp ecx, 20h
    jge invalid
    mov eax, 1
    shl eax, cl
    cmp byte ptr [esp + 8], 0
    je clear
    or dword ptr [edx + 68h], eax
    ret 8
  clear:
    not eax
    and dword ptr [edx + 68h], eax
  invalid:
    ret 8
  }
}
#elif defined(__GNUC__) || defined(__clang__)
extern "C" __attribute__((naked, thiscall)) std::uint32_t
app_cAppSystem_func88h_00a6c940(OpaqueAppSystem* system, std::int32_t index,
                                std::uint8_t enabled) {
  __asm__("movl %ecx, %edx\n\t"
          "movl 4(%esp), %ecx\n\t"
          "cmpl $0x20, %ecx\n\t"
          "jge 1f\n\t"
          "movl $1, %eax\n\t"
          "shll %cl, %eax\n\t"
          "cmpb $0, 8(%esp)\n\t"
          "jz 2f\n\t"
          "orl %eax, 0x68(%edx)\n\t"
          "ret $8\n\t"
          "2:\n\t"
          "notl %eax\n\t"
          "andl %eax, 0x68(%edx)\n\t"
          "1:\n\t"
          "ret $8\n\t");
}
#endif

}

#undef PKG_APP_LIFECYCLE_CDECL
#undef PKG_APP_LIFECYCLE_THISCALL
