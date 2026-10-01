# Evidence 0x006891f0

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0745e7d192831a0c3046dfc5e45eab7ba3398bd12df86a4de0933e35753628ec`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__cdecl",
  "hidden_this_register": "ECX is not a receiver: 0x00689205 SUB ESP,0x60 is preceded by PUSH EDI at 0x0068920b, and ECX is only used as a scratch thiscall target for the string and allocator ports (0x00689225, 0x0068924a, 0x00689296, 0x006892ab, 0x0068930f, 0x00689385).",
  "ordinary_stack_argument_slots": 2,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x006894ca is C3 with no immediate and no preceding MOV EAX; the last value written to EAX is the return of 0x00931fd0 at 0x00689421, which is immediately followed by stack-pointer arithmetic and the epilogue.",
  "return_register": "EAX (clobbered, unused)",
  "return_semantics": "no value; EAX is clobbered by the last tail call and none of the 4 observed call sites reads it",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "EBX",
    "EBP",
    "ESI",
    "EDI"
  ],
  "stack_arguments": [
    {
      "proof": "0x00de48e1 PUSH 0x145fb88 pushes L\"GGEUserData.dat\" first, so it is the second argument; 0x00de48e6 PUSH 0x147e040 pushes L\"GGEUserData.dat.tmp\" second, so it is the first argument, and the reconstruction's source_name is the .tmp name",
      "role": "source_name",
      "slot": "[ESP_entry+4]"
    },
    {
      "proof": "same callsite, the argument the reconstruction concatenates to form the destination path",
      "role": "dest_name",
      "slot": "[ESP_entry+8]"
    }
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "single exit at 0x006894ca"
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
    "flow_not_modelled: the linear ESP walk ends at +36, so the listing is not one path",
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
  "content_sha256": "6b0f0afd9728bde2ae1ba730ca7c1c21754f7fc71a4424be2e0c3b2fa3e2f27b",
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
    "persisted_calling_convention": "__cdecl"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 1,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0118"
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
        "obs-0014",
        "obs-0018",
        "obs-0019",
        "obs-0028",
        "obs-0041",
        "obs-0046",
        "obs-0051",
        "obs-0054",
        "obs-0059",
        "obs-0065",
        "obs-0069",
        "obs-0072",
        "obs-0076",
        "obs-0083",
        "obs-0096",
        "obs-0100",
        "obs-0107",
        "obs-0112",
        "obs-0117"
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
        "obs-0001",
        "obs-0004",
        "obs-0117"
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
        "obs-0118"
      ],
      "claim": "the function is byte-identical under all four conventions",
      "confidence": "UNKNOWN",
      "id": "C10"
    },
    {
      "based_on": [
        "obs-0118"
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
        "obs-0118"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0118"
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
    "name": "FUN_00580cb0",
    "reconstructed": false,
    "va": "0x00580cb0"
  },
  {
    "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
    "reconstructed": true,
    "va": "0x00b28ec0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00bb4ba0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00de4850"
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
  "count": 239,
  "instructions": [
    {
      "address": "006891f0",
      "instruction": "PUSH -0x1"
    },
    {
      "address": "006891f2",
      "instruction": "PUSH 0x120c8a0"
    },
    {
      "address": "006891f7",
      "instruction": "MOV EAX,FS:[0x0]"
    },
    {
      "address": "006891fd",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006891fe",
      "instruction": "MOV dword ptr FS:[0x0],ESP"
    },
    {
      "address": "00689205",
      "instruction": "SUB ESP,0x60"
    },
    {
      "address": "00689208",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00689209",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0068920a",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0068920b",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0068920c",
      "instruction": "PUSH 0x4729a47"
    },
    {
      "address": "00689211",
      "instruction": "CALL 0x006b1f90"
    },
    {
      "address": "00689216",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00689218",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "0068921a",
      "instruction": "MOV EAX,dword ptr [EDX + 0x28]"
    },
    {
      "address": "0068921d",
      "instruction": "ADD ESP,0x4"
    },
    {
      "address": "00689220",
      "instruction": "CALL EAX"
    },
    {
      "address": "00689222",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00689224",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00689225",
      "instruction": "LEA ECX,[ESP + 0x44]"
    },
    {
      "address": "00689229",
      "instruction": "MOV dword ptr [ESP + 0x44],EDI"
    },
    {
      "address": "0068922d",
      "instruction": "MOV dword ptr [ESP + 0x48],EDI"
    },
    {
      "address": "00689231",
      "instruction": "MOV dword ptr [ESP + 0x4c],EDI"
    },
    {
      "address": "00689235",
      "instruction": "CALL 0x00579a90"
    },
    {
      "address": "0068923a",
      "instruction": "MOV ESI,dword ptr [ESP + 0x44]"
    },
    {
      "address": "0068923e",
      "instruction": "MOV EBX,dword ptr [ESP + 0x40]"
    },
    {
      "address": "00689242",
      "instruction": "SUB ESI,EBX"
    },
    {
      "address": "00689244",
      "instruction": "SAR ESI,0x1"
    },
    {
      "address": "00689246",
      "instruction": "LEA ECX,[ESI + 0x1]"
    },
    {
      "address": "00689249",
      "instruction": "PUSH ECX"
    },
    {
      "address": "0068924a",
      "instruction": "LEA ECX,[ESP + 0x34]"
    },
    {
      "address": "0068924e",
      "instruction": "MOV dword ptr [ESP + 0x7c],EDI"
    },
    {
      "address": "00689252",
      "instruction": "MOV dword ptr [ESP + 0x34],EDI"
    },
    {
      "address": "00689256",
      "instruction": "MOV dword ptr [ESP + 0x38],EDI"
    },
    {
      "address": "0068925a",
      "instruction": "MOV dword ptr [ESP + 0x3c],EDI"
    },
    {
      "address": "0068925e",
      "instruction": "CALL 0x00429760"
    },
    {
      "address": "00689263",
      "instruction": "MOV EBP,dword ptr [ESP + 0x30]"
    },
    {
      "address": "00689267",
      "instruction": "ADD ESI,ESI"
    },
    {
      "address": "00689269",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0068926a",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0068926b",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0068926c",
      "instruction": "CALL 0x011e0744"
    },
    {
      "address": "00689271",
      "instruction": "LEA EAX,[ESI + EBP*0x1]"
    },
    {
      "address": "00689274",
      "instruction": "XOR EDX,EDX"
    },
    {
      "address": "00689276",
      "instruction": "MOV dword ptr [ESP + 0x40],EAX"
    },
    {
      "address": "0068927a",
      "instruction": "MOV word ptr [EAX],DX"
    },
    {
      "address": "0068927d",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0068927e",
      "instruction": "MOV byte ptr [ESP + 0x88],0x1"
    },
    {
      "address": "00689286",
      "instruction": "CALL 0x00932ae0"
    },
    {
      "address": "0068928b",
      "instruction": "MOV EAX,dword ptr [ESP + 0x94]"
    },
    {
      "address": "00689292",
      "instruction": "ADD ESP,0x10"
    },
    {
      "address": "00689295",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00689296",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "0068929a",
      "instruction": "MOV dword ptr [ESP + 0x14],EDI"
    },
    {
      "address": "0068929e",
      "instruction": "MOV dword ptr [ESP + 0x18],EDI"
    },
    {
      "address": "006892a2",
      "instruction": "MOV dword ptr [ESP + 0x1c],EDI"
    },
    {
      "address": "006892a6",
      "instruction": "CALL 0x00579a90"
    },
    {
      "address": "006892ab",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "006892af",
      "instruction": "PUSH ECX"
    },
    {
      "address": "006892b0",
      "instruction": "LEA EDX,[ESP + 0x34]"
    },
    {
      "address": "006892b4",
      "instruction": "PUSH EDX"
    },
    {
      "address": "006892b5",
      "instruction": "LEA EAX,[ESP + 0x58]"
    },
    {
      "address": "006892b9",
      "instruction": "PUSH EAX"
    },
    {
      "address": "006892ba",
      "instruction": "MOV byte ptr [ESP + 0x84],0x2"
    },
    {
      "address": "006892c2",
      "instruction": "CALL 0x00688f00"
    },
    {
      "address": "006892c7",
      "instruction": "ADD ESP,0xc"
    },
    {
      "address": "006892ca",
      "instruction": "LEA ECX,[ESP + 0x10]"
    },
    {
      "address": "006892ce",
      "instruction": "MOV byte ptr [ESP + 0x78],0x3"
    },
    {
      "address": "006892d3",
      "instruction": "CMP EAX,ECX"
    },
    {
      "address": "006892d5",
      "instruction": "JZ 0x006892e3"
    },
    {
      "address": "006892d7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4]"
    },
    {

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
  "original_bytes": 12728,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__cdecl\",\n    \"hidden_this_register\": \"ECX is not a receiver: 0x00689205 SUB ESP,0x60 is preceded by PUSH EDI at 0x0068920b, and ECX is only used as a scratch thiscall target for the string and allocator ports (0x00689225, 0x0068924a, 0x00689296, 0x006892ab, 0x0068930f, 0x00689385).\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"0x006894ca is C3 with no immediate and no preceding MOV EAX; the last value written to EAX is the return of 0x00931fd0 at 0x00689421, which is immediately followed by stack-pointer arithmetic and the epilogue.\",\n    \"return_register\": \"EAX (clobbered, unused)\",\n    \"return_semantics\": \"no value; EAX is clobbered by the last tail call and none of the 4 observed call sites reads it\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"EBX\",\n      \"EBP\",\n      \"ESI\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [\n      {\n        \"proof\": \"0x00de48e1 PUSH 0x145fb88 pushes L\\\"GGEUserData.dat\\\" first, so it is the second argument; 0x00de48e6 PUSH 0x147e040 pushes L\\\"GGEUserData.dat.tmp\\\" second, so it is the first argument, and the reconstruction's source_name is the .tmp name\",\n        \"role\": \"source_name\",\n        \"slot\": \"[ESP_entry+4]\"\n      },\n      {\n        \"proof\": \"same callsite, the argument the reconstruction concatenates to form the destination path\",\n        \"role\": \"dest_name\",\n        \"slot\": \"[ESP_entry+8]\"\n      }\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"single exit at 0x006894ca\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-20-PERSISTENCE-BOUNDARY\",\n      \"score\": 3,\n      \"symbol\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n      \"va\": \"0x00b28ec0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"editor_bake_probe_004bf770\",\n      \"va\": \"0x004bf770\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IStateManager_Get_0067dce0\",\n      \"va\": \"0x0067dce0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"WAVE6-ENGINE-RUNTIME\",\n      \"score\": 2,\n      \"symbol\": \"app_config_manager_get_0067dcf0\",\n      \"va\": \"0x0067dcf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-06-WAVE6-APP-MANAGERS\",\n      \"score\": 2,\n      \"symbol\": \"App_IPropManager_Get_0067ddf0\",\n      \"va\": \"0x0067ddf0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 2,\n      \"symbol\": \"FUN_00b3d3a0\",\n      \"va\": \"0x00b3d3a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 2,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": \"FUN_00580cb0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00580cb0\"\n      },\n      {\n        \"name\": \"ProfilePersistenceBoundary_run_candidate_00b28ec0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b28ec0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00bb4ba0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00de4850\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00580dc9\",\n        \"direction\": \"in\",\n        \"other\": \"0x00580cb0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00b293d4\",\n        \"direction\": \"in\",\n        \"other\": \"0x00b28ec0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00bb4f0a\",\n        \"direction\": \"in\",\n        \"other\": \"0x00bb4ba0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00de48eb\",\n        \"direction\": \"in\",\n        \"other\": \"0x00de4850\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x006892de\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00689358\",\n        \"direction\": \"out\",\n        \"other\": \"0x00423650\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x0068925e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00429760\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00689235\",\n        \"direction\": \"out\",\
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
  "body_end": "006894ca",
  "body_span_bytes": 731,
  "body_start": "006891f0",
  "callees": [
    "IO_File_Remove",
    "FUN_006b1f90",
    "memcpy",
    "FUN_00f47380",
    "FUN_00931fd0",
    "FUN_00579a90",
    "FUN_00932ae0",
    "FUN_00688f00",
    "FUN_00423650",
    "FUN_00429760",
    "FUN_00931ff0"
  ],
  "callers": [
    "FUN_00de4850",
    "FUN_00b28ec0",
    "FUN_00580cb0",
    "FUN_00bb4ba0"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "006891f0",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "FUN_006891f0",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x2891f0",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_006891f0(void)",
  "size_bytes": 731,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x006891f0",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00b293d4"
    },
    {
      "from": "00bb4f0a"
    },
    {
      "from": "00580dc9"
    },
    {
      "from": "00de48eb"
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
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.cpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file.hpp",
    "reconstruction/staging/wave13-w1-dispatch-b03/editor_promote_save_file_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-dispatch-b03/006891f0.json"
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
    "A trace must record the return value and the observable effect of 0x00932ae0 on the base path, which is the only way to resolve whether the leading delete is live behaviour or a no-op.",
    "A trace must record whether MoveFileExW at 0x00689406 succeeds in practice, because the body discards the result and static analysis cannot predict the filesystem state.",
    "No original-process trace exists for this function. A differential trace must record the string returned by the save-area virtual slot +0x28, since the whole path algebra depends on whether it is separator-terminated."
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
