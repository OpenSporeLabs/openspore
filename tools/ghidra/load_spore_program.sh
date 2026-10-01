#!/usr/bin/env bash
# Wait for the headless bridge to answer, then load SporeApp.exe into the project.
# Kept as its own script because the JSON body needs nested quotes, which
# systemd's ExecStartPost= mangles unless triple-escaped.
set -uo pipefail

PORT="${SPORE_GHIDRA_PORT:-8089}"
PROGRAM_PATH="${SPORE_GHIDRA_PROGRAM:-/SporeApp.exe}"
LOG="${SPORE_GHIDRA_LOG:-/tmp/opencode/ghidra/mcp-server.log}"
BASE="http://127.0.0.1:${PORT}"

for i in $(seq 1 120); do
  curl -sf -m 2 "${BASE}/check_connection" >/dev/null 2>&1 && break
  sleep 1
done

if ! curl -sf -m 2 "${BASE}/check_connection" >/dev/null 2>&1; then
  echo "WARN: bridge never became ready on ${BASE}" >&2
  exit 0
fi

if curl -sf -m 300 -X POST -H 'Content-Type: application/json' \
     -d "{\"path\":\"${PROGRAM_PATH}\"}" "${BASE}/load_program_from_project" >/dev/null; then
  echo "loaded ${PROGRAM_PATH}" >&2
else
  echo "WARN: ${PROGRAM_PATH} failed to load; see ${LOG}" >&2
fi
exit 0
