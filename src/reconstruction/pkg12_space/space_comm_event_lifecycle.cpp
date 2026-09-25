#include "space_comm_event_lifecycle.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg12_space {
namespace {

void* at_offset(void* base, std::size_t offset) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(base) +
                                 offset);
}

const void* at_offset(const void* base, std::size_t offset) {
  return reinterpret_cast<const void*>(reinterpret_cast<std::uintptr_t>(base) +
                                       offset);
}

std::uint32_t read_word(const void* base, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, at_offset(base, offset), sizeof(value));
  return value;
}

void write_word(void* base, std::size_t offset, std::uint32_t value) {
  std::memcpy(at_offset(base, offset), &value, sizeof(value));
}

void write_byte(void* base, std::size_t offset, std::uint8_t value) {
  std::memcpy(at_offset(base, offset), &value, sizeof(value));
}

cCommEvent* event_from_word(OpaqueWord value) {
  return reinterpret_cast<cCommEvent*>(value);
}

cCommEvent** event_slot(OpaqueWord value) {
  return reinterpret_cast<cCommEvent**>(value);
}

void add_ref(cCommEvent* event) {
  if (event != nullptr) {
    pkg12_re_event_add_ref(event);
  }
}

void release(cCommEvent* event) {
  if (event != nullptr) {
    pkg12_re_event_release(event);
  }
}

}

extern "C" void __attribute__((fastcall)) pkg12_re_00aea250(cCommEvent* self) {
  write_word(self, 0x04, 0x013ef094u);
  write_word(self, 0x08, 0u);
  write_word(self, 0x00, 0x0145bed8u);
  write_word(self, 0x04, 0x0145bed4u);
  write_word(self, 0x10, 0u);
  write_word(self, 0x14, 0u);
  write_word(self, 0x0c, UINT32_MAX);
  write_word(self, 0x18, UINT32_MAX);
  write_word(self, 0x1c, UINT32_MAX);
  write_word(self, 0x20, 0u);
  write_word(self, 0x24, 0u);
  write_word(self, 0x28, 0u);
  write_word(self, 0x2c, 0u);
  write_byte(self, 0x30, 0u);
  write_word(self, 0x34, UINT32_MAX);
  write_word(self, 0x38, UINT32_MAX);
  write_word(self, 0x3c, UINT32_MAX);
  write_word(self, 0x40, 0u);
  write_word(self, 0x44, UINT32_MAX);
  write_word(self, 0x48, 0u);
  write_word(self, 0x4c, 0u);
  write_word(self, 0x50, 0u);
  write_word(self, 0x54, 0u);
  write_word(self, 0x58, 0u);
  write_word(self, 0x64, 0u);
  write_word(self, 0x68, 0u);
  write_word(self, 0x6c, 0u);
  write_word(self, 0x78, 0u);
  write_word(self, 0x7c, 0u);
  write_word(self, 0x80, 0u);
  write_word(self, 0x8c, 0u);
  write_word(self, 0x90, 0u);
  write_word(self, 0x94, 0u);
}

extern "C" void __thiscall pkg12_re_00aea5d0(cCommVector* vector,
                                             cCommEvent** position,
                                             cCommEvent** value) {
  const OpaqueWord begin = vector->begin;
  const OpaqueWord end = vector->end;
  const OpaqueWord capacity = vector->capacity;

  if (end != capacity) {
    if (reinterpret_cast<OpaqueWord>(position) <=
            reinterpret_cast<OpaqueWord>(value) &&
        reinterpret_cast<OpaqueWord>(value) < end) {
      value = reinterpret_cast<cCommEvent**>(
          reinterpret_cast<OpaqueWord>(value) + sizeof(cCommEvent*));
    }

    cCommEvent** last = event_slot(end - sizeof(cCommEvent*));
    if (end != 0u) {
      cCommEvent* previous = *last;
      *event_slot(end) = previous;
      add_ref(previous);
    }

    static_cast<void>(pkg12_re_00ac97a0(position, last, event_slot(end)));

    cCommEvent* inserted = *value;
    cCommEvent* previous = *position;
    if (inserted != previous) {
      add_ref(inserted);
      *position = inserted;
      release(previous);
    }
    vector->end = end + sizeof(cCommEvent*);
    return;
  }

  OpaqueWord count = (end - begin) >> 2u;
  if (count == 0u) {
    count = 1u;
  } else {
    count *= 2u;
  }

  OpaqueWord allocated = 0u;
  if (count != 0u) {
    allocated = pkg12_re_00f473a0(
        static_cast<std::size_t>(count * sizeof(cCommEvent*)), "Simulator", 0u,
        0u,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
        "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1u);
  }

  const OpaqueWord position_word = reinterpret_cast<OpaqueWord>(position);
  const OpaqueWord prefix_size = position_word - begin;
  pkg12_re_011e0744(event_from_word(allocated),
                    reinterpret_cast<const void*>(begin),
                    static_cast<std::size_t>(prefix_size));

  cCommEvent** new_end =
      event_slot(allocated + ((prefix_size >> 2u) * sizeof(cCommEvent*)));
  if (new_end != nullptr) {
    cCommEvent* inserted = *value;
    *new_end = inserted;
    add_ref(inserted);
  }

  const OpaqueWord tail_size = end - position_word;
  void* tail = at_offset(new_end, sizeof(cCommEvent*));
  pkg12_re_011e0744(tail, position, static_cast<std::size_t>(tail_size));

  if (begin != 0u && read_word(reinterpret_cast<void*>(begin - 4u), 0u) != 0u) {
    pkg12_re_00f47380(begin);
  }

  vector->begin = allocated;
  vector->end = reinterpret_cast<OpaqueWord>(tail) + tail_size;
  vector->capacity = allocated + count * sizeof(cCommEvent*);
}

extern "C" void* __thiscall pkg12_re_00aea230(cCommManager* manager,
                                              cCommStringRange* range) {
  void* target = at_offset(manager, 0x64u);
  if (range == reinterpret_cast<cCommStringRange*>(target)) {
    return range;
  }
  return pkg12_re_00454cb0(target, range->begin, range->end);
}

extern "C" cCommEvent* __thiscall pkg12_re_00aeb160(
    cCommManager* manager, OpaqueWord payload0, OpaqueWord payload1,
    OpaqueWord payload2, OpaqueWord payload3, OpaqueWord payload4,
    OpaqueWord payload5, OpaqueWord payload6) {
  cCommEvent* event = event_from_word(
      pkg12_re_00f473a0(0xa0u, "Simulator", 0u, 0u, nullptr, 0u));
  if (event != nullptr) {
    pkg12_re_00aea250(event);
  }

  write_word(event, 0x18, static_cast<std::uint32_t>(payload0));
  write_word(event, 0x0c, 0u);
  write_word(event, 0x34, static_cast<std::uint32_t>(payload1));
  write_word(event, 0x38, static_cast<std::uint32_t>(payload2));
  write_word(event, 0x3c, static_cast<std::uint32_t>(payload3));

  const OpaqueWord old_payload_word = read_word(event, 0x40u);
  if (payload4 != old_payload_word) {
    add_ref(event_from_word(payload4));
    write_word(event, 0x40, static_cast<std::uint32_t>(payload4));
    release(event_from_word(old_payload_word));
  }

  write_word(event, 0x44, static_cast<std::uint32_t>(payload5));
  write_word(event, 0x48, static_cast<std::uint32_t>(payload6));
  add_ref(event);

  cCommVector* vector =
      reinterpret_cast<cCommVector*>(at_offset(manager, 0x24u));
  const OpaqueWord end = vector->end;
  if (end < vector->capacity) {
    vector->end = end + sizeof(cCommEvent*);
    if (end != 0u) {
      *event_slot(end) = event;
      add_ref(event);
    }
  } else {
    cCommEvent* value = event;
    pkg12_re_00aea5d0(vector, event_slot(end), &value);
  }

  release(event);
  return event;
}

}
