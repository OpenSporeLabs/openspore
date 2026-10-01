# Evidence 0x007c4900

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d24494b1cb9f99f117e78a73e1e56d03926e3505f5b9c70d24ed63cc58107132`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    "direction output pointer at [ESP+4]",
    "origin output pointer at [ESP+8]"
  ],
  "ret_form": "RET 0x8 after restoring ESI",
  "return_type": "void",
  "stack_cleanup_bytes": 8
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
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
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
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
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "45e11068b34c87000c3f1baaec136fdac12e764030eb49eff71132c1a1a3367f",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
      "__thiscall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021"
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
        "obs-0012",
        "obs-0013"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0007",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0007",
        "obs-0011",
        "obs-0012"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0021"
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
        "obs-0021"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0021"
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
      "at": "0x007c4900",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x007c4901",
      "count": 2,
      "first_use": 1,
      "first_write_index": 4,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x007c4901",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x007c4903",
      "id": "obs-0004",
      "index": 2,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067dd50",
      "target": "0x0067dd50"
    },
    {
      "at": "0x007c4908",
      "count": 5,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x007c4908",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x007c490a",
      "definite": true,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MO
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00574850"
  },
  {
    "name": "Editors::cEditor::HandleMessage",
    "reconstructed": false,
    "va": "0x00591fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ace4e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b34790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b349b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c63dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c66760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c678f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d0a040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d0ae50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d11730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e5aae0"
  },
  {
    "name": "cell_move_player_to_mouse_position_00e5b790",
    "reconstructed": true,
    "va": "0x00e5b790"
  },
  {
    "name": "cell_mode_strategy_on_mouse_up_00e5c0f0",
    "reconstructed": true,
    "va": "0x00e5c0f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e62500"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e6c780"
  }
]
```

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
  "count": 20,
  "instructions": [
    {
      "address": "007c4900",
      "instruction": "PUSH ESI"
    },
    {
      "address": "007c4901",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "007c4903",
      "instruction": "CALL 0x0067dd50"
    },
    {
      "address": "007c4908",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "007c490a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "007c490c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x1c]"
    },
    {
      "address": "007c490f",
      "instruction": "CALL EAX"
    },
    {
      "address": "007c4911",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "007c4915",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "007c4919",
      "instruction": "CVTSI2SS XMM0,dword ptr [EAX + 0xc]"
    },
    {
      "address": "007c491e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "007c491f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "007c4920",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "007c4923",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "007c4929",
      "instruction": "CVTSI2SS XMM0,dword ptr [EAX + 0x8]"
    },
    {
      "address": "007c492e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "007c4930",
      "instruction": "MOVSS dword ptr [ESP],XMM0"
    },
    {
      "address": "007c4935",
      "instruction": "CALL 0x007c4730"
    },
    {
      "address": "007c493a",
      "instruction": "POP ESI"
    },
    {
      "address": "007c493b",
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
  "original_bytes": 12778,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"ordinary_stack_arguments\": [\n      \"direction output pointer at [ESP+4]\",\n      \"origin output pointer at [ESP+8]\"\n    ],\n    \"ret_form\": \"RET 0x8 after restoring ESI\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 8\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 25,\n      \"symbol\": \"cell_move_player_to_mouse_position_00e5b790\",\n      \"va\": \"0x00e5b790\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"camera_manager_set_active_007c64c0\",\n      \"va\": \"0x007c64c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"camera_manager_dispose_007c6e50\",\n      \"va\": \"0x007c6e50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueCameraState\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE7\",\n      \"score\": 22,\n      \"symbol\": \"cell_get_globals_data_00e4ce20\",\n      \"va\": \"0x00e4ce20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_func24h_005a2050\",\n      \"va\": \"0x005a2050\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_func54h_005a2320\",\n      \"va\": \"0x005a2320\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-CAMERA-WAVE8\",\n      \"score\": 8,\n      \"symbol\": \"editor_camera_on_exit_00c2e640\",\n      \"va\": \"0x00c2e640\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 3,\n      \"symbol\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n      \"va\": \"0x00e5c0f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCameraState\",\n  \"cluster\": null,\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00574850\"\n      },\n      {\n        \"name\": \"Editors::cEditor::HandleMessage\",\n        \"reconstructed\": false,\n        \"va\": \"0x00591fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ace4e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b34790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b349b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c63dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c66760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c678f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d0a040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d0ae50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d11730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e5aae0\"\n      },\n      {\n        \"name\": \"cell_move_player_to_mouse_position_00e5b790\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5b790\"\n      },\n      {\n        \"name\": \"cell_mode_strategy_on_mouse_up_00e5c0f0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e5c0f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e62500\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e6c780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ebab30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ebacb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ebb0b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ebb2e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00efc930\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,
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
  "body_end": "007c493d",
  "body_span_bytes": 62,
  "body_start": "007c4900",
  "callees": [
    "FUN_007c4730",
    "Graphics::ILightingManager::Get"
  ],
  "callers": [
    "Editors::cEditor::HandleMessage",
    "FUN_00ebacb0",
    "FUN_00574850",
    "FUN_00ace4e0",
    "FUN_00d0ae50",
    "FUN_00ebab30",
    "FUN_00c63dd0",
    "FUN_00ebb0b0",
    "FUN_01001cd0",
    "FUN_00c678f0",
    "FUN_00e5aae0",
    "FUN_00ebb2e0",
    "FUN_00f015b0",
    "FUN_00e62500",
    "FUN_00efc930",
    "FUN_00b34790",
    "FUN_00c66760",
    "App::cCellModeStrategy::OnMouseUp",
    "FUN_00f02700",
    "FUN_0104e060",
    "FUN_00d0a040",
    "FUN_00f011b0",
    "FUN_00b349b0",
    "FUN_00e6c780",
    "FUN_00efd6e0",
    "FUN_00d11730",
    "FUN_00efc9c0",
    "Simulator::Cell::MovePlayerToMousePosition"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "007c4900",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_007c4900",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3c4900",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_007c4900(void)",
  "size_bytes": 62,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x007c4900",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 29,
  "xrefs": [
    {
      "from": "005748e3"
    },
    {
      "from": "00ace509"
    },
    {
      "from": "00b347b6"
    },
    {
      "from": "00b349e3"
    },
    {
      "from": "00c63dee"
    },
    {
      "from": "00c66788"
    },
    {
      "from": "00c67912"
    },
    {
      "from": "00ebab4d"
    },
    {
      "from": "00ebaccd"
    },
    {
      "from": "00ebb0cd"
    },
    {
      "from": "00ebb304"
    },
    {
      "from": "00d0a099"
    },
    {
      "from": "00d0aea6"
    },
    {
      "from": "00e5aafc"
    },
    {
      "from": "00e5b84f"
    },
    {
      "from": "00e62582"
    },
    {
      "from": "00efc9dd"
    },
    {
      "from": "00efc94c"
    },
    {
      "from": "00efd6fc"
    },
    {
      "from": "00f02742"
    },
    {
      "from": "00f0122e"
    },
    {
      "from": "00f01645"
    },
    {
      "from": "0104e0a7"
    },
    {
      "from": "01001d39"
    },
    {
      "from": "00d117a0"
    },
    {
      "from": "005935bd"
    },
    {
      "from": "00b34cbc"
    },
    {
      "from": "00e5c133"
    },
    {
      "from": "00e6c7a3"
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
  "file": "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_camera_wave7/camera_wave7.cpp",
    "src/reconstruction/pkg_camera_wave7/camera_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-camera-wave7/007c4900.json"
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
  "gates": [
    "Original application camera-frame trace is not available; no runtime promotion is claimed.",
    "runtime observation required"
  ],
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
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueCameraState",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
