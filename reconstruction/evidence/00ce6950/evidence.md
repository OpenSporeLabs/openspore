# Evidence 0x00ce6950

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `b4ab19b74b8b5c4a7f50e8a967cb2ca2149b99ad3f9d0106abd11171cc602710`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "fastcall-compatible one-argument ECX function",
  "hidden_receiver": "ECX is the opaque context-window pointer",
  "ordinary_stack_argument_slots": 0,
  "ret_form": "RET",
  "return_note": "raw 32-bit word",
  "return_type": "OpaqueContextWord",
  "stack_cleanup_bytes": 0
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
    "return_semantics": "pointer_like_in_EAX",
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
  "content_sha256": "de95c5c6fc13e3db84cc5fcf160bd90196aef2648e2ffb8f0788b5a2c38836fb",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": "fastcall-compatible one-argument ECX function"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0003"
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
        "obs-0002"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          388
        ],
        "register": "ECX",
        "written_through": 0
      }
    },
    {
      "based_on": [
        "obs-0001",
        "obs-0002",
        "obs-0003"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0003"
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
        "obs-0003"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0003"
      ],
      "claim": "the last value written to EAX classifies as pointer_like",
      "confidence": "INFERRED",
      "id": "RT2",
      "value": {
        "register_class": "pointer_like"
      }
    }
  ],
  "observations": [
    {
      "at": "0x00ce6950",
      "count": 1,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EAX,dword ptr [ECX + 0x184]",
      "reg": "ECX"
    },
    {
      "at": "0x00ce6950",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,dword ptr [ECX + 0x184]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00ce6956",
      "form": "RET",
      "id": "obs-0003",
      "imm": null,
      "index": 1,
      "kind": "RET",
      "raw": "RET"
    }
  ],
  "parse": {
    "declared_count": 2,
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
    "distinct_offsets": 1,
    "max_offset": 388,
    "offsets": [
      388
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
    "register_class": "pointer_like",
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
    "image_base": "0x00400000",
    "instructions": 2,
    "syntax": "intel",
    "va": "0x00ce6950"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_INFERRED"
}
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
    "va": "0x00aeb3e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb890"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aebe90"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba4f30"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5270"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5650"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba57f0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba58f3"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5a60"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ba5bd3"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00baf790"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb99e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf0330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf03e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf0810"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bf1270"
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
  "count": 2,
  "instructions": [
    {
      "address": "00ce6950",
      "instruction": "MOV EAX,dword ptr [ECX + 0x184]"
    },
    {
      "address": "00ce6956",
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
  "original_bytes": 14695,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"fastcall-compatible one-argument ECX function\",\n    \"hidden_receiver\": \"ECX is the opaque context-window pointer\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"ret_form\": \"RET\",\n    \"return_note\": \"raw 32-bit word\",\n    \"return_type\": \"OpaqueContextWord\",\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 16,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb3e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb890\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aebe90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba4f30\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5650\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba57f0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba58f3\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5a60\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ba5bd3\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00baf790\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb99e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf0330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf03e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf0810\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf1270\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf14b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf3180\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bf74a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c314a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c31550\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c316c0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c32610\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c33cc0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c35240\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c35810\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c455b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c45f90\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c472e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \
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
  "body_end": "00ce6956",
  "body_span_bytes": 7,
  "body_start": "00ce6950",
  "callees": [],
  "callers": [
    "FUN_00c74550",
    "FUN_0102caa0",
    "FUN_00c830f0",
    "FUN_00c4dd10",
    "FUN_00bf1270",
    "FUN_00cfd220",
    "FUN_0106a7b0",
    "FUN_0102cd90",
    "FUN_0103fc10",
    "FUN_00bf0810",
    "FUN_0102d1b0",
    "FUN_00c316c0",
    "FUN_00c77450",
    "FUN_01045910",
    "FUN_01056160",
    "FUN_00cb6090",
    "FUN_00ba5bd3",
    "FUN_00c314a0",
    "FUN_0100aec0",
    "FUN_00fdeac0",
    "FUN_00cf50e0",
    "FUN_0100fbc0",
    "FUN_01067b60",
    "FUN_0103eff0",
    "FUN_010151a0",
    "FUN_01058c90",
    "FUN_00d06a50",
    "FUN_01004e50",
    "FUN_00c74690",
    "FUN_00e1bbc0",
    "FUN_010134d0",
    "FUN_00c35240",
    "FUN_00c73f80",
    "FUN_00bf74a0",
    "FUN_010225d0",
    "FUN_00dca100",
    "FUN_01038410",
    "FUN_00c74730",
    "FUN_00daafb0",
    "FUN_00c74400",
    "FUN_00bf3180",
    "FUN_00dd5160",
    "FUN_00e39ab0",
    "FUN_00c7ae80",
    "FUN_00c45f90",
    "FUN_00aeb890",
    "FUN_0102c9e0",
    "FUN_00c35810",
    "FUN_00fef140",
    "FUN_00fe9580",
    "FUN_00c74650",
    "FUN_00c73ff0",
    "FUN_00c455b0",
    "FUN_010543e0",
    "FUN_00c74210",
    "FUN_00cfeeb0",
    "FUN_0102daa0",
    "FUN_00c47350",
    "FUN_0102cc30",
    "FUN_00c741a0",
    "FUN_00c75520",
    "FUN_00bb99e0",
    "FUN_00c33cc0",
    "FUN_00c57ad0",
    "FUN_00fe0570",
    "FUN_00bf14b0",
    "FUN_00baf790",
    "FUN_0100e730",
    "FUN_00cfbc10",
    "FUN_00c73f10",
    "FUN_00c7bd40",
    "FUN_00d056c0",
    "FUN_00c73ea0",
    "FUN_00ba5650",
    "FUN_00ba57f0",
    "FUN_00c73250",
    "FUN_010488e0",
    "FUN_00e34bd0",
    "FUN_00cd1960",
    "FUN_00c472e0",
    "FUN_00ba58f3",
    "FUN_00c744e0",
    "FUN_00c32610",
    "FUN_0102df20",
    "FUN_00c74470",
    "FUN_0102cf10",
    "FUN_00c745d0",
    "FUN_00aeb3e0",
    "FUN_00c5c470",
    "FUN_00bf0330",
    "FUN_00d05730",
    "FUN_00d01ab0",
    "FUN_00ba4f30",
    "FUN_00ba5a60",
    "FUN_00ba5270",
    "FUN_0102ce30",
    "FUN_00e34a00",
    "FUN_00c74280",
    "FUN_00ce8ab0",
    "FUN_01072d40",
    "FUN_00c73cf0",
    "FUN_00cde2f0",
    "FUN_00bf03e0",
    "FUN_00aebe90",
    "FUN_0102cae0",
    "FUN_00c706d0",
    "FUN_01045740",
    "FUN_00c71750",
    "FUN_00cb61d0",
    "FUN_00c31550",
    "FUN_0103e8e0",
    "FUN_00cf31f0"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00ce6950",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00ce6950",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x8e6950",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ce6950(void)",
  "size_bytes": 7,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ce6950",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 100,
  "xrefs": [
    {
      "from": "00c316ce"
    },
    {
      "from": "00c71787"
    },
    {
      "from": "00fe9ea8"
    },
    {
      "from": "00fe9ed9"
    },
    {
      "from": "00fea103"
    },
    {
      "from": "00aeb4ae"
    },
    {
      "from": "00bb99e9"
    },
    {
      "from": "00c3152b"
    },
    {
      "from": "00c31624"
    },
    {
      "from": "00c70733"
    },
    {
      "from": "00c70749"
    },
    {
      "from": "00c358ac"
    },
    {
      "from": "00ba5ca6"
    },
    {
      "from": "00d01af6"
    },
    {
      "from": "00d0578a"
    },
    {
      "from": "00c7be08"
    },
    {
      "from": "01045776"
    },
    {
      "from": "00ba5b52"
    },
    {
      "from": "00bf147e"
    },
    {
      "from": "00aec2fd"
    },
    {
      "from": "00aeb8a1"
    },
    {
      "from": "00bf1749"
    },
    {
      "from": "00bf3271"
    },
    {
      "from": "00bf337f"
    },
    {
      "from": "00bf33f5"
    },
    {
      "from": "00bf76f8"
    },
    {
      "from": "00c352b2"
    },
    {
      "from": "00c74592"
    },
    {
      "from": "00c744e9"
    },
    {
      "from": "00cfeff6"
    },
    {
      "from": "00cff0d7"
    },
    {
      "from": "00cff150"
    },
    {
      "from": "00cff2c6"
    },
    {
      "from": "00cff419"
    },
    {
      "from": "00cff4b7"
    },
    {
      "from": "00cff689"
    },
    {
      "from": "00cff802"
    },
    {
      "from": "00cffa5a"
    },
    {
      "from": "00cffc2a"
    },
    {
      "from": "0102e233"
    },
    {
      "from": "0102e390"
    },
    {
      "from": "0102e768"
    },
    {
      "from": "0102e7c0"
    },
    {
      "from": "0102e7da"
    },
    {
      "from": "0102ebd6"
    },
    {
      "from": "0102edb5"
    },
    {
      "from": "00c4732a"
    },
    {
      "from": "00e39b72"
    },
    {
      "from": "00c7554f"
    },
    {
      "from": "0102ca7d"
    },
    {
      "from": "0102cac6"
    },
    {
      "from": "0102cc0a"
    },
    {
      "from": "0102cce1"
    },
    {
      "from": "0102ce10"
    },
    {
      "from": "0102ceea"
    },
    {
      "from": "0102d092"
    },
    {
      "from": "0102d6d9"
    },
    {
      "from": "0102de1b"
    },
    {
      "from": "0103e911"
    },
    {
      "from": "0103fd61"
    },
    {
      "from": "00c74619"
    },
    {
      "from": "00c7479d"
    },
    {
      "from": "00c747d6"
    },
    {
      "
[TRUNCATED]
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
    "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.cpp",
    "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3.hpp",
    "reconstruction/staging/pkg11-h4-helper-wave3/helper_wave3_model_test.cpp",
    "src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.cpp",
    "src/reconstruction/pkg11_h4_helper_wave3/helper_wave3.hpp",
    "src/reconstruction/pkg11_h4_helper_wave3/helper_wave3_model_test.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-sim-social-world-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg11-h4-helper-wave3/00ce6950.json"
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
  "OpaqueContextWord raw 32-bit word"
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
    "derived": "__thiscall",
    "field": "calling_convention",
    "kind": "derived_vs_persisted",
    "persisted": "fastcall-compatible one-argument ECX function",
    "resolution_status": "unresolved"
  }
]
```
