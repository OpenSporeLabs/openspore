# Empire, Space, Player, Diplomacy, Trade, Mission, and Progression Archaeology

- **Partition:** `05-empire-space`
- **Status:** research only; no implementation, runtime trace, Ghidra mutation, knowledge-graph mutation, or `SPORE/` write
- **Binary:** `SporeApp.exe` 3.1.0.22, x86:LE:32, image base `0x00400000`
- **Binary SHA-256:** `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`
- **Analysis snapshot:** `f0e310e0`, 58,757 functions
- **Live Ghidra state:** no open programs; this partition uses committed exports only

This is a static archaeology partition. SDK names and layouts are evidence, not authoritative gameplay semantics. No empire, space, diplomacy, trade, or economy transition is runtime-observed: the committed S5 Wine result is negative for reaching Cell Stage.

## Evidence policy

The evidence scale is `UNKNOWN < APPROXIMATION < INFERRED < SUPPORTED < OBSERVED < CONFIRMED < VERIFIED`. Confidence is confidence in the bounded static contract, not confidence in undocumented gameplay behavior. The source precedence is pinned binary/runtime artifacts, committed Ghidra/SDK/vtable/xref exports, triage-v6/read-only KG projections, existing dossiers, and current OpenSpore code.

Clean-room boundary: addresses, names, field layouts, and behavioral summaries are evidence only. No proprietary source or assets are copied into OpenSpore.

## Static spine

The strongest reconstruction spine is:

```text
simulator manager accessors
  -> SpacePlayerData cached player/empire state
  -> cEmpire identity, politics, home system, money, and species profile
  -> cStarManager galaxy/star database and generation
      -> cStarRecord
          -> cPlanetRecord
              -> cCivData, cTribeData, cCommodityNodeData
  -> cRelationshipManager
  -> cSpaceTrading
  -> cMissionManager
      -> cMission
  -> cCommManager
      -> cCommEvent
  -> cSimulatorSpaceGame
      -> cPlayerInventory
          -> cSpaceInventoryItem
          -> cSpaceToolData
      -> cSimulatorPlayerUFO
          -> cGameDataUFO
      -> cMissionManager
```

The singleton accessors are central but incompletely characterized. Confirmed roots include `cStarManager::Get` at `0x00b3d3a0`, `cRelationshipManager::Get` at `0x00b3d3c0`, `cSpaceTrading::Get` at `0x00b3d4d0`, `cMissionManager::Get` at `0x00feb770`, and `cSimulatorSpaceGame::Get` at `0x010027b0`. The packed accessor block also contains high-fan-in addresses whose owner types are not safely assignable to one of these managers.

## Type and layout summary

| Type | Size | Role | Evidence |
|---|---:|---|---|
| `cEmpire` | 344 | political identity, home star/planet, species, culture, money, enemies/allies | `CONFIRMED`, 0.90 |
| `cPlayer` | 4,824 | refcounted game-data player and message listener | `SUPPORTED`, 0.76 |
| `cPlayerInventory` | 152 | inventory, unlockable tools, active tool/cargo pointers | `SUPPORTED`, 0.84 |
| `cSpaceInventoryItem` | 124 | count/cost/type, item identity, descriptions, property list | `SUPPORTED`, 0.86 |
| `cSpaceToolData` | 672 | derived tool, projectile, weapon, recharge, and effect state | `SUPPORTED`, 0.79 |
| `cGameDataUFO` | 2,072 | spacecraft game-data and energy state | `SUPPORTED`, 0.75 |
| `cVehicle` | 3,480 | large locomotive/game-data vehicle state | `SUPPORTED`, 0.75 |
| `cSimulatorPlayerUFO` | 224 | player-UFO wrapper, scan and range state | `SUPPORTED`, 0.78 |
| `cSimulatorSpaceGame` | 240 | active space-game composition root | `SUPPORTED`, 0.84 |
| `SpacePlayerData` | 52 | shared player/empire/planet/relationship context | `CONFIRMED`, 0.92 |
| `cStarManager` | 556 | star database, generation, empire registry, trade-route and relationship roots | `CONFIRMED`, 0.91 |
| `cStarRecord` | 176 | serializable star, owner, species, and planet record | `SUPPORTED`, 0.87 |
| `cPlanetRecord` | 432 | planet scores, orbit, species, civ/tribe/commodity records | `SUPPORTED`, 0.85 |
| `cCivilization` | 1,240 | large civilization game-data object | `SUPPORTED`, 0.70 |
| `cTribe` | 6,624 | tribe politics, population, food, tools, plans, and position | `SUPPORTED`, 0.79 |
| `cRelationshipManager` | 256 | ordered political-ID relationship table and event state | `SUPPORTED`, 0.88 |
| `cSpaceTrading` | 248 | spices, rares, NPC stores, and newly available commodities | `SUPPORTED`, 0.84 |
| `cCommodityNode` | 656 | resource depletion, ownership, capture, conversion, and purchase state | `SUPPORTED`, 0.82 |
| `cMission` | 496 | mission state, rewards, costs, clues, targets, and callbacks | `SUPPORTED`, 0.86 |
| `cMissionManager` | 324 | tracked missions, recent missions, configuration, and limits | `SUPPORTED`, 0.84 |
| `cCommManager` | 100 | communication current event, queue, and cancellation map | `SUPPORTED`, 0.80 |

### `cEmpire`

`cEmpire` begins with `ISimulatorSerializable`, `RefCountTemplate`, and `cIdentityColorable` vtable pointers. Important fields are `mIDColorID` at `0x10`, `mCachedColor` at `0x30`, `mEmpireName` at `0x3c`, `mPoliticalID` at `0x84`, `mStars` at `0x88`, home star/planet at `0xb0/0xb4`, UFO/captain ResourceKeys at `0xb8/0xc4`, `mEmpireMoney` at `0xd0`, and `mAdventureList` at `0x148`.

The money field is confirmed as a field, but no balance formula or payout rule is claimed. The enemy/allied vectors and political ID are strong static structure, not proof of a complete economic simulation.

### `SpacePlayerData`

The 52-byte shared player state is:

| Offset | Field | Type |
|---:|---|---|
| `0x00` | `mMillisecondsSinceLastUpdate` | `int` |
| `0x04` | `mpActivePlanet` | `intrusive_ptr<cPlanet>` |
| `0x08` | `mpActiveStar` | `intrusive_ptr<cStar>` |
| `0x0c` | `mpTribeCivRelationships` | `intrusive_ptr<cRelationshipManager>` |
| `0x10` | `mCurrentContext` | `SpaceContext` |
| `0x14` | `mfRotationRateFactor` | `float` |
| `0x18` | `mPlayerEmpireID` | `uint32_t` |
| `0x1c` | `mpPlayerEmpire` | `intrusive_ptr<cEmpire>` |
| `0x20` | `mPlayerColonies` | `vector<intrusive_ptr<cPlanet>>` |

Accessor evidence:

- `0x01021080` reads `+0x10`.
- `0x01021260` reads `+0x04` with a null guard.
- `0x01021300` validates `mPlayerEmpireID` against the cached `mpPlayerEmpire`; on mismatch it re-resolves the empire and releases the old object through the vtable release slot.

This is a cached identity/ownership seam. It should not be modeled as an ordinary owning `cPlayer` field without preserving the manager-registry relationship.

### Galaxy and planet records

`cStarManager` holds a star-record grid, starter/saved/black-hole/possible-start vectors, an empire-home-star map, an empire map, name registry, adventure map, trade-route manager, relationship-manager pointer, transaction log, collectables, and planet-record databases. It also contains generation controls and `mNextPoliticalID`.

`cStarRecord` is serializable and refcounted. It stores saved-game version/time data, position, star type, tech level, empire ID, starter-world ID, flags, name, key, citizen species, species profile, and intrusive planet records.

`cPlanetRecord` stores planet type/orbit, atmosphere/temperature/water scores, plant/animal species, commodity nodes, civ/tribe data, tech level, spice generation, and generated terrain key. The schema is strong enough for data-first reconstruction, but generation formulas and persistence order remain unresolved.

### Inventory, tools, UFOs, and vehicles

`cPlayerInventory` owns vectors of inventory items and unlockable tools and separately tracks the drop-cargo tool, active tool, and active cargo item. `cSpaceInventoryItem` contains item count, type, cost, uniqueness, political ID, position, property list, localized descriptions, item ResourceKey, and message pointers. `cSpaceToolData` derives from the inventory-item shape and adds ammunition, recharge, projectile, damage, target, effect, relationship-delta, reward, and environmental fields.

`cSimulatorSpaceGame` composes the active UI, player inventory, player-UFO wrapper, mission manager, NPC UFOs, message-listener data, and planets-to-uplift. `cSimulatorPlayerUFO` owns a `cGameDataUFO`; `cGameDataUFO::ChangeEnergy` is a confirmed named consumer. `cVehicle` is a separate large locomotive/game-data object and is not a substitute for the space-game inventory model.

### Diplomacy

`cRelationshipManager` is keyed by ordered political-ID pairs. `cRelationshipData` stores a float value, flags, and a relationship-event map. Static bodies support the following flag contract:

- bit 0: at war;
- bit 1: allied.

`DeclareWar` sets bit 0 and clears bit 1 for the applicable directed entries. `DeclareAlliance` follows the peace path and then sets bit 1. `DeclarePeace` clears bit 0. `BreakAlliance` clears bit 1. Message and economy side effects are observed as calls, but their numeric payloads and exact ordering are not named.

### Trading and commodities

`cSpaceTrading` holds spice vectors, a five-slot NPC-store fixed vector, rare-resource map, rare groups, store index, and newly available commodities. Named consumers include `IsRare`, `GetRareHasBeenFound`, `AssignPlanetSpice`, `GenerateNPCStore`, `SetRareAsFound`, and `ObtainTradingObject`.

`cCommodityNode` stores resource points, maximum points, constructing/capture/convert/buy political IDs, and capture/convert/buy percentages. The layouts establish the economy seam but not the formulas.

### Missions and communication

`cMission` carries owner/target empire IDs and pointers, source/target planets, reward money/tool, unlock tools, clue data, progress event ID, costs, accept rewards, communication event, and target planet. Known states are `Unaccepted=0`, `Finished=1`, `Accepted=2`, `Active=3`, `Completed=5`, `Failed=6`, `Aborted=7`, `Rejected=8`, and `StepCompleted=9`.

`cMissionManager` stores tutorial state, generator/config PropertyLists, tracked missions, recent NPC/colony mission lists, mission limits, and teaching mission vectors. The mission vtable includes `Write`, `Read`, `WriteToXML`, accept/reject/abort/completed/failed callbacks, state access, cargo checks, clue creation, message-listener management, and mission-duration calculation.

`cCommManager` owns the current communication event, event vector, and cancellation-condition map. A targeted read at `0x00aeb720` matches a create-and-dispatch space-event wrapper that allocates a `0xa0` event and forwards it to the display/dispatch path. Triage labels the same address `HandleSpaceCommAction`; that identity is contested and is not promoted.

## Vtable families

- `cMission__vftable`: 408 bytes; refcount/dtor, serialization, mission callbacks, state, clues, cargo, listeners, and duration slots.
- `cSpaceInventoryItem__vftable`: 80 bytes; refcount, item identity/type, cargo/duplicate, descriptions, images, count, availability, and `ParseProp`.
- `PlayerPlanetData__vftable`, `cSpacePlayerWarData__vftable`, and `cSpaceTradeRouteManager__vftable`: 12 bytes each; destructor plus `Write`/`Read`.
- `cEmpire`, `cStarManager`, `cSpaceTrading`, `cRelationshipManager`, `cMissionManager`, `cSimulatorSpaceGame`, and `cSimulatorPlayerUFO` expose multiple adjacent vtable pointers. These are SDK/static-layout relations, not RTTI-backed C++ hierarchy proofs.

## Ownership and lifecycle

- `cStarManager` owns or indexes star records, empires, home stars, relationship state, trade routes, and planet databases.
- `cEmpire` is refcounted and holds intrusive enemy/allied/star vectors; it is cached by `SpacePlayerData` by political ID.
- `cStarRecord` is refcounted/serializable and owns intrusive planet-record references.
- `cPlanetRecord` embeds or references civ, tribe, and commodity data records.
- `cSimulatorSpaceGame` composes the active player inventory, player-UFO wrapper, mission manager, UI, NPC UFOs, and uplift list.
- `cPlayerInventory` owns item/tool vectors and separately tracks active pointers.
- `cMissionManager` owns tracked mission intrusive pointers and recent mission lists.
- `cCommManager` owns queued `cCommEvent` intrusive pointers.
- The exact manager singleton setters/reset behavior and the full owner of the packed shared-state accessor block remain unresolved.

## Serialization

The shared `PropertyList` spine is visible at:

- `0x006a2f60` — `Read`;
- `0x006a1540` — `Write`;
- `0x006a2530` — `GetProperty`;
- `0x006a2e20` — `SetProperty`.

Serializable or property-backed surfaces include `cEmpire`, `cStarRecord`, `cMission`, `cMissionManager`, `cSpaceInventoryItem`, `PlayerPlanetData`, `cSpacePlayerWarData`, and `cSpaceTradeRouteManager`. Exact property sets are not recovered. The inventory constructor/refresh path observes property IDs `0x3068d95d`, `0x04cad19b`, and `0x1bfc1dee`; the factory observes `0x037d494e`; trading routines observe `0x034d97fa`, `0x034f1a4f`, `0x036801e8`, `0x036801e9`, `0x068b657b`, `0x068b657d`, and `0x068b657e`. These IDs are not semantically named.

No original property fixture or runtime serialization round trip exists in the committed evidence.

## Reconstruction order

1. Characterize and name the simulator manager roots, setters, and reset/persistence boundary.
2. Freeze `cEmpire`, `cStarRecord`, `cPlanetRecord`, `cMission`, and `cSpaceTrading` field and serialization relationships.
3. Recover relationship event/message payloads and the `cSpaceTrading` property dictionary.
4. Recover inventory insertion/removal, cargo, trade, and mission reward transitions.
5. Recover star/planet/civilization generation and persistence.
6. Create a gated original runtime trace only after the static contracts are stable.

## Disagreements and limits

- Committed decomp-gap accounting says unavailable; targeted read-only review returned complete bodies. The committed state is preserved and no new persisted decomp coverage is claimed.
- `0x00aeb720` is triage-associated with `HandleSpaceCommAction` but behaves as a create/dispatch wrapper; the SDK identity remains contested.
- The `cSpaceInventoryItem` slot `+0x4c` is SDK-labeled `IsAvailableInCurrentPlanet`, but candidate vtable `0x01473558` points to an interior target; runtime slot meaning is not promoted.
- The runtime 12-color identity palette is not captured.
- The 27-field and 24-field space event records are inferred from builders, not verified named types.
- No MSVC RTTI exists; adjacent vtable pointers are structural evidence only.
- No runtime transition, economy formula, balance rule, message payload, or serialization round trip is verified.

## Open questions

- What exact owners and types are behind the unnamed high-fan-in simulator accessors?
- What initializes the identity palette and manager state?
- How are star/planet/civilization records generated and persisted?
- What are the economy, cargo, rare-resource, store, and route formulas?
- Which functions mutate empire money, mission rewards, and inventory counts?
- What are the numeric names and payload layouts of relationship, civ, and space messages?
- What drives each mission-state transition and reward payout?
- What is the complete `cTradeRouteData` format?
- Can a future original trace reach space or empire stages?

## Sources

- `knowledgegraph/research/types/05-empire-space.json`
- `knowledgegraph/research/global-campaign-2026/track-f-empire-economy.json`
- `knowledgegraph/research/decomp-gap/sim-space-00.json`
- `.spore-analysis/ghidra-exports/structs.tsv`
- `.spore-analysis/ghidra-exports/structs_fields.tsv`
- `.spore-analysis/ghidra-exports/spore_sdk.xml`
- `.spore-analysis/ghidra-exports/functions.tsv`
- `docs/analysis/vtables.json`
- `knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl`
- `knowledgegraph/triage/xrefs-2540f2ca.summary.json`
- `docs/analysis/dossiers/unknown-high/space-player-data-accessors.md`
- `docs/analysis/dossiers/unknown-high/space-player-data-accessors-2.md`
- `docs/analysis/dossiers/unknown-high/space-player-data-accessors-3.md`
- `docs/analysis/dossiers/unknown-high/space-event-record-pair.md`
- `docs/analysis/dossiers/unknown-high/empire-idcolor-pick.md`
- `docs/analysis/dossiers/unknown-high/gamemode-state-player-id.md`
- `docs/RECON-3.1.0.22.md`
