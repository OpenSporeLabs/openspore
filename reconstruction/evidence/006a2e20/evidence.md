# Evidence 0x006a2e20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7382047a39c1498ddd5c2dd960365ae3f8daf18a58b87210bd7ba95a12731c37`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "__thiscall",
    "x86-32 thiscall; receiver in ECX, caller cleanup"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_register": "EAX",
  "return_semantics": "void. The receiver is copied into EDI at 0x006a2e3b and is never moved back into EAX on any path; the epilogue restores the exception frame and returns. EAX is therefore scratch on every exit, and the only value the function produces is its effect on the receiver's map and its counter at +0x34.",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": [
    "callee",
    "caller"
  ],
  "termination": "RET 0x8"
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
      "entry_ESP+0x4",
      "entry_ESP+0x8"
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
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x8",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
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
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x8"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +16, so the listing is not one path"
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
  "content_sha256": "188389e7139f191b52260b8604f4ca3bc7e8062e2261bf922bac8566cf0bdaec",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "['__thiscall', 'x86-32 thiscall; receiver in ECX, caller cleanup']"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0040"
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
        "obs-0015",
        "obs-0017",
        "obs-0019"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 2,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0019",
        "obs-0020",
        "obs-0023",
        "obs-0033",
        "obs-0035",
        "obs-0039"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          24,
          28,
          44,
          52
        ],
        "register": "ECX",
        "written_through": 1
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0004",
        "obs-0039"
      ],
      "claim": "an FS:/GS: operand is an SEH or cookie frame, which is not variadic evidence",
      "confidence": "OBSERVED",
      "id": "V2",
      "value": {
        "seh_or_cookie_frame": true
      }
    },
    {
      "based_on": [
        "obs-0011",
        "obs-0012",
        "obs-0019",
        "obs-0020",
        "obs-0023",
        "obs-0033",
        "obs-0035",
        "obs-0039",
        "obs-0040"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0040"
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
        "obs-0040"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0040"
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
      "at": "0x006a2e20",
      "id": "obs-0001",
      "index": 0,
      "kind": "SEGMENT_TLS",
      "raw": "MOV EAX,FS:[0x0]",
      "segment": "FS",
      "text": "FS:[0x0]"
    },
    {
      "at": "0x006a2e20",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,FS:[0x0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x006a2e2d",
      "count": 9,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 3,
      "kind": "REG_READ",
      "raw": "PUSH EAX",
      "reg": "EAX"
    },
    {
      "at": "0x006a2e2e",
      "id": "obs-0004",
      "index": 4,
      "kind": "SEGMENT_TLS",
      "raw": "MOV dword ptr FS:[0x0],ESP",
      "segment": "FS",
      "text": "dword ptr FS:[0x0]"
    },
    {
      "at": "0x006a2e2e",
      "count": 15,
   
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "editor_query_clear_flags_0093db80",
    "reconstructed": true,
    "va": "0x0093db80"
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
    "name": "opaque_list_set_property_006a30c0",
    "reconstructed": true,
    "va": "0x006a30c0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bed460"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bed920"
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
  "count": 65,
  "instructions": [
    {
      "address": "006a2e20",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "006a2e26",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "006a2e28",
      "instruction": "PUSH 0x120d6b8"
    },
    {
      "address": "006a2e2d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2e2e",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "006a2e35",
      "instruction": "SUB ESP,0x20"
    },
    {
      "address": "006a2e38",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2e39",
      "instruction": "PUSH ESI"
    },
    {
      "address": "006a2e3a",
      "instruction": "PUSH EDI"
    },
    {
      "address": "006a2e3b",
      "instruction": "MOV EDI,ECX"
    },
    {
      "address": "006a2e3d",
      "instruction": "MOVZX ECX,byte ptr [EDI + 0x2c]"
    },
    {
      "address": "006a2e41",
      "instruction": "MOV EBX,dword ptr [EDI + 0x1c]"
    },
    {
      "address": "006a2e44",
      "instruction": "MOV EAX,dword ptr [EDI + 0x18]"
    },
    {
      "address": "006a2e47",
      "instruction": "LEA ESI,[EDI + 0x18]"
    },
    {
      "address": "006a2e4a",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2e4b",
      "instruction": "LEA EDX,[ESP + 0x40]"
    },
    {
      "address": "006a2e4f",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a2e50",
      "instruction": "PUSH EBX"
    },
    {
      "address": "006a2e51",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2e52",
      "instruction": "CALL 0x00612db0"
    },
    {
      "address": "006a2e57",
      "instruction": "MOV EDX,dword ptr [ESP + 0x4c]"
    },
    {
      "address": "006a2e5b",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "006a2e5e",
      "instruction": "CMP EAX,EBX"
    },
    {
      "address": "006a2e60",
      "instruction": "JZ 0x006a2e6d"
    },
    {
      "address": "006a2e62",
      "instruction": "CMP EDX,dword ptr [EAX]"
    },
    {
      "address": "006a2e64",
      "instruction": "JC 0x006a2e6d"
    },
    {
      "address": "006a2e66",
      "instruction": "LEA ECX,[EAX + 0x18]"
    },
    {
      "address": "006a2e69",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "006a2e6b",
      "instruction": "JNZ 0x006a2e6f"
    },
    {
      "address": "006a2e6d",
      "instruction": "MOV EAX,EBX"
    },
    {
      "address": "006a2e6f",
      "instruction": "MOV ECX,dword ptr [ESP + 0x40]"
    },
    {
      "address": "006a2e73",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006a2e74",
      "instruction": "CMP EAX,dword ptr [EDI + 0x1c]"
    },
    {
      "address": "006a2e77",
      "instruction": "JZ 0x006a2e83"
    },
    {
      "address": "006a2e79",
      "instruction": "LEA ECX,[EAX + 0x4]"
    },
    {
      "address": "006a2e7c",
      "instruction": "CALL 0x00542b80"
    },
    {
      "address": "006a2e81",
      "instruction": "JMP 0x006a2ed1"
    },
    {
      "address": "006a2e83",
      "instruction": "MOV dword ptr [ESP + 0x18],EDX"
    },
    {
      "address": "006a2e87",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "006a2e89",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "006a2e8b",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "006a2e8f",
      "instruction": "MOV word ptr [ESP + 0x2c],DX"
    },
    {
      "address": "006a2e94",
      "instruction": "MOV word ptr [ESP + 0x2e],AX"
    },
    {
      "address": "006a2e99",
      "instruction": "CALL 0x00542b80"
    },
    {
      "address": "006a2e9e",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "006a2ea2",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006a2ea3",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "006a2ea7",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006a2ea8",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "006a2eaa",
      "instruction": "MOV dword ptr [ESP + 0x3c],0x0"
    },
    {
      "address": "006a2eb2",
      "instruction": "CALL 0x006a2c50"
    },
    {
      "address": "006a2eb7",
      "instruction": "TEST byte ptr [ESP + 0x28],0x4"
    },
    {
      "address": "006a2ebc",
      "instruction": "MOV dword ptr [ESP + 0x34],0xffffffff"
    },
    {
      "address": "006a2ec4",
      "instruction": "JZ 0x006a2ed1"
    },
    {
      "address": "006a2ec6",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "006a2ec8",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "006a2ecc",
      "instruction": "CALL 0x0093db80"
    },
    {
      "address": "006a2ed1",
      "instruction": "INC dword ptr [EDI + 0x34]"
    },
    {
      "address": "006a2ed4",
      "instruction": "MOV ECX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "006a2ed8",
      "instruction": "POP EDI"
    },
    {
      "address": "006a2ed9",
      "instruction": "POP ESI"
    },
    {
      "address": "006a2eda",
      "instruction": "POP EBX"
    },
    {
      "address": "006a2edb",
      "instruction": "MOV dword ptr FS:[0x0],ECX"
    },
    {
      "address": "006a2ee2",
      "instruction": "ADD ESP,0x2c"
    },
    {
      "address": "006a2ee5",
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
  "original_bytes": 14405,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"__thiscall\",\n      \"x86-32 thiscall; receiver in ECX, caller cleanup\"\n    ],\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x8\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"void. The receiver is copied into EDI at 0x006a2e3b and is never moved back into EAX on any path; the epilogue restores the exception frame and returns. EAX is therefore scratch on every exit, and the only value the function produces is its effect on the receiver's map and its counter at +0x34.\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": [\n      \"callee\",\n      \"caller\"\n    ],\n    \"termination\": \"RET 0x8\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-app-proplist-copyall-wave16\",\n      \"score\": 10,\n      \"symbol\": \"all_copy_from_properties_006a14d0\",\n      \"va\": \"0x006a14d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-dfw-006a1540\",\n      \"score\": 10,\n      \"symbol\": \"proplist_write_006a1540\",\n      \"va\": \"0x006a1540\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-property-clear-wave13\",\n      \"score\": 10,\n      \"symbol\": \"property_list_clear_006a2a80\",\n      \"va\": \"0x006a2a80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"pkg-property-remove-006a2ef0\",\n      \"score\": 10,\n      \"symbol\": \"property_list_remove_property_006a2ef0\",\n      \"va\": \"0x006a2ef0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-direct-property-clear-wave14\",\n      \"score\": 6,\n      \"symbol\": \"direct_property_list_clear_006a2b20\",\n      \"va\": \"0x006a2b20\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 4,\n      \"symbol\": \"property_list_has_property_006a2470\",\n      \"va\": \"0x006a2470\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"wave6-resources\",\n      \"score\": 4,\n      \"symbol\": \"property_list_get_property_object_006a24d0\",\n      \"va\": \"0x006a24d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x01408820\"\n      ],\n      \"package\": \"PKG-PROPERTY-SAFE-WAVE9\",\n      \"score\": 4,\n      \"symbol\": \"property_list_copy_from_006a2a40\",\n      \"va\": \"0x006a2a40\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"app-lifecycle\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"editor_query_clear_flags_0093db80\",\n        \"reconstructed\": true,\n        \"va\": \"0x0093db80\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"opaque_list_set_property_006a30c0\",\n        \"reconstructed\": true,\n        \"va\": \"0x006a30c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bed460\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bed920\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x006a3162\",\n        \"direction\": \"in\",\n        \"other\": \"0x006a30c0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bed826\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bed460\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00beda96\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bed920\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2e7c\",\n        \"direction\": \"out\",\n        \"other\": \"0x00542b80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2e99\",\n        \"direction\": \"out\",\n        \"other\": \"0x00542b80\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2e52\",\n        \"direction\": \"out\",\n        \"other\": \"0x00612db0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2eb2\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a2c50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006a2ecc\",\n        \"direction\": \"out\",\n        \"other\": \"0x0093db80\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 3,\n    \"fan_out\": 1,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x006a30c0\",\n      \"0x0093db80\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0215\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\",\n    \"global:the complete 65-instr
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
  "body_end": "006a2ee7",
  "body_span_bytes": 200,
  "body_start": "006a2e20",
  "callees": [
    "FUN_00612db0",
    "FUN_00542b80",
    "FUN_006a2c50",
    "FUN_0093db80"
  ],
  "callers": [
    "App::DirectPropertyList::SetProperty",
    "FUN_00bed460",
    "FUN_00bed920"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006a2e20",
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
    },
    {
      "name": "local_c",
      "storage": "Stack[-0xc]:4",
      "type": "undefined4"
    },
    {
      "name": "local_e",
      "storage": "Stack[-0xe]:2",
      "type": "undefined2"
    },
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:2",
      "type": "undefined2"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:1",
      "type": "undefined"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:1",
      "type": "undefined"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "App::PropertyList::SetProperty",
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
      "name": "pValue",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Property *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x2a2e20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void App::PropertyList::SetProperty(PropertyList * this, uint32_t propertyID, Property * pValue)",
  "size_bytes": 200,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006a2e20",
  "vtables": {
    "referenced_by_vtables": [
      "0x01408820"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 6,
  "xrefs": [
    {
      "from": "00bed826"
    },
    {
      "from": "01408834"
    },
    {
      "from": "006a3162"
    },
    {
      "from": "00baefd9"
    },
    {
      "from": "010588e9"
    },
    {
      "from": "00beda96"
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
  "global:PASS",
  "global:the complete 65-instruction listing names no data-segment address and the source span names none"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__SetProperty.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/App__PropertyList__SetProperty.c",
    "reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20.cpp",
    "reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20_model_test.cpp",
    "reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20_types.hpp",
    "reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20.cpp",
    "reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20.hpp",
    "reconstruction/staging/pkg-proplist-setprop-w15/property_set_006a2e20_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dfw-006a2e20/006a2e20.json",
    "reconstruction/metadata/pkg-proplist-setprop-w15/006a2e20.json"
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
  "openspore::reconstruction::pkg_proplist_setprop_w15::MapEntry",
  "openspore::reconstruction::pkg_proplist_setprop_w15::MapLookup",
  "openspore::reconstruction::pkg_proplist_setprop_w15::Property",
  "openspore::reconstruction::pkg_proplist_setprop_w15::PropertyList",
  "openspore::reconstruction::pkg_proplist_setprop_w15::PropertyMap",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x006a2470",
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
