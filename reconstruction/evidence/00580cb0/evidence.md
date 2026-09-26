# Evidence 0x00580cb0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d396a889dcc7771f0e4bbfd9e6967a89258e18394d9022fad0100cc620caf19d`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [],
  "ordinary_stack_arguments": [],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "The last write to EAX before the epilogue is the CALL at 0x00580dd8, and the four instructions after it are POP EDI, POP ESI, ADD ESP,0x1024 and RET, none of which touches EAX. There is no direct call site to measure consumption against, because the body has zero incoming direct-call edges and is reached only through 0x013f57f8 + 0x54, so how the indirect callers treat the value is not measurable from this target.",
  "return_register": "EAX",
  "return_semantics": "a 4-byte opaque word in EAX, forwarded unmodified from the handle's table slot +0x04; the body writes no instruction to EAX between 0x00580dd8 and 0x00580de2",
  "return_type": "OpaqueWord",
  "return_width_bytes": 4,
  "saved_registers": "ESI and EDI, pushed at 0x00580cba/0x00580cbb and popped at 0x00580dda/0x00580ddb. No other callee-saved register is pushed or written.",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00688fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006891f0"
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */\n\nvoid __fastcall FUN_00580cb0(undefined4 param_1)\n\n{\n  int *piVar1;\n  int *piVar2;\n  undefined4 uVar3;\n  undefined4 auStack_1024 [3];\n  int *piStack_1018;\n  undefined1 local_1014 [512];\n  undefined1 local_e14 [512];\n  undefined1 local_c14 [3088];\n  undefined4 uStack_4;\n  \n  uStack_4 = 0x580cba;\n  FUN_00580c10(local_1014);\n  FUN_00939a30(local_e14,0x100,L\"%s.db.tmp\",local_1014);\n  FUN_00939a30(local_c14,0x100,L\"%s.db\",local_1014);\n  piVar1 = (int *)FUN_00688fa0(local_e14);\n  if (piVar1 != (int *)0x0) {\n    (**(code **)*piVar1)();\n    FUN_00693d60(piVar1,&WORD_01897c18,&WORD_01897c18,&WORD_01897c18);\n    FUN_00692ea0();\n    piVar2 = (int *)(**(code **)(*piStack_1018 + 0x20))();\n    auStack_1024[0] = 1;\n    uVar3 = (**(code **)(*piVar2 + 0x18))();\n    FUN_0093aa70(uVar3,auStack_1024,1,0);\n    FUN_00692f90(param_1,&DAT_0150d100,0x1a80d26);\n    FUN_00692900(piStack_1018);\n    FUN_00693900();\n  }\n  (**(code **)(piVar1[1] + 0x1c))();\n  (**(code **)(piVar1[1] + 8))();\n  FUN_006891f0(local_e14,local_c14);\n  (**(code **)(*piVar1 + 4))();\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 91,
  "instructions": [
    {
      "address": "00580cb0",
      "instruction": "MOV EAX,0x1024"
    },
    {
      "address": "00580cb5",
      "instruction": "CALL 0x011e0700"
    },
    {
      "address": "00580cba",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00580cbb",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00580cbc",
      "instruction": "LEA EAX,[ESP + 0x18]"
    },
    {
      "address": "00580cc0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00580cc1",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00580cc3",
      "instruction": "CALL 0x00580c10"
    },
    {
      "address": "00580cc8",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "00580ccc",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00580ccd",
      "instruction": "PUSH 0x13f5c74"
    },
    {
      "address": "00580cd2",
      "instruction": "LEA EDX,[ESP + 0x224]"
    },
    {
      "address": "00580cd9",
      "instruction": "PUSH 0x100"
    },
    {
      "address": "00580cde",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00580cdf",
      "instruction": "CALL 0x00939a30"
    },
    {
      "address": "00580ce4",
      "instruction": "LEA EAX,[ESP + 0x2c]"
    },
    {
      "address": "00580ce8",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00580ce9",
      "instruction": "PUSH 0x13f5c68"
    },
    {
      "address": "00580cee",
      "instruction": "LEA ECX,[ESP + 0x434]"
    },
    {
      "address": "00580cf5",
      "instruction": "PUSH 0x100"
    },
    {
      "address": "00580cfa",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00580cfb",
      "instruction": "CALL 0x00939a30"
    },
    {
      "address": "00580d00",
      "instruction": "LEA EDX,[ESP + 0x23c]"
    },
    {
      "address": "00580d07",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00580d08",
      "instruction": "CALL 0x00688fa0"
    },
    {
      "address": "00580d0d",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00580d0f",
      "instruction": "ADD ESP,0x28"
    },
    {
      "address": "00580d12",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00580d14",
      "instruction": "JZ 0x00580da3"
    },
    {
      "address": "00580d1a",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00580d1c",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00580d1e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00580d20",
      "instruction": "CALL EDX"
    },
    {
      "address": "00580d22",
      "instruction": "PUSH 0x1897c18"
    },
    {
      "address": "00580d27",
      "instruction": "PUSH 0x1897c18"
    },
    {
      "address": "00580d2c",
      "instruction": "PUSH 0x1897c18"
    },
    {
      "address": "00580d31",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00580d32",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "00580d36",
      "instruction": "CALL 0x00693d60"
    },
    {
      "address": "00580d3b",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00580d3f",
      "instruction": "CALL 0x00692ea0"
    },
    {
      "address": "00580d44",
      "instruction": "MOV ECX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00580d48",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00580d4a",
      "instruction": "MOV EDX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "00580d4d",
      "instruction": "CALL EDX"
    },
    {
      "address": "00580d4f",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00580d51",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00580d53",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "00580d56",
      "instruction": "MOV dword ptr [ESP + 0x8],0x1"
    },
    {
      "address": "00580d5e",
      "instruction": "CALL EAX"
    },
    {
      "address": "00580d60",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00580d62",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00580d64",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00580d68",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00580d69",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00580d6a",
      "instruction": "CALL 0x0093aa70"
    },
    {
      "address": "00580d6f",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00580d72",
      "instruction": "PUSH 0x1a80d26"
    },
    {
      "address": "00580d77",
      "instruction": "PUSH 0x150d100"
    },
    {
      "address": "00580d7c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00580d7d",
      "instruction": "LEA ECX,[ESP + 0x624]"
    },
    {
      "address": "00580d84",
      "instruction": "CALL 0x00692f90"
    },
    {
      "address": "00580d89",
      "instruction": "MOV EDX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00580d8d",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00580d8e",
      "instruction": "LEA ECX,[ESP + 0x61c]"
    },
    {
      "address": "00580d95",
      "instruction": "CALL 0x00692900"
    },
    {
      "address": "00580d9a",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00580d9e",
      "instruction": "CALL 0x00693900"
    },
    {
      "address": "00580da3",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00580da6",
      "instruction": "MOV EDX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "00580da9",
      "instruction": "LEA EDI,[ESI + 0x4]"
    },
    {
      "address": "00580dac",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00580dae",
      "instruction": "CALL EDX"
    },
    {
      "address": "00580d
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
  "original_bytes": 15357,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [],\n    \"ordinary_stack_arguments\": [],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"The last write to EAX before the epilogue is the CALL at 0x00580dd8, and the four instructions after it are POP EDI, POP ESI, ADD ESP,0x1024 and RET, none of which touches EAX. There is no direct call site to measure consumption against, because the body has zero incoming direct-call edges and is reached only through 0x013f57f8 + 0x54, so how the indirect callers treat the value is not measurable from this target.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"a 4-byte opaque word in EAX, forwarded unmodified from the handle's table slot +0x04; the body writes no instruction to EAX between 0x00580dd8 and 0x00580de2\",\n    \"return_type\": \"OpaqueWord\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": \"ESI and EDI, pushed at 0x00580cba/0x00580cbb and popped at 0x00580dda/0x00580ddb. No other callee-saved register is pushed or written.\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005f9230\",\n      \"va\": \"0x005f9230\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005f9310\",\n      \"va\": \"0x005f9310\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fc330\",\n      \"va\": \"0x005fc330\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00688fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x006891f0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00580cc3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00580c10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580d08\",\n        \"direction\": \"out\",\n        \"other\": \"0x00688fa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580dc9\",\n        \"direction\": \"out\",\n        \"other\": \"0x006891f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580d95\",\n        \"direction\": \"out\",\n        \"other\": \"0x00692900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580d3f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00692ea0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580d84\",\n        \"direction\": \"out\",\n        \"other\": \"0x00692f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580d9e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00693900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580d36\",\n        \"direction\": \"out\",\n        \"other\": \"0x00693d60\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580cdf\",\n        \"direction\": \"out\",\n        \"other\": \"0x00939a30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580cfb\",\n        \"direction\": \"out\",\n        \"other\": \"0x00939a30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00580d6a\",\n        \"direction\": \"out\",\n    
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
  "body_end": "00580de2",
  "body_span_bytes": 307,
  "body_start": "00580cb0",
  "callees": [
    "FUN_0093aa70",
    "FUN_00692ea0",
    "FUN_00693900",
    "__alloca_probe",
    "FUN_00939a30",
    "FUN_00688fa0",
    "FUN_00693d60",
    "FUN_00692900",
    "FUN_006891f0",
    "FUN_00580c10",
    "FUN_00692f90"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00580cb0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c14",
      "storage": "",
      "type": "undefined1[3088]"
    },
    {
      "name": "local_e14",
      "storage": "",
      "type": "undefined1[512]"
    },
    {
      "name": "local_1014",
      "storage": "",
      "type": "undefined1[512]"
    },
    {
      "name": "uStack_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "auStack_1024",
      "storage": "Stack[-0x1024]:4",
      "type": "undefined4[3]"
    },
    {
      "name": "piStack_1018",
      "storage": "Stack[-0x1018]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "undefined4"
    },
    {
      "name": "piVar1",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "piVar2",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "uVar3",
      "storage": "register:00000000:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00580cb0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x180cb0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00580cb0(void)",
  "size_bytes": 307,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00580cb0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f57f8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "013f584c"
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
  "global:NOT_AVAILABLE"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/.clang-format",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.cpp",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.hpp",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_boundary_test.sh",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1_model_test.cpp",
    "reconstruction/staging/pkg-dogfood-00580cb0-a1/ownership.json"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-00580cb0-a1/00580cb0.json"
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
    "No original-process invocation was captured, so no live handle, no live path buffer contents and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.",
    "The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.",
    "The null-handle path cannot be exercised without a filesystem that refuses the open, and the observable it would produce is a fault rather than a value.",
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueWord"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00580df0",
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
[]
```
