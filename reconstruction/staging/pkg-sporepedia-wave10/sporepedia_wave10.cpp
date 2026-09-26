#include "sporepedia_wave10.hpp"

namespace openspore::reconstruction::pkg_sporepedia_wave10 {

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_WAVE10_THISCALL __thiscall
#define PKG_SPOREPEDIA_WAVE10_CDECL __cdecl
#define PKG_SPOREPEDIA_WAVE10_NAKED __declspec(naked)
#else
#define PKG_SPOREPEDIA_WAVE10_THISCALL __attribute__((thiscall))
#define PKG_SPOREPEDIA_WAVE10_CDECL __attribute__((cdecl))
#define PKG_SPOREPEDIA_WAVE10_NAKED __attribute__((naked))
#endif

OpaqueKey16 g_key_015da8e0{};
OpaqueKey16 g_key_015dab18{};
OpaqueKey16 g_key_015da80c{};

namespace {

void default_free_00f47380(OpaqueWord) {}

void PKG_SPOREPEDIA_WAVE10_THISCALL
default_base_destroy_006412a0(OpaqueSporepediaAsset*) {}

OpaqueKey16* PKG_SPOREPEDIA_WAVE10_THISCALL
default_key_fill_004babe0(OpaqueKeyedSet*, OpaqueKey16* out, OpaqueWord) {
  return out;
}

std::uint8_t default_mask_test_004f3d60(OpaqueKey16, OpaqueKey16) { return 0u; }

bool default_key_collect_004f5720(OpaqueKeyedSet*, OpaqueWordVector* out) {
  out->first = nullptr;
  out->last = nullptr;
  out->end_of_storage = nullptr;
  return false;
}

void PKG_SPOREPEDIA_WAVE10_THISCALL
default_word_vector_reserve_00642070(OpaqueInlineWordVector*, OpaqueWord) {}

void PKG_SPOREPEDIA_WAVE10_THISCALL default_word_vector_insert_0060a600(
    OpaqueInlineWordVector*, OpaqueWord* position, const OpaqueWord* value) {
  if (position != nullptr && value != nullptr) {
    *position = *value;
  }
}

const OpaqueGlobalRecordRange* default_global_record_range_005507a0() {
  static const OpaqueGlobalRecordRange range{0u, 0u};
  return &range;
}

OpaqueLookup* default_gate_lookup_0067dea0() { return nullptr; }

const OpaqueLookupEntry* PKG_SPOREPEDIA_WAVE10_THISCALL
default_entry_lookup_007db5e0(OpaqueLookup*, OpaqueWord) {
  return nullptr;
}

OpaqueWord inline_entry_count(const OpaqueInlineWordVector& vector) {
  return static_cast<OpaqueWord>(
      (reinterpret_cast<std::uintptr_t>(vector.last) -
       reinterpret_cast<std::uintptr_t>(vector.first)) >>
      2);
}

OpaqueWord collected_entry_count(const OpaqueWordVector& vector) {
  return static_cast<OpaqueWord>(
      (reinterpret_cast<std::uintptr_t>(vector.last) -
       reinterpret_cast<std::uintptr_t>(vector.first)) >>
      2);
}

}

SporepediaRuntime& sporepedia_runtime() {
  static SporepediaRuntime runtime{default_free_00f47380,
                                   default_base_destroy_006412a0,
                                   default_key_fill_004babe0,
                                   default_mask_test_004f3d60,
                                   default_key_collect_004f5720,
                                   default_word_vector_reserve_00642070,
                                   default_word_vector_insert_0060a600,
                                   default_global_record_range_005507a0,
                                   default_gate_lookup_0067dea0,
                                   default_entry_lookup_007db5e0};
  return runtime;
}

extern "C" void PKG_SPOREPEDIA_WAVE10_NAKED PKG_SPOREPEDIA_WAVE10_THISCALL
sporepedia_asset_destroy_00642190(OpaqueSporepediaAsset* asset) {
  __asm__(
      "pushl %esi\n\t"
      "movl %ecx, %esi\n\t"
      "movl $0x013ff648, (%esi)\n\t"
      "movl $0x01462748, 0x10(%esi)\n\t"
      "movl $0x01462738, 0x14(%esi)\n\t"
      "movl 0x74(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 1f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "1:\n\t"
      "movl 0x70(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 2f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "2:\n\t"
      "movl 0x40(%esi), %eax\n\t"
      "testl %eax, %eax\n\t"
      "jz 3f\n\t"
      "cmpl 0x50(%esi), %eax\n\t"
      "jz 3f\n\t"
      "pushl %eax\n\t"
      "call sporepedia_free_00f47380\n\t"
      "addl $0x4, %esp\n\t"
      "3:\n\t"
      "movl 0x3c(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 4f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "4:\n\t"
      "movl 0x20(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 5f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "5:\n\t"
      "movl 0x1c(%esi), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 6f\n\t"
      "movl (%ecx), %eax\n\t"
      "movl 0x4(%eax), %edx\n\t"
      "call *%edx\n\t"
      "6:\n\t"
      "movl %esi, %ecx\n\t"
      "popl %esi\n\t"
      "jmp sporepedia_base_destroy_006412a0\n\t"
      "ret\n\t");
}

extern "C" void PKG_SPOREPEDIA_WAVE10_THISCALL sporepedia_asset_load_00642230(
    OpaqueSporepediaAsset* asset, OpaqueLookupSource* source) {
  SporepediaRuntime& runtime = sporepedia_runtime();

  asset->word_2c = 2u;
  asset->entries_40.last = asset->entries_40.first;

  OpaqueAssetRef* primary_ref = nullptr;
  OpaqueAssetRef* secondary_ref = nullptr;

  if (source != nullptr) {
    primary_ref = source->vtable->lookup_0c(source, 0x0670da17u);
    if (primary_ref != nullptr) {
      primary_ref->vtable->retain_00(primary_ref);
    }
    secondary_ref = source->vtable->lookup_0c(source, 0x03c609f8u);
    if (secondary_ref != nullptr) {
      secondary_ref->vtable->retain_00(secondary_ref);
    }
    if (primary_ref != nullptr) {
      const OpaqueGlobalRecordRange* const range =
          runtime.global_record_range_005507a0();
      auto record = reinterpret_cast<OpaqueWord*>(range->first);
      const auto end = reinterpret_cast<OpaqueWord*>(range->last);
      for (; record != end;
           record += sizeof(OpaqueGlobalRecord) / sizeof(OpaqueWord)) {
        asset->vtable->apply_property_b4(
            asset, reinterpret_cast<const OpaqueGlobalRecord*>(record));
      }
    } else if (secondary_ref != nullptr) {
      OpaqueKeyedSet* const keyed =
          reinterpret_cast<OpaqueKeyedSet*>(secondary_ref);
      asset->word_28 = keyed->word_18;
      OpaqueKey16 key{};
      static_cast<void>(runtime.key_fill_004babe0(keyed, &key, 1u));
      asset->flag_25 = runtime.mask_test_004f3d60(key, g_key_015da8e0);
      asset->flag_24 = runtime.mask_test_004f3d60(key, g_key_015dab18);
      asset->flag_26 = runtime.mask_test_004f3d60(key, g_key_015da80c);
      OpaqueWordVector collected{};
      if (runtime.key_collect_004f5720(keyed, &collected)) {
        runtime.word_vector_reserve_00642070(&asset->entries_40,
                                             collected_entry_count(collected));
        if (collected_entry_count(collected) != 0u) {
          for (OpaqueWord index = 0u; index < collected_entry_count(collected);
               ++index) {
            OpaqueWord* const slot = asset->entries_40.last;
            const OpaqueWord* const word = collected.first + index;
            if (reinterpret_cast<std::uintptr_t>(slot) <
                reinterpret_cast<std::uintptr_t>(
                    asset->entries_40.end_of_storage)) {
              asset->entries_40.last = slot + 1;
              if (slot != nullptr) {
                *slot = *word;
              }
            } else {
              runtime.word_vector_insert_0060a600(&asset->entries_40, slot,
                                                  word);
            }
          }
        }
      }
      if (collected.first != nullptr && collected.first[-1] != 0u) {
        runtime.free_00f47380(static_cast<OpaqueWord>(
            reinterpret_cast<std::uintptr_t>(collected.first)));
      }
    }
  }

  asset->max_6c = 0u;
  if (runtime.gate_lookup_0067dea0() != nullptr) {
    for (OpaqueWord index = 0u; index < inline_entry_count(asset->entries_40);
         ++index) {
      const OpaqueWord element = asset->entries_40.first[index];
      OpaqueLookup* const lookup = runtime.gate_lookup_0067dea0();
      const OpaqueLookupEntry* const entry =
          runtime.entry_lookup_007db5e0(lookup, element);
      if (entry != nullptr) {
        asset->max_6c =
            entry->value_04 >= asset->max_6c ? entry->value_04 : asset->max_6c;
      }
    }
  }

  if (secondary_ref != nullptr) {
    secondary_ref->vtable->release_04(secondary_ref);
  }
  if (primary_ref != nullptr) {
    primary_ref->vtable->release_04(primary_ref);
  }
}

}

extern "C" void PKG_SPOREPEDIA_WAVE10_CDECL
sporepedia_free_00f47380(std::uint32_t address) {
  openspore::reconstruction::pkg_sporepedia_wave10::sporepedia_runtime()
      .free_00f47380(address);
}

extern "C" void PKG_SPOREPEDIA_WAVE10_THISCALL sporepedia_base_destroy_006412a0(
    openspore::reconstruction::pkg_sporepedia_wave10::OpaqueSporepediaAsset*
        asset) {
  openspore::reconstruction::pkg_sporepedia_wave10::sporepedia_runtime()
      .base_destroy_006412a0(asset);
}

#undef PKG_SPOREPEDIA_WAVE10_NAKED
#undef PKG_SPOREPEDIA_WAVE10_CDECL
#undef PKG_SPOREPEDIA_WAVE10_THISCALL
