# OpenSpore Implementation Dependency Graph

Direction: `from depends on to`. A hard edge is a semantic/interface prerequisite; soft means work can proceed independently and reconcile later; optional is compatibility/future fidelity; runtime-validation is an evidence gate for original behavior and not necessarily for a host-only minimum.

## Counts

- Hard: 37
- Optional: 2
- Runtime-Validation: 22
- Soft: 10

## Hard prerequisites

- ALL_SEMANTIC_PACKAGES -> PKG-00-EVIDENCE-VALIDATION
- PKG-01-SHARED-STATE-ROOTS -> ARCH-BLOCKER-A
- PKG-01-SHARED-STATE-ROOTS -> ARCH-BLOCKER-B
- PKG-01-SHARED-STATE-ROOTS -> PKG-00-EVIDENCE-VALIDATION
- PKG-02-APP-LIFECYCLE -> PKG-00-EVIDENCE-VALIDATION
- PKG-03-RESOURCE-IO -> PKG-00-EVIDENCE-VALIDATION
- PKG-04-ASSET-GEOMETRY-TEXTURE -> PKG-03-RESOURCE-IO
- PKG-05-CELL-CONTENT -> PKG-03-RESOURCE-IO
- PKG-06-CELL-STATE -> PKG-01-SHARED-STATE-ROOTS
- PKG-06-CELL-STATE -> PKG-05-CELL-CONTENT
- PKG-07-CELL-MOVEMENT -> PKG-01-SHARED-STATE-ROOTS
- PKG-07-CELL-MOVEMENT -> PKG-06-CELL-STATE
- PKG-08-CELL-MODE -> PKG-01-SHARED-STATE-ROOTS
- PKG-09-CELL-PRESENTATION -> PKG-03-RESOURCE-IO
- PKG-09-CELL-PRESENTATION -> PKG-04-ASSET-GEOMETRY-TEXTURE
- PKG-09-CELL-PRESENTATION -> PKG-05-CELL-CONTENT
- PKG-09-CELL-PRESENTATION -> PKG-08-CELL-MODE
- PKG-10-EDITOR-DISPATCH -> PKG-02-APP-LIFECYCLE
- PKG-11-SIM-CORE -> ARCH-BLOCKER-B
- PKG-11-SIM-CORE -> PKG-01-SHARED-STATE-ROOTS
- PKG-12-SIM-SPACE -> PKG-01-SHARED-STATE-ROOTS
- PKG-12-SIM-SPACE -> PKG-11-SIM-CORE
- PKG-12-SIM-SPACE -> PKG-14-TERRAIN-WORLD
- PKG-13-SIM-CREATURE-TRIBECIV -> PKG-01-SHARED-STATE-ROOTS
- PKG-13-SIM-CREATURE-TRIBECIV -> PKG-11-SIM-CORE
- PKG-13-SIM-CREATURE-TRIBECIV -> PKG-14-TERRAIN-WORLD
- PKG-14-TERRAIN-WORLD -> PKG-12-SIM-SPACE
- PKG-15-EDITOR-SUPPORT -> PKG-10-EDITOR-DISPATCH
- PKG-16-SPOREPEDIA-ONLINE -> PKG-03-RESOURCE-IO
- PKG-17-ANIMATION-SWARM -> PKG-05-CELL-CONTENT
- PKG-17-ANIMATION-SWARM -> PKG-09-CELL-PRESENTATION
- PKG-18-UI-SCRIPTING -> PKG-02-APP-LIFECYCLE
- PKG-18-UI-SCRIPTING -> PKG-03-RESOURCE-IO
- PKG-19-AUDIO-INPUT -> PKG-01-SHARED-STATE-ROOTS
- PKG-19-AUDIO-INPUT -> PKG-18-UI-SCRIPTING
- PKG-20-GAMEGLOBAL -> PKG-01-SHARED-STATE-ROOTS
- PKG-21-UNKNOWN-ROUTING -> PKG-00-EVIDENCE-VALIDATION

## Parallel implementation waves

### PAR-00

Join condition: Provenance and safety gates checked; no launch without approval.

- ORACLE-M0-PREPARATION
- PKG-00-EVIDENCE-VALIDATION

### PAR-01

Join condition: Evidence class and negative semantics preserved; no implementation promotion.

- M0-RUNTIME-CONTROL
- PKG-01-ROOT-CHARACTERIZATION
- PKG-03-PARSER-FIXTURES
- PKG-20-MAP-CHARACTERIZATION
- PKG-21-BOUNDED-ADJUDICATION

### PAR-02

Join condition: Record identity and fixture provenance stable.

- PKG-04-ASSET-GEOMETRY-TEXTURE
- PKG-05-CELL-CONTENT
- PKG-16-SPOREPEDIA-LOCAL-FIXTURE

### PAR-03

Join condition: Root and family boundaries frozen without collapsing modes/events/managers.

- PKG-06-CELL-STATE-HOST
- PKG-08-CELL-MODE-HOST
- PKG-10-EDITOR-STATIC
- PKG-11-SIM-CORE-LEAVES
- PKG-18-UI-STATIC

### PAR-04

Join condition: M0 positive or explicit post-negative decision; approval/display/Wine/lock gates satisfied.

- M1-CELL-REACHABILITY
- M5-MENU-TRANSITION
- M6-RENDERER-BOUNDARY

### PAR-05

Join condition: M1 positive; M2/M3/M4/M6 attributable or explicit negatives.

- PKG-07-CELL-MOVEMENT
- PKG-09-CELL-PRESENTATION
- PKG-17-CELL-ANIMATION

### PAR-06

Join condition: Root/manager characterization supports bounded function families and discriminators.

- PKG-12-SIM-SPACE-CHARACTERIZATION
- PKG-13-SIM-CREATURE-CHARACTERIZATION
- PKG-19-AUDIO-INPUT-CHARACTERIZATION

### PAR-07

Join condition: Concrete Space/editor/runtime dependencies identified; PKG-22 remains stub-only.

- PKG-14-TERRAIN-WORLD
- PKG-15-EDITOR-SUPPORT
- PKG-22-ON-DEMAND-STUBS

## Runtime validation gates

- ORACLE-AUDIO-INPUT
- ORACLE-CELL-PRESENTATION
- ORACLE-CREATURE-STAGE
- ORACLE-M0
- ORACLE-M1
- ORACLE-M2
- ORACLE-M3
- ORACLE-M4
- ORACLE-M5
- ORACLE-M6
- ORACLE-PROPERTY-ROUNDTRIP
- ORACLE-SPACE-STAGE
- ORACLE-SPOREPEDIA-ONLINE
- ORACLE-STAGE-PACKAGE
- ORACLE-UNKNOWN-PACKAGE

## Edge policy

- **hard:** Required semantic, ownership, interface, or fixture dependency.
- **optional:** Compatibility, migration, future fidelity, or out-of-scope boundary dependency.
- **runtime-validation:** Original or controlled-runtime evidence required for behavioral validation, not necessarily host-only implementation.
- **soft:** Independent work allowed, reconciled at the named interface before integrated fidelity.
