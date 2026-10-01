# Evidence 0x00577310

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `8d5d44cf78322155e3cd9f7d19dcec7d0b1f639a947634ba924703871a26869c`

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
  "ordinary_stack_argument_slots": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4",
  "return_register": "EAX",
  "return_type": "void",
  "saved_registers": [
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x4"
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
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x4",
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
        "observed": false,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "source": "ret_immediate",
        "written": false
      }
    ],
    "stack_cleanup_bytes": 4,
    "stack_cleanup_owner": "callee",
    "termination": "RET 0x4"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +36, so the listing is not one path"
  ],
  "cleanup": {
    "bytes": 4,
    "confidence": "OBSERVED",
    "corroboration": "not_available",
    "evidence": "ret 0x4",
    "side": "callee"
  },
  "completeness": "CORE_RESOLVED",
  "conflicts": [],
  "content_sha256": "72b3092c29c4be5645f6db8524dd871da391a973369a75cdf49ac9cf1282c03f",
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
    "indirect_calls": 7,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0062"
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
        "obs-0062"
      ],
      "claim": "argument slots derived from the terminal immediate alone; no argument read was observed, so this is the popped area and not a parameter count",
      "confidence": "APPROXIMATION",
      "id": "A1-IMM",
      "value": {
        "derived_slots": 1,
        "total_bytes": 4
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0009",
        "obs-0010",
        "obs-0025",
        "obs-0038",
        "obs-0041",
        "obs-0048",
        "obs-0057"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          776,
          780
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0005",
        "obs-0006",
        "obs-0009",
        "obs-0010",
        "obs-0025",
        "obs-0038",
        "obs-0041",
        "obs-0048",
        "obs-0057",
        "obs-0062"
      ],
      "claim": "calling convention is __thiscall: the callee pops the stack arguments, which rules out cdecl and fastcall, and the receiver arrives in ECX",
      "confidence": "INFERRED",
      "id": "C6B",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0062"
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
        "obs-0062"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0062"
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
      "and_esp": null,
      "at": "0x00577310",
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
      "raw": "SUB ESP,0x28",
      "sub": 40
    },
    {
      "at": "0x00577310",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x28",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00577313",
      "count": 9,
      "first_use": 1,
      "first_write_index": 23,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH EBX",
      "reg": "EBX"
    },
    {
      "at": "0x00577314",
      "count": 10,
      "first_use": 2,
      "first_write_index": 3,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00577315",
      "count": 9,
      "first_use": 3,
      "first_write_index": 18,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00577315",
      "definite": true,
      "id": "obs-0006",
      "index": 3,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x0057731e",
      "count": 14,
      "first_use": 5,
      "first_write_index": 20,
      "id": "obs-0007",
      "index": 5,
  
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
  "count": 147,
  "instructions": [
    {
      "address": "00577310",
      "instruction": "SUB ESP,0x28"
    },
    {
      "address": "00577313",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00577314",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00577315",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00577317",
      "instruction": "CMP dword ptr [ESI + 0x308],0x0"
    },
    {
      "address": "0057731e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0057731f",
      "instruction": "JNZ 0x005773e2"
    },
    {
      "address": "00577325",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00577327",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00577329",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0057732b",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "0057732d",
      "instruction": "PUSH 0x13eb430"
    },
    {
      "address": "00577332",
      "instruction": "PUSH 0x34"
    },
    {
      "address": "00577334",
      "instruction": "CALL 0x00f473a0"
    },
    {
      "address": "00577339",
      "instruction": "ADD ESP,0x18"
    },
    {
      "address": "0057733c",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "0057733e",
      "instruction": "JZ 0x0057734d"
    },
    {
      "address": "00577340",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "00577342",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00577344",
      "instruction": "CALL 0x007b07e0"
    },
    {
      "address": "00577349",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "0057734b",
      "instruction": "JMP 0x0057734f"
    },
    {
      "address": "0057734d",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "0057734f",
      "instruction": "MOV EBX,dword ptr [ESI + 0x308]"
    },
    {
      "address": "00577355",
      "instruction": "CMP EDI,EBX"
    },
    {
      "address": "00577357",
      "instruction": "JZ 0x00577378"
    },
    {
      "address": "00577359",
      "instruction": "TEST EDI,EDI"
    },
    {
      "address": "0057735b",
      "instruction": "JZ 0x00577365"
    },
    {
      "address": "0057735d",
      "instruction": "MOV EAX,dword ptr [EDI]"
    },
    {
      "address": "0057735f",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00577361",
      "instruction": "MOV ECX,EDI"
    },
    {
      "address": "00577363",
      "instruction": "CALL EDX"
    },
    {
      "address": "00577365",
      "instruction": "MOV dword ptr [ESI + 0x308],EDI"
    },
    {
      "address": "0057736b",
      "instruction": "TEST EBX,EBX"
    },
    {
      "address": "0057736d",
      "instruction": "JZ 0x00577378"
    },
    {
      "address": "0057736f",
      "instruction": "MOV EAX,dword ptr [EBX]"
    },
    {
      "address": "00577371",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {
      "address": "00577374",
      "instruction": "MOV ECX,EBX"
    },
    {
      "address": "00577376",
      "instruction": "CALL EDX"
    },
    {
      "address": "00577378",
      "instruction": "MOV ECX,dword ptr [ESI + 0x308]"
    },
    {
      "address": "0057737e",
      "instruction": "LEA EAX,[ESP + 0x10]"
    },
    {
      "address": "00577382",
      "instruction": "MOV EDI,0x510a95b"
    },
    {
      "address": "00577387",
      "instruction": "MOV EBX,0x40464100"
    },
    {
      "address": "0057738c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "0057738d",
      "instruction": "MOV dword ptr [ESP + 0x14],0x8104e4b0"
    },
    {
      "address": "00577395",
      "instruction": "MOV dword ptr [ESP + 0x18],EDI"
    },
    {
      "address": "00577399",
      "instruction": "MOV dword ptr [ESP + 0x1c],EBX"
    },
    {
      "address": "0057739d",
      "instruction": "CALL 0x007b1e90"
    },
    {
      "address": "005773a2",
      "instruction": "LEA ECX,[ESP + 0x1c]"
    },
    {
      "address": "005773a6",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005773a7",
      "instruction": "MOV ECX,dword ptr [ESI + 0x308]"
    },
    {
      "address": "005773ad",
      "instruction": "MOV dword ptr [ESP + 0x20],0x9d1fcc2f"
    },
    {
      "address": "005773b5",
      "instruction": "MOV dword ptr [ESP + 0x24],EDI"
    },
    {
      "address": "005773b9",
      "instruction": "MOV dword ptr [ESP + 0x28],EBX"
    },
    {
      "address": "005773bd",
      "instruction": "CALL 0x007b1e90"
    },
    {
      "address": "005773c2",
      "instruction": "MOV ECX,dword ptr [ESI + 0x308]"
    },
    {
      "address": "005773c8",
      "instruction": "LEA EDX,[ESP + 0x28]"
    },
    {
      "address": "005773cc",
      "instruction": "PUSH EDX"
    },
    {
      "address": "005773cd",
      "instruction": "MOV dword ptr [ESP + 0x2c],0x7d708f46"
    },
    {
      "address": "005773d5",
      "instruction": "MOV dword ptr [ESP + 0x30],EDI"
    },
    {
      "address": "005773d9",
      "instruction": "MOV dword ptr [ESP + 0x34],EBX"
    },
    {
      "address": "005773dd",
      "instruction": "CALL 0x007b1e90"
    },
    {
      "address": "005773e2",
      "instruction": "MOV EBX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "005773e6",
      "instruction": "CMP EBX,-0x1"
    },
    {
      "address": "005773e9",
      "instruction": "JZ 0x005774e0"
    },
    {
      "address": "005773ef",
      "instruction": "MOV dword ptr [ESP + 0x38],0x0"
    },
    {
      "address": "005773f7",
      "instruction": "CALL 0x0067de30"
    },
    {
      "address": "005773fc",
      "instruction": "MOV ECX,dword ptr [ESP + 0x38]"
    },
    {
      "address": "00577400",
      "instruction": "MOV EDI,EAX"
    },
    {
      "address": "00577402",
      "instruction": "TEST ECX,ECX"
    },
    {
      "address": "00577404",
      "instruction": "JZ 0x00577415"
    },
    {
      "address
[TRUNCATED]
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
  "original_bytes": 9388,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET 0x4\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_cleanup_bytes\": 4,\n    \"stack_cleanup_owner\": \"callee\",\n    \"termination\": \"RET 0x4\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_00588570\",\n      \"va\": \"0x00588570\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_vtable:vtable:0x013f57f8\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 4,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x005773f7\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067de30\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057749d\",\n        \"direction\": \"out\",\n        \"other\": \"0x006a12a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00577344\",\n        \"direction\": \"out\",\n        \"other\": \"0x007b07e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00577452\",\n        \"direction\": \"out\",\n        \"other\": \"0x007b07e0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0057739d\",\n        \"direction\": \"out\",\n        \"other\": \"0x007b1e90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005773bd\",\n        \"direction\": \"out\",\n        \"other\": \"0x007b1e90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005773dd\",\n        \"direction\": \"out\",\n        \"other\": \"0x007b1e90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x005774cc\",\n        \"direction\": \"out\",\n        \"other\": \"0x007b1e90\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00577334\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00577442\",\n        \"direction\": \"out\",\n        \"other\": \"0x00f473a0\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0064\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"INFERRED\",\n  \"globals\": [\n    \"global:WARN\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"FUN_00577310\",\n  \"normalized_symbol\": \"FUN_00577310\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"candidate\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": null,\n    \"file\": null,\n    \"files\": [\n      \"reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310.cpp\",\n      \"reconstruction/staging/pkg-swarm-w2-00
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
  "body_end": "005774e8",
  "body_span_bytes": 473,
  "body_start": "00577310",
  "callees": [
    "App::Property::GetKeyInstanceID",
    "FUN_00f473a0",
    "FUN_007b07e0",
    "FUN_0067de30",
    "FUN_007b1e90"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00577310",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_1c",
      "storage": "Stack[-0x1c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_20",
      "storage": "Stack[-0x20]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 3,
  "mode": "live",
  "name": "FUN_00577310",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x177310",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00577310(void)",
  "size_bytes": 473,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00577310",
  "vtables": {
    "referenced_by_vtables": [
      "0x013f57f8"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "013f5840"
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
  "global:WARN"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310.cpp",
    "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w2-00577310/00577310.json"
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
  "void"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x013f57f8"
]
```

## Conflicts

```json
[]
```
