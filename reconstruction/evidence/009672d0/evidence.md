# Evidence 0x009672d0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `a06e481ced06d5275afb85bfe7087ad7d90dba33b2cd4383567d72d6c2d3dda3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with the receiver in ECX and one 4-byte type word on the stack",
  "ordinary_stack_argument_slots": 1,
  "return_register": "EAX",
  "return_type": "Opaque*",
  "return_width_bytes": 4,
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
    "calling_convention": "__thiscall",
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
    "return_semantics": "integral_in_EAX",
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
  "abstained_because": [],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "90a092a50858b3eb1e6c0255c41c9f29e54695a533bf8bf51995c89c22a28cce",
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
    "persisted_calling_convention": "x86-32 thiscall with the receiver in ECX and one 4-byte type word on the stack"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0008",
        "obs-0009"
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
        "obs-0002",
        "obs-0005"
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
        "obs-0007"
      ],
      "claim": "ECX carries the receiver: 0x009672d0 is slot 3 of the vptr-backed vftable at 0x014414b8, so it is a virtual member of some class and every virtual call that reaches it indexes the vptr through the object address; the body takes the address of its incoming ECX (LEA at 0x009672e8) and never touches memory through it, after a null test of it, and a body that computes an address from a register the vtable dispatch delivered computes it from the object, so the receiver is in ECX. The callee pops its own stack arguments, which is the COM / __stdcall interface form, and that is the one shape in which a virtual member takes its receiver from the first popped stack word instead -- a body in that form has no register parameter and never reads its incoming ECX, which is why this body reading it is what decides the two apart",
      "confidence": "INFERRED",
      "id": "R2-VFT",
      "value": {
        "cleanup_side": "callee",
        "incoming_ecx_null_test": true,
        "incoming_ecx_reads": 1,
        "incoming_member_leas": 1,
        "member_lea_displacements": [
          12
        ],
        "member_lea_sites": [
          "0x009672e8"
        ],
        "membership_count": 1,
        "receiver_provenance": "vftable_slot_address",
        "receiver_register": "ECX",
        "slot_index": 3,
        "table": "0x014414b8"
      }
    },
    {
      "based_on": [
        "obs-0007",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009"
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
        "obs-0006",
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the function can reach a caller by transferring out of the listing, so the path that actually returns was never observed",
      "confidence": "UNKNOWN",
      "id": "T2",
      "value": {
        "form": "epilogue_then_jmp"
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0009"
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
      "at": "0x009672d0",
      "count": 2,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "reg": "ESP"
    },
    {
      "at": "0x009672d0",
      "base": "ESP",
      "disp": 4,
      "id": "obs-0002",
      "index": 0,
      "key": 4,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EAX,dword ptr [ESP + 0x4]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x009672d0",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword pt
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

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\n/* WARNING: Unknown calling convention */\n/* WARNING: Enum \"ObjectTYPE\": Some values do not have unique names */\n\nbool UTFWin__CascadeEffect__HandleUIMessage(CascadeEffect *this,IWindow *pWindow,Message *message)\n\n{\n  undefined1 uVar1;\n  int in_ECX;\n  \n  if (this != (CascadeEffect *)0x6f90a535) {\n    uVar1 = FUN_00950eb0();\n    return (bool)uVar1;\n  }\n  if (in_ECX != 0) {\n    return (bool)((char)in_ECX + '\\f');\n  }\n  return false;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 11,
  "instructions": [
    {
      "address": "009672d0",
      "instruction": "MOV EAX,dword ptr [ESP + 0x4]"
    },
    {
      "address": "009672d4",
      "instruction": "CMP EAX,0x6f90a535"
    },
    {
      "address": "009672d9",
      "instruction": "JZ 0x009672e4"
    },
    {
      "address": "009672db",
      "instruction": "MOV dword ptr [ESP + 0x4],EAX"
    },
    {
      "address": "009672df",
      "instruction": "JMP 0x00950eb0"
    },
    {
      "address": "009672e4",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "009672e6",
      "instruction": "JZ 0x009672ee"
    },
    {
      "address": "009672e8",
      "instruction": "LEA EAX,[ECX + 0xc]"
    },
    {
      "address": "009672eb",
      "instruction": "RET 0x4"
    },
    {
      "address": "009672ee",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "009672f0",
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
  "original_bytes": 6183,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with the receiver in ECX and one 4-byte type word on the stack\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"return_register\": \"EAX\",\n    \"return_type\": \"Opaque*\",\n    \"return_width_bytes\": 4,\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-0095fa30-utfwin-isancestorof\",\n      \"score\": 6,\n      \"symbol\": \"is_ancestor_of_0095fa30\",\n      \"va\": \"0x0095fa30\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-utfwin-func35-wave12\",\n      \"score\": 6,\n      \"symbol\": \"func35_0095fd60\",\n      \"va\": \"0x0095fd60\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-0096ff70\",\n      \"score\": 6,\n      \"symbol\": \"dfw_func88h_0096ff70\",\n      \"va\": \"0x0096ff70\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-00980510\",\n      \"score\": 6,\n      \"symbol\": \"dfw_get_proxy_id_00980510\",\n      \"va\": \"0x00980510\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-dfw-00980c50\",\n      \"score\": 6,\n      \"symbol\": \"dfw_00980c50_func88h\",\n      \"va\": \"0x00980c50\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-utfwin-slot7-wave12\",\n      \"score\": 6,\n      \"symbol\": \"re_00fc7e10_UTFWin_ImageDrawable_GetTiling\",\n      \"va\": \"0x00fc7e10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"pkg-utfwin-settiling-wave13\",\n      \"score\": 6,\n      \"symbol\": \"set_tiling_00fd9460\",\n      \"va\": \"0x00fd9460\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x014414b8\"\n      ],\n      \"package\": \"PKG-UTFWIN-CORE-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"re_00951220\",\n      \"va\": \"0x00951220\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"utfwin-framework\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x009672df\",\n        \"direction\": \"out\",\n        \"other\": \"0x00950eb0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0306\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [],\n  \"integration_status\": null,\n  \"name\": \"UTFWin::CascadeEffect::HandleUIMessage\",\n  \"normalized_symbol\": \"UTFWin::CascadeEffect::HandleUIMessage\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c\",\n      \"reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.cpp\",\n      \"reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.hpp\",\n      \"reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0_model_test.cpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-utfwin-cascade-009672d0/009672d0.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"UTFWin\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"utfwin-framework\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c\",\n    \"dependencies\": [\n      \"app-lifecycle\",\n      \"resource-io\"\n    ],\n    \"evidence\": \"CONFIRMED\",\n    \"kg_node_id\": \"fun:009672d0\",\n    \"name\": \"UTFWin::CascadeEffect::HandleUIMessage\",\n    \"priority\": \"P0\",\n    \"provenance\": {\n      \"classifier\": \"triage-v4\",\n      \"generated_at\": \"2026-09-23T10:12:09Z\",\n      \"generator\": \"subagent-7-sequential-triage\",\n      \"sdk_name\": \"UTFWin::CascadeEffect::HandleUIMessage\",\n      \"snapshot\": \"2540f2ca\",\n      \"snapshot_sha256\": \"2540f2ca7cd361a72b559448fa5cf247eff3cee20d375b14ed0dd256c45229c8\",\n      \"vtable_addrs\": [\n        \"014414b8\"\n      ]\n    },\n    \"queue_state\": \"queued\",\n    \"rank\": 123\n  },\n  \"types\": [\n    \"Opaque*\",\n    \"openspore::reconstruction::pkg_utfwin_cascade_009672d0::CascadeEffectReceiver\",\n    \"openspore::reconstruction::pkg_utfwin_cascade_009672d0::Opaque\"\n  ],\n  \"unresolved_questions\": [\n    \"
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
  "body_end": "009672f2",
  "body_span_bytes": 35,
  "body_start": "009672d0",
  "callees": [
    "FUN_00950eb0"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "009672d0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "uVar1",
      "storage": "register:00000000:1",
      "type": "undefined1"
    },
    {
      "name": "in_ECX",
      "storage": "register:00000004:4",
      "type": "int"
    },
    {
      "name": "message",
      "storage": "Stack[0xc]:4",
      "type": "Message *"
    },
    {
      "name": "pWindow",
      "storage": "Stack[0x8]:4",
      "type": "IWindow *"
    },
    {
      "name": "this",
      "storage": "Stack[0x4]:4",
      "type": "CascadeEffect *"
    }
  ],
  "locals_count": 5,
  "mode": "live",
  "name": "UTFWin::CascadeEffect::HandleUIMessage",
  "namespace": "UTFWin",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "CascadeEffect *"
    },
    {
      "name": "pWindow",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "IWindow *"
    },
    {
      "name": "message",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Message *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x5672d0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool UTFWin::CascadeEffect::HandleUIMessage(CascadeEffect * this, IWindow * pWindow, Message * message)",
  "size_bytes": 35,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x009672d0",
  "vtables": {
    "referenced_by_vtables": [
      "0x014414b8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 3,
  "xrefs": [
    {
      "from": "014414c4"
    },
    {
      "from": "00967633"
    },
    {
      "from": "00967643"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__CascadeEffect__HandleUIMessage.c",
    "reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.cpp",
    "reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0.hpp",
    "reconstruction/staging/pkg-utfwin-cascade-009672d0/utfwin_cascade_009672d0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-cascade-009672d0/009672d0.json"
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
  "Opaque*",
  "openspore::reconstruction::pkg_utfwin_cascade_009672d0::CascadeEffectReceiver",
  "openspore::reconstruction::pkg_utfwin_cascade_009672d0::Opaque"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x014414b8"
]
```

## Conflicts

```json
[]
```
