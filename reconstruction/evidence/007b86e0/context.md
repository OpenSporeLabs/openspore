# Reconstruction context 0x007b86e0

- Status: `partial`
- Content SHA-256: `cf1dd59d559b3608a1494efb23923c419bb14c741c5fc23a02b0113af8a7c4c4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x007b86e0",
  "phase": "reconstruction",
  "target": "0x007b86e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_007b86e0",
  "package": null,
  "subsystem": "Editor",
  "va": "0x007b86e0"
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
  "content_sha256": "545a4d10d907946f14c6e267eee3397c222b3a78c14f7265361c23bc1c64064d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x007b86e0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX is the receiver; 0x007b86e3 ADD ECX,4 biases it to the embedded sub-object and it stays biased for the indirect call at 0x007b86fb",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x007b86e6 ADD EAX,-1 leaves the new count in EAX and 0x007b86ec JNZ branches to 0x007b86ff (RET) with EAX untouched, so the non-zero path returns the decremented count. The zero path ends at 0x007b86fd XOR EAX,EAX, so it returns exactly 0. Both paths write the full 32-bit register.",
  "return_register": "EAX",
  "return_semantics": "the decremented reference count, or 0 when the zero arm ran and the object was destroyed",
  "return_type": "std::int32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x007b86ff; the JNZ at 0x007b86ec targets it directly"
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
      "va": "0x00650190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00782660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bb670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bced0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c1c10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00801230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e642a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed8a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f33bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fffdd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01070290"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00650349",
      "direction": "in",
      "other": "0x00650190",
      "reference_type": "computed-call"
    }
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::int32_t"
  ],
  "vtables": [
    "vtable:0x013f56a8",
    "vtable:0x013f57f8",
    "vtable:0x013f625c",
    "vtable:0x013f6364",
    "vtable:0x013f68c4",
    "vtable:0x013f6ae0",
    "vtable:0x013f6cec",
    "vtable:0x013f6d6c",
    "vtable:0x013f6de4",
    "vtable:0x013f6f14",
    "vtable:0x013f6fc0",
    "vtable:0x013f7b54"
  ]
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
      "No original-process trace has been captured for 0x007b86e0. A differential run must confirm that the decrement, the restore-to-1 and the destructor call happen in that order on a real receiver, and that no runtime patch retargets the address.",
      "The 417 vtable slots need at least one resolved concrete receiver before any owning class can be named.",
      "The zero arm has never been observed executing. Whether the delete-on-zero path is reachable in the shipping build, and what the caller does with the 0 return, needs a trace."
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
      "va": "0x00650190"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00658c70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0065e110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0076dee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00782660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bb670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007bced0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007c1c10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00801230"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e642a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ed8a30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00f33bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fffdd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01070290"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00650349",
      "directi
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
      "shared_vtable:vtable:0x0140da74,vtable:0x014123b4"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 10,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x0140da74,vtable:0x014123b4"
    ],
    "package": "subobject-forward-0051e380",
    "score": 10,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w2-00586700",
    "score": 10,
    "symbol": "re_00586700",
    "va": "0x00586700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005b2490",
    "score": 10,
    "symbol": "re_005b2490",
    "va": "0x005b2490"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "pkg-swarm-w1-005ba0d0",
    "score": 10,
    "symbol": "re_005ba0d0",
    "va": "0x005ba0d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f57f8,vtable:0x013fdc9c"
    ],
    "package": "pkg-editor-child-007f30d0",
    "score": 10,
    "symbol": "FUN_007f30d0",
    "va": "0x007f30d0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 6,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/007b86e0.json"
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
    "Is the SDK correspondence Spore::Object::Release an identity or only a slot-shape match? The declared order {AddRef, Release, ~Object, Cast} matches one sampled table exactly and 0x00e5cac0 at slot +0x0C does return its receiver unchanged as Cast would, but the SDK declares Object with no data members while the observed count lives at +0x08, so the two layouts are not the same declaration.",
    "No differential trace exists for any of the 63 code references, so it is unproven that every receiver reaching this body has the expected +0x04 sub-object and is not a null or a dangling pointer.",
    "No original-process trace has been captured for 0x007b86e0. A differential run must confirm that the decrement, the restore-to-1 and the destructor call happen in that order on a real receiver, and that no runtime patch retargets the address.",
    "The 417 vtable slots need at least one resolved concrete receiver before any owning class can be named.",
    "The zero arm has never been observed executing. Whether the delete-on-zero path is reachable in the shipping build, and what the caller does with the 0 return, needs a trace.",
    "What happens to the 8 data references whose slot-offset scan did not report +0x04? They were not individually inspected.",
    "What is the second base at +0x04? Its vtable is 0x013ef094 for the one class inspected and its slot +0x00 is a deleting destructor; the SDK's IVirtual, documented as an interface whose only virtual is a destructor, fits, but that is a candidate and no other slot of that b
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b04/007b86e0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b04/007b86e0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "rec
[TRUNCATED]
```
