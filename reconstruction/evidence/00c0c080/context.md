# Reconstruction context 0x00c0c080

- Status: `partial`
- Content SHA-256: `3ecb1f497813065dd701cb9476a05913bba8b47ed2652d818f7ae844b67c94b3`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c0c080",
  "phase": "reconstruction",
  "target": "0x00c0c080"
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
  "va": "0x00c0c080"
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
  "content_sha256": "9e14bab0662713a5dd8a9bea209869184b21d4a49db5c8a7569fbd81330a89e1",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c0c080 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall with one callee-cleaned stack argument",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX is copied to EDI at 0x00c0c084 and reloaded into ECX at 0x00c0c0a9 before the second virtual call",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4 (two sites)",
  "return_note": "(index, or the sentinel -1)",
  "return_observation": "the match path returns ESI (0x00c0c0c2: MOV EAX,ESI) and the miss path returns the constant built by 0x00c0c0ba: OR EAX,0xffffffff, so all 32 bits are defined on both paths",
  "return_register": "EAX",
  "return_semantics": "the zero-based index of the first element whose dword at +0x8 equals the argument, or 0xffffffff when no element matches or the collection is empty",
  "return_type": "std::int32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "ESP0 + 0x04",
      "read_at": [
        "0x00c0c098"
      ],
      "role": "the id to search for, compared against each element's dword at +0x8",
      "slot": 1
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4 at 0x00c0c0be (miss) and 0x00c0c0c7 (hit)"
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
      "va": "0x00c0c140"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0dac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0db10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c197a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1aad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1ad10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1aed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1cdd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c222f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f10bd0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c0c145",
      "direction": "in",
      "other": "0x00c0c140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0c153",
      "direction": "in",
      "other": "0x00c0c140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0dac6",
      "direction": "in",
      "other": "0x00c0dac0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0dae2",
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
    "std::int32_t (index, or the sentinel -1)"
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
      "A runtime differential test must observe a concrete receiver and resolve what virtual slots +0xb0 and +0xb4 dispatch to, which is the only way to name the owning class.",
      "No original-process trace has been captured for 0x00c0c080, so the claim that subclasses never change the vtable mid-scan is static-only.",
      "The count values returned by slot +0xb0 must be captured live, because the unsigned JBE guard and the signed JC bound disagree for counts above 0x7fffffff and no live count is known."
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
      "va": "0x00c0c140"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0dac0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0db10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c18740"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c197a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1aad0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1ad10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1aed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1cdd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c222f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f10bd0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c0c145",
      "direction": "in",
      "other": "0x00c0c140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0c153",
      "direction": "in",
      "other": "0x00c0c140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c0dac6",
      "direction": "in",
      "other": "0x00c0dac0",
      "reference_type": "direct-call"

[TRUNCATED]
```

## 11_related_functions

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
    "reconstruction/staging/wave13-w1-core-b10/c0c080_find_index.cpp",
    "reconstruction/staging/wave13-w1-core-b10/c0c080_find_index.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00c0c080.json"
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
    "A runtime differential test must observe a concrete receiver and resolve what virtual slots +0xb0 and +0xb4 dispatch to, which is the only way to name the owning class.",
    "Do any of the eleven sibling accessors in 0x00c0c0d0..0x00c0c1c0 belong to a different class? They share the receiver and are contiguous in the binary, which is strong but circumstantial.",
    "Is 0xffffffff ever a valid index? It would require a collection of more than 0x7ffffffe elements, so in practice the sentinel is unambiguous; the code does not rely on that.",
    "No original-process trace exists for any function in this batch. Every statement here is static.",
    "No original-process trace has been captured for 0x00c0c080, so the claim that subclasses never change the vtable mid-scan is static-only.",
    "The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.",
    "The count values returned by slot +0xb0 must be captured live, because the unsigned JBE guard and the signed JC bound disagree for counts above 0x7fffffff and no live count is known.",
    "Twenty-eight of the thirty-one observed call sites were not disassembled, so only three call sites have a verified use of the return value.",
    "What are virtual slots +0xb0 and +0xb4? Their behaviour is pinned (a no-argument count and an indexed accessor) but their SDK names, if any, are not established.",
    "What class owns 0x00c0c080? The receiver's offset signature is known
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b10/00c0c080.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c0c080_find_index.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c0c080_find_index.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b10/00c0c080.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c0c080_find_index.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c0c080_find_index.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "r
[TRUNCATED]
```
