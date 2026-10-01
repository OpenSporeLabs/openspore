# Evidence 0x00641fa0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ddd80a7ac65579f7ff69ad624589f3ea13a9facb5070475cd17318ef7a89107b`

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
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_register": "EAX, and only AL: both terminators write AL explicitly (MOV AL,0x1 at 0x00641fc6, XOR AL,AL at 0x00641fca) and nothing in the 22 writes any other byte of it.",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller (moot: there is no ordinary stack argument to clean, and both terminators are a bare RET with no immediate)",
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
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -4, so the listing is not one path"
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
  "content_sha256": "fc612f66c7073938efc520e82b1ba1ab8948dd271ded42c94e1ae3118cccbb1a",
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
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0013",
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
        "obs-0002",
        "obs-0003",
        "obs-0010"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          28
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0010",
        "obs-0013",
        "obs-0015"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0013",
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
        "obs-0013",
        "obs-0015"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0015"
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
      "at": "0x00641fa0",
      "count": 5,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00641fa1",
      "count": 1,
      "first_use": 1,
      "first_write_index": 12,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00641fa1",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00641fa9",
      "count": 3,
      "first_use": 4,
      "first_write_index": 11,
      "id": "obs-0004",
      "index": 4,
      "kind": "REG_READ",
      "raw": "LEA EAX,[ESI + 0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x00641fad",
      "id": "obs-0005",
      "index": 6,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00641900",
      "target": "0x00641900"
    },
    {
      "at": "0x00641fb2",
      "definite": true,
      "id": "obs-0006",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "ADD ESP,0x4",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00641fb9",
      "definite": true,
      "id": "obs-0007",
      "index": 10,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESI]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00641fbb",
      "count": 1,
      "first_use": 11,
      "first_write_index": 10,
      "id": "obs-0008",
      "index": 11,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [EDX + 0x68]",
      "reg": "EDX"
    },
    {
      "at": "0x00641fbb",
      "definite": true,
      "id": "obs-0009",
      "index": 11,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [EDX + 0x68]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00641fbe",
      "definite": true,
      "id": "obs-0010",
      "index": 12,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00641fc0",
      "base": "EAX",
      "disp": null,
      "id": "obs-0011",
      "index": 13,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EAX",
      "via": "register"
    },
    {
      "at": "0x00641fc8",
      "id": "obs-0012",
      "index": 17,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00641fc9",
      "form": "RET",
      "id": "obs-0013",
      "imm": null,
      "index": 18,
      "kind": "RET",
      "raw": "RET"
    },
    {
      "at": "0x00
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
  "count": 22,
  "instructions": [
    {
      "address": "00641fa0",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00641fa1",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00641fa3",
      "instruction": "CMP dword ptr [ESI + 0x1c],0x0"
    },
    {
      "address": "00641fa7",
      "instruction": "JZ 0x00641fca"
    },
    {
      "address": "00641fa9",
      "instruction": "LEA EAX,[ESI + 0x4]"
    },
    {
      "address": "00641fac",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00641fad",
      "instruction": "CALL 0x00641900"
    },
    {
      "address": "00641fb2",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00641fb5",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00641fb7",
      "instruction": "JZ 0x00641fca"
    },
    {
      "address": "00641fb9",
      "instruction": "MOV EDX,dword ptr [ESI]"
    },
    {
      "address": "00641fbb",
      "instruction": "MOV EAX,dword ptr [EDX + 0x68]"
    },
    {
      "address": "00641fbe",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00641fc0",
      "instruction": "CALL EAX"
    },
    {
      "address": "00641fc2",
      "instruction": "TEST AL,AL"
    },
    {
      "address": "00641fc4",
      "instruction": "JZ 0x00641fca"
    },
    {
      "address": "00641fc6",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "00641fc8",
      "instruction": "POP ESI"
    },
    {
      "address": "00641fc9",
      "instruction": "RET"
    },
    {
      "address": "00641fca",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00641fcc",
      "instruction": "POP ESI"
    },
    {
      "address": "00641fcd",
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
  "original_bytes": 9954,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX, and only AL: both terminators write AL explicitly (MOV AL,0x1 at 0x00641fc6, XOR AL,AL at 0x00641fca) and nothing in the 22 writes any other byte of it.\",\n    \"return_type\": \"std::uint8_t\",\n    \"return_width_bytes\": 1,\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller (moot: there is no ordinary stack argument to clean, and both terminators are a bare RET with no immediate)\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x013ff6ac\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00641fad\",\n        \"direction\": \"out\",\n        \"other\": \"0x00641900\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0167\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS -- none; no instruction names a data-segment address and the record's globals list is empty.\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00641fa0\",\n  \"normalized_symbol\": \"FUN_00641fa0\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_model_test.cpp\",\n      \"reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-swarm-w1-00641fa0/00641fa0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Sporepedia\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"sporepedia-online\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\": \"INFERRED\",\n    \"kg_node_id\": \"fun:00641fa0\",\n    \"name\": \"FUN_00641fa0\",\n    \"priority\": \"P1\",\n    \"provenance\": {\n      \"classifier\": \"triage-v5\",\n      \"sdk_name\": null,\n      \"snapshot\": \"f0e310e0\",\n      \"snapshot_sha256\": \"f0e310e0c83fc960ed38d490ff6d2a78d53925969206b4c4db7a0
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
  "body_end": "00641fcd",
  "body_span_bytes": 46,
  "body_start": "00641fa0",
  "callees": [
    "FUN_00641900"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00641fa0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00641fa0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x241fa0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00641fa0(void)",
  "size_bytes": 46,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00641fa0",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147c9e8",
      "0x0147ca30",
      "0x0147caf8",
      "0x0147cbbc",
      "0x01489090",
      "0x014893b0",
      "0x013ff6ac",
      "0x0147cc14",
      "0x014890f4",
      "0x01489414",
      "0x014627bc"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "013ff6b8"
    },
    {
      "from": "014627c8"
    },
    {
      "from": "0147ca68"
    },
    {
      "from": "0147cb30"
    },
    {
      "from": "0147cc20"
    },
    {
      "from": "01489100"
    },
    {
      "from": "01489420"
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
  "global:PASS -- none; no instruction names a data-segment address and the record's globals list is empty."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00641fa0/00641fa0.json"
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
  "openspore::reconstruction::pkg_swarm_w1_00641fa0::AssetDataSubObject04",
  "openspore::reconstruction::pkg_swarm_w1_00641fa0::DispatchSlot68",
  "openspore::reconstruction::pkg_swarm_w1_00641fa0::DispatchTable",
  "openspore::reconstruction::pkg_swarm_w1_00641fa0::SporepediaAssetDataOtdb",
  "openspore::reconstruction::pkg_swarm_w1_00641fa0::Word",
  "std::uint8_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013ff648",
  "vtable:0x013ff6ac",
  "vtable:0x01462764",
  "vtable:0x014627bc",
  "vtable:0x0147c9e8",
  "vtable:0x0147ca30",
  "vtable:0x0147caf8",
  "vtable:0x0147cbbc",
  "vtable:0x0147cc14",
  "vtable:0x01489090",
  "vtable:0x014890f4",
  "vtable:0x014893b0",
  "vtable:0x01489414"
]
```

## Conflicts

```json
[]
```
