# Evidence 0x00fa5040

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9c7ae2db35920bfe2429685c030caf956eb2c1b1ffb7b93b39dbf11aa3a368d8`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver": "ECX carries the receiver, at INFERRED confidence, and is aliased into EBP at 0x00fa5045 for the rest of the body. The record's bounds_only flag is its own statement that the four enumerated displacements are an OPEN lower bound, and this package treats it as one: the offsets it reaches through the receiver alias are exactly the four the record enumerates (0x770, 0x774, 0x784, 0x788), and it asserts no field name, member, layout or size for any of them. Receiver is declared and left undefined.",
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_note": ". The WIDTH is the machine's: the last write before each of the two reachable terminators is a ONE-BYTE write to AL (XOR AL,AL at 0x00fa50d6, MOV AL,0x1 at 0x00fa5234 and 0x00fa5428) with no CALL between the write and the RET on either path. The exact C spelling is a source-side choice among the one-byte types and is not verified by the machine; bool is the width-computable choice and asserts no value constraint the machine does not show.",
  "return_observation": "Two reachable terminators, one byte each, and no bulk write. The record's return.aggregate_evidence.bulk_write is false and sret.present is false, so no hidden-pointer return is in play and the width read off the register is the width of the value.",
  "return_register": "EAX, low byte only. DIVERGENCE FROM THE RECORD, RECORDED NOT RESOLVED: the machine's own abi_derived.return reads {register XMM0, register_class float_or_x87, confidence APPROXIMATION, void_possible false, type null} and inference RT1 states \"the return value is carried in XMM0: an x87 or SSE instruction appears in the body\" at APPROXIMATION confidence. RT1 is a presence heuristic -- XMM0 in this body is scratch for the four COMISS comparisons, written by MOVSS at 0x00fa516a, 0x00fa517d, 0x00fa5189, 0x00fa5195, 0x00fa52ce, 0x00fa52e1, 0x00fa52ed and 0x00fa52f9, and never written after the l...",
  "return_semantics": "one_byte_in_EAX, by this package's reading of the complete listing; the derived record's own classification is float_or_x87_in_XMM0 at APPROXIMATION confidence and is contradicted (see return_register).",
  "return_type": "bool",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
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
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 15
    },
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
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 15
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
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
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 15
    },
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -48, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "bcfc8aac8d17dc1232c0306d733f796ab5cdb13c5a182c1050ae6fa2b7930593",
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
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0030",
        "obs-0066",
        "obs-0108"
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
        "obs-0018",
        "obs-0031",
        "obs-0032",
        "obs-0033",
        "obs-0035",
        "obs-0038",
        "obs-0040",
        "obs-0041",
        "obs-0042",
        "obs-0045",
        "obs-0046",
        "obs-0047",
        "obs-0048",
        "obs-0049",
        "obs-0051",
        "obs-0052",
        "obs-0053",
        "obs-0054",
        "obs-0055",
        "obs-0056",
        "obs-0057",
        "obs-0067",
        "obs-0068",
        "obs-0070",
        "obs-0071",
        "obs-0072",
        "obs-0073",
        "obs-0074",
        "obs-0076",
        "obs-0077",
        "obs-0078",
        "obs-0079",
        "obs-0080",
        "obs-0081",
        "obs-0082",
        "obs-0089",
        "obs-0090",
        "obs-0091",
        "obs-0093",
        "obs-0094",
        "obs-0095",
        "obs-0096",
        "obs-0097",
        "obs-0098",
        "obs-0099",
        "obs-0103"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 3,
        "observed_slots": 17,
        "total_bytes": 80
      }
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0031",
        "obs-0032",
        "obs-0033",
        "obs-0035",
        "obs-0038",
        "obs-0040",
        "obs-0041",
        "obs-0042",
        "obs-0045",
        "obs-0046",
        "obs-0047",
        "obs-0048",
        "obs-0049",
        "obs-0051",
        "obs-0052",
        "obs-0053",
        "obs-0054",
        "obs-0055",
        "obs-0056",
        "obs-0057",
        "obs-0067",
        "obs-0068",
        "obs-0070",
        "obs-0071",
        "obs-0072",
        "obs-0073",
        "obs-0074",
        "obs-0076",
        "obs-0077",
        "obs-0078",
        "obs-0079",
        "obs-0080",
        "obs-0081",
        "obs-0082",
        "obs-0089",
        "obs-0090",
        "obs-0091",
        "obs-0093",
        "obs-0094",
        "obs-0095",
        "obs-0096",
        "obs-0097",
        "obs-0098",
        "obs-0099",
        "obs-0103"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0021",
        "obs-0022",
  
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
"\nundefined4 __thiscall FUN_00fa5040(int param_1,int param_2,char param_3)\n\n{\n  float *pfVar1;\n  undefined4 *puVar2;\n  uint *puVar3;\n  uint uVar4;\n  char cVar5;\n  int *piVar6;\n  int iVar7;\n  int iVar8;\n  int *piVar9;\n  uint uVar10;\n  uint uVar11;\n  int iVar12;\n  uint uVar13;\n  int local_18;\n  uint local_14;\n  float local_10;\n  float local_c;\n  float local_8;\n  float local_4;\n  \n  iVar8 = *(int *)(param_1 + 0x788) - *(int *)(param_1 + 0x784);\n  iVar12 = iVar8 >> 0x1f;\n  iVar8 = iVar8 / 0xac + iVar12;\n  uVar10 = 0;\n  if (iVar8 != iVar12) {\n    piVar9 = (int *)(*(int *)(param_1 + 0x784) + 0xa8);\n    do {\n      if (*piVar9 == param_2) {\n        if (param_3 != '\\0') {\n          param_2 = 0;\n          piVar9 = (int *)(param_1 + 0x218);\n          do {\n            uVar11 = piVar9[1] - *piVar9 >> 2;\njoined_r0x00fa5106:\n            uVar11 = uVar11 - 1;\n            if (-1 < (int)uVar11) {\n              piVar6 = (int *)(*piVar9 + uVar11 * 4);\n              if ((*piVar6 != 0) && ((*(uint *)(*piVar6 + 0xb8) >> 3 & 1) != 0)) {\n                iVar8 = 0;\n                iVar12 = 0;\n                do {\n                  cVar5 = FUN_00fad140(iVar8,&local_10);\n                  if ((((cVar5 != '\\0') &&\n                       (iVar7 = uVar10 * 0xac + iVar12,\n                       pfVar1 = (float *)(iVar7 + 0x38 + *(int *)(param_1 + 0x784)),\n                       iVar7 = iVar7 + 0x38 + *(int *)(param_1 + 0x784),\n                       *pfVar1 <= local_8 && local_8 != *pfVar1)) &&\n                      (local_10 < *(float *)(iVar7 + 8))) &&\n                     ((*(float *)(iVar7 + 4) <= local_4 && local_4 != *(float *)(iVar7 + 4) &&\n                      (local_c < *(float *)(iVar7 + 0xc))))) {\n                    FUN_00fa29b0(param_2 << 0x18 | uVar11);\n                    break;\n                  }\n                  iVar12 = iVar12 + 0x10;\n                  iVar8 = iVar8 + 1;\n                } while (iVar12 < 0x60);\n              }\n              goto joined_r0x00fa5106;\n            }\n            param_2 = param_2 + 1;\n            piVar9 = piVar9 + 5;\n          } while (param_2 < 4);\n        }\n        uVar11 = *(uint *)(param_1 + 0x788);\n        uVar10 = uVar10 * 0xac + *(int *)(param_1 + 0x784) + 0xac;\n        if (uVar10 < uVar11) {\n          do {\n            FUN_00f9f620(uVar10);\n            uVar10 = uVar10 + 0xac;\n          } while (uVar10 != uVar11);\n        }\n        *(int *)(param_1 + 0x788) = *(int *)(param_1 + 0x788) + -0xac;\n        return 1;\n      }\n      uVar10 = uVar10 + 1;\n      piVar9 = piVar9 + 0x2b;\n    } while (uVar10 < (uint)(iVar8 - iVar12));\n  }\n  uVar10 = (*(int *)(param_1 + 0x774) - *(int *)(param_1 + 0x770)) / 0xac;\n  uVar11 = 0;\n  if (uVar10 != 0) {\n    piVar9 = (int *)(*(int *)(param_1 + 0x770) + 0xa8);\n    do {\n      if (*piVar9 == param_2) {\n        if (param_3 != '\\0') {\n          piVar9 = (int *)(param_1 + 0x218);\n          local_18 = 0;\n          do {\n            uVar10 = piVar9[1] - *piVar9 >> 2;\njoined_r0x00fa526b:\n            uVar10 = uVar10 - 1;\n            if (-1 < (int)uVar10) {\n              if ((*(int *)(*piVar9 + uVar10 * 4) != 0) &&\n                 ((*(uint *)(*(int *)(*piVar9 + uVar10 * 4) + 0xb8) >> 3 & 1) != 0)) {\n                iVar12 = 0;\n                iVar8 = 0;\n                do {\n                  cVar5 = FUN_00fad140(iVar8,&local_10);\n                  if ((((cVar5 != '\\0') &&\n                       (iVar7 = uVar11 * 0xac + iVar12,\n                       pfVar1 = (float *)(iVar7 + 0x38 + *(int *)(param_1 + 0x770)),\n                       iVar7 = iVar7 + 0x38 + *(int *)(param_1 + 0x770),\n                       *pfVar1 <= local_8 && local_8 != *pfVar1)) &&\n                      (local_10 < *(float *)(iVar7 + 8))) &&\n                     ((*(float *)(iVar7 + 4) <= local_4 && local_4 != *(float *)(iVar7 + 4) &&\n                      (local_c < *(float *)(iVar7 + 0xc))))) {\n                    uVar13 = local_18 << 0x18 | uVar10;\n                    piVar6 = (int *)(param_1 + 0x218 + (uVar13 >> 0x18) * 0x14);\n                    uVar4 = uVar10 & 0xffffff;\n                    if ((uVar4 < (uint)(piVar6[1] - *piVar6 >> 2)) &&\n                       (puVar2 = *(undefined4 **)(*piVar6 + uVar4 * 4), puVar2 != (undefined4 *)0x0)\n                       ) {\n                      FUN_00fadac0();\n                      iVar12 = puVar2[1];\n                      puVar2[1] = iVar12 + -1;\n                      if (iVar12 + -1 == 0) {\n                        puVar2[1] = 1;\n                        (**(code **)*puVar2)(1);\n                      }\n                      iVar8 = (int)uVar13 >> 0x18;\n                      iVar12 = param_1 + iVar8 * 0x14;\n                      *(undefined4 *)(*(int *)(param_1 + 0x218 + iVar8 * 0x14) + uVar4 * 4) = 0;\n                      puVar3 = *(uint **)(iVar12 + 0x26c);\n                      local_14 = uVar4;\n                      if (puVar3 < *(uint **)(iVar12 + 0x270)) {\n                        *(uint **)(iVar12 + 0x26c) = puVar3 + 1;\n                        if (puVar3 != (uint *)0x0) {\n                          *puVar3 = uVar4;\n                        }\n                      }\n                      else {\n                        FUN_004558a0(puVar3,&local_14);\n                      }\n                    }\n                    break;\n                  }\n                  iVar12 = iVar12 + 0x10;\n                  iVar8 = iVar8 + 1;\n                } while (iVar12 < 0x60);\n              }\n              goto joined_r0x00fa526b;\n            }\n            local_18 = local_18 + 1;\n            piVar9 = piVar9 + 5;\n          } while (local_18 < 4);\n        }\n        uVar4 = *(uint *)(param_1 + 0x774);\n        uVar10 = uVar11 * 0xac + *(int *)(param_1 + 0x770) + 0xac;\n        if (uVar10 < uVar4) {\n          do {\n            FUN_00f9f620(uVar10);\n            uVar10 = uVar10 + 0xac;\n          } 
[TRUNCATED]
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 297,
  "instructions": [
    {
      "address": "00fa5040",
      "instruction": "SUB ESP,0x1c"
    },
    {
      "address": "00fa5043",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00fa5044",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00fa5045",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00fa5047",
      "instruction": "MOV ECX,dword ptr [EBP + 0x788]"
    },
    {
      "address": "00fa504d",
      "instruction": "SUB ECX,dword ptr [EBP + 0x784]"
    },
    {
      "address": "00fa5053",
      "instruction": "MOV EAX,0x2fa0be83"
    },
    {
      "address": "00fa5058",
      "instruction": "IMUL ECX"
    },
    {
      "address": "00fa505a",
      "instruction": "SAR EDX,0x5"
    },
    {
      "address": "00fa505d",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00fa505f",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00fa5060",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00fa5063",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00fa5065",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00fa5067",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00fa5069",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00fa506a",
      "instruction": "MOV EDI,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00fa506e",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "00fa5072",
      "instruction": "JZ 0x00fa508f"
    },
    {
      "address": "00fa5074",
      "instruction": "MOV ECX,dword ptr [EBP + 0x784]"
    },
    {
      "address": "00fa507a",
      "instruction": "ADD ECX,0xa8"
    },
    {
      "address": "00fa5080",
      "instruction": "CMP dword ptr [ECX],EDI"
    },
    {
      "address": "00fa5082",
      "instruction": "JZ 0x00fa50df"
    },
    {
      "address": "00fa5084",
      "instruction": "INC ESI"
    },
    {
      "address": "00fa5085",
      "instruction": "ADD ECX,0xac"
    },
    {
      "address": "00fa508b",
      "instruction": "CMP ESI,EAX"
    },
    {
      "address": "00fa508d",
      "instruction": "JC 0x00fa5080"
    },
    {
      "address": "00fa508f",
      "instruction": "MOV ECX,dword ptr [EBP + 0x774]"
    },
    {
      "address": "00fa5095",
      "instruction": "SUB ECX,dword ptr [EBP + 0x770]"
    },
    {
      "address": "00fa509b",
      "instruction": "MOV EAX,0x2fa0be83"
    },
    {
      "address": "00fa50a0",
      "instruction": "IMUL ECX"
    },
    {
      "address": "00fa50a2",
      "instruction": "SAR EDX,0x5"
    },
    {
      "address": "00fa50a5",
      "instruction": "MOV EAX,EDX"
    },
    {
      "address": "00fa50a7",
      "instruction": "SHR EAX,0x1f"
    },
    {
      "address": "00fa50aa",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00fa50ac",
      "instruction": "ADD EAX,EDX"
    },
    {
      "address": "00fa50ae",
      "instruction": "JZ 0x00fa50d3"
    },
    {
      "address": "00fa50b0",
      "instruction": "MOV ECX,dword ptr [EBP + 0x770]"
    },
    {
      "address": "00fa50b6",
      "instruction": "ADD ECX,0xa8"
    },
    {
      "address": "00fa50bc",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00fa50c0",
      "instruction": "CMP dword ptr [ECX],EDI"
    },
    {
      "address": "00fa50c2",
      "instruction": "JZ 0x00fa523d"
    },
    {
      "address": "00fa50c8",
      "instruction": "INC ESI"
    },
    {
      "address": "00fa50c9",
      "instruction": "ADD ECX,0xac"
    },
    {
      "address": "00fa50cf",
      "instruction": "CMP ESI,EAX"
    },
    {
      "address": "00fa50d1",
      "instruction": "JC 0x00fa50c0"
    },
    {
      "address": "00fa50d3",
      "instruction": "POP EDI"
    },
    {
      "address": "00fa50d4",
      "instruction": "POP ESI"
    },
    {
      "address": "00fa50d5",
      "instruction": "POP EBP"
    },
    {
      "address": "00fa50d6",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00fa50d8",
      "instruction": "POP EBX"
    },
    {
      "address": "00fa50d9",
      "instruction": "ADD ESP,0x1c"
    },
    {
      "address": "00fa50dc",
      "instruction": "RET 0x8"
    },
    {
      "address": "00fa50df",
      "instruction": "MOV dword ptr [ESP + 0x14],ESI"
    },
    {
      "address": "00fa50e3",
      "instruction": "CMP byte ptr [ESP + 0x34],BL"
    },
    {
      "address": "00fa50e7",
      "instruction": "JZ 0x00fa51eb"
    },
    {
      "address": "00fa50ed",
      "instruction": "MOV dword ptr [ESP + 0x30],EBX"
    },
    {
      "address": "00fa50f1",
      "instruction": "LEA EBX,[EBP + 0x218]"
    },
    {
      "address": "00fa50f7",
      "instruction": "MOV ECX,dword ptr [EBX + 0x4]"
    },
    {
      "address": "00fa50fa",
      "instruction": "SUB ECX,dword ptr [EBX]"
    },
    {
      "address": "00fa50fc",
      "instruction": "SAR ECX,0x2"
    },
    {
      "address": "00fa50ff",
      "instruction": "SUB ECX,0x1"
    },
    {
      "address": "00fa5102",
      "instruction": "MOV dword ptr [ESP + 0x34],ECX"
    },
    {
      "address": "00fa5106",
      "instruction": "JS 0x00fa51d6"
    },
    {
      "address": "00fa510c",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00fa5110",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00fa5112",
      "instruction": "LEA EBP,[ECX*0x4 + 0x0]"
    },
    {
      "address": "00fa5119",
      "instruction": "ADD EAX,EBP"
    },
    {
      "address": "00fa511b",
      "instruction": "CMP dword ptr [EAX],0x0"
    },
    {
      "address": "00fa511e",
      "instruction": "JZ 0x00fa51c5"
    },
    {
      "address": "00fa5124",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00fa5126",
      "instruction": "MOV EAX,dword ptr [EDX + 0xb8]"
    },
    {
      "address": "00fa512c",
      "instruction": "SH
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
  "original_bytes": 15872,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": \"ECX carries the receiver, at INFERRED confidence, and is aliased into EBP at 0x00fa5045 for the rest of the body. The record's bounds_only flag is its own statement that the four enumerated displacements are an OPEN lower bound, and this package treats it as one: the offsets it reaches through the receiver alias are exactly the four the record enumerates (0x770, 0x774, 0x784, 0x788), and it asserts no field name, member, layout or size for any of them. Receiver is declared and left undefined.\",\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_note\": \". The WIDTH is the machine's: the last write before each of the two reachable terminators is a ONE-BYTE write to AL (XOR AL,AL at 0x00fa50d6, MOV AL,0x1 at 0x00fa5234 and 0x00fa5428) with no CALL between the write and the RET on either path. The exact C spelling is a source-side choice among the one-byte types and is not verified by the machine; bool is the width-computable choice and asserts no value constraint the machine does not show.\",\n    \"return_observation\": \"Two reachable terminators, one byte each, and no bulk write. The record's return.aggregate_evidence.bulk_write is false and sret.present is false, so no hidden-pointer return is in play and the width read off the register is the width of the value.\",\n    \"return_register\": \"EAX, low byte only. DIVERGENCE FROM THE RECORD, RECORDED NOT RESOLVED: the machine's own abi_derived.return reads {register XMM0, register_class float_or_x87, confidence APPROXIMATION, void_possible false, type null} and inference RT1 states \\\"the return value is carried in XMM0: an x87 or SSE instruction appears in the body\\\" at APPROXIMATION confidence. RT1 is a presence heuristic -- XMM0 in this body is scratch for the four COMISS comparisons, written by MOVSS at 0x00fa516a, 0x00fa517d, 0x00fa5189, 0x00fa5195, 0x00fa52ce, 0x00fa52e1, 0x00fa52ed and 0x00fa52f9, and never written after the l...\",\n    \"return_semantics\": \"one_byte_in_EAX, by this package's reading of the complete listing; the derived record's own classification is float_or_x87_in_XMM0 at APPROXIMATION confidence and is contradicted (see return_register).\",\n    \"return_type\": \"bool\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w2-00f999e0\",\n      \"score\": 10,\n      \"symbol\": \"re_00f999e0\",\n      \"va\": \"0x00f999e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-fa0d50-atomic-inc\",\n      \"score\": 10,\n      \"symbol\": \"FUN_00fa0d50\",\n      \"va\": \"0x00fa0d50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa5580\",\n      \"score\": 10,\n      \"symbol\": \"re_00fa5580\",\n      \"va\": \"0x00fa5580\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa6ec0\",\n      \"score\": 10,\n      \"symbol\": \"re_00fa6ec0\",\n      \"va\": \"0x00fa6ec0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-00fa73c0\",\n      \"score\": 10,\n      \"symbol\": \"sw1_snap_and_dispatch_00fa73c0\",\n      \"va\": \"0x00fa73c0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01490be8\"\n      ],\n      \"package\": \"pkg-swarm-w1-0104c110\",\n      \"score\": 10,\n      \"symbol\": \"re_0104c110\",\n      \"va\": \"0x0104c110\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-005c0dd0\",\n      \"score\": 6,\n      \"symbol\": \"re_005c0dd0\",\n      \"va\": \"0x005c0dd0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-swarm-w1-006413d0\",\n      \"score\": 6,\n      \"symbol\": \"re_006413d0\",\n      \"va\": \"0x006413d0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00fa53ad\",\n        \"direction\": \"out\",\n        \"other\": \"0x004558a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fa5214\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9f620\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fa5408\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f9f620\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fa51b8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fa29b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00fa514d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00fad140\",\n        \"reference_typ
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
  "body_end": "00fa5430",
  "body_span_bytes": 1009,
  "body_start": "00fa5040",
  "callees": [
    "FUN_00fadac0",
    "FUN_00fad140",
    "FUN_00fa29b0",
    "FUN_004558a0",
    "FUN_00f9f620"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00fa5040",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "uint"
    },
    {
      "name": "local_18",
      "storage": "Stack[-0x18]:4",
      "type": "int"
    },
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "float"
    },
    {
      "name": "puVar2",
      "storage": "unique:00017200:4",
      "type": "undefined4 *"
    },
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "float"
    },
    {
      "name": "puVar3",
      "storage": "unique:00017200:4",
      "type": "uint *"
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "float"
    },
    {
      "name": "uVar4",
      "storage": "unique:00017200:4",
      "type": "uint"
    },
    {
      "name": "cVar5",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "float"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:1",
      "type": "char"
    },
    {
      "name": "pfVar1",
      "storage": "unique:00007400:4",
      "type": "float *"
    },
    {
      "name": "uVar10",
      "storage": "register:00000018:4",
      "type": "uint"
    },
    {
      "name": "uVar11",
      "storage": "register:00000018:4",
      "type": "uint"
    },
    {
      "name": "iVar12",
      "storage": "register:00000018:4",
      "type": "int"
    },
    {
      "name": "uVar13",
      "storage": "register:00000018:4",
      "type": "uint"
    },
    {
      "name": "piVar6",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "iVar7",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar8",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "piVar9",
      "storage": "register:00000000:4",
      "type": "int *"
    }
  ],
  "locals_count": 22,
  "mode": "live",
  "name": "FUN_00fa5040",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xba5040",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00fa5040(void)",
  "size_bytes": 1009,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00fa5040",
  "vtables": {
    "referenced_by_vtables": [
      "0x01490be8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01490c40"
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
    "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.cpp",
    "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.hpp",
    "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-dual-00fa5040/00fa5040.json"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bool",
  "bool. The WIDTH is the machine's: the last write before each of the two reachable terminators is a ONE-BYTE write to AL (XOR AL,AL at 0x00fa50d6, MOV AL,0x1 at 0x00fa5234 and 0x00fa5428) with no CALL between the write and the RET on either path. The exact C spelling is a source-side choice among the one-byte types and is not verified by the machine; bool is the width-computable choice and asserts no value constraint the machine does not show.",
  "openspore::reconstruction::pkg_sporepedia_dual_00fa5040::Real",
  "openspore::reconstruction::pkg_sporepedia_dual_00fa5040::Receiver",
  "openspore::reconstruction::pkg_sporepedia_dual_00fa5040::Word"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01490be8"
]
```

## Conflicts

```json
[]
```
