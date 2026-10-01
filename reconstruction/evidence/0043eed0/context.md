# Reconstruction context 0x0043eed0

- Status: `partial`
- Content SHA-256: `a71baa8ef686faae38022c637ee5bfaaa9c34b061854fbf6331e1f748b5407af`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0043eed0",
  "phase": "reconstruction",
  "target": "0x0043eed0"
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
  "va": "0x0043eed0"
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
  "content_sha256": "de6eab32bf5408adb66d4ac46b4cfedba5ad29217da782455e5c1ffbb2cf992c",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0043eed0 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x0043eed4",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x0043eeda is FLD dword ptr [EAX+0x1D4] and is the only floating-point instruction in the body. There is no FSTP, FADD, FMUL or memory store, so the loaded value is still on the x87 stack when the frame is torn down and the caller reads ST(0) directly. The caller confirms this: 0x0043f4c6 is FLD1, the matching push of the 1.0f the caller substitutes when it has no child to ask.",
  "return_register": "ST(0) - the x87 stack top, NOT an XMM register",
  "return_semantics": "the float32 stored at receiver+0x1D4, unmodified",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x0043eee3"
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
      "va": "0x0043ecb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043f3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043f3f0"
    },
    {
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004860b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048b370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a0bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a1070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004c73f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582250"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043ed5d",
      "direction": "in",
      "other": "0x0043ecb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043ed68",
      "direction": "in",
      "other": "0x0043ecb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043eda4",
      "direction": "in",
      "other": "0x0043ecb0",
      "
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:The body contains no absolute address operand, so it reads and writes no global."
  ],
  "types": [
    "Editors::EditorRigblock (SDK candidate, two-offset match)",
    "float"
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
      "No original-process trace has been captured. The value actually stored at +0x1D4 in the shipping build, and its range, are runtime facts that static analysis cannot supply.",
      "Whether the getter is ever reached through a pointer stored in a table, which would explain its out-of-line form, needs a reference scan beyond the 29 direct calls."
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
      "va": "0x0043ecb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043f3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043f3f0"
    },
    {
      "name": "FUN_0044ae00",
      "reconstructed": false,
      "va": "0x0044ae00"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004860b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0048b370"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0049cfd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a0bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a1070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a29a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004c73f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00582250"
    },
    {
      "name": "editor_input_0058ac10",
      "reconstructed": true,
      "va": "0x0058ac10"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0043ed5d",
      "direction": "in",
      "other": "0x0043ecb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043ed68",
      "direction": "in",
      "other": "0x0043ecb0",
      "reference_type": "direct-call"
    },
    {
      "c
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 3,
    "symbol": "editor_input_0058ac10",
    "va": "0x0058ac10"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/0043eed0.json"
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
    "Is the +0x218/+0x21C clamp range per-object or per-class? It is read from the receiver, so per-object, but what sets it was not established.",
    "Is the value guaranteed to lie in [0,1]? The caller clamps it into [+0x218, +0x21C] before normalising, which suggests it may not, but nothing in the getter or its 29 callers establishes a range.",
    "No original-process trace has been captured. The value actually stored at +0x1D4 in the shipping build, and its range, are runtime facts that static analysis cannot supply.",
    "The 16 code references that were not disassembled could include a caller that treats the value as something other than a weight.",
    "What does the float at +0x1D4 represent? The 'normalised blend weight' reading comes from FUN_0043ecb0's arithmetic and is labelled INFERRED; the SDK does not name the field and no string or property reference ties it to a concept.",
    "Whether the getter is ever reached through a pointer stored in a table, which would explain its out-of-line form, needs a reference scan beyond the 29 direct calls.",
    "Why is the getter out of line at all? It is nine instructions and would inline; a shipped build that kept it out of line may indicate it is a virtual override, an address taken somewhere, or simply an unoptimised translation unit. The 0 data references argue against the vtable case but do not exclude an address being taken."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b04/0043eed0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b04/0043eed0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "rea
[TRUNCATED]
```
