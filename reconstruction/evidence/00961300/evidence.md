# Evidence 0x00961300

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `6156e38bfe31040cb5ae184c5b342f9ac5d34ae98eefcd8ca71f49990a91e8df`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit parent receiver in ECX and caller cleanup",
  "return_semantics": "void",
  "return_type": "void",
  "stack_cleanup_bytes": 4,
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
    "ret_form": "RET 0x4",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
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
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "esp_alignment_unknown: the entry-relative ESP offset is unknown and there is no frame pointer to fall back on"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "a359facb352a80a4f09aa633989e257b4d68dfa908823d856eff55a51e0e8a4d",
  "conventions": {
    "ambiguities": [
      "esp_alignment_unknown"
    ],
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
    "ghidra_parameter_count": 2,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit parent receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0027"
      ],
      "claim": "the callee pops 4 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 4,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "INFERRED",
      "id": "A1",
      "value": {
        "gaps": 0,
        "observed_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009",
        "obs-0015",
        "obs-0018",
        "obs-0022"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "the entry-relative argument offsets are unknown, so the convention is unknown",
      "confidence": "UNKNOWN",
      "id": "C11"
    },
    {
      "based_on": [
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
        "obs-0027"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0027"
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
      "at": "0x00961300",
      "count": 6,
      "first_use": 0,
      "first_write_index": 4,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "PUSH EBP",
      "reg": "EBP"
    },
    {
      "and_esp": null,
      "at": "0x00961300",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0002",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 0,
      "raw": "PUSH EBP",
      "sub": null
    },
    {
      "at": "0x00961301",
      "count": 6,
      "first_use": 1,
      "first_write_index": 10,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00961302",
      "count": 6,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH EDI",
      "reg": "EDI"
    },
    {
      "at": "0x00961303",
      "count": 5,
      "first_use": 3,
      "first_write_index": null,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "reg": "ESP"
    },
    {
      "at": "0x00961303",
      "base": "ESP",
      "disp": 16,
      "id": "obs-0006",
      "index": 3,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDI,dword ptr [ESP + 0x10]",
      "resolved": true,
      "size": 4,
      "trust": "untrusted_frame"
    },
    {
      "at": "0x00961303",
      "definite": true,
      "id": "obs-0007",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV EDI,dword p
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

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960250",
      "0x00960250",
      "0x00960370",
      "0x00960370",
      "0x00961300",
      "0x00961300",
      "0x00980470",
      "0x00980470",
      "0x00aeb0e0",
      "0x00aeb0e0",
      "0x00aeb1c0",
      "0x00aeb1c0"
    ],
    "conflict_id": "Q-UTFWIN-ORDER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x00809e60",
      "0x00809e60",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250",
      "0x00960310",
      "0x00960310",
      "0x00961300",
      "0x00961300",
      "0x00961980",
      "0x00961980"
    ],
    "conflict_id": "U-UTFWIN-DISPATCH",
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
  "count": 64,
  "instructions": [
    {
      "address": "00961300",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00961301",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00961302",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00961303",
      "instruction": "MOV EDI,dword ptr [ESP + 0x10]"
    },
    {
      "address": "00961307",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00961309",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "0096130b",
      "instruction": "JZ 0x0096138c"
    },
    {
      "address": "0096130d",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0096130f",
      "instruction": "MOV EDX,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00961312",
      "instruction": "LEA ESI,[EBP + -0x4]"
    },
    {
      "address": "00961315",
      "instruction": "NEG ESI"
    },
    {
      "address": "00961317",
      "instruction": "SBB ESI,ESI"
    },
    {
      "address": "00961319",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "0096131b",
      "instruction": "AND ESI,EBP"
    },
    {
      "address": "0096131d",
      "instruction": "CALL EDX"
    },
    {
      "address": "0096131f",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00961321",
      "instruction": "JNZ 0x0096138c"
    },
    {
      "address": "00961323",
      "instruction": "TEST byte ptr [EDI + 0x28],0x40"
    },
    {
      "address": "00961327",
      "instruction": "LEA ECX,[EDI + 0x4]"
    },
    {
      "address": "0096132a",
      "instruction": "JNZ 0x00961341"
    },
    {
      "address": "0096132c",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0096132d",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "0096132f",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "00961331",
      "instruction": "LEA ECX,[EBP + 0x38]"
    },
    {
      "address": "00961334",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00961335",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00961336",
      "instruction": "MOV EAX,ESP"
    },
    {
      "address": "00961338",
      "instruction": "MOV dword ptr [EAX],ECX"
    },
    {
      "address": "0096133a",
      "instruction": "CALL 0x008fe6d0"
    },
    {
      "address": "0096133f",
      "instruction": "JMP 0x00961380"
    },
    {
      "address": "00961341",
      "instruction": "MOV ESI,dword ptr [ECX]"
    },
    {
      "address": "00961343",
      "instruction": "LEA EDI,[EBP + 0x38]"
    },
    {
      "address": "00961346",
      "instruction": "MOV EAX,ESI"
    },
    {
      "address": "00961348",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "0096134a",
      "instruction": "JZ 0x00961367"
    },
    {
      "address": "0096134c",
      "instruction": "LEA ESP,[ESP]"
    },
    {
      "address": "00961350",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00961352",
      "instruction": "JZ 0x00961359"
    },
    {
      "address": "00961354",
      "instruction": "LEA EDX,[EAX + -0x8]"
    },
    {
      "address": "00961357",
      "instruction": "JMP 0x0096135b"
    },
    {
      "address": "00961359",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "0096135b",
      "instruction": "TEST byte ptr [EDX + 0x2c],0x40"
    },
    {
      "address": "0096135f",
      "instruction": "JZ 0x00961367"
    },
    {
      "address": "00961361",
      "instruction": "MOV EAX,dword ptr [EAX]"
    },
    {
      "address": "00961363",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00961365",
      "instruction": "JNZ 0x00961350"
    },
    {
      "address": "00961367",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "00961369",
      "instruction": "JZ 0x00961380"
    },
    {
      "address": "0096136b",
      "instruction": "MOV EDX,dword ptr [ECX + 0x4]"
    },
    {
      "address": "0096136e",
      "instruction": "MOV dword ptr [ESI + 0x4],EDX"
    },
    {
      "address": "00961371",
      "instruction": "MOV dword ptr [EDX],ESI"
    },
    {
      "address": "00961373",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00961376",
      "instruction": "MOV dword ptr [EDX],ECX"
    },
    {
      "address": "00961378",
      "instruction": "MOV dword ptr [EAX + 0x4],ECX"
    },
    {
      "address": "0096137b",
      "instruction": "MOV dword ptr [ECX + 0x4],EDX"
    },
    {
      "address": "0096137e",
      "instruction": "MOV dword ptr [ECX],EAX"
    },
    {
      "address": "00961380",
      "instruction": "MOV ECX,dword ptr [EBP + 0x30]"
    },
    {
      "address": "00961383",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00961385",
      "instruction": "JZ 0x0096138c"
    },
    {
      "address": "00961387",
      "instruction": "CALL 0x00958110"
    },
    {
      "address": "0096138c",
      "instruction": "POP EDI"
    },
    {
      "address": "0096138d",
      "instruction": "POP ESI"
    },
    {
      "address": "0096138e",
      "instruction": "POP EBP"
    },
    {
      "address": "0096138f",
      "instruction": "RET 0x4"
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
  "original_bytes": 11243,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit parent receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"void\",\n    \"return_type\": \"void\",\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x013fdbe4\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009601e0\",\n      \"va\": \"0x009601e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\",\n        \"shared_vtable:vtable:0x013fdb6c,vtable:0x013fdbe4\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 27,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00961260\",\n      \"va\": \"0x00961260\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00962830\",\n      \"va\": \"0x00962830\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_009646d0\",\n      \"va\": \"0x009646d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e20\",\n      \"va\": \"0x00967e20\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e60\",\n      \"va\": \"0x00967e60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_00967e80\",\n      \"va\": \"0x00967e80\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager,openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject,openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier\"\n      ],\n      \"package\": \"PKG-UTFWIN-LAYOUT-WAVE6\",\n      \"score\": 23,\n      \"symbol\": \"pkg_utfwin_layout_wave6_0096feb0\",\n      \"va\": \"0x0096feb0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x0096133a\",\n        \"direction\": \"out\",\n        \"other\": \"0x008fe6d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00961387\",\n        \"direction\": \"out\",\n        \"other\": \"0x00958110\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n
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
  "body_end": "00961391",
  "body_span_bytes": 146,
  "body_start": "00961300",
  "callees": [
    "FUN_00958110",
    "FUN_008fe6d0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00961300",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "UTFWin::Window::GetNextWinProc",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 2,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "IWindow *"
    },
    {
      "name": "pWinProc",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IWinProc *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "IWinProc *",
  "return_type_resolved": true,
  "rva": "0x561300",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "IWinProc * UTFWin::Window::GetNextWinProc(IWindow * this, IWinProc * pWinProc)",
  "size_bytes": 146,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00961300",
  "vtables": {
    "referenced_by_vtables": [
      "0x013fdb6c",
      "0x01414c14",
      "0x014151cc",
      "0x01419974",
      "0x01419ba4",
      "0x01441b4c",
      "0x01442e44",
      "0x0144324c",
      "0x01444624",
      "0x01444a9c",
      "0x01444f94",
      "0x01445464",
      "0x01445d94",
      "0x01445fac",
      "0x014461e4",
      "0x014464c4",
      "0x0145d68c",
      "0x01479314",
      "0x0147f964",
      "0x01414f38"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 32,
  "xrefs": [
    {
      "from": "013fdc04"
    },
    {
      "from": "01414cac"
    },
    {
      "from": "01414f9c"
    },
    {
      "from": "01415264"
    },
    {
      "from": "014432e4"
    },
    {
      "from": "01418804"
    },
    {
      "from": "0141919c"
    },
    {
      "from": "014193d4"
    },
    {
      "from": "01419674"
    },
    {
      "from": "01419a0c"
    },
    {
      "from": "01419c3c"
    },
    {
      "from": "0141ac5c"
    },
    {
      "from": "0144120c"
    },
    {
      "from": "0144185c"
    },
    {
      "from": "01441be4"
    },
    {
      "from": "01441fa4"
    },
    {
      "from": "01442edc"
    },
    {
      "from": "01443bb4"
    },
    {
      "from": "014446bc"
    },
    {
      "from": "01444b34"
    },
    {
      "from": "0144502c"
    },
    {
      "from": "014454fc"
    },
    {
      "from": "0144598c"
    },
    {
      "from": "01445e2c"
    },
    {
      "from": "01446044"
    },
    {
      "from": "0144627c"
    },
    {
      "from": "0144655c"
    },
    {
      "from": "0145d724"
    },
    {
      "from": "014793ac"
    },
    {
      "from": "0147f9fc"
    },
    {
      "from": "0147fcac"
    },
    {
      "from": "0147f834"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetNextWinProc.c",
  "file": "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__Window__GetNextWinProc.c",
    "src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-layout-wave6/00961300.json"
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
    "intrusive-list ownership, parent query, and manager port behavior remain gated",
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
  "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutManager",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::LayoutWindow",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueCastObject",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueImageCarrier",
  "openspore::reconstruction::pkg_utfwin_layout_wave6::OpaqueIndexCarrier",
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013fdb6c",
  "vtable:0x013fdbe4",
  "vtable:0x01414c14",
  "vtable:0x01414c8c",
  "vtable:0x01414f38",
  "vtable:0x01414f7c",
  "vtable:0x014151cc",
  "vtable:0x01415244",
  "vtable:0x014187a0",
  "vtable:0x014187e4",
  "vtable:0x01419138",
  "vtable:0x0141917c",
  "vtable:0x01419370",
  "vtable:0x014193b4",
  "vtable:0x01419610",
  "vtable:0x01419654"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960250",
      "0x00960250",
      "0x00960370",
      "0x00960370",
      "0x00961300",
      "0x00961300",
      "0x00980470",
      "0x00980470",
      "0x00aeb0e0",
      "0x00aeb0e0",
      "0x00aeb1c0",
      "0x00aeb1c0"
    ],
    "conflict_id": "Q-UTFWIN-ORDER",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00960250",
      "0x00960250",
      "0x00809e60",
      "0x00809e60",
      "0x0095fcc0",
      "0x0095fcc0",
      "0x00960050",
      "0x00960050",
      "0x00960250",
      "0x00960250",
      "0x00960310",
      "0x00960310",
      "0x00961300",
      "0x00961300",
      "0x00961980",
      "0x00961980"
    ],
    "conflict_id": "U-UTFWIN-DISPATCH",
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
