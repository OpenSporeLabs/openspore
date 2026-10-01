# Evidence 0x0069d3f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `62c882eaee46a275cff5421da1933890f519130c1a81ab54f31320edefacadef`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "undetermined by the machine ABI record; the reconstruction declares __thiscall from the listing observation below, which is a source-side claim and not a derived fact",
  "receiver": {
    "record_bounds_only": true,
    "record_confidence": "UNKNOWN",
    "record_offsets": [],
    "record_present": null,
    "record_reason": "ecx_reassigned_before_deref",
    "register_named_by_record": null
  },
  "ret_form": "RET",
  "return_note": "not named by the machine ABI record; the reconstruction declares a 32-bit integral return",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX (the machine record's own wording)",
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "receiver_not_determinable: ecx_reassigned_before_deref"
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
  "content_sha256": "a126b488378056b2fe13c9d2a9b9daec3c7f93f94872510fb4988d9b1a004f5a",
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
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "undetermined by the machine ABI record; the reconstruction declares __thiscall from the listing observation below, which is a source-side claim and not a derived fact"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0006"
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
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "the register receiver is undetermined: ecx_reassigned_before_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_reassigned_before_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "calling convention is __thiscall: 0x0069d3f0 is slot 8 of the vptr-backed vftable at 0x014084f0, so it is a virtual member of some class; the callee pops nothing and no stack word is read as an argument, so the receiver is in a register, and ECX is the only one that carries one",
      "confidence": "INFERRED",
      "id": "V1-VFT",
      "value": {
        "cleanup_side": "caller",
        "membership_count": 7,
        "receiver_provenance": "vftable_slot",
        "receiver_register": "ECX",
        "slot_index": 8,
        "table": "0x014084f0"
      }
    },
    {
      "based_on": [
        "obs-0006"
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
        "obs-0006"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0006"
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
      "at": "0x0069d3f0",
      "count": 2,
      "first_use": 0,
      "first_write_index": 0,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "XOR EAX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x0069d3f0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x0069d3f2",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "ADD ECX,0x8",
      "reg": "ECX",
      "write_kind": "arith"
    },
    {
      "at": "0x0069d3f5",
      "count": 1,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x0069d3f5",
      "clobbers": [
        "EAX",
        "ECX"
      ],
      "form": "XADD.LOCK",
      "id": "obs-0005",
      "index": 2,
      "kind": "STRING_OP",
      "raw": "XADD.LOCK dword ptr [ECX],EAX",
      "rep": false,
      "string_base": false
    },
    {
      "at": "0x0069d3f9",
      "form": "RET",
      "id": "obs-0006",
      "imm": null,
      "index": 3,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 4,
    "degraded": false,
    "esp_unresolved": false,
    "flow_complete": true,
    "frame": {
      "and_esp": null,
      "ebp_is_general_register": false,
      "fp": false,
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "sub": null
    },
    "layout": "json_instruction_list",
    "local_extent": 0,
    "unparsed": 0
  },
  "receiver": {
    "bounds_only": true,
    "confidence": "UNKNOWN",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": null,
    "provenance": "vftable_slot",
    "reason": "ecx_reassigned_before_deref",
    "register": "ECX",
    "shape": null,
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "integral",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be miss
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
  "count": 4,
  "instructions": [
    {
      "address": "0069d3f0",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "0069d3f2",
      "instruction": "ADD ECX,0x8"
    },
    {
      "address": "0069d3f5",
      "instruction": "XADD.LOCK dword ptr [ECX],EAX"
    },
    {
      "address": "0069d3f9",
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
  "original_bytes": 6193,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"undetermined by the machine ABI record; the reconstruction declares __thiscall from the listing observation below, which is a source-side claim and not a derived fact\",\n    \"receiver\": {\n      \"record_bounds_only\": true,\n      \"record_confidence\": \"UNKNOWN\",\n      \"record_offsets\": [],\n      \"record_present\": null,\n      \"record_reason\": \"ecx_reassigned_before_deref\",\n      \"register_named_by_record\": null\n    },\n    \"ret_form\": \"RET\",\n    \"return_note\": \"not named by the machine ABI record; the reconstruction declares a 32-bit integral return\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"integral_in_EAX (the machine record's own wording)\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"resource-io\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0197\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:none; the body names no absolute address\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"Resource::DatabaseDirectoryFiles::GetRefCount\",\n  \"normalized_symbol\": \"Resource::DatabaseDirectoryFiles::GetRefCount\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c\",\n      \"reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.cpp\",\n      \"reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.hpp\",\n      \"reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-resource-ddf-refcount/0069d3f0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"Resource\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"resource-io\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c\",\n    \"dependencies\": [\n      \"runtime-crt-stl\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:0069d3f0\",\n    \"name\": \"Resource::DatabaseDirectoryFiles::GetRefCount\",\n    \"priority\": \"P0\",\n    \"provenance\": {\n      \"classifier\": \"triage-v4\",\n      \"generated_at\": \"2026-09-23T10:12:09Z\",\n      \"generator\": \"subagent-7-sequential-triage\",\n      \"sdk_name\": \"Resource::DatabaseDirectoryFiles::GetRefCount\",\n      \"snapshot\": \"2540f2ca\",\n      \"snapshot_sha256\": \"2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8\",\n      \"vtable_addrs\": [\n        \"014084f0\",\n        \"014086a8\",\n        \"01409630\",\n        \"0140a138\",\n        \"01436700\",\n        \"014367b0\",\n        \"01482d38\"\n      ]\n    },\n    \"queue_state\": \"queued\",\n    \"rank\": 97\n  },\n  \"types\": [\n    \"not named by the machine ABI record; the reconstruction declares a 32-bit integral return\",\n    \"std::int32_t\"\n  ],\n  \"unresolved_questions\": [\n    \"ABI_UNKNOWN: the machine ABI record abstained -- no_discriminator: no stack-argument read and no positive receiver evidence\",\n    \"ABI_UNKNOWN: the machine ABI record abstained -- receiver_not_determinable: ecx_reassigned_before_deref\",\n    \"Byte-level confirmation of the four instructions is now recorded (evidence.byte_level_confirmation), including that 83c108 is an in-place ADD with no prior definition of ECX. It changes no verdict: the ABI record still abstains with the same two reasons, so the receiver observation remains an observation and the convention remains unestablished.\",\n    \"Can any of the seven vtable-slot call sites pass a null or partially constructed receiver? The body has no guard.\",\n    \"Is the word at receiver+0x8 really this object's reference count? The name comes from the SDK symbol, and a single 32-bit word read cannot distinguish a count from any other counter.\",\n    \"The record associates seven vtables with this target while the xref export records zero vtable references; the classifier association is unexplained and no slot identity is claimed.\",\n    \"The source declares __thiscall from a reading of the listing (ECX is never defined before the dereference, the body reads no stack slot, and Ghidra's own decompilation dereferences in_ECX). That observation is not corroborated by the machine ABI record, which names
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
  "body_end": "0069d3f9",
  "body_span_bytes": 10,
  "body_start": "0069d3f0",
  "callees": [],
  "callers": [],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "0069d3f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Resource::DatabaseDirectoryFiles::GetRefCount",
  "namespace": "Resource",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "DatabaseDirectoryFiles *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "int",
  "return_type_resolved": true,
  "rva": "0x29d3f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "int Resource::DatabaseDirectoryFiles::GetRefCount(DatabaseDirectoryFiles * this)",
  "size_bytes": 10,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x0069d3f0",
  "vtables": {
    "referenced_by_vtables": [
      "0x014084f0",
      "0x014367b0",
      "0x0140a138",
      "0x01436700",
      "0x01482d38",
      "0x014086a8",
      "0x01409630"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 7,
  "xrefs": [
    {
      "from": "014086a8"
    },
    {
      "from": "01408510"
    },
    {
      "from": "01409640"
    },
    {
      "from": "0140a148"
    },
    {
      "from": "01436710"
    },
    {
      "from": "014367c0"
    },
    {
      "from": "01482d48"
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
  "global:none; the body names no absolute address"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Resource__DatabaseDirectoryFiles__GetRefCount.c",
    "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.cpp",
    "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count.hpp",
    "reconstruction/staging/pkg-resource-ddf-refcount/ddf_get_ref_count_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-resource-ddf-refcount/0069d3f0.json"
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
  "not named by the machine ABI record; the reconstruction declares a 32-bit integral return",
  "std::int32_t"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014084f0",
  "vtable:0x014086a8",
  "vtable:0x01409630",
  "vtable:0x0140a138",
  "vtable:0x01436700",
  "vtable:0x014367b0",
  "vtable:0x01482d38"
]
```

## Conflicts

```json
[]
```
