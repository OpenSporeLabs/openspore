# Reconstruction context 0x00c70150

- Status: `partial`
- Content SHA-256: `55ceb632dfb2f883ee40f59c28ba19a88c17f197fe555967cfa3d3f8ae6055af`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c70150",
  "phase": "reconstruction",
  "target": "0x00c70150"
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
  "va": "0x00c70150"
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
  "content_sha256": "81c904593ff2baa0a69df067d7e1bd3d9b88b4b187deb2cd3e445b2c5e9101f5",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c70150 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__cdecl",
  "hidden_receiver": "none: ECX is written at 0x00c70156 from ESI and is a call argument, not a receiver",
  "hidden_this_register": "ECX is only ever loaded, at 0x00c70156 (MOV ECX,ESI) and 0x00c701a7 (MOV ECX,ESI) and 0x00c701b2 (MOV ECX,ESI), each immediately before a thiscall to a one-argument accessor",
  "ordinary_stack_argument_slots": 3,
  "receiver": false,
  "ret_form": "RET",
  "return_note": "(boolean)",
  "return_observation": "0x00c70246: MOV AL,0x1 and 0x00c7024e: XOR AL,AL write only the low byte; bits 8..31 of EAX are left as the caller left them, and every consumer tests AL (0x00c3588f, 0x00c3514c, 0x00c61a3c, 0x00c630bf, 0x01068b72)",
  "return_register": "EAX",
  "return_semantics": "1 when some entry satisfies the acceptance test, 0 otherwise; the only writes are XOR AL,AL at 0x00c70162 and 0x00c7024e, and MOV AL,0x1 at 0x00c70246, so only AL is defined",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "ESP0 + 0x04",
      "overwritten": "0x00c7017b stores the loop counter into this same slot and 0x00c701ef reloads it, so the argument is dead after its first read",
      "read_at": [
        "0x00c70152"
      ],
      "role": "the owner object; supplies the element count through its +0x160 and +0x15c fields and the kind through 0x00b8dab0",
      "slot": 1
    },
    {
      "frame_offset": "ESP0 + 0x08",
      "read_at": [
        "0x00c70190"
      ],
   
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [
    {
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    }
  ],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c308e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c344f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c70b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01068970"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00c308ec",
      "direction": "in",
      "other": "0x00c308e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c34568",
      "direction": "in",
      "other": "0x00c344f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c35144",
      "direction": "in",
      "other": "0x00c34ee0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c35887",
      "direction": "in",
      "other": "0x00c35810",
      "reference_type": "d
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint8_t (boolean)"
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
      "A runtime differential test must confirm the owner's +0x194 value is 5 whenever the scan is expected to run, since a different value would make every call return 0.",
      "No original-process trace has been captured for 0x00c70150. The 0x00c701d0 read of an apparently uninitialised stack slot is the single most important runtime gate: a trace must record the flag value at that address on entry to each of the ten call sites.",
      "The 0x00c70221 ADD ESP,0x18 and the 0x00f473a0 argument order must be observed live to confirm the six-argument allocation contract.",
      "The population-count computation in 0x00ff0870 must be checked against a live element, because the acceptance threshold of 1 depends on its exact result."
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
      "name": "address_window_offset_005c65e0",
      "reconstructed": true,
      "va": "0x005c65e0"
    },
    {
      "name": "FUN_00b8dab0",
      "reconstructed": false,
      "va": "0x00b8dab0"
    },
    {
      "name": "FUN_01021080",
      "reconstructed": true,
      "va": "0x01021080"
    }
  ],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c308e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c344f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c34ee0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c35810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c59540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c62ff0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c70b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x01068970"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "callsite": "0x00c308ec",
      "direction": "in",
      "other": "0x00c308e0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c34568",
      "direction": "in",
      "other": "0x00c344f0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c35144",
      "direction": "in",
      "other": "0x00c34ee0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00c358
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
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 3,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "direct_xref_neighbor"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 3,
    "symbol": "FUN_01021080",
    "va": "0x01021080"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-EDITOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "editor_bake_probe_004bf770",
    "va": "0x004bf770"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 2,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 2,
    "symbol": "App_IStateManager_Get_0067dce0",
    "va": "0x0067dce0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "WAVE6-ENGINE-RUNTIME",
    "score": 2,
    "symbol": "app_config_manager_get_0067dcf0",
    "va": "0x0067dcf0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-06-WAVE6-APP-MANAGERS",
    "score": 2,
    "symbol": "App_IPropManager_Get_0067ddf0",
    "va": "0x0067ddf0"
  },
  {
    "match_basis": [
      "same_calling_convention"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 2,
    "symbol": "FUN_00b3d3a0",
    "va": "0x00b3d3a0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
    "reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.cpp",
    "reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00c70150.json"
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
    "A runtime differential test must confirm the owner's +0x194 value is 5 whenever the scan is expected to run, since a different value would make every call return 0.",
    "How many stack arguments does 0x00c70150 really take? The body reads a fourth slot at ESP0+0x10 (0x00c701d0) but all ten inspected call sites push three words and clean twelve bytes. Either a caller that pushes four was not found, or the read is of an uninitialised slot whose observed value happens to be zero.",
    "If the fourth slot is uninitialised, what is its value at run time, and does the non-strict accept branch therefore execute by accident at some call sites? This changes the meaning of eight of the ten observed call sites.",
    "No original-process trace exists for any function in this batch. Every statement here is static.",
    "No original-process trace has been captured for 0x00c70150. The 0x00c701d0 read of an apparently uninitialised stack slot is the single most important runtime gate: a trace must record the flag value at that address on entry to each of the ten call sites.",
    "The 0x00c70221 ADD ESP,0x18 and the 0x00f473a0 argument order must be observed live to confirm the six-argument allocation contract.",
    "The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.",
    "The population-count computation in 0x00ff0870 must be checked against a live element, because the acceptance threshold of 1 depends on its exact re
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b10/00c70150.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/wave13-w1-core-b10/00c70150.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index
[TRUNCATED]
```
