#!/usr/bin/env python3
"""lock.py — shared machine lock (flock on /tmp/openspore-machine.lock).

Single source of truth for the machine-lock contract also used by
tools/mcp/runtime_tools.py, tools/observatory/observe.py,
tools/observatory/menu_walk.sh and tools/observatory/machine_lock.sh.

Usage:
    lock.py probe
    lock.py acquire <label> [--task-id ID] [--timeout SEC] [-- <cmd> [args...]]

Semantics (fail-closed):
  * flock(2) LOCK_EX|LOCK_NB on the lock file: the kernel releases the
    lock on process death, so a stale lock is impossible.
  * On acquire, the body {pid,label,ts,task_id} is written into the lock
    file for diagnostics.
  * Contention: MachineLocked / CLI exit 5 with a machine_locked JSON line.
  * `acquire ... -- <cmd>` execs the command while holding the lock. The
    lock fd is opened CLOEXEC-free (CPython 3.4+ sets O_CLOEXEC by
    default), so the exec'd child inherits it and the kernel keeps the
    flock held until the child exits. The body's `pid` is this process's
    pid — the same pid that becomes the command after exec — i.e. the
    holder's (child's) pid.
  * `acquire` without a command holds until SIGTERM/SIGINT.

Lock path: $OPENSPORE_MCP_LOCK (absolute as-is; relative resolved against
the repo root), else /tmp/openspore-machine.lock — same prefix as the MCP.

Exit codes: 0 ok, 2 usage, 5 machine_locked.
"""
import fcntl
import json
import os
import shutil
import signal
import sys
import time

_DEFAULT_LOCK = "/tmp/openspore-machine.lock"
_REPO_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))


class MachineLocked(Exception):
    """Raised when the machine lock is held by another process."""

    def __init__(self, path):
        super().__init__(path)
        self.path = path


def lock_path():
    env = os.environ.get("OPENSPORE_MCP_LOCK")
    if env:
        if os.path.isabs(env):
            return os.path.normpath(env)
        return os.path.normpath(os.path.join(_REPO_ROOT, env))
    return _DEFAULT_LOCK


def lock_held(path=None):
    """True when the lock is held (non-blocking probe; never raises)."""
    path = path or lock_path()
    try:
        fh = open(path, "a+")
    except OSError:
        return False
    try:
        try:
            fcntl.flock(fh.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError:
            return True
        fcntl.flock(fh.fileno(), fcntl.LOCK_UN)
        return False
    finally:
        fh.close()


def acquire(label, task_id=None, timeout=0.0, path=None):
    """Acquire the lock; returns the open fd (hold it; release on exit).

    Raises MachineLocked when held (after `timeout` seconds of polling).
    """
    path = path or lock_path()
    os.makedirs(os.path.dirname(path) or ".", exist_ok=True)
    deadline = time.time() + max(0.0, float(timeout))
    fh = open(path, "a+")
    while True:
        try:
            fcntl.flock(fh.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
            break
        except OSError:
            if time.time() >= deadline:
                fh.close()
                raise MachineLocked(path)
            time.sleep(0.5)
    try:
        fh.seek(0)
        fh.truncate(0)
        fh.write(json.dumps({
            "pid": os.getpid(),
            "label": label,
            "ts": time.time(),
            "task_id": task_id,
        }))
        fh.flush()
    except OSError:
        pass
    return fh


def release(fh):
    """Unlock and close. Idempotent; the kernel also releases on death."""
    if fh is None:
        return
    try:
        fcntl.flock(fh.fileno(), fcntl.LOCK_UN)
    except OSError:
        pass
    try:
        fh.close()
    except OSError:
        pass


def _main(argv):
    if not argv:
        print("usage: lock.py probe | acquire <label> [--task-id ID] "
              "[--timeout SEC] [-- <cmd> [args...]]", file=sys.stderr)
        return 2
    if argv[0] == "probe":
        if lock_held():
            print(json.dumps({"status": "error", "code": "machine_locked",
                              "lock": lock_path()}))
            return 5
        print(json.dumps({"status": "ok", "machine_locked": False,
                          "lock": lock_path()}))
        return 0
    if argv[0] == "acquire":
        label = argv[1] if len(argv) > 1 else ""
        task_id = None
        timeout = 0.0
        cmd = []
        i = 2
        while i < len(argv):
            a = argv[i]
            if a == "--task-id" and i + 1 < len(argv):
                task_id = argv[i + 1]
                i += 2
            elif a == "--timeout" and i + 1 < len(argv):
                timeout = float(argv[i + 1])
                i += 2
            elif a == "--":
                cmd = argv[i + 1:]
                i = len(argv)
            else:
                print("usage: lock.py acquire <label> [--task-id ID] "
                      "[--timeout SEC] [-- <cmd> ...]", file=sys.stderr)
                return 2
        if not label:
            print("error: acquire needs a label", file=sys.stderr)
            return 2
        try:
            fh = acquire(label, task_id=task_id, timeout=timeout)
        except MachineLocked as exc:
            print(json.dumps({"status": "error", "code": "machine_locked",
                              "message": "shared display/GPU busy (lock %s "
                                         "held); park, no attempt burn"
                                         % exc.path,
                              "lock": lock_path()}))
            return 5
        try:
            if cmd:
                # CPython 3.4+ opens with O_CLOEXEC by default; clear it so
                # the exec'd child inherits the flock'd fd and the kernel
                # keeps the lock held for the whole command (else the lock
                # is released at exec time and nothing serializes).
                fcntl.fcntl(fh.fileno(), fcntl.F_SETFD, 0)
                print(json.dumps({"status": "ok", "acquired": True,
                                  "label": label, "task_id": task_id}),
                      file=sys.stderr)
                cmd0 = cmd[0]
                if os.path.sep in cmd0:
                    full = cmd0
                elif os.path.exists(cmd0):  # CWD-relative (CTest binaries)
                    full = os.path.abspath(cmd0)
                else:
                    full = shutil.which(cmd0)
                if not full:
                    print(json.dumps({"status": "error",
                                      "code": "exec_failed",
                                      "message": "cannot resolve %r" % cmd0}),
                          file=sys.stderr)
                    return 127
                os.execvpe(full, [full] + cmd[1:], os.environ)
            print(json.dumps({"status": "ok", "acquired": True,
                              "label": label, "task_id": task_id}))

            def _stop(signum, frame):
                sys.exit(0)

            signal.signal(signal.SIGTERM, _stop)
            signal.signal(signal.SIGINT, _stop)
            while True:
                time.sleep(0.5)
        finally:
            release(fh)
        return 0
    print("unknown command %r" % argv[0], file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(_main(sys.argv[1:]))
