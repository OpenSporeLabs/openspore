# Evidence 0x01053d50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `140324ead9bb2055fecd0cd5d702ebb89f5c23b5885c803ed9a0efac6caf3437`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_this": true,
  "receiver_register": "ECX",
  "ret_form": "ret 0x8",
  "return_type": "void",
  "saved_registers": [
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "entry_slot": "ESP+0x04 at function entry",
      "observed_use": "Loaded by MOV EAX,dword ptr [ESP + 0x4c] at 0x01053d84, where ESP is already 0x48 below the entry ESP, so the slot is entry ESP+0x04. It is pushed as the first stack argument of the virtual call at 0x01053d8f and is used nowhere else in the body.",
      "position": 1,
      "type": "void * (opaque, forwarded only)",
      "width_bytes": 4
    },
    {
      "entry_slot": "ESP+0x08 at function entry",
      "observed_use": "Loaded by MOV EDI,dword ptr [ESP + 0x50] at 0x01053d55 into EDI, which is kept live across three calls. It is the first stack argument of the frame constructor at 0x01053d65, whose body copies 12 bytes from it, and the second stack argument of the virtual call at 0x01053d8f.",
      "position": 2,
      "type": "const OpaqueVector3 * (12-byte float triple)",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "Unconditional fall-through to the epilogue. The body contains no conditional branch, no loop, and no early exit, so every call in the sequence executes on every invocation."
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "c8be7e38b3547838ce4127f1d61d8e3266780537bf0cd32818a280c33c3e36cc",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0014",
        "obs-0016",
        "obs-0023"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0014",
        "obs-0016",
        "obs-0023",
        "obs-0027"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "entry slot 0 is not written through a pointer",
      "confidence": "APPROXIMATION",
      "id": "S2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "the last value written to EAX classifies as aggregate_unknown",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "aggregate_unknown"
      }
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x01053d50",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x40",
      "sub": 64
    },
    {
      "at": "0x01053d50",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x40",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x01053d53",
      "count": 3,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x01053d54",
      "count": 3,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x01053d55",
      "count": 6,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x50]",
      "reg": "ESP"
    },
    {
      "at": "0x01053d55",
      "base": "ESP",
      "disp": 80,
      "id": "obs-0006",
      "index": 3,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x50]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x01053d55",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword ptr [ESP + 0x50]",
      "reg": "EDI",
      "write_kind": "mem_load"
    },
    {
      "at": "0x01053d59",
      "count": 4,
      "first_use": 4,
      "first_write_index": 18,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_READ",
 
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "Simulator_cSpaceTrading_Get",
    "reconstructed": true,
    "va": "0x00b3d4d0"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 30,
  "instructions": [
    {
      "address": "01053d50",
      "instruction": "SUB ESP,0x40"
    },
    {
      "address": "01053d53",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01053d54",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01053d55",
      "instruction": "MOV EDI,dword ptr [ESP + 0x50]"
    },
    {
      "address": "01053d59",
      "instruction": "LEA EAX,[ESP + 0x8]"
    },
    {
      "address": "01053d5d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01053d5e",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "01053d60",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01053d61",
      "instruction": "LEA ECX,[ESP + 0x20]"
    },
    {
      "address": "01053d65",
      "instruction": "CALL 0x00ad79d0"
    },
    {
      "address": "01053d6a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "01053d6c",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "01053d70",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01053d71",
      "instruction": "PUSH 0x5dce504a"
    },
    {
      "address": "01053d76",
      "instruction": "CALL 0x00b3d4d0"
    },
    {
      "address": "01053d7b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "01053d7d",
      "instruction": "CALL 0x00ae09b0"
    },
    {
      "address": "01053d82",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "01053d84",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4c]"
    },
    {
      "address": "01053d88",
      "instruction": "MOV EDX,dword ptr [EDX + 0x4c]"
    },
    {
      "address": "01053d8b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "01053d8c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01053d8d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "01053d8f",
      "instruction": "CALL EDX"
    },
    {
      "address": "01053d91",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "01053d95",
      "instruction": "CALL 0x00ad7ad0"
    },
    {
      "address": "01053d9a",
      "instruction": "POP EDI"
    },
    {
      "address": "01053d9b",
      "instruction": "POP ESI"
    },
    {
      "address": "01053d9c",
      "instruction": "ADD ESP,0x40"
    },
    {
      "address": "01053d9f",
      "instruction": "RET 0x8"
    }
  ]
}
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9453,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"ret 0x8\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_slot\": \"ESP+0x04 at function entry\",\n        \"observed_use\": \"Loaded by MOV EAX,dword ptr [ESP + 0x4c] at 0x01053d84, where ESP is already 0x48 below the entry ESP, so the slot is entry ESP+0x04. It is pushed as the first stack argument of the virtual call at 0x01053d8f and is used nowhere else in the body.\",\n        \"position\": 1,\n        \"type\": \"void * (opaque, forwarded only)\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_slot\": \"ESP+0x08 at function entry\",\n        \"observed_use\": \"Loaded by MOV EDI,dword ptr [ESP + 0x50] at 0x01053d55 into EDI, which is kept live across three calls. It is the first stack argument of the frame constructor at 0x01053d65, whose body copies 12 bytes from it, and the second stack argument of the virtual call at 0x01053d8f.\",\n        \"position\": 2,\n        \"type\": \"const OpaqueVector3 * (12-byte float triple)\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"Unconditional fall-through to the epilogue. The body contains no conditional branch, no loop, and no early exit, so every call in the sequence executes on every invocation.\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No canonical structure exists for the 48-byte frame, the 16-byte rotation source or the receiver; all three layouts are assembled from the observed offsets and the callee bodies.\",\n    \"Simulator::cDefaultBeamTool::OnMouseDown at 0x01053d00, the neighbouring address in the same class neighbourhood, has an unusable decompilation in the live program and cannot corroborate the receiver layout.\",\n    \"The owning class and the overridden interface are unresolved, so this virtual cannot be tied to a named SDK declaration.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"Simulator_cSpaceTrading_Get\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d4d0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x01053d65\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ad79d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053d95\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ad7ad0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053d7d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ae09b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01053d76\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d4d0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00b3d4d0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0607\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"FUN_01053d50\",\n  \"normalized_symbol\": \"FUN_01053d50\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n 
[TRUNCATED]
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "01053da1",
  "body_span_bytes": 82,
  "body_start": "01053d50",
  "callees": [
    "FUN_00ae09b0",
    "Simulator::cSpaceTrading::Get",
    "FUN_00ad7ad0",
    "FUN_00ad79d0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01053d50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:1",
      "type": "undefined"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_01053d50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc53d50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01053d50(void)",
  "size_bytes": 82,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01053d50",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b8b4",
      "0x0149b900",
      "0x0149b810"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "0149b800"
    },
    {
      "from": "0149b8a0"
    },
    {
      "from": "0149b8f0"
    },
    {
      "from": "0149b940"
    },
    {
      "from": "0149ba20"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.cpp",
    "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50.hpp",
    "reconstruction/staging/pkg-sim-toolevent-01053d50/sim_tool_event_01053d50_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sim-toolevent-01053d50/01053d50.json"
  ]
}
```

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocking_reason": null,
  "gates": [],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueQuaternion16 (4 floats)",
  "OpaqueVector3 (3 floats)",
  "Word (__thiscall *)(OpaqueToolEventReceiver *, void *, const OpaqueVector3 *)",
  "const OpaqueToolEventVTable *",
  "const OpaqueVector3 * (12-byte float triple)",
  "float[4]",
  "void",
  "void (__thiscall *)(void *)",
  "void *",
  "void * (opaque, forwarded only)",
  "void *[19]"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x010537b0",
  "vtable:0x0149b810",
  "vtable:0x0149b8b4",
  "vtable:0x0149b900"
]
```

## Conflicts

```json
[]
```
