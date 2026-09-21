# Replacement Boundaries — current review (Objective 37, 2026-09-21)

Review of what OpenSpore has actually replaced, where the seams sit, and what
blocks promotion. Built from `docs/replacement-status.json` (the source of
truth), `docs/BOUNDARIES.md` (seams B1–B3), `docs/REPLACEMENT-ABI.md`
(in-process hook contract), `docs/REPLACEMENT-DIFF.md`, and `src/`.

Evidence vocabulary (RECON appendix A): OBSERVED / VERIFIED / CONFIRMED /
SUPPORTED / INFERRED / APPROXIMATION / UNKNOWN. Decompilation is
**EVIDENCE-NOT-TRUTH**.

---

## 1. What is replaced, at which status

Every subsystem from `docs/replacement-status.json`. Status vocabulary:
`unknown, hypothesis, inferred, supported, verified, approximated,
replaced-stub, replaced-approx, replaced-verified`.

| Subsystem | Status | Seam | OpenSpore side | Gate (to next status) |
|---|---|---|---|---|
| dbpf-index | replaced-verified | B1 | `src/assets/Dbpf.cpp:parseDbpfIndex` | — (real-package tests incl. real-asset diff) |
| qfs-decompress | replaced-verified | B1 | `src/assets/Dbpf.cpp:qfsDecompress` | — |
| gmdl-walk-v8-static | replaced-verified | B2 | `src/assets/Gmdl.cpp:parseGmdl` | — (4209-record population walk; BE refCount verified) |
| mesh-extract-bounds | replaced-verified | B2 | `src/assets/Mesh.cpp:meshFromGmdl` | — |
| material-shader-texture | supported | B3 (createTexture, additive) | `src/assets/Texture.cpp`, `Dxt5.cpp`, lit pipeline | lit light values stay APPROXIMATION (no light data observed) |
| renderer-offscreen-submit | replaced-stub | B3 | `src/renderer/VulkanRenderer.cpp` | one material/lighting behavior pixel-matched under Wine (no original frame exists yet) |
| cell-sim-movement-interaction | replaced-stub | none (no seam while unobserved) | `src/sim/Sim.cpp` CellSim | no differential oracle for cell movement (no headless trace of the original) |
| **cell-movement-mouse-steering** | **replaced-approx** | **in-process hook, 5-byte `jmp` at `0x00e5b790` (seam proven in `tools/replace/synthetic`)** | `src/replace/Replace.cpp:replacement_MovePlayerToMousePosition` | **Wine cell-mode runtime trace** — promote INFERRED field offsets + APPROXIMATION plane constants to VERIFIED |
| interactive-presentation | replaced-stub | B3 (present mode, backend-only) | `src/apps/cell_stage.cpp:runInteractive` + present mode | no differential oracle for interactive behavior |
| cell-stage-scene-assembly | approximated | B1+B2+B3 | `src/apps/cell_stage.cpp` | scene/identity evidence (world-obj 0x0f43029a undecoded; player-cell identity UNRESOLVED) |
| resource-manager-full | inferred | — | — | traced menu transition showing the original load path |
| bootstrap-appsystem-lifecycle | supported | — | — | observation only; reimplementation not started |
| utfwin-message-dispatch | hypothesis | — | — | run `menu_transition` under the tracer |
| rw4-container-animation | supported | — | — | C++ section walker field-matching the python oracle on `rw4_11` |
| simulator-gameplay | hypothesis | — | — | behavioral trace of a stage transition |
| property-serialization | inferred | — | — | `.prop` record round-trip |
| audio-havok-input | unknown | — | — | any Wine-observed call sequence |
| pollinator-online | unknown (non-goal) | — | — | defunct service; will be stubbed, never reimplemented |

Only `cell-movement-mouse-steering` is at `replaced-approx` — the first
subsystem with a clean-room replacement that passes a differential test
(64/64 field comparisons, `docs/REPLACEMENT-DIFF.md`) while its status stays
honest: **NOT a live-runtime verification** (cell mode is unreachable
headless; the reference is EVIDENCE-NOT-TRUTH).

## 2. The seams

Three static compatibility seams (`docs/BOUNDARIES.md`), each a small
header-only interface with a real producer and a consumer in-tree:

| Seam | File | Semantic responsibility | Producers / consumers |
|---|---|---|---|
| B1 `IResourceProvider` | `src/compat/ResourceProvider.hpp` | record bytes by `(type, group, instance)`; no file/compression/manager leaks | `DbpfResourceProvider` (real packages), `MemoryResourceProvider` (stub); consumer `fetchGmdlModel` |
| B2 `IMeshSource` | `src/compat/MeshSource.hpp` | parsed model → host `Mesh` by index; version quirks stay behind | `GmdlMeshSource`; consumer `submitMeshSource` |
| B3 `IRenderer` | `src/renderer/Renderer.hpp` | lifecycle + upload + draw + readback (present mode is backend-only) | `VulkanRenderer` (offscreen + WSI); `NullRenderer` in tests proves any backend accepts any producer |

Substitutability is proven in-tree by `testCompatBoundaries` (same consumer
against the real provider and the stub, byte-identical).

### The in-process seam (new with Obj36)

`cell-movement-mouse-steering` does not sit on B1–B3. It sits on the
**inline-hook mechanism** proven headless in `tools/replace/synthetic/`:

1. `mprotect` the code page **RWX** (RW alone de-executes the patcher mid-patch).
2. Overwrite the target's first 5 bytes with `jmp rel32` — op `0xE9`
   (5 bytes). `0xEB` is `jmp rel8` (2 bytes) — the documented gotcha.
3. Self-check the readback, restore RX, save the original bytes (reversible).

For the Spore target the 5-byte boundary is clean: the entry is one complete
self-contained instruction `mov eax,[0x016b3c04]`
(`a1 04 3c 6b 01` VERIFIED at file offset `0xA5AB90`); overwriting it leaves
the rest of the function intact-but-unreachable — the intended seam
(`docs/REPLACEMENT-ABI.md` §1).

**How a Spore function is swapped in-process** (per-target contract in
`docs/REPLACEMENT-ABI.md` §5): the replacement is a `jmp` target, not a
`call` target — so `esp` and the arg layout are inherited from the original
caller unchanged (cdecl `float deltaTime` on the stack); it reads only the
documented globals/fields by address; it reproduces the observable effects;
it returns with the stack as found.

Honest status of this seam: the mechanism is **VERIFIED** on a native 32-bit
synthetic (`make test` → PASS: BEFORE `orig` 40× / `replacement` 0×; AFTER
output `x*2+1000`, `replacement_ran=1`). **No patch has been installed into
`SporeApp.exe`** — the replacement and its decompilation reference are
differentially tested on the host, not inside the original process. (This
refines the BOUNDARIES.md statement that live in-EXE replacement "is not the
current mechanism": the mechanism is now proven feasible; the install step
itself is gated on §3.)

## 3. What is NOT replaced, and why

Everything without an `openspore_impl` in the status file is unreplaced, and
the two load-bearing gaps are both **gated on a live cell-mode runtime trace
that is unreachable headless**:

- **Why unreachable (OBSERVED, 9 runs, `docs/analysis/CELL-RUNTIME-OBSERVATION.md`):**
  Xvfb/xdotool absent (no synthetic input); Wine 11.17 under XWayland `:0`
  boot-stalls before D3D init on 8/9 boots; in the one run that reached the
  menu, all 10 cell-stage probes fired 0 events (the menu's 30 Hz loop is a
  generic per-frame function, `FUN_0069b600` — do not use it as a cell marker).
- **The exact gate** for `cell-movement-mouse-steering`
  `replaced-approx` → `replaced-verified`: a Wine cell-mode runtime trace that
  (a) byte-reads the plane constants `DAT_015a7c40/44/48` and
  `DAT_016b3c28/2c/30` (addresses OBSERVED, values never read →
  APPROXIMATION today) and (b) confirms the sCellGame field offsets
  (`+0x5158` lock, `+0x411c` player index, `+0x5270` moving flag — INFERRED).
  The 12 byte-verified probes in `tools/observatory/probes/cell_movement.json`
  (image base `0x400000`, each entry byte-checked at
  `file_off = linked − 0x400C00`) fire the moment the cell stage is entered.
  What the operator needs: a real/Xvfb display **plus** synthetic input
  (xdotool) and the menu path into cell stage; the boot-stall fix makes the
  menu reproducible.
- Also blocked on runtime: `resource-manager-full` (menu_transition trace),
  `utfwin-message-dispatch`, `simulator-gameplay` (stage-transition trace),
  `audio-havok-input` (any observed call sequence).
- Blocked on decoding, not runtime: `rw4-container-animation` (C++ walker vs
  python oracle on `rw4_11`), `property-serialization` (.prop round-trip),
  `cell-stage-scene-assembly` (world-obj 0x0f43029a decode + player-cell identity).

## 4. Risk / ABI hazards, and containment

| Hazard | Level | Containment |
|---|---|---|
| cdecl frame inherited across the `jmp` | convention INFERRED (no SDK `CONVENTION` attr; 32-bit global fns are cdecl, single 4-byte arg on stack) | hook is a `jmp`, not a `call` — caller frame is unchanged by construction; contract §5 requires the replacement to return with `esp` balanced; proven on the synthetic |
| `sCellGame` field layout | INFERRED (offsets VERIFIED from decompilation; meanings guessed; no MSVC RTTI, no trace) | every field labeled in the ABI table §2/§3; `CellGameView.hpp` structs are explicit POD views that *alias* offsets — "NOT the true class layout, padding anonymous by design"; promotion gate above |
| Decompiler type-guesses | EVIDENCE-NOT-TRUTH; casts are guesses | reference is a line-by-line transcription with the omission boundary documented (`Reference.cpp` header: what is omitted and why none of it touches a compared field); diff tolerance 1e-6 on float32, exact on flags |
| `delta` sign transcription | the decompiled body computes `delta = −(target − current)` and feeds the orientation; a sign flip turns the player 180° away | orientation quaternion is a compared field in all 64 diff comparisons — 4 hit cases with non-zero `orient_qy` (±0.216930449, 0.948683262, ±0.973249018) would mismatch on a flip; all MATCH |
| Plane constant values | APPROXIMATION (never read) | pinned as APPROXIMATION in contract §3/§6, ABI §2, status note; the diff uses identical inputs on both sides so it does not smuggle the assumption; read at runtime to promote |

## 5. How to add the next replacement target

1. **Dossier**: `python3 tools/re/dossier.py <topic>` from the committed
   snapshot (`tools/re/data/ghidra_snapshot_<topic>.json`) + `vtables.json` +
   KG + SDK; fill `docs/analysis/dossiers/<topic>.md` (schema:
   `docs/RE-DOSSIER-SCHEMA.md`).
2. **Decompiled capture**: commit the Ghidra capture under
   `tools/re/data/decompiled/<Name>.c` — EVIDENCE-NOT-TRUTH header mandatory.
3. **ABI doc**: per-target `docs/REPLACEMENT-ABI`-style section — symbol/VA
   (SDK), file offset (image base `0x400000`), return/params/convention
   (label INFERRED), entry bytes read from the EXE with the 5-byte hook
   boundary checked (self-contained instruction), globals/fields table with
   per-field evidence labels, behavioral contract, replacement contract
   (read-only addresses, `esp` balanced, effects reproduced).
4. **Hook seam**: reuse the proven `0xE9 rel32` + RWX mechanism
   (`tools/replace/synthetic/`); verify the BEFORE/AFTER split (tracer for
   BEFORE only — the tracer's INT3 and the constructor's patch cannot
   coexist on one address).
5. **Implementation + reference**: `src/replace/` — the replacement (pure,
   deterministic) and the decompilation transcription as reference; POD view
   headers with offset evidence labels.
6. **Differential test**: `src/replace/tests/diff_test.cpp` pattern —
   deterministic cases × compared fields, float32 tolerance 1e-6 / exact
   flags, byte-identical inputs both sides (low-4-GiB `MAP_32BIT` for 32-bit
   stand-ins); record the full table in a `REPLACEMENT-DIFF`-style doc.
7. **Record**: `docs/replacement-status.json` entry (status + `gate` +
   evidence + commits), KG update via `knowledgegraph/kg.py`, `docs/STATE.md`
   / devlog. Status is `replaced-approx` until the live trace of §3 lands —
   never `replaced-verified` on a decompilation reference alone.
