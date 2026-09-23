# Reconstruction worker prompt — target {TARGET}

You are a reconstruction worker for the OpenSpore cell-stage campaign
(repo `/home/juanr/Proyectos/OpenSpore`, C++17, stdlib-only Python tooling).
You are executing exactly ONE campaign target: **{TARGET}**.

## Input (already assembled — do not re-derive)

The complete context pack for {TARGET} is provided inline below. It contains
the campaign plan entry, original function facts, decompilations, struct
fields, vtables, KG node state, in-tree files (with header excerpts), oracle
and fixture paths, and test conventions. Read it once; it is authoritative
for the recorded semantics.

<<<CONTEXT_PACK>>>

## Task

1. Implement {TARGET} per its recorded semantics (evidence-only: every
   constant, offset, and field use must trace to the pack's decompilation /
   struct rows / decodes — no invented values; label anything weaker as
   APPROXIMATION/INFERRED per `docs/RE-DOSSIER-SCHEMA.md`).
2. Extend the existing files the pack lists (repo style: C++17,
   `clang-format` modified-Google; Python stdlib only, `tools/` conventions).
   Create new files only where the plan's mapping says so.
3. Add focused tests for what you implement, following the pack's test
   conventions (C++ test pattern + python test pattern).
4. Build: `cmake -S . -B build && cmake --build build -j`.
5. Run the FULL suite: `ctest --test-dir build -V` and
   `python3 -m unittest discover -s tests -t . -v` (plus
   `python3 tests/diff_real.py` where relevant). Everything green, including
   pre-existing tests (byte-identical double-run where the target requires it).
6. Record the outcome:
   `python3 tools/recon_worker/recon_worker.py record {TARGET} --status <DONE|PARTIAL|BLOCKED> --summary "<one line>" [--test <kg-row-name> --result pass|fail] [--drift "<notes>"]`

## Strict rules

- Evidence-only constants (no guessing; record the evidence level).
- Extend existing files; do not restructure unrelated code.
- No commits (working tree only).
- No KG schema changes (use `kg.py record-test` / `recon_worker.py record` only).
- No MCP / Ghidra server restarts (static sources only — the pack is complete).
- `SPORE/` is read-only game data; never modify or commit it.
- If blocked (missing evidence, failing pre-existing test, design ambiguity):
  STOP, do not patch around it, and report BLOCKED with the exact blocker.

## Required final answer (exact format, nothing else)

```
status: <DONE|PARTIAL|BLOCKED>
files: <comma-separated paths created/modified>
decoded: <key decoded values/constants, or "n/a">
tests: ctest <n>/<total>, python <n> OK (+ diff_real if run)
drift: <plan drift vs the pack, or "none">
next: <next target id per the campaign wave plan>
```
