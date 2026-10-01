# Evidence 0x00c47180

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `42f908493213f4daa48ce3b4806271707a80f5a93da42a61f63a6fd3126966a7`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, read at 0x00c47181",
  "hidden_this_register": "ECX is consumed once; the receiver is then reached only through the address held in ESI.",
  "ordinary_stack_argument_slots": 1,
  "receiver": true,
  "ret_form": "RET 0x4",
  "return_register": null,
  "return_semantics": "No return value. EAX is clobbered by 0x00c471a8 MOV ECX,EAX and is dead on exit.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI"
  ],
  "stack_arguments": [
    {
      "actual_use": "NONE. 0x00B3D2A0 is exactly MOV EAX,dword ptr [0x0167EAE4] ; RET (two instructions, six bytes) and consumes no argument. The pushed word therefore survives 0x00c471a3 and becomes the SECOND stack argument of 0x00BB59B0, which ends in RET 0x8.",
      "declared_use": "PUSH EAX at 0x00c471a2, as an argument to 0x00B3D2A0",
      "index": 0,
      "note": "One dead word pushed and one live word pushed. The compiler folded the unused argument away without removing the push, because the push is what positions the two arguments 0x00BB59B0 needs.",
      "offset_at_entry": "[ESP + 0x4]",
      "read_at": "0x00c4719d MOV EAX,[ESP + 0x8]",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "single RET 0x4 at 0x00c471b0"
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +8, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "69ab4d4f13b6ed64de1c58c54272222c293460291b6fa73108a33b3ef421a474",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
      "__thiscall"
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0014"
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
        "obs-0010"
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
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0014"
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
        "obs-0014"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014"
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
      "at": "0x00c47180",
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
      "at": "0x00c47181",
      "count": 2,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "LEA ESI,[ECX + 0x1e8]",
      "reg": "ECX"
    },
    {
      "at": "0x00c47187",
      "definite": true,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [ESI]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c47193",
      "definite": true,
      "id": "obs-0004",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c47195",
      "count": 3,
      "first_use": 7,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 7,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0xc0]",
      "reg": "EAX"
    },
    {
      "at": "0x00c47195",
      "definite": true,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0xc0]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c4719b",
      "count": 1,
      "first_use": 8,
      "first_write_index": 7,
      "id": "obs-0007",
      "index": 8,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00c4719b",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 8,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00c4719d",
      "count": 1,
      "first_use": 9,
      "first_write_index": null,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_READ",
    
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
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
    "va": "0x00c4b440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4b7f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4e440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c4f4e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c51010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c54380"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c557c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5ea60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c5f770"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c60e90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c62b30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c63380"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00fe9580"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0100e780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0101246a"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01012aa0"
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
  "count": 17,
  "instructions": [
    {
      "address": "00c47180",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c47181",
      "instruction": "LEA ESI,[ECX + 0x1e8]"
    },
    {
      "address": "00c47187",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00c47189",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00c4718b",
      "instruction": "JZ 0x00c4719d"
    },
    {
      "address": "00c4718d",
      "instruction": "MOV dword ptr [ESI],0x0"
    },
    {
      "address": "00c47193",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00c47195",
      "instruction": "MOV EDX,dword ptr [EAX + 0xc0]"
    },
    {
      "address": "00c4719b",
      "instruction": "CALL EDX"
    },
    {
      "address": "00c4719d",
      "instruction": "MOV EAX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00c471a1",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c471a2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c471a3",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00c471a8",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c471aa",
      "instruction": "CALL 0x00bb59b0"
    },
    {
      "address": "00c471af",
      "instruction": "POP ESI"
    },
    {
      "address": "00c471b0",
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
  "original_bytes": 14453,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, read at 0x00c47181\",\n    \"hidden_this_register\": \"ECX is consumed once; the receiver is then reached only through the address held in ESI.\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": null,\n    \"return_semantics\": \"No return value. EAX is clobbered by 0x00c471a8 MOV ECX,EAX and is dead on exit.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"actual_use\": \"NONE. 0x00B3D2A0 is exactly MOV EAX,dword ptr [0x0167EAE4] ; RET (two instructions, six bytes) and consumes no argument. The pushed word therefore survives 0x00c471a3 and becomes the SECOND stack argument of 0x00BB59B0, which ends in RET 0x8.\",\n        \"declared_use\": \"PUSH EAX at 0x00c471a2, as an argument to 0x00B3D2A0\",\n        \"index\": 0,\n        \"note\": \"One dead word pushed and one live word pushed. The compiler folded the unused argument away without removing the push, because the push is what positions the two arguments 0x00BB59B0 needs.\",\n        \"offset_at_entry\": \"[ESP + 0x4]\",\n        \"read_at\": \"0x00c4719d MOV EAX,[ESP + 0x8]\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"single RET 0x4 at 0x00c471b0\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4b440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4b7f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4e440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c4f4e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c51010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c54380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c557c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5ea60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c5f770\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c60e90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c62b30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c63380\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00fe9580\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0100e780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0101246a\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01012aa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01012b50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x01014540\
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
  "body_end": "00c471b2",
  "body_span_bytes": 51,
  "body_start": "00c47180",
  "callees": [
    "FUN_00bb59b0",
    "FUN_00b3d2a0"
  ],
  "callers": [
    "FUN_0101246a",
    "FUN_01014870",
    "FUN_00c62b30",
    "FUN_010251e0",
    "FUN_00c54380",
    "FUN_00c51010",
    "FUN_0100e780",
    "FUN_00c557c0",
    "FUN_00c5f770",
    "FUN_00c60e90",
    "FUN_00c63380",
    "FUN_010593e0",
    "FUN_00c4b440",
    "FUN_0102d0b0",
    "FUN_00c4f4e0",
    "FUN_00c5ea60",
    "FUN_00fe9580",
    "FUN_01014540",
    "FUN_00c4b7f0",
    "FUN_01012b50",
    "FUN_01012aa0",
    "FUN_00c4e440"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c47180",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c47180",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x847180",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c47180(void)",
  "size_bytes": 51,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c47180",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 31,
  "xrefs": [
    {
      "from": "00fe9acf"
    },
    {
      "from": "0102d125"
    },
    {
      "from": "00c4b520"
    },
    {
      "from": "00c4b86d"
    },
    {
      "from": "00c4b8c0"
    },
    {
      "from": "00c4e498"
    },
    {
      "from": "00c4e527"
    },
    {
      "from": "00c4f5f8"
    },
    {
      "from": "00c4f6d0"
    },
    {
      "from": "00c511b6"
    },
    {
      "from": "00c511fa"
    },
    {
      "from": "00c5440a"
    },
    {
      "from": "00c54509"
    },
    {
      "from": "00c557db"
    },
    {
      "from": "00c5ea89"
    },
    {
      "from": "00c5eb0e"
    },
    {
      "from": "00c5fae1"
    },
    {
      "from": "00c60ec4"
    },
    {
      "from": "00c60f4e"
    },
    {
      "from": "00c62c63"
    },
    {
      "from": "00c633fb"
    },
    {
      "from": "00c6345d"
    },
    {
      "from": "010124de"
    },
    {
      "from": "01012bae"
    },
    {
      "from": "01014633"
    },
    {
      "from": "01014944"
    },
    {
      "from": "0102544b"
    },
    {
      "from": "0100e7ea"
    },
    {
      "from": "01012b0b"
    },
    {
      "from": "01059e95"
    },
    {
      "from": "00c54e18"
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
    "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00c47180.json"
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
    "No original-process trace exists. A differential run must confirm the occupant's vtable slot +0xC0 does not re-read the receiver's +0x1E8 slot, which is the invariant the clear-before-detach ordering depends on.",
    "The concrete receiver type and the concrete occupant type can only be fixed by observing a vtable pointer in a running process.",
    "Whether the dead argument has any effect requires a run that varies it at a callsite and observes an unchanged result."
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
