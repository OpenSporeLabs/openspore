# Evidence 0x0057ac00

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6b7427f646045602fed83d43ddfffc7b5c0cc016b5a69581bf934caa7adb65d0`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall with a hidden pointer return",
  "hidden_receiver": "read",
  "hidden_this_register": "ECX, spilled to ESI at 0x0057ac07; the body reads [ESI + 0x24], [ESI + 0x48], [ESI + 0x98], [ESI + 0x2a8], [ESI + 0x4b1] and [ESI + 0x4b2] and, through 0x0057a960 and 0x0057a9e0, [ESI + 0x1cc]",
  "ordinary_stack_argument_slots": 4,
  "receiver": true,
  "ret_form": "RET 0x10",
  "return_note": "(a pointer to a 16-byte four-dword structure)",
  "return_observation": "0x0057add8 MOV EAX,dword ptr [ESP + 0x64] loads argument 1 into EAX after the last helper call, and 0x0057ade8/0x0057adee/0x0057adf7/0x0057adfa write the four dwords through EAX. EAX is never otherwise written between 0x0057add8 and the RET. The early path agrees: 0x0057ac1d MOV EAX,dword ptr [ESP + 0x5c] then four stores through EAX then 0x0057ac35 RET 0x10.",
  "return_register": "EAX",
  "return_semantics": "returns the same pointer that was passed as argument 1; all six callers immediately dereference EAX as [EAX], [EAX + 4], [EAX + 8] and [EAX + 0xc]",
  "return_type": "EditMask0057ac00*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "[ESP + 0x5c]",
      "read_at": [
        "0x0057ac1d",
        "0x0057add8"
      ],
      "role": "pointer to the 16-byte output buffer; also the return value",
      "slot": 1,
      "written_at": [
        "0x0057ac23",
        "0x0057ac25",
        "0x0057ac28",
        "0x0057ac2b",
        "0x0057ade8",
        "0x0057adee",
        "0x0057adf7",
        "0x0057adfa"
      ]
    },
    {
      "frame_offset": "[ESP + 0x60]",
      "read_at": [
        "0x0057ac6b",
        "0x0057ac83",
        "0x0057ad38",
        "0x0057ad8c"
      ],
      "role": "the edit-history record; becomes the `this` of 0x004bac30 at 0x0057ac83 and the first argument of 0x004efb20 / 0x004ef880",
      "slot": 2
    },
    {
      "frame_offset": "[ESP + 0x64]",
      "read_at": [
        "0x0057adc9",
        "0x0057add2"
      ],
      "role": "the part name; the single argument of 0x004edf40 at 0x0057add2",
      "slot": 3
    },
    {
      "frame_offset": "[ESP + 0x68]",
      "read_at": [],
      "role": "unused; pushed as the constant 1 at five call sites (0x0058a75d, 0x0058aae8, 0x0057f794, 0x0057f7cd, 0x0058d2f0) and as the caller's EBP register at 0x0058662b, and never read by the body",
      "slot": 4
    }
  ],
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x10 via two exits: 0x0057ac35 (the global kill-switch path) and 0x0057ae01 (the normal path)"
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
      "entry_ESP+0x1c",
      "entry_ESP+0x28",
      "entry_ESP+0x2c",
      "entry_ESP+0x30",
      "entry_ESP+0x34",
      "entry_ESP+0x38",
      "entry_ESP+0x40",
      "entry_ESP+0x54"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
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
    "ret_form": "RET 0x10",
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
        "entry_offset": "entry_ESP+0x1c",
        "observed": true,
        "ordinal": 7,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x28",
        "observed": true,
        "ordinal": 10,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x2c",
        "observed": true,
        "ordinal": 11,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x30",
        "observed": true,
        "ordinal": 12,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x34",
        "observed": true,
        "ordinal": 13,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x38",
        "observed": true,
        "ordinal": 14,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x54",
        "observed": true,
        "ordinal": 21,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -36, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x10 pops less than the highest read slot 0x54; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x10 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x10 but entry slot 0x54 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "84566fd1a50c55ac26c4bf2ec9165a6ac9e9ee9755c7ab7f0fd2358e961c8f8b",
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
    "persisted_calling_convention": "__thiscall with a hidden pointer return"
  },
  "dispatch": {
    "call_offset
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "app_direct_property_list_get_direct_bool_006a25a0",
    "reconstructed": true,
    "va": "0x006a25a0"
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
    "va": "0x0057ea30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057f6c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00586410"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058a5a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058a950"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058d1c0"
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
  "count": 166,
  "instructions": [
    {
      "address": "0057ac00",
      "instruction": "SUB ESP,0x48"
    },
    {
      "address": "0057ac03",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0057ac04",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0057ac05",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0057ac06",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0057ac07",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0057ac09",
      "instruction": "MOV ECX,dword ptr [0x015fd918]"
    },
    {
      "address": "0057ac0f",
      "instruction": "PUSH 0x55d7ca1"
    },
    {
      "address": "0057ac14",
      "instruction": "CALL 0x006a25a0"
    },
    {
      "address": "0057ac19",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0057ac1b",
      "instruction": "JZ 0x0057ac38"
    },
    {
      "address": "0057ac1d",
      "instruction": "MOV EAX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "0057ac21",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0057ac23",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "0057ac25",
      "instruction": "MOV dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "0057ac28",
      "instruction": "MOV dword ptr [EAX + 0x8],ECX"
    },
    {
      "address": "0057ac2b",
      "instruction": "MOV dword ptr [EAX + 0xc],ECX"
    },
    {
      "address": "0057ac2e",
      "instruction": "POP EDI"
    },
    {
      "address": "0057ac2f",
      "instruction": "POP ESI"
    },
    {
      "address": "0057ac30",
      "instruction": "POP EBP"
    },
    {
      "address": "0057ac31",
      "instruction": "POP EBX"
    },
    {
      "address": "0057ac32",
      "instruction": "ADD ESP,0x48"
    },
    {
      "address": "0057ac35",
      "instruction": "RET 0x10"
    },
    {
      "address": "0057ac38",
      "instruction": "LEA EAX,[ESP + 0x38]"
    },
    {
      "address": "0057ac3c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0057ac3d",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0057ac3f",
      "instruction": "CALL 0x0057a960"
    },
    {
      "address": "0057ac44",
      "instruction": "LEA ECX,[ESP + 0x48]"
    },
    {
      "address": "0057ac48",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0057ac49",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0057ac4b",
      "instruction": "CALL 0x0057a9e0"
    },
    {
      "address": "0057ac50",
      "instruction": "MOV ECX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "0057ac54",
      "instruction": "OR ECX,dword ptr [EAX]"
    },
    {
      "address": "0057ac56",
      "instruction": "MOV EDX,dword ptr [ESP + 0x3c]"
    },
    {
      "address": "0057ac5a",
      "instruction": "OR EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0057ac5d",
      "instruction": "MOV EDI,dword ptr [ESP + 0x40]"
    },
    {
      "address": "0057ac61",
      "instruction": "OR EDI,dword ptr [EAX + 0x8]"
    },
    {
      "address": "0057ac64",
      "instruction": "MOV EBP,dword ptr [ESP + 0x44]"
    },
    {
      "address": "0057ac68",
      "instruction": "OR EBP,dword ptr [EAX + 0xc]"
    },
    {
      "address": "0057ac6b",
      "instruction": "MOV EBX,dword ptr [ESP + 0x60]"
    },
    {
      "address": "0057ac6f",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0057ac71",
      "instruction": "SUB ESP,0x10"
    },
    {
      "address": "0057ac74",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "0057ac76",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "0057ac78",
      "instruction": "MOV dword ptr [EAX + 0x4],EDX"
    },
    {
      "address": "0057ac7b",
      "instruction": "LEA EDX,[ESP + 0x3c]"
    },
    {
      "address": "0057ac7f",
      "instruction": "MOV dword ptr [EAX + 0x8],EDI"
    },
    {
      "address": "0057ac82",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0057ac83",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "0057ac85",
      "instruction": "MOV dword ptr [EAX + 0xc],EBP"
    },
    {
      "address": "0057ac88",
      "instruction": "CALL 0x004bac30"
    },
    {
      "address": "0057ac8d",
      "instruction": "MOV EAX,dword ptr [ESI + 0x2a8]"
    },
    {
      "address": "0057ac93",
      "instruction": "CMP EAX,0x2b978c46"
    },
    {
      "address": "0057ac98",
      "instruction": "JZ 0x0057aca1"
    },
    {
      "address": "0057ac9a",
      "instruction": "CMP EAX,0x3d97a8e4"
    },
    {
      "address": "0057ac9f",
      "instruction": "JNZ 0x0057ad03"
    },
    {
      "address": "0057aca1",
      "instruction": "MOV ECX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "0057aca7",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "0057aca9",
      "instruction": "CALL 0x004accf0"
    },
    {
      "address": "0057acae",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "0057acb0",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "0057acb2",
      "instruction": "JLE 0x0057acf1"
    },
    {
      "address": "0057acb4",
      "instruction": "MOV ECX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "0057acba",
      "instruction": "PUSH 0xb00f0fec"
    },
    {
      "address": "0057acbf",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0057acc0",
      "instruction": "CALL 0x004accb0"
    },
    {
      "address": "0057acc5",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0057acc7",
      "instruction": "CALL 0x00435b60"
    },
    {
      "address": "0057accc",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0057acce",
      "instruction": "JNZ 0x0057acfb"
    },
    {
      "address": "0057acd0",
      "instruction": "MOV ECX,dword ptr [ESI + 0x98]"
    },
    {
      "address": "0057acd6",
      "in
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
  "original_bytes": 12356,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall with a hidden pointer return\",\n    \"hidden_receiver\": \"read\",\n    \"hidden_this_register\": \"ECX, spilled to ESI at 0x0057ac07; the body reads [ESI + 0x24], [ESI + 0x48], [ESI + 0x98], [ESI + 0x2a8], [ESI + 0x4b1] and [ESI + 0x4b2] and, through 0x0057a960 and 0x0057a9e0, [ESI + 0x1cc]\",\n    \"ordinary_stack_argument_slots\": 4,\n    \"receiver\": true,\n    \"ret_form\": \"RET 0x10\",\n    \"return_note\": \"(a pointer to a 16-byte four-dword structure)\",\n    \"return_observation\": \"0x0057add8 MOV EAX,dword ptr [ESP + 0x64] loads argument 1 into EAX after the last helper call, and 0x0057ade8/0x0057adee/0x0057adf7/0x0057adfa write the four dwords through EAX. EAX is never otherwise written between 0x0057add8 and the RET. The early path agrees: 0x0057ac1d MOV EAX,dword ptr [ESP + 0x5c] then four stores through EAX then 0x0057ac35 RET 0x10.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"returns the same pointer that was passed as argument 1; all six callers immediately dereference EAX as [EAX], [EAX + 4], [EAX + 8] and [EAX + 0xc]\",\n    \"return_type\": \"EditMask0057ac00*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"frame_offset\": \"[ESP + 0x5c]\",\n        \"read_at\": [\n          \"0x0057ac1d\",\n          \"0x0057add8\"\n        ],\n        \"role\": \"pointer to the 16-byte output buffer; also the return value\",\n        \"slot\": 1,\n        \"written_at\": [\n          \"0x0057ac23\",\n          \"0x0057ac25\",\n          \"0x0057ac28\",\n          \"0x0057ac2b\",\n          \"0x0057ade8\",\n          \"0x0057adee\",\n          \"0x0057adf7\",\n          \"0x0057adfa\"\n        ]\n      },\n      {\n        \"frame_offset\": \"[ESP + 0x60]\",\n        \"read_at\": [\n          \"0x0057ac6b\",\n          \"0x0057ac83\",\n          \"0x0057ad38\",\n          \"0x0057ad8c\"\n        ],\n        \"role\": \"the edit-history record; becomes the `this` of 0x004bac30 at 0x0057ac83 and the first argument of 0x004efb20 / 0x004ef880\",\n        \"slot\": 2\n      },\n      {\n        \"frame_offset\": \"[ESP + 0x64]\",\n        \"read_at\": [\n          \"0x0057adc9\",\n          \"0x0057add2\"\n        ],\n        \"role\": \"the part name; the single argument of 0x004edf40 at 0x0057add2\",\n        \"slot\": 3\n      },\n      {\n        \"frame_offset\": \"[ESP + 0x68]\",\n        \"read_at\": [],\n        \"role\": \"unused; pushed as the constant 1 at five call sites (0x0058a75d, 0x0058aae8, 0x0057f794, 0x0057f7cd, 0x0058d2f0) and as the caller's EBP register at 0x0058662b, and never read by the body\",\n        \"slot\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x10 via two exits: 0x0057ac35 (the global kill-switch path) and 0x0057ae01 (the normal path)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-PROPERTY-ADAPTER\",\n      \"score\": 3,\n      \"symbol\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n      \"va\": \"0x006a25a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"app_direct_property_list_get_direct_bool_006a25a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a25a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057ea30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057f6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00586410\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058a5a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058a950\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0058d1c0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0057eb7c\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057ea30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057f79e\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057f6c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057f7d9\",\n        \"direction\": \"in\",\n        \"other\": \"0x0057f6c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00586635\",\n        \"direction\": \"in\",\n        \"other\": \"0x00586410\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058a768\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058a5a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058aaf3\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058a950\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0058d2fb\",\n        \"direction\": \"in\",\n        \"other\": \"0x0058d1c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057acc7\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435b60\",\n        \"reference_type\": \"direct-ca
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
  "body_end": "0057ae03",
  "body_span_bytes": 516,
  "body_start": "0057ac00",
  "callees": [
    "FUN_004efb20",
    "FUN_0057a960",
    "FUN_004accb0",
    "FUN_0057a9e0",
    "FUN_004ef880",
    "FUN_004accf0",
    "FUN_004edf40",
    "FUN_004bac30",
    "Prop_GetPropValueBool",
    "FUN_00435b60",
    "App::Property::GetKey"
  ],
  "callers": [
    "Editors::cEditor::CommitEditHistory",
    "FUN_0057f6c0",
    "FUN_0058d1c0",
    "Editors::cEditor::Undo",
    "FUN_0057ea30",
    "Editors::cEditor::Redo"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0057ac00",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:1",
      "type": "undefined"
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
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "local_64",
      "storage": "Stack[-0x64]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_6c",
      "storage": "Stack[-0x6c]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 19,
  "mode": "live",
  "name": "FUN_0057ac00",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x17ac00",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0057ac00(void)",
  "size_bytes": 516,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0057ac00",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00586635"
    },
    {
      "from": "0057eb7c"
    },
    {
      "from": "0058a768"
    },
    {
      "from": "0058aaf3"
    },
    {
      "from": "0058d2fb"
    },
    {
      "from": "0057f79e"
    },
    {
      "from": "0057f7d9"
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
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b05/editor_0057ac00_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b05/0057ac00.json"
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
    "A differential trace that mutates a model with and without a mouth part would be required to confirm the bit-0x400 polarity end to end.",
    "A runtime trace is required to read the eight mask globals after initialisation, to observe the actual property values behind ids 0x055D7CA1, 0x7A926123 and 0xF5CBE065, to see which capability bits the evaluator grants in practice, and to confirm the runtime class of the object at cEditor + 0x1CC.",
    "No original-process trace has been captured for 0x0057ac00. Every claim in this record is static.",
    "The Cell stage has never been entered in any recorded run, so the cll branch of the mouth scan has no runtime oracle."
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
  "EditMask0057ac00* (a pointer to a 16-byte four-dword structure)"
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
