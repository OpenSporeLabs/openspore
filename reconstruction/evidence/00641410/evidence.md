# Evidence 0x00641410

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b15caeba844c0e73fcc38be6714403a48f1076836326fac44891bce6b187f188`

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
  "ret_form": "RET (no immediate, both sites)",
  "return_register": "EAX",
  "return_type": "std::uint8_t",
  "saved_registers": [
    "ESI"
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
  "content_sha256": "43401389074f4c736746b8957b97f296a8c3236f3ef59fa0ca22026a9d873630",
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
    "indirect_calls": 4,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0014",
        "obs-0016"
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
        "obs-0009"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          38
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0009",
        "obs-0014",
        "obs-0016"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0016"
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
        "obs-0014",
        "obs-0016"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0014",
        "obs-0016"
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
      "at": "0x00641410",
      "count": 9,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00641411",
      "count": 1,
      "first_use": 1,
      "first_write_index": 9,
      "id": "obs-0002",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00641411",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00641413",
      "definite": true,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESI]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00641415",
      "count": 4,
      "first_use": 3,
      "first_write_index": 2,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [EAX + 0x24]",
      "reg": "EAX"
    },
    {
      "at": "0x00641415",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [EAX + 0x24]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00641418",
      "count": 4,
      "first_use": 4,
      "first_write_index": 3,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "CALL EDX",
      "reg": "EDX"
    },
    {
      "at": "0x00641418",
      "base": "EDX",
      "disp": null,
      "id": "obs-0008",
      "index": 4,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00641426",
      "definite": true,
      "id": "obs-0009",
      "index": 9,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,ESI",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00641428",
      "base": "EDX",
      "disp": null,
      "id": "obs-0010",
      "index": 10,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00641438",
      "base": "EDX",
      "disp": null,
      "id": "obs-0011",
      "index": 16,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00641448",
      "base": "EDX",
      "disp": null,
      "id": "obs-0012",
      "index": 22,
      "kind": "CALL_INDIRECT",
      "raw": "CALL EDX",
      "via": "register"
    },
    {
      "at": "0x00641454",
      "id": "obs-0013",
      "index": 26,
      "kind": "REG_RESTORE",
      "raw": "POP ESI",
 
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
  "count": 31,
  "instructions": [
    {
      "address": "00641410",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00641411",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00641413",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00641415",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00641418",
      "instruction": "CALL EDX"
    },
    {
      "address": "0064141a",
      "instruction": "CMP EAX,0xbcd73e89"
    },
    {
      "address": "0064141f",
      "instruction": "JZ 0x00641456"
    },
    {
      "address": "00641421",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00641423",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00641426",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00641428",
      "instruction": "CALL EDX"
    },
    {
      "address": "0064142a",
      "instruction": "CMP EAX,0xb8669ec9"
    },
    {
      "address": "0064142f",
      "instruction": "JZ 0x00641456"
    },
    {
      "address": "00641431",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00641433",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00641436",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00641438",
      "instruction": "CALL EDX"
    },
    {
      "address": "0064143a",
      "instruction": "CMP EAX,0x37148141"
    },
    {
      "address": "0064143f",
      "instruction": "JZ 0x00641456"
    },
    {
      "address": "00641441",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00641443",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00641446",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00641448",
      "instruction": "CALL EDX"
    },
    {
      "address": "0064144a",
      "instruction": "CMP EAX,0x4f684a4"
    },
    {
      "address": "0064144f",
      "instruction": "JZ 0x00641456"
    },
    {
      "address": "00641451",
      "instruction": "MOV AL,byte ptr [ESI + 0x26]"
    },
    {
      "address": "00641454",
      "instruction": "POP ESI"
    },
    {
      "address": "00641455",
      "instruction": "RET"
    },
    {
      "address": "00641456",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "00641458",
      "instruction": "POP ESI"
    },
    {
      "address": "00641459",
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
  "original_bytes": 12568,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET (no immediate, both sites)\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"std::uint8_t\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_IsEditable_00641400\",\n      \"va\": \"0x00641400\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func7ch_00641460\",\n      \"va\": \"0x00641460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770\",\n      \"va\": \"0x00641770\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_func3ch_006417b0\",\n      \"va\": \"0x006417b0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-16-SPOREPEDIA-ONLINE\",\n      \"score\": 4,\n      \"symbol\": \"Sporepedia_cSPAssetDataOTDB_GetAssetID_address_006417c0\",\n      \"va\": \"0x006417c0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_name_00641810\",\n      \"va\": \"0x00641810\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_author_id_00641820\",\n      \"va\": \"0x00641820\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013ff648,vtable:0x01462764\"\n      ],\n      \"package\": \"PKG-SPOREPEDIA-ACCESSORS-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"sporepedia_get_tags_00641850\",\n      \"va\": \"0x00641850\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"CONSTANTS provenance: the four literals are unresolved identities. The three-hash sweep in mechanics.literal_search is an absence of evidence and is recorded as such; naming them would require the original type tables or a trace.\",\n    \"EVIDENCE COVERAGE (WARN, real and not fixable from this package): DECOMPILATION is reported unavailable for this VA. For a 31-instruction body with four indirect calls and no direct callee a decompilation would add nothing that the instruction bytes do not already fix, but the category is genuinely absent and is reported rather than glossed.\",\n    \"VIRTUAL DISPATCH provenance: identifying the callee needs the run-time dispatch word, not more analysis of this body. The six candidate tables are recorded in mechanics.vtable_installations and their slot-9 contents already disagree with each other, so this is not a gap in the analysis but a fact about the class hierarchy.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"sporepedia-online\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0152\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:none. No instruction in the body names a data-segment address.\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00641410\",\n  \"normalized_symbol\": \"FUN_00641410\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"runtime_gated_requires_explicit_gate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"A trace records the dispatch word at each of 0x00641413 / 0x00641421 / 0x00641431 / 0x00641441, the slot-9 target loaded at each of the four following instructions, and the full 32-bit EAX each callee returns.\",\n      \"An object whose dispatch word points at one of the six tables listed in mechanics.vtable_installations is constructed and FUN_00641410 is entered.\",\n      \"The trace confirms or refutes that the four literals ever occur in practice, and if so with which receiver class -- this is the only way to name them.\",\n      \"The trace shows a second call site whose use of the result (mask, compare, forward) would settle the bool-versus-raw-byte question in the unresolved list.\",\n      \"The trace shows whether the dispatch word
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
  "body_end": "00641459",
  "body_span_bytes": 74,
  "body_start": "00641410",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00641410",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00641410",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x241410",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00641410(void)",
  "size_bytes": 74,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00641410",
  "vtables": {
    "referenced_by_vtables": [
      "0x013ff648",
      "0x01462764",
      "0x0147c9e8",
      "0x0147ca30",
      "0x0147caf8",
      "0x0147cbbc",
      "0x014893b0"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "013ff6a8"
    },
    {
      "from": "014627b8"
    },
    {
      "from": "0147ca58"
    },
    {
      "from": "0147cb20"
    },
    {
      "from": "0147cc10"
    },
    {
      "from": "01489410"
    },
    {
      "from": "00ec3b9c"
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
  "global:none. No instruction in the body names a data-segment address."
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00641410/00641410.json"
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
    "A trace records the dispatch word at each of 0x00641413 / 0x00641421 / 0x00641431 / 0x00641441, the slot-9 target loaded at each of the four following instructions, and the full 32-bit EAX each callee returns.",
    "An object whose dispatch word points at one of the six tables listed in mechanics.vtable_installations is constructed and FUN_00641410 is entered.",
    "The trace confirms or refutes that the four literals ever occur in practice, and if so with which receiver class -- this is the only way to name them.",
    "The trace shows a second call site whose use of the result (mask, compare, forward) would settle the bool-versus-raw-byte question in the unresolved list.",
    "The trace shows whether the dispatch word ever differs between two consecutive reads; if it never does, the three re-reads are confirmed redundant on every observed path and this package's D3 case remains a synthetic refutation only.",
    "not_required_for_the_structural_claims_but_unavailable"
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
  "PKG_SWARM_W1_00641410_THISCALL",
  "openspore::reconstruction::pkg_swarm_w1_00641410::AssetData",
  "openspore::reconstruction::pkg_swarm_w1_00641410::SlotFn",
  "openspore::reconstruction::pkg_swarm_w1_00641410::Vtable",
  "openspore::reconstruction::pkg_swarm_w1_00641410::byte_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::dispatch_target_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::kReceiverDispatchWordDisplacement",
  "openspore::reconstruction::pkg_swarm_w1_00641410::kReceiverResultByteDisplacement",
  "openspore::reconstruction::pkg_swarm_w1_00641410::kSlotDispatchedByteDisplacement",
  "openspore::reconstruction::pkg_swarm_w1_00641410::model_returned_eax",
  "openspore::reconstruction::pkg_swarm_w1_00641410::slot_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::slot_word_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::store_byte_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::store_pointer_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::store_slot_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::store_word_at",
  "openspore::reconstruction::pkg_swarm_w1_00641410::word_at",
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
  "vtable:0x01462764",
  "vtable:0x0147c9e8",
  "vtable:0x0147ca30",
  "vtable:0x0147caf8",
  "vtable:0x0147cbbc",
  "vtable:0x014893b0"
]
```

## Conflicts

```json
[]
```
