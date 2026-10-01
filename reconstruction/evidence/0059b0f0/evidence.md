# Evidence 0x0059b0f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `1f1ba798b05bfb2fbbec8a6a404e973d769a8d404724331740ecc61f1f4022c7`

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
      "name": "position",
      "position": 1,
      "type": "const Vector3 *",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "applyNow",
      "position": 2,
      "type": "bool",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x0c",
      "name": "ignoreZ",
      "position": 3,
      "type": "bool",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 12,
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBX",
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
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +44, so the listing is not one path",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "517a65ffa01ebdb00adfb3f36e413820d32fcd4e221b2bbad2e5f2469f7aee99",
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
    "ghidra_parameter_count": 4,
    "persisted": "agrees",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0057"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0016",
        "obs-0017",
        "obs-0019",
        "obs-0020",
        "obs-0026",
        "obs-0028"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0041"
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
          40,
          44,
          48,
          52,
          56,
          60,
          64
        ],
        "register": "ECX",
        "written_through": 13
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0011",
        "obs-0041",
        "obs-0057"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0020"
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
        "obs-0057"
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
        "obs-0004"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x0059b0f0",
      "count": 29,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x0059b0f0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP +
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
    "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "reconstructed": true,
    "va": "0x0059cf00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00629de0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062cc20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062d0f0"
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
  "count": 153,
  "instructions": [
    {
      "address": "0059b0f0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "0059b0f4",
      "instruction": "SUB ESP,0x3c"
    },
    {
      "address": "0059b0f7",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0059b0f8",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059b0f9",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0059b0fb",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0059b0fd",
      "instruction": "MOV dword ptr [ESI + 0x20],ECX"
    },
    {
      "address": "0059b100",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0059b103",
      "instruction": "MOV dword ptr [ESI + 0x24],EDX"
    },
    {
      "address": "0059b106",
      "instruction": "MOV ECX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0059b109",
      "instruction": "MOV dword ptr [ESI + 0x28],ECX"
    },
    {
      "address": "0059b10c",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0059b10e",
      "instruction": "MOV dword ptr [ESI + 0x2c],EDX"
    },
    {
      "address": "0059b111",
      "instruction": "MOV ECX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0059b114",
      "instruction": "MOV dword ptr [ESI + 0x30],ECX"
    },
    {
      "address": "0059b117",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0059b11a",
      "instruction": "MOV dword ptr [ESI + 0x34],EDX"
    },
    {
      "address": "0059b11d",
      "instruction": "FLD float ptr [ESI + 0x34]"
    },
    {
      "address": "0059b120",
      "instruction": "FLD float ptr [ESI + 0x30]"
    },
    {
      "address": "0059b123",
      "instruction": "FLD float ptr [ESI + 0x2c]"
    },
    {
      "address": "0059b126",
      "instruction": "FMUL ST0"
    },
    {
      "address": "0059b128",
      "instruction": "FLD ST1"
    },
    {
      "address": "0059b12a",
      "instruction": "FMULP ST2"
    },
    {
      "address": "0059b12c",
      "instruction": "FADDP"
    },
    {
      "address": "0059b12e",
      "instruction": "FLD ST1"
    },
    {
      "address": "0059b130",
      "instruction": "FMULP ST2"
    },
    {
      "address": "0059b132",
      "instruction": "FADDP"
    },
    {
      "address": "0059b134",
      "instruction": "FSQRT"
    },
    {
      "address": "0059b136",
      "instruction": "FLD float ptr [0x013f64b0]"
    },
    {
      "address": "0059b13c",
      "instruction": "FXCH"
    },
    {
      "address": "0059b13e",
      "instruction": "FCOMIP ST0,ST1"
    },
    {
      "address": "0059b140",
      "instruction": "FSTP ST0"
    },
    {
      "address": "0059b142",
      "instruction": "JBE 0x0059b1b3"
    },
    {
      "address": "0059b144",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x2c]"
    },
    {
      "address": "0059b149",
      "instruction": "FLD float ptr [ESI + 0x34]"
    },
    {
      "address": "0059b14c",
      "instruction": "FLD float ptr [ESI + 0x30]"
    },
    {
      "address": "0059b14f",
      "instruction": "MOVSS dword ptr [ESP + 0x48],XMM0"
    },
    {
      "address": "0059b155",
      "instruction": "FLD float ptr [ESP + 0x48]"
    },
    {
      "address": "0059b159",
      "instruction": "MOVSS XMM1,dword ptr [ESI + 0x34]"
    },
    {
      "address": "0059b15e",
      "instruction": "FMUL ST0"
    },
    {
      "address": "0059b160",
      "instruction": "FLD ST1"
    },
    {
      "address": "0059b162",
      "instruction": "FMULP ST2"
    },
    {
      "address": "0059b164",
      "instruction": "FADDP"
    },
    {
      "address": "0059b166",
      "instruction": "FLD ST1"
    },
    {
      "address": "0059b168",
      "instruction": "FMULP ST2"
    },
    {
      "address": "0059b16a",
      "instruction": "FADDP"
    },
    {
      "address": "0059b16c",
      "instruction": "FSQRT"
    },
    {
      "address": "0059b16e",
      "instruction": "FLD1"
    },
    {
      "address": "0059b170",
      "instruction": "FDIVRP"
    },
    {
      "address": "0059b172",
      "instruction": "FSTP float ptr [ESP + 0x48]"
    },
    {
      "address": "0059b176",
      "instruction": "MOVSS XMM3,dword ptr [ESP + 0x48]"
    },
    {
      "address": "0059b17c",
      "instruction": "MULSS XMM0,XMM3"
    },
    {
      "address": "0059b180",
      "instruction": "MOVAPS XMM2,XMM0"
    },
    {
      "address": "0059b183",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x30]"
    },
    {
      "address": "0059b188",
      "instruction": "MULSS XMM0,XMM3"
    },
    {
      "address": "0059b18c",
      "instruction": "MULSS XMM1,XMM3"
    },
    {
      "address": "0059b190",
      "instruction": "MOVSS XMM3,dword ptr [0x013f64b0]"
    },
    {
      "address": "0059b198",
      "instruction": "MULSS XMM2,XMM3"
    },
    {
      "address": "0059b19c",
      "instruction": "MULSS XMM0,XMM3"
    },
    {
      "address": "0059b1a0",
      "instruction": "MULSS XMM1,XMM3"
    },
    {
      "address": "0059b1a4",
      "instruction": "MOVSS dword ptr [ESI + 0x2c],XMM2"
    },
    {
      "address": "0059b1a9",
      "instruction": "MOVSS dword ptr [ESI + 0x30],XMM0"
    },
    {
      "address": "0059b1ae",
      "instruction": "MOVSS dword ptr [ESI + 0x34],XMM1"
    },
    {
      "address": "0059b1b3",
      "instruction": "MOV CL,byte ptr [ESP + 0x50]"
    },
    {
      "address": "0059b1b7",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "0059b1b9",
      "instruction": "CMP CL,BL"
    },
    {
      "address": "0059b1bb",
      "instruction": "JZ 0x0059b1c5"
    },
    {
      "address": "0059b1bd",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "0059b1c0",
      "instruction": "MOVSS dword ptr [ESI + 0x34],XMM0"
    },
    {
      "address": "0059b1c5",
      "instruction": "CMP byte ptr [ESP + 0x4c],BL"
    },
    {
      "address": 
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
  "original_bytes": 11196,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this\": \"OpaqueController * in ECX\",\n    \"return_register\": null,\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"position\",\n        \"position\": 1,\n        \"type\": \"const Vector3 *\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"applyNow\",\n        \"position\": 2,\n        \"type\": \"bool\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x0c\",\n        \"name\": \"ignoreZ\",\n        \"position\": 3,\n        \"type\": \"bool\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 12,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 27,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:OpaqueEditorRuntime\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 24,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE8\",\n      \"score\": 6,\n      \"symbol\": \"editor_creature_walk_controller_set_target_angle_0059b2f0\",\n      \"va\": \"0x0059b2f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_post_0059d840\",\n      \"va\": \"0x0059d840\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-RUNTIME-SERVICES-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"editor_anim_event_message_send_0059d8b0\",\n      \"va\": \"0x0059d8b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueEditorRuntime\",\n  \"cluster\": null,\n  \"confidence\": {\n    \"abi_and_cleanup\": \"high\",\n    \"body\": \"high\",\n    \"magnitude_guard\": \"high\",\n    \"ordering\": \"high\",\n    \"ray_origin\": \"high\"\n  },\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00629de0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062cc20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062d0f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0059cf4f\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cf00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00629fb2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00629de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00629fc2\",\n        \"direction\": \"in\",\n        \"other\": \"0x00629de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062a012\",\n        \"direction\": \"in\",\n        \"other\": \"0x00629de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062a022\",\n        \"direction\": \"in\",\n        \"other\": \"0x00629de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062a125\",\n        \"direction\": \"in\",\n        \"other\": \"0x00629de0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0062cc33\",\n        \"dire
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
  "body_end": "0059b2e6",
  "body_span_bytes": 503,
  "body_start": "0059b0f0",
  "callees": [
    "FUN_00a047d0",
    "Graphics::IShadowWorld::Get"
  ],
  "callers": [
    "Editors::cEditorAnimWorld::SetTargetPosition",
    "FUN_0062cc20",
    "FUN_00629de0",
    "FUN_0062d0f0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059b0f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_3",
      "storage": "Stack[-0x3]:1",
      "type": "undefined1"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:1",
      "type": "undefined1"
    },
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
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "Editors::EditorCreatureController::SetTargetPosition",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 4,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "EditorCreatureController *"
    },
    {
      "name": "position",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "Vector3 *"
    },
    {
      "name": "applyNow",
      "ordinal": 2,
      "storage": "Stack[0xc]:1",
      "type": "bool"
    },
    {
      "name": "ignoreZ",
      "ordinal": 3,
      "storage": "Stack[0x10]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x19b0f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::EditorCreatureController::SetTargetPosition(EditorCreatureController * this, Vector3 * position, bool applyNow, bool ignoreZ)",
  "size_bytes": 503,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059b0f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 9,
  "xrefs": [
    {
      "from": "0059cf4f"
    },
    {
      "from": "00629fb2"
    },
    {
      "from": "00629fc2"
    },
    {
      "from": "0062a012"
    },
    {
      "from": "0062a022"
    },
    {
      "from": "0062a125"
    },
    {
      "from": "0062d556"
    },
    {
      "from": "0062d732"
    },
    {
      "from": "0062cc33"
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
    "reconstruction/metadata/pkg-editor-runtime-wave7/0059b0f0.json"
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
    "Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08",
    "The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package",
    "The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value",
    "The picker world returned by 0x0067dd80 and the meaning of its vtable slot 0x28 return value; The IShadowWorld raycast argument record at 0x0059b294..0x0059b2c0 (eight stack slots) is not owned by this package; Whether the hit x really is a ground height; Creature layout beyond 0x0c and the AnimatedCreature at controller+0x08",
    "Whether the hit x really is a ground height"
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
  "bool",
  "const Vector3 *",
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
