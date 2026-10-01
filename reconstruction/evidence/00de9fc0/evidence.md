# Evidence 0x00de9fc0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `7098e37377db20f239f9f8ab5c7a985bd6965006c312db180014dd4657a138b9`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "calling_convention": "fastcall-style method; Ghidra reports unknown convention",
  "return_observation": "The function returns after the final guarded cleanup/free sequence and has no value return.",
  "return_type": "void",
  "stack_arguments": [],
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
    "ret_form": "RET",
    "return_register": "EAX",
    "return_semantics": "unclassified_in_EAX",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
    "stack_cleanup_bytes": 0,
    "stack_cleanup_owner": "caller",
    "termination": "RET"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at +124, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "receiver_not_determinable: ecx_read_without_deref",
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
  "content_sha256": "d1323cfc41d7c65530eb14fa22cbbfe004f2f30636d7e03fcbd8f85301fb5a29",
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
    "persisted_calling_convention": "fastcall-style method; Ghidra reports unknown convention"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0099"
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
        "obs-0007",
        "obs-0008",
        "obs-0009",
        "obs-0010",
        "obs-0019",
        "obs-0020",
        "obs-0024",
        "obs-0028",
        "obs-0029",
        "obs-0033",
        "obs-0039",
        "obs-0043",
        "obs-0047",
        "obs-0053",
        "obs-0055",
        "obs-0057",
        "obs-0065",
        "obs-0066",
        "obs-0068",
        "obs-0075",
        "obs-0077",
        "obs-0080",
        "obs-0091",
        "obs-0092"
      ],
      "claim": "the register receiver is undetermined: ecx_read_without_deref",
      "confidence": "UNKNOWN",
      "id": "R0",
      "value": {
        "reason": "ecx_read_without_deref",
        "register": null
      }
    },
    {
      "based_on": [
        "obs-0099"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0099"
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
        "obs-0099"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0099"
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
      "id": "obs-0001"
    },
    {
      "id": "obs-0002"
    },
    {
      "id": "obs-0003"
    },
    {
      "id": "obs-0004"
    },
    {
      "id": "obs-0005"
    },
    {
      "id": "obs-0006"
    },
    {
      "id": "obs-0007"
    },
    {
      "id": "obs-0008"
    },
    {
      "id": "obs-0009"
    },
    {
      "id": "obs-0010"
    },
    {
      "id": "obs-0011"
    },
    {
      "id": "obs-0012"
    },
    {
      "id": "obs-0013"
    },
    {
      "id": "obs-0014"
    },
    {
      "id": "obs-0015"
    },
    {
      "id": "obs-0016"
    },
    {
      "id": "obs-0017"
    },
    {
      "id": "obs-0018"
    },
    {
      "id": "obs-0019"
    },
    {
      "id": "obs-0020"
    },
    {
      "id": "obs-0021"
    },
    {
      "id": "obs-0022"
    },
    {
      "id": "obs-0023"
    },
    {
      "id": "obs-0024"
    },
    {
      "id": "obs-0025"
    },
    {
      "id": "obs-0026"
    },
    {
      "id": "obs-0027"
    },
    {
      "id": "obs-0028"
    },
    {
      "id": "obs-0029"
    },
    {
      "id": "obs-0030"
    },
    {
      "id": "obs-0031"
    },
    {
      "id": "obs-0032"
    },
    {
      "id": "obs-0033"
    },
    {
      "id": "obs-0034"
    },
    {
      "id": "obs-0035"
    },
    {
      "id": "obs-0036"
    },
    {
      "id": "obs-0037"
    },
    {
      "id": "obs-0038"
    },
    {
      "id": "obs-0039"
    },
    {
      "id": "obs-0040"
    },
    {
      "id": "obs-0041"
    },
    {
      "id": "obs-0042"
    },
    {
      "id": "obs-0043"
    },
    {
      "id": "obs-0044"
    },
    {
      "id": "obs-0045"
    },
    {
      "id": "obs-0046"
    },
    {
      "id": "obs-0047"
    },
    {
      "id": "obs-0048"
    },
    {
      "id": "obs-0049"
    },
    {
      "id": "obs-0050"
    },
    {
      "id": "obs-0051"
    },
    {
      "id": "obs-0052"
    },
    {
      "id": "obs-0053"
    },
    {
      "id": "obs-0054"
    },
    {
      "id": "obs-0055"
    },
    {
      "id": "obs-0056"
    },
    {
      "id": "obs-0057"
    },
    {
      "id": "obs-0058"
    },
    {
      "id": "obs-0059"
    },
    {
      "id": "obs-0060"
    },
    {
  
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
    "va": "0x00dea200"
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
  "count": 193,
  "instructions": [
    {
      "address": "00de9fc0",
      "instruction": "SUB ESP,0x64"
    },
    {
      "address": "00de9fc3",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00de9fc4",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00de9fc5",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00de9fc6",
      "instruction": "XOR ESI,ESI"
    },
    {
      "address": "00de9fc8",
      "instruction": "PUSH 0x366a930d"
    },
    {
      "address": "00de9fcd",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "00de9fcf",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00de9fd0",
      "instruction": "PUSH 0x2dd90af"
    },
    {
      "address": "00de9fd5",
      "instruction": "LEA ECX,[ESP + 0x58]"
    },
    {
      "address": "00de9fd9",
      "instruction": "MOV dword ptr [ESP + 0x1c],EBP"
    },
    {
      "address": "00de9fdd",
      "instruction": "MOV dword ptr [ESP + 0x30],ESI"
    },
    {
      "address": "00de9fe1",
      "instruction": "MOV dword ptr [ESP + 0x34],ESI"
    },
    {
      "address": "00de9fe5",
      "instruction": "MOV dword ptr [ESP + 0x38],ESI"
    },
    {
      "address": "00de9fe9",
      "instruction": "CALL 0x00558960"
    },
    {
      "address": "00de9fee",
      "instruction": "MOV EDX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00de9ff2",
      "instruction": "CMP EDX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00de9ff6",
      "instruction": "JNC 0x00dea00d"
    },
    {
      "address": "00de9ff8",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "00de9ffa",
      "instruction": "ADD EDX,0x24"
    },
    {
      "address": "00de9ffd",
      "instruction": "MOV dword ptr [ESP + 0x28],EDX"
    },
    {
      "address": "00dea001",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "00dea003",
      "instruction": "JZ 0x00dea018"
    },
    {
      "address": "00dea005",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dea006",
      "instruction": "CALL 0x00606880"
    },
    {
      "address": "00dea00b",
      "instruction": "JMP 0x00dea018"
    },
    {
      "address": "00dea00d",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dea00e",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00dea00f",
      "instruction": "LEA ECX,[ESP + 0x2c]"
    },
    {
      "address": "00dea013",
      "instruction": "CALL 0x004e39d0"
    },
    {
      "address": "00dea018",
      "instruction": "MOV EAX,dword ptr [ESP + 0x60]"
    },
    {
      "address": "00dea01c",
      "instruction": "MOV ECX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "00dea020",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dea021",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00dea022",
      "instruction": "LEA ECX,[ESP + 0x64]"
    },
    {
      "address": "00dea026",
      "instruction": "CALL 0x004e39a0"
    },
    {
      "address": "00dea02b",
      "instruction": "MOV EAX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "00dea02f",
      "instruction": "CMP EAX,ESI"
    },
    {
      "address": "00dea031",
      "instruction": "JZ 0x00dea041"
    },
    {
      "address": "00dea033",
      "instruction": "CMP dword ptr [EAX + -0x4],ESI"
    },
    {
      "address": "00dea036",
      "instruction": "JZ 0x00dea041"
    },
    {
      "address": "00dea038",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dea039",
      "instruction": "CALL 0x00f47380"
    },
    {
      "address": "00dea03e",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00dea041",
      "instruction": "PUSH 0x913b23be"
    },
    {
      "address": "00dea046",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00dea047",
      "instruction": "PUSH 0x3cc89b1"
    },
    {
      "address": "00dea04c",
      "instruction": "LEA ECX,[ESP + 0x58]"
    },
    {
      "address": "00dea050",
      "instruction": "CALL 0x00558960"
    },
    {
      "address": "00dea055",
      "instruction": "MOV EDX,dword ptr [ESP + 0x28]"
    },
    {
      "address": "00dea059",
      "instruction": "CMP EDX,dword ptr [ESP + 0x2c]"
    },
    {
      "address": "00dea05d",
      "instruction": "JNC 0x00dea074"
    },
    {
      "address": "00dea05f",
      "instruction": "MOV ECX,EDX"
    },
    {
      "address": "00dea061",
      "instruction": "ADD EDX,0x24"
    },
    {
      "address": "00dea064",
      "instruction": "MOV dword ptr [ESP + 0x28],EDX"
    },
    {
      "address": "00dea068",
      "instruction": "CMP ECX,ESI"
    },
    {
      "address": "00dea06a",
      "instruction": "JZ 0x00dea07f"
    },
    {
      "address": "00dea06c",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dea06d",
      "instruction": "CALL 0x00606880"
    },
    {
      "address": "00dea072",
      "instruction": "JMP 0x00dea07f"
    },
    {
      "address": "00dea074",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dea075",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00dea076",
      "instruction": "LEA ECX,[ESP + 0x2c]"
    },
    {
      "address": "00dea07a",
      "instruction": "CALL 0x004e39d0"
    },
    {
      "address": "00dea07f",
      "instruction": "MOV EDX,dword ptr [ESP + 0x60]"
    },
    {
      "address": "00dea083",
      "instruction": "MOV EAX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "00dea087",
      "instruction": "PUSH EDX"
    },
    {
      "address": "00dea088",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00dea089",
      "instruction": "LEA ECX,[ESP + 0x64]"
    },
    {
      "address": "00dea08d",
      "instruction": "CALL 0x004e39a0"
    },
    {
      "address": "00dea092",
      "instruction": "MOV EAX,dword ptr [ESP + 0x5c]"
    },
    {
      "address": "00dea096",
      "instruction": "CMP EAX,ESI"
    },
    {
      "add
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
  "original_bytes": 17322,
  "preview": "{\n  \"abi\": {\n    \"calling_convention\": \"fastcall-style method; Ghidra reports unknown convention\",\n    \"return_observation\": \"The function returns after the final guarded cleanup/free sequence and has no value return.\",\n    \"return_type\": \"void\",\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 14,\n      \"symbol\": \"cSpaceInventoryItem_ctor_00c877f0\",\n      \"va\": \"0x00c877f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea250\",\n      \"va\": \"0x00aea250\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aea5d0\",\n      \"va\": \"0x00aea5d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_00aeb160\",\n      \"va\": \"0x00aeb160\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"Simulator_cCommManager_CreateAndDispatchEvent_00aeb720\",\n      \"va\": \"0x00aeb720\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 8,\n      \"symbol\": \"FUN_0102d1b0\",\n      \"va\": \"0x0102d1b0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"A linkable runtime model for the service owner, descriptor map, property record allocator, and game-mode manager is not available without changing the integrated PKG-12 boundary.\",\n    \"Concrete vtable targets and service return types remain unresolved even though their call order and record widths are preserved.\",\n    \"Empty/invalid range behavior is modeled defensively; the live implementation may fault on malformed service-returned ranges.\"\n  ],\n  \"body_status\": \"integrated\",\n  \"class_type\": \"InventoryEntryContext\",\n  \"cluster\": null,\n  \"confidence\": 0.89,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00dea200\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00dea27f\",\n        \"direction\": \"in\",\n        \"other\": \"0x00dea200\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea026\",\n        \"direction\": \"out\",\n        \"other\": \"0x004e39a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea08d\",\n        \"direction\": \"out\",\n        \"other\": \"0x004e39a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea0f1\",\n        \"direction\": \"out\",\n        \"other\": \"0x004e39a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea1da\",\n        \"direction\": \"out\",\n        \"other\": \"0x004e39a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea013\",\n        \"direction\": \"out\",\n        \"other\": \"0x004e39d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea07a\",\n        \"direction\": \"out\",\n        \"other\": \"0x004e39d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea0de\",\n        \"direction\": \"out\",\n        \"other\": \"0x004e39d0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00de9fe9\",\n        \"direction\": \"out\",\n        \"other\": \"0x00558960\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea050\",\n        \"direction\": \"out\",\n        \"other\": \"0x00558960\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea0b4\",\n        \"direction\": \"out\",\n        \"other\": \"0x00558960\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea006\",\n        \"direction\": \"out\",\n        \"other\": \"0x00606880\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea06d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00606880\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea0d1\",\n        \"direction\": \"out\",\n        \"other\": \"0x00606880\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea118\",\n        \"direction\": \"out\",\n        \"other\": \"0x0067cb40\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea183\",\n        \"direction\": \"out\",\n        \"other\": \"0x00a21dc0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00dea1b1\",\n      
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
  "body_end": "00dea1fb",
  "body_span_bytes": 572,
  "body_start": "00de9fc0",
  "callees": [
    "FUN_00f47380",
    "FUN_00a21dc0",
    "FUN_004e39d0",
    "FUN_004e39a0",
    "FUN_00606880",
    "FUN_00de9600",
    "FUN_00558960",
    "FUN_00de7010",
    "FUN_0067cb40"
  ],
  "callers": [
    "FUN_00dea200"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00de9fc0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_10",
      "storage": "Stack[-0x10]:4",
      "type": "undefined4"
    },
    {
      "name": "local_14",
      "storage": "Stack[-0x14]:4",
      "type": "undefined4"
    },
    {
      "name": "local_24",
      "storage": "Stack[-0x24]:1",
      "type": "undefined"
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
      "name": "local_38",
      "storage": "Stack[-0x38]:4",
      "type": "undefined4"
    },
    {
      "name": "local_44",
      "storage": "Stack[-0x44]:4",
      "type": "undefined4"
    },
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_4c",
      "storage": "Stack[-0x4c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 10,
  "mode": "live",
  "name": "FUN_00de9fc0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x9e9fc0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00de9fc0(void)",
  "size_bytes": 572,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00de9fc0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "00dea27f"
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
  "global:0x015fcc74"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg12_space/space_inventory_entry.cpp",
  "files": [
    "reconstruction/staging/pkg12-space/space_inventory_entry.cpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry.hpp",
    "reconstruction/staging/pkg12-space/space_inventory_entry_model_test.cpp",
    "src/reconstruction/pkg12_space/space_inventory_entry.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-source-wave3/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg12-space/00de9fc0.json"
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
    "gate-space-inventory-entry"
  ],
  "validated": 0
}
```

## semantic_hypotheses

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6636,
  "preview": "{\n  \"category\": \"GAMEPLAY_LOGIC\",\n  \"classification\": \"STRUCTURAL_ONLY\",\n  \"confidence\": {\n    \"mechanics\": 0.98\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 10,\n  \"evidence\": [\n    {\n      \"kind\": \"targeted_decompilation_and_disassembly\",\n      \"observation\": \"Three constant-backed 0x24 temporaries, 0x0c descriptor stride, receiver+0x38/+0x3c comparison, FUN_00de9600, FUN_00de7010, cleanup.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00de9fc0\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"Allocates Simulator/GGE state, sets a property parent, and invokes IGameModeManager Initialize.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00de9600\"\n    },\n    {\n      \"kind\": \"callee_decompilation\",\n      \"observation\": \"Traverses game behavior manager state and conditionally performs a bounded post-pass.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00de7010\"\n    },\n    {\n      \"kind\": \"caller_comparison\",\n      \"observation\": \"Calls 00de9fc0 before a sequence of InitGraphics calls and later receiver virtual operations.\",\n      \"source\": \"ghidra://SporeApp.exe@0x00dea200\"\n    },\n    {\n      \"kind\": \"structure_layout\",\n      \"observation\": \"The imported type supplies +0x38 and +0x3c fields but not enough type identity to prove the SDK entry.\",\n      \"source\": \"ghidra://SporeApp.exe@structure:GlobalGGEUI\"\n    }\n  ],\n  \"family\": \"galaxy_game_entry_ui_bootstrap\",\n  \"interfaces\": {\n    \"boundaries\": {},\n    \"direct_callees\": [],\n    \"direct_callers\": [],\n    \"globals\": [],\n    \"structures\": [\n      {\n        \"observation\": \"Ghidra supplies a generic GlobalGGEUI layout with field_38 at +0x38 and Unknown field_3C at +0x3c; the body uses +0x38 as a map-like lookup object and +0x3c as the matching sentinel, but does not prove the SDK field types.\",\n        \"size\": \"0x264\",\n        \"type\": \"GlobalGGEUI\"\n      },\n      {\n        \"observation\": \"The service slot +0x38 returns a range whose count is computed as (end - begin) / 0x0c; each descriptor is three dwords.\",\n        \"type\": \"descriptor vector\"\n      },\n      {\n        \"observation\": \"FUN_00558960 creates 0x24-byte values and FUN_00606880/FUN_004e39d0 manage the temporary range.\",\n        \"type\": \"temporary value\"\n      },\n      {\n        \"observation\": \"FUN_00de9600 allocates a 0x38-byte Simulator/GGE object and attaches it to a property parent before IGameModeManager initialization.\",\n        \"type\": \"GGE object\"\n      }\n    ],\n    \"vtables\": [\n      {\n        \"observation\": \"FUN_0067cb40 returns a service object; the target reads its vtable slot +0x38 to obtain the descriptor range.\",\n        \"status\": \"service_vtable_indirect\"\n      },\n      {\n        \"observation\": \"FUN_00de9600 calls IGameModeManager vtable slot +0x0c/Initialize through a service object; the concrete interface vtable address is not recovered.\",\n        \"status\": \"game_mode_manager_vtable_indirect\"\n      },\n      {\n        \"observation\": \"The target has no GlobalGGEUI vtable xref, no concrete vtable address, and no RTTI proof.\",\n        \"status\": \"no_target_vtable_or_rtti\"\n      }\n    ],\n    \"worker_contract_surface\": {\n      \"failure_behavior\": \"No explicit null guard is present; descriptor vector count zero skips the matching loop. FUN_00de9600 is called only for descriptors whose resolved value equals receiver+0x3c.\",\n      \"identity_boundary\": \"Describe this as a bootstrap sub-initializer; do not rename the entry to GlobalGGEUI::Initialize or InitializeUI.\",\n      \"inputs\": [\n        \"no explicit stack arguments; ECX receiver\"\n      ],\n      \"ordering\": [\n        \"constant temporary construction\",\n        \"temporary append/copy\",\n        \"service descriptor retrieval\",\n        \"descriptor filtering and matching game-mode initialization\",\n        \"post-pass behavior-manager cleanup\",\n        \"temporary destruction\"\n      ],\n      \"outputs\": [],\n      \"postconditions\": [],\n      \"preconditions\": [\n        \"receiver and the service returned by FUN_0067cb40 are valid\",\n        \"the service returns a descriptor vector with a 0x0c stride\"\n      ],\n      \"purpose\": \"not_reported\",\n      \"return\": {\n        \"status\": \"not_reported\"\n      },\n      \"side_effects\": [\n        \"initializes GGE/game-mode state for matching descriptors\",\n        \"mutates the receiver/game-mode state observed by FUN_00de7010\",\n        \"allocates and releases temporary 0x24 records\"\n      ],\n      \"status\": \"supported_static_contract_identity_partial\",\n      \"unresolved\": [\n        \"What concrete 0x0c descriptor type is returned by the service, and what do its three dwords mean?\",\n        \"What concrete ordered-map/container type occupies receiver+0x38, and why is only the receiver+0x3c result acted upon?\",\n        \"Which service is returned by FUN_0067cb40, and what is the true GlobalGGEUI::Initialize entry?\",\n        \"What state does FUN_00de7010 observe after the matching game-mode initialization?\",\n        \"Which UI/game-mode side effects are required for a replacement, and which are SDK-only compatibility behavior?\"\n      ]\n    }\n  },\n  \"invariants\": {\n    \"failure_semantics\": [],\n    \"invariants\": [],\n    \"invariants_status\": \"not_reported\"\n  },\n  \"name\": \"galaxy_game_entry_game_mode_bootstrap_sub_initializer\",\n  \"package\": {\n    \"caveat\": \"not_reported\",\n    \"ownership_status\": \"not_reported\",\n    \"primary\": null,\n    \"secondary\": []\n  },\n  \"readiness\": {\n    \"next_action\": \"Resolve the service descriptor and receiver+0x38 type, then validate the bootstrap path with a Galaxy-entry trace; do not merge it with the exact SDK Initialize entry.\",\n    \"
[TRUNCATED]
```

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
  "/Spore/App/IGameModeManager",
  "/Spore/GalaxyGameEntry/GlobalGGEUI",
  "/Spore/Simulator/cGameBehaviorManager",
  "/Spore/Simulator/cGameModeManager",
  "AllocationService",
  "BehaviorCleanupService",
  "EntryIndex",
  "GameEntryDescriptor",
  "GameEntryRange",
  "GameModeService",
  "InventoryEntryContext",
  "InventoryEntryServices",
  "PropertyRecord",
  "PropertyRecordBuffer",
  "PropertyRecordService",
  "void"
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
