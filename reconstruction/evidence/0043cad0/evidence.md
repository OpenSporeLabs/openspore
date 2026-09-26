# Evidence 0x0043cad0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b6b5fe0f92651c8fe49044a7afb48c6566fbaceef7670faacc285c27d750293d`

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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "unparsed_lines_present: 3 line(s) matched no grammar rule"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "1750455a423b17046210a3dc9325cde67e1aa99a16be32ef0143ecf43dd501f6",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0130"
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
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0024",
        "obs-0028",
        "obs-0032",
        "obs-0038",
        "obs-0042",
        "obs-0048",
        "obs-0049",
        "obs-0052",
        "obs-0054",
        "obs-0058",
        "obs-0062",
        "obs-0064",
        "obs-0065",
        "obs-0068",
        "obs-0069",
        "obs-0074",
        "obs-0078",
        "obs-0082",
        "obs-0090",
        "obs-0093",
        "obs-0100",
        "obs-0103",
        "obs-0104",
        "obs-0109",
        "obs-0111",
        "obs-0114",
        "obs-0116",
        "obs-0118",
        "obs-0122",
        "obs-0124"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          40,
          352,
          432
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0013",
        "obs-0014",
        "obs-0019",
        "obs-0024",
        "obs-0028",
        "obs-0032",
        "obs-0038",
        "obs-0042",
        "obs-0048",
        "obs-0049",
        "obs-0052",
        "obs-0054",
        "obs-0058",
        "obs-0062",
        "obs-0064",
        "obs-0065",
        "obs-0068",
        "obs-0069",
        "obs-0074",
        "obs-0078",
        "obs-0082",
        "obs-0090",
        "obs-0093",
        "obs-0100",
        "obs-0103",
        "obs-0104",
        "obs-0109",
        "obs-0111",
        "obs-0114",
        "obs-0116",
        "obs-0118",
        "obs-0122",
        "obs-0124",
        "obs-0130"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0130"
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
        "obs-0130"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0130"
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
"\n/* WARNING: Removing unreachable block (ram,0x0043cc91) */\n/* WARNING: Removing unreachable block (ram,0x0043cb5e) */\n/* WARNING: Removing unreachable block (ram,0x0043cd02) */\n\nvoid __fastcall FUN_0043cad0(int param_1)\n\n{\n  int iVar1;\n  int iVar2;\n  bool bVar3;\n  int local_78;\n  int local_1c;\n  int local_c;\n  char local_6;\n  char local_5;\n  \n  local_6 = '\\0';\n  local_5 = '\\0';\n  if (*(int *)(param_1 + 0x28) != 0) {\n    local_6 = FUN_004adb80();\n    local_5 = FUN_004adbc0();\n  }\n  bVar3 = false;\n  if (local_6 == '\\0') {\n    FUN_0043ce40();\n  }\n  if ((*(uint *)(param_1 + 0xdc8) & 0x2000000) == 0) {\n    for (local_c = 0; local_c < 3; local_c = local_c + 1) {\n      if ((*(int *)(param_1 + 0x154 + local_c * 4) != 0) &&\n         ((*(char *)(*(int *)(param_1 + 0x154 + local_c * 4) + 0x92) == '\\0' || (local_6 != '\\0'))))\n      {\n        (**(code **)(**(int **)(param_1 + 0x154 + local_c * 4) + 0x30))(3,1);\n        bVar3 = true;\n      }\n    }\n    if ((*(int *)(param_1 + 0x160) != 0) &&\n       ((*(char *)(*(int *)(param_1 + 0x160) + 0x5d) == '\\0' || (local_6 != '\\0')))) {\n      (**(code **)(**(int **)(param_1 + 0x160) + 0x30))(3,1);\n      bVar3 = true;\n    }\n  }\n  if ((*(uint *)(param_1 + 0xdc8) & 0x1000000) == 0) {\n    if (((*(uint *)(param_1 + 0xdc8) & 0x800) == 0) || (local_5 != '\\0')) {\n      local_78 = -1;\n    }\n    else {\n      local_78 = *(int *)(param_1 + 0x1b0);\n    }\n    local_1c = 0;\n    iVar1 = *(int *)(param_1 + 0x6d0);\n    iVar2 = *(int *)(param_1 + 0x6cc);\n    for (; local_1c < iVar1 - iVar2 >> 2; local_1c = local_1c + 1) {\n      if ((local_1c != local_78) &&\n         ((*(char *)(*(int *)(*(int *)(param_1 + 0x6cc) + local_1c * 4) + 0x1d4) == '\\0' ||\n          (local_6 != '\\0')))) {\n        (**(code **)(**(int **)(*(int *)(param_1 + 0x6cc) + local_1c * 4) + 0x30))(3,1);\n        bVar3 = true;\n      }\n    }\n  }\n  if (bVar3) {\n    FUN_004a88d0(0xd0a55625);\n  }\n  return;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 22151,
  "preview": "{\n  \"count\": 251,\n  \"instructions\": [\n    {\n      \"address\": \"0043cad0\",\n      \"instruction\": \"PUSH EBP\"\n    },\n    {\n      \"address\": \"0043cad1\",\n      \"instruction\": \"MOV EBP,ESP\"\n    },\n    {\n      \"address\": \"0043cad3\",\n      \"instruction\": \"SUB ESP,0x78\"\n    },\n    {\n      \"address\": \"0043cad6\",\n      \"instruction\": \"MOV dword ptr [EBP + -0x68],ECX\"\n    },\n    {\n      \"address\": \"0043cad9\",\n      \"instruction\": \"MOV byte ptr [EBP + -0x2],0x0\"\n    },\n    {\n      \"address\": \"0043cadd\",\n      \"instruction\": \"MOV byte ptr [EBP + -0x1],0x0\"\n    },\n    {\n      \"address\": \"0043cae1\",\n      \"instruction\": \"MOV EAX,dword ptr [EBP + -0x68]\"\n    },\n    {\n      \"address\": \"0043cae4\",\n      \"instruction\": \"CMP dword ptr [EAX + 0x28],0x0\"\n    },\n    {\n      \"address\": \"0043cae8\",\n      \"instruction\": \"JZ 0x0043cb06\"\n    },\n    {\n      \"address\": \"0043caea\",\n      \"instruction\": \"MOV ECX,dword ptr [EBP + -0x68]\"\n    },\n    {\n      \"address\": \"0043caed\",\n      \"instruction\": \"MOV ECX,dword ptr [ECX + 0x28]\"\n    },\n    {\n      \"address\": \"0043caf0\",\n      \"instruction\": \"CALL 0x004adb80\"\n    },\n    {\n      \"address\": \"0043caf5\",\n      \"instruction\": \"MOV byte ptr [EBP + -0x2],AL\"\n    },\n    {\n      \"address\": \"0043caf8\",\n      \"instruction\": \"MOV EDX,dword ptr [EBP + -0x68]\"\n    },\n    {\n      \"address\": \"0043cafb\",\n      \"instruction\": \"MOV ECX,dword ptr [EDX + 0x28]\"\n    },\n    {\n      \"address\": \"0043cafe\",\n      \"instruction\": \"CALL 0x004adbc0\"\n    },\n    {\n      \"address\": \"0043cb03\",\n      \"instruction\": \"MOV byte ptr [EBP + -0x1],AL\"\n    },\n    {\n      \"address\": \"0043cb06\",\n      \"instruction\": \"MOV byte ptr [EBP + -0x3],0x0\"\n    },\n    {\n      \"address\": \"0043cb0a\",\n      \"instruction\": \"MOVZX EAX,byte ptr [EBP + -0x2]\"\n    },\n    {\n      \"address\": \"0043cb0e\",\n      \"instruction\": \"TEST EAX,EAX\"\n    },\n    {\n      \"address\": \"0043cb10\",\n      \"instruction\": \"JNZ 0x0043cb1a\"\n    },\n    {\n      \"address\": \"0043cb12\",\n      \"instruction\": \"MOV ECX,dword ptr [EBP + -0x68]\"\n    },\n    {\n      \"address\": \"0043cb15\",\n      \"instruction\": \"CALL 0x0043ce40\"\n    },\n    {\n      \"address\": \"0043cb1a\",\n      \"instruction\": \"MOV ECX,0x19\"\n    },\n    {\n      \"address\": \"0043cb1f\",\n      \"instruction\": \"CMP ECX,0x3c\"\n    },\n    {\n      \"address\": \"0043cb22\",\n      \"instruction\": \"JNC 0x0043cb5e\"\n    },\n    {\n      \"address\": \"0043cb24\",\n      \"instruction\": \"MOV EDX,0x19\"\n    },\n    {\n      \"address\": \"0043cb29\",\n      \"instruction\": \"SHR EDX,0x5\"\n    },\n    {\n      \"address\": \"0043cb2c\",\n      \"instruction\": \"MOV EAX,dword ptr [EBP + -0x68]\"\n    },\n    {\n      \"address\": \"0043cb2f\",\n      \"instruction\": \"MOV ECX,dword ptr [EAX + EDX*0x4 + 0xdc8]\"\n    },\n    {\n      \"address\": \"0043cb36\",\n      \"instruction\": \"MOV dword ptr [EBP + -0x1c],ECX\"\n    },\n    {\n      \"address\": \"0043cb39\",\n      \"instruction\": \"MOV EAX,0x19\"\n    },\n    {\n      \"address\": \"0043cb3e\",\n      \"instruction\": \"XOR EDX,EDX\"\n    },\n    {\n      \"address\": \"0043cb40\",\n      \"instruction\": \"MOV ECX,0x20\"\n    },\n    {\n      \"address\": \"0043cb45\",\n      \"instruction\": \"DIV ECX\"\n    },\n    {\n      \"address\": \"0043cb47\",\n      \"instruction\": \"MOV EAX,0x1\"\n    },\n    {\n      \"address\": \"0043cb4c\",\n      \"instruction\": \"MOV ECX,EDX\"\n    },\n    {\n      \"address\": \"0043cb4e\",\n      \"instruction\": \"SHL EAX,CL\"\n    },\n    {\n      \"address\": \"0043cb50\",\n      \"instruction\": \"AND EAX,dword ptr [EBP + -0x1c]\"\n    },\n    {\n      \"address\": \"0043cb53\",\n      \"instruction\": \"NEG EAX\"\n    },\n    {\n      \"address\": \"0043cb55\",\n      \"instruction\": \"SBB EAX,EAX\"\n    },\n    {\n      \"address\": \"0043cb57\",\n      \"instruction\": \"NEG EAX\"\n    },\n    {\n      \"address\": \"0043cb59\",\n      \"instruction\": \"MOV byte ptr [EBP + -0x1d],AL\"\n    },\n    {\n      \"address\": \"0043cb5c\",\n      \"instruction\": \"JMP 0x0043cb62\"\n    },\n    {\n      \"address\": \"0043cb5e\",\n      \"instruction\": \"MOV byte ptr [EBP + -0x1d],0x0\"\n    },\n    {\n      \"address\": \"0043cb62\",\n      \"instruction\": \"MOVZX ECX,byte ptr [EBP + -0x1d]\"\n    },\n    {\n      \"address\": \"0043cb66\",\n      \"instruction\": \"TEST ECX,ECX\"\n    },\n    {\n      \"address\": \"0043cb68\",\n      \"instruction\": \"JNZ 0x0043cc4d\"\n    },\n    {\n      \"address\": \"0043cb6e\",\n      \"instruction\": \"MOV dword ptr [EBP + -0x8],0x0\"\n    },\n    {\n      \"address\": \"0043cb75\",\n      \"instruction\": \"JMP 0x0043cb80\"\n    },\n    {\n      \"address\": \"0043cb77\",\n      \"instruction\": \"MOV EDX,dword ptr [EBP + -0x8]\"\n    },\n    {\n      \"address\": \"0043cb7a\",\n      \"instruction\": \"ADD EDX,0x1\"\n    },\n    {\n      \"address\": \"0043cb7d\",\n      \"instruction\": \"MOV dword ptr [EBP + -0x8],EDX\"\n    },\n    {\n      \"address\": \"0043cb80\",\n      \"instruction\": \"CMP dword ptr [EBP + -0x8],0x3\"\n    },\n    {\n      \"address\": \"0043cb84\",\n      \"instruction\": \"JGE 0x0043cbf5\"\n    },\n    {\n      \"address\": \"0043cb86\",\n      \"instruction\": \"MOV EAX,dword ptr [EBP + -0x8]\"\n    },\n    {\n      \"address\": \"0043cb89\",\n      \"instruction\": \"MOV ECX,dword ptr [EBP + -0x68]\"\n    },\n    {\n      \"address\": \"0043cb8c\",\n      \"instruction\": \"MOV EDX,dword ptr [ECX + EAX*0x4 + 0x154]\"\n    },\n    {\n      \"address\": \"0043cb93\",\n      \"instruction\": \"MOV dword ptr [EBP + -0x24],EDX\"\n    },\n    {\n      \"address\": \"0043cb96\",\n      \"instructio
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
  "body_end": "0043cdf5",
  "body_span_bytes": 806,
  "body_start": "0043cad0",
  "callees": [
    "FUN_004adb80",
    "FUN_004adbc0",
    "FUN_004a88d0",
    "FUN_0043ce40"
  ],
  "callers": [
    "FUN_0057e790",
    "FUN_00573780",
    "FUN_005b4fa0",
    "FUN_0043a9e0",
    "FUN_005757b0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0043cad0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "int"
    },
    {
      "name": "local_5",
      "storage": "Stack[-0x5]:1",
      "type": "char"
    },
    {
      "name": "local_6",
      "storage": "Stack[-0x6]:1",
      "type": "char"
    },
    {
      "name": "iVar1",
      "storage": "unique:00017200:4",
      "type": "int"
    },
    {
      "name": "param_1",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "int"
    },
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "int"
    },
    {
      "name": "bVar3",
      "storage": "unique:100000ca:1",
      "type": "bool"
    },
    {
      "name": "iVar2",
      "storage": "unique:00017200:4",
      "type": "int"
    }
  ],
  "locals_count": 9,
  "mode": "live",
  "name": "FUN_0043cad0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x3cad0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0043cad0(void)",
  "size_bytes": 806,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0043cad0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "0043ab76"
    },
    {
      "from": "005757bd"
    },
    {
      "from": "005737c7"
    },
    {
      "from": "0057e88d"
    },
    {
      "from": "005b5009"
    },
    {
      "from": "005acc23"
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
