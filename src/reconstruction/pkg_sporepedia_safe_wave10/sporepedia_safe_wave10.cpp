#include "sporepedia_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_SAFE_WAVE10_CDECL __cdecl
#define PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL __thiscall
#else
#define PKG_SPOREPEDIA_SAFE_WAVE10_CDECL __attribute__((cdecl))
#define PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_sporepedia_safe_wave10 {
namespace {

const OpaqueKey16 g_zero_tag = {{0u, 0u, 0u, 0u}};

const Word g_default_vtable_primary_00 = 0x013ff648u;

const Word g_default_vtable_secondary_10 = 0x01462748u;

const Word g_default_vtable_tertiary_14 = 0x01462738u;

const Word g_base_vtable_tertiary_14 = 0x013ec458u;

const Word g_base_vtable_secondary_10 = 0x013eb938u;

const Word g_base_vtable_primary_00 = 0x01403758u;

Word word_of(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

void* pointer_of(Word word) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(word));
}

SignedWord signed_word_delta(const void* last, const void* first) {
  const auto delta =
      static_cast<std::intptr_t>(reinterpret_cast<std::uintptr_t>(last) -
                                 reinterpret_cast<std::uintptr_t>(first));
  return static_cast<SignedWord>(delta >> 2);
}

SignedWord signed_span(const OpaqueWordVector& vector) {
  return signed_word_delta(vector.last, vector.first);
}

SignedWord signed_inline_span(const OpaqueInlineWordVector& vector) {
  return signed_word_delta(vector.last, vector.first);
}

void PKG_SPOREPEDIA_SAFE_WAVE10_CDECL default_free_00f47380(Word) {}

void PKG_SPOREPEDIA_SAFE_WAVE10_CDECL
default_clear_011e0744(void* first, const void* last, std::size_t count) {
  static_cast<void>(first);
  static_cast<void>(last);
  static_cast<void>(count);
}

void PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
default_base_destroy_006412a0(OpaqueSporepediaAsset* asset) {
  asset->vtable_14 = reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_base_vtable_tertiary_14));
  asset->vtable_10 = reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_base_vtable_secondary_10));
  asset->vtable_00 = reinterpret_cast<OpaqueAssetVtable*>(
      static_cast<std::uintptr_t>(g_base_vtable_primary_00));
}

OpaqueKey16* PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
default_key_fill_004babe0(OpaqueKeyedSet*, OpaqueKey16* out, Word) {
  return out;
}

std::uint8_t PKG_SPOREPEDIA_SAFE_WAVE10_CDECL
default_mask_test_004f3d60(OpaqueKey16, OpaqueKey16) {
  return 0u;
}

bool PKG_SPOREPEDIA_SAFE_WAVE10_CDECL
default_key_collect_004f5720(OpaqueKeyedSet*, OpaqueWordVector*) {
  return false;
}

void PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
default_inline_reserve_00642070(OpaqueInlineWordVector*, Word) {}

void PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
default_inline_insert_0060a600(OpaqueInlineWordVector*, Word*, const Word*) {}

const OpaqueGlobalRecordRange* PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
default_global_record_range_005507a0(OpaqueAssetRef* primary) {
  return reinterpret_cast<const OpaqueGlobalRecordRange*>(
      reinterpret_cast<std::uintptr_t>(primary) + kGlobalRecordRangeOffset);
}

OpaqueLookup* PKG_SPOREPEDIA_SAFE_WAVE10_CDECL default_gate_lookup_0067dea0() {
  return nullptr;
}

const OpaqueLookupEntry* PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
default_entry_lookup_007db5e0(OpaqueLookup*, Word) {
  return nullptr;
}

SporepediaSafeBindings default_bindings() {
  SporepediaSafeBindings bindings = {};
  bindings.vtable_words.primary_00 = g_default_vtable_primary_00;
  bindings.vtable_words.secondary_10 = g_default_vtable_secondary_10;
  bindings.vtable_words.tertiary_14 = g_default_vtable_tertiary_14;
  bindings.tag_015da8e0 = &g_zero_tag;
  bindings.tag_015dab18 = &g_zero_tag;
  bindings.tag_015da80c = &g_zero_tag;
  bindings.free_00f47380 = default_free_00f47380;
  bindings.clear_011e0744 = default_clear_011e0744;
  bindings.base_destroy_006412a0 = default_base_destroy_006412a0;
  bindings.key_fill_004babe0 = default_key_fill_004babe0;
  bindings.mask_test_004f3d60 = default_mask_test_004f3d60;
  bindings.key_collect_004f5720 = default_key_collect_004f5720;
  bindings.inline_reserve_00642070 = default_inline_reserve_00642070;
  bindings.inline_insert_0060a600 = default_inline_insert_0060a600;
  bindings.global_record_range_005507a0 = default_global_record_range_005507a0;
  bindings.gate_lookup_0067dea0 = default_gate_lookup_0067dea0;
  bindings.entry_lookup_007db5e0 = default_entry_lookup_007db5e0;
  return bindings;
}

SporepediaSafeBindings g_bindings = default_bindings();

}

SporepediaSafeBindings& sporepedia_safe_bindings() { return g_bindings; }

void sporepedia_safe_publish_bindings(const SporepediaSafeBindings& bindings) {
  g_bindings = bindings;
}

void sporepedia_safe_reset_bindings() { g_bindings = default_bindings(); }

void PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
sporepedia_asset_destroy_00642190(OpaqueSporepediaAsset* asset) {
  const SporepediaSafeBindings& bindings = sporepedia_safe_bindings();

  asset->vtable_00 = reinterpret_cast<OpaqueAssetVtable*>(
      pointer_of(bindings.vtable_words.primary_00));
  asset->vtable_10 = pointer_of(bindings.vtable_words.secondary_10);
  asset->vtable_14 = pointer_of(bindings.vtable_words.tertiary_14);

  OpaqueAssetRef* const access_74 = asset->access_74;
  if (access_74 != nullptr) {
    access_74->vtable->release_04(access_74);
  }
  OpaqueAssetRef* const access_70 = asset->access_70;
  if (access_70 != nullptr) {
    access_70->vtable->release_04(access_70);
  }

  Word* const entry_pointer = asset->entries_40.first;
  if (entry_pointer != nullptr &&
      word_of(entry_pointer) != asset->entries_40.inline_marker_10) {
    bindings.free_00f47380(word_of(entry_pointer));
  }

  OpaqueAssetRef* const access_3c = asset->access_3c;
  if (access_3c != nullptr) {
    access_3c->vtable->release_04(access_3c);
  }
  OpaqueAssetRef* const access_20 = asset->access_20;
  if (access_20 != nullptr) {
    access_20->vtable->release_04(access_20);
  }
  OpaqueAssetRef* const access_1c = asset->access_1c;
  if (access_1c != nullptr) {
    access_1c->vtable->release_04(access_1c);
  }

  bindings.base_destroy_006412a0(asset);
}

void PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL sporepedia_asset_load_00642230(
    OpaqueSporepediaAsset* asset, OpaqueLookupSource* source) {
  const SporepediaSafeBindings& bindings = sporepedia_safe_bindings();

  asset->state_2c = 2u;

  Word* const clear_first = asset->entries_40.first;
  Word* const clear_last = asset->entries_40.last;
  bindings.clear_011e0744(clear_first, clear_last, 0u);

  const SignedWord cleared_span = signed_word_delta(clear_last, clear_first);
  asset->entries_40.last =
      reinterpret_cast<Word*>(reinterpret_cast<std::intptr_t>(clear_last) -
                              4 * static_cast<std::intptr_t>(cleared_span));

  OpaqueAssetRef* primary = nullptr;
  OpaqueAssetRef* secondary = nullptr;

  if (source != nullptr) {
    primary = source->vtable->lookup_0c(source, 0x0670da17u);
    if (primary != nullptr) {
      primary->vtable->retain_00(primary);
    }
    secondary = source->vtable->lookup_0c(source, 0x03c609f8u);
    if (secondary != nullptr) {
      secondary->vtable->retain_00(secondary);
    }

    if (primary != nullptr) {
      const OpaqueGlobalRecordRange* const range_head =
          bindings.global_record_range_005507a0(primary);
      const Word range_first = range_head->first;
      const OpaqueGlobalRecordRange* const range_tail =
          bindings.global_record_range_005507a0(primary);
      const Word range_last = range_tail->last;
      for (Word cursor = range_first; cursor != range_last;
           cursor += sizeof(OpaqueGlobalRecord)) {
        asset->vtable_00->apply_property_b4(
            asset, reinterpret_cast<const OpaqueGlobalRecord*>(cursor));
      }
    } else if (secondary != nullptr) {
      OpaqueKeyedSet* const keyed =
          reinterpret_cast<OpaqueKeyedSet*>(secondary);
      asset->source_word_28 = keyed->word_18;

      OpaqueKey16 tag = {{0u, 0u, 0u, 0u}};
      bindings.key_fill_004babe0(keyed, &tag, 1u);
      asset->flag_25 = bindings.mask_test_004f3d60(tag, *bindings.tag_015da8e0);
      asset->flag_24 = bindings.mask_test_004f3d60(tag, *bindings.tag_015dab18);
      asset->flag_26 = bindings.mask_test_004f3d60(tag, *bindings.tag_015da80c);

      OpaqueWordVector collected = {nullptr, nullptr, nullptr};
      if (bindings.key_collect_004f5720(keyed, &collected)) {
        bindings.inline_reserve_00642070(
            &asset->entries_40, static_cast<Word>(signed_span(collected)));
        if (static_cast<Word>(signed_span(collected)) > 0u) {
          for (Word index = 0u;
               static_cast<SignedWord>(index) < signed_span(collected);
               ++index) {
            const Word* const collected_first = collected.first;
            const Word* const value = collected_first + index;
            Word* const slot = asset->entries_40.last;
            if (reinterpret_cast<std::uintptr_t>(slot) <
                reinterpret_cast<std::uintptr_t>(asset->entries_40.capacity)) {
              asset->entries_40.last = slot + 1;
              if (slot != nullptr) {
                *slot = *value;
              }
            } else {
              bindings.inline_insert_0060a600(&asset->entries_40, slot, value);
            }
          }
        }
      }

      if (collected.first != nullptr && collected.first[-1] != 0u) {
        bindings.free_00f47380(word_of(collected.first));
      }
    }
  }

  asset->max_6c = 0u;

  if (bindings.gate_lookup_0067dea0() != nullptr) {
    if (static_cast<Word>(signed_inline_span(asset->entries_40)) > 0u) {
      for (Word index = 0u; static_cast<SignedWord>(index) <
                            signed_inline_span(asset->entries_40);
           ++index) {
        const Word* const entry_first = asset->entries_40.first;
        const Word element = entry_first[index];
        OpaqueLookup* const gate = bindings.gate_lookup_0067dea0();
        const OpaqueLookupEntry* const entry =
            bindings.entry_lookup_007db5e0(gate, element);
        if (entry != nullptr) {
          const SignedWord candidate = static_cast<SignedWord>(entry->value_04);
          const SignedWord current = static_cast<SignedWord>(asset->max_6c);
          asset->max_6c =
              static_cast<Word>(candidate >= current ? candidate : current);
        }
      }
    }
  }

  if (secondary != nullptr) {
    secondary->vtable->release_04(secondary);
  }
  if (primary != nullptr) {
    primary->vtable->release_04(primary);
  }
}

}

#undef PKG_SPOREPEDIA_SAFE_WAVE10_CDECL
#undef PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
