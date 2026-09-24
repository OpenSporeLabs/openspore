# Track 6 — Opaque Forwarded State

**Conflict:** `CONFLICT-OPAQUE-FORWARDED-STATE`  
**Targets:** `0x00b5b800`, `0x00b3d320`, `DAT_0167eaec`, `receiver+0x20`, `0x00a42730`, `0xffffffff`, `0x01654c00..0x01654c06`  
**Status:** partial static resolution; identity, publication, and lifecycle deferred  
**Method:** read-only Ghidra queries against explicit program `SporeApp.exe`; follow-up 02 incorporated; no runtime, mutation, implementation, or historical-file edits.

## Verdict and taxonomy

`0x00b5b800` is a null-safe two-level forwarding read:

```text
0x00b3d320 -> DAT_0167eaec
0x00b5b800 -> source word == 0 ? 0xffffffff : [source word+0x20] via 0x00a42730
```

The receiver is borrowed/read-only only during the field read. The returned value is a `uint32` copied by value into EAX; no ownership transfer or retained reference occurs. Static evidence does not establish semantic freshness, when the source word was written, or whether it is published.

**Allowed classification taxonomy:** `required_for_semantics`, `runtime_compatibility_only`, `replaceable_infrastructure`, `unknown`.  
**Top-level classification:** `unknown`.

The safe contract is an opaque by-value read result, not an established object pointer, mode ID, strategy pointer, or enum.

## Nine-step record

| Step | Test | Result |
|---|---|---|
| 1. Mechanism | Is the body an observed forwarding read? | `0x00b3d320` loads `DAT_0167eaec`; `0x00a42730` is `[ECX+0x20]`; `0x00b5b800` returns `0xffffffff` on zero. |
| 2. Normal pointer result | Does EAX behave as a dereferenceable pointer? | 843 direct callsites, 0 observed strict pointer dereferences; 6 apparent pointer-like cases are normalization/indexing and 7 remain bounded-ambiguous. |
| 3. Opaque state/handle | Is the result used as a by-value token? | 829 scalar compare/branch/copy/pass sites, 6 normalization sites, and 1 return-only site support a bounded opaque contract. |
| 4. Mode/manager alias | Is it a current mode ID or manager field? | Not established: `DAT_0167eaec` is distinct from the named simulator/input/mode slots, with no matching owner store or dataflow. |
| 5. Strategy identity | Is `+0x20` an `ISimulatorStrategy`/interface identity? | Not established: it is a plain field load, not a vtable load; no owner, constructor, strategy call, AddRef, or Release is connected. |
| 6. Sentinel scope | Which requested tokens are evidenced? | Whole-program exact counts: C00=66, C01=147, C02=153, C03=0, C04=167, C05=329, C06=20. Direct b5 comparisons: C00=27, C01=89, C02=89, C03=0, C04=110, C05=260, C06=2. C03 is unknown, not proven impossible. |
| 7. First writer/publication | Can allocation, publication, or teardown be recovered? | Direct xref, address-operand, byte-pattern, memory, and global-audit surfaces find one read only; no direct writer, constructor, allocation, `+0x20` writer, clear, replacement, publication, or teardown chain. Indirect/bulk publication remains possible. |
| 8. Downstream ownership | Does the returned uint32 own or identify the downstream object? | No. `0x00ad12a0` uses it as a C04 discriminator while updating a separate object; `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0`, and `0x00c099e0` use separate downstream paths. |
| 9. Architecture dependence | What can be frozen without inventing identity? | Freeze only raw by-value `uint32` read semantics, `0xffffffff` for a zero source word, receiver-borrowed-during-read, and explicit unknown freshness/publication. Defer stronger types and lifecycle claims. |

## First-writer and publication search

The read-only Ghidra separator for `DAT_0167eaec` found:

- one direct xref, `0x00b3d320:0x00b3d321`, type `READ`;
- no xrefs from the slot;
- one exact little-endian address-byte hit, `0x00b3d321`, belonging to the read;
- loaded memory around `0x0167eaec` zero, which is not a runtime observation;
- `undefined4`, untyped global audit with one xref;
- no statically connected constructor, allocation, first `+0x20` writer, clear, replacement, publication, or teardown.

This is a complete negative within the stated direct Ghidra surface, not proof that computed, address-taken, bulk, or runtime-populated publication is impossible. The smallest remaining separator is computed/address-taken provenance to `DAT_0167eaec`, followed by the first `[receiver+0x20]` write and its clear/replacement/teardown path.

## Caller-use census

The follow-up full-listing flow scan covered 843 direct call instructions and 460 unique flow identities; the function-call endpoint returned 459 function records.

| Bounded class | Count |
|---|---:|
| Scalar compare/branch/copy/pass | 829 |
| Apparent pointer-like cases manually reclassified as normalization/indexing | 6 |
| Return-only | 1 |
| Ambiguous within the 24-instruction window | 7 |
| **Strict pointer dereference observed** | **0** |

The defensible bound is 0 observed and 7 unresolved. Deeper branch, phi, and stack propagation is not claimed. The six apparent cases use range checks, switch normalization, LEA/index arithmetic, or table indexing rather than dereferencing the returned word as a pointer.

## Exact observed tokens

The only evidenced requested comparison tokens are:

```text
C00=0x01654c00
C01=0x01654c01
C02=0x01654c02
C04=0x01654c04
C05=0x01654c05
C06=0x01654c06
```

C03 has no exact scalar operand, exact byte pattern, or direct b5 comparison evidence and remains **unknown**. Equivalent arithmetic or range coverage cannot be excluded. `0x01654c10` and `0x02ccd1d2` are also compared outside the requested range, so C00..C06 is not a complete proven 32-bit domain.

## Ownership and lifetime

The root path performs only `read global`, `null test`, `read [ECX+0x20]`, and `copy to EAX`. It performs no allocation, mutation, lock, `AddRef`, `Release`, retention, or ownership transfer. The receiver is borrowed only while the field is read. The returned `uint32` is held by value after return, but its semantic freshness, publication state, and source replacement timing are unknown.

## Safe interface freeze

```text
std::uint32_t read_forwarded_state();
```

Freeze these semantics:

- no arguments;
- return the raw 32-bit value copied by value from receiver `+0x20` when the source word is nonzero;
- return exactly `0xffffffff` when the source word is zero;
- borrow the receiver only for the read; do not expose, retain, or claim it is published;
- keep only evidenced C00/C01/C02/C04/C05/C06 as distinct comparison tokens;
- keep C03 unknown;
- perform no allocation, mutation, lock, retention, or release;
- keep input/mode manager accessors and downstream gameplay objects separate;
- make semantic freshness and publication explicit as unknown.

Defer concrete receiver class, physical `+0x20` type, first writer, allocation, publication, freshness guarantee, replacement, teardown, C03 semantics, runtime reachability, and mode/strategy identity.

## Blockers and limitations

- No indirect first-writer, constructor, allocation, publication, freshness, replacement, or teardown trace is available.
- Seven direct callsites remain ambiguous within the bounded analysis window.
- C03 is not evidenced, but equivalent arithmetic cannot be excluded.
- No original-process runtime trace was used.
- No source, implementation, Ghidra state, or historical artifact was modified.

## Citations

- Ghidra read-only `SporeApp.exe`: `0x00b5b800`, `0x00b3d320`, `0x00a42730`, `0x0167eaec`, `0x00ad12a0`, `0x00d2e4a0`, `0x00d2e580`, `0x00d2e8a0`, `0x00c099e0`.
- `knowledgegraph/research/architecture-resolution/followup-02-forwarded-state.json:37-163,200-227,229-377`.
- `knowledgegraph/research/architecture-resolution/followup-02-forwarded-state.md:6-96,98-172`.
- `knowledgegraph/research/root-closure/track-b-strategy-handle.json:57-148,150-175,280-380`.
- `docs/analysis/conflict-adjudication.md:108-114,207-227`.
- `docs/analysis/simulator-shared-state-interface.md:66-79,217-225,266-279`.
