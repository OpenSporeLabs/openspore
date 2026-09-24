# Focused Research — Audio and original input marshalling

Package: `PKG-19-AUDIO-INPUT`  
Readiness: `BLOCKED_BY_RE`  
Research class: `BLOCKED_BY_RE`

## Exact question

What original input and audio functions feed mode-owned gameplay state?

## Competing hypotheses

- original input marshaller
- host-only input adapter
- audio backend boundary
- no-audio fallback

## Evidence currently available

- Audio boundary or explicit no-audio/stub contract.
- Identity of the 11-function audio/input cluster.
- Input marshalling into cGameInputManager.

## Smallest useful investigation

Inspect the 11-function cluster, cGameInputManager xrefs, and input callbacks; separate original families from SDL/host assumptions.

Inspect exactly: GameInput functions, Audio functions, cell_movement input probes, cGameInputManager xrefs.

## Expected observations

- Pinned bytes/decompilation/xrefs or raw runtime events with explicit environment and outcome.

## Decision criterion

Original input/audio separated from CellInput, SDL, and host timing.

## Safety boundary

Missing reachability remains NOT_YET_TESTABLE.
## Source records

- knowledgegraph/research/architecture-resolution.json
- docs/analysis/architecture-resolution.md
- docs/analysis/reconstruction-research-queue.md
- knowledgegraph/research/track-m-oracle-plan.json
- knowledgegraph/research/track-n-testability.json

