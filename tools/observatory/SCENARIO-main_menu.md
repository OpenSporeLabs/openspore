# SCENARIO-main_menu — launch → startup to first stable frame

Status: **done (Obj 6.1d, 2026-09-21)**. After a `wineserver -k`,
the game boots cleanly and the traced run captured **1004 events**
(entry → InitPlugins/Init/Startup → `IAppSystem::Get` capped at 1000).
A boot-stall pattern was found and worked around along the way (§6).

## Exact command

```sh
timeout -s KILL 120 python3 tools/observatory/observe.py main_menu --duration 30
# = probe_tracer --launch wine --launch-arg SPORE/SporeBin/SporeApp.exe \
#     probes/main_menu.json out/obs_main_menu.jsonl \
#     --duration 30 --module SporeApp.exe --wait-module 60
```

## Environment

- wine-11.17, Wine prefix `~/.wine` (pre-existing), `DISPLAY=:0` (existing X
  session — **not** headless, no Xvfb). `which Xvfb xdotool` → both absent, so
  **no synthetic input** was possible; the scenario is strictly
  "launch → observe startup for N seconds → terminate".
- Tracer: `tools/observatory/probe_tracer` rebuilt clean (`-Wall -Wextra`, zero
  warnings) with the preloader-drain fix (§4).
- Ghidra cross-check **not available**: the headless GhidraMCP server
  (`127.0.0.1:8089`) reports "No program loaded" and cannot open programs
  (`Opening programs requires GUI mode`). RVAs were verified with
  `objdump` + exe byte inspection instead (§3).

## What was observed

### A. Untraced oracle run (timestamped, game works fine)

`timeout -s KILL 35 stdbuf -o0 -e0 wine SPORE/SporeBin/SporeApp.exe` → 23 wine
stderr lines over a 30 s span; game ran the whole window, killed by timeout:

| +t | tid | event |
|----|-----|-------|
| +0s | 011c | 4× `NtSetInformationThread ThreadIdealProcessor` (thread-pool bring-up) |
| +1s | 011c | `NtQuerySystemInformation SYSTEM_PERFORMANCE_INFORMATION` |
| +1s | 011c | `d3d9:wined3dformat_from_d3dformat Unhandled D3DFORMAT 0x64` — **renderer bring-up** |
| +1s | 011c | 2× `NtGdiDdDDIOpenAdapterFromHdc stub` (display adapter open) |
| +1s | 011c | `wined3d_swapchain_resize_buffers ... holding back buffer` — **first present/resize** |
| +1s | 011c/0144 | thread stubs spread to tid 0144 (worker threads up) |
| +1s | 011c | `ImmDisableTextFrameService` (window/input init) |
| +1s | 0140 | `state_undefined UNKNOWN_STATE(0)` + `state_linepattern_w` (first draws) |
| +2s | 011c/0154 | steady-state thread stubs |
| +28s | 0170 | `CreateToolhelp32Snapshot`/`Heap32ListFirst` (late toolhelp query) |
| +30s | 011c | last stub before SIGKILL |

Read: main thread (011c) brings up D3D within ~1 s of spawn; workers (0140/0144/
0154/0170) appear over the first seconds. No menu interaction (none sent).

### B. Traced runs (4 attempts, attempts 1–2 = wedge-fix validation)

- Attempt 1 (preloader-drain fix): wedge **fixed** — lineage followed, game
  booted to the same d3d fixmes under trace, event loop ran 13.3 s.
  0 breakpoints: only the PE header page (`0x400000-0x401000 rw-p`) was mapped
  in the loader child when probed.
- Attempt 2 (+exec-mapping wait): game ran to renderer under trace
  (d3d/swapchain fixmes, thread exits). 0 breakpoints: PE code sections
  (`0x401000-0x13cc000 r-xp`) are mapped **anonymously in the game process**,
  not in the loader child. Discovered via orphaned game pid maps.
- Attempts 3–4 (+module-host discovery, +tree scan): `SporeApp.exe` never
  appeared in the traced tree within 60 s (exit 1, clean kill/reap). The wine
  stderr in the same runs shows the game DID boot (same d3d signature) — in a
  pid outside the traced lineage.

### C. Pipeline validation (m32 self-test, green)

`probe_tracer --launch ./test/m32target --launch-arg 400 test/probes_m32.json
out/obs_m32.jsonl --duration 3 --module m32target` → exit 0, **1801 events**;
`analyze.py --json`:

| function | count | first | tids |
|----------|------:|-------|------|
| main | 1 | 0 ns | 1 tid |
| beta | 800 | 86 µs | same tid |
| alpha | 1000 (+1 dropped at cap) | 118 µs | same tid |

Single-threaded, no rate spikes (steady ~5 ms cadence). The observe→analyze
pipeline works end to end; only the wine game target is blocked.

## Top functions / threads / SDK participation (game)

None captured — no probe fired (blocker §4). Intended read-upon-success:
per-function counts + first-seen order
(`entry → local_main → stateMachine → cAppSystem::{Init,Startup,InitPlugins}`,
`IAppSystem::Get` high-frequency across threads), thread histogram, 1 s-window
spikes. The m32 table above is the only measured sample and is **not** game data.

## 1. Probe RVA verification (found + fixed a real bug)

`objdump -p`: ImageBase `0x400000`, AddressOfEntryPoint `0xde11a0`;
all 7 values lie in `.text` (`0x401000-0x13cbf2a`). Byte inspection:

- `entry` was filed as `0xde11a0` (a file RVA); the tracer needs linked VAs,
  so it would have planted at absolute `0xde11a0` (mid-`.text`) instead of the
  true entry (absolute `0x11e11a0`, bytes `e8 … e9 …` call+jmp bootstrap).
  **Fixed to `0x11e11a0`.**
- The other six are absolute VAs and plant correctly: `IAppSystem::Get`
  `0x67dcc0` = bytes `a1 90 d8 5f 01 c3` (`mov eax,[0x15fd890]; ret`, the RECON
  singleton getter); `Init`/`Startup` show SEH prologues; `local_main`/
  `stateMachine` show valid prologues.
- `InitPlugins 0x7e93d0` (SDK slot) sits ~384 B inside the init body (nearest
  prologue-like boundary `0x7e9250) but is instruction-aligned → kept, noted.

## 4. Blocker (wine game process escapes the traced lineage)

> RESOLVED in Obj 6.1d (2026-09-21): the attached-set scan finds the reparented
> game pid — launch 6 captured 1004 events (see §6–§7). Below kept as history.

`wine SporeApp.exe` → root child execs `start.exe /exec`, which spawns the
game **reparented to PID 1/systemd** (observed untraced: game PPID = 845 =
`systemd --user` while `start.exe /exec` is still alive). Under
`yama ptrace_scope=1` the tracer can only touch descendants, and the
ppid-walk tree scan finds only the root child — so the module never maps and
the run exits 1 after `--wait-module`. Promising next lead (not tried, attempt
budget exhausted): fork/clone events survive reparenting, so scan the
**attached-set pids'** maps instead of (or in addition to) the ppid tree —
the game pid should already be in `attached` via `PTRACE_EVENT_FORK`.
Alternative: bypass `start.exe` (launch with an absolute `Z:` path or
`wine start /unix …` variants) so the game stays a direct child.

## 5. Explicit next scenario

`menu → galaxy transition with synthetic input`: needs (a) the unblock above,
(b) an automation layer (`xdotool` on this X session, or Xvfb + `xte` —
neither installed; do NOT install without asking), (c) probes in
`probes/menu_transition.json` (8 targets, Ghidra/SDK-sourced, byte-checked,
**defined but never run**). Suggested flow: boot → wait for first
present (swapchain-resize fixme) → send one click/key → capture 20 s →
`analyze.py --json`. Keep `--max-events` tight on `HandleMessage`/`Update`
(per-frame fire rate).

## 6. Boot-stall investigation (2026-09-21, 6-launch budget — all used)

Environment re-check: `DISPLAY=:0` present (Xwayland :0, Plasma/Wayland
session), AMD RX 7900 XTX + direct rendering — display available, same as the
known-good baseline. `which Xvfb xdotool` → both still absent. No missing
display; suspect #1 ruled out.

Stale wineserver ruled IN as the stall trigger. Observed pattern:

| # | variant | result |
|---|---------|--------|
| 1 | untraced, after `wineserver -k` (killed stale 10:51 `wineserver`+services) | **boots**: 23-line d3d signature identical to §A, multi-thread, CPU-active |
| 2 | traced `observe.py main_menu --duration 30` (same wineserver gen) | 7/7 planted, 33.7 s loop, **0 traps** — game mapped module + d3d DLLs but never reached `entry`; post-detach: 1 thread, 0 CPU, `ntsync_schedule` |
| 3 | untraced, same wineserver | **silent exit <20 s, zero stderr** |
| 4 | untraced `WINEDEBUG=+loaddll` | loader loads full DLL set (last: `d3d9.dll` on tid 0140), then frozen: 1 thread, 0 CPU, `ntsync_schedule`, no renderer fixmes |
| 5 | untraced, after 2nd `wineserver -k` | **boots**: full d3d signature, 28 % CPU |
| 6 | traced `observe.py main_menu --duration 30` (fresh wineserver) | **1004 events** (see §7) |

Rule of thumb: **first boot after `wineserver -k` works (launches 1, 5);
later boots on the same wineserver generation stall** (single-threaded
`ntsync_schedule` before renderer bring-up) **or exit silently** (launches
2–4). SIGKILL-terminated sessions (`timeout -s KILL`) appear to leave
wineserver-side sync state behind that blocks re-init. Workaround: `wineserver
-k` before any game run (traced or not). No sudo needed (plain `kill` on own
PIDs + `wineserver -k` suffice). `/proc/<pid>/stack` was unreadable only
because the pid had already exited (silent-exit case), not EACCES.

## 7. Obj 6.1d traced capture (launch 6, fresh wineserver)

`timeout -s KILL 120 python3 tools/observatory/observe.py main_menu
--duration 30` → module host pid 120690 via attached-set discovery, 7/7
breakpoints, 33.2 s event loop, **1004 events / 1005 traps**, single thread
(tid 120690). Full JSONL: `out/obs_main_menu.jsonl` (git-ignored, 247 KB);
trimmed 150-event copy: `examples/obs_main_menu_example.jsonl` (37 KB).

| function | count | first | note |
|----------|------:|-------|------|
| entry | 1 | 0 ns | probe RVA correct, game reached it |
| App::cAppSystem::InitPlugins | 1 | 503.766 ms | |
| App::cAppSystem::Init | 1 | 503.802 ms | ~36 µs after InitPlugins |
| App::cAppSystem::Startup | 1 | 543.544 ms | |
| App::IAppSystem::Get | 1000 (+1 dropped at cap) | 519.524 ms | min-ival 22 µs, med 27.9 µs — hot singleton getter as predicted |
| App::Bootstrap::local_main | 0 | — | not reached in 30 s window |
| App::Bootstrap::stateMachine | 0 | — | not reached in 30 s window |

Rate spikes: `[1s-2s): 178 events (13.7x)`, `[4s-5s): 235 events (235x)` —
`IAppSystem::Get` bursts after Startup. `this` parameter captured
(`ecx=0x0285eeb8` on Init/InitPlugins) for future `this`-typing work.
