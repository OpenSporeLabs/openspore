# Evidence 0x00643a40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8a7ca5b19fd78e8c46c7d7337edb5300ff9e71976d307ab1e039265a91316745`

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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
          4
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
        "sizes": [
          1,
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
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path",
    "unparsed_lines_present: 2 line(s) matched no grammar rule",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "45042679d36c16a2bd7a40e8da3874928fd0066018590c17270096a4c3ceac4d",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028",
        "obs-0032"
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
        "obs-0009",
        "obs-0018",
        "obs-0019",
        "obs-0021"
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
        "obs-0009",
        "obs-0018",
        "obs-0019",
        "obs-0021"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          12,
          16,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0028",
        "obs-0032"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0019"
      ],
      "claim": "a hidden struct-return pointer is a hypothesis only: entry slot 0 is written through a pointer",
      "confidence": "INFERRED",
      "id": "S1",
      "value": {
        "ambiguity": "sret_vs_out_param",
        "present": null,
        "slot": 4
      }
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0032"
      ],
      "claim": "in MSVC x86 a hidden struct-return pointer is always stack slot 0 while this is in ECX, so the two never contend",
      "confidence": "APPROXIMATION",
      "id": "S3",
      "value": {
        "ordering": "not_applicable"
      }
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0032"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0028",
        "obs-0032"
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
      "at": "0x00643a40",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xc]",
      "reg": "ECX"
    },
    {
      "at": "0x00643a40",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xc]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "and_esp": null,
      "at": "0x00643a43",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x8",
      "sub": 8
    },
    {
      "at": "0x00643a43",
      "definite": true,
      "id": "obs-0004",
   
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 * __thiscall FUN_00643a40(int param_1,uint *param_2)\n\n{\n  undefined4 *puVar1;\n  undefined4 *puVar2;\n  undefined4 *puVar3;\n  undefined4 *puVar4;\n  uint local_8 [2];\n  \n  puVar1 = (undefined4 *)(param_1 + 4);\n  puVar4 = puVar1;\n  if (*(undefined4 **)(param_1 + 0xc) != (undefined4 *)0x0) {\n    puVar2 = *(undefined4 **)(param_1 + 0xc);\n    do {\n      if ((uint)puVar2[4] < *param_2) {\n        puVar3 = (undefined4 *)*puVar2;\n      }\n      else {\n        puVar3 = (undefined4 *)puVar2[1];\n        puVar4 = puVar2;\n      }\n      puVar2 = puVar3;\n    } while (puVar3 != (undefined4 *)0x0);\n  }\n  if ((puVar4 != puVar1) && ((uint)puVar4[4] <= *param_2)) {\n    return puVar4 + 5;\n  }\n  local_8[0] = *param_2;\n  param_2 = (uint *)((uint)param_2 & 0xffffff00);\n  local_8[1] = 0;\n  FUN_006432d0(&param_2,puVar4,local_8,param_2);\n  return (undefined4 *)((int)param_2 + 0x14);\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 51,
  "instructions": [
    {
      "address": "00643a40",
      "instruction": "MOV EAX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "00643a43",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00643a46",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00643a47",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00643a48",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "00643a4b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00643a4c",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00643a50",
      "instruction": "MOV EDX,ESI"
    },
    {
      "address": "00643a52",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00643a54",
      "instruction": "JZ 0x00643a6a"
    },
    {
      "address": "00643a56",
      "instruction": "MOV EBP,dword ptr [EDI]"
    },
    {
      "address": "00643a58",
      "instruction": "CMP dword ptr [EAX + 0x10],EBP"
    },
    {
      "address": "00643a5b",
      "instruction": "JC 0x00643a64"
    },
    {
      "address": "00643a5d",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "00643a5f",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00643a62",
      "instruction": "JMP 0x00643a66"
    },
    {
      "address": "00643a64",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00643a66",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00643a68",
      "instruction": "JNZ 0x00643a58"
    },
    {
      "address": "00643a6a",
      "instruction": "CMP EDX,ESI"
    },
    {
      "address": "00643a6c",
      "instruction": "JZ 0x00643a75"
    },
    {
      "address": "00643a6e",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00643a70",
      "instruction": "CMP EAX,dword ptr [EDX + 0x10]"
    },
    {
      "address": "00643a73",
      "instruction": "JNC 0x00643ab1"
    },
    {
      "address": "00643a75",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "00643a77",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "00643a7b",
      "instruction": "MOV byte ptr [ESP + 0x18],0x0"
    },
    {
      "address": "00643a80",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00643a84",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00643a85",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00643a89",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00643a8a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00643a8b",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "00643a8d",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "00643a8f",
      "instruction": "LEA EDX,[ESP + 0x24]"
    },
    {
      "address": "00643a93",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00643a94",
      "instruction": "MOV dword ptr [ESP + 0x20],0x0"
    },
    {
      "address": "00643a9c",
      "instruction": "CALL 0x006432d0"
    },
    {
      "address": "00643aa1",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00643aa5",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "00643aa8",
      "instruction": "POP EDI"
    },
    {
      "address": "00643aa9",
      "instruction": "POP ESI"
    },
    {
      "address": "00643aaa",
      "instruction": "POP EBP"
    },
    {
      "address": "00643aab",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00643aae",
      "instruction": "RET 0x4"
    },
    {
      "address": "00643ab1",
      "instruction": "POP EDI"
    },
    {
      "address": "00643ab2",
      "instruction": "POP ESI"
    },
    {
      "address": "00643ab3",
      "instruction": "LEA EAX,[EDX + 0x14]"
    },
    {
      "address": "00643ab6",
      "instruction": "POP EBP"
    },
    {
      "address": "00643ab7",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "00643aba",
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
  "body_end": "00643abc",
  "body_span_bytes": 125,
  "body_start": "00643a40",
  "callees": [
    "FUN_006432d0"
  ],
  "callers": [
    "FUN_00b32190",
    "FUN_00b32220",
    "FUN_00be9980",
    "FUN_00be11f0",
    "FUN_00beaa30",
    "FUN_00baf790",
    "FUN_00fede80",
    "FUN_00644530",
    "FUN_00be32f0",
    "FUN_00b32280",
    "FUN_00fe5a20",
    "FUN_00b322c0",
    "FUN_0066b0c0",
    "FUN_00be32b0",
    "FUN_00be3f00",
    "Editors::cEditor::Initialize",
    "FUN_00643db0",
    "FUN_00a18d90",
    "FUN_00beb1c0",
    "FUN_00b32250",
    "FUN_00be9cb0",
    "FUN_00ce6af0",
    "FUN_00fede40",
    "FUN_00fede60",
    "FUN_00644510",
    "FUN_00be1150",
    "FUN_00beb090",
    "FUN_00be9850",
    "FUN_00be2110"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00643a40",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "uint *"
    },
    {
      "name": "puVar1",
      "storage": "unique:00006600:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar2",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar3",
      "storage": "register:00000000:4",
      "type": "undefined4 *"
    },
    {
      "name": "puVar4",
      "storage": "register:00000008:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "uint[2]"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00643a40",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x243a40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00643a40(void)",
  "size_bytes": 125,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00643a40",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00b3222c"
    },
    {
      "from": "00b3225c"
    },
    {
      "from": "00584383"
    },
    {
      "from": "0058439d"
    },
    {
      "from": "005843b7"
    },
    {
      "from": "005843d1"
    },
    {
      "from": "005843eb"
    },
    {
      "from": "00584405"
    },
    {
      "from": "00643df2"
    },
    {
      "from": "0066b10f"
    },
    {
      "from": "00a18db6"
    },
    {
      "from": "00a18de0"
    },
    {
      "from": "00a18e0a"
    },
    {
      "from": "00a18e34"
    },
    {
      "from": "00a18e5e"
    },
    {
      "from": "00a18e88"
    },
    {
      "from": "00a18eb2"
    },
    {
      "from": "00a18edc"
    },
    {
      "from": "00a18f06"
    },
    {
      "from": "00a18f30"
    },
    {
      "from": "00a18f5a"
    },
    {
      "from": "00a18f84"
    },
    {
      "from": "00a18fae"
    },
    {
      "from": "00a18fd8"
    },
    {
      "from": "00a19002"
    },
    {
      "from": "00a1902c"
    },
    {
      "from": "00a19056"
    },
    {
      "from": "00a19080"
    },
    {
      "from": "00a190aa"
    },
    {
      "from": "00a190d4"
    },
    {
      "from": "00a190fe"
    },
    {
      "from": "00a19128"
    },
    {
      "from": "00a19152"
    },
    {
      "from": "00a1917c"
    },
    {
      "from": "00a191a6"
    },
    {
      "from": "00a191d0"
    },
    {
      "from": "00a191fa"
    },
    {
      "from": "00a19224"
    },
    {
      "from": "00a1924e"
    },
    {
      "from": "00a19278"
    },
    {
      "from": "00a192a2"
    },
    {
      "from": "00a192cc"
    },
    {
      "from": "00a192f6"
    },
    {
      "from": "00a19320"
    },
    {
      "from": "00a1934a"
    },
    {
      "from": "00a19374"
    },
    {
      "from": "00a1939e"
    },
    {
      "from": "00a193c8"
    },
    {
      "from": "00a193f2"
    },
    {
      "from": "00a1941c"
    },
    {
      "from": "00a19446"
    },
    {
      "from": "00a19470"
    },
    {
      "from": "00a1949a"
    },
    {
      "from": "00a194c4"
    },
    {
      "from": "00a194ee"
    },
    {
      "from": "00a19518"
    },
    {
      "from": "00a19542"
    },
    {
      "from": "00a1956c"
    },
    {
      "from": "00a19596"
    },
    {
      "from": "00a195c0"
    },
    {
      "from": "00a195ea"
    },
    {
      "from": "00b3228c"
    },
    {
      "from": "00be21b7"
    },
    {
      "from": "00be21d1"
    },
    {
      "from": "00be21df"
    },
    {
      "from": "00be3f62"
    },
    {
      "from": "00be12d3"
    },
    {
      "from": "00be12e9"
    },
    {
      "from": "00be1316"
    },
    {
      "from": "00beb22e"
    },
    {
      "from": "00beb0e5"
    },
    {
      "from": "00beb0f7"
    },
    {
      "from": "00beb105"
    },
    {
      "from": "00beb113"
    },
    {
      "from": "00beb151"
    },
    {
      "from": "00beb16f"
    },
    {
      "from": "00beb17d"
    },
    {
      "from": "00beb19c"
    },
    {
      "from": "00beab91"
    },
    {
      "from": "00be9d2e"
    },
    {
      "from": "00be11b1"
    },
    {
      "from": "00be994b"
    },
    {
      "from": "00b322e6"
    },
    {
      "from": "00b323b7"
    },
    {
      "from": "00b32206"
    },
    {
      "from": "00644518"
    },
    {
      "from": "00644538"
    },
    {
[TRUNCATED]
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
