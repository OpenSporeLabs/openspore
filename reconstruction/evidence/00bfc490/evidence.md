# Evidence 0x00bfc490

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `81920f55c0245202b74be2475b1e07884ec73aed5e10e3dacf6dfe6c909f0692`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, read once at 0x00bfc491 and never written",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_observation": "0x00bfc49a is FDIVR float ptr [ESI + 0x38], an x87 divide whose only writer of the result is the x87 stack. No EAX or XMM0 write appears in the body, which is why the Ghidra decompilation declares a float10 return and casts it to float; the observed writer is the FPU, not a general-purpose register.",
  "return_register": "ST0",
  "return_semantics": "x87 extended-precision value in ST0",
  "return_type": "float",
  "return_width_bytes": 10,
  "saved_registers": [
    {
      "pop": "0x00bfc49d",
      "push": "0x00bfc490",
      "register": "ESI"
    }
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00bfc49e"
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "ESI"
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
  "content_sha256": "b07c584693071b3613c9f601e8730492e2da874129ebd07695e2383044932fd3",
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
        "obs-0010"
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
        "obs-0002",
        "obs-0003"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          56
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0010"
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
        "obs-0010"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00bfc490",
      "count": 3,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bfc491",
      "count": 1,
      "first_use": 1,
      "first_write_index": null,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00bfc491",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00bfc493",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bfc495",
      "count": 1,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x58]",
      "reg": "EAX"
    },
    {
      "at": "0x00bfc495",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x58]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00bfc498",
      "count": 1,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00bfc498",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 4,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00bfc49d",
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00bfc49e",
      "form": "RET",
      "id": "obs-0010",
      "imm": null,
      "index": 7,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 8,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "INFERRED",
    "distinct_offsets": 2,
    "max_offset": 56,
    "offsets": [
      0,
      56
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-ALIAS",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "APPROXIMATION",
    "register": "ST0",
    "register_class": "float_or_x87",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": nul
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
    "va": "0x00b188b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b685e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bd8660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c02df0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0ba30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0ba70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0bab0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0bb90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c22ae0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c23e90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c26170"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c9cfd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c9e700"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ccc640"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ccefb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd0830"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00e7a4a0",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e62340",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00bfc460",
      "0x00bfc460",
      "0x00bfc490",
      "0x00bfc490",
      "0x00bfc4a0",
      "0x00bfc4a0"
    ],
    "conflict_id": "cell_field_112_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bfc460",
      "0x00bfc540",
      "0x00bfc460",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00bfc460",
      "0x00bfc460",
      "0x00bfc490",
      "0x00bfc490",
      "0x00bfc4a0",
      "0x00bfc4a0",
      "0x00bfc540",
      "0x00bfc540",
      "0x00bfc540"
    ],
    "conflict_id": "creature_death_publication",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 8,
  "instructions": [
    {
      "address": "00bfc490",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bfc491",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00bfc493",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00bfc495",
      "instruction": "MOV EDX,dword ptr [EAX + 0x58]"
    },
    {
      "address": "00bfc498",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bfc49a",
      "instruction": "FDIVR float ptr [ESI + 0x38]"
    },
    {
      "address": "00bfc49d",
      "instruction": "POP ESI"
    },
    {
      "address": "00bfc49e",
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
  "original_bytes": 15268,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX, read once at 0x00bfc491 and never written\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x00bfc49a is FDIVR float ptr [ESI + 0x38], an x87 divide whose only writer of the result is the x87 stack. No EAX or XMM0 write appears in the body, which is why the Ghidra decompilation declares a float10 return and casts it to float; the observed writer is the FPU, not a general-purpose register.\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"x87 extended-precision value in ST0\",\n    \"return_type\": \"float\",\n    \"return_width_bytes\": 10,\n    \"saved_registers\": [\n      {\n        \"pop\": \"0x00bfc49d\",\n        \"push\": \"0x00bfc490\",\n        \"register\": \"ESI\"\n      }\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET at 0x00bfc49e\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b188b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b685e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bd8660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c02df0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0ba30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0ba70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0bab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0bb90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c22ae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c23e90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c26170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c9cfd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c9e700\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ccc640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ccefb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd0830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ce8d00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cea970\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2b6b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2b720\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2b950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2dd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d41a70\"\n      },\n      {\n 
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
  "body_end": "00bfc49e",
  "body_span_bytes": 15,
  "body_start": "00bfc490",
  "callees": [],
  "callers": [
    "FUN_00d7d160",
    "FUN_00b188b0",
    "FUN_00d71060",
    "FUN_00d2dd20",
    "FUN_00cd0830",
    "FUN_00d2b6b0",
    "FUN_00db7190",
    "FUN_00c26170",
    "FUN_00c0ba30",
    "FUN_00f0e6e0",
    "FUN_00e934f0",
    "FUN_00c02df0",
    "FUN_00db4370",
    "FUN_00c9e700",
    "FUN_00c0bb90",
    "FUN_00d824a0",
    "FUN_00ccefb0",
    "FUN_01072680",
    "FUN_00c9cfd0",
    "FUN_00d2b950",
    "FUN_00d2b720",
    "FUN_00c22ae0",
    "FUN_00d41a70",
    "FUN_00f0e520",
    "FUN_00ccc640",
    "FUN_00d62010",
    "FUN_00b685e0",
    "FUN_00cea970",
    "FUN_00ce8d00",
    "FUN_00c0bab0",
    "FUN_00c0ba70",
    "FUN_00da9800",
    "FUN_00bd8660",
    "FUN_00dc57a0",
    "FUN_00e93f50",
    "FUN_00c23e90",
    "FUN_00e07e70",
    "FUN_00f0efa0",
    "FUN_00f10bd0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00bfc490",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00bfc490",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7fc490",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bfc490(void)",
  "size_bytes": 15,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bfc490",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 55,
  "xrefs": [
    {
      "from": "00c0ba8a"
    },
    {
      "from": "00c0bb96"
    },
    {
      "from": "00bd86fc"
    },
    {
      "from": "010726fc"
    },
    {
      "from": "00c02e2e"
    },
    {
      "from": "00d7d1de"
    },
    {
      "from": "00c22b1f"
    },
    {
      "from": "00c23e9e"
    },
    {
      "from": "00c9e726"
    },
    {
      "from": "00c9e739"
    },
    {
      "from": "00ccc6ee"
    },
    {
      "from": "00ccf587"
    },
    {
      "from": "00ccf596"
    },
    {
      "from": "00ccf9e0"
    },
    {
      "from": "00ccf9f3"
    },
    {
      "from": "00c9cff4"
    },
    {
      "from": "00ceaa5b"
    },
    {
      "from": "00b1891b"
    },
    {
      "from": "00d2b9a1"
    },
    {
      "from": "00d41f4b"
    },
    {
      "from": "00d62093"
    },
    {
      "from": "00d620a8"
    },
    {
      "from": "00d620b7"
    },
    {
      "from": "00c0ba4a"
    },
    {
      "from": "00d82e0a"
    },
    {
      "from": "00da9825"
    },
    {
      "from": "00db7655"
    },
    {
      "from": "00dc58e3"
    },
    {
      "from": "00ce8d0b"
    },
    {
      "from": "00e07fff"
    },
    {
      "from": "00e941c8"
    },
    {
      "from": "00f10d2f"
    },
    {
      "from": "00f10fe6"
    },
    {
      "from": "00f0e564"
    },
    {
      "from": "00f0e5c9"
    },
    {
      "from": "00f0e93e"
    },
    {
      "from": "00f0eff1"
    },
    {
      "from": "00b68697"
    },
    {
      "from": "00c261ef"
    },
    {
      "from": "00d715dc"
    },
    {
      "from": "00db45af"
    },
    {
      "from": "00c0baca"
    },
    {
      "from": "00c24497"
    },
    {
      "from": "00c9cb92"
    },
    {
      "from": "00cabc6f"
    },
    {
      "from": "00d2de08"
    },
    {
      "from": "00d2b6bd"
    },
    {
      "from": "00d2b764"
    },
    {
      "from": "00d2b7c9"
    },
    {
      "from": "00e8a897"
    },
    {
      "from": "00e93774"
    },
    {
      "from": "00e97072"
    },
    {
      "from": "00cd0864"
    },
    {
      "from": "00d7710d"
    },
    {
      "from": "00db29f3"
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
    "reconstruction/staging/wave13-pilot-core-b01/bfc490_combatant_ratio.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_model_test.cpp",
    "reconstruction/staging/wave13-pilot-core-b01/wave13_pilot_core_b01_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-pilot-core-b01/00bfc490.json"
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
    "A runtime trace would be needed to see which override of slot +0x58 is reached for a real creature, to observe the actual return values of the ratio in play, and to check whether the divisor is ever zero.",
    "No original-process trace exists for 0x00bfc490; every claim is static.",
    "The runtime values of the six threshold and scale globals cannot be recovered statically because they are zero in the file image."
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
  "float"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x00e7a4a0",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e7a4a0",
      "0x00e62340",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00e7a7c0",
      "0x00bfc460",
      "0x00bfc460",
      "0x00bfc490",
      "0x00bfc490",
      "0x00bfc4a0",
      "0x00bfc4a0"
    ],
    "conflict_id": "cell_field_112_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00bfc460",
      "0x00bfc540",
      "0x00bfc460",
      "0x00e7e6c0",
      "0x00e7a4a0",
      "0x00e52910",
      "0x00e7a7c0",
      "0x00bfc460",
      "0x00bfc460",
      "0x00bfc490",
      "0x00bfc490",
      "0x00bfc4a0",
      "0x00bfc4a0",
      "0x00bfc540",
      "0x00bfc540",
      "0x00bfc540"
    ],
    "conflict_id": "creature_death_publication",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "resolution_status": "The cited producer, consumer, or registration surface is retained, but the complete event-to-message mapping, timing, and payload contract remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
