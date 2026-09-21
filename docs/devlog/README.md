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
smoke test, then the Obj 8 first real asset through the full pipeline
(DBPF → RW4/GMDL → mesh → Vulkan).

Since then the journal covers the Cell Stage sprint (chapter
[013](013-cell-stage-slice.md)): Obj 13–18 — repo sanitation, cell-stage recon
(BE refCount, DXT5 envelope, PNG32=RW4), materials/textures, the cell scene, a
deterministic sim with eat/flee, a live SDL3+Vulkan window at 60 fps, and
differential validation. The project now presents an **interactive,
keyboard-driven Cell Stage** built entirely from clean-room-decoded game assets.

**Next: second vertical slice** — creature-creator block assembly (sporemol XML →
block gmdl placement) or a cell-mode runtime trace via Xvfb; plus resolving
player-cell identity (`docs/STATE.md` §6).

## Where are we now?

It is worth stating the pace plainly: everything from repository scaffolding to the
first live game window happened across two days, 2026-09-20 to 2026-09-21. The Cell
Stage sprint alone — sanitation, recon, materials/textures, scene, deterministic sim,
live window, validation — landed between 12:05 and 18:41 on 09-21 (six commits,
`e0d6230` → `b939cb7`). The journal currently ends at the interactive cell window
(chapter [013](013-cell-stage-slice.md)).

Note for future readers: `docs/STATE.md` was refreshed operationally (Obj 11,
`460b599`, and again this sprint) and now tracks the same state as this index.
Chapters [006](006-vtable-detection.md)–[012](012-roadmap.md) are referenced in the
index below but not yet written to disk — do not create those numbers; the next free
chapter is 013.

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
| 013 | [Cell stage slice](013-cell-stage-slice.md) | 2026-09-21 | Obj 13–18: sanitation, cell-stage recon (BE refCount, DXT5 envelope, PNG32=RW4), materials/textures, cell scene, deterministic sim + eat, live window, differential validation | Done |

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
