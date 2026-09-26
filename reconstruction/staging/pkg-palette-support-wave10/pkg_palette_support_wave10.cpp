#include "pkg_palette_support_wave10.hpp"

namespace openspore::reconstruction::pkg_palette_support_wave10 {
namespace {

constexpr std::uint32_t kTagValue = 0x13eb430U;
constexpr std::uint32_t kPageABytes = 0x84U;
constexpr std::uint32_t kPageBBytes = 0x90U;
constexpr std::uint32_t kPropertyArrayId = 0xf21e733cU;
constexpr std::uint32_t kPropertyKeyId = 0xb35d7835U;
constexpr std::uint32_t kPropertyProbeId = 0x0332b28bU;
constexpr std::uint32_t kPropertyGroupId = 0x02233661U;
constexpr std::uint32_t kPropertyInstanceId = 0xc46ec042U;
constexpr std::uint32_t kProbeHalfValue = 9U;
constexpr std::uint32_t kSlotPrefix = 0x406b6b00U;
constexpr std::uint32_t kSlotHeadToken = 0x013eb898U;
constexpr std::uint32_t kSlotTailToken = 0x00b1b104U;
constexpr std::uint32_t kBlockToken = 0x013eb394U;
constexpr std::uint32_t kMaskWord = 0xfffffffcU;
constexpr std::size_t kGateTableSlot = 0x3cU / 4U;
constexpr std::size_t kGateFlagSlot = 0x118U / 4U;
constexpr std::int32_t kSlotShift = 2;

OpaqueNode *node_of(void *object) {
  return reinterpret_cast<OpaqueNode *>(object);
}

OpaqueNodeVtable *node_vtable(const void *object) {
  return static_cast<OpaqueNodeVtable *>(
      *reinterpret_cast<void *const *>(object));
}

void retain_node(void *object) {
  if (object != nullptr) {
    node_vtable(object)->retain04(node_of(object));
  }
}

void release_node(void *object) {
  if (object != nullptr) {
    node_vtable(object)->release08(node_of(object));
  }
}

OpaqueVectorHost *lookup_host(void *object) {
  return reinterpret_cast<OpaqueVectorHost *>(object);
}

void *allocate(std::uint32_t bytes) {
  return unresolved_00f473a0(bytes, kTagValue, 0U, 0U, 0U, 0U);
}

OpaquePageB *build_page() {
  OpaquePageB *raw = static_cast<OpaquePageB *>(allocate(kPageBBytes));
  if (raw == nullptr) {
    return nullptr;
  }
  return unresolved_005c2020(raw);
}

std::int32_t slot_bytes(const OpaqueSlotVector &vector) {
  return static_cast<std::int32_t>(
      reinterpret_cast<const std::uint8_t *>(vector.end) -
      reinterpret_cast<const std::uint8_t *>(vector.begin));
}

std::int32_t slot_count(const OpaqueSlotVector &vector) {
  return slot_bytes(vector) >> kSlotShift;
}

const std::uint32_t *gate_flags() {
  return *reinterpret_cast<std::uint32_t *const *>(
      reinterpret_cast<const std::uint8_t *>(g_table_015fd918) +
      kGateTableSlot * 4U);
}

}

void *g_table_015fd918 = nullptr;

extern "C" std::uint32_t PKG_PALETTE_SUPPORT_THISCALL unresolved_005c5cc0(
    OpaqueSupport *self, OpaquePageA *first, OpaquePageB *second) {
  (void)self;
  const std::int32_t first_count = slot_count(first->host.field70);
  const std::int32_t second_count = slot_count(second->host.field0c);
  std::uint32_t visited = 0U;
  std::uint32_t matched = 0U;
  std::int32_t first_index = 0;
  while (first_index < first_count) {
    OpaqueEntryA *entry = static_cast<OpaqueEntryA *>(unresolved_005c7f00(
        &first->host, static_cast<std::uint32_t>(first_index)));
    if (entry != nullptr) {
      visited += 1U;
      std::int32_t second_index = 0;
      while (second_index < second_count) {
        OpaqueEntryB *group = unresolved_005c1ce0(
            &second->host, static_cast<std::uint32_t>(second_index));
        if (group->host.field5c == 1U) {
          const std::int32_t leaf_count = slot_count(group->host.field70);
          std::int32_t leaf_index = 0;
          while (leaf_index < leaf_count) {
            OpaqueLeaf *leaf = static_cast<OpaqueLeaf *>(unresolved_005c7f00(
                &group->host, static_cast<std::uint32_t>(leaf_index)));
            if (leaf != nullptr && leaf->key.field00 == entry->key.field00 &&
                leaf->key.field04 == entry->key.field04 &&
                leaf->key.field08 == entry->key.field08) {
              unresolved_005c6810(entry, &entry->key,
                                  static_cast<std::int32_t>(-1),
                                  entry->field20);
              matched += 1U;
              break;
            }
            leaf_index += 1;
          }
        }
        second_index += 1;
      }
    }
    first_index += 1;
  }
  return matched == visited ? 1U : 0U;
}

extern "C" void PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c6010(OpaqueSupport *self, OpaqueResourceEntry *source) {
  OpaqueService *service = unresolved_0067de30();
  OpaqueProperty *property = nullptr;
  if (property != nullptr) {
    property = nullptr;
    property->vtable->release04(property);
  }
  service->vtable->resolve2c(service, source->field00, source->field08,
                             &property);
  if (property == nullptr) {
    return;
  }
  std::int32_t count = 0;
  OpaqueResourceEntry entries[2]{};
  unresolved_006a0ae0(property, kPropertyArrayId, &count, entries);
  std::int32_t index = 0;
  while (index < count) {
    OpaqueResourceEntry *element = entries + static_cast<std::size_t>(index);
    index += 1;
    OpaquePageA *raw = static_cast<OpaquePageA *>(allocate(kPageABytes));
    OpaquePageA *page = raw != nullptr ? unresolved_005c7f50(raw) : nullptr;
    retain_node(page);
    if (!unresolved_005c8ad0(page, element, self->field30, self->field34,
                             self->field28, self->field2c)) {
      release_node(page);
    } else {
      OpaqueResourceEntry key{};
      key.field00 = page->host.field64;
      key.field04 = page->host.field68;
      key.field08 = page->host.field6c;
      OpaqueResourceEntry channel{};
      OpaqueService *inner = unresolved_0067de30();
      OpaqueProperty *owner = nullptr;
      if (owner != nullptr) {
        owner = nullptr;
        owner->vtable->release04(owner);
      }
      if (inner->vtable->resolve2c(inner, key.field00, key.field08, &owner)) {
        unresolved_006a1250(owner, kPropertyKeyId, &channel);
      }
      OpaquePageB *by_key = nullptr;
      OpaquePageB *by_channel = nullptr;
      OpaqueEntryB *found =
          unresolved_005c5df0(lookup_host(property), key.field04);
      if (found != nullptr) {
        retain_node(found);
        by_key = reinterpret_cast<OpaquePageB *>(
            reinterpret_cast<std::uint8_t *>(found));
      }
      if (channel.field00 != 0U) {
        OpaqueEntryB *alternate =
            unresolved_005c5df0(lookup_host(property), channel.field00);
        if (alternate != nullptr) {
          retain_node(alternate);
          by_channel = reinterpret_cast<OpaquePageB *>(
              reinterpret_cast<std::uint8_t *>(alternate));
        } else {
          OpaquePageB *built = build_page();
          if (built != nullptr) {
            retain_node(built);
            unresolved_005c1e20(built, &channel, self->field24);
            by_channel = built;
            unresolved_005c5f00(property, built);
          }
        }
      }
      if (by_key == nullptr) {
        OpaquePageB *fresh = build_page();
        if (fresh != nullptr) {
          retain_node(fresh);
          unresolved_005c1e20(fresh, &key, self->field24);
          by_key = fresh;
          if (by_channel == nullptr) {
            unresolved_005c5f00(property, fresh);
          }
        }
      }
      if (by_channel != nullptr && !unresolved_005c1d40(by_channel, by_key)) {
        unresolved_005c22b0(by_channel, by_key);
      }
      if (by_key != nullptr) {
        const std::uint32_t *gate = gate_flags();
        const std::uint32_t span =
            static_cast<std::uint32_t>(slot_bytes(by_key->host.field0c));
        std::uint32_t tally = 0U;
        const bool retained = gate[kGateFlagSlot] != 0U &&
                              (span & kMaskWord) != 0U &&
                              unresolved_005c5cc0(self, page, by_key) != 0U &&
                              unresolved_005c5c50(self, page, &tally) ==
                                  static_cast<std::int32_t>(tally);
        if (!retained) {
          unresolved_005c2390(by_key, node_of(page));
        }
      }
      release_node(by_channel);
      release_node(by_key);
      if (owner != nullptr) {
        owner->vtable->release04(owner);
      }
      release_node(page);
    }
  }
  property->vtable->release04(property);
}

extern "C" bool PKG_PALETTE_SUPPORT_THISCALL
unresolved_005c6340(OpaqueSupport *self, OpaqueResourceKey *ref,
                    std::uint32_t back_link, std::uint32_t unused_word,
                    std::uint32_t key_word0, std::uint32_t instance_word,
                    std::uint32_t key_word1, std::uint32_t key_word2) {
  (void)unused_word;
  self->field3c = back_link;
  OpaqueService *service = unresolved_0067de30();
  OpaqueProperty *property = nullptr;
  if (property != nullptr) {
    property = nullptr;
    property->vtable->release04(property);
  }
  service->vtable->resolve2c(service, ref->field00, ref->field08, &property);
  if (property == nullptr) {
    return false;
  }
  if (property->vtable->query24(property, ref, kPropertyProbeId) &&
      ref->field12 == kProbeHalfValue) {
    self->field38 = *unresolved_0041e990(ref);
  }
  unresolved_006a12e0(property, kPropertyGroupId, &self->field30);
  self->field34 = key_word0;
  if (instance_word != 0U) {
    self->field20 = instance_word;
  } else {
    unresolved_006a12a0(property, kPropertyInstanceId, &self->field20);
  }
  self->field24 = instance_word;
  self->field28 = key_word1;
  self->field2c = key_word2;
  OpaqueRegistry *registry = unresolved_008de1a0();
  OpaqueFilterContext context{};
  OpaqueFilterFrame frame{};
  frame.slot.field00 = kSlotHeadToken;
  frame.slot.field04 = static_cast<std::uint32_t>(-1);
  frame.slot.field08 =
      static_cast<std::uint32_t>(static_cast<std::uint8_t>(ref->field00)) |
      kSlotPrefix;
  frame.slot.field0c = kSlotTailToken;
  frame.slot.field10 = static_cast<std::uint32_t>(-1);
  frame.field10 = kBlockToken;
  registry->vtable->filter38(registry, &context, &frame, 0U);
  OpaqueResourceEntry *cursor = frame.list.field04;
  const OpaqueResourceEntry *const limit = frame.list.field00;
  while (cursor != limit) {
    unresolved_005c6010(self, cursor);
    cursor += 1;
  }
  if (cursor != nullptr && cursor[-1].field08 != 0U) {
    unresolved_00f47380(cursor);
  }
  property->vtable->release04(property);
  return true;
}

}
