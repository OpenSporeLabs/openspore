#!/bin/sh
# machine_lock.sh — human-command wrapper for the shared machine lock
# (flock on /tmp/openspore-machine.lock; body {pid,label,ts,task_id};
# fail-closed: exit 5 machine_locked; kernel-released on death).
# Usage: machine_lock.sh <command> [args...]
set -eu

HERE=$(cd "$(dirname "$0")" && pwd)

if [ $# -lt 1 ]; then
  echo "usage: machine_lock.sh <command> [args...]" >&2
  exit 2
fi

exec python3 "$HERE/lock.py" acquire human-machine-lock -- "$@"
