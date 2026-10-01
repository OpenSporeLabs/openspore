# Evidence 0x004ad550

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `24817a1be9118b006a0c58fd7635ecdfaf6930c62561caa5ee34954eadd54264`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this_register": "ECX, spilled to [EBP-0xb0] at 0x004ad559 and reloaded at each use",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "the last write to EAX before the epilogue is 0x004ad6e4 MOV EAX,dword ptr [EBP+0x8]. The value is the out parameter, not a status code and not a pointer to the internal accumulator.",
  "return_register": "EAX",
  "return_semantics": "the function returns its own first stack argument unchanged; 0x004ad6e4 MOV EAX,[EBP+0x8] copies the out-parameter pointer into EAX after the copy at 0x004ad6df. The return value carries no information beyond what the caller already passed in.",
  "return_type": "BoundingBox*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP"
  ],
  "stack_arguments": [
    {
      "proof": "0x004ad6db PUSH EDX pushes &accumulator and 0x004ad6dc MOV ECX,[EBP+0x8] makes the same slot the thiscall receiver of the final store, so it is the destination; 0x004ad6e4 then returns it",
      "role": "out_bounds",
      "slot": "[EBP+0x8]"
    },
    {
      "proof": "0x004ad653 MOVZX EDX,byte ptr [EBP+0xc] is read as a one-byte flag; the caller at 0x00586ed8/0x00586ee1 pushes a register and a stack address, and the byte slot is the one tested",
      "role": "filter_hidden",
      "slot": "[EBP+0xc]"
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "single exit at 0x004ad6ea"
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
      },
      {
        "ebp_offset": "EBP+0xc",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x8",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "4f4ae6d15f7e6d44205ee055bb2e3f64e0cce07e078ee6a20ad455e7fe0b7c26",
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
        "obs-0070"
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
        "obs-0047",
        "obs-0066",
        "obs-0068"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0016",
        "obs-0017",
        "obs-0024",
        "obs-0026",
        "obs-0028",
        "obs-0032",
        "obs-0033",
        "obs-0036",
        "obs-0041",
        "obs-0045",
        "obs-0046",
        "obs-0051",
        "obs-0053",
        "obs-0055",
        "obs-0057",
        "obs-0060",
        "obs-0061",
        "obs-0063",
        "obs-0066"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0016",
        "obs-0017",
        "obs-0024",
        "obs-0026",
        "obs-0028",
        "obs-0032",
        "obs-0033",
        "obs-0036",
        "obs-0041",
        "obs-0045",
        "obs-0046",
        "obs-0051",
        "obs-0053",
        "obs-0055",
        "obs-0057",
        "obs-0060",
        "obs-0061",
        "obs-0063",
        "obs-0066",
        "obs-0070"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0070"
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
        "obs-0070"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0070"
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
      "at": "0x004ad550",
      "count": 52,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x004ad550",
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
      "sub": 176
    },
    {
      "at": "0x004ad551",
      "count": 1,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "re
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00409c00"
  },
  {
    "name": "FUN_0044ae00",
    "reconstructed": false,
    "va": "0x0044ae00"
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
    "va": "0x00574b40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00580700"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00583c50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00586b00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005addb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005ae300"
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
  "count": 112,
  "instructions": [
    {
      "address": "004ad550",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004ad551",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004ad553",
      "instruction": "SUB ESP,0xb0"
    },
    {
      "address": "004ad559",
      "instruction": "MOV dword ptr [EBP + 0xffffff50],ECX"
    },
    {
      "address": "004ad55f",
      "instruction": "LEA ECX,[EBP + -0x1c]"
    },
    {
      "address": "004ad562",
      "instruction": "CALL 0x00409c00"
    },
    {
      "address": "004ad567",
      "instruction": "LEA ECX,[EBP + -0x1c]"
    },
    {
      "address": "004ad56a",
      "instruction": "CALL 0x00409c00"
    },
    {
      "address": "004ad56f",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff50]"
    },
    {
      "address": "004ad575",
      "instruction": "ADD EAX,0x18"
    },
    {
      "address": "004ad578",
      "instruction": "MOV dword ptr [EBP + 0xffffff78],EAX"
    },
    {
      "address": "004ad57e",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff78]"
    },
    {
      "address": "004ad584",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff78]"
    },
    {
      "address": "004ad58a",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "004ad58d",
      "instruction": "SUB EAX,dword ptr [EDX]"
    },
    {
      "address": "004ad58f",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "004ad592",
      "instruction": "MOV dword ptr [EBP + -0x4],EAX"
    },
    {
      "address": "004ad595",
      "instruction": "CMP dword ptr [EBP + -0x4],0x0"
    },
    {
      "address": "004ad599",
      "instruction": "JBE 0x004ad6d8"
    },
    {
      "address": "004ad59f",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "004ad5a1",
      "instruction": "SHL ECX,0x2"
    },
    {
      "address": "004ad5a4",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff50]"
    },
    {
      "address": "004ad5aa",
      "instruction": "ADD ECX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "004ad5ad",
      "instruction": "MOV dword ptr [EBP + 0xffffff74],ECX"
    },
    {
      "address": "004ad5b3",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff74]"
    },
    {
      "address": "004ad5b9",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "004ad5bb",
      "instruction": "MOV dword ptr [EBP + 0xffffff70],ECX"
    },
    {
      "address": "004ad5c1",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004ad5c3",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004ad5c5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "004ad5c7",
      "instruction": "LEA EDX,[EBP + -0x3c]"
    },
    {
      "address": "004ad5ca",
      "instruction": "PUSH EDX"
    },
    {
      "address": "004ad5cb",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff70]"
    },
    {
      "address": "004ad5d1",
      "instruction": "CALL 0x0044ae00"
    },
    {
      "address": "004ad5d6",
      "instruction": "MOV dword ptr [EBP + 0xffffff6c],EAX"
    },
    {
      "address": "004ad5dc",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff6c]"
    },
    {
      "address": "004ad5e2",
      "instruction": "ADD EAX,0xc"
    },
    {
      "address": "004ad5e5",
      "instruction": "LEA ECX,[EBP + -0x10]"
    },
    {
      "address": "004ad5e8",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "004ad5ea",
      "instruction": "MOV dword ptr [ECX],EDX"
    },
    {
      "address": "004ad5ec",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "004ad5ef",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "004ad5f2",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "004ad5f5",
      "instruction": "MOV dword ptr [ECX + 0x8],EAX"
    },
    {
      "address": "004ad5f8",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff6c]"
    },
    {
      "address": "004ad5fe",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "004ad600",
      "instruction": "MOV dword ptr [EBP + -0x1c],EDX"
    },
    {
      "address": "004ad603",
      "instruction": "MOV EAX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "004ad606",
      "instruction": "MOV dword ptr [EBP + -0x18],EAX"
    },
    {
      "address": "004ad609",
      "instruction": "MOV ECX,dword ptr [ECX + 0x8]"
    },
    {
      "address": "004ad60c",
      "instruction": "MOV dword ptr [EBP + -0x14],ECX"
    },
    {
      "address": "004ad60f",
      "instruction": "MOV dword ptr [EBP + -0x24],0x1"
    },
    {
      "address": "004ad616",
      "instruction": "MOV EDX,dword ptr [EBP + 0xffffff50]"
    },
    {
      "address": "004ad61c",
      "instruction": "ADD EDX,0x18"
    },
    {
      "address": "004ad61f",
      "instruction": "MOV dword ptr [EBP + 0xffffff68],EDX"
    },
    {
      "address": "004ad625",
      "instruction": "MOV EAX,dword ptr [EBP + 0xffffff68]"
    },
    {
      "address": "004ad62b",
      "instruction": "MOV ECX,dword ptr [EBP + 0xffffff68]"
    },
    {
      "address": "004ad631",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "004ad634",
      "instruction": "SUB EDX,dword ptr [ECX]"
    },
    {
      "address": "004ad636",
      "instruction": "SAR EDX,0x2"
    },
    {
      "address": "004ad639",
      "instruction": "MOV dword ptr [EBP + -0x20],EDX"
    },
    {
      "address": "004ad63c",
      "instruction": "JMP 0x004ad647"
    },
    {
      "address": "004ad63e",
      "instruction": "MOV EAX,dword ptr [EBP + -0x24]"
    },
    {
      "address": "004ad641",
      "instruction": "ADD EAX,0x1"
    },
    {
      "address": "004ad644",
      "instruction": "MOV dword ptr [EBP + -0x24],EAX"
    },
    {
      "address": "004ad647",
      "instruction": "MOV ECX,dword pt
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
  "original_bytes": 10752,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this_register\": \"ECX, spilled to [EBP-0xb0] at 0x004ad559 and reloaded at each use\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"the last write to EAX before the epilogue is 0x004ad6e4 MOV EAX,dword ptr [EBP+0x8]. The value is the out parameter, not a status code and not a pointer to the internal accumulator.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"the function returns its own first stack argument unchanged; 0x004ad6e4 MOV EAX,[EBP+0x8] copies the out-parameter pointer into EAX after the copy at 0x004ad6df. The return value carries no information beyond what the caller already passed in.\",\n    \"return_type\": \"BoundingBox*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"proof\": \"0x004ad6db PUSH EDX pushes &accumulator and 0x004ad6dc MOV ECX,[EBP+0x8] makes the same slot the thiscall receiver of the final store, so it is the destination; 0x004ad6e4 then returns it\",\n        \"role\": \"out_bounds\",\n        \"slot\": \"[EBP+0x8]\"\n      },\n      {\n        \"proof\": \"0x004ad653 MOVZX EDX,byte ptr [EBP+0xc] is read as a one-byte flag; the caller at 0x00586ed8/0x00586ee1 pushes a register and a stack address, and the byte slot is the one tested\",\n        \"role\": \"filter_hidden\",\n        \"slot\": \"[EBP+0xc]\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"single exit at 0x004ad6ea\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00409c00\"\n      },\n      {\n        \"name\": \"FUN_0044ae00\",\n        \"reconstructed\": false,\n        \"va\": \"0x0044ae00\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00574b40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00580700\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00583c50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00586b00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005addb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005ae300\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00574bb4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00574b40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058072b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00580700\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00583e94\",\n        \"direction\": \"in\",\n        \"other\": \"0x00583c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00586ee8\",\n        \"direction\": \"in\",\n        \"other\": \"0x00586b00\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005addc6\",\n        \"direction\": \"in\",\n        \"other\": \"0x005addb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005ae348\",\n        \"direction\": \"in\",\n       
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
  "body_end": "004ad6ec",
  "body_span_bytes": 413,
  "body_start": "004ad550",
  "callees": [
    "FUN_00409c00",
    "FUN_00511140",
    "FUN_00435d40",
    "FUN_0044ae00",
    "FUN_0043f050"
  ],
  "callers": [
    "FUN_005addb0",
    "FUN_00574b40",
    "FUN_005ae300",
    "FUN_00583c50",
    "FUN_00580700",
    "Editors::cEditor::SetEditorModel"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "004ad550",
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
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:1",
      "type": "undefined"
    },
    {
      "name": "local_58",
      "storage": "Stack[-0x58]:1",
      "type": "undefined"
    },
    {
      "name": "local_8c",
      "storage": "Stack[-0x8c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_90",
      "storage": "Stack[-0x90]:4",
      "type": "undefined4"
    },
    {
      "name": "local_94",
      "storage": "Stack[-0x94]:4",
      "type": "undefined4"
    },
    {
      "name": "local_98",
      "storage": "Stack[-0x98]:4",
      "type": "undefined4"
    },
    {
      "name": "local_9c",
      "storage": "Stack[-0x9c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a0",
      "storage": "Stack[-0xa0]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a4",
      "storage": "Stack[-0xa4]:4",
      "type": "undefined4"
    },
    {
      "name": "local_a8",
      "storage": "Stack[-0xa8]:4",
      "type": "undefined4"
    },
    {
      "name": "local_ac",
      "storage": "Stack[-0xac]:4",
      "type": "undefined4"
    },
    {
      "name": "local_b4",
      "storage": "Stack[-0xb4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 21,
  "mode": "live",
  "name": "FUN_004ad550",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xad550",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004ad550(void)",
  "size_bytes": 413,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004ad550",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00574bb4"
    },
    {
      "from": "00583e94"
    },
    {
      "from": "0058072b"
    },
    {
      "from": "00586ee8"
    },
    {
      "from": "005addc6"
    },
    {
      "from": "005ae348"
    },
    {
      "from": "005ae35d"
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
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/004ad550.json"
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
    "A differential test must confirm the box is written even when the list is empty, since that is the invariant a caller is most likely to depend on incorrectly.",
    "A trace must confirm that the 100-level ceiling in 0x00435d40 is never reached, i.e. that no rigblock hierarchy in the shipping data is deeper than 100.",
    "A trace must record the actual filter-flag values passed by callers, which is the only way to learn whether the ancestor-chain test is ever active in the shipping build.",
    "No original-process trace exists for this function. Static analysis cannot show whether the rigblock vector is ever empty in a live editor session, which is the only path that produces the inverted sentinel in a caller's box."
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
  "BoundingBox*"
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
