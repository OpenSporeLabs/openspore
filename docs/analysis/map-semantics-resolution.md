# Map Semantics Resolution: `0x00e5c780`

## Final classification

`0x00e5c780` is a **fixed hybrid guarded lower-bound lookup** (option C), not a caller-specific operation and not a conventional `lower_bound`.

It retains the ordinary lower-bound candidate while walking:

```text
candidate = &map->anchor
node = map->anchor.parent
while node != null:
    if node->key < query:
        node = node->left
    else:
        candidate = node
        node = node->right
```

It then applies the decisive final check:

```text
if candidate != &map->anchor and candidate->key <= query:
    *out = candidate
else:
    *out = &map->anchor
```

Because the traversal invariant is `candidate->key >= query`, the accepted candidate is equal to the query. A greater successor is therefore rejected.

## Exact evidence

- `0x00e5c780`: `MOV EAX,[ECX+0x0c]` loads the root at `map+0x0c`.
- `0x00e5c783`: `LEA EDX,[ECX+0x04]` forms the end sentinel.
- `0x00e5c78b`: `MOV ECX,EDX` initializes the candidate to the sentinel.
- `0x00e5c794-0x00e5c79b`: unsigned key comparison sends smaller keys left; otherwise the current node is retained and the walk goes right.
- `0x00e5c7a7-0x00e5c7a9`: the sentinel candidate is rejected.
- `0x00e5c7ab-0x00e5c7b0`: `CMP EAX,[ECX+0x10]; JC` rejects the candidate when `query < candidate.key`.
- `0x00e5c7b6` stores the accepted candidate; `0x00e5c7c0` stores the end sentinel.
- There is no equality branch, equality instruction, or independent equality test.

The observed map layout is anchor/end `+0x04`, root `+0x0c`, node key `+0x10`, and payload `+0x14`.

## Result matrix

| Query | Returned node |
|---|---|
| Exact key with no greater candidate retained | Equal node |
| Exact key followed by a greater candidate on the rightward walk | End sentinel |
| Below first key | End sentinel |
| Between existing keys | End sentinel; the least-greater successor is rejected |
| Above final key | End sentinel |
| Empty map | End sentinel |

A static fixture with root `20`, left `10`, and right `30` demonstrates the important edge: query `20` still returns end because `30` replaces `20` as the retained candidate. A single-node `20` map returns node `20`.

## Downstream classification

- `0x00b21340` — **exact-find dependent**. It checks only the end sentinel at `this+0x9c`; a non-end result is consumed at `+0x14` without checking the key. A successor would be incorrectly used as the requested noun record.
- `0x00ba9370` — **exact-find dependent**. It checks only the end sentinel at `this+0x154`, then returns `node+0x14` without checking `node+0x10`.
- `0x01021300` — **exact-find dependent through `0x00ba9370`**. It caches the returned empire without rechecking the returned object's `+0x84` ID. The existing cache check tests the previous object, not the lookup result.
- `0x00b3d300` — **independent**. Its body is only `MOV EAX,[0x0167eae0]; RET`; it neither calls nor consumes the helper result.

## Reconstruction action

- Keep the candidate walk and sentinel output in `reconstruction/staging/pkg20-gameglobal/map_search.cpp`.
- State the accepted candidate as `candidate->key == query` at source level; this is equivalent to the observed final `CMP/JC` because the walk invariant guarantees `candidate->key >= query`.
- Keep `0x00b21340` and `0x01021300` as exact-result consumers; do not implement successor acceptance.
- Do not change `0x00b3d300`; its remaining publication/lifetime gate is independent.
- Treat the older lower-bound/ceiling wording as stale. This resolution supersedes it.

## Remaining runtime gates

Static helper semantics are resolved. No runtime claim is made. The existing runtime gates for global root publication, canonical-slot equality, object lifetime, callback failure, locking, and reentrancy remain open.
