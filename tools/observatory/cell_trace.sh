#!/bin/sh
# cell_trace.sh — S5 real Cell runtime evidence: boot SporeApp.exe THROUGH
# probe_tracer (the walk and the cell_movement trace share one traced process),
# walk to Cell Stage on :0 under Wine via the S4-approved FOCUSED-window input
# path, capture the cell_movement probe trace, and record an honest outcome.
#
# It is NOT a new GUI surface: it reuses the SAME xdotool + SAME fixed-key
# allowlist + SAME agent_overlay.py + SAME lock.py as the verified
# tools/observatory/menu_walk.sh. The only input path is the focused-window
# one (xdotool windowactivate --sync + key --clearmodifiers); the XSendEvent
# --window form S4 found INCONCLUSIVE is deliberately absent.
#
# Usage:
#   cell_trace.sh --dry-run [--duration SEC]
#   cell_trace.sh --approve --duration SEC            (needs OPENSPORE_MCP_TRUSTED=1)
#   cell_trace.sh --validate-key <key>
#   cell_trace.sh --registration-decision <signal>    (signal: advanced|persists)
#   cell_trace.sh --manifest <jsonl> <stage> <run_id> <duration> <machine_locked>
#   cell_trace.sh --shot-line <seq> <path> <sha> <wall> <trace_t> <input> <geom> <prev_sha>
#
# A real run requires --approve AND OPENSPORE_MCP_TRUSTED=1 (the MCP gate
# semantics of tools/mcp/safety.py); the orchestrator sets both only after
# explicit human sign-off. The registration gate is empirical: if reaching
# Cell Stage requires TYPING text (outside the fixed allowlist), the driver
# attempts an allowlisted Down/Return bypass and, failing that, records the
# honest negative (registration_blocked). A recorded negative is a valid S5
# deliverable.
#
# Safety (all fail-closed):
#   1 approval gate        --approve + OPENSPORE_MCP_TRUSTED=1, else exit 3
#   2 preflight            :0 display; SporeApp.exe present; xdotool/maim/probe_tracer present
#   3 machine lock         lock.py acquire (held by another => exit 5 machine_locked)
#   4 window confinement   wine window pinned to 2304x1296+2561+144; drift => STOP
#   5 fixed key set        Return Escape Up Down Left Right only (no letters/digits)
#   6 visible overlay      red-bordered AGENT DRIVING window on top
#   7 global stop key      Ctrl+Alt+Backspace -> stop-state -> stop the walk
#   8 file surface         out/cell/<run>/ + /tmp/openspore-walk only
#
# Ladder per failing key step: 1 reassert focus (windowactivate --sync) +
# retry the key ONCE, 2 STOP input-no-response (record partial; no loop).
# Exit codes:
#   0 completed  2 usage  3 approval_required  5 machine_locked
#   6 stopped/failed (outcome in the manifest)
set -u

SELF=$(cd "$(dirname "$0")" && pwd)/$(basename "$0")
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/../.." && pwd)
OUT_BASE="$ROOT/tools/observatory/out/cell"
WALK_TMP="/tmp/openspore-walk"
STOP_FILE="$WALK_TMP/stop-state"
WALKER_PID_FILE="$WALK_TMP/walker.pid"
OVERLAY="$HERE/agent_overlay.py"
LOCKPY="$HERE/lock.py"
TRACER="$HERE/probe_tracer"
PROBE="$HERE/probes/cell_movement.json"
PROBE_JSONL="obs_cell_movement.jsonl"
PROBE_SET="cell_movement"
MODULE="SporeApp.exe"
EXE_REL="SPORE/SporeBin/SporeApp.exe"
ALLOWED_KEYS="Return Escape Up Down Left Right"
OVERLAY_GEOM="460x44+0+0"
# Primary-monitor pin rect, preflight-verified (S4 window geometry).
PIN_W=2304
PIN_H=1296
PIN_X=2561
PIN_Y=144
DURATION_DEFAULT=150
# The single CONTROL probe; every other fired probe is a cell-stage event.
ENTRY_PROBE_NAME="entry (bootstrap control)"

# Walk table "phase|key|note". key is 'none' for window/shot ops and the
# special token 'registration' for the allowlisted-bypass step. Only
# ALLOWED_KEYS may appear as a real key (validated per step at runtime).
STEPS_CELL='
boot|none|wineserver -k; probe_tracer --launch wine SporeApp.exe (the traced process)
pin|none|discover wine window (xdotool search --class sporeapp.exe; fallback --name Spore); pin to 2304x1296+2561+144
dismiss|Return|main menu: dismiss intro / accept prompt
registration|registration|allowlisted bypass: bounded Down/Return probe; blocked => registration_blocked
play|Down|menu: move down to Play
enter_play|Return|menu: enter Play
new_game|Down|menu: move down to New Game
start|Return|menu: start new game -> Cell Stage
settle|none|settle; final shot; cell_stage_reached from the cell_movement trace
'

usage() {
  sed -n '2,33p' "$SELF" | sed 's/^# \{0,2\}//'
}

validate_key() {
  for k in $ALLOWED_KEYS; do
    [ "$k" = "$1" ] && return 0
  done
  return 1
}

# A key is a letter/digit (i.e. TYPING) if it matches [A-Za-z0-9]. The allowlist
# is pure navigation keys, so validate_key() passing implies not typing; this
# predicate is the belt-and-suspenders guard the registration logic relies on.
key_is_typing() {
  case "$1" in
    *[A-Za-z0-9]*) return 0 ;;
  esac
  return 1
}

shot_line() { # seq path sha wall trace_t input geom prev_sha
  delta=false
  if [ -z "$8" ] || [ "$3" != "$8" ]; then delta=true; fi
  printf '{"seq":%s,"path":"%s","sha256":"%s","wall_clock":%s,"trace_t_nearest":%s,"input_event":"%s","window_geom":"%s","delta_vs_prev_sha":%s}\n' \
    "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$delta"
}

# registration-decision: the pure, testable heart of the registration gate.
# signal=advanced  -> the allowlisted probe advanced the form past registration
#                     => decision continue (keep walking toward Cell Stage).
# signal=persists  -> validation text persists / no field advances across the
#                     bounded probe => decision registration_blocked (STOP the
#                     walk; do NOT type letters/digits). The key sequence is
#                     always the allowlisted Down/Return probe; a letter/digit
#                     key is never emitted, so letters_or_digits is false by
#                     construction (asserted by the test).
registration_decision() { # signal
  sig="${1:-}"
  keys='["Down","Return","Down","Return","Down","Return"]'
  case "$sig" in
    advanced)
      printf '{"signal":"advanced","decision":"continue","keys":%s,"letters_or_digits":false}\n' "$keys"
      ;;
    persists)
      printf '{"signal":"persists","decision":"registration_blocked","keys":%s,"letters_or_digits":false}\n' "$keys"
      ;;
    *)
      printf 'error: unknown registration signal %s (expected advanced|persists)\n' "$sig" >&2
      return 2
      ;;
  esac
  return 0
}

# manifest_from: the pure, testable manifest builder. Counts each probe name in
# <jsonl> (one JSON object per line, each with a "name" field) and emits the
# S5 manifest (menu_walk.sh:231-244 shape PLUS the trace block). Deterministic:
# sorted keys + sorted probe counts; <run_id>/<duration>/<machine_locked> are
# caller-supplied so the output is byte-stable for a fixed input.
manifest_from() { # jsonl stage run_id duration machine_locked
  jsonl="$1"; stage="$2"; run_id="$3"; duration="$4"; machine_locked="$5"
  python3 - "$jsonl" "$stage" "$run_id" "$duration" "$machine_locked" <<'PY'
import json, sys
jsonl, stage, run_id, duration, machine_locked = sys.argv[1:6]
counts = {}
try:
    with open(jsonl) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            rec = json.loads(line)
            name = rec.get("name")
            if name:
                counts[name] = counts.get(name, 0) + 1
except Exception:
    pass
counts = dict(sorted(counts.items()))
if stage in ("true", "false"):
    cell_stage_reached = (stage == "true")
else:
    cell_stage_reached = stage  # registration_blocked | menu_only
manifest = {
    "schema": "observatory-s5-celltrace-1",
    "run_id": run_id,
    "scenario": "cell_movement",
    "outcome": "completed",
    "window": {"pinned_geom": "2304x1296+2561+144"},
    "trace": {
        "probe_set": "cell_movement",
        "jsonl": "obs_cell_movement.jsonl",
        "duration": int(duration),
        "cell_stage_reached": cell_stage_reached,
        "probe_event_counts": counts,
    },
    "lock_probe": {"machine_locked": machine_locked == "true"},
    "replayable": "input-logged; stage-deterministic; non-bit-exact",
    "proprietary_bytes_added": False,
}
print(json.dumps(manifest, indent=2, sort_keys=True))
PY
}

# ---- dry run: enumerate the full plan; issues nothing -------------------- #
dry_run() {
  echo "cell_trace DRY RUN (S5: real Cell runtime evidence) — no xdotool events,"
  echo "no probe_tracer, no wine, no overlay, no shots, no lock: safe on any machine."
  echo "gate:     real run needs --approve AND OPENSPORE_MCP_TRUSTED=1, else exit 3 approval_required"
  echo "preflight: :0 display; $EXE_REL present; xdotool/maim/probe_tracer present; else non-zero exit"
  echo "lock:     lock.py acquire (held by another => exit 5 machine_locked); released before the closing probe"
  echo "launch:   probe_tracer --launch wine --launch-arg $EXE_REL"
  echo "          probes/cell_movement.json <out>/$PROBE_JSONL --duration ${DURATION} --module $MODULE --wait-module 60"
  echo "window:   xdotool search --class sporeapp.exe (fallback --name Spore); marker swapchain_resize_buffers in stderr"
  echo "pin:      windowmove $PIN_X $PIN_Y; windowsize $PIN_W $PIN_H (NOT WM maximize); per-step geometry drift => STOP"
  echo "input:    FOCUSED-window path only: xdotool windowactivate --sync \$WIN then xdotool key --clearmodifiers <key>"
  echo "          (the XSendEvent window-targeted form is deliberately absent)"
  echo "keys:     allowlist: $ALLOWED_KEYS (validated per step; violation => STOP; no letters/digits)"
  echo "registration: bounded Down/Return probe x3; advanced=>continue | persists=>registration_blocked (honest negative)"
  echo "stop:     Ctrl+Alt+Backspace (overlay grab) -> stop-state -> STOP the walk"
  echo "ladder:   no-op (shot sha == prev) => 1 reassert focus (windowactivate --sync) + retry key ONCE, 2 STOP input-no-response"
  echo "stage:    cell_stage_reached = true if any non-control cell probe fired; else menu_only; registration_blocked if the gate stopped the walk"
  echo "manifest: <out>/<run>/manifest.json {run_id, scenario, outcome, trace{probe_set,jsonl,duration,cell_stage_reached,probe_event_counts}, lock_probe{machine_locked:false}}"
  echo "surface:  $OUT_BASE/<run>/ (manifest.json, shots.jsonl, input.jsonl, shot_NNN.png, $PROBE_JSONL) + $WALK_TMP"
  echo
  echo "planned steps (each: stop-state poll -> drift check -> input log -> command(s) -> settle -> shot):"
  seq=0
  while IFS='|' read -r phase key note; do
    [ -z "$phase" ] && continue
    case "$key" in
      none)
        printf '  [%02d] %-13s op=%-13s target=<pinned wine window>  (%s)\n' "$seq" "$phase" "$phase" "$note"
        ;;
      registration)
        seq=$((seq + 1))
        printf '  [%02d] %-13s registration probe x3 (bounded allowlisted bypass):\n' "$seq" "$phase"
        printf '         xdotool windowactivate --sync $WIN\n'
        printf '         xdotool key --clearmodifiers Down\n'
        printf '         xdotool key --clearmodifiers Return\n'
        printf '         (repeat x3; decision advanced=>continue | persists=>registration_blocked; never a letter/digit)\n'
        ;;
      *)
        seq=$((seq + 1))
        printf '  [%02d] %-13s key=%-9s ts=<wall at run> target=$WIN shot=seq-%03d  (%s)\n' \
          "$seq" "$phase" "$key" "$seq" "$note"
        printf '         xdotool windowactivate --sync $WIN\n'
        printf '         xdotool key --clearmodifiers %s\n' "$key"
        printf '         no-op check: shot sha vs prev; ladder 1=reassert focus+retry  2=STOP input-no-response\n'
        ;;
    esac
  done <<EOF
$STEPS_CELL
EOF
  echo
  echo "dry run complete: 0 events issued."
}

# ---- real run state ------------------------------------------------------ #
WIN=""
PIN_GEOM=""
TRACER_PID=""
OVERLAY_PID=""
LOCK_PID=""
OUTCOME="running"
RUN_ID="S5-$(date -u +%Y%m%dT%H%M%SZ)-$$"
OUT_DIR=""
MANIFEST=""
INPUT_LOG=""
SHOTS_FILE=""
PREV_SHA=""
REG_BLOCKED=0
REG_SIGNAL=""
WALK_ACTIVE=0

on_exit() {
  [ "$WALK_ACTIVE" = "1" ] || return 0
  WALK_ACTIVE=0
  [ -n "$TRACER_PID" ] && kill -9 "$TRACER_PID" 2>/dev/null
  wineserver -k 2>/dev/null || true
  [ -n "$OVERLAY_PID" ] && kill "$OVERLAY_PID" 2>/dev/null
  python3 "$OVERLAY" --stop 2>/dev/null || true
  [ -n "$LOCK_PID" ] && kill "$LOCK_PID" 2>/dev/null
  return 0
}
# SIGTERM/SIGINT must STOP the walk (the overlay stop-key chain sends TERM);
# a trap that only cleans up would let the walk resume and keep issuing events.
trap on_exit EXIT
trap 'on_exit; exit 130' INT
trap 'on_exit; exit 143' TERM

stop_chain() { # outcome
  OUTCOME="$1"
  printf 'STOP: %s\n' "$1" >&2
  exit 6
}

check_stop() {
  [ -f "$STOP_FILE" ] && stop_chain stopped_by_human
}

log_input() { # target cmd
  printf '{"ts":%s,"target":"%s","cmd":"%s"}\n' \
    "$(date +%s)" "$1" "$2" >> "$INPUT_LOG"
}

win_geom() {
  xwininfo -id "$1" 2>/dev/null | awk '
    /^ *Width:/     {w=$2}
    /^ *Height:/    {h=$2}
    /^ *X origin:/  {x=$3}
    /^ *Y origin:/  {y=$3}
    /^ *Absolute upper-left X:/ {x=$4}
    /^ *Absolute upper-left Y:/ {y=$4}
    END {if (w && h) print w "x" h "+" x "+" y}'
}

take_shot() { # seq input_event
  f="$OUT_DIR/shot_$(printf '%03d' "$1").png"
  if ! maim -i "$WIN" "$f" 2>/dev/null; then
    printf 'shot %s failed (window %s)\n' "$1" "$WIN" >&2
    return 1
  fi
  sha=$(sha256sum "$f" | cut -d' ' -f1)
  "$SELF" --shot-line "$1" "$f" "$sha" "$(date +%s)" "$(date +%s)" \
    "$2" "$(win_geom "$WIN")" "$PREV_SHA" >> "$SHOTS_FILE"
  PREV_SHA=$sha
  return 0
}

# One focused-window key event: assert focus to the pinned window, then send the
# key to the FOCUSED window (S4-approved path). The XSendEvent --window form is
# deliberately NOT used here.
emit_key() { # key
  validate_key "$1" || stop_chain key-violation
  log_input "$WIN" "xdotool windowactivate --sync $WIN; key --clearmodifiers $1"
  xdotool windowactivate --sync "$WIN"
  xdotool key --clearmodifiers "$1" &
  wait $!
  sleep 0.3
}

# registration step: bounded allowlisted bypass (Down/Return x3). Computes the
# observed signal (advanced|persists) from the shot hashes and applies the pure
# decision. A TYPING gate (validation text persists, no field advances) is
# recorded as registration_blocked; no letter/digit key is ever emitted.
registration_step() {
  base_sha="$PREV_SHA"
  reg_i=0
  reg_stable=1
  while [ "$reg_i" -lt 3 ]; do
    reg_i=$((reg_i + 1))
    check_stop
    emit_key Down
    emit_key Return
    shot_seq=$((shot_seq + 1))
    take_shot "$shot_seq" "registration:probe$reg_i" || stop_chain shot-failed
    if [ -n "$base_sha" ] && [ "$PREV_SHA" != "$base_sha" ]; then
      reg_stable=0   # the frame changed: a field advanced / form moved
    fi
  done
  if [ "$reg_stable" = "1" ]; then
    REG_SIGNAL="persists"
  else
    REG_SIGNAL="advanced"
  fi
  decision=$("$SELF" --registration-decision "$REG_SIGNAL")
  printf 'registration signal=%s decision-line: %s\n' "$REG_SIGNAL" "$decision"
  case "$decision" in
    *registration_blocked*)
      REG_BLOCKED=1
      ;;
  esac
}

walk_steps() {
  shot_seq=0
  while IFS='|' read -r phase key note; do
    [ -z "$phase" ] && continue
    check_stop
    g=$(win_geom "$WIN")
    if [ -n "$PIN_GEOM" ] && [ "$g" != "$PIN_GEOM" ]; then
      stop_chain geometry-drift
    fi
    case "$phase" in
      boot|pin)
        : # already done in do_run before this loop
        ;;
      settle)
        sleep 0.3
        shot_seq=$((shot_seq + 1))
        take_shot "$shot_seq" "settle" || stop_chain shot-failed
        ;;
      registration)
        registration_step
        if [ "$REG_BLOCKED" = "1" ]; then
          printf 'registration_blocked: stopping walk (honest negative; no typing)\n'
          OUTCOME_CELL="registration_blocked"
          return 0
        fi
        ;;
      *)
        prev_before=$PREV_SHA
        emit_key "$key"
        shot_seq=$((shot_seq + 1))
        take_shot "$shot_seq" "key:$key" || stop_chain shot-failed
        if [ -n "$prev_before" ] && [ "$PREV_SHA" = "$prev_before" ]; then
          printf 'step %s: no-op; ladder 1 reassert focus + retry once\n' "$phase"
          xdotool windowactivate --sync "$WIN"
          log_input "$WIN" "xdotool windowactivate --sync $WIN; key --clearmodifiers $key (reassert)"
          xdotool key --clearmodifiers "$key" &
          wait $!
          sleep 0.3
          prev_before=$PREV_SHA
          shot_seq=$((shot_seq + 1))
          take_shot "$shot_seq" "key:$key:reassert"
          if [ -n "$prev_before" ] && [ "$PREV_SHA" = "$prev_before" ]; then
            stop_chain input-no-response
          fi
        fi
        ;;
    esac
  done <<EOF
$STEPS_CELL
EOF
  OUTCOME_CELL="menu_only"
  return 0
}

# Cell-stage determination from the trace: any fired probe that is NOT the
# control entry probe means a per-frame cell-stage function ran.
determine_cell_stage() {
  python3 - "$OUT_DIR/$PROBE_JSONL" "$ENTRY_PROBE_NAME" <<'PY'
import json, sys
f, entry_name = sys.argv[1], sys.argv[2]
cell = 0
try:
    for line in open(f):
        line = line.strip()
        if not line:
            continue
        rec = json.loads(line)
        if rec.get("name") != entry_name:
            cell += 1
except Exception:
    pass
print("true" if cell > 0 else "false")
PY
}

write_manifest() { # stage machine_locked
  stage="$1"; machine_locked="$2"
  [ -n "$MANIFEST" ] || return 0
  [ "$OUTCOME" = "running" ] && OUTCOME="completed"
  "$SELF" --manifest "$OUT_DIR/$PROBE_JSONL" "$stage" "$RUN_ID" "$DURATION" "$machine_locked" \
    > "$MANIFEST"
  printf 'manifest: %s (outcome=%s cell_stage_reached=%s)\n' "$MANIFEST" "$OUTCOME" "$stage"
}

do_run() {
  WALK_ACTIVE=1
  mkdir -p "$OUT_DIR" "$WALK_TMP"
  : > "$INPUT_LOG"
  : > "$SHOTS_FILE"
  echo "$$" > "$WALKER_PID_FILE"
  rm -f "$STOP_FILE"
  printf 'run %s started (cell_movement, duration %ss)\n' "$RUN_ID" "$DURATION"

  # 1. fresh wineserver generation, then launch THROUGH the tracer (the walk
  #    and the trace share this one traced process).
  wineserver -k 2>/dev/null || true
  : > "$OUT_DIR/wine_stderr.log"
  : > "$OUT_DIR/wine_stdout.log"
  ( cd "$ROOT" && "$TRACER" --launch wine --launch-arg "$EXE_REL" \
      "$PROBE" "$OUT_DIR/$PROBE_JSONL" \
      --duration "$DURATION" --module "$MODULE" --wait-module 60 \
      > "$OUT_DIR/wine_stdout.log" 2> "$OUT_DIR/wine_stderr.log" ) &
  TRACER_PID=$!

  # 2. find the wine window (--class primary; --name loose fallback).
  WIN=""
  deadline=$(( $(date +%s) + 90 ))
  while [ "$(date +%s)" -lt "$deadline" ]; do
    WIN=$(xdotool search --class sporeapp.exe 2>/dev/null | head -1 || true)
    [ -n "$WIN" ] || WIN=$(xdotool search --name Spore 2>/dev/null | head -1 || true)
    [ -n "$WIN" ] && break
    sleep 1
  done
  [ -n "$WIN" ] || stop_chain window-not-found
  printf 'window %s found\n' "$WIN"

  # 3. renderer marker (fail-closed on boot-stall / missing renderer).
  sleep 5
  if ! grep -q swapchain_resize_buffers "$OUT_DIR/wine_stderr.log" 2>/dev/null; then
    stop_chain renderer-marker-absent
  fi

  # 4. pin the window to the primary rect (NOT WM maximize).
  log_input "$WIN" "xdotool windowmove $WIN $PIN_X $PIN_Y; windowsize $WIN $PIN_W $PIN_H"
  xdotool windowmove "$WIN" "$PIN_X" "$PIN_Y"
  xdotool windowsize "$WIN" "$PIN_W" "$PIN_H"
  sleep 0.3
  PIN_GEOM=$(win_geom "$WIN")
  [ -n "$PIN_GEOM" ] || stop_chain pin-failed
  printf 'pinned window %s at %s\n' "$WIN" "$PIN_GEOM"

  # 5. overlay on top, before any input.
  python3 "$OVERLAY" --start "$OVERLAY_GEOM" &
  OVERLAY_PID=$!
  sleep 0.5

  # 6. walk (focused-window path; registration gate; per-step observability).
  OUTCOME_CELL="menu_only"
  walk_steps

  # 7. determine cell_stage_reached from the trace, then reconcile the gate.
  if [ "$OUTCOME_CELL" = "registration_blocked" ]; then
    STAGE="registration_blocked"
  else
    STAGE=$(determine_cell_stage)
    [ "$STAGE" = "true" ] || STAGE="menu_only"
  fi

  OUTCOME="completed"
  printf 'walk completed (cell_stage_reached=%s)\n' "$STAGE"

  # 8. teardown: kill the traced game, fresh-kill the wineserver, stop overlay.
  [ -n "$TRACER_PID" ] && kill -9 "$TRACER_PID" 2>/dev/null
  wineserver -k 2>/dev/null || true
  [ -n "$OVERLAY_PID" ] && kill "$OVERLAY_PID" 2>/dev/null
  python3 "$OVERLAY" --stop 2>/dev/null || true
  WALK_ACTIVE=0

  # 9. release the machine lock, then probe: assert machine_locked=false.
  [ -n "$LOCK_PID" ] && kill "$LOCK_PID" 2>/dev/null
  probe_line=$(python3 "$LOCKPY" probe 2>/dev/null)
  if printf '%s' "$probe_line" | grep -q '"machine_locked": *false'; then
    ML="false"
  else
    ML="true"
  fi
  printf 'post-teardown lock probe: %s\n' "$probe_line"

  # 10. manifest.
  write_manifest "$STAGE" "$ML"
  return 0
}

preflight() {
  case "${DISPLAY:-}" in
    :0|:0.*) : ;;
    *)
      printf '{"status":"error","code":"preflight","message":"display must be :0 (got %s)"}\n' "${DISPLAY:-unset}"
      return 1 ;;
  esac
  [ -f "$ROOT/$EXE_REL" ] || {
    printf '{"status":"error","code":"preflight","message":"missing %s"}\n' "$ROOT/$EXE_REL"; return 1; }
  command -v xdotool >/dev/null 2>&1 || { printf '{"status":"error","code":"preflight","message":"xdotool not found"}\n'; return 1; }
  command -v maim >/dev/null 2>&1 || { printf '{"status":"error","code":"preflight","message":"maim not found"}\n'; return 1; }
  [ -x "$TRACER" ] || { printf '{"status":"error","code":"preflight","message":"probe_tracer not built (%s)"}\n' "$TRACER"; return 1; }
  return 0
}

# ---- dispatch ------------------------------------------------------------ #
DRY=0
APPROVE=0
DURATION="$DURATION_DEFAULT"
MODE=""

while [ $# -gt 0 ]; do
  case "$1" in
    --dry-run) DRY=1 ;;
    --approve) APPROVE=1 ;;
    --duration) shift; DURATION="${1:-$DURATION_DEFAULT}" ;;
    --validate-key)
      shift
      if validate_key "${1:-}"; then
        printf 'key %s allowed\n' "${1:-}"
      else
        printf 'key %s rejected (allowlist: %s)\n' "${1:-}" "$ALLOWED_KEYS" >&2
        exit 2
      fi
      exit 0
      ;;
    --registration-decision)
      shift
      registration_decision "${1:-}"
      exit $?
      ;;
    --manifest)
      shift
      if [ $# -lt 5 ]; then usage; exit 2; fi
      manifest_from "$@"
      exit $?
      ;;
    --shot-line)
      shift
      if [ $# -lt 8 ]; then usage; exit 2; fi
      case "$1$4$5" in
        ""|*[!0-9]*) usage; exit 2 ;;
      esac
      shot_line "$@"
      exit 0
      ;;
    -h|--help) usage; exit 0 ;;
    *) usage; exit 2 ;;
  esac
  shift
done

if [ "$DRY" = "1" ]; then
  dry_run
  exit 0
fi

# real run: preflight (fail-closed), approval gate, machine lock, then run.
if ! preflight; then
  exit 1
fi

if [ "$APPROVE" != "1" ] || [ "${OPENSPORE_MCP_TRUSTED:-}" != "1" ]; then
  printf '{"status":"error","code":"approval_required","message":"boots the original SporeApp.exe under Wine, walks to Cell Stage, captures the cell_movement probe trace (~%ss on shared :0). pass --approve and set OPENSPORE_MCP_TRUSTED=1 after explicit human sign-off"}\n' "$DURATION"
  exit 3
fi

# machine lock: refuse if already held, else acquire (held in a background
# holder; released explicitly before the closing probe so the probe reads false).
if python3 "$LOCKPY" probe | grep -q '"machine_locked": *false'; then
  :
else
  printf '{"status":"error","code":"machine_locked","message":"shared display/GPU busy (lock held); park, no attempt burn"}\n'
  exit 5
fi

OUT_DIR="$OUT_BASE/$RUN_ID"
MANIFEST="$OUT_DIR/manifest.json"
INPUT_LOG="$OUT_DIR/input.jsonl"
SHOTS_FILE="$OUT_DIR/shots.jsonl"

python3 "$LOCKPY" acquire cell_trace --task-id "$RUN_ID" &
LOCK_PID=$!
sleep 0.3   # let the holder settle the flock before we rely on it

do_run
exit $?
