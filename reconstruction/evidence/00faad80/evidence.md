# Evidence 0x00faad80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9a684e6c0a7668f853e8062d4f86dc1a9a6b3ce464a2531dc84e2ead586b33f3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_register": "none -- EAX is dead and the x87 stack is empty at both returns",
  "return_semantics": "none. The committed record's phrase 'float_or_x87_in_ST0' is an APPROXIMATION derived by inference RT1 from the presence of an x87 instruction; the bytes do not support it. See implementation.return_type_note and unresolved_questions item 1.",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
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
    "flow_not_modelled: the linear ESP walk ends at +60, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "32705098fe44a648250c10cd95f9208b40a9bcfaa287deeb1daf9d5d4e3fde33",
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
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0021",
        "obs-0082"
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
        "obs-0015",
        "obs-0016"
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
        "obs-0004",
        "obs-0005",
        "obs-0017",
        "obs-0023",
        "obs-0061",
        "obs-0078"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          44,
          252,
          272,
          273,
          276,
          464,
          524,
          528,
          780,
          784,
          788,
          829,
          864,
          868,
          876,
          880,
          2632
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0017",
        "obs-0021",
        "obs-0023",
        "obs-0061",
        "obs-0078",
        "obs-0082"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0021",
        "obs-0082"
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
  "count": 242,
  "instructions": [
    {
      "address": "00faad80",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00faad83",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00faad84",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00faad86",
      "instruction": "MOV EAX,dword ptr [ESI + 0xa48]"
    },
    {
      "address": "00faad8c",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00faad8d",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00faad8f",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00faad91",
      "instruction": "JZ 0x00faade3"
    },
    {
      "address": "00faad93",
      "instruction": "JLE 0x00fab0cc"
    },
    {
      "address": "00faad99",
      "instruction": "DEC EAX"
    },
    {
      "address": "00faad9a",
      "instruction": "MOV dword ptr [ESI + 0xa48],EAX"
    },
    {
      "address": "00faada0",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00faada2",
      "instruction": "JNZ 0x00fab0cc"
    },
    {
      "address": "00faada8",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00faadaa",
      "instruction": "MOV EDX,dword ptr [EAX + 0x80]"
    },
    {
      "address": "00faadb0",
      "instruction": "CALL EDX"
    },
    {
      "address": "00faadb2",
      "instruction": "FLD float ptr [0x01473c70]"
    },
    {
      "address": "00faadb8",
      "instruction": "CMP dword ptr [ESI + 0xfc],EDI"
    },
    {
      "address": "00faadbe",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00faadbf",
      "instruction": "SETNZ AL"
    },
    {
      "address": "00faadc2",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00faadc5",
      "instruction": "MOVZX ECX,AL"
    },
    {
      "address": "00faadc8",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00faadc9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00faadca",
      "instruction": "LEA EDX,[ESP + 0x2c]"
    },
    {
      "address": "00faadce",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00faadcf",
      "instruction": "LEA EAX,[ESP + 0x30]"
    },
    {
      "address": "00faadd3",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00faadd4",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00faadd6",
      "instruction": "CALL 0x00f9b8c0"
    },
    {
      "address": "00faaddb",
      "instruction": "POP EDI"
    },
    {
      "address": "00faaddc",
      "instruction": "POP ESI"
    },
    {
      "address": "00faaddd",
      "instruction": "ADD ESP,0x14"
    },
    {
      "address": "00faade0",
      "instruction": "RET 0x8"
    },
    {
      "address": "00faade3",
      "instruction": "CMP dword ptr [ESI + 0xfc],EDI"
    },
    {
      "address": "00faade9",
      "instruction": "JNZ 0x00fab0cc"
    },
    {
      "address": "00faadef",
      "instruction": "MOV ECX,dword ptr [ESI + 0x2c]"
    },
    {
      "address": "00faadf2",
      "instruction": "MOVSS XMM0,dword ptr [ESI + 0x360]"
    },
    {
      "address": "00faadfa",
      "instruction": "UCOMISS XMM0,dword ptr [ECX + 0x34]"
    },
    {
      "address": "00faadfe",
      "instruction": "LAHF"
    },
    {
      "address": "00faadff",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00faae00",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00faae03",
      "instruction": "JP 0x00faae29"
    },
    {
      "address": "00faae05",
      "instruction": "MOVSS XMM0,dword ptr [ECX + 0x3c]"
    },
    {
      "address": "00faae0a",
      "instruction": "MULSS XMM0,dword ptr [ECX + 0x38]"
    },
    {
      "address": "00faae0f",
      "instruction": "MOVSS XMM1,dword ptr [ESI + 0x364]"
    },
    {
      "address": "00faae17",
      "instruction": "UCOMISS XMM1,XMM0"
    },
    {
      "address": "00faae1a",
      "instruction": "LAHF"
    },
    {
      "address": "00faae1b",
      "instruction": "TEST AH,0x44"
    },
    {
      "address": "00faae1e",
      "instruction": "JP 0x00faae29"
    },
    {
      "address": "00faae20",
      "instruction": "CMP byte ptr [ESI + 0x111],0x0"
    },
    {
      "address": "00faae27",
      "instruction": "JZ 0x00faae96"
    },
    {
      "address": "00faae29",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00faae2b",
      "instruction": "CALL 0x00f977c0"
    },
    {
      "address": "00faae30",
      "instruction": "MOV EAX,dword ptr [ESI + 0x2c]"
    },
    {
      "address": "00faae33",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x3c]"
    },
    {
      "address": "00faae38",
      "instruction": "MULSS XMM0,dword ptr [EAX + 0x38]"
    },
    {
      "address": "00faae3d",
      "instruction": "ADDSS XMM0,dword ptr [EAX + 0x34]"
    },
    {
      "address": "00faae42",
      "instruction": "MOVSS XMM1,dword ptr [EAX + 0x50]"
    },
    {
      "address": "00faae47",
      "instruction": "COMISS XMM0,XMM1"
    },
    {
      "address": "00faae4a",
      "instruction": "MOVSS XMM2,dword ptr [EAX + 0x54]"
    },
    {
      "address": "00faae4f",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "00faae55",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM1"
    },
    {
      "address": "00faae5b",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM2"
    },
    {
      "address": "00faae61",
      "instruction": "LEA EBX,[ESP + 0xc]"
    },
    {
      "address": "00faae65",
      "instruction": "JA 0x00faae6b"
    },
    {
      "address": "00faae67",
      "instruction": "LEA EBX,[ESP + 0x10]"
    },
    {
      "address": "00faae6b",
      "instruction": "CALL 0x0067dd80"
    },
    {
      "address": "00faae70",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00faae72",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00faae74",
      "instruction": "MO
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
  "original_bytes": 11707,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"none -- EAX is dead and the x87 stack is empty at both returns\",\n    \"return_semantics\": \"none. The committed record's phrase 'float_or_x87_in_ST0' is an APPROXIMATION derived by inference RT1 from the presence of an x87 instruction; the bytes do not support it. See implementation.return_type_note and unresolved_questions item 1.\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00faae6b\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab036\",\n        \"direction\": \"out\",\n        \"other\": \"0x00690120\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab047\",\n        \"direction\": \"out\",\n        \"other\": \"0x006909b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00faaf41\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f96370\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab017\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f96f90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00faae2b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f977c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00faadd6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9b8c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab05c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9ba40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab0b0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fa5610\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab03d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00faacd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00faaff3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00faf140\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab000\",\n        \"direction\": \"out\",\n        \"other\": \"0x00faf400\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00faafe6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fb0d20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00faaf0b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fbf570\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fab0c7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fc7b30\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    
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
  "body_end": "00fab0d3",
  "body_span_bytes": 852,
  "body_start": "00faad80",
  "callees": [
    "FUN_00fa5610",
    "FUN_00fc7b30",
    "FUN_00faf140",
    "Graphics::IShadowWorld::Get",
    "FUN_00faacd0",
    "FUN_00f9ba40",
    "FUN_00faf400",
    "FUN_00fb0d20",
    "FUN_00fbf570",
    "FUN_006909b0",
    "FUN_00690120",
    "FUN_00f977c0",
    "FUN_00f9b8c0",
    "FUN_00f96370",
    "FUN_00f96f90"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00faad80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00faad80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xbaad80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00faad80(void)",
  "size_bytes": 852,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00faad80",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8",
      "0x01490c7c"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01490c84"
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
  "global:WARN"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80.cpp",
    "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00faad80/sw2_00faad80_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00faad80/00faad80.json"
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
  "gates": [],
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
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01490be8",
  "vtable:0x01490c7c"
]
```

## Conflicts

```json
[]
```
