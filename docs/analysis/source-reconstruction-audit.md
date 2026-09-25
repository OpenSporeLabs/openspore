# Source Reconstruction Audit

As of 2026-09-25, 10 integrated functions were audited across `PKG-01`, `PKG-06`, `PKG-10`, and `PKG-12`, plus the targeted `0x00e5c780` P0 resolution. All 10 integrated functions remain runtime-gated; `runtime_validated=0`.

## Counts

| Metric | Count |
|---|---:|
| Functions audited | 10 |
| P0 | 0 |
| P1 | 9 |
| P2 | 1 |
| P3 | 0 |
| Repairs performed | 1 |
| Runtime-gated findings | 10 |
| Clean findings | 10 |

P0-001 is statically resolved as a fixed guarded-lower-bound contract. P1/P2 counts include propagation and document metadata boundaries; they are not all integrated-body semantic defects. The repaired PKG-12 function is clean after final semantic and ABI re-review.

## Findings

| ID | VA | Finding | Status / boundary | Evidence |
|---|---|---|---|---|
| P0-001 | `0x00e5c780` | Live traversal retains a lower-bound-shaped candidate, then the final unsigned comparison rejects a greater successor; the accepted candidate is exactly equal to the query. | Resolved statically as a fixed hybrid guarded lower bound; do not propagate successor behavior. | `knowledgegraph/research/map-semantics-resolution.json`; `docs/analysis/map-semantics-resolution.md`. `0x00b21340`, `0x00ba9370`, and `0x01021300` are exact-find dependent; `0x00b3d300` is independent. |
| P1-001 | `0x00b3d300` / `0x00b3d400` | Alternate and canonical noun roots read distinct slots; publication, equality, and lifetime are unresolved. | Metadata boundary; no body repair. | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:15-17`; `docs/analysis/semantic-decomp.md:195`. |
| P1-002 | `0x00b3d2a0` / `0x00b3d3a0` | Alternate and canonical star roots read distinct slots; publication, equality, and lifetime are unresolved. | Metadata boundary; no body repair. | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:19-21`; `docs/analysis/semantic-decomp.md:195`. |
| P1-003 | Nine interior alias pairs | SDK labels are interior aliases of containing live functions, not separate entries. Includes `0x01073730/0x01073700`, `0x00835080/0x00834fa0`, `0x005cb690/0x005cb5a0`, `0x005c54b0/0x005c53c0`, `0x005c9320/0x005c9230`, and `0x005cb2a0/0x005cb240`. | Metadata boundary; no fabricated repairs. | `docs/analysis/semantic-decomp.md:196`. |
| P1-004 | `0x00834fa0` / `0x00835080` | Live `cSPUITextZoom` has seven stack arguments and `RET 0x1c`; the six-parameter SDK label is interior. | Preserve the observed ABI. | `docs/analysis/semantic-decomp.md:154,199`. |
| P1-005 | `0x013f7b54` | Live `EditorNamePanel` table targets occur at `+0x30` and `+0x58`; inherited slot ownership is unresolved. | Metadata boundary. | `docs/analysis/semantic-decomp.md:135,198`. |
| P1-006 | `0x005cb240` / `0x005cb2a0` | Live body is the active-category setter; the stale interior `GetSelectedRigblockPaint` alias is rejected. | Metadata boundary; no body repair. | `docs/analysis/semantic-decomp.md:136,197`. |
| P1-007 | `0x00b28ec0` / `0x00b3d440` | Persistence candidate is not a persistence manager; the accessor does not establish manager membership. | Do not promote ownership. | `docs/analysis/semantic-decomp.md:151,188`. |
| P1-008 | `0x00ff3f00` | Local timeline-event command-line pointer accessor on `OpaqueTimelineEventData`; not Cell state. | Runtime-gated local accessor. | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:27-32`; `docs/analysis/semantic-decomp.md:137,157`. |
| P1-009 | `0x00dd0e10` | Blocked dispatch remains a local timeline-event variant boundary with no network edge. | No online promotion. | `docs/analysis/semantic-decomp.md:112,157,187,200-201`. |
| P2-001 | `0x00b3d4f0` | Body is mechanically clean, but `Simulator_GetUIMissionLogManager` is alias-unresolved. | Not evidence of `cMissionManager`. | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:23-25`. |

No P3 finding was recorded.

## Function disposition

| VA | Package | Current source | Disposition | Evidence boundary |
|---|---|---|---|---|
| `0x00b3d300` | PKG-01 | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:15-17` | Clean; gated | Alternate noun root only. |
| `0x00b3d2a0` | PKG-01 | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:19-21` | Clean; gated | Alternate star root only. |
| `0x00b3d4f0` | PKG-01 | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:23-25` | Mechanically clean; P2 alias boundary | No `cMissionManager` evidence. |
| `0x00ff3f00` | PKG-01 | `src/reconstruction/pkg01_roots/pkg01_roots.cpp:27-32` | Clean; gated | Local timeline command-line pointer; no Cell/online semantics. |
| `0x00e7a7c0` | PKG-06 | `src/reconstruction/pkg06_cell_state/cell_state.cpp:407-482` | Clean; gated | Runtime damage/death values unresolved. |
| `0x00e7a4a0` | PKG-06 | `src/reconstruction/pkg06_cell_state/cell_state.cpp:484-560` | Clean; gated | Runtime removal/death values unresolved. |
| `0x00e7fd00` | PKG-06 | `src/reconstruction/pkg06_cell_state/cell_state.cpp:617-860` | Clean; gated | Cell and Cell GFX ordering remain separate. |
| `0x00e780a0` | PKG-06 | `src/reconstruction/pkg06_cell_state/cell_state.cpp:562-615` | Clean; gated | Cell identity and old-identity release preserved. |
| `0x005dda30` | PKG-10 | `src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp:169-191` | Clean; gated | `target_selector` candidate rejected. |
| `0x0102d1b0` | PKG-12 | `src/reconstruction/pkg12_space/space_functions.cpp:142-146,193-200,205-205,433-433` | Clean after repair; gated | Event carrier remains separate from keyed state. |

## Repaired ABI

`0x0102d1b0` originally used aggregate-by-value event-tail declarations that did not preserve the live x86 ABI. The current source explicitly preserves `0x00ce6950` as `__fastcall` ECX-only (`space_functions.cpp:142`) and `0x00aeb720` as `__thiscall` with ECX manager plus six stack words in order `space,event_data,0xc8fbf7d7,event_code,0,0` (`space_functions.cpp:143-146,197-200`). Final semantic and ABI re-review is clean.

The `0x00676e90` carrier is already correct as `{manager,0xd3f14a26,1}` in callee-stack order (`space_functions.cpp:414-415`); it did not require a final repair.

## High-risk boundary ledger

- `0x00e5c780` is a fixed guarded-lower-bound lookup: it rejects a strictly greater successor and is not a conventional lower-bound iterator. `0x00b21340`, `0x00ba9370`, and `0x01021300` therefore require exact-result behavior, while `0x00b3d300` remains independent.
- Cell identity versus Cell GFX ordering is preserved in `0x00e780a0`.
- Event-carrier separation is preserved in `0x0102d1b0`.
- Persistence candidate `0x00b28ec0` is not promoted to a persistence manager.
- Local timeline data is not promoted to online semantics.
- The earlier PKG-10 `target_selector` candidate is rejected. The current declaration at `src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp:25` and model stub at `src/reconstruction/pkg10_editor_dispatch/editor_dispatch_model_test.cpp:104-108` use `__thiscall`, matching `MOV ECX,[manager+0x5c]; CALL 0x00b1e4d0`.

## Tests after audit

| Check | Passed |
|---|---:|
| Package syntax | 4 |
| Editor model | 1 |
| Python | 427 |
| CTest | 42 |
| CMake build | 1 |
| Format | 1 |
| JSON validation | 2 |
| Git diff check | 1 |

## Runtime validation

No original-process or differential runtime validation was performed. All 10 functions remain runtime-gated and `runtime_validated=0`; repository and static checks do not establish original-binary compatibility.
