# Architecture Blocker Research — Persistence object/reference/restore graph and mode-handoff boundary

Blocker: `BLOCKER-C`  
Status: `OPEN_ARCHITECTURE_BLOCKER_CLUSTER_C`

## Exact question

How can the blocker be resolved without collapsing unresolved owners or promoting an opaque value?

## Competing hypotheses

- The current safe interim boundary is sufficient for implementation but not for original compatibility.
- The unresolved identity is a distinct owner/lifetime and changes architecture.
- The apparent identity is an alias or stale value and can be replaced by an explicit invalidation contract.

## Evidence currently available

- Pinned direct mechanics and bounded static xrefs exist for the involved functions/slots.
- No positive original lifecycle trace establishes publication, equality, or teardown.
- The affected package boundary is already represented as interim-safe and unresolved.

## Smallest useful investigation

- Recover ClassSerializer Read/Write bodies, object-table encoding, cycles, and deferred association.
- Recover the outer PROP/.spo envelope, database record, checksum or compression placement, and boundaries.
- Map cCellSerializableData and cSavedGameHeader field emission, restoration, and survival.
- Determine whether Cell mode handoff shares live state or transfers a DTO.
- Characterize cross-file commit, rollback, and recovery boundaries.
- Confirm or reject cGamePersistenceManager membership for 0x00b28ec0 and 0x00b279e0.

## Expected observations

- In-memory round trip plus cycle or failing-stream branch tied to exact bytes.
- Byte fixture spanning stream open through finalization and reopen.
- Field-by-field matrix across a mode handoff.
- Owner and reference-transfer trace across create, handoff, reload, and teardown.
- Successful multi-artifact replacement and interrupted/failing replacement trace.
- Concrete vtable/this-binding or service-routing evidence.

## Decision criterion

Freeze a single owner/type only when the required observation set is complete. Otherwise retain the interim port, record the negative/unknown result, and do not reopen settled semantic boundaries.
## Affected packages

- PKG-03-PROPERTY-CONFIG
- PKG-03-RESOURCE-IO
- PKG-05-CELL-CONTENT
- PKG-08-CELL-MODE
- PKG-11-PERSISTENCE
- PKG-11-SIM-CORE
- PKG-12-SIM-SPACE
- PKG-13-SIM-CREATURE-TRIBECIV
- PKG-14-CROSS-MODE-OBJECT
- PKG-20-GAMEGLOBAL

