#!/usr/bin/env python3
"""Objective 10 sprint seed: engineering-loop coverage for knowledgegraph/spore.db.

Rebuild:  python3 knowledgegraph/kg.py init && python3 knowledgegraph/seed_sprint.py init
Re-run:   python3 knowledgegraph/seed_sprint.py init   (idempotent, same counts)

STATUS -> EVIDENCE MAPPING (1:1, docs/replacement-status.json vocabulary onto the
graph's evidence levels UNKNOWN/HYPOTHESIS/INFERRED/SUPPORTED/VERIFIED):
  unknown           -> UNKNOWN    (nothing measured; e.g. audio-havok-input)
  hypothesis        -> HYPOTHESIS (named path, no trace; e.g. utfwin dispatch order)
  inferred          -> INFERRED   (SDK/RECON structure, no runtime proof)
  supported         -> SUPPORTED  (traced or byte-framed, not yet asserted in-tree)
  verified          -> VERIFIED   (asserted against real bytes AND green in-tree)
  replaced-stub     -> SUPPORTED  (code exists + in-tree substitutability shown,
                                   gate test NOT yet passed; gate linked via gatedBy)
  replaced-verified -> VERIFIED   (gate tests green on real bytes; gate linked via
                                   verifiedBy to the Test nodes that verify it)
Only measured bytes, passing tests, and planted-breakpoint traces count as
evidence. Decompiler-guessing never promotes above INFERRED. AI inference is
never VERIFIED.

NEW NODE KINDS (one paragraph): the pre-existing schema (node/edge/test_result,
UNIQUE(label,name) / UNIQUE(src,dst,rel)) is unchanged -- no migration needed.
This seed only uses new *values* of label/rel: Observation (one planted-probe
trace summary per probe: fired=measured counts, unfired=explicit 0-event
misses, plus one never-run trace definition), AssetRecord (the single chosen
real asset by (type,group,instance) identity with measured decode facts),
Implementation (OpenSpore source files that exist in-tree), Subsystem (the 14
docs/replacement-status.json entries with mapped evidence), Test (the 4 ctest
names; outcomes live in test_result), Analysis (one static-analysis PASS
summary, never per-candidate rows). New rel values: observes, missed,
storedIn, decodesWith, walksAs, readBy, parsedBy, renderedBy, verifies,
testedBy, implementedBy, boundedBy, verifiedBy, gatedBy, observedVia.
"""
import json
import os
import sqlite3
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DB = os.path.join(HERE, "spore.db")
SCHEMA = os.path.join(HERE, "schema.sql")

CONF = {"UNKNOWN": 0.0, "HYPOTHESIS": 0.25, "INFERRED": 0.5,
        "SUPPORTED": 0.75, "VERIFIED": 1.0}

STATUS2EV = {"unknown": "UNKNOWN", "hypothesis": "HYPOTHESIS",
             "inferred": "INFERRED", "supported": "SUPPORTED",
             "verified": "VERIFIED", "replaced-stub": "SUPPORTED",
             "replaced-verified": "VERIFIED"}

# Pre-existing RenderWare-research entries (added manually 2026-09-20, before this
# seed existed). Embedded verbatim so a fresh checkout rebuilds the FULL graph;
# inserted with DO NOTHING so manual curation is never clobbered by re-seeding.
LEGACY_NODES = [
    ("Structure", "RW4Container", 0.0, "manual",
     {"magic": "\\x89RW4w32\\0\\r\\n\\x1a\\x0a +16B",
      "header": "28B magic, type@0x1C (1=MODEL,0x04000000=TEXTURE,0xCAFED00D=SPECIAL), objCount@0x20, secCount@0x24, pSectionInfo@0x30, pBufferData@0x44, buffersSize@0x4C, manifest@0x98",
      "sectionInfo": "6xu32: pData(rel-to-buffer-for-BaseResource), f4, size, align, typeCodeIndex, typeCode (24B)"},
     "Validated on rw4_7/11/12.bin from Spore_Graphics; type codes 0x10030/0x20003-0x200af/0x70001-3/0x80003/5/0xff0000-2; 0x2000b+0x7000b undocumented"),
    ("Structure", "GameModelResource", 0.0, "manual",
     {"ext": "gmdl 0x00E6BCE5",
      "layout": "version(<=9), refFiles[{inst,group,type}], meshCount, bbox 7f, radius, indexBuffers[prim,count,bits,size], vertexDescriptors, vertexBuffers, meshes, materialInfos, boneRanges, animDatas[GameModelAnimData]"},
     "Validated on gmdl_148/156 from Spore_Content group 0x40666203; gmdl_156 = v8 heightfield patch, 153 u16 idx grid"),
    ("Structure", "DBPFv3", 0.0, "manual",
     {"header": "96B: major=3,minor=0,idxMinor=3",
      "index": "no name table; 32-bit FNV-1a binary IDs; records {instance,group,type,offset,size}",
      "payload": "often QFS-compressed"}, None),
    ("Structure", "QFSCompression", 0.0, "manual",
     {"header": "5B: 0x10FB/0x50FB + 3B BE size",
      "note": "LZ-style control-byte data, not zlib; implemented in tools dbpf.py qfs_decompress"}, None),
    ("Structure", "MaterialShader", 0.0, "sdk",
     {"storage": "global linked list, next@+0x40, id@+0",
      "api": "Graphics::MaterialShader::GetMaterialShader(shaderID) 0x011fa030 caches hit"}, None),
    ("Structure", "CompiledState", 0.0, "sdk",
     {"api": "Load/SetRaster/GetRaster 0x011ee700-8c0",
      "groups": "CompiledStates 0x40212001, ShaderFragments 0x40212002, Shaders 0x40212004"}, None),
    ("Function", "RenderWare_Mesh_SetIndexBuffer_Draw", 0.0, "static",
     {"addr": "0x011f9710",
      "semantics": "active-shader vertex decl -> per-stream SetStreamSource(rebind-on-change, unbind surplus) + SetIndices scope check + DrawIndexedPrimitive"}, None),
    ("Function", "RenderUtils_CreateDevice", 0.0, "static",
     {"addr": "0x011f8680",
      "calls": "IDirect3D9::CheckAdapterFormat(+0x38), CreateDevice(+0x40), color RTT + depth RTT (FUN_011efeb0 types 1/2), SetRenderTarget(+0xa0), 8-fn init chain, state=2, QPC stamp"}, None),
    ("Structure", "TerrainSphereQuad", 0.0, "sdk",
     {"passes": "RenderLand 0x00fb66a0, RenderSeabedAsLand, RenderWater, RenderAtmosphere, RenderDecals",
      "world": "sphere subdivided into quads; LOD via cModelWorld::UpdateWithLODMeshes"}, None),
    ("Renderer", "SporeGraphicsDevice", 0.0, "static",
     {"kind": "wrapper around IDirect3D9 (NOT raw ID3D9 layout)",
      "slots": "+0x144 SetIndices-ish, +0x1a0 IsIndicesInScope-ish, +0x190 SetStreamSource",
      "d3dx": "d3dx9_27.dll imported but ZERO call sites (4.6M instr scan) - shaders precompiled"}, None),
]
LEGACY_EDGES = [
    ("DBPFv3", "compressesWith", "QFSCompression"),
    ("DBPFv3", "contains", "RW4Container"),
    ("DBPFv3", "contains", "GameModelResource"),
    ("RW4Container", "references", "CompiledState"),
    ("MaterialShader", "binds", "CompiledState"),
    ("RenderWare_Mesh_SetIndexBuffer_Draw", "uses", "SporeGraphicsDevice"),
    ("RenderWare_Mesh_SetIndexBuffer_Draw", "reads", "MaterialShader"),
    ("RenderUtils_CreateDevice", "creates", "SporeGraphicsDevice"),
    ("TerrainSphereQuad", "dispatches", "RenderWare_Mesh_SetIndexBuffer_Draw"),
]
LEGACY_TESTS = [
    ("rw4_parser_validation", "assets", "n/a",
     "rw4_7/11/12 header+manifest+sections parse",
     "parsed OK: TEXTURE 128x128 DXT5 8mips; MODEL 20 sections all type codes matched", 1),
    ("gmdl_parser_validation", "assets", "n/a",
     "gmdl_148/156 top-level fields parse",
     "v8, 1 mesh, 153 u16 idx grid, bbox+radius sane", 1),
    ("d3dx_usage_scan", "binary", "n/a",
     "D3DX call sites present?", "0 of 4.6M instructions - dead import", 1),
]

# (label, name, evidence, origin, attrs, note)
NODES = [
    # --- main_menu runtime functions: fired probes (planted-breakpoint trace = evidence)
    ("Function", "entry", "VERIFIED", "dynamic",
     {"rva": "0x11e11a0", "events": 1, "trace": "main_menu",
      "src": "tools/observatory/examples/obs_main_menu_example.jsonl"},
     "PE AddressOfEntryPoint; fired x1 in traced run"),
    ("Function", "App::cAppSystem::InitPlugins", "VERIFIED", "dynamic",
     {"rva": "0x7e93d0", "events": 1, "trace": "main_menu"}, "SDK slot; fired x1"),
    ("Function", "App::cAppSystem::Init", "VERIFIED", "dynamic",
     {"rva": "0x7e8ba0", "events": 1, "trace": "main_menu"},
     "cAppSystem vtable slot 0; fired x1"),
    ("Function", "App::cAppSystem::Startup", "VERIFIED", "dynamic",
     {"rva": "0x7e67a0", "events": 1, "trace": "main_menu"},
     "cAppSystem vtable slot 1; fired x1"),
    ("Function", "App::IAppSystem::Get", "VERIFIED", "dynamic",
     {"rva": "0x67dcc0", "events": 1000, "trace": "main_menu",
      "note": "tracer per-function cap 1000; committed example excerpt shows 146"},
     "Singleton getter; capped at 1000 events"),
    # --- main_menu probes that never fired: recorded, NOT observed
    ("Function", "App::Bootstrap::local_main", "UNKNOWN", "dynamic",
     {"rva": "0xde13d0", "events": 0, "trace": "main_menu",
      "src": "tools/observatory/probes/main_menu.json"},
     "Probe defined + RVA byte-verified, 0 events in trace"),
    ("Function", "App::Bootstrap::stateMachine", "UNKNOWN", "dynamic",
     {"rva": "0xe20860", "events": 0, "trace": "main_menu",
      "src": "tools/observatory/probes/main_menu.json"},
     "Probe defined + RVA byte-verified, 0 events in trace"),
    # --- menu_transition probes: defined, never run under tracer
    ("Function", "UI::cEditor::HandleMessage", "UNKNOWN", "manual",
     {"rva": "0x591fa0", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    ("Function", "UI::cEditor::OnMouseDown", "UNKNOWN", "manual",
     {"rva": "0x588570", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    ("Function", "UI::cEditor::Update", "UNKNOWN", "manual",
     {"rva": "0x58be50", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    ("Function", "UI::MessagePump::PeekDispatch", "UNKNOWN", "manual",
     {"rva": "0x848210", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    ("Function", "Res::cResourceManager::Initialize", "UNKNOWN", "manual",
     {"rva": "0x8de530", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    ("Function", "Res::DatabasePackedFile::Lock", "UNKNOWN", "manual",
     {"rva": "0x8d84f0", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    ("Function", "Res::PFIndexModifiable::Read", "UNKNOWN", "manual",
     {"rva": "0x8dbcc0", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    ("Function", "Frame::TimeAtStartOfFrame", "UNKNOWN", "manual",
     {"rva": "0xb63980", "events": 0, "trace": "menu_transition"}, "Probe defined, never traced"),
    # --- observation nodes (one per probe + one never-run trace definition)
    ("Observation", "obs:main_menu:entry", "VERIFIED", "dynamic",
     {"trace": "main_menu", "probe": "entry", "events": 1,
      "src": "tools/observatory/examples/obs_main_menu_example.jsonl"}, None),
    ("Observation", "obs:main_menu:InitPlugins", "VERIFIED", "dynamic",
     {"trace": "main_menu", "probe": "App::cAppSystem::InitPlugins", "events": 1,
      "src": "tools/observatory/examples/obs_main_menu_example.jsonl"}, None),
    ("Observation", "obs:main_menu:Init", "VERIFIED", "dynamic",
     {"trace": "main_menu", "probe": "App::cAppSystem::Init", "events": 1,
      "src": "tools/observatory/examples/obs_main_menu_example.jsonl"}, None),
    ("Observation", "obs:main_menu:Startup", "VERIFIED", "dynamic",
     {"trace": "main_menu", "probe": "App::cAppSystem::Startup", "events": 1,
      "src": "tools/observatory/examples/obs_main_menu_example.jsonl"}, None),
    ("Observation", "obs:main_menu:IAppSystem_Get", "VERIFIED", "dynamic",
     {"trace": "main_menu", "probe": "App::IAppSystem::Get", "events": 1000,
      "src": "tools/observatory/examples/obs_main_menu_example.jsonl"}, "Per-function cap; 1004 events total per SCENARIO-main_menu.md"),
    ("Observation", "obs:main_menu:local_main", "UNKNOWN", "dynamic",
     {"trace": "main_menu", "probe": "App::Bootstrap::local_main", "events": 0,
      "src": "tools/observatory/probes/main_menu.json"}, "Defined probe, 0 events -- not observed"),
    ("Observation", "obs:main_menu:stateMachine", "UNKNOWN", "dynamic",
     {"trace": "main_menu", "probe": "App::Bootstrap::stateMachine", "events": 0,
      "src": "tools/observatory/probes/main_menu.json"}, "Defined probe, 0 events -- not observed"),
    ("Observation", "obs:menu_transition", "UNKNOWN", "manual",
     {"trace": "menu_transition", "probes": 8, "events": 0,
      "src": "tools/observatory/probes/menu_transition.json"},
     "8 probes defined, never run under tracer (wine lineage blocker)"),
    # --- chosen real asset record (measured facts from docs/ASSET-PATH.md)
    ("AssetRecord", "asset:gmdl:00E6BCE5:40637E03:067A07F0", "VERIFIED", "dynamic",
     {"package": "SPORE/Data/Spore_Content.package", "record_index": 16594,
      "type": "0x00E6BCE5", "group": "0x40637E03", "instance": "0x067A07F0",
      "stored": 794, "memSize": 1156, "qfs": True, "gmdl_version": 8,
      "meshCount": 1, "verts": 32, "stride": 24, "indices": 60, "tris": 20,
      "primType": 4, "material": "0x407DFDDB",
      "src": "docs/ASSET-PATH.md"}, "Smallest geometry-bearing gmdl in Spore_Content"),
    # --- OpenSpore implementations (files exist in-tree)
    ("Implementation", "impl:src/assets/Dbpf.cpp", "VERIFIED", "static",
     {"path": "src/assets/Dbpf.cpp", "role": "dbpf-index + qfs-decompress"}, None),
    ("Implementation", "impl:src/assets/Gmdl.cpp", "VERIFIED", "static",
     {"path": "src/assets/Gmdl.cpp", "role": "gmdl-walk-v8-static"}, None),
    ("Implementation", "impl:src/assets/Mesh.cpp", "VERIFIED", "static",
     {"path": "src/assets/Mesh.cpp", "role": "mesh-extract-bounds"}, None),
    ("Implementation", "impl:src/renderer/VulkanRenderer.cpp", "VERIFIED", "static",
     {"path": "src/renderer/VulkanRenderer.cpp", "role": "renderer-offscreen-submit (stub scope)"}, None),
    ("Implementation", "impl:src/compat/ResourceProvider.hpp", "VERIFIED", "static",
     {"path": "src/compat/ResourceProvider.hpp", "role": "boundary B1 IResourceProvider"}, None),
    ("Implementation", "impl:src/compat/MeshSource.hpp", "VERIFIED", "static",
     {"path": "src/compat/MeshSource.hpp", "role": "boundary B2 IMeshSource + B3 seam submitMeshSource"}, None),
    ("Implementation", "impl:src/renderer/Renderer.hpp", "VERIFIED", "static",
     {"path": "src/renderer/Renderer.hpp", "role": "boundary B3 IRenderer (referenced, not duplicated)"}, None),
    # --- tests (ctest names; outcomes in test_result, green 2026-09-21)
    ("Test", "test:assets_synthetic", "VERIFIED", "static",
     {"ctest": "assets_synthetic", "scope": "synthetic 2-row DBPF + ABCD-QFS + triangle-gmdl fixtures"}, None),
    ("Test", "test:assets_real", "VERIFIED", "static",
     {"ctest": "assets_real", "scope": "real chosen gmdl record, skips if SPORE/ absent"}, None),
    ("Test", "test:triangle_smoke", "VERIFIED", "static",
     {"ctest": "triangle_smoke", "scope": "offscreen triangle pixels, bit-identical"}, None),
    ("Test", "test:asset_render", "VERIFIED", "static",
     {"ctest": "asset_render", "scope": "real gmdl through Vulkan, 27685 drawn px"}, None),
    # --- vtable pass summary (candidate-level import explicitly out of scope)
    ("Analysis", "analysis:vtable_pass", "SUPPORTED", "static",
     {"pass": "vtable scan .rdata/.data", "candidates": 3081, "high": 369,
      "medium": 871, "low": 1841, "labeled": 20,
      "path": "docs/analysis/vtables.json",
      "note": "20 labeled incl. UTFWin/Editors/Sporepedia/Resource namespaces; per-candidate import out of scope"},
     "Vtable detection never ran headless before; class hierarchy still via SDK + vtables"),
]

# 14 subsystems imported from docs/replacement-status.json (status->evidence via STATUS2EV)
SUBSYSTEMS = [
    ("sub:dbpf-index", "replaced-verified", "B1 src/compat/ResourceProvider.hpp",
     "src/assets/Dbpf.cpp:parseDbpfIndex"),
    ("sub:qfs-decompress", "replaced-verified", "B1 src/compat/ResourceProvider.hpp",
     "src/assets/Dbpf.cpp:qfsDecompress"),
    ("sub:gmdl-walk-v8-static", "replaced-verified", "B2 src/compat/MeshSource.hpp",
     "src/assets/Gmdl.cpp:parseGmdl"),
    ("sub:mesh-extract-bounds", "replaced-verified", "B2 src/compat/MeshSource.hpp",
     "src/assets/Mesh.cpp:meshFromGmdl"),
    ("sub:renderer-offscreen-submit", "replaced-stub",
     "B3 src/renderer/Renderer.hpp via submitMeshSource", "src/renderer/VulkanRenderer.cpp"),
    ("sub:resource-manager-full", "inferred", None, None),
    ("sub:bootstrap-appsystem-lifecycle", "supported", None, None),
    ("sub:utfwin-message-dispatch", "hypothesis", None, None),
    ("sub:material-shader-texture", "inferred", None, None),
    ("sub:rw4-container-animation", "supported", None, None),
    ("sub:simulator-gameplay", "hypothesis", None, None),
    ("sub:property-serialization", "inferred", None, None),
    ("sub:audio-havok-input", "unknown", None, None),
    ("sub:pollinator-online", "unknown", None, None),
]

# (src_name, rel, dst_name)
EDGES = [
    # observations -> functions
    ("obs:main_menu:entry", "observes", "entry"),
    ("obs:main_menu:InitPlugins", "observes", "App::cAppSystem::InitPlugins"),
    ("obs:main_menu:Init", "observes", "App::cAppSystem::Init"),
    ("obs:main_menu:Startup", "observes", "App::cAppSystem::Startup"),
    ("obs:main_menu:IAppSystem_Get", "observes", "App::IAppSystem::Get"),
    ("obs:main_menu:local_main", "missed", "App::Bootstrap::local_main"),
    ("obs:main_menu:stateMachine", "missed", "App::Bootstrap::stateMachine"),
    ("obs:menu_transition", "missed", "UI::cEditor::HandleMessage"),
    ("obs:menu_transition", "missed", "UI::cEditor::OnMouseDown"),
    ("obs:menu_transition", "missed", "UI::cEditor::Update"),
    ("obs:menu_transition", "missed", "UI::MessagePump::PeekDispatch"),
    ("obs:menu_transition", "missed", "Res::cResourceManager::Initialize"),
    ("obs:menu_transition", "missed", "Res::DatabasePackedFile::Lock"),
    ("obs:menu_transition", "missed", "Res::PFIndexModifiable::Read"),
    ("obs:menu_transition", "missed", "Frame::TimeAtStartOfFrame"),
    # asset path: record -> formats (pre-existing Structure nodes) + impls
    ("asset:gmdl:00E6BCE5:40637E03:067A07F0", "storedIn", "DBPFv3"),
    ("asset:gmdl:00E6BCE5:40637E03:067A07F0", "decodesWith", "QFSCompression"),
    ("asset:gmdl:00E6BCE5:40637E03:067A07F0", "walksAs", "GameModelResource"),
    ("asset:gmdl:00E6BCE5:40637E03:067A07F0", "readBy", "impl:src/assets/Dbpf.cpp"),
    ("asset:gmdl:00E6BCE5:40637E03:067A07F0", "parsedBy", "impl:src/assets/Gmdl.cpp"),
    ("asset:gmdl:00E6BCE5:40637E03:067A07F0", "parsedBy", "impl:src/assets/Mesh.cpp"),
    ("asset:gmdl:00E6BCE5:40637E03:067A07F0", "renderedBy", "impl:src/renderer/VulkanRenderer.cpp"),
    # implementations -> tests
    ("impl:src/assets/Dbpf.cpp", "testedBy", "test:assets_synthetic"),
    ("impl:src/assets/Dbpf.cpp", "testedBy", "test:assets_real"),
    ("impl:src/assets/Gmdl.cpp", "testedBy", "test:assets_synthetic"),
    ("impl:src/assets/Gmdl.cpp", "testedBy", "test:assets_real"),
    ("impl:src/assets/Mesh.cpp", "testedBy", "test:assets_synthetic"),
    ("impl:src/assets/Mesh.cpp", "testedBy", "test:assets_real"),
    ("impl:src/renderer/VulkanRenderer.cpp", "testedBy", "test:triangle_smoke"),
    ("impl:src/renderer/VulkanRenderer.cpp", "testedBy", "test:asset_render"),
    # tests -> asset record
    ("test:assets_real", "verifies", "asset:gmdl:00E6BCE5:40637E03:067A07F0"),
    ("test:asset_render", "verifies", "asset:gmdl:00E6BCE5:40637E03:067A07F0"),
    # subsystems -> implementations / boundaries
    ("sub:dbpf-index", "implementedBy", "impl:src/assets/Dbpf.cpp"),
    ("sub:qfs-decompress", "implementedBy", "impl:src/assets/Dbpf.cpp"),
    ("sub:gmdl-walk-v8-static", "implementedBy", "impl:src/assets/Gmdl.cpp"),
    ("sub:mesh-extract-bounds", "implementedBy", "impl:src/assets/Mesh.cpp"),
    ("sub:renderer-offscreen-submit", "implementedBy", "impl:src/renderer/VulkanRenderer.cpp"),
    ("sub:dbpf-index", "boundedBy", "impl:src/compat/ResourceProvider.hpp"),
    ("sub:qfs-decompress", "boundedBy", "impl:src/compat/ResourceProvider.hpp"),
    ("sub:gmdl-walk-v8-static", "boundedBy", "impl:src/compat/MeshSource.hpp"),
    ("sub:mesh-extract-bounds", "boundedBy", "impl:src/compat/MeshSource.hpp"),
    ("sub:renderer-offscreen-submit", "boundedBy", "impl:src/renderer/Renderer.hpp"),
    # replaced-verified gates -> the tests that verify them
    ("sub:dbpf-index", "verifiedBy", "test:assets_synthetic"),
    ("sub:dbpf-index", "verifiedBy", "test:assets_real"),
    ("sub:qfs-decompress", "verifiedBy", "test:assets_synthetic"),
    ("sub:qfs-decompress", "verifiedBy", "test:assets_real"),
    ("sub:gmdl-walk-v8-static", "verifiedBy", "test:assets_synthetic"),
    ("sub:gmdl-walk-v8-static", "verifiedBy", "test:assets_real"),
    ("sub:mesh-extract-bounds", "verifiedBy", "test:assets_synthetic"),
    ("sub:mesh-extract-bounds", "verifiedBy", "test:assets_real"),
    # open gates -> what would close them
    ("sub:renderer-offscreen-submit", "gatedBy", "test:triangle_smoke"),
    ("sub:renderer-offscreen-submit", "gatedBy", "test:asset_render"),
    ("sub:resource-manager-full", "gatedBy", "obs:menu_transition"),
    ("sub:utfwin-message-dispatch", "gatedBy", "obs:menu_transition"),
    # observations supporting the bootstrap subsystem
    ("sub:bootstrap-appsystem-lifecycle", "observedVia", "obs:main_menu:entry"),
    ("sub:bootstrap-appsystem-lifecycle", "observedVia", "obs:main_menu:InitPlugins"),
    ("sub:bootstrap-appsystem-lifecycle", "observedVia", "obs:main_menu:Init"),
    ("sub:bootstrap-appsystem-lifecycle", "observedVia", "obs:main_menu:Startup"),
    ("sub:bootstrap-appsystem-lifecycle", "observedVia", "obs:main_menu:IAppSystem_Get"),
]

# test_result rows reflecting the measured 2026-09-21 runs (ctest 4/4 green, SPORE/ present)
TEST_ROWS = [
    ("assets_synthetic", "assets", "n/a", "all fixtures decode", "all fixtures decode", 1),
    ("assets_real", "assets", "n/a", "chosen gmdl consumed==1156", "chosen gmdl consumed==1156", 1),
    ("triangle_smoke", "render", "n/a", "pixels bit-identical", "pixels bit-identical", 1),
    ("asset_render", "render", "n/a", "27685 drawn px in range", "27685 drawn px in range", 1),
]


def main():
    if len(sys.argv) != 2 or sys.argv[1] not in ("init", "seed"):
        sys.exit("usage: seed_sprint.py [init|seed]")
    with open(SCHEMA) as f:
        schema = f.read()
    c = sqlite3.connect(DB)
    c.executescript(schema)
    with c:
        for label, name, conf, origin, attrs, note in LEGACY_NODES:
            c.execute(
                """INSERT INTO node(label,name,attrs_json,confidence,origin,note)
                   VALUES(?,?,?,?,?,?) ON CONFLICT(label,name) DO NOTHING""",
                (label, name, json.dumps(attrs), conf, origin, note))
        for label, name, ev, origin, attrs, note in NODES:
            c.execute(
                """INSERT INTO node(label,name,attrs_json,confidence,origin,note)
                   VALUES(?,?,?,?,?,?)
                   ON CONFLICT(label,name) DO UPDATE SET
                     attrs_json=excluded.attrs_json, confidence=excluded.confidence,
                     origin=excluded.origin, note=excluded.note""",
                (label, name, json.dumps(attrs), CONF[ev], origin, note))
        for short, status, boundary, impl in SUBSYSTEMS:
            attrs = {"status": status, "evidence": STATUS2EV[status],
                     "src": "docs/replacement-status.json"}
            if boundary:
                attrs["boundary"] = boundary
            if impl:
                attrs["impl"] = impl
            c.execute(
                """INSERT INTO node(label,name,attrs_json,confidence,origin,note)
                   VALUES(?,?,?,?,?,?)
                   ON CONFLICT(label,name) DO UPDATE SET
                     attrs_json=excluded.attrs_json, confidence=excluded.confidence,
                     origin=excluded.origin, note=excluded.note""",
                ("Subsystem", short, json.dumps(attrs), CONF[STATUS2EV[status]],
                 "manual", "imported from docs/replacement-status.json"))
        ids = {r[0]: r[1] for r in
               c.execute("SELECT name,id FROM node").fetchall()}
        # _node_id parity with kg.py: names are globally unique by construction
        for s, rel, d in LEGACY_EDGES + EDGES:
            c.execute("INSERT OR IGNORE INTO edge(src,dst,rel) VALUES(?,?,?)",
                      (ids[s], ids[d], rel))
        for t in LEGACY_TESTS:
            c.execute(
                """INSERT INTO test_result(name,stage,seed,expected,actual,pass)
                   SELECT ?,?,?,?,?,? WHERE NOT EXISTS
                   (SELECT 1 FROM test_result WHERE name=? AND stage=?)""",
                (*t, t[0], t[1]))
        # test outcomes: deterministic refresh of this seed's own rows only
        c.execute("DELETE FROM test_result WHERE name IN (?,?,?,?)",
                  tuple(t[0] for t in TEST_ROWS))
        c.executemany(
            """INSERT INTO test_result(name,stage,seed,expected,actual,pass)
               VALUES(?,?,?,?,?,?)""", TEST_ROWS)
    n = c.execute("SELECT COUNT(*) FROM node").fetchone()[0]
    e = c.execute("SELECT COUNT(*) FROM edge").fetchone()[0]
    t = c.execute("SELECT COUNT(*) FROM test_result").fetchone()[0]
    print(f"seeded {DB}: {n} nodes, {e} edges, {t} test rows")
    c.close()


if __name__ == "__main__":
    main()
