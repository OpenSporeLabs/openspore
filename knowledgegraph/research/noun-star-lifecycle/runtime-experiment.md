# Noun/Star Root Lifecycle Runtime Experiment

**Date:** 2026-09-24  
**Scope:** One narrowly scoped, no-input runtime attempt for the four noun/star root words at manager initialization, noun/star materialization, mode transition, and teardown boundaries.  
**Result:** `NOT_OBSERVED` — the module mapped and all breakpoints were active, but the traced process tree exited before any target boundary event produced a sample.

## 1. Safety and command boundary

The experiment used the existing repository runtime tooling:

- `tools/observatory/lock.py` for the shared machine lock;
- `tools/observatory/probe_tracer` for Wine launch, module discovery, temporary `INT3` breakpoints, event capture, and restoration;
- `tools/observatory/analyze.py` for the read-only JSONL summary;
- read-only Ghidra queries against the already-open `SporeApp.exe` program for address and body preflight.

The command used a temporary `WINEPREFIX` at `/tmp/openspore-noun-star-lifecycle/wineprefix`, sent no input, and did not use `cell_trace.sh`, gameplay navigation, message injection, save/load, replacement, or executable modification. It did not write `SPORE/` or the canonical executable. The tracer's existing process-local breakpoint mechanism temporarily wrote 16 `INT3` bytes and restored all 16 on detach; this is the repository's documented read-only-runtime exception, not persistent target modification.

The sampler itself was a GDB command file used only to call the existing tracer process's `/proc/<pid>/mem` read path at the tracer's event-write line. It did not write target memory. The sibling-process alternative was rejected because this host has Yama `ptrace_scope=1`; the GDB-in-tracer path was validated against the repository's native 32-bit fixture before the game attempt.

The exact game command was:

```text
WINEPREFIX=/tmp/openspore-noun-star-lifecycle/wineprefix \
python3 tools/observatory/lock.py acquire noun-star-lifecycle \
  --task-id noun-star-lifecycle-runtime -- \
  gdb -q -batch -x /tmp/openspore-noun-star-lifecycle/root-sampler.gdb \
  --args tools/observatory/probe_tracer \
  --launch wine --launch-arg SPORE/SporeBin/SporeApp.exe \
  /tmp/openspore-noun-star-lifecycle/probes.json \
  /tmp/openspore-noun-star-lifecycle/events.jsonl \
  --duration 30 --wait-module 60 --module SporeApp.exe \
  --max-bps 32 --max-events 32
```

No `wineserver -k` was issued. After the attempt, only processes verified to belong to the temporary `WINEPREFIX` were terminated; the unrelated Proton Wine server was left untouched.

## 2. Static preflight evidence

Fresh read-only Ghidra inspection confirmed the intended addresses and lifecycle surfaces:

| Boundary | Static address | Static role |
|---|---:|---|
| Alternate noun root accessor | `0x00b3d300` | raw load of `DAT_0167eae0`, then `RET` |
| Canonical noun root accessor | `0x00b3d400` | raw load of `DAT_0167eb60`, then `RET` |
| Alternate star root accessor | `0x00b3d2a0` | raw load of `DAT_0167eae4`, then `RET` |
| Canonical star root accessor | `0x00b3d3a0` | raw load of `DAT_0167eb0c`, then `RET` |
| Manager initialization | `0x00b60d80` | contains noun-manager construction followed by star-manager construction |
| Noun manager constructor | `0x00b232b0` | constructs the noun-manager-shaped object |
| Noun instance materialization | `0x00b20c60` | eager concrete noun allocation and manager publication |
| Noun typed-view materialization | `0x00b21340` | lower-bound lookup and cached manager-local vector materialization |
| Star manager constructor | `0x00bae490` | constructs the star-manager-shaped object |
| Star-record materialization | `0x00bb5d80` | generated star-record path and grid publication |
| Star/planet materialization | `0x00bb1560` | record-to-planet materialization path |
| Mode transition helper | `0x007d85b0` | old-mode exit, active-index write, exit announcement, new-mode enter, enter announcement |
| Noun-manager teardown | `0x00b22440` | manager-local field and map teardown |
| Star-manager teardown | `0x00babe70` | manager-local star/empire field teardown |
| Space cache teardown | `0x01022460` | current-player cache clear/reset path |

These static facts are decisive only for the existence and local mechanics of the listed functions and for the physical distinction of the four root words. They do not prove a publisher, value equality, phase identity, or liveness. The static reports already preserve those unresolved questions: `track-a-root-identity.md:95-106,128-173,263-283` and `track-f-lifecycle-ordering.md:72-147,293-348`.

The runtime sampler would have read the four words at these runtime addresses:

```text
module_base + 0x0127eae0   DAT_0167eae0  alternate noun
module_base + 0x0127eb60   DAT_0167eb60  canonical noun
module_base + 0x0127eae4   DAT_0167eae4  alternate star
module_base + 0x0127eb0c   DAT_0167eb0c  canonical star
```

The sampler did not dereference any returned value and did not treat a non-null word as a validated object.

## 3. Runtime evidence

### Attempt outcome

The repository logger recorded:

- `SporeApp.exe` module base: `0x400000`;
- module host PID: `903531`, with header `0x400000` and anonymous executable code `0x401000-0x13cc000`;
- all 16 selected probes resolved into executable memory;
- all 16 probes were active;
- the raw event file was empty: zero events and zero root samples;
- traced Wine processes then exited with status `0`, while the GDB inferior ended with status `3` after the bounded tracer path ended.

The relevant raw log is `/tmp/openspore-noun-star-lifecycle/gdb-run.log`; the raw event file is `/tmp/openspore-noun-star-lifecycle/events.jsonl`. These are temporary experiment artifacts, not shared final artifacts.

### Samples by requested boundary

| Boundary | Runtime events | Four-word samples | Interpretation |
|---|---:|---:|---|
| Manager initialization | 0 | 0 | Not observed |
| Noun instance/view materialization | 0 | 0 | Not observed |
| Star record/planet materialization | 0 | 0 | Not observed |
| Mode transition | 0 | 0 | Not observed |
| Manager/cache teardown | 0 | 0 | Not observed |
| Root getter boundaries | 0 | 0 | Not observed |

There is therefore no runtime value for any of the four roots from this attempt, and no runtime equality, inequality, publication, replacement, unpublication, or liveness result. The correct report is **not observed in this bounded attempt**, not “the roots are equal,” “the roots are unequal,” “the roots are null,” or “the roots are dead.”

## 4. Decisiveness

### Decisive for this attempt

- The environment reached the mapped `SporeApp.exe` module host.
- The 16-function probe set was installed and active.
- No selected manager, materialization, mode-transition, teardown, or root-getter event was observed before the traced process tree exited.
- The experiment produced no synchronized four-word snapshot.

### Not decisive for the original lifecycle

- It does not establish absence of a publisher or writer.
- It does not establish absence or presence of root equality.
- It does not establish whether a root is published, live, stale, replaced, or cleared.
- It does not establish any global teardown order.
- It does not generalize to another Wine generation, profile, mode, or save state.
- A module-mapped/zero-event result is an environment/reachability negative, not a gameplay negative.

The existing observatory limitations and the required memory-sampling distinction are consistent with `tools/observatory/README.md:43-56,167-176`, `docs/analysis/runtime-experiments.md:123-173`, and `knowledgegraph/research/noun-star-lifecycle/track-g-edge-cases.md:293-302,420-428`.

## 5. Cleanup and integrity

- Experiment-owned temporary Wine processes were terminated after identifying `WINEPREFIX=/tmp/openspore-noun-star-lifecycle/wineprefix`.
- The machine lock returned `machine_locked=false`.
- `SPORE/SporeBin/SporeApp.exe` remained SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.
- No `SPORE/` file, original executable, shared knowledge-graph file, or unrelated service was modified.

**Final classification:** runtime question unresolved. The one permitted attempt was blocked before any target boundary event; only the static four-slot/accessor facts remain decisive.
