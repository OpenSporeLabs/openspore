# Evidence 0x00c33690

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1fe237e753cb553c93edd6b6e33d873974040f57e6e17ebebfd4bd71a4ff041a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueSpeciesProfile*",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "profile",
      "position": 1,
      "type": "OpaqueProfile*",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4 on the single exit"
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
      "entry_ESP+0x4"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
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
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "a0423eda412bdf0d8fd63fd7229d7d19fb75a4398c28f1db7be7f767edf68ff3",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0059"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0011"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0019",
        "obs-0022",
        "obs-0033",
        "obs-0036",
        "obs-0049",
        "obs-0052"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          32,
          136,
          140
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0019",
        "obs-0022",
        "obs-0033",
        "obs-0036",
        "obs-0049",
        "obs-0052",
        "obs-0059"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0059"
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
        "obs-0059"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0059"
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
      "at": "0x00c33690",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x2c",
      "sub": 44
    },
    {
      "at": "0x00c33690",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x2c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00c33693",
      "count": 7,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c33694",
      "count": 6,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00c33695",
      "count": 9,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00c33696",
      "count": 2,
      "first_use": 4,
      "first_write_index": 50,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00c33697",
   
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "star_manager_record_to_planet_00bb5b50",
    "reconstructed": true,
    "va": "0x00bb5b50"
  },
  {
    "name": "EmpirePoliticalColor_00c32cd0",
    "reconstructed": true,
    "va": "0x00c32cd0"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
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
    "va": "0x00bb1340"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bba2a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0100a160"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x010221f0"
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
  "count": 130,
  "instructions": [
    {
      "address": "00c33690",
      "instruction": "SUB ESP,0x2c"
    },
    {
      "address": "00c33693",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c33694",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c33695",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c33696",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c33697",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c33699",
      "instruction": "CALL 0x01021300"
    },
    {
      "address": "00c3369e",
      "instruction": "MOV EBP,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00c336a2",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00c336a4",
      "instruction": "JNZ 0x00c336ff"
    },
    {
      "address": "00c336a6",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c336a8",
      "instruction": "CMP EBP,EBX"
    },
    {
      "address": "00c336aa",
      "instruction": "JZ 0x00c33701"
    },
    {
      "address": "00c336ac",
      "instruction": "MOV EAX,0x1667bac"
    },
    {
      "address": "00c336b1",
      "instruction": "MOV dword ptr [ESP + 0x1c],EAX"
    },
    {
      "address": "00c336b5",
      "instruction": "MOV dword ptr [ESP + 0x20],EAX"
    },
    {
      "address": "00c336b9",
      "instruction": "LEA EAX,[ESP + 0x1c]"
    },
    {
      "address": "00c336bd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c336be",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00c336c0",
      "instruction": "MOV dword ptr [ESP + 0x28],0x1667bae"
    },
    {
      "address": "00c336c8",
      "instruction": "CALL 0x004da330"
    },
    {
      "address": "00c336cd",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "00c336d1",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c336d2",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c336d7",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c336d9",
      "instruction": "CALL 0x00bb5b50"
    },
    {
      "address": "00c336de",
      "instruction": "MOV EDX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "00c336e2",
      "instruction": "MOV EAX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c336e6",
      "instruction": "SUB EDX,EAX"
    },
    {
      "address": "00c336e8",
      "instruction": "AND EDX,0xfffffffe"
    },
    {
      "address": "00c336eb",
      "instruction": "CMP EDX,0x2"
    },
    {
      "address": "00c336ee",
      "instruction": "JLE 0x00c33701"
    },
    {
      "address": "00c336f0",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00c336f2",
      "instruction": "JZ 0x00c33701"
    },
    {
      "address": "00c336f4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c336f5",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00c336fa",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00c336fd",
      "instruction": "JMP 0x00c33701"
    },
    {
      "address": "00c336ff",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c33701",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00c33705",
      "instruction": "MOV dword ptr [ESP + 0x14],EBX"
    },
    {
      "address": "00c33709",
      "instruction": "MOV dword ptr [ESP + 0x18],EBX"
    },
    {
      "address": "00c3370d",
      "instruction": "CMP EBP,EBX"
    },
    {
      "address": "00c3370f",
      "instruction": "JZ 0x00c3372f"
    },
    {
      "address": "00c33711",
      "instruction": "MOV EAX,dword ptr [EBP + 0x504]"
    },
    {
      "address": "00c33717",
      "instruction": "MOV ECX,dword ptr [EBP + 0x508]"
    },
    {
      "address": "00c3371d",
      "instruction": "MOV EDX,dword ptr [EBP + 0x50c]"
    },
    {
      "address": "00c33723",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00c33727",
      "instruction": "MOV dword ptr [ESP + 0x14],ECX"
    },
    {
      "address": "00c3372b",
      "instruction": "MOV dword ptr [ESP + 0x18],EDX"
    },
    {
      "address": "00c3372f",
      "instruction": "MOV EDI,dword ptr [ESI + 0x8c]"
    },
    {
      "address": "00c33735",
      "instruction": "SUB EDI,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00c3373b",
      "instruction": "SAR EDI,0x2"
    },
    {
      "address": "00c3373e",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00c33740",
      "instruction": "JLE 0x00c3375a"
    },
    {
      "address": "00c33742",
      "instruction": "MOV ECX,dword ptr [ESI + 0x88]"
    },
    {
      "address": "00c33748",
      "instruction": "MOV ECX,dword ptr [ECX + EBX*0x4]"
    },
    {
      "address": "00c3374b",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00c3374f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c33750",
      "instruction": "CALL 0x00bb9b90"
    },
    {
      "address": "00c33755",
      "instruction": "INC EBX"
    },
    {
      "address": "00c33756",
      "instruction": "CMP EBX,EDI"
    },
    {
      "address": "00c33758",
      "instruction": "JL 0x00c33742"
    },
    {
      "address": "00c3375a",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00c3375c",
      "instruction": "JZ 0x00c3380b"
    },
    {
      "address": "00c33762",
      "instruction": "LEA EDX,[ESP + 0x1c]"
    },
    {
      "address": "00c33766",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c33767",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c33769",
      "instruction": "CALL 0x00c32cd0"
    },
    {
      "address": "00c3376e",
      "instruction": "MOV EAX,0x1667bac"
    },
    {
      "address": "00c33773",
      "instruction": "MOV dword ptr [ESP + 0x2c],EAX"
    },
    {
      "address": "00
[TRUNCATED]
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
  "original_bytes": 10138,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueSpeciesProfile*\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"profile\",\n        \"position\": 1,\n        \"type\": \"OpaqueProfile*\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4 on the single exit\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"SpeciesProfileSelector_00c30cc0\",\n      \"va\": \"0x00c30cc0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 14,\n      \"symbol\": \"ArchetypeRelationshipsID_00c30e20\",\n      \"va\": \"0x00c30e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-E3-EMPIRE-STATE-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"HomeWorldMetricLazy_00c31890\",\n      \"va\": \"0x00c31890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-14-A2-WORLD-LIFECYCLE-WAVE2\",\n      \"score\": 5,\n      \"symbol\": \"star_manager_record_to_planet_00bb5b50\",\n      \"va\": \"0x00bb5b50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 5,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueSpeciesProfile\",\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"star_manager_record_to_planet_00bb5b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00bb5b50\"\n      },\n      {\n        \"name\": \"EmpirePoliticalColor_00c32cd0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00c32cd0\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb1340\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bba2a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0100a160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x010221f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00bb1473\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb1340\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bba488\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bba2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0100a381\",\n        \"direction\": \"in\",\n        \"other\": \"0x0100a160\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x01022419\",\n        \"direction\": \"in\",\n        \"other\": \"0x010221f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c337e7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c336c8\",\n        \"direction\": \"out\",\n        \"other\": \"0x004da330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c3378a\",\n        \"direction\": \"out\",\n        \"other\": \"0x004da330\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c336d2\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c33797\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b6f380\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c336d9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb5b50\",\n        \"reference_type\": \"direct-call\"\n      },\n    
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
  "body_end": "00c33814",
  "body_span_bytes": 389,
  "body_start": "00c33690",
  "callees": [
    "FUN_00f47380",
    "FUN_01021300",
    "Simulator::cStarManager::RecordToPlanet",
    "FUN_00bb9b90",
    "FUN_00c32cd0",
    "FUN_004da330",
    "FUN_00b3d2a0",
    "FUN_00b6f380",
    "FUN_00423650"
  ],
  "callers": [
    "FUN_010221f0",
    "cStarRecord__ctor",
    "FUN_00bb1340",
    "FUN_0100a160"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c33690",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_00c33690",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x833690",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c33690(void)",
  "size_bytes": 389,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c33690",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 5,
  "xrefs": [
    {
      "from": "00bb1473"
    },
    {
      "from": "00bba488"
    },
    {
      "from": "01022419"
    },
    {
      "from": "0100a381"
    },
    {
      "from": "00fe3216"
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
  "file": "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
  "files": [
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary.S",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_boundary_test.sh",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.cpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2.hpp",
    "reconstruction/staging/pkg13-e3-empire-state-wave2/empire_state_wave2_model_test.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary.S",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_boundary_test.sh",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.hpp",
    "src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-e3-empire-state-wave2/00c33690.json"
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
    "gate-profile-setter-00c33690",
    "runtime validation not run"
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
  "OpaqueProfile*",
  "OpaqueSpeciesProfile",
  "OpaqueSpeciesProfile*",
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
