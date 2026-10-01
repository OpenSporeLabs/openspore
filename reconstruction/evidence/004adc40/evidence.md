# Evidence 0x004adc40

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6f2bc2d767ecfa7503633524fcbeb6ed9e5164e8b7ad63feffda536251ddf015`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "thiscall-compatible ECX-only machine ABI",
  "hidden_this": "OpaqueEditorFlag* receiver in ECX",
  "return_note": "Byte; Field",
  "return_register": "EAX",
  "return_semantics": [
    "Returns the unsigned byte stored at receiver+0x4F. In the original only AL is written, so the upper 24 bits of EAX are NOT zero-extended: they retain receiver address bits 8..31 because EAX was reloaded from the spilled ECX immediately before the byte load. Consumers must read AL only; all three sampled call sites do. The reconstructed source returns a std::uint8_t and therefore zero-extends, which is a strictly stronger guarantee; see source_fidelity.",
    "Returns the unsigned byte stored at receiver+0x4F. In the original only AL is written, so the upper 24 bits of EAX are NOT zero-extended: they retain receiver address bits 8..31 because EAX was reloaded from the spilled ECX immediately before the byte load. Consumers must read AL only; all three sampled call sites do. The reconstructed source returns a std::uint8_t and therefore zero-extends, which is a strictly stronger guarantee."
  ],
  "return_width_bytes": 1,
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "saved_registers": [
      "EBP"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "b141e3b72da0d30c45aed306c32abb4fe110677eaf69f7285dd0ebab44a52409",
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
    "persisted_calling_convention": "thiscall-compatible ECX-only machine ABI"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0012"
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
        "obs-0005",
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          79
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0012"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0012"
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
        "obs-0012"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0012"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x004adc40",
      "count": 4,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x004adc40",
      "ebp_is_general_register": true,
      "fp": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": true,
      "mov_ebp_esp_at": 1,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x004adc41",
      "count": 1,
      "first_use": 1,
      "first_write_index": 6,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004adc41",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004adc43",
      "count": 2,
      "first_use": 2,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004adc44",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0006",
      "index": 3,
      "key": null,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [EBP + -0x4],ECX",
      "reason": "local",
      "resolved": false,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x004adc47",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0007",
      "index": 4,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x004adc47",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004adc4a",
      "count": 1,
      "first_use": 5,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 5,
      "kind": "REG_READ",
      "raw": "MOV AL,byte ptr [EAX + 0x4f]",
      "reg": "EAX"
    },
    {
      "at": "0x004adc4d",
      "definite": true,
      "id": "obs-0010",
      "index": 6,
      "kind": "REG_WRITE",
      "raw": "MOV ESP,EBP",
      "reg": "ESP",
      "write_kind": "reg"
    },
    {
      "at": "0x004adc4f",
      "id": "obs-0011",
      "index": 7,
      "kind": "REG_RESTORE",
      "raw": "POP EBP",
      "reg": "EBP"
    },
    {
      "at": "0x004adc50",
      "form": "RET",
      "id": "obs-0012",
      "imm": null,
      "index": 8,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 9,
    "degraded": false,
    "esp_unresolved": false,
    "
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
    "va": "0x00435a10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004370a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00438700"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00438a40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00439110"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043c450"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043e7e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043e9c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043ea40"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043eae0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043eb50"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043fc20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0043ffa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00440020"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00440090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00448d60"
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
  "count": 9,
  "instructions": [
    {
      "address": "004adc40",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004adc41",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004adc43",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004adc44",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004adc47",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004adc4a",
      "instruction": "MOV AL,byte ptr [EAX + 0x4f]"
    },
    {
      "address": "004adc4d",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004adc4f",
      "instruction": "POP EBP"
    },
    {
      "address": "004adc50",
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 15567,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"thiscall-compatible ECX-only machine ABI\",\n    \"hidden_this\": \"OpaqueEditorFlag* receiver in ECX\",\n    \"return_note\": \"Byte; Field\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": [\n      \"Returns the unsigned byte stored at receiver+0x4F. In the original only AL is written, so the upper 24 bits of EAX are NOT zero-extended: they retain receiver address bits 8..31 because EAX was reloaded from the spilled ECX immediately before the byte load. Consumers must read AL only; all three sampled call sites do. The reconstructed source returns a std::uint8_t and therefore zero-extends, which is a strictly stronger guarantee; see source_fidelity.\",\n      \"Returns the unsigned byte stored at receiver+0x4F. In the original only AL is written, so the upper 24 bits of EAX are NOT zero-extended: they retain receiver address bits 8..31 because EAX was reloaded from the spilled ECX immediately before the byte load. Consumers must read AL only; all three sampled call sites do. The reconstructed source returns a std::uint8_t and therefore zero-extends, which is a strictly stronger guarantee.\"\n    ],\n    \"return_width_bytes\": 1,\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:Byte\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Byte\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"editor_bake_select_004c4a30\",\n      \"va\": \"0x004c4a30\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-CREATURE-ACCESSOR\",\n      \"score\": 2,\n      \"symbol\": \"pkg13_creature_accessor_00b1fdb0\",\n      \"va\": \"0x00b1fdb0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Observed field values and receiver availability in the original process remain runtime-gated.\",\n    \"Receiver identity and the +0x4F field name remain unknown; the SDK layout could not be tied to this receiver by the two-instruction body.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00435a10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004370a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00438700\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00438a40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00439110\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043c450\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043e7e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043e9c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043ea40\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043eae0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043eb50\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043fc20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0043ffa0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00440020\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00440090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00448d60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00448e90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00449420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004494b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00449ce0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0044f420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0048f790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004934d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004942b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004956b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00498470\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004986d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": fals
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
  "body_end": "004adc50",
  "body_span_bytes": 17,
  "body_start": "004adc40",
  "callees": [],
  "callers": [
    "FUN_005b4bf0",
    "FUN_0043eae0",
    "FUN_005bccc0",
    "FUN_0048f790",
    "FUN_004a6ca0",
    "FUN_004a1070",
    "FUN_005820a0",
    "FUN_005b8fb0",
    "FUN_00438a40",
    "FUN_0043fc20",
    "FUN_0043e7e0",
    "FUN_004a29a0",
    "FUN_005b2a50",
    "FUN_00449ce0",
    "FUN_004a7c90",
    "FUN_004934d0",
    "FUN_0043ffa0",
    "FUN_004a3920",
    "FUN_00498470",
    "FUN_005ae480",
    "FUN_0049efc0",
    "FUN_00440090",
    "FUN_004370a0",
    "FUN_0044f420",
    "FUN_005d02d0",
    "FUN_0043e9c0",
    "FUN_005ab5c0",
    "FUN_004a3dc0",
    "FUN_004986d0",
    "FUN_005a9bc0",
    "FUN_00439110",
    "FUN_00448e90",
    "FUN_00435a10",
    "FUN_004942b0",
    "FUN_004a4d60",
    "FUN_0043c450",
    "FUN_00440020",
    "FUN_0049d6b0",
    "FUN_005a9d40",
    "FUN_0049b8b0",
    "FUN_004a6d20",
    "FUN_00449420",
    "Editors::cEditor::sub_581F70",
    "FUN_00586960",
    "FUN_0049a2a0",
    "FUN_00448d60",
    "FUN_005d07f0",
    "FUN_005b75e0",
    "FUN_004494b0",
    "FUN_004a6690",
    "FUN_005bcaa0",
    "FUN_005be500",
    "FUN_004956b0",
    "FUN_005ad5d0",
    "FUN_0043eb50",
    "FUN_004a6f10",
    "FUN_004acd20",
    "FUN_00438700",
    "FUN_0043ea40",
    "FUN_004a7f30",
    "FUN_005ba190",
    "Editors::cEditor::OnMouseDown",
    "FUN_0049fbd0",
    "FUN_0049e6a0"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "004adc40",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_8",
      "storage": "Stack[-0x8]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 1,
  "mode": "live",
  "name": "FUN_004adc40",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xadc40",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004adc40(void)",
  "size_bytes": 17,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004adc40",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 76,
  "xrefs": [
    {
      "from": "004934ff"
    },
    {
      "from": "00448ee1"
    },
    {
      "from": "00435aa5"
    },
    {
      "from": "004986fb"
    },
    {
      "from": "0043c4b8"
    },
    {
      "from": "00449457"
    },
    {
      "from": "004942dd"
    },
    {
      "from": "0049fd8b"
    },
    {
      "from": "0043ffd2"
    },
    {
      "from": "0049f881"
    },
    {
      "from": "00495b64"
    },
    {
      "from": "004371f1"
    },
    {
      "from": "00438728"
    },
    {
      "from": "00438a68"
    },
    {
      "from": "004397aa"
    },
    {
      "from": "004400be"
    },
    {
      "from": "00449d09"
    },
    {
      "from": "0043e87d"
    },
    {
      "from": "0043e9e0"
    },
    {
      "from": "0043ea64"
    },
    {
      "from": "0043eb07"
    },
    {
      "from": "0043eb77"
    },
    {
      "from": "0043fc7b"
    },
    {
      "from": "0044004c"
    },
    {
      "from": "00448d9f"
    },
    {
      "from": "0044955a"
    },
    {
      "from": "0044f54f"
    },
    {
      "from": "004a7f58"
    },
    {
      "from": "004a6700"
    },
    {
      "from": "0048f7c4"
    },
    {
      "from": "004984c2"
    },
    {
      "from": "004a4df7"
    },
    {
      "from": "0049a5be"
    },
    {
      "from": "0049b8f9"
    },
    {
      "from": "0049d899"
    },
    {
      "from": "0049e7f5"
    },
    {
      "from": "004a10ba"
    },
    {
      "from": "004a339d"
    },
    {
      "from": "004a3432"
    },
    {
      "from": "004a44a4"
    },
    {
      "from": "004a6f80"
    },
    {
      "from": "004a6d72"
    },
    {
      "from": "004a3956"
    },
    {
      "from": "004a6ca9"
    },
    {
      "from": "004a7d2d"
    },
    {
      "from": "004acdf5"
    },
    {
      "from": "00586a10"
    },
    {
      "from": "00582149"
    },
    {
      "from": "00582889"
    },
    {
      "from": "005a9bf0"
    },
    {
      "from": "005a9d8f"
    },
    {
      "from": "005ab679"
    },
    {
      "from": "005ad7f3"
    },
    {
      "from": "005ae522"
    },
    {
      "from": "005b2b3d"
    },
    {
      "from": "005b4c1e"
    },
    {
      "from": "005b4ecc"
    },
    {
      "from": "005b75fa"
    },
    {
      "from": "005b93c4"
    },
    {
      "from": "005ba273"
    },
    {
      "from": "005bcb23"
    },
    {
      "from": "005bd49f"
    },
    {
      "from": "005be878"
    },
    {
      "from": "005d02fb"
    },
    {
      "from": "005d0c50"
    },
    {
      "from": "005b72b5"
    },
    {
      "from": "00588ba6"
    },
    {
      "from": "00588ca1"
    },
    {
      "from": "00589ab9"
    },
    {
      "from": "005ac8bf"
    },
    {
      "from": "005ace2c"
    },
    {
      "from": "005af457"
    },
    {
      "from": "005b3d74"
    },
    {
      "from": "005b79e9"
    },
    {
      "from": "005bd684"
    },
    {
      "from": "005beb06"
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
    "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.cpp",
    "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag.hpp",
    "reconstruction/staging/pkg-editor-adc40-flag/adc40_flag_model_test.cpp",
    "reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01.cpp",
    "reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01.hpp",
    "reconstruction/staging/pkg-editor-adc40-smoke01/adc40_smoke01_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-editor-adc40-flag/004adc40.json",
    "reconstruction/metadata/pkg-editor-adc40-smoke01/004adc40.json"
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Byte",
  "Field"
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
