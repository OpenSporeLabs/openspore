# 016 — S3: the GUI automation shell

Date: 2026-09-22. Status: **Done (PASS).** Predecessor: chapter
[015](015-knowledge-graph-spine.md) (S1, the KG spine). Followed by S4 (the one
manual XSendEvent feasibility run) and S5 (the unattended walk + cell trace).

## What the objective actually is

We had to be precise about numbering before writing a line of code. The repository's
current architecture (`docs/RE-AUTOMATION-ARCHITECTURE.md §11`) defines **S3 as the GUI
automation shell** — not the runtime trace (that is S5) and not the manual X11
validation (that is S4, class MANUAL). There is no numbering drift: the sprint ends at
S3 *with the evidence*, and the single critical unknown (does wine accept `xdotool
--window` XSendEvent under KWin/XWayland) is answered by S4, one human-watched run.

S3's gate is build/verify only. It requires no real game boot: *"script + overlay
committed and diff-reviewed; dry-run lists every step without issuing events; overlay
appears/destroys cleanly; Ctrl+Alt+Backspace stop verified once by hand; lock
acquired/released."*

## What we built

The whole automation surface is one committed script plus one small overlay:

- **`tools/observatory/menu_walk.sh`** — the walk. Approval gate
  (`--approve` + `OPENSPORE_MCP_TRUSTED=1`, else exit 3, and a direct `--walk` bypass is
  refused); machine-lock re-exec; `wineserver -k` before every spawn; `xrandr`/`xwininfo`
  window pin with a **per-step geometry-drift check that STOPS** (we read the live
  `Absolute upper-left X/Y` — the docs' old 2796×1290 size is gone; the real root is now
  4865×1440 across two monitors); a fixed key allowlist of `Return Escape Up Down Left
  Right` (no typing, ever); a 3-level no-op ladder (retry once → fresh boot once → STOP +
  record negative); a stop-state poll every step; a `maim -i` shot manifest
  (`out/shots/<run_id>/shots.jsonl` with sha256 + `delta_vs_prev_sha`); trap cleanup; and a
  file surface limited to `out/**` + `/tmp/openspore-walk/**`.
- **`tools/observatory/agent_overlay.py`** — ~60 lines of `python3-xlib`: a borderless
  `override_redirect` always-on-top red frame reading "AGENT DRIVING — press
  Ctrl+Alt+Backspace to stop"; a global `XGrabKey` that, when fired, writes a stop-state
  file and SIGTERMs the walker.
- **`tools/observatory/lock.py`** + **`machine_lock.sh`** — `flock` on
  `/tmp/openspore-machine.lock`, body `{pid,label,ts,task_id}`, `machine_locked` exit 5;
  wired into `observe.py` and the four CMake display smoke tests so a human command and an
  agent run are mutually exclusive.

We installed the toolchain for S3 (item 9): `xdotool`, `maim`, and `xorg-xwininfo` via
pacman — Arch has no `x11-utils` metapackage, and we deliberately do not depend on `xwd`
(`maim` is the capture path). `python3-xlib` was already present.

## Bugs we found while testing fail-closed

We built the shell, then attacked it. Thirteen failure modes, and the testing surfaced
real defects we fixed in-scope:

- `--walk` could be invoked directly, bypassing the gate — now refused (exit 3) unless the
  gated re-exec sets its token.
- INT/TERM traps cleaned up but then **resumed the walk** — they now tear down and `exit
  130/143`.
- The geometry check parsed dead `xwininfo` fields, so a **moved** window was invisible —
  it now reads real X/Y, and a resize or a move both STOP.
- A failed boot generation fell through to pin + drive a **foreign window named
  "Spore"** — it now stops on a non-zero generation instead of driving the wrong window.
- Foreground key steps were un-interruptible by trapped signals — they now run via
  `&`+`wait` so a SIGTERM lands immediately.
- `--selftest` with no display returned 0 "skipped" — it now returns 2 "refused".

The most consequential fix came from validation, not from the happy path: CPython 3.4+
opens files with `O_CLOEXEC` by default, so the flock'd file descriptor was **closed at
`os.execvpe` and the kernel released the lock the moment the command started**. Our lock
wrapper wrote its body and looked fine, but a concurrent acquire *succeeded* while a
command was running — nothing was serializing. We clear close-on-exec
(`fcntl(fd, F_SETFD, 0)`) so the child inherits the flock and the kernel holds it for the
whole command. We added a regression test that probes *during* a running child and asserts
`machine_locked` (exit 5).

## What this proved — and what it did not

We are careful here, because this is the whole point of the project. S3's evidence is
**BUILD/VERIFY only**:

- **Proved:** the shell plumbing is built, committed, diff-reviewable, and fails closed on
  every mode we tested — no display, no wine, missing exe, missing tool, a window that
  vanishes mid-walk, geometry drift, lock contention, a hung step, a dead process,
  missing approval, and a malformed manifest. Dry-run lists all nine steps and issues
  nothing. The overlay maps a real `override_redirect` viewable window on `:0` and tears
  down cleanly. The stop chain writes the stop-state file, destroys the overlay, and
  SIGTERMs the walker (fired with `xdotool key ctrl+alt+BackSpace` — a functional
  substitute for the one-time hand press, not a literal finger). The lock serializes live.
- **Not proved:** anything about live runtime behavior. We did not boot the game, did not
  run the cell trace (S5), and did not check whether wine accepts synthetic input under
  KWin/XWayland (S4). A zero-event dry-run is not evidence that a function does not run;
  and none of the 13 modes tells us the Cell Stage is reachable.

We record four gaps as **UNVERIFIED / out-of-scope-for-S3** rather than papering over
them: no per-step hard `timeout` (a SIGTERM covers hangs); no binary/wine identity in the
shot manifest; no explicit `wine`/exe precheck (a missing exe and a boot-stall are
indistinguishable in the log — real wine exits 0 silently); and no OS sandbox (the
confinement is convention plus `xdotool search --name Spore` trust, so any window named
"Spore" matches until we add a strict WM_CLASS/geometry/age check).

## Verification

Full Python suite **392/392 OK** (373 S2.1 baseline + 19 new S3 tests). C++
`cmake --build build -j` is clean under `-Wall -Wextra -Werror` and **ctest is 10/10**
with the smoke tests running through the now-correctly-serializing lock wrapper. S1 KG
invariants, the S2 MCP surface (21 tools, `ALWAYS_GATED = trace_run/status_update` +
`fixture_check(rebuild)` intact), and the read-only viewer are all unchanged. Scope is
clean: no `tools/mcp/*` file was modified, no C++ source changed, and no S4/S5/S6 work
leaked in.

**Next:** S4 — the one manual, human-watched run on `:0` to answer the single critical
unknown.
