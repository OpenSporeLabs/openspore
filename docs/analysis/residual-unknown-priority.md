# Residual unknown priority research report

This report is a read-only research synthesis for the 1,976 canonical gameplay functions whose `gameplay_affinity` is `gameplay` and whose nested `gameplay_contract.status.semantic_understanding` is `not_established`. It is an ordering and investigation plan, not a gameplay implementation, runtime oracle, semantic promotion, or assertion that any original behavior has been reproduced.

## 1. Scope, binary, predicate, and counts

| Item | Exact value |
|---|---|
| Binary | `SporeApp.exe` 3.1.0.22, `x86:LE:32:windows` |
| Image base | `0x00400000` |
| Binary SHA-256 | `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e` |
| Canonical snapshot | `f0e310e0`; snapshot SHA-256 `5fd07ad16b85da68716e7e7fe2c1fcbc78e397888b532c0c09783b4480b6321e` |
| Canonical functions | 58,757 |
| Gameplay-affinity functions | 2,149 |
| Predicate | `gameplay_affinity=gameplay AND gameplay_contract.status.semantic_understanding=not_established` |
| Residual population | **1,976 unique VAs** |
| Existing partial gameplay rows excluded | **173** |
| Worker union | 8 physical worker files, 1,976 records, 1,976 unique VAs, no missing/extra/duplicate row |
| Track C cross-check | 2,149 total = 1,976 not-established + 173 partial |
| Runtime-verified functions | **0** |
| Persisted canonical decompilation in this residual population | **0** |
| Reused targeted/committed static observations | 176: 97 targeted-live, 10 committed-live, 69 decomp-gap body observations |

The residual is partitioned exactly as follows:

| Cluster | Rows | Primary package projection |
|---|---:|---|
| `editor-core` | 226 | `PKG-10-EDITOR-DISPATCH` |
| `editor-support` | 66 | `PKG-15-EDITOR-SUPPORT` (plus one dispatch projection) |
| `gameglobal-misc` | 35 | `PKG-20-GAMEGLOBAL` |
| `sim-core-systems` | 1,469 | `PKG-11-SIM-CORE` |
| `sim-space` | 5 | `PKG-12-SIM-SPACE` |
| `sporepedia-online` | 69 | `PKG-16-SPOREPEDIA-ONLINE` |
| `terrain-world` | 96 | `PKG-14-TERRAIN-WORLD`, with broad secondary projections |
| `ui-shell` | 10 | `PKG-18-UI-SCRIPTING` |
| **Total** | **1,976** | exact, non-overlapping residual partition |

The older decomp-gap documents report 1,977 rows. That historical population must not be added to or substituted for this 1,976-row nested-Track-C predicate. The current reconciliation explicitly excludes 173 partial gameplay rows and validates exact equality with Track C.

## 2. Sources, provenance, and evidence boundaries

The canonical identity and predicate authority is `knowledgegraph/research/semantic-atlas.json`, snapshot `f0e310e0`. The independent ranking and publication authority is `knowledgegraph/research/residual-unknowns/worker-00-reconciliation.json`; worker-00 pins the ranking and published projections, not the aggregate. The normalized synthesis under review is `knowledgegraph/research/residual-unknown-priority.json`.

All nine requested worker inputs were reviewed:

- `knowledgegraph/research/residual-unknowns/worker-00-reconciliation.json`
- `knowledgegraph/research/residual-unknowns/worker-10-editor-core.json`
- `knowledgegraph/research/residual-unknowns/worker-11-sim-core.json`
- `knowledgegraph/research/residual-unknowns/worker-12-sim-space.json`
- `knowledgegraph/research/residual-unknowns/worker-14-terrain-world.json`
- `knowledgegraph/research/residual-unknowns/worker-15-editor-support.json`
- `knowledgegraph/research/residual-unknowns/worker-16-sporepedia-online.json`
- `knowledgegraph/research/residual-unknowns/worker-18-ui-shell.json`
- `knowledgegraph/research/residual-unknowns/worker-20-gameglobal-misc.json`

Required interpretation inputs included `docs/analysis/semantic-atlas.md`, `docs/analysis/reconstruction-packages.md`, `docs/analysis/architecture-blockers.md`, `docs/analysis/architecture-resolution.md`, `docs/analysis/conflict-adjudication.md`, `docs/analysis/implementation-dependency-graph.md`, `docs/analysis/event-message-map.md`, `docs/analysis/gameplay-data-model.md`, `docs/analysis/type-archaeology.md`, `docs/analysis/decomp-gap-excavation.md`, `docs/analysis/reconstruction-readiness.md`, and `docs/analysis/simulator-root-closure.md`.

Evidence boundaries are strict:

- Canonical xrefs establish direct static endpoint relationships, not transitive or runtime reachability.
- SDK names, candidate vtables, package candidates, semantic families, and root proximity are bounded structural evidence, not unique ownership or behavior.
- There is no MSVC RTTI; candidate tables cannot establish a complete original class hierarchy.
- Targeted or committed static bodies are not persisted canonical decompilation and do not promote `semantic_understanding`.
- No runtime, differential, persistence, network, or original-process evidence was produced by this report.
- The quality status remains **COMPLETE_WITH_EVIDENCE_LIMITATIONS** for runtime and canonical static evidence limits, not broken provenance.
- Package membership inferred from cluster scope is not ownership proof. This is especially important for Terrain/RTT/render rows projected broadly into App, Resource, Editor, UI, and GameGlobal packages.
- The historical `docs/analysis/gameplay-state-machines.json` citation defect is resolved to `knowledgegraph/research/gameplay-state-machines.json` across 226 records and 452 occurrences. There are 0 current broken references and zero semantic change; worker-10 records remain unchanged.

## 3. Ranking formula, weights, normalization, and interpretation

`static-information-gain-v1` is an ordering function only. Worker decisions and defer reasons are preserved; the score never rewrites them.

For each count feature, `N(x) = log1p(max(0,x)) / log1p(max_observed_x)`. Boolean boundary/blocker features are already in `[0,1]`. Ranking uses unrounded score descending, then VA ascending.

| Feature | Weight | Observed maximum | Extraction boundary |
|---|---:|---:|---|
| Direct constrained endpoints | 0.25 | 1,097 | `direct_callers + direct_callees`; static endpoints only |
| Package count | 0.10 | 6 | constrained/package-candidate breadth, not ownership |
| Unresolved type surfaces | 0.15 | 8 | one-surface estimate, not a class census |
| Direct state transitions | 0.12 | 7 | exact/direct state matches; related-only transitions excluded |
| Direct events | 0.12 | 5 | exact/direct event surfaces; family candidates excluded |
| Reconstruction boundary | 0.08 | boolean | explicit non-empty boundary |
| Architecture blocker | 0.08 | boolean | explicit open/blocked/conflict signal; explicit safe/none is zero |
| Decomp/caller evidence | 0.10 | 0..1 | `0.6*decomp evidence + 0.4*caller evidence`; decomp levels are persisted 1.0, targeted/committed body 0.75, non-empty gap evidence 0.5, otherwise 0; caller evidence is structured endpoints 1.0, aggregate xrefs 0.5, otherwise 0 |

`IG = 100 * (0.25*N(functions) + 0.10*N(packages) + 0.15*N(types) + 0.12*N(states) + 0.12*N(events) + 0.08*boundary + 0.08*blocker + 0.10*decomp/caller)`.

This is ordering, not confidence. A high score can be driven by generic infrastructure, fan-in/fan-out, package breadth, or unresolved-type breadth rather than gameplay specificity. Two important examples are:

- `00c2e4e0` scores 48.427 largely because of 198 direct constrained endpoints, yet its targeted body is a one-instruction default/forwarder and it is explicitly package-boundary-safe to defer.
- `00faad80` scores 47.450 because of broad terrain/graphics ownership and type-surface constraints, yet adjudication assigns the row to Terrain rendering, not Sporepedia, and it is explicitly safe from `PKG-16` under the current clean-room boundary.

Likewise, `007c3410` and `00f9d9b0` span five and six package projections, respectively. That breadth makes them useful owner separators, not proof of six gameplay dependencies.

## 4. Complete Top 25

| Rank | VA | Name | Score | Cluster | Family | Affected packages/surfaces | Next action | Blockers/caveat |
|---:|---|---|---:|---|---|---|---|---|
| 1 | `00b21340` | `FUN_00b21340` | 61.893 | sim-core-systems | lookup | `PKG-11`; noun/map spine | Recover one producer/consumer and one field/lifetime boundary from the targeted static observation | 12 blockers: no persisted body, outside reconstruction scope, root alias/lifetime and noun-map invalidation unresolved |
| 2 | `005bf9d0` | `FUN_005bf9d0` | 54.703 | ui-shell | editor name panel lifecycle/dispatch | `PKG-18`; UTFWin managed messages | Build the four-ID producer/registration matrix; type `0067caa0+0x44` and list interface | 5 blockers: interior SDK address, zero direct caller, payload/manager ownership unresolved |
| 3 | `005c0380` | `FUN_005c0380` | 54.656 | ui-shell | editor name panel lifecycle/dispatch | `PKG-18`; panel state | Decompile service/window slots and record `field_11`/random-name gates | 6 blockers: interior SDK label, service owners/slots and runtime transition unresolved |
| 4 | `01021300` | `FUN_01021300` | 52.719 | sim-core-systems | accessors | `PKG-11`; current-empire cache | Recover producer/consumer and field/lifetime boundary; retain lower-bound/successor caveat | 11 blockers including root alias/lifetime; cache mechanics are not full ownership proof |
| 5 | `005dda30` | `FUN_005dda30` | 52.322 | sporepedia-online | scenario_gameplay_events | `PKG-16`; editor/mode/event family | Trace one branch through caller, message construction, listener, mutation, and release | Explicit `safe_to_defer=false`; 4 blockers including no persisted body and no runtime validation |
| 6 | `005c0100` | `FUN_005c0100` | 50.050 | ui-shell | editor name panel lifecycle/dispatch | `PKG-18`; UTFWin UI messages | Map IDs `1`, `9`, `0x18`, `0x287259f6`; type `0067caa0+0x4c` and `005ecf80` | 5 blockers: interior SDK alias, payload variants/order and manager types unresolved |
| 7 | `00b3d2a0` | `FUN_00b3d2a0` | 49.978 | sim-core-systems | accessors | `PKG-11`; star-manager alternate slot | Recover producer/consumer and lifecycle boundary; do not merge with canonical manager slot | 13 blockers; alternate/canonical publication and teardown equality unresolved |
| 8 | `00b3d300` | `FUN_00b3d300` | 49.794 | sim-core-systems | accessors | `PKG-01`/`PKG-11`; noun-manager alternate slot | Recover producer/consumer and field/lifetime boundary; compare canonical `00b3d400` | 13 blockers; no direct writer/equality/teardown proof; high fan-in is not singleton proof |
| 9 | `00834fa0` | `FUN_00834fa0` | 49.563 | ui-shell | text_zoom_presentation | `PKG-18`; UI presentation | Type seven arguments, resolve `00989000`, fields `+0x48..+0x74`, and service `0x626e3b8+0x7c` | 5 blockers: ABI conflict, untyped later fields, factory/service ownership absent |
| 10 | `00fb6850` | `FUN_00fb6850` | 49.084 | terrain-world | engine boundary | `PKG-04`, `PKG-09`, `PKG-14`, `PKG-21`; terrain/render | Use targeted body only to separate named owner/type and first resource writer/consumer | 9 blockers; 4-package breadth, anonymous identity, no Terrain oracle or runtime trace |
| 11 | `0106e3e0` | `FUN_0106e3e0` | 49.070 | ui-shell | Space UI lifecycle/palette | `PKG-18`; Space UI state | Type six caller arguments, decompile `0106aa10`, and map panel/service callbacks | 5 blockers: interior SDK label, caller/panel contracts and runtime transition unresolved |
| 12 | `007c3410` | `FUN_007c3410` | 48.688 | terrain-world | engine boundary | `PKG-02`, `PKG-03`, `PKG-14`, `PKG-21`, `PKG-22` | Targeted decompile plus one caller/callee separator; do not promote from topology | 8 blockers; five-package breadth, no type/runtime evidence |
| 13 | `00f9d9b0` | `FUN_00f9d9b0` | 48.542 | terrain-world | engine boundary | `PKG-02`, `PKG-04`, `PKG-09`, `PKG-14`, `PKG-21`, `PKG-22` | Resolve terrain owner/type conflict and first writer/consumer/resource lifecycle boundary | 9 blockers; six-package breadth is an owner-separation signal, not six semantics |
| 14 | `00c2e4e0` | `FUN_00c2e4e0` | 48.427 | sporepedia-online | generic virtual default/forwarder | `PKG-16`; shared virtual infrastructure | Represent a documented default at its proven consumer; do not spend more decompilation unless non-default behavior appears | **Explicit safe defer**; generic candidate-vtable default has no exclusive domain contract |
| 15 | `00fb6e00` | `FUN_00fb6e00` | 48.390 | terrain-world | engine boundary | `PKG-04`, `PKG-09`, `PKG-14`, `PKG-21`; render resource path | Use targeted body to resolve owner/type and first resource writer/consumer | 9 blockers; anonymous identity, no Terrain oracle/runtime, package breadth caveat |
| 16 | `005cb5a0` | `FUN_005cb5a0` | 48.198 | editor-support | palette-ui-selection | `PKG-15`; palette/editor UI | Type receiver and one adjacent caller/callee; preserve the support boundary | 8 blockers; payload/order and selected-paint identity unresolved |
| 17 | `007c4bc0` | `FUN_007c4bc0` | 47.751 | terrain-world | engine boundary | `PKG-02`, `PKG-14`, `PKG-18`, `PKG-21` | Targeted decompile plus one caller/callee separator | 8 blockers; no type, vtable, runtime, or original surface trace |
| 18 | `00b534c0` | `FUN_00b534c0` | 47.751 | terrain-world | engine boundary | `PKG-11`, `PKG-14`, `PKG-18`, `PKG-21` | First acquire a concrete SDK/vtable/type or independent path witness | 8 blockers; worker decision is defer despite four-package breadth |
| 19 | `00f9c0d0` | `FUN_00f9c0d0` | 47.604 | terrain-world | engine boundary | `PKG-02`, `PKG-04`, `PKG-09`, `PKG-14`, `PKG-21`, `PKG-22` | Resolve owner/type and first writer/consumer or resource lifecycle boundary | 6 blockers; no vtable, runtime, or implementation oracle; breadth caveat |
| 20 | `007c4010` | `FUN_007c4010` | 47.563 | terrain-world | engine boundary | `PKG-02`, `PKG-11`, `PKG-14`, `PKG-15`, `PKG-21` | Acquire concrete owner/type/call-path witness before targeted decompilation | 9 blockers; worker decision is defer |
| 21 | `00faad80` | `FUN_00faad80` | 47.450 | sporepedia-online | Terrain graphics owner misattribution | `PKG-16` projection; adjudicated to Terrain | Move research ownership to `cTerrainSphere`; recover raw interface only if compatibility is required | **Explicit safe defer from PKG-16**; 7 blockers remain globally, and Sporepedia ownership is rejected |
| 22 | `00fa5610` | `FUN_00fa5610` | 47.388 | terrain-world | engine boundary | Six packages including `PKG-14`, `PKG-16`, `PKG-20`, `PKG-21` | Resolve owner/type and first writer/consumer or resource lifecycle boundary | 6 blockers; broad cross-package projection is not semantic breadth |
| 23 | `00fb43b0` | `FUN_00fb43b0` | 47.244 | terrain-world | engine boundary | `PKG-14`, `PKG-21`, `PKG-22`; render/runtime support | Use targeted body to separate owner/type and resource lifecycle | 9 blockers; no Terrain/runtime oracle and type breadth is unresolved |
| 24 | `007c4d00` | `FUN_007c4d00` | 47.069 | terrain-world | engine boundary | `PKG-02`, `PKG-14`, `PKG-18`, `PKG-21` | Acquire concrete SDK/vtable/type or independent path witness first | 8 blockers; worker decision is defer |
| 25 | `0092cb00` | `FUN_0092cb00` | 47.017 | terrain-world | engine boundary | `PKG-02`, `PKG-14`, `PKG-21` | Acquire concrete SDK/vtable/type or independent path witness first | 9 blockers; worker decision is defer |

## 5. Complete validated Top 100 projection

This table is a row-for-row rendering of the validated `top_100` projection. “Unmarked” means `safe_to_defer` is null; it does not mean globally safe. “Explicit investigate” is `safe_to_defer=false`.

| Rank | VA | Score | Cluster | Semantic family | Decision/action class | Explicit defer or investigation |
|---:|---|---:|---|---|---|---|
| 1 | `00b21340` | 61.893 | sim-core-systems | lookup | Investigate / root-owner and noun-map separator | Unmarked investigate |
| 2 | `005bf9d0` | 54.703 | ui-shell | editor_name_panel_lifecycle_and_dispatch | Investigate / message producer and payload trace | Unmarked investigate |
| 3 | `005c0380` | 54.656 | ui-shell | editor_name_panel_lifecycle_and_dispatch | Investigate / service-slot and state trace | Unmarked investigate |
| 4 | `01021300` | 52.719 | sim-core-systems | accessors | Investigate / cache and root lifetime separator | Unmarked investigate |
| 5 | `005dda30` | 52.322 | sporepedia-online | scenario_gameplay_events | Investigate / event and mode-family trace | **Explicit investigate** |
| 6 | `005c0100` | 50.050 | ui-shell | editor_name_panel_lifecycle_and_dispatch | Investigate / UTFWin message trace | Unmarked investigate |
| 7 | `00b3d2a0` | 49.978 | sim-core-systems | accessors | Investigate / alternate star-root separator | Unmarked investigate |
| 8 | `00b3d300` | 49.794 | sim-core-systems | accessors | Investigate / alternate noun-root separator | Unmarked investigate |
| 9 | `00834fa0` | 49.563 | ui-shell | text_zoom_presentation | Investigate / type ABI and service owner | Unmarked investigate |
| 10 | `00fb6850` | 49.084 | terrain-world | engine_boundaries | Investigate / terrain owner and resource separator | Unmarked investigate |
| 11 | `0106e3e0` | 49.070 | ui-shell | space_game_ui_lifecycle_and_palette | Investigate / palette and panel state trace | Unmarked investigate |
| 12 | `007c3410` | 48.688 | terrain-world | engine_boundaries | Investigate / cross-package owner separator | Unmarked investigate |
| 13 | `00f9d9b0` | 48.542 | terrain-world | engine_boundaries | Investigate / broad owner/type separator | Unmarked investigate |
| 14 | `00c2e4e0` | 48.427 | sporepedia-online | generic_virtual_defaults_and_forwarders | Defer / semantic default at consumer | **Explicit safe defer** |
| 15 | `00fb6e00` | 48.390 | terrain-world | engine_boundaries | Investigate / render-resource owner separator | Unmarked investigate |
| 16 | `005cb5a0` | 48.198 | editor-support | palette-ui-selection | Investigate / receiver and message type | Unmarked investigate |
| 17 | `007c4bc0` | 47.751 | terrain-world | engine_boundaries | Investigate / targeted owner separator | Unmarked investigate |
| 18 | `00b534c0` | 47.751 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 19 | `00f9c0d0` | 47.604 | terrain-world | engine_boundaries | Investigate / owner and resource separator | Unmarked investigate |
| 20 | `007c4010` | 47.563 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 21 | `00faad80` | 47.450 | sporepedia-online | terrain_graphics_owner_misattribution | Defer / move to Terrain owner | **Explicit safe defer** |
| 22 | `00fa5610` | 47.388 | terrain-world | engine_boundaries | Investigate / cross-package owner separator | Unmarked investigate |
| 23 | `00fb43b0` | 47.244 | terrain-world | engine_boundaries | Investigate / resource lifecycle separator | Unmarked investigate |
| 24 | `007c4d00` | 47.069 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 25 | `0092cb00` | 47.017 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 26 | `005cb240` | 46.703 | editor-support | palette-ui-selection | Investigate / receiver, category, message type | Unmarked investigate |
| 27 | `00b5b800` | 46.703 | sim-core-systems | lookup | Investigate / opaque state first-writer trace | Unmarked investigate |
| 28 | `007c40f0` | 46.476 | terrain-world | engine_boundaries | Investigate / owner and lifecycle trace | Unmarked investigate |
| 29 | `007c3af0` | 46.365 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 30 | `00fa2a20` | 46.360 | terrain-world | engine_boundaries | Investigate / targeted owner separator | Unmarked investigate |
| 31 | `005bfd40` | 46.088 | ui-shell | editor_name_panel_lifecycle_and_dispatch | Investigate / lifecycle and service type trace | Unmarked investigate |
| 32 | `00603650` | 45.998 | ui-shell | configuration_property_materialization | Conditional / owner and pair type before semantics | **Conditional** |
| 33 | `0064a400` | 45.783 | sporepedia-online | misattributed_app_lifecycle | Defer / move to App/plugin owner | **Explicit safe defer** |
| 34 | `007c46f0` | 45.710 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 35 | `0102d1b0` | 45.603 | sporepedia-online | scenario_gameplay_events | Investigate / scenario and communication trace | **Explicit investigate** |
| 36 | `00adad70` | 45.479 | terrain-world | engine_boundaries | Investigate / owner and type separator | Unmarked investigate |
| 37 | `00dd0e10` | 45.462 | sporepedia-online | scenario_gameplay_events | Investigate / mode and event trace | **Explicit investigate** |
| 38 | `007c4a60` | 45.428 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 39 | `01073700` | 45.423 | ui-shell | space_game_ui_lifecycle_and_palette | Investigate / Load split, jump table, registrations | Unmarked investigate |
| 40 | `00b13b50` | 45.338 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 41 | `00f9e120` | 45.338 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 42 | `00b1fdb0` | 45.208 | sim-core-systems | accessors | Investigate / receiver-typed avatar separator | Unmarked investigate |
| 43 | `007c3990` | 45.118 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 44 | `007c3ba0` | 44.986 | terrain-world | lifecycle | Investigate / lifecycle owner and type | Unmarked investigate |
| 45 | `00b28ec0` | 44.914 | editor-core | state_mutators | Investigate / save transaction candidate | Unmarked investigate |
| 46 | `00fa5cc0` | 44.882 | terrain-world | engine_boundaries | Investigate / owner and type separator | Unmarked investigate |
| 47 | `007c4b50` | 44.777 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 48 | `01021260` | 44.691 | sim-core-systems | accessors | Investigate / active-planet and lifecycle trace | Unmarked investigate |
| 49 | `007c3c50` | 44.567 | terrain-world | state_mutators | Investigate / state writer and owner | Unmarked investigate |
| 50 | `00f678a0` | 44.166 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 51 | `00fa0400` | 44.166 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 52 | `007c3c10` | 44.166 | terrain-world | wrappers | Investigate / wrapper mechanics and consumer | Unmarked investigate |
| 53 | `007c3f70` | 44.146 | terrain-world | lifecycle | Investigate / lifecycle owner and type | Unmarked investigate |
| 54 | `00f9fef0` | 43.924 | sporepedia-online | terrain_graphics_owner_misattribution | Defer / move to Terrain owner | **Explicit safe defer** |
| 55 | `007c3cb0` | 43.404 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 56 | `007c4000` | 43.333 | terrain-world | lifecycle | Investigate / lifecycle owner and type | Unmarked investigate |
| 57 | `00962950` | 43.273 | ui-shell | ui_window_construction | Conditional / allocation and layout type first | **Conditional** |
| 58 | `007b77a0` | 43.269 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 59 | `01021080` | 43.257 | sim-core-systems | accessors | Investigate / SpaceContext and lifecycle trace | Unmarked investigate |
| 60 | `007c4b00` | 43.254 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 61 | `00f9bc40` | 43.183 | terrain-world | engine_boundaries | Investigate / targeted owner separator | Unmarked investigate |
| 62 | `005e0000` | 43.115 | editor-core | event_dispatchers | Investigate / command dispatcher and payload trace | Unmarked investigate |
| 63 | `00e31100` | 42.872 | sporepedia-online | generic_virtual_defaults_and_forwarders | Defer / semantic default at consumer | **Explicit safe defer** |
| 64 | `007c4ad0` | 42.834 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 65 | `00b16dc0` | 42.834 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 66 | `007c3c20` | 42.808 | terrain-world | lifecycle | Investigate / lifecycle owner and type | Unmarked investigate |
| 67 | `004badd0` | 42.801 | editor-support | editor-mode-bridge | Investigate / parameter and mode-owner type | Unmarked investigate |
| 68 | `00faed90` | 42.718 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 69 | `005c1ce0` | 42.694 | editor-support | palette-page-category-ui | Investigate / palette lookup and support boundary | Unmarked investigate |
| 70 | `007c3cc0` | 42.688 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 71 | `00ba9370` | 42.530 | sim-core-systems | lookup | Investigate / lower-bound empire lookup and cache trace | Unmarked investigate |
| 72 | `00f99980` | 42.476 | sporepedia-online | terrain_graphics_owner_misattribution | Defer / move to Terrain owner | **Explicit safe defer** |
| 73 | `00e7a7c0` | 42.432 | sim-core-systems | state_mutators | Investigate / death and damage path trace | Unmarked investigate |
| 74 | `00f9bee0` | 42.424 | sporepedia-online | terrain_graphics_owner_misattribution | Defer / move to Terrain owner | **Explicit safe defer** |
| 75 | `00fa5040` | 42.424 | sporepedia-online | terrain_graphics_owner_misattribution | Defer / move to Terrain owner | **Explicit safe defer** |
| 76 | `007b9620` | 42.357 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 77 | `007c4d20` | 42.357 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 78 | `00688830` | 42.218 | editor-support | shared-viewer-render-support | Investigate / map owner and release contract | Unmarked investigate |
| 79 | `007b3760` | 42.067 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 80 | `00de9fc0` | 41.909 | sim-space | wrappers | Investigate / ordered-map and Space UI type trace | Unmarked investigate |
| 81 | `00fb66d0` | 41.894 | terrain-world | engine_boundaries | Investigate / owner and resource separator | Unmarked investigate |
| 82 | `007c43e0` | 41.806 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 83 | `007c40c0` | 41.790 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 84 | `00fb1780` | 41.776 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 85 | `00fb6630` | 41.776 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 86 | `00e7fd00` | 41.688 | sim-core-systems | state_mutators | Investigate / lifecycle and state-owner trace | Unmarked investigate |
| 87 | `00f347e0` | 41.615 | sporepedia-online | game_mode_and_scenario_projection | Defer / move to mode/input owner | **Explicit safe defer** |
| 88 | `00c877f0` | 41.372 | sim-space | state_mutators | Investigate / item type and lifecycle trace | Unmarked investigate |
| 89 | `00fc27e0` | 41.355 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 90 | `00fb6cd0` | 41.297 | terrain-world | engine_boundaries | Investigate / owner and type separator | Unmarked investigate |
| 91 | `007c3c90` | 41.270 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 92 | `0077f210` | 41.155 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 93 | `00e780a0` | 41.060 | sim-core-systems | engine_boundaries | Defer / concrete owner or type witness first | Unmarked defer |
| 94 | `00f967d0` | 40.976 | sporepedia-online | terrain_graphics_owner_misattribution | Defer / move to Terrain owner | **Explicit safe defer** |
| 95 | `00fa73c0` | 40.976 | sporepedia-online | terrain_graphics_owner_misattribution | Defer / move to Terrain owner | **Explicit safe defer** |
| 96 | `0080d710` | 40.964 | editor-support | shared-viewer-render-support | Defer / owner or type witness first | Unmarked defer |
| 97 | `00aeb720` | 40.950 | sim-space | event_dispatchers | Investigate / communication entry and lifecycle trace | Unmarked investigate |
| 98 | `00fb5090` | 40.879 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 99 | `00fb77b0` | 40.879 | terrain-world | engine_boundaries | Defer / owner or type witness first | Unmarked defer |
| 100 | `005c53c0` | 40.858 | editor-support | palette-page-category-ui | Investigate / category receiver and resource type | Unmarked investigate |

## 6. Semantic clusters worth researching together

The following 11 buckets are a deterministic, non-overlapping planning normalization of all 1,976 rows. B1–B3 partition `sim-core-systems` by normalized semantic family; B4–B11 partition the remaining clusters, with Sporepedia split by the explicit safety flag. `I` means `INVESTIGATE_NOW`; `D` means plain `DEFER`; `C` means one of the three conditional UI-shell decisions.

| Bucket and selection | Rows | Decision split | Package concentration | Dependencies/blockers | Cheapest action | Conservative / optimistic reduction |
|---|---:|---|---|---|---|---:|
| B1 Simulator roots, managers, accessors, lookup: families `managers`, `accessors`, `lookup` | 255 | 82 I / 173 D | `PKG-11` 255; conceptually gates `PKG-01` | root publication/equality/teardown, return type, map owner, successor behavior | Trace the 11-root U1 spine plus one owner and two consumers each | 35 / 230 |
| B2 Anonymous Simulator long-tail: family `other` | 852 | 172 I / 680 D | `PKG-11` 852 | identity, no RTTI, weak type/event anchors; blanket decompilation is low value | Require one concrete type, vtable, root, or named caller before selecting rows | 5 / 55 |
| B3 Simulator behavior/state/dispatch: remaining `sim-core-systems` families | 362 | 116 I / 246 D | `PKG-11` 362 | manager roots, payload/order, AI/tool ownership, state axes | Start with exact event/state/dispatch rows, then one producer/consumer pair | 20 / 80 |
| B4 Editor core: `cluster=editor-core` | 226 | 63 I / 163 D | `PKG-10` 226 | App mode/messages, command payload, history and save boundary | U3 command/mode/history spine before serializer inventory | 20 / 85 |
| B5 Editor support: `cluster=editor-support` | 66 | 53 I / 13 D | `PKG-15` 66; `PKG-10` 1 | typed receiver/owner, palette/viewer/Skinner resources, C-ORDER | Type palette category/page/UI receiver and one resource lifecycle path | 18 / 65 |
| B6 Terrain lifecycle/render boundary: `cluster=terrain-world` | 96 | 40 I / 56 D | `PKG-14` 96; `PKG-21` 83; broad projections into 02/03/04/09/16/18/20/22 | no surface trace, RTT/render ownership, 40-slot candidate versus SDK 74/75 conflict | U7 seed set, then owner/vtable plus one resource writer/consumer | 12 / 30 |
| B7 Sporepedia local metadata: `cluster=sporepedia-online AND safe_to_defer=false` | 33 | 33 explicit I / 0 D | `PKG-16` 33 | local fixture, caller/event characterization, no-network contract | Close field/lifecycle/property/factory contracts before scenario rows | 20 / 50 |
| B8 Sporepedia package-boundary deferrals: `cluster=sporepedia-online AND safe_to_defer=true` | 36 | 0 I / 36 explicit safe D | `PKG-16` projection only | no-network stubs, generic defaults/collections, App/Terrain owner separation | Preserve the package boundary; reopen only on the triggers in section 8 | 0 / 0 |
| B9 UI shell: `cluster=ui-shell` | 10 | 7 I / 0 plain D / 3 C | `PKG-18` 10 | interior SDK aliases, service types, manager/list ownership, runtime order | Producer/registration matrix for `005bf9d0`, `005c0100`, `005c0380` | 8 / 25 |
| B10 Sim Space: `cluster=sim-space` | 5 | 3 I / 2 D | `PKG-12` 5; related `PKG-11`, `PKG-13` | all stage transitions, shared container typing, communication identity, item vtable | Resolve the three I rows individually; keep two shared/type rows deferred | 10 / 20 |
| B11 GameGlobal: `cluster=gameglobal-misc` | 35 | 16 I / 19 D | `PKG-20` 35 | map key/value/owner, mode/resource/editor boundaries, many rows misprojected by cluster | Characterize `00e5c780` and one hit/miss plus mutation caller | 1 / 14 |
| **Total** | **1,976** | **585 I / 1,388 D / 3 C** | exact residual partition | — | — | **149 / 654** |

The decision total is 585 `INVESTIGATE_NOW` + 1,388 `DEFER` + 3 conditional = 1,976. The three conditional decisions consist of two defer-until rows and one investigate-type-before-semantics row; they are not silently collapsed into plain defer or investigation.

## 7. Smallest package and architecture unlock sets

These are research unlocks, not implementation waves. “Exact” means the set can be selected without semantic guessing. Anchors marked external are static reference VAs outside the 1,976 residual predicate but are needed to interpret the in-scope rows.

| Unlock | Exact VAs or selection rule | Package effect | Prerequisites | Conservative / optimistic reduction |
|---|---|---|---|---:|
| U1 Shared root/map spine | Exact 11: `00b1fdb0`, `00b21340`, `00b25fb0`, `00b3d2a0`, `00b3d300`, `00b5b800`, `00ba9370`, `00e5c780`, `01021080`, `01021260`, `01021300` | Freezes `PKG-01` interfaces and removes the largest static prerequisite from `PKG-06`–`PKG-13` and `PKG-20` characterization | Publisher/equality/teardown matrix; allocation-to-slot-to-field evidence; map key/value/successor contract; four root slots remain separate | 60 / 365 |
| U2 Persistence descriptor/editor transaction | Residual seeds `00b28ec0`, `00577650`, `00574080`; external anchors `00b279e0`, `00692900`, `00693e10`, `006a2f60`, `006a1540` | Separates profile persistence from editor asset save and property configuration across `PKG-02`, `PKG-03`, `PKG-11`, `PKG-12`, `PKG-15` | Resolve Property carrier/parent branch, descriptor key domain, manager binding, close/failure order; no original wire claim | 5 / 20 |
| U3 Editor command/mode/history | Selection: `cluster=editor-core` rows with direct state/event relevance or a direct edge to `005dda30`, `005e0000`, `00587270`, `00591fa0`, `00586410`; exact residual seeds `005dda30`, `005e0000`, `005744b0`; external anchors `00587270`, `00591fa0`, `00586410` | Establishes `PKG-10` command, mode, and transient-history boundaries used by `PKG-11`, `PKG-12`, and `PKG-15` | App mode/message producer matrix, editor constructor/receiver type, command payloads, history lifetime separate from persistence | 15 / 65 |
| U4 Palette/viewer/Skinner support | Exact selection: all 66 `cluster=editor-support` rows | Unlocks `PKG-15` support contracts without assigning presentation to gameplay authority | Typed receivers/fields, one viewer lifecycle, one palette resource path, one Skinner paint-job owner; `PKG-10` and `PKG-03/04` boundaries | 18 / 65 |
| U5 UI shell | Exact selection: all 10 `cluster=ui-shell` rows | Closes the smallest `PKG-18` message, palette, property-materialization, and text-zoom contracts | `005bf9d0/005c0100/005c0380` producer matrix; service manager types; conditional type-first rows remain gated | 8 / 25 |
| U6 Sporepedia local metadata | Exact selection: 33 `cluster=sporepedia-online` rows with `safe_to_defer=false` | Establishes a local `PKG-16` metadata/lifecycle/property/factory boundary; online remains stubbed | Local fixture, no-network contract, caller/event trace, receiver types; scenario event family stays separate | 20 / 50 |
| U7 Terrain lifecycle/RTT/render | Twelve exact seeds: `00fb6850`, `007c3410`, `00f9d9b0`, `00fb6e00`, `00f9c0d0`, `007c4010`, `007c3ba0`, `007c3c50`, `007c3c10`, `007c3f70`, `00fc2830`, `00fb43b0`; expansion rule: residual records with information_gain_score >=35 within `cluster=terrain-world` gives 84 rows | Separates `PKG-14` from Resource, Cell presentation, Editor/UI, GameGlobal, CRT, and unknown routing | One constructor/vtable, one RTT/resource writer, one render/consumer path; no surface trace or raw ABI claim | 12 / 30 |
| U8 Sim Space | Exact five: `00606880`, `00aeb720`, `00c877f0`, `00de58c0`, `00de9fc0` | Closes the small `PKG-12` interface set and related `PKG-11`/`PKG-13`/`PKG-14` seams | U1 roots, stage trace, container element/ownership type, communication entry identity, inventory vtable; keep `00606880`/`00de58c0` deferred unless type witness exists | 10 / 20 |
| U9 Relationship/diplomacy | Exact residual transition bodies `00d065a0`, `00d06920`, `00d01e30`; external root anchor `00b3d3c0` | Separates alliance/diplomacy semantics from App messages and other event families in `PKG-11`, `PKG-12`, `PKG-13`, `PKG-18` | Political-ID/key layout, before/after relationship delta, listener and UI consumers, no universal event ABI | 1 / 14 |
| **Total** | — | architecture prerequisites only | — | **149 / 654** |

## 8. Functions safe to defer

Exactly 36 normalized records have `safe_to_defer=true`. All 36 remain `semantic_understanding=not_established`; none is globally solved or deleted. Safety is package-boundary-safe, not a general correctness finding.

| Group | Exact VAs | Reopen trigger |
|---|---|---|
| Pollinator/no-network progression, 8 | `006751c0`, `00615db0`, `00676660`, `006766f0`, `00676a20`, `00676e40`, `00676f20`, `00676f60` | A local, explicit no-network progression contract requires key encoding, comparator, counter mutation, and manager lifetime |
| Generic collection, 2 | `00553f10`, `006066f0` | A concrete domain owner plus mutation/iteration caller establishes a non-replaceable contract |
| Generic virtual defaults/forwarders, 5 | `00b1e4d0`, `00b7e380`, `00c2e4e0`, `00e31100`, `006e64f0` | A proven consumer shows non-default behavior or an exclusive gameplay contract |
| Terrain graphics owner misattribution, 14 | `00f96840`, `00f99980`, `00f999e0`, `00f967d0`, `00f9bee0`, `00f9f770`, `00f9fef0`, `00fa0d50`, `00fa5040`, `00fa5580`, `00fa6ec0`, `00fa73c0`, `00faad80`, `0104c110` | Raw Terrain ABI/compatibility, installed-subobject ownership, or a package dependency outside Terrain becomes necessary |
| Mode/input/scenario owner, 6 | `00552080`, `006419f0`, `00670610`, `006707a0`, `00f135b0`, `00f347e0` | A direct local Sporepedia dependency or the owning mode/input/scenario contract is established |
| Misattributed App/plugin lifecycle, 1 | `0064a400` | The rejected `ShopperRequest::Show` ownership must be revisited for App/plugin/lighting work; do not reattach it to `PKG-16` |
| **Total** | **36 VAs** | package-boundary deferral only |

`00c2e4e0`, `00faad80`, `00e31100`, and `0064a400` illustrate the caveat: a high score can indicate broad generic reach or package/type breadth while the worker has already identified a safe package boundary. None of their canonical semantic status changes.

## 9. Functions requiring investigation before implementation

The governing selection rule is exact: every residual whose `safe_to_defer != true` is `INVESTIGATE_NOW` before implementation. This is **1,940 functions**: 33 explicit false rows, three conditional rows, and 1,904 other non-explicitly-safe residuals. A worker `DEFER` remains in this set; deferral is scheduling/safety prioritization, not deletion or resolution.

The 33 explicit `safe_to_defer=false` rows are:

| Family | Exact VAs | Required action class |
|---|---|---|
| Local asset field projection, 5 | `005507a0`, `005508c0`, `005c0dd0`, `00a649a0`, `00ff3f00` | Bind one receiver field to a fixture-backed local metadata contract |
| Local asset lifecycle, 10 | `006413d0`, `00641cd0`, `00641e10`, `00641e40`, `00642190`, `00642210`, `00dd0bc0`, `00ec3bc0`, `00ec4280`, `00ecc620` | Pair constructor, initialize/dispose/delete, one caller, and one retained object |
| Asset predicates/properties, 13 | `00641410`, `00641490`, `00641780`, `006417d0`, `00641fa0`, `00641fd0`, `00642230`, `00642530`, `00642700`, `00dd0550`, `00dd06a0`, `00dd07f0`, `00ec3be0` | Enumerate accepted key/value/result states against deterministic local fixtures |
| Asset factory/filter, 2 | `006442e0`, `00661740` | Trace one created record and one filter through ownership/release; prove whether network is touched |
| Scenario gameplay events, 3 | `005dda30`, `00dd0e10`, `0102d1b0` | Trace producer, family-specific payload, listener, mutation, and release order |

The three conditional rows are exact:

| VA | Decision | Gate |
|---|---|---|
| `005bf950` | `DEFER_UNTIL_SERVICE_TYPED` | Identify service owners for `0xd0e6d04b` and `0xc7ceb1bd`, then type service slot `+0x80` and text ownership |
| `00603650` | `INVESTIGATE_TYPE_BEFORE_SEMANTICS` | Recover the containing callsite, `+0x40/+0x44` owner and pair type, property key/type, and reconcile `gameModeID` |
| `00962950` | `DEFER_UNTIL_TYPE_OR_ALLOCATION_WITNESS` | Trace allocation through `00962be0` and distinguish `UI::Window` from `UTFWin::Window` |

High-value examples beyond the explicit false subset are `00b21340`, `00b3d300`, `00b3d2a0`, `01021300`, `00b5b800`, `005bf9d0`, `005c0380`, `005c0100`, `00fb6850`, `00de9fc0`, `00c877f0`, and `00aeb720`. Their value lies in owner, field, lifecycle, payload, or package-boundary separation—not in decompilation volume.

## 10. Functions whose resolution could unlock packages

No single function establishes an entire package’s semantics. The following sets can nevertheless remove a package-wide prerequisite or owner ambiguity:

| Unlock surface | Highest-leverage functions/rule | Package-level effect | Remaining limitation |
|---|---|---|---|
| Root and map spine | U1’s 11 exact VAs, led by `00b21340`, `00b3d300`, `00b3d2a0`, `01021300`, and `00e5c780` | Enables typed characterization across Simulator, Cell, Editor, Space, and GameGlobal | Root publication, equality, teardown, and owner authority remain open |
| Persistence graph | `00b28ec0`, `00577650`, `00574080` plus U2 anchors | Separates property/configuration, profile persistence, and editor asset save | Original envelope, references, migration, field survival, and atomicity remain open |
| Editor command/mode/history | `005dda30`, `005e0000`, `005744b0` plus U3 anchors | Provides the dispatch and transient-history contract consumed by editor support and Simulator | Runtime message timing and menu-to-stage causality remain absent |
| Palette/viewer/Skinner | All 66 `cluster=editor-support` rows | Makes PKG-15 separable from editor command authority and renderer/gameplay semantics | Resource and service ownership still require type evidence |
| UI shell | All 10 `cluster=ui-shell` rows; especially `005bf9d0`, `005c0380`, `005c0100`, `01073700` | Delivers the smallest coherent UTFWin/message/presentation boundary | Service types, producer payloads, and runtime order remain unresolved |
| Local Sporepedia metadata | The 33 false rows, especially `00661740`, `00ff3f00`, and the lifecycle/property families | Enables a local metadata adapter without online implementation | Network remains blocked; scenario rows need family-specific traces |
| Terrain/RTT/render | U7 seed set, especially `00fb6850`, `00f9d9b0`, `007c3410`, `007c3ba0`, `007c3c50` | Prevents generic infrastructure and render code from being promoted as gameplay state | No original surface trace, pixel oracle, or complete vtable ownership |
| Space | All five U8 VAs | Closes the small package interface and exposes container, communication, inventory, and UI seams | Stage lifecycle and runtime order remain unobserved |
| Relationship/diplomacy | `00d065a0`, `00d06920`, `00d01e30` plus `00b3d3c0` | Separates political transition semantics from the App event transport | Payload, listener set, and runtime order remain open |

## 11. Decompilation and research strategy

| Strategy | Use when | Required output | Examples |
|---|---|---|---|
| Targeted decompilation | A bounded body, field write, or branch is the shortest discriminator | Persist or explicitly record body/contract provenance; separate targeted static observation from canonical decompilation | `00b21340`, `005e0000`, `00aeb720`, `00c877f0`, U7 seed set |
| Caller/callee separator | Identity depends on receiver propagation, a successor, mutation, or owner use | One caller and one callee with direction, return use, field/lifetime evidence | `00b21340` with `00e5c780`/`00ba8420`; `00b3d300` consumer; `00aeb720` with creator/dispatcher |
| Type and vtable recovery | An SDK/candidate table, object layout, property key, or service slot blocks meaning | Constructor, vtable bytes/slots, field offsets, and two independent consumers; retain alternatives | `00c877f0` and `0x01473558`; `00603650`; `00962950`; UI service slots |
| State/data analysis | The question is payload order, state transition, persistence, or data ownership | Exact producer/consumer and field sequence; no inferred universal ABI | `005dda30`, `00aeb720`, `00b28ec0`, `00d06920` |
| Runtime experiment | Static scans cannot separate publication, timing, field survival, or renderer behavior | Approved, pinned trace with synchronized state snapshots and explicit negative controls | Root equality/teardown, mode transition, save/load round trip, Space and Terrain stage traces |

Explicit no-decomp or no-defer-decomp examples under the current boundary:

- `00c2e4e0`: no more blanket decompilation; represent an exact default/forwarder at its proven consumer unless non-default behavior appears.
- `00faad80`: no Sporepedia decompilation effort; move ownership to Terrain and reopen only for raw ABI compatibility.
- `00e31100`: no more blanket decompilation unless an exclusive domain contract appears.
- `0064a400`: do not decompile as `ShopperRequest`; preserve the App/plugin/lighting owner conclusion.
- The 36 safe rows remain package-boundary deferrals; they are not globally solved.

Runtime experiments are future evidence gates only. None was run for this report, and none authorizes implementation without a separate approval and quality gate.

## 12. Blockers

1. **No runtime evidence:** runtime-verified function count is zero; no Cell, Editor, Space, Terrain, save/load, relationship, or event-order trace is available.
2. **No persisted canonical body in this residual:** all 1,976 rows lack persisted canonical decompilation, even though 176 rows reuse targeted/committed static observations.
3. **Identity/type gaps:** 1,617 rows normalize to an unresolved type/identity class; 1,715 exact blocker occurrences say no vtable association and 1,536 say SDK identity absent.
4. **State/event gaps:** 142 rows carry a state/event contract blocker. Family candidates and equal-sized records are not payload equivalence.
5. **Architecture boundaries:** 159 rows carry architecture/boundary blockers. Root publication, forwarded state, persistence references, mode axes, resource/cache order, and conditional vtables remain bounded.
6. **Package breadth is not semantics:** Terrain and generic infrastructure rows often project into four to six packages. These projections are routing hints and can be misattributions.
7. **No RTTI:** candidate vtables and SDK names cannot uniquely settle class ownership or raw ABI.
8. **Static ordering limits:** direct xrefs do not establish transitive reachability, queue timing, object lifetime, or event delivery.
9. **Resolved source citation provenance:** the historical `docs/analysis/gameplay-state-machines.json` defect is resolved to `knowledgegraph/research/gameplay-state-machines.json` across 226 records and 452 occurrences, with 0 current broken references and zero semantic change.
10. **Scope metadata tensions:** worker-16 and worker-20 describe alternate predicate paths. Reconciliation proves their requested output VA sets exact; their declaration text is not canonical authority.
11. **Historical population tension:** the older 1,977-row decomp-gap total must not be mixed with the current 1,976 nested-semantic residual.
12. **Deferral boundary:** `safe_to_defer=true` is package-specific. It never changes canonical `not_established` and does not mean the function is globally understood.

## 13. Quality gates

Before any future implementation proposal:

- Reconfirm binary version, image base, SHA-256, canonical snapshot, and xref snapshot.
- Reproduce the exact predicate and reconcile all 1,976 VAs with no duplicates, omissions, or extras.
- Preserve the validated rank order and worker decisions; score remains ordering only.
- Record whether a body is persisted, targeted static, committed static, runtime-observed, or absent; never conflate those evidence classes.
- Establish owner, type, field, return, vtable, and caller/callee evidence with alternatives retained when unresolved.
- Keep App, Simulator strategy/input, SpaceContext, scenario, Cell, Terrain, and presentation state axes separate.
- Keep event families, registration records, queue records, and payloads separate; require an exact producer/consumer trace before promotion.
- Keep static content, runtime/cache state, presentation state, and persistent save/profile state separate.
- Require a local fixture for Sporepedia metadata and an explicit no-network boundary.
- Require a matched original trace and human approval before any runtime experiment, differential claim, or compatibility claim.
- Record source-citation validation and the resolved historical provenance repair; preserve other metadata tensions, contradictions, and negative-scan records rather than repairing them by assumption.
- Do not treat package-boundary deferral, a high score, or a high-fan-in root as semantic completion.

## 14. Estimated reduction by major cluster and overall

The planning envelope below is defined narrowly as a possible transition from **canonical `not_established` to bounded static partial characterization**. It is not runtime validation, original semantic resolution, implementation completion, or a claim that a row will be promoted. The figures are a static planning allocation, not observed reduction.

| Major cluster | Conservative static-planning reduction | Optimistic static-planning reduction |
|---|---:|---:|
| `editor-core` | 22 | 80 |
| `editor-support` | 20 | 75 |
| `gameglobal-misc` | 2 | 25 |
| `sim-core-systems` | 55 | 320 |
| `sim-space` | 12 | 35 |
| `sporepedia-online` | 25 | 85 |
| `terrain-world` | 12 | 30 |
| `ui-shell` | 1 | 4 |
| **Overall** | **149** | **654** |

Accounting:

- Gameplay population: 2,149 = 1,976 not-established residuals + 173 existing partial rows.
- The 173 existing partial rows are not counted as new reduction; they are already outside the predicate.
- A conservative 149-row static-partial scenario would leave 1,827 not-established residuals and 322 partial rows, arithmetically. It does not change runtime-verified count, which remains zero.
- An optimistic 654-row static-partial scenario would leave 1,322 not-established residuals and 827 partial rows, arithmetically. It also does not establish runtime semantics.
- The JSON’s 191 residual records with information_gain_score >=35 are high-gain candidates, not solved rows and not the source of the 149/654 planning envelope.
- No estimate authorizes implementation or canonical mutation.

## 15. Validation, consistency, and mutation statement

- Section count: **15**.
- Top 25 rows: **25/25**, matching the validated projection.
- Top 100 rows: **100/100**, matching rank, VA, score, cluster, and family from the validated projection; no row was dropped.
- Safety classes: **36** `safe_to_defer=true`, **33** `safe_to_defer=false`, **3** conditional, and **1,904** other non-explicitly-safe residuals.
- Eleven-bucket count: **255 + 852 + 362 + 226 + 66 + 96 + 33 + 36 + 10 + 5 + 35 = 1,976**.
- Unlock-set reduction envelopes sum to **149 conservative / 654 optimistic**.
- Every address in the Top 25, Top 100, safe-defer groups, explicit-false list, conditional list, and U1–U9 seeds is checked against the normalized residual set or explicitly labeled as an external static anchor.

This synthesis did not modify worker artifacts, the canonical knowledge graph, the Ghidra project, `SPORE/` content, or implementation source/tests. Pre-existing unrelated dirty files were left unchanged; the two requested synthesis outputs are the only files created or updated by this refresh.
