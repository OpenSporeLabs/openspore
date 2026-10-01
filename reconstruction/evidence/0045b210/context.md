# Reconstruction context 0x0045b210

- Status: `partial`
- Content SHA-256: `38d6d47c507d50192df3dedb386022a3088d4406976e5a3b148e79225dc94e00`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0045b210",
  "phase": "reconstruction",
  "target": "0x0045b210"
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
  "va": "0x0045b210"
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
  "content_sha256": "3b9afbd14b59fcdc538610172d644018854d2c19629dd7ee1f0fefb77e7048fc",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0045b210 failed: Decompilation did not complete. Reason: ",
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
  "architecture": "x86-32 (x86:LE:32:windows, image base 0x00400000)",
  "calling_convention": "__thiscall",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "used by every observed caller as a pointer-like value",
  "return_observation": "0x0045b27a MOV EDX,dword ptr [ECX+4] loads a full dword from the matched node and 0x0045b280 MOV EAX,dword ptr [EBP-0x5c] copies all 32 bits. 0x0045b26d XOR EAX,EAX zeroes all 32 bits on the miss path.",
  "return_register": "EAX",
  "return_semantics": "The mapped 32-bit value of the id when the id has an entry, and the literal 0 when it does not. The mapped value is an object pointer in every sampled use: callers load its vtable and dispatch through it.",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP",
    "EBX is used as a scratch by the callee-prologue spill sequence only"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "id",
      "observed_values": [
        "0xb8deeb8b (literal, 0x0058bf39)",
        "0xabf6fbdd (literal, 0x0043f951)",
        "dword from [ESI+0x27c] (0x0058bf6a)",
        "dword from [EBP+0x278] (0x005872dc)",
        "dword from [EBP+0x27c] (0x005877cb)"
      ],
      "read_evidence": "0x0045b219 LEA EAX,[EBP + 0x8] followed by 0x0045b21c PUSH EAX -- the argument is read INDIRECTLY, by passing its address to 0x00421950, not by a direct load. The callee dereferences it at 0x0042195c MOV ECX,dword ptr [EAX].",
      "type": "std::uint32_t",
      "width_bytes": 4
    }
  ],
[TRUNCATED]
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
      "va": "0x0043f6b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045afc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005744b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00575f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f920"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043f7ff",
      "direction": "in",
      "other": "0x0043f6b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043fa22",
      "direction": "in",
      "other": "0x0043f6b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043fa39",
      "direction": "in",
      "other": "0x0043f6b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0045afd0",
      "direction": "in",
      "other": "0x0045afc0",
      "reference_type": "direct-call"
    },
    {
 
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t",
    "std::uint32_t, used by every observed caller as a pointer-like value"
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
      "A runtime pass would need to record the bucket count and the resolved object pointer for a handful of the hardcoded ids to confirm the id-to-class mapping.",
      "No original-process trace exists, so the claim that the global at 0x015d0c14 is populated and that lookups succeed is static only.",
      "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made."
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
      "va": "0x0043f6b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045afc0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b000"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0045b110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005744b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00575f70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00587270"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f2f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0062f920"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0043f7ff",
      "direction": "in",
      "other": "0x0043f6b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043fa22",
      "direction": "in",
      "other": "0x0043f6b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043fa39",
      "direction": "in",
      "other": "0x0043f6b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0045afd0",
      "direction": "i
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
    "reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/0045b210.json"
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
    "A runtime pass would need to record the bucket count and the resolved object pointer for a handful of the hardcoded ids to confirm the id-to-class mapping.",
    "Are 0x0045afc0 / 0x0045b000 / 0x0045b040 / 0x0045b110 thin wrappers over a named SDK method or a hand-rolled dispatch table? The body shape is a bare guarded virtual call, which fits either.",
    "Can a mapped value legitimately equal 0? If so, that entry is permanently invisible to every caller. Nothing in the static evidence answers this.",
    "Fourteen of the twenty-five reported call sites were not disassembled window-by-window in this batch; their receiver provenances come from the briefing's call graph.",
    "Is the bucket count fixed or rehashed at runtime? 0x0045b4c0 (the miss-path inserter reached from 0x0045b290) was not read, so rehash behaviour is unestablished.",
    "No original-process trace exists, so the claim that the global at 0x015d0c14 is populated and that lookups succeed is static only.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.",
    "What are the concrete classes behind the mapped objects? Six virtual slots are observed across five call sites but no vtable base was resolved, so the interface is unnamed.",
    "What class owns the map? The only proven address is the global slot 0x015d0c14 and no vtable was located for the registry object, so the owning type is unnamed.",
    "What does the 32-bit id denote? Two sampled values look like hashed type ids, but n
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b01/0045b210.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b01/0045b210.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/0045b210_lookup.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/stagi
[TRUNCATED]
```
