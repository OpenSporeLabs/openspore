# Evidence 0x00641cd0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `aecc1c80814572015d64a1ee11f7791072b7d9574608c4fb5126d6c8367f46e5`

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
    "flow_not_modelled: the linear ESP walk ends at +68, so the listing is not one path",
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
  "content_sha256": "290f0b1550213cadd1c7c5f48f2e4d000999d47540f4373fc1e193aeab3fd654",
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
    "indirect_calls": 10,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0055"
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
        "obs-0023"
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
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0024",
        "obs-0028",
        "obs-0031",
        "obs-0034",
        "obs-0036",
        "obs-0042",
        "obs-0044",
        "obs-0050"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          8,
          12,
          28,
          112
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0024",
        "obs-0028",
        "obs-0031",
        "obs-0034",
        "obs-0036",
        "obs-0042",
        "obs-0044",
        "obs-0050",
        "obs-0055"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0055"
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
        "obs-0055"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0055"
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
      "at": "0x00641cd0",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00641cd0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00641cd3",
      "count": 9,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00641cd4",
      "count": 13,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBP,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00641cd4",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ECX",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at":
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
    "flow_not_modelled: the linear ESP walk ends at +68, so the listing is not one path",
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
  "content_sha256": "290f0b1550213cadd1c7c5f48f2e4d000999d47540f4373fc1e193aeab3fd654",
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
    "indirect_calls": 10,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0055"
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
        "obs-0023"
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
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0024",
        "obs-0028",
        "obs-0031",
        "obs-0034",
        "obs-0036",
        "obs-0042",
        "obs-0044",
        "obs-0050"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          4,
          8,
          12,
          28,
          112
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0024",
        "obs-0028",
        "obs-0031",
        "obs-0034",
        "obs-0036",
        "obs-0042",
        "obs-0044",
        "obs-0050",
        "obs-0055"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0055"
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
        "obs-0055"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0055"
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
      "at": "0x00641cd0",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "SUB ESP,0x10",
      "sub": 16
    },
    {
      "at": "0x00641cd0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x10",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00641cd3",
      "count": 9,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00641cd4",
      "count": 13,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV EBP,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00641cd4",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ECX",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at":
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
  "count": 117,
  "instructions": [
    {
      "address": "00641cd0",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "00641cd3",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00641cd4",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00641cd6",
      "instruction": "MOV ECX,dword ptr [EBP + 0x8]"
    },
    {
      "address": "00641cd9",
      "instruction": "MOV EAX,dword ptr [EBP + 0x4]"
    },
    {
      "address": "00641cdc",
      "instruction": "MOV EDX,dword ptr [EBP + 0xc]"
    },
    {
      "address": "00641cdf",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00641ce0",
      "instruction": "MOV dword ptr [ESP + 0x10],ECX"
    },
    {
      "address": "00641ce4",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00641ce5",
      "instruction": "MOV dword ptr [ESP + 0x10],EAX"
    },
    {
      "address": "00641ce9",
      "instruction": "MOV dword ptr [ESP + 0x18],EDX"
    },
    {
      "address": "00641ced",
      "instruction": "MOV dword ptr [ESP + 0x14],0x30bdee3"
    },
    {
      "address": "00641cf5",
      "instruction": "MOV dword ptr [ESP + 0xc],0x0"
    },
    {
      "address": "00641cfd",
      "instruction": "CALL 0x0067dcd0"
    },
    {
      "address": "00641d02",
      "instruction": "CMP byte ptr [ESP + 0x20],0x0"
    },
    {
      "address": "00641d07",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00641d0b",
      "instruction": "JZ 0x00641d82"
    },
    {
      "address": "00641d0d",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00641d0f",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00641d11",
      "instruction": "JZ 0x00641d22"
    },
    {
      "address": "00641d13",
      "instruction": "MOV dword ptr [ESP + 0xc],0x0"
    },
    {
      "address": "00641d1b",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00641d1d",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00641d20",
      "instruction": "CALL EDX"
    },
    {
      "address": "00641d22",
      "instruction": "MOV ECX,dword ptr [EBP + 0x70]"
    },
    {
      "address": "00641d25",
      "instruction": "LEA ESI,[EBP + 0x70]"
    },
    {
      "address": "00641d28",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00641d2a",
      "instruction": "JZ 0x00641d39"
    },
    {
      "address": "00641d2c",
      "instruction": "MOV dword ptr [ESI],0x0"
    },
    {
      "address": "00641d32",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00641d34",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00641d37",
      "instruction": "CALL EDX"
    },
    {
      "address": "00641d39",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00641d3b",
      "instruction": "MOV EAX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00641d3e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641d40",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641d42",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641d44",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641d46",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641d48",
      "instruction": "LEA ECX,[ESP + 0x20]"
    },
    {
      "address": "00641d4c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00641d4d",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00641d4e",
      "instruction": "LEA EDX,[ESP + 0x2c]"
    },
    {
      "address": "00641d52",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00641d53",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00641d55",
      "instruction": "CALL EAX"
    },
    {
      "address": "00641d57",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00641d59",
      "instruction": "JZ 0x00641df3"
    },
    {
      "address": "00641d5f",
      "instruction": "MOV ECX,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00641d63",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00641d65",
      "instruction": "JZ 0x00641e02"
    },
    {
      "address": "00641d6b",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00641d6d",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00641d70",
      "instruction": "PUSH 0x30bdee3"
    },
    {
      "address": "00641d75",
      "instruction": "CALL EAX"
    },
    {
      "address": "00641d77",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00641d78",
      "instruction": "LEA ECX,[EBP + 0x1c]"
    },
    {
      "address": "00641d7b",
      "instruction": "CALL 0x00b5f950"
    },
    {
      "address": "00641d80",
      "instruction": "JMP 0x00641df3"
    },
    {
      "address": "00641d82",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00641d84",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00641d86",
      "instruction": "JZ 0x00641d97"
    },
    {
      "address": "00641d88",
      "instruction": "MOV dword ptr [ESP + 0xc],0x0"
    },
    {
      "address": "00641d90",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00641d92",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "00641d95",
      "instruction": "CALL EAX"
    },
    {
      "address": "00641d97",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00641d99",
      "instruction": "MOV EDX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00641d9c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641d9e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641da0",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00641da2"
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
        "shared_vtable:vtable:0x013ff6ac,vtable:0x01462764"
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
        "shared_vtable:vtable:0x01462764"
      ],
      "package": "PKG-16-SPOREPEDIA-ONLINE",
      "score": 4,
      "symbol": "Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770",
      "va": "0x00641770"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x01462764,vtable:0x0147ca30"
      ],
      "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
      "score": 4,
      "symbol": "sporepedia_func3ch_006417b0",
      "va": "0x006417b0"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x01462764,vtable:0x0147ca30"
      ],
      "package": "PKG-16-SPOREPEDIA-ONLINE",
      "score": 4,
      "symbol": "Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0",
      "va": "0x006417c0"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x01462764,vtable:0x0147cbbc"
      ],
      "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
      "score": 4,
      "symbol": "sporepedia_get_author_name_00641810",
      "va": "0x00641810"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x01462764,vtable:0x0147cbbc"
      ],
      "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
      "score": 4,
      "symbol": "sporepedia_get_author_id_00641820",
      "va": "0x00641820"
    },
    {
      "match_basis": [
        "shared_vtable:vtable:0x01462764,vtable:0x0147cbbc"
      ],
      "package": "PKG-SPOREPEDIA-ACCESSORS-WAVE6",
      "score": 4,
      "symbol": "sporepedia_get_tags_00641850",
      "va": "0x00641850"
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
        "callsite": "0x00641cfd",
        "direction": "out",
        "other": "0x0067dcd0",
        "reference_type": "direct-call"
      },
      {
        "callsite": "0x00641d7b",
        "direction": "out",
        "other": "0x00b5f950",
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
      "id": "scc-0164",
      "size": 1
    },
    "vtable_reference_count": 0
  },
  "evidence_level": "INFERRED",
  "globals": [],
  "integration_status": null,
  "name": "FUN_00641cd0",
  "normalized_symbol": "FUN_00641cd0",
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
    "kg_node_id": "fun:00641cd0",
    "name": "FUN_00641cd0",
    "priority": "P1",
    "provenance": {
      "classifier": "triage-v5",
      "sdk_name": null,
      "snapshot": "f0e310e0",
      "snapshot_sha256": "f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a012ddbf8b54b",
      "vtable_addrs": [
        "013ff6ac",
        "01462764",
        "014627bc",
        "0147ca30",
        "0147ca70",
        "0147caf8",
        "0147cbbc",
        "0147cc14",
        "014890f4",
        "01489414"
      ]
    },
    "queue_state": "candidate",
    "rank": 240
  },
  "types": [],
  "unresolved_questions": [],
  "va": "0x00641cd0",
  "vtables": [
    "vtable:0x013ff6ac",
    "vtable:0x01462764",
    "vtable:0x014627bc",
    "vtable:0x0147ca30",
    "vtable:0x0147ca70",
    "vtable:0x0147caf8",
    "vtable:0x0147cbbc",
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
  "body_end": "00641e0a",
  "body_span_bytes": 315,
  "body_start": "00641cd0",
  "callees": [
    "App::IGameModeManager::Get",
    "FUN_00b5f950"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00641cd0",
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
    }
  ],
  "locals_count": 4,
  "mode": "live",
  "name": "FUN_00641cd0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x241cd0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00641cd0(void)",
  "size_bytes": 315,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00641cd0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01462764",
      "0x0147ca30",
      "0x0147ca70",
      "0x0147caf8",
      "0x0147cbbc",
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
      "from": "013ff6ec"
    },
    {
      "from": "014627fc"
    },
    {
      "from": "0147ca9c"
    },
    {
      "from": "0147cb64"
    },
    {
      "from": "0147cc54"
    },
    {
      "from": "01489134"
    },
    {
      "from": "01489454"
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
  "vtable:0x01462764",
  "vtable:0x014627bc",
  "vtable:0x0147ca30",
  "vtable:0x0147ca70",
  "vtable:0x0147caf8",
  "vtable:0x0147cbbc",
  "vtable:0x0147cc14",
  "vtable:0x014890f4",
  "vtable:0x01489414"
]
```

## Conflicts

```json
[]
```
