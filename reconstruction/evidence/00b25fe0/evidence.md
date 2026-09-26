# Evidence 0x00b25fe0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7ed0bd48b88f2da2e3c693a0a8f44ddec552f0f417f9d4cf8ffa946d5c38e786`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "unparsed_lines_present: 4 line(s) matched no grammar rule",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "9cd19b16808ec86ca3e5c28155a57d7d66c138c33c07fe7c5ad070e3131d9914",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0079"
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
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0016",
        "obs-0035",
        "obs-0036"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          88
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
        "obs-0079"
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
        "obs-0079"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0079"
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
      "at": "0x00b25fe0",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 2,
      "raw": "SUB ESP,0x1c",
      "sub": 28
    },
    {
      "at": "0x00b25fe0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x1c",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00b25fe3",
      "count": 9,
      "first_use": 1,
      "first_write_index": 79,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00b25fe4",
      "count": 1,
      "first_use": 2,
      "first_write_index": 88,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "at": "0x00b25fe5",
      "count": 30,
      "first_use": 3,
      "first_write_index": 5,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00b25fe6",
      "count": 17,
      "first_use": 4,
      "first_write_index": 67,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00b25fe7",
      "count": 13,
      "first_use": 5,
      "first_write_index": 8,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00b25fe7",
      "definite": true,
      "id": "obs-0008",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25fe9",
      "id": "obs-0009",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22960",
      "target": "0x00b22960"
    },
    {
      "at": "0x00b25ff3",
      "definite": true,
      "id": "obs-0010",
      "index": 8,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00b25ff5",
      "id": "obs-0011",
      "index": 9,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b22650"
    },
    {
      "at": "0x00b26001",
      "id": "obs-0012",
      "index": 12,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00b22650",
      "target": "0x00b22650"
    },
    {
      "at": "0x00b2600d",
      "id": "obs-0013",
      "index": 15,
      "kind": "CALL_D
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
"\nvoid __fastcall FUN_00b25fe0(int param_1)\n\n{\n  undefined4 uVar1;\n  int iVar2;\n  int iVar3;\n  int *piVar4;\n  int *piVar5;\n  int *piStack_1c;\n  int *piStack_18;\n  int *piStack_14;\n  \n  FUN_00b22960();\n  FUN_00b22650(0x18eb45e);\n  FUN_00b22650(0x2c9cc91);\n  FUN_00b22650(0x2e96892);\n  FUN_00b22650(&DAT_018c84a9);\n  FUN_00b22650(0x1be418e);\n  piVar4 = *(int **)(param_1 + 0x58);\n  if (piVar4 != (int *)0x0) {\n    *(undefined4 *)(param_1 + 0x58) = 0;\n    (**(code **)(*piVar4 + 4))();\n  }\n  FUN_00b22650(0x2a8fb3f);\n  FUN_00b22650(0x2a034cd);\n  FUN_00b22650(&DAT_018c6de8);\n  FUN_00b22650(&DAT_018c88e4);\n  FUN_00b22650(0x3a2511e);\n  FUN_00b22650(0x403df5c);\n  FUN_00b22650(0x61494be);\n  FUN_00b22650(0x629bafe);\n  FUN_00b3d2b0();\n  uVar1 = FUN_00ac79d0();\n  FUN_00b3d2b0(uVar1);\n  FUN_00ac7a40(uVar1);\n  iVar2 = FUN_00b21340(&LAB_00cd7d10,&LAB_00d3d420,&LAB_00ad48b0,&LAB_00b1e500,0x18ebadc);\n  FUN_00b93c60(*(int *)(iVar2 + 8) - *(int *)(iVar2 + 4) >> 2,iVar2 + 0x10);\n  piVar4 = piStack_14;\n  FUN_00829110(&piStack_1c,*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8),piStack_14,\n               piStack_18);\n  piVar5 = piStack_1c;\n  for (; piVar4 != piVar5; piVar4 = piVar4 + 1) {\n    iVar2 = *(int *)(*piVar4 + 0x714);\n    if (((iVar2 != 0) && (iVar2 != 8)) && (iVar2 != 3)) {\n      FUN_0102c340(*piVar4,0);\n    }\n  }\n  FUN_00b22650(0x2dd8c42);\n  FUN_00b22650(0x4e3fab5);\n  FUN_00b22650(&DAT_018c6d19);\n  FUN_00b22650(0x24270c9);\n  FUN_00b22650(&DAT_018c43e8);\n  FUN_00b22650(0x18eb4b7);\n  FUN_00b25ee0();\n  iVar2 = FUN_00b21340(&LAB_00cd7d10,&LAB_00ae7060,&LAB_00ae7080,&LAB_00b1e520,&DAT_0142db2a);\n  iVar3 = *(int *)(iVar2 + 8) - *(int *)(iVar2 + 4) >> 2;\n  if (iVar3 == 0) {\n    piVar4 = (int *)0x0;\n  }\n  else {\n    piVar4 = (int *)FUN_00f473a0(iVar3 * 4,\"Simulator\",0,0,\n                                 \"c:\\\\BuildAgent\\\\max-spore001-spore\\\\CMBuild\\\\SporeEP1_RL\\\\Core\\\\UTFKernel\\\\EASTL\\\\include\\\\EASTL/allocator.h\"\n                                 ,0xd1);\n  }\n  FUN_00ae6780(&piStack_18,*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 8),piVar4,piStack_18);\n  for (piVar5 = piVar4; piVar5 != piStack_18; piVar5 = piVar5 + 1) {\n    if ((char)((int *)*piVar5)[4] == '\\0') {\n      uVar1 = (**(code **)(*(int *)*piVar5 + 4))(0x17f243b);\n      FUN_00b225d0(uVar1);\n    }\n  }\n  FUN_00b22650(0x18eb641);\n  FUN_00b22650(0x36be27e);\n  for (piVar5 = piVar4; piVar5 < piStack_18; piVar5 = piVar5 + 1) {\n    if ((int *)*piVar5 != (int *)0x0) {\n      (**(code **)(*(int *)*piVar5 + 8))();\n    }\n  }\n  piVar5 = piStack_14;\n  if ((piVar4 != (int *)0x0) && (piVar4[-1] != 0)) {\n    FUN_00f47380(piVar4);\n    piVar5 = piStack_14;\n  }\n  for (; piVar5 < piStack_1c; piVar5 = piVar5 + 1) {\n    if ((int *)*piVar5 != (int *)0x0) {\n      (**(code **)(*(int *)*piVar5 + 4))();\n    }\n  }\n  if ((piStack_14 != (int *)0x0) && (piStack_14[-1] != 0)) {\n    FUN_00f47380(piStack_14);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 19002,
  "preview": "{\n  \"count\": 236,\n  \"instructions\": [\n    {\n      \"address\": \"00b25fe0\",\n      \"instruction\": \"SUB ESP,0x1c\"\n    },\n    {\n      \"address\": \"00b25fe3\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00b25fe4\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00b25fe5\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00b25fe6\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00b25fe7\",\n      \"instruction\": \"MOV ESI,ECX\"\n    },\n    {\n      \"address\": \"00b25fe9\",\n      \"instruction\": \"CALL 0x00b22960\"\n    },\n    {\n      \"address\": \"00b25fee\",\n      \"instruction\": \"PUSH 0x18eb45e\"\n    },\n    {\n      \"address\": \"00b25ff3\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b25ff5\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b25ffa\",\n      \"instruction\": \"PUSH 0x2c9cc91\"\n    },\n    {\n      \"address\": \"00b25fff\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b26001\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b26006\",\n      \"instruction\": \"PUSH 0x2e96892\"\n    },\n    {\n      \"address\": \"00b2600b\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b2600d\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b26012\",\n      \"instruction\": \"PUSH 0x18c84a9\"\n    },\n    {\n      \"address\": \"00b26017\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b26019\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b2601e\",\n      \"instruction\": \"PUSH 0x1be418e\"\n    },\n    {\n      \"address\": \"00b26023\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b26025\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b2602a\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0x58]\"\n    },\n    {\n      \"address\": \"00b2602d\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"00b2602f\",\n      \"instruction\": \"JZ 0x00b2603f\"\n    },\n    {\n      \"address\": \"00b26031\",\n      \"instruction\": \"MOV dword ptr [ESI + 0x58],0x0\"\n    },\n    {\n      \"address\": \"00b26038\",\n      \"instruction\": \"MOV EAX,dword ptr [ECX]\"\n    },\n    {\n      \"address\": \"00b2603a\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"00b2603d\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00b2603f\",\n      \"instruction\": \"PUSH 0x2a8fb3f\"\n    },\n    {\n      \"address\": \"00b26044\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b26046\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b2604b\",\n      \"instruction\": \"PUSH 0x2a034cd\"\n    },\n    {\n      \"address\": \"00b26050\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b26052\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b26057\",\n      \"instruction\": \"PUSH 0x18c6de8\"\n    },\n    {\n      \"address\": \"00b2605c\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b2605e\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b26063\",\n      \"instruction\": \"PUSH 0x18c88e4\"\n    },\n    {\n      \"address\": \"00b26068\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b2606a\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b2606f\",\n      \"instruction\": \"PUSH 0x3a2511e\"\n    },\n    {\n      \"address\": \"00b26074\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b26076\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b2607b\",\n      \"instruction\": \"PUSH 0x403df5c\"\n    },\n    {\n      \"address\": \"00b26080\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b26082\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b26087\",\n      \"instruction\": \"PUSH 0x61494be\"\n    },\n    {\n      \"address\": \"00b2608c\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b2608e\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b26093\",\n      \"instruction\": \"PUSH 0x629bafe\"\n    },\n    {\n      \"address\": \"00b26098\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00b2609a\",\n      \"instruction\": \"CALL 0x00b22650\"\n    },\n    {\n      \"address\": \"00b2609f\",\n      \"instruction\": \"CALL 0x00b3d2b0\"\n    },\n    {\n      \"address\": \"00b260a4\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00b260a6\",\n      \"instruction\": \"CALL 0x00ac79d0\"\n    },\n    {\n      \"address\": \"00b260ab\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00b260ac\",\n      \"instruction\": \"CALL 0x00b3d2b0\"\n    },\n    {\n      \"address\": \"00b260b1\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00b260b3\",\n      \"instruction\": \"CALL 0x00ac7a40\"\n    },\n    {\n      \"address\": \"00b260b8\",\n      \"instruction\": \"PUSH 0x18ebadc\"\n    },\n    {\n      \"address\": \"00b260bd\",\n      \"instruction\": \"PUSH 0xb1e500\"\n    },\n    {\n      \"address\": \"00b260c2\",\n      \"instruction\": \"PUSH 0xad48b0\"\n    },\n    {\n      \"address\": \"00b260c7\",\n      \"instruction\": \"PUSH 0xd3d420\"\n    },\n    {\n      \"address\": \"00b260cc\",\n 
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
  "body_end": "00b262be",
  "body_span_bytes": 735,
  "body_start": "00b25fe0",
  "callees": [
    "FUN_00f473a0",
    "FUN_00829110",
    "FUN_00f47380",
    "FUN_00b93c60",
    "FUN_00ac79d0",
    "FUN_00b22650",
    "FUN_00b25ee0",
    "FUN_00b3d2b0",
    "FUN_00ae6780",
    "FUN_00b21340",
    "FUN_00b225d0",
    "FUN_00b22960",
    "FUN_0102c340",
    "FUN_00ac7a40"
  ],
  "callers": [
    "FUN_00f41300",
    "FUN_00d1c9e0",
    "FUN_00ffa2c0",
    "FUN_00b26320",
    "FUN_00b26600"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00b25fe0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "piStack_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "int *"
    },
    {
      "name": "piStack_18",
      "storage": "Stack[-0x18]:4",
      "type": "int *"
    },
    {
      "name": "piStack_14",
      "storage": "Stack[-0x14]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "uVar1",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "iVar2",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "piVar4",
      "storage": "register:0000000c:4",
      "type": "int *"
    },
    {
      "name": "piVar5",
      "storage": "register:0000001c:4",
      "type": "int *"
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_00b25fe0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x725fe0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b25fe0(void)",
  "size_bytes": 735,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b25fe0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 8,
  "xrefs": [
    {
      "from": "00b26369"
    },
    {
      "from": "00b26605"
    },
    {
      "from": "00ffa4be"
    },
    {
      "from": "00d1cac5"
    },
    {
      "from": "00f413fd"
    },
    {
      "from": "00cfa83b"
    },
    {
      "from": "00d19aea"
    },
    {
      "from": "00d19cd1"
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
