# Evidence 0x00b3d230

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `c7b9f5576440eec6382727f32d67600e7a653b4e2840e485f8e7fee2dd6aa2ef`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": false,
  "ordinary_stack_argument_slots": 0,
  "ordinary_stack_arguments": [],
  "receiver": false,
  "receiver_register": null,
  "ret_form": "RET",
  "return_register": [
    "EAX",
    "AL"
  ],
  "return_semantics": "the four bytes stored at absolute address 0x0167eac0, whole, in EAX",
  "return_type": "uint32",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "none",
  "termination": "RET at 0x00b3d235 (bare C3, no immediate operand); the instruction after it, 0x00b3d236, is a CC int3 pad byte, so the function has exactly one exit and it is the terminal RET"
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
    "receiver": false,
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "pointer_like_in_EAX",
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "no_discriminator: no stack-argument read and no positive receiver evidence"
  ],
  "cleanup": {
    "bytes": 0,
    "confidence": "INFERRED",
    "corroboration": "not_available",
    "evidence": "ret with no immediate, no stack reads",
    "side": "caller"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "43e80526c17cd2096750786bd6158393f1b7f6003482c502751e133100c1df51",
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
    "ghidra_parameter_count": 0,
    "persisted": "no_information",
    "persisted_calling_convention": null
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "ECX is never read in any form, so there is no register receiver",
      "confidence": "OBSERVED",
      "id": "R2",
      "value": {
        "present": false
      }
    },
    {
      "based_on": [
        "obs-0002"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0002"
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
        "obs-0002"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0002"
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
      "at": "0x00b3d230",
      "definite": true,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EAX,[0x0167eac0]",
      "reg": "EAX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00b3d235",
      "form": "RET",
      "id": "obs-0002",
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
    "confidence": "OBSERVED",
    "distinct_offsets": 0,
    "max_offset": null,
    "offsets": [],
    "present": false,
    "register": null,
    "shape": null,
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
    "va": "0x00b3d230"
  },
  "variadic": "UNKNOWN",
  "verdict": "ABI_UNKNOWN"
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
    "va": "0x00adad70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00adf840"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b19440"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b279e0"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00b69990"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c0d3a0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c38510"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00c69540"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ccc640"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ccefb0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cd9da0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cde660"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ce0a20"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00ce8ab0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00cf1440"
  }
]
```

## contradictions

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## decompilation

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json
"\nundefined4 FUN_00b3d230(void)\n\n{\n  return DAT_0167eac0;\n}\n\n"
```

## disassembly

- Availability: `available`
- Evidence state: `LIVE`
- Provenance: `GhidraMCP /disassemble_function`

```json
{
  "count": 2,
  "instructions": [
    {
      "address": "00b3d230",
      "instruction": "MOV EAX,[0x0167eac0]"
    },
    {
      "address": "00b3d235",
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
  "original_bytes": 21065,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": false,\n    \"ordinary_stack_argument_slots\": 0,\n    \"ordinary_stack_arguments\": [],\n    \"receiver\": false,\n    \"receiver_register\": null,\n    \"ret_form\": \"RET\",\n    \"return_register\": [\n      \"EAX\",\n      \"AL\"\n    ],\n    \"return_semantics\": \"the four bytes stored at absolute address 0x0167eac0, whole, in EAX\",\n    \"return_type\": \"uint32\",\n    \"return_width_bytes\": 4,\n    \"saved_registers\": [],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"none\",\n    \"termination\": \"RET at 0x00b3d235 (bare C3, no immediate operand); the instruction after it, 0x00b3d236, is a CC int3 pad byte, so the function has exactly one exit and it is the terminal RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"Runtime validation against the original process is an open capability gate: no original-process trace exists in this repository, nothing was attempted, and nothing failed. The validation report for this target records runtime.status GATED with validated 0.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adad70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00adf840\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b19440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b279e0\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00b69990\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c0d3a0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c38510\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00c69540\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ccc640\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ccefb0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cd9da0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cde660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ce0a20\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00ce8ab0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf1440\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf14d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf4660\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cf71d0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfbc10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00cfe160\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d0e170\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00d100b0\"\n      },\n      {\n        \"name\": null,\n
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
  "body_end": "00b3d235",
  "body_span_bytes": 6,
  "body_start": "00b3d230",
  "callees": [],
  "callers": [
    "FUN_00ef10c0",
    "FUN_00ef0ee0",
    "FUN_00fe0570",
    "FUN_01016950",
    "FUN_00cd9da0",
    "FUN_00cf71d0",
    "FUN_00fdc800",
    "FUN_0106ba00",
    "FUN_00fe0f40",
    "FUN_0106a0a0",
    "FUN_00fda2e0",
    "FUN_01066d60",
    "FUN_00d43e30",
    "FUN_00d100b0",
    "FUN_00adf840",
    "FUN_00b69990",
    "FUN_00fe2ab0",
    "FUN_00ce0a20",
    "FUN_00f11ca0",
    "FUN_00cde660",
    "FUN_00d30830",
    "FUN_00ef1e00",
    "FUN_00ef0cd0",
    "FUN_00cfe160",
    "FUN_00cf14d0",
    "FUN_00f11f90",
    "FUN_00b279e0",
    "FUN_00ccc640",
    "FUN_00ef2fe0",
    "FUN_00b19440",
    "FUN_01066dd0",
    "FUN_01016070",
    "FUN_00ccefb0",
    "FUN_00eda130",
    "FUN_00c38510",
    "FUN_01003a50",
    "FUN_00ffd390",
    "FUN_00eda9a0",
    "FUN_00adad70",
    "FUN_00fe19a0",
    "FUN_00fdcee0",
    "FUN_00d1cdf0",
    "FUN_00fde3e0",
    "FUN_00c0d3a0",
    "FUN_010691e0",
    "FUN_00cf4660",
    "FUN_00de4720",
    "FUN_00efdee0",
    "FUN_00cfbc10",
    "FUN_00d0e170",
    "FUN_00fdbee0",
    "FUN_01073700",
    "FUN_00b28ec0",
    "FUN_00cf1440",
    "FUN_00e35370",
    "FUN_0106c930",
    "FUN_0106cc70",
    "FUN_00c69540",
    "FUN_00ce8ab0",
    "FUN_01071570"
  ],
  "classification": "stub",
  "dispatch": null,
  "entry_point": "00b3d230",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_00b3d230",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x73d230",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00b3d230(void)",
  "size_bytes": 6,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00b3d230",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 94,
  "xrefs": [
    {
      "from": "00b29355"
    },
    {
      "from": "00c0d3bb"
    },
    {
      "from": "00adfc2a"
    },
    {
      "from": "00c3852d"
    },
    {
      "from": "01066de2"
    },
    {
      "from": "00b19449"
    },
    {
      "from": "00b27cc1"
    },
    {
      "from": "00b27dfb"
    },
    {
      "from": "00fde57c"
    },
    {
      "from": "01003acf"
    },
    {
      "from": "010169e6"
    },
    {
      "from": "01066d83"
    },
    {
      "from": "0106ba3b"
    },
    {
      "from": "0106baa7"
    },
    {
      "from": "0106a0a9"
    },
    {
      "from": "0106cca7"
    },
    {
      "from": "0106cded"
    },
    {
      "from": "01073db4"
    },
    {
      "from": "00d10184"
    },
    {
      "from": "00ffd6bf"
    },
    {
      "from": "00c6955d"
    },
    {
      "from": "00ce0a3c"
    },
    {
      "from": "00ccc77f"
    },
    {
      "from": "00b699b8"
    },
    {
      "from": "00cceff4"
    },
    {
      "from": "00cd9eea"
    },
    {
      "from": "00cdec36"
    },
    {
      "from": "00ce8c8c"
    },
    {
      "from": "00cf1444"
    },
    {
      "from": "00cf14dc"
    },
    {
      "from": "00cf467f"
    },
    {
      "from": "00cf72e8"
    },
    {
      "from": "00cfe24b"
    },
    {
      "from": "00cfe56d"
    },
    {
      "from": "00cfe599"
    },
    {
      "from": "00cfc8de"
    },
    {
      "from": "00d0fb8e"
    },
    {
      "from": "00d1d28d"
    },
    {
      "from": "00d1d2b9"
    },
    {
      "from": "00d1d2c9"
    },
    {
      "from": "00d3084a"
    },
    {
      "from": "00d454db"
    },
    {
      "from": "00de47cf"
    },
    {
      "from": "00e353ae"
    },
    {
      "from": "00edaa61"
    },
    {
      "from": "00ef0f4a"
    },
    {
      "from": "00ef0d22"
    },
    {
      "from": "00eda144"
    },
    {
      "from": "00efdee9"
    },
    {
      "from": "00ef1214"
    },
    {
      "from": "00ef3104"
    },
    {
      "from": "00ef3349"
    },
    {
      "from": "00ef3359"
    },
    {
      "from": "00f11cb4"
    },
    {
      "from": "00f12068"
    },
    {
      "from": "00fdbef1"
    },
    {
      "from": "00fdc8fc"
    },
    {
      "from": "00fdc91c"
    },
    {
      "from": "010717a6"
    },
    {
      "from": "00fdd190"
    },
    {
      "from": "00fe1132"
    },
    {
      "from": "00fe1226"
    },
    {
      "from": "01069212"
    },
    {
      "from": "0106c951"
    },
    {
      "from": "00fe19ad"
    },
    {
      "from": "00fe2e0b"
    },
    {
      "from": "010162e6"
    },
    {
      "from": "00fe09e9"
    },
    {
      "from": "00fe0a34"
    },
    {
      "from": "00cfccd4"
    },
    {
      "from": "00cfccea"
    },
    {
      "from": "00d43e5c"
    },
    {
      "from": "00d44d6c"
    },
    {
      "from": "00d450c4"
    },
    {
      "from": "00d450da"
    },
    {
      "from": "00cde94d"
    },
    {
      "from": "00cde960"
    },
    {
      "from": "00ef203d"
    },
    {
      "from": "00adad9d"
    },
    {
      "from": "00cdef5e"
    },
    {
      "from": "00cdf2dd"
    },
    {
      "from": "00cdfdd7"
    },
    {
      "from": "00cdfe05"
    },
    {
      "from": "00d1bf29"
    },
    {
      "from": "00d45898"
    },
    {
      "from": "00d46381"
    },
    {
      "from": "00dddc0c"
    },
    {
      "from": "00ed9ce7"
    },
    {
      "from": "00fda300"
    },
    {
      "from": "0100cdc7"
    },
    {
      "from": "0100ced
[TRUNCATED]
```

## globals

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "global:g_0167eac0, a reference alias to the single modelled slot word"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.cpp",
    "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230.hpp",
    "reconstruction/staging/pkg-w2-00b3d230/root_accessor_00b3d230_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00b3d230/00b3d230.json"
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
    "A differential run must call this VA through a direct call, as all 60 recorded callers do; there is no vtable slot and therefore no dispatch path to reconstruct for it.",
    "The static validator reported no target source span (validation.json source.path null), so no structural check has been run against the staged sources for this package; that is an orchestrator-side gap, not a pass.",
    "The value returned by 0x00b3d230 is whatever is stored at 0x0167eac0 at the moment of the call, so a differential run must establish that dword's value first; the body itself does not determine it and the image carries no initializer for that address."
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
  "std::uint32_t",
  "uint32"
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
