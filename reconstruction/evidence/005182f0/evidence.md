# Evidence 0x005182f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `e8ae966b465768720d44196cfb884233909ab110164ed5381980150fd61343a8`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall, receiver only, no stack arguments",
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0
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
  "content_sha256": "78ec712718eade489d1066b52ca360fd726a3da6c6d470218b48bcf2216a71ad",
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
    "persisted_calling_convention": "thiscall, receiver only, no stack arguments"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0037"
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
        "obs-0014",
        "obs-0015",
        "obs-0023",
        "obs-0026",
        "obs-0028",
        "obs-0029",
        "obs-0032",
        "obs-0034"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          20
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0023",
        "obs-0026",
        "obs-0028",
        "obs-0029",
        "obs-0032",
        "obs-0034",
        "obs-0037"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0037"
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
        "obs-0037"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0037"
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
      "at": "0x005182f0",
      "count": 19,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x005182f0",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": 12
    },
    {
      "at": "0x005182f1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x005182f1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x005182f3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0xc",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x005182f6",
      "count": 5,
      "first_use": 3,
      "first_write_index": 8,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x005182f6",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0007",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x005182f9",
      "id": "obs-0008",
      "index": 4,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067dd00",
      "target": "0x0067dd00"
    },
    {
      "at": "0x005182fe",
      "count": 8,
      "first_use": 5,
      "first_write_index": 6,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0xc],EAX",
      "reg": "EAX"
    },
    {
      "at": "0x005182fe",
      "base": "EBP",
      "disp": -12,
      "id": "obs-0010",
      "index": 5,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0xc],EAX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00518301",
      "base": "EBP",
      "disp": -12,
      "id": "obs-001
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 69,
  "instructions": [
    {
      "address": "005182f0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005182f1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "005182f3",
      "instruction": "SUB ESP,0xc"
    },
    {
      "address": "005182f6",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "005182f9",
      "instruction": "CALL 0x0067dd00"
    },
    {
      "address": "005182fe",
      "instruction": "MOV dword ptr [EBP + -0xc],EAX"
    },
    {
      "address": "00518301",
      "instruction": "MOV EAX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "00518304",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00518306",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "00518309",
      "instruction": "MOV EAX,dword ptr [EDX + 0x44]"
    },
    {
      "address": "0051830c",
      "instruction": "CALL EAX"
    },
    {
      "address": "0051830e",
      "instruction": "MOVZX ECX,AL"
    },
    {
      "address": "00518311",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00518313",
      "instruction": "JZ 0x00518351"
    },
    {
      "address": "00518315",
      "instruction": "MOV dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "0051831c",
      "instruction": "JMP 0x00518327"
    },
    {
      "address": "0051831e",
      "instruction": "MOV EDX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00518321",
      "instruction": "ADD EDX,0x1"
    },
    {
      "address": "00518324",
      "instruction": "MOV dword ptr [EBP + -0x4],EDX"
    },
    {
      "address": "00518327",
      "instruction": "CMP dword ptr [EBP + -0x4],0xc"
    },
    {
      "address": "0051832b",
      "instruction": "JL 0x00518336"
    },
    {
      "address": "0051832d",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00518330",
      "instruction": "CMP dword ptr [EAX + 0x14],0x0"
    },
    {
      "address": "00518334",
      "instruction": "JZ 0x0051834b"
    },
    {
      "address": "00518336",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00518339",
      "instruction": "CALL 0x00517430"
    },
    {
      "address": "0051833e",
      "instruction": "MOVZX ECX,AL"
    },
    {
      "address": "00518341",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00518343",
      "instruction": "JZ 0x00518349"
    },
    {
      "address": "00518345",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00518347",
      "instruction": "JMP 0x005183ad"
    },
    {
      "address": "00518349",
      "instruction": "JMP 0x0051831e"
    },
    {
      "address": "0051834b",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "0051834d",
      "instruction": "JMP 0x005183ad"
    },
    {
      "address": "00518351",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00518354",
      "instruction": "CMP dword ptr [EDX + 0x14],0x0"
    },
    {
      "address": "00518358",
      "instruction": "JNZ 0x0051836d"
    },
    {
      "address": "0051835a",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0051835d",
      "instruction": "CALL 0x00517430"
    },
    {
      "address": "00518362",
      "instruction": "MOVZX EAX,AL"
    },
    {
      "address": "00518365",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00518367",
      "instruction": "JZ 0x0051836d"
    },
    {
      "address": "00518369",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "0051836b",
      "instruction": "JMP 0x005183ad"
    },
    {
      "address": "0051836d",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00518370",
      "instruction": "CMP dword ptr [ECX + 0x14],0x2"
    },
    {
      "address": "00518374",
      "instruction": "JNZ 0x00518389"
    },
    {
      "address": "00518376",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00518379",
      "instruction": "CALL 0x00517430"
    },
    {
      "address": "0051837e",
      "instruction": "MOVZX EDX,AL"
    },
    {
      "address": "00518381",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00518383",
      "instruction": "JZ 0x00518389"
    },
    {
      "address": "00518385",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00518387",
      "instruction": "JMP 0x005183ad"
    },
    {
      "address": "00518389",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0051838c",
      "instruction": "CMP dword ptr [EAX + 0x14],0x3"
    },
    {
      "address": "00518390",
      "instruction": "JNZ 0x005183a5"
    },
    {
      "address": "00518392",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00518395",
      "instruction": "CALL 0x00517430"
    },
    {
      "address": "0051839a",
      "instruction": "MOVZX ECX,AL"
    },
    {
      "address": "0051839d",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0051839f",
      "instruction": "JZ 0x005183a5"
    },
    {
      "address": "005183a1",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005183a3",
      "instruction": "JMP 0x005183ad"
    },
    {
      "address": "005183a5",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "005183a8",
      "instruction": "CALL 0x00517430"
    },
    {
      "address": "005183ad",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "005183af",
      "instruction": "POP EBP"
    },
    {
      "address": "005183b0",
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
  "original_bytes": 8164,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall, receiver only, no stack arguments\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 17,\n      \"symbol\": \"skin_painter_state_setup_00506590\",\n      \"va\": \"0x00506590\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_paint_slot_pass_005183c0\",\n      \"va\": \"0x005183c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_tex0_full_region_00518bf0\",\n      \"va\": \"0x00518bf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_tex2_uv_region_00518cf0\",\n      \"va\": \"0x00518cf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_rig_block_draw_00518f10\",\n      \"va\": \"0x00518f10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_rig_index_pass_0051a350\",\n      \"va\": \"0x0051a350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_job_setup_0051a9a0\",\n      \"va\": \"0x0051a9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Skinner::cSkinPainterJobApplyBrushes\",\n  \"cluster\": null,\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00518339\",\n        \"direction\": \"out\",\n        \"other\": \"0x00517430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0051835d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00517430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00518379\",\n        \"direction\": \"out\",\n        \"other\": \"0x00517430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00518395\",\n        \"direction\": \"out\",\n        \"other\": \"0x00517430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005183a8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00517430\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005182f9\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd00\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x0067dd00\",\n      \"0x00517430\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0040\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [],\n  \"integration_status\": \"integrated\",\n  \"name\": \"skin_painter_job_brush_pass_005182f0\",\n  \"normalized_symbol\": \"skin_painter_job_brush_pass_005182f0\",\n  \"observed_mechanics\": [\n    \"Fetch the graphics probe through the cdecl port 0x0067dd00 exactly once.\",\n    \"Call only the probe vtable slot +0x44; no other probe slot is touched.\",\n    \"When the query result is nonzero, run a bounded loop that stops on a nonzero low byte from the step port 0x00517430.\",\n    \"The loop guard returns 0 when the attempt counter reaches 12 while the pass field at +0x14 is still zero.\",\n    \"The pass field is re-read on every guard evaluation, so a port that mutates it mid-loop changes the outcome.\",\n    \"When the query result is zero, test the step port once for each of the pass values 0, 2 and 3 and return 1 on a nonzero low byte.\",\n    \"Otherwise return the raw 32 bit result of the final step port call unchanged.\",\n    \"No job field other than the pass word is written.\"\n  ],\n  \"ownership\": {\n    \"claimability\": \"do_not_claim\",\n    \"handoff_packages\": [\n      \"PKG-SKINNER-SAFE-WAVE10\"\n    ],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n  
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
  "body_end": "005183b0",
  "body_span_bytes": 193,
  "body_start": "005182f0",
  "callees": [
    "FUN_00517430",
    "FUN_0067dd00"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005182f0",
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
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_005182f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1182f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005182f0(void)",
  "size_bytes": 193,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005182f0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f1a30"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "013f1a94"
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
  "file": "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.cpp",
    "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10.hpp",
    "src/reconstruction/pkg_skinner_safe_wave10/skinner_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-skinner-safe-wave10/005182f0.json"
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
    "Pass field semantics are inferred from 0x00517430, which increments and wraps the counter at 4; that body is owned elsewhere and is not reconstructed here.",
    "The 12 attempt limit is a static property; the runtime distribution of the pass field at the limit is not established.",
    "The vtable cluster at 0x013f1a30 is unattributed in docs/analysis/vtables.json, so slot 25 is bound to this body by the data pointer alone.",
    "The widened 0 and 1 on the short paths follow the repository convention rather than a literal 32 bit store in the original.",
    "gate-skin-painter-brush-pass-runtime-probe-and-step-semantics"
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
  "DATA",
  "OpaqueGraphicsProbe",
  "OpaqueGraphicsProbeVTable",
  "OpaquePainterJob",
  "OpaquePainterJob*",
  "Skinner::cSkinPainterJobApplyBrushes",
  "std::int32_t",
  "unsigned int"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f1a30"
]
```

## Conflicts

```json
[]
```
