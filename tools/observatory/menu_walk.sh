#!/bin/sh
# menu_walk.sh — committed GUI automation shell: main menu -> Cell Stage
# walk on :0 under Wine (docs/analysis/GUI-BOUNDARY.md §6,
# docs/RE-AUTOMATION-ARCHITECTURE.md §8). One reviewable script; the
# overlay (agent_overlay.py) is the second, visible, stoppable component.
#
# Usage:
#   menu_walk.sh --dry-run [--scenario NAME]
#   menu_walk.sh --approve --scenario NAME
#   menu_walk.sh --validate-key <key>
#   menu_walk.sh --shot-line <seq> <path> <sha> <wall> <trace_t> <input> <geom> <prev_sha>
#
# A real walk requires --approve AND OPENSPORE_MCP_TRUSTED=1 (the MCP gate
# semantics of tools/mcp/safety.py). Every key event is validated against a
# fixed allowlist, --window-targeted, and logged BEFORE it is issued.
#
# Safety (all fail-closed):
#   1 approval gate        --approve + OPENSPORE_MCP_TRUSTED=1, else exit 3
#   2 window confinement   wine window pinned to a fixed rect at start;
#                          geometry drift vs pin => STOP
#   3 fixed key set        Return Escape Up Down Left Right only
#   4 visible overlay      red-bordered AGENT DRIVING window on top
#   5 global stop key      Ctrl+Alt+Backspace -> stop-state -> SIGTERM
#                          walker -> SIGKILL wine -> wineserver -k
#   6 file surface         out/shots/<run>/ + /tmp/openspore-walk only
#   7 reviewability        this script + the overlay, both committed
#
# Ladder per failing step: 1 reassert+retry once, 2 fresh wineserver -k
# generation once, 3 STOP + negative recorded. Exit codes:
#   0 completed  2 usage  3 approval_required  5 machine_locked
#   6 stopped/failed (outcome in the manifest)
set -u

SELF=$(cd "$(dirname "$0")" && pwd)/$(basename "$0")
HERE=$(cd "$(dirname "$0")" && pwd)
ROOT=$(cd "$HERE/../.." && pwd)
OUT_BASE="$ROOT/tools/observatory/out/shots"
WALK_TMP="/tmp/openspore-walk"
STOP_FILE="$WALK_TMP/stop-state"
WALKER_PID_FILE="$WALK_TMP/walker.pid"
OVERLAY="$HERE/agent_overlay.py"
LOCKPY="$HERE/lock.py"
ALLOWED_KEYS="Return Escape Up Down Left Right"
OVERLAY_GEOM="460x44+0+0"

# Walk table "phase|key|note". key is 'none' for window ops.
# Only ALLOWED_KEYS may appear (validated per step at runtime).
STEPS_MAIN_MENU='
boot|none|wineserver -k, fresh wine generation, boot SporeApp.exe
pin|none|discover wine window (xdotool search), baseline geometry
maximize|none|pin window to primary monitor rect (xrandr), no WM dependency
dismiss|Return|main menu: dismiss intro / accept prompt
play|Down|menu: move down to Play
enter_play|Return|menu: enter Play
new_game|Down|menu: move down to New Game
start|Return|menu: start new game -> Cell Stage
settle|none|settle 300ms after last input before final shot
'

usage() {
  sed -n '2,20p' "$SELF" | sed 's/^# \{0,2\}//'
}

validate_key() {
  for k in $ALLOWED_KEYS; do
    [ "$k" = "$1" ] && return 0
  done
  return 1
}

shot_line() { # seq path sha wall trace_t input geom prev_sha
  delta=false
  if [ -z "$8" ] || [ "$3" != "$8" ]; then delta=true; fi
  printf '{"seq":%s,"path":"%s","sha256":"%s","wall_clock":%s,"trace_t_nearest":%s,"input_event":"%s","window_geom":"%s","delta_vs_prev_sha":%s}\n' \
    "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$delta"
}

# ---- dry run: enumerate the full plan; issues nothing -------------------- #
dry_run() {
  echo "menu_walk DRY RUN (scenario: $SCENARIO) — no xdotool events, no wine,"
  echo "no overlay, no shots, no lock: safe on any machine."
  echo "gate:     real walk needs --approve AND OPENSPORE_MCP_TRUSTED=1, else exit 3 approval_required"
  echo "lock:     flock /tmp/openspore-machine.lock body {pid,label,ts,task_id}; held => exit 5 machine_locked (park)"
  echo "stop:     Ctrl+Alt+Backspace (overlay grab) -> stop-state file -> SIGTERM walker -> SIGKILL wine -> wineserver -k"
  echo "window:   pin to primary monitor rect (xrandr); per-step drift vs pin => STOP geometry-drift"
  echo "keys:     allowlist: $ALLOWED_KEYS (validated per step; violation => STOP)"
  echo "surface:  $OUT_BASE/<run>/ (manifest.json, shots.jsonl, input.jsonl, shot_NNN.png) + $WALK_TMP"
  echo "ladder:   no-op (sha == prev) => 1 reassert+retry once, 2 fresh wineserver -k generation once, 3 STOP input-no-response"
  echo "shots:    maim -i <window> per step; sha256 manifest; delta_vs_prev_sha; trace_t_nearest=wall_clock"
  echo
  echo "planned steps (each: stop-state poll -> drift check -> input log -> event -> settle -> shot):"
  seq=0
  while IFS='|' read -r phase key note; do
    [ -z "$phase" ] && continue
    if [ "$key" = "none" ]; then
      printf '  [%02d] %-11s op=%-9s ts=<wall at run> target=<pinned wine window>  (%s)\n' \
        "$seq" "$phase" "$phase" "$note"
    else
      seq=$((seq + 1))
      printf '  [%02d] %-11s key=%-9s ts=<wall at run> target=$WIN shot=seq-%03d  (%s)\n' \
        "$seq" "$phase" "$key" "$seq" "$note"
      printf '         no-op check: sha vs prev; ladder 1=reassert+retry  2=fresh generation  3=STOP\n'
    fi
  done <<EOF
$STEPS_MAIN_MENU
EOF
  echo
  echo "dry run complete: 0 events issued."
}

# ---- real walk ------------------------------------------------------------ #
WIN=""
PIN_GEOM=""
WINE_PID=""
OUTCOME="running"
RUN_ID="walk_$(date +%Y%m%d-%H%M%S)_$$"
SHOTS_DIR=""
MANIFEST=""
INPUT_LOG=""
PREV_SHA=""

write_manifest() {
  [ -n "$MANIFEST" ] || return 0
  [ "$OUTCOME" = "running" ] && OUTCOME="interrupted"
  {
    printf '{\n'
    printf '  "run_id": "%s",\n' "$RUN_ID"
    printf '  "scenario": "%s",\n' "$SCENARIO"
    printf '  "outcome": "%s",\n' "$OUTCOME"
    printf '  "window": {"id": "%s", "pinned_geom": "%s"},\n' "$WIN" "$PIN_GEOM"
    printf '  "shots_dir": "%s",\n' "$SHOTS_DIR"
    printf '  "replayable": "input-logged; stage-deterministic; non-bit-exact"\n'
    printf '}\n'
  } > "$MANIFEST"
  printf 'manifest: %s (outcome=%s)\n' "$MANIFEST" "$OUTCOME"
}

WALK_ACTIVE=0

on_exit() {
  [ "$WALK_ACTIVE" = "1" ] || return 0
  WALK_ACTIVE=0
  if [ -n "${WINE_PID:-}" ]; then kill -9 "$WINE_PID" 2>/dev/null; fi
  wineserver -k 2>/dev/null || true
  python3 "$OVERLAY" --stop 2>/dev/null || true
  write_manifest
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
  if [ -f "$STOP_FILE" ]; then
    stop_chain stopped_by_human
  fi
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

primary_rect() { # W H X Y of the first connected output
  xrandr -q 2>/dev/null | grep -E '^[^ ]+ connected [0-9]+x[0-9]+\+[0-9-]+\+[0-9-]+' \
    | head -1 | awk '{split($3, g, /[x+]/); print g[1], g[2], g[3], g[4]}'
}

take_shot() { # seq input_event
  f="$SHOTS_DIR/shot_$(printf '%03d' "$1").png"
  if ! maim -i "$WIN" "$f" 2>/dev/null; then
    printf 'shot %s failed (window %s)\n' "$1" "$WIN" >&2
    return 1
  fi
  sha=$(sha256sum "$f" | cut -d' ' -f1)
  "$SELF" --shot-line "$1" "$f" "$sha" "$(date +%s)" "$(date +%s)" \
    "$2" "$(win_geom "$WIN")" "$PREV_SHA" >> "$SHOTS_DIR/shots.jsonl"
  PREV_SHA=$sha
  return 0
}

boot_game() { # fresh generation: wineserver -k -> wine -> discover window
  wineserver -k 2>/dev/null || true
  wineserver -v > "$WALK_TMP/wineserver.log" 2>&1 || true
  : > "$WALK_TMP/wine_stderr.log"
  WINEDEBUG=+d3d wine "$ROOT/SPORE/SporeBin/SporeApp.exe" \
    > "$WALK_TMP/wine_stdout.log" 2>> "$WALK_TMP/wine_stderr.log" &
  WINE_PID=$!
  wineserver -v >> "$WALK_TMP/wineserver.log" 2>&1 || true
  WIN=""
  deadline=$(( $(date +%s) + 60 ))
  while [ "$(date +%s)" -lt "$deadline" ]; do
    WIN=$(xdotool search --name Spore 2>/dev/null | head -1 || true)
    [ -n "$WIN" ] && break
    sleep 1
  done
  if [ -z "$WIN" ]; then
    return 1
  fi
  sleep 5
  if ! grep -q swapchain_resize_buffers "$WALK_TMP/wine_stderr.log" 2>/dev/null; then
    printf 'renderer marker (swapchain_resize_buffers) absent\n' >&2
    return 2
  fi
  return 0
}

walk() {
  WALK_ACTIVE=1
  mkdir -p "$SHOTS_DIR" "$WALK_TMP"
  : > "$INPUT_LOG"
  echo "$$" > "$WALKER_PID_FILE"
  rm -f "$STOP_FILE"
  printf 'run %s started (scenario %s)\n' "$RUN_ID" "$SCENARIO"

  # boot (ladder 2/3 if it stalls; marker check)
  # A window found BEFORE this generation's wine proved itself (renderer
  # marker) may be a foreign "Spore" window; a failed generation must stop
  # the walk, not fall through to pin+drive whatever name matched.
  boot_game
  rc=$?
  if [ "$rc" != "0" ]; then
    printf 'boot failed (rc=%s); fresh generation once\n' "$rc"
    boot_game
    rc=$?
    [ "$rc" = "0" ] || stop_chain boot-stall
  fi

  # pin: primary monitor rect, re-read actual geometry as the baseline
  set -- $(primary_rect)
  [ -n "${1:-}" ] || stop_chain no-monitor
  log_input "$WIN" "xdotool windowmove $WIN $3 $4; windowsize $WIN $1 $2"
  xdotool windowmove "$WIN" "$3" "$4"
  xdotool windowsize "$WIN" "$1" "$2"
  sleep 0.3
  PIN_GEOM=$(win_geom "$WIN")
  [ -n "$PIN_GEOM" ] || stop_chain pin-failed
  printf 'pinned window %s at %s\n' "$WIN" "$PIN_GEOM"

  # overlay on top of the pinned window, before any input
  python3 "$OVERLAY" --start "$OVERLAY_GEOM" &
  sleep 0.5

  # steps
  shot_seq=0
  while IFS='|' read -r phase key note; do
    [ -z "$phase" ] && continue
    check_stop
    g=$(win_geom "$WIN")
    if [ "$g" != "$PIN_GEOM" ]; then
      stop_chain geometry-drift
    fi
    case "$phase" in
      boot|pin|maximize)
        : # already done above
        ;;
      settle)
        sleep 0.3
        shot_seq=$((shot_seq + 1))
        take_shot "$shot_seq" "settle"
        ;;
      *)
        if ! validate_key "$key"; then
          stop_chain key-violation
        fi
        log_input "$WIN" "xdotool key --clearmodifiers --window $WIN $key"
        printf 'step %-11s key=%s target=%s\n' "$phase" "$key" "$WIN"
        # Background+wait so a trapped SIGTERM/SIGINT interrupts the step
        # immediately (a foreground child defers the trap until it returns).
        xdotool key --clearmodifiers --window "$WIN" "$key" &
        wait $!
        sleep 0.3
        prev_before=$PREV_SHA
        shot_seq=$((shot_seq + 1))
        take_shot "$shot_seq" "key:$key" || stop_chain shot-failed
        # no-op check + ladder: no delta after an input = first-class negative
        if [ -n "$prev_before" ] && [ "$PREV_SHA" = "$prev_before" ]; then
          printf 'step %s: no-op; ladder 1 reassert+retry\n' "$phase"
          log_input "$WIN" "xdotool key --clearmodifiers --window $WIN $key (reassert)"
          xdotool key --clearmodifiers --window "$WIN" "$key" &
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
$STEPS_MAIN_MENU
EOF

  OUTCOME="completed"
  printf 'walk completed\n'
  return 0
}

# ---- dispatch ------------------------------------------------------------- #
DRY=0
APPROVE=0
SCENARIO="main_menu"
MODE=""

while [ $# -gt 0 ]; do
  case "$1" in
    --dry-run) DRY=1 ;;
    --approve) APPROVE=1 ;;
    --scenario) shift; SCENARIO="${1:-}" ;;
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
    --shot-line)
      shift
      if [ $# -lt 8 ]; then usage; exit 2; fi
      # seq, wall_clock and trace_t_nearest must be numeric: a malformed
      # manifest line must be rejected, not written into shots.jsonl.
      case "$1$4$5" in
        ""|*[!0-9]*) usage; exit 2 ;;
      esac
      shot_line "$@"
      exit 0
      ;;
    --walk) MODE="walk" ;;
    -h|--help) usage; exit 0 ;;
    *) usage; exit 2 ;;
  esac
  shift
done

if [ "$DRY" = "1" ]; then
  dry_run
  exit 0
fi

if [ "$MODE" = "walk" ]; then
  # --walk is the post-gate re-exec entry: only the gated path below exports
  # OPENSPORE_WALK_LOCKED=1 before it. Invoking it directly skips the approval
  # gate and the machine lock, so refuse fail-closed.
  if [ "${OPENSPORE_WALK_LOCKED:-}" != "1" ]; then
    printf '{"status":"error","code":"approval_required","message":"--walk is the post-gate re-exec entry; invoke with --approve and OPENSPORE_MCP_TRUSTED=1"}\n'
    exit 3
  fi
  SHOTS_DIR="$OUT_BASE/$RUN_ID"
  MANIFEST="$SHOTS_DIR/manifest.json"
  INPUT_LOG="$SHOTS_DIR/input.jsonl"
  walk
  exit $?
fi

# real walk: approval gate (fail-closed), then lock, then walk
if [ "$APPROVE" != "1" ] || [ "${OPENSPORE_MCP_TRUSTED:-}" != "1" ]; then
  printf '{"status":"error","code":"approval_required","message":"pass --approve and set OPENSPORE_MCP_TRUSTED=1"}\n'
  exit 3
fi
if [ "${OPENSPORE_WALK_LOCKED:-}" != "1" ]; then
  export OPENSPORE_WALK_LOCKED=1 RUN_ID
  exec python3 "$LOCKPY" acquire menu_walk --task-id "$RUN_ID" \
    -- "$SELF" --walk --scenario "$SCENARIO"
fi
SHOTS_DIR="$OUT_BASE/$RUN_ID"
MANIFEST="$SHOTS_DIR/manifest.json"
INPUT_LOG="$SHOTS_DIR/input.jsonl"
walk
exit $?
