# Evidence 0x004df420

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c287a69a4d1c461bbdde2e5f48fb3fb9d9e3c95f9858f16d0ecac425a6198bad`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": [],
  "ordinary_stack_arguments": [],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": [
    "The last write to EAX before the call is the ADD EAX,0xa4 argument computation, which the call then overwrites. 0x004df550 ends with MOV EAX,[EBP-0x4] / MOV ESP,EBP / POP EBP / RET 0x4, so the callee does produce that dword. Across the 58 direct call sites the value is consumed at 50 of them by the immediately following instruction and at 7 more within the following instructions; at 0x00d5d074 no use of EAX follows on the traced path. Two sites dereference the value behind a TEST EAX,EAX null guard, 0x00c02734 reading [EAX + 0x5b0] and 0x00aec396 reading [EAX + 0x51c], which is consistent w...",
    "The last write to EAX before the call is the ADD EAX,0xa4 argument computation, which the call then overwrites. No instruction after 0x004df433 writes EAX, so the callee's dword is what leaves the frame. 0x004df550 ends with MOV EAX,[EBP-0x4] / MOV ESP,EBP / POP EBP / RET 0x4, so the callee does produce that dword. Across the 58 direct call sites the value is consumed at 50 of them by the immediately following instruction and at 7 more within the following instructions; at 0x00d5d074 no use of EAX follows on the traced path. Two sites dereference the value, 0x00c02734 reading [EAX + 0x5b0] ..."
  ],
  "return_register": "EAX",
  "return_semantics": "a 4-byte opaque word in EAX, produced by 0x004df550 and forwarded unmodified; the body writes no instruction to EAX after the call",
  "return_type": "OpaqueWord",
  "return_width_bytes": 4,
  "saved_registers": [
    "EBP only; pushed at 0x004df420 and popped at 0x004df43a. No other callee-saved register is pushed or written.",
    "EBP only; it is pushed at 0x004df420 and popped at 0x004df43a. No other callee-saved register is pushed or written."
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
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
    "receiver_not_determinable: ecx_read_without_deref",
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "93bd56fe46b9d16c69f1e6feda3d1cad2cbdc818c987b207ae88b87c8f9fbf97",
  "conventions": {
    "ambiguities": [],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl",
      "__stdcall",
      "__thiscall",
      "__fastcall"
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0015"
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
        "obs-0006",
        "obs-0010",
        "obs-0011"
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
        "obs-0015"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0015"
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
        "obs-0015"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0015"
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
      "at": "0x004df420",
      "count": 5,
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
      "at": "0x004df420",
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
      "at": "0x004df421",
      "count": 1,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EBP,ESP",
      "reg": "ESP"
    },
    {
      "at": "0x004df421",
      "definite": true,
      "id": "obs-0004",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EBP,ESP",
      "reg": "EBP",
      "write_kind": "reg"
    },
    {
      "at": "0x004df423",
      "count": 2,
      "first_use": 2,
      "first_write_index": 7,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ECX",
      "reg": "ECX"
    },
    {
      "at": "0x004df424",
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
      "at": "0x004df427",
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
      "at": "0x004df427",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EBP + -0x4]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004df42f",
      "count": 1,
      "first_use": 6,
      "first_write_index": 4,
      "id": "obs-0009",
      "index": 6,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x004df430",
      "base": "EBP",
      "disp": -4,
      "id": "obs-0010",
      "index": 7,
      "key": null,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV ECX,dword ptr [EBP + -0x4]",
      "reason": "local",
      "resolved": false,
      "size": 4
    },
    {
      "at": "0x004df430",
      "definite": true,
      "id": "obs-0011",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,dword ptr [EBP + -0x4]",
      "reg": "ECX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x004df433",
      "id": "obs-0012",
      "index": 8,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x004df550",
      "target": "0x004df550"
    },
    {
      "at": "0x004df438",
      "definite": true,
      "id": "obs-0013",
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
    "va": "0x004d2200"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b5ba30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6baf0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b6ca10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b99420"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b99ed0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b9aa10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba3860"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c02710"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c04010"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c042e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c099e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c09fa0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0c2d0"
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
      "0x004d3dd0",
      "0x004df6d0",
      "0x004e0560",
      "0x00f473a0",
      "0x004df440",
      "0x004d3dd0",
      "0x004df440",
      "0x004d3dd0",
      "0x004df550",
      "0x004d3dd0",
      "0x004df440",
      "0x004df550",
      "0x004df420",
      "0x00c8a5b0",
      "0x004df440",
      "0x004df550"
    ],
    "conflict_id": "FL-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "cSpeciesProfile runtime size",
    "unresolved_reason": "Cache eviction, transfer, destructor, and manager ownership remain unresolved; the object-size conflict is resolved."
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
  "count": 12,
  "instructions": [
    {
      "address": "004df420",
      "instruction": "PUSH EBP"
    },
    {
      "address": "004df421",
      "instruction": "MOV EBP,ESP"
    },
    {
      "address": "004df423",
      "instruction": "PUSH ECX"
    },
    {
      "address": "004df424",
      "instruction": "MOV dword ptr [EBP + -0x4],ECX"
    },
    {
      "address": "004df427",
      "instruction": "MOV EAX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004df42a",
      "instruction": "ADD EAX,0xa4"
    },
    {
      "address": "004df42f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "004df430",
      "instruction": "MOV ECX,dword ptr [EBP + -0x4]"
    },
    {
      "address": "004df433",
      "instruction": "CALL 0x004df550"
    },
    {
      "address": "004df438",
      "instruction": "MOV ESP,EBP"
    },
    {
      "address": "004df43a",
      "instruction": "POP EBP"
    },
    {
      "address": "004df43b",
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
  "original_bytes": 25995,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": [],\n    \"ordinary_stack_arguments\": [],\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_observation\": [\n      \"The last write to EAX before the call is the ADD EAX,0xa4 argument computation, which the call then overwrites. 0x004df550 ends with MOV EAX,[EBP-0x4] / MOV ESP,EBP / POP EBP / RET 0x4, so the callee does produce that dword. Across the 58 direct call sites the value is consumed at 50 of them by the immediately following instruction and at 7 more within the following instructions; at 0x00d5d074 no use of EAX follows on the traced path. Two sites dereference the value behind a TEST EAX,EAX null guard, 0x00c02734 reading [EAX + 0x5b0] and 0x00aec396 reading [EAX + 0x51c], which is consistent w...\",\n      \"The last write to EAX before the call is the ADD EAX,0xa4 argument computation, which the call then overwrites. No instruction after 0x004df433 writes EAX, so the callee's dword is what leaves the frame. 0x004df550 ends with MOV EAX,[EBP-0x4] / MOV ESP,EBP / POP EBP / RET 0x4, so the callee does produce that dword. Across the 58 direct call sites the value is consumed at 50 of them by the immediately following instruction and at 7 more within the following instructions; at 0x00d5d074 no use of EAX follows on the traced path. Two sites dereference the value, 0x00c02734 reading [EAX + 0x5b0] ...\"\n    ],\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"a 4-byte opaque word in EAX, produced by 0x004df550 and forwarded unmodified; the body writes no instruction to EAX after the call\",\n    \"return_type\": \"OpaqueWord\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [\n      \"EBP only; pushed at 0x004df420 and popped at 0x004df43a. No other callee-saved register is pushed or written.\",\n      \"EBP only; it is pushed at 0x004df420 and popped at 0x004df43a. No other callee-saved register is pushed or written.\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005f9230\",\n      \"va\": \"0x005f9230\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005f9310\",\n      \"va\": \"0x005f9310\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fc330\",\n      \"va\": \"0x005fc330\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-PERSISTENCE-BOUNDARY\",\n      \"score\": 5,\n      \"symbol\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n      \"va\": \"0x00b28ec0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"re_00575ea0\",\n      \"va\": \"0x00575ea0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:OpaqueWord\"\n      ],\n      \"package\": \"PKG-APP-CANVAS-WAVE6\",\n      \"score\": 3,\n      \"symbol\": \"app_canvas_00847a40\",\n      \"va\": \"0x00847a40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004d2200\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b5ba30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6baf0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b6ca10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b99420\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b99ed0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b9aa10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba3860\"\n      },\n      {\n        \"name\"
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
  "body_end": "004df43b",
  "body_span_bytes": 28,
  "body_start": "004df420",
  "callees": [
    "FUN_004df550"
  ],
  "callers": [
    "FUN_00b99ed0",
    "FUN_00cfb890",
    "FUN_00b5ba30",
    "FUN_00d5c720",
    "FUN_004d2200",
    "FUN_00d1e830",
    "FUN_00e434a0",
    "FUN_00c04010",
    "FUN_00b6baf0",
    "FUN_00deb770",
    "FUN_00b6ca10",
    "FUN_00d5fb60",
    "FUN_00c93160",
    "FUN_00cde660",
    "FUN_00d40cc0",
    "FUN_00c6cf10",
    "FUN_00b9aa10",
    "FUN_00c099e0",
    "FUN_00cfbc10",
    "FUN_00dd15a0",
    "FUN_00c02710",
    "FUN_00d425f0",
    "FUN_00c0c2d0",
    "FUN_00deb930",
    "FUN_00cc8a30",
    "FUN_00fe0160",
    "FUN_00c69f80",
    "FUN_00c932a0",
    "FUN_00ff9100",
    "FUN_00c042e0",
    "FUN_00cd5f70",
    "FUN_00aebe90",
    "FUN_00c09fa0",
    "FUN_00b28ec0",
    "FUN_00d39dc0",
    "FUN_00d87620",
    "FUN_00ba3860",
    "FUN_00c6d7c0",
    "FUN_00d5cfd0",
    "FUN_00b99420",
    "FUN_00c222f0",
    "FUN_00d5bfa0",
    "FUN_00d40b40",
    "Simulator::cCreatureGameData::CalculateAvatarNormalizingScale",
    "FUN_00c6e4f0",
    "FUN_00e8df50",
    "FUN_00c6aa50",
    "FUN_00d5ccf0",
    "FUN_00d40230",
    "FUN_00d43e30",
    "FUN_00c99dc0",
    "FUN_00cc5bc0",
    "FUN_00cd8e70"
  ],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "004df420",
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
  "name": "FUN_004df420",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0xdf420",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_004df420(void)",
  "size_bytes": 28,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x004df420",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 64,
  "xrefs": [
    {
      "from": "00b28f57"
    },
    {
      "from": "004d2239"
    },
    {
      "from": "004d2366"
    },
    {
      "from": "00d5c005"
    },
    {
      "from": "00c22368"
    },
    {
      "from": "00d5c773"
    },
    {
      "from": "00cc8a50"
    },
    {
      "from": "00d5cd0d"
    },
    {
      "from": "00d6087b"
    },
    {
      "from": "00c0a74d"
    },
    {
      "from": "00c0ab0e"
    },
    {
      "from": "00c04548"
    },
    {
      "from": "00c69f8b"
    },
    {
      "from": "00c09aa9"
    },
    {
      "from": "00c0272b"
    },
    {
      "from": "00aec385"
    },
    {
      "from": "00dd15da"
    },
    {
      "from": "00b6bd95"
    },
    {
      "from": "00d40ba8"
    },
    {
      "from": "00c93173"
    },
    {
      "from": "00b9942c"
    },
    {
      "from": "00b9a296"
    },
    {
      "from": "00b9aa38"
    },
    {
      "from": "00c04060"
    },
    {
      "from": "00c6aa61"
    },
    {
      "from": "00c0c2da"
    },
    {
      "from": "00c932c3"
    },
    {
      "from": "00c6d922"
    },
    {
      "from": "00c6e513"
    },
    {
      "from": "00c6e6e9"
    },
    {
      "from": "00cc5bcd"
    },
    {
      "from": "00cd5f7e"
    },
    {
      "from": "00cd8e8b"
    },
    {
      "from": "00d1e8b1"
    },
    {
      "from": "00c99dd5"
    },
    {
      "from": "00d39f0a"
    },
    {
      "from": "00d2e73b"
    },
    {
      "from": "00d40403"
    },
    {
      "from": "00d40ce1"
    },
    {
      "from": "00c6d087"
    },
    {
      "from": "00d5d074"
    },
    {
      "from": "00debb8a"
    },
    {
      "from": "00deb81d"
    },
    {
      "from": "00e43501"
    },
    {
      "from": "00e8df88"
    },
    {
      "from": "00fe0275"
    },
    {
      "from": "00ff9115"
    },
    {
      "from": "00b6cb07"
    },
    {
      "from": "00ba3959"
    },
    {
      "from": "00cfb89e"
    },
    {
      "from": "00cfcd33"
    },
    {
      "from": "00d44523"
    },
    {
      "from": "00d447a9"
    },
    {
      "from": "00d4514f"
    },
    {
      "from": "00cde9ad"
    },
    {
      "from": "00d87b86"
    },
    {
      "from": "00b5baa0"
    },
    {
      "from": "00c04afb"
    },
    {
      "from": "00cc634f"
    },
    {
      "from": "00ce68c3"
    },
    {
      "from": "00d1d433"
    },
    {
      "from": "00d43bc8"
    },
    {
      "from": "00d45aeb"
    },
    {
      "from": "00d42816"
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
    "reconstruction/staging/pkg-dogfood-004df420-a1/.clang-format",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.cpp",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.hpp",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1_boundary_test.sh",
    "reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1_model_test.cpp",
    "reconstruction/staging/pkg-dogfood-004df420-a1/ownership.json",
    "reconstruction/staging/pkg-editor-species-default-wave12/.clang-format",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12.cpp",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12.hpp",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12_boundary_test.sh",
    "reconstruction/staging/pkg-editor-species-default-wave12/editor_species_default_wave12_model_test.cpp",
    "reconstruction/staging/pkg-editor-species-default-wave12/ownership.json"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-004df420-a1/004df420.json",
    "reconstruction/metadata/pkg-editor-species-default-wave12/004df420.json"
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
    "No original-process invocation was captured, so no live receiver value, no live argument value and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.",
    "The call sites were counted and classified from a static xref export. Which of them execute in a given play session, and with what receiver and key contents, is a runtime question this repository has no instrument for.",
    "The unreachability result for the callee's key-substitution branch is static. Confirming it as an execution count needs an instrumented run of the original, which was not performed.",
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
  "status": "candidate"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "OpaqueWord"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[
  {
    "anchors": [
      "0x004d3dd0",
      "0x004df6d0",
      "0x004e0560",
      "0x00f473a0",
      "0x004df440",
      "0x004d3dd0",
      "0x004df440",
      "0x004d3dd0",
      "0x004df550",
      "0x004d3dd0",
      "0x004df440",
      "0x004df550",
      "0x004df420",
      "0x00c8a5b0",
      "0x004df440",
      "0x004df550"
    ],
    "conflict_id": "FL-002",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "RESOLVED_OBSERVED",
    "resolution_status": "RESOLVED_OBSERVED",
    "source": "knowledgegraph/research/conflicts/track-a-type-signature.json",
    "subject": "cSpeciesProfile runtime size",
    "unresolved_reason": "Cache eviction, transfer, destructor, and manager ownership remain unresolved; the object-size conflict is resolved."
  }
]
```
