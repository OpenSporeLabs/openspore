# Reconstruction context 0x005b2490

- Status: `partial`
- Content SHA-256: `45a7d255b3bd605619a7c3f255bbf89d72f581056cbd7a282d98835975a0da92`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x005b2490",
  "phase": "reconstruction",
  "target": "0x005b2490"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_005b2490",
  "package": "pkg-swarm-w1-005b2490",
  "subsystem": "Editor",
  "va": "0x005b2490"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "80e5e53bc6b120b0113239608cd0637776bb4ca2a879960fc0d47fed32eee216",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x005b2490 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "saved_registers": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "openspore::reconstruction::pkg_sw1_005b2490::Receiver",
    "openspore::reconstruction::pkg_sw1_005b2490::Word",
    "std::uint32_t",
    "std::uint32_t -- the 32-bit word the listing leaves in EAX, spelled as the width-computable builtin rather than as this package's `Word` alias. `using Word = std::uint32_t;` remains in the header and is still what the body's load, its store and the model test's decoys name, because an alias asks no reader to verify a width; only the DECLARED return type had to be spelled so a static reader can compute its width. The two spellings are one type and the emitted code is byte-identical (verified at -O0 and -O2 against the pre-change source: `mov 0x18(%ecx),%eax; add $0x1,%eax; mov %eax,0x18(%ecx); ret`)."
  ],
  "vtables": [
    "vtable:0x013f57f8",
    "vtable:0x013f7028",
    "vtable:0x013f70d4",
    "vtable:0x013f718c",
    "vtable:0x013f7214",
    "vtable:0x013f72ac",
    "vtable:0x013f7348",
    "vtable:0x013f74cc",
    "vtable:0x013f756c",
    "vtable:0x013f7624",
    "vtable:0x013f76c4",
    "vtable:0x013f7774"
  ]
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0106",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 12,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8,vtable:0x013f7028",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 12,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 8,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score": 8,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 8,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00a980b0",
    "score": 8,
    "symbol": "re_00a980b0",
    "va": "0x00a980b0"
  },
  {
    "match_basis": [
      "same_subsyste
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490.cpp",
    "reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-005b2490/005b2490.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "Does any caller use the returned value, and as what? The body is entered only through a table slot, so its callers are the dispatch sites, which this package did not enumerate. The return is the incremented word; whether a caller treats it as a count, an index, a new generation or an opaque handle is not established here.",
    "Is the receiver the head of its object or a sub-object? The body never stores ECX, so a this-adjusting caller is invisible from inside it. The three adjustors (-0x04, -0x10, -0x14) prove the word lives at more than one displacement within a hierarchy, but which class each table belongs to is not established by anything in this package.",
    "Is the word signed or unsigned? INC EAX is bit-identical for signed and unsigned, nothing in the body tests bit 31, and abi_derived's return_semantics is 'unclassified_in_EAX' (RT2 register_class aggregate_unknown). The reconstruction models it as an unsigned 32-bit word -- which is what fixes the 0xffffffff -> 0x00000000 wrap the machine performs -- and the SIGN itself is unresolved. The declared return type is now spelled std::uint32_t rather than the `Word` alias, and that spelling fixes the WIDTH and the wrap only: unsigned is what the wraparound test at 0xffffffff needs to be defined, and it is not a claim that the original's type is unsigned, because INC EAX cannot distinguish the two and no instruction here reads bit 31. Whether the true type is signed changes no observable behaviour of THIS body and changes the meaning of its return value at every ca
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-005b2490/005b2490.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490_types.hpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/research/source-reconstruction-manifest.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/triage/queue-f0e310e0-v6.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-swarm-w1-005b2490/005b2490.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-005b2490/sw1_005b2490_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
