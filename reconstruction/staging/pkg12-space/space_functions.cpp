#include "space_functions.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace openspore::reconstruction::pkg12_space {
namespace {

using Opaque = std::uintptr_t;
using TargetWord = std::uint32_t;

static_assert(sizeof(TargetWord) == 4, "PKG-12 target words are 32-bit");
static_assert(sizeof(std::int32_t) == 4,
              "PKG-12 signed target words are 32-bit");
static_assert(sizeof(float) == 4, "PKG-12 target floats are 32-bit");

// RE: These records describe the observed 32-bit machine ABI where ECX and
// caller-stack arguments cannot be expressed by the unresolved source
// boundary. Opaque is only a host carrier for target words and pointers.
struct Pkg12EcxOnly {
  Opaque ecx;
};

struct Pkg12Stack1 {
  Opaque ecx;
  Opaque stack0;
};

struct Pkg12StringRange {
  Opaque begin;
  Opaque end;
};

struct Pkg12Stack2 {
  Opaque ecx;
  Opaque stack0;
  Opaque stack1;
};

struct Pkg12Stack3 {
  Opaque ecx;
  Opaque stack0;
  Opaque stack1;
  Opaque stack2;
};

struct Pkg12Stack4 {
  Opaque ecx;
  Opaque stack0;
  Opaque stack1;
  Opaque stack2;
  Opaque stack3;
};

struct Pkg12D06240Call {
  Opaque ecx;
  Opaque space;
  Opaque selected;
  TargetWord code;
  float amount;
};

struct Pkg12C8ce40Call {
  Opaque context;
  float third_scale;
  TargetWord stack2;
  float second_scale;
  TargetWord stack4;
  float first_scale;
  TargetWord stack6;
};

struct Pkg12Ad79d0Call {
  Opaque ecx_destination;
  Opaque position;
  Opaque rotation;
};

struct Pkg12Vtable14Call {
  Opaque ecx;
  Opaque stack0;
  Opaque stack1;
  Opaque stack2;
};

struct Pkg12EventTailCall {
  Opaque ecx;
  Opaque stack0;
  Opaque stack1;
  Opaque stack2;
  Opaque stack3;
  Opaque stack4;
  Opaque stack5;
};

// RE: Direct callees remain source-like boundaries; no recovered SDK type is
// asserted.
extern "C" std::int32_t pkg12_re_00bba990(Pkg12EcxOnly call);
extern "C" Opaque pkg12_re_0102f810();
extern "C" std::int32_t pkg12_re_0102fa30(Pkg12Stack1 call);
extern "C" std::int32_t pkg12_re_0102ffc0(Pkg12EcxOnly call);
extern "C" std::int32_t pkg12_re_0102ff40(Pkg12EcxOnly call);
extern "C" std::int32_t pkg12_re_0102ff80(Pkg12EcxOnly call);
extern "C" Opaque pkg12_re_01021090();
extern "C" Opaque pkg12_re_00b3d2c0();
extern "C" void pkg12_re_00d06240(Pkg12D06240Call call);
extern "C" Opaque pkg12_re_00b3d2a0();
extern "C" Opaque pkg12_re_00ba6490(Pkg12EcxOnly call);
extern "C" Opaque pkg12_re_00ba9370(Pkg12Stack1 call);
extern "C" Opaque pkg12_re_00e39ab0(TargetWord code, Opaque source,
                                    void* position, void* rotation,
                                    Opaque context_object, Opaque value_6,
                                    void* output_position,
                                    void* output_rotation);
extern "C" float pkg12_re_01030600(Pkg12EcxOnly call);
extern "C" float pkg12_re_010305b0(Pkg12EcxOnly call);
extern "C" float pkg12_re_01030560(Pkg12EcxOnly call);
extern "C" void pkg12_re_00c8ce40(Pkg12C8ce40Call call);
extern "C" std::uint8_t pkg12_re_010383a0(Pkg12Stack1 call);
extern "C" void pkg12_re_01037e40(Pkg12Stack2 call);
extern "C" Opaque pkg12_re_00bbaa60(Pkg12Stack1 call);
extern "C" std::int32_t pkg12_re_00b8dab0(Pkg12EcxOnly call);
extern "C" void pkg12_re_00bb59b0(Pkg12Stack2 call);
extern "C" bool pkg12_re_00c70c00(Pkg12EcxOnly call);
extern "C" Opaque pkg12_re_00c71e70(Pkg12EcxOnly call);
extern "C" std::int32_t pkg12_re_00c705c0(Opaque value, std::int32_t amount);
extern "C" Opaque pkg12_re_00b3d4a0();
extern "C" void pkg12_re_00ae9140(Pkg12Stack1 call);
extern "C" std::int32_t pkg12_re_01021080();
extern "C" std::uint8_t pkg12_re_01044640();
extern "C" Opaque pkg12_re_0067dcc0();
extern "C" void pkg12_re_vtable_14(Pkg12Vtable14Call call);
extern "C" Opaque pkg12_re_00f473a0(TargetWord size, const char* domain,
                                    Opaque value_3, Opaque value_4,
                                    const char* allocator, TargetWord line);
extern "C" void pkg12_re_00aea230(Pkg12Stack1 call);
extern "C" void pkg12_re_00f47380(void* value);
extern "C" Opaque pkg12_re_01021230();
extern "C" Opaque pkg12_re_00c8b770(Pkg12EcxOnly call);
extern "C" Opaque pkg12_re_00ffbe50();
extern "C" Opaque pkg12_re_00a1ad60(Pkg12EcxOnly call);
extern "C" std::int32_t pkg12_re_00c70e00(Pkg12EcxOnly call);
extern "C" const float* pkg12_re_vtable_2c(Pkg12EcxOnly call);
extern "C" const float* pkg12_re_vtable_30(Pkg12EcxOnly call);
extern "C" void pkg12_re_00ad79d0(Pkg12Ad79d0Call call);
extern "C" float pkg12_re_vtable_70(Pkg12EcxOnly call);
extern "C" float pkg12_re_vtable_74(Pkg12EcxOnly call);
extern "C" Opaque pkg12_re_00b3d4d0();
extern "C" void pkg12_re_00ae09b0(Pkg12Stack3 call);
extern "C" void pkg12_re_00ad7ad0(Pkg12EcxOnly call);
extern "C" Opaque pkg12_re_00675250();
extern "C" void pkg12_re_00676e90(Pkg12Stack2 call);
extern "C" Opaque pkg12_re_01002bd0();
extern "C" Opaque pkg12_re_00bfc5f0(Pkg12EcxOnly call);
extern "C" void pkg12_re_00fe5430(Pkg12Stack2 call);
extern "C" Opaque pkg12_re_01021300();
extern "C" void pkg12_re_00c31a00(Pkg12Stack1 call);
extern "C" Opaque pkg12_re_01021260();
extern "C" Opaque pkg12_re_00ce6950(Pkg12Stack4 call);
extern "C" void pkg12_re_00aeb720(Pkg12EventTailCall call);
extern "C" void pkg12_re_vtable_4(Pkg12EcxOnly call);

std::uint32_t read_word32(const void* base, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset,
              sizeof(value));
  return value;
}

std::uint8_t read_byte(const void* base, std::size_t offset) {
  return static_cast<const unsigned char*>(base)[offset];
}

Opaque read_opaque_word(Opaque base, std::size_t offset) {
  return static_cast<Opaque>(
      read_word32(reinterpret_cast<const void*>(base), offset));
}

std::int32_t signed_bits(std::uint32_t value) {
  std::int32_t result = 0;
  std::memcpy(&result, &value, sizeof(result));
  return result;
}

std::int32_t sar32(std::uint32_t value, unsigned int shift) {
  static_assert(sizeof(TargetWord) == 4, "SAR operates on 32-bit target words");
  if (shift == 0) {
    return signed_bits(value);
  }
  if (shift >= 32) {
    return (value & 0x80000000u) != 0 ? -1 : 0;
  }
  const std::uint32_t sign_fill = (value & 0x80000000u) != 0 ? 0xffffffffu : 0u;
  const std::uint32_t shifted = (value >> shift) | (sign_fill << (32u - shift));
  return signed_bits(shifted);
}

std::uint32_t neg32(std::uint32_t value) {
  static_assert(sizeof(TargetWord) == 4, "NEG operates on 32-bit target words");
  return TargetWord{0} - value;
}

void store_float(void* word, float value) {
  std::memcpy(word, &value, sizeof(value));
}

void create_common_event(Space* space, std::uint32_t code) {
  // RE: 0x01021260 result, +0x13c, and ECX-held callee ownership are preserved.
  const Opaque owner = pkg12_re_01021260();
  const Opaque event_owner = read_opaque_word(owner, 0x13c);
  const Pkg12Stack4 event_stage{event_owner, 0xc8fbf7d7u, code, 0, 0};
  const Opaque event_data = pkg12_re_00ce6950(event_stage);
  const Opaque manager = pkg12_re_00b3d4a0();
  pkg12_re_00aeb720({manager, reinterpret_cast<Opaque>(space), event_data,
                     event_stage.stack0, event_stage.stack1, event_stage.stack2,
                     event_stage.stack3});
}

}  // namespace

void pkg12_space_0102d1b0(Space* space, SpaceContext* context,
                          std::uint32_t value) {
  // RE: The live prologue has no implicit this and keeps the three stack
  // dwords.
  const std::int32_t seed =
      pkg12_re_00bba990({reinterpret_cast<Opaque>(context)});
  std::uint32_t event_code = 0x92a95b57u;
  const Pkg12Stack1 selected_seed_stage{pkg12_re_0102f810(), 4u};
  const std::int32_t selected_seed = pkg12_re_0102fa30(selected_seed_stage);
  const bool selected_seed_matches =
      value == static_cast<std::uint32_t>(selected_seed);
  if (selected_seed_matches) {
    event_code = 0x57c98667u;
  }

  // RE: SUB is 32-bit; the subsequent CMP/JLE sequence compares signed values.
  const std::int32_t interval =
      signed_bits(value - static_cast<std::uint32_t>(seed));
  bool run_planet_work = false;
  const std::int32_t near_threshold = pkg12_re_0102ffc0({pkg12_re_0102f810()});
  if (near_threshold < interval) {
    const Opaque selected = pkg12_re_01021090();
    const Opaque selected_view = pkg12_re_00b3d2c0();
    pkg12_re_00d06240({selected_view, reinterpret_cast<Opaque>(space), selected,
                       0x055901b3u, 1.0F});
    event_code = 0xe8a568ecu;
    run_planet_work = true;
  } else {
    const std::int32_t middle_threshold =
        pkg12_re_0102ff40({pkg12_re_0102f810()});
    if (middle_threshold < interval) {
      event_code = 0x57c98667u;
      run_planet_work = true;
    } else if (!selected_seed_matches) {
      const std::int32_t far_threshold =
          pkg12_re_0102ff80({pkg12_re_0102f810()});
      if (far_threshold < interval) {
        event_code = 0x81034ee0u;
      } else {
        const Opaque selected = pkg12_re_01021090();
        const Opaque selected_view = pkg12_re_00b3d2c0();
        pkg12_re_00d06240({selected_view, reinterpret_cast<Opaque>(space),
                           selected, 0x05590199u, 1.0F});
        event_code = 0x92a95b57u;
      }
    } else {
      run_planet_work = true;
    }
  }

  if (run_planet_work) {
    // RE: Opaque word arrays preserve the Ghidra output locals without a
    // payload claim.
    TargetWord position_words[3]{};
    TargetWord rotation_words[3]{};
    TargetWord output_position_words[3]{};
    TargetWord output_rotation_words[3]{};
    const Opaque planet_view = pkg12_re_00b3d2a0();
    const Opaque planet_data =
        pkg12_re_00ba9370({planet_view, reinterpret_cast<Opaque>(space)});
    const Opaque context_object = read_word32(context, 0x70);
    pkg12_re_00e39ab0(0xfdd30461u, planet_data, position_words, rotation_words,
                      context_object, 0, output_position_words,
                      output_rotation_words);

    const float first_scale = pkg12_re_01030600({pkg12_re_0102f810()});
    const float second_scale = pkg12_re_010305b0({pkg12_re_0102f810()});
    const float third_scale = pkg12_re_01030560({pkg12_re_0102f810()});
    pkg12_re_00c8ce40({reinterpret_cast<Opaque>(context), third_scale, 1u,
                       second_scale, 1u, first_scale, 0u});
    (void)first_scale;
    (void)second_scale;

    const Opaque context_view = pkg12_re_00b3d2a0();
    const Opaque context_node = pkg12_re_00ba6490({context_view});
    pkg12_re_010383a0({context_node, reinterpret_cast<Opaque>(context)});

    const std::uint8_t count = read_byte(context, 0xac);
    for (std::uint32_t index = 0; index < count; ++index) {
      const Opaque object =
          pkg12_re_00bbaa60({reinterpret_cast<Opaque>(context), index});
      if (pkg12_re_00b8dab0({object}) == 5) {
        const Opaque owner = pkg12_re_00b3d2a0();
        pkg12_re_00bb59b0({owner, object, reinterpret_cast<Opaque>(&seed)});
        if (!pkg12_re_00c70c00({static_cast<Opaque>(seed)})) {
          pkg12_re_00c71e70({static_cast<Opaque>(seed)});
        }
        pkg12_re_00c705c0(object, 0x7fffffff);
      }
    }

    const Opaque cleanup_owner = pkg12_re_00b3d4a0();
    pkg12_re_00ae9140({cleanup_owner, context_object});

    const std::int32_t state = pkg12_re_01021080();
    if (state == 0) {
      pkg12_re_01044640();
      const Opaque service = pkg12_re_0067dcc0();
      pkg12_re_vtable_14({service, 0x678a3efu, 0, 0});

      const Opaque allocated = pkg12_re_00f473a0(
          0x26u, "Simulator", 0, 0,
          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_"
          "RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
          0xd1u);
      void* buffer = reinterpret_cast<void*>(allocated);
      std::memcpy(buffer, "SPG_SystemSurrender_Diplomatic_Planet", 0x25u);
      static_cast<unsigned char*>(buffer)[0x25] = 0;
      const Opaque string_end = allocated + 0x26u;
      const Pkg12StringRange string_range{allocated, string_end};
      const Opaque string_owner = pkg12_re_00b3d4a0();
      pkg12_re_00aea230(
          {string_owner, reinterpret_cast<Opaque>(&string_range)});
      if (string_end - allocated > 1 && allocated != 0) {
        pkg12_re_00f47380(buffer);
      }
    } else if (state == 1) {
      const Opaque simulation = pkg12_re_01021230();
      const Opaque list = pkg12_re_00c8b770({simulation});
      const Opaque service_token = pkg12_re_00ffbe50();
      const Opaque service = pkg12_re_00a1ad60({service_token});
      const Opaque service_position = service + 0x34u;
      const float* origin = pkg12_re_vtable_2c({service_position});
      const Opaque list_begin = read_opaque_word(list, 0x10);
      const Opaque list_end = read_opaque_word(list, 0x14);
      const std::int32_t count =
          sar32(static_cast<std::uint32_t>(list_end) -
                    static_cast<std::uint32_t>(list_begin),
                2);
      Opaque selected = 0;

      for (std::int32_t index = 0; index < count; ++index) {
        const Opaque entry =
            read_opaque_word(list_begin, static_cast<std::size_t>(index) *
                                             sizeof(std::uint32_t));
        if (pkg12_re_00c70e00({entry}) == 5) {
          const float* candidate = pkg12_re_vtable_2c({entry});
          const float dx = origin[0] - candidate[0];
          const float dz = origin[2] - candidate[2];
          const float dy = origin[1] - candidate[1];
          const float distance = dx * dx + dz * dz + dy * dy;
          if (distance < 3.4028235e+38F) {
            selected = entry;
          }
        }
      }

      if (selected != 0) {
        TargetWord selected_position[3]{};
        TargetWord selected_rotation[4]{};
        TargetWord event_state[12]{};
        const float* position = pkg12_re_vtable_2c({selected});
        const float* rotation = pkg12_re_vtable_30({selected});
        store_float(&selected_position[0], position[0]);
        store_float(&selected_position[1], position[1]);
        store_float(&selected_position[2], position[2]);
        store_float(&selected_rotation[0], rotation[0]);
        store_float(&selected_rotation[1], rotation[1]);
        store_float(&selected_rotation[2], rotation[2]);
        store_float(&selected_rotation[3], rotation[3]);
        pkg12_re_00ad79d0({reinterpret_cast<Opaque>(event_state),
                           reinterpret_cast<Opaque>(selected_position),
                           reinterpret_cast<Opaque>(selected_rotation)});
        const float vtable_70_value = pkg12_re_vtable_70({selected});
        const float vtable_74_value = pkg12_re_vtable_74({selected});
        store_float(&event_state[7], vtable_74_value);
        store_float(&event_state[8], vtable_70_value);

        const Opaque trading = pkg12_re_00b3d4d0();
        pkg12_re_00ae09b0(
            {trading, 0x5f848353u, reinterpret_cast<Opaque>(event_state), 0});

        const Opaque allocated = pkg12_re_00f473a0(
            0x25u, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_"
            "RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1u);
        void* buffer = reinterpret_cast<void*>(allocated);
        std::memcpy(buffer, "SPG_SystemSurrender_Diplomatic_Solar", 0x24u);
        static_cast<unsigned char*>(buffer)[0x24] = 0;
        const Opaque string_end = allocated + 0x25u;
        const Pkg12StringRange string_range{allocated, string_end};
        const Opaque string_owner = pkg12_re_00b3d4a0();
        pkg12_re_00aea230(
            {string_owner, reinterpret_cast<Opaque>(&string_range)});
        if (string_end - allocated > 1 && allocated != 0) {
          pkg12_re_00f47380(buffer);
        }
        pkg12_re_00ad7ad0({reinterpret_cast<Opaque>(event_state)});
      }
    }

    const Opaque manager = pkg12_re_00675250();
    pkg12_re_00676e90({manager, 0xd3f14a26u, 1u});
    const Pkg12Stack2 flag_stage{pkg12_re_01002bd0(), 0x1au, 1u};
    const Opaque flag_value = pkg12_re_00bfc5f0({flag_stage.ecx});
    pkg12_re_00fe5430({flag_value, flag_stage.stack0, flag_stage.stack1});
    const Opaque c31_owner = pkg12_re_01021300();
    pkg12_re_00c31a00({c31_owner, static_cast<Opaque>(neg32(value))});

    // RE: The service object and its 32-bit cleanup mask are one contiguous
    // opaque object; no separate cleanup_slots array is present.
    TargetWord service_object[65]{};
    service_object[0] = 0x13eb844u;
    service_object[1] = 0;
    service_object[2] = read_word32(context, 0x70);
    service_object[12] = 0xf46092d2u;
    service_object[14] = 0;
    const Opaque service = pkg12_re_0067dcc0();
    pkg12_re_vtable_14({service, service_object[12],
                        reinterpret_cast<Opaque>(service_object), 0});
    const TargetWord cleanup_mask = static_cast<TargetWord>(service_object[14]);
    for (std::uint32_t bit = 0; bit < 32u; ++bit) {
      const Opaque slot = service_object[2u + bit * 2u];
      if ((cleanup_mask & (TargetWord{1} << bit)) != 0 && slot != 0) {
        pkg12_re_vtable_4({slot});
      }
    }
  } else {
    // RE: The short path performs the +0x70 object lookup and cleanup before
    // the tail.
    const Opaque context_object = read_word32(context, 0x70);
    const Opaque context_view = pkg12_re_00b3d2a0();
    const Opaque context_node = pkg12_re_00ba6490({context_view});
    pkg12_re_01037e40(
        {context_node, context_object, reinterpret_cast<Opaque>(space)});
  }

  create_common_event(space, event_code);
}

}  // namespace openspore::reconstruction::pkg12_space
