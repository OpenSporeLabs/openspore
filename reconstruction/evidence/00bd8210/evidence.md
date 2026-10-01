# Evidence 0x00bd8210

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c4db125e3afea67a570123d9725d1bf5846db2ef625f82231d50ab34530ac69c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX is read at 0x00bd8210 and forwarded unchanged into the slot +0x58 call at 0x00bd821c",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "0x00b885a9..0x00b8875a computes a value and 0x00b8875a masks it with 0x3ff, so at most ten bits are significant. 0x00bd821f/0x00bd8226 do not touch EAX after the 0x00b88590 call, and 0x00bd822e is a bare RET, so the full EAX is forwarded.",
  "return_register": "EAX",
  "return_semantics": "the 10-bit payload that 0x00b88590 returns, forwarded unchanged in EAX",
  "return_type": "std::uint16_t",
  "return_width_bytes": 2,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller for 0x00bd8210 itself; callee for 0x00bd821c and 0x00b88590",
  "termination": "RET"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "1827051e0f69776198b42db071d63e806c20c5a994b35883390c69bedbf2d629",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0013"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0011"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          88
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0011",
        "obs-0013"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0013"
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
        "obs-0013"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013"
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
      "at": "0x00bd8210",
      "count": 1,
      "first_use": 0,
      "first_write_index": 8,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "ECX"
    },
    {
      "at": "0x00bd8210",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bd8212",
      "count": 4,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EAX + 0x58]",
      "reg": "EAX"
    },
    {
      "and_esp": null,
      "at": "0x00bd8215",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0004",
      "index": 2,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0xc",
      "sub": 12
    },
    {
      "at": "0x00bd8215",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00bd8218",
      "count": 2,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ESP]",
      "reg": "EDX"
    },
    {
      "at": "0x00bd8218",
      "count": 1,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EDX,[ESP]",
      "reg": "ESP"
    },
    {
      "at": "0x00bd8218",
      "base": "ESP",
      "disp": 0,
      "id": "obs-0008",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "LEA EDX,[ESP]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x00bd821c",
      "base": "EAX",
      "disp": null,
      "id": "obs-0009",
      "index": 5,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x00bd821f",
      "id": "obs-0010",
      "index": 7,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b3d350",
      "target": "0x00b3d350"
    },
    {
      "at": "0x00bd8224",
      "definite": true,
      "id": "obs-0011",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00bd8226",
      "id": "obs-0012",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b88590",
      "target": "0x00b88590"
    },
    {
      "at": "0x00bd822e",
      "form": "RET",
      "id": "obs-0013",
      "imm": n
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "simulator_game_input_manager_get_00b3d350",
    "reconstructed": true,
    "va": "0x00b3d350"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf00a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf0110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf0130"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf5720"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf8440"
  },
  {
    "name": "culture_selection_00bf9820",
    "reconstructed": true,
    "va": "0x00bf9820"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf9e70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bfa660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bfb020"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ca8340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d04320"
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
  "count": 12,
  "instructions": [
    {
      "address": "00bd8210",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00bd8212",
      "instruction": "MOV EAX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00bd8215",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "00bd8218",
      "instruction": "LEA EDX,[ESP]"
    },
    {
      "address": "00bd821b",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00bd821c",
      "instruction": "CALL EAX"
    },
    {
      "address": "00bd821e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bd821f",
      "instruction": "CALL 0x00b3d350"
    },
    {
      "address": "00bd8224",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bd8226",
      "instruction": "CALL 0x00b88590"
    },
    {
      "address": "00bd822b",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "00bd822e",
      "instruction": "RET"
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
  "original_bytes": 12201,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read\",\n    \"hidden_this_register\": \"ECX is read at 0x00bd8210 and forwarded unchanged into the slot +0x58 call at 0x00bd821c\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x00b885a9..0x00b8875a computes a value and 0x00b8875a masks it with 0x3ff, so at most ten bits are significant. 0x00bd821f/0x00bd8226 do not touch EAX after the 0x00b88590 call, and 0x00bd822e is a bare RET, so the full EAX is forwarded.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the 10-bit payload that 0x00b88590 returns, forwarded unchanged in EAX\",\n    \"return_type\": \"std::uint16_t\",\n    \"return_width_bytes\": 2,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller for 0x00bd8210 itself; callee for 0x00bd821c and 0x00b88590\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"simulator_game_input_manager_get_00b3d350\",\n      \"va\": \"0x00b3d350\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-C4-CIV-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"culture_selection_00bf9820\",\n      \"va\": \"0x00bf9820\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"simulator_game_input_manager_get_00b3d350\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d350\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf00a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf0110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf0130\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf5720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf8440\"\n      },\n      {\n        \"name\": \"culture_selection_00bf9820\",\n        \"reconstructed\": true,\n        \"va\": \"0x00bf9820\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf9e70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bfa660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bfb020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ca8340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d04320\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bf00cb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bf00a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf011c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bf0110\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf016d\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bf0130\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf0199\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bf0130\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf578b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bf5720\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bf85f1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bf8440\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0
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
  "body_end": "00bd822e",
  "body_span_bytes": 31,
  "body_start": "00bd8210",
  "callees": [
    "FUN_00b88590",
    "Simulator::cGameInputManager::Get"
  ],
  "callers": [
    "FUN_00bf8440",
    "FUN_00bfa660",
    "FUN_00bf0110",
    "FUN_00ca8340",
    "FUN_00bf0130",
    "FUN_00bf9820",
    "FUN_00d04320",
    "FUN_00bfb020",
    "FUN_00bf00a0",
    "FUN_00bf5720",
    "FUN_00bf9e70"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bd8210",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00bd8210",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7d8210",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bd8210(void)",
  "size_bytes": 31,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bd8210",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 21,
  "xrefs": [
    {
      "from": "00d043c4"
    },
    {
      "from": "00d04415"
    },
    {
      "from": "00d0443a"
    },
    {
      "from": "00d044a0"
    },
    {
      "from": "00bf016d"
    },
    {
      "from": "00bf0199"
    },
    {
      "from": "00bf578b"
    },
    {
      "from": "00bf85f1"
    },
    {
      "from": "00bf00cb"
    },
    {
      "from": "00bf9b34"
    },
    {
      "from": "00bf9d16"
    },
    {
      "from": "00bfa338"
    },
    {
      "from": "00bfa51a"
    },
    {
      "from": "00bfad49"
    },
    {
      "from": "00bfad54"
    },
    {
      "from": "00bfaede"
    },
    {
      "from": "00bfaee7"
    },
    {
      "from": "00bf011c"
    },
    {
      "from": "00bfb31f"
    },
    {
      "from": "00bfb328"
    },
    {
      "from": "00ca8451"
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
    "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
    "reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.cpp",
    "reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00bd8210.json"
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
    "A runtime check must confirm whether the table at receiver+0x4c is rebuilt (dirty byte +0x78) at the moments 0x00bd8210 runs, since that is the only side effect on the path.",
    "No original-process trace has been captured for 0x00bd8210, so the claim that equal directions always quantise to equal indices is static-only.",
    "The 12-byte out buffer written by the slot +0x58 callee must be observed in a live process before its role can be named."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::uint16_t"
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
