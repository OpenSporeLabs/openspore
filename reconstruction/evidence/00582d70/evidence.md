# Evidence 0x00582d70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `f48bef9e9818cd48fac8e106128e0a31e93ca3446cfc26bb3daafd42397b2f3b`

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
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0xc",
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
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "confidence": "UNKNOWN",
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1,
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": true,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 12,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0xc"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -20, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_width_ambiguous: one entry slot is read at more than one width"
  ],
  "cleanup": {
    "bytes": 12,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0xc",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "2f138dbcaa97455aebb2da6d23318b56ac5ac5815187816abb512cb812e8f9cb",
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
        "obs-0024",
        "obs-0037",
        "obs-0052",
        "obs-0070",
        "obs-0075",
        "obs-0079"
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
        "obs-0010",
        "obs-0012",
        "obs-0027",
        "obs-0031",
        "obs-0039",
        "obs-0041",
        "obs-0056",
        "obs-0058"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 3,
        "total_bytes": 12
      }
    },
    {
      "based_on": [
        "obs-0010",
        "obs-0012",
        "obs-0027",
        "obs-0031",
        "obs-0039",
        "obs-0041",
        "obs-0056",
        "obs-0058"
      ],
      "claim": "one entry slot carries several read widths",
      "confidence": "UNKNOWN",
      "id": "A2"
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0018",
        "obs-0041",
        "obs-0046",
        "obs-0053",
        "obs-0054"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          864,
          868,
          872,
          876,
          880,
          901
        ],
        "register": "ECX",
        "written_through": 3
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0006",
        "obs-0018",
        "obs-0024",
        "obs-0037",
        "obs-0041",
        "obs-0046",
        "obs-0052",
        "obs-0053",
        "obs-0054",
        "obs-0070",
        "obs-0075",
        "obs-0079"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0024",
        "obs-0037",
        "obs-0052",
        "obs-0070",
        "obs-0075",
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
        "obs-00
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
"\n/* WARNING: Enum \"Names\": Some values do not have unique names */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nvoid __thiscall FUN_00582d70(int param_1,int param_2,char param_3,int param_4)\n\n{\n  int *piVar1;\n  int iVar2;\n  int *piVar3;\n  int unaff_EBP;\n  int unaff_EDI;\n  int iVar4;\n  undefined4 uVar5;\n  undefined1 *puVar6;\n  undefined4 uVar7;\n  undefined1 local_c [12];\n  \n  iVar4 = 0;\n  if (*(int *)(param_1 + 0x360) != 0) {\n    if (param_2 == 1) {\n      if (param_3 == '\\0') {\n        piVar1 = (int *)(param_1 + 0x36c);\n        if (param_4 == 0) {\n          iVar4 = (*(int *)(param_1 + 0x370) - *piVar1) / 0x30;\n          if (0 < iVar4) {\n            iVar2 = 0;\n            do {\n              FUN_0059d110(*(undefined4 *)(iVar2 + *piVar1),local_c);\n              puVar6 = local_c;\n              uVar7 = 0;\n              uVar5 = 0x3f1bf57;\n              FUN_00401050(0x3f1bf57,0,puVar6);\n              FUN_0045af60(uVar5,uVar7,puVar6);\n              Editors__cEditorAnimWorld__DestroyCreature\n                        (*(cEditorAnimWorld **)(iVar2 + *piVar1),unaff_EBP);\n              iVar2 = iVar2 + 0x30;\n              iVar4 = iVar4 + -1;\n            } while (iVar4 != 0);\n          }\n          FUN_009c69f0(*piVar1,*(undefined4 *)(param_1 + 0x370));\n          return;\n        }\n        iVar2 = (*(int *)(param_1 + 0x370) - *piVar1) / 0x30;\n        if (0 < iVar2) {\n          piVar3 = (int *)*piVar1;\n          do {\n            if (*piVar3 == param_4) {\n              iVar4 = iVar4 * 0x30;\n              FUN_0059d110(*(undefined4 *)(iVar4 + *piVar1),local_c);\n              puVar6 = local_c;\n              uVar7 = 0;\n              uVar5 = 0x3f1bf57;\n              FUN_00401050(0x3f1bf57,0,puVar6);\n              FUN_0045af60(uVar5,uVar7,puVar6);\n              Editors__cEditorAnimWorld__DestroyCreature\n                        (*(cEditorAnimWorld **)(*piVar1 + iVar4),unaff_EBP);\n              FUN_0057ef50(*piVar1 + iVar4);\n              return;\n            }\n            iVar4 = iVar4 + 1;\n            piVar3 = piVar3 + 0xc;\n          } while (iVar4 < iVar2);\n        }\n      }\n      else {\n        iVar2 = *(int *)(param_1 + 0x370) - *(int *)(param_1 + 0x36c);\n        iVar4 = iVar2 >> 0x1f;\n        if (iVar2 / 0x30 + iVar4 != iVar4) {\n          FUN_0059d110(*(undefined4 *)\n                        (((*(int *)(param_1 + 0x370) - *(int *)(param_1 + 0x36c)) / 0x30) * 0x30 +\n                         -0x30 + *(int *)(param_1 + 0x36c)),local_c);\n          puVar6 = local_c;\n          uVar7 = 0;\n          uVar5 = 0x3f1bf57;\n          FUN_00401050(0x3f1bf57,0,puVar6);\n          FUN_0045af60(uVar5,uVar7,puVar6);\n          Editors__cEditorAnimWorld__DestroyCreature\n                    (*(cEditorAnimWorld **)\n                      (((*(int *)(param_1 + 0x370) - *(int *)(param_1 + 0x36c)) / 0x30) * 0x30 +\n                       -0x30 + *(int *)(param_1 + 0x36c)),unaff_EDI);\n          *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + -0x30;\n          return;\n        }\n      }\n    }\n    else if (param_2 == 0) {\n      if (*(int *)(param_1 + 0x364) != 0) {\n        if (*(char *)(param_1 + 0x385) != '\\0') {\n          FUN_0057e340(0);\n        }\n        Editors__cEditorAnimWorld__DestroyCreature\n                  (*(cEditorAnimWorld **)(param_1 + 0x364),unaff_EDI);\n        *(undefined4 *)(param_1 + 0x364) = 0;\n        return;\n      }\n    }\n    else if ((param_2 == 2) && (*(cEditorAnimWorld **)(param_1 + 0x368) != (cEditorAnimWorld *)0x0))\n    {\n      Editors__cEditorAnimWorld__DestroyCreature(*(cEditorAnimWorld **)(param_1 + 0x368),unaff_EDI);\n      *(undefined4 *)(param_1 + 0x368) = 0;\n      return;\n    }\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 16233,
  "preview": "{\n  \"count\": 199,\n  \"instructions\": [\n    {\n      \"address\": \"00582d70\",\n      \"instruction\": \"SUB ESP,0xc\"\n    },\n    {\n      \"address\": \"00582d73\",\n      \"instruction\": \"PUSH ESI\"\n    },\n    {\n      \"address\": \"00582d74\",\n      \"instruction\": \"MOV ESI,ECX\"\n    },\n    {\n      \"address\": \"00582d76\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0x360]\"\n    },\n    {\n      \"address\": \"00582d7c\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00582d7d\",\n      \"instruction\": \"XOR EDI,EDI\"\n    },\n    {\n      \"address\": \"00582d7f\",\n      \"instruction\": \"CMP ECX,EDI\"\n    },\n    {\n      \"address\": \"00582d81\",\n      \"instruction\": \"JZ 0x00582e96\"\n    },\n    {\n      \"address\": \"00582d87\",\n      \"instruction\": \"MOV EAX,dword ptr [ESP + 0x18]\"\n    },\n    {\n      \"address\": \"00582d8b\",\n      \"instruction\": \"CMP EAX,0x1\"\n    },\n    {\n      \"address\": \"00582d8e\",\n      \"instruction\": \"JNZ 0x00582f72\"\n    },\n    {\n      \"address\": \"00582d94\",\n      \"instruction\": \"CMP byte ptr [ESP + 0x1c],0x0\"\n    },\n    {\n      \"address\": \"00582d99\",\n      \"instruction\": \"MOV EAX,0x2aaaaaab\"\n    },\n    {\n      \"address\": \"00582d9e\",\n      \"instruction\": \"JZ 0x00582e59\"\n    },\n    {\n      \"address\": \"00582da4\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI + 0x370]\"\n    },\n    {\n      \"address\": \"00582daa\",\n      \"instruction\": \"SUB EDX,dword ptr [ESI + 0x36c]\"\n    },\n    {\n      \"address\": \"00582db0\",\n      \"instruction\": \"IMUL EDX\"\n    },\n    {\n      \"address\": \"00582db2\",\n      \"instruction\": \"SAR EDX,0x3\"\n    },\n    {\n      \"address\": \"00582db5\",\n      \"instruction\": \"MOV EAX,EDX\"\n    },\n    {\n      \"address\": \"00582db7\",\n      \"instruction\": \"SHR EAX,0x1f\"\n    },\n    {\n      \"address\": \"00582dba\",\n      \"instruction\": \"ADD EAX,EDX\"\n    },\n    {\n      \"address\": \"00582dbc\",\n      \"instruction\": \"JZ 0x00582e96\"\n    },\n    {\n      \"address\": \"00582dc2\",\n      \"instruction\": \"LEA EDX,[ESP + 0x8]\"\n    },\n    {\n      \"address\": \"00582dc6\",\n      \"instruction\": \"PUSH EDX\"\n    },\n    {\n      \"address\": \"00582dc7\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI + 0x370]\"\n    },\n    {\n      \"address\": \"00582dcd\",\n      \"instruction\": \"SUB EDX,dword ptr [ESI + 0x36c]\"\n    },\n    {\n      \"address\": \"00582dd3\",\n      \"instruction\": \"MOV EAX,0x2aaaaaab\"\n    },\n    {\n      \"address\": \"00582dd8\",\n      \"instruction\": \"IMUL EDX\"\n    },\n    {\n      \"address\": \"00582dda\",\n      \"instruction\": \"SAR EDX,0x3\"\n    },\n    {\n      \"address\": \"00582ddd\",\n      \"instruction\": \"MOV EAX,EDX\"\n    },\n    {\n      \"address\": \"00582ddf\",\n      \"instruction\": \"SHR EAX,0x1f\"\n    },\n    {\n      \"address\": \"00582de2\",\n      \"instruction\": \"ADD EAX,EDX\"\n    },\n    {\n      \"address\": \"00582de4\",\n      \"instruction\": \"MOV EDX,dword ptr [ESI + 0x36c]\"\n    },\n    {\n      \"address\": \"00582dea\",\n      \"instruction\": \"LEA EAX,[EAX + EAX*0x2]\"\n    },\n    {\n      \"address\": \"00582ded\",\n      \"instruction\": \"SHL EAX,0x4\"\n    },\n    {\n      \"address\": \"00582df0\",\n      \"instruction\": \"MOV EAX,dword ptr [EAX + EDX*0x1 + -0x30]\"\n    },\n    {\n      \"address\": \"00582df4\",\n      \"instruction\": \"PUSH EAX\"\n    },\n    {\n      \"address\": \"00582df5\",\n      \"instruction\": \"CALL 0x0059d110\"\n    },\n    {\n      \"address\": \"00582dfa\",\n      \"instruction\": \"LEA ECX,[ESP + 0x8]\"\n    },\n    {\n      \"address\": \"00582dfe\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00582dff\",\n      \"instruction\": \"PUSH EDI\"\n    },\n    {\n      \"address\": \"00582e00\",\n      \"instruction\": \"PUSH 0x3f1bf57\"\n    },\n    {\n      \"address\": \"00582e05\",\n      \"instruction\": \"CALL 0x00401050\"\n    },\n    {\n      \"address\": \"00582e0a\",\n      \"instruction\": \"MOV ECX,EAX\"\n    },\n    {\n      \"address\": \"00582e0c\",\n      \"instruction\": \"CALL 0x0045af60\"\n    },\n    {\n      \"address\": \"00582e11\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0x370]\"\n    },\n    {\n      \"address\": \"00582e17\",\n      \"instruction\": \"SUB ECX,dword ptr [ESI + 0x36c]\"\n    },\n    {\n      \"address\": \"00582e1d\",\n      \"instruction\": \"MOV EAX,0x2aaaaaab\"\n    },\n    {\n      \"address\": \"00582e22\",\n      \"instruction\": \"IMUL ECX\"\n    },\n    {\n      \"address\": \"00582e24\",\n      \"instruction\": \"SAR EDX,0x3\"\n    },\n    {\n      \"address\": \"00582e27\",\n      \"instruction\": \"MOV EAX,EDX\"\n    },\n    {\n      \"address\": \"00582e29\",\n      \"instruction\": \"SHR EAX,0x1f\"\n    },\n    {\n      \"address\": \"00582e2c\",\n      \"instruction\": \"ADD EAX,EDX\"\n    },\n    {\n      \"address\": \"00582e2e\",\n      \"instruction\": \"LEA EDX,[EAX + EAX*0x2]\"\n    },\n    {\n      \"address\": \"00582e31\",\n      \"instruction\": \"MOV EAX,dword ptr [ESI + 0x36c]\"\n    },\n    {\n      \"address\": \"00582e37\",\n      \"instruction\": \"SHL EDX,0x4\"\n    },\n    {\n      \"address\": \"00582e3a\",\n      \"instruction\": \"MOV ECX,dword ptr [EDX + EAX*0x1 + -0x30]\"\n    },\n    {\n      \"address\": \"00582e3e\",\n      \"instruction\": \"PUSH ECX\"\n    },\n    {\n      \"address\": \"00582e3f\",\n      \"instruction\": \"MOV ECX,dword ptr [ESI + 0x360]\"\n    },\n    {\n      \"address\": \"00582e45\",\n      \"instruction\": \"CALL 0x0059c6e0\"\n    },\n    {\n      \"address\": \"00582e4a\",\n      \"instruction\": \"ADD dword ptr [ESI + 0x370],-0x30\"\n    },\n    {\n      \"address\": \"00582e51\",\n      \"instruction\": \"POP EDI\"\n    },\n    {\n      \"ad
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
  "body_end": "00582fdd",
  "body_span_bytes": 622,
  "body_start": "00582d70",
  "callees": [
    "FUN_0059d110",
    "FUN_0057e340",
    "FUN_00401050",
    "FUN_0045af60",
    "FUN_0057ef50",
    "FUN_009c69f0",
    "Editors::cEditorAnimWorld::DestroyCreature"
  ],
  "callers": [
    "FUN_0062c340",
    "FUN_0062c990",
    "FUN_0062ba10"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00582d70",
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
      "type": "int"
    },
    {
      "name": "local_c",
      "storage": "",
      "type": "undefined1[12]"
    },
    {
      "name": "uVar5",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "puVar6",
      "storage": "Stack[-0x20]:4",
      "type": "undefined1 *"
    },
    {
      "name": "uVar7",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "piVar3",
      "storage": "register:00000008:4",
      "type": "int *"
    },
    {
      "name": "unaff_EBP",
      "storage": "register:00000014:4",
      "type": "int"
    },
    {
      "name": "unaff_EDI",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "iVar4",
      "storage": "register:0000001c:4",
      "type": "int"
    },
    {
      "name": "param_3",
      "storage": "Stack[0x8]:1",
      "type": "char"
    },
    {
      "name": "param_4",
      "storage": "Stack[0xc]:4",
      "type": "int"
    },
    {
      "name": "piVar1",
      "storage": "unique:00006800:4",
      "type": "int *"
    },
    {
      "name": "iVar2",
      "storage": "register:00000008:4",
      "type": "int"
    }
  ],
  "locals_count": 14,
  "mode": "live",
  "name": "FUN_00582d70",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x182d70",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00582d70(void)",
  "size_bytes": 622,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00582d70",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "0062c3de"
    },
    {
      "from": "0062ba5e"
    },
    {
      "from": "0062ba7f"
    },
    {
      "from": "0062ca18"
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
