# Evidence 0x00841540

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `95a27a047c329ec3c9f7a5d5a955661fbe6cefef489976b36c38b8934fd97d83`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "__thiscall observed",
  "hidden_this_register": "ECX (ArgScript::FormatParser*)",
  "ordinary_stack_arguments": [
    {
      "index": 0,
      "note": "Two consecutive 32-bit words written at offsets +0 and +4 and returned in EAX; the caller at 0x0082fde0 reads exactly two dwords back from it.",
      "role": "out",
      "stack_offset_at_entry": "[ESP+4]",
      "type": "float *"
    },
    {
      "index": 1,
      "note": "The address of this word is taken three times and passed to both callees, which read the char pointer it holds and advance it.",
      "role": "cursor",
      "stack_offset_at_entry": "[ESP+8]",
      "type": "const char **"
    }
  ],
  "ret_form": "RET 0x8 (0x0084157c and 0x00841588)",
  "return_register": "EAX",
  "return_semantics": "EAX is loaded with the destination pointer by MOV EAX,EDI at 0x00841578 and 0x00841581, immediately before the register pops. The x87 stack is empty at both exits, so no part of the result travels in ST0. The caller confirms this by reading [EAX] and [EAX+0x4] as two MOVSS floats.",
  "return_type": "float *",
  "saved_registers": "ESI and EDI are pushed at 0x00841540..0x00841541 and popped at 0x0084157a..0x0084157b and 0x00841586..0x00841587",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "two exits, both RET 0x8"
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
        "size_inferred": true,
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
        "size_inferred": true,
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
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path"
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
  "content_sha256": "d6f7191851eae5a678d1b7a6f4dac1138e1fc109d5f2252940232247e20fccb5",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0019",
        "obs-0022"
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
        "obs-0006",
        "obs-0011"
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
        "obs-0003"
      ],
      "claim": "ECX carries the receiver: 0x00841540 is slot 41 of the vptr-backed vftable at 0x0141c930, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body takes the address of its incoming ECX (LEA at 0x00841542) and never touches memory through it, and a body that computes an address from a register the vtable dispatch delivered computes it from the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form has no register parameter and never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R2-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_null_test": false,
        "incoming_ecx_reads": 1,
        "incoming_member_leas": 1,
        "member_lea_displacements": [
          76
        ],
        "member_lea_sites": [
          "0x00841542"
        ],
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_address",
        "receiver_register": "ECX",
        "slot_index": 41,
        "table": "0x0141c930"
      }
    },
    {
      "based_on": [
        "obs-0003",
        "obs-0007",
        "obs-0011",
        "obs-0019",
        "obs-0022"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0022"
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
        "obs-0022"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00841540",
      "count": 5,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00841541",
      "count": 7,
      "first_use": 1,
      "first_write_index": 7,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00841542",
      "count": 3,
      "first_use": 2,
      "first_write_index": 5,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "LEA ESI,[ECX + 0x4c]",
  
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
    "va": "0x0082f9a0"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Unknown calling convention */\n\nvoid ArgScript__FormatParser__SetFlag(FormatParser *this,int flag,bool bValue)\n\n{\n  char cVar1;\n  float10 fVar2;\n  \n  fVar2 = (float10)FUN_0083e470(&flag);\n  this->_vftable0 = (FormatParser__vftable *)(float)fVar2;\n  cVar1 = FUN_0083d290(&flag,0x2c);\n  if (cVar1 != '\\0') {\n    fVar2 = (float10)FUN_0083e470(&flag);\n    this->field_04 = (uint32_t)(float)fVar2;\n    return;\n  }\n  this->field_04 = (uint32_t)this->_vftable0;\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 31,
  "instructions": [
    {
      "address": "00841540",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00841541",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00841542",
      "instruction": "LEA ESI,[ECX + 0x4c]"
    },
    {
      "address": "00841545",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00841549",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0084154a",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0084154c",
      "instruction": "CALL 0x0083e470"
    },
    {
      "address": "00841551",
      "instruction": "MOV EDI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00841555",
      "instruction": "PUSH 0x2c"
    },
    {
      "address": "00841557",
      "instruction": "FSTP float ptr [EDI]"
    },
    {
      "address": "00841559",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "0084155d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0084155e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00841560",
      "instruction": "CALL 0x0083d290"
    },
    {
      "address": "00841565",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00841567",
      "instruction": "JZ 0x0084157f"
    },
    {
      "address": "00841569",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "0084156d",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0084156e",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00841570",
      "instruction": "CALL 0x0083e470"
    },
    {
      "address": "00841575",
      "instruction": "FSTP float ptr [EDI + 0x4]"
    },
    {
      "address": "00841578",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "0084157a",
      "instruction": "POP EDI"
    },
    {
      "address": "0084157b",
      "instruction": "POP ESI"
    },
    {
      "address": "0084157c",
      "instruction": "RET 0x8"
    },
    {
      "address": "0084157f",
      "instruction": "FLD float ptr [EDI]"
    },
    {
      "address": "00841581",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "00841583",
      "instruction": "FSTP float ptr [EDI + 0x4]"
    },
    {
      "address": "00841586",
      "instruction": "POP EDI"
    },
    {
      "address": "00841587",
      "instruction": "POP ESI"
    },
    {
      "address": "00841588",
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
  "original_bytes": 12943,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall observed\",\n    \"hidden_this_register\": \"ECX (ArgScript::FormatParser*)\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"index\": 0,\n        \"note\": \"Two consecutive 32-bit words written at offsets +0 and +4 and returned in EAX; the caller at 0x0082fde0 reads exactly two dwords back from it.\",\n        \"role\": \"out\",\n        \"stack_offset_at_entry\": \"[ESP+4]\",\n        \"type\": \"float *\"\n      },\n      {\n        \"index\": 1,\n        \"note\": \"The address of this word is taken three times and passed to both callees, which read the char pointer it holds and advance it.\",\n        \"role\": \"cursor\",\n        \"stack_offset_at_entry\": \"[ESP+8]\",\n        \"type\": \"const char **\"\n      }\n    ],\n    \"ret_form\": \"RET 0x8 (0x0084157c and 0x00841588)\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"EAX is loaded with the destination pointer by MOV EAX,EDI at 0x00841578 and 0x00841581, immediately before the register pops. The x87 stack is empty at both exits, so no part of the result travels in ST0. The caller confirms this by reading [EAX] and [EAX+0x4] as two MOVSS floats.\",\n    \"return_type\": \"float *\",\n    \"saved_registers\": \"ESI and EDI are pushed at 0x00841540..0x00841541 and popped at 0x0084157a..0x0084157b and 0x00841586..0x00841587\",\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"two exits, both RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:FormatParser\",\n        \"shared_vtable:vtable:0x0141c97c\"\n      ],\n      \"package\": \"PKG-ARGSCRIPT-WAVE9\",\n      \"score\": 13,\n      \"symbol\": \"pkg_argscript_get_current_scope_00d1dcd0\",\n      \"va\": \"0x00d1dcd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-argscript-createdefsafe-00841440\",\n      \"score\": 6,\n      \"symbol\": \"argscript_formatparser_create_definition_safe_00841440\",\n      \"va\": \"0x00841440\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"scripting-content\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0082f9a0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0082fde0\",\n        \"direction\": \"in\",\n        \"other\": \"0x0082f9a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00841560\",\n        \"direction\": \"out\",\n        \"other\": \"0x0083d290\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0084154c\",\n        \"direction\": \"out\",\n        \"other\": \"0x0083e470\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00841570\",\n        \"direction\": \"out\",\n        \"other\": \"0x0083e470\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0263\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"ArgScript::FormatParser::SetFlag\",\n  \"normalized_symbol\": \"ArgScript::FormatParser::SetFlag\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"No original-process invocation, no differential trace an
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
  "body_end": "0084158a",
  "body_span_bytes": 75,
  "body_start": "00841540",
  "callees": [
    "FUN_0083d290",
    "FUN_0083e470"
  ],
  "callers": [
    "FUN_0082f9a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00841540",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "bValue",
      "storage": "Stack[0xc]:1",
      "type": "bool"
    },
    {
      "name": "cVar1",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "fVar2",
      "storage": "register:00001100:10",
      "type": "float10"
    },
    {
      "name": "flag",
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "FormatParser *"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "ArgScript::FormatParser::SetFlag",
  "namespace": "ArgScript",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FormatParser *"
    },
    {
      "name": "flag",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "int"
    },
    {
      "name": "bValue",
      "ordinal": 2,
      "storage": "Stack[0xc]:1",
      "type": "bool"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x441540",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void ArgScript::FormatParser::SetFlag(FormatParser * this, int flag, bool bValue)",
  "size_bytes": 75,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00841540",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141c97c",
      "0x0141c9d4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "0082fde0"
    },
    {
      "from": "0141c9d4"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__SetFlag.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__SetFlag.c",
    "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.cpp",
    "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.hpp",
    "reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-formatparser-setflag/00841540.json"
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
    "No original-process invocation, no differential trace and no indirect-caller trace was captured, so runtime_validated remains 0.",
    "The exact numeric type of the destination pair is modelled as two floats on the strength of the x87 store/pop pair and of the caller packing the result as a two-element float array; the decompiler independently typed them float10.",
    "The identity, type and width of the FormatParser sub-object at this+0x4c are unresolved. Only its address is observable; the model holds a single opaque word and SetFlag never dereferences it.",
    "The x87 instruction forms are resolved and are no longer a gate: three independent decoders and a hand ModRM decode all give FSTP, FSTP, FLD. The remaining gates below are unchanged."
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
  "FormatParser",
  "const char **",
  "float *"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141c97c",
  "vtable:0x0141c9d4"
]
```

## Conflicts

```json
[]
```
