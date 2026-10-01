# Evidence 0x008dff30

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `5911645acd3a095b2320f349e37616c4a9aad997527a46fcf0940ee388e2701a`

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
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x04",
    "entry_ESP+0x08"
  ],
  "ordinary_stack_arguments": 2,
  "ret_form": "RET 0x8",
  "return_register": "EAX",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8 at 0x008e001f and 0x008e00ab"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
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
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "7cc153acab8c3969dc71dd5d7661ae9b2b9a595bb4bb36018ce75b7952e2f6d9",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
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
        "obs-0042",
        "obs-0058"
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
        "obs-0009"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0025",
        "obs-0028",
        "obs-0050"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          52,
          56,
          60
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0042",
        "obs-0058"
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
        "obs-0042",
        "obs-0058"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0042",
        "obs-0058"
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
      "and_esp": null,
      "at": "0x008dff30",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x008dff30",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x008dff33",
      "count": 8,
      "first_use": 1,
      "first_write_index": 30,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x008dff34",
      "count": 8,
      "first_use": 2,
      "first_write_index": 9,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x008dff35",
      "count": 7,
      "first_use": 3,
      "first_write_index": 33,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x008dff36",
      "count": 7,
      "first_use": 4,
      "first_write_index": 5,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x008dff37",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": 
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
  "count": 132,
  "instructions": [
    {
      "address": "008dff30",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "008dff33",
      "instruction": "PUSH EBX"
    },
    {
      "address": "008dff34",
      "instruction": "PUSH EBP"
    },
    {
      "address": "008dff35",
      "instruction": "PUSH ESI"
    },
    {
      "address": "008dff36",
      "instruction": "PUSH EDI"
    },
    {
      "address": "008dff37",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "008dff39",
      "instruction": "CMP dword ptr [ESP + 0x28],-0x1"
    },
    {
      "address": "008dff3e",
      "instruction": "JNZ 0x008e0022"
    },
    {
      "address": "008dff44",
      "instruction": "MOV EAX,dword ptr [ECX + 0x34]"
    },
    {
      "address": "008dff47",
      "instruction": "MOV EBP,dword ptr [EAX]"
    },
    {
      "address": "008dff49",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "008dff4d",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "008dff4f",
      "instruction": "JNZ 0x008dff71"
    },
    {
      "address": "008dff51",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "008dff54",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "008dff58",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "008dff5a",
      "instruction": "JNZ 0x008dff6b"
    },
    {
      "address": "008dff5c",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "008dff60",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "008dff63",
      "instruction": "CMP dword ptr [EAX],EDI"
    },
    {
      "address": "008dff65",
      "instruction": "JZ 0x008dff60"
    },
    {
      "address": "008dff67",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "008dff6b",
      "instruction": "MOV EBP,dword ptr [EAX]"
    },
    {
      "address": "008dff6d",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "008dff71",
      "instruction": "MOV EDX,dword ptr [ECX + 0x38]"
    },
    {
      "address": "008dff74",
      "instruction": "MOV ECX,dword ptr [ECX + 0x34]"
    },
    {
      "address": "008dff77",
      "instruction": "MOV EDX,dword ptr [ECX + EDX*0x4]"
    },
    {
      "address": "008dff7a",
      "instruction": "MOV dword ptr [ESP + 0x18],EDX"
    },
    {
      "address": "008dff7e",
      "instruction": "CMP EBP,EDX"
    },
    {
      "address": "008dff80",
      "instruction": "JZ 0x008e00a2"
    },
    {
      "address": "008dff86",
      "instruction": "MOV EBX,dword ptr [ESP + 0x24]"
    },
    {
      "address": "008dff8a",
      "instruction": "LEA EBX,[EBX]"
    },
    {
      "address": "008dff90",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "008dff93",
      "instruction": "MOV ESI,dword ptr [EBP + 0x4]"
    },
    {
      "address": "008dff96",
      "instruction": "MOV dword ptr [ESP + 0x24],ECX"
    },
    {
      "address": "008dff9a",
      "instruction": "CMP ESI,ECX"
    },
    {
      "address": "008dff9c",
      "instruction": "JZ 0x008dfff2"
    },
    {
      "address": "008dff9e",
      "instruction": "MOV EDI,EDI"
    },
    {
      "address": "008dffa0",
      "instruction": "PUSH 0xd1"
    },
    {
      "address": "008dffa5",
      "instruction": "PUSH 0x13ebb38"
    },
    {
      "address": "008dffaa",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "008dffac",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "008dffae",
      "instruction": "INC EDI"
    },
    {
      "address": "008dffaf",
      "instruction": "PUSH 0x13f2150"
    },
    {
      "address": "008dffb4",
      "instruction": "MOV dword ptr [ESP + 0x3c],EDI"
    },
    {
      "address": "008dffb8",
      "instruction": "MOV EDI,dword ptr [ESI]"
    },
    {
      "address": "008dffba",
      "instruction": "PUSH 0xc"
    },
    {
      "address": "008dffbc",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "008dffc1",
      "instruction": "LEA ECX,[EAX + 0x8]"
    },
    {
      "address": "008dffc4",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "008dffc7",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "008dffc9",
      "instruction": "JZ 0x008dffcd"
    },
    {
      "address": "008dffcb",
      "instruction": "MOV dword ptr [ECX],EDI"
    },
    {
      "address": "008dffcd",
      "instruction": "MOV EDI,dword ptr [ESP + 0x28]"
    },
    {
      "address": "008dffd1",
      "instruction": "MOV dword ptr [EAX],EBX"
    },
    {
      "address": "008dffd3",
      "instruction": "MOV EDX,dword ptr [EBX + 0x4]"
    },
    {
      "address": "008dffd6",
      "instruction": "MOV dword ptr [EAX + 0x4],EDX"
    },
    {
      "address": "008dffd9",
      "instruction": "MOV ECX,dword ptr [EBX + 0x4]"
    },
    {
      "address": "008dffdc",
      "instruction": "ADD ESI,0x8"
    },
    {
      "address": "008dffdf",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "008dffe1",
      "instruction": "MOV dword ptr [EBX + 0x4],EAX"
    },
    {
      "address": "008dffe4",
      "instruction": "CMP ESI,dword ptr [ESP + 0x24]"
    },
    {
      "address": "008dffe8",
      "instruction": "JNZ 0x008dffa0"
    },
    {
      "address": "008dffea",
      "instruction": "MOV EDX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "008dffee",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "008dfff2",
      "instruction": "MOV EBP,dword ptr [EBP + 0x18]"
    },
    {
      "address": "008dfff5",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "008dfff7",
      "instruction": "JNZ 0x008e000e"
    },
    {
      "address": "008dfff9",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "008e0000",
      "instruction": "MOV EBP,dword ptr
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
  "original_bytes": 7102,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x04\",\n      \"entry_ESP+0x08\"\n    ],\n    \"ordinary_stack_arguments\": 2,\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8 at 0x008e001f and 0x008e00ab\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"No direct caller or SDK prototype pins the declared order or spelling of the two stack words, so the parameter names are modelling choices.\",\n    \"The destination container is only known through its node layout, so no EASTL or std list type name is claimed.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x008e0031\",\n        \"direction\": \"out\",\n        \"other\": \"0x00aea1b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x008dffbc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x008e0078\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0276\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"Resource::cResourceManager::GetTypenameFromType\",\n  \"normalized_symbol\": \"Resource::cResourceManager::GetTypenameFromType\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__cResourceManager__GetTypenameFromType.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__cResourceManager__GetTypenameFromType.c\",\n      \"reconstruction/staging/wave6-resource-typename-map/typename_from_type.cpp\",\n      \"reconstruction/staging/wave6-resource-typename-map/typename_from_type.hpp\",\n      \"reconstruction/staging/wave6-resource-typename-map/typename_from_type_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/wave6-resource-typename-map/008dff30.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"Resource\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"resource-io\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \
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
  "body_end": "008e00ad",
  "body_span_bytes": 382,
  "body_start": "008dff30",
  "callees": [
    "FUN_00aea1b0",
    "FUN_00f473a0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "008dff30",
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
      "name": "local_20",
      "storage": "Stack[-0x20]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "Resource::cResourceManager::GetTypenameFromType",
  "namespace": "Resource",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cResourceManager *"
    },
    {
      "name": "nTypeID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "wchar16 *",
  "return_type_resolved": true,
  "rva": "0x4dff30",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "wchar16 * Resource::cResourceManager::GetTypenameFromType(cResourceManager * this, uint32_t nTypeID)",
  "size_bytes": 382,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x008dff30",
  "vtables": {
    "referenced_by_vtables": [
      "0x01436ae8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01436b34"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__cResourceManager__GetTypenameFromType.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__cResourceManager__GetTypenameFromType.c",
    "reconstruction/staging/wave6-resource-typename-map/typename_from_type.cpp",
    "reconstruction/staging/wave6-resource-typename-map/typename_from_type.hpp",
    "reconstruction/staging/wave6-resource-typename-map/typename_from_type_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave6-resource-typename-map/008dff30.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::uint32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01436ae8"
]
```

## Conflicts

```json
[]
```
