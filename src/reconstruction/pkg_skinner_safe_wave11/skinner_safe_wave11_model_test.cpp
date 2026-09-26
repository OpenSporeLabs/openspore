#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "skinner_safe_wave11.hpp"

#if defined(_MSC_VER)
#define PKG_SKINNER_SAFE_WAVE11_THISCALL __thiscall
#define PKG_SKINNER_SAFE_WAVE11_CDECL __cdecl
#else
#define PKG_SKINNER_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_SKINNER_SAFE_WAVE11_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_skinner_safe_wave11 {

namespace {

int g_failures = 0;
int g_checks = 0;
int g_tests = 0;

void check(bool ok, const char* what) {
  ++g_checks;
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

struct Trace {
  TargetWord start_render;
  TargetWord end_render;
  TargetWord set_color;
  TargetWord paint_region;
  TargetWord emit;
  TargetWord flush;
  TargetWord set_limit;
  TargetWord swap;
  TargetWord get_system;
  TargetWord get_probe;
  TargetWord get_manager;
  TargetWord get_key;
  TargetWord classify;
  TargetWord get_float;
  TargetWord get_raster;
  TargetWord get_scale;
  TargetWord get_render_object;
  TargetWord truncate;
  TargetWord lazy_reset;
  TargetWord ref_release;
  TargetWord manager_create_block;
  TargetWord manager_prepare;
  TargetWord element_has;
  TargetWord element_get;
  TargetWord probe_query;
  TargetWord collect_job;
  TargetWord render_dispatch;
};

struct EmitRecord {
  float pos[2];
  float uv[2];
  TargetWord normal[3];
  TargetWord colour;
};

struct PaintRecord {
  const OpaqueTexturePainter* painter;
  float a0[2];
  float a1[2];
  TargetWord a2;
};

struct FloatsRecord {
  TargetWord object;
  TargetWord key;
};

struct KeyRecord {
  TargetWord id;
  TargetWord key;
};

struct CreateRecord {
  TargetWord tag;
  TargetWord block[3];
};

struct BuildRecord {
  TargetWord arg[7];
};

struct Fixture {
  OpaqueTexturePainter tex[3];
  OpaqueSkinPainter painter;
  OpaqueMeshBlock block;
  OpaqueMesh mesh;
  OpaqueBatchSlot batch_slot[4];
  OpaqueBatchSlot* batch_slot_ptr[4];
  OpaqueBatch batch;
  OpaquePaintSystem system;
  OpaqueGraphicsProbe probe;
  OpaqueGraphicsProbeVTable probe_vtable;
  OpaqueRenderTargetManager manager;
  OpaqueRenderTargetManagerVTable manager_vtable;
  OpaqueRefObject target;
  OpaqueRefObject target2;
  OpaqueSkinJob* collect_job_receiver[4];
  TargetWord collect_job_argument[4];
  OpaqueRefObject render_object;
  OpaqueRefVTable ref_vtable;
  OpaqueRenderObjectVTable render_vtable;
  OpaqueRefVTable* resolved_vtable = nullptr;
  OpaqueRigblock rigblock[16];
  OpaqueVec4f mesh_slot[16];
  TargetWord mesh_id[16];
  TargetWord vertex[32];
  TargetWord index[32];
  TargetWord part[36];
  TargetWord owner[8];

  Trace trace{};
  EmitRecord emit[48];
  PaintRecord paint[48];
  FloatsRecord floats[48];
  KeyRecord key[48];
  CreateRecord create[48];
  BuildRecord build[16];
  TargetWord emit_count = 0;
  TargetWord paint_count = 0;
  TargetWord float_count = 0;
  TargetWord key_count = 0;
  TargetWord create_count = 0;
  TargetWord set_limit_value = 3u;
  float tone_value = 1.0F;
  TargetSignedWord classify_value = 0;
  TargetSignedWord key_mask = 0xf;
  TargetSignedWord scale_value = 0;
  bool probe_answer = false;
  bool dispatch_answer = false;
};

Fixture* g_fixture = nullptr;

extern "C" OpaquePaintSystem* PKG_SKINNER_SAFE_WAVE11_CDECL
stub_get_paint_system_00401080() {
  ++g_fixture->trace.get_system;
  return &g_fixture->system;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_start_render_00528e90(OpaqueTexturePainter*) {
  ++g_fixture->trace.start_render;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL stub_set_color_write_00529280(
    OpaqueTexturePainter*, TargetWord, TargetWord, TargetWord, TargetWord) {
  ++g_fixture->trace.set_color;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_paint_region_005296b0(OpaqueTexturePainter* painter, const OpaqueVec2* a0,
                           const OpaqueVec2* a1, TargetWord a2) {
  ++g_fixture->trace.paint_region;
  PaintRecord& record = g_fixture->paint[g_fixture->paint_count];
  record.painter = painter;
  record.a0[0] = a0->a;
  record.a0[1] = a0->b;
  record.a1[0] = a1->a;
  record.a1[1] = a1->b;
  record.a2 = a2;
  ++g_fixture->paint_count;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_end_render_00529bf0(OpaqueTexturePainter*) {
  ++g_fixture->trace.end_render;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL stub_emit_005295b0(
    OpaqueTexturePainter*, const OpaqueVec2* pos, const OpaqueVec2* uv,
    const OpaqueVec3w* nrm, TargetWord colour) {
  ++g_fixture->trace.emit;
  EmitRecord& record = g_fixture->emit[g_fixture->emit_count];
  record.pos[0] = pos->a;
  record.pos[1] = pos->b;
  record.uv[0] = uv->a;
  record.uv[1] = uv->b;
  record.normal[0] = nrm->a;
  record.normal[1] = nrm->b;
  record.normal[2] = nrm->c;
  record.colour = colour;
  ++g_fixture->emit_count;
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_set_vertex_limit_00529520(OpaqueTexturePainter*, TargetWord requested) {
  ++g_fixture->trace.set_limit;
  return requested < g_fixture->set_limit_value ? requested
                                                : g_fixture->set_limit_value;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_flush_00529690(OpaqueTexturePainter*) {
  ++g_fixture->trace.flush;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL stub_swap_00518b00(void*,
                                                                    void*) {
  ++g_fixture->trace.swap;
}

extern "C" OpaqueGraphicsProbe* PKG_SKINNER_SAFE_WAVE11_CDECL
stub_get_graphics_probe_0067dd00() {
  ++g_fixture->trace.get_probe;
  return &g_fixture->probe;
}

extern "C" OpaqueRenderTargetManager* PKG_SKINNER_SAFE_WAVE11_CDECL
stub_get_render_target_manager_0067dd60() {
  ++g_fixture->trace.get_manager;
  return &g_fixture->manager;
}

extern "C" OpaqueRefObject* PKG_SKINNER_SAFE_WAVE11_CDECL
stub_get_render_object_0067de30() {
  ++g_fixture->trace.get_render_object;
  return &g_fixture->render_object;
}

extern "C" float PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_get_scale_006a2710(OpaqueRefObject*, TargetWord) {
  ++g_fixture->trace.get_scale;
  return static_cast<float>(g_fixture->scale_value);
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_CDECL
stub_classify_004bb860(TargetWord) {
  ++g_fixture->trace.classify;
  return static_cast<TargetWord>(g_fixture->classify_value);
}

extern "C" bool PKG_SKINNER_SAFE_WAVE11_CDECL
stub_get_float_0040cf10(TargetWord object, TargetWord key, float* out) {
  ++g_fixture->trace.get_float;
  FloatsRecord& record = g_fixture->floats[g_fixture->float_count];
  record.object = object;
  record.key = key;
  ++g_fixture->float_count;
  if (object == 0u) {
    return false;
  }
  *out = g_fixture->tone_value;
  return true;
}

extern "C" bool PKG_SKINNER_SAFE_WAVE11_CDECL
stub_get_key_006a1250(TargetWord id, TargetWord key, OpaqueKeyBlock*) {
  ++g_fixture->trace.get_key;
  KeyRecord& record = g_fixture->key[g_fixture->key_count];
  record.id = id;
  record.key = key;
  ++g_fixture->key_count;
  return (g_fixture->key_mask & (1 << (key & 3u))) != 0;
}

extern "C" OpaqueRefObject* PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_get_raster_00525aa0(OpaquePaintSystem*) {
  ++g_fixture->trace.get_raster;
  return reinterpret_cast<OpaqueRefObject*>(&g_fixture->owner[0]);
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_truncate_004259e0(OpaqueVector*, OpaqueRefObject*, OpaqueRefObject*) {
  ++g_fixture->trace.truncate;
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_lazy_reset_0041d870(OpaqueRefObject** slot) {
  ++g_fixture->trace.lazy_reset;
  TargetWord old = *slot == nullptr ? 0u : 1u;
  *slot = nullptr;
  return old;
}
extern "C" OpaqueRefVTable* PKG_SKINNER_SAFE_WAVE11_CDECL
stub_resolve_ref_vtable(TargetWord) {
  return g_fixture->resolved_vtable;
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_ref_add_000(OpaqueRefObject* object) {
  return object->refcount_008 + 1u;
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_ref_release_004(OpaqueRefObject*) {
  ++g_fixture->trace.ref_release;
  return 0u;
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_ref_step_010(OpaqueRefObject*) {
  return 0u;
}

extern "C" OpaqueRefObject* PKG_SKINNER_SAFE_WAVE11_THISCALL stub_create_01c(
    OpaqueRenderTargetManager*, OpaqueKeyBlock block, TargetWord tag) {
  ++g_fixture->trace.manager_create_block;
  CreateRecord& record = g_fixture->create[g_fixture->create_count];
  record.tag = tag;
  record.block[0] = block.w0;
  record.block[1] = block.w1;
  record.block[2] = block.w2;
  ++g_fixture->create_count;
  return &g_fixture->target2;
}
extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_prepare_034(OpaqueRenderTargetManager*, OpaqueRefObject*) {
  ++g_fixture->trace.manager_prepare;
  return 0u;
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_query_044(OpaqueGraphicsProbe*) {
  ++g_fixture->trace.probe_query;
  return g_fixture->probe_answer ? 1u : 0u;
}

extern "C" TargetWord PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_dispatch_02c(OpaqueRefObject*, TargetWord, TargetWord, TargetWord) {
  ++g_fixture->trace.render_dispatch;
  return g_fixture->dispatch_answer ? 1u : 0u;
}

extern "C" void PKG_SKINNER_SAFE_WAVE11_THISCALL
stub_collect_job_0051ab50(OpaqueSkinJob* job, TargetWord argument) {
  const std::size_t index = g_fixture->trace.collect_job;
  ++g_fixture->trace.collect_job;
  if (index < 4u) {
    g_fixture->collect_job_receiver[index] = job;
    g_fixture->collect_job_argument[index] = argument;
  }
}

void install_ports() {
  SkinnerSafeWave11Ports ports{};
  ports.collect_job_0051ab50 = stub_collect_job_0051ab50;
  ports.get_paint_system_00401080 = stub_get_paint_system_00401080;
  ports.start_render_00528e90 = stub_start_render_00528e90;
  ports.set_color_write_00529280 = stub_set_color_write_00529280;
  ports.paint_region_005296b0 = stub_paint_region_005296b0;
  ports.end_render_00529bf0 = stub_end_render_00529bf0;
  ports.emit_005295b0 = stub_emit_005295b0;
  ports.set_vertex_limit_00529520 = stub_set_vertex_limit_00529520;
  ports.flush_00529690 = stub_flush_00529690;
  ports.swap_00518b00 = stub_swap_00518b00;
  ports.get_graphics_probe_0067dd00 = stub_get_graphics_probe_0067dd00;
  ports.get_render_target_manager_0067dd60 =
      stub_get_render_target_manager_0067dd60;
  ports.get_render_object_0067de30 = stub_get_render_object_0067de30;
  ports.get_scale_006a2710 = stub_get_scale_006a2710;
  ports.classify_004bb860 = stub_classify_004bb860;
  ports.get_float_0040cf10 = stub_get_float_0040cf10;
  ports.get_key_006a1250 = stub_get_key_006a1250;
  ports.get_raster_00525aa0 = stub_get_raster_00525aa0;
  ports.truncate_004259e0 = stub_truncate_004259e0;
  ports.lazy_reset_0041d870 = stub_lazy_reset_0041d870;
  ports.resolve_ref_vtable = stub_resolve_ref_vtable;
  g_skinner_safe_wave11_ports = ports;
}

void setup(Fixture& f, TargetSignedWord rig_count) {
  std::memset(&f, 0, sizeof(f));
  f.set_limit_value = 3u;
  f.tone_value = 1.0F;
  f.classify_value = 0;
  f.key_mask = 0xf;
  f.scale_value = 0;
  f.probe_answer = false;
  f.dispatch_answer = false;

  f.ref_vtable.add_000 = stub_ref_add_000;
  f.ref_vtable.release_004 = stub_ref_release_004;
  f.ref_vtable.step_010 = stub_ref_step_010;
  f.render_vtable.dispatch_02c = stub_dispatch_02c;
  f.resolved_vtable = &f.ref_vtable;
  f.probe_vtable.query_044 = stub_query_044;
  f.manager_vtable.create_01c = stub_create_01c;
  f.manager_vtable.prepare_034 = stub_prepare_034;

  f.tex[0].vtable_000 = &f.target;
  f.tex[1].vtable_000 = &f.target;
  f.tex[2].vtable_000 = &f.target;
  f.tex[0].field_058 = 4u;
  f.tex[0].field_05c = 8u;
  f.tex[2].field_058 = 16u;
  f.tex[2].field_05c = 32u;
  f.painter.textures_010[0] = &f.tex[0];
  f.painter.textures_010[1] = &f.tex[1];
  f.painter.textures_010[2] = &f.tex[2];
  f.painter.scale_02c = 2.0F;
  f.painter.scale_030 = 3.0F;

  f.owner[0] = 0x1000u;
  f.owner[1] = 0x1000u;
  f.owner[2] = 0x1000u;
  f.painter.field_040 = reinterpret_cast<TargetWord>(f.owner);
  f.painter.count_044 = 0;

  for (TargetSignedWord i = 0; i < 16; ++i) {
    f.rigblock[i].flags_008 = 0;
    f.mesh_slot[i].a = static_cast<float>(i);
    f.mesh_slot[i].b = static_cast<float>(i) + 0.5F;
    f.mesh_slot[i].c = static_cast<float>(i) + 1.0F;
    f.mesh_slot[i].d = static_cast<float>(i) + 1.5F;
    f.mesh_id[i] = reinterpret_cast<TargetWord>(&f.target);
  }
  f.block.field_008 = f.mesh_id;
  f.block.field_018 = 0x1234u;
  f.block.rigblocks_098 = f.rigblock;
  f.block.rigblocks_09c = f.rigblock + rig_count;
  f.mesh.field_008 = &f.block;
  f.mesh.ids_00c = f.mesh_id;
  f.mesh.slots_090 = f.mesh_slot;

  for (std::size_t i = 0; i < 32; ++i) {
    f.vertex[i] = 0x3f800000u;
  }
  for (std::size_t i = 0; i < 36; ++i) {
    f.part[i] = static_cast<TargetWord>(i % 3u);
  }
  for (std::size_t i = 0; i < 4; ++i) {
    f.index[i] = static_cast<TargetWord>(i);
  }
  f.batch.vertices_030 = f.vertex;
  f.batch.parts_begin_058 = f.part;
  f.batch.parts_end_05c = f.part + 36;
  f.batch.index_080 = f.index;
  for (std::size_t i = 0; i < 4; ++i) {
    f.batch_slot[i].field_058 = static_cast<float>(i * 4);
    f.batch_slot[i].field_05c = static_cast<float>(i * 4 + 1);
    f.batch_slot[i].field_060 = static_cast<float>(i * 4 + 2);
    f.batch_slot[i].field_064 = static_cast<float>(i * 4 + 3);
    f.batch_slot_ptr[i] = &f.batch_slot[i];
  }
  f.batch.slots_begin_0e4 = f.batch_slot_ptr;
  f.batch.slots_end_0e8 = f.batch_slot_ptr + 4;

  f.system.painter_00c = &f.painter;
  f.system.batch_010 = &f.batch;
  f.system.mesh_020 = &f.mesh;

  f.probe.vtable_000 = &f.probe_vtable;
  f.manager.vtable_000 = &f.manager_vtable;
  f.target.vtable_000 = &f.ref_vtable;
  f.target2.vtable_000 = &f.ref_vtable;
  f.target.field_018 = 0u;
  f.render_object.vtable_000 =
      reinterpret_cast<OpaqueRefVTable*>(&f.render_vtable);

  g_fixture = &f;
  install_ports();
  g_skinner_safe_wave11_scale_source = nullptr;
}

void test_slot_pass_setup_emits_six_quads() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  OpaqueSkinJobState job{};
  job.field_010 = 1;
  job.field_014 = 4;
  job.field_018 = 0;

  const TargetWord result = skin_paint_slot_pass_005183c0(&job);
  check(result == 0u, "slot pass setup returns zero");
  check(job.field_018 == 1, "slot pass setup advances cursor");
  check(f.emit_count == 42u, "slot pass setup emits the quad and vertices");
  check(f.trace.start_render == 1u, "slot pass setup starts one render");
  check(f.trace.end_render == 1u, "slot pass setup ends one render");
  check(f.tex[1].field_004 == kMaterialPassSetup,
        "slot pass setup writes material");
  check(f.emit[0].pos[0] == 0.0F && f.emit[0].pos[1] == 0.0F,
        "slot pass first vertex is origin");
  check(f.emit[1].pos[0] == 1.0F && f.emit[1].pos[1] == 0.0F,
        "slot pass second vertex is unit x");
  check(f.emit[2].pos[0] == 1.0F && f.emit[2].pos[1] == 1.0F,
        "slot pass third vertex is unit square");
  check(f.emit[3].pos[0] == 1.0F && f.emit[3].pos[1] == 1.0F,
        "slot pass fourth vertex repeats third");
  check(f.emit[4].pos[0] == 0.0F && f.emit[4].pos[1] == 1.0F,
        "slot pass fifth vertex is unit y");
  check(f.emit[5].pos[0] == 0.0F && f.emit[5].pos[1] == 0.0F,
        "slot pass sixth vertex repeats first");
  check(f.emit[0].colour == 0u, "slot pass emit tail is zero");
  check(f.emit[0].normal[0] == 0u && f.emit[0].normal[2] == 0u,
        "slot pass emit normal is zero");
  check(f.emit[0].uv[0] == 0.0F && f.emit[0].uv[1] == 0.0F,
        "slot pass emit shared uv is zero");
  check(f.trace.set_color == 2u, "slot pass setup writes colour twice");
}

void test_slot_pass_setup_emit_rig_blocks() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  f.set_limit_value = 4u;
  OpaqueSkinJobState job{};
  job.field_010 = 0;
  job.field_018 = 0;

  skin_paint_slot_pass_005183c0(&job);
  check(f.emit_count == 42u, "slot pass emits quad plus every rig vertex");
  check(f.trace.flush == 4u,
        "slot pass flushes after the quad and the batches");
  check(f.trace.set_limit == 4u, "slot pass clamps every batch");
  check(f.emit[6].colour == kColourOpaque, "rig vertex colour is opaque");
  check(f.emit[6].pos[0] == 1.0F, "rig vertex reads the data base as floats");
  check(f.emit[6].uv[0] == 1.0F,
        "rig vertex reuses the base for the second slot");
}

void test_slot_pass_probe_query_bounds_passes() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  OpaqueSkinJobState job{};
  job.field_018 = 1;
  job.field_014 = 100;

  skin_paint_slot_pass_005183c0(&job);
  check(f.paint_count == 2u, "probe false gives two passes");
  check(f.trace.swap == 2u, "probe false swaps twice");
  check(job.field_018 == 3, "probe false advances cursor by two");
  check(f.paint[0].painter == &f.tex[2], "loop pass paints texture two");
  check(f.paint[0].a0[0] == 0.0F && f.paint[0].a1[0] == 1.0F,
        "loop pass region is unit square");
  check(f.paint[0].a2 == 0xffffffffu, "loop pass region tail is minus one");

  setup(f, 0);
  job.field_018 = 1;
  job.field_014 = 100;
  f.probe_answer = true;
  skin_paint_slot_pass_005183c0(&job);
  check(f.paint_count == 8u, "probe true gives eight passes");
  check(job.field_018 == 9, "probe true advances cursor by eight");
}

void test_slot_pass_clamps_to_remaining() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  OpaqueSkinJobState job{};
  job.field_018 = 4;
  job.field_014 = 5;
  f.probe_answer = true;

  const TargetWord result = skin_paint_slot_pass_005183c0(&job);
  check(f.paint_count == 2u, "pass count clamps to remaining");
  check(job.field_018 == 6, "cursor advances by clamped count");
  check(result == 1u, "cursor beyond limit returns one");
}

void test_slot_pass_params_from_slot_extent() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  OpaqueSkinJobState job{};
  job.field_018 = 1;
  job.field_014 = 4;
  skin_paint_slot_pass_005183c0(&job);
  check(f.tex[2].count_044 == 1, "loop pass raises param count");
  check(f.tex[2].params_00c.a == 0.25F, "loop pass param r is inverse width");
  check(f.tex[2].params_00c.b == 0.125F, "loop pass param g is inverse height");
  check(f.tex[2].params_00c.c == 0.0F && f.tex[2].params_00c.d == 0.0F,
        "loop pass param ba is zero");
  check(f.tex[2].count_048 == 0, "loop pass leaves raster count when null");
  check(f.tex[2].field_004 == kMaterialPassLoop, "loop pass writes material");
}

void test_slot_pass_raster_binding() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  OpaqueSkinJobState job{};
  job.field_018 = 1;
  job.field_014 = 4;
  f.tex[0].field_060 = reinterpret_cast<OpaqueHandle*>(&f.owner[0]);
  skin_paint_slot_pass_005183c0(&job);
  check(f.tex[2].count_048 == 1, "loop pass raises raster count when set");
  check(f.tex[2].rasters_03c == f.tex[0].field_060,
        "loop pass copies the slot raster");
}

void test_slot_pass_selects_texture_by_index() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  OpaqueSkinJobState job{};
  job.field_010 = 2;
  job.field_018 = 0;
  skin_paint_slot_pass_005183c0(&job);
  check(f.tex[2].field_004 == kMaterialPassSetup,
        "setup honours the slot index");
  check(f.tex[0].field_004 == 0u, "setup leaves the other textures alone");
}

void test_tex0_full_region_uses_texture_one_raster() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  f.tex[1].field_060 = reinterpret_cast<OpaqueHandle*>(&f.owner[1]);

  const TargetWord result = skin_tex0_full_region_00518bf0(&f.tex[0]);
  check(result == 1u, "tex0 full region returns one");
  check(f.trace.start_render == 1u && f.trace.end_render == 1u,
        "tex0 full region brackets one render");
  check(f.paint_count == 1u, "tex0 full region paints once");
  check(f.paint[0].painter == &f.tex[0],
        "tex0 full region paints texture zero");
  check(f.tex[0].field_004 == kMaterialTex0Full, "tex0 full region material");
  check(f.tex[0].rasters_03c == f.tex[1].field_060,
        "tex0 full region borrows texture one raster");
  check(f.tex[0].count_048 == 1, "tex0 full region raises raster count");
  check(f.trace.set_color == 2u, "tex0 full region writes colour twice");
  check(f.trace.get_system == 2u, "tex0 full region samples system twice");
  check(f.paint[0].a0[0] == 0.0F && f.paint[0].a1[1] == 1.0F,
        "tex0 full region uses the unit square");
}

void test_tex0_full_region_null_raster() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  skin_tex0_full_region_00518bf0(&f.tex[0]);
  check(f.tex[0].count_048 == 0, "null raster leaves count alone");
  check(f.tex[0].rasters_03c == nullptr, "null raster still stores zero");
}

void test_tex2_uv_region_scale_fallback() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  skin_tex2_uv_region_00518cf0(&f.target);
  check(f.trace.get_scale == 1u, "tex2 uv region queries scale once");
  check(f.tex[2].params_00c.c == 5.0F / 3.0F,
        "tex2 uv region falls back to five thirds");
  check(f.tex[2].params_00c.a == 1.0F / 16.0F,
        "tex2 uv region inverts own width");
  check(f.tex[2].params_00c.b == 1.0F / 32.0F,
        "tex2 uv region inverts own height");
  check(f.tex[2].params_00c.d == 0.0F, "tex2 uv region param alpha is zero");
  check(f.tex[2].field_004 == kMaterialTex2Uv, "tex2 uv region material");
  check(f.paint_count == 1u, "tex2 uv region paints once");
  check(f.trace.get_system == 1u, "tex2 uv region samples system once");
}

void test_tex2_uv_region_preserves_nonzero_scale() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  f.scale_value = 9;
  skin_tex2_uv_region_00518cf0(&f.target);
  check(f.tex[2].params_00c.c == 3.0F, "tex2 uv region keeps nonzero scale");
}

void test_tex2_uv_region_raster_source() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  f.tex[1].field_060 = reinterpret_cast<OpaqueHandle*>(&f.owner[2]);
  skin_tex2_uv_region_00518cf0(&f.target);
  check(f.tex[2].rasters_03c == f.tex[1].field_060,
        "tex2 uv region borrows texture one raster");
  check(f.tex[2].count_048 == 1, "tex2 uv region raises raster count");
}

void test_rig_block_draw_two_passes() {
  ++g_tests;
  Fixture f;
  setup(f, 3);
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.trace.start_render == 2u && f.trace.end_render == 2u,
        "rig block draw brackets two renders");
  check(f.paint_count == 8u, "rig block draw paints rig plus drain slots");
  check(f.paint[0].painter == &f.tex[0], "rig block draw first pass texture");
  check(f.paint[4].painter == &f.tex[1], "rig block draw second pass texture");
  check(f.paint[0].a0[0] == 0.0F && f.paint[0].a0[1] == 2.0F,
        "rig block draw passes x extent");
  check(f.paint[0].a1[0] == 1.0F && f.paint[0].a1[1] == 3.0F,
        "rig block draw passes y extent");
  check(f.paint[0].a2 == 0xffffffffu, "rig block draw saturates the tone");
  check(f.paint[3].a2 == 0xffffffffu, "rig block drain uses minus one");
  check(f.tex[0].field_004 == kMaterialRigBlock, "rig block draw material");
  check(f.tex[0].params_00c.a == 1.0F && f.tex[0].params_00c.b == 0.0F,
        "rig block draw default tune pair");
  check(f.trace.set_color == 4u, "rig block draw writes colour twice a pass");
}

void test_rig_block_draw_packs_tone() {
  ++g_tests;
  Fixture f;
  setup(f, 1);
  f.dispatch_answer = true;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.float_count == 4u, "rig block draw reads two tunes and two tones");
  check(f.floats[0].key == kKeyTuneA, "rig block draw first tune key");
  check(f.floats[0].object == 0u, "rig block draw tune passes the reset slot");
  check(f.floats[1].key == kKeyTuneB, "rig block draw second tune key");
  check(f.floats[2].key == kKeyTone, "rig block draw tone key");
  check(f.floats[2].object != 0u, "rig block draw tone passes the rig id");
  check(f.floats[3].key == kKeyTone, "rig block draw reads a tone per pass");
  check(f.tex[0].params_00c.a == 1.0F,
        "a null tune object leaves the tune pair at its seed");
}

void test_rig_block_draw_skips_flagged_rig_blocks() {
  ++g_tests;
  Fixture f;
  setup(f, 3);
  f.rigblock[1].flags_008 = 1u;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.float_count == 4u, "rig block draw skips flagged rig blocks");
  check(f.paint_count == 8u, "rig block draw drain absorbs the skip");
}

void test_rig_block_draw_colour_dispatch() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  f.classify_value = static_cast<TargetSignedWord>(kClassifyKey);
  f.dispatch_answer = true;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.trace.render_dispatch == 1u, "rig block draw dispatches once");
  check(f.float_count == 2u, "rig block draw tunes only when dispatched");

  setup(f, 0);
  f.dispatch_answer = false;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.float_count == 0u, "rig block draw skips tuning when not dispatched");
}

void test_rig_block_draw_tone_packing() {
  ++g_tests;
  Fixture f;
  setup(f, 1);
  f.tone_value = 0.0F;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.paint[0].a2 == 0u, "rig block draw packs a zero tone");

  setup(f, 1);
  f.tone_value = 0.5F;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.paint[0].a2 == 0x80808080u,
        "rig block draw rounds a half tone up to the even byte");

  setup(f, 1);
  f.tone_value = 0.9F;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.paint[0].a2 == 0xe6e6e6e6u,
        "rig block draw rounds 229.5 up instead of truncating to 229");

  setup(f, 1);
  f.tone_value = -1.0F;
  skin_rig_block_draw_00518f10(&f.tex[0]);
  check(f.paint[0].a2 == 0u, "rig block draw clamps a negative tone");
}
void test_rig_index_pass_walks_rig_blocks() {
  ++g_tests;
  Fixture f;
  setup(f, 3);
  OpaqueSkinJobState job{};
  const TargetWord result = skin_rig_index_pass_0051a350(&job);
  check(result == 1u, "rig index pass returns one when drained");
  check(job.field_010 == 3, "rig index pass consumes the whole array");
  check(f.paint_count == 3u, "rig index pass paints every rig block");
  check(f.trace.start_render == 1u && f.trace.end_render == 1u,
        "rig index pass brackets one render");
  check(f.tex[0].field_004 == kMaterialOverlay, "rig index pass material");
  check(f.tex[0].rasters_040 == nullptr, "rig index pass clears second raster");
  check(f.tex[0].count_044 == 1, "rig index pass raises the param count");
  check(f.paint[1].a0[0] == 1.0F && f.paint[1].a1[0] == 2.0F,
        "rig index pass follows the mesh cursor");
}

void test_rig_index_pass_flag_and_key_gates() {
  ++g_tests;
  Fixture f;
  setup(f, 3);
  f.rigblock[1].flags_008 = 1u;
  OpaqueSkinJobState job{};
  skin_rig_index_pass_0051a350(&job);
  check(f.paint_count == 2u, "rig index pass skips flagged rig blocks");
  check(job.field_010 == 3, "rig index pass still drains the array");

  setup(f, 2);
  f.key_mask = 0;
  OpaqueSkinJobState fresh_index{};
  skin_rig_index_pass_0051a350(&fresh_index);
  check(f.paint_count == 0u, "rig index pass skips when the key is absent");
  check(fresh_index.field_010 == 2, "rig index pass still advances the cursor");
}

void test_rig_index_pass_pass_limit() {
  ++g_tests;
  Fixture f;
  setup(f, 12);
  OpaqueSkinJobState job{};
  skin_rig_index_pass_0051a350(&job);
  check(f.paint_count == 10u, "rig index pass honours the ten pass limit");
  check(job.field_010 == 10, "rig index pass stops at the limit");
  check(job.field_010 < 12, "rig index pass leaves work for the next call");
}

void test_rig_index_pass_null_create() {
  ++g_tests;
  Fixture f;
  setup(f, 1);
  OpaqueSkinJobState job{};
  skin_rig_index_pass_0051a350(&job);
  check(f.trace.manager_create_block == 1u, "rig index pass still creates");
  check(f.paint_count == 1u, "rig index pass paints the resolved slot");
}

void test_job_setup_stores_arguments() {
  ++g_tests;
  Fixture f;
  setup(f, 0);
  OpaqueSkinJob job{};
  job.array_008 = f.owner;
  job.array_00c = f.owner + 4;
  job.cursor_340 = 7u;
  job.calls_344 = 9u;
  f.system.byte_07e = 0x5au;

  skin_job_setup_0051a9a0(&job, 0x1111u, 0x22u, 0x33u, 0x4444u, 0x5555u,
                          0x6666u, 0x7777u, 0x88u, 0x99u, 0xaau);

  check(job.field_338 == 0x1111u, "job setup stores the owner word");
  check(job.flag_348 == 0x22u, "job setup stores flag 348");
  check(job.flag_349 == 0x33u, "job setup stores flag 349");
  check(job.flag_34a == 0x5au, "job setup copies the system flag");
  check(job.field_320 == 0x4444u, "job setup stores 320");
  check(job.field_324 == 0x5555u, "job setup stores 324");
  check(job.field_328 == 0x6666u, "job setup stores 328");
  check(job.field_32c == 0x7777u, "job setup stores 32c");
  check(job.flag_34b == 0x88u, "job setup stores 34b");
  check(job.flag_34c == 0x99u, "job setup stores 34c");
  check(job.flag_34d == 0xaau, "job setup stores 34d");
  check(job.flag_34e == 0u, "job setup clears 34e");
  check(job.cursor_340 == 0u, "job setup clears the cursor");
  check(job.calls_344 == 0u, "job setup clears the call counter");
  check(f.trace.truncate == 1u, "job setup truncates once");
  check(f.trace.collect_job == 1u, "job setup reaches the collector once");
  check(f.collect_job_receiver[0] == &job,
        "job setup hands the job receiver to the collector port");
  check(f.collect_job_argument[0] == 0x22u,
        "job setup forwards the widened low byte of stack word one");
  check(job.state_33c == 0u, "job setup leaves the state alone");

  OpaqueSkinJob wide{};
  wide.array_008 = f.owner;
  wide.array_00c = f.owner + 4;
  f.system.byte_07e = 0x5au;
  skin_job_setup_0051a9a0(&wide, 0x1111u, 0x22u, 0x33u, 0x4444u, 0x5555u,
                          0x6666u, 0x7777u, 0x88u, 0x99u, 0xaau);
  check(f.trace.collect_job == 2u,
        "two job setups reach the collector port exactly twice");
  check(f.collect_job_receiver[1] == &wide,
        "the collector port receives the second job receiver");
  check(f.collect_job_argument[1] == 0x22u,
        "the collector argument is the widened low byte, not the whole word");
  check(wide.state_33c == 0u, "the second job setup leaves the state alone");
}
void test_port_table_shape() {
  ++g_tests;
  install_ports();
  check(sizeof(SkinnerSafeWave11Ports) > 0u, "port table is populated");
  check(g_skinner_safe_wave11_ports.get_paint_system_00401080 != nullptr,
        "port table retains the system accessor");
  check(g_skinner_safe_wave11_ports.collect_job_0051ab50 != nullptr,
        "port table retains the opaque collector port");
  check(g_skinner_safe_wave11_ports.resolve_ref_vtable != nullptr,
        "port table retains the reference vtable resolver");
  check(g_skinner_safe_wave11_ports.paint_region_005296b0 != nullptr,
        "port table retains the paint region port");
}

void test_layout_contract() {
  ++g_tests;
  check(sizeof(OpaqueTexturePainter) == 0x68u, "texture painter size");
  check(offsetof(OpaqueTexturePainter, count_044) == 0x44u,
        "texture painter param count offset");
  check(offsetof(OpaqueTexturePainter, rasters_03c) == 0x3cu,
        "texture painter raster offset");
  check(offsetof(OpaqueTexturePainter, field_060) == 0x60u,
        "texture painter source raster offset");
  check(offsetof(OpaqueSkinPainter, textures_010) == 0x10u,
        "skin painter texture base offset");
  check(offsetof(OpaqueSkinPainter, scale_02c) == 0x2cu,
        "skin painter scale offset");
  check(offsetof(OpaqueSkinPainter, field_040) == 0x40u,
        "skin painter slot owner offset");
  check(offsetof(OpaqueRigblock, flags_008) == 0x08u, "rigblock flag offset");
  check(sizeof(OpaqueRigblock) == 0x8cu, "rigblock stride");
  check(offsetof(OpaquePaintSystem, byte_07c) == 0x7cu,
        "paint system flag offset");
  check(offsetof(OpaqueSkinJob, state_33c) == 0x33cu, "skin job state offset");
  check(offsetof(OpaqueSkinJob, handle_330) == 0x330u,
        "skin job handle offset");
  check(offsetof(OpaqueRenderTargetManagerVTable, prepare_034) == 0x34u,
        "render target prepare slot offset");
  check(offsetof(OpaqueGraphicsProbeVTable, query_044) == 0x44u,
        "graphics probe query slot offset");
}

}  // namespace

int run_skinner_safe_wave11_tests() {
  test_port_table_shape();
  test_layout_contract();
  test_slot_pass_setup_emits_six_quads();
  test_slot_pass_setup_emit_rig_blocks();
  test_slot_pass_probe_query_bounds_passes();
  test_slot_pass_clamps_to_remaining();
  test_slot_pass_params_from_slot_extent();
  test_slot_pass_raster_binding();
  test_slot_pass_selects_texture_by_index();
  test_tex0_full_region_uses_texture_one_raster();
  test_tex0_full_region_null_raster();
  test_tex2_uv_region_scale_fallback();
  test_tex2_uv_region_preserves_nonzero_scale();
  test_tex2_uv_region_raster_source();
  test_rig_block_draw_two_passes();
  test_rig_block_draw_packs_tone();
  test_rig_block_draw_skips_flagged_rig_blocks();
  test_rig_block_draw_colour_dispatch();
  test_rig_block_draw_tone_packing();
  test_rig_index_pass_walks_rig_blocks();
  test_rig_index_pass_flag_and_key_gates();
  test_rig_index_pass_pass_limit();
  test_rig_index_pass_null_create();
  test_job_setup_stores_arguments();
  std::printf("tests %d checks %d failures %d\n", g_tests, g_checks,
              g_failures);
  return g_failures == 0 ? 0 : 1;
}

}  // namespace openspore::reconstruction::pkg_skinner_safe_wave11

int main() {
  return openspore::reconstruction::pkg_skinner_safe_wave11::
      run_skinner_safe_wave11_tests();
}
