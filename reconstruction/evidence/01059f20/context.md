# Reconstruction context 0x01059f20

- Status: `partial`
- Content SHA-256: `6341b59185827f6e608c39a39e5c1b8b50e996ab760593dcd7754b7b03485d7f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x01059f20",
  "phase": "reconstruction",
  "target": "0x01059f20"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_01059f20",
  "package": null,
  "subsystem": "Simulator",
  "va": "0x01059f20"
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
  "content_sha256": "2629d06da8316d8deb63b2556ef887032b1e2839f904f4e17c52369223af355f",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x01059f20 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "thiscall",
  "hidden_receiver": true,
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueToolStrategy*",
  "receiver_register": "ECX",
  "ret_form": "ret 0xc",
  "return_register": "AL",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04 at function entry",
      "load_site": "0x01059f2d, `mov ebp, dword ptr [esp + 0x1c]` after `push ebp`",
      "observed_use": "The SDK structure cSpaceToolData (size 0x2a0) supplies every field the body touches: +0x114 mpToolOwner, +0x120 mpArea, +0x124 mpBeam and +0x174 mFlags. The callee 0x010568b0 reads the same +0x114 and +0x120 words and the callee 0x01059170 reads the same three, so one object type is proven across three functions.",
      "position": 1,
      "register": "EBP",
      "type": "cSpaceToolData*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08 at function entry",
      "load_site": "0x01059f28, `mov ebx, dword ptr [esp + 0x1c]` after `push ebx`",
      "observed_use": "Read as three consecutive floats at +0, +4 and +8 by `movss` at 0x01059f6e, 0x01059f7e and 0x01059f89, copied into a 12-byte stack local, and re-materialised by `flds`/`fstps` at 0x0105a00f-0x0105a022 for the call to 0x01059170. A by-value Vector3 would need four stack words at the call site; the direct caller at 0x0105aa5c-0x0105aa6e pushes exactly three dwords, so the argument is a pointer.",
      "position": 2,
      "register": "EBX",
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
      "callsite": "0x01059ff8",
      "direction": "out",
      "other": "0x00b3d3c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01059fff",
      "direction": "out",
      "other": "0x00b7c160",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01059fed",
      "direction": "out",
      "other": "0x0104cd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01059f3a",
      "direction": "out",
      "other": "0x010568b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105a025",
      "direction": "out",
      "other": "0x01059170",
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
    "OpaqueToolStrategy*",
    "Simulator::cSpaceToolData::SpaceToolFlags",
    "Vector3",
    "Vector3*",
    "bool",
    "cGameData__vftable*",
    "cSpaceToolData*",
    "float",
    "int",
    "intrusive_ptr<Simulator::cDefaultAoEArea>",
    "intrusive_ptr<Simulator::cDefaultBeamProjectile>",
    "intrusive_ptr<Simulator::cSpaceToolData>",
    "intrusive_ptr<Simulator::cSpatialObject>",
    "map<pair<unsigned int, unsigned int>, Simulator::cRelationshipData>",
    "uint32_t"
  ],
  "vtables": [
    "vtable:0x0149b810",
    "vtable:0x0149b8b4"
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
      "callsite": "0x01059ff8",
      "direction": "out",
      "other": "0x00b3d3c0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01059fff",
      "direction": "out",
      "other": "0x00b7c160",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01059fed",
      "direction": "out",
      "other": "0x0104cd50",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x01059f3a",
      "direction": "out",
      "other": "0x010568b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x0105a025",
      "direction": "out",
      "other": "0x01059170",
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
    "id": "scc-0613",
    "size": 1
  },
  "vtable_reference_count": 1
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
      "shared_vtable:vtable:0x0149b810,vtable:0x0149b8b4",
      "same_calling_convention"
    ],
    "package": "pkg-sim-toolevent-01053d50",
    "score": 12,
    "symbol": "sim_toolevent_slot8_fun_01053d50",
    "va": "0x01053d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 8,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  },
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
  }
]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.cpp",
    "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.hpp",
    "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sim-toolstrategy-01059f20/01059f20.json"
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
    "0x00b7c160 has no SDK name. Its effect on cRelationshipManager is described from its twenty instructions; the meaning of the word at +0x20 bits 1 and 2 and of the dword at +0x55a0, and the behaviour of 0x00b7a710, are unresolved. The SDK spells +0x20 as the bool mbIsInitialized, so only bit 0 is named.",
    "No differential runtime corpus exists for this virtual, so every claim here is static evidence only.",
    "The behaviour of 0x010568b0 is not reconstructed here; only its ABI, its constant-true return and its use of cSpaceToolData::+0x114 and +0x120 are used. Because it always returns 1, this function's first branch is dead in this build, so the reconstruction cannot say what that branch would have suppressed.",
    "The behaviour of 0x01059170 is not reconstructed here; only its four-argument cdecl ABI and its use of cSpaceToolData::+0x114 and +0x120 are used.",
    "The function is unnamed in the Spore-ModAPI symbol table, so no SDK class name is asserted for the receiver. The evidence supports a cToolStrategy-derived virtual whose receiver dispatches cDefaultBeamTool__vftable word 0x48, but the owning class is not identified.",
    "The meaning of vtable word 0x2c is not settled. The SDK names cGameData__vftable word 0x2c IsDestroyed, but the listing takes the bridge path precisely when that call returns NON-ZERO, which is the opposite of an IsDestroyed guard. Either the concrete override at 0x2c is not the SDK IsDestroyed, or the code deliberately acts on beams it considers destroyed. The source therefore names
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sim-toolstrategy-01059f20/01059f20.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-sim-toolstrategy-01059f20/01059f20.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sim-toolstrategy-01059f20/tool_strategy_01059f20_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],

[TRUNCATED]
```
