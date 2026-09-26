# Evidence 0x00573d70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `2690a0b5850683b8a42ce17b7eb3c9492692b570939379efbb5c1a2a89be5c02`

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
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
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
    "flow_not_modelled: the linear ESP walk ends at +32, so the listing is not one path",
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
  "content_sha256": "ae60ff08ab279bcc1e4c0c6e1fdbc02cc517758209da8c1df69df68c32325ea4",
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
    "indirect_calls": 6,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0044",
        "obs-0050"
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
        "obs-0003"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0016"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          228,
          244,
          320,
          321
        ],
        "register": "ECX",
        "written_through": 6
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0016",
        "obs-0044",
        "obs-0050"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0044",
        "obs-0050"
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
        "obs-0044",
        "obs-0050"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0044",
        "obs-0050"
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
      "at": "0x00573d70",
      "count": 7,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00573d71",
      "count": 2,
      "first_use": 1,
      "first_write_index": 99,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00573d71",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0003",
      "index": 1,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00573d71",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBX,dword ptr [ESP + 0x8]",
      "reg": "EBX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00573d75",
      "count": 17,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00573d76",
      "count": 13,
      "first_use": 3,
      "first_write_index": 124,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00573d77",
      "count": 5,
      "first_use": 4,
      "first_write_index": 10,
    
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
"\nvoid __thiscall FUN_00573d70(int param_1,int *param_2)\n\n{\n  int *piVar1;\n  int *piVar2;\n  int iVar3;\n  int iVar4;\n  undefined4 uVar5;\n  undefined4 uVar6;\n  \n  if ((param_2 == (int *)0x0) && (*(char *)(param_1 + 0x140) == '\\0')) {\n    *(undefined1 *)(param_1 + 0x140) = 1;\n  }\n  piVar1 = (int *)(param_1 + 0xe4);\n  if ((param_2 != *(int **)(param_1 + 0xe4)) ||\n     ((*(int **)(param_1 + 0xe4) != (int *)0x0 && (iVar3 = FUN_0047ec20(), iVar3 != 0)))) {\n    if ((*(int **)(param_1 + 0xf4) != (int *)0x0) && (*(int **)(param_1 + 0xf4) != param_2)) {\n      if (*(char *)(param_1 + 0x140) == '\\0') {\n        *(undefined1 *)(param_1 + 0x140) = 1;\n      }\n      *(undefined4 *)(param_1 + 0xf4) = 0;\n    }\n    if ((int *)*piVar1 != param_2) {\n      if (((param_2 != (int *)0x0) && (iVar3 = FUN_0047e6c0(), iVar3 != 0)) &&\n         ((*(uint *)(iVar3 + 0xdc8) >> 0xb & 1) != 0)) {\n        *(undefined1 *)(param_1 + 0x140) = 0;\n      }\n      if (((int *)*piVar1 != (int *)0x0) &&\n         ((**(code **)(*(int *)*piVar1 + 0x30))(3,1), *(char *)(param_1 + 0x141) != '\\0')) {\n        if (((int *)*piVar1 != (int *)0x0) &&\n           ((iVar3 = (**(code **)(*(int *)*piVar1 + 0xc))(0x50a993c), iVar3 != 0 &&\n            (iVar4 = FUN_0047e6c0(), iVar4 != 0)))) {\n          FUN_0047e6c0();\n          uVar6 = 1;\n          uVar5 = FUN_0043c3d0(iVar3);\n          FUN_0043e7e0(uVar5,uVar6);\n        }\n        *(undefined1 *)(param_1 + 0x141) = 0;\n      }\n      piVar2 = (int *)*piVar1;\n      if (param_2 != piVar2) {\n        if (param_2 != (int *)0x0) {\n          (**(code **)*param_2)();\n        }\n        *piVar1 = (int)param_2;\n        if (piVar2 != (int *)0x0) {\n          (**(code **)(*piVar2 + 4))();\n        }\n      }\n      if (*piVar1 == 0) {\n        Audio__StopAudio(param_1,0);\n      }\n      else {\n        FUN_00435ed0(0xd2cfe2ad,param_1);\n        FUN_00573c00(0,0xffffffff);\n        (**(code **)(*(int *)*piVar1 + 0x30))(0,1);\n        iVar3 = (**(code **)(*(int *)*piVar1 + 0x10))();\n        if ((iVar3 == 0x50a993c) && (*(char *)(param_1 + 0x140) != '\\0')) {\n          uVar5 = FUN_00572770(piVar1);\n          FUN_0047e6c0();\n          uVar5 = FUN_0043c3d0(uVar5);\n          FUN_0047e6c0(uVar5);\n          FUN_0043e760(uVar5);\n          *(undefined1 *)(param_1 + 0x141) = 1;\n          return;\n        }\n      }\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 12035,
  "preview": "{\n  \"count\": 148,\n  \"instructions\": [\n    {\n      \"address\": \"00573d70\",\n      \"instruction\": \"PUSH EBX\"\n    },\n    {\n      \"address\": \"00573d71\",\n      \"instruction\": \"MOV EBX,dword ptr [ESP + 0x8]\"\n    },\n    {\n      \"address\": \"00573d75\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00573d76\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00573d77\",\n      \"instruction\": \"MOV ESI,ECX\"\n    },\n    {\n      \"address\": \"00573d79\",\n      \"instruction\": \"TEST EBX,EBX\"\n    },\n    {\n      \"address\": \"00573d7b\",\n      \"instruction\": \"JNZ 0x00573d8c\"\n    },\n    {\n      \"address\": \"00573d7d\",\n      \"instruction\": \"CMP byte ptr [ESI + 0x140],BL\"\n    },\n    {\n      \"address\": \"00573d83\",\n      \"instruction\": \"JNZ 0x00573d8c\"\n    },\n    {\n      \"address\": \"00573d85\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x140],0x1\"\n    },\n    {\n      \"address\": \"00573d8c\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0xe4]\"\n    },\n    {\n      \"address\": \"00573d92\",\n      \"instruction\": \"LEA EDI,[ESI + 0xe4]\"\n    },\n    {\n      \"address\": \"00573d98\",\n      \"instruction\": \"CMP EBX,ECX\"\n    },\n    {\n      \"address\": \"00573d9a\",\n      \"instruction\": \"JNZ 0x00573db1\"\n    },\n    {\n      \"address\": \"00573d9c\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"00573d9e\",\n      \"instruction\": \"JZ 0x00573f13\"\n    },\n    {\n      \"address\": \"00573da4\",\n      \"instruction\": \"CALL 0x0047ec20\"\n    },\n    {\n      \"address\": \"00573da9\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00573dab\",\n      \"instruction\": \"JZ 0x00573f13\"\n    },\n    {\n      \"address\": \"00573db1\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0xf4]\"\n    },\n    {\n      \"address\": \"00573db7\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00573db9\",\n      \"instruction\": \"JZ 0x00573dd9\"\n    },\n    {\n      \"address\": \"00573dbb\",\n      \"instruction\": \"CMP EAX,EBX\"\n    },\n    {\n      \"address\": \"00573dbd\",\n      \"instruction\": \"JZ 0x00573dd9\"\n    },\n    {\n      \"address\": \"00573dbf\",\n      \"instruction\": \"CMP byte ptr [ESI + 0x140],0x0\"\n    },\n    {\n      \"address\": \"00573dc6\",\n      \"instruction\": \"JNZ 0x00573dcf\"\n    },\n    {\n      \"address\": \"00573dc8\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x140],0x1\"\n    },\n    {\n      \"address\": \"00573dcf\",\n      \"instruction\": \"MOV dword ptr [ESI + 0xf4],0x0\"\n    },\n    {\n      \"address\": \"00573dd9\",\n      \"instruction\": \"CMP dword ptr [EDI],EBX\"\n    },\n    {\n      \"address\": \"00573ddb\",\n      \"instruction\": \"JZ 0x00573f13\"\n    },\n    {\n      \"address\": \"00573de1\",\n      \"instruction\": \"TEST EBX,EBX\"\n    },\n    {\n      \"address\": \"00573de3\",\n      \"instruction\": \"JZ 0x00573e04\"\n    },\n    {\n      \"address\": \"00573de5\",\n      \"instruction\": \"MOV ECX,EBX\"\n    },\n    {\n      \"address\": \"00573de7\",\n      \"instruction\": \"CALL 0x0047e6c0\"\n    },\n    {\n      \"address\": \"00573dec\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"00573dee\",\n      \"instruction\": \"JZ 0x00573e04\"\n    },\n    {\n      \"address\": \"00573df0\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + 0xdc8]\"\n    },\n    {\n      \"address\": \"00573df6\",\n      \"instruction\": \"SHR EAX,0xb\"\n    },\n    {\n      \"address\": \"00573df9\",\n      \"instruction\": \"TEST AL,0x1\"\n    },\n    {\n      \"address\": \"00573dfb\",\n      \"instruction\": \"JZ 0x00573e04\"\n    },\n    {\n      \"address\": \"00573dfd\",\n      \"instruction\": \"MOV byte ptr [ESI + 0x140],0x0\"\n    },\n    {\n      \"address\": \"00573e04\",\n      \"instruction\": \"MOV ECX,dword ptr [EDI]\"\n    },\n    {\n      \"address\": \"00573e06\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"00573e07\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"00573e09\",\n      \"instruction\": \"JZ 0x00573e68\"\n    },\n    {\n      \"address\": \"00573e0b\",\n      \"instruction\": \"MOV EDX,dword ptr [ECX]\"\n    },\n    {\n      \"address\": \"00573e0d\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0x30]\"\n    },\n    {\n      \"address\": \"00573e10\",\n      \"instruction\": \"PUSH 0x1\"\n    },\n    {\n      \"address\": \"00573e12\",\n      \"instruction\": \"PUSH 0x3\"\n    },\n    {\n      \"address\": \"00573e14\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00573e16\",\n      \"instruction\": \"CMP byte ptr [ESI + 0x141],0x0\"\n    },\n    {\n      \"address\": \"00573e1d\",\n      \"instruction\": \"JZ 0x00573e68\"\n    },\n    {\n      \"address\": \"00573e1f\",\n      \"instruction\": \"MOV ECX,dword ptr [EDI]\"\n    },\n    {\n      \"address\": \"00573e21\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"00573e23\",\n      \"instruction\": \"JZ 0x00573e61\"\n    },\n    {\n      \"address\": \"00573e25\",\n      \"instruction\": \"MOV EDX,dword ptr [ECX]\"\n    },\n    {\n      \"address\": \"00573e27\",\n      \"instruction\": \"MOV EAX,dword ptr [EDX + 0xc]\"\n    },\n    {\n      \"address\": \"00573e2a\",\n      \"instruction\": \"PUSH 0x50a993c\"\n    },\n    {\n      \"address\": \"00573e2f\",\n      \"instruction\": \"CALL EAX\"\n    },\n    {\n      \"address\": \"00573e31\",\n      \"instruction\": \"MOV EBP,EAX\"\n    },\n    {\n      \"address\": \"00573e33\",\n      \"instruction\": \"TEST EBP,EBP\"\n    },\n    {\n      \"address\": \"00573e35\",\n      \"instruction\": \"JZ 0x00573e61\"\n    },\n    {\n      \"address\": \"00573e37\",\n      \
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
  "body_end": "00573f18",
  "body_span_bytes": 425,
  "body_start": "00573d70",
  "callees": [
    "FUN_0047ec20",
    "FUN_0047e6c0",
    "Audio::StopAudio",
    "FUN_0043c3d0",
    "FUN_00573c00",
    "FUN_0043e7e0",
    "FUN_0043e760",
    "FUN_00572770",
    "FUN_00435ed0"
  ],
  "callers": [
    "FUN_00577520",
    "Editors::cEditor::SetActiveMode",
    "Editors::cEditor::OnMouseDown",
    "Editors::cEditor::OnMouseUp",
    "FUN_0057e790",
    "Editors::cEditor::OnKeyDown",
    "Editors::cEditor::OnExit",
    "FUN_0057f6c0",
    "FUN_0058ba60"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00573d70",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x4]:4",
      "type": "int *"
    },
    {
      "name": "piVar1",
      "storage": "unique:00006800:4",
      "type": "int *"
    },
    {
      "name": "piVar2",
      "storage": "unique:00017200:4",
      "type": "int *"
    },
    {
      "name": "iVar3",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "iVar4",
      "storage": "register:00000000:4",
      "type": "int"
    },
    {
      "name": "uVar5",
      "storage": "register:00000000:4",
      "type": "undefined4"
    },
    {
      "name": "uVar6",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00573d70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x173d70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00573d70(void)",
  "size_bytes": 425,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00573d70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00577573"
    },
    {
      "from": "00587498"
    },
    {
      "from": "00587d06"
    },
    {
      "from": "0058b96a"
    },
    {
      "from": "0057e810"
    },
    {
      "from": "0058bd2b"
    },
    {
      "from": "0058025f"
    },
    {
      "from": "0058aecd"
    },
    {
      "from": "00589752"
    },
    {
      "from": "00589caf"
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
