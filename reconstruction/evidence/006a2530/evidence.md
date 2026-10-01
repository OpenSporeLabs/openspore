# Evidence 0x006a2530

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6c2e468b2f0baf6f2811c9e881a09a69677dfbe686e39ddcb86f4e77342fd956`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall (receiver in ECX; the SDK prototype's first parameter is named `this`)",
  "hidden_receiver": "ECX = the parent pointer loaded from receiver+0x30 at 0x006a2577",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x04",
      "observed": true,
      "ordinal": 1,
      "read": true,
      "read_at": "0x006a254b MOV EDX,dword ptr [ESP + 0x1c] (ESP is entry_ESP-0x18 there), re-used as the comparison operand at 0x006a2556 and as the second push at 0x006a2585",
      "role": "propertyID, the 32-bit key searched for; also the &key pointer target handed to the lower-bound helper at 0x006a253f LEA ECX,[ESP + 0x10] which is entry_ESP+0x04",
      "sizes": [
        4
      ],
      "written": false
    },
    {
      "entry_offset": "entry_ESP+0x08",
      "observed": true,
      "ordinal": 2,
      "read": true,
      "read_at": "0x006a2567 MOV ECX,dword ptr [ESP + 0x10] (ESP is entry_ESP-0x08 there) and 0x006a257e MOV ESI,dword ptr [ESP + 0x10] on the parent path",
      "role": "Property** out parameter; receives the ADDRESS of the matched pair's value half (entry+0x04)",
      "sizes": [
        4
      ],
      "written": true,
      "written_at": "0x006a256f MOV dword ptr [ECX],EAX, and only there"
    }
  ],
  "ret_form": "RET 0x8 at all three return sites",
  "return_register": "EAX",
  "return_type": "bool",
  "stack_arguments": [
    "propertyID (pushed first, 0x006a2585)",
    "out pointer (pushed second, 0x006a2584)"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee"
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x8",
      "entry_ESP+0x10"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "saved_registers": [
      "EDI",
      "ESI"
    ],
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x4",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": true,
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
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -8, so the listing is not one path",
    "ret_imm_below_highest_slot: ret 0x8 pops less than the highest read slot 0x10; everything above it belongs to the caller's frame",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x8 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x8 but entry slot 0x10 is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "e77449fce1d436ea854b90fd3d64c30a8470c703b3ee47886d7ff21a7f9197bb",
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
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall (receiver in ECX; the SDK prototype's first parameter is named `this`)"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0019",
        "obs-0024",
        "obs-0027"
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
        "obs-0019",
        "obs-0024",
        "obs-0027"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 8,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0009",
        "obs-0012",
        "obs-0015",
        "obs-0020"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 3,
        "total_bytes": 16
      }
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0003",
        "obs-0008",
        "obs-0009",
        "obs-0015",
        "obs-0016"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28,
          44,
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "the calling convention is unknown: the terminal pop is not a whole number of dword arguments",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0024",
        "obs-0027"
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
        "obs-0019",
        "obs-0024",
        "obs-0027"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0019",
        "obs-0024",
        "obs-0027"
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
      "at": "0x006a2530",
      "count": 6,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
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

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "opaque_list_get_property_006a28c0",
    "reconstructed": true,
    "va": "0x006a28c0"
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
      "0x006a1540",
      "0x006a2f60",
      "0x006a2e20",
      "0x006a2530",
      "0x006a2b80",
      "0x006a2c50",
      "0x00694440",
      "0x006a1540",
      "0x006a1540",
      "0x006a154a",
      "0x006a15f3",
      "0x006a2f60",
      "0x006a2f60",
      "0x006a2f78",
      "0x006a2fe9",
      "0x006a2f60"
    ],
    "conflict_id": "TD-DATA-003",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "competing_hypotheses.1.claim",
        "status": "rejected_for_current_read_write_bodies     ",
        "text": "PropertyList Write serializes the entire recursive parent graph as ordinary local entries."
      }
    ],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
    "subject": "PropertyList local transfer, parent reference, and PROP framing",
    "unresolved_reason": [
      "The exact three-word parent identity and its manager-side construction are not fully identified.",
      "Outer record envelope, version negotiation, compression, and atomic rollback are not established by the selected bodies."
    ]
  },
  {
    "anchors": [
      "0x006a1540",
      "0x006a2f60",
      "0x006a1540",
      "0x013c7d90",
      "0x013c7d90",
      "0x006a1540",
      "0x006a1540",
      "0x006a1540",
      "0x006a1640",
      "0x006a1640",
      "0x006a2530",
      "0x006a2530",
      "0x006a2e20",
      "0x006a2e20",
      "0x006a2f60",
      "0x006a2f60"
    ],
    "conflict_id": "prop_wire_format",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 47,
  "instructions": [
    {
      "address": "006a2530",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2531",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "006a2533",
      "instruction": "MOVZX EAX,byte ptr [ESI + 0x2c]"
    },
    {
      "address": "006a2537",
      "instruction": "MOV EDX,dword ptr [ESI + 0x18]"
    },
    {
      "address": "006a253a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a253b",
      "instruction": "MOV EDI,dword ptr [ESI + 0x1c]"
    },
    {
      "address": "006a253e",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a253f",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "006a2543",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2544",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2545",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a2546",
      "instruction": "CALL 0x00612db0"
    },
    {
      "address": "006a254b",
      "instruction": "MOV EDX,dword ptr [ESP + 0x1c]"
    },
    {
      "address": "006a254f",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a2552",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a2554",
      "instruction": "JZ 0x006a2561"
    },
    {
      "address": "006a2556",
      "instruction": "CMP EDX,dword ptr [EAX]"
    },
    {
      "address": "006a2558",
      "instruction": "JC 0x006a2561"
    },
    {
      "address": "006a255a",
      "instruction": "LEA ECX,[EAX + 0x18]"
    },
    {
      "address": "006a255d",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "006a255f",
      "instruction": "JNZ 0x006a2563"
    },
    {
      "address": "006a2561",
      "instruction": "MOV EAX,EDI"
    },
    {
      "address": "006a2563",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "006a2565",
      "instruction": "JZ 0x006a2577"
    },
    {
      "address": "006a2567",
      "instruction": "MOV ECX,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a256b",
      "instruction": "ADD EAX,0x4"
    },
    {
      "address": "006a256e",
      "instruction": "POP EDI"
    },
    {
      "address": "006a256f",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "006a2571",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "006a2573",
      "instruction": "POP ESI"
    },
    {
      "address": "006a2574",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a2577",
      "instruction": "MOV ECX,dword ptr [ESI + 0x30]"
    },
    {
      "address": "006a257a",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "006a257c",
      "instruction": "JZ 0x006a2590"
    },
    {
      "address": "006a257e",
      "instruction": "MOV ESI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "006a2582",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "006a2584",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2585",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a2586",
      "instruction": "MOV EDX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "006a2589",
      "instruction": "CALL EDX"
    },
    {
      "address": "006a258b",
      "instruction": "POP EDI"
    },
    {
      "address": "006a258c",
      "instruction": "POP ESI"
    },
    {
      "address": "006a258d",
      "instruction": "RET 0x8"
    },
    {
      "address": "006a2590",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2591",
      "instruction": "XOR AL,AL"
    },
    {
      "address": "006a2593",
      "instruction": "POP ESI"
    },
    {
      "address": "006a2594",
      "instruction": "RET 0x8"
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
  "original_bytes": 9554,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall (receiver in ECX; the SDK prototype's first parameter is named `this`)\",\n    \"hidden_receiver\": \"ECX = the parent pointer loaded from receiver+0x30 at 0x006a2577\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"ordinary_stack_arguments\": [\n      {\n        \"entry_offset\": \"entry_ESP+0x04\",\n        \"observed\": true,\n        \"ordinal\": 1,\n        \"read\": true,\n        \"read_at\": \"0x006a254b MOV EDX,dword ptr [ESP + 0x1c] (ESP is entry_ESP-0x18 there), re-used as the comparison operand at 0x006a2556 and as the second push at 0x006a2585\",\n        \"role\": \"propertyID, the 32-bit key searched for; also the &key pointer target handed to the lower-bound helper at 0x006a253f LEA ECX,[ESP + 0x10] which is entry_ESP+0x04\",\n        \"sizes\": [\n          4\n        ],\n        \"written\": false\n      },\n      {\n        \"entry_offset\": \"entry_ESP+0x08\",\n        \"observed\": true,\n        \"ordinal\": 2,\n        \"read\": true,\n        \"read_at\": \"0x006a2567 MOV ECX,dword ptr [ESP + 0x10] (ESP is entry_ESP-0x08 there) and 0x006a257e MOV ESI,dword ptr [ESP + 0x10] on the parent path\",\n        \"role\": \"Property** out parameter; receives the ADDRESS of the matched pair's value half (entry+0x04)\",\n        \"sizes\": [\n          4\n        ],\n        \"written\": true,\n        \"written_at\": \"0x006a256f MOV dword ptr [ECX],EAX, and only there\"\n      }\n    ],\n    \"ret_form\": \"RET 0x8 at all three return sites\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"stack_arguments\": [\n      \"propertyID (pushed first, 0x006a2585)\",\n      \"out pointer (pushed second, 0x006a2584)\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 10,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 10,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 10,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 10,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 4,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 4,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"opaque_list_get_property_006a28c0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a28c0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a28e0\",\n        \"direction\": \"in\",\n        \"other\": \"0x006a28c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2546\",\n        \"direction\": \"out\",\n        \"other\": \"0x00612db0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x006a28c0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0206\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"App::PropertyList::GetProperty\",\n  \"normalized_symbol\": \"App::PropertyList::GetProperty\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blo
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
  "body_end": "006a2596",
  "body_span_bytes": 103,
  "body_start": "006a2530",
  "callees": [
    "FUN_00612db0"
  ],
  "callers": [
    "App::DirectPropertyList::GetProperty"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a2530",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "App::PropertyList::GetProperty",
  "namespace": "App",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "PropertyList *"
    },
    {
      "name": "propertyID",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "uint32_t"
    },
    {
      "name": "result",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Property * *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x2a2530",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool App::PropertyList::GetProperty(PropertyList * this, uint32_t propertyID, Property * * result)",
  "size_bytes": 103,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a2530",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 2,
  "xrefs": [
    {
      "from": "01408844"
    },
    {
      "from": "006a28e0"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetProperty.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__GetProperty.c",
    "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.cpp",
    "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530.hpp",
    "reconstruction/staging/pkg-app-property-get-wave15/property_list_get_property_006a2530_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-app-property-get-wave15/006a2530.json"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "bool"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x00000024",
  "vtable:0x0000004c",
  "vtable:0x01408820"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x006a1540",
      "0x006a2f60",
      "0x006a2e20",
      "0x006a2530",
      "0x006a2b80",
      "0x006a2c50",
      "0x00694440",
      "0x006a1540",
      "0x006a1540",
      "0x006a154a",
      "0x006a15f3",
      "0x006a2f60",
      "0x006a2f60",
      "0x006a2f78",
      "0x006a2fe9",
      "0x006a2f60"
    ],
    "conflict_id": "TD-DATA-003",
    "kind": "conflict_ledger",
    "rejected": [
      {
        "path": "competing_hypotheses.1.claim",
        "status": "rejected_for_current_read_write_bodies     ",
        "text": "PropertyList Write serializes the entire recursive parent graph as ordinary local entries."
      }
    ],
    "resolution": null,
    "resolution_status": null,
    "source": "knowledgegraph/research/conflicts/track-d-data-serialization.json",
    "subject": "PropertyList local transfer, parent reference, and PROP framing",
    "unresolved_reason": [
      "The exact three-word parent identity and its manager-side construction are not fully identified.",
      "Outer record envelope, version negotiation, compression, and atomic rollback are not established by the selected bodies."
    ]
  },
  {
    "anchors": [
      "0x006a1540",
      "0x006a2f60",
      "0x006a1540",
      "0x013c7d90",
      "0x013c7d90",
      "0x006a1540",
      "0x006a1540",
      "0x006a1540",
      "0x006a1640",
      "0x006a1640",
      "0x006a2530",
      "0x006a2530",
      "0x006a2e20",
      "0x006a2e20",
      "0x006a2f60",
      "0x006a2f60"
    ],
    "conflict_id": "prop_wire_format",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
