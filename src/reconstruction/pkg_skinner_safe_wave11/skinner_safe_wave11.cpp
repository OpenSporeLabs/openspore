#include "skinner_safe_wave11.hpp"

#include <cmath>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_SKINNER_SAFE_WAVE11_THISCALL __thiscall
#else
#define PKG_SKINNER_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_skinner_safe_wave11 {

SkinnerSafeWave11Ports g_skinner_safe_wave11_ports{};

OpaqueRefObject* g_skinner_safe_wave11_scale_source = nullptr;

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

OpaqueVec2 entry_low(const OpaqueVec4f* entry) {
  OpaqueVec2 pair;
  pair.a = entry->a;
  pair.b = entry->b;
  return pair;
}

OpaqueVec2 entry_high(const OpaqueVec4f* entry) {
  OpaqueVec2 pair;
  pair.a = entry->c;
  pair.b = entry->d;
  return pair;
}

OpaqueVec2 slot_extent_x(const OpaqueBatchSlot* slot) {
  OpaqueVec2 pair;
  pair.a = slot->field_058;
  pair.b = slot->field_060;
  return pair;
}

OpaqueVec2 slot_extent_y(const OpaqueBatchSlot* slot) {
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

void raise_param_count(OpaqueTexturePainter* painter, TargetSignedWord want) {
  if (painter->count_044 <= want) {
    painter->count_044 = want + 1;
  }
}

void raise_raster_count(OpaqueTexturePainter* painter, TargetSignedWord want) {
  if (painter->count_048 <= want) {
    painter->count_048 = want + 1;
  }
}

void store_param(OpaqueTexturePainter* painter, TargetSignedWord index,
                 const OpaqueVec4f& value) {
  OpaqueVec4f* slot = reinterpret_cast<OpaqueVec4f*>(
      reinterpret_cast<std::uint8_t*>(&painter->params_00c) +
      static_cast<std::size_t>(index) * sizeof(OpaqueVec4f));
  *slot = value;
}
float inverse_extent(TargetWord value) {
  return static_cast<float>(
      1.0 / static_cast<double>(static_cast<std::int64_t>(value)));
}

TargetSignedWord rigblock_count(const OpaqueMesh* mesh) {
  const OpaqueRigblock* begin = mesh->field_008->rigblocks_098;
  const OpaqueRigblock* end = mesh->field_008->rigblocks_09c;
  return static_cast<TargetSignedWord>(end - begin);
}
OpaqueRefVTable* ref_vtable_of(OpaqueRefObject* object) {
  return g_skinner_safe_wave11_ports.resolve_ref_vtable(
      reinterpret_cast<TargetWord>(object->vtable_000));
}
void prepare_slot(OpaqueRenderTargetManager* manager, OpaqueRefObject* target) {
  if ((target->field_004 & 1u) != 0u) {
    return;
  }
  manager->vtable_000->prepare_034(manager, target);
}

void bind_raster(OpaqueTexturePainter* painter, OpaqueRefObject* target,
                 bool second) {
  OpaqueHandle* handle = reinterpret_cast<OpaqueHandle*>(target->vtable_000);
  raise_raster_count(painter, second ? 1 : 0);
  if (second) {
    painter->rasters_040 = handle;
  } else {
    painter->rasters_03c = handle;
  }
}

}  // namespace

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_paint_slot_pass_005183c0(OpaqueSkinJobState* job) {
  const OpaqueVec2 shared = zero_pair();
  const OpaqueVec3w tone = {0u, 0u, 0u};
  const TargetWord shared_tail = 0u;

  OpaqueSkinPainter* painter =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter* slot = painter->textures_010[job->field_010];

  if (job->field_018 == 0) {
    g_skinner_safe_wave11_ports.start_render_00528e90(slot);
    g_skinner_safe_wave11_ports.set_color_write_00529280(slot, 0u, 0u, 0u, 1u);
    slot->field_004 = kMaterialPassSetup;
    g_skinner_safe_wave11_ports.set_vertex_limit_00529520(slot, kPassSlot);

    const OpaqueVec2 first = zero_pair();
    g_skinner_safe_wave11_ports.emit_005295b0(slot, &first, &shared, &tone,
                                              shared_tail);
    const OpaqueVec2 second = axis_pair(kScaleUnit, kScaleZero);
    g_skinner_safe_wave11_ports.emit_005295b0(slot, &second, &shared, &tone,
                                              shared_tail);
    const OpaqueVec2 third = unit_pair();
    g_skinner_safe_wave11_ports.emit_005295b0(slot, &third, &shared, &tone,
                                              shared_tail);
    g_skinner_safe_wave11_ports.emit_005295b0(slot, &third, &shared, &tone,
                                              shared_tail);
    const OpaqueVec2 fifth = axis_pair(kScaleZero, kScaleUnit);
    g_skinner_safe_wave11_ports.emit_005295b0(slot, &fifth, &shared, &tone,
                                              shared_tail);
    const OpaqueVec2 sixth = zero_pair();
    g_skinner_safe_wave11_ports.emit_005295b0(slot, &sixth, &shared, &tone,
                                              shared_tail);
    g_skinner_safe_wave11_ports.flush_00529690(slot);

    OpaqueBatch* batch =
        g_skinner_safe_wave11_ports.get_paint_system_00401080()->batch_010;
    TargetSignedWord remaining = static_cast<TargetSignedWord>(
        batch->parts_end_05c - batch->parts_begin_058);
    remaining /= 3;

    TargetSignedWord index = 0;
    while (remaining != 0) {
      const TargetSignedWord taken = static_cast<TargetSignedWord>(
          g_skinner_safe_wave11_ports.set_vertex_limit_00529520(
              slot, static_cast<TargetWord>(remaining)));
      const TargetSignedWord stop = taken * 3 + index;
      for (; index < stop; ++index) {
        const TargetWord* entry = batch->index_080 + index;
        const TargetWord* base = batch->vertices_030 + *entry * 8u;
        g_skinner_safe_wave11_ports.emit_005295b0(
            slot, reinterpret_cast<const OpaqueVec2*>(base),
            reinterpret_cast<const OpaqueVec2*>(base), &tone, kColourOpaque);
      }
      remaining -= taken;
      g_skinner_safe_wave11_ports.flush_00529690(slot);
    }

    g_skinner_safe_wave11_ports.set_color_write_00529280(slot, 1u, 1u, 1u, 1u);
    g_skinner_safe_wave11_ports.end_render_00529bf0(slot);
    job->field_018 = 1;
    return 0u;
  }

  OpaqueGraphicsProbe* probe =
      g_skinner_safe_wave11_ports.get_graphics_probe_0067dd00();
  const TargetWord steps =
      probe->vtable_000->query_044(probe) != 0u ? kPassNormal : kPassSmall;

  const TargetSignedWord remaining = job->field_014 - job->field_018 + 1;
  const TargetSignedWord batch_count =
      remaining < static_cast<TargetSignedWord>(steps)
          ? remaining
          : static_cast<TargetSignedWord>(steps);

  OpaqueTexturePainter* active =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()
          ->painter_00c->textures_010[2];
  for (TargetSignedWord pass = 0; pass < batch_count; ++pass) {
    g_skinner_safe_wave11_ports.start_render_00528e90(active);
    active->field_004 = kMaterialPassLoop;

    OpaqueVec4f param;
    param.a = inverse_extent(slot->field_058);
    param.b = inverse_extent(slot->field_05c);
    param.c = kScaleZero;
    param.d = kScaleZero;
    raise_param_count(active, 0);
    store_param(active, 0, param);

    OpaqueHandle* raster = slot->field_060;
    if (raster != nullptr) {
      raise_raster_count(active, 0);
    }
    active->rasters_03c = raster;

    const OpaqueVec2 low = zero_pair();
    const OpaqueVec2 high = unit_pair();
    g_skinner_safe_wave11_ports.paint_region_005296b0(active, &low, &high,
                                                      0xffffffffu);
    g_skinner_safe_wave11_ports.end_render_00529bf0(active);
    g_skinner_safe_wave11_ports.swap_00518b00(active, slot);
  }

  job->field_018 += batch_count;
  return job->field_018 > job->field_014 ? 1u : 0u;
}

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_tex0_full_region_00518bf0(OpaqueTexturePainter* job) {
  static_cast<void>(job);
  OpaqueSkinPainter* first =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter* primary = first->textures_010[0];
  OpaqueSkinPainter* second =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter* secondary = second->textures_010[1];

  g_skinner_safe_wave11_ports.start_render_00528e90(primary);
  g_skinner_safe_wave11_ports.set_color_write_00529280(primary, 0u, 0u, 0u, 1u);
  primary->field_004 = kMaterialTex0Full;

  OpaqueHandle* raster = secondary->field_060;
  if (raster != nullptr) {
    raise_raster_count(primary, 0);
  }
  primary->rasters_03c = raster;

  const OpaqueVec2 low = zero_pair();
  const OpaqueVec2 high = unit_pair();
  g_skinner_safe_wave11_ports.paint_region_005296b0(primary, &low, &high,
                                                    0xffffffffu);
  g_skinner_safe_wave11_ports.set_color_write_00529280(primary, 1u, 1u, 1u, 1u);
  g_skinner_safe_wave11_ports.end_render_00529bf0(primary);
  return 1u;
}

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_tex2_uv_region_00518cf0(OpaqueRefObject* job) {
  static_cast<void>(job);
  float scale = g_skinner_safe_wave11_ports.get_scale_006a2710(
      g_skinner_safe_wave11_scale_source, kKeyTuneQuery);
  if (scale == kScaleZero) {
    scale = kScaleFallback;
  }

  OpaqueSkinPainter* painter =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()->painter_00c;
  OpaqueTexturePainter* active = painter->textures_010[2];

  g_skinner_safe_wave11_ports.start_render_00528e90(active);
  active->field_004 = kMaterialTex2Uv;

  OpaqueHandle* raster = painter->textures_010[1]->field_060;
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
  g_skinner_safe_wave11_ports.paint_region_005296b0(active, &low, &high,
                                                    0xffffffffu);
  g_skinner_safe_wave11_ports.end_render_00529bf0(active);
  return 1u;
}

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_rig_block_draw_00518f10(OpaqueTexturePainter* job) {
  static_cast<void>(job);
  OpaquePaintSystem* system =
      g_skinner_safe_wave11_ports.get_paint_system_00401080();
  OpaqueBatch* batch = system->batch_010;
  OpaqueSkinPainter* painter = system->painter_00c;
  OpaqueMesh* mesh =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()->mesh_020;

  const OpaqueRigblock* rigblocks = mesh->field_008->rigblocks_098;
  const TargetSignedWord rig_total = rigblock_count(mesh);

  float tune_low = kScaleUnit;
  float tune_high = kScaleZero;
  const TargetWord colour = kColourMask;

  const TargetWord material = g_skinner_safe_wave11_ports.classify_004bb860(
                                  mesh->field_008->field_018) == kClassifyKey
                                  ? kMaterialHit
                                  : kMaterialMiss;

  OpaqueRefObject* target =
      g_skinner_safe_wave11_ports.get_render_object_0067de30();
  OpaqueRefObject* lazy = nullptr;
  const TargetWord lazy_slot =
      g_skinner_safe_wave11_ports.lazy_reset_0041d870(&lazy);

  OpaqueRenderObjectVTable* dispatch =
      reinterpret_cast<OpaqueRenderObjectVTable*>(target->vtable_000);
  if (dispatch->dispatch_02c(target, material, colour, lazy_slot) != 0u) {
    // 0x0051916a and 0x00519187 push the value stored in the lazy slot, and
    // 0x0041d870 always leaves that slot null, so the receiver is zero.
    g_skinner_safe_wave11_ports.get_float_0040cf10(kLazySlotValue, kKeyTuneA,
                                                   &tune_low);
    g_skinner_safe_wave11_ports.get_float_0040cf10(kLazySlotValue, kKeyTuneB,
                                                   &tune_high);
  }

  for (TargetWord pass = 0; pass < 2u; ++pass) {
    OpaqueTexturePainter* active =
        pass == 0u ? painter->textures_010[0] : painter->textures_010[1];
    g_skinner_safe_wave11_ports.start_render_00528e90(active);
    // 0x005191e7 pushes (1,1,1,0) for the first pass and 0x00519217 pushes
    // (1,0,0,0) for the second, so the second pass clears the two inner
    // write flags and both passes clear the fourth.
    g_skinner_safe_wave11_ports.set_color_write_00529280(
        active, 1u, pass == 0u ? 1u : 0u, pass == 0u ? 1u : 0u, 0u);
    active->field_004 = kMaterialRigBlock;

    OpaqueVec4f param;
    param.a = tune_low;
    param.b = tune_high;
    param.c = kScaleZero;
    param.d = kScaleZero;
    raise_param_count(active, 0);
    store_param(active, 0, param);

    OpaqueHandle* raster = reinterpret_cast<OpaqueHandle*>(
        g_skinner_safe_wave11_ports.get_raster_00525aa0(system));
    if (raster != nullptr) {
      raise_raster_count(active, 0);
    }
    active->rasters_03c = raster;

    TargetSignedWord drain = 0;
    // 0x00519375 subtracts the two array words as raw addresses and 0x00519377
    // shifts the byte span right by two, because the array holds four byte
    // slot pointers, not slots by value.
    const TargetSignedWord drain_total = static_cast<TargetSignedWord>(
        (reinterpret_cast<const TargetByte*>(batch->slots_end_0e8) -
         reinterpret_cast<const TargetByte*>(batch->slots_begin_0e4)) >>
        2);
    for (TargetSignedWord index = 0; index < rig_total; ++index) {
      if ((rigblocks[index].flags_008 & 1u) != 0u) {
        continue;
      }
      float tone = kScaleUnit;
      g_skinner_safe_wave11_ports.get_float_0040cf10(mesh->ids_00c[index],
                                                     kKeyTone, &tone);
      float clamped = tone < kScaleZero ? kScaleZero : tone;
      clamped *= kByteScale;
      clamped = clamped > kByteScale ? kByteScale : clamped;
      // 0x00519427 is CVTSS2SI, which rounds to nearest, not a truncating cast.
      const TargetWord packed =
          static_cast<TargetWord>(quantise_byte_round_to_nearest(clamped));
      const TargetWord shade =
          packed | (packed << 8) | (packed << 16) | (packed << 24);
      const OpaqueBatchSlot* const slot = batch->slots_begin_0e4[drain];
      const OpaqueVec2 low = slot_extent_x(slot);
      const OpaqueVec2 high = slot_extent_y(slot);
      ++drain;
      g_skinner_safe_wave11_ports.paint_region_005296b0(active, &low, &high,
                                                        shade);
    }
    for (; drain < drain_total; ++drain) {
      const OpaqueBatchSlot* const slot = batch->slots_begin_0e4[drain];
      const OpaqueVec2 low = slot_extent_x(slot);
      const OpaqueVec2 high = slot_extent_y(slot);
      g_skinner_safe_wave11_ports.paint_region_005296b0(active, &low, &high,
                                                        0xffffffffu);
    }
    g_skinner_safe_wave11_ports.set_color_write_00529280(active, 1u, 1u, 1u,
                                                         1u);
    g_skinner_safe_wave11_ports.end_render_00529bf0(active);
  }

  if (lazy != nullptr) {
    ref_vtable_of(lazy)->release_004(lazy);
  }
  return 1u;
}

extern "C" TargetByte PKG_SKINNER_SAFE_WAVE11_THISCALL
skin_rig_index_pass_0051a350(OpaqueSkinJobState* job) {
  OpaquePaintSystem* system =
      g_skinner_safe_wave11_ports.get_paint_system_00401080();
  OpaqueSkinPainter* painter = system->painter_00c;
  OpaqueTexturePainter* primary = painter->textures_010[0];
  OpaqueMesh* mesh =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()->mesh_020;
  const TargetSignedWord rig_total = rigblock_count(mesh);
  const OpaqueRigblock* rigblocks = mesh->field_008->rigblocks_098;

  g_skinner_safe_wave11_ports.start_render_00528e90(primary);

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

    const OpaqueVec4f* entry = mesh->slots_090 + job->field_010;
    const OpaqueVec2 low = entry_low(entry);
    const OpaqueVec2 high = entry_high(entry);

    OpaqueKeyBlock block = {0u, 0u, 0u};
    OpaqueRefObject* made = nullptr;
    if (g_skinner_safe_wave11_ports.get_key_006a1250(
            mesh->ids_00c[job->field_010], kKeySlotB, &block)) {
      OpaqueRenderTargetManager* manager =
          g_skinner_safe_wave11_ports.get_render_target_manager_0067dd60();
      made = manager->vtable_000->create_01c(manager, block, kCreateBlockTags);
    }

    if (made != nullptr) {
      const OpaqueVec4f flat = flat_unit();
      g_skinner_safe_wave11_ports.set_color_write_00529280(primary, 0u, 0u, 0u,
                                                           1u);
      primary->field_004 = kMaterialOverlay;
      raise_param_count(primary, 0);
      store_param(primary, 0, flat);
      OpaqueRenderTargetManager* manager =
          g_skinner_safe_wave11_ports.get_render_target_manager_0067dd60();
      prepare_slot(manager, made);
      bind_raster(primary, made, false);
      primary->rasters_040 = nullptr;
      g_skinner_safe_wave11_ports.paint_region_005296b0(primary, &low, &high,
                                                        0xffffffffu);
      ++passes;
    }
    job->field_010 += 1;
  }

  g_skinner_safe_wave11_ports.end_render_00529bf0(primary);
  return job->field_010 >= rig_total ? 1u : 0u;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL skin_job_setup_0051a9a0(
    OpaqueSkinJob* job, TargetWord arg_1, TargetByte arg_2, TargetByte arg_3,
    TargetWord arg_4, TargetWord arg_5, TargetWord arg_6, TargetWord arg_7,
    TargetByte arg_8, TargetByte arg_9, TargetByte arg_10) {
  job->cursor_340 = 0u;
  g_skinner_safe_wave11_ports.truncate_004259e0(
      reinterpret_cast<OpaqueVector*>(&job->array_008),
      reinterpret_cast<OpaqueRefObject*>(job->array_008),
      reinterpret_cast<OpaqueRefObject*>(job->array_00c));
  job->cursor_340 = 0u;
  job->calls_344 = 0u;
  job->field_338 = arg_1;
  job->flag_348 = arg_2;
  job->flag_349 = arg_3;
  job->flag_34a =
      g_skinner_safe_wave11_ports.get_paint_system_00401080()->byte_07e;
  job->field_320 = arg_4;
  job->field_324 = arg_5;
  job->field_328 = arg_6;
  job->field_32c = arg_7;
  job->flag_34b = arg_8;
  job->flag_34c = arg_9;
  job->flag_34d = arg_10;
  job->flag_34e = 0u;
  g_skinner_safe_wave11_ports.collect_job_0051ab50(
      job, static_cast<TargetWord>(arg_2));
}

}  // namespace openspore::reconstruction::pkg_skinner_safe_wave11

#undef PKG_SKINNER_SAFE_WAVE11_THISCALL
