# Evidence 0x00c0b7a0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `ccc2a6035631088b994749a3b39a4d10b1d697d4568181237e1268974db61a82`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "read once, at the first instruction only",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_note": "(boolean, 0 or 1)",
  "return_observation": "0x00c0b7ae SBB EAX,EAX and 0x00c0b7b0 NEG EAX together overwrite all 32 bits of EAX. Consumers agree the width is meaningful: 0x00d2c164 uses MOVZX ESI,AL, 0x00ba2835 and 0x00d2c1e6 use TEST AL,AL, and 0x00d2c156 uses SETZ CL over the AL byte. Had only AL been meaningful the compiler would have emitted SETNE AL rather than the SBB/NEG pair, so the dword width is the real contract.",
  "return_register": "EAX",
  "return_semantics": "A full dword in EAX that is exactly 0 or exactly 1, never an arbitrary true value and never a leftover pointer. The chain is: XOR ECX,ECX zeroes the compare operand; CMP ECX,[EAX + 0x60c] sets CF when the dword is non-zero; SBB EAX,EAX with EAX holding the sub-object pointer computes EAX - EAX - CF, i.e. 0xFFFFFFFF or 0; NEG then yields 1 or 0.",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
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
    "return_semantics": "unclassified_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "51e088d4f5691d68b959f96f4054d559772559b2b210c94bb5571f1b4eb1a069",
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
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0005"
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
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          2848,
          4396
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003",
        "obs-0004",
        "obs-0005"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0005"
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
        "obs-0005"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0005"
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
      "at": "0x00c0b7a0",
      "count": 2,
      "first_use": 0,
      "first_write_index": 1,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0xb20]",
      "reg": "ECX"
    },
    {
      "at": "0x00c0b7a0",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0xb20]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00c0b7a6",
      "definite": true,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_WRITE",
      "raw": "XOR ECX,ECX",
      "reg": "ECX",
      "write_kind": "zero"
    },
    {
      "at": "0x00c0b7a8",
      "count": 2,
      "first_use": 2,
      "first_write_index": 0,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "CMP ECX,dword ptr [EAX + 0x60c]",
      "reg": "EAX"
    },
    {
      "at": "0x00c0b7b2",
      "form": "RET",
      "id": "obs-0005",
      "imm": null,
      "index": 5,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 6,
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
    "confidence": "INFERRED",
    "distinct_offsets": 2,
    "max_offset": 4396,
    "offsets": [
      2848,
      4396
    ],
    "present": true,
    "register": "ECX",
    "shape": "R-DIRECT",
    "written_through": 0
  },
  "return": {
    "aggregate_evidence": {
      "bulk_write": false
    },
    "confidence": "INFERRED",
    "register": "EAX",
    "register_class": "aggregate_unknown",
    "type": null,
    "void_possible": false
  },
  "schema": "openspore-abi-inference-1",
  "seh_or_cookie_frame": false,
  "sret": {
    "ambiguity": null,
    "basis": "entry slot 0 is not written through a pointer; DERIVED absence is weak, a struct filled through another alias would be missed",
    "candidates": null,
    "confidence": "APPROXIMATION",
    "eax_holds_slot0_at_ret": null,
    "hypothesis_confidence": null,
    "present": false,
    "slot": null,
    "this_interaction": null
  },
  "stack_arguments": {
    "confidence": "APPROXIMATION",
    "derived_slots": 0,
    "gaps": 0,
    "not_complete": false,
    "observed_slots": 0,
    "slots": [],
    "total_bytes": 0,
    "widths_ambiguous": false
  },
  "tail_call": {
    "after_frame_setup": false,
    "form": null,
    "present": false,
    "target": null
  },
  "target": {
    "address_available": true,
    "image
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
    "va": "0x00ba27b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c042e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d2c000"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d342d0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d3cdc0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d581b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d58ea0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d5f780"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d841a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d87620"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00d8f560"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00dbc7a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00e8bf20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00f0e380"
  }
]
```

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
  "count": 6,
  "instructions": [
    {
      "address": "00c0b7a0",
      "instruction": "MOV EAX,dword ptr [ECX + 0xb20]"
    },
    {
      "address": "00c0b7a6",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00c0b7a8",
      "instruction": "CMP ECX,dword ptr [EAX + 0x60c]"
    },
    {
      "address": "00c0b7ae",
      "instruction": "SBB EAX,EAX"
    },
    {
      "address": "00c0b7b0",
      "instruction": "NEG EAX"
    },
    {
      "address": "00c0b7b2",
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
  "original_bytes": 11573,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"read once, at the first instruction only\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"(boolean, 0 or 1)\",\n    \"return_observation\": \"0x00c0b7ae SBB EAX,EAX and 0x00c0b7b0 NEG EAX together overwrite all 32 bits of EAX. Consumers agree the width is meaningful: 0x00d2c164 uses MOVZX ESI,AL, 0x00ba2835 and 0x00d2c1e6 use TEST AL,AL, and 0x00d2c156 uses SETZ CL over the AL byte. Had only AL been meaningful the compiler would have emitted SETNE AL rather than the SBB/NEG pair, so the dword width is the real contract.\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"A full dword in EAX that is exactly 0 or exactly 1, never an arbitrary true value and never a leftover pointer. The chain is: XOR ECX,ECX zeroes the compare operand; CMP ECX,[EAX + 0x60c] sets CF when the dword is non-zero; SBB EAX,EAX with EAX holding the sub-object pointer computes EAX - EAX - CF, i.e. 0xFFFFFFFF or 0; NEG then yields 1 or 0.\",\n    \"return_type\": \"std::uint32_t\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"model_parts_apply_properties_00447150\",\n      \"va\": \"0x00447150\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_insert_004786e0\",\n      \"va\": \"0x004786e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_entry_expand_004ad6f0\",\n      \"va\": \"0x004ad6f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 2,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"pair_vector_construct_004b62a0\",\n      \"va\": \"0x004b62a0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba27b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c042e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d2c000\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d342d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d3cdc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d581b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d58ea0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d5f780\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d841a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d87620\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d8f560\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dbc7a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e8bf20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00f0e380\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00ba2830\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba27b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba2856\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba27b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00ba2866\",\n        \"direction\": \"in\",\n        \"other\": \"0x00ba27b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00c04443\",\n        \"direction\": \"in\",\n        \"other\": \"0x00
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
  "body_end": "00c0b7b2",
  "body_span_bytes": 19,
  "body_start": "00c0b7a0",
  "callees": [],
  "callers": [
    "FUN_00d5f780",
    "FUN_00d342d0",
    "FUN_00ba27b0",
    "FUN_00d841a0",
    "FUN_00c042e0",
    "FUN_00d58ea0",
    "FUN_00d2c000",
    "FUN_00d3cdc0",
    "FUN_00d87620",
    "FUN_00f0e380",
    "FUN_00d581b0",
    "FUN_00d8f560",
    "FUN_00dbc7a0",
    "FUN_00e8bf20"
  ],
  "classification": "leaf",
  "dispatch": null,
  "entry_point": "00c0b7a0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00c0b7a0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x80b7a0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00c0b7a0(void)",
  "size_bytes": 19,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00c0b7a0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 20,
  "xrefs": [
    {
      "from": "00d5f842"
    },
    {
      "from": "00d5fb25"
    },
    {
      "from": "00d582d7"
    },
    {
      "from": "00d58f5c"
    },
    {
      "from": "00c04443"
    },
    {
      "from": "00ba2830"
    },
    {
      "from": "00ba2856"
    },
    {
      "from": "00ba2866"
    },
    {
      "from": "00d3d07e"
    },
    {
      "from": "00d2c14f"
    },
    {
      "from": "00d2c15f"
    },
    {
      "from": "00d2c1e1"
    },
    {
      "from": "00d345e3"
    },
    {
      "from": "00d8f657"
    },
    {
      "from": "00e8bfdf"
    },
    {
      "from": "00e8c000"
    },
    {
      "from": "00f0e47c"
    },
    {
      "from": "00d84445"
    },
    {
      "from": "00d88359"
    },
    {
      "from": "00dbd333"
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
    "reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.cpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0.hpp",
    "reconstruction/staging/wave13-w1-core-b09/sim_subflag_00c0b7a0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b09/00c0b7a0.json"
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
    "A differential fixture is cheap but needs a receiver whose +0xb20 sub-object is constructed, which static evidence does not supply.",
    "No original-process trace exists for this address, so the runtime values of the +0x608 and +0x60c flag cluster are unverified.",
    "The Cell stage has never been entered in any recorded run, so nothing here is runtime observed."
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
  "status": "unresolved"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "dword",
  "pointer to sub-object",
  "std::uint32_t (boolean, 0 or 1)"
]
```

## vtables

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## Conflicts

```json
[]
```
