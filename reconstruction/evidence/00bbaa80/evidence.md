# Evidence 0x00bbaa80

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7680457b33f6c7adfcd8fdd0ae71253e0001f9384776d01773de229e7bf33657`

## abi

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
      "entry_ESP+0x4f",
      "entry_ESP+0x68"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4f",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x68",
        "observed": true,
        "ordinal": 26,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
        "entry_offset": "entry_ESP+0x4f",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x68",
        "observed": true,
        "ordinal": 26,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -184, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0xc8; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0xc8 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "af9ecebc5a71b0eb37bec1e7a78bc8bcc156aa5457b945bce95856169d7903ae",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008",
        "obs-0015",
        "obs-0087"
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
        "obs-0015",
        "obs-0087"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0023",
        "obs-0024",
        "obs-0027",
        "obs-0028",
        "obs-0029",
        "obs-0033",
        "obs-0034",
        "obs-0036",
        "obs-0037",
        "obs-0038",
        "obs-0039",
        "obs-0040",
        "obs-0041",
        "obs-0042",
        "obs-0043",
        "obs-0044",
        "obs-0045",
        "obs-0047",
        "obs-0048",
        "obs-0050",
        "obs-0051",
        "obs-0052",
        "obs-0053",
        "obs-0054",
        "obs-0056",
        "obs-0057",
        "obs-0059",
        "obs-0061",
        "obs-0064",
        "obs-0065",
        "obs-0067",
        "obs-0068",
        "obs-0070",
        "obs-0074",
        "obs-0075",
        "obs-0077",
        "obs-0078",
        "obs-0080",
        "obs-0081",
        "obs-0083"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 29,
        "observed_slots": 21,
        "total_bytes": 200
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0018",
        "obs-0019",
        "obs-0020",
        "obs-0033",
        "obs-0034",
        "obs-0037",
        "obs-0043",
        "obs-0047",
        "obs-0048",
        "obs-0051",
        "obs-0057",
        "obs-0061",
        "obs-0064",
        "obs-0074",
        "obs-0080"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88,
          132,
          172
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0087"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0015",
        "obs-0087"
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
        "obs-0008",
        "obs-0015",
 
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4f",
      "entry_ESP+0x68"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4f",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x68",
        "observed": true,
        "ordinal": 26,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
        "entry_offset": "entry_ESP+0x4f",
        "observed": true,
        "ordinal": 19,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x68",
        "observed": true,
        "ordinal": 26,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 19
    },
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -184, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x4 pops less than the highest read slot 0xc8; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x4 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x4 but entry slot 0xc8 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "af9ecebc5a71b0eb37bec1e7a78bc8bcc156aa5457b945bce95856169d7903ae",
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
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 2,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008",
        "obs-0015",
        "obs-0087"
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
        "obs-0015",
        "obs-0087"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 4,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0023",
        "obs-0024",
        "obs-0027",
        "obs-0028",
        "obs-0029",
        "obs-0033",
        "obs-0034",
        "obs-0036",
        "obs-0037",
        "obs-0038",
        "obs-0039",
        "obs-0040",
        "obs-0041",
        "obs-0042",
        "obs-0043",
        "obs-0044",
        "obs-0045",
        "obs-0047",
        "obs-0048",
        "obs-0050",
        "obs-0051",
        "obs-0052",
        "obs-0053",
        "obs-0054",
        "obs-0056",
        "obs-0057",
        "obs-0059",
        "obs-0061",
        "obs-0064",
        "obs-0065",
        "obs-0067",
        "obs-0068",
        "obs-0070",
        "obs-0074",
        "obs-0075",
        "obs-0077",
        "obs-0078",
        "obs-0080",
        "obs-0081",
        "obs-0083"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 29,
        "observed_slots": 21,
        "total_bytes": 200
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0018",
        "obs-0019",
        "obs-0020",
        "obs-0033",
        "obs-0034",
        "obs-0037",
        "obs-0043",
        "obs-0047",
        "obs-0048",
        "obs-0051",
        "obs-0057",
        "obs-0061",
        "obs-0064",
        "obs-0074",
        "obs-0080"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88,
          132,
          172
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0087"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0015",
        "obs-0087"
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
        "obs-0008",
        "obs-0015",
 
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
  "count": 172,
  "instructions": [
    {
      "address": "00bbaa80",
      "instruction": "SUB ESP,0x6c"
    },
    {
      "address": "00bbaa83",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00bbaa84",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "00bbaa86",
      "instruction": "CMP byte ptr [EDI + 0xac],0x0"
    },
    {
      "address": "00bbaa8d",
      "instruction": "JNZ 0x00bbaa98"
    },
    {
      "address": "00bbaa8f",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00bbaa91",
      "instruction": "POP EDI"
    },
    {
      "address": "00bbaa92",
      "instruction": "ADD ESP,0x6c"
    },
    {
      "address": "00bbaa95",
      "instruction": "RET 0x4"
    },
    {
      "address": "00bbaa98",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00bbaa99",
      "instruction": "CALL 0x00bba640"
    },
    {
      "address": "00bbaa9e",
      "instruction": "MOV EAX,dword ptr [EDI + 0x84]"
    },
    {
      "address": "00bbaaa4",
      "instruction": "MOV EBX,dword ptr [EAX]"
    },
    {
      "address": "00bbaaa6",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00bbaaa8",
      "instruction": "JZ 0x00bbaab3"
    },
    {
      "address": "00bbaaaa",
      "instruction": "CMP byte ptr [EBX + 0x130],0x0"
    },
    {
      "address": "00bbaab1",
      "instruction": "JNZ 0x00bbaabd"
    },
    {
      "address": "00bbaab3",
      "instruction": "POP EBX"
    },
    {
      "address": "00bbaab4",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00bbaab6",
      "instruction": "POP EDI"
    },
    {
      "address": "00bbaab7",
      "instruction": "ADD ESP,0x6c"
    },
    {
      "address": "00bbaaba",
      "instruction": "RET 0x4"
    },
    {
      "address": "00bbaabd",
      "instruction": "MOV EAX,dword ptr [EDI + 0x58]"
    },
    {
      "address": "00bbaac0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00bbaac1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00bbaac2",
      "instruction": "CALL 0x00bb9e00"
    },
    {
      "address": "00bbaac7",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00bbaaca",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "00bbaace",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bbaacf",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00bbaad1",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "00bbaad3",
      "instruction": "CALL 0x00b8dd60"
    },
    {
      "address": "00bbaad8",
      "instruction": "CMP ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00bbaadc",
      "instruction": "SETZ AL"
    },
    {
      "address": "00bbaadf",
      "instruction": "MOV byte ptr [ESP + 0xf],AL"
    },
    {
      "address": "00bbaae3",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00bbaae5",
      "instruction": "JNZ 0x00bbac6f"
    },
    {
      "address": "00bbaaeb",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00bbaaec",
      "instruction": "MOV EBP,0x1667bac"
    },
    {
      "address": "00bbaaf1",
      "instruction": "MOV dword ptr [ESP + 0x5c],EBP"
    },
    {
      "address": "00bbaaf5",
      "instruction": "MOV dword ptr [ESP + 0x60],EBP"
    },
    {
      "address": "00bbaaf9",
      "instruction": "MOV dword ptr [ESP + 0x64],0x1667bae"
    },
    {
      "address": "00bbab01",
      "instruction": "CALL 0x0067dcd0"
    },
    {
      "address": "00bbab06",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00bbab08",
      "instruction": "MOV EDX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "00bbab0b",
      "instruction": "LEA ECX,[ESP + 0x5c]"
    },
    {
      "address": "00bbab0f",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bbab10",
      "instruction": "LEA ECX,[ESP + 0x18]"
    },
    {
      "address": "00bbab14",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bbab15",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bbab17",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bbab19",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
      "address": "00bbab1d",
      "instruction": "MOV ECX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00bbab21",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00bbab25",
      "instruction": "MOV dword ptr [ESP + 0x20],EAX"
    },
    {
      "address": "00bbab29",
      "instruction": "MOV dword ptr [ESP + 0x4c],EBP"
    },
    {
      "address": "00bbab2d",
      "instruction": "MOV dword ptr [ESP + 0x50],EBP"
    },
    {
      "address": "00bbab31",
      "instruction": "MOV dword ptr [ESP + 0x54],0x1667bae"
    },
    {
      "address": "00bbab39",
      "instruction": "MOV dword ptr [ESP + 0x24],ECX"
    },
    {
      "address": "00bbab3d",
      "instruction": "MOV dword ptr [ESP + 0x28],EDX"
    },
    {
      "address": "00bbab41",
      "instruction": "MOV dword ptr [ESP + 0x20],ESI"
    },
    {
      "address": "00bbab45",
      "instruction": "CALL 0x0067dcd0"
    },
    {
      "address": "00bbab4a",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00bbab4c",
      "instruction": "MOV EDX,dword ptr [EDX + 0x7c]"
    },
    {
      "address": "00bbab4f",
      "instruction": "LEA ECX,[ESP + 0x4c]"
    },
    {
      "address": "00bbab53",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bbab54",
      "instruction": "LEA ECX,[ESP + 0x24]"
    },
    {
      "address": "00bbab58",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00bbab59",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00bbab5b",
      "instruction": "CALL EDX"
    },
    {
      "address": "00bbab5d",
      "instruction": "MOV EAX,dword ptr [ESP + 0x14]"
    },
    {
    
[TRUNCATED]
```

## external_callees

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## function_identity

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## ghidra_function

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089`

```json
{
  "binary_available": true,
  "binary_sha256": "25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
  "body_end": "00bbac7b",
  "body_span_bytes": 508,
  "body_start": "00bbaa80",
  "callees": [
    "FUN_00472fe0",
    "FUN_00b8dde0",
    "FUN_00f47380",
    "FUN_00454cb0",
    "FUN_0093c570",
    "FUN_00bb9e00",
    "FUN_00618890",
    "FUN_00ba8010",
    "FUN_00bba640",
    "FUN_00b3d2a0",
    "FUN_00b8dd60",
    "App::IGameModeManager::Get"
  ],
  "callers": [
    "FUN_00deb930",
    "FUN_00df47b0",
    "FUN_00ba6e00"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00bbaa80",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_69",
      "storage": "Stack[-0x69]:1",
      "type": "undefined1"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_00bbaa80",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x7baa80",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00bbaa80(void)",
  "size_bytes": 508,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00bbaa80",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "00ba6e4e"
    },
    {
      "from": "00debbc4"
    },
    {
      "from": "00df4fba"
    }
  ]
}
```

## globals

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## reconstruction

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## runtime_metadata

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## semantic_hypotheses

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## status

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
