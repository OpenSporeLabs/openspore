# Reconstruction context 0x00a85840

- Status: `partial`
- Content SHA-256: `f829e4b4223adf36106678455c59e0a695e60840fc83033f3e83e5554f9d2587`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00a85840",
  "phase": "reconstruction",
  "target": "0x00a85840"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00a85840",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00a85840"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "4c177208f0bf564baa94b336bf3eb65c9523a36ebebb59cbed7d46b8a36cfc5a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00a85840 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 2,
  "receiver": "ECX carries the receiver, and the record says so at R1-VFT (INFERRED) with conventions.confidence SUPPORTED / corroboration persisted_agrees. The record's own words: 0x00a85840 is slot 6 of the vptr-backed vftable at 0x01458024, the body reads its incoming ECX before writing it, and incoming_ecx_reads is 1. In the listing that read is 0x00a85867 `MOV ESI,ECX` (obs-0013 REG_READ, obs-0014 REG_WRITE), and the ECX value is used as a base 0x00a858a7 `LEA ECX,[ESI + 0x24]`, whose result is handed to 0x00537dc0 as that callee's hidden receiver. So the record's bounds_only true / offsets [] / dist...",
  "ret_form": "RET 0x8",
  "return_observation": "return_type is void, and that is a SOURCE-SIDE choice with the machine evidence stated, not a recovered fact. (1) The machine record's own return sub-record names XMM0 with register_class float_or_x87 at confidence APPROXIMATION, and its stated basis is inference RT1: \"an x87 or SSE instruction appears in the body\". That is a property of every SSE instruction ever written, not of a return. (2) The last XMM0 write in the listing is 0x00a85889 `MOVSS [ESP + 0x18],XMM0`, a STORE to the frame, 0x2a bytes before the terminator at 0x00a858b3, and no instruction after it writes XMM0. (3) The last ...",
  "return_register": "XMM0",
  "return_semantics": "float_or_x87_in_XMM0",
  "return_type": "void",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
[TRUNCATED]
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
      "callsite": "0x00a8588f",
      "direction": "out",
      "other": "0x0041cb40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a858aa",
      "direction": "out",
      "other": "0x00537dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a8589d",
      "direction": "out",
      "other": "0x00537f40",
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
  "globals": [],
  "types": [
    "openspore::reconstruction::pkg_w2_00a85840::Receiver",
    "std::size_t",
    "std::uint32_t",
    "void"
  ],
  "vtables": [
    "vtable:0x01458024"
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
  "edges": [
    {
      "callsite": "0x00a8588f",
      "direction": "out",
      "other": "0x0041cb40",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a858aa",
      "direction": "out",
      "other": "0x00537dc0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00a8589d",
      "direction": "out",
      "other": "0x00537f40",
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
    "id": "scc-0338",
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
      "shared_vtable:vtable:0x01458024",
      "same_calling_convention"
    ],
    "package": "pkg-vft-preinc-0051e340",
    "score": 12,
    "symbol": "vft_preinc_0051e340",
    "va": "0x0051e340"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458024",
      "same_calling_convention"
    ],
    "package": "subobject-forward-0051e380",
    "score": 12,
    "symbol": "subobject_forward_0051e380",
    "va": "0x0051e380"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458024",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a85070",
    "score": 12,
    "symbol": "re_00a85070",
    "va": "0x00a85070"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458024"
    ],
    "package": "pkg-w2-0052e640",
    "score": 10,
    "symbol": "reconstruct_0052e640",
    "va": "0x0052e640"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01458024"
    ],
    "package": "pkg-w2-0052e650",
    "score": 10,
    "symbol": "reconstruct_0052e650",
    "va": "0x0052e650"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-editor-w1-0057d6f0",
    "score": 8,
    "symbol": "re_0057d6f0",
    "va": "0x0057d6f0"
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
    "m
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00a85840/w2_00a85840.cpp",
    "reconstruction/staging/pkg-w2-00a85840/w2_00a85840_model_test.cpp",
    "reconstruction/staging/pkg-w2-00a85840/w2_00a85840_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00a85840/00a85840.json"
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
    "HOW FAR THE TABLE AT 0x01458024 RUNS. Seven words from 0x01458024 to 0x0145803f are transcribed, and the run of .text-looking words continues past the own slot (0x00951230, 0x0052e640 at 0x01458040..0x01458047). Nothing in the record or in a code reference fixes the table's end, so no length is claimed.",
    "NO DECOMPILATION EXISTS for this VA in this session: the evidence pack's decompilation category is absent and there is no second, independently-derived reading to cross-check the reconstruction against.",
    "THE 0x6c OBJECT SIZE AND EVERY RECEIVER MEMBER ABOVE +0x24. The +0x24 LEA and 0x00537dc0's own extent bound this body at 0x5c on its own. The 0x6c figure in this package's earlier revision came from 0x00a853b0, a DIFFERENT listing, and it is not used here.",
    "THE DECLARED RETURN TYPE IS A SOURCE-SIDE CHOICE THE MACHINE CANNOT SETTLE. The machine return state is UNCLASSIFIED: the ABI record names XMM0, and evidence_returns.classify returns UNCLASSIFIED on that alone -- \"the machine fixes where the value travels and not the C type, and no width can be claimed\". There is no width record, no return_semantics string that is a C type, and no incoming call edge to read a caller's use of EAX or XMM0. void and T* are byte-identical here because the body contains no instruction that places a value in a return register at the terminator. void was taken as the weaker claim. The disagreement with the record's XMM0 is recorded, not arbitrated.",
    "THE DOMAIN TYPES. ghidra_function.sdk_name is null for this VA, the
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00a85840/00a85840.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00a85840/w2_00a85840.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00a85840/w2_00a85840_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00a85840/w2_00a85840_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-w2-00a85840/00a85840.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00a85840/w2_00a85840.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00a85840/w2_00a85840_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00a85840/w2_00a85840_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_catego
[TRUNCATED]
```
