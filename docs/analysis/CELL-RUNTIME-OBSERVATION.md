# CELL-RUNTIME-OBSERVATION — Objective 32 / 32A (2026-09-21)

Clean-room ptrace observation of the **cell-stage movement** functions, run headless
under Wine via `tools/observatory`. Companion to `docs/analysis/dossiers/cell-movement.md`
(whose runtime column was "NOT OBTAINED"). All evidence below is from this session; no
proprietary code or assets were used.

## 1. Environment diagnosis (saved: /tmp/opencode/cell-runtime-env.txt)

| Item | State |
|---|---|
| Xvfb / xvfb-run / xdotool | **ABSENT** (per rules: not installed) |
| `DISPLAY` | `:0` — reachable real X.Org 24.1.13 (XWayland), socket `/tmp/.X11-unix/X0` |
| Wine | `wine-11.17` |
| Session | Wayland (`Display=4`), active |

Consequence: the game can open a window on `:0`, but **no synthetic input is possible**
(no xdotool, no Xvfb test display), so the game cannot be driven past the main menu into
the cell stage.

## 2. Address-mapping verification (the critical arithmetic)

The dossier/snapshot RVA column does **not** equal a PE file RVA. Verified mapping:

- PE `ImageBase = 0x400000` (`objdump -h`: `.text` VMA 0x401000 / file off 0x400).
- The raw vtable at linked `0x1485550` (file off 0x1084950, `.rdata`) contains entries
  equal to the SDK XML addresses (Update=0xe80980, OnKeyDown=0xe818f0, OnMouseMove=0xe51010,
  OnMouseWheel=0xe7d660, …). Decompiled headers read `@ 0x00e806b0` / `@ 0x006ffe00`.
- Therefore **Ghidra project image base = 0x400000**, and every function's "address" is a
  PE-linked VA. The snapshot note claiming `image_base 0x01100000` / `RVA = address - image_base`
  is a documentation bug: its `rva` field is `address - 0x100000`, which is arithmetically
  inconsistent with 0x01100000 (it would go negative). **Probe `rva` = snapshot `address`
  field = dossier RVA + 0x100000.**

Each of the 11 cell probes was byte-verified at `file_off = linked - 0x400C00` in
`SPORE/SporeBin/SporeApp.exe` (GOG 3.1.0.22): all sit at clean, instruction-aligned
prologues. Three match decompiled dossier semantics byte-for-byte:
`MovePlayerToMousePosition` (`mov eax,[0x116b3c04]` = sCellGame; `cmp [eax+0x5158],0` =
+20824 lock flag), `cell_per_frame_FUN_00e5b2e0` (`mov edx,[eax+0x411C]` = +16668 player
ref), `cam_light_origin_FUN_007c4900` (`call 0x7c4730` = the decompiled callee).

Probe file: `tools/observatory/probes/cell_movement.json` (12 probes, `image_base 0x400000`).

## 3. Runs (all `observe.py cell_movement --duration 40`, fresh `wineserver -k` each)

| Run | Reached renderer? | Events | Notes |
|---|---|---|---|
| 1 (clean env, 18:55) | **Yes** (21 fixmes, 6 d3d lines) | **227** | entry ×1; `face_travel_orient_FUN_0069b600` ×226 |
| 2, 3, 4 | No (0 fixmes, 0 d3d) | 0 | boot stalled before D3D init |
| 5–8 (recapture) | No | 0 | same stall |
| 9 (final) | No (module attached, 12 probes planted) | 0 | same stall |

**Run 1 detail** (the only boot that reached the menu):

```
function                            count   first     min-ival   med-ival  tids
face_travel_orient_FUN_0069b600      226    18.173s   32.103ms   33.101ms  211718
entry (bootstrap control)              1     0ns       -          -         211718
```
Single thread; rate spike `[18-19s): 25 events`; 30 Hz frame loop (33 ms median).

**All 10 cell-stage probes: 0 events in every run** — including run 1, where the main
menu was rendering. Cell stage was never entered.

## 4. Findings

1. **Cell-stage movement is UNREACHABLE headless.** Even when the main menu rendered
   (run 1), zero cell functions fired. There is no synthetic-input path (Xvfb/xdotool
   absent), so the game cannot be driven from menu → cell stage.
2. **`FUN_0069b600` is a GENERIC per-frame function, not cell-specific.** It fires at
   30 Hz on the main menu. The dossier lists it as the "face-travel orientation" callee
   of `MovePlayerToMousePosition`, but it is evidently shared with the menu/camera
   frame loop. Do NOT use it as a cell-mode marker.
3. **`entry` fires exactly once at startup** (consistent with `SCENARIO-main_menu.md`).

## 5. Reproducibility classification

- **Boot stall (no renderer, 0 events): STABLE / env-dominant** — 8/9 runs. Wine 11.17
  under XWayland `:0` stalls before D3D init on most boots (matches the documented
  `ntsync_schedule` boot-stall and the "only first boot reaches the renderer" caveat).
- **Menu render loop (30 Hz per-frame call): ENV-DEPENDENT** — observed once (run 1),
  not reproduced in 8 later boots.
- **Cell-stage probes = 0: STABLE** — zero in all 9 runs; this is the reliable negative
  result (cell stage not entered).

## 6. Exact blocker & smallest next steps

Blocker: (a) Wine boot stall prevents reliable menu capture; (b) even with the menu up,
no input-injection tool exists to reach the cell stage.

Smallest next steps (need operator, not doable headless here):
1. Fix the Wine boot stall for a repeatable main-menu capture (real display, warm X
   session, or `WINEDLLOVERRIDES`/timing tweak) so the 30 Hz loop is reproducible.
2. Provide a real/Xvfb display **plus** synthetic input (e.g. `xdotool`) and the exact
   menu path to the cell stage, then re-run this same probe set. The 11 byte-verified
   cell probes are ready; they will fire the moment the cell stage is entered.

## Artifacts
- Probe set: `tools/observatory/probes/cell_movement.json`
- Run logs: `/tmp/opencode/cell-obs-run{1,2,3,4}.log`, `cell-obs-recapture{1..4}.log`, `cell-obs-final.log`
- Env diagnosis: `/tmp/opencode/cell-runtime-env.txt`
