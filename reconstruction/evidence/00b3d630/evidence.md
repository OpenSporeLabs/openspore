# Evidence 0x00b3d630

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5d6f70e1a5c4a1d063fab1536e11f071c228efe436d583fce8d7c3e6d8a0f6e8`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX, moved to ESI at 0x00b3d637 and never rewritten",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00b3d64f FLD float ptr [ESP + 0x8] and 0x00b3d678 FLD float ptr [ESP + 0x4] are the only two value producers; 0x00b3d67c and 0x00b3d68e FMUL float ptr [ESI + 0x10] are the only arithmetic. Callers confirm: 0x00b3e40c and 0x00b3e417 FSTP the result into stack locals, and 0x00b42687 FLD ST0 / 0x00b42689 FLD ST1 duplicate it, which only makes sense for a value already on the x87 stack.",
  "return_register": "ST(0) (x87)",
  "return_semantics": "IEEE-754 single delivered on the x87 stack in ST(0). The body uses FLD and FMUL and never executes FSTP, so the value is left on the x87 register stack for the caller.",
  "return_type": "float",
  "return_width_bytes": 4,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "d5ce2b09ddc1a5625668b06fe8c40f0d3987fb781e4c32e2a7d9141291ff1440",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0015",
        "obs-0021",
        "obs-0027"
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
        "obs-0018",
        "obs-0019"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
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
        "obs-0022",
        "obs-0023"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          16,
          24,
          64
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0015",
        "obs-0021",
        "obs-0022",
        "obs-0023",
        "obs-0027"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0015",
        "obs-0021",
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
        "obs-0001"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00b3d630",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00b3d630",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x8",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b3d633",
      "count": 4,
      "first_use": 1,
      "first_write_index": 1,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0"
    },
    {
      "at": "0x00b3d633",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XORPS XMM0,XMM0",
      "reg": "XMM0",
      "write_kind": "unknown"
    },
    {
      "at": "0x00b3d636",
      "count": 7,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b3d637",
      "count": 2,
      "first_use": 3,
      "first_write_index": 28,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b3d637",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b3d639",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOVSS XMM1,dword ptr [ESI + 0x18]",
      "reg": "XMM1",
      "write_kind": "unknown"
    },
    {
      "at": "0x00b3d63e",
      "count": 2,
    
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
    "va": "0x00b3e3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b40a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b425b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b42760"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b43790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b43d50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b47730"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b4b320"
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
  "count": 36,
  "instructions": [
    {
      "address": "00b3d630",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00b3d633",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00b3d636",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00b3d637",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00b3d639",
      "instruction": "MOVSS XMM1,dword ptr [ESI + 0x18]"
    },
    {
      "address": "00b3d63e",
      "instruction": "COMISS XMM1,XMM0"
    },
    {
      "address": "00b3d641",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00b3d647",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM1"
    },
    {
      "address": "00b3d64d",
      "instruction": "JBE 0x00b3d658"
    },
    {
      "address": "00b3d64f",
      "instruction": "FLD float ptr [ESP + 0x8]"
    },
    {
      "address": "00b3d653",
      "instruction": "POP ESI"
    },
    {
      "address": "00b3d654",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00b3d657",
      "instruction": "RET"
    },
    {
      "address": "00b3d658",
      "instruction": "MOV EAX,dword ptr [ESI + 0x4]"
    },
    {
      "address": "00b3d65b",
      "instruction": "SUB EAX,0x0"
    },
    {
      "address": "00b3d65e",
      "instruction": "JZ 0x00b3d684"
    },
    {
      "address": "00b3d660",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00b3d663",
      "instruction": "JZ 0x00b3d684"
    },
    {
      "address": "00b3d665",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00b3d668",
      "instruction": "JNZ 0x00b3d678"
    },
    {
      "address": "00b3d66a",
      "instruction": "MOV EAX,dword ptr [ESI + 0x40]"
    },
    {
      "address": "00b3d66d",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x44]"
    },
    {
      "address": "00b3d672",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00b3d678",
      "instruction": "FLD float ptr [ESP + 0x4]"
    },
    {
      "address": "00b3d67c",
      "instruction": "FMUL float ptr [ESI + 0x10]"
    },
    {
      "address": "00b3d67f",
      "instruction": "POP ESI"
    },
    {
      "address": "00b3d680",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00b3d683",
      "instruction": "RET"
    },
    {
      "address": "00b3d684",
      "instruction": "MOV ECX,dword ptr [ESI + 0x40]"
    },
    {
      "address": "00b3d687",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00b3d689",
      "instruction": "MOV EAX,dword ptr [EDX + 0x70]"
    },
    {
      "address": "00b3d68c",
      "instruction": "CALL EAX"
    },
    {
      "address": "00b3d68e",
      "instruction": "FMUL float ptr [ESI + 0x10]"
    },
    {
      "address": "00b3d691",
      "instruction": "POP ESI"
    },
    {
      "address": "00b3d692",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00b3d695",
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
  "original_bytes": 9743,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read\",\n    \"hidden_this_register\": \"ECX, moved to ESI at 0x00b3d637 and never rewritten\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x00b3d64f FLD float ptr [ESP + 0x8] and 0x00b3d678 FLD float ptr [ESP + 0x4] are the only two value producers; 0x00b3d67c and 0x00b3d68e FMUL float ptr [ESI + 0x10] are the only arithmetic. Callers confirm: 0x00b3e40c and 0x00b3e417 FSTP the result into stack locals, and 0x00b42687 FLD ST0 / 0x00b42689 FLD ST1 duplicate it, which only makes sense for a value already on the x87 stack.\",\n    \"return_register\": \"ST(0) (x87)\",\n    \"return_semantics\": \"IEEE-754 single delivered on the x87 stack in ST(0). The body uses FLD and FMUL and never executes FSTP, so the value is left on the x87 register stack for the caller.\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b3e3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b40a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b425b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b42760\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b43790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b43d50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b47730\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b4b320\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00b3e407\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b3e3e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b3e412\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b3e3e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b40a50\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b40a20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b40a5b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b40a20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b42682\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b425b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b4322f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b42760\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b437bc\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b43790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b43d95\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b43d50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b47812\",\n        \"direct
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
  "body_end": "00b3d695",
  "body_span_bytes": 102,
  "body_start": "00b3d630",
  "callees": [],
  "callers": [
    "FUN_00b425b0",
    "FUN_00b3e3e0",
    "FUN_00b42760",
    "FUN_00b40a20",
    "FUN_00b43790",
    "FUN_00b47730",
    "FUN_00b4b320",
    "FUN_00b43d50"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00b3d630",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "FUN_00b3d630",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d630",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d630(void)",
  "size_bytes": 102,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d630",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00b47812"
    },
    {
      "from": "00b3e407"
    },
    {
      "from": "00b3e412"
    },
    {
      "from": "00b42682"
    },
    {
      "from": "00b4322f"
    },
    {
      "from": "00b437bc"
    },
    {
      "from": "00b4b336"
    },
    {
      "from": "00b43d95"
    },
    {
      "from": "00b40a50"
    },
    {
      "from": "00b40a5b"
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
    "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_scale_00b3d630.cpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_scale_00b3d630.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_scale_00b3d630_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b09/00b3d630.json"
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
    "A differential fixture would need a constructed owner with a concrete sub-object instance, which static evidence alone cannot supply.",
    "No original-process trace exists for this address, so the value returned by the +0x70 slot, the runtime contents of the sub-object and the real distribution of selector values are all unverified.",
    "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed."
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
  "dword enum",
  "float",
  "pointer to polymorphic sub-object"
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
