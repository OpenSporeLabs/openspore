# Evidence 0x00c982a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8ecd72a18ca092cdd177ed1da5e73e97d1fbc89eda76fe77e0c81146280b31ca`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "thiscall",
  "hidden_this_register": "ECX",
  "hidden_this_type": "Tribe*",
  "ordinary_stack_arguments": [],
  "return_note": "incoming receiver returned unchanged",
  "return_register": "EAX",
  "return_type": "Tribe*",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "termination": "plain RET"
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -12, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "ac766f72306bb4fbb5244d65c19927af90b9a1962a8706d4dc86620f84e42e7c",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall",
      "__fastcall"
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
        "obs-0043",
        "obs-0048"
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
        "obs-0009",
        "obs-0032"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          4,
          52,
          560,
          608,
          612,
          616,
          620,
          656,
          660,
          664,
          668,
          680,
          684,
          688,
          700,
          704,
          708,
          712,
          716,
          720,
          724,
          728,
          768,
          769,
          772,
          776,
          780,
          784,
          788,
          792,
          796,
          808,
          816,
          820,
          824,
          828,
          832,
          836,
          840,
          852,
          856,
          860,
          872,
          876,
          880,
          884,
          896,
          900,
          904,
          920,
          924,
          928,
          932,
          936,
          940,
          1048,
          1052,
          1056,
          1068,
          1256,
          1260,
          1264,
          1268,
          1272,
          1276,
          1360,
          1364,
          1365,
          1366,
          1367,
          6248,
          6252,
          6256,
          6260,
          6264,
          6265,
          6272,
          6276,
          6280,
          6284,
          6288,
          6289,
          6296,
          6300,
          6304,
          6308,
          6312,
          6313,
          6320,
          6324,
          6328,
          6332,
          6336,
          6337,
          6344,
          6596,
          6600,
          6604,
          6608,
          6612,
          6616
        ],
        "register": "ECX",
        "written_through": 105
      }
    },
    {
      "based_on": [
        "obs-0006",
        "obs-0007",
        "obs-0009",
        "obs-0032",
        "obs-0043",
        "obs-0048"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0043",
        "obs-0048"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "at": "0x00c982a0",
      "count": 83,
      "first_use": 0,
      "first_write_index": 20,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00c982a1",
      "count": 9,
      "first_use": 1,
      "first_write_index": 84,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00c982a1",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0003",
      "index": 1,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 1,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00c982a2",
      "count": 122,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 201,
  "instructions": [
    {
      "address": "00c982a0",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00c982a1",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00c982a2",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00c982a3",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00c982a4",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00c982a6",
      "instruction": "CALL 0x00c011c0"
    },
    {
      "address": "00c982ab",
      "instruction": "LEA EDI,[ESI + 0x120]"
    },
    {
      "address": "00c982b1",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00c982b3",
      "instruction": "CALL 0x00c89630"
    },
    {
      "address": "00c982b8",
      "instruction": "LEA EBX,[ESI + 0x1f4]"
    },
    {
      "address": "00c982be",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00c982c0",
      "instruction": "CALL 0x00ac03d0"
    },
    {
      "address": "00c982c5",
      "instruction": "LEA EBP,[ESI + 0x20c]"
    },
    {
      "address": "00c982cb",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "00c982cd",
      "instruction": "CALL 0x00cee630"
    },
    {
      "address": "00c982d2",
      "instruction": "LEA ECX,[ESI + 0x230]"
    },
    {
      "address": "00c982d8",
      "instruction": "CALL 0x00b6f280"
    },
    {
      "address": "00c982dd",
      "instruction": "MOVSS XMM0,dword ptr [0x01473c70]"
    },
    {
      "address": "00c982e5",
      "instruction": "MOV dword ptr [EBX],0x1473d64"
    },
    {
      "address": "00c982eb",
      "instruction": "MOV dword ptr [EDI],0x1473d80"
    },
    {
      "address": "00c982f1",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00c982f3",
      "instruction": "MOV dword ptr [ESI],0x1473e58"
    },
    {
      "address": "00c982f9",
      "instruction": "MOV dword ptr [ESI + 0x4],0x1473e44"
    },
    {
      "address": "00c98300",
      "instruction": "MOV dword ptr [ESI + 0x34],0x1469cc0"
    },
    {
      "address": "00c98307",
      "instruction": "MOV dword ptr [EBP],0x1473d20"
    },
    {
      "address": "00c9830e",
      "instruction": "MOV dword ptr [ESI + 0x230],0x1473d00"
    },
    {
      "address": "00c98318",
      "instruction": "MOV dword ptr [ESI + 0x260],EBX"
    },
    {
      "address": "00c9831e",
      "instruction": "OR EDI,0xffffffff"
    },
    {
      "address": "00c98321",
      "instruction": "LEA ECX,[ESI + 0x270]"
    },
    {
      "address": "00c98327",
      "instruction": "MOV byte ptr [ESI + 0x264],BL"
    },
    {
      "address": "00c9832d",
      "instruction": "MOVSS dword ptr [ESI + 0x268],XMM0"
    },
    {
      "address": "00c98335",
      "instruction": "MOV dword ptr [ESI + 0x26c],EDI"
    },
    {
      "address": "00c9833b",
      "instruction": "CALL 0x00b63890"
    },
    {
      "address": "00c98340",
      "instruction": "MOV dword ptr [ESI + 0x290],EBX"
    },
    {
      "address": "00c98346",
      "instruction": "MOV dword ptr [ESI + 0x294],EBX"
    },
    {
      "address": "00c9834c",
      "instruction": "MOV dword ptr [ESI + 0x298],EBX"
    },
    {
      "address": "00c98352",
      "instruction": "MOV dword ptr [ESI + 0x29c],EBX"
    },
    {
      "address": "00c98358",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00c9835b",
      "instruction": "MOV dword ptr [ESI + 0x2a8],EBX"
    },
    {
      "address": "00c98361",
      "instruction": "MOV dword ptr [ESI + 0x2ac],EBX"
    },
    {
      "address": "00c98367",
      "instruction": "MOV dword ptr [ESI + 0x2b0],EBX"
    },
    {
      "address": "00c9836d",
      "instruction": "MOVSS dword ptr [ESI + 0x2c0],XMM0"
    },
    {
      "address": "00c98375",
      "instruction": "MOVSS dword ptr [ESI + 0x2c4],XMM0"
    },
    {
      "address": "00c9837d",
      "instruction": "MOVSS dword ptr [ESI + 0x2c8],XMM0"
    },
    {
      "address": "00c98385",
      "instruction": "MOVSS dword ptr [ESI + 0x2cc],XMM0"
    },
    {
      "address": "00c9838d",
      "instruction": "MOV dword ptr [ESI + 0x2bc],EDI"
    },
    {
      "address": "00c98393",
      "instruction": "MOV dword ptr [ESI + 0x2d0],EBX"
    },
    {
      "address": "00c98399",
      "instruction": "MOV dword ptr [ESI + 0x2d4],EBX"
    },
    {
      "address": "00c9839f",
      "instruction": "MOV dword ptr [ESI + 0x2d8],EBX"
    },
    {
      "address": "00c983a5",
      "instruction": "MOV byte ptr [ESI + 0x300],BL"
    },
    {
      "address": "00c983ab",
      "instruction": "MOV byte ptr [ESI + 0x301],BL"
    },
    {
      "address": "00c983b1",
      "instruction": "MOVSS XMM1,dword ptr [0x01695374]"
    },
    {
      "address": "00c983b9",
      "instruction": "MOVSS dword ptr [ESI + 0x304],XMM1"
    },
    {
      "address": "00c983c1",
      "instruction": "MOVSS XMM1,dword ptr [0x01695378]"
    },
    {
      "address": "00c983c9",
      "instruction": "MOVSS dword ptr [ESI + 0x308],XMM1"
    },
    {
      "address": "00c983d1",
      "instruction": "MOVSS XMM1,dword ptr [0x0169537c]"
    },
    {
      "address": "00c983d9",
      "instruction": "MOVSS dword ptr [ESI + 0x30c],XMM1"
    },
    {
      "address": "00c983e1",
      "instruction": "MOVSS dword ptr [ESI + 0x310],XMM0"
    },
    {
      "address": "00c983e9",
      "instruction": "MOVSS XMM0,dword ptr [0x014853bc]"
    },
    {
      "address": "00c983f1",
      "instruction": "MOV dword ptr [ESI + 0x314],EBX"
    },
    {
      "address": "00c983f7",
      "instruction": "MOV dword ptr [ESI + 0x318],EBX"
    },
    {
      "address": "00c983fd",
      "instruction": "MOV dword ptr [ESI + 0x31c],EBX"
    },
    {
      "address": "00c98403",
      "instruction": "MOVSS dword ptr [ESI + 0x330],XMM0"
    },
    {
      "address": "00c9840b",
      "instruction": "MOVSS XMM0,dword ptr [0x01485720]"
    },
    {
      "address": "00c98413",
      "instruction": "MOV dword ptr [ESI + 0
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
  "original_bytes": 9807,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"thiscall\",\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"Tribe*\",\n    \"ordinary_stack_arguments\": [],\n    \"return_note\": \"incoming receiver returned unchanged\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Tribe*\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"termination\": \"plain RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-C3-TRIBE-CIV-WAVE2\",\n      \"score\": 10,\n      \"symbol\": \"city_add_building_00be1fb0\",\n      \"va\": \"0x00be1fb0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-13-SIM-CREATURE-TRIBECIV\",\n      \"score\": 8,\n      \"symbol\": \"TribeState_test_purchased_tool_bit_00c8ec00\",\n      \"va\": \"0x00c8ec00\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_SetTargetPosition_0059b0f0\",\n      \"va\": \"0x0059b0f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorCreatureController_Update_0059b4b0\",\n      \"va\": \"0x0059b4b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_GetCreatureController_0059cac0\",\n      \"va\": \"0x0059cac0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_PlayAnimation_0059cb10\",\n      \"va\": \"0x0059cb10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetAngle_0059cea0\",\n      \"va\": \"0x0059cea0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-RUNTIME-WAVE7\",\n      \"score\": 2,\n      \"symbol\": \"EditorAnimWorld_SetTargetPosition_0059cf00\",\n      \"va\": \"0x0059cf00\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and ABI are canonical; runtime values, ownership, concrete types, and opaque port behavior remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"Tribe\",\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00c9864a\",\n        \"direction\": \"out\",\n        \"other\": \"0x004548d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c982c0\",\n        \"direction\": \"out\",\n        \"other\": \"0x00ac03d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c984bc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00afba10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c9833b\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b63890\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c98528\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b63890\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c98533\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b63890\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c982d8\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b6f280\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c9866c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc3170\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c98673\",\n        \"direction\": \"out\",\n        \"other\": \"0x00bc3170\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c982a6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c011c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c982b3\",\n        \"direction\": \"out\",\n        \"other\": \"0x00c89630\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c9855c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00cc7e10\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c982cd\",\n        \"direction\": \"out\",\n        \"other\": \"0x00cee630\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c98683\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c98691\",\n        \"direction\": \"out\",\n        \"other\": \"0x01062ee0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c9863e\",\n        \"direction\": \"out\",\n        \"other\": \"0x01
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
  "body_end": "00c986af",
  "body_span_bytes": 1040,
  "body_start": "00c982a0",
  "callees": [
    "memset",
    "FUN_00c89630",
    "FUN_00cee630",
    "FUN_00cc7e10",
    "FUN_00c011c0",
    "FUN_00afba10",
    "FUN_01062ee0",
    "FUN_00f473a0",
    "FUN_00ac03d0",
    "FUN_00b6f280",
    "FUN_004548d0",
    "FUN_00b63890",
    "FUN_00bc3170"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00c982a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c982a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8982a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c982a0(void)",
  "size_bytes": 1040,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c982a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00b1f1f0"
    }
  ]
}
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:0x01485720"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
  "files": [
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.hpp",
    "src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave2/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg13-c3-tribe-civ-wave2/00c982a0.json"
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
    "gate-tribe-constructor-00c982a0",
    "runtime validation not run"
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
  "Tribe",
  "Tribe*",
  "Tribe* incoming receiver returned unchanged"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01473e58"
]
```

## Conflicts

```json
[]
```
