# Evidence 0x00641e40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `3b2d65c26c63578b85fd558db11058ed60e7fedb3473e675d5c550d3b4d8f414`

## abi

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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +116, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "d8121b621c91b7384e3655322b319d5de3b03a4d30d16c415f437df84c7b0d47",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 12,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0063"
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
        "obs-0028"
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
        "obs-0012",
        "obs-0013",
        "obs-0018",
        "obs-0027",
        "obs-0033",
        "obs-0037",
        "obs-0041",
        "obs-0046",
        "obs-0049",
        "obs-0052",
        "obs-0056",
        "obs-0058"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          116
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0012",
        "obs-0013",
        "obs-0018",
        "obs-0027",
        "obs-0033",
        "obs-0037",
        "obs-0041",
        "obs-0046",
        "obs-0049",
        "obs-0052",
        "obs-0056",
        "obs-0058",
        "obs-0063"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0063"
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
        "obs-0063"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0063"
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
      "at": "0x00641e40",
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
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x00641e40",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00641e43",
      "count": 27,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00641e44",
      "count": 8,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00641e45",
      "count": 13,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00641e46",
      "co
[TRUNCATED]
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
          1
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +116, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "d8121b621c91b7384e3655322b319d5de3b03a4d30d16c415f437df84c7b0d47",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 12,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0063"
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
        "obs-0028"
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
        "obs-0012",
        "obs-0013",
        "obs-0018",
        "obs-0027",
        "obs-0033",
        "obs-0037",
        "obs-0041",
        "obs-0046",
        "obs-0049",
        "obs-0052",
        "obs-0056",
        "obs-0058"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          116
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0012",
        "obs-0013",
        "obs-0018",
        "obs-0027",
        "obs-0033",
        "obs-0037",
        "obs-0041",
        "obs-0046",
        "obs-0049",
        "obs-0052",
        "obs-0056",
        "obs-0058",
        "obs-0063"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0063"
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
        "obs-0063"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0063"
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
      "at": "0x00641e40",
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
      "raw": "SUB ESP,0x14",
      "sub": 20
    },
    {
      "at": "0x00641e40",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x14",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00641e43",
      "count": 27,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00641e44",
      "count": 8,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00641e45",
      "count": 13,
      "first_use": 3,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00641e46",
      "co
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
    "va": "0x0067dcd0"
  }
]
```

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
  "count": 145,
  "instructions": [
    {
      "address": "00641e40",
      "instruction": "SUB ESP,0x14"
    },
    {
      "address": "00641e43",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00641e44",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00641e45",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00641e46",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00641e48",
      "instruction": "LEA EBP,[ESI + 0x4]"
    },
    {
      "address": "00641e4b",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00641e4d",
      "instruction": "MOV dword ptr [ESP + 0x10],ESI"
    },
    {
      "address": "00641e51",
      "instruction": "CMP dword ptr [EBP],EBX"
    },
    {
      "address": "00641e54",
      "instruction": "JZ 0x00641f94"
    },
    {
      "address": "00641e5a",
      "instruction": "MOV ECX,dword ptr [EBP + 0x4]"
    },
    {
      "address": "00641e5d",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "00641e60",
      "instruction": "MOV EDX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00641e63",
      "instruction": "MOV dword ptr [ESP + 0x18],ECX"
    },
    {
      "address": "00641e67",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00641e68",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "00641e6c",
      "instruction": "MOV dword ptr [ESP + 0x20],EDX"
    },
    {
      "address": "00641e70",
      "instruction": "MOV dword ptr [ESP + 0x1c],0x2d5c9af"
    },
    {
      "address": "00641e78",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00641e7c",
      "instruction": "CALL 0x0067dcd0"
    },
    {
      "address": "00641e81",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00641e85",
      "instruction": "CMP byte ptr [ESP + 0x28],BL"
    },
    {
      "address": "00641e89",
      "instruction": "JZ 0x00641f14"
    },
    {
      "address": "00641e8f",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00641e91",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00641e93",
      "instruction": "JZ 0x00641ea0"
    },
    {
      "address": "00641e95",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00641e99",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00641e9b",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00641e9e",
      "instruction": "CALL EDX"
    },
    {
      "address": "00641ea0",
      "instruction": "MOV ECX,dword ptr [ESI + 0x74]"
    },
    {
      "address": "00641ea3",
      "instruction": "ADD ESI,0x74"
    },
    {
      "address": "00641ea6",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00641ea8",
      "instruction": "JZ 0x00641eb3"
    },
    {
      "address": "00641eaa",
      "instruction": "MOV dword ptr [ESI],EBX"
    },
    {
      "address": "00641eac",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00641eae",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00641eb1",
      "instruction": "CALL EDX"
    },
    {
      "address": "00641eb3",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00641eb5",
      "instruction": "MOV EAX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00641eb8",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00641eb9",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00641eba",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00641ebb",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00641ebc",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00641ebd",
      "instruction": "LEA ECX,[ESP + 0x24]"
    },
    {
      "address": "00641ec1",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00641ec2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00641ec3",
      "instruction": "LEA EDX,[ESP + 0x34]"
    },
    {
      "address": "00641ec7",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00641ec8",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00641eca",
      "instruction": "CALL EAX"
    },
    {
      "address": "00641ecc",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00641ece",
      "instruction": "JNZ 0x00641f6d"
    },
    {
      "address": "00641ed4",
      "instruction": "CALL 0x0067dcd0"
    },
    {
      "address": "00641ed9",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00641edd",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00641edf",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00641ee1",
      "instruction": "JZ 0x00641eee"
    },
    {
      "address": "00641ee3",
      "instruction": "MOV dword ptr [ESP + 0x10],EBX"
    },
    {
      "address": "00641ee7",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00641ee9",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00641eec",
      "instruction": "CALL EDX"
    },
    {
      "address": "00641eee",
      "instruction": "MOV ECX,dword ptr [ESI]"
    },
    {
      "address": "00641ef0",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00641ef2",
      "instruction": "JZ 0x00641efd"
    },
    {
      "address": "00641ef4",
      "instruction": "MOV dword ptr [ESI],EBX"
    },
    {
      "address": "00641ef6",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00641ef8",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00641efb",
      "instruction": "CALL EDX"
    },
    {
      "address": "00641efd",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
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
  "abi": {},
  "analogues": [
    {
      "match_basis": [
        "shared_vtable:vtable:0x013ff6ac,vtable:0x014627bc"
      ],
      "package": "PKG-16-SPOREPEDIA-ONLINE",
      "score": 4,
      "symbol": "Sporepedia_cSPAssetDataOTDB_IsEditable_00641400",
      "va": "0x00641400"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x013ff6ac,vtable:0x0147ca30"
      ],
      "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
      "score": 4,
      "symbol": "sporepedia_func7ch_00641460",
      "va": "0x00641460"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70"
      ],
      "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
      "score": 4,
      "symbol": "sporepedia_func3ch_006417b0",
      "va": "0x006417b0"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70"
      ],
      "package": "PKG-16-SPOREPEDIA-ONLINE",
      "score": 4,
      "symbol": "Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0",
      "va": "0x006417c0"
    }
  ],
  "audit_evidence_boundary": null,
  "audit_findings": [],
  "audit_status": null,
  "blocked": false,
  "blockers": [],
  "body_status": null,
  "class_type": null,
  "cluster": "sporepedia-online",
  "confidence": null,
  "dependencies": {
    "callees": [
      {
        "name": null,
        "reconstructed": false,
        "va": "0x0067dcd0"
      }
    ],
    "callees_truncated": false,
    "callers": [],
    "callers_truncated": false,
    "data_reference_count": 0,
    "edges": [
      {
        "callsite": "0x00641e7c",
        "direction": "out",
        "other": "0x0067dcd0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00641ed4",
        "direction": "out",
        "other": "0x0067dcd0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00641f40",
        "direction": "out",
        "other": "0x0067dcd0",
        "reference_type": "direct-call"
      }
    ],
    "edges_truncated": false,
    "external_callees": [],
    "fan_in": 0,
    "fan_out": 1,
    "manifest_callees": [],
    "manifest_callers": [],
    "nearby_reconstructed": [],
    "scc": {
      "id": "scc-0166",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "INFERRED",
  "globals": [],
  "integration_status": null,
  "name": "FUN_00641e40",
  "normalized_symbol": "FUN_00641e40",
  "observed_mechanics": [],
  "ownership": {
    "claimability": "queue_candidate",
    "handoff_packages": [],
    "manifest": {
      "record": null,
      "worker_ownership": null
    },
    "package": null,
    "queue_state": "candidate"
  },
  "package": null,
  "reconstructed": false,
  "review_status": null,
  "runtime": {
    "blocking_reason": null,
    "gates": [],
    "validated": 0
  },
  "runtime_gated": false,
  "runtime_validated": 0,
  "semantic": null,
  "semantic_status": null,
  "services": [],
  "source": {
    "decomp": null,
    "file": null,
    "files": [],
    "handoffs": [],
    "metadata": [],
    "provenance": []
  },
  "status": "candidate",
  "subsystem": "Sporepedia",
  "triage": {
    "category": "GAMEPLAY_LOGIC",
    "cluster": "sporepedia-online",
    "db_triage_status": "candidate",
    "decomp_path": null,
    "dependencies": [],
    "evidence": "INFERRED",
    "kg_node_id": "fun:00641e40",
    "name": "FUN_00641e40",
    "priority": "P1",
    "provenance": {
      "classifier": "triage-v5",
      "sdk_name": null,
      "snapshot": "f0e310e0",
      "snapshot_sha256": "f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b",
      "vtable_addrs": [
        "013ff6ac",
        "014627bc",
        "0147ca30",
        "0147ca70",
        "0147caf8",
        "0147cc14",
        "014890f4",
        "01489414"
      ]
    },
    "queue_state": "candidate",
    "rank": 246
  },
  "types": [],
  "unresolved_questions": [],
  "va": "0x00641e40",
  "vtables": [
    "vtable:0x013ff6ac",
    "vtable:0x014627bc",
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
    "vtable:0x0147caf8",
    "vtable:0x0147cc14",
    "vtable:0x014890f4",
    "vtable:0x01489414"
  ]
}
```

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00641f9c",
  "body_span_bytes": 349,
  "body_start": "00641e40",
  "callees": [
    "App::IGameModeManager::Get"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00641e40",
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
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00641e40",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x241e40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00641e40(void)",
  "size_bytes": 349,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00641e40",
  "vtables": {
    "referenced_by_vtables": [
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x013ff6ac",
      "0x0147cc14",
      "0x014890f4",
      "0x01489414",
      "0x014627bc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "013ff6f4"
    },
    {
      "from": "01462804"
    },
    {
      "from": "0147caa4"
    },
    {
      "from": "0147cb6c"
    },
    {
      "from": "0147cc5c"
    },
    {
      "from": "0148913c"
    },
    {
      "from": "0148945c"
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
  "files": [],
  "handoffs": [],
  "metadata": []
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ff6ac",
  "vtable:0x014627bc",
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
  "vtable:0x0147cc14",
  "vtable:0x014890f4",
  "vtable:0x01489414"
]
```

## Conflicts

```json
[]
```
