#include "app_wave11.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_app_wave11 {
namespace {

template <typename T>
T *at(TargetWord address) {
  return reinterpret_cast<T *>(static_cast<std::uintptr_t>(address));
}

TargetWord address_of(const void *pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

TargetSigned span_of(TargetWord high, TargetWord low) {
  return static_cast<TargetSigned>(high) - static_cast<TargetSigned>(low);
}

TargetHalf load_half(TargetWord address) {
  TargetHalf value = 0u;
  std::memcpy(&value, at<void>(address), sizeof(value));
  return value;
}

void store_byte(TargetWord address, TargetByte value) {
  std::memcpy(at<void>(address), &value, sizeof(value));
}

void store_half(TargetWord address, TargetHalf value) {
  std::memcpy(at<void>(address), &value, sizeof(value));
}

TargetWord load_word(TargetWord address) {
  TargetWord value = 0u;
  std::memcpy(&value, at<void>(address), sizeof(value));
  return value;
}

void store_word(TargetWord address, TargetWord value) {
  std::memcpy(at<void>(address), &value, sizeof(value));
}

TargetFloat load_float(TargetWord address) {
  TargetFloat value = 0.0f;
  std::memcpy(&value, at<void>(address), sizeof(value));
  return value;
}

void store_float(TargetWord address, TargetFloat value) {
  std::memcpy(at<void>(address), &value, sizeof(value));
}

void clear_bytes(TargetWord address, std::size_t span) {
  std::memset(at<void>(address), 0, span);
}

TargetWord copy_span(TargetWord destination, TargetWord source,
                     TargetWord span) {
  std::memcpy(at<void>(destination), at<void>(source), span);
  return destination;
}

void move_bytes(TargetWord destination, TargetWord source, TargetWord span) {
  std::memmove(at<void>(destination), at<void>(source), span);
}

void PKG_APP_WAVE11_THISCALL default_notify_0093db80(OpaquePropertyRecord *,
                                                     TargetByte) {
}

TargetByte PKG_APP_WAVE11_THISCALL
default_store_0093dd80(OpaquePropertyRecord *, TargetSigned, TargetWord, void *,
                       TargetSigned, TargetSigned) {
  return 0u;
}

OpaquePropertyRecord *PKG_APP_WAVE11_THISCALL
default_insert_00423650(OpaquePropertyRecord *receiver, void *, TargetWord) {
  return receiver;
}

TargetWord PKG_APP_WAVE11_FASTCALL
default_find_root_0043c0a0(const OpaquePartList *) {
  return 0u;
}

TargetSigned PKG_APP_WAVE11_THISCALL
default_find_key_0043c120(const OpaquePartList *, TargetWord) {
  return -1;
}

void PKG_APP_WAVE11_FASTCALL
default_word_construct_00533360(OpaqueWordVector *vector) {
  std::memset(vector, 0, sizeof(*vector));
  const TargetWord inline_base = address_of(vector->payload_18.data());
  vector->first = inline_base;
  vector->last = inline_base;
  vector->limit = inline_base + 0x20u;
  vector->inline_sentinel = inline_base;
}

void PKG_APP_WAVE11_THISCALL default_reserve_00454b80(OpaqueWordVector *vector,
                                                      TargetWord count) {
  vector->last = vector->first + count * sizeof(TargetWord);
}

OpaqueWordVector *PKG_APP_WAVE11_THISCALL
default_pair_insert_00454cb0(TargetWord address, TargetWord, TargetWord) {
  return at<OpaqueWordVector>(address);
}

void PKG_APP_WAVE11_THISCALL default_pair_reserve_00454640(OpaqueAssocBlob *,
                                                           TargetWord) {
}

TargetWord *PKG_APP_WAVE11_THISCALL
default_pair_slot_00454750(OpaqueAssocBlob *blob, const TargetWord *key) {
  return reinterpret_cast<TargetWord *>(blob->opaque_00_9b.data()) +
         (*key & 0x3u);
}

OpaqueTreeBlob *PKG_APP_WAVE11_THISCALL default_tree_insert_004544d0(
    OpaqueTreeBlob *tree, const TargetWord *, const OpaqueWordPair *) {
  return tree;
}

void PKG_APP_WAVE11_THISCALL default_node_append_005402c0(OpaqueTreeBlob *) {
}

void PKG_APP_WAVE11_FASTCALL default_release_004c0b80(OpaqueWordVector *) {
}

TargetWord PKG_APP_WAVE11_CDECL default_array_bool_006a0760(
    void *, TargetWord, std::size_t *count, const TargetByte **values) {
  *count = 0u;
  *values = nullptr;
  return 0u;
}

TargetByte PKG_APP_WAVE11_THISCALL
default_has_property_00447150(OpaqueVtableHolder *, TargetWord) {
  return 0u;
}

const OpaquePropertyRecord *PKG_APP_WAVE11_THISCALL
default_get_property_00447150(OpaqueVtableHolder *, TargetWord) {
  return nullptr;
}

TargetWord PKG_APP_WAVE11_CDECL default_global_key_015d(void) {
  return 0u;
}

TargetWord PKG_APP_WAVE11_CDECL default_allocate_0042dee0(TargetWord,
                                                          TargetWord,
                                                          TargetWord,
                                                          TargetWord) {
  return 0u;
}

void PKG_APP_WAVE11_CDECL default_release_00f47380(TargetWord) {
}

TargetWord PKG_APP_WAVE11_CDECL default_lookup_004b0010(TargetWord) {
  return 0u;
}

TargetWord PKG_APP_WAVE11_CDECL default_classify_004bb860(TargetWord) {
  return 0u;
}

void PKG_APP_WAVE11_THISCALL default_record_grow_004afdd0(OpaqueSlotVector *,
                                                          TargetWord) {
}

void PKG_APP_WAVE11_THISCALL default_record_reserve_004afd00(OpaqueSlotVector *,
                                                             TargetWord) {
}

void PKG_APP_WAVE11_THISCALL default_weight_reserve_004afc80(TargetWord,
                                                             TargetWord) {
}

void PKG_APP_WAVE11_THISCALL default_key_reserve_004cd3c0(TargetWord,
                                                          TargetWord) {
}

TargetWord PKG_APP_WAVE11_FASTCALL default_element_gate_0044f220(TargetWord) {
  return 0u;
}

void PKG_APP_WAVE11_THISCALL default_push_004b7290(OpaquePairVector *,
                                                   TargetWord, TargetWord,
                                                   TargetByte) {
}

TargetWord PKG_APP_WAVE11_CDECL default_stream_lookup_004c0500(TargetWord) {
  return 0u;
}

TargetWord PKG_APP_WAVE11_CDECL default_stream_read_004bf430(TargetWord,
                                                             TargetWord) {
  return 0u;
}

TargetByte PKG_APP_WAVE11_CDECL default_stream_apply_004bc6d0(TargetWord,
                                                              TargetWord,
                                                              TargetWord) {
  return 0u;
}

TargetWord PKG_APP_WAVE11_CDECL default_stream_report_006ac0a0(TargetWord,
                                                               TargetWord) {
  return 0u;
}

TargetWord PKG_APP_WAVE11_THISCALL
default_holder_probe_004bc540(OpaqueVtableHolder *) {
  return 0u;
}

TargetWord PKG_APP_WAVE11_THISCALL
default_holder_resolve_004bc540(OpaqueVtableHolder *, TargetWord) {
  return 0u;
}

TargetByte stale_slot_004b62a0() {
  static TargetByte slot = 0u;
  return slot;
}

TargetWord element_count_of(const OpaquePartList *receiver) {
  return sar_count(
      span_of(receiver->elements_last_6d0, receiver->elements_first_6cc), 2);
}

TargetWord part_entry_at(const OpaquePartList *receiver, TargetWord index) {
  return load_word(receiver->elements_first_6cc + index * sizeof(TargetWord));
}

TargetWord vector_size(const OpaqueWordVector *vector) {
  return sar_count(span_of(vector->last, vector->first), 2);
}

void model_apply_link_values(OpaquePartList *receiver,
                             OpaqueVtableHolder *service, TargetWord code,
                             TargetWord count) {
  OpaquePropertyPorts &ports = property_runtime().ports;
  if (ports.has_property_00447150(service, code) == 0u) {
    return;
  }
  const OpaquePropertyRecord *const record =
      ports.get_property_00447150(service, code);
  const TargetWord span = array_kind(record);
  const TargetWord *const data = array_data(record);
  for (TargetWord i = 0u; i < span; ++i) {
    const TargetWord head = data[i * 3u];
    const TargetWord middle = data[i * 3u + 1u];
    const TargetWord tail = data[i * 3u + 2u];
    for (TargetWord j = 0u; j < count; ++j) {
      OpaquePartEntry *const entry =
          at<OpaquePartEntry>(part_entry_at(receiver, j));
      if (entry->key_8c != tail) {
        continue;
      }
      entry->link_value_ac = head;
      if (head == kLinkValueSentinel) {
        entry->link_value_b0 = middle;
      }
    }
  }
}

TargetWord stage_resolve_index(TargetWord reference, TargetWord owner,
                               TargetWord elements, TargetWord count) {
  if (reference == 0u || reference == owner) {
    return kNoIndex;
  }
  const TargetWord index = load_word(reference + 0xe04u);
  if (index >= count) {
    return kNoIndex;
  }
  if (load_word(elements + index * sizeof(TargetWord)) != reference) {
    return kNoIndex;
  }
  return index;
}

}  // namespace

TargetWord array_kind(const OpaquePropertyRecord *record) {
  if (array_mask(record->flags_10) != 0u) {
    return record->slot_08;
  }
  return record->kind_12 != 0u ? 1u : 0u;
}

const TargetWord *array_data(const OpaquePropertyRecord *record) {
  if (array_mask(record->flags_10) != 0u) {
    return at<const TargetWord>(record->slot_00);
  }
  if (record->kind_12 != 0u) {
    return reinterpret_cast<const TargetWord *>(record);
  }
  return nullptr;
}

TargetByte record_bit(const OpaqueStageEntry *entry, TargetWord bit) {
  if (bit >= kBitSpan) {
    return 0u;
  }
  const TargetWord word =
      load_word(address_of(entry) + 0xdc8u + (bit >> 5) * sizeof(TargetWord));
  return static_cast<TargetByte>((word >> (bit & 31u)) & 1u);
}

OpaquePropertyRuntime &property_runtime() {
  static OpaquePropertyRuntime runtime{[] {
    OpaquePropertyPorts ports{};
    ports.notify_0093db80 = default_notify_0093db80;
    ports.store_0093dd80 = default_store_0093dd80;
    ports.insert_00423650 = default_insert_00423650;
    ports.find_root_0043c0a0 = default_find_root_0043c0a0;
    ports.find_key_0043c120 = default_find_key_0043c120;
    ports.reserve_00454b80 = default_reserve_00454b80;
    ports.pair_insert_00454cb0 = default_pair_insert_00454cb0;
    ports.pair_reserve_00454640 = default_pair_reserve_00454640;
    ports.pair_slot_00454750 = default_pair_slot_00454750;
    ports.tree_insert_004544d0 = default_tree_insert_004544d0;
    ports.node_append_005402c0 = default_node_append_005402c0;
    ports.release_004c0b80 = default_release_004c0b80;
    ports.array_bool_006a0760 = default_array_bool_006a0760;
    ports.has_property_00447150 = default_has_property_00447150;
    ports.get_property_00447150 = default_get_property_00447150;
    ports.global_key_015d25b0 = default_global_key_015d;
    ports.global_key_015d2180 = default_global_key_015d;
    ports.global_key_015d22a4 = default_global_key_015d;
    return ports;
  }()};
  return runtime;
}

OpaqueSlotRuntime &slot_runtime() {
  static OpaqueSlotRuntime runtime{[] {
    OpaqueSlotPorts ports{};
    ports.allocate_0042dee0 = default_allocate_0042dee0;
    ports.release_00f47380 = default_release_00f47380;
    ports.lookup_004b0010 = default_lookup_004b0010;
    ports.classify_004bb860 = default_classify_004bb860;
    ports.record_grow_004afdd0 = default_record_grow_004afdd0;
    ports.record_reserve_004afd00 = default_record_reserve_004afd00;
    ports.weight_reserve_004afc80 = default_weight_reserve_004afc80;
    ports.key_reserve_004cd3c0 = default_key_reserve_004cd3c0;
    ports.element_gate_0044f220 = default_element_gate_0044f220;
    ports.push_004b7290 = default_push_004b7290;
    return ports;
  }()};
  return runtime;
}

OpaqueStreamRuntime &stream_runtime() {
  static OpaqueStreamRuntime runtime{[] {
    OpaqueStreamPorts ports{};
    ports.lookup_004c0500 = default_stream_lookup_004c0500;
    ports.read_004bf430 = default_stream_read_004bf430;
    ports.apply_004bc6d0 = default_stream_apply_004bc6d0;
    ports.report_006ac0a0 = default_stream_report_006ac0a0;
    ports.probe_004bc540 = default_holder_probe_004bc540;
    ports.resolve_004bc540 = default_holder_resolve_004bc540;
    return ports;
  }()};
  return runtime;
}

OpaquePropertyRecord *PKG_APP_WAVE11_THISCALL
property_record_assign_pair_004279d0(OpaquePropertyRecord *receiver,
                                     void *source) {
  OpaquePropertyPorts &ports = property_runtime().ports;
  if ((receiver->flags_10 & kFlagLocked) != 0u) {
    ports.notify_0093db80(receiver, 1u);
  }
  ports.store_0093dd80(receiver, static_cast<TargetSigned>(kKindPair), 9u,
                       source, static_cast<TargetSigned>(kPairSourceSpan),
                       static_cast<TargetSigned>(1));
  return receiver;
}

OpaquePropertyRecord *PKG_APP_WAVE11_THISCALL
property_record_assign_scalar_00428060(OpaquePropertyRecord *receiver,
                                       const TargetFloat *source) {
  OpaquePropertyPorts &ports = property_runtime().ports;
  if ((receiver->flags_10 & kFlagLocked) != 0u) {
    ports.notify_0093db80(receiver, 1u);
  }
  const TargetWord flags = receiver->flags_10;
  if ((flags & kFlagLive) == 0u ||
      static_cast<TargetWord>(receiver->kind_12) == kKindFloat) {
    store_word(address_of(&receiver->slot_00), load_word(address_of(source)));
    store_half(address_of(&receiver->kind_12),
               static_cast<TargetHalf>(kKindFloat));
    store_half(address_of(&receiver->flags_10),
               static_cast<TargetHalf>(flags & kFlagLive));
  } else {
    ports.store_0093dd80(receiver, static_cast<TargetSigned>(kKindFloat), 0u,
                         const_cast<TargetFloat *>(source), 4,
                         static_cast<TargetSigned>(1));
  }
  return receiver;
}

void PKG_APP_WAVE11_THISCALL model_parts_apply_properties_00447150(
    OpaquePartList *receiver, OpaqueVtableHolder *service) {
  OpaquePropertyPorts &ports = property_runtime().ports;
  OpaqueWordVector resolved;
  default_word_construct_00533360(&resolved);
  receiver->find_root_1b0 = ports.find_root_0043c0a0(receiver);
  const TargetWord key_a = ports.global_key_015d25b0();
  receiver->find_key_a_1b4 =
      static_cast<TargetWord>(ports.find_key_0043c120(receiver, key_a));
  if (receiver->find_key_a_1b4 != 0xffffffffu) {
    at<OpaquePartEntry>(part_entry_at(receiver, receiver->find_key_a_1b4))
        ->flag_1d5 = 1u;
  }
  const TargetWord key_b = ports.global_key_015d2180();
  receiver->find_key_b_1b8 =
      static_cast<TargetWord>(ports.find_key_0043c120(receiver, key_b));
  if (receiver->find_key_b_1b8 != 0xffffffffu) {
    at<OpaquePartEntry>(part_entry_at(receiver, receiver->find_key_b_1b8))
        ->flag_1d5 = 1u;
  }
  const TargetWord key_c = ports.global_key_015d22a4();
  receiver->find_key_c_1bc =
      static_cast<TargetWord>(ports.find_key_0043c120(receiver, key_c));
  if (receiver->find_key_c_1bc != 0xffffffffu) {
    at<OpaquePartEntry>(part_entry_at(receiver, receiver->find_key_c_1bc))
        ->flag_1d5 = 1u;
  }
  const TargetWord count = element_count_of(receiver);
  if (ports.has_property_00447150(service, 0x8ecb344au) != 0u) {
    const OpaquePropertyRecord *const record =
        ports.get_property_00447150(service, 0x8ecb344au);
    const TargetWord span = array_kind(record);
    const TargetWord *const data = array_data(record);
    ports.reserve_00454b80(&resolved, span);
    for (TargetWord i = 0u; i < span; ++i) {
      store_word(resolved.first + i * sizeof(TargetWord), 0u);
      const TargetWord key = data[i * 3u];
      for (TargetWord j = 0u; j < count; ++j) {
        OpaquePartEntry *const entry =
            at<OpaquePartEntry>(part_entry_at(receiver, j));
        if (entry->key_8c == key) {
          store_word(resolved.first + i * sizeof(TargetWord),
                     part_entry_at(receiver, j));
        }
      }
    }
  }
  const TargetWord resolved_count = vector_size(&resolved);
  if (ports.has_property_00447150(service, 0x3644a2c5u) != 0u) {
    const OpaquePropertyRecord *const record =
        ports.get_property_00447150(service, 0x3644a2c5u);
    if (load_half(address_of(&record->kind_12)) == kKindPairArray) {
      const TargetWord span = array_kind(record);
      const TargetWord *const data = array_data(record);
      for (TargetWord i = 0u; i < span; ++i) {
        if (i >= resolved_count) {
          continue;
        }
        const TargetWord entry =
            load_word(resolved.first + i * sizeof(TargetWord));
        if (entry == 0u) {
          continue;
        }
        const TargetWord slot = entry + 0x11cu;
        if (address_of(data + i * 4u) != slot) {
          ports.pair_insert_00454cb0(slot, data[i * 4u], data[i * 4u + 1u]);
        }
      }
    }
  }
  if (ports.has_property_00447150(service, 0x04604b04u) != 0u) {
    std::size_t span = 0u;
    const TargetByte *values = nullptr;
    ports.array_bool_006a0760(receiver->property_list, 0x04604b04u, &span,
                              &values);
    for (std::size_t i = 0u; i < span; ++i) {
      const TargetWord index = static_cast<TargetWord>(i);
      if (index >= resolved_count) {
        continue;
      }
      const TargetWord entry =
          load_word(resolved.first + index * sizeof(TargetWord));
      if (entry != 0u) {
        store_byte(entry + 0x1d4u, values[i]);
      }
    }
  }
  if (ports.has_property_00447150(service, 0x87fe8a14u) != 0u) {
    const OpaquePropertyRecord *const record =
        ports.get_property_00447150(service, 0x87fe8a14u);
    const TargetWord span = array_kind(record);
    const TargetWord *const data = array_data(record);
    for (TargetWord i = 0u; i < span; ++i) {
      const TargetWord tail = data[i * 3u + 2u];
      const TargetWord head = data[i * 3u];
      TargetWord found_tail = 0u;
      TargetWord found_head = 0u;
      for (TargetWord j = 0u; j < count; ++j) {
        OpaquePartEntry *const entry =
            at<OpaquePartEntry>(part_entry_at(receiver, j));
        if (entry->key_8c == tail) {
          found_tail = part_entry_at(receiver, j);
        }
        if (entry->key_8c == head) {
          found_head = part_entry_at(receiver, j);
        }
      }
      if (found_head != 0u && found_tail != 0u) {
        at<OpaquePartEntry>(found_tail)->link_b4 = found_head;
        at<OpaquePartEntry>(found_head)->link_b4 = found_tail;
      }
    }
  }
  if (ports.has_property_00447150(service, 0x45101f3eu) != 0u) {
    const OpaquePropertyRecord *const record =
        ports.get_property_00447150(service, 0x45101f3eu);
    const TargetWord span = array_kind(record);
    const TargetWord *const data = array_data(record);
    for (TargetWord i = 0u; i < span; ++i) {
      const TargetWord tail = data[i * 3u + 2u];
      const TargetWord head = data[i * 3u];
      const TargetByte detach = static_cast<TargetByte>(head == kLinkSuppressA);
      TargetWord found_tail = 0u;
      TargetWord found_head = 0u;
      for (TargetWord j = 0u; j < count; ++j) {
        OpaquePartEntry *const entry =
            at<OpaquePartEntry>(part_entry_at(receiver, j));
        if (entry->key_8c == tail) {
          found_tail = part_entry_at(receiver, j);
        }
        if (detach == 0u && entry->key_8c == head) {
          found_head = part_entry_at(receiver, j);
        }
      }
      if (found_head != 0u && found_tail != 0u) {
        at<OpaquePartEntry>(found_tail)->link_b4 = found_head;
        at<OpaquePartEntry>(found_head)->link_b4 = found_tail;
        continue;
      }
      if (detach != 0u && found_tail != 0u) {
        OpaquePartEntry *const entry = at<OpaquePartEntry>(found_tail);
        if (entry->link_b4 != 0u) {
          at<OpaquePartEntry>(entry->link_b4)->link_b4 = 0u;
        }
        entry->link_b4 = 0u;
      }
    }
  }
  model_apply_link_values(receiver, service, 0x3b58c554u, count);
  model_apply_link_values(receiver, service, 0x23fc767eu, count);
  if (ports.has_property_00447150(service, 0xb75fd502u) != 0u) {
    const OpaquePropertyRecord *const record =
        ports.get_property_00447150(service, 0xb75fd502u);
    const TargetWord span = array_kind(record);
    const TargetWord *const data = array_data(record);
    ports.pair_reserve_00454640(&receiver->assoc_630, span);
    for (TargetWord i = 0u; i < span; ++i) {
      TargetWord key = data[i * 3u + 2u];
      TargetWord *const slot =
          ports.pair_slot_00454750(&receiver->assoc_630, &key);
      *slot = data[i * 3u];
    }
  }
  if (ports.has_property_00447150(service, 0x41f72519u) != 0u) {
    const OpaquePropertyRecord *const record =
        ports.get_property_00447150(service, 0x41f72519u);
    const TargetWord span = array_kind(record);
    const TargetWord *const data = array_data(record);
    for (TargetWord i = 0u; i < span; ++i) {
      TargetWord tail = data[i * 3u + 2u];
      const TargetWord middle = data[i * 3u + 1u];
      const TargetWord head = data[i * 3u];
      TargetWord found = 0u;
      for (TargetWord j = 0u; j < count; ++j) {
        OpaquePartEntry *const entry =
            at<OpaquePartEntry>(part_entry_at(receiver, j));
        if (entry->key_8c == middle) {
          found = part_entry_at(receiver, j);
        }
      }
      OpaqueWordPair pair;
      pair.first = head;
      pair.second = found;
      OpaqueTreeBlob *const node =
          ports.tree_insert_004544d0(&receiver->tree_614, &tail, &pair);
      ports.node_append_005402c0(node);
    }
  }
  ports.release_004c0b80(&resolved);
}

void PKG_APP_WAVE11_THISCALL pair_vector_insert_004786e0(
    OpaqueSlotVector *receiver, TargetWord position, const TargetWord *value) {
  OpaqueSlotPorts &ports = slot_runtime().ports;
  const TargetWord base = receiver->first;
  const TargetWord last = receiver->last;
  if (last == receiver->limit) {
    const TargetWord count = sar_count(span_of(last, base), 3);
    const TargetWord grown = count != 0u ? count << 1 : 1u;
    const TargetWord fresh =
        grown != 0u
            ? ports.allocate_0042dee0(address_of(&receiver->arena),
                                      grown * kPairStride, kPairStride, 0u)
            : 0u;
    const TargetWord prefix = position - base;
    const TargetWord slot =
        copy_span(fresh, base, prefix) + (prefix >> 3) * kPairStride;
    if (slot != 0u) {
      store_word(slot, value[0]);
      store_word(slot + sizeof(TargetWord), value[1]);
    }
    const TargetWord cursor = slot + kPairStride;
    const TargetWord tail = last - position;
    const TargetWord refreshed =
        copy_span(cursor, position, tail) + (tail >> 3) * kPairStride;
    if (base != 0u && load_word(base - sizeof(TargetWord)) != 0u) {
      ports.release_00f47380(base);
    }
    receiver->first = fresh;
    receiver->last = refreshed;
    receiver->limit = fresh + grown * kPairStride;
    return;
  }
  TargetWord source = address_of(value);
  if (position <= source && source < last) {
    source += kPairStride;
  }
  if (last != 0u) {
    store_word(last, load_word(last - kPairStride));
    store_word(last + sizeof(TargetWord), load_word(last - sizeof(TargetWord)));
  }
  const TargetSigned span = span_of(last - kPairStride, position);
  move_bytes(last - static_cast<TargetWord>((span >> 3) << 3), position,
             static_cast<TargetWord>(span));
  store_word(position, load_word(source));
  store_word(position + sizeof(TargetWord),
             load_word(source + sizeof(TargetWord)));
  receiver->last = last + kPairStride;
}

TargetByte PKG_APP_WAVE11_THISCALL
model_stage_serialize_004af260(OpaqueStageModel *receiver, TargetWord source) {
  OpaqueSlotPorts &ports = slot_runtime().ports;
  if (receiver->flag_2c == 0u) {
    return 0u;
  }
  const TargetWord stage = ports.lookup_004b0010(source);
  if (stage == 0u) {
    return 0u;
  }
  TargetByte detach = 0u;
  const TargetWord class_id = ports.classify_004bb860(receiver->kind_58);
  if (class_id == kStageSuppressA || class_id == kStageSuppressB ||
      class_id == kStageSuppressC) {
    detach = 1u;
  }
  const TargetWord count = sar_count(
      span_of(receiver->elements_last_1c, receiver->elements_first_18), 2);
  const TargetWord elements = receiver->elements_first_18;
  for (TargetWord i = 0u; i < count; ++i) {
    at<OpaqueStageEntry>(load_word(elements + i * sizeof(TargetWord)))
        ->index_e04 = i;
  }
  OpaqueStage *const target = at<OpaqueStage>(stage);
  ports.record_grow_004afdd0(&target->records_98, 0u);
  ports.record_reserve_004afd00(&target->records_98, count);
  const TargetWord header = address_of(target->header_18.data());
  clear_bytes(header, kHeaderClearSpan);
  const TargetSigned live =
      span_of(target->records_98.last, target->records_98.first);
  const TargetWord clear =
      static_cast<TargetWord>(live / static_cast<TargetSigned>(kRecordStride) *
                              static_cast<TargetSigned>(kRecordStride));
  if (clear != 0u) {
    clear_bytes(target->records_98.first, clear);
  }
  store_word(header, receiver->kind_58);
  for (TargetWord i = 0u; i < 3u; ++i) {
    store_word(
        header + 0x08u + i * sizeof(TargetWord),
        load_word(address_of(&receiver->triplet_8c) + i * sizeof(TargetWord)));
    store_word(
        header + 0x14u + i * sizeof(TargetWord),
        load_word(address_of(&receiver->triplet_98) + i * sizeof(TargetWord)));
    const TargetWord from = address_of(&receiver->triple_a4) + i * 0x0cu;
    const TargetWord into = header + 0x20u + i * 0x0cu;
    for (TargetWord j = 0u; j < 3u; ++j) {
      store_word(into + j * sizeof(TargetWord),
                 load_word(from + j * sizeof(TargetWord)));
    }
  }
  store_word(header + 0x04u, receiver->field_dc);
  const TargetWord records = target->records_98.first;
  for (TargetWord i = 0u; i < count; ++i) {
    const OpaqueStageEntry *const entry = at<const OpaqueStageEntry>(
        load_word(elements + i * sizeof(TargetWord)));
    OpaqueStageRecord *const out =
        at<OpaqueStageRecord>(records + i * kRecordStride);
    TargetWord *const words = reinterpret_cast<TargetWord *>(out);
    TargetFloat *const scalars = reinterpret_cast<TargetFloat *>(out);
    const TargetWord owner = address_of(entry);
    out->field_00 = entry->field_20;
    out->field_04 = entry->field_1c;
    out->parent_08 =
        stage_resolve_index(entry->ref_33c, owner, elements, count);
    out->secondary_0c =
        stage_resolve_index(entry->ref_3e0, owner, elements, count);
    if (record_bit(entry, 0x39u) != 0u) {
      out->flag_81 = 1u;
      out->secondary_0c =
          stage_resolve_index(entry->ref_3e4, owner, elements, count);
    }
    out->value_10 = entry->value_1d8;
    out->field_14 = entry->field_48;
    out->field_18 = entry->field_4c;
    out->field_1c = entry->field_50;
    if (receiver->flag_4f != 0u && ports.element_gate_0044f220(owner) == 0u) {
      out->field_14 = 0.0f;
    }
    for (TargetWord k = 0u; k < 9u; ++k) {
      out->block_38[k] = entry->block_a8[k];
      out->block_5c[k] = entry->block_f0[k];
    }
    out->field_20 = entry->field_3a0;
    out->field_24 = entry->field_3a4;
    out->field_28 = entry->field_3a8;
    out->field_2c = entry->field_3ac;
    out->field_30 = entry->field_3b0;
    out->field_34 = entry->field_3b4;
    out->field_84 = entry->field_1cc;
    if (record_bit(entry, 0x0bu) != 0u) {
      out->value_88 = entry->value_1d0;
    }
    if (record_bit(entry, 0x1fu) != 0u) {
      out->value_8c = entry->value_1d4;
    }
    if (record_bit(entry, 0x0cu) != 0u) {
      out->flag_80 = 1u;
    }
    if (entry->gate_10 != 0u) {
      const TargetWord kids =
          sar_count(span_of(entry->kids_last_6d0, entry->kids_first_6cc), 2);
      ports.weight_reserve_004afc80(address_of(&entry->weights_first_704),
                                    kids);
      ports.key_reserve_004cd3c0(address_of(&entry->keys_first_73c), kids);
      for (TargetWord k = 0u; k < kids; ++k) {
        const TargetWord kid =
            load_word(entry->kids_first_6cc + k * sizeof(TargetWord));
        store_float(entry->weights_first_704 + k * sizeof(TargetFloat),
                    load_float(kid + 0x180u));
        store_word(entry->keys_first_73c + k * sizeof(TargetWord),
                   load_word(kid + 0x8cu));
      }
    }
    const TargetWord weights = sar_count(
        span_of(entry->weights_last_708, entry->weights_first_704), 2);
    const TargetWord weight_slots = kMinCount < weights ? weights : kMinCount;
    out->weight_count_90 = weight_slots;
    for (TargetWord k = 0u; k < weight_slots; ++k) {
      scalars[(0x94u >> 2) + k] =
          load_float(entry->weights_first_704 + k * sizeof(TargetFloat));
      words[(0xb4u >> 2) + k] =
          load_word(entry->keys_first_73c + k * sizeof(TargetWord));
    }
    const TargetWord blocks =
        sar_count(span_of(entry->blocks_last_4cc, entry->blocks_first_4c8), 5);
    const TargetWord block_slots = kMinCount < blocks ? blocks : kMinCount;
    const TargetWord used = detach != 0u ? 0u : block_slots;
    out->block_count_d4 = used;
    for (TargetWord k = 0u; k < used; ++k) {
      const TargetWord block = entry->blocks_first_4c8 + k * kBlockStride;
      words[(0xd8u >> 2) + k] = load_word(block);
      words[(0xf8u >> 2) + k] = load_word(block + sizeof(TargetWord));
      for (TargetWord m = 0u; m < 3u; ++m) {
        words[(0x118u >> 2) + k * 3u + m] =
            load_word(block + 2u * sizeof(TargetWord) + m * sizeof(TargetWord));
        words[(0x178u >> 2) + k * 3u + m] =
            load_word(block + 5u * sizeof(TargetWord) + m * sizeof(TargetWord));
      }
    }
  }
  store_word(stage + 0x08u, receiver->field_0c);
  store_word(stage + 0x0cu, receiver->field_10);
  store_word(stage + 0x10u, receiver->field_14);
  return 1u;
}

OpaquePairVector *PKG_APP_WAVE11_THISCALL pair_vector_construct_004b62a0(
    OpaquePairVector *receiver, const TargetWord *source) {
  const TargetWord inline_base = address_of(receiver->payload_18.data());
  receiver->first = 0u;
  receiver->last = 0u;
  receiver->limit = 0u;
  receiver->arena = inline_base;
  receiver->last = inline_base;
  receiver->first = receiver->last;
  receiver->limit = receiver->first + 0x100u;
  const TargetWord begin = source[0];
  const TargetWord end = source[1];
  slot_runtime().ports.push_004b7290(receiver, begin, end,
                                     stale_slot_004b62a0());
  return receiver;
}

TargetByte PKG_APP_WAVE11_THISCALL stream_probe_dispatch_004bc540(
    OpaqueVtableHolder *receiver, OpaqueVtableHolder *holder_08,
    OpaqueVtableHolder *holder_0c, TargetWord unused_10, TargetWord code_14) {
  (void)receiver;
  (void)unused_10;
  OpaqueStreamPorts &ports = stream_runtime().ports;
  const TargetWord anchor = address_of(holder_0c);
  if (code_14 == kProbePrimary) {
    TargetByte verdict = 0u;
    const TargetWord found = ports.lookup_004c0500(anchor);
    if (found != 0u) {
      const TargetWord resolved = ports.resolve_004bc540(holder_08, found);
      const TargetWord probe = ports.read_004bf430(resolved, found);
      if ((probe & 0xffu) != 0u) {
        verdict = 1u;
      }
    }
    ports.report_006ac0a0(kProbeReport, anchor);
    return verdict;
  }
  if (code_14 == kProbeClassA || code_14 == kProbeClassB ||
      code_14 == kProbeClassC || code_14 == kProbeClassD ||
      code_14 == kProbeClassE || code_14 == kProbeClassF) {
    const TargetWord probe = ports.probe_004bc540(holder_08);
    const TargetWord tag = load_word(probe + sizeof(TargetWord));
    const TargetWord resolved = ports.resolve_004bc540(holder_08, anchor);
    return ports.apply_004bc6d0(resolved, anchor, tag);
  }
  return 0u;
}

}  // namespace openspore::reconstruction::pkg_app_wave11
