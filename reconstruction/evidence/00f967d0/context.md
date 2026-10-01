# Reconstruction context 0x00f967d0

- Status: `partial`
- Content SHA-256: `b909a7bdf3ad8662e4909581e891d3caccb64a2f1b601d0bf59bd015e73a047a`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f967d0",
  "phase": "reconstruction",
  "target": "0x00f967d0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00f967d0",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00f967d0"
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
  "content_sha256": "ad0e9bf260b971ee4e00119e9256c99b36952b388dc721357c1c39e902f74a79",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00f967d0 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x04",
    "entry_ESP+0x08",
    "entry_ESP+0x0c"
  ],
  "receiver_register": "ECX",
  "ret_form": "RET 0xc",
  "return_note": "The machine-derived ABI record for this VA (briefing.abi) reports return_register ST0 and return_semantics 'float_or_x87_in_ST0'. That is a reading of the x87 PAIR the body executes, not of an outgoing value: 0x00f967dc's FLD result is consumed by the FMUL at 0x00f967e1 and committed to memory by the FSTP at 0x00f967e7, so the x87 stack is EMPTY from 0x00f967e8 onward and no instruction on any path writes ST0 after that. EAX is equally dead: its last writer is the store at 0x00f9682a, two instructions before the terminator, and it is not copied anywhere. The declared return type is void and...",
  "return_type": "void",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 12,
  "stack_cleanup_owner": "callee",
  "termination": "0x00f96830, bytes C2 0C 00. The callee owns all twelve argument bytes: the epilogue's POP ESI (0x00f9682c) and ADD ESP,0x10 (0x00f9682d) land ESP back on its entry value, and 0x62 is the offset from the first instruction to the terminator."
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00f967dc",
      "direction": "out",
      "other": "0x0097ef00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f96810",
      "direction": "out",
      "other": "0x00fb7bb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f96821",
      "direction": "out",
      "other": "0x00fb7bc0",
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
    "global:0x0140f334"
  ],
  "types": [
    "OpaquePointee",
    "OpaqueReceiver",
    "PKG_SW1_00F967D0_THISCALL",
    "void"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
      "Conditions are listed in full under runtime_gate.conditions; the shortest form is that a live receiver of this vtable's class, with a non-null word at +0x20c, must be driven through both floor arms and through a NaN, and the three callee returns plus the three out-pointer addresses must be captured at the call sites.",
      "RUNTIME is required and gated at 0: no trace was run and no differential evidence was gathered for this VA."
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00f967dc",
      "direction": "out",
      "other": "0x0097ef00",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f96810",
      "direction": "out",
      "other": "0x00fb7bb0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00f96821",
      "direction": "out",
      "other": "0x00fb7bc0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0569",
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 12,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 12,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 12,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 12,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 12,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 12,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00f967d0/00f967d0.json"
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
    "Conditions are listed in full under runtime_gate.conditions; the shortest form is that a live receiver of this vtable's class, with a non-null word at +0x20c, must be driven through both floor arms and through a NaN, and the three callee returns plus the three out-pointer addresses must be captured at the call sites.",
    "RUNTIME is required and gated at 0: no trace was run and no differential evidence was gathered for this VA.",
    "The class that owns vtable 0x01490be8 is not established. ghidra_function.namespace and ghidra_function.sdk_name are null for this VA, and the sibling package that read the same table could not establish the owner either. The receiver is therefore an opaque 0x210-byte run and no member is named.",
    "The meaning of the three values is not established. The listing fixes where each comes from -- a scaled, floored float and the two words at the pointee's +0x5c0 and +0x5c4 -- and nothing fixes what any of them is for. The two words are one dword apart and are read by two separate two-instruction accessors, which is the shape of an adjacent pair of counters, a size and an alignment, or a key and a value; no record available here chooses between those.",
    "The one unparsed line in the derived ABI record (abstained_because: 'unparsed_lines_present: 1 line(s) matched no grammar rule') was not located. All 27 instructions of the listing are accounted for by the model and the frame walk balances, so no reconstruction claim rests on it, but which line the tool could not parse is not known.",
  
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00f967d0/00f967d0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00f967d0/00f967d0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00f967d0/sw1_00f967d0_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
