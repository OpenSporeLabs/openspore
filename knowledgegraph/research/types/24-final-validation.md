# Final Machine Validation

## Verdict

**PASS.** The final validation artifact reports 22 PASS structural conditions, zero FAIL conditions, 36/36 CTest tests passed, and no remaining blockers.

## Target integrity

- Target: `knowledgegraph/research/type-archaeology.json`
- Bytes: `81081768`
- SHA-256: `302452c3f4dec236722dd8e43ed4632b43c1faff1e66d3d3cc0b6f5d164f0af4`
- JSON parse: `PASS`
- Canonical parse/serialization SHA-256: `c153de4204e5a91b338f650cfc5a2c3c0d00f4c1e3356fc5bc21ce78720da80a`
- Repeatable serialization: `PASS`
- Required top-level sections: `19` in declared order; `class_families` extension: `explicit_user_required_extension`

## Exact metrics

| Metric | Declared | Computed | Result |
|---|---:|---:|---|
| `M-BASELINE-FUNCTIONS` | 58757 | 58757 | PASS |
| `M-BASELINE-XREFS` | 223704 | 223704 | PASS |
| `M-VTABLE-INVENTORY` | 3081 | 3081 | PASS |
| `M-SELECTED-VTABLES` | 33 | 33 | PASS |
| `M-CLASS-FAMILIES` | 1250 | 1250 | PASS |
| `M-NAMING-ONLY-FAMILIES` | 1199 | 1199 | PASS |
| `M-WORKER-ARTIFACTS` | 17 | 17 | PASS |
| `M-CANONICAL-TYPES` | 6967 | 6967 | PASS |
| `M-CANONICAL-FIELDS` | 646 | 646 | PASS |
| `M-CANONICAL-VTABLES` | 128 | 128 | PASS |
| `M-CANONICAL-SLOTS` | 53 | 53 | PASS |
| `M-CANONICAL-METHODS` | 889 | 889 | PASS |
| `M-CANONICAL-CONFLICTS` | 2738 | 2738 | PASS |
| `M-CANONICAL-QUESTIONS` | 231 | 231 | PASS |
| `M-COVERAGE-EVIDENCE` | 9672 | 9672 | PASS |
| `M-COVERAGE-WORKER-SECTIONS` | 17 | 17 | PASS |
| `M-SEMANTIC-TYPE-ROWS` | 1591 | 1591 | PASS |
| `M-TYPE-PROJECTION-ROWS` | 5376 | 5376 | PASS |
| `M-FAMILY-TYPE-KEY-REUSE` | 16 | 16 | PASS |
| `M-METHODS-WITH-NORMALIZED-KIND` | 33 | 33 | PASS |
| `M-METHODS-WITH-SOURCE-NATIVE-KIND` | 48 | 48 | PASS |
| `M-RECON-SOURCE-CLASSIFICATIONS` | replaceable-infrastructure=13;reproduce-layout=32;semantic-interface-only=65 | replaceable-infrastructure=13;reproduce-layout=32;semantic-interface-only=65 | PASS |
| `M-RECON-NORMALIZED-CLASSIFICATIONS` | preserve=33;replace=21;unknown=145 | preserve=33;replace=21;unknown=145 | PASS |

## Structural conditions

| ID | Condition | Result | Evidence |
|---|---|---|---|
| `STRUCT-001` | `target_json_syntax` | **PASS** | validated |
| `STRUCT-002` | `canonical_parse_serialization_repeatable` | **PASS** | canonical_hash=c153de4204e5a91b338f650cfc5a2c3c0d00f4c1e3356fc5bc21ce78720da80a |
| `STRUCT-003` | `schema_identity` | **PASS** | validated |
| `STRUCT-004` | `required_top_level_sections_and_order` | **PASS** | sections=19 |
| `STRUCT-005` | `top_level_section_types` | **PASS** | section_types=19 |
| `STRUCT-006` | `stable_ids_unique` | **PASS** | record_sections=15; duplicates=0 |
| `STRUCT-007` | `type_record_contracts` | **PASS** | rows=6967 |
| `STRUCT-008` | `alias_record_contracts` | **PASS** | rows=2658 |
| `STRUCT-009` | `field_record_contracts` | **PASS** | rows=646 |
| `STRUCT-010` | `vtable_record_contracts` | **PASS** | rows=128 |
| `STRUCT-011` | `slot_record_contracts_and_pointer_arithmetic` | **PASS** | rows=53 |
| `STRUCT-012` | `inheritance_record_contracts_and_scope` | **PASS** | rows=267 |
| `STRUCT-013` | `lifecycle_record_contracts_and_runtime_scope` | **PASS** | rows=220 |
| `STRUCT-014` | `method_record_contracts_and_runtime_scope` | **PASS** | rows=889 |
| `STRUCT-015` | `evidence_record_contracts` | **PASS** | rows=9672 |
| `STRUCT-016` | `semantic_and_reconstruction_contracts` | **PASS** | validated |
| `STRUCT-017` | `question_and_conflict_contracts` | **PASS** | validated |
| `STRUCT-018` | `substantive_evidence_and_source_pointer_coverage` | **PASS** | issues=0 |
| `STRUCT-019` | `internal_reference_integrity` | **PASS** | issues=0 |
| `STRUCT-020` | `source_pointer_resolution` | **PASS** | issues=0 |
| `STRUCT-021` | `source_artifact_hashes_and_json_keys` | **PASS** | manifest=23; mismatches=0 |
| `STRUCT-022` | `deterministic_arrays_and_policy` | **PASS** | arrays sorted; policy violations=0 |

## Source artifact hashes

- Manifest entries: `23`
- JSON/Markdown pairs: `22`
- Contextual sources: `1`
- File hash checks: `45`; verified: `45`; mismatches: `0`

| Source | Kind | Path | SHA-256 | Match |
|---|---|---|---|---|
| `AUD-17` | json | `knowledgegraph/research/types/17-audit-integrity.json` | `5e3f0175695b952d6bb4e9cfac76c4273218a5be7a5c6b2bca19d103c0ddc6b8` | PASS |
| `AUD-17` | markdown | `knowledgegraph/research/types/17-audit-integrity.md` | `3976f43c5dc6fff552dcfb2375fcef4d07a732e0cac286b71d3bf268b9ba4f6d` | PASS |
| `AUD-18` | json | `knowledgegraph/research/types/18-audit-coverage.json` | `53defe7e7a7a1c228f472b200401a64452a4588138a64943512d79f6bd233f4c` | PASS |
| `AUD-18` | markdown | `knowledgegraph/research/types/18-audit-coverage.md` | `63f3abcf7fb31075e3be97955934ac792c395a6f338e0e1170726cb36241dd4f` | PASS |
| `AUD-19` | json | `knowledgegraph/research/types/19-audit-conflicts.json` | `9cafbd7177d728f085fc5e631f06d499c062bc274b2736e07aaab53fc868d8ad` | PASS |
| `AUD-19` | markdown | `knowledgegraph/research/types/19-audit-conflicts.md` | `0a680f46a44830746be16cec5d2a94a7f3dd37f11c09fdb66664332f7eeb89e5` | PASS |
| `AUD-20` | json | `knowledgegraph/research/types/20-synthesis-blueprint.json` | `3ee434b53fed20ac458cf214faa279b9c1419d184f75c07948965a952f1566ec` | PASS |
| `AUD-20` | markdown | `knowledgegraph/research/types/20-synthesis-blueprint.md` | `766f4893c8b3c81323c6d95d39c0127a245bd0381f2f0595687b9b914ea33b2f` | PASS |
| `AUD-21` | json | `knowledgegraph/research/types/21-report-brief.json` | `e9e3bf5cc48fd5222b3685711b2df96f9750f675674bc74d6461ae122f6d6030` | PASS |
| `AUD-21` | markdown | `knowledgegraph/research/types/21-report-brief.md` | `62a9049d33fcec49ae7014788cebdf3f51ebb24689e904b5d2b5c337a1ae7efc` | PASS |
| `CAMPAIGN-CELL-STAGE` | contextual | `docs/analysis/campaigns/cell-stage-campaign.md` | `a13f740a9f890277277a85775ad58a710d4f9683be189edfdb06a407356e533a` | PASS |
| `WA-00` | json | `knowledgegraph/research/types/00-corpus-inventory.json` | `d9f48d1948df7767416ebbd8821d5e64af00b5c593366bcf746aeee5a7e7e0cd` | PASS |
| `WA-00` | markdown | `knowledgegraph/research/types/00-corpus-inventory.md` | `07277613b0efdbb95d2407012a8978adb49b8d5cd1f9400ddfbc499f92c4d99d` | PASS |
| `WA-01` | json | `knowledgegraph/research/types/01-simulator-core.json` | `704b3e997715825020e64e70ae08a9fe86238be6360d20f972744dce4215ebc6` | PASS |
| `WA-01` | markdown | `knowledgegraph/research/types/01-simulator-core.md` | `9b3b4c9f0bc575e5711e9749880c4755d1291b764260bb31614c6e9ae45660cb` | PASS |
| `WA-02` | json | `knowledgegraph/research/types/02-gameplay-entity.json` | `465d64a0885f7aee43ac042e8ce9b947a6d1c7d1a4115d47c2fd2bfb1aa84bd3` | PASS |
| `WA-02` | markdown | `knowledgegraph/research/types/02-gameplay-entity.md` | `4dadbea01bca5580d79934470fa49b4e3bcf5998926c3eec9183e3f338fc3d43` | PASS |
| `WA-03` | json | `knowledgegraph/research/types/03-creature.json` | `54da9e9ecbdec57362e06496bb73bbd9ede56097f45218b062dc3ff73f1bea1f` | PASS |
| `WA-03` | markdown | `knowledgegraph/research/types/03-creature.md` | `e7579a65591b9eeaff7adc5cb3edfcaaf74e444fa69ce1d94defa16a2d0a2766` | PASS |
| `WA-04` | json | `knowledgegraph/research/types/04-world-planet.json` | `26a33d0d114568549824e7e0c3e27b22b18b722e3fdf362ae5b47b9633e36f16` | PASS |
| `WA-04` | markdown | `knowledgegraph/research/types/04-world-planet.md` | `8158f2622d4ded9a7f7b0210fd38ddebcc724fcc73eb8e9f540002783a1d5f39` | PASS |
| `WA-05` | json | `knowledgegraph/research/types/05-empire-space.json` | `bcd2cb8dfa80237b2787b9cd185215398498f6a2dc10b5e283954efdcab560a8` | PASS |
| `WA-05` | markdown | `knowledgegraph/research/types/05-empire-space.md` | `8a484b3e48aea298b9af4d623a9d8938c7c5b36c5cbb8977c1ac28ad8536591f` | PASS |
| `WA-06` | json | `knowledgegraph/research/types/06-editor-ui.json` | `f6c6b0652a8c7c68724423e7af5a2d5731a09c96852a286167ff186172fe1083` | PASS |
| `WA-06` | markdown | `knowledgegraph/research/types/06-editor-ui.md` | `1b97dc7a8148792a240a5d01103fc5cc37b4f3b26c30d713a997f4610272f653` | PASS |
| `WA-07` | json | `knowledgegraph/research/types/07-event-message.json` | `c6e1abb8516011fe6071bddd5088f5dc08678d944da2b08b68aade201e1f0fe8` | PASS |
| `WA-07` | markdown | `knowledgegraph/research/types/07-event-message.md` | `6f6c6958b7eb6eb9ae8d15b678321807fdbc05d478385d55587c73720863b52a` | PASS |
| `WA-08` | json | `knowledgegraph/research/types/08-persistence-serialization.json` | `2bfa6e0e00e9a1304e36c7dd2adaaa03a2109c52b46219929853ab044f7bc4a9` | PASS |
| `WA-08` | markdown | `knowledgegraph/research/types/08-persistence-serialization.md` | `204c1649b3b72b251dde6974a3cf62dfb6d1c1e56471dfef367c23673f8d48ae` | PASS |
| `WA-09` | json | `knowledgegraph/research/types/09-asset-content.json` | `3ea2ae16d8cd8d693586d7c466b7ad919edc1d01b0c978e1ce7eb68d270331d3` | PASS |
| `WA-09` | markdown | `knowledgegraph/research/types/09-asset-content.md` | `d2b74c74f0cb5803fd49caacdc9ebb8592a55657b9b19fbc555c80e58fbe0ccc` | PASS |
| `WA-10` | json | `knowledgegraph/research/types/10-managers-registries.json` | `38042e96352ebfa7449f81653966bb53159ffe5a84b45cab1805abaea5d2ef09` | PASS |
| `WA-10` | markdown | `knowledgegraph/research/types/10-managers-registries.md` | `88cb94f8c0ecb840a009aff08ecebd8d9f44546442d8d602ff9c8e0251ee5f9f` | PASS |
| `WA-11` | json | `knowledgegraph/research/types/11-vtable-archaeology.json` | `16ba425a90450fa03ce9614ad8681e8095e3c191fd6608465c7f4b3f09ae7050` | PASS |
| `WA-11` | markdown | `knowledgegraph/research/types/11-vtable-archaeology.md` | `9698f997a07b77e27b61db6987ea19fb692119157f887dac56c349e2071ae5ec` | PASS |
| `WA-12` | json | `knowledgegraph/research/types/12-field-archaeology.json` | `dddbc04ab720a0d4f2c683a9f568bff083bcd05198e6c0d94548e7c3d2170129` | PASS |
| `WA-12` | markdown | `knowledgegraph/research/types/12-field-archaeology.md` | `f6da1e1b329085cccf7138e81acc5c318be68a713520c089b7b3caa122e25e22` | PASS |
| `WA-13` | json | `knowledgegraph/research/types/13-lifecycle.json` | `c4fd653270baca4efb425107e60b4b9a3ae1677bbf5a870af0d422e6b42ce070` | PASS |
| `WA-13` | markdown | `knowledgegraph/research/types/13-lifecycle.md` | `90897394cb9c85a0451e31e5dfacc4febf58c4944e2fb7fed3a150ac34fa2281` | PASS |
| `WA-14` | json | `knowledgegraph/research/types/14-class-families.json` | `3d54b5969cfe57dcc4808a6df83f84547de8b0d6f97f0ff2f1f4e99a3b3eff28` | PASS |
| `WA-14` | markdown | `knowledgegraph/research/types/14-class-families.md` | `2816dceab1e1cf9a9e0f198cf5a060fedd3e6261f0af69fa7764b7993b1509a4` | PASS |
| `WA-15` | json | `knowledgegraph/research/types/15-reconstruction-relevance.json` | `00610332e84ccc064432641306d952989c40be43afd884923de7adc8fcfef384` | PASS |
| `WA-15` | markdown | `knowledgegraph/research/types/15-reconstruction-relevance.md` | `c06d3cca605ad079c82158e0313a05d0d1852ad48d3142d558358793a881d573` | PASS |
| `WA-16` | json | `knowledgegraph/research/types/16-misc-unknown.json` | `3fd1b8e51acbaf39984ee5ada662fed84ac723aac78556f56a3339d0cd2383c4` | PASS |
| `WA-16` | markdown | `knowledgegraph/research/types/16-misc-unknown.md` | `8889cbd072579eaaec4e09ca1e616a74df8ccece9da0bf9e1aa04120e0b66966` | PASS |

## Repository commands

| Command | Working directory | Outcome | Result |
|---|---|---|---|
| `cmake .. && make -j` | `build` | **PASS** | CMake configured successfully and the existing Release build completed successfully with all targets built. |
| `ctest --output-on-failure` | `build` | **PASS** | 36/36 passed; 0 failed; 0 skipped |
| `python3 <temporary machine validator>` | `.` | **PASS** | Final machine validator completed with 22 PASS conditions and 0 FAIL conditions. |

## Integrity policy

- Internal reference issues: `0`; source pointers resolved: `30037`; source pointer issues: `0`.
- Array-sort failures: `0`.
- Timestamp values: `0`; UUID values: `0`; absolute machine paths in target: `0`.
- Circular provenance entries: `0`; runtime overclaims: `0`; RTTI structural overclaims: `0`.

## Scope

Only the two requested `24-final-validation` outputs are deliverables. The target corpus and all source, final JSON inputs, SPORE, Ghidra, knowledge-graph, history, and other documentation files remain outside the validation write set.
