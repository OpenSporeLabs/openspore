#!/usr/bin/env python3
"""agent_overlay.py — visible AGENT DRIVING overlay (python3-xlib, stdlib).

Usage:
    agent_overlay.py --start <WxH+X+Y>   map overlay + grab Ctrl+Alt+Backspace
    agent_overlay.py --stop              SIGTERM the running overlay
    agent_overlay.py --selftest          start/verify/stop a test overlay on :0

On the global stop key: writes /tmp/openspore-walk/stop-state, SIGTERMs the
walker (if any), tears the window down. The overlay is override-redirect
(above KWin, borderless) with a red border so an agent-driven window is
never mistaken for human input.
"""
import json
import os
import signal
import subprocess
import sys
import time

WALK_TMP = "/tmp/openspore-walk"
STOP_FILE = os.path.join(WALK_TMP, "stop-state")
PID_FILE = os.path.join(WALK_TMP, "overlay.pid")
WALKER_PID_FILE = os.path.join(WALK_TMP, "walker.pid")
TEXT = b"AGENT DRIVING - press Ctrl+Alt+Backspace to stop"


def _geom(spec):
    parts = spec.split("+")
    if len(parts) != 3:
        raise ValueError("geometry must be WxH+X+Y")
    w, h = parts[0].split("x")
    return int(w), int(h), int(parts[1]), int(parts[2])


def _cleanup():
    for p in (PID_FILE,):
        try:
            os.unlink(p)
        except OSError:
            pass


def _sigterm_walker():
    try:
        with open(WALKER_PID_FILE) as f:
            os.kill(int(f.read().strip()), signal.SIGTERM)
    except (OSError, ValueError):
        pass


def start(spec):
    from Xlib import X, XK, display
    from Xlib.protocol import request
    os.makedirs(WALK_TMP, exist_ok=True)
    with open(PID_FILE, "w") as f:
        f.write(str(os.getpid()))
    d = display.Display()
    scr = d.screen()
    root = scr.root
    font = d.open_font("fixed")
    w, h, x, y = _geom(spec)
    win = root.create_window(x, y, w, h, 4, scr.root_depth, X.InputOutput,
                             X.CopyFromParent, event_mask=X.KeyPressMask,
                             override_redirect=True, border_color=0xFF0000)
    gc = win.create_gc(background=0x101010, foreground=0xFFFFFF)
    request.ImageText8(display=d.display, x=10, y=14, drawable=win,
                       gc=gc, font=font, string=TEXT)
    win.map()
    d.flush()
    print("overlay wid=%d" % win.id, flush=True)
    keycode = d.keysym_to_keycode(XK.XK_BackSpace)
    root.grab_key(keycode, X.AnyModifier, True, X.GrabModeAsync,
                  X.GrabModeAsync)
    d.flush()

    def teardown():
        try:
            win.destroy()
            d.flush()
        finally:
            d.close()
            _cleanup()
            sys.exit(0)

    signal.signal(signal.SIGTERM, lambda s, f: teardown())
    while True:
        ev = d.next_event()
        if ev.type == X.KeyPress and ev.detail == keycode \
                and (ev.state & (X.ControlMask | X.Mod1Mask)) \
                == (X.ControlMask | X.Mod1Mask):
            break
    with open(STOP_FILE, "w") as f:
        json.dump({"ts": time.time(), "reason": "ctrl+alt+backspace"}, f)
    _sigterm_walker()
    teardown()


def stop():
    try:
        with open(PID_FILE) as f:
            pid = int(f.read().strip())
        os.kill(pid, signal.SIGTERM)
        print("overlay stopped (pid %d)" % pid)
        return 0
    except (OSError, ValueError):
        print("no running overlay", file=sys.stderr)
        return 0


def selftest():
    if not os.environ.get("DISPLAY"):
        # Refuse, don't skip-as-pass: a selftest that could not run must not
        # report success.
        print("selftest refused: no DISPLAY set (X session required)",
              file=sys.stderr)
        return 2
    from Xlib import display, X
    from Xlib.xobject.drawable import Window
    proc = subprocess.Popen(
        [sys.executable, os.path.abspath(__file__), "--start", "460x44+10+10"],
        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    wid = None
    line = proc.stdout.readline()
    if "overlay wid=" in line:
        wid = int(line.split("overlay wid=")[1].strip())
    d = display.Display()
    ok = False
    deadline = time.time() + 5
    evidence = {}
    while time.time() < deadline and not ok:
        if proc.poll() is not None:
            break
        try:
            a = Window(d.display, wid).get_attributes()._data
            evidence = {"map_state": a["map_state"],
                        "override_redirect": a["override_redirect"]}
            ok = a["map_state"] == X.IsViewable \
                 and a["override_redirect"] == 1
        except Exception:
            time.sleep(0.2)
    proc.terminate()
    try:
        proc.wait(timeout=5)
    except subprocess.TimeoutExpired:
        proc.kill()
    d.close()
    if ok:
        print("overlay selftest: PASS %s" % json.dumps(evidence))
        return 0
    print("overlay selftest: FAIL (wid=%r, proc=%s)" % (wid, proc.returncode))
    return 1


def main(argv):
    if argv and argv[0] == "--start" and len(argv) >= 2:
        start(argv[1])
        return 0
    if argv and argv[0] == "--stop":
        return stop()
    if argv and argv[0] == "--selftest":
        return selftest()
    print("usage: agent_overlay.py --start <WxH+X+Y> | --stop | --selftest",
          file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
