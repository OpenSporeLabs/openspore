# Evidence 0x00c70150

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `81c904593ff2baa0a69df067d7e1bd3d9b88b4b187deb2cd3e445b2c5e9101f5`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "hidden_receiver": "none: ECX is written at 0x00c70156 from ESI and is a call argument, not a receiver",
  "hidden_this_register": "ECX is only ever loaded, at 0x00c70156 (MOV ECX,ESI) and 0x00c701a7 (MOV ECX,ESI) and 0x00c701b2 (MOV ECX,ESI), each immediately before a thiscall to a one-argument accessor",
  "ordinary_stack_argument_slots": 3,
  "receiver": false,
  "ret_form": "RET",
  "return_note": "(boolean)",
  "return_observation": "0x00c70246: MOV AL,0x1 and 0x00c7024e: XOR AL,AL write only the low byte; bits 8..31 of EAX are left as the caller left them, and every consumer tests AL (0x00c3588f, 0x00c3514c, 0x00c61a3c, 0x00c630bf, 0x01068b72)",
  "return_register": "EAX",
  "return_semantics": "1 when some entry satisfies the acceptance test, 0 otherwise; the only writes are XOR AL,AL at 0x00c70162 and 0x00c7024e, and MOV AL,0x1 at 0x00c70246, so only AL is defined",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "frame_offset": "ESP0 + 0x04",
      "overwritten": "0x00c7017b stores the loop counter into this same slot and 0x00c701ef reloads it, so the argument is dead after its first read",
      "read_at": [
        "0x00c70152"
      ],
      "role": "the owner object; supplies the element count through its +0x160 and +0x15c fields and the kind through 0x00b8dab0",
      "slot": 1
    },
    {
      "frame_offset": "ESP0 + 0x08",
      "read_at": [
        "0x00c70190"
      ],
      "role": "reloaded into ESI at the top of every outer iteration but never used on any observed path",
      "slot": 2
    },
    {
      "frame_offset": "ESP0 + 0x0c",
      "read_at": [
        "0x00c70194",
        "0x00c7019a"
      ],
      "role": "used both as the dword-array base (0x00c7019e: MOV ESI,[EAX + EBP*0x4]) and as the holder of the dword at +0x84 (0x00c701a1)",
      "slot": 3
    },
    {
      "frame_offset": "ESP0 + 0x10",
      "read_at": [
        "0x00c701d0"
      ],
      "role": "byte flag selecting the inner acceptance rule; no inspected caller initialises this slot",
      "slot": 4,
      "status": "UNRESOLVED"
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET (two sites: 0x00c7024a on the accept path, 0x00c70252 on the reject path)"
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
      "entry_ESP+0x4",
      "entry_ESP+0xc",
      "entry_ESP+0x10",
      "entry_ESP+0x14"
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
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
      },
      {
        "entry_offset": "entry_ESP+0x14",
        "observed": true,
        "ordinal": 5,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -28, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "receiver_not_determinable: ecx_reassigned_before_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_reassigned_before_deref), and the convention rule that would apply discriminates on receiver absence"
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
  "content_sha256": "31427e643c7971ae9ed4ffa6997a449c4981e9fbe37156f72d9c04fc45522a8f",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012",
        "obs-0044",
        "obs-0050"
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
        "obs-0004",
        "obs-0019",
        "obs-0020",
        "obs-0021",
        "obs-0027",
        "obs-0032",
        "obs-0033"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 4,
        "total_bytes": 20
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0006",
        "obs-0011",
        "obs-0021",
        "obs-0022",
        "obs-0030",
        "obs-0043",
        "obs-0049"
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
        "obs-0001",
        "obs-0006",
        "obs-0011",
        "obs-0021",
        "obs-0022",
        "obs-0030",
        "obs-0043",
        "obs-0049"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_reassigned_before_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0012",
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
        "obs-0012",
        "obs-0044",
        "obs-0050"
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "address_window_offset_005c65e0",
    "reconstructed": true,
    "va": "0x005c65e0"
  },
  {
    "name": "FUN_00b8dab0",
    "reconstructed": false,
    "va": "0x00b8dab0"
  },
  {
    "name": "FUN_01021080",
    "reconstructed": true,
    "va": "0x01021080"
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
    "va": "0x00c308e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c344f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c34ee0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c35810"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c59540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c62ff0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c70b20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x01068970"
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
  "count": 96,
  "instructions": [
    {
      "address": "00c70150",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00c70151",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c70152",
      "instruction": "MOV ESI,dword ptr [ESP + 0xc]"
    },
    {
      "address": "00c70156",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c70158",
      "instruction": "CALL 0x00b8dab0"
    },
    {
      "address": "00c7015d",
      "instruction": "CMP EAX,0x5"
    },
    {
      "address": "00c70160",
      "instruction": "JZ 0x00c70167"
    },
    {
      "address": "00c70162",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00c70164",
      "instruction": "POP ESI"
    },
    {
      "address": "00c70165",
      "instruction": "POP ECX"
    },
    {
      "address": "00c70166",
      "instruction": "RET"
    },
    {
      "address": "00c70167",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c70168",
      "instruction": "MOV EBX,dword ptr [ESI + 0x160]"
    },
    {
      "address": "00c7016e",
      "instruction": "SUB EBX,dword ptr [ESI + 0x15c]"
    },
    {
      "address": "00c70174",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c70175",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00c70177",
      "instruction": "SAR EBX,0x2"
    },
    {
      "address": "00c7017a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c7017b",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "00c7017f",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00c70181",
      "instruction": "JLE 0x00c701fc"
    },
    {
      "address": "00c70183",
      "instruction": "JMP 0x00c70194"
    },
    {
      "address": "00c70190",
      "instruction": "MOV ESI,dword ptr [ESP + 0x18]"
    },
    {
      "address": "00c70194",
      "instruction": "MOV EAX,dword ptr [ESI + 0x15c]"
    },
    {
      "address": "00c7019a",
      "instruction": "MOV ECX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "00c7019e",
      "instruction": "MOV ESI,dword ptr [EAX + EBP*0x4]"
    },
    {
      "address": "00c701a1",
      "instruction": "MOV EDI,dword ptr [ECX + 0x84]"
    },
    {
      "address": "00c701a7",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c701a9",
      "instruction": "CALL 0x00ff0420"
    },
    {
      "address": "00c701ae",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00c701b0",
      "instruction": "JNZ 0x00c701f3"
    },
    {
      "address": "00c701b2",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00c701b4",
      "instruction": "CALL 0x005c65e0"
    },
    {
      "address": "00c701b9",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00c701bb",
      "instruction": "MOV ESI,dword ptr [EBP + 0x4]"
    },
    {
      "address": "00c701be",
      "instruction": "SUB ESI,dword ptr [EBP]"
    },
    {
      "address": "00c701c1",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00c701c3",
      "instruction": "SAR ESI,0x2"
    },
    {
      "address": "00c701c6",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "00c701c8",
      "instruction": "JLE 0x00c701ef"
    },
    {
      "address": "00c701ca",
      "instruction": "LEA EBX,[EBX]"
    },
    {
      "address": "00c701d0",
      "instruction": "CMP byte ptr [ESP + 0x20],0x0"
    },
    {
      "address": "00c701d5",
      "instruction": "JZ 0x00c70243"
    },
    {
      "address": "00c701d7",
      "instruction": "MOV EDX,dword ptr [EBP]"
    },
    {
      "address": "00c701da",
      "instruction": "MOV ECX,dword ptr [EDX + EDI*0x4]"
    },
    {
      "address": "00c701dd",
      "instruction": "LEA EAX,[EDX + EDI*0x4]"
    },
    {
      "address": "00c701e0",
      "instruction": "CALL 0x00ff0870"
    },
    {
      "address": "00c701e5",
      "instruction": "CMP EAX,0x1"
    },
    {
      "address": "00c701e8",
      "instruction": "JG 0x00c70243"
    },
    {
      "address": "00c701ea",
      "instruction": "INC EDI"
    },
    {
      "address": "00c701eb",
      "instruction": "CMP EDI,ESI"
    },
    {
      "address": "00c701ed",
      "instruction": "JL 0x00c701d0"
    },
    {
      "address": "00c701ef",
      "instruction": "MOV EBP,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00c701f3",
      "instruction": "INC EBP"
    },
    {
      "address": "00c701f4",
      "instruction": "CMP EBP,EBX"
    },
    {
      "address": "00c701f6",
      "instruction": "MOV dword ptr [ESP + 0x10],EBP"
    },
    {
      "address": "00c701fa",
      "instruction": "JL 0x00c70190"
    },
    {
      "address": "00c701fc",
      "instruction": "CALL 0x01021080"
    },
    {
      "address": "00c70201",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c70203",
      "instruction": "JNZ 0x00c7024b"
    },
    {
      "address": "00c70205",
      "instruction": "MOV EAX,[0x0167a60c]"
    },
    {
      "address": "00c7020a",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c7020c",
      "instruction": "JNZ 0x00c70238"
    },
    {
      "address": "00c7020e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c7020f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c70210",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c70211",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00c70212",
      "instruction": "PUSH 0x145f924"
    },
    {
      "address": "00c70217",
      "instruction": "PUSH 0xc8"
    },
    {
      "address": "00c7021c",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00c70221",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "00c70224",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00c70226",
      "instruction": "JZ 0x00c70231"
    },
    {
      "ad
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
  "original_bytes": 14061,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_receiver\": \"none: ECX is written at 0x00c70156 from ESI and is a call argument, not a receiver\",\n    \"hidden_this_register\": \"ECX is only ever loaded, at 0x00c70156 (MOV ECX,ESI) and 0x00c701a7 (MOV ECX,ESI) and 0x00c701b2 (MOV ECX,ESI), each immediately before a thiscall to a one-argument accessor\",\n    \"ordinary_stack_argument_slots\": 3,\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"(boolean)\",\n    \"return_observation\": \"0x00c70246: MOV AL,0x1 and 0x00c7024e: XOR AL,AL write only the low byte; bits 8..31 of EAX are left as the caller left them, and every consumer tests AL (0x00c3588f, 0x00c3514c, 0x00c61a3c, 0x00c630bf, 0x01068b72)\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"1 when some entry satisfies the acceptance test, 0 otherwise; the only writes are XOR AL,AL at 0x00c70162 and 0x00c7024e, and MOV AL,0x1 at 0x00c70246, so only AL is defined\",\n    \"return_type\": \"std::uint8_t\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"frame_offset\": \"ESP0 + 0x04\",\n        \"overwritten\": \"0x00c7017b stores the loop counter into this same slot and 0x00c701ef reloads it, so the argument is dead after its first read\",\n        \"read_at\": [\n          \"0x00c70152\"\n        ],\n        \"role\": \"the owner object; supplies the element count through its +0x160 and +0x15c fields and the kind through 0x00b8dab0\",\n        \"slot\": 1\n      },\n      {\n        \"frame_offset\": \"ESP0 + 0x08\",\n        \"read_at\": [\n          \"0x00c70190\"\n        ],\n        \"role\": \"reloaded into ESI at the top of every outer iteration but never used on any observed path\",\n        \"slot\": 2\n      },\n      {\n        \"frame_offset\": \"ESP0 + 0x0c\",\n        \"read_at\": [\n          \"0x00c70194\",\n          \"0x00c7019a\"\n        ],\n        \"role\": \"used both as the dword-array base (0x00c7019e: MOV ESI,[EAX + EBP*0x4]) and as the holder of the dword at +0x84 (0x00c701a1)\",\n        \"slot\": 3\n      },\n      {\n        \"frame_offset\": \"ESP0 + 0x10\",\n        \"read_at\": [\n          \"0x00c701d0\"\n        ],\n        \"role\": \"byte flag selecting the inner acceptance rule; no inspected caller initialises this slot\",\n        \"slot\": 4,\n        \"status\": \"UNRESOLVED\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET (two sites: 0x00c7024a on the accept path, 0x00c70252 on the reject path)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 3,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_01021080\",\n      \"va\": \"0x01021080\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_bake_probe_004bf770\",\n      \"va\": \"0x004bf770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 2,\n      \"symbol\": \"app_config_manager_get_0067dcf0\",\n      \"va\": \"0x0067dcf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 2,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"The fourth-stack-slot read at 0x00c701d0 cannot be reconciled with the three-word pushes at all ten inspected call sites; this is recorded as an open ABI discrepancy rather than resolved by assumption.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"address_window_offset_005c65e0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005c65e0\"\n      },\n      {\n        \"name\": \"FUN_00b8dab0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b8dab0\"\n      },\n      {\n        \"name\": \"FUN_01021080\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021080\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c308e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c344f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c34ee0\"\n      },\n      {\n    
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
  "body_end": "00c70252",
  "body_span_bytes": 259,
  "body_start": "00c70150",
  "callees": [
    "FUN_005c65e0",
    "FUN_00ae3740",
    "FUN_00b8dab0",
    "FUN_01021080",
    "FUN_00ae5c30",
    "FUN_00f473a0",
    "FUN_00ff0870",
    "FUN_00ff0420"
  ],
  "callers": [
    "FUN_00c308e0",
    "FUN_00c62ff0",
    "FUN_01068970",
    "FUN_00c344f0",
    "FUN_00c35810",
    "FUN_00c70b20",
    "FUN_00c59540",
    "FUN_00c34ee0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c70150",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_4",
      "storage": "Stack[-0x4]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_00c70150",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x870150",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c70150(void)",
  "size_bytes": 259,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c70150",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 10,
  "xrefs": [
    {
      "from": "00c35887"
    },
    {
      "from": "00c35144"
    },
    {
      "from": "00c70b3a"
    },
    {
      "from": "00c308ec"
    },
    {
      "from": "00c34568"
    },
    {
      "from": "00c59711"
    },
    {
      "from": "01068b6a"
    },
    {
      "from": "00c630b7"
    },
    {
      "from": "00c61a34"
    },
    {
      "from": "00c61b5a"
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
    "reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp",
    "reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.cpp",
    "reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b10/00c70150.json"
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
    "A runtime differential test must confirm the owner's +0x194 value is 5 whenever the scan is expected to run, since a different value would make every call return 0.",
    "No original-process trace has been captured for 0x00c70150. The 0x00c701d0 read of an apparently uninitialised stack slot is the single most important runtime gate: a trace must record the flag value at that address on entry to each of the ten call sites.",
    "The 0x00c70221 ADD ESP,0x18 and the 0x00f473a0 argument order must be observed live to confirm the six-argument allocation contract.",
    "The population-count computation in 0x00ff0870 must be checked against a live element, because the acceptance threshold of 1 depends on its exact result."
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
  "std::uint8_t (boolean)"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
