# Semantic Spot-check

## Scope

This is a read-only post-remediation comparison of `knowledgegraph/research/type-archaeology.json` against worker artifacts `01` through `16` and audits `19` and `21`. It covers `SporeApp.exe` 3.1.0.22, `x86:LE:32`, image base `0x00400000`, SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.

The recheck covers the original 10 types, 10 fields, 8 vtables/families, 8 lifecycle chains, 8 methods, 8 reconstruction assessments, and 7 conflict records. No worker, target, source, `SPORE/`, Ghidra, database, or history file was modified.

## Post-remediation verdict

**Verified with residual high/medium findings.**

The remediated target substantially improves semantic retention:

- all ten sampled field groups retain source offsets, source claims, and layout-owner links;
- `VT:01485550` and `VT:01490be8` link to their preserved conflict records;
- lifecycle records now expose structured `operation_phases` and `source_phase_claims` while retaining `runtime_observed=false`;
- method records retain source-native kind claims and improved normalized kinds;
- all eight sampled WA-15 records retain exact `source_classification` and `source_domain` values, including explicit null domains;
- canonical `cCellGame` field linkage is now traversable.

The remaining gaps are in type-kind coverage, complete type-layout projection, manager field linkage, lifecycle subphase mapping, and normalized method-kind coverage.

## Sample summary

| Area | Result | Main observation |
|---|---|---|
| Types | Partial | Seven sampled type kinds are normalized; `cEditor`, `cObjectPool<cCellObjectData>`, and `cEmpire` remain `unknown_candidate`. `cCellGame` kind is fixed but `layout_claims` remains empty. |
| Fields | Pass | All ten sampled groups retain exact source offsets, access/role/source claims, and `layout_owner_type_ids`. |
| Vtables | Pass | Slot counts and candidate identities survive; both disputed vtables now link to their conflict records. |
| Lifecycle | Partial | Structured phase maps exist for all eight samples; `allocate`, `create_effect`, `create_rollover`, and `reuse` still normalize to `unknown` in sampled records. |
| Methods | Partial | Source kinds and several normalized categories survive; two initializer records remain broad `method`, and one source record has no explicit kind. |
| Reconstruction | Pass | Exact source classification/domain values are preserved; normalized `classification` remains broader in several records. |
| Conflicts | Pass | All seven categories preserve alternatives, merge decisions, and resolution status; vtable linkage is now present. |

## Findings

### SPOT-001 — Type kind normalization: partially resolved

The original five examples are fixed: `cCellGame` is `global_state`, `cCellObjectData` is `record`, `cGameInputManager` and `cCellModeStrategy` are `class`, and `ResourceKey` is `value_type`.

`Editors::cEditor`, `cObjectPool<cCellObjectData>`, and `cEmpire` still have `kind: "unknown_candidate"` even though their source-native roles remain available. The original REM-001 scope is fixed, but the sampled type-kind finding is not fully closed.

### SPOT-002 — Field claim retention: resolved for the sample

All ten sampled WA-02 groups now retain every source offset in `offset_claims`, along with source access, role, source type ID, grouped source claims, and explicit layout-owner type IDs. The prior empty-offset loss is not observed.

### SPOT-003 — Vtable conflict linkage: resolved

`VT:01485550` now links to `CONFLICT:2bdc94b5e38ac8da1c90487e`, and `VT:01490be8` now links to `CONFLICT:72bb6c455c2d655bfed033f8`. Both conflicts retain their alternative owner claims and unresolved status.

### SPOT-004 — Lifecycle structure: partially resolved

All eight sampled lifecycle records now have structured operation phase maps and preserve source phase values, operation text, ownership qualifications, and `runtime_observed=false`.

The remaining issue is incomplete phase normalization: sampled `allocate`, `create_effect`, `create_rollover`, and `reuse` operations still appear as `unknown`.

### SPOT-005 — Method normalization: partially resolved

The target now retains source-native method kinds and has distinct normalized `accessor`, `factory`, `dispatch`, and `serialization` claims.

`METHOD:00e5dba0` and `METHOD:00e80ba0` retain initialization semantics in `source_native_kind` but remain broad `kind: "method"`. `METHOD:00b3d360` remains `unknown`, which is bounded because its source accessor record has no explicit method-kind claim.

### SPOT-006 — Reconstruction classification: resolved for source projection

All eight sampled WA-15 records retain the exact source classification in `source_classification`:

- `reproduce-layout`
- `semantic-interface-only`
- `replaceable-infrastructure` where present in the source vocabulary

Source domains are also retained. The normalized `classification` remains broader or `unknown` in several records, but the exact worker value is no longer lost.

### SPOT-007 — Type/field linkage: resolved for cCellGame

`cCellGame` now has eight canonical `field_ids`, and the sampled shared-layout fields have `layout_owner_type_ids` pointing to `cCellGame` or `cCellObjectData`.

The `cGameInputManager` type still has an empty `field_ids` list despite retaining source field-map provenance and the exact accessor. This is a residual manager-linkage gap.

### SPOT-008 — Runtime/RTTI overclaim: no action required

Sampled methods retain `runtime_observed=false`; unresolved vtable owners remain candidates; structural relations remain non-RTTI-backed; conflict alternatives remain preserved. No original-runtime or MSVC RTTI promotion was observed.

## Remaining high/medium issues

| ID | Severity | Issue |
|---|---|---|
| `POST-001` | High | `cEditor`, `cObjectPool<cCellObjectData>`, and `cEmpire` retain source-native roles but remain `unknown_candidate`. |
| `POST-002` | Medium | `cCellGame` has normalized kind and field links, but its `layout_claims` array remains empty. |
| `POST-003` | Medium | `cGameInputManager` retains source field-map provenance but has `field_ids: []`. |
| `POST-004` | Medium | Several lifecycle source subphases still normalize to `unknown`. |
| `POST-005` | Medium | Some method records retain source kinds but remain broad or `unknown` in the normalized dimension. |

## Remediation status

- `REM-001`: partially resolved; extend normalized kind mapping to the three remaining sampled types.
- `REM-002`: resolved for all ten sampled field groups.
- `REM-003`: resolved; both disputed vtables link to their conflicts.
- `REM-004`: partially resolved; complete the remaining lifecycle subphase mappings.
- `REM-005`: partially resolved; retain source kinds and map initializer categories more precisely.
- `REM-006`: resolved for source projection; exact classifications and domains are retained.
- `REM-007`: resolved for the sampled `cCellGame` linkage.

## Integrity

The report is deterministic, timestamp-free, and limited to:

- `knowledgegraph/research/types/23-semantic-spotcheck.json`
- `knowledgegraph/research/types/23-semantic-spotcheck.md`
