# Evidence 0x004b09b0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0034d4ded0add813607a7eef36549a4523a97c54848085110f10770de6f7faf1`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX, one stack argument, callee pops it)",
  "hidden_receiver": "ECX",
  "hidden_this_register": "ECX is read only by the spill at 0x004b09b6 and then served from the frame",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_note": "(the receiver)",
  "return_observation": "0x004b09f9: MOV EAX,[EBP-8] where [EBP-8] was written from ECX at 0x004b09b6, so the result is always the receiver and is never derived from either pointer argument. The early exit at 0x004b09c1 jumps to the same 0x004b09f9, so the self-assignment case returns the holder too.",
  "return_register": "EAX",
  "return_semantics": "the holder itself, not the assigned pointer and not a status; 0x004b09f9 loads [EBP-8] into EAX, i.e. the address the caller passed in ECX",
  "return_type": "IntrusiveRefHolder*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "offset": "[EBP+8]",
      "role": "the incoming pointer",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single RET 0x4 at 0x004b09ff"
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
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "383a5636da3a7a9781e1b4bec8e402bc0c9412ed94a19696d5ae7fac9fb44d29",
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
    "persisted_calling_convention": "__thiscall (receiver in ECX, one stack argument, callee pops it)"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029"
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
        "obs-0010",
        "obs-0017",
        "obs-0018",
        "obs-0019",
        "obs-0022"
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
        "obs-0010",
        "obs-0011",
        "obs-0012",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0025"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0
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
        "obs-0011",
        "obs-0012",
        "obs-0018",
        "obs-0019",
        "obs-0021",
        "obs-0025",
        "obs-0029"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0018",
        "obs-0019",
        "obs-0022"
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
        "obs-0029"
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
        "obs-0029"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0029"
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
      "at": "0x004b09b0",
      "count": 16,
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
      "at": "0x004b09b0",
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
      "at": "0x004b09b1",
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
      "at": "0x004b09b1",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004b09b3",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg":
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
    "va": "0x004b0590"
  },
  {
    "name": "editor_input_005737d0",
    "reconstructed": true,
    "va": "0x005737d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057e790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00582250"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
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
  "count": 32,
  "instructions": [
    {
      "address": "004b09b0",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004b09b1",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004b09b3",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "004b09b6",
      "instruction": "MOV dword ptr [EBP + -0x8],ECX"
    },
    {
      "address": "004b09b9",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09bc",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09bf",
      "instruction": "CMP ECX,dword ptr [EAX]"
    },
    {
      "address": "004b09c1",
      "instruction": "JZ 0x004b09f9"
    },
    {
      "address": "004b09c3",
      "instruction": "MOV EDX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09c6",
      "instruction": "MOV EAX,dword ptr [EDX]"
    },
    {
      "address": "004b09c8",
      "instruction": "MOV dword ptr [EBP + -0x4],EAX"
    },
    {
      "address": "004b09cb",
      "instruction": "CMP dword ptr [EBP + 0x8],0x0"
    },
    {
      "address": "004b09cf",
      "instruction": "JZ 0x004b09de"
    },
    {
      "address": "004b09d1",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09d4",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "004b09d6",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09d9",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "004b09dc",
      "instruction": "CALL EAX"
    },
    {
      "address": "004b09de",
      "instruction": "MOV ECX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09e1",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004b09e4",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "004b09e6",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "004b09ea",
      "instruction": "JZ 0x004b09f9"
    },
    {
      "address": "004b09ec",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004b09ef",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "004b09f1",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004b09f4",
      "instruction": "MOV EAX,dword ptr [EDX + 0x8]"
    },
    {
      "address": "004b09f7",
      "instruction": "CALL EAX"
    },
    {
      "address": "004b09f9",
      "instruction": "MOV EAX,dword ptr [EBP + -0x8]"
    },
    {
      "address": "004b09fc",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004b09fe",
      "instruction": "POP EBP"
    },
    {
      "address": "004b09ff",
      "instruction": "RET 0x4"
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
  "original_bytes": 7654,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (receiver in ECX, one stack argument, callee pops it)\",\n    \"hidden_receiver\": \"ECX\",\n    \"hidden_this_register\": \"ECX is read only by the spill at 0x004b09b6 and then served from the frame\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_note\": \"(the receiver)\",\n    \"return_observation\": \"0x004b09f9: MOV EAX,[EBP-8] where [EBP-8] was written from ECX at 0x004b09b6, so the result is always the receiver and is never derived from either pointer argument. The early exit at 0x004b09c1 jumps to the same 0x004b09f9, so the self-assignment case returns the holder too.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the holder itself, not the assigned pointer and not a status; 0x004b09f9 loads [EBP-8] into EAX, i.e. the address the caller passed in ECX\",\n    \"return_type\": \"IntrusiveRefHolder*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"offset\": \"[EBP+8]\",\n        \"role\": \"the incoming pointer\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"single RET 0x4 at 0x004b09ff\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b0590\"\n      },\n      {\n        \"name\": \"editor_input_005737d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005737d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057e790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00582250\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x004b06c3\",\n        \"direction\": \"in\",\n        \"other\": \"0x004b0590\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005738e6\",\n        \"direction\": \"in\",\n        \"other\": \"0x005737d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00573cd0\",\n        \"direction\": \"in\",\n        \"other\": \"0x00573c00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057e843\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057e790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005824ce\",\n        \"direction\": \"in\",\n        \"other\": \"0x00582250\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00588afb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00588570\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00588b11\",\n        \"direction\": \"in\",\n        \"other\": \"0x00588570\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00588bf5\",\n        \"direction\": \"in\",\n        \"other\": \"0x00588570\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00589774\",\n        \"direction\": \"in\",\n        \"other\": \"0x00588570\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 6,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x005737d0\",\n      \"0x00588570\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0031\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": null,\n  \"globals\": [\n    \"global:The body contains no absolute address, so it touches no global.\"\n  ],\n  \"integration_status\": null,\n  \"name\": null,\n  \"normalized_symbol\": null,\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": null\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process trace exists for this function. The acquire/store/release order is proved statically but its purpose - which re-entrant write-back it defends against - has not been observed.\",\n      \"The +0x04 and +0x08 callees have never been resolved on a concrete receiver, so the reference-count names remain inferred.\"\n    ],\n    \"validated\": 0\n  },\n  \"runtime
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
  "body_end": "004b0a01",
  "body_span_bytes": 82,
  "body_start": "004b09b0",
  "callees": [],
  "callers": [
    "FUN_0057e790",
    "Editors::cEditor::OnMouseMove",
    "Editors::cEditor::sub_581F70",
    "Editors::cEditor::OnMouseDown",
    "FUN_004b0590",
    "FUN_00573c00"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004b09b0",
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
  "name": "FUN_004b09b0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xb09b0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004b09b0(void)",
  "size_bytes": 82,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004b09b0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 11,
  "xrefs": [
    {
      "from": "004b06c3"
    },
    {
      "from": "005738e6"
    },
    {
      "from": "00573cd0"
    },
    {
      "from": "005824ce"
    },
    {
      "from": "0057e843"
    },
    {
      "from": "00588afb"
    },
    {
      "from": "00588b11"
    },
    {
      "from": "00588bf5"
    },
    {
      "from": "00589774"
    },
    {
      "from": "005ac70b"
    },
    {
      "from": "005b3b7e"
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
  "global:The body contains no absolute address, so it touches no global."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b04/wave13_w1_dispatch_b04_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b04/004b09b0.json"
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
    "No original-process trace exists for this function. The acquire/store/release order is proved statically but its purpose - which re-entrant write-back it defends against - has not been observed.",
    "The +0x04 and +0x08 callees have never been resolved on a concrete receiver, so the reference-count names remain inferred."
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
  "IntrusiveRefHolder* (the receiver)",
  "eastl::intrusive_ptr<Editors::EditorRigblock> (SDK candidate)"
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
