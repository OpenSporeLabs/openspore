# Evidence 0x008db310

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6895e4f7d428b10969d95e8fe8ac3079dc5080314985df808258a94d19ba1831`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "x86-32 thiscall, callee cleanup",
    "__thiscall observed"
  ],
  "convention": "__thiscall observed",
  "hidden_receiver": "ECX, the write carrier, read only at +0x2c and +0x30",
  "hidden_this_register": "ECX",
  "hidden_this_type": "PFIndexModifiableWriteCarrier*",
  "ordinary_stack_arguments": [
    {
      "entry_offset": "ESP+0x04",
      "name": "destination",
      "position": 1,
      "read_at": "0x008db31c reads ESP+0x14, which is the entry ESP+0x04 after the four register pushes at 0x008db314..0x008db317",
      "type": "void*",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x08",
      "name": "destination_size",
      "position": 2,
      "read_at": "0x008db310 reads ESP+0x08 into EAX before any push",
      "type": "uint32_t",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x8 at 0x008db384 and 0x008db38d",
  "return_register": "AL",
  "return_semantics": "AL is set to 0x1 at 0x008db381 on the no-overlap path and to 0x0 at 0x008db38a on the overlap path; the function returns true when the destination extent is empty or when no scanned record interval overlaps it, and false on the first overlap",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": "EBX, EBP, ESI, EDI are pushed at 0x008db314..0x008db317 and popped on both exits",
  "stack_arguments": [
    "{'entry_offset': 'ESP+0x04', 'name': 'destination', 'position': 1, 'type': 'void*', 'width_bytes': 4}",
    "{'entry_offset': 'ESP+0x08', 'name': 'destination_size', 'position': 2, 'type': 'uint32_t', 'width_bytes': 4}"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": [
    "two exits, both RET 0x8",
    "RET 0x8 at 0x008db384 and 0x008db38d"
  ]
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
      "entry_ESP+0x8"
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
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -16, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "33c94cba2ecc60450393f51152701a9d7be13a7b16447609b4f1c2df8549745a",
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
    "ghidra_parameter_count": 5,
    "persisted": "no_information",
    "persisted_calling_convention": "['x86-32 thiscall, callee cleanup', '__thiscall observed']"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0022",
        "obs-0027"
      ],
      "claim": "the callee pops 8 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 8,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0009"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0015",
        "obs-0016",
        "obs-0017"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          44,
          48,
          52,
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0015",
        "obs-0016",
        "obs-0017",
        "obs-0022",
        "obs-0027"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0027"
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
        "obs-0022",
        "obs-0027"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0022",
        "obs-0027"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x008db310",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x008db310",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x008db310",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x8]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x008db314",
      "count": 4,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x008db315",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x008db315",
      "ebp_is_general_regis
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
  "count": 57,
  "instructions": [
    {
      "address": "008db310",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "008db314",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008db315",
      "instruction": "PUSH EBP"
    },
    {
      "address": "008db316",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008db317",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008db318",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "008db31a",
      "instruction": "JZ 0x008db37e"
    },
    {
      "address": "008db31c",
      "instruction": "MOV EBX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "008db320",
      "instruction": "MOV EDX,dword ptr [ECX + 0x2c]"
    },
    {
      "address": "008db323",
      "instruction": "LEA EBP,[EBX + EAX*0x1]"
    },
    {
      "address": "008db326",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "008db328",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "008db32a",
      "instruction": "JNZ 0x008db33d"
    },
    {
      "address": "008db32c",
      "instruction": "ADD EDX,0x4"
    },
    {
      "address": "008db32f",
      "instruction": "CMP dword ptr [EDX],EAX"
    },
    {
      "address": "008db331",
      "instruction": "JNZ 0x008db33b"
    },
    {
      "address": "008db333",
      "instruction": "ADD EDX,0x4"
    },
    {
      "address": "008db336",
      "instruction": "CMP dword ptr [EDX],0x0"
    },
    {
      "address": "008db339",
      "instruction": "JZ 0x008db333"
    },
    {
      "address": "008db33b",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "008db33d",
      "instruction": "MOV ESI,dword ptr [ECX + 0x30]"
    },
    {
      "address": "008db340",
      "instruction": "MOV ECX,dword ptr [ECX + 0x2c]"
    },
    {
      "address": "008db343",
      "instruction": "MOV EDI,dword ptr [ECX + ESI*0x4]"
    },
    {
      "address": "008db346",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "008db348",
      "instruction": "JZ 0x008db37e"
    },
    {
      "address": "008db34a",
      "instruction": "LEA EBX,[EBX]"
    },
    {
      "address": "008db350",
      "instruction": "MOV ESI,dword ptr [EAX + 0x10]"
    },
    {
      "address": "008db353",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "008db355",
      "instruction": "JZ 0x008db364"
    },
    {
      "address": "008db357",
      "instruction": "MOV ECX,dword ptr [EAX + 0xc]"
    },
    {
      "address": "008db35a",
      "instruction": "CMP ECX,EBP"
    },
    {
      "address": "008db35c",
      "instruction": "JNC 0x008db364"
    },
    {
      "address": "008db35e",
      "instruction": "ADD ECX,ESI"
    },
    {
      "address": "008db360",
      "instruction": "CMP EBX,ECX"
    },
    {
      "address": "008db362",
      "instruction": "JC 0x008db387"
    },
    {
      "address": "008db364",
      "instruction": "MOV EAX,dword ptr [EAX + 0x1c]"
    },
    {
      "address": "008db367",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "008db369",
      "instruction": "JNZ 0x008db37a"
    },
    {
      "address": "008db36b",
      "instruction": "JMP 0x008db370"
    },
    {
      "address": "008db370",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "008db373",
      "instruction": "ADD EDX,0x4"
    },
    {
      "address": "008db376",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "008db378",
      "instruction": "JZ 0x008db370"
    },
    {
      "address": "008db37a",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "008db37c",
      "instruction": "JNZ 0x008db350"
    },
    {
      "address": "008db37e",
      "instruction": "POP EDI"
    },
    {
      "address": "008db37f",
      "instruction": "POP ESI"
    },
    {
      "address": "008db380",
      "instruction": "POP EBP"
    },
    {
      "address": "008db381",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "008db383",
      "instruction": "POP EBX"
    },
    {
      "address": "008db384",
      "instruction": "RET 0x8"
    },
    {
      "address": "008db387",
      "instruction": "POP EDI"
    },
    {
      "address": "008db388",
      "instruction": "POP ESI"
    },
    {
      "address": "008db389",
      "instruction": "POP EBP"
    },
    {
      "address": "008db38a",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "008db38c",
      "instruction": "POP EBX"
    },
    {
      "address": "008db38d",
      "instruction": "RET 0x8"
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
  "original_bytes": 9593,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"x86-32 thiscall, callee cleanup\",\n      \"__thiscall observed\"\n    ],\n    \"convention\": \"__thiscall observed\",\n    \"hidden_receiver\": \"ECX, the write carrier, read only at +0x2c and +0x30\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"PFIndexModifiableWriteCarrier*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x04\",\n        \"name\": \"destination\",\n        \"position\": 1,\n        \"read_at\": \"0x008db31c reads ESP+0x14, which is the entry ESP+0x04 after the four register pushes at 0x008db314..0x008db317\",\n        \"type\": \"void*\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x08\",\n        \"name\": \"destination_size\",\n        \"position\": 2,\n        \"read_at\": \"0x008db310 reads ESP+0x08 into EAX before any push\",\n        \"type\": \"uint32_t\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x8 at 0x008db384 and 0x008db38d\",\n    \"return_register\": \"AL\",\n    \"return_semantics\": \"AL is set to 0x1 at 0x008db381 on the no-overlap path and to 0x0 at 0x008db38a on the overlap path; the function returns true when the destination extent is empty or when no scanned record interval overlaps it, and false on the first overlap\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": \"EBX, EBP, ESI, EDI are pushed at 0x008db314..0x008db317 and popped on both exits\",\n    \"stack_arguments\": [\n      \"{'entry_offset': 'ESP+0x04', 'name': 'destination', 'position': 1, 'type': 'void*', 'width_bytes': 4}\",\n      \"{'entry_offset': 'ESP+0x08', 'name': 'destination_size', 'position': 2, 'type': 'uint32_t', 'width_bytes': 4}\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": [\n      \"two exits, both RET 0x8\",\n      \"RET 0x8 at 0x008db384 and 0x008db38d\"\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-SKINNER-SAFE-WAVE10\",\n      \"score\": 3,\n      \"symbol\": \"skin_painter_job_brush_pass_005182f0\",\n      \"va\": \"0x005182f0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005bf9d0\",\n      \"va\": \"0x005bf9d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0100\",\n      \"va\": \"0x005c0100\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:DATA\"\n      ],\n      \"package\": \"PKG-18-UI-SCRIPTING\",\n      \"score\": 3,\n      \"symbol\": \"FUN_005c0380\",\n      \"va\": \"0x005c0380\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No direct caller xrefs establish the runtime write-buffer allocation and persistence envelope.\",\n    \"The imported four-parameter prototype is not reconciled beyond the two words consumed by the live body.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0272\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"Resource::PFIndexModifiable::Write\",\n  \"normalized_symbol\": \"Resource::PFIndexModifiable::Write\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No direct caller xref exists, so the producer of the destination pointer and the meaning of the extent word in bytes versus an index count are unconfirmed.\",\n      \"No original-process invocation or indirect-caller trace was captured; runtime_validation stays 0.\",\n      \"The end sentinel at slots[carrier+0x30] is proven as a terminating value but its construction and lifetime are unresolved.\",\n      \"The ow
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
  "body_end": "008db38f",
  "body_span_bytes": 128,
  "body_start": "008db310",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "008db310",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Resource::PFIndexModifiable::Write",
  "namespace": "Resource",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PFIndexModifiable *"
    },
    {
      "name": "pDstIndexData",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "void * *"
    },
    {
      "name": "nDstIndexSize",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "size_t *"
    },
    {
      "name": "nIndexCount",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "size_t"
    },
    {
      "name": "arg_C",
      "ordinal": 4,
      "storage": "Stack[0x14]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x4db310",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Resource::PFIndexModifiable::Write(PFIndexModifiable * this, void * * pDstIndexData, size_t * nDstIndexSize, size_t nIndexCount, bool arg_C)",
  "size_bytes": 128,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x008db310",
  "vtables": {
    "referenced_by_vtables": [
      "0x01436878"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "014368bc"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__PFIndexModifiable__Write.c",
    "reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.cpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.hpp",
    "reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310_model_test.cpp",
    "reconstruction/staging/wave6-resources/pf_index_write.cpp",
    "reconstruction/staging/wave6-resources/pf_index_write.hpp",
    "reconstruction/staging/wave6-resources/property_list_variants_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-orchestrate-dogfood-008db310/008db310.json",
    "reconstruction/metadata/wave6-resources/008db310.json"
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
    "No direct caller xref exists, so the producer of the destination pointer and the meaning of the extent word in bytes versus an index count are unconfirmed.",
    "No original-process invocation or indirect-caller trace was captured; runtime_validation stays 0.",
    "The end sentinel at slots[carrier+0x30] is proven as a terminating value but its construction and lifetime are unresolved.",
    "The owner of the pointer run around 0x01436878 that stores 0x008db310 at 0x014368bc is unknown, so the class that reaches this function and the slot index it occupies are unproved.",
    "The record interval values at node+0x0c and node+0x10 are treated as opaque 32-bit offsets; the buffer they index is not identified from this function."
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DATA",
  "ItemsMap",
  "PFIndexModifiableWriteCarrier*",
  "bool",
  "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::DispatchSlot014368bc",
  "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaqueItemNode",
  "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaquePorts",
  "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaqueWord",
  "openspore::reconstruction::pkg_orchestrate_dogfood_008db310::OpaqueWriteCarrier",
  "uint32_t",
  "void*"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01436878"
]
```

## Conflicts

```json
[]
```
