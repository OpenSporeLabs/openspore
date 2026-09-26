#include "skinner_wave11.hpp"

#include <cmath>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_SKINNER_WAVE11_THISCALL __thiscall
#else
#define PKG_SKINNER_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_skinner_wave11 {

SkinnerWave11Ports g_skinner_wave11_ports{};

float g_skinner_wave11_scale[9]{};

OpaqueRefObject *g_skinner_wave11_scale_source = nullptr;

namespace {

OpaqueVec2 zero_pair() {
  OpaqueVec2 pair;
  pair.a = kScaleZero;
  pair.b = kScaleZero;
  return pair;
}

OpaqueVec2 unit_pair() {
  OpaqueVec2 pair;
  pair.a = kScaleUnit;
  pair.b = kScaleUnit;
  return pair;
}

OpaqueVec2 axis_pair(float a, float b) {
  OpaqueVec2 pair;
  pair.a = a;
  pair.b = b;
  return pair;
}

OpaqueVec4f flat_unit() {
  OpaqueVec4f value;
  value.a = kScaleUnit;
  value.b = kScaleUnit;
  value.c = kScaleUnit;
  value.d = kScaleUnit;
  return value;
}

OpaqueVec2 entry_low(const OpaqueVec4f *entry) {
  OpaqueVec2 pair;
  pair.a = entry->a;
  pair.b = entry->b;
  return pair;
}

OpaqueVec2 entry_high(const OpaqueVec4f *entry) {
  OpaqueVec2 pair;
  pair.a = entry->c;
  pair.b = entry->d;
  return pair;
}

OpaqueVec2 slot_extent_x(const OpaqueBatchSlot *slot) {
  OpaqueVec2 pair;
  pair.a = slot->field_058;
  pair.b = slot->field_060;
  return pair;
}

OpaqueVec2 slot_extent_y(const OpaqueBatchSlot *slot) {
  OpaqueVec2 pair;
  pair.a = slot->field_05c;
  pair.b = slot->field_064;
  return pair;
}

// 0x00519427 is CVTSS2SI, the x86 convert with the current rounding mode, and
// 0x0051942b narrows the dword result to a byte. The default mode is round to
// nearest even, so this is a rounding cast rather than a truncating one.
TargetByte quantise_byte_round_to_nearest(float value) {
  return static_cast<TargetByte>(
      static_cast<std::int32_t>(std::nearbyint(static_cast<double>(value))));
}

void raise_param_count(OpaqueTexturePainter *painter, TargetSignedWord want) {
  if (painter->count_044 <= want) {
    painter->count_044 = want + 1;
  }
}

void raise_raster_count(OpaqueTexturePainter *painter, TargetSignedWord want) {
  if (painter->count_048 <= want) {
    painter->count_048 = want + 1;
  }
}

void store_param(OpaqueTexturePainter *painter, TargetSignedWord index,
                 const OpaqueVec4f &value) {
  OpaqueVec4f *slot = reinterpret_cast<OpaqueVec4f *>(
      reinterpret_cast<std::uint8_t *>(&painter->params_00c) +
      static_cast<std::size_t>(index) * sizeof(OpaqueVec4f));
  *slot = value;
}

OpaqueVec4f widen(const OpaqueVec3f &value) {
  OpaqueVec4f wide;
  wide.a = value.a;
  wide.b = value.b;
  wide.c = value.c;
  wide.d = kScaleZero;
  return wide;
}

float inverse_extent(TargetWord value) {
  return static_cast<float>(
      1.0 / static_cast<double>(static_cast<std::int64_t>(value)));
}

TargetSignedWord rigblock_count(const OpaqueMesh *mesh) {
  const OpaqueRigblock *begin = mesh->field_008->rigblocks_098;
  const OpaqueRigblock *end = mesh->field_008->rigblocks_09c;
  return static_cast<TargetSignedWord>(end - begin);
}

OpaqueRefObject *acquire_plain(TargetWord size) {
  return static_cast<OpaqueRefObject *>(
      g_skinner_wave11_ports.acquire_object_00f473a0(size, kAcquireKey, 0u, 0u,
                                                     0u, 0u));
}

OpaqueRefObject *acquire_vtable(TargetWord size, TargetWord vtable) {
  OpaqueRefObject *object = acquire_plain(size);
  if (object == nullptr) {
    return nullptr;
  }
  g_skinner_wave11_ports.job_init_005173a0(object);
  object->vtable_000 = reinterpret_cast<OpaqueRefVTable *>(vtable);
  object->field_004 = kJobAuxVTable;
  return object;
}

OpaqueRefObject *offset_eight(OpaqueRefObject *object) {
  if (object == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<OpaqueRefObject *>(
      reinterpret_cast<std::uint8_t *>(object) + 8);
}

OpaqueRefVTable *ref_vtable_of(OpaqueRefObject *object) {
  return g_skinner_wave11_ports.resolve_ref_vtable(
      reinterpret_cast<TargetWord>(object->vtable_000));
}

void refcount_add(OpaqueRefObject *object) {
  if (object == nullptr) {
    return;
  }
  object->refcount_008 += 1u;
}

void ref_assign(OpaqueRefObject **slot, OpaqueRefObject *value) {
  if (value == *slot) {
    return;
  }
  OpaqueRefObject *previous = *slot;
  if (value != nullptr) {
    ref_vtable_of(value)->add_000(value);
  }
  *slot = value;
  if (previous != nullptr) {
    ref_vtable_of(previous)->release_004(previous);
  }
}

void ref_drop(OpaqueRefObject **slot) {
  OpaqueRefObject *previous = *slot;
  if (previous == nullptr) {
    return;
  }
  *slot = nullptr;
  ref_vtable_of(previous)->release_004(previous);
}

void ref_maybe_drop(OpaqueSkinJob *job) {
  if (job->handle_330 == nullptr || job->handle_330->flag_00c == 0u) {
    return;
  }
  ref_drop(&job->handle_330);
}

OpaqueRefObject *resolve_block(OpaqueElement *element, TargetWord key) {
  OpaqueKeyBlock desc;
  if (element->vtable_000->has_01c(element, key) == 0u) {
    return nullptr;
  }
  OpaqueRefObject *handle = element->vtable_000->get_028(element, key);
  const TargetHalf tag = *reinterpret_cast<const TargetHalf *>(
      reinterpret_cast<const std::uint8_t *>(handle) + 0x12);
  if (tag == kHandleTypeWide || tag == kHandleTypeNarrow) {
    desc = *g_skinner_wave11_ports.get_desc_00446ff0(handle);
  } else {
    desc = *g_skinner_wave11_ports.get_default_desc_006bb640();
  }
  OpaqueRenderTargetManager *manager =
      g_skinner_wave11_ports.get_render_target_manager_0067dd60();
  if (manager->vtable_000->can_create_024(manager, desc) == 0u) {
    return nullptr;
  }
  OpaqueRenderTargetManager *maker =
      g_skinner_wave11_ports.get_render_target_manager_0067dd60();
  return maker->vtable_000->create_01c(maker, desc, kCreateBlockTags);
}

void prepare_slot(OpaqueRenderTargetManager *manager, OpaqueRefObject *target) {
  if ((target->field_004 & 1u) != 0u) {
    return;
  }
  manager->vtable_000->prepare_034(manager, target);
}

void bind_raster(OpaqueTexturePainter *painter, OpaqueRefObject *target,
                 bool second) {
  OpaqueHandle *handle = reinterpret_cast<OpaqueHandle *>(target->vtable_000);
  raise_raster_count(painter, second ? 1 : 0);
  if (second) {
    painter->rasters_040 = handle;
  } else {
    painter->rasters_03c = handle;
  }
}

}  // namespace

extern "C" TargetByte PKG_SKINNER_WAVE11_THISCALL
skin_paint_slot_pass_005183c0(OpaqueSkinJobState *job) {
  const OpaqueVec2 shared = zero_pair();
  const OpaqueVec3w tone = {0u, 0u, 0u};
  const TargetWord shared_tail = 0u;

  OpaqueSkinPainter *painter =
      g_skinner_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter *slot = painter->textures_010[job->field_010];

  if (job->field_018 == 0) {
    g_skinner_wave11_ports.start_render_00528e90(slot);
    g_skinner_wave11_ports.set_color_write_00529280(slot, 0u, 0u, 0u, 1u);
    slot->field_004 = kMaterialPassSetup;
    g_skinner_wave11_ports.set_vertex_limit_00529520(slot, kPassSlot);

    const OpaqueVec2 first = zero_pair();
    g_skinner_wave11_ports.emit_005295b0(slot, &first, &shared, &tone,
                                         shared_tail);
    const OpaqueVec2 second = axis_pair(kScaleUnit, kScaleZero);
    g_skinner_wave11_ports.emit_005295b0(slot, &second, &shared, &tone,
                                         shared_tail);
    const OpaqueVec2 third = unit_pair();
    g_skinner_wave11_ports.emit_005295b0(slot, &third, &shared, &tone,
                                         shared_tail);
    g_skinner_wave11_ports.emit_005295b0(slot, &third, &shared, &tone,
                                         shared_tail);
    const OpaqueVec2 fifth = axis_pair(kScaleZero, kScaleUnit);
    g_skinner_wave11_ports.emit_005295b0(slot, &fifth, &shared, &tone,
                                         shared_tail);
    const OpaqueVec2 sixth = zero_pair();
    g_skinner_wave11_ports.emit_005295b0(slot, &sixth, &shared, &tone,
                                         shared_tail);
    g_skinner_wave11_ports.flush_00529690(slot);

    OpaqueBatch *batch =
        g_skinner_wave11_ports.get_paint_system_00401080()->batch_010;
    TargetSignedWord remaining = static_cast<TargetSignedWord>(
        batch->parts_end_05c - batch->parts_begin_058);
    remaining /= 3;

    TargetSignedWord index = 0;
    while (remaining != 0) {
      const TargetSignedWord taken = static_cast<TargetSignedWord>(
          g_skinner_wave11_ports.set_vertex_limit_00529520(
              slot, static_cast<TargetWord>(remaining)));
      const TargetSignedWord stop = taken * 3 + index;
      for (; index < stop; ++index) {
        const TargetWord *entry = batch->index_080 + index;
        const TargetWord *base = batch->vertices_030 + *entry * 8u;
        g_skinner_wave11_ports.emit_005295b0(
            slot, reinterpret_cast<const OpaqueVec2 *>(base),
            reinterpret_cast<const OpaqueVec2 *>(base), &tone, kColourOpaque);
      }
      remaining -= taken;
      g_skinner_wave11_ports.flush_00529690(slot);
    }

    g_skinner_wave11_ports.set_color_write_00529280(slot, 1u, 1u, 1u, 1u);
    g_skinner_wave11_ports.end_render_00529bf0(slot);
    job->field_018 = 1;
    return 0u;
  }

  OpaqueGraphicsProbe *probe =
      g_skinner_wave11_ports.get_graphics_probe_0067dd00();
  const TargetWord steps =
      probe->vtable_000->query_044(probe) != 0u ? kPassNormal : kPassSmall;

  const TargetSignedWord remaining = job->field_014 - job->field_018 + 1;
  const TargetSignedWord batch_count =
      remaining < static_cast<TargetSignedWord>(steps)
          ? remaining
          : static_cast<TargetSignedWord>(steps);

  OpaqueTexturePainter *active =
      g_skinner_wave11_ports.get_paint_system_00401080()
          ->painter_00c->textures_010[2];
  for (TargetSignedWord pass = 0; pass < batch_count; ++pass) {
    g_skinner_wave11_ports.start_render_00528e90(active);
    active->field_004 = kMaterialPassLoop;

    OpaqueVec4f param;
    param.a = inverse_extent(slot->field_058);
    param.b = inverse_extent(slot->field_05c);
    param.c = kScaleZero;
    param.d = kScaleZero;
    raise_param_count(active, 0);
    store_param(active, 0, param);

    OpaqueHandle *raster = slot->field_060;
    if (raster != nullptr) {
      raise_raster_count(active, 0);
    }
    active->rasters_03c = raster;

    const OpaqueVec2 low = zero_pair();
    const OpaqueVec2 high = unit_pair();
    g_skinner_wave11_ports.paint_region_005296b0(active, &low, &high,
                                                 0xffffffffu);
    g_skinner_wave11_ports.end_render_00529bf0(active);
    g_skinner_wave11_ports.swap_00518b00(active, slot);
  }

  job->field_018 += batch_count;
  return job->field_018 > job->field_014 ? 1u : 0u;
}

extern "C" TargetByte PKG_SKINNER_WAVE11_THISCALL
skin_tex0_full_region_00518bf0(OpaqueTexturePainter *job) {
  static_cast<void>(job);
  OpaqueSkinPainter *first =
      g_skinner_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter *primary = first->textures_010[0];
  OpaqueSkinPainter *second =
      g_skinner_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter *secondary = second->textures_010[1];

  g_skinner_wave11_ports.start_render_00528e90(primary);
  g_skinner_wave11_ports.set_color_write_00529280(primary, 0u, 0u, 0u, 1u);
  primary->field_004 = kMaterialTex0Full;

  OpaqueHandle *raster = secondary->field_060;
  if (raster != nullptr) {
    raise_raster_count(primary, 0);
  }
  primary->rasters_03c = raster;

  const OpaqueVec2 low = zero_pair();
  const OpaqueVec2 high = unit_pair();
  g_skinner_wave11_ports.paint_region_005296b0(primary, &low, &high,
                                               0xffffffffu);
  g_skinner_wave11_ports.set_color_write_00529280(primary, 1u, 1u, 1u, 1u);
  g_skinner_wave11_ports.end_render_00529bf0(primary);
  return 1u;
}

extern "C" TargetByte PKG_SKINNER_WAVE11_THISCALL
skin_tex2_uv_region_00518cf0(OpaqueRefObject *job) {
  static_cast<void>(job);
  float scale = g_skinner_wave11_ports.get_scale_006a2710(
      g_skinner_wave11_scale_source, kKeyTuneQuery);
  if (scale == kScaleZero) {
    scale = kScaleFallback;
  }

  OpaqueSkinPainter *painter =
      g_skinner_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter *active = painter->textures_010[2];

  g_skinner_wave11_ports.start_render_00528e90(active);
  active->field_004 = kMaterialTex2Uv;

  OpaqueHandle *raster = painter->textures_010[1]->field_060;
  if (raster != nullptr) {
    raise_raster_count(active, 0);
  }
  active->rasters_03c = raster;

  OpaqueVec4f param;
  param.a = inverse_extent(active->field_058);
  param.b = inverse_extent(active->field_05c);
  param.c = scale / kScaleThird;
  param.d = kScaleZero;
  raise_param_count(active, 0);
  store_param(active, 0, param);

  const OpaqueVec2 low = zero_pair();
  const OpaqueVec2 high = unit_pair();
  g_skinner_wave11_ports.paint_region_005296b0(active, &low, &high,
                                               0xffffffffu);
  g_skinner_wave11_ports.end_render_00529bf0(active);
  return 1u;
}

extern "C" TargetByte PKG_SKINNER_WAVE11_THISCALL
skin_rig_block_draw_00518f10(OpaqueTexturePainter *job) {
  static_cast<void>(job);
  OpaquePaintSystem *system =
      g_skinner_wave11_ports.get_paint_system_00401080();
  OpaqueBatch *batch = system->batch_010;
  OpaqueSkinPainter *painter = system->painter_00c;
  OpaqueMesh *mesh =
      g_skinner_wave11_ports.get_paint_system_00401080()->mesh_020;

  const OpaqueRigblock *rigblocks = mesh->field_008->rigblocks_098;
  const TargetSignedWord rig_total = rigblock_count(mesh);

  float tune_low = kScaleUnit;
  float tune_high = kScaleZero;
  const TargetWord colour = kColourMask;

  const TargetWord material = g_skinner_wave11_ports.classify_004bb860(
                                  mesh->field_008->field_018) == kClassifyKey
                                  ? kMaterialHit
                                  : kMaterialMiss;

  OpaqueRefObject *target = g_skinner_wave11_ports.get_render_object_0067de30();
  OpaqueRefObject *lazy = nullptr;
  const TargetWord lazy_slot =
      g_skinner_wave11_ports.lazy_reset_0041d870(&lazy);

  OpaqueRenderObjectVTable *dispatch =
      reinterpret_cast<OpaqueRenderObjectVTable *>(target->vtable_000);
  if (dispatch->dispatch_02c(target, material, colour, lazy_slot) != 0u) {
    // 0x0051916a and 0x00519187 push the value stored in the lazy slot, and
    // 0x0041d870 always leaves that slot null, so the receiver is zero.
    g_skinner_wave11_ports.get_float_0040cf10(kLazySlotValue, kKeyTuneA,
                                              &tune_low);
    g_skinner_wave11_ports.get_float_0040cf10(kLazySlotValue, kKeyTuneB,
                                              &tune_high);
  }

  for (TargetWord pass = 0; pass < 2u; ++pass) {
    OpaqueTexturePainter *active =
        pass == 0u ? painter->textures_010[0] : painter->textures_010[1];
    g_skinner_wave11_ports.start_render_00528e90(active);
    // 0x005191e7 pushes (1,1,1,0) for the first pass and 0x00519217 pushes
    // (1,0,0,0) for the second, so the second pass clears the two inner
    // write flags and both passes clear the fourth.
    g_skinner_wave11_ports.set_color_write_00529280(
        active, 1u, pass == 0u ? 1u : 0u, pass == 0u ? 1u : 0u, 0u);
    active->field_004 = kMaterialRigBlock;

    OpaqueVec4f param;
    param.a = tune_low;
    param.b = tune_high;
    param.c = kScaleZero;
    param.d = kScaleZero;
    raise_param_count(active, 0);
    store_param(active, 0, param);

    OpaqueHandle *raster = reinterpret_cast<OpaqueHandle *>(
        g_skinner_wave11_ports.get_raster_00525aa0(system));
    if (raster != nullptr) {
      raise_raster_count(active, 0);
    }
    active->rasters_03c = raster;

    TargetSignedWord drain = 0;
    // 0x00519375 subtracts the two array words as raw addresses and 0x00519377
    // shifts the byte span right by two, because the array holds four byte
    // slot pointers, not slots by value.
    const TargetSignedWord drain_total = static_cast<TargetSignedWord>(
        (reinterpret_cast<const TargetByte *>(batch->slots_end_0e8) -
         reinterpret_cast<const TargetByte *>(batch->slots_begin_0e4)) >>
        2);
    for (TargetSignedWord index = 0; index < rig_total; ++index) {
      if ((rigblocks[index].flags_008 & 1u) != 0u) {
        continue;
      }
      float tone = kScaleUnit;
      g_skinner_wave11_ports.get_float_0040cf10(mesh->ids_00c[index], kKeyTone,
                                                &tone);
      float clamped = tone < kScaleZero ? kScaleZero : tone;
      clamped *= kByteScale;
      clamped = clamped > kByteScale ? kByteScale : clamped;
      // 0x00519427 is CVTSS2SI, which rounds to nearest, not a truncating cast.
      const TargetWord packed =
          static_cast<TargetWord>(quantise_byte_round_to_nearest(clamped));
      const TargetWord shade =
          packed | (packed << 8) | (packed << 16) | (packed << 24);
      const OpaqueBatchSlot *const slot = batch->slots_begin_0e4[drain];
      const OpaqueVec2 low = slot_extent_x(slot);
      const OpaqueVec2 high = slot_extent_y(slot);
      ++drain;
      g_skinner_wave11_ports.paint_region_005296b0(active, &low, &high, shade);
    }
    for (; drain < drain_total; ++drain) {
      const OpaqueBatchSlot *const slot = batch->slots_begin_0e4[drain];
      const OpaqueVec2 low = slot_extent_x(slot);
      const OpaqueVec2 high = slot_extent_y(slot);
      g_skinner_wave11_ports.paint_region_005296b0(active, &low, &high,
                                                   0xffffffffu);
    }
    g_skinner_wave11_ports.set_color_write_00529280(active, 1u, 1u, 1u, 1u);
    g_skinner_wave11_ports.end_render_00529bf0(active);
  }

  if (lazy != nullptr) {
    ref_vtable_of(lazy)->release_004(lazy);
  }
  return 1u;
}

extern "C" TargetByte PKG_SKINNER_WAVE11_THISCALL
skin_rig_pass_state_00519640(OpaqueSkinJobState *job) {
  OpaquePaintSystem *system =
      g_skinner_wave11_ports.get_paint_system_00401080();
  OpaqueSkinPainter *painter = system->painter_00c;
  OpaqueTexturePainter *primary = painter->textures_010[0];
  OpaqueTexturePainter *secondary = painter->textures_010[1];
  OpaqueMesh *mesh =
      g_skinner_wave11_ports.get_paint_system_00401080()->mesh_020;
  const TargetSignedWord rig_total = rigblock_count(mesh);
  const OpaqueRigblock *rigblocks = mesh->field_008->rigblocks_098;

  if (job->field_010 == kRigStateSkip) {
    job->field_010 = kRigStateSkip + 1;
  }
  if (job->field_010 >= kRigStatePass) {
    return job->field_010 == kRigStatePass ? 1u : 0u;
  }

  const bool wide = job->field_010 >= kRigStateSkip;
  g_skinner_wave11_ports.start_render_00528e90(wide ? secondary : primary);

  OpaqueVec3f table[3];
  table[0].a = kScaleZero;
  table[0].b = kScaleZero;
  table[0].c = kScaleZero;
  table[1].a = kScaleZero;
  table[1].b = kScaleZero;
  table[1].c = kScaleZero;
  table[2].a = kScaleZero;
  table[2].b = kScaleZero;
  table[2].c = kScaleZero;
  for (TargetSignedWord i = 0; i < 3; ++i) {
    g_skinner_wave11_ports.copy_vec3_004098a0(
        &table[i],
        reinterpret_cast<const OpaqueVec3f *>(g_skinner_wave11_scale + i * 3));
  }
  table[2].c = kScaleZero;

  float scale = g_skinner_wave11_ports.get_scale_006a2710(
      g_skinner_wave11_scale_source, kKeyScale);
  if (scale == kScaleZero) {
    scale = kScaleUnit;
  }

  TargetSignedWord passes = 0;
  for (;;) {
    if (job->field_014 >= rig_total) {
      break;
    }
    if (passes >= kRigPassLimit) {
      break;
    }
    if ((rigblocks[job->field_014].flags_008 & 1u) != 0u) {
      job->field_014 += 1;
      continue;
    }
    ++passes;

    const OpaqueVec4f *entry = mesh->slots_090 + job->field_014;
    const OpaqueVec2 low = entry_low(entry);
    const OpaqueVec2 high = entry_high(entry);
    OpaqueElement *element =
        reinterpret_cast<OpaqueElement *>(mesh->ids_00c[job->field_014]);

    OpaqueRefObject *slot_a = nullptr;
    OpaqueRefObject *slot_b = nullptr;
    OpaqueRefObject *slot_c = nullptr;
    if (job->field_010 == 0) {
      slot_a = resolve_block(element, kKeySlotA);
    }
    if (job->field_010 == 0 || job->field_010 == 1) {
      slot_b = resolve_block(element, kKeySlotB);
    }
    if (job->field_010 == 2 || job->field_010 == 3) {
      slot_c = resolve_block(element, kKeySlotC);
    }

    if (job->field_010 == 0 && slot_a != nullptr && slot_b != nullptr) {
      g_skinner_wave11_ports.set_color_write_00529280(primary, 1u, 1u, 1u, 0u);
      primary->field_004 = kMaterialBase;
      raise_param_count(primary, 0);
      store_param(primary, 0, widen(table[0]));
      raise_param_count(primary, 1);
      store_param(primary, 1, widen(table[1]));
      raise_param_count(primary, 2);
      store_param(primary, 2, widen(table[2]));
      OpaqueRenderTargetManager *manager =
          g_skinner_wave11_ports.get_render_target_manager_0067dd60();
      prepare_slot(manager, slot_a);
      bind_raster(primary, slot_a, false);
      prepare_slot(manager, slot_b);
      bind_raster(primary, slot_b, true);
      g_skinner_wave11_ports.paint_region_005296b0(primary, &low, &high,
                                                   0xffffffffu);
    }
    if (job->field_010 == 1 && slot_b != nullptr) {
      g_skinner_wave11_ports.set_color_write_00529280(primary, 0u, 0u, 0u, 1u);
      primary->field_004 = kMaterialOverlay;
      const OpaqueVec4f flat = flat_unit();
      raise_param_count(primary, 0);
      store_param(primary, 0, flat);
      OpaqueRenderTargetManager *manager =
          g_skinner_wave11_ports.get_render_target_manager_0067dd60();
      prepare_slot(manager, slot_b);
      bind_raster(primary, slot_b, false);
      primary->rasters_040 = nullptr;
      g_skinner_wave11_ports.paint_region_005296b0(primary, &low, &high,
                                                   0xffffffffu);
    }
    if (job->field_010 == 2 && slot_c != nullptr) {
      OpaqueVec4f flat;
      flat.a = painter->scale_030;
      flat.b = painter->scale_030;
      flat.c = painter->scale_030;
      flat.d = kScaleUnit;
      g_skinner_wave11_ports.set_color_write_00529280(secondary, 1u, 0u, 0u,
                                                      0u);
      secondary->field_004 = kMaterialRim;
      raise_param_count(secondary, 0);
      store_param(secondary, 0, flat);
      OpaqueRenderTargetManager *manager =
          g_skinner_wave11_ports.get_render_target_manager_0067dd60();
      prepare_slot(manager, slot_c);
      bind_raster(secondary, slot_c, false);
      g_skinner_wave11_ports.paint_region_005296b0(secondary, &low, &high,
                                                   0xffffffffu);
    }
    if (job->field_010 == 3 && slot_c != nullptr) {
      const float value = painter->scale_02c * scale;
      OpaqueVec4f flat;
      flat.a = value;
      flat.b = value;
      flat.c = value;
      flat.d = kScaleUnit;
      g_skinner_wave11_ports.set_color_write_00529280(secondary, 0u, 0u, 1u,
                                                      0u);
      secondary->field_004 = kMaterialScale;
      raise_param_count(secondary, 0);
      store_param(secondary, 0, flat);
      OpaqueRenderTargetManager *manager =
          g_skinner_wave11_ports.get_render_target_manager_0067dd60();
      prepare_slot(manager, slot_c);
      bind_raster(secondary, slot_c, false);
      g_skinner_wave11_ports.paint_region_005296b0(secondary, &low, &high,
                                                   0xffffffffu);
    }
    job->field_014 += 1;
  }

  g_skinner_wave11_ports.end_render_00529bf0(wide ? secondary : primary);

  if (job->field_014 >= rig_total) {
    job->field_014 = 0;
    job->field_010 += 1;
  }
  return job->field_010 == kRigStatePass ? 1u : 0u;
}

extern "C" TargetByte PKG_SKINNER_WAVE11_THISCALL
skin_rig_index_pass_0051a350(OpaqueSkinJobState *job) {
  OpaquePaintSystem *system =
      g_skinner_wave11_ports.get_paint_system_00401080();
  OpaqueSkinPainter *painter = system->painter_00c;
  OpaqueTexturePainter *primary = painter->textures_010[0];
  OpaqueMesh *mesh =
      g_skinner_wave11_ports.get_paint_system_00401080()->mesh_020;
  const TargetSignedWord rig_total = rigblock_count(mesh);
  const OpaqueRigblock *rigblocks = mesh->field_008->rigblocks_098;

  g_skinner_wave11_ports.start_render_00528e90(primary);

  TargetSignedWord passes = 0;
  for (;;) {
    if (job->field_010 >= rig_total) {
      break;
    }
    if (passes >= kRigPassLimit) {
      break;
    }
    if ((rigblocks[job->field_010].flags_008 & 1u) != 0u) {
      job->field_010 += 1;
      continue;
    }

    const OpaqueVec4f *entry = mesh->slots_090 + job->field_010;
    const OpaqueVec2 low = entry_low(entry);
    const OpaqueVec2 high = entry_high(entry);

    OpaqueKeyBlock block = {0u, 0u, 0u};
    OpaqueRefObject *made = nullptr;
    if (g_skinner_wave11_ports.get_key_006a1250(mesh->ids_00c[job->field_010],
                                                kKeySlotB, &block)) {
      OpaqueRenderTargetManager *manager =
          g_skinner_wave11_ports.get_render_target_manager_0067dd60();
      made = manager->vtable_000->create_01c(manager, block, kCreateBlockTags);
    }

    if (made != nullptr) {
      const OpaqueVec4f flat = flat_unit();
      g_skinner_wave11_ports.set_color_write_00529280(primary, 0u, 0u, 0u, 1u);
      primary->field_004 = kMaterialOverlay;
      raise_param_count(primary, 0);
      store_param(primary, 0, flat);
      OpaqueRenderTargetManager *manager =
          g_skinner_wave11_ports.get_render_target_manager_0067dd60();
      prepare_slot(manager, made);
      bind_raster(primary, made, false);
      primary->rasters_040 = nullptr;
      g_skinner_wave11_ports.paint_region_005296b0(primary, &low, &high,
                                                   0xffffffffu);
      ++passes;
    }
    job->field_010 += 1;
  }

  g_skinner_wave11_ports.end_render_00529bf0(primary);
  return job->field_010 >= rig_total ? 1u : 0u;
}

extern "C" void PKG_SKINNER_WAVE11_THISCALL skin_job_setup_0051a9a0(
    OpaqueSkinJob *job, TargetWord arg_1, TargetByte arg_2, TargetByte arg_3,
    TargetWord arg_4, TargetWord arg_5, TargetWord arg_6, TargetWord arg_7,
    TargetByte arg_8, TargetByte arg_9, TargetByte arg_10) {
  job->cursor_340 = 0u;
  g_skinner_wave11_ports.truncate_004259e0(
      reinterpret_cast<OpaqueVector *>(&job->array_008),
      reinterpret_cast<OpaqueRefObject *>(job->array_008),
      reinterpret_cast<OpaqueRefObject *>(job->array_00c));
  job->cursor_340 = 0u;
  job->calls_344 = 0u;
  job->field_338 = arg_1;
  job->flag_348 = arg_2;
  job->flag_349 = arg_3;
  job->flag_34a = g_skinner_wave11_ports.get_paint_system_00401080()->byte_07e;
  job->field_320 = arg_4;
  job->field_324 = arg_5;
  job->field_328 = arg_6;
  job->field_32c = arg_7;
  job->flag_34b = arg_8;
  job->flag_34c = arg_9;
  job->flag_34d = arg_10;
  job->flag_34e = 0u;
  skin_job_collect_0051ab50(job, static_cast<TargetWord>(arg_2));
}

extern "C" void PKG_SKINNER_WAVE11_THISCALL
skin_job_collect_0051ab50(OpaqueSkinJob *job, TargetWord arg_1) {
  OpaqueSkinPainter *painter =
      g_skinner_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueMesh *mesh =
      g_skinner_wave11_ports.get_paint_system_00401080()->mesh_020;
  if (painter == nullptr || mesh == nullptr) {
    return;
  }

  const OpaqueRigblock *rigblocks = mesh->field_008->rigblocks_098;
  OpaqueVector *vector = reinterpret_cast<OpaqueVector *>(&job->array_008);

  OpaqueCursorQuad cursor;
  cursor.field_000 = 0u;
  cursor.field_004 = 0u;
  // 0x0051ac6d reads [EDX+ECX*4+0x4] with EDX loaded from [EBP-0x8], the value
  // of slot.field_000, so the triple is slot.field_000 + 4 + 4i. The two upper
  // words of the local quad are never written, and the loop tests whatever the
  // slot itself holds there.
  cursor.field_008 = 0u;
  cursor.field_00c = 0u;

  OpaqueSlotHandle slot;
  slot.field_000 = *reinterpret_cast<TargetWord *>(painter->field_040);
  slot.field_004 = painter->field_040;
  if (slot.field_000 == 0u) {
    g_skinner_wave11_ports.acquire_slot_00552750(&slot);
  }
  cursor.field_000 = slot.field_000;
  cursor.field_004 = slot.field_004;

  const TargetWord *end_slot = reinterpret_cast<const TargetWord *>(
      painter->field_040 +
      static_cast<TargetSignedWord>(painter->count_044) * 4);
  if (cursor.field_000 == *end_slot) {
    OpaqueRenderTargetManager *manager =
        g_skinner_wave11_ports.get_render_target_manager_0067dd60();
    OpaqueRefObject *made =
        manager->vtable_000->create_020(manager, 0u, 0u, kCreateRawKey);
    refcount_add(made);
    g_skinner_wave11_ports.collect_0051d1e0(vector, &made);
    if (made != nullptr) {
      g_skinner_wave11_ports.release_one_00402420(made);
    }
  } else {
    TargetWord *const entries = reinterpret_cast<TargetWord *>(
        static_cast<std::uintptr_t>(slot.field_000));
    for (TargetSignedWord i = 0; i < 3; ++i) {
      if (entries[i + 1u] == 0u) {
        continue;
      }
      g_skinner_wave11_ports.collect_0051d1e0(
          vector, reinterpret_cast<OpaqueRefObject **>(&entries[i + 1u]));
    }
    g_skinner_wave11_ports.rewind_0051d140(vector);
  }

  if (static_cast<TargetByte>(arg_1) == 0u) {
    return;
  }

  for (TargetSignedWord i = 0; i < rigblock_count(mesh); ++i) {
    if ((rigblocks[i].flags_008 & 1u) != 0u) {
      continue;
    }
    const TargetWord id = mesh->ids_00c[i];
    static const TargetWord kKeys[3] = {kKeySlotA, kKeySlotB, kKeySlotC};
    for (TargetWord k = 0; k < 3u; ++k) {
      OpaqueKeyBlock block = {0u, 0u, 0u};
      if (!g_skinner_wave11_ports.get_key_006a1250(id, kKeys[k], &block)) {
        continue;
      }
      OpaqueRenderTargetManager *manager =
          g_skinner_wave11_ports.get_render_target_manager_0067dd60();
      OpaqueRefObject *made =
          manager->vtable_000->create_01c(manager, block, kCreateBlockTags);
      refcount_add(made);
      g_skinner_wave11_ports.collect_0051d1e0(vector, &made);
      if (made != nullptr) {
        g_skinner_wave11_ports.release_one_00402420(made);
      }
    }
  }
}

extern "C" void PKG_SKINNER_WAVE11_THISCALL
skin_job_state_step_0051afd0(OpaqueSkinJob *job) {
  OpaquePaintSystem *system =
      g_skinner_wave11_ports.get_paint_system_00401080();
  job->calls_344 += 1u;

  switch (job->state_33c) {
    case 0u:
      job->state_33c = 1u;
      [[fallthrough]];
    case 1u:
      job->state_33c = 2u;
      [[fallthrough]];
    case 2u: {
      job->state_33c = 3u;
      const TargetSignedWord count =
          static_cast<TargetSignedWord>(job->array_00c - job->array_008);
      for (TargetSignedWord i = 0; i < count; ++i) {
        OpaqueElement *element =
            reinterpret_cast<OpaqueElement *>(job->array_008[i]);
        if (element == nullptr) {
          continue;
        }
        if ((element->opaque_004[0] & 1u) != 0u) {
          continue;
        }
        job->cursor_340 += 1u;
        return;
      }
      [[fallthrough]];
    }
    case 3u: {
      job->state_33c = 3u;
      OpaqueRefObject *fresh = nullptr;
      if (job->handle_330 == nullptr) {
        OpaqueRefObject *object = acquire_plain(kAcquireSizeStage);
        if (object != nullptr) {
          fresh = reinterpret_cast<OpaqueRefObject *>(
              g_skinner_wave11_ports.job_init_primary_00517310(
                  object, job->field_338, job->flag_349 == 0u ? 1u : 0u));
        }
        ref_assign(&job->handle_330, fresh);
      }
      ref_vtable_of(job->handle_330)->step_010(job->handle_330);
      ref_maybe_drop(job);
      [[fallthrough]];
    }
    case 4u: {
      job->state_33c = 4u;
      if (job->flag_348 != 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          fresh = acquire_vtable(kAcquireSizeJob, kJobVTableA);
          if (fresh != nullptr) {
            fresh->field_010 = 0u;
            fresh->field_014 = 0u;
          }
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 5u: {
      job->state_33c = 5u;
      if (job->flag_348 != 0u && job->flag_34a != 0u &&
          system->byte_07c == 0u) {
        return;
      }
      [[fallthrough]];
    }
    case 6u: {
      job->state_33c = 6u;
      if (job->flag_348 != 0u && job->flag_34a != 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          fresh = acquire_vtable(kAcquireSizeRaw, kJobVTableB);
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 7u: {
      job->state_33c = 7u;
      if (job->flag_348 != 0u && job->flag_34e == 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          fresh = acquire_vtable(kAcquireSizeJobWide, kJobVTableC);
          if (fresh != nullptr) {
            fresh->field_010 = 0u;
            fresh->field_014 = kJobField14Eight;
            fresh->field_018 = kJobField18Zero;
          }
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 8u: {
      job->state_33c = 8u;
      if (job->flag_348 != 0u && job->flag_34e == 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          fresh = acquire_vtable(kAcquireSizeJobWide, kJobVTableC);
          if (fresh != nullptr) {
            fresh->field_010 = 1u;
            fresh->field_014 = kJobField14Eight;
            fresh->field_018 = kJobField18Zero;
          }
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 9u: {
      job->state_33c = 9u;
      if (job->flag_348 != 0u && job->flag_349 != 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          fresh = acquire_vtable(kAcquireSizeRaw, kJobVTableD);
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 10u: {
      job->state_33c = 10u;
      if (job->flag_348 != 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          fresh = acquire_vtable(kAcquireSizeMid, kJobVTableE);
          if (fresh != nullptr) {
            fresh->field_010 = 0u;
          }
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 11u: {
      job->state_33c = 11u;
      if (job->field_324 != 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          OpaqueRefObject *object = acquire_plain(kAcquireSizeWide);
          if (object != nullptr) {
            OpaqueRefObject *made = g_skinner_wave11_ports.job_build_0051c470(
                object, 0u, job->field_320, job->field_324, job->flag_34d,
                job->field_32c, 0u, job->flag_34c);
            fresh = offset_eight(made);
          }
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 12u: {
      job->state_33c = 12u;
      if (job->field_328 != 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          fresh = acquire_vtable(kAcquireSizeRaw, kJobVTableF);
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 13u: {
      job->state_33c = 13u;
      if (job->field_328 != 0u) {
        OpaqueRefObject *fresh = nullptr;
        if (job->handle_330 == nullptr) {
          OpaqueRefObject *object = acquire_plain(kAcquireSizeWide);
          if (object != nullptr) {
            OpaqueRefObject *made = g_skinner_wave11_ports.job_build_0051c470(
                object, 2u, job->field_320, job->field_328, job->flag_34d,
                0xffffffffu, job->flag_34b, job->flag_34c);
            fresh = offset_eight(made);
          }
          ref_assign(&job->handle_330, fresh);
        }
        ref_vtable_of(job->handle_330)->step_010(job->handle_330);
        ref_maybe_drop(job);
      }
      [[fallthrough]];
    }
    case 14u:
      [[fallthrough]];
    default:
      if (job->state_33c == kStateTerminal) {
        return;
      }
      job->state_33c = kStateTerminal;
      return;
  }
}

}  // namespace openspore::reconstruction::pkg_skinner_wave11

#undef PKG_SKINNER_WAVE11_THISCALL
