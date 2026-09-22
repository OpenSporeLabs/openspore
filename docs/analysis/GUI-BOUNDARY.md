# GUI AUTOMATION BOUNDARY — where computer-use genuinely adds value (Subagent 7)

Machine-verified analysis, 2026-09-22. Principle: API/headless automation is PREFERRED; GUI is a last-resort tier; nothing here is implemented.

## 0. Verified machine facts

| Fact | Status |
|---|---|
| `xdotool` | **Installable**: `extra/xdotool 4.20260303.1-1.1` |
| `xorg-server-xvfb` | **Installable**: `extra/xorg-server-xvfb 21.1.24-1.1` |
| `wmctrl` / `x11-utils` | Absent (install `x11-utils` alongside for `xwininfo`/`xprop`) |
| Session | **KWin/Plasma Wayland** with XWayland at `:0`; `XDG_SESSION_TYPE=wayland`; `/tmp/.X11-unix/X0` present |
| Display | **2796×1290 "Virtual-sunshine-vm"** — a VM running a Sunshine streaming server; the human is on the same display, almost certainly via streaming |
| Wine | 11.17, `~/.wine` prefix; **SporeApp.exe is running RIGHT NOW** — any walk must `wineserver -k` first |
| Ghidra | Headless MCP server live at `:8089`, SporeApp.exe open and decompilable |
| Schema | `trace_run` manifest already has `xdotool TEXT, display_env TEXT` columns (SCHEMA-DELTA §2.3); screenshot evidence slots into an existing field |

Two consequences:
1. **Xvfb is a trap, not an unblock.** The 8/9 stall happened *with* real `:0` + direct rendering; under Xvfb wined3d falls back to llvmpipe software GL and Spore's D3D bring-up may never fire. Xvfb buys isolation from the human but likely loses the renderer. **`:0` + `xdotool` is the minimal unblock; Xvfb is a last-resort fallback with the risk stated in the manifest.**
2. **KWin is a full compositor on top of XWayland.** `xdotool` works (X11 events pass through XWayland), but focus is KWin-managed: expect focus-stealing-prevention and window animations. Mitigation: target events with `xdotool --window $WIN` (XSendEvent, focus-independent) — **validate in one manual run before any unattended walk** (some apps reject `send_event=true`; this is the single biggest unknown on the critical path).

## 1. GUI workflow inventory & classification

| # | Workflow | Class | Mechanism of record | Why |
|---|---|---|---|---|
| W1 | **Menu navigation main-menu → cell stage** (unblocks the cell trace — the single highest-leverage evidence) | **(c) GUI-genuinely-required** | xdotool script → screenshot-loop only for unknowns | Stage transition is driven by the game's own input handling (`menu_transition.json` probes are exactly `UI::cEditor::HandleMessage` / `OnMouseDown` / dispatch + DBPF load path). No config/console/DLC-flag path into cell; ModAPI detours would *alter the behavior under observation* — tracing detoured behavior violates the clean-room evidence contract. Real synthetic input into the real window is the only faithful path. |
| W2 | **Ghidra GUI: import EP1 binary** (`SporebinEP1/SporeApp.exe`, 24.9 MB) | **(c) GUI-required, but HUMAN-ONLY** | Agent posts exact 3-click steps; human clicks; agent verifies via REST | Headless *cannot* open (verified). But the action is ~3 clicks on a Swing UI with no AT-SPI; automating is pure fragility for a one-shot. Agent prepares (file present, project open, steps written), human clicks, agent verifies (`list_project_files`/`get_metadata`), then all analysis is headless again. |
| W3 | **Ghidra GUI: vtable-labeling pass** | **(b) headless-better, GUI-fallback-justified** | `run_script_inline` on the live MCP server: enable the VTable analyzer + `reanalyze`; verify via `list_function_tags`/vtable join | AGENTS.md's "never ran headless (0 vtable labels)" was via `analyzeHeadless` config, not the running server. A script on the open program is headless and scriptable. GUI only if the script route fails. |
| W4 | **Ghidra GUI: visual decompile inspection** | **(a) headless-already-possible** | REST `decompile_function` | The MCP decompile text IS the decompiler's output. Useful to a human, never needed by the agent. |
| W5 | **gdb/lldb with the game as inferior** | **(a) scripted / human-only** | `gdb -batch -ex ...` for data; interactive TTY = human | gdb is a TTY app, not GUI — computer-use is the wrong tool by definition. |
| W6 | **Watching the game live to understand a transition** | **HUMAN-ONLY** | Human eyes on `:0` | Understanding ≠ capture. Never automate "understanding." |
| W7 | **Viewer on 127.0.0.1:8787** | **(a) headless-already-possible, NEVER GUI** | `curl`/fetch its JSON endpoints | Driving an API-served page with a screenshot loop is strictly worse than calling the API. |
| W8 | **OS-level: display config / window mgmt** | **(b)** | `xrandr` + `xdotool` for window geometry | Compositor-level ops (KWin workspace switching) are not reliably headless-scriptable on Plasma — use window pinning + full-screen instead. |

**Net: exactly ONE workflow (W1) can ever justify real GUI automation. W2 is GUI-required-but-human. Everything else is headless or human.**

## 2. Synchronization problems of a screenshot-driven loop

- **Frame timing vs 30/60 Hz.** A screenshot loop at 100–500 ms cadence is a coarse annotation, never frame-accurate. Fine by design: the INT3 JSONL carries nanosecond timestamps and is ground truth; the screenshot is a wall-clock-millisecond annotation correlated to trace-t. Capture latency must be measured once and recorded as a constant in the shot manifest.
- **wineserver generation is a consumed resource.** First boot after `wineserver -k` works; later boots on the same generation stall in `ntsync_schedule` or exit silently. A walk that retries a stalled boot must `wineserver -k` + relaunch between attempts — the script owns a generation counter: every `wine` spawn is preceded by `-k`, every attempt logged (`wineserver -v` output + wineserver PID at launch).
- **Window focus races under KWin.** Mouse clicks are position-based (robust); key events need focus. KWin focus-stealing-prevention can drop `windowactivate`; a human click anywhere steals focus mid-walk. Mitigations in order of reliability: (1) `xdotool key/click --window $WIN` (XSendEvent, focus-independent — validate in the manual run); (2) if rejected by wine, re-assert focus per keystep.
- **The display is shared with the human (a streaming VM).** If the human moves the wine window mid-walk, click coordinates hit the wrong widget. Mitigations: pin + maximize the wine window at walk start and never re-query geometry per step; a human protocol (walk is ~30–60 s, announced via the AGENT DRIVING overlay, hands-off); geometry re-check each step — if the window moved, that's a stop condition, not a recover.
- **XWayland input-state drift.** Use `xdotool clearmodifiers` before key sends.

## 3. Screenshot as evidence — capture→store→cite chain

**Rule: the screenshot is a timestamped annotation of the INT3 trace, never primary evidence.** The JSONL is ground truth; a shot is *evidence* iff it is (a) hash-pinned + wall-clock timestamped + trace-t correlated, and (b) its pixel delta coincides with tracer activity in the same window. A shot with no events in its window is **junk**: stored in `out/`, never cited as a KG `Observation`.

1. **Capture**: per-step + per-phase shot of the wine window rectangle (`xwd -id $WIN -out <path>` — window-only, ~1–3 MB). Capture *after* the input event + a 250–500 ms settle delay.
2. **Store**: `tools/observatory/out/shots/<run_id>/` (git-ignored) — `shots.jsonl` manifest: `{seq, path, sha256, wall_clock, trace_t_nearest, input_event, window_geom, delta_vs_prev_sha:bool}`. Committed examples: only a trimmed keyframe set (≤5 shots) under `tools/observatory/examples/shots_*/` — mirroring the committed JSONL-example precedent.
3. **Cite**: the `trace_run` manifest gains `screenshots {count, first, last, manifest_path}` (one line of schema). KG `Observation` nodes cite `run_id` → manifest → JSONL; the shot set is reachable from the manifest but **cited only as corroboration**, never as the `evidence` pointer of a promotion.
4. **Evidence vs junk (machine-checkable):** `delta_vs_prev_sha=true` AND ≥1 event in `[trace_t − 1s, trace_t + 0.5s]` → annotation; otherwise junk. A *no-delta after an input event* is a first-class negative signal.

## 4. Reproducibility verdict

A GUI-driven run is **not** replayable the way the sim's `--input script.jsonl` replay is (that bar applies to *our* code only). What a GUI-driven trace must record: the exact input event stream (every xdotool invocation + wall-clock ts + target window id, logged *before* issuing), display state (`xrandr` + per-step window geometry), wine/generation state (`wine --version`, `wineserver -v`, PID at launch, `WINEDEBUG` level, prefix path + mtime), environment (`DISPLAY`, `XDG_SESSION_TYPE`, compositor version, `xdotool` version), trace ground truth (binary_sha256, probes_sha256, JSONL path, events_total), and the screenshot set.

**Honest verdict: reproducible-enough for evidence, not bit-exact.** Re-running the input log against the same binary/wine/display reaches the *same stages* (menu logic is deterministic given the input sequence; the probes fire in the same order — that's the check), but frame timing, wineserver scheduling, and tracer ns timestamps will differ. Manifest must state: `replayable: "input-logged, stage-deterministic, non-bit-exact"`. Claiming bit-exactness for the original's trace would be fabricating evidence.

## 5. Failure detection & escalation (the 9-run precedent, operationalized)

Observable signals of "input did nothing / boot stalled" (all cheap, all headless):
1. **Process state**: `ps -o stat,wchan=` on the game pid — the 9-run signature is 1 thread, 0 CPU, `ntsync_schedule`. Poll every 2 s.
2. **Trace ground truth**: module mapped (probes planted) but **0 events for 10 s** → stalled before entry.
3. **Renderer marker**: `WINEDEBUG=+d3d` stderr — absence of `swapchain_resize_buffers` within 5 s of launch = renderer never came up.
4. **Screenshot no-delta**: ≥3 consecutive identical window hashes after an input event = click had no effect.
5. **Geometry drift**: `xwininfo` geom ≠ pinned geom → human moved the window → **stop, no retry**.

Escalation ladder (budgeted, never a loop):

| Level | Trigger | Action |
|---|---|---|
| 1 | 1 no-op at a step | Re-assert (`windowactivate` or `--window` resend), retry the step **once** |
| 2 | 2nd no-op, or renderer marker absent | `wineserver -k` + fresh boot, **1 attempt only** |
| 3 | 3rd failure, any phase timeout (boot ≤60 s, step ≤10 s, total ≤180 s), or geometry drift | **STOP.** SIGKILL game. Record the negative result as first-class: manifest `outcome: boot-stall \| input-no-response \| geometry-drift`, partial JSONL (0 events is a valid file), KG `Observation` with the run_id. Park the task `approval_required` with the evidence pointer. |

The 9-run lesson is the policy: *a budget of attempts, each recorded, then a negative result is the deliverable.*

## 6. Security/safety boundaries (concrete)

1. **Approval gate — unchanged.** GUI automation is a *precondition phase of `trace_run`*, not a new MCP tool. Same `approval_required` → human sign-off → `approve=true` + `OPENSPORE_MCP_TRUSTED=1` semantics.
2. **Window confinement — allowlist of one.** The walker discovers the wine window id at launch and targets *only* that id (`--window $WIN` on every event). No events to any other window; terminal/plasmashell windows never touched.
3. **Keystroke safety — no typing, period.** The walk uses a fixed pre-declared key set: `Return`, `Escape`, `Up/Down/Left/Right`. `xdotool type` is **not used anywhere** — no strings can enter any field. A code-reviewable invariant, not a prompt-level promise.
4. **Visible AGENT DRIVING indicator** — a small borderless always-on-top X11 overlay window (Python `python3-xlib`, ~60 lines) at the wine window's edge: red frame + "AGENT DRIVING — press **Ctrl+Alt+Backspace** to stop". Created at walk start, destroyed at stop.
5. **Emergency stop, human-side, works even if the agent hangs.** The overlay `XGrabKey`s the combo globally (verify `Ctrl+Alt+Backspace` is unbound in default Plasma once). On press: SIGTERM walker → walker SIGKILLs wine, `wineserver -k`, writes `stopped_by_human` to the manifest, destroys the overlay. The agent polls the overlay's stop-state file between every input event.
6. **File/OS surface**: the walker writes only `tools/observatory/out/**` and `/tmp/openspore-walk/`. No package installs mid-walk. No sudo.
7. **Reviewability**: the entire automation surface is *one committed script* (`tools/observatory/menu_walk.sh` + the overlay `.py`), diff-reviewed like any other. An agent improvising clicks is never allowed — if it isn't in the committed script, it isn't happening.

## 7. Recommendation matrix & build order

| Workflow | Preferred mechanism | Escalate to next tier when | Gate |
|---|---|---|---|
| W1 Menu walk → cell | **xdotool script** (committed, pinned geom, input log, shots, no-op ladder) | Script derails on unknown/fragile UI state only → minimal screenshot-driven loop *inside the same safety shell*, never free-form | `trace_run` approval |
| W2 Ghidra EP1 import | **Human-only** (agent prepares + verifies via REST) | — | human click |
| W3 Vtable pass | Headless: MCP `run_script_inline` + `reanalyze` | Analyzer refuses script mode → human runs it once | none |
| W4 Decomp inspection | REST `decompile_function` | Human opens GUI themselves | none |
| W5 gdb inferior | `gdb -batch` scripted | Interactive session → human TTY | none |
| W6 Live watching | Human eyes | — | none |
| W7 Viewer | `curl` its JSON | — | none |
| W8 Display/window | `xrandr` + `xdotool` headless | Compositor-level ops → human | none |

**The ONE thing that must exist before any computer-use is allowed: the committed xdotool menu-walk script, proven to work unattended on `:0` ≥3 consecutive times.** Script the known path first; a screenshot loop is licensed only for the unknown/fragile residue; full general-purpose computer-use is **not justified** — no workflow requires it.

Build order:
1. **Install** (approval): `pacman -S xdotool x11-utils maim python3-xlib`.
2. **One manual validation run, human watching**: fresh `wineserver -k` → boot on `:0` → does `xdotool click/key --window $WIN` (XSendEvent) reach the game under KWin+XWayland? If wine rejects synthetic events, fall back to `windowactivate`+send. This single answer decides the script's design.
3. **Commit `tools/observatory/menu_walk.sh` + overlay**: generation discipline, pin/maximize, per-step input-log + shot + no-op check, §5 ladder, §6 shell. Run unattended ≥3× → the `menu_transition` + `cell_movement` traces under the byte-verified probes.
4. **Record the evidence**: manifest (+`screenshots` field), committed keyframe shots in `examples/`, KG Observations (fires *and* negative runs), then `status_update` (approval) to promote `replaced-approx` → `replaced-verified` where the trace supports it.
5. **Screenshot-driven computer-use** — *only if* step 3 derails on unknown UI states; minimal loop, same shell.
6. **General computer-use**: do not build it.

Current-machine note: **kill the stale SporeApp.exe (PID 213519 at analysis time) and `wineserver -k` before any of this** — a live game on a stale generation is exactly the stall condition.
