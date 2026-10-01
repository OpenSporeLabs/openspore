# Evidence 0x0043cad0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c92c1faf73be2d596755115b2ead908cacf4f7a1d945776b080db6689418dab9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX), no stack arguments",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is spilled once at 0x0043cad6 and every later access goes through [EBP-0x68]",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "no FLD, no MOV to EAX as a result and no value is propagated out; the decompiler also gives the function a void return",
  "return_register": null,
  "return_semantics": "no value; EAX is never written on any path except as scratch inside the callee-setup sequences",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single RET at 0x0043cdf5, reached from the fallthrough of the marker block"
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
    "saved_registers": [
      "EBP"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "c8fc3d2def3e038cf7ecc826b3bfa6843ddd8f92011393cacfa1ce43177ede7f",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall (receiver in ECX), no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0127"
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
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0024",
        "obs-0027",
        "obs-0031",
        "obs-0037",
        "obs-0041",
        "obs-0047",
        "obs-0048",
        "obs-0051",
        "obs-0053",
        "obs-0057",
        "obs-0061",
        "obs-0063",
        "obs-0064",
        "obs-0067",
        "obs-0068",
        "obs-0072",
        "obs-0076",
        "obs-0080",
        "obs-0087",
        "obs-0090",
        "obs-0097",
        "obs-0100",
        "obs-0101",
        "obs-0106",
        "obs-0108",
        "obs-0111",
        "obs-0113",
        "obs-0115",
        "obs-0119",
        "obs-0121"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          40,
          352,
          432
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0024",
        "obs-0027",
        "obs-0031",
        "obs-0037",
        "obs-0041",
        "obs-0047",
        "obs-0048",
        "obs-0051",
        "obs-0053",
        "obs-0057",
        "obs-0061",
        "obs-0063",
        "obs-0064",
        "obs-0067",
        "obs-0068",
        "obs-0072",
        "obs-0076",
        "obs-0080",
        "obs-0087",
        "obs-0090",
        "obs-0097",
        "obs-0100",
        "obs-0101",
        "obs-0106",
        "obs-0108",
        "obs-0111",
        "obs-0113",
        "obs-0115",
        "obs-0119",
        "obs-0121",
        "obs-0127"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0127"
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
        "obs-0127"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0127"
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
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
  
[TRUNCATED]
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
    "va": "0x004a88d0"
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
    "va": "0x0043a9e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005757b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057e790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b4fa0"
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
  "count": 251,
  "instructions": [
    {
      "address": "0043cad0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0043cad1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0043cad3",
      "instruction": "SUB ESP,0x78"
    },
    {
      "address": "0043cad6",
      "instruction": "MOV dword ptr [EBP + -0x68],ECX"
    },
    {
      "address": "0043cad9",
      "instruction": "MOV byte ptr [EBP + -0x2],0x0"
    },
    {
      "address": "0043cadd",
      "instruction": "MOV byte ptr [EBP + -0x1],0x0"
    },
    {
      "address": "0043cae1",
      "instruction": "MOV EAX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0043cae4",
      "instruction": "CMP dword ptr [EAX + 0x28],0x0"
    },
    {
      "address": "0043cae8",
      "instruction": "JZ 0x0043cb06"
    },
    {
      "address": "0043caea",
      "instruction": "MOV ECX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0043caed",
      "instruction": "MOV ECX,dword ptr [ECX + 0x28]"
    },
    {
      "address": "0043caf0",
      "instruction": "CALL 0x004adb80"
    },
    {
      "address": "0043caf5",
      "instruction": "MOV byte ptr [EBP + -0x2],AL"
    },
    {
      "address": "0043caf8",
      "instruction": "MOV EDX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0043cafb",
      "instruction": "MOV ECX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "0043cafe",
      "instruction": "CALL 0x004adbc0"
    },
    {
      "address": "0043cb03",
      "instruction": "MOV byte ptr [EBP + -0x1],AL"
    },
    {
      "address": "0043cb06",
      "instruction": "MOV byte ptr [EBP + -0x3],0x0"
    },
    {
      "address": "0043cb0a",
      "instruction": "MOVZX EAX,byte ptr [EBP + -0x2]"
    },
    {
      "address": "0043cb0e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0043cb10",
      "instruction": "JNZ 0x0043cb1a"
    },
    {
      "address": "0043cb12",
      "instruction": "MOV ECX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0043cb15",
      "instruction": "CALL 0x0043ce40"
    },
    {
      "address": "0043cb1a",
      "instruction": "MOV ECX,0x19"
    },
    {
      "address": "0043cb1f",
      "instruction": "CMP ECX,0x3c"
    },
    {
      "address": "0043cb22",
      "instruction": "JNC 0x0043cb5e"
    },
    {
      "address": "0043cb24",
      "instruction": "MOV EDX,0x19"
    },
    {
      "address": "0043cb29",
      "instruction": "SHR EDX,0x5"
    },
    {
      "address": "0043cb2c",
      "instruction": "MOV EAX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0043cb2f",
      "instruction": "MOV ECX,dword ptr [EAX + EDX*0x4 + 0xdc8]"
    },
    {
      "address": "0043cb36",
      "instruction": "MOV dword ptr [EBP + -0x1c],ECX"
    },
    {
      "address": "0043cb39",
      "instruction": "MOV EAX,0x19"
    },
    {
      "address": "0043cb3e",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "0043cb40",
      "instruction": "MOV ECX,0x20"
    },
    {
      "address": "0043cb45",
      "instruction": "DIV ECX"
    },
    {
      "address": "0043cb47",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "0043cb4c",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "0043cb4e",
      "instruction": "SHL EAX,CL"
    },
    {
      "address": "0043cb50",
      "instruction": "AND EAX,dword ptr [EBP + -0x1c]"
    },
    {
      "address": "0043cb53",
      "instruction": "NEG EAX"
    },
    {
      "address": "0043cb55",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "0043cb57",
      "instruction": "NEG EAX"
    },
    {
      "address": "0043cb59",
      "instruction": "MOV byte ptr [EBP + -0x1d],AL"
    },
    {
      "address": "0043cb5c",
      "instruction": "JMP 0x0043cb62"
    },
    {
      "address": "0043cb5e",
      "instruction": "MOV byte ptr [EBP + -0x1d],0x0"
    },
    {
      "address": "0043cb62",
      "instruction": "MOVZX ECX,byte ptr [EBP + -0x1d]"
    },
    {
      "address": "0043cb66",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0043cb68",
      "instruction": "JNZ 0x0043cc4d"
    },
    {
      "address": "0043cb6e",
      "instruction": "MOV dword ptr [EBP + -0x8],0x0"
    },
    {
      "address": "0043cb75",
      "instruction": "JMP 0x0043cb80"
    },
    {
      "address": "0043cb77",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0043cb7a",
      "instruction": "ADD EDX,0x1"
    },
    {
      "address": "0043cb7d",
      "instruction": "MOV dword ptr [EBP + -0x8],EDX"
    },
    {
      "address": "0043cb80",
      "instruction": "CMP dword ptr [EBP + -0x8],0x3"
    },
    {
      "address": "0043cb84",
      "instruction": "JGE 0x0043cbf5"
    },
    {
      "address": "0043cb86",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0043cb89",
      "instruction": "MOV ECX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0043cb8c",
      "instruction": "MOV EDX,dword ptr [ECX + EAX*0x4 + 0x154]"
    },
    {
      "address": "0043cb93",
      "instruction": "MOV dword ptr [EBP + -0x24],EDX"
    },
    {
      "address": "0043cb96",
      "instruction": "CMP dword ptr [EBP + -0x24],0x0"
    },
    {
      "address": "0043cb9a",
      "instruction": "JZ 0x0043cbf3"
    },
    {
      "address": "0043cb9c",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0043cb9f",
      "instruction": "MOV ECX,dword ptr [EBP + -0x68]"
    },
    {
      "address": "0043cba2",
      "instruction": "MOV EDX,dword ptr [ECX + EAX*0x4 + 0x154]"
    },
    {
      "address": "0043cba9",
      "instruction": "MOV dword ptr [EBP + -0x28],EDX"
    },
    {
      "address": "0043cbac",
      "instruction": "MOV EAX,dword ptr [EBP + -0x28]"
    },
    {
      "address": "0043cbaf",
      "instruction": "MOV CL,byte ptr [EAX + 0x92]"
    },
    {
      "address": "0043cbb5",
      "instruction
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
  "original_bytes": 7214,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (receiver in ECX), no stack arguments\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is spilled once at 0x0043cad6 and every later access goes through [EBP-0x68]\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"no FLD, no MOV to EAX as a result and no value is propagated out; the decompiler also gives the function a void return\",\n    \"return_register\": null,\n    \"return_semantics\": \"no value; EAX is never written on any path except as scratch inside the callee-setup sequences\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single RET at 0x0043cdf5, reached from the fallthrough of the marker block\"\n  },\n  \"analogues\": [],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043a9e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005757b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057e790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b4fa0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0043ab76\",\n        \"direction\": \"in\",\n        \"other\": \"0x0043a9e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005737c7\",\n        \"direction\": \"in\",\n        \"other\": \"0x00573780\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005757bd\",\n        \"direction\": \"in\",\n        \"other\": \"0x005757b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057e88d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057e790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005b5009\",\n        \"direction\": \"in\",\n        \"other\": \"0x005b4fa0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043cb15\",\n        \"direction\": \"out\",\n        \"other\": \"0x0043ce40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043cdea\",\n        \"direction\": \"out\",\n        \"other\": \"0x004a88d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043caf0\",\n        \"direction\": \"out\",\n        \"other\": \"0x004adb80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0043cafe\",\n        \"direction\": \"out\",\n        \"other\": \"0x004adbc0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 5,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0011\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": null,\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": null,\n  \"normalized_symbol\": null,\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": null\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process trace has been captured. A differential run must show which handle classes are actually reached through slot +0x30 and what state 3 does to them.\",\n      \"The relationship between this sweep and the globally gated 0x0043ce40 can only be settled by observing both in one run.\",\n      \"The three attribute bits and the per-handle flag bytes are only ever read in this build; whether any runtime path sets them, and in which order, needs a trace.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime_gated\": true,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.cpp\",\n      \"reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.hpp\",\n      \"reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/wave13-w1-dispatch-b04/0043cad0.json\"\n    ],\n    \"provenance\": [\n      \"Spore-App-SDK: Spore ModAPI/Spore/Editors/EditorBaseHandle.h (func30h at /* 30h */, EditorHandleState enum)\",\n      \"Spore-App-SDK: Spore ModAPI/Spore/Editors/EditorRigblock.h (mAxisHandles +0x154, mpRota
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
  "body_end": "0043cdf5",
  "body_span_bytes": 806,
  "body_start": "0043cad0",
  "callees": [
    "FUN_004a88d0",
    "FUN_004adb80",
    "FUN_004adbc0",
    "FUN_0043ce40"
  ],
  "callers": [
    "FUN_00573780",
    "FUN_0057e790",
    "FUN_005757b0",
    "FUN_005b4fa0",
    "FUN_0043a9e0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0043cad0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_5",
      "storage": "Stack[-0x5]:1",
      "type": "undefined1"
    },
    {
      "name": "local_6",
      "storage": "Stack[-0x6]:1",
      "type": "undefined1"
    },
    {
      "name": "local_7",
      "storage": "Stack[-0x7]:1",
      "type": "undefined1"
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
      "name": "local_21",
      "storage": "Stack[-0x21]:1",
      "type": "undefined1"
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
    },
    {
      "name": "local_2d",
      "storage": "Stack[-0x2d]:1",
      "type": "undefined1"
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
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    },
    {
      "name": "local_45",
      "storage": "Stack[-0x45]:1",
      "type": "undefined1"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_51",
      "storage": "Stack[-0x51]:1",
      "type": "undefined1"
    },
    {
      "name": "local_58",
      "storage": "Stack[-0x58]:4",
      "type": "undefined4"
    },
    {
      "name": "local_5c",
      "storage": "Stack[-0x5c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 32,
  "mode": "live",
  "name": "FUN_0043cad0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3cad0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0043cad0(void)",
  "size_bytes": 806,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0043cad0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "0043ab76"
    },
    {
      "from": "005757bd"
    },
    {
      "from": "005737c7"
    },
    {
      "from": "0057e88d"
    },
    {
      "from": "005b5009"
    },
    {
      "from": "005acc23"
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
    "reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/0043cad0_rigblock_handle_sweep.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/0043cad0.json"
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
    "No original-process trace has been captured. A differential run must show which handle classes are actually reached through slot +0x30 and what state 3 does to them.",
    "The relationship between this sweep and the globally gated 0x0043ce40 can only be settled by observing both in one run.",
    "The three attribute bits and the per-handle flag bytes are only ever read in this build; whether any runtime path sets them, and in which order, needs a trace."
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
  "Editors::EditorRigblock (SDK candidate, field-offset match)",
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
