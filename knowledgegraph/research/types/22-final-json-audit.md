# Final Type Archaeology JSON Audit

## Final verdict

**PASS.** The latest final corpus passes A-015 metric correctness, A-016 non-circular provenance, and all prior fixed-check regression checks. The final corpus was not modified by this audit.

## Focused verification

| Check | Result | Evidence |
|---|---|---|
| A-015 metric correctness | Pass | `M-COVERAGE-EVIDENCE` 9,672 = 9,672; `M-SEMANTIC-TYPE-ROWS` 1,591 = 1,591; `M-TYPE-PROJECTION-ROWS` 5,376 = 5,376 |
| A-016 provenance | Pass | 23 manifest entries; 22 JSON/Markdown pairs plus one contextual campaign; 45/45 file hashes match; 0 self-referential entries |
| Prior fixed checks | Pass | 0 regressions across A-001–A-014 fixed/justified indicators |
| Final target mutation | Pass | Final target SHA-256 remains `302452c3f4dec236722dd8e43ed4632b43c1faff1e66d3d3cc0b6f5d164f0af4` |

## A-015 — Metric correctness

All 23 metric rows have explicit `count_label` values. The three previously mismatched metrics now match the final array predicates:

- `M-COVERAGE-EVIDENCE`: 9,672 declared and 9,672 final evidence records.
- `M-SEMANTIC-TYPE-ROWS`: 1,591 declared and 1,591 `semantic_entity: true` type rows.
- `M-TYPE-PROJECTION-ROWS`: 5,376 declared and 5,376 `semantic_entity: false` type rows.

## A-016 — Non-circular provenance

The final source manifest contains `AUD-17` through `AUD-21`, the contextual campaign, and workers `WA-00` through `WA-16`. It does not list `22-final-json-audit.json` or `22-final-json-audit.md` as inputs. All 22 JSON/Markdown pairs parse and hash-verify, the campaign hash-verify, and there are zero manifest mismatches.

## Prior fixed-check regression

No regression was detected:

- A-002 slot `identity_status` missing: 0.
- A-004 invalid normalized support: 0.
- A-005 out-of-range confidence scores: 0.
- A-006 unspecified source levels: 0.
- A-007 campaign manifest and hash: pass.
- A-008 null raw claims: 0.
- A-009 unsorted claim arrays: 0.
- A-012 unlabeled metrics: 0.
- A-010 projection status omissions: 0.
- A-011 incomplete-method status omissions: 0.
- A-013 unrouted conflicts: 0.
- A-014 unmarked reused family rows: 0.

## Scope

Read-only inputs included the latest `type-archaeology.json`, the synthesis blueprint, the 22 manifested JSON/Markdown pairs, the Cell-stage campaign, the binary, and the pinned triage/xref snapshots. Only `22-final-json-audit.json` and this Markdown file were written.

## Result

**PASS — no remaining blocker for A-015, A-016, or prior fixed-check regression.**
