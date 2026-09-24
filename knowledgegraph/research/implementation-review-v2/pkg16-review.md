# Independent implementation review v2 — PKG-16

**Scope reviewed:** current on-disk PKG-16 characterization `docs/analysis/future-research/pkg16-unknowns.md`, the package entry in `docs/analysis/reconstruction-blueprint.md`, PKG-03 `ResourceKey`/store boundary for dependency context, and the current repository search for Sporepedia/Pollinator implementations. No implementation, tests, CMake, runtime tooling, status docs, or canonical KG were modified.

## Evidence classification

- **HOST_IMPLEMENTED:** No PKG-16 host implementation is present. The current `src/editor/EditorSupport.*` files are assigned to PKG-15 by `docs/analysis/future-research/implementation-unknowns.md:53-59`, not PKG-16.
- **RUNTIME_VERIFIED:** None. `docs/analysis/future-research/pkg16-unknowns.md:31-41` correctly excludes live original process, account, remote catalog, server trace, and matched end-to-end evidence.
- **ORIGINAL_COMPATIBLE:** Not established. The characterization explicitly states this at `docs/analysis/future-research/pkg16-unknowns.md:3-5` and `:109-111`.
- **CHARACTERIZED_ONLY:** The local metadata projection surface, complete-key rule, no-network invariant, and future evidence checklist are documented at `docs/analysis/future-research/pkg16-unknowns.md:7-29,43-73,97-111`.

## Findings

### PKG16-01 — Important — confidence 96 — no PKG-16 implementation exists to review or promote

**Evidence:** The only new package-specific artifact is `docs/analysis/future-research/pkg16-unknowns.md`, which states `CHARACTERIZED_ONLY / NOT_IMPLEMENTED` at lines 3-5 and says no host implementation/network client/runtime adapter is authorized at lines 7-16. Repository search finds no `Sporepedia`, `cSPAssetDataOTDB`, `isEditable`, `hasName`, asset-ID, or network implementation under `src/`. The existing editor support is separately classified as PKG-15 at `docs/analysis/future-research/implementation-unknowns.md:53-59`.

**Finding:** PKG-16 is correctly pending, not implemented. The required future contract has no concrete host type, fixture, provider, or disabled seam to test yet.

**Impact:** There is no evidence for PKG-16 runtime behavior, caller identity, metadata ordering, error mapping, ownership, or no-network enforcement. Any status change to `HOST_IMPLEMENTED` or `ORIGINAL_COMPATIBLE` would be unsupported.

**Recommendation:** Keep the status `CHARACTERIZED_ONLY / NOT_IMPLEMENTED` until a separately authorized implementation supplies the exact local projection, complete `ResourceKey` identity tests, caller-supplied dependency/lifetime tests, error distinctions, and static/runtime no-network checks. Do not reuse PKG-15 editor support as PKG-16 evidence.

### PKG16-02 — Moderate — confidence 89 — blueprint wording can imply an unestablished local request/response protocol

**Evidence:** The PKG-16 blueprint describes runtime state as `cSPAssetDataOTDB and local request/response` at `docs/analysis/reconstruction-blueprint.md:826-832` and lists an online state path `online service not_initialized -> request -> response/failure unresolved` at line 844. The newer characterization explicitly says there is no established live or remote protocol and that request/response is unknown at `docs/analysis/future-research/pkg16-unknowns.md:89-95`.

**Finding:** The blueprint’s “local request/response” terminology is not clearly marked as a hypothetical caller seam and is stronger than the package evidence boundary permits.

**Impact:** A future implementer or status reviewer could infer a concrete local protocol, payload order, or response lifecycle that has not been observed, creating an unsupported architecture dependency.

**Recommendation:** Rewrite the blueprint as a candidate local projection seam with unresolved caller/event order, and explicitly state that no request/response protocol is established. Keep the no-network invariant attached to both the blueprint and the characterization.

### PKG16-03 — Moderate — confidence 88 — future test matrix is specified but not instantiated

**Evidence:** The characterization requires tests for incomplete/wildcard keys, absent/present/malformed asset IDs, caller isolation, six error categories, no-network behavior, and fixture boundaries at `docs/analysis/future-research/pkg16-unknowns.md:97-109`. The PKG-03 `ResourceKey` has a host tuple and wildcard completion check at `src/assets/ResourceKey.hpp:8-18`, but no PKG-16 fixture or projection test exists.

**Finding:** The required evidence is correctly identified but remains a checklist, not an executable test surface.

**Impact:** Future implementation could accidentally use an incomplete key as a lookup wildcard, fabricate an absent asset ID, retain caller-owned metadata, or add a fallback path without a regression test catching it. The current status correctly prevents claiming these behaviors.

**Recommendation:** When implementation is authorized, add a dedicated local fixture suite before any status promotion. Include static no-network checks and runtime fixture checks; keep all remote/service fields explicitly absent.

## Review disposition

**Pending review / characterized only.** There is no PKG-16 host implementation to assess for ownership, ordering, or coupling. The current documentation is directionally conservative, but the blueprint wording should be aligned with the explicit no-protocol/no-network boundary before downstream work relies on it.
