# Follow-up 02 — Forwarded State at `0x00b5b800`

**Program:** `SporeApp.exe`  
**Scope:** read-only static Ghidra observation; no mutation, runtime, `SPORE/`, `spore.db`, implementation, or historical edits.

## Verdict

`0x00b5b800` is a null-safe two-level forwarding read:

```text
0x00b3d320 -> DAT_0167eaec
0x00b5b800 -> receiver == 0 ? 0xffffffff : [receiver+0x20]
0x00a42730 -> MOV EAX,[ECX+0x20]; RET
```

The returned word is mechanically a raw 32-bit value. Its physical meaning, receiver type, allocation, publication, first `+0x20` writer, and teardown remain unresolved. The bounded static contract is an opaque uint32-sized borrowed read-through value, not an established object pointer, mode ID, or strategy pointer.

## Direct writers and publication

| Query | Static result |
|---|---|
| `get_xrefs_to(0x0167eaec)` | One `READ` at `0x00b3d320` |
| `get_xrefs_from(0x0167eaec)` | None |
| Full instruction address-operand scan | One absolute read at `0x00b3d320`; no absolute write |
| Exact little-endian address-byte search | One hit at `0x00b3d321`, the operand bytes of that read |
| Global audit | `DAT_0167eaec`, `undefined4`, 4 bytes, untyped, one xref |
| Loaded memory | `0x0167eae0..0x0167eaff` queried range is zero, including the target slot |

**Direct writers:** none recovered.  
**Indirect/bulk publication:** no site statically recovered; computed, address-taken, bulk, or runtime-populated publication remains possible.  
**Constructor/allocation/clear/teardown:** no chain connected to the slot.

Adjacent accessor slots are distinct: `0x00b3d300` reads `DAT_0167eae0`, `0x00b3d310` reads `DAT_0167eae8`, `0x00b3d330` reads `DAT_0167eaf0` (`cSimulatorSystem::Get`), and `0x00b3d350` reads `DAT_0167eaf8` (`cGameInputManager::Get`). Adjacency does not prove aliasing or ownership.

## Receiver and `+0x20`

- Receiver storage: `DAT_0167eaec`, writable `.data`, 4 bytes, aligned, Ghidra type `undefined4`.
- Loaded value: zero in the queried Ghidra image; this is not a runtime observation.
- Allocation/type/owner: unresolved.
- `0x00a42730` proves only a 4-byte field load from `receiver+0x20`; it is not a vtable load.
- First writer of `receiver+0x20`: not recovered.
- Clear/replacement/teardown: not recovered.
- The root performs only global read, null test, and field read; it performs no allocation, mutation, lock, AddRef, Release, retention, or ownership transfer.

## Direct callers and pointer use

A read-only full-listing flow scan found:

- **843** direct call instructions to `0x00b5b800`.
- **460** unique caller identities in the instruction-flow inventory; the function-call endpoint returned **459** function records.

A conservative 24-instruction live-`EAX` alias check, followed by manual review, found:

| Bounded class | Count |
|---|---:|
| Scalar compare/branch/copy/pass | 829 |
| Apparent pointer-like patterns manually reclassified as switch/index normalization | 6 |
| Return-only | 1 |
| Ambiguous within the bounded window | 7 |
| **Strict pointer dereference observed** | **0** |

The six apparent cases use `LEA`, range checks, or table-index normalization rather than dereferencing the returned word as a pointer. Examples are `0x00c0b273`, `0x00c0b2f0`, `0x00e02062`, and `0x00e19dd3`. The defensible bound is **0 observed, 7 unresolved** by this method; deeper branch/phi/stack propagation is not claimed.

Independent selected consumers support scalar gating:

- `0x00ad12a0`: compares the result with `0x01654c04`; the later `+0x5fc` write targets a separately obtained object.
- `0x00b3d2c0`: dispatches on the result, including C02/C04/C05 and other values; its later path uses a separate global flow.
- `0x00d2e4a0`: compares with `0x01654c01`, then obtains and dispatches a separate object.
- `0x00d2e580` and `0x00d2e8a0`: compare with `0x01654c10`, then operate on separately obtained objects.
- `0x00c099e0`: compares with `0x01654c01`/`0x01654c02` before separate editor/object operations.

## Exact token observations

### Whole-program exact scalar/byte census

| Token | Value | Exact scalar occurrences |
|---|---:|---:|
| C00 | `0x01654c00` | 66 |
| C01 | `0x01654c01` | 147 |
| C02 | `0x01654c02` | 153 |
| **C03** | **`0x01654c03`** | **0** |
| C04 | `0x01654c04` | 167 |
| C05 | `0x01654c05` | 329 |
| C06 | `0x01654c06` | 20 |

C00, C01, C02, C04, C05, and C06 have exact little-endian byte-pattern matches. C03 has no exact byte-pattern match, no exact scalar operand, and no exact scalar occurrence of its two's-complement equivalent `0xfe9ab3fd`. Range checks or equivalent arithmetic may still cover C03; absence is not proof that the value is impossible.

### Direct `0x00b5b800` result comparisons

Within the bounded live-`EAX` window, exact C00..C06 `CMP`/`SUB` counts were:

```text
C00=27  C01=89  C02=89  C03=0  C04=110  C05=260  C06=2
```

`0x01654c10` and `0x02ccd1d2` are also observed outside the requested range, so C00..C06 is not a complete proven 32-bit domain.

## Hypotheses

### H1 — Normal receiver pointer

**Prediction:** constructor/allocation, direct or indirect publication, typed `+0x20` store, dereference/virtual dispatch/reference operations, and teardown.

**For:** the receiver is used as an `ECX` base and the slot is writable.

**Against:** no writer, allocation, constructor, teardown, vtable owner, or reference operation is connected; `+0x20` is a plain load; zero strict pointer dereferences are observed across the direct-call inventory.

**Status:** not established; unsafe as a default type.

### H2 — Opaque state/handle/token

**Prediction:** compare/branch/copy/index/return use, absent `-1`, distinct C00..C06 tokens, and no object ownership.

**For:** exact forwarding mechanics; 829 scalar sites; six non-pointer normalization sites; C00/C01/C02/C04/C05/C06 comparisons; untyped zero-valued global.

**Against:** tokens are address-like; receiver storage may be pointer-backed; indirect publication and field writer remain unresolved.

**Status:** supported as a bounded static contract; physical representation unresolved.

### H3 — Current mode ID

**Prediction:** dataflow into a named game/input/mode manager, matching field layout, and typed mode writers.

**For:** target is adjacent to named simulator/input accessor slots; consumers occur in mode/gameplay regions.

**Against:** target is distinct from `0x0167eaf0` and `0x0167eaf8`; no mode-manager dataflow, field-owner store, or C03 exact token; token set is incomplete.

**Status:** not established.

### H4 — Strategy/interface pointer

**Prediction:** strategy constructor/vtable owner, strategy/interface call, AddRef/Release, and strategy-layout explanation for `+0x20`.

**For:** `+0x20` field access and Simulator-adjacent code are compatible with a family hypothesis.

**Against:** no concrete owner, constructor, vtable, strategy call, AddRef, Release, or returned-value pointer dereference is connected.

**Status:** low-confidence family hypothesis only.

### H5 — Recoverable publication/teardown chain

**Prediction:** direct/address-taken/bulk publication, first `+0x20` write, replacement, clear, and teardown.

**For:** writable `.data` placement and accessor pattern.

**Against:** direct xref, literal-address, byte-pattern, and memory surfaces contain only the read at `0x00b3d320`; no chain is connected.

**Status:** unresolved; indirect publication remains possible.

### H6 — One enum including `-1`

**Prediction:** one typed writer/unification for `-1` and C00..C06.

**For:** all observed values are 32-bit words used in branch logic.

**Against:** `-1` is produced before the field read; C00..C06 are separate post-read discriminators; C03 is absent; no typed writer unifies them.

**Status:** not established.

## Smallest remaining separator

The direct-writer separator is complete and negative within the current Ghidra surface. The smallest remaining static observation is:

> Recover computed or address-taken provenance to `0x0167eaec` from candidate constructor/publisher/copy helpers; if found, follow the first write to `[receiver+0x20]` and the matching clear/replacement/teardown path.

No direct site remains to separate before that indirect provenance is recovered. The result is therefore a bounded static resolution of mechanics and token behavior, not a lifecycle/type resolution.

## Static-only contract and limitations

Freeze only: raw 32-bit read-through, exact `0xffffffff` for absent receiver, no ownership operation, and distinct observed tokens. Do not authorize a pointer, mode ID, strategy pointer, or enum identity from this observation.

Limitations: Ghidra decompiler types are unnamed/`undefined4`; the caller result is bounded by a 24-instruction straight-line analysis with seven unresolved sites; exact token scans do not exclude equivalent arithmetic; no runtime or indirect publication evidence was used.
