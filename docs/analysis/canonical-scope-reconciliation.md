# Canonical Scope Reconciliation

**Decision:** retain the canonical executable-function universe at **58,757** unchanged. The historical manager excess is **488 distinct EXTERNAL manager records outside the canonical executable VA universe, but 0 additional executable binary functions**. Of the 488, **360 have allowlist identity** and **128 are identity-unknown**.

## Question 1 — What is the discrepancy, and what caused it?

**Proven:** `59,245 - 58,757 = 488`. The 488 entries are contiguous `EXTERNAL:00000001` through `EXTERNAL:000001e8`, all `external=true` and `canonical=false`, with zero overlap against the 58,757 canonical `.text` VAs. The four disjoint ranges are exact: 122 + 121 + 121 + 124 = 488. This is an external-manager/address-space scope difference, not 488 missing canonical functions.

**Unobservable:** the current Ghidra bridge has no open program, so the historical 59,245 manager count and 488 identities were not freshly re-read. Snapshot/version drift is disproven for the committed corpus; stale live state remains a live limitation, not a demonstrated cause.

## Question 2 — Are these duplicates or generated/thunk/stub artifacts?

**Proven:** delta duplicate entries: **0**; all 488 entry keys are unique. Known canonical name collisions: **14 delta rows / 15 canonical matching addresses**; these are name collisions with zero VA overlap, not duplicate functions. The two allowlist targets outside the 488 are `EXTERNAL:000001ea` `WSAIoctl` and `EXTERNAL:000001ec` `WSASocketA`. Delta rows with `is_thunk=true`: **0**; `is_thunk=null`: **488**. Established generated rows: **0**; established stub rows: **0**; both classifications are unobservable for all 488 because external bodies are unavailable. The separate canonical corpus has 178 thunk-flagged functions and 141 SDK tail-alias repairs; neither count is the 488.

**Disproven:** the 488 are not a same-address duplicate set, not classified internal thunks, and not generated/compiler additions. **Unobservable:** live-manager-internal representation, external implementation equivalence, generated origin, and stub status.

## Question 3 — Are any genuinely distinct executable functions among the 488?

**Answer: no.** Genuinely distinct additional executable functions: **0**; entries: **none**. The rows are distinct as Ghidra EXTERNAL manager records only. Body size, local section/block, local body, function contract, and runtime validation are unavailable/not applicable; no row is a local executable body. Canonical executable functions remain **58,757** unique VAs.

## Question 4 — Which gameplay-support adjacency positives were confirmed?

**Exactly 7**, and these are static caller-category adjacencies—not gameplay bodies or gameplay contracts. Names/entries:

| Entry | Name | Token | Static gameplay callers |
|---|---|---|---:|
| `EXTERNAL:000000a7` | `QueryPerformanceCounter` | `EXT:KERNEL32.DLL::QueryPerformanceCounter` | 3 |
| `EXTERNAL:00000164` | `_localtime64` | `EXT:MSVCR90.DLL::_localtime64` | 4 |
| `EXTERNAL:00000196` | `wcstoul` | `EXT:MSVCR90.DLL::wcstoul` | 5 |
| `EXTERNAL:000001a6` | `wcsncmp` | `EXT:MSVCR90.DLL::wcsncmp` | 4 |
| `EXTERNAL:000001b4` | `wcschr` | `EXT:MSVCR90.DLL::wcschr` | 1 |
| `EXTERNAL:000001b7` | `iswctype` | `EXT:MSVCR90.DLL::iswctype` | 1 |
| `EXTERNAL:000001c3` | `_time64` | `EXT:MSVCR90.DLL::_time64` | 4 |

No row is promoted to gameplay logic. Caller names, categories, and callsites are contextual evidence only. Static xref adjacency is not runtime reachability.

## Question 5 — Which engine-boundary positives, shared-state roots, or package anchors were confirmed?

**Exactly 9** bounded host/engine-boundary positives:

| Entry | Name | Token | Xref edges | Distinct callers |
|---|---|---|---:|---:|
| `EXTERNAL:00000003` | `timeGetTime` | `EXT:WINMM.DLL::timeGetTime` | 7 | 5 |
| `EXTERNAL:00000020` | `QueryPerformanceFrequency` | `EXT:KERNEL32.DLL::QueryPerformanceFrequency` | 10 | 6 |
| `EXTERNAL:000000a7` | `QueryPerformanceCounter` | `EXT:KERNEL32.DLL::QueryPerformanceCounter` | 123 | 106 |
| `EXTERNAL:000000c5` | `TranslateMessage` | `EXT:USER32.DLL::TranslateMessage` | 1 | 1 |
| `EXTERNAL:000000cb` | `GetCursorPos` | `EXT:USER32.DLL::GetCursorPos` | 3 | 3 |
| `EXTERNAL:000000dd` | `PeekMessageW` | `EXT:USER32.DLL::PeekMessageW` | 2 | 1 |
| `EXTERNAL:000000de` | `DispatchMessageW` | `EXT:USER32.DLL::DispatchMessageW` | 1 | 1 |
| `EXTERNAL:000000e2` | `GetKeyState` | `EXT:USER32.DLL::GetKeyState` | 10 | 2 |
| `EXTERNAL:000000f7` | `GetAsyncKeyState` | `EXT:USER32.DLL::GetAsyncKeyState` | 11 | 5 |

These are external platform/input/timing boundary adjacencies; none is an internal engine interface. Shared-state external roots: **0**; package-anchor matches: **0**. The atlas candidate `PKG-22-RUNTIME-CRT-STL` is a candidate-only membership for all 488 rows, outside the canonical reconstruction universe, not an explicit package anchor.

## Question 6 — What is the final decision, and is later re-adjudication required?

**Decision:** keep the canonical 58,757 unchanged and report the 488 separately as external-only manager scope. No later re-adjudication is required for the current committed evidence. Re-adjudication is conditional if a fresh live manager row export, a new binary/snapshot identity, or new evidence changes the partition or resolves any of the 128 unknown identities.

### Evidence classification

- **Proven:** external/noncanonical scope, disjoint partition, exact arithmetic, 360/128 identity split, 0 canonical VA overlap, 0 additional executable functions, 0 duplicate delta entries, and the exact 7/9 adjacency positives.
- **Disproven:** missing canonical functions, same-address duplicates, internal-thunk classification, generated/compiler cause, and committed snapshot/version drift as the count explanation.
- **Unobservable:** fresh live manager identities, external implementation bodies and semantics, generated/stub origin, runtime reachability, semantic duplicate identity, and actual per-row reconstruction-package requirements.

The complete deterministic 488-row index, all source hashes/provenance, cause adjudications, null/unavailable fields, and exact positive/negative lists are in `knowledgegraph/research/canonical-scope-reconciliation.json`.
