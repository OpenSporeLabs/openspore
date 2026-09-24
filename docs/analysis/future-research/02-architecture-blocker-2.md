# Architecture Blocker Research — DAT_0167eaec/0x00b5b800 first writer, physical state identity, freshness, and downstream ownership

Blocker: `BLOCKER-B`  
Status: `OPEN_ARCHITECTURE_BLOCKER_CLUSTER_B`

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

- Find the first writer, clearer, and receiver construction path for DAT_0167eaec.
- Determine physical storage and ownership of forwarded receiver+0x20.
- Relate C00, C01, C02, C04, C05, C06, unknown C03, and 0xffffffff without inventing an enum.
- Characterize publication freshness and downstream ownership across one mode transition and teardown.

## Expected observations

- Publisher/lifecycle table for initialization, replacement, clear, and teardown.
- Defining store, all clear/release paths, and consumer dereference or retention.
- Producer-to-consumer traces and a negative C03 case.
- Source, forwarded field, consumers, and owner-lifetime snapshots.

## Decision criterion

Freeze a single owner/type only when the required observation set is complete. Otherwise retain the interim port, record the negative/unknown result, and do not reopen settled semantic boundaries.
## Affected packages

- PKG-01-SHARED-STATE-ROOTS
- PKG-02-APP-LIFECYCLE
- PKG-05-CELL-CONTENT
- PKG-06-CELL-STATE
- PKG-08-CELL-MODE
- PKG-11-SIM-CORE
- PKG-18-UI-SCRIPTING
- PKG-19-AUDIO-INPUT
- PKG-21-UNKNOWN-ROUTING

