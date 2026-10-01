# Evidence 0x0041e920

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4bc709a7b2b31d75598af5913b6c1e2be4bef6dbb07527a2b4f5a9bb0f3c8428`

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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "fe2ce6e0e4b1c37e4fbceb6c7b517fb29fd5258b14c2f82947cfe042aa024651",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0024"
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
        "obs-0010",
        "obs-0014",
        "obs-0015",
        "obs-0017",
        "obs-0019",
        "obs-0020"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          18
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0010",
        "obs-0014",
        "obs-0015",
        "obs-0017",
        "obs-0019",
        "obs-0020",
        "obs-0024"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024"
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
        "obs-0024"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0024"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x0041e920",
      "count": 13,
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
      "at": "0x0041e920",
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
      "sub": 8
    },
    {
      "at": "0x0041e921",
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
      "at": "0x0041e921",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x0041e923",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x0041e926",
      "count": 5,
      "first_use": 3,
      "first_write_index": 12,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x8],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x0041e926",
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
      "at": "0x0041e929",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0008",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0x8]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x0041e929",
      "definite": true,
      "id": "obs-0009",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x0041e92c",
      "count": 4,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0010",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOVZX ECX,word ptr [EAX + 0x12]",
      "reg": "EAX"
    },
    {
      "at": "0x0041e935",
      "base": "EBP",
      "disp": -8,
      "id": "obs-0011",
      "index": 8,
      "key": null,
  
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
    "va": "0x00406570"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00406ef0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00407190"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00407280"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040aeb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040eb70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0040f4a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004147b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004360f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004410d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044f240"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00452080"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0046c000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00471000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0047d950"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004ba150"
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
  "count": 34,
  "instructions": [
    {
      "address": "0041e920",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0041e921",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0041e923",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "0041e926",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "0041e929",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041e92c",
      "instruction": "MOVZX ECX,word ptr [EAX + 0x12]"
    },
    {
      "address": "0041e930",
      "instruction": "CMP ECX,0x1"
    },
    {
      "address": "0041e933",
      "instruction": "JZ 0x0041e941"
    },
    {
      "address": "0041e935",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041e938",
      "instruction": "MOVZX EAX,word ptr [EDX + 0x12]"
    },
    {
      "address": "0041e93c",
      "instruction": "CMP EAX,0x10"
    },
    {
      "address": "0041e93f",
      "instruction": "JNZ 0x0041e978"
    },
    {
      "address": "0041e941",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041e944",
      "instruction": "MOVZX EDX,word ptr [ECX + 0x10]"
    },
    {
      "address": "0041e948",
      "instruction": "AND EDX,0x30"
    },
    {
      "address": "0041e94b",
      "instruction": "JZ 0x0041e959"
    },
    {
      "address": "0041e94d",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041e950",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "0041e952",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "0041e955",
      "instruction": "JMP 0x0041e973"
    },
    {
      "address": "0041e959",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041e95c",
      "instruction": "MOVZX EAX,word ptr [EDX + 0x12]"
    },
    {
      "address": "0041e960",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0041e962",
      "instruction": "JZ 0x0041e96c"
    },
    {
      "address": "0041e964",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041e967",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "0041e96a",
      "instruction": "JMP 0x0041e973"
    },
    {
      "address": "0041e96c",
      "instruction": "MOV dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "0041e973",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "0041e976",
      "instruction": "JMP 0x0041e97d"
    },
    {
      "address": "0041e978",
      "instruction": "MOV EAX,0x15d115d"
    },
    {
      "address": "0041e97d",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0041e97f",
      "instruction": "POP EBP"
    },
    {
      "address": "0041e980",
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
  "original_bytes": 16576,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall, receiver only, no stack arguments\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 8,\n      \"symbol\": \"vector3_add_0041dc10\",\n      \"va\": \"0x0041dc10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 8,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"palette_safe_wave11_load_page_state_005c85d0\",\n      \"va\": \"0x005c85d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-DIRECT-PROPERTY-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"opaque_list_set_property_006a30c0\",\n      \"va\": \"0x006a30c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"palette_row_layout_005c3000\",\n      \"va\": \"0x005c3000\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-SAFE-WAVE10\",\n      \"score\": 2,\n      \"symbol\": \"sporepedia_asset_destroy_00642190\",\n      \"va\": \"0x00642190\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaquePropertySlot\",\n  \"cluster\": null,\n  \"confidence\": 0.94,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00406570\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00406ef0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00407190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00407280\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040aeb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040eb70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0040f4a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004147b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004360f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004410d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044f240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00452080\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0046c000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00471000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0047d950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ba150\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004d2450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ea310\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ee9b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ef190\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004efb20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004f1350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004f5720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004f5c60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00524a50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057d710\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005a51c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstr
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
  "body_end": "0041e980",
  "body_span_bytes": 97,
  "body_start": "0041e920",
  "callees": [],
  "callers": [
    "FUN_00608120",
    "FUN_00eac530",
    "FUN_0064b6b0",
    "FUN_00ef26c0",
    "FUN_00e09d10",
    "FUN_00f17b00",
    "FUN_00f04d10",
    "FUN_00ef0570",
    "FUN_00675700",
    "FUN_00fa3c10",
    "FUN_005e4190",
    "FUN_004f5c60",
    "FUN_00676a20",
    "FUN_00d20e70",
    "FUN_00f46630",
    "FUN_0044f240",
    "FUN_007e67a0",
    "FUN_00df10d0",
    "FUN_00406570",
    "App::Property::GetBool",
    "FUN_00b5a750",
    "FUN_00e47100",
    "FUN_00dee360",
    "FUN_00c45f90",
    "FUN_0104cc90",
    "FUN_005c85d0",
    "FUN_0104cf20",
    "FUN_00fa6c60",
    "FUN_00817040",
    "FUN_00d3d870",
    "FUN_0063d050",
    "FUN_004360f0",
    "FUN_004147b0",
    "FUN_00b01db0",
    "FUN_005cf830",
    "FUN_0040f4a0",
    "FUN_010504a0",
    "FUN_005c1e20",
    "FUN_00ac6aa0",
    "FUN_00524a50",
    "App::DirectPropertyList::SetProperty",
    "FUN_00d47960",
    "FUN_00c4e390",
    "FUN_004efb20",
    "FUN_00b7bd50",
    "FUN_004ef190",
    "FUN_004ba150",
    "FUN_00d30990",
    "FUN_00f9b8c0",
    "FUN_005a5ec0",
    "FUN_00452080",
    "FUN_00d4af80",
    "FUN_0047d950",
    "FUN_00c3fc80",
    "FUN_004f1350",
    "FUN_00731e70",
    "FUN_007d9460",
    "FUN_004410d0",
    "FUN_0101fb40",
    "FUN_00f368b0",
    "FUN_0040eb70",
    "FUN_00f0d8b0",
    "FUN_004ea310",
    "FUN_00c4a980",
    "App::cCellModeStrategy::Initialize",
    "FUN_0040aeb0",
    "FUN_00c38d00",
    "FUN_005e5470",
    "FUN_00dd8640",
    "FUN_00ef7d90",
    "FUN_0057d710",
    "FUN_0104cc40",
    "FUN_01078120",
    "FUN_00c52580",
    "FUN_008178b0",
    "FUN_00645620",
    "FUN_004f5720",
    "FUN_0070aed0",
    "FUN_004d2450",
    "FUN_00407280",
    "FUN_00c63380",
    "FUN_00ef73c0",
    "FUN_00d247f0",
    "FUN_00df1ba0",
    "FUN_00a41280",
    "FUN_00406ef0",
    "FUN_00471000",
    "FUN_004ee9b0",
    "FUN_00e2fcb0",
    "FUN_0046c000",
    "FUN_00ba0770",
    "FUN_00e46600",
    "FUN_00c47e20",
    "FUN_0063caf0",
    "FUN_00fa2a20",
    "FUN_00c45c60",
    "FUN_00c51010",
    "FUN_00de11a0",
    "FUN_00c4ad50",
    "FUN_00605f90",
    "FUN_0070ec80",
    "FUN_008145d0",
    "FUN_00e40700",
    "FUN_00b9b090",
    "FUN_00a415f0",
    "FUN_010409b0",
    "FUN_006661d0",
    "FUN_00efe110",
    "FUN_00e3f2a0",
    "FUN_00d46730",
    "FUN_00c4f4e0",
    "FUN_00ff45e0",
    "FUN_00df6c40",
    "FUN_0075de80",
    "FUN_01070290",
    "FUN_007e6210",
    "FUN_00bb6a30",
    "FUN_00c45a10",
    "FUN_00dfa930",
    "FUN_006634d0",
    "FUN_005a51c0",
    "FUN_00c45340",
    "FUN_00f05dc0",
    "FUN_00b2f350",
    "FUN_00669f50"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0041e920",
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
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_0041e920",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1e920",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0041e920(void)",
  "size_bytes": 97,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0041e920",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "004071c7"
    },
    {
      "from": "007d993b"
    },
    {
      "from": "007d999c"
    },
    {
      "from": "007d99cd"
    },
    {
      "from": "004d2eda"
    },
    {
      "from": "004412e7"
    },
    {
      "from": "0044f3ef"
    },
    {
      "from": "004521c0"
    },
    {
      "from": "0047db19"
    },
    {
      "from": "005c1ea6"
    },
    {
      "from": "005c1ed8"
    },
    {
      "from": "005c8778"
    },
    {
      "from": "005c88a2"
    },
    {
      "from": "005c88d7"
    },
    {
      "from": "005c8a0d"
    },
    {
      "from": "005c8a3e"
    },
    {
      "from": "00675751"
    },
    {
      "from": "00dd86c1"
    },
    {
      "from": "00dd8cde"
    },
    {
      "from": "008170df"
    },
    {
      "from": "00817146"
    },
    {
      "from": "004eee51"
    },
    {
      "from": "004eef04"
    },
    {
      "from": "004eef4d"
    },
    {
      "from": "004ef53d"
    },
    {
      "from": "004efc99"
    },
    {
      "from": "004f16a6"
    },
    {
      "from": "004f18df"
    },
    {
      "from": "004f1a5b"
    },
    {
      "from": "004068b3"
    },
    {
      "from": "0040710d"
    },
    {
      "from": "00407163"
    },
    {
      "from": "00409426"
    },
    {
      "from": "0046c3c1"
    },
    {
      "from": "0047135f"
    },
    {
      "from": "0040b107"
    },
    {
      "from": "0040ef2e"
    },
    {
      "from": "0040f732"
    },
    {
      "from": "00414965"
    },
    {
      "from": "004149bc"
    },
    {
      "from": "0043614b"
    },
    {
      "from": "004361a3"
    },
    {
      "from": "00731ea1"
    },
    {
      "from": "004ba6a0"
    },
    {
      "from": "004ba733"
    },
    {
      "from": "005e55cf"
    },
    {
      "from": "005e56c4"
    },
    {
      "from": "005e56fd"
    },
    {
      "from": "005e5736"
    },
    {
      "from": "005e576
[TRUNCATED]
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
  "file": "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
  "files": [
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.hpp",
    "src/reconstruction/pkg_app_safe_wave10/app_safe_wave10_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave10-safe-core/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-app-safe-wave10/0041e920.json"
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
    "The body is a leaf, so no dependency port was introduced.",
    "The meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only.",
    "The opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it.",
    "The sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established.",
    "gate-property-value-resolve-runtime-kind-and-storage-semantics",
    "no vtable or callee is involved, so no dependency port was introduced",
    "runtime validation not performed; static decompilation and disassembly only",
    "the meaning of the storage mask 0x0030 and of the kind values 0x0001 and 0x0010 is inferred from the compare immediates only",
    "the opaque +0x04..+0x0f region of the slot is never read, so no field evidence exists for it",
    "the sentinel address 0x015d115d is a .data address returned to the caller as a marker; its runtime identity is not established"
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
  "OpaquePropertySlot",
  "const OpaquePropertySlot*",
  "const unsigned char*"
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
