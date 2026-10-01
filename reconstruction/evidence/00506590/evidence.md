# Evidence 0x00506590

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0ad8da6ece210aed1973a6e1e50afbb5e09a69c3ef138d7ad68be01d2095c52c`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall with callee stack cleanup",
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_width_bytes": 0,
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x08",
      "machine_type": "std::uint32_t",
      "native_reads": [
        "EBP+0x08 loaded twice per create call, PUSH EAX then PUSH EAX",
        "EBP+0x08 stored verbatim to receiver+0x1c"
      ],
      "normalized_name": "source",
      "position": 1,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBP"
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
  "content_sha256": "36969b70498d2dbe676b37d88546cb8c2cd8916bd50f1db1ae1fdded69159029",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "persisted_calling_convention": "thiscall with callee stack cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0056"
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
        "obs-0012",
        "obs-0014",
        "obs-0027",
        "obs-0028",
        "obs-0038",
        "obs-0039",
        "obs-0047"
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
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0027",
        "obs-0029",
        "obs-0034",
        "obs-0040",
        "obs-0044",
        "obs-0047",
        "obs-0052"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          16,
          20,
          28,
          32,
          36,
          44,
          48
        ],
        "register": "ECX",
        "written_through": 7
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0014",
        "obs-0015",
        "obs-0016",
        "obs-0027",
        "obs-0029",
        "obs-0034",
        "obs-0040",
        "obs-0044",
        "obs-0047",
        "obs-0052",
        "obs-0056"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0014",
        "obs-0027",
        "obs-0028",
        "obs-0038",
        "obs-0039",
        "obs-0047"
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
        "obs-0056"
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
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00506590",
      "count": 37,
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
      "at": "0x00506590",
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
      "sub": 28
    },
    {
      "at": "0x00506591",
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
      "at": "0x00506591",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00506593",
      "definite": true,
      "id": "obs-0005",
      
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
    "va": "0x00521ba0"
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
  "count": 94,
  "instructions": [
    {
      "address": "00506590",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00506591",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00506593",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "00506596",
      "instruction": "MOV dword ptr [EBP + -0x10],ECX"
    },
    {
      "address": "00506599",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0050659b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0050659d",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0050659f",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005065a1",
      "instruction": "PUSH 0x13f116c"
    },
    {
      "address": "005065a6",
      "instruction": "PUSH 0x64"
    },
    {
      "address": "005065a8",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "005065ad",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "005065b0",
      "instruction": "MOV dword ptr [EBP + -0x4],EAX"
    },
    {
      "address": "005065b3",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "005065b7",
      "instruction": "JZ 0x005065ce"
    },
    {
      "address": "005065b9",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "005065bc",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005065bd",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "005065c0",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005065c1",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "005065c4",
      "instruction": "CALL 0x005288f0"
    },
    {
      "address": "005065c9",
      "instruction": "MOV dword ptr [EBP + -0x14],EAX"
    },
    {
      "address": "005065cc",
      "instruction": "JMP 0x005065d5"
    },
    {
      "address": "005065ce",
      "instruction": "MOV dword ptr [EBP + -0x14],0x0"
    },
    {
      "address": "005065d5",
      "instruction": "MOV EDX,dword ptr [EBP + -0x10]"
    },
    {
      "address": "005065d8",
      "instruction": "MOV EAX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "005065db",
      "instruction": "MOV dword ptr [EDX + 0x10],EAX"
    },
    {
      "address": "005065de",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005065e0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005065e2",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005065e4",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005065e6",
      "instruction": "PUSH 0x13f116c"
    },
    {
      "address": "005065eb",
      "instruction": "PUSH 0x64"
    },
    {
      "address": "005065ed",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "005065f2",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "005065f5",
      "instruction": "MOV dword ptr [EBP + -0x8],EAX"
    },
    {
      "address": "005065f8",
      "instruction": "CMP dword ptr [EBP + -0x8],0x0"
    },
    {
      "address": "005065fc",
      "instruction": "JZ 0x00506613"
    },
    {
      "address": "005065fe",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00506601",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00506602",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00506605",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00506606",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "00506609",
      "instruction": "CALL 0x005288f0"
    },
    {
      "address": "0050660e",
      "instruction": "MOV dword ptr [EBP + -0x18],EAX"
    },
    {
      "address": "00506611",
      "instruction": "JMP 0x0050661a"
    },
    {
      "address": "00506613",
      "instruction": "MOV dword ptr [EBP + -0x18],0x0"
    },
    {
      "address": "0050661a",
      "instruction": "MOV EAX,dword ptr [EBP + -0x10]"
    },
    {
      "address": "0050661d",
      "instruction": "MOV ECX,dword ptr [EBP + -0x18]"
    },
    {
      "address": "00506620",
      "instruction": "MOV dword ptr [EAX + 0x14],ECX"
    },
    {
      "address": "00506623",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00506625",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00506627",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00506629",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0050662b",
      "instruction": "PUSH 0x13f116c"
    },
    {
      "address": "00506630",
      "instruction": "PUSH 0x64"
    },
    {
      "address": "00506632",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00506637",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "0050663a",
      "instruction": "MOV dword ptr [EBP + -0xc],EAX"
    },
    {
      "address": "0050663d",
      "instruction": "CMP dword ptr [EBP + -0xc],0x0"
    },
    {
      "address": "00506641",
      "instruction": "JZ 0x00506658"
    },
    {
      "address": "00506643",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00506646",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00506647",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0050664a",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0050664b",
      "instruction": "MOV ECX,dword ptr [EBP + -0xc]"
    },
    {
      "address": "0050664e",
      "instruction": "CALL 0x005288f0"
    },
    {
      "address": "00506653",
      "instruction": "MOV dword ptr [EBP + -0x1c],EAX"
    },
    {
      "address": "00506656",
      "instruction": "JMP 0x0050665f"
    },
    {
      "address": "00506658",
      "instruction": "MOV dword ptr [EBP + -0x1c],0x0"
    },
    {
      "address": "0050665f",
      "instr
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
  "original_bytes": 8922,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall with callee stack cleanup\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 0,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"EBP+0x08\",\n        \"machine_type\": \"std::uint32_t\",\n        \"native_reads\": [\n          \"EBP+0x08 loaded twice per create call, PUSH EAX then PUSH EAX\",\n          \"EBP+0x08 stored verbatim to receiver+0x1c\"\n        ],\n        \"normalized_name\": \"source\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:unsigned int\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 17,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:OpaqueTexturePainter\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 9,\n      \"symbol\": \"skin_tex0_full_region_00518bf0\",\n      \"va\": \"0x00518bf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:OpaqueTexturePainter\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 9,\n      \"symbol\": \"skin_rig_block_draw_00518f10\",\n      \"va\": \"0x00518f10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_paint_slot_pass_005183c0\",\n      \"va\": \"0x005183c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_tex2_uv_region_00518cf0\",\n      \"va\": \"0x00518cf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_rig_index_pass_0051a350\",\n      \"va\": \"0x0051a350\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"skin_job_setup_0051a9a0\",\n      \"va\": \"0x0051a9a0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:unsigned int\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 5,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Skinner::cSkinPainter\",\n  \"cluster\": null,\n  \"confidence\": 0.92,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00521ba0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00521c08\",\n        \"direction\": \"in\",\n        \"other\": \"0x00521ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005065c4\",\n        \"direction\": \"out\",\n        \"other\": \"0x005288f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00506609\",\n        \"direction\": \"out\",\n        \"other\": \"0x005288f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0050664e\",\n        \"direction\": \"out\",\n        \"other\": \"0x005288f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005065a8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005065ed\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00506632\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [\n      \"0x00f473a0\",\n      \"0x005288f0\"\n    ],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0039\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"OBSERVED\",\n  \"globals\": [\n    \"global:0x013eecd8\",\n    \"global:0x01471064\",\n    \"global:0x01485720\"\n  ],\n  \"integration_status\": \"integrated\",\n  \"name\": \"skin_painter_state_setup_00506590\",\n  \"normalized_symbol\": \"skin_painter_state_setup_00506590\",\n  \"observed_mechanics\": [\n    \"Acquire a layer factory three times through the cdecl port 0x00f473a0 with the constants 0x64, 0x013f116c and four trailing zeros.\",\n    \"On a null factory 
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
  "body_end": "005066c6",
  "body_span_bytes": 311,
  "body_start": "00506590",
  "callees": [
    "FUN_00f473a0",
    "FUN_005288f0"
  ],
  "callers": [
    "FUN_00521ba0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00506590",
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
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00506590",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x106590",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00506590(void)",
  "size_bytes": 311,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00506590",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00521c08"
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
  "global:0x013eecd8",
  "global:0x01471064",
  "global:0x01485720"
]
```

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
    "reconstruction/metadata/pkg-skinner-safe-wave10/00506590.json"
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
    "Receiver class identity is taken from the triage record /Spore/Skinner/cSkinPainter; offsets 0x00..0x0f and above 0x30 are not exercised.",
    "The 0x64 size class and the \"Skinner\" tag at 0x013f116c are inferred from the call shape, not from an SDK signature.",
    "The neighbouring 0x005171b0 label is repaired-contained inside this body and no symbol is claimed for it.",
    "The two unresolved callees at 0x00f473a0 and 0x005288f0 are owned elsewhere and remain runtime gated.",
    "gate-skin-painter-setup-runtime-acquire-and-scale-values"
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
  "OpaqueLayerFactory",
  "OpaqueSkinPainterState",
  "OpaqueSkinPainterState*",
  "OpaqueTexturePainter",
  "OpaqueTexturePainter*",
  "Skinner::cSkinPainter",
  "float",
  "std::uint32_t",
  "unsigned int",
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
