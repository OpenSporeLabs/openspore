#!/usr/bin/env bash
# Launch the headless GhidraMCP bridge for the Spore project and load SporeApp.exe.
# Safe to run repeatedly: stale project locks are cleared first, and the load is
# idempotent. Intended to be run from the ghidra-mcp.service systemd user unit.
set -euo pipefail

PROJECT_DIR="${SPORE_GHIDRA_PROJECT:-/home/juanr/ghidra-spore-project}"
PROJECT_NAME="${SPORE_GHIDRA_PROJECT_NAME:-SporeProject}"
PROGRAM_PATH="${SPORE_GHIDRA_PROGRAM:-/SporeApp.exe}"
PORT="${SPORE_GHIDRA_PORT:-8089}"
BIND="${SPORE_GHIDRA_BIND:-127.0.0.1}"
GHIDRA_HOME="${SPORE_GHIDRA_HOME:-/opt/ghidra}"
EXT_JAR="${SPORE_GHIDRA_EXT_JAR:-/home/juanr/.config/ghidra/ghidra_12.1.2_DEV/Extensions/GhidraMCP/lib/GhidraMCP-7.0.0.jar}"
LOG="${SPORE_GHIDRA_LOG:-/tmp/opencode/ghidra/mcp-server.log}"

# A previous unclean shutdown leaves SporeProject.lock behind and the project
# then refuses to open. No other java process can hold it once we are down.
if pgrep -f GhidraMCPHeadlessServer >/dev/null 2>&1; then
  echo "ghidra bridge already running; not starting a second instance" >&2
  exit 0
fi
rm -f "${PROJECT_DIR}/${PROJECT_NAME}.lock" "${PROJECT_DIR}/${PROJECT_NAME}.lock~"

mkdir -p "$(dirname "$LOG")"

CLASSPATH="${EXT_JAR}:$(find "${GHIDRA_HOME}/Ghidra" -name '*.jar' | tr '\n' ':')"

export GHIDRA_MCP_ALLOW_SCRIPTS=1

echo "starting ghidra bridge on ${BIND}:${PORT} (project=${PROJECT_NAME})" >&2
exec java -Xmx8g -Dghidra.home="${GHIDRA_HOME}" \
  -classpath "${CLASSPATH}" \
  com.xebyte.headless.GhidraMCPHeadlessServer \
  --port "${PORT}" --bind "${BIND}" --project "${PROJECT_DIR}" \
  >>"${LOG}" 2>&1
