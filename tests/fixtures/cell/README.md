# Cell contract fixtures (Obj35)

Frozen oracle inputs/outputs for the canonical Cell simulation contract,
`cell-sim-contract/1` (see `docs/CELL-CONTRACT.md`).

## Provenance

`fixtures.json` is generated, never hand-edited:

```
python3 tools/gen_cell_fixtures.py --rebuild
```

The generator runs the C++ emitter (`sim_test --emit-fixtures`) twice and
requires byte-identical output before writing. The "expected" values are
exactly what the current `CellSim` (this tree, this toolchain) produces.

## Consumers

- `src/sim/tests/sim_contract_test.cpp` — CTest `sim_contract_test`: replays
  every fixture through a fresh `CellSim` and asserts the per-frame oracle
  **bit-exactly** (float32).
- Obj36 differential testing — the original game under Wine is the oracle to
  diff against; these fixtures pin what our sim must produce.

## JSON schema

Top level:

| field      | type   | meaning                                                    |
| ---------- | ------ | ---------------------------------------------------------- |
| `contract` | string | pinned contract version (`cell-sim-contract/1`)            |
| `dt`       | number | fixed timestep (1/60 s)                                     |
| `floats`   | string | float policy note                                           |
| `params`   | string | movement params policy note                                 |
| `scenarios`| array  | one entry per scenario, in the defined order                |

Per scenario:

| field        | type   | meaning                                                    |
| ------------ | ------ | ---------------------------------------------------------- |
| `name`       | string | scenario id (matches `contract_scenarios.hpp` order)       |
| `description`| string | human description of the behaviour under test              |
| `entities`   | array  | `{ "role": string, "pos": [x,y,z] }` in entity order       |
| `camera`     | object | `{ yaw, pitch, zoom, baseDist, fov }` before frame 0       |
| `plane`      | object | `{ "normal": [x,y,z], "point": [x,y,z] }` movement plane   |
| `frames`     | array  | ordered input frames (one `update()` per entry)            |
| `expected`   | object | `{ "frames": [...] }` — one entry per input frame          |

Per input frame:

| field    | type   | meaning                                                    |
| -------- | ------ | ---------------------------------------------------------- |
| `keys`   | array  | any of `left`, `right`, `forward`, `back`, `boost`          |
| `camera` | object | `{ yaw, pitch, zoom }` when the frame overrides the camera |
| `mouse`  | array  | `[ndcX, ndcY]` in `[-1,1]` when the frame uses the mouse   |

Per expected frame (the oracle, after that `update()` call):

| field       | type   | meaning                                                    |
| ----------- | ------ | ---------------------------------------------------------- |
| `pos`       | array  | player position `[x,y,z]`                                  |
| `heading`   | number | player heading angle                                       |
| `vel`       | array  | player velocity `[x,y,z]`                                  |
| `growMeter` | number | integer grow meter                                         |
| `events`    | array  | `["type", "entity"]` pairs this frame, in fire order       |
| `alive`     | array  | per-entity alive flags, in entity order                    |

## Float policy

All numbers are `%.9g` decimal — 9 significant digits round-trip binary32
exactly, so the contract test's `strtof`-equivalent parse recovers the
emitted bits. Comparison in `sim_contract_test` is therefore bit-exact, not
epsilon.

## Regenerating after a contract change

1. Make the semantics change in `src/sim/`.
2. Bump `kContractVersion` in `contract_scenarios.hpp` (and the doc).
3. `python3 tools/gen_cell_fixtures.py --rebuild`
4. `ctest -R sim_contract_test` must pass; commit fixtures + doc together.
