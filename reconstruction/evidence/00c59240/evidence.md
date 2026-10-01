# Evidence 0x00c59240

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `d3703caa663a2662362551e5aca726fbed28fb0b10e815a954e782e1c344a75b`

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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +76, so the listing is not one path",
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
  "content_sha256": "e022312e59c1de6a0350a2b4f9f54b93f6fc52e91fe69dce1fa5f02731c0111c",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0106"
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
        "obs-0004",
        "obs-0009",
        "obs-0028"
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
        "obs-0012",
        "obs-0013",
        "obs-0015",
        "obs-0017",
        "obs-0055",
        "obs-0067",
        "obs-0081",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0091",
        "obs-0092",
        "obs-0094",
        "obs-0098"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          156,
          524
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0013",
        "obs-0015",
        "obs-0017",
        "obs-0055",
        "obs-0067",
        "obs-0081",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0091",
        "obs-0092",
        "obs-0094",
        "obs-0098",
        "obs-0106"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0106"
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
      "id": "o
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +76, so the listing is not one path",
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
  "content_sha256": "e022312e59c1de6a0350a2b4f9f54b93f6fc52e91fe69dce1fa5f02731c0111c",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0106"
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
        "obs-0004",
        "obs-0009",
        "obs-0028"
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
        "obs-0012",
        "obs-0013",
        "obs-0015",
        "obs-0017",
        "obs-0055",
        "obs-0067",
        "obs-0081",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0091",
        "obs-0092",
        "obs-0094",
        "obs-0098"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          156,
          524
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0012",
        "obs-0013",
        "obs-0015",
        "obs-0017",
        "obs-0055",
        "obs-0067",
        "obs-0081",
        "obs-0082",
        "obs-0085",
        "obs-0087",
        "obs-0091",
        "obs-0092",
        "obs-0094",
        "obs-0098",
        "obs-0106"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0106"
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
      "id": "o
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "address_window_offset_005c65e0",
    "reconstructed": true,
    "va": "0x005c65e0"
  },
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b8d9b0"
  },
  {
    "name": "FUN_00b8de30",
    "reconstructed": false,
    "va": "0x00b8de30"
  },
  {
    "name": "star_regenerate_00bb4af0",
    "reconstructed": true,
    "va": "0x00bb4af0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb9af0"
  },
  {
    "name": "FUN_00bba790",
    "reconstructed": false,
    "va": "0x00bba790"
  },
  {
    "name": "FUN_01021370",
    "reconstructed": false,
    "va": "0x01021370"
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
    "va": "0x00c59b50"
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
  "count": 228,
  "instructions": [
    {
      "address": "00c59240",
      "instruction": "SUB ESP,0x58"
    },
    {
      "address": "00c59243",
      "instruction": "MOV EAX,dword ptr [ESP + 0x60]"
    },
    {
      "address": "00c59247",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c59248",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c59249",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c5924a",
      "instruction": "MOV ESI,dword ptr [ESP + 0x68]"
    },
    {
      "address": "00c5924e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c5924f",
      "instruction": "SUB EAX,ESI"
    },
    {
      "address": "00c59251",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00c59253",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c59254",
      "instruction": "MOV ECX,0x1601760"
    },
    {
      "address": "00c59259",
      "instruction": "CALL 0x00a68fb0"
    },
    {
      "address": "00c5925e",
      "instruction": "MOV ECX,dword ptr [EBP + 0x9c]"
    },
    {
      "address": "00c59264",
      "instruction": "MOV ECX,dword ptr [ECX + 0x13c]"
    },
    {
      "address": "00c5926a",
      "instruction": "ADD EAX,ESI"
    },
    {
      "address": "00c5926c",
      "instruction": "MOV dword ptr [ESP + 0x20],EAX"
    },
    {
      "address": "00c59270",
      "instruction": "CALL 0x00b8de30"
    },
    {
      "address": "00c59275",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00c59277",
      "instruction": "MOV dword ptr [ESP + 0x18],EBX"
    },
    {
      "address": "00c5927b",
      "instruction": "CALL 0x01021370"
    },
    {
      "address": "00c59280",
      "instruction": "MOV dword ptr [ESP + 0x1c],EAX"
    },
    {
      "address": "00c59284",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c59286",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00c59288",
      "instruction": "MOV dword ptr [ESP + 0x24],EAX"
    },
    {
      "address": "00c5928c",
      "instruction": "MOV dword ptr [ESP + 0x28],EAX"
    },
    {
      "address": "00c59290",
      "instruction": "MOV dword ptr [ESP + 0x2c],EAX"
    },
    {
      "address": "00c59294",
      "instruction": "CALL 0x00c45b80"
    },
    {
      "address": "00c59299",
      "instruction": "FSTP float ptr [ESP + 0x70]"
    },
    {
      "address": "00c5929d",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00c5929f",
      "instruction": "CALL 0x00c45bd0"
    },
    {
      "address": "00c592a4",
      "instruction": "FSTP float ptr [ESP + 0x14]"
    },
    {
      "address": "00c592a8",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00c592aa",
      "instruction": "CALL 0x00c45c20"
    },
    {
      "address": "00c592af",
      "instruction": "MOV EDX,dword ptr [EBP + 0x20c]"
    },
    {
      "address": "00c592b5",
      "instruction": "LEA ESI,[EBP + 0x208]"
    },
    {
      "address": "00c592bb",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00c592bd",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00c592bf",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c592c0",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c592c1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c592c3",
      "instruction": "CALL 0x00c58770"
    },
    {
      "address": "00c592c8",
      "instruction": "FLDZ"
    },
    {
      "address": "00c592ca",
      "instruction": "FLD float ptr [ESP + 0x70]"
    },
    {
      "address": "00c592ce",
      "instruction": "MOVSS XMM0,dword ptr [0x013eb1bc]"
    },
    {
      "address": "00c592d6",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00c592d8",
      "instruction": "FCOMIP ST0,ST1"
    },
    {
      "address": "00c592da",
      "instruction": "FSTP ST0"
    },
    {
      "address": "00c592dc",
      "instruction": "MOV dword ptr [ESP + 0x54],EAX"
    },
    {
      "address": "00c592e0",
      "instruction": "MOVSS dword ptr [ESP + 0x58],XMM0"
    },
    {
      "address": "00c592e6",
      "instruction": "MOVSS dword ptr [ESP + 0x5c],XMM0"
    },
    {
      "address": "00c592ec",
      "instruction": "MOVSS dword ptr [ESP + 0x60],XMM0"
    },
    {
      "address": "00c592f2",
      "instruction": "MOV dword ptr [ESP + 0x64],EAX"
    },
    {
      "address": "00c592f6",
      "instruction": "JC 0x00c59304"
    },
    {
      "address": "00c592f8",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x70]"
    },
    {
      "address": "00c592fe",
      "instruction": "MOVSS dword ptr [ESP + 0x58],XMM0"
    },
    {
      "address": "00c59304",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00c5930a",
      "instruction": "COMISS XMM0,dword ptr [0x01485378]"
    },
    {
      "address": "00c59311",
      "instruction": "JBE 0x00c59319"
    },
    {
      "address": "00c59313",
      "instruction": "MOVSS dword ptr [ESP + 0x5c],XMM0"
    },
    {
      "address": "00c59319",
      "instruction": "MOV dword ptr [ESP + 0x4c],0x1ff1"
    },
    {
      "address": "00c59321",
      "instruction": "MOV dword ptr [ESP + 0x50],0x3e"
    },
    {
      "address": "00c59329",
      "instruction": "CALL 0x00ffbe50"
    },
    {
      "address": "00c5932e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00c59330",
      "instruction": "CALL 0x00ffbfc0"
    },
    {
      "address": "00c59335",
      "instruction": "FSTP float ptr [ESP + 0x60]"
    },
    {
      "address": "00c59339",
      "instruction": "LEA ECX,[ESP + 0x24]"
    },
    {
      "address": "00c5933d",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c5933e",
      "instruction": "LEA EDX,[ESP + 0x50]"
    },
    {
      "address": "00c59342",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00c59343",
      "
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
  "original_bytes": 8678,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 9,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 9,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"address_window_offset_005c65e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c65e0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b8d9b0\"\n      },\n      {\n        \"name\": \"FUN_00b8de30\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8de30\"\n      },\n      {\n        \"name\": \"star_regenerate_00bb4af0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00bb4af0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb9af0\"\n      },\n      {\n        \"name\": \"FUN_00bba790\",\n        \"reconstructed\": false,\n        \"va\": \"0x00bba790\"\n      },\n      {\n        \"name\": \"FUN_01021370\",\n        \"reconstructed\": false,\n        \"va\": \"0x01021370\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c59b50\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c59beb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00c59b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c59349\",\n        \"direction\": \"out\",\n        \"other\": \"0x005c65e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c59259\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a68fb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c5936c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a68fb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c5934f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c593ae\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c5940a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b3d2a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c593f3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b8d9b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c59270\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b8de30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c59356\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb1080\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c593b5\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb4af0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c59411\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb59b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c59394\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bb9af0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c593bc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bba790\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c59294\",\n        \"direction\": \
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
  "body_end": "00c5953d",
  "body_span_bytes": 766,
  "body_start": "00c59240",
  "callees": [
    "FUN_005c65e0",
    "FUN_00f47380",
    "FUN_00ffbfc0",
    "FUN_00c45bd0",
    "FUN_00bba790",
    "FUN_00a68fb0",
    "FUN_00b3d2a0",
    "FUN_00c45c20",
    "FUN_00b8d9b0",
    "FUN_00b8de30",
    "FUN_00c45b80",
    "FUN_00bb1080",
    "FUN_01021370",
    "FUN_00c58770",
    "FUN_00c570e0",
    "FUN_00c58ee0",
    "FUN_00bb4af0",
    "FUN_00c57a80",
    "FUN_00bb59b0",
    "FUN_00bb9af0",
    "FUN_00ffbe50"
  ],
  "callers": [
    "FUN_00c59b50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c59240",
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
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    },
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_54",
      "storage": "Stack[-0x54]:4",
      "type": "undefined4"
    },
    {
      "name": "local_58",
      "storage": "Stack[-0x58]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_74",
      "storage": "Stack[-0x74]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 19,
  "mode": "live",
  "name": "FUN_00c59240",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x859240",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c59240(void)",
  "size_bytes": 766,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c59240",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00c59beb"
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
