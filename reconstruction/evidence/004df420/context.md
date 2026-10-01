# Reconstruction context 0x004df420

- Status: `partial`
- Content SHA-256: `b71df7327c701da76008450f5441126a83becd9392a2a20f3679317028e8ae10`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x004df420",
  "phase": "reconstruction",
  "target": "0x004df420"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_004df420",
  "package": null,
  "subsystem": "Editor",
  "va": "0x004df420"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "c287a69a4d1c461bbdde2e5f48fb3fb9d9e3c95f9858f16d0ecac425a6198bad",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x004df420 failed: Decompilation did not complete. Reason: ",
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
  "convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [],
  "ordinary_stack_arguments": [],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": [
    "The last write to EAX before the call is the ADD EAX,0xa4 argument computation, which the call then overwrites. 0x004df550 ends with MOV EAX,[EBP-0x4] / MOV ESP,EBP / POP EBP / RET 0x4, so the callee does produce that dword. Across the 58 direct call sites the value is consumed at 50 of them by the immediately following instruction and at 7 more within the following instructions; at 0x00d5d074 no use of EAX follows on the traced path. Two sites dereference the value behind a TEST EAX,EAX null guard, 0x00c02734 reading [EAX + 0x5b0] and 0x00aec396 reading [EAX + 0x51c], which is consistent w...",
    "The last write to EAX before the call is the ADD EAX,0xa4 argument computation, which the call then overwrites. No instruction after 0x004df433 writes EAX, so the callee's dword is what leaves the frame. 0x004df550 ends with MOV EAX,[EBP-0x4] / MOV ESP,EBP / POP EBP / RET 0x4, so the callee does produce that dword. Across the 58 direct call sites the value is consumed at 50 of them by the immediately following instruction and at 7 more within the following instructions; at 0x00d5d074 no use of EAX follows on the traced path. Two sites dereference the value, 0x00c02734 reading [EAX + 0x5b0] ..."
  ],
  "return_register": "EAX",
  "return_semantics": "a 4-b
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
      "va": "0x004d2200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6ca10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b99420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b99ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9aa10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba3860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c04010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c099e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0c2d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x004d2239",
      "direction": "in",
      "other": "0x004d2200",
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "OpaqueWord"
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
      "No original-process invocation was captured, so no live receiver value, no live argument value and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.",
      "The call sites were counted and classified from a static xref export. Which of them execute in a given play session, and with what receiver and key contents, is a runtime question this repository has no instrument for.",
      "The unreachability result for the callee's key-substitution branch is static. Confirming it as an execution count needs an instrumented run of the original, which was not performed.",
      "runtime validation not run"
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
      "va": "0x004d2200"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ba30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6baf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b6ca10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b99420"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b99ed0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9aa10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba3860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c02710"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c04010"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c042e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c099e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c09fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c0c2d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c222f0"
 
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
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
    "package": "pkg-swarm-w2-00586700",
    "score": 8,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 8,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 8,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
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
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00a98200",
    "score": 8,
    "symbol": "re
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-dogfood-004df420-a1/.clang-format",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.cpp",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.hpp",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1_boundary_test.sh",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1_model_test.cpp",
    "reconstruction/staging/pkg-dogfood-004df420-a1/ownership.json",
    "reconstruction/staging/pkg-editor-species-default-wave12/.clang-format",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12.cpp",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12.hpp",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12_boundary_test.sh",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12_model_test.cpp",
    "reconstruction/staging/pkg-editor-species-default-wave12/ownership.json"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-004df420-a1/004df420.json",
    "reconstruction/metadata/pkg-editor-species-default-wave12/004df420.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x004d3dd0",
        "0x004df6d0",
        "0x004e0560",
        "0x00f473a0",
        "0x004df440",
        "0x004d3dd0",
        "0x004df440",
        "0x004d3dd0",
        "0x004df550",
        "0x004d3dd0",
        "0x004df440",
        "0x004df550",
        "0x004df420",
        "0x00c8a5b0",
        "0x004df440",
        "0x004df550"
      ],
      "conflict_id": "FL-002",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_OBSERVED",
      "resolution_status": "RESOLVED_OBSERVED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
      "subject": "cSpeciesProfile runtime size",
      "unresolved_reason": "Cache eviction, transfer, destructor, and manager ownership remain unresolved; the object-size conflict is resolved."
    }
  ],
  "unresolved_questions": [
    "Are the offsets the resolve family uses, +0x04 in 0x004df550, +0x44 in 0x004df440 and +0xa4 here, three fields of one object or anchors of three different sub-objects? The two resolve bodies are near-clones differing only in those offsets and in the constant passed to 0x004d3dd0, consistent with one template instantiated at several offsets, but no evidence here decides it.",
    "Are the three receiver-relative offsets the resolve family uses, +0x04 in 0x004df550, +0x44 in 0x004df440 and +0xa4 here, three fields of one object or anchors of three different sub-objects? The two resolve bodies are near-clones differing only in those offsets and in the constant passed to 0x004d3dd0, which is cons
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-dogfood-004df420-a1/004df420.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-editor-species-default-wave12/004df420.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-004df420-a1/.clang-format', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-dogfood-004df420-a1/ownership.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-species-default-wave12/.clang-format', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12_boundary_test.sh', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-editor-species-default-wave12/ownership.json', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-dogfood-004df420-a1/004df420.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/pkg-editor-species-default-wave12/004df420.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-004df420-a1/.clang-format",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruc
[TRUNCATED]
```
