# Evidence 0x00ae9f50

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0006c655c9e638c8df883f8902001ab4d5ca0f4fa05972cfae7073c91f296299`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "__thiscall",
  "hidden_receiver": "ECX, copied to ESI at 0x00ae9f57",
  "hidden_this_register": "ECX is consumed immediately; ESI carries the receiver for the rest of the body, which is what lets ECX be reused as the receiver for the many __thiscall ports.",
  "ordinary_stack_argument_slots": 0,
  "receiver": true,
  "ret_form": "RET",
  "return_register": null,
  "return_semantics": "No return value. EAX is a scratch register throughout.",
  "return_type": "void",
  "return_width_bytes": 0,
  "saved_registers": [
    "ESI",
    "EBX",
    "EBP",
    "EDI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "two exits, both the same bare RET: 0x00aea166 reached by falling off the end, and 0x00aea15f reached by the null-sub-object jump and by the +0x64 / +0x68 skips."
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
    "flow_not_modelled: the linear ESP walk ends at +68, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register"
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
  "content_sha256": "ecf88b253ff2b7038e6e90770e2e2b20bffcae4949d56a3af5c476ce34c972f8",
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
    "indirect_calls": 3,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0073"
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
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0021",
        "obs-0032",
        "obs-0035",
        "obs-0036",
        "obs-0046",
        "obs-0047",
        "obs-0049",
        "obs-0070"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          32,
          100,
          104,
          116
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0004",
        "obs-0005",
        "obs-0007",
        "obs-0008",
        "obs-0021",
        "obs-0032",
        "obs-0035",
        "obs-0036",
        "obs-0046",
        "obs-0047",
        "obs-0049",
        "obs-0070",
        "obs-0073"
      ],
      "claim": "calling convention is __thiscall: the receiver arrives in ECX and the caller cleans the stack",
      "confidence": "INFERRED",
      "id": "C7",
      "value": "__thiscall"
    },
    {
      "based_on": [
        "obs-0073"
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
        "obs-0073"
      ],
      "claim": "the return value is carried in EAX",
      "confidence": "INFERRED",
      "id": "RT1",
      "value": "EAX"
    },
    {
      "based_on": [
        "obs-0073"
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
      "at": "0x00ae9f50",
      "ebp_is_general_register": true,
      "fp": false,
      "id": "obs-0001",
      "index": 0,
      "kind": "FRAME",
      "lea_esp": null,
      "mov_ebp_esp": false,
      "mov_ebp_esp_at": null,
      "push_ebp": true,
      "push_ebp_at": 12,
      "raw": "SUB ESP,0x80",
      "sub": 128
    },
    {
      "at": "0x00ae9f50",
      "definite": true,
      "id": "obs-0002",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "SUB ESP,0x80",
      "reg": "ESP",
      "write_kind": "arith"
    },
    {
      "at": "0x00ae9f56",
      "count": 13,
      "first_use": 1,
      "first_write_index": 2,
      "id": "obs-0003",
      "index": 1,
      "kind": "REG_READ",
      "raw": "PUSH ESI",
      "reg": "ESI"
    },
    {
      "at": "0x00ae9f57",
      "count": 15,
      "first_use": 2,
      "first_write_index": 4,
      "id": "obs-0004",
      "index": 2,
      "kind": "REG_READ",
      "raw": "MOV ESI,ECX",
      "reg": "ECX"
    },
    {
      "at": "0x00ae9f57",
      "definite": true,
      "id": "obs-0005",
      "index": 2,
      "kind": "REG_WRITE",
      "raw": "MOV ESI,ECX",
      "reg": "ESI",
      "write_kind": "reg"
    },
    {
      "at": "0x00ae9f59",
      "id": "obs-0006",
      "index": 3,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00dd1ca0",
      "target": "0x00dd1ca0"
    },
    {
      "at": "0x00ae9f5e",
      "count": 36,
      "first_use": 4,
      "first_write_index": 6,
      "id": "obs-0007",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV ECX,EAX",
      "reg": "EAX"
    },
    {
      "at": "0x00ae9f5e",
      "definite": true,
      "id": "obs-0008",
      "index": 4,
      "kind": "REG_WRITE",
      "raw": "MOV ECX,EAX",
      "reg": "ECX",
      "write_kind": "reg"
    },
    {
      "at": "0x00ae9f60",
      "id": "obs-0009",
      "index": 5,
      "kind": "CALL_DIRECT",
      "raw": "CALL 0x00dd30d0",
      "target": "0x00dd30d0"
    },
    {
      "at": "0x00ae9f65",
      "definite": true,
      "id": "obs-
[TRUNCATED]
```

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  },
  {
    "name": "FUN_00b3d2a0",
    "reconstructed": true,
    "va": "0x00b3d2a0"
  },
  {
    "name": "FUN_00b3d300",
    "reconstructed": true,
    "va": "0x00b3d300"
  },
  {
    "name": "FUN_00b3d380",
    "reconstructed": false,
    "va": "0x00b3d380"
  },
  {
    "name": "FUN_00b3d400",
    "reconstructed": true,
    "va": "0x00b3d400"
  },
  {
    "name": "Simulator_cSpaceTrading_Get",
    "reconstructed": true,
    "va": "0x00b3d4d0"
  },
  {
    "name": "Simulator_LookupEmpireByPoliticalId",
    "reconstructed": true,
    "va": "0x00ba9370"
  },
  {
    "name": "FUN_01021090",
    "reconstructed": false,
    "va": "0x01021090"
  },
  {
    "name": "pkg12_space_01021300",
    "reconstructed": true,
    "va": "0x01021300"
  }
]
```

## callers_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aea210"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb090"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb7b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00aeb890"
  }
]
```

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00b3d2a0",
      "0x00b3d300",
      "0x00b5b800",
      "0x01021300",
      "0x01021300",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0",
      "0x00aeb3e0",
      "0x00aebe90",
      "0x00b25fb0"
    ],
    "conflict_id": "global_root_identities",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0067dcc0",
      "0x0067deb0",
      "0x00b3d330",
      "0x00b3d4e0",
      "0x015fd890",
      "0x0167eaf0",
      "0x0167eb60",
      "0x0067dcc0",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0"
    ],
    "conflict_id": "global_service_publication",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
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
  "count": 169,
  "instructions": [
    {
      "address": "00ae9f50",
      "instruction": "SUB ESP,0x80"
    },
    {
      "address": "00ae9f56",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00ae9f57",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00ae9f59",
      "instruction": "CALL 0x00dd1ca0"
    },
    {
      "address": "00ae9f5e",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ae9f60",
      "instruction": "CALL 0x00dd30d0"
    },
    {
      "address": "00ae9f65",
      "instruction": "MOV EAX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "00ae9f68",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ae9f6a",
      "instruction": "JZ 0x00aea15f"
    },
    {
      "address": "00ae9f70",
      "instruction": "CMP dword ptr [EAX + 0xc],0x0"
    },
    {
      "address": "00ae9f74",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00ae9f75",
      "instruction": "SETZ BL"
    },
    {
      "address": "00ae9f78",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00ae9f79",
      "instruction": "PUSH EDI"
    },
    {
      "address": "00ae9f7a",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00ae9f7c",
      "instruction": "JZ 0x00ae9f92"
    },
    {
      "address": "00ae9f7e",
      "instruction": "MOV EAX,dword ptr [EAX + 0x18]"
    },
    {
      "address": "00ae9f81",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ae9f82",
      "instruction": "CALL 0x00b3d2a0"
    },
    {
      "address": "00ae9f87",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ae9f89",
      "instruction": "CALL 0x00ba9370"
    },
    {
      "address": "00ae9f8e",
      "instruction": "MOV EBP,EAX"
    },
    {
      "address": "00ae9f90",
      "instruction": "JMP 0x00ae9f94"
    },
    {
      "address": "00ae9f92",
      "instruction": "XOR EBP,EBP"
    },
    {
      "address": "00ae9f94",
      "instruction": "MOV dword ptr [ESP + 0x40],0x3ac86b5"
    },
    {
      "address": "00ae9f9c",
      "instruction": "MOV dword ptr [ESP + 0x10],0x13eb90c"
    },
    {
      "address": "00ae9fa4",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00ae9fa6",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00ae9faa",
      "instruction": "XCHG dword ptr [ECX],EAX"
    },
    {
      "address": "00ae9fac",
      "instruction": "MOV EDI,dword ptr [ESI + 0x20]"
    },
    {
      "address": "00ae9faf",
      "instruction": "MOV dword ptr [ESP + 0x10],0x13eb844"
    },
    {
      "address": "00ae9fb7",
      "instruction": "MOV dword ptr [ESP + 0x48],0x0"
    },
    {
      "address": "00ae9fbf",
      "instruction": "MOV EDX,dword ptr [EDI + 0xc]"
    },
    {
      "address": "00ae9fc2",
      "instruction": "MOV dword ptr [ESP + 0x18],EDX"
    },
    {
      "address": "00ae9fc6",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00ae9fc8",
      "instruction": "JZ 0x00ae9fce"
    },
    {
      "address": "00ae9fca",
      "instruction": "MOV EAX,EBP"
    },
    {
      "address": "00ae9fcc",
      "instruction": "JMP 0x00ae9fed"
    },
    {
      "address": "00ae9fce",
      "instruction": "MOV EAX,dword ptr [EDI + 0x18]"
    },
    {
      "address": "00ae9fd1",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00ae9fd2",
      "instruction": "CALL 0x00b3d300"
    },
    {
      "address": "00ae9fd7",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ae9fd9",
      "instruction": "CALL 0x00b20750"
    },
    {
      "address": "00ae9fde",
      "instruction": "MOV EAX,dword ptr [EDI + 0x28]"
    },
    {
      "address": "00ae9fe1",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00ae9fe3",
      "instruction": "JNZ 0x00ae9fed"
    },
    {
      "address": "00ae9fe5",
      "instruction": "MOV ECX,dword ptr [EDI + 0x20]"
    },
    {
      "address": "00ae9fe8",
      "instruction": "CALL 0x00bd9bf0"
    },
    {
      "address": "00ae9fed",
      "instruction": "MOV dword ptr [ESP + 0x20],EAX"
    },
    {
      "address": "00ae9ff1",
      "instruction": "MOV EAX,dword ptr [ESI + 0x20]"
    },
    {
      "address": "00ae9ff4",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00ae9ff6",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00ae9ff8",
      "instruction": "JNZ 0x00ae9ffd"
    },
    {
      "address": "00ae9ffa",
      "instruction": "MOV ECX,dword ptr [EAX + 0x20]"
    },
    {
      "address": "00ae9ffd",
      "instruction": "MOV dword ptr [ESP + 0x28],ECX"
    },
    {
      "address": "00aea001",
      "instruction": "TEST BL,BL"
    },
    {
      "address": "00aea003",
      "instruction": "JZ 0x00aea009"
    },
    {
      "address": "00aea005",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00aea007",
      "instruction": "JMP 0x00aea00c"
    },
    {
      "address": "00aea009",
      "instruction": "MOV EAX,dword ptr [EAX + 0x24]"
    },
    {
      "address": "00aea00c",
      "instruction": "MOV dword ptr [ESP + 0x30],EAX"
    },
    {
      "address": "00aea010",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00aea015",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00aea017",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00aea01a",
      "instruction": "PUSH 0x0"
    },
    {
      "address": "00aea01c",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00aea020",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00aea021",
      "instruction": "MOV ECX,dword ptr [ESP + 0x48]"
    },
    {
      "address": "00aea025",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00aea026",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00aea028",
      "instruction": "CALL EDX"
    },
    {
      "addr
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
  "original_bytes": 14444,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_receiver\": \"ECX, copied to ESI at 0x00ae9f57\",\n    \"hidden_this_register\": \"ECX is consumed immediately; ESI carries the receiver for the rest of the body, which is what lets ECX be reused as the receiver for the many __thiscall ports.\",\n    \"ordinary_stack_argument_slots\": 0,\n    \"receiver\": true,\n    \"ret_form\": \"RET\",\n    \"return_register\": null,\n    \"return_semantics\": \"No return value. EAX is a scratch register throughout.\",\n    \"return_type\": \"void\",\n    \"return_width_bytes\": 0,\n    \"saved_registers\": [\n      \"ESI\",\n      \"EBX\",\n      \"EBP\",\n      \"EDI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"two exits, both the same bare RET: 0x00aea166 reached by falling off the end, and 0x00aea15f reached by the null-sub-object jump and by the +0x64 / +0x68 skips.\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"FUN_00b3d400\",\n      \"va\": \"0x00b3d400\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_cSpaceTrading_Get\",\n      \"va\": \"0x00b3d4d0\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-11-SIM-CORE\",\n      \"score\": 3,\n      \"symbol\": \"Simulator_LookupEmpireByPoliticalId\",\n      \"va\": \"0x00ba9370\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 3,\n      \"symbol\": \"pkg12_space_01021300\",\n      \"va\": \"0x01021300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 2,\n      \"symbol\": \"property_record_assign_scalar_00428060\",\n      \"va\": \"0x00428060\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": null,\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0067dcc0\"\n      },\n      {\n        \"name\": \"FUN_00b3d2a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d2a0\"\n      },\n      {\n        \"name\": \"FUN_00b3d300\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d300\"\n      },\n      {\n        \"name\": \"FUN_00b3d380\",\n        \"reconstructed\": false,\n        \"va\": \"0x00b3d380\"\n      },\n      {\n        \"name\": \"FUN_00b3d400\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d400\"\n      },\n      {\n        \"name\": \"Simulator_cSpaceTrading_Get\",\n        \"reconstructed\": true,\n        \"va\": \"0x00b3d4d0\"\n      },\n      {\n        \"name\": \"Simulator_LookupEmpireByPoliticalId\",\n        \"reconstructed\": true,\n        \"va\": \"0x00ba9370\"\n      },\n      {\n        \"name\": \"FUN_01021090\",\n        \"reconstructed\": false,\n        \"va\": \"0x01021090\"\n      },\n      {\n        \"name\": \"pkg12_space_01021300\",\n        \"reconstructed\": true,\n        \"va\": \"0x01021300\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aea210\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb090\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb7b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00aeb890\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00aea210\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aea210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aeb099\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aeb090\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aeb801\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aeb7b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aeb906\",\n        \"direction\": \"in\",\n        \"other\": \"0x00aeb890\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aea08f\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00aea15a\",\n        \"direction\": \"out\",\n        \"other\": \"0x00421cf0\",\n        \"reference_type\": \"direct-call\"\n      
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
  "body_end": "00aea166",
  "body_span_bytes": 535,
  "body_start": "00ae9f50",
  "callees": [
    "FUN_00dd30d0",
    "FUN_00c35240",
    "FUN_01021090",
    "Simulator::cSpaceTrading::Get",
    "FUN_00b32250",
    "FUN_00ba9370",
    "FUN_00b3d380",
    "Simulator::cGameNounManager::Get",
    "FUN_00b3d2a0",
    "FUN_00bd9bf0",
    "FUN_00421cf0",
    "FUN_00435ed0",
    "Simulator::cToolManager::Get",
    "FUN_00e14c10",
    "FUN_00dd1ca0",
    "FUN_01021300",
    "FUN_00a206f0",
    "FUN_00ae0930",
    "App::IAppSystem::Get",
    "FUN_00b3d300",
    "FUN_00ba6d80",
    "FUN_00ae8ea0",
    "FUN_00b20750"
  ],
  "callers": [
    "FUN_00aeb7b0",
    "FUN_00aeb090",
    "FUN_00aeb890",
    "FUN_00aea210"
  ],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00ae9f50",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [
    {
      "name": "local_48",
      "storage": "Stack[-0x48]:4",
      "type": "undefined4"
    },
    {
      "name": "local_50",
      "storage": "Stack[-0x50]:4",
      "type": "undefined4"
    },
    {
      "name": "local_60",
      "storage": "Stack[-0x60]:4",
      "type": "undefined4"
    },
    {
      "name": "local_68",
      "storage": "Stack[-0x68]:4",
      "type": "undefined4"
    },
    {
      "name": "local_70",
      "storage": "Stack[-0x70]:4",
      "type": "undefined4"
    },
    {
      "name": "local_78",
      "storage": "Stack[-0x78]:4",
      "type": "undefined4"
    },
    {
      "name": "local_7c",
      "storage": "Stack[-0x7c]:4",
      "type": "undefined4"
    },
    {
      "name": "local_80",
      "storage": "Stack[-0x80]:4",
      "type": "undefined4"
    }
  ],
  "locals_count": 8,
  "mode": "live",
  "name": "FUN_00ae9f50",
  "namespace": null,
  "namespace_source": null,
  "parameter_count": 0,
  "parameters": [],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "undefined",
  "return_type_resolved": false,
  "rva": "0x6e9f50",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "undefined FUN_00ae9f50(void)",
  "size_bytes": 535,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00ae9f50",
  "vtables": {
    "referenced_by_vtables": [],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 4,
  "xrefs": [
    {
      "from": "00aeb801"
    },
    {
      "from": "00aea210"
    },
    {
      "from": "00aeb906"
    },
    {
      "from": "00aeb099"
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
    "reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp",
    "reconstruction/staging/wave13-w1-core-b08/b8dad0_spice_gen_key_ptr.cpp",
    "reconstruction/staging/wave13-w1-core-b08/ba61b0_make_planet_record.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0b780_sub_object_flag_608.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c0ce80_tier_value_lookup.cpp",
    "reconstruction/staging/wave13-w1-core-b08/c47180_manager_slot_replace.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_model_test2.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_reconstructed.hpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.cpp",
    "reconstruction/staging/wave13-w1-core-b08/wave13_w1_core_b08_test_stubs.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b08/00ae9f50.json"
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
    "No original-process trace exists. A differential run must confirm the two AppSystem submissions, the two publishes and the three memory writes actually occur in the observed order in the shipping build.",
    "The claim that 0x00421CF0 destroys the stack records must be observed: a run that keeps the record alive after return would refute it.",
    "The sentinel-free runtime values behind the six-entry table at 0x015D9650 used by the sibling 0x00C0CE80 are irrelevant here, but the two record ids 0x3AC86B5 and 0x43F2590 can only be resolved by observing what the AppSystem slot +0x14 does with them.",
    "Whether receiver+0x74 can be non-(-1) at entry, and what 0x00BA6D80 returns for it, can only be established at runtime."
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
[
  {
    "anchors": [
      "0x00b3d2a0",
      "0x00b3d300",
      "0x00b5b800",
      "0x01021300",
      "0x01021300",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0",
      "0x00aeb3e0",
      "0x00aebe90",
      "0x00b25fb0"
    ],
    "conflict_id": "global_root_identities",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x0067dcc0",
      "0x0067deb0",
      "0x00b3d330",
      "0x00b3d4e0",
      "0x015fd890",
      "0x0167eaf0",
      "0x0167eb60",
      "0x0067dcc0",
      "0x00ad23c0",
      "0x00adbca0",
      "0x00ae73e0",
      "0x00ae9590",
      "0x00ae9930",
      "0x00ae9c90",
      "0x00ae9f50",
      "0x00aeb3e0"
    ],
    "conflict_id": "global_service_publication",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
