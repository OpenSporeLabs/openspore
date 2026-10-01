# Evidence 0x0059b4b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ee0812a68810d1a79a8985233a78463b6a156949e8a4266a900d125b2fe3f41a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall",
  "hidden_this": "OpaqueController * in ECX",
  "return_register": null,
  "return_type": "void",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "dt",
      "position": 1,
      "type": "std::int32_t",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "caller"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4"
    ],
    "ordinary_stack_arguments": [
      {
        "ebp_offset": "EBP+0x8",
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
        "ebp_offset": "EBP+0x8",
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
    "unparsed_lines_present: 4 line(s) matched no grammar rule",
    "no_discriminator: the cleanup side 'callee' and receiver state True do not combine into a discriminator",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "21f7e91f109f2ad79bcc776751410f271b01d9889ac35b29659370eece771564",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0264",
        "obs-0272"
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
        "obs-0013",
        "obs-0015"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0021",
        "obs-0029",
        "obs-0059",
        "obs-0107",
        "obs-0111",
        "obs-0121",
        "obs-0125",
        "obs-0130",
        "obs-0147",
        "obs-0171",
        "obs-0186",
        "obs-0190",
        "obs-0205",
        "obs-0216",
        "obs-0228",
        "obs-0231",
        "obs-0247"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          8,
          12,
          32,
          36,
          68,
          72,
          76,
          80,
          84,
          85,
          88,
          92,
          96,
          100,
          104,
          108,
          116,
          120,
          124,
          128,
          132
        ],
        "register": "ECX",
        "written_through": 17
      }
    },
    {
      "based_on": [
        "obs-0272"
      ],
      "claim": "the calling convention is unknown: no rule's precondition is satisfied by this body's cleanup and receiver state",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0013"
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
        "obs-0264",
        "obs-0272"
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
        "obs-0002"
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
    },
    {
      "id": "obs-0028"
    },
    {

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
    "va": "0x0059d610"
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
  "count": 721,
  "instructions": [
    {
      "address": "0059b4b0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0059b4b1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0059b4b3",
      "instruction": "AND ESP,0xfffffff0"
    },
    {
      "address": "0059b4b6",
      "instruction": "SUB ESP,0x84"
    },
    {
      "address": "0059b4bc",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0059b4bd",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059b4be",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0059b4c0",
      "instruction": "MOV ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "0059b4c3",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "0059b4c5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059b4c6",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "0059b4c8",
      "instruction": "JZ 0x0059c006"
    },
    {
      "address": "0059b4ce",
      "instruction": "CMP dword ptr [ESI + 0xc],EBX"
    },
    {
      "address": "0059b4d1",
      "instruction": "JZ 0x0059c006"
    },
    {
      "address": "0059b4d7",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0059b4da",
      "instruction": "FILD dword ptr [EBP + 0x8]"
    },
    {
      "address": "0059b4dd",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0059b4df",
      "instruction": "JGE 0x0059b4e7"
    },
    {
      "address": "0059b4e1",
      "instruction": "FADD float ptr [0x013f4fd0]"
    },
    {
      "address": "0059b4e7",
      "instruction": "FMUL float ptr [0x013f9428]"
    },
    {
      "address": "0059b4ed",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "0059b4f5",
      "instruction": "LEA EAX,[ESP + 0x3c]"
    },
    {
      "address": "0059b4f9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059b4fa",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0059b4fb",
      "instruction": "FSTP float ptr [ESP + 0x3c]"
    },
    {
      "address": "0059b4ff",
      "instruction": "MOV dword ptr [ESP + 0x44],EBX"
    },
    {
      "address": "0059b503",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "0059b505",
      "instruction": "MOV EDX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "0059b508",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0059b509",
      "instruction": "LEA EAX,[ESP + 0x44]"
    },
    {
      "address": "0059b50d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059b50e",
      "instruction": "MOVSS dword ptr [ESP + 0x3c],XMM0"
    },
    {
      "address": "0059b514",
      "instruction": "MOVSS dword ptr [ESP + 0x2c],XMM0"
    },
    {
      "address": "0059b51a",
      "instruction": "CALL EDX"
    },
    {
      "address": "0059b51c",
      "instruction": "CALL 0x0067cb20"
    },
    {
      "address": "0059b521",
      "instruction": "MOV ECX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "0059b525",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0059b527",
      "instruction": "MOV EDX,dword ptr [EDX + 0x40]"
    },
    {
      "address": "0059b52a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059b52b",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0059b52d",
      "instruction": "CALL EDX"
    },
    {
      "address": "0059b52f",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "0059b532",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "0059b534",
      "instruction": "JZ 0x0059b54e"
    },
    {
      "address": "0059b536",
      "instruction": "CMP byte ptr [EAX + 0x1d],BL"
    },
    {
      "address": "0059b539",
      "instruction": "JNZ 0x0059b54e"
    },
    {
      "address": "0059b53b",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0059b53d",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
    {
      "address": "0059b543",
      "instruction": "MOVSS dword ptr [ESP + 0x2c],XMM0"
    },
    {
      "address": "0059b549",
      "instruction": "CALL 0x0059b390"
    },
    {
      "address": "0059b54e",
      "instruction": "MOV EAX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "0059b552",
      "instruction": "MOV ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "0059b555",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059b556",
      "instruction": "CALL 0x00a02710"
    },
    {
      "address": "0059b55b",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0059b55d",
      "instruction": "JZ 0x0059b5e9"
    },
    {
      "address": "0059b563",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "0059b566",
      "instruction": "MOV ECX,dword ptr [ESI + 0x8]"
    },
    {
      "address": "0059b569",
      "instruction": "LEA EAX,[ESP + 0x40]"
    },
    {
      "address": "0059b56d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059b56e",
      "instruction": "LEA EAX,[ESP + 0x20]"
    },
    {
      "address": "0059b572",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059b573",
      "instruction": "MOV EAX,dword ptr [ESP + 0x44]"
    },
    {
      "address": "0059b577",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM0"
    },
    {
      "address": "0059b57d",
      "instruction": "MOVSS dword ptr [ESP + 0x48],XMM0"
    },
    {
      "address": "0059b583",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "0059b585",
      "instruction": "MOV EDX,dword ptr [EDX + 0x5c]"
    },
    {
      "address": "0059b588",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059b589",
      "instruction": "CALL EDX"
    },
    {
      "address": "0059b58b",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0059b58d",
      "instruct
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
  "original_bytes": 13795,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": \"OpaqueController * in ECX\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"dt\",\n        \"position\": 1,\n        \"type\": \"std::int32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n      \"va\": \"0x0059b2f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorRuntime\",\n  \"cluster\": null,\n  \"confidence\": {\n    \"abi_and_cleanup\": \"high\",\n    \"body\": \"high\",\n    \"bounds_callback_contract\": \"high\",\n    \"constants\": \"high\",\n    \"interpolation_hoist\": \"high\",\n    \"limited_angle_projection\": \"high\",\n    \"magnitude_guard\": \"high\",\n    \"ordering\": \"high\",\n    \"quarter_turn_sign\": \"high\",\n    \"runtime_injected_basis\": \"high\",\n    \"temporary_aliasing\": \"medium\"\n  },\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d610\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0059d723\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059d610\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059bc9e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00436ce0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059ba99\",\n        \"direction\": \"out\",\n        \"other\": \"0x00576b00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059bd3c\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059ab70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059ba1f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059ac00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059ba2f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059ac00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059ba3b\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059ac00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059bd12\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059aed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059b549\",\n        \"direction\": \"out\",\n        \"other\": \"0x0059b390\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059b51c\",\n 
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
  "body_end": "0059c00e",
  "body_span_bytes": 2911,
  "body_start": "0059b4b0",
  "callees": [
    "FUN_0059ac00",
    "FUN_0069b840",
    "FUN_0059ab70",
    "FUN_00a027a0",
    "FUN_0069b760",
    "FUN_0059b390",
    "FUN_0059aed0",
    "FUN_0067cb20",
    "FUN_00699600",
    "FUN_00576b00",
    "Graphics::IShadowWorld::Get",
    "FUN_00436ce0",
    "FUN_00a02710"
  ],
  "callers": [
    "FUN_0059d610"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059b4b0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:1",
      "type": "undefined"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "local_84",
      "storage": "Stack[-0x84]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "Editors::EditorCreatureController::Update",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "EditorCreatureController *"
    },
    {
      "name": "dt",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x19b4b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::EditorCreatureController::Update(EditorCreatureController * this, int dt)",
  "size_bytes": 2911,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059b4b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0059d723"
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
  "file": "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
  "files": [
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.hpp",
    "src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave7/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059b4b0.json"
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
    "Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image",
    "Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned)",
    "Semantics of the 0x00699600, 0x0069b840 and 0x0069b760 helpers (lerp, angle lerp and projection are inferred from usage, not owned); Runtime values of the injected basis words 0x015e5a0c/0x10/0x14, 0x015e5a88/0x8c/0x90 and 0x015e590c/0x015e5910/0x015e5914, which read as zero in the file image; The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros; The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c; The eight-slot IShadowWorld raycast argument record; The picking helper 0x0067dd80 and its vtable slot 0x28 return value; The meaning of controller+0x1c and of the 0x0059b390 publication port; Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically",
    "The AnimatedCreature vtable at controller+0x08 and its slots 0x58 and 0x5c",
    "The eight-slot IShadowWorld raycast argument record",
    "The four-argument contract of the creature bounds callback beyond the two output slots and two literal zeros",
    "The meaning of controller+0x1c and of the 0x0059b390 publication port",
    "The picking helper 0x0067dd80 and its vtable slot 0x28 return value",
    "Whether a zero-length current offset is reachable; the binary produces 1.0f/0.0f = +inf and then 0.0f*inf = NaN, which this reconstruction reproduces but does not test numerically"
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
  "OpaqueEditorRuntime",
  "std::int32_t",
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
