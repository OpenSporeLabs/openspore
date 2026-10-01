# Evidence 0x01021740

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `70e73a8e540fe687ac64131ee210c583c270aa8c9773c8c8ed3c7814d4f8e627`

## abi

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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
    "receiver_not_determinable: ecx_used_as_counter",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "112612877f4af5a5e30d8f05543032ed4e8c6f5d991a17dac0486b00b08e1b29",
  "conventions": {
    "ambiguities": [
      "variadic_suspected"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl"
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
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0087"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0026",
        "obs-0032",
        "obs-0041",
        "obs-0043",
        "obs-0067",
        "obs-0070",
        "obs-0082"
      ],
      "claim": "the register receiver is undetermined: ecx_used_as_counter",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_used_as_counter",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0037"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
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
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {
      "id": "obs-0048"
    },
    {
      "id": "obs-0049"
    },
    {
      "id": "obs-0050"
    },
    {
      "id": "obs-0051"
    },
    {
      "id": "obs-0052"
    },
    {
      "id": "obs-0053"
    },
    {
      "id": "obs-0054"
    },
    {
      "id": "obs-0055"
    },
    {
      "id": "obs-0056"
    },
    {
      "id": "obs-0057"
    },
    {
      "id": "obs-0058"
    },
    {
    
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
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
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
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
    "receiver_not_determinable: ecx_used_as_counter",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "112612877f4af5a5e30d8f05543032ed4e8c6f5d991a17dac0486b00b08e1b29",
  "conventions": {
    "ambiguities": [
      "variadic_suspected"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl"
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
    "indirect_calls": 9,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0087"
      ],
      "claim": "the caller cleans up the stack: a bare RET is compatible with caller cleanup and, for a zero-parameter __stdcall, with zero bytes of callee cleanup",
      "confidence": "INFERRED",
      "id": "C5",
      "value": {
        "bytes": 0,
        "side": "caller"
      }
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0026",
        "obs-0032",
        "obs-0041",
        "obs-0043",
        "obs-0067",
        "obs-0070",
        "obs-0082"
      ],
      "claim": "the register receiver is undetermined: ecx_used_as_counter",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_used_as_counter",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0037"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
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
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {
      "id": "obs-0048"
    },
    {
      "id": "obs-0049"
    },
    {
      "id": "obs-0050"
    },
    {
      "id": "obs-0051"
    },
    {
      "id": "obs-0052"
    },
    {
      "id": "obs-0053"
    },
    {
      "id": "obs-0054"
    },
    {
      "id": "obs-0055"
    },
    {
      "id": "obs-0056"
    },
    {
      "id": "obs-0057"
    },
    {
      "id": "obs-0058"
    },
    {
    
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
  "count": 151,
  "instructions": [
    {
      "address": "01021740",
      "instruction": "MOV EAX,[0x016dda8c]"
    },
    {
      "address": "01021745",
      "instruction": "SUB ESP,0xb4"
    },
    {
      "address": "0102174b",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0102174c",
      "instruction": "MOV EBX,dword ptr [ESP + 0xbc]"
    },
    {
      "address": "01021753",
      "instruction": "CMP EBX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "01021756",
      "instruction": "JNZ 0x0102194a"
    },
    {
      "address": "0102175c",
      "instruction": "CMP dword ptr [EAX + 0x10],0x0"
    },
    {
      "address": "01021760",
      "instruction": "JNZ 0x0102194a"
    },
    {
      "address": "01021766",
      "instruction": "MOVSS XMM0,dword ptr [0x016dda90]"
    },
    {
      "address": "0102176e",
      "instruction": "MOVSS dword ptr [ESP + 0xc],XMM0"
    },
    {
      "address": "01021774",
      "instruction": "MOVSS XMM0,dword ptr [0x016dda94]"
    },
    {
      "address": "0102177c",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0102177d",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "0102177f",
      "instruction": "MOVSS dword ptr [ESP + 0x14],XMM0"
    },
    {
      "address": "01021785",
      "instruction": "MOVSS XMM0,dword ptr [0x016dda98]"
    },
    {
      "address": "0102178d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102178e",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "01021790",
      "instruction": "MOV word ptr [ESP + 0x12],CX"
    },
    {
      "address": "01021795",
      "instruction": "MOVSS dword ptr [ESP + 0x1c],XMM0"
    },
    {
      "address": "0102179b",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "010217a3",
      "instruction": "PUSH 0x16ddb10"
    },
    {
      "address": "010217a8",
      "instruction": "LEA ECX,[ESP + 0x28]"
    },
    {
      "address": "010217ac",
      "instruction": "MOV word ptr [ESP + 0x14],AX"
    },
    {
      "address": "010217b1",
      "instruction": "MOVSS dword ptr [ESP + 0x24],XMM0"
    },
    {
      "address": "010217b7",
      "instruction": "CALL 0x0041cb40"
    },
    {
      "address": "010217bc",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "010217be",
      "instruction": "MOV EAX,dword ptr [EDX + 0x2c]"
    },
    {
      "address": "010217c1",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "010217c3",
      "instruction": "CALL EAX"
    },
    {
      "address": "010217c5",
      "instruction": "MOV ECX,dword ptr [EAX]"
    },
    {
      "address": "010217c7",
      "instruction": "MOV dword ptr [ESP + 0x14],ECX"
    },
    {
      "address": "010217cb",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "010217ce",
      "instruction": "MOV dword ptr [ESP + 0x18],EDX"
    },
    {
      "address": "010217d2",
      "instruction": "MOV EAX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "010217d5",
      "instruction": "MOV EDX,dword ptr [EBX]"
    },
    {
      "address": "010217d7",
      "instruction": "OR word ptr [ESP + 0x10],0x4"
    },
    {
      "address": "010217dd",
      "instruction": "INC word ptr [ESP + 0x12]"
    },
    {
      "address": "010217e2",
      "instruction": "MOV dword ptr [ESP + 0x1c],EAX"
    },
    {
      "address": "010217e6",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "010217e9",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "010217eb",
      "instruction": "CALL EAX"
    },
    {
      "address": "010217ed",
      "instruction": "PUSH EAX"
    },
    {
      "address": "010217ee",
      "instruction": "LEA ECX,[ESP + 0xa0]"
    },
    {
      "address": "010217f5",
      "instruction": "PUSH ECX"
    },
    {
      "address": "010217f6",
      "instruction": "CALL 0x0059c190"
    },
    {
      "address": "010217fb",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "010217fd",
      "instruction": "MOV ECX,0x9"
    },
    {
      "address": "01021802",
      "instruction": "LEA EDI,[ESP + 0x2c]"
    },
    {
      "address": "01021806",
      "instruction": "MOVSD.REP ES:EDI,ESI"
    },
    {
      "address": "01021808",
      "instruction": "OR word ptr [ESP + 0x18],0x2"
    },
    {
      "address": "0102180e",
      "instruction": "INC word ptr [ESP + 0x1a]"
    },
    {
      "address": "01021813",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "01021816",
      "instruction": "CALL 0x0067de00"
    },
    {
      "address": "0102181b",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "0102181d",
      "instruction": "MOV EDX,dword ptr [EDX + 0xdc]"
    },
    {
      "address": "01021823",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "01021827",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01021828",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0102182a",
      "instruction": "CALL EDX"
    },
    {
      "address": "0102182c",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "01021830",
      "instruction": "CALL 0x0040efa0"
    },
    {
      "address": "01021835",
      "instruction": "FLD float ptr [ESP + 0x1c]"
    },
    {
      "address": "01021839",
      "instruction": "FMUL ST0"
    },
    {
      "address": "0102183b",
      "instruction": "MOVSS XMM0,dword ptr [ESP + 0x14]"
    },
    {
      "address": "01021841",
      "instruction": "FLD float ptr [ESP + 0x18]"
    },
    {
      "address": "01021845",
      "instruction": "MOVSS XMM1,dword ptr [ESP + 0x18]"
    },
    {
      "address": "0102184b",
      "instruction": "FMUL ST0"
    },
    {
      "address": "0102184d",
      "instruction": "MOVSS XMM2,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "01021853",
      "instruc
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
  "body_end": "01021951",
  "body_span_bytes": 530,
  "body_start": "01021740",
  "callees": [
    "FUN_00fbad70",
    "FUN_0040efa0",
    "QuaternionToMatrix",
    "App::cLocaleManager::Get",
    "FUN_00698180",
    "Graphics::IShadowWorld::Get",
    "FUN_0041cb40",
    "Simulator::cGameInputManager::Get",
    "FUN_00409930"
  ],
  "callers": [
    "FUN_00fdf5f0",
    "FUN_00c84d60",
    "FUN_01003690",
    "FUN_00bc2c50"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "01021740",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_9c",
      "storage": "Stack[-0x9c]:1",
      "type": "undefined"
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
      "name": "local_ae",
      "storage": "Stack[-0xae]:2",
      "type": "undefined2"
    },
    {
      "name": "local_b0",
      "storage": "Stack[-0xb0]:2",
      "type": "undefined2"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_01021740",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21740",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021740(void)",
  "size_bytes": 530,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021740",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00bc2e8e"
    },
    {
      "from": "00c850e3"
    },
    {
      "from": "01003824"
    },
    {
      "from": "00fdf89a"
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
