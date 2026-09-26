# Evidence 0x01021180

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `da86461be8174d0d72bb601162dc730833fbbd08ff15f8f8b6eb1417782a3bbd`

## abi

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "abi": {
    "architecture": "x86-32",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0xc",
      "entry_ESP+0x10"
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
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
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
      },
      {
        "entry_offset": "entry_ESP+0xc",
        "observed": true,
        "ordinal": 3,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      },
      {
        "entry_offset": "entry_ESP+0x10",
        "observed": true,
        "ordinal": 4,
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
    "flow_not_modelled: the linear ESP walk ends at -36, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "8abde3b7231c750b99f7b7074d0281866bb464711b582413cb97682bd5d793ae",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__thiscall"
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
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0029",
        "obs-0034",
        "obs-0042"
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
        "obs-0003",
        "obs-0009",
        "obs-0012",
        "obs-0018"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 4,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0016"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0016"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0034",
        "obs-0042"
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
        "obs-0029",
        "obs-0034",
        "obs-0042"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0029",
        "obs-0034",
        "obs-0042"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
 
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
"\nundefined4 * FUN_01021180(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,code *param_4)\n\n{\n  int iVar1;\n  \n  iVar1 = (*param_4)(*param_1,*param_2);\n  if (iVar1 == 0) {\n    iVar1 = (*param_4)(*param_1,*param_3);\n    if (iVar1 != 0) {\n      return param_1;\n    }\n    iVar1 = (*param_4)(*param_2,*param_3);\n    if (iVar1 != 0) {\n      return param_3;\n    }\n  }\n  else {\n    iVar1 = (*param_4)(*param_2,*param_3);\n    if (iVar1 == 0) {\n      iVar1 = (*param_4)(*param_1,*param_3);\n      if (iVar1 == 0) {\n        return param_1;\n      }\n      return param_3;\n    }\n  }\n  return param_2;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 65,
  "instructions": [
    {
      "address": "01021180",
      "instruction": "PUSH EBX"
    },
    {
      "address": "01021181",
      "instruction": "MOV EBX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "01021185",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "01021187",
      "instruction": "PUSH EBP"
    },
    {
      "address": "01021188",
      "instruction": "PUSH ESI"
    },
    {
      "address": "01021189",
      "instruction": "MOV ESI,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "0102118d",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0102118e",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "01021192",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "01021194",
      "instruction": "PUSH EAX"
    },
    {
      "address": "01021195",
      "instruction": "PUSH ECX"
    },
    {
      "address": "01021196",
      "instruction": "CALL ESI"
    },
    {
      "address": "01021198",
      "instruction": "MOV EBP,dword ptr [ESP + 0x24]"
    },
    {
      "address": "0102119c",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "0102119f",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010211a1",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "010211a4",
      "instruction": "PUSH EAX"
    },
    {
      "address": "010211a5",
      "instruction": "JZ 0x010211d1"
    },
    {
      "address": "010211a7",
      "instruction": "MOV ECX,dword ptr [EDI]"
    },
    {
      "address": "010211a9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "010211aa",
      "instruction": "CALL ESI"
    },
    {
      "address": "010211ac",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "010211af",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010211b1",
      "instruction": "JNZ 0x010211ef"
    },
    {
      "address": "010211b3",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "010211b6",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "010211b8",
      "instruction": "PUSH EAX"
    },
    {
      "address": "010211b9",
      "instruction": "PUSH ECX"
    },
    {
      "address": "010211ba",
      "instruction": "CALL ESI"
    },
    {
      "address": "010211bc",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "010211bf",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010211c1",
      "instruction": "JZ 0x010211ca"
    },
    {
      "address": "010211c3",
      "instruction": "POP EDI"
    },
    {
      "address": "010211c4",
      "instruction": "POP ESI"
    },
    {
      "address": "010211c5",
      "instruction": "MOV EAX,EBP"
    },
    {
      "address": "010211c7",
      "instruction": "POP EBP"
    },
    {
      "address": "010211c8",
      "instruction": "POP EBX"
    },
    {
      "address": "010211c9",
      "instruction": "RET"
    },
    {
      "address": "010211ca",
      "instruction": "POP EDI"
    },
    {
      "address": "010211cb",
      "instruction": "POP ESI"
    },
    {
      "address": "010211cc",
      "instruction": "POP EBP"
    },
    {
      "address": "010211cd",
      "instruction": "MOV EAX,EBX"
    },
    {
      "address": "010211cf",
      "instruction": "POP EBX"
    },
    {
      "address": "010211d0",
      "instruction": "RET"
    },
    {
      "address": "010211d1",
      "instruction": "MOV ECX,dword ptr [EBX]"
    },
    {
      "address": "010211d3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "010211d4",
      "instruction": "CALL ESI"
    },
    {
      "address": "010211d6",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "010211d9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010211db",
      "instruction": "JNZ 0x010211ca"
    },
    {
      "address": "010211dd",
      "instruction": "MOV EAX,dword ptr [EBP]"
    },
    {
      "address": "010211e0",
      "instruction": "MOV ECX,dword ptr [EDI]"
    },
    {
      "address": "010211e2",
      "instruction": "PUSH EAX"
    },
    {
      "address": "010211e3",
      "instruction": "PUSH ECX"
    },
    {
      "address": "010211e4",
      "instruction": "CALL ESI"
    },
    {
      "address": "010211e6",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "010211e9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "010211eb",
      "instruction": "MOV EAX,EBP"
    },
    {
      "address": "010211ed",
      "instruction": "JNZ 0x010211f1"
    },
    {
      "address": "010211ef",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "010211f1",
      "instruction": "POP EDI"
    },
    {
      "address": "010211f2",
      "instruction": "POP ESI"
    },
    {
      "address": "010211f3",
      "instruction": "POP EBP"
    },
    {
      "address": "010211f4",
      "instruction": "POP EBX"
    },
    {
      "address": "010211f5",
      "instruction": "RET"
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
  "body_end": "010211f5",
  "body_span_bytes": 118,
  "body_start": "01021180",
  "callees": [],
  "callers": [
    "FUN_01024920",
    "FUN_01021fd0",
    "FUN_0103c800"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "01021180",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "param_2",
      "storage": "Stack[0x8]:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_1",
      "storage": "Stack[0x4]:4",
      "type": "undefined4 *"
    },
    {
      "name": "param_4",
      "storage": "Stack[0x10]:4",
      "type": "undefined *"
    },
    {
      "name": "param_3",
      "storage": "Stack[0xc]:4",
      "type": "undefined4 *"
    },
    {
      "name": "iVar1",
      "storage": "register:00000000:4",
      "type": "int"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "FUN_01021180",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc21180",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_01021180(void)",
  "size_bytes": 118,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x01021180",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "0103c83e"
    },
    {
      "from": "0102495e"
    },
    {
      "from": "0102200e"
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
