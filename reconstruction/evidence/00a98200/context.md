# Reconstruction context 0x00a98200

- Status: `partial`
- Content SHA-256: `ce43b1515f33c9b95a93d1319a9c924958c83938007c96d195ce31e20b1d5792`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00a98200",
  "phase": "reconstruction",
  "target": "0x00a98200"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00a98200",
  "package": "pkg-swarm-w2-00a98200",
  "subsystem": "Editor",
  "va": "0x00a98200"
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
  "content_sha256": "da46022a7f12512b163a7147fdff596fc32ca9687a6b5d569e898c2de934ade4",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00a98200 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_note": "DECLARED void BECAUSE THE BYTES PRODUCE NOTHING, and the canonical machine record disagrees in a way that is recorded rather than papered over. The three exits are 0x00a98332 (latch already zero -- EAX untouched by this body, so whatever the caller had), 0x00a98330 (service null -- EAX holds the service word the null test just read) and the fall-through (EAX holds the last indirect callee's return, which the body never reads). No path loads EAX with a value meant for the caller, and the epilogue does not move it. Ghidra's independent decompilation of the same listing agrees: it opens `void ...",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
      "callsite": "0x00a98216",
      "direction": "out",
      "other": "0x00883860",
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
    "void"
  ],
  "vtables": [
    "vtable:0x01458788"
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
      "callsite": "0x00a98216",
      "direction": "out",
      "other": "0x00883860",
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
    "id": "scc-0340",
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
      "shared_vtable:vtable:0x01458788",
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
      "shared_vtable:vtable:0x01458788",
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
      "shared_vtable:vtable:0x01458788",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00a980b0",
    "score": 12,
    "symbol": "re_00a980b0",
    "va": "0x00a980b0"
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
      "sha
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00a98200/00a98200.json"
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
    "The canonical machine record's return classification remains in tension with the reconstruction. abi.value.return_semantics is `unclassified_in_EAX` and abi_derived.return.void_possible is false, while this reconstruction declares void on the grounds that no path writes EAX with a value for the caller and Ghidra's own decompilation of the same listing agrees. The disagreement is published rather than resolved: see observed_original_abi.return_note. If the integrator prefers the machine phrase, the honest alternative is to keep `void` in the source and accept the RETURN SEMANTICS warning, which is what happens when the sidecar's return_type is not taken as the canonical claim.",
    "The identity of the 0x016514cc global. It is the only source of the service pointer in the whole program, this body never writes it, and nothing in this pack identifies it. It is named in this sidecar and in the package header but deliberately not in the reconstructed source, so the repository's GLOBALS check is not asked to corroborate an address the listing never names.",
    "What the flag word's bit assignments mean. Bits 0, 1 and 2 select which key and which pair dword goes out, bit 4 selects the list call, and bits 5..9 select which of the record's five dwords fills which of the list's five conditional dwords. That the mapping is bit N to the Nth pair is arithmetic over the shifts; the MEANING of any bit is not established here.",
    "What the four indirect callees do with the frame object they are handed, and whether either callee wri
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w2-00a98200/00a98200.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w2-00a98200/00a98200.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w2-00a98200/sw2_00a98200_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.js
[TRUNCATED]
```
