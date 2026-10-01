# Reconstruction context 0x00c37360

- Status: `partial`
- Content SHA-256: `10b988e9040bcd69910482e9673d4244388f559d7a39aa25711cf1d0586a9307`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c37360",
  "phase": "reconstruction",
  "target": "0x00c37360"
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
  "va": "0x00c37360"
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
  "content_sha256": "9ed7c448825143cfe1aa7cb0d51384ebaa1e3fa08d2d42beef17f469dae90051",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c37360 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl (a bare RET with no argument reads; the body is identical under __cdecl, __thiscall and __fastcall, so no convention is asserted)",
  "hidden_receiver": "none",
  "hidden_this_register": "none: EAX is the only register touched and it is written before it is read",
  "ordinary_stack_argument_slots": 0,
  "receiver": false,
  "ret_form": "RET",
  "return_note": "(32-bit pointer in EAX)",
  "return_observation": "0x00c37360: MOV EAX,dword ptr [0x0168df68] is a full 32-bit load; all 32 bits of EAX are defined",
  "return_register": "EAX",
  "return_semantics": "the 32-bit value stored at the absolute address 0x0168df68, forwarded unchanged",
  "return_type": "void*",
  "return_width_bytes": 4,
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
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e99550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffcab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffe570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffe860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01001cd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01017bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01017d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101b670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101ba10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101d130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010317d0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00b6154e",
      "direction": "in",
      "other": "0x00b60d80",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "void* (32-bit pointer in EAX)"
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
      "A runtime differential test must confirm that 0x00b60d80 is the only creator of the slot and that no runtime patch retargets 0x0168df68.",
      "No original-process trace has been captured for 0x00c37360, so the claim that the slot is non-null during a live Cell stage is static-only."
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
      "va": "0x00b60d80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b6c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c5b860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e99550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00fe0f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffcab0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffe570"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ffe860"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01001cd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01017bb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01017d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101b670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101ba10"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0101d130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x010317d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01056d30"
    },
    {
      "name": null,
      "reconst
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
    "reconstruction/staging/wave13-w1-core-b10/c37360_global_accessor.cpp",
    "reconstruction/staging/wave13-w1-core-b10/c37360_global_accessor.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00c37360.json"
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
    "A runtime differential test must confirm that 0x00b60d80 is the only creator of the slot and that no runtime patch retargets 0x0168df68.",
    "Is 0x00f473a0(0x1bc, \"Simulator\", ...) a generic app-system factory whose name argument is a registry key, or a bespoke Simulator constructor? The 0x00f473a0 body is a six-argument forwarder to 0x009289f0 and does not settle it.",
    "No original-process trace exists for any function in this batch. Every statement here is static.",
    "No original-process trace has been captured for 0x00c37360, so the claim that the slot is non-null during a live Cell stage is static-only.",
    "Of the 40 call sites, only 0x00b6154e was disassembled; the result use at the other 39 is unverified.",
    "The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.",
    "What is the class of the object behind 0x0168df68? Only its vtable address 0x0146bb78 and its 0x1bc allocation size are observed; no RTTI and no SDK declaration identifies it.",
    "Why do 0x00b5f1d0 and 0x00c3762a read the global inline rather than calling 0x00c37360? The two spellings are byte-equivalent, so the difference is a compilation artefact, not a semantic one."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b10/00c37360.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c37360_global_accessor.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c37360_global_accessor.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b10/00c37360.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c37360_global_accessor.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c37360_global_accessor.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
[TRUNCATED]
```
