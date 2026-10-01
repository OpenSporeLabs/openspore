# Evidence 0x005c8480

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `18db9dded0e9b27eaa5071257a74198e842498ca3711cd167c51f051dd0b6b01`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to EDI at 0x005c8487; every receiver access in the body is [EDI + disp]",
  "ordinary_stack_argument_slots": 2,
  "receiver": true,
  "ret_form": "RET 0x8",
  "return_observation": "no MOV to EAX in either epilogue; the last EAX written on the grow arm is the biased cursor at 0x005c8597, which is immediately stored to [EDI + 4] at 0x005c85bd rather than returned.",
  "return_register": "none (EAX carries the allocator result and the running memcpy cursor but is not returned as a value)",
  "return_semantics": "no register result. The observable effects are the rewritten receiver triple and, on the in-capacity arm, an overwrite of the caller's *second argument* through the pointer it holds.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "offset_in_callee": "[ESP + 0x1c] with ESP lowered 0x18",
      "read_by": "0x005c8495: MOV EBP,dword ptr [ESP + 0x1c] (grow arm re-read at 0x005c8550)",
      "role": "the append/insert position, a slot address; both inspected callers pass the receiver's own `last` pointer",
      "slot": 1,
      "width_bytes": 4
    },
    {
      "offset_in_callee": "[ESP + 0x20] with ESP lowered 0x18",
      "read_by": "0x005c8491: MOV ECX,dword ptr [ESP + 0x20] (grow arm re-read at 0x005c8571)",
      "role": "a pointer to a value slot; both inspected callers pass the address of a caller stack slot holding the new value",
      "slot": 2,
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8 (two distinct sites: 0x005c84fc for the in-capacity arm, 0x005c85cc for the grow arm)"
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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0x10",
      "entry_ESP+0x14",
      "entry_ESP+0x1c",
      "entry_ESP+0x20"
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
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
    "return_semantics": "pointer_like_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x20",
        "observed": true,
        "ordinal": 8,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -24, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x20; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x20 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "5ac13018b9898291bca61f051fc8aeb14a2d3766d15cd889c46e5bab7396c145",
  "conventions": {
    "ambiguities": [],
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0030",
        "obs-0050"
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
        "obs-0030",
        "obs-0050"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0013",
        "obs-0031",
        "obs-0033",
        "obs-0034",
        "obs-0035",
        "obs-0036",
        "obs-0037",
        "obs-0038",
        "obs-0040",
        "obs-0044",
        "obs-0045"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      
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
    "va": "0x00586410"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cb80"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005c21d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005c22b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005c2390"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005c5f00"
  },
  {
    "name": "palette_safe_wave11_load_page_state_005c85d0",
    "reconstructed": true,
    "va": "0x005c85d0"
  },
  {
    "name": "palette_page_construct_005c9230",
    "reconstructed": true,
    "va": "0x005c9230"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005e04d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062bb40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062ce00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062ec90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062efb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0062f9f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00631df0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x006338a0"
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
  "count": 133,
  "instructions": [
    {
      "address": "005c8480",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "005c8483",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005c8484",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005c8485",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005c8486",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005c8487",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "005c8489",
      "instruction": "MOV EAX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "005c848c",
      "instruction": "CMP EAX,dword ptr [EDI + 0x8]"
    },
    {
      "address": "005c848f",
      "instruction": "JZ 0x005c84ff"
    },
    {
      "address": "005c8491",
      "instruction": "MOV ECX,dword ptr [ESP + 0x20]"
    },
    {
      "address": "005c8495",
      "instruction": "MOV EBP,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "005c8499",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "005c849b",
      "instruction": "CMP ECX,EBP"
    },
    {
      "address": "005c849d",
      "instruction": "JC 0x005c84a6"
    },
    {
      "address": "005c849f",
      "instruction": "CMP ECX,EAX"
    },
    {
      "address": "005c84a1",
      "instruction": "JNC 0x005c84a6"
    },
    {
      "address": "005c84a3",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "005c84a6",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c84a8",
      "instruction": "JZ 0x005c84ba"
    },
    {
      "address": "005c84aa",
      "instruction": "MOV ECX,dword ptr [EAX + -0x4]"
    },
    {
      "address": "005c84ad",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "005c84af",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "005c84b1",
      "instruction": "JZ 0x005c84ba"
    },
    {
      "address": "005c84b3",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "005c84b5",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005c84b8",
      "instruction": "CALL EDX"
    },
    {
      "address": "005c84ba",
      "instruction": "MOV EAX,dword ptr [EDI + 0x4]"
    },
    {
      "address": "005c84bd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c84be",
      "instruction": "ADD EAX,-0x4"
    },
    {
      "address": "005c84c1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c84c2",
      "instruction": "PUSH EBP"
    },
    {
      "address": "005c84c3",
      "instruction": "CALL 0x005c1dc0"
    },
    {
      "address": "005c84c8",
      "instruction": "MOV ESI,dword ptr [ESI]"
    },
    {
      "address": "005c84ca",
      "instruction": "MOV EBX,dword ptr [EBP]"
    },
    {
      "address": "005c84cd",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "005c84d0",
      "instruction": "CMP ESI,EBX"
    },
    {
      "address": "005c84d2",
      "instruction": "JZ 0x005c84f1"
    },
    {
      "address": "005c84d4",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "005c84d6",
      "instruction": "JZ 0x005c84e1"
    },
    {
      "address": "005c84d8",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "005c84da",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "005c84dd",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005c84df",
      "instruction": "CALL EDX"
    },
    {
      "address": "005c84e1",
      "instruction": "MOV dword ptr [EBP],ESI"
    },
    {
      "address": "005c84e4",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "005c84e6",
      "instruction": "JZ 0x005c84f1"
    },
    {
      "address": "005c84e8",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "005c84ea",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "005c84ed",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "005c84ef",
      "instruction": "CALL EDX"
    },
    {
      "address": "005c84f1",
      "instruction": "ADD dword ptr [EDI + 0x4],0x4"
    },
    {
      "address": "005c84f5",
      "instruction": "POP EDI"
    },
    {
      "address": "005c84f6",
      "instruction": "POP ESI"
    },
    {
      "address": "005c84f7",
      "instruction": "POP EBP"
    },
    {
      "address": "005c84f8",
      "instruction": "POP EBX"
    },
    {
      "address": "005c84f9",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "005c84fc",
      "instruction": "RET 0x8"
    },
    {
      "address": "005c84ff",
      "instruction": "SUB EAX,dword ptr [EDI]"
    },
    {
      "address": "005c8501",
      "instruction": "SAR EAX,0x2"
    },
    {
      "address": "005c8504",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c8506",
      "instruction": "JBE 0x005c8538"
    },
    {
      "address": "005c8508",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "005c850a",
      "instruction": "MOV dword ptr [ESP + 0x14],EAX"
    },
    {
      "address": "005c850e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005c8510",
      "instruction": "JZ 0x005c8546"
    },
    {
      "address": "005c8512",
      "instruction": "PUSH 0xd1"
    },
    {
      "address": "005c8517",
      "instruction": "PUSH 0x13ebb38"
    },
    {
      "address": "005c851c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005c851e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005c8520",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "005c8522",
      "instruction": "ADD EAX,EAX"
    },
    {
      "address": "005c8524",
      "instruction": "PUSH 0x13eb430"
    },
    {
      "address": "005c8529",
      "instruction": "PUSH EAX"
    },
    {
      "address": "005c852a",
      "instruction": "
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
  "original_bytes": 15477,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, copied to EDI at 0x005c8487; every receiver access in the body is [EDI + disp]\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"no MOV to EAX in either epilogue; the last EAX written on the grow arm is the biased cursor at 0x005c8597, which is immediately stored to [EDI + 4] at 0x005c85bd rather than returned.\",\n    \"return_register\": \"none (EAX carries the allocator result and the running memcpy cursor but is not returned as a value)\",\n    \"return_semantics\": \"no register result. The observable effects are the rewritten receiver triple and, on the in-capacity arm, an overwrite of the caller's *second argument* through the pointer it holds.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"offset_in_callee\": \"[ESP + 0x1c] with ESP lowered 0x18\",\n        \"read_by\": \"0x005c8495: MOV EBP,dword ptr [ESP + 0x1c] (grow arm re-read at 0x005c8550)\",\n        \"role\": \"the append/insert position, a slot address; both inspected callers pass the receiver's own `last` pointer\",\n        \"slot\": 1,\n        \"width_bytes\": 4\n      },\n      {\n        \"offset_in_callee\": \"[ESP + 0x20] with ESP lowered 0x18\",\n        \"read_by\": \"0x005c8491: MOV ECX,dword ptr [ESP + 0x20] (grow arm re-read at 0x005c8571)\",\n        \"role\": \"a pointer to a value slot; both inspected callers pass the address of a caller stack slot holding the new value\",\n        \"slot\": 2,\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8 (two distinct sites: 0x005c84fc for the in-capacity arm, 0x005c85cc for the grow arm)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"palette_safe_wave11_load_page_state_005c85d0\",\n      \"va\": \"0x005c85d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-15-EDITOR-SUPPORT\",\n      \"score\": 5,\n      \"symbol\": \"palette_page_construct_005c9230\",\n      \"va\": \"0x005c9230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00586410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cb80\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c21d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c22b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c2390\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005c5f00\"\n      },\n      {\n        \"name\": \"palette_safe_wave11_load_page_state_005c85d0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c85d0\"\n      },\n      {\n        \"name\": \"palette_page_construct_005c9230\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c9230\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005e04d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062bb40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062ce00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062ec90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0062efb0\"\n      },\n      {\n        \"name\": null
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
  "body_end": "005c85ce",
  "body_span_bytes": 335,
  "body_start": "005c8480",
  "callees": [
    "FUN_00f47380",
    "FUN_00f473a0",
    "FUN_005c1dc0",
    "memcpy"
  ],
  "callers": [
    "FUN_00631df0",
    "FUN_005c85d0",
    "FUN_0062efb0",
    "FUN_0059cb80",
    "FUN_00e0a680",
    "FUN_0062ec90",
    "FUN_0066b130",
    "FUN_006338a0",
    "FUN_0066b050",
    "FUN_0062ce00",
    "FUN_0066b480",
    "FUN_005c2390",
    "Editors::cEditor::CommitEditHistory",
    "FUN_005e04d0",
    "FUN_01076540",
    "FUN_005c22b0",
    "FUN_005c5f00",
    "FUN_0062f9f0",
    "FUN_005c9230",
    "FUN_005c21d0",
    "FUN_0062bb40"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005c8480",
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
  "name": "FUN_005c8480",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1c8480",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005c8480(void)",
  "size_bytes": 335,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005c8480",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 39,
  "xrefs": [
    {
      "from": "005c2372"
    },
    {
      "from": "005c221a"
    },
    {
      "from": "005c2455"
    },
    {
      "from": "005c5fbe"
    },
    {
      "from": "005c5feb"
    },
    {
      "from": "005c8a82"
    },
    {
      "from": "00586510"
    },
    {
      "from": "0062bd91"
    },
    {
      "from": "0062fb88"
    },
    {
      "from": "005c95ea"
    },
    {
      "from": "005e08ef"
    },
    {
      "from": "0062ceca"
    },
    {
      "from": "0062ef7b"
    },
    {
      "from": "0062f1af"
    },
    {
      "from": "0063399e"
    },
    {
      "from": "00631e35"
    },
    {
      "from": "0066b2c8"
    },
    {
      "from": "0066b3ba"
    },
    {
      "from": "0066b437"
    },
    {
      "from": "0066b4f3"
    },
    {
      "from": "0066b577"
    },
    {
      "from": "0066b5fb"
    },
    {
      "from": "0066b67f"
    },
    {
      "from": "0066b703"
    },
    {
      "from": "0066b787"
    },
    {
      "from": "0066b80b"
    },
    {
      "from": "0066b88f"
    },
    {
      "from": "0066b916"
    },
    {
      "from": "0066b9a1"
    },
    {
      "from": "0066ba2c"
    },
    {
      "from": "0066bab3"
    },
    {
      "from": "0066bb3e"
    },
    {
      "from": "0066bbc9"
    },
    {
      "from": "0066bc54"
    },
    {
      "from": "0066bcdf"
    },
    {
      "from": "010769de"
    },
    {
      "from": "0066b09f"
    },
    {
      "from": "00e0a716"
    },
    {
      "from": "0059cbb8"
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
    "reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b00/slot_vector_005c8480.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b00/005c8480.json"
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
    "No original-process trace exists for 0x005c8480; every claim is static and the Cell stage has never been entered in any recorded run.",
    "The capacity*16 allocation size and the null-block overflow path can only be confirmed as intentional or as defects by a run that exercises them.",
    "The payload's vtable and therefore the meanings of slots +0x4 and +0x8 require a run with a live editor or palette session.",
    "Whether the in-capacity arm is ever reached with an interior position can only be settled by instrumenting the 19 uninspected callsites or by a run; the two inspected ones never reach it."
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
  "allocator cookie / size",
  "payload pointer",
  "pointer to the first slot (nullable)",
  "pointer to the slot one past the capacity",
  "pointer to the slot one past the last used slot (nullable)",
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
