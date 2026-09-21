# OpenSpore — Development Journal

This is a chronological, first-person-plural engineering journal of how OpenSpore is
being built: a from-scratch C++17 reimplementation of *Spore* 3.1.0.22 (GOG digital
build, no DRM) driven by a fully AI pipeline. Each chapter is dated and grounded in
the repository at the moment it describes — commits, files, measured values. It reads
as a mix of reverse-engineering research diary, development log, clean-room record,
and architecture-evolution log. Failures, dead ends, and environmental ceilings are
documented alongside wins; claims are labeled by evidence strength (observed /
measured / verified / hypothesized) rather than asserted.

## What OpenSpore is trying to achieve

A clean-room reimplementation of the *Spore* base game: logic separated from data,
no proprietary code or assets in this repository, and differential verification
against the original executable under Wine as the oracle. The endpoint is a
**semantic reimplementation** — independent code that exhibits the same observable
behavior — not a decompilation, not source translation, and not a binary clone.
Offsets, formats, and architecture findings are recorded; EA source and asset bytes
are not reproduced.

## Methodology

Three pillars share context across tools:

- **Ghidra (MCP, headless)** — the analysis graph: functions, SDK-imported symbols,
  structures, xrefs, decompilation of `SporeApp.exe`.
- **codegraph (MCP)** — the source graph: a pre-built index of this C++ repo.
- **SQLite sidecar** (`knowledgegraph/spore.db` + `kg.py`) — shared memory for
  cross-tool results: test outcomes, decisions, format mappings.

Clean-room and evidence rules:

- Vocabulary is strict: *Observed / Measured / Verified / Supported by / We
  hypothesize / This remains unknown / The current implementation assumes.*
- GPL projects (Spore-ModAPI, SporeModder-FX) are **semantics-only references** —
  never code. No proprietary assets, no decompiled EA source, GOG build only.

Working loop: **observe the original → understand bounded behavior → implement
independently → compare → replace incrementally → repeat.** We observe first and
interpret second: raw traces are captured, then analyzed offline.

## Current phase

**Phase: incremental reimplementation** (started 2026-09-21, chapter
[010](010-phase-transition.md)).

The RE foundation (chapters [000](000-project-origin.md)–[009](009-wine-reparenting.md))
is complete: format parsers validated on real assets; 15 deterministic tests; vtable
anchors (3,081 candidates, 369 high-confidence, 20 labeled); a working runtime
observatory; and the first real *Spore* trace captured — 1,004 events over a 33.2 s
main-menu window. The first C++ code is committed: the Obj 7 Vulkan renderer
skeleton (chapter [011](011-vulkan-skeleton.md)) with a green offscreen-triangle
smoke test.

**Next: Obj 8** — the first real *Spore* asset through the full pipeline:
DBPF → RW4/GMDL → mesh → Vulkan (roadmap: chapter [012](012-roadmap.md)).

## Where are we now?

It is worth stating the pace plainly: the entire foundation above happened in two
days, 2026-09-20 to 2026-09-21. Eleven chapters of RE and tooling — from repository
audit to the first traced 1,004-event game trace to the first compiling, tested
C++ renderer — landed between a morning scaffolding commit and a mid-morning
Vulkan commit the next day. The journal currently ends at the Vulkan triangle.

One caveat for future readers: `docs/STATE.md` is stale. Its last update stopped at
the RenderWare research step (commit 36e704a, 2026-09-20), and its "Next step:
Phase 1 — Foundation" plan is superseded by the incremental-reimplementation model.
Refreshing it operationally is Obj 11 on the roadmap — planned, not done. This index
is the current source of truth for state.

## Chapters

| # | Chapter | Date | Objective | Status |
|---|---------|------|-----------|--------|
| 000 | [Project origin](000-project-origin.md) | 2026-09-20 | The original plan (`OpenSpore.md`), clean-room legal basis, bootstrap commit, plan vs. reality | Done |
| 001 | [Repository audit](001-repository-audit.md) | 2026-09-20 | Audit the fresh repository: layout, ignores, agent rules | Done |
| 002 | [Ghidra foundation](002-ghidra-foundation.md) | 2026-09-20 | Repair the import (defensive SDK script, corrupt project rebuild), full binary recon | Done |
| 003 | [RenderWare research](003-renderware-research.md) | 2026-09-20 | RW3/RW4/gmdl/D3DX findings, license landscape, knowledge-graph entries | Done |
| 004 | [Format tooling](004-format-tooling.md) | 2026-09-20 | Promote DBPF/RW4/GMDL parsers into `tools/` and validate on real assets | Done |
| 005 | [Deterministic tests](005-deterministic-tests.md) | 2026-09-20 | 15 synthetic tests, deterministic fixtures, opt-in differential harness | Done |
| 006 | [Vtable detection](006-vtable-detection.md) | 2026-09-21 | Headless vtable pass: 3,081 candidates, 369 high, 20 labeled anchors | Done |
| 007 | [Runtime observatory](007-runtime-observatory.md) | 2026-09-21 | Self-contained ptrace tracer: design, m32 self-test, bugs found and fixed | Done |
| 008 | [First runtime scenario](008-first-runtime-scenario.md) | 2026-09-21 | Launch the real game under trace: boot timeline, oracle run, the RVA probe bug | Done |
| 009 | [Wine reparenting](009-wine-reparenting.md) | 2026-09-21 | Attached-set discovery fix, wineserver boot-stall rule, the 1,004-event capture | Done |
| 010 | [Phase transition](010-phase-transition.md) | 2026-09-21 | From RE foundation to incremental reimplementation; the guiding model | Done |
| 011 | [Vulkan skeleton](011-vulkan-skeleton.md) | 2026-09-21 | First C++: IRenderer, Vulkan backend, offscreen triangle, green smoke test | Done |
| 012 | [Roadmap](012-roadmap.md) | 2026-09-21 | Obj 8–12 as *planned* work: first real asset end-to-end, replacement boundaries, final verification | Planned |

## Maintenance protocol

For future OpenSpore agents, when a major objective finishes:

1. Read this index.
2. Inspect the actual changes and the git history for the objective's commit(s).
3. Create or update the corresponding chapter from that evidence.
4. Document verified facts and remaining uncertainty separately (use the evidence
   vocabulary above; never present reasoning as evidence).
5. Update the "Current phase" and "Where are we now?" sections.
6. Link the relevant commit(s) by SHA.
7. Never invent future results — planned work stays in chapter
   [012](012-roadmap.md) as *planned*.

No automation framework: this convention is the whole protocol.
