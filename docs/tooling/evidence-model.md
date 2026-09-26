# Evidence model

An evidence pack has schema `openspore-evidence-pack-1` and a target VA. Categories are independently available, conflicted, or unavailable. Every category carries:

```json
{
  "availability": "available|unavailable",
  "evidence_state": "LIVE|PERSISTED|DERIVED|INFERRED|MISSING",
  "evidence_level": "UNKNOWN|INFERRED|SUPPORTED|OBSERVED|CONFIRMED|VERIFIED",
  "provenance": ["repository-relative/path#locator"],
  "value": "bounded evidence or null",
  "reason": "why missing, or null"
}
```

## Sources

- Generated index: derived joins over manifest, triage, metadata, handoffs, xrefs, and semantic research.
- Committed Ghidra snapshots: persisted function observations.
- Live Ghidra: explicit function, decompilation, and optional disassembly queries.
- SQLite: only coordination/cross-tool data, never fabricated decompilation.
- Runtime: always `MISSING` unless an exact trace is supplied; `runtime_metadata` may preserve gates and status separately.

The pack-level `provenance` array uses objects with `ref`, lowercase `mode` (`live`, `persisted`, `derived`, or `snapshot`), and `source_class`. Category-level provenance is a list of source references.

`--live` first attempts live Ghidra. A failed live attempt is recorded with `mode: LIVE` and a failure code. A committed snapshot may then fill a category as `PERSISTED`; it is never relabelled live. Default mode does not contact Ghidra.

## Determinism

JSON is UTF-8, sorted, indented, and newline-terminated. Set-like lists are sorted. Instruction/decompilation order is preserved. Wall-clock timestamps, random IDs, and cache-hit counters are excluded from the pack digest. `content_sha256` is computed over the document before that field is populated; oversized values include a byte-bounded preview and source hash.

## Conflicts

Conflicting values are retained as `conflicts`; the collector does not choose a winner by count or confidence. Existing reconstruction contradictions and live-versus-persisted signature differences are exposed to context and validation.
