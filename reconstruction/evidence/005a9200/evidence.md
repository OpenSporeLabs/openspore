# Evidence 0x005a9200

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7181801f73ac2b07547d06236952d3a9a39f7586ab9987ac7408e7e15fe80bdb`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "hidden_receiver": "none",
  "hidden_this_register": "ECX is never read before the first call and is only ever loaded as an explicit argument (0x005a92be, 0x005a92e1, 0x005a9276, 0x005a945c) or used as scratch (0x005a92a6 XOR ECX,ECX, 0x005a92f9 XOR ECX,ECX, 0x005a9450 MOV ECX,EAX, 0x005a92ef MOV ECX,EAX). There is no callee-side this.",
  "ordinary_stack_argument_slots": 1,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x005a9462: MOV AL,0x1 writes only the low byte. The body contains no other write to EAX after the last callee return, so nothing else is defined in the return register.",
  "return_register": "AL",
  "return_semantics": "unconditional true; the only write to the return register is MOV AL,0x1 at 0x005a9462, so bits 8..31 of EAX are undefined on exit. All three inspected callers discard the value.",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit at 0x005a9465; no early return exists in the 199-instruction body"
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
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
    "flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence",
    "sret_vs_out_param: entry slot 0 is written through a pointer"
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
  "content_sha256": "9acd92d08257c53531308163248e401b4f80999866678bc7783bd9a8c26e61e1",
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
    "persisted_calling_convention": "__cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 5,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0032"
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
        "obs-0012"
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
        "obs-0014"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0014"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0032"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0032"
      ],
      "claim": "the last value written to EAX classifies as integral",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "integral"
      }
    }
  ],
  "observations": [
    {
      "at": "0x005a9200",
      "count": 8,
      "first_use": 0,
      "first_write_index": 61,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x005a9201",
      "count": 5,
      "first_use": 1,
      "first_write_index": 35,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x005a9202",
      "count": 8,
      "first_use": 2,
      "first_write_index": 8,
      "id": "obs-0003",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x005a9203",
      "id": "obs-0004",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x0067dd10",
      "target": "0x0067dd10"
    },
    {
      "at": "0x005a9208",
      "count": 27,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0005",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EAX"
    },
    {
      "at": "0x005a9208",
      "definite": true,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x005a920a",
      "definite": true,
      "id": "obs-0007",
      "index": 5,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x005a920c",
      "count": 15,
      "first_use": 6,
      "first_write_index": 4,
      "id": "obs-0008",
      "index": 6,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x38]",
      "reg": "ED
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "wave6_reference_00432a50",
    "reconstructed": true,
    "va": "0x00432a50"
  },
  {
    "name": "achievement_progress_flag_transition_00676ed0",
    "reconstructed": true,
    "va": "0x00676ed0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005a94d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0064acd0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b1dee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d3c6a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d43e30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e84600"
  }
]
```

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
  "count": 199,
  "instructions": [
    {
      "address": "005a9200",
      "instruction": "PUSH EBX"
    },
    {
      "address": "005a9201",
      "instruction": "PUSH ESI"
    },
    {
      "address": "005a9202",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005a9203",
      "instruction": "CALL 0x0067dd10"
    },
    {
      "address": "005a9208",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005a920a",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005a920c",
      "instruction": "MOV EAX,dword ptr [EDX + 0x38]"
    },
    {
      "address": "005a920f",
      "instruction": "CALL EAX"
    },
    {
      "address": "005a9211",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "005a9215",
      "instruction": "LEA EDX,[EDI + 0x24]"
    },
    {
      "address": "005a9218",
      "instruction": "MOV dword ptr [EDI + 0x1c],EAX"
    },
    {
      "address": "005a921b",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "005a921d",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "005a921f",
      "instruction": "NOP"
    },
    {
      "address": "005a9220",
      "instruction": "CMP dword ptr [ECX],0x0"
    },
    {
      "address": "005a9223",
      "instruction": "JNZ 0x005a924f"
    },
    {
      "address": "005a9225",
      "instruction": "INC EAX"
    },
    {
      "address": "005a9226",
      "instruction": "ADD ECX,0x4"
    },
    {
      "address": "005a9229",
      "instruction": "CMP EAX,0x4"
    },
    {
      "address": "005a922c",
      "instruction": "JC 0x005a9220"
    },
    {
      "address": "005a922e",
      "instruction": "MOV ECX,dword ptr [0x015da7c4]"
    },
    {
      "address": "005a9234",
      "instruction": "MOV dword ptr [EDX],ECX"
    },
    {
      "address": "005a9236",
      "instruction": "MOV EAX,[0x015da7c8]"
    },
    {
      "address": "005a923b",
      "instruction": "MOV dword ptr [EDX + 0x4],EAX"
    },
    {
      "address": "005a923e",
      "instruction": "MOV ECX,dword ptr [0x015da7cc]"
    },
    {
      "address": "005a9244",
      "instruction": "MOV dword ptr [EDX + 0x8],ECX"
    },
    {
      "address": "005a9247",
      "instruction": "MOV EAX,[0x015da7d0]"
    },
    {
      "address": "005a924c",
      "instruction": "MOV dword ptr [EDX + 0xc],EAX"
    },
    {
      "address": "005a924f",
      "instruction": "CMP dword ptr [EDI + 0xc],-0x1"
    },
    {
      "address": "005a9253",
      "instruction": "JNZ 0x005a9260"
    },
    {
      "address": "005a9255",
      "instruction": "LEA EAX,[EDI + 0x10]"
    },
    {
      "address": "005a9258",
      "instruction": "CALL 0x005a8f80"
    },
    {
      "address": "005a925d",
      "instruction": "MOV dword ptr [EDI + 0xc],EAX"
    },
    {
      "address": "005a9260",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "005a9265",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a9267",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "005a9269",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "005a926b",
      "instruction": "MOV EAX,dword ptr [EDX + 0x18]"
    },
    {
      "address": "005a926e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a9270",
      "instruction": "PUSH EDI"
    },
    {
      "address": "005a9271",
      "instruction": "PUSH 0xb03bc30c"
    },
    {
      "address": "005a9276",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "005a9278",
      "instruction": "CALL EAX"
    },
    {
      "address": "005a927a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a927c",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a927e",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a9280",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a9282",
      "instruction": "PUSH 0x13ebc58"
    },
    {
      "address": "005a9287",
      "instruction": "PUSH 0x40"
    },
    {
      "address": "005a9289",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "005a928e",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "005a9291",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "005a9293",
      "instruction": "JZ 0x005a9356"
    },
    {
      "address": "005a9299",
      "instruction": "MOV dword ptr [EAX + 0x30],0x0"
    },
    {
      "address": "005a92a0",
      "instruction": "MOV dword ptr [EAX],0x13eb90c"
    },
    {
      "address": "005a92a6",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "005a92a8",
      "instruction": "LEA EDX,[EAX + 0x4]"
    },
    {
      "address": "005a92ab",
      "instruction": "XCHG dword ptr [EDX],ECX"
    },
    {
      "address": "005a92ad",
      "instruction": "MOV dword ptr [EAX],0x13eb844"
    },
    {
      "address": "005a92b3",
      "instruction": "MOV dword ptr [EAX + 0x38],0x0"
    },
    {
      "address": "005a92ba",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005a92bc",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "005a92be",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005a92c0",
      "instruction": "MOV EAX,dword ptr [EDX + 0x4]"
    },
    {
      "address": "005a92c3",
      "instruction": "CALL EAX"
    },
    {
      "address": "005a92c5",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a92c7",
      "instruction": "MOV dword ptr [EBX + 0x30],0xe11332"
    },
    {
      "address": "005a92ce",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "005a92d0",
      "instruction": "MOV dword ptr [EBX + 0x8],0xdbdba1"
    },
    {
      "address": "005a92d7",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "005a92d9",
      "instruction": "MOV EAX,dword ptr [EBX + 0x30]"
    },
    {
      "address": "005
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
  "original_bytes": 13168,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_receiver\": \"none\",\n    \"hidden_this_register\": \"ECX is never read before the first call and is only ever loaded as an explicit argument (0x005a92be, 0x005a92e1, 0x005a9276, 0x005a945c) or used as scratch (0x005a92a6 XOR ECX,ECX, 0x005a92f9 XOR ECX,ECX, 0x005a9450 MOV ECX,EAX, 0x005a92ef MOV ECX,EAX). There is no callee-side this.\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x005a9462: MOV AL,0x1 writes only the low byte. The body contains no other write to EAX after the last callee return, so nothing else is defined in the return register.\",\n    \"return_register\": \"AL\",\n    \"return_semantics\": \"unconditional true; the only write to the return register is MOV AL,0x1 at 0x005a9462, so bits 8..31 of EAX are undefined on exit. All three inspected callers discard the value.\",\n    \"return_type\": \"std::uint8_t\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single exit at 0x005a9465; no early return exists in the 199-instruction body\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-WAVE6-CONTAINERS-MEMORY\",\n      \"score\": 3,\n      \"symbol\": \"wave6_reference_00432a50\",\n      \"va\": \"0x00432a50\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-A3-ACHIEVEMENT-MISSION-WAVE2\",\n      \"score\": 3,\n      \"symbol\": \"achievement_progress_flag_transition_00676ed0\",\n      \"va\": \"0x00676ed0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_bake_probe_004bf770\",\n      \"va\": \"0x004bf770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 2,\n      \"symbol\": \"app_config_manager_get_0067dcf0\",\n      \"va\": \"0x0067dcf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 2,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"wave6_reference_00432a50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00432a50\"\n      },\n      {\n        \"name\": \"achievement_progress_flag_transition_00676ed0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00676ed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005a94d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0064acd0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b1dee0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d3c6a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d43e30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e84600\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005a95ea\",\n        \"direction\": \"in\",\n        \"other\": \"0x005a94d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0064b417\",\n        \"direction\": \"in\",\n        \"other\": \"0x0064acd0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b1df94\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b1dee0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d3c8ca\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d3c6a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00d45002\",\n        \"direction\": \"in\",\n        \"other\": \"0x00d43e30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8467b\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e84600\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e8475c\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e
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
  "body_end": "005a94c0",
  "body_span_bytes": 705,
  "body_start": "005a9200",
  "callees": [
    "FUN_00404f90",
    "FUN_005a8f80",
    "FUN_0067cab0",
    "FUN_00675250",
    "Graphics::IRenderer::Get",
    "FUN_00f473a0",
    "FUN_00801bb0",
    "Reference",
    "App::IAppSystem::Get",
    "FUN_00676ed0"
  ],
  "callers": [
    "FUN_00d3c6a0",
    "FUN_005a94d0",
    "FUN_00b1dee0",
    "FUN_00d43e30",
    "FUN_0064acd0",
    "FUN_00e84600"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "005a9200",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_005a9200",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x1a9200",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_005a9200(void)",
  "size_bytes": 705,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x005a9200",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "0064b417"
    },
    {
      "from": "005a95ea"
    },
    {
      "from": "00b1df94"
    },
    {
      "from": "00d3c8ca"
    },
    {
      "from": "00e8467b"
    },
    {
      "from": "00e8475c"
    },
    {
      "from": "00d45002"
    },
    {
      "from": "00cf5955"
    },
    {
      "from": "00d43044"
    },
    {
      "from": "00dee6d7"
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
    "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b02/005a9200.json"
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
  "gates": [
    "A runtime trace is required to confirm 0x00676ed0's dead first argument is genuinely dead in the shipping build rather than read by an inlined or patched variant.",
    "A runtime trace is required to observe the actual value of [[0x015fd918]+0x3c]+0x118 at editor entry and therefore whether the mask write ever fires in the shipping configuration.",
    "A runtime trace is required to read the runtime-initialised 16 bytes at 0x015da7c4 and confirm the seeded ContentValidation matches the shipped illegal-character set.",
    "A runtime trace with a resolved IAppSystem vtable pointer is required to name the two notification consumers.",
    "No original-process trace has ever been captured for 0x005a9200; every claim here is static. The original Cell stage has never been entered in any recorded run."
  ],
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
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "std::uint8_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013eb844"
]
```

## Conflicts

```json
[]
```
