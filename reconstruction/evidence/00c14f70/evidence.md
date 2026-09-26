# Evidence 0x00c14f70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `fad81d16ac43af69341c5328cae9ae8159af3358ec43c573a755a142801c3030`

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
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0x40"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
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
    "ret_form": "RET 0xc",
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
        "size_inferred": true,
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
      },
      {
        "entry_offset": "entry_ESP+0x40",
        "observed": true,
        "ordinal": 16,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -60, so the listing is not one path",
    "unparsed_lines_present: 1 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0xc pops less than the highest read slot 0x40; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0xc but entry slot 0x40 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "b9bab18e39af866088f625e9678042afda7ee782bf00ffc39dc81b55f56ca8cc",
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
        "obs-0066",
        "obs-0073"
      ],
      "claim": "the callee pops 12 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 12,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0066",
        "obs-0073"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 12,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0013",
        "obs-0015",
        "obs-0019",
        "obs-0024",
        "obs-0025",
        "obs-0067"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 13,
        "observed_slots": 3,
        "total_bytes": 64
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0011",
        "obs-0015",
        "obs-0016",
        "obs-0020",
        "obs-0025",
        "obs-0028",
        "obs-0031",
        "obs-0037",
        "obs-0043",
        "obs-0048",
        "obs-0050",
        "obs-0060",
        "obs-0067"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          192,
          2900
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0042"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0066",
        "obs-0073"
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
      "and_esp": null,
      "at
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
"\nint * __thiscall FUN_00c14f70(int param_1,int *param_2,undefined4 param_3)\n\n{\n  int iVar1;\n  int *piVar2;\n  char cVar3;\n  int *piVar4;\n  int iVar5;\n  undefined4 *puVar6;\n  undefined4 uVar7;\n  undefined4 *puVar8;\n  ushort uStack_44;\n  short sStack_42;\n  undefined4 uStack_40;\n  undefined4 uStack_3c;\n  undefined4 uStack_38;\n  undefined4 auStack_30 [9];\n  int *piStack_c;\n  int *piStack_8;\n  undefined4 uStack_4;\n  \n  iVar1 = (int)param_2;\n  if (param_2 != (int *)0xffffffff) {\n    param_2 = (int *)0x0;\n    piVar4 = (int *)FUN_0067ddd0();\n    piVar2 = param_2;\n    if (param_2 != (int *)0x0) {\n      param_2 = (int *)0x0;\n      (**(code **)(*piVar2 + 4))();\n    }\n    cVar3 = (**(code **)(*piVar4 + 0x2c))(param_3,0,&param_2);\n    if (cVar3 != '\\0') {\n      if ((*(int *)(param_1 + 0xb54) != 0) && (iVar5 = FUN_00a02bd0(), iVar5 == 0)) {\n        FUN_00434040();\n        puVar6 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0xc0) + 0x2c))();\n        uStack_40 = *puVar6;\n        uStack_3c = puVar6[1];\n        uStack_38 = puVar6[2];\n        uStack_44 = uStack_44 | 4;\n        sStack_42 = sStack_42 + 1;\n        uVar7 = (**(code **)(*(int *)(param_1 + 0xc0) + 0x30))();\n        QuaternionToMatrix(&stack0xffffff98,uVar7);\n        puVar6 = (undefined4 *)&stack0xffffff98;\n        puVar8 = auStack_30;\n        for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {\n          *puVar8 = *puVar6;\n          puVar6 = puVar6 + 1;\n          puVar8 = puVar8 + 1;\n        }\n        uStack_44 = uStack_44 | 2;\n        sStack_42 = sStack_42 + 1;\n        (**(code **)(*piStack_8 + 0x18))(&uStack_44);\n      }\n      (**(code **)(*piStack_8 + 8))(0);\n      piVar2 = piStack_c;\n      if ((piStack_c != (int *)0x0) && (iVar5 = FUN_009cb300(uStack_4,0,0), iVar5 != 0)) {\n        FUN_009caa40(piVar2,iVar1,0);\n        iVar1 = *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0xb54) + 0x17c) + 0x2e4) + iVar1 * 700\n                        );\n        if ((*(float *)(iVar1 + 0x140) + *(float *)(iVar1 + 0x13c) + *(float *)(iVar1 + 0x138)) *\n            0.15 < *(float *)(iVar1 + 0x10c)) {\n          FUN_00c0c4b0(DAT_0157174c);\n        }\n        piVar2 = *(int **)(iVar5 + 0xa4);\n        if (piVar2 != (int *)0x0) {\n          *(undefined4 *)(iVar5 + 0xa4) = 0;\n          (**(code **)(*piVar2 + 4))();\n        }\n      }\n      if (piStack_c != (int *)0x0) {\n        (**(code **)(*piStack_c + 4))();\n      }\n      return piStack_c;\n    }\n    if (piStack_8 != (int *)0x0) {\n      (**(code **)(*piStack_8 + 4))();\n    }\n  }\n  return (int *)0x0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 12365,
  "preview": "{\n  \"count\": 147,\n  \"instructions\": [\n    {\n      \"address\": \"00c14f70\",\n      \"instruction\": \"SUB ESP,0x5c\"\n    },\n    {\n      \"address\": \"00c14f73\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00c14f74\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00c14f75\",\n      \"instruction\": \"MOV EBP,dword ptr [ESP + 0x68]\"\n    },\n    {\n      \"address\": \"00c14f79\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00c14f7a\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00c14f7b\",\n      \"instruction\": \"MOV EBX,ECX\"\n    },\n    {\n      \"address\": \"00c14f7d\",\n      \"instruction\": \"CMP EBP,-0x1\"\n    },\n    {\n      \"address\": \"00c14f80\",\n      \"instruction\": \"JZ 0x00c15138\"\n    },\n    {\n      \"address\": \"00c14f86\",\n      \"instruction\": \"XOR EDI,EDI\"\n    },\n    {\n      \"address\": \"00c14f88\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x70],EDI\"\n    },\n    {\n      \"address\": \"00c14f8c\",\n      \"instruction\": \"CALL 0x0067ddd0\"\n    },\n    {\n      \"address\": \"00c14f91\",\n      \"instruction\": \"MOV ECX,dword ptr [ESP + 0x70]\"\n    },\n    {\n      \"address\": \"00c14f95\",\n      \"instruction\": \"MOV ESI,EAX\"\n    },\n    {\n      \"address\": \"00c14f97\",\n      \"instruction\": \"CMP ECX,EDI\"\n    },\n    {\n      \"address\": \"00c14f99\",\n      \"instruction\": \"JZ 0x00c14fa6\"\n    },\n    {\n      \"address\": \"00c14f9b\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x70],EDI\"\n    },\n    {\n      \"address\": \"00c14f9f\",\n      \"instruction\": \"MOV EAX,dword ptr [ECX]\"\n    },\n    {\n      \"address\": \"00c14fa1\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"00c14fa4\",\n      \"instruction\": \"CALL EDX\"\n    },\n    {\n      \"address\": \"00c14fa6\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00c14fa8\",\n      \"instruction\": \"MOV EDX,dword ptr [ESP + 0x74]\"\n    },\n    {\n      \"address\": \"00c14fac\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0x2c]\"\n    },\n    {\n      \"address\": \"00c14faf\",\n      \"instruction\": \"LEA ECX,[ESP + 0x70]\"\n    },\n    {\n      \"address\": \"00c14fb3\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00c14fb4\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00c14fb5\",\n      \"instruction\": \"PUSH EDX\"\n    },\n    {\n      \"address\": \"00c14fb6\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00c14fb8\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00c14fba\",\n      \"instruction\": \"TEST AL,AL\"\n    },\n    {\n      \"address\": \"00c14fbc\",\n      \"instruction\": \"JZ 0x00c15129\"\n    },\n    {\n      \"address\": \"00c14fc2\",\n      \"instruction\": \"MOV ECX,dword ptr [EBX + 0xb54]\"\n    },\n    {\n      \"address\": \"00c14fc8\",\n      \"instruction\": \"CMP ECX,EDI\"\n    },\n    {\n      \"address\": \"00c14fca\",\n      \"instruction\": \"JZ 0x00c15055\"\n    },\n    {\n      \"address\": \"00c14fd0\",\n      \"instruction\": \"CALL 0x00a02bd0\"\n    },\n    {\n      \"address\": \"00c14fd5\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00c14fd7\",\n      \"instruction\": \"JNZ 0x00c15055\"\n    },\n    {\n      \"address\": \"00c14fd9\",\n      \"instruction\": \"LEA ECX,[ESP + 0x34]\"\n    },\n    {\n      \"address\": \"00c14fdd\",\n      \"instruction\": \"CALL 0x00434040\"\n    },\n    {\n      \"address\": \"00c14fe2\",\n      \"instruction\": \"MOV EDX,dword ptr [EBX + 0xc0]\"\n    },\n    {\n      \"address\": \"00c14fe8\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x2c]\"\n    },\n    {\n      \"address\": \"00c14feb\",\n      \"instruction\": \"LEA ESI,[EBX + 0xc0]\"\n    },\n    {\n      \"address\": \"00c14ff1\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00c14ff3\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00c14ff5\",\n      \"instruction\": \"MOV ECX,dword ptr [EAX]\"\n    },\n    {\n      \"address\": \"00c14ff7\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x38],ECX\"\n    },\n    {\n      \"address\": \"00c14ffb\",\n      \"instruction\": \"MOV EDX,dword ptr [EAX + 0x4]\"\n    },\n    {\n      \"address\": \"00c14ffe\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x3c],EDX\"\n    },\n    {\n      \"address\": \"00c15002\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0x8]\"\n    },\n    {\n      \"address\": \"00c15005\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI]\"\n    },\n    {\n      \"address\": \"00c15007\",\n      \"instruction\": \"OR word ptr [ESP + 0x34],0x4\"\n    },\n    {\n      \"address\": \"00c1500d\",\n      \"instruction\": \"INC word ptr [ESP + 0x36]\"\n    },\n    {\n      \"address\": \"00c15012\",\n      \"instruction\": \"MOV dword ptr [ESP + 0x40],EAX\"\n    },\n    {\n      \"address\": \"00c15016\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x30]\"\n    },\n    {\n      \"address\": \"00c15019\",\n      \"instruction\": \"MOV ECX,ESI\"\n    },\n    {\n      \"address\": \"00c1501b\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00c1501d\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00c1501e\",\n      \"instruction\": \"LEA ECX,[ESP + 0x14]\"\n    },\n    {\n      \"address\": \"00c15022\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00c15023\",\n      \"instruction\": \"CALL 0x0059c190\"\n    },\n    {\n      \"address\": \"00c15028\",\n      \"instruction\": \"MOV ECX,0x9\"\n    },\n    {\n      \"address\": \"00c1502d\",\n      \"instruction\": \"LEA ESI,[E
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
  "body_end": "00c15143",
  "body_span_bytes": 468,
  "body_start": "00c14f70",
  "callees": [
    "FUN_00a02bd0",
    "FUN_0067ddd0",
    "FUN_00434040",
    "FUN_009cb300",
    "FUN_009caa40",
    "FUN_00c0c4b0",
    "QuaternionToMatrix"
  ],
  "callers": [
    "FUN_00c17c80",
    "FUN_00c15470",
    "FUN_00c17d60",
    "FUN_00c17cc0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c14f70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "puVar8",
      "storage": "register:0000001c:4",
      "type": "undefined4 *"
    },
    {
      "name": "uVar7",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "puVar6",
      "storage": "register:00000018:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar5",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "piVar4",
      "storage": "register:00000000:4",
      "type": "int *"
    },
    {
      "name": "cVar3",
      "storage": "register:00000000:1",
      "type": "char"
    },
    {
      "name": "piVar2",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:4",
      "type": "undefined4"
    },
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "uStack_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    },
    {
      "name": "piStack_8",
      "storage": "Stack[-0x8]:4",
      "type": "int *"
    },
    {
      "name": "piStack_c",
      "storage": "Stack[-0xc]:4",
      "type": "int *"
    },
    {
      "name": "auStack_30",
      "storage": "",
      "type": "undefined4[9]"
    },
    {
      "name": "uStack_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_3c",
      "storage": "Stack[-0x3c]:4",
      "type": "undefined4"
    },
    {
      "name": "uStack_40",
      "storage": "Stack[-0x40]:4",
      "type": "undefined4"
    },
    {
      "name": "sStack_42",
      "storage": "Stack[-0x42]:2",
      "type": "short"
    },
    {
      "name": "uStack_44",
      "storage": "Stack[-0x44]:2",
      "type": "ushort"
    }
  ],
  "locals_count": 20,
  "mode": "live",
  "name": "FUN_00c14f70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x814f70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c14f70(void)",
  "size_bytes": 468,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c14f70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "00c17db9"
    },
    {
      "from": "00c17d32"
    },
    {
      "from": "00c15628"
    },
    {
      "from": "00c17cad"
    },
    {
      "from": "00d768a3"
    },
    {
      "from": "00d76e85"
    },
    {
      "from": "00d813aa"
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
