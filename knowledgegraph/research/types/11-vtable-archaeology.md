# Global Vtable Archaeology

Read-only cross-cutting RE synthesis for `SporeApp.exe` 3.1.0.22. This report is static evidence only: no implementation, triage rewrite, Ghidra mutation, or `SPORE/` access occurred.

## Scope and method

- Frozen vtable scan: 3081 candidates, 20 labels, 16107 clusters, 12 explicit chains.
- High-value union: 33 records = all labels + all explicit chain endpoints + five dossier/SDK family anchors.
- Xrefs: 223704 canonical edges, including 11898 `vtable-ref` rows; rows identify the containing table base, not the exact selected slot.
- Ghidra read-only availability: zero open programs; the committed artifacts are the controlling evidence.
- Slot status is structural: `implemented`, `inherited`, `overridden`, and `unknown` are defined in the JSON and never treated as RTTI or runtime proof.

## Headline findings

- The strongest recoverable identity is `App::cCellModeStrategy` at `0x01485550`: 27 slots, ten named lifecycle/input/update methods, and three frozen table-base xref rows from two caller VAs. The current `IGameMode` is a clean-room partial interface, not a 27-slot ABI replacement.
- The explicit inheritance evidence is limited to two 21-slot UTFWin bases and six derived tables. The two bases are byte-identical at the recorded prefix, so the artifact does not choose a canonical base.
- UTFWin 40-slot candidates dominate the labels and clusters; many mix `UTFWin::Window` anchors with a single `Sporepedia::cSPAssetDataOTDB::HasName` method. This is a contradiction to preserve, not a hierarchy.
- `Sporepedia::cSPAssetDataOTDB`, `Editors::cEditor`, and `Simulator::cToolStrategy` have strong SDK family evidence but no RTTI proof. `0x01490be8` is additionally contradicted by a Terrain-labeled table versus a decomp-gap Sporepedia projection.
- No function-level runtime validation exists. The cell movement dossier is static; cell-stage probe evidence is negative.

## RTTI status

MSVC RTTI is absent from the supplied corpus. The scan provides code-pointer runs, SDK names, and xrefs, not type descriptors or a Complete Object Locator hierarchy. SDK labels, shared prefixes, and vtable references are recorded as RTTI-like evidence only; they do not establish unique class identity. The absence is justified by the committed campaign reports, while a fresh live binary-wide RTTI search was not possible because no Ghidra program was open.

## High-value vtable records

| VA | identity | status | slots | I/H/O/U | SDK methods | xref consumers | confidence |
|---|---|---|---:|---|---:|---:|---|
| `0x013f1a30` | VTAB_013f1a30_40slots | observed candidate | 40 | 38/0/0/2 | 17 | 71 | MEDIUM_OR_LOW_IDENTITY |
| `0x013f2194` | VTAB_013f2194_40slots | observed candidate | 40 | 39/0/0/1 | 13 | 32 | HIGH_STATIC_IDENTITY |
| `0x013f57f8` | Editors::cEditor | observed candidate | 29 | 24/0/0/5 | 24 | 6 | HIGH_STATIC_IDENTITY |
| `0x013fa794` | UTFWin::UTFWinObject family candidate | observed candidate | 30 | 0/21/3/6 | 7 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x013fa8f0` | VTAB_013fa8f0_40slots | observed candidate | 40 | 32/0/0/8 | 12 | 4 | HIGH_STATIC_IDENTITY |
| `0x013fa974` | UTFWin::UTFWinObject family candidate | observed candidate | 21 | 18/0/0/3 | 5 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x013fcc08` | VTAB_013fcc08_40slots | observed candidate | 40 | 32/0/0/8 | 14 | 1 | HIGH_STATIC_IDENTITY |
| `0x013fef9c` | UTFWin::UTFWinObject family candidate | observed candidate | 24 | 0/21/0/3 | 5 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x013ff648` | VTAB_013ff648_40slots | observed candidate | 40 | 29/0/0/11 | 26 | 3 | HIGH_STATIC_IDENTITY |
| `0x01408820` | App::PropertyList | observed candidate | 19 | 19/0/0/0 | 19 | 2 | HIGH_STATIC_IDENTITY |
| `0x01408870` | App::DirectPropertyList | observed candidate | 19 | 19/0/0/0 | 19 | 2 | HIGH_STATIC_IDENTITY |
| `0x01413acc` | VTAB_01413acc_40slots | observed candidate | 40 | 18/0/0/22 | 16 | 2 | HIGH_STATIC_IDENTITY |
| `0x01414ed4` | VTAB_01414ed4_40slots | observed candidate | 40 | 32/0/0/8 | 32 | 0 | HIGH_STATIC_IDENTITY |
| `0x0141873c` | VTAB_0141873c_40slots | observed candidate | 40 | 32/0/0/8 | 32 | 0 | HIGH_STATIC_IDENTITY |
| `0x01418838` | VTAB_01418838_40slots | observed candidate | 40 | 32/0/0/8 | 20 | 15 | HIGH_STATIC_IDENTITY |
| `0x014190d4` | VTAB_014190d4_40slots | observed candidate | 40 | 32/0/0/8 | 32 | 0 | HIGH_STATIC_IDENTITY |
| `0x014191d0` | VTAB_014191d0_40slots | observed candidate | 40 | 34/0/0/6 | 23 | 2 | HIGH_STATIC_IDENTITY |
| `0x0141930c` | VTAB_0141930c_40slots | observed candidate | 40 | 32/0/0/8 | 32 | 0 | HIGH_STATIC_IDENTITY |
| `0x014195ac` | VTAB_014195ac_40slots | observed candidate | 40 | 32/0/0/8 | 32 | 0 | HIGH_STATIC_IDENTITY |
| `0x01419794` | UTFWin::UTFWinObject family candidate | observed candidate | 21 | 18/0/0/3 | 5 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x0141a024` | UTFWin::UTFWinObject family candidate | observed candidate | 26 | 0/21/2/3 | 6 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x0141ab94` | VTAB_0141ab94_40slots | observed candidate | 40 | 32/0/0/8 | 32 | 0 | HIGH_STATIC_IDENTITY |
| `0x0141c930` | VTAB_0141c930_40slots | observed candidate | 40 | 25/0/0/15 | 25 | 2 | HIGH_STATIC_IDENTITY |
| `0x014368c4` | VTAB_014368c4_40slots | observed candidate | 40 | 22/0/0/18 | 21 | 6 | HIGH_STATIC_IDENTITY |
| `0x0143eaac` | VTAB_0143eaac_40slots | observed candidate | 40 | 22/0/0/18 | 20 | 3 | HIGH_STATIC_IDENTITY |
| `0x01441144` | VTAB_01441144_40slots | observed candidate | 40 | 32/0/0/8 | 32 | 1 | HIGH_STATIC_IDENTITY |
| `0x01442324` | Simulator::cToolStrategy family candidate | observed candidate | 28 | 0/21/3/4 | 8 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x01442604` | UTFWin::UTFWinObject family candidate | observed candidate | 24 | 0/21/3/0 | 7 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x014434fc` | UTFWin::UTFWinObject family candidate | observed candidate | 24 | 0/21/3/0 | 7 | 0 | MEDIUM_OR_LOW_IDENTITY |
| `0x014624d0` | Simulator::cToolStrategy family | observed candidate | 40 | 10/0/0/30 | 1 | 1 | HIGH_STATIC_IDENTITY |
| `0x01485550` | App::cCellModeStrategy | observed candidate | 27 | 18/0/0/9 | 17 | 2 | HIGH_STATIC_IDENTITY |
| `0x01490be8` | VTAB_01490be8_40slots | observed candidate | 40 | 17/0/0/23 | 17 | 2 | HIGH_STATIC_IDENTITY |
| `0x0149b4d8` | VTAB_0149b4d8_40slots | observed candidate | 40 | 20/0/0/20 | 12 | 1 | HIGH_STATIC_IDENTITY |

## Per-record archaeology

### `0x013f1a30` — VTAB_013f1a30_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `unattributed`, score `11`, long-run `True`.
- **Slots:** 40 total; implemented `38`, inherited `0`, overridden `0`, unknown `2`. Unknown slot indices: `0, 10`.
- **Methods:** `FUN_00402ab0, FUN_00461290, FUN_00472970, FUN_004cc320, FUN_00516da0, FUN_00516e10, FUN_00517160, FUN_005172c0, FUN_00517400, FUN_005182f0, FUN_0051a900, FUN_0051d090, FUN_0051e340, FUN_0051e380, FUN_0056f2b0, FUN_007f9b80, purecall`.
- **SDK association:** `none in the supplied vtable SDK index`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 71 unique caller VAs; `0x00410cc0, 0x00418870, 0x0041a980, 0x004301e0, 0x004329e0, 0x004346b0, 0x004575d0, 0x00469590, 0x0046a750, 0x0047d6a0, 0x004b24c0, 0x004bab30`.

### `0x013f2194` — VTAB_013f2194_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `Editors`, score `13`, long-run `True`.
- **Slots:** 40 total; implemented `39`, inherited `0`, overridden `0`, unknown `1`. Unknown slot indices: `0`.
- **Methods:** `Editors::EditorModel::SetColor, FUN_0051e340, FUN_0051e380, FUN_0052e620, FUN_0052e630, FUN_0052e640, FUN_0052e650, FUN_0052e660, FUN_0052e680, FUN_00533d80, FUN_00533da0, FUN_007f9b80, purecall`.
- **SDK association:** `Editors::EditorModel::SetColor`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 32 unique caller VAs; `0x0052e5b0, 0x0052e980, 0x00531270, 0x00531310, 0x00533ce0, 0x00537c90, 0x00537d60, 0x00538180, 0x007d5c50, 0x007d7d00, 0x007e0f70, 0x007edc90`.

### `0x013f57f8` — Editors::cEditor

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `Editors`, score `10`, long-run `False`.
- **Slots:** 29 total; implemented `24`, inherited `0`, overridden `0`, unknown `5`. Unknown slot indices: `6, 16, 17, 22, 24`.
- **Methods:** `Editors::cEditor::Dispose, Editors::cEditor::Initialize, Editors::cEditor::OnExit, Editors::cEditor::OnKeyDown, Editors::cEditor::OnKeyUp, Editors::cEditor::OnMouseDown, Editors::cEditor::OnMouseMove, Editors::cEditor::OnMouseUp, Editors::cEditor::OnMouseWheel, Editors::cEditor::Update, FUN_005732f0, FUN_00577310, FUN_005774f0, FUN_0057d6f0, FUN_0057e1d0, FUN_00580cb0, FUN_00586700, FUN_005b2490, FUN_005ba0d0, FUN_007b86e0, FUN_007f30d0, FUN_00b1fbf0, FUN_00c6a960, FUN_00e5cac0`.
- **SDK association:** `Editors::cEditor::Dispose, Editors::cEditor::Initialize, Editors::cEditor::OnExit, Editors::cEditor::OnKeyDown, Editors::cEditor::OnKeyUp, Editors::cEditor::OnMouseDown, Editors::cEditor::OnMouseMove, Editors::cEditor::OnMouseUp, Editors::cEditor::OnMouseWheel, Editors::cEditor::Update`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Named lifecycle operation is present; constructor/destructor ownership is not established from this table alone.
- **Consumers:** 6 unique caller VAs; `0x00579e20, 0x0057a6d0, 0x0057ce80, 0x00e642a0, 0x00ed8a30, 0x00fffdd0`.

### `0x013fa794` — UTFWin::UTFWinObject family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `11`, long-run `True`.
- **Slots:** 30 total; implemented `0`, inherited `21`, overridden `3`, unknown `6`. Unknown slot indices: `22, 23, 24, 25, 26, 27`.
- **Methods:** `FUN_006f2f20, FUN_00951280, FUN_00b267f0, FUN_00e31100, FUN_010829f0, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `0x013fa974, 0x01419794`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.

### `0x013fa8f0` — VTAB_013fa8f0_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `2, 4, 5, 16, 17, 18, 19, 27`.
- **Methods:** `FUN_00607df0, FUN_00620660, FUN_006f2f20, FUN_0083f5d0, FUN_00950eb0, FUN_00951280, FUN_009800e0, FUN_00b267f0, FUN_00e31100, FUN_010829f0, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 4 unique caller VAs; `0x00607450, 0x00607480, 0x0060b730, 0x006204b0`.

### `0x013fa974` — UTFWin::UTFWinObject family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `12`, long-run `True`.
- **Slots:** 21 total; implemented `18`, inherited `0`, overridden `0`, unknown `3`. Unknown slot indices: `7, 9, 10`.
- **Methods:** `FUN_006f2f20, FUN_00b267f0, FUN_010829f0, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `none`; explicit derived `0x013fa794, 0x013fef9c, 0x0141a024, 0x01442324, 0x01442604, 0x014434fc`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** Both bases share the same 21-slot prefix and are both reported as bases for the same six derived tables; the artifact does not resolve which base is canonical.

### `0x013fcc08` — VTAB_013fcc08_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `5, 6, 18, 20, 21, 34, 36, 39`.
- **Methods:** `FUN_00620660, FUN_00620720, FUN_006f2f20, FUN_0083f5d0, FUN_00950eb0, FUN_009800e0, FUN_00b1e4d0, FUN_00b1fbf0, FUN_00b267f0, FUN_00c2e4e0, FUN_00e31100, FUN_010829f0, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 1 unique caller VAs; `0x006204b0`.

### `0x013fef9c` — UTFWin::UTFWinObject family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `11`, long-run `True`.
- **Slots:** 24 total; implemented `0`, inherited `21`, overridden `0`, unknown `3`. Unknown slot indices: `21, 22, 23`.
- **Methods:** `FUN_006f2f20, FUN_00b267f0, FUN_010829f0, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `0x013fa974, 0x01419794`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.

### `0x013ff648` — VTAB_013ff648_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `Sporepedia`, score `13`, long-run `True`.
- **Slots:** 40 total; implemented `29`, inherited `0`, overridden `0`, unknown `11`. Unknown slot indices: `1, 6, 7, 10, 17, 18, 19, 21, 26, 31, 37`.
- **Methods:** `FUN_005c0dd0, FUN_006413d0, FUN_00641410, FUN_00641490, FUN_00641780, FUN_006417d0, FUN_00641fa0, FUN_00641fd0, FUN_00642210, FUN_00642700, FUN_006e64f0, FUN_00a649a0, FUN_00b1e4d0, FUN_00b1fbf0, FUN_00b7e380, FUN_00c2e4e0, FUN_00e31100, Sporepedia::cSPAssetDataOTDB::GetAssetID, Sporepedia::cSPAssetDataOTDB::GetAuthorID, Sporepedia::cSPAssetDataOTDB::GetAuthorName, Sporepedia::cSPAssetDataOTDB::GetTags, Sporepedia::cSPAssetDataOTDB::GetTimeCreated, Sporepedia::cSPAssetDataOTDB::HasName, Sporepedia::cSPAssetDataOTDB::IsEditable, Sporepedia::cSPAssetDataOTDB::func3Ch, Sporepedia::cSPAssetDataOTDB::func7Ch`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::GetAssetID, Sporepedia::cSPAssetDataOTDB::GetAuthorID, Sporepedia::cSPAssetDataOTDB::GetAuthorName, Sporepedia::cSPAssetDataOTDB::GetTags, Sporepedia::cSPAssetDataOTDB::GetTimeCreated, Sporepedia::cSPAssetDataOTDB::HasName, Sporepedia::cSPAssetDataOTDB::IsEditable, Sporepedia::cSPAssetDataOTDB::func3Ch, Sporepedia::cSPAssetDataOTDB::func7Ch`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `1`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 3 unique caller VAs; `0x00642100, 0x00642190, 0x00ecc680`.

### `0x01408820` — App::PropertyList

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `App`, score `11`, long-run `False`.
- **Slots:** 19 total; implemented `19`, inherited `0`, overridden `0`, unknown `0`. Unknown slot indices: `none`.
- **Methods:** `App::PropertyList::AddAllPropertiesFrom, App::PropertyList::AddPropertiesFrom, App::PropertyList::Clear, App::PropertyList::CopyAllPropertiesFrom, App::PropertyList::CopyFrom, App::PropertyList::GetProperty, App::PropertyList::GetPropertyAlt, App::PropertyList::GetPropertyIDs, App::PropertyList::GetPropertyObject, App::PropertyList::HasProperty, App::PropertyList::Read, App::PropertyList::RemoveProperty, App::PropertyList::SetProperty, App::PropertyList::Write, FUN_00432940, FUN_00432b50, FUN_00432be0, FUN_006a1c80, FUN_006abe20`.
- **SDK association:** `App::PropertyList::AddAllPropertiesFrom, App::PropertyList::AddPropertiesFrom, App::PropertyList::Clear, App::PropertyList::CopyAllPropertiesFrom, App::PropertyList::CopyFrom, App::PropertyList::GetProperty, App::PropertyList::GetPropertyAlt, App::PropertyList::GetPropertyIDs, App::PropertyList::GetPropertyObject, App::PropertyList::HasProperty, App::PropertyList::Read, App::PropertyList::RemoveProperty, App::PropertyList::SetProperty, App::PropertyList::Write`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 2 unique caller VAs; `0x006a1b90, 0x006a1c40`.

### `0x01408870` — App::DirectPropertyList

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `App`, score `10`, long-run `False`.
- **Slots:** 19 total; implemented `19`, inherited `0`, overridden `0`, unknown `0`. Unknown slot indices: `none`.
- **Methods:** `App::DirectPropertyList::AddPropertiesFrom, App::DirectPropertyList::Clear, App::DirectPropertyList::CopyFrom, App::DirectPropertyList::GetProperty, App::DirectPropertyList::GetPropertyAlt, App::DirectPropertyList::GetPropertyIDs, App::DirectPropertyList::GetPropertyObject, App::DirectPropertyList::HasProperty, App::DirectPropertyList::Read, App::DirectPropertyList::SetProperty, App::DirectPropertyList::Write, App::PropertyList::AddAllPropertiesFrom, App::PropertyList::CopyAllPropertiesFrom, App::PropertyList::RemoveProperty, FUN_00432940, FUN_00432b50, FUN_00432be0, FUN_006a1d60, FUN_006abe20`.
- **SDK association:** `App::DirectPropertyList::AddPropertiesFrom, App::DirectPropertyList::Clear, App::DirectPropertyList::CopyFrom, App::DirectPropertyList::GetProperty, App::DirectPropertyList::GetPropertyAlt, App::DirectPropertyList::GetPropertyIDs, App::DirectPropertyList::GetPropertyObject, App::DirectPropertyList::HasProperty, App::DirectPropertyList::Read, App::DirectPropertyList::SetProperty, App::DirectPropertyList::Write, App::PropertyList::AddAllPropertiesFrom, App::PropertyList::CopyAllPropertiesFrom, App::PropertyList::RemoveProperty`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 2 unique caller VAs; `0x006a1bd0, 0x006a1ca0`.

### `0x01413acc` — VTAB_01413acc_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `App`, score `12`, long-run `True`.
- **Slots:** 40 total; implemented `18`, inherited `0`, overridden `0`, unknown `22`. Unknown slot indices: `0, 1, 2, 3, 4, 9, 13, 15, 16, 17, 18, 19, 20, 21, 22, 24, 29, 30, 32, 33, 34, 39`.
- **Methods:** `App::cAppSystem::HookWindows, App::cAppSystem::InitPlugins, App::cAppSystem::Unpause, FUN_00671f50, FUN_007e6090, FUN_007e6470, FUN_007e6650, FUN_007e67a0, FUN_007e7380, FUN_007e8b70, FUN_007e9300, FUN_007e9d00, FUN_007e9db0, FUN_00ae06a0, FUN_00b1e4d0, FUN_00e31100`.
- **SDK association:** `App::cAppSystem::HookWindows, App::cAppSystem::InitPlugins, App::cAppSystem::Unpause`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 2 unique caller VAs; `0x007e7630, 0x007e78d0`.

### `0x01414ed4` — VTAB_01414ed4_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `3, 4, 8, 9, 23, 26, 27, 29`.
- **Methods:** `FUN_006e87e0, FUN_00885c90, FUN_0095fa00, FUN_0095fa20, FUN_0095fa60, FUN_0095fdc0, FUN_0095fe40, FUN_0095fec0, FUN_0095ff20, FUN_0095ff70, FUN_0095ffd0, FUN_00960020, FUN_009600f0, FUN_00960100, FUN_009608c0, FUN_009609b0, FUN_00960f20, FUN_00960fe0, FUN_00961760, FUN_00961860, FUN_009618e0, FUN_00961950, FUN_00962530, FUN_0098e690, FUN_0098f940, Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35, thunk_FUN_008d5f20, thunk_FUN_0095fa50`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `1`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** The table carries UTFWin method anchors but only Sporepedia::cSPAssetDataOTDB::HasName; this is cross-namespace candidate contamination, not proof of a UTFWin-to-Sporepedia base.

### `0x0141873c` — VTAB_0141873c_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `3, 4, 8, 9, 15, 26, 27, 29`.
- **Methods:** `FUN_006e87e0, FUN_00885c90, FUN_008d5f20, FUN_0095fa00, FUN_0095fa20, FUN_0095fa40, FUN_0095fa50, FUN_0095fa60, FUN_0095fdc0, FUN_0095fec0, FUN_0095ff20, FUN_0095ff70, FUN_0095ffd0, FUN_00960020, FUN_009600f0, FUN_00960100, FUN_009608c0, FUN_009609b0, FUN_00960f20, FUN_00960fe0, FUN_00961760, FUN_00961860, FUN_009618e0, FUN_00961950, FUN_00961f20, FUN_00962530, FUN_0098f940, Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `5`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** The table carries UTFWin method anchors but only Sporepedia::cSPAssetDataOTDB::HasName; this is cross-namespace candidate contamination, not proof of a UTFWin-to-Sporepedia base.

### `0x01418838` — VTAB_01418838_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `False`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `5, 7, 10, 15, 34, 37, 38, 39`.
- **Methods:** `FUN_007b86e0, FUN_00813370, FUN_00813550, FUN_00813630, FUN_008136b0, FUN_00813e70, FUN_00814380, FUN_00814d50, FUN_00815dd0, FUN_0081d5a0, FUN_0081d5b0, FUN_00950ea0, FUN_00960310, FUN_00960520, FUN_00b1e4d0, FUN_00c2e4e0, FUN_00c6a960, FUN_010829f0, UTFWin::UTFWinObject::new_, UTFWin::Window::GetRealArea`.
- **SDK association:** `UTFWin::UTFWinObject::new_, UTFWin::Window::GetRealArea`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 15 unique caller VAs; `0x00633ac0, 0x006f9020, 0x00720010, 0x00782660, 0x007a7d50, 0x0080e850, 0x00813ca0, 0x008141b0, 0x00815dd0, 0x00a7a960, 0x00a92d90, 0x00e61550`.

### `0x014190d4` — VTAB_014190d4_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `3, 4, 8, 9, 26, 27, 29, 38`.
- **Methods:** `FUN_006e87e0, FUN_00885c90, FUN_008d5f20, FUN_0095fa00, FUN_0095fa20, FUN_0095fa40, FUN_0095fa50, FUN_0095fa60, FUN_0095fdc0, FUN_0095fe40, FUN_0095fec0, FUN_0095ff20, FUN_0095ff70, FUN_0095ffd0, FUN_00960020, FUN_009600f0, FUN_00960100, FUN_009608c0, FUN_00960f20, FUN_00961860, FUN_009618e0, FUN_00961950, FUN_00961f20, FUN_00962530, FUN_00964610, FUN_00964640, FUN_0098f940, Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `8`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** The table carries UTFWin method anchors but only Sporepedia::cSPAssetDataOTDB::HasName; this is cross-namespace candidate contamination, not proof of a UTFWin-to-Sporepedia base.

### `0x014191d0` — VTAB_014191d0_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `34`, inherited `0`, overridden `0`, unknown `6`. Unknown slot indices: `3, 5, 7, 19, 20, 39`.
- **Methods:** `FUN_0081ad10, FUN_0081ae40, FUN_0081ae60, FUN_0081af30, FUN_0081c900, FUN_00950bb0, FUN_00950ea0, FUN_00964000, FUN_00964190, FUN_009642d0, FUN_00964330, FUN_009643c0, FUN_009645a0, FUN_00964890, FUN_00964c90, FUN_00965230, FUN_00966c70, FUN_00c2e4e0, FUN_010829f0, UTFWin::UTFWinObject::new_, UTFWin::Window::SetCommandID, UTFWin::Window::SetTextFontID, thunk_FUN_00b1fbf0`.
- **SDK association:** `UTFWin::UTFWinObject::new_, UTFWin::Window::SetCommandID, UTFWin::Window::SetTextFontID`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 2 unique caller VAs; `0x0081aa00, 0x0081ad10`.

### `0x0141930c` — VTAB_0141930c_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `3, 4, 8, 9, 26, 27, 29, 38`.
- **Methods:** `FUN_006e87e0, FUN_00885c90, FUN_008d5f20, FUN_0095fa00, FUN_0095fa20, FUN_0095fa40, FUN_0095fa50, FUN_0095fa60, FUN_0095fdc0, FUN_0095fe40, FUN_0095fec0, FUN_0095ff20, FUN_0095ff70, FUN_0095ffd0, FUN_00960020, FUN_009600f0, FUN_00960100, FUN_009608c0, FUN_00960f20, FUN_00961860, FUN_009618e0, FUN_00961950, FUN_00961f20, FUN_00962530, FUN_00964610, FUN_00964640, FUN_0098f940, Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `8`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** The table carries UTFWin method anchors but only Sporepedia::cSPAssetDataOTDB::HasName; this is cross-namespace candidate contamination, not proof of a UTFWin-to-Sporepedia base.

### `0x014195ac` — VTAB_014195ac_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `3, 4, 8, 9, 26, 27, 29, 38`.
- **Methods:** `FUN_006e87e0, FUN_00885c90, FUN_008d5f20, FUN_0095fa00, FUN_0095fa20, FUN_0095fa40, FUN_0095fa50, FUN_0095fa60, FUN_0095fdc0, FUN_0095fe40, FUN_0095fec0, FUN_0095ff20, FUN_0095ff70, FUN_0095ffd0, FUN_00960020, FUN_009600f0, FUN_00960100, FUN_009608c0, FUN_00960f20, FUN_00961860, FUN_009618e0, FUN_00961950, FUN_00961f20, FUN_00962530, FUN_00964610, FUN_00964640, FUN_0098f940, Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `8`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** The table carries UTFWin method anchors but only Sporepedia::cSPAssetDataOTDB::HasName; this is cross-namespace candidate contamination, not proof of a UTFWin-to-Sporepedia base.

### `0x01419794` — UTFWin::UTFWinObject family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `12`, long-run `True`.
- **Slots:** 21 total; implemented `18`, inherited `0`, overridden `0`, unknown `3`. Unknown slot indices: `7, 9, 10`.
- **Methods:** `FUN_006f2f20, FUN_00b267f0, FUN_010829f0, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `none`; explicit derived `0x013fa794, 0x013fef9c, 0x0141a024, 0x01442324, 0x01442604, 0x014434fc`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** Both bases share the same 21-slot prefix and are both reported as bases for the same six derived tables; the artifact does not resolve which base is canonical.

### `0x0141a024` — UTFWin::UTFWinObject family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `11`, long-run `True`.
- **Slots:** 26 total; implemented `0`, inherited `21`, overridden `2`, unknown `3`. Unknown slot indices: `23, 24, 25`.
- **Methods:** `FUN_006f2f20, FUN_00b267f0, FUN_010829f0, FUN_01154720, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `0x013fa974, 0x01419794`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.

### `0x0141ab94` — VTAB_0141ab94_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `3, 4, 8, 9, 23, 26, 27, 29`.
- **Methods:** `FUN_006e87e0, FUN_00885c90, FUN_008d5f20, FUN_0095fa00, FUN_0095fa20, FUN_0095fa40, FUN_0095fa50, FUN_0095fa60, FUN_0095fdc0, FUN_0095fe40, FUN_0095fec0, FUN_0095ff20, FUN_0095ff70, FUN_0095ffd0, FUN_00960020, FUN_009600f0, FUN_00960100, FUN_009608c0, FUN_009609b0, FUN_00960f20, FUN_00960fe0, FUN_00961860, FUN_009618e0, FUN_00961950, FUN_00962530, FUN_00988710, FUN_0098f940, Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `5`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 0 unique caller VAs; `none`.
- **Contradictions:** The table carries UTFWin method anchors but only Sporepedia::cSPAssetDataOTDB::HasName; this is cross-namespace candidate contamination, not proof of a UTFWin-to-Sporepedia base.

### `0x0141c930` — VTAB_0141c930_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `ArgScript`, score `10`, long-run `True`.
- **Slots:** 40 total; implemented `25`, inherited `0`, overridden `0`, unknown `15`. Unknown slot indices: `1, 4, 5, 6, 7, 8, 9, 10, 25, 26, 30, 31, 33, 35, 39`.
- **Methods:** `ArgScript::FormatParser::GetCurrentScope, ArgScript::FormatParser::ParseFloat, ArgScript::FormatParser::ParseUInt, ArgScript::FormatParser::Release, FUN_0083f5d0, FUN_00841220, FUN_00841300, FUN_00841370, FUN_008413e0, FUN_008413f0, FUN_00841c90, FUN_00842c60, FUN_00842f50, FUN_00843240, FUN_00843320, FUN_008440d0, FUN_00844ec0, FUN_00844fb0, FUN_00845320, FUN_008456e0, FUN_00846280, FUN_00846b00, FUN_00846db0, FUN_00846f10, FUN_00ff35d0`.
- **SDK association:** `ArgScript::FormatParser::GetCurrentScope, ArgScript::FormatParser::ParseFloat, ArgScript::FormatParser::ParseUInt, ArgScript::FormatParser::Release`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Named lifecycle operation is present; constructor/destructor ownership is not established from this table alone.
- **Consumers:** 2 unique caller VAs; `0x00847200, 0x00847490`.

### `0x014368c4` — VTAB_014368c4_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `Resource`, score `13`, long-run `True`.
- **Slots:** 40 total; implemented `22`, inherited `0`, overridden `0`, unknown `18`. Unknown slot indices: `0, 1, 2, 3, 4, 6, 8, 9, 11, 20, 21, 23, 24, 26, 27, 28, 29, 30`.
- **Methods:** `FUN_004c0190, FUN_006c0200, FUN_006c04a0, FUN_006c04e0, FUN_006c0520, FUN_008dc790, FUN_008dc7b0, FUN_008dc7e0, FUN_008dc860, FUN_008dca00, FUN_008dcd70, FUN_008dd1b0, FUN_008dd1c0, FUN_00950ea0, FUN_00b1e4d0, FUN_00b1fbf0, FUN_00e31100, FUN_0113ae10, Resource::PFRecordRead::ReadData, Resource::PFRecordWrite::GetAvailable, Resource::PFRecordWrite::GetType`.
- **SDK association:** `Resource::PFRecordRead::ReadData, Resource::PFRecordWrite::GetAvailable, Resource::PFRecordWrite::GetType`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 6 unique caller VAs; `0x008dcc80, 0x008dcd70, 0x008dcdc0, 0x008dcea0, 0x008dd0d0, 0x008dd1f0`.
- **Contradictions:** The candidate has SDK PFRecordRead/PFRecordWrite anchors, but the 40-slot run mixes read/write and unnamed targets; exact base type and slot ownership remain unresolved.

### `0x0143eaac` — VTAB_0143eaac_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `IO`, score `12`, long-run `True`.
- **Slots:** 40 total; implemented `22`, inherited `0`, overridden `0`, unknown `18`. Unknown slot indices: `2, 3, 4, 12, 13, 15, 17, 18, 21, 23, 24, 25, 26, 30, 32, 33, 34, 38`.
- **Methods:** `FUN_006c0200, FUN_0083f5d0, FUN_0093ae80, FUN_0093aeb0, FUN_0093aef0, FUN_0093b050, FUN_0093b0a0, FUN_0093b450, FUN_0093b490, FUN_0093b6c0, FUN_0093b770, FUN_0093b920, FUN_0093c3e0, FUN_00950ea0, FUN_00b1fbf0, FUN_00e31100, FUN_00fc7e50, IO::StreamBuffer::GetAvailable, IO::StreamChild::GetAvailable, StreamChild_Close`.
- **SDK association:** `IO::StreamBuffer::GetAvailable, IO::StreamChild::GetAvailable`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Named lifecycle operation is present; constructor/destructor ownership is not established from this table alone.
- **Consumers:** 3 unique caller VAs; `0x0093b530, 0x0093b5a0, 0x0093b7d0`.

### `0x01441144` — VTAB_01441144_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `UTFWin`, score `14`, long-run `True`.
- **Slots:** 40 total; implemented `32`, inherited `0`, overridden `0`, unknown `8`. Unknown slot indices: `3, 4, 8, 9, 26, 27, 29, 38`.
- **Methods:** `FUN_006e87e0, FUN_00885c90, FUN_008d5f20, FUN_0095fa00, FUN_0095fa20, FUN_0095fa40, FUN_0095fa50, FUN_0095fa60, FUN_0095fdc0, FUN_0095fe40, FUN_0095fec0, FUN_0095ff20, FUN_0095ff70, FUN_0095ffd0, FUN_00960020, FUN_009600f0, FUN_00960100, FUN_009608c0, FUN_00960f20, FUN_00961860, FUN_009618e0, FUN_00961950, FUN_00961f20, FUN_00962530, FUN_00964610, FUN_00964640, FUN_0098f940, Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, UTFWin::Window::GetCursorID, UTFWin::Window::GetDrawable, UTFWin::Window::IsAncestorOf, UTFWin::Window::func35`.
- **Inheritance:** shared-slot cluster only; explicit bases `none`; explicit derived `none`; related candidates `8`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 1 unique caller VAs; `0x00966f90`.
- **Contradictions:** The table carries UTFWin method anchors but only Sporepedia::cSPAssetDataOTDB::HasName; this is cross-namespace candidate contamination, not proof of a UTFWin-to-Sporepedia base.

### `0x01442324` — Simulator::cToolStrategy family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `11`, long-run `True`.
- **Slots:** 28 total; implemented `0`, inherited `21`, overridden `3`, unknown `4`. Unknown slot indices: `22, 25, 26, 27`.
- **Methods:** `FUN_006f2f20, FUN_00a6ca00, FUN_00b267f0, FUN_00e31100, FUN_010829f0, Simulator::cToolStrategy::OnSelect, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `Simulator::cToolStrategy::OnSelect, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `0x013fa974, 0x01419794`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.

### `0x01442604` — UTFWin::UTFWinObject family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `12`, long-run `True`.
- **Slots:** 24 total; implemented `0`, inherited `21`, overridden `3`, unknown `0`. Unknown slot indices: `none`.
- **Methods:** `FUN_006f2f20, FUN_00970010, FUN_00b267f0, FUN_010829f0, FUN_01154720, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `0x013fa974, 0x01419794`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.

### `0x014434fc` — UTFWin::UTFWinObject family candidate

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `MEDIUM_OR_LOW_IDENTITY`, namespace `UTFWin`, score `12`, long-run `True`.
- **Slots:** 24 total; implemented `0`, inherited `21`, overridden `3`, unknown `0`. Unknown slot indices: `none`.
- **Methods:** `FUN_006f2f20, FUN_0097e5e0, FUN_00b267f0, FUN_010829f0, FUN_01154720, UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **SDK association:** `UTFWin::GetAllocator, UTFWin::UTFWinObject::new_`.
- **Inheritance:** explicit prefix chain; explicit bases `0x013fa974, 0x01419794`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Allocator/new scaffolding is visible; no explicit destructor method is resolved.
- **Consumers:** 0 unique caller VAs; `none`.

### `0x014624d0` — Simulator::cToolStrategy family

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `Simulator`, score `12`, long-run `True`.
- **Slots:** 40 total; implemented `10`, inherited `0`, overridden `0`, unknown `30`. Unknown slot indices: `1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15, 17, 18, 19, 21, 22, 23, 25, 26, 27, 29, 30, 31, 33, 34, 35, 37, 38, 39`.
- **Methods:** `Simulator::cToolStrategy::OnSelect`.
- **SDK association:** `Simulator::cToolStrategy::OnSelect`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 1 unique caller VAs; `0x00b60d80`.

### `0x01485550` — App::cCellModeStrategy

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `App`, score `11`, long-run `False`.
- **Slots:** 27 total; implemented `18`, inherited `0`, overridden `0`, unknown `9`. Unknown slot indices: `0, 1, 4, 10, 15, 20, 22, 23, 26`.
- **Methods:** `App::cCellModeStrategy::Dispose, App::cCellModeStrategy::Initialize, App::cCellModeStrategy::OnEnter, App::cCellModeStrategy::OnExit, App::cCellModeStrategy::OnKeyDown, App::cCellModeStrategy::OnMouseDown, App::cCellModeStrategy::OnMouseMove, App::cCellModeStrategy::OnMouseUp, App::cCellModeStrategy::OnMouseWheel, App::cCellModeStrategy::Update, FUN_007b86e0, FUN_00b1fbf0, FUN_00b7d400, FUN_00c6a960, FUN_00dd3d10, FUN_00e5cac0, FUN_01154720`.
- **SDK association:** `App::cCellModeStrategy::Dispose, App::cCellModeStrategy::Initialize, App::cCellModeStrategy::OnEnter, App::cCellModeStrategy::OnExit, App::cCellModeStrategy::OnKeyDown, App::cCellModeStrategy::OnMouseDown, App::cCellModeStrategy::OnMouseMove, App::cCellModeStrategy::OnMouseUp, App::cCellModeStrategy::OnMouseWheel, App::cCellModeStrategy::Update`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** Slot 1 is SDK-associated HandleMessage data, not a constructor/destructor; lifecycle is slots 6-9 and 16-17.
- **Consumers:** 2 unique caller VAs; `0x00e61550, 0x00e616c0`.
- **Contradictions:** The decomp-gap/triage cEditor family projection includes this address because of shared pointer runs, while the SDK/vtable/dossier evidence identifies App::cCellModeStrategy; family projection is not a class identity proof.

### `0x01490be8` — VTAB_01490be8_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `Terrain`, score `8`, long-run `True`.
- **Slots:** 40 total; implemented `17`, inherited `0`, overridden `0`, unknown `23`. Unknown slot indices: `1, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19, 21, 23, 25, 27, 29, 31, 32, 38`.
- **Methods:** `FUN_00967e70, FUN_00f967d0, FUN_00f96840, FUN_00f99980, FUN_00f999e0, FUN_00f9b7f0, FUN_00f9bee0, FUN_00f9fef0, FUN_00fa0d50, FUN_00fa5040, FUN_00fa5580, FUN_00fa6ec0, FUN_00fa73c0, FUN_00faad80, FUN_0104c110, Sporepedia::cSPAssetDataOTDB::HasName, Terrain::cTerrainSphere::GetSimDataRTT`.
- **SDK association:** `Sporepedia::cSPAssetDataOTDB::HasName, Terrain::cTerrainSphere::GetSimDataRTT`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 2 unique caller VAs; `0x00fa0780, 0x00fa1bc0`.
- **Contradictions:** A decomp-gap projection associates this address with Sporepedia::cSPAssetDataOTDB, while the vtable pass labels it Terrain and the slot has Terrain::cTerrainSphere::GetSimDataRTT; preserve both claims without hierarchy inference.

### `0x0149b4d8` — VTAB_0149b4d8_40slots

- **Status:** observed_candidate; candidate confidence `HIGH`, identity confidence `HIGH_STATIC_IDENTITY`, namespace `Simulator`, score `13`, long-run `True`.
- **Slots:** 40 total; implemented `20`, inherited `0`, overridden `0`, unknown `20`. Unknown slot indices: `1, 2, 3, 5, 6, 7, 9, 10, 11, 15, 16, 17, 20, 24, 25, 26, 33, 34, 35, 38`.
- **Methods:** `FUN_007b86e0, FUN_00b267f0, FUN_00b7d400, FUN_00c6a960, FUN_01052f00, FUN_010535e0, FUN_010537b0, FUN_010537e0, FUN_01053980, FUN_01053bb0, FUN_01053be0, Simulator::cToolStrategy::OnSelect`.
- **SDK association:** `Simulator::cToolStrategy::OnSelect`.
- **Inheritance:** no inheritance evidence in supplied artifacts; explicit bases `none`; explicit derived `none`; related candidates `0`.
- **Constructor/destructor:** No explicit constructor/destructor method is resolved; do not infer ABI ownership from slot position alone.
- **Consumers:** 1 unique caller VAs; `0x01055890`.

## Family trees

### FAM-APP-CAPPSYSTEM — App::cAppSystem candidate family

- Anchors: `0x01413acc`; selected members: `0x01413acc`.
- Status: shared-slot-family-only; confidence `MEDIUM_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-APP-CELLMODE — App::cCellModeStrategy 27-slot mode contract

- Anchors: `0x01485550`; selected members: `0x01485550`.
- Status: shared-slot-family-only; confidence `HIGH_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.
- Explicit/manual edges: IGameMode::clean-room interface -> 0x01485550 (prefix None)

### FAM-APP-PROPERTY — App::PropertyList / DirectPropertyList 19-slot family

- Anchors: `0x01408820, 0x01408870`; selected members: `0x01408820, 0x01408870`.
- Status: shared-slot-family-only; confidence `MEDIUM_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-ARGSCRIPT-FORMAT — ArgScript::FormatParser candidate family

- Anchors: `0x0141c930`; selected members: `0x0141c930`.
- Status: shared-slot-family-only; confidence `HIGH_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-EDITORS-CEDITOR — Editors::cEditor gameplay dispatch family

- Anchors: `0x013f57f8`; selected members: `0x013f57f8`.
- Status: shared-slot-family-only; confidence `HIGH_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-EDITORS-EDITOR-MODEL — Editors::EditorModel candidate family

- Anchors: `0x013f2194`; selected members: `0x013f2194`.
- Status: shared-slot-family-only; confidence `MEDIUM_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-IO-STREAM — IO candidate family

- Anchors: `0x0143eaac`; selected members: `0x0143eaac`.
- Status: shared-slot-family-only; confidence `MEDIUM_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-RESOURCE-PFRECORD — Resource::PFRecordRead/PFRecordWrite candidate family

- Anchors: `0x014368c4`; selected members: `0x014368c4`.
- Status: shared-slot-family-only; confidence `HIGH_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-SIMULATOR-TOOL — Simulator::cToolStrategy 40-slot family

- Anchors: `0x014624d0, 0x0149b4d8`; selected members: `0x01442324, 0x014624d0, 0x0149b4d8`.
- Status: shared-slot-family-only; confidence `HIGH_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-SPORPEDIA-ASSET — Sporepedia::cSPAssetDataOTDB candidate family

- Anchors: `0x013ff648`; selected members: `0x013ff648, 0x01414ed4, 0x0141873c, 0x014190d4, 0x0141930c, 0x014195ac, 0x0141ab94, 0x01441144, 0x01490be8`.
- Status: shared-slot-family-only; confidence `HIGH_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-TERRAIN-SPHERE — Terrain::cTerrainSphere candidate family

- Anchors: `0x01490be8`; selected members: `0x01490be8`.
- Status: shared-slot-family-only; confidence `HIGH_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-UNATTRIBUTED-40 — Unattributed 40-slot candidate family

- Anchors: `0x013f1a30`; selected members: `0x013f1a30`.
- Status: shared-slot-family-only; confidence `MEDIUM_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

### FAM-UTFWIN-UTFWINOBJECT-21 — UTFWin::UTFWinObject 21-slot base-prefix family

- Anchors: `0x013fa974, 0x01419794`; selected members: `0x013fa794, 0x013fa974, 0x013fef9c, 0x01419794, 0x0141a024, 0x01442324, 0x01442604, 0x014434fc`.
- Status: explicit_prefix_chains; confidence `MEDIUM_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.
- Explicit/manual edges: 0x013fa974 -> 0x01442604 (prefix 21); 0x013fa974 -> 0x014434fc (prefix 21); 0x013fa974 -> 0x013fa794 (prefix 21); 0x013fa974 -> 0x013fef9c (prefix 21); 0x013fa974 -> 0x0141a024 (prefix 21); 0x013fa974 -> 0x01442324 (prefix 21); 0x01419794 -> 0x01442604 (prefix 21); 0x01419794 -> 0x014434fc (prefix 21); 0x01419794 -> 0x013fa794 (prefix 21); 0x01419794 -> 0x013fef9c (prefix 21); 0x01419794 -> 0x0141a024 (prefix 21); 0x01419794 -> 0x01442324 (prefix 21)

### FAM-UTFWIN-WINDOW-40 — UTFWin::Window 40-slot candidate family

- Anchors: `0x01414ed4, 0x0141873c, 0x01418838, 0x014190d4, 0x014191d0, 0x0141930c, 0x014195ac, 0x0141ab94, 0x01441144, 0x01441794, 0x01441edc, 0x01443aec, 0x014458c4, 0x0147f76c, 0x0147fbe4`; selected members: `0x01414ed4, 0x0141873c, 0x01418838, 0x014190d4, 0x014191d0, 0x0141930c, 0x014195ac, 0x0141ab94, 0x01441144`.
- Status: shared-slot-family-only; confidence `MEDIUM_STATIC`.
- Shared vtable prefixes and SDK method anchors identify candidate families; without MSVC RTTI they do not prove a unique C++ base class.

## Xrefs, fields, and vtable consumers

- Global table-base xrefs: `11898` `vtable-ref` + `4049` `data-ref`; allowlist `3081`.
- `cGameInputManager` has an SDK-confirmed vtable field at `+0x00`, `mLastGameMode` at `+0x18`, and `mCurrentGameMode` at `+0x1c`; no candidate base is uniquely attached by the supplied field map.
- `SpacePlayerData` fields `+0x04`, `+0x10`, `+0x18`, and `+0x1c` feed accessors; the cached empire validator uses virtual AddRef/Release, but the exact object table and slot numbers are unresolved.
- `sCellGame+0x411c`, `+0x5158`, and `+0x5270` are field-offset anchors for the Cell update/movement path, not proof of a C++ vtable owner.
- A vtable-ref points to the containing base. It does not identify which slot a call selected, and a direct caller count of zero does not mean a virtual method is unreachable.

## Current src comparison

| Original/boundary | Current source | Comparison |
|---|---|---|
| App::cCellModeStrategy | `src/apps/IGameMode.hpp:28-52; src/apps/CellModeStrategy.hpp:45-76` | Strong slot correspondence for ten named methods; current IGameMode is a clean-room abstract interface and does not reproduce all 27 original slots. |
| CellGame state | `src/sim/CellGame.hpp:55-155; src/replace/CellGameView.hpp:41-57` | Current structs model named fields and selected aliases; CellGameView is explicitly not the true class layout. |
| cCellQueryEntry | `src/sim/CellQuery.hpp:27-82` | Layout-stable clean-room POD, not a vtable and not a complete original arena contract. |
| Resource provider seam | `src/compat/ResourceProvider.hpp:21-88` | Modern one-method virtual compatibility seam; unrelated to the original binary vtable ABI. |
| Input/mode routing | `src/apps/CellInput.hpp:1-10,85-107; src/apps/CellModeStrategy.hpp:79-97` | Current routing shell reproduces selected static contracts, not original event order or runtime semantics. |

## Semantic atlas, global campaign, dossiers, and decomp gaps

- Semantic atlas: all 58,757 canonical contracts remain unknown; SDK/vtable links, current tests, and package scope are not runtime evidence; cluster-derived package ownership is not a fact.
- Global campaign: 3,081 candidates, 20 labels, 11,898 vtable refs, 5,600 FUN-vtable-pool rows, 1,501 triage rows with a vtable family, 4,384 `unknown-vtable-impl` rows, and zero verified/runtime-validated functions.
- Dossiers: only `docs/analysis/dossiers/cell-movement.json` contains a non-empty vtable section. All 15 unknown-high dossiers have `vtables: []`; they remain accessor/field/decompilation dossiers, not vtable-family evidence.
- Decomp gaps: Sporepedia and Terrain projections preserve the `0x01490be8` identity contradiction; editor decomp-gap records preserve cEditor family evidence while warning that zero direct callers plus a vtable association is not unreachable evidence; UI-shell records preserve vtable associations without a unique family.

## Contradictions preserved

- **V-001:** vtables.json meta.functions=58756; canonical triage/xref closure=58757; live Ghidra manager count=59245. Resolution: Use 58757 as the frozen canonical denominator; preserve 58756 and 59245 as scope/snapshot drift.
- **V-002:** The candidate scan reports 3081 tables but only 20 labels; vtable confidence HIGH is table-structure confidence, not class identity confidence. Resolution: Report candidate versus identity confidence separately.
- **V-003:** 0x01485550 is App::cCellModeStrategy in vtables/dossier/current source, while decomp-gap/triage projections include it in an Editors::cEditor family due shared pointer runs. Resolution: Preserve both; do not infer a single class family from projection overlap.
- **V-004:** The cCellModeStrategy dossier lists AddRef as a member, but the raw table contains unnamed/non-function entries and repeated shared targets rather than a recovered AddRef symbol. Resolution: Treat AddRef as dossier/SDK evidence and keep raw slot targets unknown.
- **V-005:** Sporepedia decomp-gap projections associate 0x01490be8 with cSPAssetDataOTDB, while vtables.json labels it Terrain and includes Terrain::cTerrainSphere::GetSimDataRTT. Resolution: Preserve the contradiction; do not promote family or hierarchy.
- **V-006:** Some vtable members have zero direct caller counts while their vtable association is present. Resolution: Do not call them unreachable; virtual dispatch is not represented as a direct-call edge.
- **V-007:** Current source lifecycle mapping is described as one-to-one for ten named Cell-mode methods, while the original table has 27 slots and only ten named methods in the supplied SDK association. Resolution: Treat the current IGameMode as a partial clean-room contract, not a complete original ABI.
- **V-008:** Field offsets are observed or SDK-supported, but meanings such as lock/moving/camera semantics remain inferred or runtime-unvalidated. Resolution: Keep field offsets and semantic meanings in separate evidence fields.
- **V-009:** The global campaign has stale/variant category populations: 39716 triage-v6 UNKNOWN, 48296 in an older v5/v6 debt reference, and 35771 genuinely_unknown debt ownership. Resolution: Use the cited artifact population for each claim; do not combine denominators.
- **V-010:** No function-level runtime validation exists; cell-stage probes are negative in the recorded campaign. Resolution: No record is marked observed or verified at function-contract level.

## Open questions

- Resolve the unique identity of the 3048 unselected candidates and the 20 labeled UTFWin tables without relying on RTTI.
- Repair or independently validate candidate boundaries for SDK vtable slots that are currently data/interior addresses, especially 0x00e62700 and 0x01485550 slot 1.
- Recover exact constructor/destructor and ownership contracts for UTFWin allocator scaffolds, PropertyList, PFRecord, FormatParser, cEditor, and cToolStrategy families.
- Recover the exact vtable base/slot owner for the SpacePlayerData cached empire AddRef/Release calls.
- Disambiguate shared-prefix families such as cSPAssetDataOTDB versus UTFWin and Terrain versus Sporepedia projections.
- Establish whether cGameInputManager size/vtable field map corresponds to any of the 3081 candidate bases; the supplied field map alone does not.
- Obtain a positive Cell-stage runtime trace before promoting field meanings, lifecycle order, or current source behavior to observed/verified.

## Determinism and provenance

- No timestamps, randomness, live Ghidra calls, implementation changes, triage rewrites, or `SPORE/` writes are included.
- JSON keys and arrays are sorted; vtable records are ascending by numeric VA; addresses are lowercase eight-digit linked VAs.
- Primary source hashes are recorded in the JSON `provenance.source_manifest`. The complete dossier/decomp-gap paths are recorded in the JSON sections.
- Only `knowledgegraph/research/types/11-vtable-archaeology.json` and `.md` are outputs of this track.
