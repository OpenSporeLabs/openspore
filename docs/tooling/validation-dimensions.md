# Validation dimensions

`openspore validate` answers one question — does this reconstruction agree with the machine binary — and, separately, a question it cannot answer: was the original process ever observed. This file is the explicit, auditable specification of both: what every status token means, what evidence a positive verdict requires, and why a positive verdict cannot be manufactured out of a missing value.

It exists because the alternative is inferring the rules from a JSON report. `report["static"]["checks"]["CALLS"]["status"] == "PASS"` says nothing on its own about what was compared, against what, or with what completeness. The rules are here so a reader can check a verdict instead of trusting it, and so a change to a check that would alter the meaning of a verdict has to argue with a written rule rather than slip through.

The implementation is `tools/reconstruction_tooling/validate.py`. Symbols are cited by name because that file changes; line numbers are not stable enough to be a citation. The worker-side halves of the same vocabulary are in `worker_contract.py`, the queue half in `tools/mcp/kg_tools.py`, and the one place a runtime artifact can promote a status is `tools/mcp/runtime_tools.py`.

## The two axes

| Axis | Field | Question | Alphabet |
|---|---|---|---|
| static | `report["static"]["status"]`, aliased as `report["status"]` | does the reconstruction agree with the binary? | `PASS` / `WARN` / `FAIL` / `UNKNOWN` / `NOT_AVAILABLE` |
| runtime | `report["runtime"]["status"]` | was the original process observed? | `GATED` / `PASS` |

`report["status"]` is a back-compat alias of the static verdict and nothing else. Every existing consumer of that key keeps its current meaning; the runtime verdict is only ever read from `report["runtime"]`.

Four properties hold at once, and each of them has been got wrong somewhere in this repository's history:

- **A static `PASS` is not a runtime claim, and never implies one.** The static axis is adjudicated against a machine binary. It says what the reconstruction agrees with, not what the game does. The two axes are reported side by side in `validate.render_markdown` precisely so a reader of the human output cannot collapse them.
- **`runtime == "GATED"` is not a runtime failure.** It is an open capability gate: nothing was attempted, and nothing failed. A runtime `FAIL` is not representable, because no experiment exists in this repository that could fail. `GATED` is also the reason the runtime axis is not spelled `NOT_AVAILABLE` — see §8.
- **The runtime axis is excluded from the static coverage denominator, never appears as a member of `checks`, and is never consulted by the static aggregate ladder.** The reserved `runtime` evidence category is a permanent capability gap on the original process; counting it in the static denominator let a gap on one axis veto a verdict on the other. `validate.validate` filters it out by name (`RUNTIME_CATEGORY`) before counting, and the ladder reads only the structural checks plus the coverage floor.
- **`STATIC_VALIDATED` is a reading of one report, not a state.** It means `report["static"]["status"] == "PASS"` together with `report["runtime"]["status"] == "GATED"`. No new state machine, no new field, and no new status token were introduced for it: the string `STATIC_VALIDATED` appears nowhere in the code, and the two fields it names already carry the whole claim. §7 says what it does and does not license.

## Vocabulary

Every token in this section is a string in a report, a worker result, an evidence pack, or a queue row. None of them is a display label; all of them are compared by code.

### Check status (the static alphabet)

| Token | Meaning | Defined in |
|---|---|---|
| `PASS` | the oracle for this dimension is complete and bounded — a machine listing, a machine-derived record, or a bounded projection of one — and the reconstruction either makes no claim in it or every claim agrees with that oracle | `validate._check`, one `PASS` arm per check in `validate.validate` |
| `WARN` | the dimension was adjudicated and something in it needs a human: evidence that is present but partial, two machine sources that disagree, or a claim the oracle cannot ground | as above |
| `FAIL` | the reconstruction contradicts the machine evidence | as above |
| `UNKNOWN` | a claim was made that nothing available can confirm or contradict | as above |
| `NOT_AVAILABLE` | there is no evidence to run this check against | as above |

`UNKNOWN` is emitted from exactly one place in the whole validator: the `VIRTUAL DISPATCH` arm where the source span declares an opaque slot boundary and no machine listing exists. It is not a general "I could not tell" — it names a specific combination (a claim, and no oracle) and exists so that combination is visible instead of being rounded to `NOT_AVAILABLE` or `WARN`.

`NOT_AVAILABLE` is an absence of evidence and is never evidence of failure. It is also, as of the current ladder, not neutral — see §4.

### Per-check coverage

`_check(status, detail, coverage, evidence)` returns `{"status", "detail", "coverage", "evidence"}`. `coverage` is one of:

| Token | Meaning |
|---|---|
| `none` | nothing was evaluated; the check had no evidence and the reconstruction was not read for this dimension |
| `partial` | something was evaluated and something bounds it — a truncated oracle, a weaker of two oracles, an unproven confidence |
| `complete` | the oracle for this dimension was whole and bounded, and the comparison covered all of it |

`coverage` is descriptive. It is not an input to the aggregate and must not be read as one: a check can be `PASS` with `coverage: partial` (a convention token present in both the span and the metadata is a complete agreement about a narrow fact), and `coverage: complete` is not by itself a clearance.

### Runtime status

| Token | Meaning |
|---|---|
| `GATED` | the capability gate on the original process is open. Nothing was attempted; nothing failed |
| `PASS` | `record["runtime"]["validated"]` is a positive integer: the canonical record reports original-process observations |

`NOT_AVAILABLE` is deliberately **not** a runtime state. `validate._runtime_dimension` spells out why: `NOT_AVAILABLE` means "a verdict could not be reached" and is indistinguishable from a category that was searched and came up empty, which would report a permanent capability gap as a per-target finding. The gate is open, which is a different fact with its own name.

### Worker outcomes

From `worker_contract.py`:

| Symbol | Members | Meaning |
|---|---|---|
| `OUTCOMES` | `IMPLEMENTED`, `PARTIAL`, `STRUCTURAL_ONLY`, `STILL_UNKNOWN`, `BLOCKED`, `FAILED_VALIDATION` | what a worker reports about its own work |
| `TERMINAL_OUTCOMES` | `IMPLEMENTED`, `PARTIAL`, `STRUCTURAL_ONLY` | outcomes that produced a reviewable candidate |
| `UNSATISFIED_OUTCOMES` | `STILL_UNKNOWN`, `BLOCKED`, `FAILED_VALIDATION` | outcomes that produced none; none of them closes a row, all of them cost an attempt |
| `VALIDATION_VERDICTS` | `PASS`, `WARN`, `FAIL`, `UNKNOWN`, `NOT_AVAILABLE` | the alphabet a worker may self-report in `result.validation` |

An outcome is not a verdict. A worker may report a self-verdict, and the parser (`worker_contract.parse_result`) only checks that it is a member of `VALIDATION_VERDICTS`; the orchestrator never takes it as the verdict. The verdict is whatever `openspore validate` says about the candidate on disk.

### Evidence pack and category fields

Per `docs/tooling/evidence-model.md`, and as produced by `evidence._category`:

| Field | Values |
|---|---|
| `availability` | `available`, `unavailable` |
| `evidence_state` | `LIVE`, `PERSISTED`, `DERIVED`, `INFERRED`, `MISSING` |
| `evidence_level` | `UNKNOWN`, `APPROXIMATION`, `INFERRED`, `SUPPORTED`, `OBSERVED`, `CONFIRMED`, `VERIFIED` (the canonical scale; `evidence._category` only ever emits `OBSERVED`, `INFERRED`, `SUPPORTED` and `UNKNOWN`) |
| `provenance` | repository-relative `path#locator` strings |
| `value`, `reason` | the bounded evidence, and why it is missing when it is |

A category with `availability: "available"` and `value: {"truncated": true, "preview": ...}` is **not** a listing. See §5.

### Queue status

`kg_tools._INVESTIGATION_STATUSES` is `("queued", "active", "blocked", "done", "dropped")`, with `kg_tools._TERMINAL_STATUSES` being `done` and `dropped`. This is a **separate axis** from validation status and the two must never be mapped onto each other:

- a `queued` row can hold a target whose static verdict is `PASS` (the worker produced a candidate, the verdict has not been run yet);
- a `done` row was closed on a static `PASS` (see `orchestrate.reconcile`), which says nothing about the runtime axis, and the closed row still carries `runtime: {status, gated, gates}`;
- `blocked` with `reason: validation_warn` is not the same fact as `blocked` with `reason: dependency_blocked`, and neither is a runtime failure.

The prefixes the orchestrator routes on are listed in `orchestration.md` § `block_reason` prefixes. `validation_not_available` there records the verdict, not the cause: the cause is in the checkpoint and in the briefing's `missing_sections`.

## The nine checks

`validate.STATIC_CHECKS` is the tuple of the eight structural checks, in report order:

```text
ABI, CALLS, GLOBALS, FIELDS/OFFSETS, CONSTANTS, CONTROL FLOW, VIRTUAL DISPATCH, RETURN SEMANTICS
```

`validate.COVERAGE_CHECK` is `"EVIDENCE COVERAGE"`, and it is a **measurement, not a per-target verdict on the reconstruction**:

- it is excluded from `report["static"]["checks"]` (the structural dict) and appears at `report["static"]["evidence_coverage"]`, and in the legacy `report["checks"]` map alongside the eight;
- `validate.render_markdown` prints it *outside* the check table for the same reason, with the sentence "Evidence coverage is a measurement, not a verdict";
- its only power over the aggregate is its floor (§4).

The worker briefing advertises all nine as `validation_requirements.required_categories` (the list is written in `context.py`, section `15_validation_and_provenance`). That list is the worker's checklist; the ladder consumes the eight. A worker reading nine required categories is not being asked for a ninth verdict.

## The aggregate ladder

`report["static"]["status"]` is computed in `validate.validate` over the eight structural checks plus the coverage floor, in this order:

| Order | Condition | Aggregate |
|---|---|---|
| 1 | any structural check is `NOT_AVAILABLE` | `NOT_AVAILABLE` |
| 2 | the coverage check is `NOT_AVAILABLE` (no static evidence category available at all) | `NOT_AVAILABLE` |
| 3 | any structural check is `FAIL` | `FAIL` |
| 4 | any structural check is `UNKNOWN` | `UNKNOWN` |
| 5 | any structural check is `WARN` | `WARN` |
| 6 | otherwise | `PASS` |

Rule 1 is the strengthened one, and it is the rule most worth arguing for. **`NOT_AVAILABLE` used to be neutral**: it was skipped, like a dimension nobody asked about, so a `PASS` could rest on a single evaluated check while seven went unjudged, and nothing in the verdict said so. That is a false-`PASS` vector — an absence of evidence being averaged in as if it were agreement. `NOT_AVAILABLE` now names the aggregate instead of being absorbed by it, which also subsumes the older "nothing was attempted" case (all eight `NOT_AVAILABLE` is one `NOT_AVAILABLE`).

The consequence is worth stating plainly: **no target in this repository reaches a static `PASS` today** (verified over all 200 pack-backed targets and a 40-record sample of the rest), and the honest reason is coverage, not disagreement. `report["static"]["evidence_basis"]` is reported on every report for the same reason — a thin pass must be legible as thin:

```json
{
  "static_checks_total": 8,
  "static_checks_evaluated": 7,
  "static_checks_passed": 5,
  "static_checks_not_available": 1,
  "static_evidence_categories_available": 10,
  "static_evidence_categories_total": 16
}
```

`static_evidence_categories_total` is 16 rather than 17 because the reserved `runtime` category is excluded from the denominator; see the second bullet under "The two axes".

## The truth table

The `PASS` column of all six evidence dimensions records one uniform rule. A check reaches `PASS` only when both hold:

1. **the machine evidence for that dimension is complete and bounded** — it exists, it covers the whole body, and it is not a preview, a lower bound, or a truncated slice; and
2. **agreement or evidenced absence** — the reconstruction either makes no claim in that dimension, or every claim it makes is grounded in that machine evidence.

Clause 2 has a name worth keeping: *evidenced absence*. "The source claims nothing here" is a pass only when the machine oracle is present, complete, and was actually searched — see §6.

| check | `PASS` means | evidence a `PASS` requires | `WARN` means | `FAIL` means | `NOT_AVAILABLE` means | required for `STATIC_VALIDATED` |
|---|---|---|---|---|---|---|
| `ABI` | the calling convention the reconstruction declares is the one the machine record states, and no ABI-bearing conflict is unresolved | `record["abi"]` / `categories.abi` convention claim, plus a resolvable target span; no unresolved `live_vs_persisted` or ABI-field conflict | the derived ABI record abstained (`ABI_UNKNOWN`), or its confidence is `unknown`/`approximation`, or the convention is not extractable | the span declares a convention that contradicts the persisted or derived record, or an ABI-bearing conflict is unresolved | no resolvable source span | yes |
| `CALLS` | the callee set is adjudicated: the xref export and the listing agree (or the export bounds the source), and the source names no callee the export does not record | the **complete** xref export for this VA (`knowledgegraph/triage/xrefs-2540f2ca.tsv`, read whole by `evidence_xrefs.authoritative_callees`) when it is available, else the `dependencies.edges` projection; **and** `categories.disassembly.value.instructions`; plus the `symbol_<va>` callee convention in the span | with no complete export, a projection truncated at export time; or a span that names no address-suffixed callee, so the machine set cannot bound the source | a callee the source names has no call edge in the export, or two bounded machine sources disagree with each other | no call oracle at all: neither the export nor a listing | yes |
| `GLOBALS` | the complete listing names **no** data-segment address and the span names none — positive machine evidence that the body touches no global | `categories.disassembly.value.instructions`, complete and untruncated; the absence of a data-segment address in it | the listing names data addresses, or the span names addresses the listing does not corroborate, and read/write mode needs per-access evidence | not reachable: there is no independent global oracle to contradict | no complete listing to search, and `record["globals"]` alone is not evidence | yes |
| `FIELDS/OFFSETS` | every offset the span declares is witnessed by the **complete, fully-parsed listing** read alias-aware over the receiver register, or by the machine-derived receiver record — and, when the span declares none, a complete listing that reaches no receiver field is itself the evidence | `categories.disassembly.value.instructions`, complete and consumed in full by `categories.abi.value.parse` (`declared_count == len(instructions)`, `degraded == false`, `unparsed == 0`), read through an alias-aware scan that follows copies, `XCHG`, address chains and push/pop pairs; **or**, with no receiver register, a complete fully-parsed listing naming no memory operand at all; `categories.abi.value.receiver` supplies a second witness and `bounds_only` widens it | an offset no witness shows; a `may`-only witness (an alias assigned on one arm of a branch), which grounds nothing; a `bounds_only` record that does not enumerate a declared offset, which is silence and not a refutation; a declared offset shown only under a **non-receiver** base, which is unattributed and neither a contradiction nor a clearance; a span that names a field, which no machine record can corroborate by identity | a declared offset that an **enumerating** record (`bounds_only` is not `true`) excludes *and* the complete listing does not show either | no complete listing, or a receiver record with no register and a listing whose memory operands cannot be read as an absence | yes |
| `CONSTANTS` | every hexadecimal literal the span states appears in a listing that is **shown to be whole** | `categories.disassembly.value.instructions` plus `categories.abi.value.parse`: `declared_count == len(instructions)`, `degraded == false`, `unparsed == 0` | the listing exists but is not fully parsed (`degraded` true, or `unparsed > 0`), so a match may be a coincidence of a partial read | a stated literal is absent from the listing, or the machine parse and the listing disagree about the body length | the span states no constant to compare, or the listing carries no parse record so it cannot be shown whole | yes |
| `CONTROL FLOW` | the branch graph is **closed inside the recovered body span**: either the complete listing contains no conditional branch at all, or every conditional branch target lies within the listing's own `[lo, hi]` address span | `categories.disassembly.value.instructions`, complete, with instruction addresses that parse; branch targets read from the instruction text | some branch has no absolute target the body can be bounded against, or a target falls outside the span, so the listing is a slice | not reachable: the machine side is a bound, not a claim to contradict | no listing. `ghidra_function.dispatch` is `null` in every committed pack, so it is never an oracle | yes |
| `VIRTUAL DISPATCH` | either side is clean: the complete listing names no indirect transfer **and** `categories.abi.value.dispatch.indirect_calls` is `0` — **or** every site is a positively corroborated vtable slot: a `MOV R2,[R1+d]` whose base `R1` is itself loaded from memory, read over a complete fully-parsed listing whose site count agrees with the dispatch record | `categories.disassembly.value.instructions` (register transfers and `[size ptr [...]]` memory operands both count) **and** `categories.abi.value.dispatch.indirect_calls`, **and**, for the positive arm, `categories.abi.value.parse` showing the listing was consumed in full | the listing names indirect sites, the listing is clean but no dispatch record was collected, the two machine sources disagree on the site count, or a site's shape is not a vtable slot — `FUNCTION_POINTER` (a target read straight from a global or a frame slot), `INDIRECT_NON_VTABLE` (a jump table such as `[EAX*0x4+0x…]`, or `CALL dword ptr [ESP+0x…]`), or `UNRESOLVED` (the target register's value cannot be traced) | the span declares a virtual-slot boundary and the complete listing contains no indirect transfer | no listing and no dispatch record; a span that declares a slot boundary here is `UNKNOWN` instead | yes |
| `RETURN SEMANTICS` | the span's return type is the one the bounded ABI record states — **or**, where no layer records a `return_type`, the return is adjudicated from the ABI envelope's return sub-record together with the complete fully-parsed listing, in an explicit state: `VOID_PROVEN` (no return register, or one the listing never writes on any path to a `RET`), `WIDTH_<n>_IN_<REG>` (a must-analysis shows every path to every reachable return wrote that register at that width), `SRET_PROVEN`, or `UNCLASSIFIED` | the `return_type` in `record["abi"]` / `categories.abi` and a resolvable span; for the second route, `categories.abi.value.parse` (`declared_count == len(instructions)`, `degraded == false`, `unparsed == 0`) over the complete listing, plus `categories.abi.value.return_register` / `return_semantics` / `sret` | the return type differs or is semantically renamed; a machine width that contradicts the span's type width; a suspected-but-unproven hidden-pointer return | a span declaring a non-void return where the machine returns nothing, or vice versa | `UNCLASSIFIED` (the last value-producing op is a `CALL`, or the paths disagree), or no complete listing, no fully-consumed parse, or no return field in any ABI layer. **A missing record is never a record of void** | yes |
| `EVIDENCE COVERAGE` | not a per-target verdict; `PASS` here means every static category is available | the pack's per-category `availability` | some static categories are unavailable | n/a | no static category available — this is the one floor the metric has over the aggregate | no: floor only |

### Which artifact is the oracle, per check

The table above says what a `PASS` requires. This is the concrete provenance behind each row, measured against the committed corpus (see §10).

**The persisted evidence pack.** `reconstruction/evidence/<va8>/evidence.json`, hash-anchored by its own `content_sha256`. `validate._persisted_pack` recomputes that digest the way `evidence.collect` computes it (with `content_sha256` set to `None` and no `paths` key attached), and `validate.validate` **reuses a pack that verifies** instead of re-collecting one with `live=False`. That single change is what made the listing available at all: `collect(live=False)` never calls `_live_disassembly`, so it stored `disassembly = unavailable` and every listing-dependent check was structurally incapable of `PASS` — the machine evidence was on disk, hash-anchored, and thrown away. A pack that fails verification (`unreadable`, `schema_mismatch`, `target_mismatch`, `digest_mismatch`) falls through to the collection path, is reported in `report["binary_evidence"]["integrity"]` and `["integrity_note"]`, and is not overwritten. A pack handed in by the caller is `source: "caller_supplied"`, `integrity: "unchecked"` — never `verified`, because there is nothing on disk to check it against.

**`categories.disassembly.value.instructions` is the universal per-VA machine oracle.** 195 of the 200 committed packs have the category `available`; 172 carry a real instruction list; 168 of those have `categories.abi.value.parse.declared_count == len(instructions)`.

**A truncated envelope is not a listing — explicit prohibition.** 23 of the 200 packs carry a `disassembly` value of the shape:

```json
{"truncated": true, "preview": "<string>", "original_bytes": 22151, "sha256": "…"}
```

while their category still reads `availability: "available"`, `evidence_state: "LIVE"`. **The `preview` string must never be parsed as an instruction listing.** A reader that checks only `availability` will treat a byte-bounded prefix as the body, and a partial oracle produces a spurious `CONSTANTS` `FAIL` — a reconstruction refuted by evidence that was never collected. `validate._listing` returns nothing for such a value, so the affected checks read it as absent. (Two other categories use the same envelope: 14 `function_identity` values and 1 `contradictions` value. Only `disassembly` is an oracle, but the rule is general.)

**`dependencies.edges` is the only reconstruction-independent call oracle.** Its `reference_type` census over the index's per-record edge lists is `direct-call` 8030, `computed-call` 91, `thunk` 33, `external` 19 — 8173 edges in total and **zero data-reference edges of any kind**. `validate.CALL_REFERENCE_TYPES` admits exactly those four, and anything else in the export is a data reference that cannot adjudicate a call set. The full export on disk is larger (223,704 rows, including 4,049 `data-ref` and 11,898 `vtable-ref` rows); those row types never reach the per-record edge lists, which is why the census above shows none. The census is quoted from the committed `reconstruction/knowledge/index.json`; a projection rebuilt in memory today carries two records the committed file does not yet have, and reads `direct-call` 8057 with the other three unchanged.

**GLOBALS has two machine sides: the listing, and a Ghidra data-reference artifact.** `record["globals"]` remains reconstruction-authored and is still not an oracle — validating a source against it would be validating it against itself. The listing is one machine side: it can evidence an *absence* (a complete listing naming zero data-segment addresses is positive evidence the body touches no global, a `PASS`), but it could not corroborate a presence.

The second side is `knowledgegraph/triage/datarefs-2540f2ca.tsv`, read by `evidence_datarefs`. It exists because the edge export could not supply one: its `data-ref` row is *defined* as a reference to a function entry, so every reference to a global, a TLS slot or a constant table was discarded by the exporter (`ExportXrefs.java:322-343` before the extension). It carries Ghidra's own `RefType` classification — `read` / `write` / `readwrite` / `other` — and the memory block the address lives in, which the listing cannot say.

Measured on the canonical image (snapshot `2540f2ca`): the pre-extension exporter discarded **731,045** references. **573,206** of those were into Ghidra's `stack` address space — frame slots, not globals — and the sidecar deliberately excludes them; **157,839** were RAM-space; the predicate emits **157,640**, which the canonicalizer dedupes to **157,633** (Ghidra holds 7 genuinely duplicated `Reference` objects) across **29,943** distinct callers and **52,198** distinct targets. Of those rows, 89,925 land in *writable* storage (`.data` / `tdb` / `CONST`), which is where a mutable global can live; the remainder are read-only constants, and 1,956 are references into `.text` that are jump tables rather than globals. The segment column is what keeps those apart, and it is Ghidra's own classification of the address rather than an inference.

The arms are ordered so the extension can only ever *add* corroboration. A `PASS` is left alone — an evidenced absence needs no second source, and a disagreement between two machine sources is reported inside the pass rather than used to revoke it. A `WARN` becomes a `PASS` only when the artifact records a reference to **every** address the source names **and** the listing corroborates at least one, so one machine source is never enough and a reconstruction cannot pass by getting one address right and others wrong. Every other `WARN` stays a `WARN`, with the artifact's own reading attached. An address the artifact does *not* record is never on its own a refutation: the artifact indexes the pinned caller universe at one moment, and a body read at another would produce exactly that shape.

The source side is read in both spellings a reconstruction actually uses: a `0x`-prefixed literal, and this repository's own `g_<va8>` global-name convention — the same convention `CALLEE_TOKEN` already reads on the call side. Reading only `0x` literals meant a reconstruction that declared its global *correctly* was invisible to the check, so its claims could never be corroborated; the corpus names 11 distinct data-range addresses this way.

**`categories.abi.value.receiver` is machine-derived, and it is bounds — not a layout.** It names the base register the body addresses the receiver through and the set of displacements it was seen using. It is an object on 191 of the 200 packs, a bare boolean on 4 (`true` on 3, `false` on 1), and absent on the remaining 5; `bounds_only` is `true` on 190 of those 191 objects, and 75 of them list no offsets at all. `bounds_only` is the record's **own statement that its enumeration is open** — "where the body was *seen* reaching", not everything it reaches — so it is a witness that **widens what a claim may be grounded in and refutes nothing**. A declared offset outside such a window is uncorroborated, not contradicted, and it is a `WARN`; only an *enumerating* record (`bounds_only` not `true`) that excludes the offset **and** a complete listing that does not show it either is a `FAIL`. The `FIELDS/OFFSETS` `PASS` wording must still never say that a field layout is confirmed. The receiver record is a set of displacements; it cannot say which member is which, so a source that names a field is a `WARN` even when its displacement is in bounds.

**The complete listing outranks the receiver record, because the listing enumerates and the record only samples.** The record is a derived observation; the listing, once `parse` shows it was consumed in full, is the whole body. So the ground truth for "which offsets does this body reach through its receiver" is the **union** of an alias-aware scan of the listing and the record's offsets, and where they disagree the listing governs. Measured: `0x0067e6f0`'s record enumerates `{0x50, 0x60, 0x64}` while its listing shows `0x4c, 0x50, 0x64` through `ECX`; the old rule differenced the source's declared offsets against the record alone and reported a contradiction the machine listing contradicts. Alias awareness is what makes the scan a witness at all: `_receiver_displacements` reads only operands naming the *named* register, so a body that copies its receiver (`MOV EBX,ECX`) and then reads `[EBX+0x18]` was invisible to it — 16 corpus targets held a `PASS` whose "the body addresses no receiver field" claim the machine refutes (a bare `[ECX]` is a field access at offset **zero**), and 16 more were told the source and the body disagree with a record the complete listing itself contradicts.

**`record["globals"]` and `record["vtables"]` are authored, not observed.** 56 index records carry `globals`; 272 carry `vtables` ids (3,589 in total, 1,308 distinct) and **none of those ids belongs to a pack-backed record**. `record["vtables"]` is formally withdrawn as an oracle: it is a transitive classifier association that contradicts the xref export outright — `0x00b1fbf0` carries 356 `vtable:` ids against a `vtable_reference_count` of 0 on the same record.

**`ghidra_function.dispatch` is `null` in every committed pack** (196 packs carry the category with `dispatch: null`, 4 carry no value at all) because the bridge passes the field through without computing it. Branching on it is branching on nothing, so the listing is the real control-flow oracle.

**`categories.abi.value.parse` is the listing-completeness oracle.** It carries `declared_count`, `degraded`, `unparsed`, `esp_unresolved`, `flow_complete`, `frame`, `layout` and `local_extent`. Across the 190 packs that have it, `degraded` is `true` on 30 and `unparsed` is non-zero on 30; 160 are clean on both. Among the 172 complete listings, 168 have a parse block and every one of those has `declared_count == len(instructions)`; 144 of the 168 are clean on `degraded`/`unparsed` as well. `CONSTANTS` may only pass on the 144-class evidence, because a `declared_count` that matches the emitted list while `unparsed > 0` is a coincidence, not a proof that the listing was consumed in full.

**Branch targets against the listing's own span are the control-flow oracle.** The span is `[min, max]` of the listing's own instruction addresses. Across the 172 complete listings there are 569 conditional branches; every one of them has an absolute target, and every one of those targets lands inside its own listing's span — so today the `WARN` arms for an unbounded or escaping branch are reachable in principle and not in practice on this corpus. Widening the scan to `JMP` as well (a tail transfer, which MSVC emits where the source has a call) adds 78 targeted jumps, 12 of which leave the span in 10 of the 172 listings: those 10 listings are slices, and both `CONTROL FLOW` and the `CALLS` machine-vs-machine rule exist to say so instead of passing them. A branch whose operand is not an absolute address cannot be bounded at all, and an unbounded branch is never counted as a closing one.

**`categories.abi.value.dispatch.indirect_calls` plus a listing scan is the virtual-dispatch oracle.** The scan must cover `CALL`/`JMP` to a register *and* `CALL`/`JMP` to a `[size ptr [...]]` memory operand. The previous pattern's size prefix was `[A-Z]{2,3}`, which cannot match `dword` — Ghidra spells the operand `dword ptr [EAX*0x4 + 0x5dd840]`, five letters — and the corpus contains no other bracketed shape for it, so the pattern matched a shape the listing never emits and therefore matched **zero instructions across all 172 listings**. A detector that cannot fire is not a detector. It produced one factually wrong `FAIL`: at `0x00580cb0` the report read "the 91-instruction body contains no indirect call but the source span declares a virtual-slot boundary", while that body contains six register transfers (`CALL EDX` four times, `CALL EAX` twice). With the fixed scan the same target reads "the complete 91-instruction body names 6 indirect dispatch site(s) and the machine dispatch record counts nothing and the source declares a slot boundary" — a `WARN` about unreviewed slot offsets, which is what the evidence actually supports. `validate.INDIRECT_TRANSFER` and `validate.INDIRECT_REGISTER_TRANSFER` are the two halves of the fixed scan. The machine record agrees with the listing on 168 of the 172 complete listings (it counts a different number on 0 of them; the other 4 carry no `dispatch` record at all), and 22 of the 23 truncated-envelope packs still carry a `dispatch.indirect_calls` value — which is why the record is worth consulting where the listing is gone.

## Absence is not a pass

The rule, stated once:

> A check with no relevant phenomenon may be `PASS` **only if that absence is itself evidenced** — a complete, bounded machine oracle that covers the whole body and finds nothing. `NOT_AVAILABLE` is never a disguised `PASS`.

Worked examples from the committed corpus, all checkable in `reconstruction/evidence/00fc7e10/evidence.json` and the source it resolves to:

- **A straight-line body is a `CONTROL FLOW` `PASS`.** `0x00fc7e10` has a 5-instruction listing spanning `0x00fc7e10..0x00fc7e1e` with zero conditional branches. The listing is the evidence of the absence: it covers the whole body and there is no branch in it. The verdict records that the source declares no branch keyword, and states that keyword shape is a source-side signal that is not part of the verdict.
- **A complete listing naming no data address is a `GLOBALS` `PASS`.** The same target: zero data-segment addresses in the listing and none in the span, so the machine body is positive evidence that it touches no global. The artifact is read as a second opinion and, recording nothing here, agrees; that agreement is reported in the detail but is not what the pass rests on, because the claim is an absence and the listing alone is the evidence for it.
- **The same target is `NOT_AVAILABLE` on `CONSTANTS` and `WARN` on `FIELDS/OFFSETS`.** Its listing exists but carries no `parse` record, so it cannot be shown to have been consumed in full; and its `receiver` is a bare `true` with no register and no offsets, so the span's `word_08` / `word_10` declarations have nothing to be checked against. `VIRTUAL DISPATCH` is `WARN` rather than `PASS` even though the listing is clean, because no `dispatch` record was collected to corroborate it: **a missing record is not a record of zero.** The aggregate is `NOT_AVAILABLE`. Three passes by evidenced absence, and the target still does not pass — which is the point.

The counter-examples that must never produce a `PASS`, each with the reason:

| Situation | Verdict | Why not a pass |
|---|---|---|
| no source artifact for the target | `NOT_AVAILABLE` on every structural check | nothing was read, so nothing was compared |
| source artifact present but the target span does not resolve | `NOT_AVAILABLE` | the reconstruction under test was never located in the file |
| no listing: category unavailable, or a truncated envelope | `NOT_AVAILABLE` for the listing-dependent checks | there is no body to compare against; a preview is not a body |
| a caller-supplied evidence pack whose digest could not be checked | whatever the checks say, reported as `integrity: "unchecked"` | the pack is taken on trust, so no verdict over it is `verified`; a `PASS` reached this way is not comparable with one over a verified pack |
| a `coverage` value of `partial` | never sufficient on its own | a partial oracle bounds one direction only; a subset match against a lower bound is not agreement |
| a truncated dependency edge list, **and no complete xref export for this VA** | `WARN` on `CALLS` | the machine callee set is then a lower bound and cannot bound the source |
| a `dependencies.edges` projection truncated at export time, **while the export itself is readable** | never on its own a verdict | the projection is a *scheduler* projection capped at `MAX_DEPENDENCY_EDGES = 30` rows, and `edges_truncated` is computed over a record's incoming **and** outgoing rows with the sort order putting every in-edge first — so of the 617 index records 149 carry the flag while only 25 have more than 30 outgoing rows and 47 project no outgoing callee at all (their whole window is fan-in). `CALLS` therefore reads the export whole (`evidence_xrefs.authoritative_callees`, one pass, cached on the file's `(mtime, size)`) and adjudicates over the complete callee set. `MAX_DEPENDENCY_EDGES` is untouched: it is a scheduler budget, and bounding the scheduler is not the same question as bounding the evidence |
| `record["globals"]` or `record["vtables"]` as the only counterparty | never an oracle | the reconstruction would be validating itself |
| `ghidra_function.dispatch` | never an oracle | it is `null` in every committed pack |

## What `STATIC_VALIDATED` does and does not mean

`STATIC_VALIDATED` is the composition `report["static"]["status"] == "PASS"` and `report["runtime"]["status"] == "GATED"`. It is not a field, not an enum member, and not a new state machine; nothing in the code emits the token.

It does **not** mean:

- that the reconstruction is compatible with the original at runtime — nothing here observes the original process;
- that it is byte-compatible with anything;
- that it was runtime-tested, or exercised under Wine, or observed in a trace;
- that gameplay parity is proven;
- that the ABI is correct against the original binary — the ABI check compares a calling-convention token, not a stack frame;
- a substitute for a live Ghidra read. A pack whose digest does not reproduce, or a listing that is a preview, is a statement about evidence, never about the binary.

It **does** mean: the reconstruction was adjudicated against machine evidence in all eight structural dimensions; each of those eight had a complete, bounded oracle; the aggregate ladder reached `PASS`, which means no check was `FAIL`, `UNKNOWN`, `WARN` **or** `NOT_AVAILABLE`; and the runtime axis is an open gate rather than a claim.

## Runtime validation

Runtime validation is the reconstruction being exercised in the **original** process under Wine. It is a separate axis with its own machinery, and today the honest state of all of it is: present, wired, and unexercised.

The field chain, from the worker side to the report:

| Field | Where | Meaning |
|---|---|---|
| `runtime_validation` | per-VA metadata sidecars under `reconstruction/metadata/**` | worker-side prose: `0` on 184 occurrences, plus `"not run"`, `"not performed"`, an object on 16, and on `0x00587a20` the string `"NOT_AVAILABLE -- no original-process trace exists in this repository for this target; nothing was run and nothing failed."` That is a **worker's note, not a verdict**: the runtime axis has no `NOT_AVAILABLE` state, and the index does not read this field |
| `audit_runtime_validated` / `audit_runtime_gated` | `functions[]` in `knowledgegraph/research/source-reconstruction-manifest.json` | the audited form, on 238 of the manifest's 300 function records (the other 62 carry no audit fields): `0` on all 238, `true` on all 238 |
| `runtime_gates` | the same manifest, top level | the declared open gates (e.g. `gate-simulator-global-slots`) |
| `runtime_gated` / `runtime_validated` | index records | per-record projection; `runtime_validated` is `0` on all 615 records |
| `runtime{gates, validated, blocking_reason}` | index records | the block the validator reads; every one of the 615 records carries all three keys |
| `runtime_metadata` | the evidence pack category | the gates travel here, not in the reserved `runtime` slot |
| `report["runtime"]` | `validate._runtime_dimension` | `GATED` unless `record["runtime"]["validated"]` is a positive integer |

Observatory traces live under `tools/observatory/out/<run_id>/` (each with a `manifest.json`, `input.jsonl`, `shots.jsonl`, wine logs) and the committed examples under `tools/observatory/examples/`. They record what the original process did under a specific Wine, display and input environment, and that environment is part of the claim.

**The one place a runtime artifact gates a status promotion** is `runtime_tools.status_update`, the only writer of `docs/replacement-status.json`:

- `replaced-verified` requires a trace manifest that exists under `tools/observatory/out/` or `tools/observatory/examples/` (`runtime_tools._trace_manifest_hit`), or an explicit `trace_manifest` path. No manifest, no promotion.
- a decompilation reference **caps at `replaced-approx`**, with the reason the module states in its own docstring: *decompiler output = evidence, not truth*. A worker's "VERIFIED" claim stays a proposition, never state.

So no target has ever been runtime-validated: `runtime_validated` is `0` on all 615 index records, and the corpus-wide runtime measure `coverage.json#runtime.validated` is `0` against 299 gated. A **negative** trace result is first-class evidence and is not a pass: a run that recorded 0 events is evidence that the probes never fired — the process never reached the stage — not that behaviour matched. `docs/tooling/reconstruction-coverage.md` §7 carries the full token inventory; every token in it means *the observation was never attempted*.

## Open known gaps

What still cannot reach a static `PASS`, with the measured reason. None of these is a defect to be papered over; each is a coverage fact about the corpus (200 evidence packs, 615 index records, binary 3.1.0.22 / `25d42a7a…9d914e`), measured as described in §10.

| Gap | Measured | Consequence |
|---|---|---|
| no resolvable source span | 117 of 200 pack targets have no source artifact at all; 76 more have a source file whose target span does not resolve. 193 of 200 therefore cannot be adjudicated in any dimension | with the strengthened ladder, 193 of 200 pack targets are `NOT_AVAILABLE` at the aggregate regardless of their evidence quality |
| the 7 targets that do have a span | none reaches `PASS`: each of the seven retains at least one `NOT_AVAILABLE` and at least one `WARN`, and all seven report `runtime: GATED` | the nearest is `0x00fc7e10` (five `PASS`, two `WARN`, one `NOT_AVAILABLE`); the only blocker class left is missing machine evidence, not disagreement |
| pack targets with no index record | 114 of the 200 pack targets have no record in the committed `reconstruction/knowledge/index.json` (112 against a projection rebuilt in memory today) | for those, the xref-derived half of every check has no counterparty; they can be validated against a listing alone or not at all |
| packs with no `parse` block | 9 of the 200 carry an `abi` value with no `parse` record (4 of them still have a complete listing) | `CONSTANTS` cannot show its listing whole for those, so it stays `NOT_AVAILABLE`; 30 more are `degraded` or carry `unparsed > 0` and are `WARN` |
| truncated disassembly envelopes | 23 of 200 | those targets have no listing oracle, so `GLOBALS`, `CONSTANTS` and `CONTROL FLOW` are `NOT_AVAILABLE` for them, `VIRTUAL DISPATCH` is `NOT_AVAILABLE` or `UNKNOWN`, and `FIELDS/OFFSETS` can do no better than `WARN`. One of the seven targets with a resolvable span is in this class (`0x00be2440`) |
| no receiver register | 5 packs have no `receiver` object at all and 4 more carry a bare boolean instead of a bounds record | `FIELDS/OFFSETS` cannot ground an offset for those targets |
| a global claim is corroborated, never refuted | the data-reference artifact records 157,633 rows over 29,943 callers, but it indexes the pinned universe at one moment | `GLOBALS` can pass a corroborated claim and can always evidence an absence; an address the artifact does not record leaves the claim ungrounded rather than refuting it |
| dead dispatch field | `ghidra_function.dispatch` is `null` in all 200 packs | a capability gap in the bridge, not in the reconstruction; the listing substitutes for it |
| runtime | 0 validated, 0 negative observations, 299 gates open | no claim in this repository can be promoted past static evidence |

## Where these numbers come from

Every figure above is a count over a committed artifact, not an estimate. The census is reproducible without the validator:

```python
import glob, json, collections
packs = sorted(glob.glob("reconstruction/evidence/*/evidence.json"))
records = json.load(open("reconstruction/knowledge/index.json"))["records"]

listing = census = truncated = parse_missing = 0
for path in packs:
    categories = json.load(open(path))["categories"]
    value = (categories.get("disassembly") or {}).get("value")
    census += (categories.get("disassembly") or {}).get("availability") == "available"
    if isinstance(value, dict) and value.get("truncated") is True:
        truncated += 1
    if isinstance(value, dict) and isinstance(value.get("instructions"), list):
        listing += 1
    abi = (categories.get("abi") or {}).get("value")
    if isinstance(abi, dict) and not isinstance(abi.get("parse"), dict):
        parse_missing += 1

edges = collections.Counter()
data_refs = 0
for record in records.values():
    dependencies = record.get("dependencies") or {}
    data_refs += (dependencies.get("data_reference_count") or 0) == 0
    for edge in dependencies.get("edges") or []:
        edges[edge.get("reference_type")] += 1
```

Note that the index is a *generated* projection: a rebuild in memory can carry records the committed file does not yet have, which is why §5 quotes the committed file and names the rebuilt figures beside them. Where two numbers appear for the same measure, both are given rather than the more convenient one.

`report["static"]["evidence_basis"]` reports the same kind of count per target, and `report["binary_evidence"]` reports which pack the verdict was reached over (`source`, `integrity`, `content_sha256`, and an `integrity_note` whenever the pack on disk was not the one used). A verdict that cannot say which evidence produced it is not auditable, and both fields exist so it always can.

Snapshot: measured 2026-09-26 against `reconstruction/evidence/` (200 packs) and `reconstruction/knowledge/index.json` (615 records). The per-check verdict census moves while the checks are being changed; the corpus facts above do not.
