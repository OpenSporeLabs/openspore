#include "editor_safe_wave11.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_WAVE11_THISCALL __thiscall
#define PKG_EDITOR_SAFE_WAVE11_CDECL __cdecl
#define PKG_EDITOR_SAFE_WAVE11_STDCALL __stdcall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_EDITOR_SAFE_WAVE11_CDECL __attribute__((cdecl))
#define PKG_EDITOR_SAFE_WAVE11_STDCALL __attribute__((stdcall))
#else
#error "PKG-EDITOR-SAFE-WAVE11 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave11 {

Real g_real_013ef54c = 1.1F;

namespace {

bool bit_is_set(Word marks, Word index) {
  return (marks & (1u << (index & 31u))) != 0u;
}

void raise_node(OpaquePaintNode* node, Byte code) {
  if (node != nullptr) {
    node->word_004 |= kMask003;
    node->code_05c = code;
  }
}

void clear_node(OpaquePaintNode* node) {
  if (node != nullptr) {
    node->word_004 &= kClear003;
  }
}

void raise_only(OpaquePaintNode* node, Byte code) {
  if (node != nullptr) {
    node->word_004 |= kMask003;
    node->code_05c = code;
  }
}

void notify_state(const OpaquePaintState* state, Word first, Word second) {
  if (state->node_3ec != nullptr) {
    state->node_3ec->slot_000->notify_028(first, second);
  }
}

Word load_word(const Byte* source) {
  return static_cast<Word>(source[0]) | (static_cast<Word>(source[1]) << 8) |
         (static_cast<Word>(source[2]) << 16) |
         (static_cast<Word>(source[3]) << 24);
}

void store_word(Byte* target, Word value) {
  target[0] = static_cast<Byte>(value);
  target[1] = static_cast<Byte>(value >> 8);
  target[2] = static_cast<Byte>(value >> 16);
  target[3] = static_cast<Byte>(value >> 24);
}

Signed vector_length(const Word* begin, const Word* end, Word stride) {
  return static_cast<Signed>(end - begin) / static_cast<Signed>(stride);
}

Signed vector_span(const Word* begin, const Word* end) {
  return static_cast<Signed>(end - begin) >> 2;
}

// 0x004ad737 reads the frame byte at [EBP-0x6b]. No instruction in the 223
// instruction body of 0x004ad6f0 ever writes that slot, so the third stack
// argument of the fallback call carries an indeterminate value.
Byte uninitialised_fallback_byte() {
  static Byte slot = kUninitialisedFallbackByte;
  return slot;
}

}  // namespace

extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL editor_paint_commit_0043ac40(
    OpaquePaintState* self, Word value, Word extra, Byte quiet) {
  (void)extra;
  self->value_03c = value;
  const bool unchanged = self->pair_040.mark_00 == self->pair_038.mark_00 &&
                         self->pair_040.tag_01 == self->pair_038.tag_01 &&
                         self->applied_044 == self->value_03c;
  if (unchanged && quiet == 0u) {
    return false;
  }
  self->word_040 = self->word_038;
  self->applied_044 = self->value_03c;
  switch (self->value_03c) {
    case kStateZero:
      if (self->pair_038.tag_01 != 0u) {
        if (self->pair_038.mark_00 != 0u) {
          notify_state(self, 1u, 8u);
          raise_only(self->node_010, 8u);
        } else {
          notify_state(self, 1u, 7u);
          raise_node(self->node_3f0, 7u);
          raise_node(self->node_010, 7u);
        }
      } else if (self->pair_038.mark_00 != 0u) {
        notify_state(self, 1u, 5u);
        raise_node(self->node_3f0, 5u);
        raise_node(self->node_010, 5u);
      } else {
        notify_state(self, 0u, 10u);
        clear_node(self->node_3f0);
        raise_node(self->node_010, 10u);
      }
      break;
    case kStateOne:
      notify_state(self, 1u, 6u);
      raise_node(self->node_3f0, 6u);
      raise_node(self->node_010, 6u);
      break;
    case 2u:
      notify_state(self, 1u, 9u);
      raise_node(self->node_3f0, 9u);
      raise_node(self->node_010, 9u);
      break;
    case kStateFour:
      notify_state(self, 1u, 11u);
      raise_node(self->node_3f0, 11u);
      raise_node(self->node_010, 11u);
      break;
    case kStateFive:
      notify_state(self, 1u, 12u);
      raise_only(self->node_3f0, 12u);
      raise_only(self->node_010, 12u);
      break;
    default:
      break;
  }
  return true;
}

extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
editor_entry_expand_004ad6f0(OpaqueEntryList* self, OpaqueRecord* records) {
  if (!unresolved_00526430(&self->range_0c8)) {
    unresolved_004b1cc0(records, &self->range_0c8, &self->range_0c8.word_04,
                        uninitialised_fallback_byte());
    return;
  }
  const Signed count =
      static_cast<Signed>(reinterpret_cast<const Byte*>(self->end_01c) -
                          reinterpret_cast<const Byte*>(self->begin_018)) >>
      2;
  unresolved_004aff80(records, count);
  for (Signed index = 0; index < count; ++index) {
    OpaqueEntryElement* const element = self->begin_018[index];
    OpaqueRecord* const target = reinterpret_cast<OpaqueRecord*>(
        reinterpret_cast<Byte*>(records) +
        static_cast<std::size_t>(index) * kElementStride);
    OpaqueRecord staging;
    const OpaqueRecord* const built =
        unresolved_0044ae00(element, &staging, 2u, 1u, 0u);
    store_word(target->opaque_00 + 0x0c, load_word(built->opaque_00 + 0x0c));
    store_word(target->opaque_00 + 0x10, load_word(built->opaque_00 + 0x10));
    store_word(target->opaque_00 + 0x14, load_word(built->opaque_00 + 0x14));
    store_word(target->opaque_00 + 0x00, load_word(built->opaque_00 + 0x00));
    store_word(target->opaque_00 + 0x04, load_word(built->opaque_00 + 0x04));
    store_word(target->opaque_00 + 0x08, load_word(built->opaque_00 + 0x08));
    if (bit_is_set(element->marks_0dc8, kMarkBit)) {
      unresolved_0041dba0(target, &g_real_013ef54c);
      unresolved_0041dba0(reinterpret_cast<Byte*>(target) + kHalfStride,
                          &g_real_013ef54c);
    }
    OpaqueBox box;
    unresolved_00409930(&box);
    box.span_04[0] = element->seed_048[0];
    box.span_04[1] = element->seed_048[1];
    box.span_04[2] = element->seed_048[2];
    box.code_00 = static_cast<std::uint16_t>(box.code_00 | 0x0004u);
    box.count_02 = static_cast<std::uint16_t>(box.count_02 + 1u);
    for (std::size_t lane = 0; lane < 9; ++lane) {
      box.basis_14[lane] = element->basis_060[lane];
    }
    box.code_00 = static_cast<std::uint16_t>(box.code_00 | 0x0002u);
    box.count_02 = static_cast<std::uint16_t>(box.count_02 + 1u);
    box.extra_10 = element->span_1d8;
    box.count_02 = static_cast<std::uint16_t>(box.count_02 + 1u);
    unresolved_00409dd0(target, &box);
  }
}

extern "C" bool PKG_EDITOR_SAFE_WAVE11_CDECL
editor_bake_probe_004bf770(OpaqueProbeOwner* owner, OpaqueBakeRow* row) {
  OpaqueProbeRequest request;
  request.tag_00 = 0xabb455b7u;
  request.span_04 = 10u;
  const Signed group = vector_length(row->block_098.begin_00,
                                     row->block_098.end_04, kProbeStride);
  const Signed spans =
      vector_span(row->block_0ac.begin_00, row->block_0ac.end_04);
  const Signed links =
      vector_span(row->block_0e8.begin_00, row->block_0e8.end_04);
  const Signed seats = vector_length(row->block_114.begin_00,
                                     row->block_114.end_04, kSeatStride);
  OpaqueProbeTable* const table = owner->table_000;
  if (!table->slot_038(&request, 8u)) {
    return false;
  }
  if (!table->slot_038(&group, 0x10u)) {
    return false;
  }
  if (!unresolved_004bf0a0(owner, row->opaque_018, 0x80u)) {
    return false;
  }
  if (!table->slot_038(row->block_098.begin_00,
                       static_cast<Word>(group) * kProbeStride)) {
    return false;
  }
  if (!table->slot_038(row->block_0ac.begin_00, static_cast<Word>(spans)
                                                    << 2)) {
    return false;
  }
  if (!table->slot_038(row->keys_0c0, static_cast<Word>(spans))) {
    return false;
  }
  if (!table->slot_038(row->marks_0d4, static_cast<Word>(links) << 2)) {
    return false;
  }
  if (!table->slot_038(row->block_0e8.begin_00, static_cast<Word>(links)
                                                    << 2)) {
    return false;
  }
  if (!table->slot_038(row->weights_0fc, static_cast<Word>(links) << 2)) {
    return false;
  }
  if (!table->slot_038(&row->head_110, 4u)) {
    return false;
  }
  if (!table->slot_038(row->block_114.begin_00,
                       static_cast<Word>(seats) * kSeatStride)) {
    return false;
  }
  return true;
}

extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL editor_bake_select_004c4a30(
    OpaqueBakeRoot* self, Signed mode, Real low_x, Real low_y, Real low_z,
    Real high_x, Real high_y, Real high_z, Word* out_first, Word* out_second,
    Real* out_value, Byte flag) {
  OpaqueFloats3 low;
  OpaqueFloats3 high;
  low.x_00 = low_x;
  low.y_04 = low_y;
  low.z_08 = low_z;
  high.x_00 = high_x;
  high.y_04 = high_y;
  high.z_08 = high_z;
  if (mode == kModeZero) {
    return unresolved_004ccae0(self->primary_018, low, high,
                               reinterpret_cast<OpaqueWords3*>(out_first),
                               reinterpret_cast<OpaqueWords3*>(out_second),
                               out_value, static_cast<Word>(flag));
  }
  if (mode == kModeOne) {
    return unresolved_004ccae0(self->secondary_01c, low, high,
                               reinterpret_cast<OpaqueWords3*>(out_first),
                               reinterpret_cast<OpaqueWords3*>(out_second),
                               out_value, static_cast<Word>(flag));
  }
  if (mode != kModeTwo) {
    return false;
  }
  bool found = false;
  Real best = 0.0F;
  OpaqueWords3 best_first = {0u, 0u, 0u};
  OpaqueWords3 best_second = {0u, 0u, 0u};
  const Signed entries =
      static_cast<Signed>(
          reinterpret_cast<const Byte*>(self->entries_048.end_04) -
          reinterpret_cast<const Byte*>(self->entries_048.begin_00)) >>
      3;
  for (Signed slot = 0; slot < entries; ++slot) {
    const OpaqueBakeEntryPair* const pair = &self->entries_048.begin_00[slot];
    if (pair->first_00 == nullptr) {
      continue;
    }
    OpaqueWords3 got_first = {0u, 0u, 0u};
    OpaqueWords3 got_second = {0u, 0u, 0u};
    Real got = 0.0F;
    const bool hit =
        unresolved_004ccae0(pair->second_04, low, high, &got_first, &got_second,
                            &got, static_cast<Word>(flag));
    if (hit && (!found || got < best)) {
      best = got;
      best_first = got_first;
      best_second = got_second;
      found = true;
    }
  }
  if (!found) {
    return false;
  }
  out_first[0] = best_first.word_00;
  out_first[1] = best_first.word_04;
  out_first[2] = best_first.word_08;
  out_second[0] = best_second.word_00;
  out_second[1] = best_second.word_04;
  out_second[2] = best_second.word_08;
  *out_value = best;
  return true;
}

}  // namespace openspore::reconstruction::pkg_editor_safe_wave11

#undef PKG_EDITOR_SAFE_WAVE11_THISCALL
#undef PKG_EDITOR_SAFE_WAVE11_CDECL
#undef PKG_EDITOR_SAFE_WAVE11_STDCALL
