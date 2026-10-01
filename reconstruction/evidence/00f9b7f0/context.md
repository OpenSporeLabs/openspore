# Reconstruction context 0x00f9b7f0

- Status: `partial`
- Content SHA-256: `1f4c03702b9341e458af9e4f8d177818918e9b4e1693c61826dae759125fd76b`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f9b7f0",
  "phase": "reconstruction",
  "target": "0x00f9b7f0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00f9b7f0",
  "package": "pkg-swarm-w1-00f9b7f0",
  "subsystem": "Terrain",
  "va": "0x00f9b7f0"
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
  "content_sha256": "4129d270b3d58e35140e9b217e0e71c0b354905be3c0bf2ba1bd932f5f4a8265",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00f9b7f0 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "(INFERRED)",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "ESI",
    "EDI",
    "EBX"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "callee (the RET carries no immediate, so for a zero-argument callee the two readings coincide; the record's stack_cleanup_owner 'caller' is the machine-derived tool's phrasing of the same fact)",
  "termination": "RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00f9b824",
      "direction": "out",
      "other": "0x0041ea00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b862",
      "direction": "out",
      "other": "0x00427fd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b898",
      "direction": "out",
      "other": "0x006b1f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b8a2",
      "direction": "out",
      "other": "0x006b4b60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b887",
      "direction": "out",
      "other": "0x0093db80",
      "reference_type": "direct-call"
    }
  ],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:PASS"
  ],
  "types": [
    "void (INFERRED from the listing; see return_semantics and unresolved_questions)",
    "void (INFERRED)"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
  "callees": [
    {
      "name": "editor_query_clear_flags_0093db80",
      "reconstructed": true,
      "va": "0x0093db80"
    }
  ],
  "callees_truncated": false,
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00f9b824",
      "direction": "out",
      "other": "0x0041ea00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b862",
      "direction": "out",
      "other": "0x00427fd0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b898",
      "direction": "out",
      "other": "0x006b1f90",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b8a2",
      "direction": "out",
      "other": "0x006b4b60",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f9b887",
      "direction": "out",
      "other": "0x0093db80",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 1,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [
    "0x0093db80"
  ],
  "scc": {
    "id": "scc-0574",
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 6,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 6,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 6,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 6,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 6,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 6,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "PKG-16-SPOREPEDIA-ONLINE",
    "score": 4,
    "symbol": "Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770",
    "va": "0x00641770"
  },
  {
    "match_basis": [
      "direct_xref_n
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00f9b7f0/00f9b7f0.json"
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
    "0x006b1f90's own frame does not close under any reading either: it pushes three words, and 0x00e5c780 must remove two of them for the body to balance, yet the value 0x00e5c780 leaves in the slot 0x006b1fa5 reads is not accounted for by anything in its 16 instructions. Both 0x006b1f90 and 0x006b4b60 read as service or thunk code rather than ordinary compiled functions, and neither has a metadata record. This does not affect the reconstruction -- both are modelled as observers with the signatures their own terminators and this call site's pushes fix -- but it is why their internals are not claimed.",
    "0x006b4b60's own body reads stack slots one through five (0x006b4b7f MOV EBP,[ESP+0x24], 0x006b4b8f MOV EAX,[ESP+0x30], 0x006b4bab MOV EBX,[ESP+0x2c], 0x006b4bd8 MOV EDI,[ESP+0x34]), while this call site pushes only two. Slots three through five therefore hold the caller's own frame and are read as if they were arguments. The body is 138 instructions and installs its own SEH scope, and this call site is inside that scope, so nothing crashes -- but the mismatch is unexplained by anything in this package and it means 0x006b4b60's real prototype is not the two-argument one this call site implies.",
    "Runtime validation is not available for this VA: the only reference to 0x00f9b7f0 in the image is the DATA xref from 0x01490c6c, so there is no direct call site to instrument and no reachable entry point outside a constructed object. Every claim in this record is static.",
    "The dword the +0x24 dispatch publishes in the fr
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00f9b7f0/00f9b7f0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00f9b7f0/00f9b7f0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00f9b7f0/sw1_00f9b7f0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
