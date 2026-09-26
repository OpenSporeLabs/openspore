# Evidence 0x0059c740

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `82ca3c3e315ea14f80aee1dcf7956434a0f021217dab80956afd1612a475c6a8`

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
  "content_sha256": "2d5b916cc38c14a65862cbaacea701bb4964fc910230b361a517c6e0d9f3894a",
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
      "at": "0x0059c740",
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
      "at": "0x0059c740",
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
      "at": "0x0059c743",
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
      "at": "0x0059c743",
      "definite": true,
      "id": "obs-0004",
   
[TRUNCATED]
```

## callees_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059c830"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059c9c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059ca70"
  },
  {
    "name": "EditorAnimWorld_GetCreatureController_0059cac0",
    "reconstructed": true,
    "va": "0x0059cac0"
  },
  {
    "name": "EditorAnimWorld_PlayAnimation_0059cb10",
    "reconstructed": true,
    "va": "0x0059cb10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cbd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cc40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cd20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cdb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059ce30"
  },
  {
    "name": "EditorAnimWorld_SetTargetAngle_0059cea0",
    "reconstructed": true,
    "va": "0x0059cea0"
  },
  {
    "name": "EditorAnimWorld_SetTargetPosition_0059cf00",
    "reconstructed": true,
    "va": "0x0059cf00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cf60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059cfb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0059d060"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x0059c740"
    ],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence.6",
    "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
    "statement": {
      "kind": "repository_contradiction",
      "source": "knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779",
      "statement": "The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection."
    },
    "va": "0x00e5c780"
  }
]
```

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 * __thiscall map_int_EditorCreatureControllerPtr__get(int param_1,uint *param_2)\n\n{\n  undefined4 *puVar1;\n  undefined4 *puVar2;\n  undefined4 *puVar3;\n  undefined4 *puVar4;\n  uint local_8 [2];\n  \n  puVar1 = (undefined4 *)(param_1 + 4);\n  puVar4 = puVar1;\n  if (*(undefined4 **)(param_1 + 0xc) != (undefined4 *)0x0) {\n    puVar2 = *(undefined4 **)(param_1 + 0xc);\n    do {\n      if ((uint)puVar2[4] < *param_2) {\n        puVar3 = (undefined4 *)*puVar2;\n      }\n      else {\n        puVar3 = (undefined4 *)puVar2[1];\n        puVar4 = puVar2;\n      }\n      puVar2 = puVar3;\n    } while (puVar3 != (undefined4 *)0x0);\n  }\n  if ((puVar4 != puVar1) && ((uint)puVar4[4] <= *param_2)) {\n    return puVar4 + 5;\n  }\n  local_8[0] = *param_2;\n  param_2 = (uint *)((uint)param_2 & 0xffffff00);\n  local_8[1] = 0;\n  FUN_0059c520(&param_2,puVar4,local_8,param_2);\n  return (undefined4 *)((int)param_2 + 0x14);\n}\n\n"
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
      "address": "0059c740",
      "instruction": "MOV EAX,dword ptr [ECX + 0xc]"
    },
    {
      "address": "0059c743",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "0059c746",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0059c747",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0059c748",
      "instruction": "LEA ESI,[ECX + 0x4]"
    },
    {
      "address": "0059c74b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0059c74c",
      "instruction": "MOV EDI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "0059c750",
      "instruction": "MOV EDX,ESI"
    },
    {
      "address": "0059c752",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0059c754",
      "instruction": "JZ 0x0059c76a"
    },
    {
      "address": "0059c756",
      "instruction": "MOV EBP,dword ptr [EDI]"
    },
    {
      "address": "0059c758",
      "instruction": "CMP dword ptr [EAX + 0x10],EBP"
    },
    {
      "address": "0059c75b",
      "instruction": "JC 0x0059c764"
    },
    {
      "address": "0059c75d",
      "instruction": "MOV EDX,EAX"
    },
    {
      "address": "0059c75f",
      "instruction": "MOV EAX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "0059c762",
      "instruction": "JMP 0x0059c766"
    },
    {
      "address": "0059c764",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "0059c766",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0059c768",
      "instruction": "JNZ 0x0059c758"
    },
    {
      "address": "0059c76a",
      "instruction": "CMP EDX,ESI"
    },
    {
      "address": "0059c76c",
      "instruction": "JZ 0x0059c775"
    },
    {
      "address": "0059c76e",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0059c770",
      "instruction": "CMP EAX,dword ptr [EDX + 0x10]"
    },
    {
      "address": "0059c773",
      "instruction": "JNC 0x0059c7b1"
    },
    {
      "address": "0059c775",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0059c777",
      "instruction": "MOV dword ptr [ESP + 0xc],EAX"
    },
    {
      "address": "0059c77b",
      "instruction": "MOV byte ptr [ESP + 0x18],0x0"
    },
    {
      "address": "0059c780",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "0059c784",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059c785",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "0059c789",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0059c78a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0059c78b",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "0059c78d",
      "instruction": "MOV dword ptr [EAX],EDX"
    },
    {
      "address": "0059c78f",
      "instruction": "LEA EDX,[ESP + 0x24]"
    },
    {
      "address": "0059c793",
      "instruction": "PUSH EDX"
    },
    {
      "address": "0059c794",
      "instruction": "MOV dword ptr [ESP + 0x20],0x0"
    },
    {
      "address": "0059c79c",
      "instruction": "CALL 0x0059c520"
    },
    {
      "address": "0059c7a1",
      "instruction": "MOV EAX,dword ptr [ESP + 0x18]"
    },
    {
      "address": "0059c7a5",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "0059c7a8",
      "instruction": "POP EDI"
    },
    {
      "address": "0059c7a9",
      "instruction": "POP ESI"
    },
    {
      "address": "0059c7aa",
      "instruction": "POP EBP"
    },
    {
      "address": "0059c7ab",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "0059c7ae",
      "instruction": "RET 0x4"
    },
    {
      "address": "0059c7b1",
      "instruction": "POP EDI"
    },
    {
      "address": "0059c7b2",
      "instruction": "POP ESI"
    },
    {
      "address": "0059c7b3",
      "instruction": "LEA EAX,[EDX + 0x14]"
    },
    {
      "address": "0059c7b6",
      "instruction": "POP EBP"
    },
    {
      "address": "0059c7b7",
      "instruction": "ADD ESP,0x8"
    },
    {
      "address": "0059c7ba",
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 9393,
  "preview": "{\n  \"abi\": {},\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00ff3f00\",\n      \"va\": \"0x00ff3f00\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 3,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"gameglobal-misc\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059c830\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059c9c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059ca70\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cac0\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cb10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cbd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cc40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cd20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cdb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059ce30\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cea0\"\n      },\n      {\n        \"name\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n        \"reconstructed\": true,\n        \"va\": \"0x0059cf00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cf60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059cfb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d010\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d060\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d0b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d1e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0059d300\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0059c981\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059c830\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059ca36\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059c9c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059ca9d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059ca70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059caed\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cac0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cb45\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cb10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cc05\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cbd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cc7d\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cc40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cd55\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cd20\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059cde6\",\n        \"direction\": \"in\",\n        \"other\": \"0x0059cdb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0059ce65\",\n        \"direction\": \"in\",\n        \"other\": \"0
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
  "body_end": "0059c7bc",
  "body_span_bytes": 125,
  "body_start": "0059c740",
  "callees": [
    "FUN_0059c520"
  ],
  "callers": [
    "FUN_0059d1e0",
    "FUN_0059c9c0",
    "FUN_0059cd20",
    "Editors::cEditorAnimWorld::SetTargetPosition",
    "EditorAnimWorld_PlayAnimation",
    "Editors::cEditorAnimWorld::GetCreatureController",
    "FUN_0059cf60",
    "FUN_0059d0b0",
    "FUN_0059d300",
    "FUN_0059cc40",
    "FUN_0059d110",
    "FUN_0059d010",
    "FUN_0059d180",
    "FUN_0059cfb0",
    "FUN_0059cbd0",
    "Editors::cEditorAnimWorld::SetTargetAngle",
    "FUN_0059cdb0",
    "FUN_0059ce30",
    "Editors::cEditorAnimWorld::GetAnimatedCreature",
    "FUN_0059d060",
    "FUN_0059c830",
    "FUN_0059d240"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0059c740",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
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
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "uint[2]"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "map_int_EditorCreatureControllerPtr__get",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x19c740",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined map_int_EditorCreatureControllerPtr__get(void)",
  "size_bytes": 125,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0059c740",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 22,
  "xrefs": [
    {
      "from": "0059caed"
    },
    {
      "from": "0059ca9d"
    },
    {
      "from": "0059c981"
    },
    {
      "from": "0059ca36"
    },
    {
      "from": "0059cb45"
    },
    {
      "from": "0059ce65"
    },
    {
      "from": "0059ced5"
    },
    {
      "from": "0059cf35"
    },
    {
      "from": "0059cf95"
    },
    {
      "from": "0059d095"
    },
    {
      "from": "0059d0e5"
    },
    {
      "from": "0059d145"
    },
    {
      "from": "0059d1b5"
    },
    {
      "from": "0059d215"
    },
    {
      "from": "0059d278"
    },
    {
      "from": "0059d340"
    },
    {
      "from": "0059cd55"
    },
    {
      "from": "0059cfe5"
    },
    {
      "from": "0059d045"
    },
    {
      "from": "0059cc05"
    },
    {
      "from": "0059cc7d"
    },
    {
      "from": "0059cde6"
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
  "files": [],
  "handoffs": [],
  "metadata": []
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x0059c740"
    ],
    "kind": "semantic_decomp_contradiction",
    "path": "evidence.6",
    "source": "knowledgegraph/research/semantic-decomp/worker-01-gameglobal.json",
    "statement": {
      "kind": "repository_contradiction",
      "source": "knowledgegraph/research/global-campaign-2026/conflicts/track-a-type-signature.json:602-779",
      "statement": "The conflict artifact calls the target an ordered lower-bound helper, while the live target body and sibling 0x0059c740 enforce exact-key selection."
    },
    "va": "0x00e5c780"
  }
]
```
