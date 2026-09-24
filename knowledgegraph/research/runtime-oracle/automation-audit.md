# Automation audit — runtime oracle

**Audit date:** 2026-09-24  
**Status:** complete as a read-only source/artifact audit  
**Scope:** GUI automation, original-process tracing, runtime launch paths, host harnesses, MCP runtime tools, build/test configuration, and relevant documentation.  
**Actions not performed:** no Wine/game launch, no X11 input, no tracer run, no process or memory inspection, and no build. No tracked file, canonical KG, `SPORE/`, or executable was modified. The only write was this audit file.

## Evidence labels

- **VERIFIED NOW** — directly inspected current source, read a current local artifact, or covered by the focused tests run for this audit.
- **HISTORICAL EVIDENCE** — recorded by an earlier run/devlog/example artifact; not reproduced in this audit.
- **PROPOSAL** — recommended work that is not implemented or verified.

## Executive conclusion

The repository has several deterministic, unattended layers: shell dry-runs, fixed key validation, pure registration/manifest decisions, the `flock` primitive, trace analysis, frozen host-side simulation tests, and a native 32-bit tracer self-test path. These are real controls, but they do not compose into a deterministic unattended original-game Cell oracle.

The original-game path remains blocked before its target stage. Historical S5 evidence shows one brief registration/menu render, accepted fixed-window input, only the bootstrap control probe, and a clean process-tree exit after 12.7 seconds; two other runs produced no usable window. The exact exit trigger is unknown. S4 also showed that the registration form requires email, screen name, and password, while the committed automation allowlist intentionally cannot type letters or digits. Even if boot stability returned, the present script has no verified unattended path through registration.

The current toolchain is installed, so missing `xdotool`, `maim`, X11 utilities, Wine, Python Xlib, CMake, or Vulkan is not the present blocker. The blockers are runtime state, registration/profile setup, process supervision, provenance, semantic classification, and human gates.

## Current tool inventory

**VERIFIED NOW** by `command -v` and `pacman -Q`:

| Tool | Current path | Installed version/package |
|---|---|---|
| xdotool | `/usr/bin/xdotool` | `4.20260303.1-1.1` |
| maim | `/usr/bin/maim` | `5.8.2-1.1` |
| xwininfo | `/usr/bin/xwininfo` | `xorg-xwininfo 1.1.7-1.1` |
| xrandr | `/usr/bin/xrandr` | `xorg-xrandr 1.5.4-1.1` |
| Wine | `/usr/bin/wine`, `/usr/bin/wineserver` | `wine 11.17-1.1` |
| Python | `/usr/bin/python3` | Python 3; `python-xlib 0.33-7` installed |
| CTest | `/usr/bin/ctest` | `cmake 4.4.3-2.1` |
| Vulkan driver | system package | `vulkan-radeon 3:26.2.3-1` |

`python3-xlib` is a real runtime dependency of `tools/observatory/agent_overlay.py:52-96`, despite the architecture's broad “stdlib-only tooling” statement. It is currently installed, but `cell_trace.sh` does not preflight-import it.

No `.github/workflows/*` file exists. There is no committed CI workflow enforcing the Python contract suite, native tracer self-test, or CTest.

## Automation and runtime entry points

### 1. MCP `trace_run`

**VERIFIED NOW:** `tools/mcp/runtime_tools.py:254-371` implements the approval-gated MCP path. It checks scenario, tracer, Wine, `DISPLAY`, `SPORE/`, lock state, duration, timeout, and output path, then executes:

```text
python3 tools/observatory/observe.py <scenario> --duration N --out-dir DIR
```

`observe.py` actually acquires the shared lock before launching (`tools/observatory/observe.py:48-63`) and runs `probe_tracer --launch wine --launch-arg SPORE/SporeBin/SporeApp.exe` (`tools/observatory/observe.py:66-90`). This is a **raw startup trace**, not a menu-to-Cell walk. No MCP handler calls `menu_walk.sh` or `cell_trace.sh`.

The gate is fail-closed for MCP calls: `tools/mcp/safety.py:21-93` requires `approve=true` and `OPENSPORE_MCP_TRUSTED=1` for `trace_run`, `status_update`, and fixture rebuild.

### 2. Direct `observe.py`

**VERIFIED NOW:** direct invocation is not approval-gated. It checks only probe/tracer existence and acquires the machine lock. Therefore the MCP approval boundary and direct-script boundary are not equivalent. A future unattended controller must not treat “called `observe.py`” as proof of human authorization.

### 3. `menu_walk.sh`

**VERIFIED NOW:** `tools/observatory/menu_walk.sh` is the older untraced GUI shell.

- Dry-run is side-effect-free by construction (`:78-109`); the current contract test PATH-shims all invoked tools and checks no marker/file-surface change (`tests/test_menu_walk.py:35-65`).
- The real path requires `--approve` plus `OPENSPORE_MCP_TRUSTED=1` (`:378-386`) and re-execs through `lock.py acquire ... --`, so its lock is held atomically through the command.
- It kills the wineserver, launches untraced Wine with `WINEDEBUG=+d3d`, searches by the loose name `Spore`, pins the first connected `xrandr` output, starts the overlay, and sends `xdotool key --window` (`:200-256`, `:258-307`).
- S4 proved the `--window` path inconclusive, so this shell is not the preferred original-GUI evidence path.

### 4. `cell_trace.sh`

**VERIFIED NOW:** `tools/observatory/cell_trace.sh` is the intended traced Cell path. It uses the S4 fallback input mechanism—`windowactivate --sync` followed by a key to the focused window (`:316-325`)—and launches the game through `probe_tracer` (`:445-490`).

The pure portions are covered by `tests/test_cell_trace.py`: deterministic dry-run, no issued tools, approval refusal, navigation-only key allowlist, registration decision, manifest count/shape, and deterministic JSON output (`tests/test_cell_trace.py:39-218`).

The real path is not yet a complete unattended supervisor; see blockers below.

### 5. Overlay and emergency stop

**VERIFIED NOW:** `tools/observatory/agent_overlay.py:52-96` creates an X11 override-redirect indicator, grabs a root BackSpace key with modifiers, writes `/tmp/openspore-walk/stop-state`, and SIGTERMs the recorded walker PID. `--selftest` verifies only that a viewable override-redirect window maps (`tools/observatory/agent_overlay.py:111-152`); it does not physically press the stop key or prove the compositor binding is available.

**HISTORICAL EVIDENCE:** S3 recorded a synthetic stop-key substitute, not a physical keypress. The S4 manifest remains explicit: `HUMAN_ACTION_REQUIRED`, physical `Ctrl+Alt+Backspace`, `performed:false` (`tools/observatory/out/S4-20260922T171504Z-379947/manifest.json:50-55`).

### 6. Machine lock

**VERIFIED NOW:** `tools/observatory/lock.py:79-114` uses nonblocking `flock`, writes `{pid,label,ts,task_id}`, and relies on kernel release. The exec path clears close-on-exec so the child retains the lock (`:163-207`). The primitive and its command path are correctly covered by `tests/test_lock.py:40-125`.

`tools/observatory/machine_lock.sh:1-15` wraps the same primitive for human and CTest commands.

### 7. Native tracer and probes

**VERIFIED NOW:** `tools/observatory/probe_tracer.cpp` is a 32-bit ptrace/INT3 entry tracer:

- bounded module wait, traced-lineage discovery, and Wine reparenting support (`:516-870`);
- probe address resolution and executable-mapping checks (`:874-899`);
- temporary breakpoint planting (`:901-963`);
- duration/cap-bounded event capture (`:965-1121`);
- bounded byte restoration and detach (`:1123-1166`).

The event schema is entry-only: `t`, `rel`, `tid`, `name`, `rva`, `addr`, `this`, `eax`, `ebx`, `ecx`, `edx`, heuristic `depth` (`:1074-1086`). It does not capture return state, stack, memory before/after, or an exact call/return pair.

Committed probe sets:

- `tools/observatory/probes/main_menu.json` — seven startup probes.
- `tools/observatory/probes/cell_movement.json` — twelve probes: eleven candidate Cell-related functions plus the bootstrap control.
- `tools/observatory/probes/menu_transition.json` — eight UI/message/resource/frame probes; its own description says it has not been run (`tools/observatory/probes/menu_transition.json:1-23`).

**HISTORICAL EVIDENCE:** the native 32-bit self-test produced 1,801 events and validated tracer mechanics only (`tools/observatory/SCENARIO-main_menu.md:69-82`). A historical original startup run captured 1,004 events; the committed 150-event example begins with entry, InitPlugins, Init, Startup, and high-frequency IAppSystem::Get (`tools/observatory/examples/obs_main_menu_example.jsonl:1-20`). This is startup evidence, not Cell evidence. The current ignored `tools/observatory/out/obs_main_menu.jsonl` has zero lines.

### 8. Analyzer and MCP trace inventory

**VERIFIED NOW:** `tools/observatory/analyze.py:21-151` deterministically summarizes a fixed JSONL input. MCP `trace_analyze` adds a file SHA-256 and normalized result (`tools/mcp/runtime_tools.py:491-540`). Focused tests confirm identical output for identical input and path confinement (`tests/mcp/test_assets_runtime.py:159-208`).

`trace_status` is sorted and read-only but shallow (`tools/mcp/runtime_tools.py:583-650`). It lists directories as `other_files` and does not recurse. S5 artifacts under `tools/observatory/out/cell/<run_id>/` are therefore not discoverable by the default run-id/status path, although an explicit nested path can be analyzed.

### 9. Host Cell harnesses

These are deterministic OpenSpore-host tests, not original-game oracles:

- `build/src/cell_stage <package> --input <jsonl>` replays fixed host input and emits a sim manifest (`src/apps/cell_stage.cpp:722-855`, `:1432-1435`). `tests/test_sim.py:82-123` checks movement/events and byte-identical manifest/PPM across two runs.
- Fixed-frame `cell_stage` emits a byte-stable manifest (`src/apps/cell_stage.cpp:484-642`); `tests/test_cellstage.py:23-42` checks two identical stdout manifests but does not compare the fixed-frame PPM.
- `sim_contract_test` is pure C++, fixture-driven, bit-exact per frame, and replays every fixture twice (`src/sim/tests/sim_contract_test.cpp:469-545`).
- Interactive host mode is real SDL3/Vulkan input (`src/apps/cell_stage.cpp:858-1200`) and may be bounded with `--frames N`; it is useful for GUI smoke testing but proves no original behavior.

### 10. Synthetic inline-hook harness

**VERIFIED NOW:** `tools/replace/synthetic/` is a headless native 32-bit, non-PIE mechanism test. `hooker.c:31-70` installs and reads back a five-byte `E9 rel32`; `test_hook.py:24-86` traces the unhooked target and then runs the hooked target directly because INT3 and the patch cannot own the same bytes. `tools/replace/synthetic/README.md:32-58` records the historical pass. It does not implement a Spore installer, unhook lifecycle, trampoline, thread quiescence, or original ABI oracle.

## What is deterministic and safe unattended today

**VERIFIED NOW unless marked historical:**

1. **Static and contract validation.** Pure C++ simulation/contract tests and stdlib Python tests can run without launching the original. Only focused automation tests were run in this audit.
2. **GUI dry-run planning.** Both shells enumerate actions without invoking real tools. `cell_trace` additionally proves byte-identical dry-run output; `menu_walk` currently proves no side effect and plan coverage, but does not itself test two-run byte identity.
3. **Fixed input policy.** The allowlist rejects letters, digits, F13, Tab, and space; every emitted key is reviewed and logged before issue.
4. **Pure decision helpers.** Registration decision, shot-line shape, and fixed-input manifest construction are deterministic and tested.
5. **Lock primitive.** Actual `lock.py acquire -- <command>` paths are serialized and tested. This does not validate every caller's acquisition sequence.
6. **Read-only analysis/status.** Trace analysis is deterministic and path-confined; status listing is sorted. Zero-line JSONL is treated as a negative capture, not a missing file.
7. **Host fixed-frame and scripted-input replay.** This is deterministic for OpenSpore's own model and fixtures only.
8. **Native tracer mechanics.** The m32 path is bounded and historically green; it is not a positive Spore Cell result.

## What is not deterministic or unattended

### 1. Original Cell reachability is currently blocked

**HISTORICAL EVIDENCE:** `docs/devlog/018-s5-cell-runtime-evidence.md:25-63` records three human-watched runs.

- Run 1 mapped all 12 probes, rendered, accepted focused-window input, and recorded nine changing screenshots, but JSONL contains only `entry (bootstrap control)`. The trace ended after 12.7 seconds with the process tree gone and all eleven Cell probes at zero (`tools/observatory/out/cell/S5-20260922T212936Z-396838/obs_cell_movement.jsonl:1`; `wine_stderr.log:145-185`).
- Runs 2 and 3 mapped the module and planted all probes but recorded zero events and no usable window (`tools/observatory/out/cell/S5-20260922T213524Z-397779/wine_stderr.log:8-23,86-100`; `.../S5-20260922T214226Z-399437/wine_stderr.log:8-23,83-100`).
- The exact clean-exit trigger remains unknown; registration/license and renderer behavior are hypotheses, not conclusions.

### 2. The registration gate is visual, not semantic

S4 focused-window Return produced visible validation text: “Email is required. Screen Name is required. Password is required.” (`docs/devlog/017-s4-x11-input-feasibility.md:28-35`; S4 manifest `:21-27`). `cell_trace.sh` intentionally cannot type those values. Its “registration” step is only Down/Return three times (`tools/observatory/cell_trace.sh:328-359`).

The current classifier calls registration `advanced` if **any** screenshot hash differs from the base. Splash/loading animation can satisfy that test. A changed frame is not proof that a form field or screen state advanced.

### 3. S5 can report “completed” after the target exits

`cell_trace.sh` starts `probe_tracer` in the background (`:454-463`) but never waits for or monitors its exit during the walk. It determines the stage from JSONL and sets `OUTCOME=completed` on the normal shell path (`:497-531`). The S5 run-1 manifest consequently says `outcome: completed`, `duration: 150`, and `cell_stage_reached: menu_only`, even though the tracer reported only 12.7 seconds and the process tree had exited (`tools/observatory/out/cell/S5-20260922T212936Z-396838/manifest.json:5-18`; stderr `:170-185`). “Completed” currently means “the shell reached manifest writing,” not “the traced process survived the requested duration.”

### 4. Failure exits do not reliably emit a manifest

`cell_trace.sh:on_exit` only kills children/overlay/lock (`:261-275`). `stop_chain` exits directly (`:277-280`) without calling `write_manifest`. Window-not-found, renderer-marker-absent, geometry-drift, input-no-response, shot failure, and human stop can therefore leave logs but no manifest, contrary to the negative-result contract in `docs/RE-AUTOMATION-ARCHITECTURE.md:478-484,637-641`.

`manifest_from` also catches every JSON parse/read exception and silently emits empty counts (`tools/observatory/cell_trace.sh:142-188`). A corrupt JSONL can be represented like a zero-event capture.

### 5. Screenshot “trace correlation” is not implemented

Both `take_shot` helpers set `trace_t_nearest` to a second `date +%s` wall-clock value (`tools/observatory/menu_walk.sh:187-196`; `tools/observatory/cell_trace.sh:303-312`). Tracer timestamps are monotonic `CLOCK_MONOTONIC` values. No conversion or nearest-event lookup is performed. The field name overstates the current evidence; screenshot records are not truly correlated to tracer time despite the architecture's requirement (`docs/RE-AUTOMATION-ARCHITECTURE.md:490-497`).

### 6. Cell-stage classification is too broad

`determine_cell_stage` treats any non-bootstrap event as Cell Stage (`tools/observatory/cell_trace.sh:415-433`). The set includes `face_travel_orient_FUN_0069b600`, historically observed at about 30 Hz on the main menu (`docs/analysis/CELL-RUNTIME-OBSERVATION.md:53-73`), plus camera/player helpers that are not individually proven Cell-exclusive. This classifier can produce a false positive.

### 7. Window identity/environment is not portable or fully attributable

`cell_trace.sh` hard-codes `2304x1296+2561+144` and falls back from `xdotool search --class` to `--name Spore` (`:63-68`, `:465-490`). It does not bind the window to the tracer's module-host PID. S4 recorded `_NET_WM_PID` absent and accepted identity from `WM_CLASS` plus a renderer marker (`tools/observatory/out/S4-20260922T171504Z-379947/environment.txt:18-21`).

`menu_walk.sh` calls the **first connected** xrandr output “primary” (`tools/observatory/menu_walk.sh:182-185`). S4 recorded DP-1 first but HDMI-A-1 marked primary (`tools/observatory/out/S4-20260922T171504Z-379947/environment.txt:7-9`), so the old shell can select the wrong monitor.

### 8. The Cell lock handoff is check-then-act, not atomic

`cell_trace.sh` probes whether the lock is free, then starts a background lock holder, sleeps 0.3 seconds, and runs regardless (`tools/observatory/cell_trace.sh:611-629`). It never checks that the holder acquired the lock. Another process can win between probe and holder startup. This differs from the correct `menu_walk.sh`/`machine_lock.sh` exec-inherited `flock` design.

No focused test covers this real Cell acquisition sequence; `tests/test_cell_trace.py` only exercises dry-run and pure helpers.

### 9. Overlay readiness and emergency stop are assumed

The shells start `agent_overlay.py --start` in the background and sleep 0.5 seconds (`menu_walk.sh:258-260`; `cell_trace.sh:492-495`). They do not verify `overlay wid=...`, map state, or successful `XGrabKey`. An Xlib import, display, or grab failure does not stop input. The physical key binding is also unresolved in the architecture (`docs/RE-AUTOMATION-ARCHITECTURE.md:715-716`).

### 10. No hard timeout covers every shell operation

The tracer itself has duration and detach deadlines, and key calls are backgrounded to allow signals. However, the GUI shells have no per-step/whole-run command timeout around `xdotool`, `maim`, `xwininfo`, overlay readiness, or the no-op ladder. The pre-existing S3 record already lists this gap (`docs/devlog/016-gui-automation-shell.md:92-97`).

### 11. Preflight and provenance are incomplete

`cell_trace.sh:534-546` checks only display, executable, xdotool, maim, and tracer existence. It does not check Wine, wineserver, xwininfo, xrandr, Python Xlib, output writability, probe/binary hashes, Wine version, compositor, or whether `probe_tracer` was rebuilt from current source. The old README warns that a stale tracer previously spun forever (`tools/observatory/README.md:136-153`).

The S5 launch block does not set `WINEDEBUG=+d3d` (`cell_trace.sh:454-462`) even though it requires the `swapchain_resize_buffers` marker (`:477-481`). Historical S5 worked only because the inherited environment evidently supplied D3D diagnostics. `menu_walk.sh` sets it explicitly (`:200-205`).

The current S5 manifest records only run/scenario/stage/duration/counts/lock/geometry. It omits executable and probe hashes, tool versions, actual process exit, actual observed duration, active/skipped/dropped breakpoint counts, input/shot hashes, stderr hashes, and environment provenance.

### 12. Tracer success and coverage reporting are incomplete

**VERIFIED NOW:**

- A probe outside an executable mapping is marked inactive, but the tracer continues and can return 0 even with zero active breakpoints (`tools/observatory/probe_tracer.cpp:881-899,957-970,1160-1166`).
- A tracee exiting or being signaled is logged, but the final process still `_exit(0)` after its own duration/event loop (`probe_tracer.cpp:992-1000,1160-1166`). Callers cannot distinguish healthy duration completion from early clean exit/crash using return code alone.
- Per-function caps retire a breakpoint; later calls are unobserved, but dropped counts exist only in stderr, not JSONL (`probe_tracer.cpp:1089-1112,1163-1165`).
- The output file is opened **after** breakpoints are planted (`probe_tracer.cpp:940-970`). If `fopen` fails, the function returns without the normal restore/detach path.

These are safety/coverage blockers for unattended use even though the normal m32 and historical Wine paths pass.

### 13. MCP has small but real reliability debt

The focused 72-test run passed but emitted `ResourceWarning` for unclosed lock files from `tools/mcp/runtime_tools.py:lock_held`. The contention branch returns before closing the file handle (`runtime_tools.py:169-194`). This did not fail the tests but can leak descriptors under repeated automation and should be covered by a regression test.

`fixture_check` identity mode only reads the same file twice and compares hashes (`runtime_tools.py:967-1001`); it does not regenerate from the emitter. Only gated rebuild mode performs two emitter runs before writing (`:1002-1073`).

## Build and test configuration

**VERIFIED NOW:**

- Root build: C++17, `-Wall -Wextra -Werror`, Vulkan required, optional SDL3, Python required, CTest enabled (`CMakeLists.txt:1-38`).
- `src/CMakeLists.txt:1-44` additionally requires `glslangValidator` and embeds generated SPIR-V headers, so the project is not build-hermetic.
- Pure simulation/lifecycle/contract tests are registered in `src/sim/CMakeLists.txt:1-90` and `src/replace/CMakeLists.txt:1-16`.
- Display/GPU tests are heterogeneous. `triangle`, `asset_render`, `material_smoke`, and the no-display interactive smoke are wrapped with `machine_lock.sh` (`src/CMakeLists.txt:54-86,166-178`), but the main `cell_stage` CTest is invoked directly (`:111-115`).
- Current source registers **37** CTest entries: 1 root + 11 src + 15 assets + 9 sim + 1 replace. The 37th is the uncommitted `assets_resource_io` test at `src/assets/CMakeLists.txt:25-31`. The committed/historical baseline documented in `docs/STATE.md:3,94` is 36. This audit did not configure or run CTest.

The working tree was already dirty before this audit. Relevant pre-existing changes include `src/assets/CMakeLists.txt`, asset implementation files, `tests/test_viewer.py`, `tools/viewer/query.py`, `build-pkg03/`, and other untracked files. They were not modified here.

## Verification performed in this audit

**VERIFIED NOW:** the following focused, side-effect-free command was run with bytecode disabled:

```text
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest \
  tests.test_menu_walk tests.test_cell_trace tests.test_lock \
  tests.mcp.test_assets_runtime -v
```

Result: **72 tests passed in 3.746 seconds**. The run did not launch Wine, the game, X11 input, or the tracer. It emitted the non-failing MCP lock-descriptor `ResourceWarning` described above.

Not run in this audit: full Python discovery, CTest configure/build/execution, native tracer self-test, synthetic hook test, overlay display self-test, host Cell render tests, any Ghidra import, and any original runtime trace.

## Human interaction that remains necessary

1. **Runtime approval.** A worker cannot self-approve `trace_run`, `status_update`, or fixture rebuild; trusted operator intent is required (`tools/mcp/safety.py:21-93`).
2. **Human presence for the shared display.** The original GUI is launched on a human-shared `:0`; the current architecture classifies RUNTIME as human-only (`docs/RE-AUTOMATION-ARCHITECTURE.md:399-404`).
3. **Physical emergency-stop verification.** The S4 record still says the physical `Ctrl+Alt+Backspace` action is unperformed. Synthetic injection is not equivalent.
4. **Registration/profile preparation.** The observed form requires text. The current no-typing allowlist cannot complete it. A human must either complete registration in a disposable profile or separately approve a profile/account state that avoids repeated manual entry. No such path is currently implemented or verified.
5. **Boot/self-exit diagnosis.** A bounded read-only Wine/renderer/log collection can be automated under approval, but deciding the root cause of the clean exit remains a human research judgment until reproduced.
6. **Independent adjudication and status promotion.** `status_update` is human-gated; final runtime evidence and status changes require independent review (`docs/RE-AUTOMATION-ARCHITECTURE.md:367-374,613-641`).
7. **Ghidra new-program import, if EP1 work resumes.** This is outside the Wine oracle and remains GUI/human-only (`docs/analysis/GUI-BOUNDARY.md:22-35`).

## PROPOSALS — not implemented or verified

Ordered by information gain and safety:

1. **Run a bounded M0 boot/exit diagnosis, not more click loops.** Pin binary/probe/tool/display/Wine identity; launch with no input; record exact module-host PID, process exit/signal/time, renderer marker, window identity, and teardown. Stop after one or two approved attempts. This is the smallest experiment that distinguishes stable boot, registration exit, renderer failure, and tracer failure.
2. **Make lock acquisition atomic in the real Cell path.** Use the existing `lock.py acquire ... -- <command>` inheritance rather than probe/start/sleep. Fail if the holder cannot acquire.
3. **Supervise every runtime child and operation.** Track tracer and Wine process state, enforce phase and total deadlines, kill on timeout, and require the output file to be opened successfully before planting breakpoints.
4. **Fail on partial instrumentation.** Require all expected probes active; record skipped, retired, and dropped counts. A zero-active or partially covered run is `blocked/partial`, never `completed`.
5. **Bind the window to the traced module host.** Use module-host PID plus WM_CLASS, generation marker, geometry, and primary-output identity. Where `_NET_WM_PID` is absent, record that limitation explicitly and refuse a loose name-only match.
6. **Add an explicit registration handoff.** Prefer a disposable profile prepared by the operator over automated credential entry. A human-visible pause/marker is safer than inferring form state from screenshot delta. Never log secrets.
7. **Use Cell-specific positive markers for stage classification.** Exclude the known generic frame helper. Require a Cell lifecycle/control event, ideally a correlated pair such as `cCellModeStrategy::OnEnter`/Cell Update plus a target-specific event, before setting `cell_stage_reached=true`.
8. **Make negative and interrupted runs first-class artifacts.** Always write a manifest in one cleanup path, including actual exit/signal, actual elapsed time, phase, stop reason, active/skipped/dropped probes, hashes, environment, input/shot/log references, and lock release. Reject malformed JSONL rather than converting it to zero events.
9. **Implement real monotonic-time screenshot correlation.** Record wall and monotonic clocks, then compute nearest trace event from a shared monotonic clock. Until then, rename or omit `trace_t_nearest`.
10. **Unify MCP and GUI orchestration.** `trace_run` should invoke one reviewed workflow that performs the GUI phase and trace on the same process, rather than exposing raw startup observation and a separate direct script with different gates.
11. **Add CI-safe gates.** Run focused Python contracts and pure CTest tests on every change; run native m32 tracer and synthetic hook checks in a dedicated environment. Keep display/SPORE tests opt-in and clearly classified.
12. **Keep replacement differential tooling separate.** The current tracer can establish entry reachability, not call/return or memory parity. Any return/state/write oracle belongs in the proposed disposable replacement harness in `knowledgegraph/research/runtime-oracle/replacement-observability.md`, not in the GUI walker.

## Final determination

**Safe unattended now:** static analysis, pure unit/contract tests, shell dry-runs, pure input-policy helpers, atomic lock primitives, trace analysis, shallow status inventory, host scripted simulation, and native fixture mechanics.

**Not safe unattended now:** any original-game Cell trace, any direct `observe.py` launch treated as approved, any status promotion, and any claim that Cell behavior has been reproduced.

**Smallest credible next step:** after explicit human approval and physical-stop readiness, perform one bounded, read-only, no-input boot/exit diagnosis that records the exact process lifecycle. Only after that cause is understood should registration/profile handling and Cell-specific classification be addressed. The immediate blocker is not key-count tuning; it is obtaining a stable, attributable original-process lifecycle and a legitimate non-secret route through registration.
