# Evidence 0x00c86760

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `245dcfc1b3111a730bc567bb5af96eb78560896780f50df7f192bb817c2115fa`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "OpaqueSolarSystem*",
  "receiver": "ECX",
  "return": "void",
  "return_type": "void",
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "star",
      "position": 1,
      "type": "OpaqueStar*"
    }
  ],
  "stack_cleanup_bytes": 4,
  "termination": "RET 0x4"
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "flow_not_modelled: the linear ESP walk ends at +40, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "5fa5aeb05b082d795134f5520d916a79a2a246dc5ac8ac7039fd48e44caf19b3",
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
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0100"
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
        "obs-0008"
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
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0020",
        "obs-0030",
        "obs-0033",
        "obs-0036",
        "obs-0039",
        "obs-0046",
        "obs-0059",
        "obs-0079",
        "obs-0082",
        "obs-0088",
        "obs-0094"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          40,
          44,
          56
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0020",
        "obs-0030",
        "obs-0033",
        "obs-0036",
        "obs-0039",
        "obs-0046",
        "obs-0059",
        "obs-0079",
        "obs-0082",
        "obs-0088",
        "obs-0094",
        "obs-0100"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0100"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
  
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00aea5d0",
    "reconstructed": true,
    "va": "0x00aea5d0"
  },
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "FUN_00bba790",
    "reconstructed": false,
    "va": "0x00bba790"
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
    "va": "0x00c8b700"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bba900",
      "0x00bba900",
      "0x00c86760",
      "0x00c8b700"
    ],
    "conflict_id": "planet_count_materialization",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "resolution_status": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 259,
  "instructions": [
    {
      "address": "00c86760",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00c86763",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c86764",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c86765",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c86766",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c86767",
      "instruction": "MOV EDI,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00c8676b",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00c8676d",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c8676f",
      "instruction": "MOV dword ptr [ESP + 0x18],EBP"
    },
    {
      "address": "00c86773",
      "instruction": "MOV dword ptr [EBP + 0xc],EDI"
    },
    {
      "address": "00c86776",
      "instruction": "CALL 0x00c8b7e0"
    },
    {
      "address": "00c8677b",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00c8677d",
      "instruction": "JZ 0x00c8678b"
    },
    {
      "address": "00c8677f",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00c86781",
      "instruction": "CALL 0x00c85540"
    },
    {
      "address": "00c86786",
      "instruction": "JMP 0x00c8688f"
    },
    {
      "address": "00c8678b",
      "instruction": "CMP dword ptr [EBP + 0x38],0x0"
    },
    {
      "address": "00c8678f",
      "instruction": "LEA ESI,[EBP + 0x38]"
    },
    {
      "address": "00c86792",
      "instruction": "JNZ 0x00c8680e"
    },
    {
      "address": "00c86794",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c86796",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c86798",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c8679a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c8679c",
      "instruction": "PUSH 0x145e06c"
    },
    {
      "address": "00c867a1",
      "instruction": "PUSH 0xcc"
    },
    {
      "address": "00c867a6",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00c867ab",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00c867ae",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c867b0",
      "instruction": "JZ 0x00c867bf"
    },
    {
      "address": "00c867b2",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00c867b4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c867b6",
      "instruction": "CALL 0x00bd6410"
    },
    {
      "address": "00c867bb",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c867bd",
      "instruction": "JMP 0x00c867c1"
    },
    {
      "address": "00c867bf",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00c867c1",
      "instruction": "MOV EBX,dword ptr [ESI]"
    },
    {
      "address": "00c867c3",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00c867c5",
      "instruction": "JZ 0x00c867e2"
    },
    {
      "address": "00c867c7",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "00c867c9",
      "instruction": "JZ 0x00c867d3"
    },
    {
      "address": "00c867cb",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00c867cd",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c867cf",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c867d1",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c867d3",
      "instruction": "MOV dword ptr [ESI],EDI"
    },
    {
      "address": "00c867d5",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00c867d7",
      "instruction": "JZ 0x00c867e2"
    },
    {
      "address": "00c867d9",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00c867db",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00c867de",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00c867e0",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c867e2",
      "instruction": "MOV EAX,dword ptr [EBP + 0x28]"
    },
    {
      "address": "00c867e5",
      "instruction": "CMP EAX,dword ptr [EBP + 0x2c]"
    },
    {
      "address": "00c867e8",
      "instruction": "LEA ECX,[EBP + 0x24]"
    },
    {
      "address": "00c867eb",
      "instruction": "JNC 0x00c86807"
    },
    {
      "address": "00c867ed",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "00c867f0",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "00c867f3",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c867f5",
      "instruction": "JZ 0x00c8680e"
    },
    {
      "address": "00c867f7",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00c867f9",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00c867fb",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c867fd",
      "instruction": "JZ 0x00c8680e"
    },
    {
      "address": "00c867ff",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00c86801",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00c86803",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c86805",
      "instruction": "JMP 0x00c8680e"
    },
    {
      "address": "00c86807",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c86808",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c86809",
      "instruction": "CALL 0x00aea5d0"
    },
    {
      "address": "00c8680e",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c86810",
      "instruction": "MOV byte ptr [EAX + 0x38],0x1"
    },
    {
      "address": "00c86814",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
  
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
  "original_bytes": 10230,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"OpaqueSolarSystem*\",\n    \"receiver\": \"ECX\",\n    \"return\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"star\",\n        \"position\": 1,\n        \"type\": \"OpaqueStar*\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-14-A3-WORLD-WAVE3\",\n      \"score\": 8,\n      \"symbol\": \"sphere_draw_direction_00b7e560\",\n      \"va\": \"0x00b7e560\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No original-process runtime trace is available for the opaque world, allocation, materialization, and radius services.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00aea5d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00aea5d0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"FUN_00bba790\",\n        \"reconstructed\": false,\n        \"va\": \"0x00bba790\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c8b700\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c8b75b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c8b700\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8686d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c86809\",\n        \"direction\": \"out\",\n        \"other\": \"0x00aea5d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c869c3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c86a16\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bab900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c869ca\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb59b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8698a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bba790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c867b6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bd6410\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c86a35\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c70f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c8687d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c84120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c868cd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c84120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c86942\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c84120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c86844\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c842a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c868e9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c84310\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"
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
  "body_end": "00c86a97",
  "body_span_bytes": 824,
  "body_start": "00c86760",
  "callees": [
    "FUN_00c85540",
    "FUN_00c8b800",
    "FUN_00c8b450",
    "FUN_00c8b550",
    "FUN_00c85a30",
    "FUN_00bba790",
    "FUN_00b3d2a0",
    "FUN_00f473a0",
    "FUN_00aea5d0",
    "FUN_00423650",
    "FUN_00bd6410",
    "FUN_00c70f90",
    "FUN_00c8b540",
    "FUN_00bb59b0",
    "FUN_00bab900",
    "FUN_00c84310",
    "FUN_00c8b7e0",
    "FUN_00c842a0",
    "FUN_00c84120",
    "FUN_00c84420"
  ],
  "callers": [
    "FUN_00c8b700"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c86760",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00c86760",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x886760",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c86760(void)",
  "size_bytes": 824,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c86760",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00c8b75b"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x01579d10"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.cpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3.hpp",
    "reconstruction/staging/pkg14-a3-world-wave3/world_wave3_model_test.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3.hpp",
    "src/reconstruction/pkg14_a3_world_wave3/world_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg14-a3-world-wave3/00c86760.json"
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
  "OpaqueName*",
  "OpaquePlanetManager*",
  "OpaquePlanetVector*",
  "OpaqueSolarSystem*",
  "OpaqueStar*",
  "void"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4af0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bb4af0",
      "0x00bb4100",
      "0x00bb42a0",
      "0x00bb4ba0",
      "0x00bb4c90",
      "0x00bba900",
      "0x00bba900",
      "0x00bba900",
      "0x00c86760",
      "0x00c8b700"
    ],
    "conflict_id": "planet_count_materialization",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "resolution_status": "The generation body increments mPlanetCount while creating cPlanetRecord objects. Lazy materialization and equality with final runtime cPlanets are unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
