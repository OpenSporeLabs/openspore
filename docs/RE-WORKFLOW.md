# RE-WORKFLOW — the end-to-end reverse-engineering pipeline (Objective 38, 2026-09-21)

The pipeline this sprint (Obj31–36) established, as a repeatable 7-stage
workflow. Every stage names the REAL tool/file it uses — no abstractions.
Evidence vocabulary is mandatory at every stage (RECON appendix A):
OBSERVED / VERIFIED / CONFIRMED / SUPPORTED / INFERRED / APPROXIMATION /
UNKNOWN. Decompilation is **EVIDENCE-NOT-TRUTH**.

Worked example throughout: `Simulator::Cell::MovePlayerToMousePosition`
(cell-movement topic) — the only target that has completed all seven stages.

---

## Stage 1 — Select target → dossier

- Pick the topic; gather committed evidence: Ghidra snapshot
  (`tools/re/data/ghidra_snapshot_<topic>.json`), vtable scan
  (`docs/analysis/vtables.json`), the shared KG
  (`knowledgegraph/kg.py` + `spore.db`), and the SDK import
  (march2017 XML — the only CONFIRMED source for symbol names).
- Generate the dossier: `python3 tools/re/dossier.py <topic>` →
  `docs/analysis/dossiers/<topic>.md` (schema
  `docs/RE-DOSSIER-SCHEMA.md`). Missing optional inputs degrade to explicit
  records — never a failure, never a fabrication (a topic with no trace
  records `runtime: NOT OBTAINED` with a reason).
- Cell-movement outcome: the dossier pinned the ray-plane steering model,
  9 functions with per-field evidence labels, and an empty runtime section.

## Stage 2 — Static evidence (Ghidra headless MCP)

- Query the headless Ghidra MCP server (bridge `127.0.0.1:8089`, project
  `~/ghidra-spore-project/SporeProject`) for functions, xrefs, and
  decompilation. **Commit** the decompiled captures under
  `tools/re/data/decompiled/<Name>.c` (EVIDENCE-NOT-TRUTH) — the dossier and
  later reference transcriptions read from the committed bytes, not from a
  live server state.
- Remember the address mapping (VERIFIED, Obj32): Ghidra image base
  `0x400000`; a function's "address" is a PE-linked VA; file offset =
  linked − `0x400C00`; probe `rva` = snapshot `address` = dossier RVA +
  `0x100000`.
- Byte-verify every function you care about at its file offset in
  `SPORE/SporeBin/SporeApp.exe` (instruction-aligned prologue check).

## Stage 3 — Runtime evidence (observatory probes + Wine)

- Define probes in `tools/observatory/probes/<topic>.json` (name, rva,
  `image_base`); each entry byte-verified at `file_off = linked − 0x400C00`
  before running (the `cell_movement.json` pattern: 12 probes, base
  `0x400000`).
- Run `tools/observatory/observe.py <probe-set> --duration N` under Wine
  with a fresh `wineserver -k` per run; the `probe_tracer` (ptrace) writes
  `/tmp` JSONL; `analyze.py` summarizes counts/intervals/tids.
- **Record what IS and IS NOT observable — no fabrication.** Cell-movement
  outcome (OBSERVED, 9 runs): 0 cell-stage events in every run (the stable
  negative result); one run reached the menu and fired only the generic
  30 Hz per-frame function; 8/9 boots stalled before D3D init (env-dominant).
  Xvfb/xdotool absent ⇒ no synthetic input ⇒ cell stage unreachable headless.
  This negative result is itself committed evidence
  (`docs/analysis/CELL-RUNTIME-OBSERVATION.md`) and drives the status gates.

## Stage 4 — Asset correlation

- `python3 tools/spore/asset_resolver.py <package> [--type T] [--group G]
  [--record T:G:I] [--near G:I N] [--map] [--json]` maps every record of a
  `.package` to `(type_id, type_name, group_id, group_name, instance_id,
  size)` using `tools/spore/types/typenames.json` + `groupnames.json`.
- Cross-check the dossier's resource references against the DBPF index of
  `SPORE/Data/Spore_Content.package` (17119 records); presence is
  CONFIRMED, identity/position claims stay APPROXIMATION until a scene/world
  record decode says otherwise. Format oracles: `tools/spore/{dbpf,rw4,gmdl,
  raster,dxt5}` (python, stdlib-only — the byte-level ground truth the C++
  walkers diff against).

## Stage 5 — Contract + frozen fixtures

- Write the behavioral contract: `docs/CELL-CONTRACT.md`
  (`cell-sim-contract/1`) — pinned invariants (60 Hz fixed step, binary32,
  `%.9g` float serialization, same-host determinism), the full state surface,
  and the exact per-frame `update()` order (reordering IS a semantics change).
- Freeze deterministic fixtures: `python3 tools/gen_cell_fixtures.py
  --rebuild` runs the C++ emitter (`sim_test --emit-fixtures`) **twice and
  requires byte-identical output before writing** `tests/fixtures/cell/
  fixtures.json`. The scenario list lives once in
  `src/sim/tests/contract_scenarios.hpp` — emitter and replay consume the
  same list, so fixtures and replay agree by construction.
- Replay: `src/sim/tests/sim_contract_test.cpp` (ctest `sim_contract_test`)
  compares the live replay against the frozen fixtures **bit-exactly**
  (float32, no epsilon), plus double-run determinism per fixture.
- Change procedure (contract §7): change semantics → bump `kContractVersion`
  + doc → rebuild fixtures → ctest passes → commit fixtures + doc + code
  together; non-semantics changes must leave fixtures byte-identical.

## Stage 6 — Replace

1. **ABI contract** (`docs/REPLACEMENT-ABI.md`): symbol/VA from the SDK
   (CONFIRMED), file offset (VERIFIED), return/params (CONFIRMED), calling
   convention (INFERRED), entry bytes read from the EXE with the clean
   5-byte hook boundary (`a1 04 3c 6b 01` = one self-contained `mov`),
   global-state table with per-field evidence, behavioral contract, and the
   replacement contract (inherited cdecl frame via `jmp`; reads only the
   documented addresses; effects reproduced; `esp` balanced; reversible).
2. **Synthetic hook proof** (`tools/replace/synthetic/`, `make test` →
   PASS): the exact install mechanism — RWX `mprotect`, `0xE9 rel32` patch
   (not `0xEB` rel8), readback self-check, RX restore, saved original bytes.
   BEFORE traced with the observatory (`orig` 40×, `replacement` 0×); AFTER
   by behavior (`x*2+1000`, `replacement_ran=1`) — the tracer's INT3 and the
   constructor's patch cannot coexist on one address.
3. **Implementation** (`src/replace/Replace.cpp`): pure, deterministic,
   reads only the ABI-documented state (POD views in `CellGameView.hpp`,
   offsets aliased, padding anonymous by design).
4. **Decompilation reference** (`src/replace/Reference.cpp`): line-by-line
   transcription of the Stage-2 capture with the omission boundary documented
   (what is deliberately omitted and why none of it touches a compared field).
5. **Differential test** (`src/replace/tests/diff_test.cpp`, ctest
   `replace_diff_test`): 8 deterministic cases × 8 compared fields =
   64 comparisons, float32 tolerance 1e-6 / exact flags, byte-identical
   inputs on both sides (low-4-GiB `MAP_32BIT` so the 32-bit `playerRef`
   stand-in is a valid address), decompiled guards verbatim. Result:
   64/64 MATCH, 0 mismatches (`docs/REPLACEMENT-DIFF.md`) — and the diff doc
   states the evidence boundary up front: **this is NOT a live-runtime
   verification**; no Wine cell-mode trace exists.

## Stage 7 — Record

- `docs/replacement-status.json`: the entry gets its evidence-labeled status
  (vocabulary: `unknown → hypothesis → inferred → supported → verified →
  approximated → replaced-stub → replaced-approx → replaced-verified`), the
  `gate` to the next status, `evidence` (committed artifacts only), and
  `commits`. The cell-movement entries landed at `replaced-approx`
  (steering) / `replaced-stub` (sim) / `approximated` (scene) — each with an
  explicit "pending a Wine cell-mode trace" gate.
- KG: record decisions/tests via `python3 knowledgegraph/kg.py
  <add-edge|record-test|...>` into `spore.db`.
- `docs/STATE.md` + `docs/devlog/` chapter with the commit SHAs.

---

## Decision table — evidence level → what you may claim → required proof

| Evidence level | You may claim | Required proof (committed) |
|---|---|---|
| OBSERVED / VERIFIED / CONFIRMED | "The original does X" / "these bytes are X" | a trace of the original (observatory JSONL run log), a byte-level read of the EXE/assets, or the SDK (march2017) — the artifact itself, not a paraphrase |
| SUPPORTED | "X, per multiple agreeing sources" | ≥ 2 independent sources cited (e.g. decompile + probe, or two real records) |
| INFERRED | "X is deduced from a single source" — usable for design, **never** as an oracle | the single source cited per field (decompilation line, one record); labeled at every use |
| APPROXIMATION | "we chose value V; no traced number exists" | the choice is pinned in a doc with defaults table; the gate to promote it to VERIFIED is stated (e.g. the plane-constant runtime read) |
| UNKNOWN | nothing — only the gap | the gap is recorded (dossier "known unknowns", status `unknown` + gate) |
| Decompilation (any row) | structure, offsets, call shape — as **evidence, not truth** | committed capture under `tools/re/data/decompiled/`; cast types are decompiler guesses and are labeled as such |

Rules that fall out of the table: a differential against a decompilation
reference caps status at `replaced-approx`; `replaced-verified` requires the
live oracle (original under Wine, real bytes/pixels/trace); a green test
against our own fixtures proves determinism, not fidelity.

## Known limitations (state of 2026-09-21)

1. **Headless cell-mode is unreachable.** Xvfb/xdotool absent; Wine boot
   stalls before D3D init on 8/9 boots; zero cell-stage probe events in all
   9 runs. No live oracle for anything cell-mode: it is the single gate on
   promoting the steering replacement and on the `resource-manager-full`,
   `utfwin-message-dispatch`, and `simulator-gameplay` entries.
2. **Decompiler type noise.** Ghidra casts are guesses on a binary with no
   type info; every transcription carries the EVIDENCE-NOT-TRUTH header and
   a documented omission boundary.
3. **No MSVC RTTI in SporeApp.exe.** Class structure comes from vtable data
   (`tools/ghidra/VtableDetect.java` → `docs/analysis/vtables.json`, 3081
   candidates / 20 labels) + SDK structures only; field meanings stay
   INFERRED until a trace reads them.
4. **Plane constants unread.** `DAT_015a7c40/44/48` (normal) and
   `DAT_016b3c28/2c/30` (point): addresses OBSERVED, values never read —
   every use of them is an APPROXIMATION default until the runtime read.
5. **Scene identity gap.** World-object records (0x0f43029a, 1,022 of them)
   undecoded; the player-cell identity is UNRESOLVED (sporemol block
   assembly, no name↔group map) — the scene stays `approximated` on it.
6. **Determinism is same-host.** Contract fixtures are bit-exact on the same
   host + toolchain only (libc `sinf`/`cosf`/`atan2f`); cross-platform is
   explicitly NOT guaranteed.
