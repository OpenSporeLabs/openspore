# Cell simulation contract — `cell-sim-contract/1`

Canonical, stable contract for the OpenSpore Cell simulation (`src/sim`),
with a frozen deterministic fixture set (`tests/fixtures/cell/fixtures.json`).
Obj36 differential testing diffs against this baseline; the original game
under Wine is the external oracle.

Evidence vocabulary (used throughout; see `docs/analysis/dossiers/`):
**OBSERVED / VERIFIED / CONFIRMED** (traced in the original), **SUPPORTED**
(multiple sources agree), **INFERRED** (deduced, single source),
**APPROXIMATION** (chosen value, no traced number), **UNKNOWN**.

## 1. Scope

In scope: player-cell movement, camera, mouse steering, keyboard fallback,
one eat interaction, one flee interaction — everything in `CellSim::update`.
Out of scope (known boundaries of v1): the original's pause/lock flag
(`sCellGame+20824`, not modeled), any RNG/time (none exist here), and the
unread movement-plane constants (APPROXIMATION defaults, §6).

## 2. Pinned invariants

| invariant | value | evidence |
|---|---|---|
| timestep `kDt` | `1.0F/60.0F` s (60 Hz) | fixed by design; SUPPORTED by the stage's fixed-rate pump |
| float type | binary32 (`float`) throughout | by construction |
| float serialization | `%.9g` decimal — 9 significant digits round-trip float32 exactly | VERIFIED property of IEEE-754 binary32 |
| determinism boundary | bit-exact on the same host + toolchain (GCC + libc). **Cross-platform NOT guaranteed** (`sinf`/`cosf`/`atan2f` are libc, libm). The Obj36 oracle runs on the same host. | VERIFIED (double-run check in the contract test) |
| no `time()`, no `rand()`, no ASLR-dependent state | guaranteed by construction | VERIFIED (test) |

## 3. State layout (the contract surface)

All fields below are the full contract surface; any addition/renaming is a
version bump.

- `Entity` — `role` (string; `food_*` = food, `prey_*` = prey), `group`,
  `inst`, `pos[3]` (world), `targetSpan`, `alive`.
- `PlayerState` — `pos[3]`, `heading` (yaw, radians; `fwd=(sin h, 0, cos h)`,
  so h=0 faces +Z, increasing h turns toward +X), `vel[3]`, `growMeter` (int).
- `CameraState` — `yaw`, `pitch`, `zoom`, `baseDist=16`, `target[3]` (follows
  the player), `fov` (vertical, 60° — APPROXIMATION). Eye:
  `target + dist*(sin yaw·cos pitch, sin pitch, cos yaw·cos pitch)` —
  INFERRED from `cCameraManager::SetViewer`.
- `MovementPlane` — `normal=(0,1,0)`, `point=(0,0,0)` — **APPROXIMATION**
  (the original reads them from `DAT_015a7c40/44/48` and `DAT_016b3c28/2c/30`;
  addresses OBSERVED, values INFERRED — never read, no runtime trace).
- `InputFrame` — `thrustLeft/Right/Forward/Back`, `boost`, `hasCamera` +
  `cameraYaw/Pitch/Zoom`, `hasMouse` + `mouseX/mouseY` (NDC, x right, y up,
  −1..1). `hasMouse=false` → keyboard-only path.
- `MovementParams` (defaults, pinned): `forwardSpeed=4.0`, `strafeSpeed=2.0`,
  `boostMul=2.0`, `turnRate=1.5` rad/s, `damping=6.0`, `eatRadius=3.5`,
  `fleeRadius=4.0`, `steerSpeed=4.0`, `steerStopRadius=0.2`,
  `keyboardSecondaryMul=0.25` — speeds/damping/turn **APPROXIMATION** (no
  traced values); radii **INFERRED** (eat smaller / flee bigger).
- `SimEvent` — `frame`, `type` ∈ {"eat","flee"}, `entity`.

## 4. Per-frame `update()` — exact processing order

The order below IS the contract; reordering is a semantics change.

1. **Camera input**: if `hasCamera`, set `yaw/pitch/zoom`.
2. **Turn**: `left` → `heading -= turnRate·kDt`; `right` → `+=`.
3. **Mouse steering target** (OBSERVED: `MovePlayerToMousePosition`): if
   `hasMouse`, cast the camera view ray (origin = camera eye using the
   camera's target from the *end of the previous frame* — the follow update
   happens in step 9) against `MovementPlane`; on hit, `steer=true`, and if
   `dist(target, player) > steerStopRadius` and the hit is not vertically
   overhead (`dx²+dz² > 1e-12`), `heading = atan2(dx, dz)` (face travel).
4. **Flee check** (INFERRED from `Cell_mov_*` states): for each live `prey_*`
   with `dist² < fleeRadius²` (checked on the *pre-integration* position):
   `heading = atan2(player−prey, horizontal)` (face directly away),
   `boost=true`, emit `flee` event.
5. **Target velocity**:
   - speeds: `fwd=strate=steer` × (`boostMul` if boosting, else 1).
   - if `steer`: full `steerSpeed` toward the target point; keyboard keys add
     a **secondary** bias × `keyboardSecondaryMul` (keys never set the target
     — VERIFIED SDK: `OnMouseMove` primary, `OnKeyDown` secondary).
   - else (no mouse): keyboard thrust path — `forward` along heading,
     `back` against it, `left`/`right` strafe (`right=(fz,0,−fx)`).
   - if fleeing: **override** — straight ahead, boosted.
6. **Damp**: `k = min(1, damping·kDt)`; `vel += (targetVel − vel)·k`.
7. **Integrate**: `pos += vel·kDt`.
8. **Eat** (INFERRED from `Cell_eat_*`): for each live `food_*` with
   `dist² < eatRadius²` (post-integration position): `alive=false`,
   `growMeter += 1`, emit `eat` event.
9. **Camera follow**: `cam.target = player.pos`; `frame += 1`; record events.

`update` returns only *this frame's* events; the full log is `events()`.

## 5. Scenarios (the fixture set)

Defined once in `src/sim/tests/contract_scenarios.hpp`; the emitter and the
contract test both consume that list, so fixtures and replay agree by
construction. Order in the fixture file is part of the contract.

| # | name | behaviour pinned |
|---|---|---|
| 0 | `zero_input_stationary` | 30 empty frames, stage entities: player never moves; no events; `growMeter` stays 0 |
| 1 | `mouse_swim_toward_target` | cam pitch −0.3; 15 center-mouse frames (stationary), 45 frames NDC (0.5, 0): ray-plane target on +X; player swims +X on the swim plane |
| 2 | `eat_food_keyboard` | 20 frames thrust-right (turn toward `food_a`), 100 thrust-forward: `eat` fires, `growMeter→1`, `food_a` culled; `prey_c` untouched |
| 3 | `flee_from_prey` | `prey_test` at (0,0,−3) inside `fleeRadius`; 40 empty frames: `flee` events while inside the radius, player pushed +Z; flee stops once it escapes |
| 4 | `keyboard_only_fallback` | stage entities; 30 frames forward+boost (swim +Z), 30 back: final position short of origin; no events (both entities out of range) |

Stage entity layout (APPROXIMATION positions, parsed from
`src/apps/cell_stage.cpp`): `food_a` at (3.5, −1.5, 2.5); `prey_c` at
(1.5, −0.5, −5.0).

## 6. Oracle semantics

Per frame, the contract test compares the live replay against
`fixtures.json` **bit-exactly** (float32 via `%.9g` round-trip — no epsilon):

- `pos[3]`, `heading`, `vel[3]`, `growMeter` — exact.
- `events` — same count, same `(type, entity)` pairs, same order.
- `alive[]` — per-entity flags, entity order.

Plus two cross-cutting checks, per fixture: two fresh replays of the same
fixture produce identical `stateString()` and identical `events()` (the
determinism guarantee), and the fixture `contract` field equals
`cell-sim-contract/1` (bump ⇒ regenerate ⇒ commit together).

## 7. Change procedure

1. Change semantics in `src/sim/`.
2. Bump `kContractVersion` in `contract_scenarios.hpp` **and** this doc.
3. `python3 tools/gen_cell_fixtures.py --rebuild` (double-run, byte-identical
   required before write).
4. `ctest -R sim_contract_test` must pass; commit fixtures + doc + code
   together.

Any *non*-semantics change (comments, refactors) must leave the fixtures
byte-identical — the emitter's double-run check enforces this.

## 8. Provenance

- `tests/fixtures/cell/fixtures.json` — generated by
  `sim_test --emit-fixtures` (this tree, this toolchain); schema in
  `tests/fixtures/cell/README.md`.
- Movement evidence: `docs/analysis/dossiers/cell-movement.md`; stage recon:
  `docs/CELLSTAGE-RECON.md`.
