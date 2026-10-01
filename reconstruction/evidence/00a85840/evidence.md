# Evidence 0x00a85840

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `4c177208f0bf564baa94b336bf3eb65c9523a36ebebb59cbed7d46b8a36cfc5a`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "__thiscall",
  "ret_form": "RET 0x8",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "0x00a858b3 (C2 08 00)"
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
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
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
    "return_register": "XMM0",
    "return_semantics": "float_or_x87_in_XMM0",
    "saved_registers": [
      "ESI"
    ],
    "stack_arguments": [
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
    "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path"
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
  "content_sha256": "69f721e6c9b78db57e2b977b10f81f80e967fd6b762ce08fe0f95a711871e34b",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0028"
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
        "obs-0004"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0013"
      ],
      "claim": "ECX carries the receiver: 0x00a85840 is slot 6 of the vptr-backed vftable at 0x01458024, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body reads its incoming ECX before writing it, and a body that reads a register the vtable dispatch delivered uses the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R1-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_reads": 1,
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_dispatch",
        "receiver_register": "ECX",
        "slot_index": 6,
        "table": "0x01458024"
      }
    },
    {
      "based_on": [
        "obs-0013",
        "obs-0014",
        "obs-0018",
        "obs-0023",
        "obs-0025",
        "obs-0028"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
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
        "obs-0001"
      ],
      "claim": "the return value is carried in XMM0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "XMM0"
    }
  ],
  "observations": [
    {
      "and_esp": null,
      "at": "0x00a85840",
      "ebp_is_general_register": false,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": false,
      "push_ebp_at": null,
      "raw": "SUB ESP,0x38",
      "sub": 56
    },
    {
      "at": "0x00a85840",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x38",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00a85843",
      "count": 11,
      "first_use": 1,
      "first_write_index": 0,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "reg": "ESP"
    },
    {
      "at": "0x00a85843",
      "base": "ESP",
      "disp": 64,
      "id": "obs-0004",
      "index": 1,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00a85843",
      "definite": true,
      "id": "obs-0005",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ESP + 0x40]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00a85847",
      "count": 8,
      "first_use": 2,
      "first_write_index": 1,
      "id": "obs-0006",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOVSS X
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
      "address": "00a85840",
      "instruction": "SUB ESP,0x38"
    },
    {
      "address": "00a85843",
      "instruction": "MOV EAX,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00a85847",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00a8584c",
      "instruction": "MOV DX,word ptr [EAX + 0x2]"
    },
    {
      "address": "00a85850",
      "instruction": "MOVSS dword ptr [ESP + 0x4],XMM0"
    },
    {
      "address": "00a85856",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00a8585b",
      "instruction": "MOVSS dword ptr [ESP + 0x8],XMM0"
    },
    {
      "address": "00a85861",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0xc]"
    },
    {
      "address": "00a85866",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00a85867",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00a85869",
      "instruction": "MOV CX,word ptr [EAX]"
    },
    {
      "address": "00a8586c",
      "instruction": "MOVSS dword ptr [ESP + 0x10],XMM0"
    },
    {
      "address": "00a85872",
      "instruction": "MOVSS XMM0,dword ptr [EAX + 0x10]"
    },
    {
      "address": "00a85877",
      "instruction": "ADD EAX,0x14"
    },
    {
      "address": "00a8587a",
      "instruction": "MOV word ptr [ESP + 0x4],CX"
    },
    {
      "address": "00a8587f",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a85880",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "00a85884",
      "instruction": "MOV word ptr [ESP + 0xa],DX"
    },
    {
      "address": "00a85889",
      "instruction": "MOVSS dword ptr [ESP + 0x18],XMM0"
    },
    {
      "address": "00a8588f",
      "instruction": "CALL 0x0041cb40"
    },
    {
      "address": "00a85894",
      "instruction": "MOV EAX,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00a85898",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00a85899",
      "instruction": "LEA ECX,[ESP + 0x8]"
    },
    {
      "address": "00a8589d",
      "instruction": "CALL 0x00537f40"
    },
    {
      "address": "00a858a2",
      "instruction": "LEA ECX,[ESP + 0x4]"
    },
    {
      "address": "00a858a6",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00a858a7",
      "instruction": "LEA ECX,[ESI + 0x24]"
    },
    {
      "address": "00a858aa",
      "instruction": "CALL 0x00537dc0"
    },
    {
      "address": "00a858af",
      "instruction": "POP ESI"
    },
    {
      "address": "00a858b0",
      "instruction": "ADD ESP,0x38"
    },
    {
      "address": "00a858b3",
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
  "original_bytes": 9125,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"__thiscall\",\n    \"ret_form\": \"RET 0x8\",\n    \"saved_registers\": [\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"0x00a858b3 (C2 08 00)\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458024\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-vft-preinc-0051e340\",\n      \"score\": 12,\n      \"symbol\": \"vft_preinc_0051e340\",\n      \"va\": \"0x0051e340\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458024\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"subobject-forward-0051e380\",\n      \"score\": 12,\n      \"symbol\": \"subobject_forward_0051e380\",\n      \"va\": \"0x0051e380\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"shared_vtable:vtable:0x01458024\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-00a85070\",\n      \"score\": 12,\n      \"symbol\": \"re_00a85070\",\n      \"va\": \"0x00a85070\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w2-00586700\",\n      \"score\": 8,\n      \"symbol\": \"re_00586700\",\n      \"va\": \"0x00586700\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-005b2490\",\n      \"score\": 8,\n      \"symbol\": \"re_005b2490\",\n      \"va\": \"0x005b2490\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w1-005ba0d0\",\n      \"score\": 8,\n      \"symbol\": \"re_005ba0d0\",\n      \"va\": \"0x005ba0d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w2-00a980b0\",\n      \"score\": 8,\n      \"symbol\": \"re_00a980b0\",\n      \"va\": \"0x00a980b0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"pkg-swarm-w2-00a98200\",\n      \"score\": 8,\n      \"symbol\": \"re_00a98200\",\n      \"va\": \"0x00a98200\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00a8588f\",\n        \"direction\": \"out\",\n        \"other\": \"0x0041cb40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00a858aa\",\n        \"direction\": \"out\",\n        \"other\": \"0x00537dc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00a8589d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00537f40\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0338\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00a85840\",\n  \"normalized_symbol\": \"FUN_00a85840\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-w2-00a85840/w2_00a85840.cpp\",\n      \"reconstruction/staging/pkg-w2-00a85840/w2_00a85840_model_test.cpp\",\n      \"reconstruction/staging/pkg-w2-00a85840/w2_00a85840_types.hpp\",\n      \"src/editor/pkg_w2_00a85840_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-w2-00a85840/00a85840.json\"\n    ],\n    \"provenance\": [\n      \"GhidraMCP /disassemble_function at 0x0041cb40, 0x00537f40, 0x00537dc0, 0x00a853b0\",\n      \"GhidraMCP /read_memory at 0x00a85840 len 118 and at 0x01458024 len 32\",\n      \"knowledgegraph/triage/xrefs-2540f2ca.tsv -- the three out-rows for 0x00a85840 and the absence of any in-row\",\n      \"reconstruction/evidence/00a85840/context.json and context.md\",\n      \"reconstruction/evidence/00a85840/evidence.json (disassembly, abi, abi_derived, ghidra_function, function_identity, callees_dependencies, callers_dependencies, vtables, contradictions, evidence_state)\",\n      \"reconstruction/evidence/00a85840/validation.json and validation.md\"\n    ]\n  },\n  \"status\": \"candidate\",\n  \"subsystem\": \"Editor\",\n  \"triage\": {\n    \"category\": \"GAMEPLAY_LOGIC\",\n    \"cluster\": \"editor-core\",\n    \"db_triage_status\": \"candidate\",\n    \"decomp_path\": null,\n    \"dependencies\": [],\n    \"evidence\"
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
  "body_end": "00a858b5",
  "body_span_bytes": 118,
  "body_start": "00a85840",
  "callees": [
    "FUN_0041cb40",
    "FUN_00537f40",
    "FUN_00537dc0"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00a85840",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:1",
      "type": "undefined"
    },
    {
      "name": "local_28",
      "storage": "Stack[-0x28]:4",
      "type": "undefined4"
    },
    {
      "name": "local_2c",
      "storage": "Stack[-0x2c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_30",
      "storage": "Stack[-0x30]:4",
      "type": "undefined4"
    },
    {
      "name": "local_34",
      "storage": "Stack[-0x34]:4",
      "type": "undefined4"
    },
    {
      "name": "local_36",
      "storage": "Stack[-0x36]:2",
      "type": "undefined2"
    },
    {
      "name": "local_38",
      "storage": "Stack[-0x38]:2",
      "type": "undefined2"
    }
  ],
  "locals_count": 7,
  "mode": "live",
  "name": "FUN_00a85840",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x685840",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00a85840(void)",
  "size_bytes": 118,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00a85840",
  "vtables": {
    "referenced_by_vtables": [
      "0x01458024"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0145803c"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00a85840/w2_00a85840.cpp",
    "reconstruction/staging/pkg-w2-00a85840/w2_00a85840_model_test.cpp",
    "reconstruction/staging/pkg-w2-00a85840/w2_00a85840_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00a85840/00a85840.json"
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
  "BlendSource",
  "BlendSource (0x38, the first stack word, opaque, extent from 0x00537f40)",
  "Block18 (0x18, 0x0041cb40's object and the SourceRecord's +0x14 member)",
  "MergeTarget (0x38, the receiver's +0x24 member, opaque, extent from 0x00537dc0)",
  "Receiver",
  "Receiver (0x6c, this body's +0x24 member named; the rest opaque)",
  "Sample",
  "Sample (0x38, the local; 0x14 this body fills plus the 0x24 the second callee writes)",
  "SourceRecord",
  "SourceRecord (0x2c, six words plus a 0x18-byte block at +0x14)"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x01458024"
]
```

## Conflicts

```json
[]
```
