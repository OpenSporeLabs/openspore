# Reconstruction context 0x0043cad0

- Status: `partial`
- Content SHA-256: `4953d9a0684bf8a3b16bdb349d62de9cc4c4f97e5dc0909018d8189b4e3c5d7a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x0043cad0",
  "phase": "reconstruction",
  "target": "0x0043cad0"
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
  "va": "0x0043cad0"
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
  "content_sha256": "c92c1faf73be2d596755115b2ead908cacf4f7a1d945776b080db6689418dab9",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x0043cad0 failed: Decompilation did not complete. Reason: ",
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
  "hidden_this_register": "ECX is spilled once at 0x0043cad6 and every later access goes through [EBP-0x68]",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "no FLD, no MOV to EAX as a result and no value is propagated out; the decompiler also gives the function a void return",
  "return_register": null,
  "return_semantics": "no value; EAX is never written on any path except as scratch inside the callee-setup sequences",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x0043cdf5, reached from the fallthrough of the marker block"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a88d0"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043a9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005757b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b4fa0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x0043ab76",
      "direction": "in",
      "other": "0x0043a9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005737c7",
      "direction": "in",
      "other": "0x00573780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005757bd",
      "direction": "in",
      "other": "0x005757b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e88d",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005b5009",
      "direction": "in",
      "other": "0x005b4fa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043cb15",
      "direction": "out",
      "other": "0x0043ce40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043cdea",
      "direction": "out",
      "other": "0x004a88d0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043caf0",
      "direction
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "Editors::EditorRigblock (SDK candidate, field-offset match)",
    "void"
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
      "No original-process trace has been captured. A differential run must show which handle classes are actually reached through slot +0x30 and what state 3 does to them.",
      "The relationship between this sweep and the globally gated 0x0043ce40 can only be settled by observing both in one run.",
      "The three attribute bits and the per-handle flag bytes are only ever read in this build; whether any runtime path sets them, and in which order, needs a trace."
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
  "callees": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004a88d0"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0043a9e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00573780"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005757b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0057e790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x005b4fa0"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x0043ab76",
      "direction": "in",
      "other": "0x0043a9e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005737c7",
      "direction": "in",
      "other": "0x00573780",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005757bd",
      "direction": "in",
      "other": "0x005757b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0057e88d",
      "direction": "in",
      "other": "0x0057e790",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x005b5009",
      "direction": "in",
      "other": "0x005b4fa0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043cb15",
      "direction": "out",
      "other": "0x0043ce40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0043cdea",
      "direction": "out",
      "other": "0x004a88d0",
      "referen
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
    "reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/0043cad0.json"
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
    "Is 0x0043ce40 really the 'complementary' pass, or an independently scheduled one? It is called only when the +0x4C override is clear, and it consults a global that this function does not, so the two are coupled but not obviously a matched pair.",
    "No original-process trace has been captured. A differential run must show which handle classes are actually reached through slot +0x30 and what state 3 does to them.",
    "The relationship between this sweep and the globally gated 0x0043ce40 can only be settled by observing both in one run.",
    "The three attribute bits and the per-handle flag bytes are only ever read in this build; whether any runtime path sets them, and in which order, needs a trace.",
    "The two call sites at 0x005737c7 and 0x005757bd, and the remaining two the ledger lists, were not disassembled, so the frequency and context of this sweep are unknown.",
    "What are the three attribute bits 25, 24 and 11 called? The SDK's EditorRigblock lists mBooleanAttributes as an unnamed bitset with no per-bit documentation.",
    "What do the per-handle flag bytes at +0x92, +0x5D and +0x1D4 mean? They behave as a veto but no SDK field matches, and they sit at three different offsets in three different handle classes.",
    "What does slot +0x30 on a handle actually do? No concrete receiver was ever available, so the effect of pushing state 3 with the flag set is unknown. This is the single largest gap in the reconstruction.",
    "What is 0xD0A55625? It is neither an address nor a plausible field offset and i
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-dispatch-b04/0043cad0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-dispatch-b04/0043cad0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_firs
[TRUNCATED]
```
