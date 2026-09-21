# 014 — RE Intelligence and the First Replacement

## 2026-09-21, evening (commits `d43e324` 20:34 → `cfd0da6` 23:40)

State of play: chapter [013](013-cell-stage-slice.md) ended at 18:41 with a live,
keyboard-driven cell window — and two open gaps that stayed open all day: the
player-cell model's identity was UNRESOLVED (no name↔group map), and the movement
dynamics were UNOBSERVED (five APPROXIMATION constants, no trace of the original).
The evening sprint, Obj 31–38, attacked both gaps with a new pipeline piece — the
**RE Intelligence** dossier generator — and, from its findings, produced the project's
**first in-process replacement** of original code.

## RE Intelligence MVP: the dossier (commit `d43e324`, Obj 31, 20:34)

`tools/re/dossier.py` is a stdlib-only generator that merges every committed evidence
source into one document per behavior: the Ghidra function snapshot
(`tools/re/data/`, committed — no live server needed), the vtable anchors, the
knowledge graph, the DBPF resource index, and the Observatory traces. It degrades
gracefully without `SPORE/` and is pinned by `tests/test_dossier.py` (7 tests).

The schema (`docs/RE-DOSSIER-SCHEMA.md`) documents a 7-level evidence vocabulary —
`OBSERVED / VERIFIED / CONFIRMED`, `SUPPORTED`, `INFERRED`, `APPROXIMATION`,
`UNKNOWN` — and one rule that governs everything downstream: decompiler output is
**EVIDENCE-NOT-TRUTH**. Structure read from a decompilation is *observed in the
decompilation*; it is never asserted as the program's truth until a runtime trace says
so.

The first dossier, `docs/analysis/dossiers/cell-movement.md`, has one headline:

> The player is steered by a **RAY-PLANE INTERSECTION**, not keyboard thrust.
> `Simulator::Cell::MovePlayerToMousePosition` (VA `0xe5b790`) takes the camera ray
> built from mouse input, intersects it with the movement plane, and the hit point
> becomes the player's target position plus a travel-direction orientation. Keyboard
> input is a *secondary* bias on top, not the driver.

Every constant in that claim carries a label: the plane's normal and point addresses
(`DAT_015a7c40/44/48`, `DAT_016b3c28/2c/30`) are OBSERVED; their *values* were never
read (no cell-mode trace exists), so they remain INFERRED; the seven scene resources
the dossier references are CONFIRMED against the 17,119-record DBPF index. And the
dossier records the negative result verbatim: **runtime NOT OBTAINED** (Xvfb absent) —
recorded, not fabricated.

## The steering, rebuilt from the dossier (commit `1a3dd2c`, Obj 33, 21:50)

`src/sim` was rewritten around the finding: `CellSim` now computes
`viewRay(mouseNDC) ∩ movementPlane` and the hit is the movement *target*; the player
turns to face the travel direction; keyboard thrust is demoted to a secondary bias
with a keyboard-only fallback for frames without a mouse position. `MovementPlane
{normal, point}` is an explicit named parameter — every value APPROXIMATION, because
the original constants were never read. New `rayPlaneHit` + `CameraState::viewRay`
helpers, new deterministic tests `testRayPlaneHit` / `testMouseSteer`.

Status in `docs/replacement-status.json`: `replaced-stub`. Deliberate: the model is
evidence-backed, but *no differential oracle exists* — there is no trace of the
original's cell movement to compare against, so nothing here may be called verified.

## Asset identity: the stand-in was a building (commit `a4b5ac5`, Obj 34, 22:15)

The 013 gap ("player-cell identity UNRESOLVED") had no answer because no tool could
map a DBPF record to its *kind*. Now it can: `tools/spore/asset_resolver.py` resolves
`(type, group, instance)` → `{type_name, group_name, instance, size}` from the sporemol
type/group tables (`tools/spore/types/typenames.json`, 31→40 entries, each
evidence-labeled; `groupnames.json`, 16 SDK group names), is idempotent and headless,
and is pinned by 19 tests.

The first thing it settled is embarrassing, and it was load-bearing: the roundish
stand-in the whole 013 slice rendered as "the player cell" — gmdl
`0x00E6BCE5:0x40637E02:0x067A0801` — is a **BUILDING**-category asset (category
`0x63`, stage `0x7E`). It is not a cell asset. Identity **REJECTED**
(VERIFIED against the DBPF index bytes).

What it found instead (VERIFIED): real cell-stage GMDLs live at groups
`0x40616201` / `0x40616202` (category `0x61`, stage `0x62` — 88 records, 44
instances); 13 `cll` SporeMol records at group `0x40616200` define cell
compositions; and there are *no* cell-stage rasters in `Spore_Content.package`.

So the 013 gap closed halfway: cell assets provably exist and are locatable by
category/stage, but the *default player composition* — which of the 13 `cll`
definitions, which blocks — is not identified. It stays OPEN, labeled.

## Contract and fixtures (commit `6470cca`, Obj 35)

Before replacing anything, the sim got a pinned contract:
`docs/CELL-CONTRACT.md`, version `cell-sim-contract/1`. The invariants are the
things a replacement must preserve: 60 Hz fixed step, binary32 floats, `%.9g`
float serialization, same-host bit-exact determinism. Five fixtures
(`tests/fixtures/cell/fixtures.json`) replay through the sim; a double run is
byte-identical, and `ctest:sim_contract_test` replays them bit-exact. The contract
is honest about itself: invariants VERIFIED; `MovementPlane` constants
APPROXIMATION; steer/eat/flee semantics INFERRED/OBSERVED — mixed, on purpose.

## The first in-process replacement (commits `9734cc3`, `b44e683`, Obj 36A–D)

Four sub-steps, in order:

- **A — the hook is real.** `tools/replace/synthetic` proves the swap mechanism in
  process: a 5-byte `jmp` (`0xE9 rel32`) lands on a verified 5-byte instruction
  boundary — the file-layout `mov eax, [0x016b3c04]` at file `0xA5AB90` (VA
  `0x00e5b790`, bytes `a1 04 3c 6b 01`) — with RWX `mprotect` on the page. The
  caller's registers and stack are untouched by the `jmp`, which is what lets a
  replacement inherit the original's calling convention for free.
- **B — the ABI contract.** `docs/REPLACEMENT-ABI.md` pins the target: VA
  `0x00e5b790`, signature `void (float deltaTime)` cdecl, reads only ABI-documented
  `sCellGame` fields plus the plane constants *by address*. A replacement that reads
  only this surface is safe under the hook.
- **C — the replacement.** `src/replace/Replace.cpp` — clean-room, pure,
  deterministic: lock guard → player fetch → camera ray ∩ movement plane → write
  target position + moving flag + travel orientation. No globals beyond the
  documented state; no allocation; the same code path the 013 sim uses.
- **D — the differential.** `ctest:replace_diff_test` runs 8 cases × 8 fields against
  the *decompilation reference* of the original: **64/64 MATCH** within 1e-6 (exact
  for the moving flag), 0 mismatches (`docs/REPLACEMENT-DIFF.md`).

Stated plainly, because it decides everything downstream: **this is not a
live-runtime verification.** Cell mode is unreachable headless, so no live oracle
exists; the reference is a decompiler's reading of the original, i.e.
EVIDENCE-NOT-TRUTH. The status recorded is `replaced-approx`, and the promotion to
`replaced-verified` is gated on one artifact only: a Wine cell-mode runtime trace of
the original with the real plane constants and field offsets read off it.

## The pipeline, made explicit (commit `cfd0da6`, Obj 37/38)

Two docs freeze the process so the next replacement doesn't re-derive it:

- `docs/replacement-boundaries.md` — all 18 subsystems' status (cross-checked
  against `docs/replacement-status.json`), the B1–B3 seams, the proven in-process
  swap, what is *not* replaced and why, and the exact gate for
  `replaced-approx → replaced-verified` (the Wine trace).
- `docs/RE-WORKFLOW.md` — the 7-stage pipeline: **dossier → static Ghidra → runtime
  observatory → asset resolver → contract + fixtures → replace → record** — plus a
  decision table mapping each evidence level to the claim it allows and the proof
  required, and the known limitations (headless cell-mode unreachable, decompiler
  noise, no MSVC RTTI in `SporeApp.exe`).

## The honest failures

- **Runtime is still NOT OBTAINED.** Nine Wine launch attempts this sprint: 8/9
  stalled at boot (wineserver), the one that attached showed a 30 Hz menu render
  loop — and zero cell-stage events (`docs/analysis/CELL-RUNTIME-OBSERVATION.md`).
  No Xvfb, no synthetic input; headless menu navigation is not possible in this
  environment. The 11 byte-verified probes sit armed and unfired.
- **The replacement was never run against the live original.** Only against the
  decompiled reference. Calling it "replaced" before the trace would be the exact
  category error the evidence vocabulary exists to prevent.
- **Player-cell default composition still unidentified** — the stand-in is now
  provably wrong (a building), but no `cll` definition has been confirmed as the
  default player.
- **1,022 world-object records (`0x0f43029a`) remain undecoded** (scene placement
  hard-coded) and the RW4 containers remain out of scope.

## Tally

| Suite | Result (2026-09-21 host build) |
|---|---|
| CTest | **10/10** (was 9/9 before Obj 36D; `replace_diff_test` added) |
| Python unittest | **53/53** (`python3 -m unittest discover -s tests -t .`) |
| Knowledge graph | 88→96 nodes, 102→115 edges, 11→14 test rows; new labels `Dossier`, `Finding`, `ReplacementTarget`, `Contract` |

### Outcome

| | |
|---|---|
| **Proven** | RE Intelligence MVP: stdlib dossier generator + 7-level evidence schema + first dossier (`cell-movement`), decompilation marked EVIDENCE-NOT-TRUTH |
| | Headline finding: movement is camera-ray × movement-plane; keyboard demoted to secondary (OBSERVED in decompilation; runtime NOT OBTAINED) |
| | The 013 stand-in is a BUILDING asset — identity REJECTED (VERIFIED via DBPF index); real cell GMDLs at `0x40616201/02`, 13 `cll` compositions at `0x40616200` |
| | 5-byte `jmp` swap mechanism proven in-process on a verified boundary (RWX `mprotect`); cdecl contract inherited across the hook |
| | Clean-room replacement of `MovePlayerToMousePosition`: 64/64 differential MATCH vs decompilation reference |
| | Sim contract `cell-sim-contract/1` + 5 fixtures, bit-exact double-run |
| **Open** | Replacement is `replaced-approx` — the gate to `replaced-verified` is a Wine cell-mode trace (fixes boot stall + a display with synthetic input) |
| | Plane constant values + sCellGame field offsets still INFERRED (addresses OBSERVED, values unread) |
| | Player-cell default composition unidentified; 1,022 world objects undecoded; no live-runtime oracle for anything this sprint |

Next: close the runtime gate — a display stack with synthetic input (Xvfb or the
`cell_stage` window as the stand-in surface) so the 11 armed probes can fire inside
cell mode — then the first `replaced-verified`, the next replacement target from the
dossier's callee list (camera manager next), and sporemol composition decoding for
the default player cell. Back: [chapter 013](013-cell-stage-slice.md).
