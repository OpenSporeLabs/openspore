# Reconstruction context 0x00b3d240

- Status: `complete`
- Content SHA-256: `cbba98232c90510e92fcc17d1932aece6a5ae6c0e0d575bed40d07afecedfc86`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d240",
  "phase": "reconstruction",
  "target": "0x00b3d240"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b3d240",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x00b3d240"
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
  "content_sha256": "63f8656d4e4fbbbc81bea9232144e249cf173d6622f66caa6ec805eadecbddcb",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 FUN_00b3d240(void)

{
  return DAT_0167eac4;
}


```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": false,
  "ordinary_stack_argument_slots": [],
  "ordinary_stack_arguments": [],
  "receiver": false,
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": [
    "EAX",
    "AL"
  ],
  "return_semantics": "The 4-byte word stored at the absolute address 0x0167eac4, returned whole in EAX. All 32 bits are meaningful: the load at 0x00b3d240 writes the full register, so no narrower or sign-extended return is consistent with the bytes.",
  "return_type": "uint32",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "none",
  "termination": "RET at 0x00b3d245, five bytes after the entry at 0x00b3d240; it is the second and last instruction of the body."
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
      "va": "0x00ae00d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b08670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0a6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b195f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b197b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b303e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b30550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b307e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b31030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32e80"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae03ed",
      "direction": "in",
      "other": "0x00ae00d0",
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
    "std::uint32_t",
    "uint32"
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
      "Any differential run against the original must arrange for 0x0167eac4 to hold a known word first: the image carries no initializer for it, and a run that reads it as zero observes the loader's zero-fill rather than the game's state.",
      "No original-process trace exists for this target (evidence.json categories.runtime is MISSING), so nothing here is runtime-validated."
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
      "va": "0x00ae00d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b08670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b0a6f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19290"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19440"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b195f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b197b0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b19810"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b303e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b30550"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b307e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b31030"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32b20"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32ce0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32dd0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32f60"
    },
    {
      "name": null,
      "reconst
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-11-H4-HELPER-WAVE3",
    "score": 6,
    "symbol": "address_window_offset_005c65e0",
    "va": "0x005c65e0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "dispatch_key_00628450",
    "va": "0x00628450"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "cycle_key_006286a0",
    "va": "0x006286a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-SIMULATOR-SAFE-WAVE11",
    "score": 6,
    "symbol": "release_child_0062c910",
    "va": "0x0062c910"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d2a0",
    "va": "0x00b3d2a0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 6,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 6,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.cpp",
    "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.hpp",
    "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00b3d240/00b3d240.json"
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
    "Any differential run against the original must arrange for 0x0167eac4 to hold a known word first: the image carries no initializer for it, and a run that reads it as zero observes the loader's zero-fill rather than the game's state.",
    "Are the 26 direct callers (fan_in 158) all expecting the same zero-parameter shape, and does any of them treat the returned word as something other than a table pointer?",
    "Does the word at 0x0167eac4 participate in a struct shared with 0x0167eac0 and 0x0167ead0 (the neighbours 0x00b3d230 and 0x00b3d250 read)? No layout is claimed and none is implied by adjacency.",
    "No original-process trace exists for this target (evidence.json categories.runtime is MISSING), so nothing here is runtime-validated.",
    "What concrete type, if any, lives at 0x0167eac4, and what does the returned word denote? The body proves a 4-byte load; nothing names the storage.",
    "Which of the four x86-32 conventions does the original use? The body cannot discriminate; only a caller-side contract beyond zero pushed arguments and zero callee cleanup could, and no caller in the recorded set supplies one.",
    "Who stores 0x0167eac4 before it is read? No write row for the address exists in the data-reference sidecar, but that artifact records only direct references and cannot see a store through a register."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-w2-00b3d240/00b3d240.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
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
      "ref": "reconstruction/metadata/pkg-w2-00b3d240/00b3d240.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00b3d240/root_accessor_00b3d240.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-w2-00b3d240/root_acce
[TRUNCATED]
```
