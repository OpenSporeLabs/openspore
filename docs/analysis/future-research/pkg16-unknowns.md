# PKG-16 Unknowns

Package: `PKG-16`  
Current status: `CHARACTERIZED_ONLY` / `NOT_IMPLEMENTED`  
Compatibility status: `ORIGINAL_COMPATIBLE` is not established.

## Scope and authorization

PKG-16 is characterized as a local metadata projection seam only. The authorized local surface is the smallest host contract that can be exercised without implementing a network, account, or external-service client:

- Project the complete PKG-03 `ResourceKey` without changing, completing, or wildcarding its type, group, or instance identity.
- Project `hasName` and the associated local name, if a name is available.
- Project `isEditable` as local metadata, not as permission to mutate the underlying resource.
- Project an optional asset identifier, preserving the distinction between an absent identifier and a present identifier.

This is a characterization of a future boundary. No PKG-16 host implementation, network client, protocol handler, service integration, or runtime adapter is authorized by this note.

## Local caller/resource dependency contract

A future local projection, if separately authorized and implemented, would be a caller-owned view over caller-supplied data:

1. The caller supplies a complete PKG-03 `ResourceKey` and a local metadata record or provider.
2. The caller supplies the resource/content dependency needed to resolve that key through an already-established local boundary. PKG-16 does not open packages, resolve directories, mount providers, or select a package priority.
3. The projection returns a bounded local view; it does not take ownership of the caller's resource, metadata record, provider, or key storage.
4. The caller keeps all borrowed inputs alive for the duration of the projection operation. The projected value must not expose dangling storage or silently copy an unbounded remote object.
5. The projection does not mutate the resource, publish an event, write a property, allocate a host/network handle, or register itself as a global service.
6. The optional asset identifier is metadata only. Its presence does not imply that the asset exists, is downloadable, is editable, or has been decoded.

The complete key is an identity, not a lookup wildcard. A future boundary should reject incomplete or wildcard keys rather than inventing a default group, instance, or type. Any package/database composition, cache policy, or multi-provider selection remains outside this package.

## Evidence boundary

The present evidence boundary is fixture-only and local:

- Committed synthetic fixtures may establish the shape of the local projection and deterministic boundary behavior.
- Static source analysis may establish the names and relationships of a caller or resource seam, but cannot establish original live behavior by itself.
- The evidence does not include a live original process, an authenticated account, a remote catalog, an original server trace, or a matched end-to-end request/response capture.
- A fixture proves only that the fixture can be projected by the characterized boundary. It does not prove that an original caller supplies the same fields, ordering, identity, or error.
- No `SPORE/` asset, service response, or proprietary runtime data is part of this characterization.

Evidence labels are therefore limited to local/host characterization. Fixture behavior must not be promoted to `BLUEPRINT_BACKED`, `EXISTING_OPENSPORE_BEHAVIOR`, or `ORIGINAL_COMPATIBLE` without a separately reviewable evidence record.

## No-network invariant

PKG-16 has a hard no-network invariant. The current and future disabled seam must not:

- resolve a hostname;
- open a socket, HTTP client, WebSocket, or other transport;
- perform DNS, proxy, or service discovery;
- contact an account, catalog, telemetry, update, or synchronization endpoint;
- retry, enqueue, cache, or authenticate a remote request;
- infer online behavior from an asset identifier, name, or editability bit.

No external-service credential, account, endpoint, response schema, or availability guarantee is assumed. A future implementation that violates this invariant is a different package and requires a new authorization and threat review.

## Optional disabled online seam

A future online seam may exist only as an explicitly disabled, non-operational boundary. It may document a possible producer/consumer relationship, but it must have no enabled implementation, transport dependency, implicit fallback, or runtime side effect. Its contract must make disabled/unavailable explicit rather than silently appearing to succeed.

The seam is not a claim that the original product had a network service. Before it could be enabled, the following would need separate evidence and authorization: the original caller identity, request/response or notification protocol, service ownership, authentication model, failure behavior, privacy boundary, and exact resource-selection semantics.

## Error semantics

The current status does not establish original error codes, messages, exception classes, retry behavior, or user-visible text. A future host boundary may define local, typed outcomes only after implementation authorization. At minimum, the characterization requires these cases to be distinct and testable:

- `invalid_resource_key`: missing type, group, or instance, or a wildcard where the local contract requires a complete key.
- `metadata_unavailable`: the requested local metadata cannot be read or is not supplied.
- `malformed_metadata`: the local record is structurally invalid.
- `unsupported_metadata`: a field, asset-ID representation, or operation is outside the local contract.
- `resource_unavailable`: the supplied local resource dependency cannot resolve the key.
- `internal_failure`: an unexpected local failure, without an assertion that the original system uses the same category.

The projection must not convert an unknown, absent, or unsupported remote value into a fabricated asset ID, name, editability state, or successful result. It must not perform network retries. Error mapping from PKG-03 or a provider remains the responsibility of the caller or a separately specified adapter.

## Known unknowns

### Caller identity

The original caller identity is unresolved. Static evidence may name a call site or interface but does not establish whether the caller is a user/profile, a player/session, a local application, a package manager, a content database, or another service. Authentication, authorization, tenant, profile, and session identity are also unresolved. The local projection must therefore accept caller-supplied metadata without claiming to authenticate or authorize the original caller.

### Resource identity and selection

The full original resource-selection process is unresolved, including package mounting, multi-package priority, directory resolution, caching, reload, eviction, and duplicate-key precedence. A complete PKG-03 `ResourceKey` in a fixture does not establish how the original system selected or materialized the resource.

### Metadata schema and lifecycle

The original field representation, optional-field sentinel, ordering, string encoding, editability policy, asset-ID namespace, ownership, update timing, and deletion lifecycle are unresolved. The local projection must document any host choice as a bounded host convention rather than an original invariant.

### Live and remote protocol

There is no established live or remote protocol for PKG-16. Unknowns include whether a protocol exists, its transport, request identity, resource key encoding, pagination, search, authorization, error response, versioning, caching, rate limits, retries, notifications, and server-side selection. No response, endpoint, or client compatibility may be inferred from the local fields.

### External-service assumptions

No external service is assumed to exist, be reachable, return stable data, or use the host's identity. Account, authentication, authorization, cloud storage, telemetry, updates, moderation, and synchronization are unsupported assumptions for PKG-16. The package must not add service discovery or fallback merely to make a missing result appear populated.

## Required evidence before `HOST_IMPLEMENTED`

This note cannot promote the package to `HOST_IMPLEMENTED`. A future implementation request must provide a separate design, implementation scope, and evidence package. Before changing status, it must add all of the following exact local checks:

1. **Projection fixture test:** a committed synthetic fixture containing a complete non-wildcard PKG-03 `ResourceKey`; assert exact type/group/instance preservation, `hasName`, name value when present, `isEditable`, and the optional asset-ID absent/present cases.
2. **Invalid-key tests:** reject each incomplete key component and each wildcard component without substituting defaults or performing a lookup with an incomplete identity.
3. **Optional-ID tests:** prove that absent, present, and malformed asset-ID cases remain distinct; no case creates an asset ID from zero, empty name, or remote lookup.
4. **Dependency/lifetime tests:** use caller-owned metadata and resource dependencies, including borrowed-input lifetime checks; assert that the projection does not own, close, mutate, or retain beyond the caller's dependency contract.
5. **Caller isolation test:** two callers with different supplied metadata but the same key must receive their supplied projections; no global caller, account, profile, or session state is consulted.
6. **Error tests:** cover `invalid_resource_key`, `metadata_unavailable`, `malformed_metadata`, `unsupported_metadata`, `resource_unavailable`, and `internal_failure`; assert no network retry or remote fallback.
7. **No-network test:** static/build checks and runtime fixture checks must demonstrate absence of DNS, sockets, HTTP/WebSocket clients, service discovery, proxy use, credentials, and remote retry paths. A disabled seam, if represented in API shape, must remain inert.
8. **Fixture-boundary test:** the test must run only from committed synthetic/local fixtures and must not read `SPORE/`, require a network, or depend on a live original service.
9. **Status/evidence record:** document the exact fixture hashes or revision, test command and results, supported host fields, unsupported fields, and the explicit absence of original-compatibility evidence.

Until all checks pass and the separate authorization is granted, the status must remain `CHARACTERIZED_ONLY` / `NOT_IMPLEMENTED`, with `ORIGINAL_COMPATIBLE` not established.
