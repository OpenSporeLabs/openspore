# Evidence 0x00e5c0f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `dc0077aee1e717ae5bf027fbec17756fededd862b1839d74fb5a11ab6b5cfbc9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_receiver": "ECX App::cCellModeStrategy*",
  "ordinary_stack_arguments": [
    {
      "evidence": "captured into ECX by MOV ECX,[ESP+0x4] at 0x00e5c0f8 and pushed as the first forwarded word; the body performs no further use of the word after the forward",
      "name": "mouseButton",
      "offset": "ESP+4",
      "slot": 0,
      "type": "int32"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0x2c] at 0x00e5c107 into the forwarded word at 0x00e5c10b",
      "name": "mouseX",
      "offset": "ESP+8",
      "slot": 1,
      "type": "raw float dword"
    },
    {
      "evidence": "loaded by FLD float ptr [ESP+0xc] at 0x00e5c0f4 into the forwarded word at 0x00e5c103",
      "name": "mouseY",
      "offset": "ESP+0xc",
      "slot": 2,
      "type": "raw float dword"
    },
    {
      "evidence": "captured into EAX by MOV EAX,[ESP+0x10] at 0x00e5c0f0 and pushed as the fourth forwarded word at 0x00e5c0ff",
      "name": "mouseState",
      "offset": "ESP+0x10",
      "slot": 3,
      "type": "uint32",
      "width_bytes": 4
    }
  ],
  "ret_form": "RET 0x10",
  "return_register": "AL, set once by MOV AL,0x1 at 0x00e5c189",
  "stack_cleanup_bytes": 16
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
    "ret_form": "RET 0x10",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "stack_cleanup_bytes": 16,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path",
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
  "content_sha256": "937697cb1b9187a1d28802f0a1842a9b455c0a42c01c61d7237f2ef9446091e0",
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
    "ghidra_parameter_count": 5,
    "persisted": "no_information",
    "persisted_calling_convention": "thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028"
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
        "obs-0002",
        "obs-0004",
        "obs-0005",
        "obs-0011"
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
        "obs-0006",
        "obs-0013",
        "obs-0019",
        "obs-0023"
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
        "obs-0013",
        "obs-0019",
        "obs-0023"
      ],
      "claim": "the calling convention is unknown: the receiver is undetermined (ecx_read_without_deref) and every remaining discriminator needs receiver absence",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0028"
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
        "obs-0007"
      ],
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
    }
  ],
  "observations": [
    {
      "at": "0x00e5c0f0",
      "count": 11,
      "first_use": 0,
      "first_write_index": 3,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00e5c0f0",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0002",
      "index": 0,
      "key": 16,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00e5c0f0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x10]
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "game_input_mouse_up_00697af0",
    "reconstructed": true,
    "va": "0x00697af0"
  },
  {
    "name": "camera_light_origin_helper_007c4900",
    "reconstructed": true,
    "va": "0x007c4900"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00e7c8c0",
      "0x00e7c8c0",
      "0x00e5c0f0",
      "0x00e7c8c0",
      "0x00e6c860"
    ],
    "conflict_id": "U7",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5c0f0",
      "0x00e6c860",
      "0x00e7d660"
    ],
    "conflict_id": "U9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```

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
  "count": 46,
  "instructions": [
    {
      "address": "00e5c0f0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00e5c0f4",
      "instruction": "FLD float ptr [ESP + 0xc]"
    },
    {
      "address": "00e5c0f8",
      "instruction": "MOV ECX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "00e5c0fc",
      "instruction": "SUB ESP,0x18"
    },
    {
      "address": "00e5c0ff",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e5c100",
      "instruction": "SUB ESP,0x8"
    },
    {
      "address": "00e5c103",
      "instruction": "FSTP float ptr [ESP + 0x4]"
    },
    {
      "address": "00e5c107",
      "instruction": "FLD float ptr [ESP + 0x2c]"
    },
    {
      "address": "00e5c10b",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e5c10e",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e5c10f",
      "instruction": "MOV ECX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e5c115",
      "instruction": "CALL 0x00697af0"
    },
    {
      "address": "00e5c11a",
      "instruction": "CALL 0x0067dd10"
    },
    {
      "address": "00e5c11f",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00e5c121",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e5c123",
      "instruction": "MOV EAX,dword ptr [EDX + 0x58]"
    },
    {
      "address": "00e5c126",
      "instruction": "CALL EAX"
    },
    {
      "address": "00e5c128",
      "instruction": "LEA ECX,[ESP]"
    },
    {
      "address": "00e5c12b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e5c12c",
      "instruction": "LEA EDX,[ESP + 0x10]"
    },
    {
      "address": "00e5c130",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e5c131",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00e5c133",
      "instruction": "CALL 0x007c4900"
    },
    {
      "address": "00e5c138",
      "instruction": "FLD float ptr [0x014851e8]"
    },
    {
      "address": "00e5c13e",
      "instruction": "MOV EAX,[0x016b3c0c]"
    },
    {
      "address": "00e5c143",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e5c144",
      "instruction": "FSTP float ptr [ESP]"
    },
    {
      "address": "00e5c147",
      "instruction": "PUSH 0x200"
    },
    {
      "address": "00e5c14c",
      "instruction": "ADD EAX,0x100"
    },
    {
      "address": "00e5c151",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00e5c152",
      "instruction": "MOV EAX,[0x016b3c04]"
    },
    {
      "address": "00e5c157",
      "instruction": "LEA ECX,[ESP + 0xc]"
    },
    {
      "address": "00e5c15b",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e5c15c",
      "instruction": "MOV ECX,dword ptr [EAX + 0x40fc]"
    },
    {
      "address": "00e5c162",
      "instruction": "LEA EDX,[ESP + 0x1c]"
    },
    {
      "address": "00e5c166",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00e5c167",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00e5c168",
      "instruction": "CALL 0x00e87200"
    },
    {
      "address": "00e5c16d",
      "instruction": "MOV EDX,dword ptr [0x016b3c0c]"
    },
    {
      "address": "00e5c173",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00e5c176",
      "instruction": "MOV dword ptr [EDX + 0x900],EAX"
    },
    {
      "address": "00e5c17c",
      "instruction": "MOV EAX,[0x016b3c0c]"
    },
    {
      "address": "00e5c181",
      "instruction": "MOVSS dword ptr [EAX + 0x904],XMM0"
    },
    {
      "address": "00e5c189",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00e5c18b",
      "instruction": "ADD ESP,0x30"
    },
    {
      "address": "00e5c18e",
      "instruction": "RET 0x10"
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
  "original_bytes": 10208,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_receiver\": \"ECX App::cCellModeStrategy*\",\n    \"ordinary_stack_arguments\": [\n      {\n        \"evidence\": \"captured into ECX by MOV ECX,[ESP+0x4] at 0x00e5c0f8 and pushed as the first forwarded word; the body performs no further use of the word after the forward\",\n        \"name\": \"mouseButton\",\n        \"offset\": \"ESP+4\",\n        \"slot\": 0,\n        \"type\": \"int32\"\n      },\n      {\n        \"evidence\": \"loaded by FLD float ptr [ESP+0x2c] at 0x00e5c107 into the forwarded word at 0x00e5c10b\",\n        \"name\": \"mouseX\",\n        \"offset\": \"ESP+8\",\n        \"slot\": 1,\n        \"type\": \"raw float dword\"\n      },\n      {\n        \"evidence\": \"loaded by FLD float ptr [ESP+0xc] at 0x00e5c0f4 into the forwarded word at 0x00e5c103\",\n        \"name\": \"mouseY\",\n        \"offset\": \"ESP+0xc\",\n        \"slot\": 2,\n        \"type\": \"raw float dword\"\n      },\n      {\n        \"evidence\": \"captured into EAX by MOV EAX,[ESP+0x10] at 0x00e5c0f0 and pushed as the fourth forwarded word at 0x00e5c0ff\",\n        \"name\": \"mouseState\",\n        \"offset\": \"ESP+0x10\",\n        \"slot\": 3,\n        \"type\": \"uint32\",\n        \"width_bytes\": 4\n      }\n    ],\n    \"ret_form\": \"RET 0x10\",\n    \"return_register\": \"AL, set once by MOV AL,0x1 at 0x00e5c189\",\n    \"stack_cleanup_bytes\": 16\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 34,\n      \"symbol\": \"cell_mode_strategy_on_mouse_down_00e6c860\",\n      \"va\": \"0x00e6c860\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy,int32,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE8\",\n      \"score\": 34,\n      \"symbol\": \"cell_mode_strategy_on_mouse_wheel_00e7d660\",\n      \"va\": \"0x00e7d660\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,raw float dword\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 18,\n      \"symbol\": \"cell_mode_strategy_on_mouse_move_00e51010\",\n      \"va\": \"0x00e51010\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:DATA,int32\",\n        \"shared_vtable:vtable:0x01485550\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 18,\n      \"symbol\": \"cell_mode_strategy_on_key_down_00e818f0\",\n      \"va\": \"0x00e818f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_class\",\n        \"shared_types:DATA,OpaqueCellModeStrategy\",\n        \"shared_vtable:vtable:0x01485550\"\n      ],\n      \"package\": \"PKG-APP-LIFECYCLE-WAVE8\",\n      \"score\": 15,\n      \"symbol\": \"app_c_cell_mode_strategy_dispose_00e81f30\",\n      \"va\": \"0x00e81f30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 14,\n      \"symbol\": \"game_input_mouse_up_00697af0\",\n      \"va\": \"0x00697af0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_on_key_down_00697a50\",\n      \"va\": \"0x00697a50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_types:int32\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-GAME-INPUT-WAVE7\",\n      \"score\": 11,\n      \"symbol\": \"game_input_on_key_up_00697a80\",\n      \"va\": \"0x00697a80\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Static mechanics and x86-32 ABI reviewed from live Ghidra; runtime values, concrete owners, and unresolved ports remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"OpaqueCellModeStrategy\",\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": 0.7,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"game_input_mouse_up_00697af0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00697af0\"\n      },\n      {\n        \"name\": \"camera_light_origin_helper_007c4900\",\n        \"reconstructed\": true,\n        \"va\": \"0x007c4900\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e5c11a\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067dd10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5c115\",\n        \"direction\": \"out\",\n        \"other\": \"0x00697af0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5c133\",\n        \"direction\": \"out\",\n        \"other\": \"0x007c4900\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e5c168\",\n        \"direction\": \"out\",\n   
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
  "body_end": "00e5c190",
  "body_span_bytes": 161,
  "body_start": "00e5c0f0",
  "callees": [
    "GameInput_MouseUp",
    "FUN_007c4900",
    "FUN_00e87200",
    "Graphics::IRenderer::Get"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00e5c0f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 2,
  "mode": "live",
  "name": "App::cCellModeStrategy::OnMouseUp",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cCellModeStrategy *"
    },
    {
      "name": "mouseButton",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "MouseButton"
    },
    {
      "name": "mouseX",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "mouseY",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "float"
    },
    {
      "name": "mouseState",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "MouseState"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0xa5c0f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::cCellModeStrategy::OnMouseUp(cCellModeStrategy * this, MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)",
  "size_bytes": 161,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00e5c0f0",
  "vtables": {
    "referenced_by_vtables": [
      "0x01485550"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "01485588"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseUp.c",
  "file": "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__cCellModeStrategy__OnMouseUp.c",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8.hpp",
    "src/reconstruction/pkg_game_input_wave8/game_input_wave8_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave8/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-game-input-wave8/00e5c0f0.json"
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
    "Observe the concrete vtable call shape, the validity of the Cell game and Cell state globals, the 0x00e87200 return value, and the resulting words at Cell state offsets 0x900 and 0x904 in the original Cell mode."
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
  "status": "reconstructed"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "DATA",
  "OpaqueCellModeStrategy",
  "bool in AL, always one",
  "int32",
  "raw float dword",
  "uint32"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01485550",
  "vtable:0x01485588"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00e7c8c0",
      "0x00e7c8c0",
      "0x00e5c0f0",
      "0x00e7c8c0",
      "0x00e6c860"
    ],
    "conflict_id": "U7",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "resolution_status": "The cited direct body establishes a bounded state mutation or call anchor, but the full transition policy, consumer order, and runtime reachability remain unresolved.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00e5c0f0",
      "0x00e6c860",
      "0x00e7d660"
    ],
    "conflict_id": "U9",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
