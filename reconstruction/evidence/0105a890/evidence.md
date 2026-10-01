# Evidence 0x0105a890

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b12d8df2e64dd4dd1a578cfea3062a645edc58fb31569ab9849f8e96dc2aae22`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4",
    "entry_ESP+0x8",
    "entry_ESP+0xc"
  ],
  "ordinary_stack_arguments": 3,
  "receiver_register": "ECX",
  "ret_form": "RET 0x10",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX",
  "return_type": "int",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 16,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x10"
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
      "entry_ESP+0x8",
      "entry_ESP+0xc"
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
      }
    ],
    "ret_form": "RET 0x10",
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
      }
    ],
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +56, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
    "receiver_undetermined_blocks_convention: the register receiver is undetermined (ecx_read_without_deref), and the convention rule that would apply discriminates on receiver absence"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x10",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "62f0bd341b4f208288480eb111b200eca2070d7ff89e2d9291ceb6d35e56cae0",
  "conventions": {
    "ambiguities": [
      "receiver_undetermined"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__stdcall",
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
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0061"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0011",
        "obs-0013"
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
        "obs-0005",
        "obs-0006",
        "obs-0011",
        "obs-0012",
        "obs-0017",
        "obs-0019",
        "obs-0038",
        "obs-0042",
        "obs-0044",
        "obs-0048",
        "obs-0050",
        "obs-0053"
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
        "obs-0006",
        "obs-0011",
        "obs-0012",
        "obs-0017",
        "obs-0019",
        "obs-0038",
        "obs-0042",
        "obs-0044",
        "obs-0048",
        "obs-0050",
        "obs-0053"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0061"
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
        "obs-0061"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0061"
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
      "and_esp": null,
      "at": "0x0105a890",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "SUB ESP
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": "FUN_01021260",
    "reconstructed": true,
    "va": "0x01021260"
  },
  {
    "name": "FUN_0105a050",
    "reconstructed": false,
    "va": "0x0105a050"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

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
  "count": 155,
  "instructions": [
    {
      "address": "0105a890",
      "instruction": "SUB ESP,0x40"
    },
    {
      "address": "0105a893",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0105a894",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0105a895",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "0105a897",
      "instruction": "CALL 0x01021260"
    },
    {
      "address": "0105a89c",
      "instruction": "MOV EAX,dword ptr [ESP + 0x54]"
    },
    {
      "address": "0105a8a0",
      "instruction": "MOV ECX,dword ptr [ESP + 0x50]"
    },
    {
      "address": "0105a8a4",
      "instruction": "MOV EBP,dword ptr [ESP + 0x4c]"
    },
    {
      "address": "0105a8a8",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0105a8aa",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105a8ab",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0105a8ac",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0105a8ad",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0105a8af",
      "instruction": "CALL 0x0105a050"
    },
    {
      "address": "0105a8b4",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "0105a8b6",
      "instruction": "JZ 0x0105aa46"
    },
    {
      "address": "0105a8bc",
      "instruction": "MOV ECX,dword ptr [EBP + 0x124]"
    },
    {
      "address": "0105a8c2",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0105a8c4",
      "instruction": "JZ 0x0105aa46"
    },
    {
      "address": "0105a8ca",
      "instruction": "CALL 0x006e87e0"
    },
    {
      "address": "0105a8cf",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0105a8d1",
      "instruction": "JZ 0x0105aa46"
    },
    {
      "address": "0105a8d7",
      "instruction": "MOV ECX,dword ptr [EBP + 0x124]"
    },
    {
      "address": "0105a8dd",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0105a8de",
      "instruction": "XOR BL,BL"
    },
    {
      "address": "0105a8e0",
      "instruction": "CALL 0x006e87e0"
    },
    {
      "address": "0105a8e5",
      "instruction": "MOV ESI,EAX"
    },
    {
      "address": "0105a8e7",
      "instruction": "TEST ESI,ESI"
    },
    {
      "address": "0105a8e9",
      "instruction": "JZ 0x0105a946"
    },
    {
      "address": "0105a8eb",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "0105a8ed",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "0105a8f0",
      "instruction": "PUSH 0xce9f6639"
    },
    {
      "address": "0105a8f5",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0105a8f7",
      "instruction": "CALL EAX"
    },
    {
      "address": "0105a8f9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0105a8fb",
      "instruction": "JZ 0x0105a90d"
    },
    {
      "address": "0105a8fd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105a8fe",
      "instruction": "CALL 0x01058680"
    },
    {
      "address": "0105a903",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0105a906",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "0105a908",
      "instruction": "JMP 0x0105aa0e"
    },
    {
      "address": "0105a90d",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "0105a90f",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "0105a912",
      "instruction": "PUSH 0x3ed590d"
    },
    {
      "address": "0105a917",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "0105a919",
      "instruction": "CALL EAX"
    },
    {
      "address": "0105a91b",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0105a91d",
      "instruction": "JZ 0x0105a946"
    },
    {
      "address": "0105a91f",
      "instruction": "MOV ECX,dword ptr [EAX + 0x88]"
    },
    {
      "address": "0105a925",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "0105a927",
      "instruction": "JZ 0x0105a933"
    },
    {
      "address": "0105a929",
      "instruction": "CMP ECX,0x1"
    },
    {
      "address": "0105a92c",
      "instruction": "JZ 0x0105a933"
    },
    {
      "address": "0105a92e",
      "instruction": "CMP ECX,0x2"
    },
    {
      "address": "0105a931",
      "instruction": "JNZ 0x0105a946"
    },
    {
      "address": "0105a933",
      "instruction": "ADD EAX,0x7c"
    },
    {
      "address": "0105a936",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105a937",
      "instruction": "CALL 0x010534c0"
    },
    {
      "address": "0105a93c",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0105a93f",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "0105a941",
      "instruction": "JMP 0x0105aa0e"
    },
    {
      "address": "0105a946",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0105a947",
      "instruction": "CALL 0x00ae6760"
    },
    {
      "address": "0105a94c",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0105a94f",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0105a951",
      "instruction": "JZ 0x0105a963"
    },
    {
      "address": "0105a953",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0105a954",
      "instruction": "CALL 0x01053320"
    },
    {
      "address": "0105a959",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0105a95c",
      "instruction": "MOV BL,AL"
    },
    {
      "address": "0105a95e",
      "instruction": "JMP 0x0105aa0e"
    },
    {
      "address": "0105a963",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0105a964",
      "instruction": "CALL 0x00b67720"
    },
    {
      "address": "0105a969",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "0105a96c",
      "instruction": "
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
  "original_bytes": 10227,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [\n      \"entry_ESP+0x4\",\n      \"entry_ESP+0x8\",\n      \"entry_ESP+0xc\"\n    ],\n    \"ordinary_stack_arguments\": 3,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x10\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX\",\n    \"return_type\": \"int\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x10\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 8,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sim-core-systems\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"FUN_01021260\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021260\"\n      },\n      {\n        \"name\": \"FUN_0105a050\",\n        \"reconstructed\": false,\n        \"va\": \"0x0105a050\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0105a9b0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421c80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a9e1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421c80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105aa08\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105aa3e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00435ed0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a9b9\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a9ea\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dcc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a8ca\",\n        \"direction\": \"out\",\n        \"other\": \"0x006e87e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a8e0\",\n        \"direction\": \"out\",\n        \"other\": \"0x006e87e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105aa22\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a206f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a947\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ae6760\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a964\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b67720\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a981\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b67740\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a9cd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bd8460\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105aa18\",\n        \"direction\": \"out\",\n        \"other\": \"0x00cb5bb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0105a897\",\n        \"direction\": \"out\",\n        \"other\": 
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
  "body_end": "0105aa4f",
  "body_span_bytes": 448,
  "body_start": "0105a890",
  "callees": [
    "FUN_00421c80",
    "FUN_01053240",
    "FUN_01030e40",
    "FUN_0105a050",
    "FUN_00a206f0",
    "FUN_00b67720",
    "FUN_00bd8460",
    "FUN_006e87e0",
    "FUN_01053320",
    "FUN_010534c0",
    "FUN_00ae6760",
    "FUN_00cb5bb0",
    "FUN_01021260",
    "FUN_01058680",
    "FUN_00b67740",
    "FUN_010533d0",
    "FUN_00421cf0",
    "FUN_00435ed0",
    "App::IAppSystem::Get"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "0105a890",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_0105a890",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xc5a890",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_0105a890(void)",
  "size_bytes": 448,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0105a890",
  "vtables": {
    "referenced_by_vtables": [
      "0x0149b8b4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0149b8f8"
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
    "reconstruction/staging/df2-live-listing/simulator_query_0105a890.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/df2-live-listing/0105a890.json"
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
    "no original-process trace exists in this repository; the static reconstruction of 0x0105a890 is unvalidated at runtime",
    "the committed evidence pack's disassembly is a truncated envelope, so no listing-dependent check could be adjudicated from committed evidence"
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "int"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0149b8b4"
]
```

## Conflicts

```json
[]
```
