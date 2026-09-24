# Architecture Blocker Research — Noun/star root publication, equality, and teardown

Blocker: `BLOCKER-A`  
Status: `OPEN_ARCHITECTURE_BLOCKER_CLUSTER_A`

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

- Find publication, replacement, equality, and unpublication paths for DAT_0167eae0 and DAT_0167eb60.
- Determine whether noun roots are equal, phase-specific, stale, or opaque.
- Find publication and teardown paths for DAT_0167eae4 and DAT_0167eb0c.
- Confirm lower-bound, successor-tolerant cache, and independent erase behavior in lifecycle context.

## Expected observations

- Publisher matrix, pointer-equality window, and teardown trace.
- Mode-transition snapshots for both noun words, including unequal windows.
- Star-manager writer/rebind matrix and owner-lifetime trace.
- One cache miss/successor, one erase, and one teardown sequence without owner collapse.

## Decision criterion

Freeze a single owner/type only when the required observation set is complete. Otherwise retain the interim port, record the negative/unknown result, and do not reopen settled semantic boundaries.
## Affected packages

- PKG-01-SHARED-STATE-ROOTS
- PKG-02-APP-LIFECYCLE
- PKG-03-RESOURCE-IO
- PKG-08-CELL-MODE
- PKG-11-SIM-CORE
- PKG-12-SIM-SPACE
- PKG-13-SIM-CREATURE-TRIBECIV
- PKG-20-GAMEGLOBAL
- PKG-21-UNKNOWN-ROUTING

