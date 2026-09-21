# Asset Import Roadmap (PROPOSAL)

**Status: PROPOSAL — nothing in §3–§5 is built.** Evidence vocabulary as in
`docs/RE-DOSSIER-SCHEMA.md`; forward-looking content is INFERRED/PROPOSAL, current
state is labeled as documented. Written 2026-09-21, end of the Obj 31–38 sprint
(chapter [014](devlog/014-re-intelligence-and-first-replacement.md)).

The asset pipeline can *decode* but cannot *find*: given a record we can walk it to
geometry, but given a *name* ("the default player cell") we cannot point at a record.
This doc states the current state, names the gap precisely, and proposes the target
architecture: a canonical asset manifest feeding the existing seams.

## 1 — Current state (what exists and is proven)

### Per-format readers (C++ `src/assets/`, each with a python oracle in `tools/spore/`)

| Format | C++ | Oracle | Status (see `docs/replacement-status.json`) |
|---|---|---|---|
| DBPF index + QFS decompress | `Dbpf.cpp` | `tools/spore/dbpf` | replaced-verified |
| GMDL walk (v8, BE refCount) | `Gmdl.cpp` | `tools/spore/gmdl` | replaced-verified (population-wide; 1,510 records fail = BE+v9 class) |
| Raster 32B envelope + DXT5 mips | `Texture.cpp`, `Dxt5.cpp` | `tools/spore/raster`, `dxt5` | supported (VERIFIED-DIFFERENTIAL on real bytes; light values APPROXIMATION) |
| RW4 container (`0x2f4e681b` et al.) | — | `tools/spore/rw4` (detection only) | supported — section walker NOT started (scope line from bytes: no PNG inside) |
| Mesh + bounds extract | `Mesh.cpp` | `tools/spore/gmdl` | replaced-verified |

### Identity resolution (Obj 34, commit `a4b5ac5`)

- `tools/spore/asset_resolver.py` — DBPF record resolver: `(type, group, instance)`
  → `{type_name, group_name, instance, size}`; `--map` / `--json`; idempotent,
  headless; 19 tests.
- `tools/spore/types/typenames.json` — 40 sporemol **type** names, each entry
  evidence-labeled. `tools/spore/types/groupnames.json` — 16 SDK **group** names.
- First result (VERIFIED via DBPF index): the 013 player stand-in `0x40637E02` is a
  BUILDING asset — identity REJECTED. Real cell GMDLs at groups `0x40616201/02`;
  13 `cll` SporeMol compositions at group `0x40616200`; no cell rasters in
  `Spore_Content.package`.

### Seams (`docs/BOUNDARIES.md`)

- **B1** `src/compat/ResourceProvider.hpp` — record access by `(type, group, instance)`.
- **B2** `src/compat/MeshSource.hpp` — gmdl → mesh/bounds.
- **B3** `src/renderer/Renderer.hpp` — submit (offscreen, present, textured).

## 2 — The gap

1. **Name ↔ instance is incomplete.** DBPF carries **no string table**; the sporemol
   tables give *type* names (40) and 16 *group* names — not per-instance names.
   Instance IDs are opaque, and the same instance ID recurs across a content family
   (e.g. `0xd1b4bb56` spans gmdl `0x40666202/03` and raster `0x40662900/01`).
2. **Semantic ownership is unknown.** Which `cll` composition is the *default
   player*? Which building is placed where? The 1,022 undecoded world-object
   records (`0x0f43029a`) are the likely carrier of placement/ownership — and are
   not decoded.
3. **Coverage holes.** 1,510 gmdl walk-fails (v9 layout undecoded); RW4 container
   sections undecoded; no cell-stage textures in `Spore_Content`.
4. **Consequence.** `src/apps/cell_stage.cpp` hard-codes its record list; the
   player cell is a REJECTED stand-in; the scene cannot be expressed in the game's
   own vocabulary.

## 3 — Target architecture (PROPOSAL, INFERRED — not built)

Three artifacts, each feeding the seams that already exist:

### 3.1 Canonical asset manifest

One rebuildable store — proposed `tools/spore/manifest/` (SQLite sidecar table or
versioned JSON) — with exactly one row per DBPF record:

```
(type, group, instance)  -- key
  type_name, group_name  -- from sporemol tables (today)
  size, format_class     -- gmdl/raster/rw4/prop/cll/... (measured)
  decode_status          -- ok | walk-fail(v9) | container-undecoded (measured)
  semantic_owner         -- entity/scene/creator block that owns it (UNKNOWN until P3/P4)
  evidence               -- per-field label (VERIFIED / INFERRED / UNKNOWN)
```

Built by an idempotent pipeline over the DBPF index + resolver + sporemol
compositions; every field carries its evidence label; double-run byte-identical (the
`sim_contract` discipline applied to data).

### 3.2 Manifest-driven loader

A C++ `AssetManifest` (new file under `src/assets/`) that the **existing** seams
consume — no seam changes:

- **B1**: provider gains a name path: `resolve("cell:default-player")` →
  `(type, group, instance)` via the manifest → existing record fetch.
- **B2/B3**: unchanged; they receive records as today.
- **Scene files become data**: `cell_stage`'s hard-coded record list becomes a
  declarative scene file (named assets + transforms) loaded through B1 — the 013
  "positions hard-coded" scar becomes an asset of the same kind as the geometry.

### 3.3 Semantic-owner join (closes the identity gap)

Two independent evidence sources feed `semantic_owner`:

- **Decoded world objects** (P3) — placement + which creator block references which
  gmdl (sporemol blockrefs carry group/instance).
- **Runtime resource-load events** (P4, gated on the Obj 36 Wine trace) — the
  strongest source: the game loading `cll` composition X at player spawn *is* the
  player-cell identity, VERIFIED by observation, not inference.

## 4 — Steps, in order (all NOT implemented)

| # | Step | Feasible with today's tools? | Closes |
|---|---|---|---|
| P1 | Manifest builder: pipeline over DBPF index + resolver + sporemol; evidence-labeled; testable headless | **Yes** — pure data over proven inputs | gap 1 (structure), 3 (coverage map) |
| P2 | C++ `AssetManifest` + B1 name path + declarative scene file for `cell_stage` | Yes — seams already exist | consequence 4 |
| P3 | World-object decoder (`0x0f43029a`, 1,022 records) via dossier workflow (7-stage pipeline, `docs/RE-WORKFLOW.md`) | No — format unknown; starts as UNKNOWN dossier | gap 2, player-cell placement |
| P4 | Runtime resource-load join (11 armed probes, `docs/REPLACEMENT-ABI.md` gate) | No — needs the Obj 36 gate (display + synthetic input, cell mode) | gap 2 (player-cell identity), promotion of the first `replaced-approx` |

Ordering is fixed by the gate: P1 → P2 are pure data/wiring and unblock the scene
from hard-coding immediately; P3 and P4 depend on the runtime gate and are the only
path to `replaced-verified` anywhere in the asset path.

## 5 — What this document is not

- No code. No format claims beyond those cited as VERIFIED/OBSERVED above.
- The manifest *schema* is INFERRED (a design choice), as is every seam-wiring
  detail in §3.2; the gap analysis in §2 is grounded in the Obj 34 findings.
- Nothing here changes the evidence rules: decompiler structure stays
  EVIDENCE-NOT-TRUTH; `semantic_owner` stays UNKNOWN until P3/P4 observation lands.
