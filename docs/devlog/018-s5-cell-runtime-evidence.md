# 018 — S5: Real Cell runtime evidence

Date: 2026-09-22. Status: **Done (NEGATIVE — no Cell-Stage evidence; blocker is boot-stability).**
Predecessor: chapter [017](017-s4-x11-input-feasibility.md) (S4). This chapter records S5
only. It does not promote Cell evidence, does not run S6, and does not modify the canonical
contract. The full S5 evidence package (dossier runtime section, committed keyframes,
`trace_run` rows) was **not** built — per the close-out decision, this finding is recorded
in the devlog only.

## Objective

S5 was to drive the original `SporeApp.exe` to Cell Stage on a real `:0` display and capture
the 12 byte-verified `probes/cell_movement.json` probes across three independent, human-approved,
human-watched runs. The game is launched **through** `probe_tracer --launch` so the walk and the
trace land on the same traced process. A recorded negative is a first-class deliverable.

New committed surface (S3-verified allowlist + overlay + lock reused; **no** new GUI capability):
`tools/observatory/cell_trace.sh` + `tests/test_cell_trace.py` (full Python suite **407/407 OK**;
C++ `ctest` **10/10** unchanged). The walk uses the S4-approved focused-window path
(`xdotool windowactivate --sync $WIN` + `key --clearmodifiers <key>`), allowlist
`Return Escape Up Down Left Right` only, a bounded `Down`/`Return` registration-probe, a
per-step no-op ladder, the AGENT DRIVING overlay + `Ctrl+Alt+Backspace` stop key, and the
shared `lock.py` machine lock.

## The three runs (human-watched on `:0`, `OPENSPORE_MCP_TRUSTED=1` approved)

Binary identity (all runs): `SporeApp.exe` SHA256
`25d42a7a5c438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, PE ImageBase `0x400000`;
Wine 11.17, `:0`, pinned geometry `2304x1296+2561+144`.

- **Run #1** `S5-20260922T212936Z-396838` — **booted** (the operator saw the window come up).
  The D3D renderer initialized (`fixme:d3d:wined3d_swapchain_resize_buffers` in `wine_stderr.log`).
  The registration/menu screen rendered and the operator's input reached it: 9 `maim` shots at the
  pinned geometry, **every one `delta_vs_prev_sha:true`** (`Return` → registration probe 1/2/3 →
  `Down` → `Return` → `Down` → `Return` → `settle`). The `entry` bootstrap control fired once
  (`obs_cell_movement.jsonl` = 1 line). Then the whole process tree **self-exited (clean `status 0`)**
  ~12.7 s into the trace. Manifest: `cell_stage_reached=menu_only`; all 11 cell-stage probes `recorded=0`.
- **Run #2** `S5-20260922T213524Z-397779` — **did not boot** (the operator saw nothing appear).
  `STOP: window-not-found` (exit 6). The process tree exited cleanly ~86 s before any window mapped;
  `obs_cell_movement.jsonl` 0 lines, no shots, no manifest.
- **Run #3** `S5-20260922T214226Z-399437` — **did not boot**, identical mode to run #2. Self-exited
  ~86.6 s before a window; 0 events; 0 shots; `entry` control 0.

Corroborating artifact: `tools/observatory/out/obs_main_menu.jsonl` is **empty (0 lines)** —
`probe_tracer` has never captured a single `SporeApp.exe` event in this environment.
(`obs_m32.jsonl` is a separate 32-bit test binary at `0x566…`, not `SporeApp`.)

## Finding

**Cell Stage was not reached in any run, and no cell-stage events were recorded.** All 11
cell-stage probes read `recorded=0` across every run; only the `entry` bootstrap control fired,
and only in run #1. The blocker is **not** the menu-walk key plan — input demonstrably reached the
game in run #1 (the screen changed on every step). The blocker is that the GOG `SporeApp.exe`
**self-exits under Wine 11.17**: it rendered once (run #1, briefly) and in the other two runs
exited cleanly before any window appeared.

**Hypothesized, not verified:** the clean `status 0` exit under a `d3d9`-on-OpenGL renderer, with
the logged D3D errors (`wined3d_swapchain_resize_buffers: Something's still holding back buffer 0`,
`state_undefined: UNKNOWN_STATE(0)`, `d3dkmt:NtGdiDdDDIOpenAdapterFromHdc … stub`), is consistent
with the GOG build's registration/license gate plus renderer init completing and then exiting. The
exact exit trigger is **not established — this remains unknown.** A read-only Wine/render/registration
diagnostic is the subject of a separate, properly-scoped investigation (not S5, not a GUI-surface
change).

## Teardown and limits

Machine lock released and re-probed `machine_locked=false` after every run; no stale
`SporeApp`/`wineserver` processes remained. No proprietary bytes were added. The physical
`Ctrl+Alt+Backspace` stop key was not pressed in any run (no stop-state was needed).

## What was NOT done

No `status_update`, no evidence promotion, no S6, no canonical-contract change.
`cell-movement-mouse-steering` remains at its current evidence level (INFERRED / APPROXIMATION —
documented, not fabricated). Until `SporeApp.exe` sustains a window under Wine, Cell Stage is
unreachable and the sim stays INFERRED/APPROXIMATION.
