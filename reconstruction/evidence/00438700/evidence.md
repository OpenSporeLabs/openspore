# Evidence 0x00438700

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `68e7bf31bd5558bb097516e722ebece9ae48e9870473bd5cbf962cd6805c1d6a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32 (x86:LE:32:windows, image base 0x00400000)",
  "calling_convention": "__thiscall",
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_observation": "0x004388a2: MOV ESP,EBP / 0x004388a4: POP EBP / 0x004388a5: RET 0x4 with no value in EAX that any caller could use; the sampled callers all discard the result.",
  "return_register": "none (void)",
  "return_semantics": "No value is returned. EAX is used only as scratch; the last write to EAX on any path is either the flag byte at 0x00438777 / 0x0043877c / 0x00438845 / 0x0043884a or the address 0x0043882c used to set up the bit mask.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "EBP+0x8",
      "name": "other",
      "observed_uses": [
        "0x0043874d: MOV ECX,dword ptr [EAX + EDX*0x4 + 0xdc8] -- bit 7 of the other object's attribute field",
        "0x004387a1 / 0x004387b3: MOV EDX / MOV ECX,dword ptr [ECX + 0x3e0] -- the other object's sub-object",
        "0x00438710: PUSH EAX then CALL 0x004388b0"
      ],
      "read_evidence": "0x00438709: MOV EAX,dword ptr [EBP + 0x8]",
      "type": "OpaqueEditorRigblock* (pointer-like)",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single shared exit at 0x004388a2 reached by every path"
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
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "909b75f05d67524e9d82551bb50546f70bd507fd4cf4a1fc55bad5ed31f9ed45",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0064"
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
        "obs-0008",
        "obs-0019",
        "obs-0028",
        "obs-0031",
        "obs-0038",
        "obs-0053",
        "obs-0058"
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
        "obs-0011",
        "obs-0012",
        "obs-0014",
        "obs-0017",
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0032",
        "obs-0035",
        "obs-0036",
        "obs-0041",
        "obs-0048",
        "obs-0049",
        "obs-0055",
        "obs-0056",
        "obs-0060",
        "obs-0061"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          40,
          992
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0011",
        "obs-0012",
        "obs-0014",
        "obs-0017",
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0032",
        "obs-0035",
        "obs-0036",
        "obs-0041",
        "obs-0048",
        "obs-0049",
        "obs-0055",
        "obs-0056",
        "obs-0060",
        "obs-0061",
        "obs-0064"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0064"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00438700",
      "count": 46,
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
      "at": "0x00438700",
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
      "sub": 52
    },
    {
      "at": "0x00438701",
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
      "at": "0x00438701",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x00438703",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x34",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00438706",
      "count": 17,
      "first_use": 3,
      "first_write_index": 6,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [EBP + -0x30],ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00438706",
      "base": "EBP",
    
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_004adc40",
    "reconstructed": false,
    "va": "0x004adc40"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00437b00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00487040"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0048f790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0048fde0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0049a2a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0049cb90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0049cfd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0049d6b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a0bf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a1070"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a2350"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a29a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a6f10"
  },
  {
    "name": "editor_input_0058ac10",
    "reconstructed": true,
    "va": "0x0058ac10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005ad5d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005b7cf0"
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
  "count": 128,
  "instructions": [
    {
      "address": "00438700",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00438701",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "00438703",
      "instruction": "SUB ESP,0x34"
    },
    {
      "address": "00438706",
      "instruction": "MOV dword ptr [EBP + -0x30],ECX"
    },
    {
      "address": "00438709",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0043870c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0043870d",
      "instruction": "MOV ECX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "00438710",
      "instruction": "CALL 0x004388b0"
    },
    {
      "address": "00438715",
      "instruction": "MOV ECX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "00438718",
      "instruction": "CMP dword ptr [ECX + 0x28],0x0"
    },
    {
      "address": "0043871c",
      "instruction": "JZ 0x004388a2"
    },
    {
      "address": "00438722",
      "instruction": "MOV EDX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "00438725",
      "instruction": "MOV ECX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "00438728",
      "instruction": "CALL 0x004adc40"
    },
    {
      "address": "0043872d",
      "instruction": "MOVZX EAX,AL"
    },
    {
      "address": "00438730",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00438732",
      "instruction": "JZ 0x004388a2"
    },
    {
      "address": "00438738",
      "instruction": "MOV ECX,0x7"
    },
    {
      "address": "0043873d",
      "instruction": "CMP ECX,0x3c"
    },
    {
      "address": "00438740",
      "instruction": "JNC 0x0043877c"
    },
    {
      "address": "00438742",
      "instruction": "MOV EDX,0x7"
    },
    {
      "address": "00438747",
      "instruction": "SHR EDX,0x5"
    },
    {
      "address": "0043874a",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "0043874d",
      "instruction": "MOV ECX,dword ptr [EAX + EDX*0x4 + 0xdc8]"
    },
    {
      "address": "00438754",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "00438757",
      "instruction": "MOV EAX,0x7"
    },
    {
      "address": "0043875c",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "0043875e",
      "instruction": "MOV ECX,0x20"
    },
    {
      "address": "00438763",
      "instruction": "DIV ECX"
    },
    {
      "address": "00438765",
      "instruction": "MOV EAX,0x1"
    },
    {
      "address": "0043876a",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "0043876c",
      "instruction": "SHL EAX,CL"
    },
    {
      "address": "0043876e",
      "instruction": "AND EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "00438771",
      "instruction": "NEG EAX"
    },
    {
      "address": "00438773",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00438775",
      "instruction": "NEG EAX"
    },
    {
      "address": "00438777",
      "instruction": "MOV byte ptr [EBP + -0x5],AL"
    },
    {
      "address": "0043877a",
      "instruction": "JMP 0x00438780"
    },
    {
      "address": "0043877c",
      "instruction": "MOV byte ptr [EBP + -0x5],0x0"
    },
    {
      "address": "00438780",
      "instruction": "MOVZX ECX,byte ptr [EBP + -0x5]"
    },
    {
      "address": "00438784",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00438786",
      "instruction": "JNZ 0x004388a2"
    },
    {
      "address": "0043878c",
      "instruction": "MOV EDX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "0043878f",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3e0]"
    },
    {
      "address": "00438795",
      "instruction": "MOV dword ptr [EBP + -0xc],EAX"
    },
    {
      "address": "00438798",
      "instruction": "CMP dword ptr [EBP + -0xc],0x0"
    },
    {
      "address": "0043879c",
      "instruction": "JZ 0x004387d9"
    },
    {
      "address": "0043879e",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004387a1",
      "instruction": "MOV EDX,dword ptr [ECX + 0x3e0]"
    },
    {
      "address": "004387a7",
      "instruction": "MOV dword ptr [EBP + -0x10],EDX"
    },
    {
      "address": "004387aa",
      "instruction": "CMP dword ptr [EBP + -0x10],0x0"
    },
    {
      "address": "004387ae",
      "instruction": "JZ 0x004387d4"
    },
    {
      "address": "004387b0",
      "instruction": "MOV EAX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004387b3",
      "instruction": "MOV ECX,dword ptr [EAX + 0x3e0]"
    },
    {
      "address": "004387b9",
      "instruction": "MOV dword ptr [EBP + -0x14],ECX"
    },
    {
      "address": "004387bc",
      "instruction": "MOV EDX,dword ptr [EBP + -0x30]"
    },
    {
      "address": "004387bf",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3e0]"
    },
    {
      "address": "004387c5",
      "instruction": "MOV dword ptr [EBP + -0x18],EAX"
    },
    {
      "address": "004387c8",
      "instruction": "MOV ECX,dword ptr [EBP + -0x14]"
    },
    {
      "address": "004387cb",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004387cc",
      "instruction": "MOV ECX,dword ptr [EBP + -0x18]"
    },
    {
      "address": "004387cf",
      "instruction": "CALL 0x004388b0"
    },
    {
      "address": "004387d4",
      "instruction": "JMP 0x004388a2"
    },
    {
      "address": "004387d9",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "004387dc",
      "instruction": "MOV EAX,dword ptr [EDX + 0x3e0]"
    },
    {
      "address": "004387e2",
      "instruction": "MOV dword ptr [EBP + -0x1c],EAX"
    },
    {
      "address": "004387e5",
      "instruction": "CMP dword ptr [EBP + -0x1c],0x0"
    },
    {
      "address": "004387e9",
      "instruction": "JZ 0x004388a2"
    },
    {
      "address": "004387ef",
    
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
  "original_bytes": 14307,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32 (x86:LE:32:windows, image base 0x00400000)\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_observation\": \"0x004388a2: MOV ESP,EBP / 0x004388a4: POP EBP / 0x004388a5: RET 0x4 with no value in EAX that any caller could use; the sampled callers all discard the result.\",\n    \"return_register\": \"none (void)\",\n    \"return_semantics\": \"No value is returned. EAX is used only as scratch; the last write to EAX on any path is either the flag byte at 0x00438777 / 0x0043877c / 0x00438845 / 0x0043884a or the address 0x0043882c used to set up the bit mask.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"EBP+0x8\",\n        \"name\": \"other\",\n        \"observed_uses\": [\n          \"0x0043874d: MOV ECX,dword ptr [EAX + EDX*0x4 + 0xdc8] -- bit 7 of the other object's attribute field\",\n          \"0x004387a1 / 0x004387b3: MOV EDX / MOV ECX,dword ptr [ECX + 0x3e0] -- the other object's sub-object\",\n          \"0x00438710: PUSH EAX then CALL 0x004388b0\"\n        ],\n        \"read_evidence\": \"0x00438709: MOV EAX,dword ptr [EBP + 0x8]\",\n        \"type\": \"OpaqueEditorRigblock* (pointer-like)\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"single shared exit at 0x004388a2 reached by every path\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_004adc40\",\n        \"reconstructed\": false,\n        \"va\": \"0x004adc40\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00437b00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00487040\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048f790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048fde0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0049a2a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0049cb90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0049cfd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0049d6b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a0bf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a1070\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a2350\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a29a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a6f10\"\n      },\n      {\n        \"name\": \"editor_input_0058ac10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058ac10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005ad5d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b7cf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005b8da0\"\n 
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
  "body_end": "004388a7",
  "body_span_bytes": 424,
  "body_start": "00438700",
  "callees": [
    "FUN_004388b0",
    "FUN_004a7e60",
    "FUN_0044f220",
    "FUN_004adc40"
  ],
  "callers": [
    "FUN_00437b00",
    "FUN_005d27e0",
    "FUN_005b7cf0",
    "FUN_0048f790",
    "FUN_004a1070",
    "FUN_005d3300",
    "FUN_005b8da0",
    "FUN_0048fde0",
    "FUN_004a2350",
    "FUN_005ad5d0",
    "FUN_0049d6b0",
    "Editors::cEditor::OnKeyDown",
    "FUN_004a0bf0",
    "FUN_00487040",
    "FUN_004a6f10",
    "FUN_005d36e0",
    "FUN_0049cb90",
    "FUN_004a29a0",
    "FUN_005bb5a0",
    "FUN_0049cfd0",
    "FUN_0049a2a0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00438700",
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
      "name": "local_9",
      "storage": "Stack[-0x9]:1",
      "type": "undefined1"
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
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_25",
      "storage": "Stack[-0x25]:1",
      "type": "undefined1"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 13,
  "mode": "live",
  "name": "FUN_00438700",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x38700",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00438700(void)",
  "size_bytes": 424,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00438700",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 26,
  "xrefs": [
    {
      "from": "00437e08"
    },
    {
      "from": "0049cd27"
    },
    {
      "from": "0048707b"
    },
    {
      "from": "0048f98c"
    },
    {
      "from": "0048fd0c"
    },
    {
      "from": "0048fe81"
    },
    {
      "from": "0049b095"
    },
    {
      "from": "0049d144"
    },
    {
      "from": "0049dc83"
    },
    {
      "from": "004a15b8"
    },
    {
      "from": "004a2ea5"
    },
    {
      "from": "004a0f88"
    },
    {
      "from": "004a73e4"
    },
    {
      "from": "004a23ef"
    },
    {
      "from": "005d3cdb"
    },
    {
      "from": "005ad8ce"
    },
    {
      "from": "005b7f47"
    },
    {
      "from": "005b8edc"
    },
    {
      "from": "005d2f1e"
    },
    {
      "from": "005d2f6b"
    },
    {
      "from": "005d34d5"
    },
    {
      "from": "005bbf9c"
    },
    {
      "from": "0058af6f"
    },
    {
      "from": "005abab7"
    },
    {
      "from": "005ac3f5"
    },
    {
      "from": "005b3b09"
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
    "reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/00438700.json"
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
    "A differential fixture would need to drive the editor with one rigblock whose bit 7 is set and one whose bit 11 is set, to see which branch actually fires.",
    "No original-process trace exists. Every flag value, every +0x1c0 value and every 0x004a7e60 result in the contract above is a static reading of the code path, not an observation.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made."
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
  "OpaqueEditorRigblock* (pointer-like)",
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
