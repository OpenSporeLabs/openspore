# Reconstruction context 0x00c0c130

- Status: `partial`
- Content SHA-256: `6b8fe04a9c73d5ed53fb220127da34b837d37987336228c7d96e0cf049970baa`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0c130",
  "phase": "reconstruction",
  "target": "0x00c0c130"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x00c0c130"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "a0c5c4514123c5fe68578645fe91e0a3c20091a23c11c7aa63b8006466265bf9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c0c130 failed: Decompilation did not complete. Reason: ",
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
  "hidden_receiver": "read",
  "hidden_this_register": "ECX is the only register mentioned by either instruction",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "0x00c0c130: MOV AL,byte ptr [ECX + 0xbb1] is a one-byte load into AL. Bits 8..31 of EAX are left exactly as the caller left them and are therefore undefined on exit. Both inspected consumers test only AL (0x00c03962 and 0x00c03b1c), so the undefined upper bits are never observed.",
  "return_register": "EAX",
  "return_semantics": "the raw byte stored at receiver + 0xbb1, forwarded unchanged; it is not normalised to 0 or 1",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [],
  "stack_arguments": [],
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c03950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c08350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c248d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c7dcb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d41a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d697a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6abe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d83370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8c120"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c0395d",
      "direction": "in",
      "other": "0x00c03950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c03b17",
      "direction": "in",
      "other": "0x00c03950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0596c",
      "direction": "in",
      "other": "0x00c05810",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c059bd",
      "direction": "in",
      "other": 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint8_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "A runtime check must confirm the upper bits of EAX are genuinely ignored by all twenty-one callers, which is inferred from the two inspected sites only.",
      "A runtime differential test must record writes to receiver + 0xbb1, since no static writer was found and the field's lifecycle is entirely unobserved.",
      "No original-process trace has been captured for 0x00c0c130, so the claim that the field is only ever 0 or non-zero is unverified; the value's range is unknown."
    ],
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c03950"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c05810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c08350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09410"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c248d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c7dcb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d1e930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d41a70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d697a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d6abe0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d83370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e8c120"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c0395d",
      "direction": "in",
      "other": "0x00c03950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c03b17",
      "direction": "in",
      "other": "0x00c03950",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0596c",
      "direction": "in",
      "other": "0x00c05810",
      "reference_type": "direct-call"

[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_pair_004279d0",
    "va": "0x004279d0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "property_record_assign_scalar_00428060",
    "va": "0x00428060"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_paint_commit_0043ac40",
    "va": "0x0043ac40"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "model_parts_apply_properties_00447150",
    "va": "0x00447150"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_insert_004786e0",
    "va": "0x004786e0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_entry_expand_004ad6f0",
    "va": "0x004ad6f0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-10-EDITOR-DISPATCH",
    "score": 2,
    "symbol": "Editors_EditorModel_SetColor_raw_004ae250",
    "va": "0x004ae250"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-APP-SAFE-WAVE11",
    "score": 2,
    "symbol": "pair_vector_construct_004b62a0",
    "va": "0x004b62a0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
    "reconstruction/staging/wave13-w1-core-b10/c0c130_flag_b91.cpp",
    "reconstruction/staging/wave13-w1-core-b10/c0c130_flag_b91.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00c0c130.json"
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
    "A runtime check must confirm the upper bits of EAX are genuinely ignored by all twenty-one callers, which is inferred from the two inspected sites only.",
    "A runtime differential test must record writes to receiver + 0xbb1, since no static writer was found and the field's lifecycle is entirely unobserved.",
    "How does the flag at +0xbb0 (read by 0x00c0c120) relate to the one at +0xbb1? They are adjacent and independently read, but no code in this batch writes either, so no relationship is established.",
    "Is the byte a boolean at all, or a small counter or enum whose only observed values are 0 and non-zero? No writer was found, so the range is unknown.",
    "No original-process trace exists for any function in this batch. Every statement here is static.",
    "No original-process trace has been captured for 0x00c0c130, so the claim that the field is only ever 0 or non-zero is unverified; the value's range is unknown.",
    "The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.",
    "The second inspected caller, at 0x00c03b17, has no owning function in the xref record; its enclosing function was not identified.",
    "Twelve of the fourteen observed caller functions were not disassembled, so only two call sites have a verified use of the return value.",
    "What class owns 0x00c0c130? The receiver's offset signature is known but no vtable was located and no ModAPI declaration matches.",
    "What does
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b10/00c0c130.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c0c130_flag_b91.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c0c130_flag_b91.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b10/00c0c130.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c0c130_flag_b91.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c0c130_flag_b91.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "requi
[TRUNCATED]
```
