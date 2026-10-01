# Evidence 0x00573d70

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a357f92a3d4a9f6414791903d552f7386f5ee98c849ef49d24c8bda8386df9c7`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32 (x86:LE:32:windows, image base 0x00400000)",
  "calling_convention": "__thiscall",
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX, moved to ESI at 0x00573d77",
  "ret_form": "RET 0x8",
  "return_observation": "0x00573ef9..0x00573f04 and 0x00573f12..0x00573f16 are the two exits, both ending in RET 0x8 with no value contract. Every sampled caller discards the result.",
  "return_register": "none (void)",
  "return_semantics": "No value is returned. EAX and EBP are used as scratch; the two exits differ in whether EBP is restored before the pops, and neither leaves a meaningful EAX that any caller could use.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "ESI",
    "EDI",
    "EBP"
  ],
  "stack_arguments": [
    {
      "entry_offset": "ESP+0x4 at entry, loaded as [ESP+8] after the PUSH EBX at 0x00573d70",
      "name": "part",
      "observed_uses": [
        "null test at 0x00573d79",
        "primary comparison at 0x00573d98",
        "secondary comparison at 0x00573dbd",
        "attribute-bit-11 test at 0x00573de5..0x00573dfd",
        "publish at 0x00573e7a",
        "indirect slot +0x00 and slot +0x04 calls at 0x00573e78 and 0x00573e88"
      ],
      "read_evidence": "0x00573d71: MOV EBX,dword ptr [ESP + 0x8]; the same word is re-read at 0x00573e5d: MOV EBX,dword ptr [ESP + 0x14] after the PUSH EBP at 0x00573e06",
      "type": "void* (refcounted editor part pointer)",
      "width_bytes": 4
    },
    {
      "entry_offset": "ESP+0x8 at entry, i.e. the second callee-cleaned word",
      "name": "arg2",
      "note": "Every observed caller pushes a value and no caller-visible behaviour depends on it. The reconstruction declares it and marks it unused rather than inventing a meaning for it.",
      "observed_values_at_call_sites": [
        "0x1 (0x00587493, 0x0058aeca)",
        "a register value EBP (0x00587d02)"
      ],
      "read_evidence": "none. No instruction in the 148-instruction body reads the second stack word.",
      "type": "std::uint32_t, value not established",
      "width_bytes": 4
    }
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "two exits: the early epilogue at 0x00573f04 and the shared epilogue at 0x00573f16"
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
  "content_sha256": "aab2404876a4eab1c731e9d1e097c79054fe5a182726d34fca78768a7f2b9e0e",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "SUPPORTED",
    "corroboration": "persisted_agrees"
  },
  "cross_validation": {
    "agreement": true,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 0,
    "persisted": "agrees",
    "persisted_calling_convention": "__thiscall"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
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
    "va": "0x00577520"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057e790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0057f6c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "Editors::cEditor::OnExit",
    "reconstructed": false,
    "va": "0x00587a20"
  },
  {
    "name": "editor_input_00588570",
    "reconstructed": true,
    "va": "0x00588570"
  },
  {
    "name": "editor_input_0058ac10",
    "reconstructed": true,
    "va": "0x0058ac10"
  },
  {
    "name": "editor_input_0058b650",
    "reconstructed": true,
    "va": "0x0058b650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0058ba60"
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
  "count": 148,
  "instructions": [
    {
      "address": "00573d70",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00573d71",
      "instruction": "MOV EBX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00573d75",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00573d76",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00573d77",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00573d79",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00573d7b",
      "instruction": "JNZ 0x00573d8c"
    },
    {
      "address": "00573d7d",
      "instruction": "CMP byte ptr [ESI + 0x140],BL"
    },
    {
      "address": "00573d83",
      "instruction": "JNZ 0x00573d8c"
    },
    {
      "address": "00573d85",
      "instruction": "MOV byte ptr [ESI + 0x140],0x1"
    },
    {
      "address": "00573d8c",
      "instruction": "MOV ECX,dword ptr [ESI + 0xe4]"
    },
    {
      "address": "00573d92",
      "instruction": "LEA EDI,[ESI + 0xe4]"
    },
    {
      "address": "00573d98",
      "instruction": "CMP EBX,ECX"
    },
    {
      "address": "00573d9a",
      "instruction": "JNZ 0x00573db1"
    },
    {
      "address": "00573d9c",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573d9e",
      "instruction": "JZ 0x00573f13"
    },
    {
      "address": "00573da4",
      "instruction": "CALL 0x0047ec20"
    },
    {
      "address": "00573da9",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00573dab",
      "instruction": "JZ 0x00573f13"
    },
    {
      "address": "00573db1",
      "instruction": "MOV EAX,dword ptr [ESI + 0xf4]"
    },
    {
      "address": "00573db7",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00573db9",
      "instruction": "JZ 0x00573dd9"
    },
    {
      "address": "00573dbb",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "00573dbd",
      "instruction": "JZ 0x00573dd9"
    },
    {
      "address": "00573dbf",
      "instruction": "CMP byte ptr [ESI + 0x140],0x0"
    },
    {
      "address": "00573dc6",
      "instruction": "JNZ 0x00573dcf"
    },
    {
      "address": "00573dc8",
      "instruction": "MOV byte ptr [ESI + 0x140],0x1"
    },
    {
      "address": "00573dcf",
      "instruction": "MOV dword ptr [ESI + 0xf4],0x0"
    },
    {
      "address": "00573dd9",
      "instruction": "CMP dword ptr [EDI],EBX"
    },
    {
      "address": "00573ddb",
      "instruction": "JZ 0x00573f13"
    },
    {
      "address": "00573de1",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "00573de3",
      "instruction": "JZ 0x00573e04"
    },
    {
      "address": "00573de5",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00573de7",
      "instruction": "CALL 0x0047e6c0"
    },
    {
      "address": "00573dec",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00573dee",
      "instruction": "JZ 0x00573e04"
    },
    {
      "address": "00573df0",
      "instruction": "MOV EAX,dword ptr [EAX + 0xdc8]"
    },
    {
      "address": "00573df6",
      "instruction": "SHR EAX,0xb"
    },
    {
      "address": "00573df9",
      "instruction": "TEST AL,0x1"
    },
    {
      "address": "00573dfb",
      "instruction": "JZ 0x00573e04"
    },
    {
      "address": "00573dfd",
      "instruction": "MOV byte ptr [ESI + 0x140],0x0"
    },
    {
      "address": "00573e04",
      "instruction": "MOV ECX,dword ptr [EDI]"
    },
    {
      "address": "00573e06",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00573e07",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573e09",
      "instruction": "JZ 0x00573e68"
    },
    {
      "address": "00573e0b",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00573e0d",
      "instruction": "MOV EAX,dword ptr [EDX + 0x30]"
    },
    {
      "address": "00573e10",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00573e12",
      "instruction": "PUSH 0x3"
    },
    {
      "address": "00573e14",
      "instruction": "CALL EAX"
    },
    {
      "address": "00573e16",
      "instruction": "CMP byte ptr [ESI + 0x141],0x0"
    },
    {
      "address": "00573e1d",
      "instruction": "JZ 0x00573e68"
    },
    {
      "address": "00573e1f",
      "instruction": "MOV ECX,dword ptr [EDI]"
    },
    {
      "address": "00573e21",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00573e23",
      "instruction": "JZ 0x00573e61"
    },
    {
      "address": "00573e25",
      "instruction": "MOV EDX,dword ptr [ECX]"
    },
    {
      "address": "00573e27",
      "instruction": "MOV EAX,dword ptr [EDX + 0xc]"
    },
    {
      "address": "00573e2a",
      "instruction": "PUSH 0x50a993c"
    },
    {
      "address": "00573e2f",
      "instruction": "CALL EAX"
    },
    {
      "address": "00573e31",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00573e33",
      "instruction": "TEST EBP,EBP"
    },
    {
      "address": "00573e35",
      "instruction": "JZ 0x00573e61"
    },
    {
      "address": "00573e37",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00573e39",
      "instruction": "CALL 0x0047e6c0"
    },
    {
      "address": "00573e3e",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00573e40",
      "instruction": "JZ 0x00573e61"
    },
    {
      "address": "00573e42",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00573e44",
      "instruction": "CALL 0x0047e6c0"
    },
    {
      "address": "00573e49",
      "instruction": "MOV EBX,EAX"
    },
    {
      "address": "00573e4b",
      "instruction": "PUSH 0x1"
    },
    {
      "address": "00573e4d",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00573e4e",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00573e50",
      "instruction": "CALL 0x004
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
  "original_bytes": 13785,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32 (x86:LE:32:windows, image base 0x00400000)\",\n    \"calling_convention\": \"__thiscall\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver_register\": \"ECX, moved to ESI at 0x00573d77\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_observation\": \"0x00573ef9..0x00573f04 and 0x00573f12..0x00573f16 are the two exits, both ending in RET 0x8 with no value contract. Every sampled caller discards the result.\",\n    \"return_register\": \"none (void)\",\n    \"return_semantics\": \"No value is returned. EAX and EBP are used as scratch; the two exits differ in whether EBP is restored before the pops, and neither leaves a meaningful EAX that any caller could use.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBX\",\n      \"ESI\",\n      \"EDI\",\n      \"EBP\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"entry_offset\": \"ESP+0x4 at entry, loaded as [ESP+8] after the PUSH EBX at 0x00573d70\",\n        \"name\": \"part\",\n        \"observed_uses\": [\n          \"null test at 0x00573d79\",\n          \"primary comparison at 0x00573d98\",\n          \"secondary comparison at 0x00573dbd\",\n          \"attribute-bit-11 test at 0x00573de5..0x00573dfd\",\n          \"publish at 0x00573e7a\",\n          \"indirect slot +0x00 and slot +0x04 calls at 0x00573e78 and 0x00573e88\"\n        ],\n        \"read_evidence\": \"0x00573d71: MOV EBX,dword ptr [ESP + 0x8]; the same word is re-read at 0x00573e5d: MOV EBX,dword ptr [ESP + 0x14] after the PUSH EBP at 0x00573e06\",\n        \"type\": \"void* (refcounted editor part pointer)\",\n        \"width_bytes\": 4\n      },\n      {\n        \"entry_offset\": \"ESP+0x8 at entry, i.e. the second callee-cleaned word\",\n        \"name\": \"arg2\",\n        \"note\": \"Every observed caller pushes a value and no caller-visible behaviour depends on it. The reconstruction declares it and marks it unused rather than inventing a meaning for it.\",\n        \"observed_values_at_call_sites\": [\n          \"0x1 (0x00587493, 0x0058aeca)\",\n          \"a register value EBP (0x00587d02)\"\n        ],\n        \"read_evidence\": \"none. No instruction in the 148-instruction body reads the second stack word.\",\n        \"type\": \"std::uint32_t, value not established\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"two exits: the early epilogue at 0x00573f04 and the shared epilogue at 0x00573f16\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00577520\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057e790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0057f6c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00587270\"\n      },\n      {\n        \"name\": \"Editors::cEditor::OnExit\",\n        \"reconstructed\": false,\n        \"va\": \"0x00587a20\"\n      },\n      {\n        \"name\": \"editor_input_00588570\",\n        \"reconstructed\": true,\n        \"va\": \"0x00588570\"\n      },\n      {\n        \"name\": \"editor_input_0058ac10\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058ac10\"\n      },\n      {\n        \"name\": \"editor_input_0058b650\",\n        \"reconstructed\": true,\n        \"va\": \"0x0058b650\"\n      },\n      {\n      
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
  "body_end": "00573f18",
  "body_span_bytes": 425,
  "body_start": "00573d70",
  "callees": [
    "Audio::StopAudio",
    "FUN_0047e6c0",
    "FUN_0043e760",
    "FUN_00572770",
    "FUN_00435ed0",
    "FUN_0043e7e0",
    "FUN_0043c3d0",
    "FUN_0047ec20",
    "FUN_00573c00"
  ],
  "callers": [
    "Editors::cEditor::OnKeyDown",
    "FUN_0057f6c0",
    "Editors::cEditor::SetActiveMode",
    "FUN_0057e790",
    "FUN_00577520",
    "Editors::cEditor::OnMouseUp",
    "Editors::cEditor::OnExit",
    "Editors::cEditor::OnMouseDown",
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
  "locals": [],
  "locals_count": 0,
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

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/opaque_types.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b01/wave13_b01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b01/00573d70.json"
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
    "A differential fixture would need to drive the editor through at least four transitions -- null-to-part, part-to-part, part-to-null and a 0x50a993c part swap -- and record whether the +0x141 handshake fires and in what order.",
    "No original-process trace exists. Every flag value, every attribute bit, every list index and both 0x50a993c comparisons in the contract above are static readings of the code path, not observations.",
    "The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function."
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
  "std::uint32_t, value not established",
  "void",
  "void* (refcounted editor part pointer)"
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
