# Evidence 0x0041dc10

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fcd14989b746a88aa6da3387078a4f6ff87ce6ddda1149b3b31a8226a0a9c6db`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl, caller stack cleanup",
  "hidden_this_register": null,
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": "EAX",
  "return_width_bytes": 4,
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x08",
      "machine_type": "OpaqueVector3*",
      "native_reads": [
        "MOV EAX,[EBP + 0x8] at 0x0041dc71 and 0x0041dc97"
      ],
      "normalized_name": "destination",
      "position": 1,
      "width_bytes": 4
    },
    {
      "entry_offset": "EBP+0x0c",
      "machine_type": "const OpaqueVector3*",
      "native_reads": [
        "MOVSS XMM0,[EAX]",
        "MOVSS XMM0,[EDX+0x4]",
        "MOVSS XMM0,[ECX+0x8]"
      ],
      "normalized_name": "left",
      "position": 2,
      "width_bytes": 4
    },
    {
      "entry_offset": "EBP+0x10",
      "machine_type": "const OpaqueVector3*",
      "native_reads": [
        "ADDSS XMM0,[ECX]",
        "ADDSS XMM0,[EAX+0x4]",
        "ADDSS XMM0,[EDX+0x8]"
      ],
      "normalized_name": "right",
      "position": 3,
      "width_bytes": 4
    }
  ],
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
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "ebp_offset": "EBP+0x10",
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
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
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "ebp_offset": "EBP+0x10",
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "e900663bd2a964d9ee4bf5359882b3c8bd1a087ab135ce25622e133dc1044fa2",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "cdecl, caller stack cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
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
        "obs-0008",
        "obs-0015",
        "obs-0017",
        "obs-0020",
        "obs-0021",
        "obs-0029",
        "obs-0031",
        "obs-0033",
        "obs-0035"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
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
        "obs-0012",
        "obs-0020",
        "obs-0031"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0012",
        "obs-0020",
        "obs-0031"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0031",
        "obs-0033",
        "obs-0035"
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
      "at": "0x0041dc10",
      "count": 24,
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
      "at": "0x0041dc10",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
   
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
    "va": "0x004099b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00409b90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00409dd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00412900"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00413cc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004224b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004364a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00436d80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004381e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043d690"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00440520"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00441440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00448fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044a0e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044ad00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0044c690"
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
  "count": 37,
  "instructions": [
    {
      "address": "0041dc10",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0041dc11",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "0041dc13",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "0041dc16",
      "instruction": "MOV EAX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "0041dc19",
      "instruction": "MOV ECX,dword ptr [EBP + 0x10]"
    },
    {
      "address": "0041dc1c",
      "instruction": "MOVSS XMM0,dword ptr [EAX]"
    },
    {
      "address": "0041dc20",
      "instruction": "ADDSS XMM0,dword ptr [ECX]"
    },
    {
      "address": "0041dc24",
      "instruction": "MOVSS dword ptr [EBP + -0x18],XMM0"
    },
    {
      "address": "0041dc29",
      "instruction": "MOV EDX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "0041dc2c",
      "instruction": "MOV EAX,dword ptr [EBP + 0x10]"
    },
    {
      "address": "0041dc2f",
      "instruction": "MOVSS XMM0,dword ptr [EDX + 0x4]"
    },
    {
      "address": "0041dc34",
      "instruction": "ADDSS XMM0,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0041dc39",
      "instruction": "MOVSS dword ptr [EBP + -0x14],XMM0"
    },
    {
      "address": "0041dc3e",
      "instruction": "MOV ECX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "0041dc41",
      "instruction": "MOV EDX,dword ptr [EBP + 0x10]"
    },
    {
      "address": "0041dc44",
      "instruction": "MOVSS XMM0,dword ptr [ECX + 0x8]"
    },
    {
      "address": "0041dc49",
      "instruction": "ADDSS XMM0,dword ptr [EDX + 0x8]"
    },
    {
      "address": "0041dc4e",
      "instruction": "MOVSS dword ptr [EBP + -0x10],XMM0"
    },
    {
      "address": "0041dc53",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x18]"
    },
    {
      "address": "0041dc58",
      "instruction": "MOVSS dword ptr [EBP + -0xc],XMM0"
    },
    {
      "address": "0041dc5d",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x14]"
    },
    {
      "address": "0041dc62",
      "instruction": "MOVSS dword ptr [EBP + -0x8],XMM0"
    },
    {
      "address": "0041dc67",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x10]"
    },
    {
      "address": "0041dc6c",
      "instruction": "MOVSS dword ptr [EBP + -0x4],XMM0"
    },
    {
      "address": "0041dc71",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0041dc74",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0xc]"
    },
    {
      "address": "0041dc79",
      "instruction": "MOVSS dword ptr [EAX],XMM0"
    },
    {
      "address": "0041dc7d",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0041dc80",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x8]"
    },
    {
      "address": "0041dc85",
      "instruction": "MOVSS dword ptr [ECX + 0x4],XMM0"
    },
    {
      "address": "0041dc8a",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0041dc8d",
      "instruction": "MOVSS XMM0,dword ptr [EBP + -0x4]"
    },
    {
      "address": "0041dc92",
      "instruction": "MOVSS dword ptr [EDX + 0x8],XMM0"
    },
    {
      "address": "0041dc97",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0041dc9a",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "0041dc9c",
      "instruction": "POP EBP"
    },
    {
      "address": "0041dc9d",
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
  "original_bytes": 15800,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"cdecl, caller stack cleanup\",\n    \"hidden_this_register\": null,\n    \"receiver_register\": null,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_width_bytes\": 4,\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"EBP+0x08\",\n        \"machine_type\": \"OpaqueVector3*\",\n        \"native_reads\": [\n          \"MOV EAX,[EBP + 0x8] at 0x0041dc71 and 0x0041dc97\"\n        ],\n        \"normalized_name\": \"destination\",\n        \"position\": 1,\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"EBP+0x0c\",\n        \"machine_type\": \"const OpaqueVector3*\",\n        \"native_reads\": [\n          \"MOVSS XMM0,[EAX]\",\n          \"MOVSS XMM0,[EDX+0x4]\",\n          \"MOVSS XMM0,[ECX+0x8]\"\n        ],\n        \"normalized_name\": \"left\",\n        \"position\": 2,\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"EBP+0x10\",\n        \"machine_type\": \"const OpaqueVector3*\",\n        \"native_reads\": [\n          \"ADDSS XMM0,[ECX]\",\n          \"ADDSS XMM0,[EAX+0x4]\",\n          \"ADDSS XMM0,[EDX+0x8]\"\n        ],\n        \"normalized_name\": \"right\",\n        \"position\": 3,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 8,\n      \"symbol\": \"cursor_buffer_emit_0041e8b0\",\n      \"va\": \"0x0041e8b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE10\",\n      \"score\": 8,\n      \"symbol\": \"property_value_resolve_0041e920\",\n      \"va\": \"0x0041e920\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static x86-32 mechanics, register/stack argument contract, stack cleanup width, RET form, field offsets, constants, strides, vtable slot indices and the compiled terminator were read from the live Ghidra disassembly of SporeApp.exe and re-confirmed against the compiled reconstruction at -O0 and -O2 with and without NDEBUG. Imported SDK signatures are candidate labels only. Concrete vtable owners, port semantics, runtime values and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_semantic_abi_and_runtime_lifecycle_review\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueVector3\",\n  \"cluster\": null,\n  \"confidence\": 0.97,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004099b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00409b90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00409dd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00412900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00413cc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004224b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004364a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00436d80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004381e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043d690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00440520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00441440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00448fa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044a0e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044ad00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044c690\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044d9e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045f5e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0046c900\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004809c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00480e90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00482670\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004834d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004837f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00485960\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004860b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00486910\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00487290\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004878e0\"\n      },\n      {\n       
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
  "body_end": "0041dc9d",
  "body_span_bytes": 142,
  "body_start": "0041dc10",
  "callees": [],
  "callers": [
    "FUN_004878e0",
    "FUN_00488fe0",
    "FUN_0044ad00",
    "FUN_0048d010",
    "FUN_00413cc0",
    "FUN_0043d690",
    "FUN_0044c690",
    "FUN_0049bcc0",
    "FUN_00409b90",
    "FUN_00496d30",
    "FUN_00412900",
    "FUN_0048dcd0",
    "FUN_0050c5a0",
    "FUN_00436d80",
    "FUN_005202f0",
    "FUN_004f2d40",
    "FUN_0044d9e0",
    "FUN_0049ecf0",
    "FUN_00482670",
    "FUN_0053eb10",
    "FUN_004099b0",
    "FUN_00492e70",
    "FUN_0049cb90",
    "FUN_0049a030",
    "Math::BoundingBox::ApplyTransform",
    "FUN_0053f960",
    "FUN_004837f0",
    "FUN_00499410",
    "FUN_004934d0",
    "FUN_00523900",
    "FUN_00496300",
    "FUN_004fcd00",
    "FUN_0049efc0",
    "FUN_004381e0",
    "FUN_004a02b0",
    "FUN_004a4840",
    "FUN_004f7e70",
    "FUN_0049ce40",
    "FUN_004928d0",
    "FUN_004f8a40",
    "FUN_00487290",
    "FUN_00491b40",
    "FUN_0048e590",
    "FUN_004ca6e0",
    "FUN_004a3dc0",
    "FUN_00531510",
    "FUN_00440520",
    "FUN_004fc100",
    "FUN_00485960",
    "FUN_0044a0e0",
    "FUN_0048a690",
    "FUN_004364a0",
    "FUN_004942b0",
    "FUN_004a4d60",
    "FUN_004f96a0",
    "FUN_005087b0",
    "FUN_0045f5e0",
    "FUN_004f7c00",
    "FUN_004d5020",
    "FUN_004a5c70",
    "FUN_00496760",
    "FUN_00522b40",
    "FUN_0049cfd0",
    "FUN_00486910",
    "FUN_0049a2a0",
    "FUN_00448fa0",
    "FUN_004860b0",
    "FUN_0051f0b0",
    "FUN_004cbf00",
    "FUN_004224b0",
    "FUN_0051fb90",
    "FUN_004834d0",
    "FUN_0046c900",
    "FUN_0050c230",
    "FUN_004956b0",
    "FUN_0050c490",
    "FUN_004e95e0",
    "FUN_00488d30",
    "FUN_00441440",
    "FUN_0049d390",
    "FUN_0049de30",
    "FUN_004809c0",
    "FUN_00480e90",
    "FUN_0048c610"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0041dc10",
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
    }
  ],
  "locals_count": 6,
  "mode": "live",
  "name": "FUN_0041dc10",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1dc10",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0041dc10(void)",
  "size_bytes": 142,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0041dc10",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00409bb9"
    },
    {
      "from": "00409e60"
    },
    {
      "from": "00409ffa"
    },
    {
      "from": "0044ad4f"
    },
    {
      "from": "0044adb9"
    },
    {
      "from": "00493573"
    },
    {
      "from": "00449161"
    },
    {
      "from": "00440997"
    },
    {
      "from": "0043dbe8"
    },
    {
      "from": "0043dc7f"
    },
    {
      "from": "0043dce9"
    },
    {
      "from": "00446508"
    },
    {
      "from": "004368b6"
    },
    {
      "from": "004368c6"
    },
    {
      "from": "00436921"
    },
    {
      "from": "0044a393"
    },
    {
      "from": "0044cfe9"
    },
    {
      "from": "0048171b"
    },
    {
      "from": "0048172b"
    },
    {
      "from": "00481821"
    },
    {
      "from": "00481831"
    },
    {
      "from": "00481e8e"
    },
    {
      "from": "00480c94"
    },
    {
      "from": "00482b0f"
    },
    {
      "from": "00482c25"
    },
    {
      "from": "00482c76"
    },
    {
      "from": "00482f06"
    },
    {
      "from": "004929fa"
    },
    {
      "from": "00492bc0"
    },
    {
      "from": "00492c50"
    },
    {
      "from": "00493114"
    },
    {
      "from": "0044df60"
    },
    {
      "from": "004950dc"
    },
    {
      "from": "004950fc"
    },
    {
      "from": "0049f3e7"
    },
    {
      "from": "0049f69b"
    },
    {
      "from": "0049f7c4"
    },
    {
      "from": "0049f9d9"
    },
    {
      "from": "0049fb47"
    },
    {
      "from": "004957ad"
    },
    {
      "from": "004a4aaf"
    },
    {
      "from": "004d5bbc"
    },
    {
      "from": "004d5bfa"
    },
    {
      "from": "004d5d20"
    },
    {
      "from": "004e9776"
    },
    {
      "from": "004e9786"
    },
    {
      "from": "004e9903"
    },
    {
      "from": "00522e0f"
    },
    {
      "from": "00409a79"
    },
    {
      "from": "00409adc"
    },
    {
      "from": "00413d1f"
    },
    {
      "from": "00412f16"
    },
    {
      "from": "00413419"
    },
    {
      "from": "0041390c"
    },
    {
      "from": "0042256f"
    },
    {
      "from": "00422589"
    },
    {
      "from": "0042262a"
    },
    {
      "from": "00422686"
    },
    {
      "from": "004226c1"
    },
    {
      "from": "004226d1"
    },
    {
      "from": "004226e1"
    },
    {
      "from": "
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
    "reconstruction/metadata/pkg-app-safe-wave10/0041dc10.json"
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
    "Aliasing between destination and either source is not guarded and is covered only by the model test.",
    "Floating point addition follows the default SSE rounding mode; no rounding-mode manipulation is observed.",
    "No original-process invocation was captured.",
    "The modelled receiver is only 0x0c bytes wide, so any wider use of the same object is outside this target.",
    "floating point addition follows the default x87/SSE rounding mode; no SSE rounding-mode manipulation is observed",
    "gate-vector3-add-runtime-rounding-and-aliasing",
    "runtime validation not performed; static decompilation and disassembly only",
    "the native body is a leaf, so no dependency port is required and none was introduced",
    "the receiver struct is only 0x0c bytes wide here, so any wider use of the same object is outside this target"
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
  "OpaqueVector3",
  "OpaqueVector3*",
  "const OpaqueVector3*"
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
