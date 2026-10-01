# Evidence 0x00587a20

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `0374bc8f05f05ad95dc661e7410508ec79daaeff1886114dd7489843dfffdbb0`

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
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET",
  "return_observation": "Ghidra resolves return_type void (analyze_function_complete, ghidra_function.return_type_resolved true). The derived openspore-abi-inference-1 record for this target abstained (conventions.confidence UNKNOWN, calling_convention null, candidate_conventions __cdecl) and its return claim is contradicted by the balanced FLD/FSTP pair; see conflicts_and_disagreements.",
  "return_semantics": "void. The epilogue is POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET: a bare RET with no immediate, and no instruction after the last call reads a return register. The x87 pair at 0x00587b10 (FLD float ptr [ESI+0x4d0]) and 0x00587b1b (FSTP float ptr [ESP]) is balanced -- FSTP pops what FLD pushed -- so nothing is left on the x87 stack, and the value is a 4-byte stack argument, not a result. This DISAGREES with the derived ABI record for this target, which reports return_register ST0 and return_semantics float_or_x87_in_ST0; that reading is a false positive of the linear-sweep inference, p...",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI",
    "ESI"
  ],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": [
    "RET at 0x0058856a, bare, no immediate",
    "RET"
  ]
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
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
    "flow_not_modelled: the linear ESP walk ends at +280, so the listing is not one path",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "variadic_not_decidable_from_listing: no caller-side va_list construction is visible",
    "variadic_caps_convention: variadic suspicion removes any guarantee about the stack-argument extent"
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
  "content_sha256": "e8454d33b0ff38785eeb979539ab86f3f3175a6e1a91e0566ee037fd7697824b",
  "conventions": {
    "ambiguities": [
      "variadic_suspected"
    ],
    "calling_convention": null,
    "candidate_conventions": [
      "__cdecl"
    ],
    "confidence": "UNKNOWN",
    "corroboration": "not_available"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 1,
    "persisted": "no_information",
    "persisted_calling_convention": "__thiscall"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 85,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0199"
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
        "obs-0006",
        "obs-0007",
        "obs-0008",
        "obs-0010",
        "obs-0028",
        "obs-0029",
        "obs-0060",
        "obs-0194"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "SUPPORTED",
      "id": "R1",
      "value": {
        "offsets": [
          0,
          120,
          124,
          132,
          140,
          148,
          152,
          156,
          160,
          164,
          168,
          172,
          208,
          212,
          228,
          232,
          233,
          324,
          328,
          332,
          336,
          340,
          428,
          460,
          526,
          660,
          668,
          672,
          676,
          688,
          848,
          852,
          856,
          860,
          864,
          868,
          872,
          896,
          900,
          901,
          952,
          956,
          960,
          964,
          1080,
          1084,
          1096,
          1100,
          1104,
          1172,
          1176,
          1180,
          1184,
          1188,
          1206,
          1212,
          1232,
          1492,
          1496,
          1500,
          1504,
          1508
        ],
        "register": "ECX",
        "written_through": 47
      }
    },
    {
      "based_on": [
        "obs-0066"
      ],
      "claim": "the calling convention is not decidable from the listing",
      "confidence": "UNKNOWN",
      "id": "C12"
    },
    {
      "based_on": [
        "obs-0199"
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
      "claim": "the return value is carried in ST0: an x87 or SSE instruction appears in the body",
      "confidence": "APPROXIMATION",
      "id": "RT1",
      "value": "ST0"
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
    "va": "0x004ad330"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573c00"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00573d70"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005772b0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x00587270"
  },
  {
    "name": "release_child_0062c910",
    "reconstructed": true,
    "va": "0x0062c910"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x0067dcc0"
  }
]
```

## callers_dependencies

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: `reconstruction/knowledge/index.json`

## contradictions

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x0058ac10",
      "0x0058ac10"
    ],
    "conflict_id": "editor_runtime_validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00586b00",
      "0x00587270",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "manipulator_cancel",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058b650",
      "0x00588570",
      "0x0057f3e0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570"
    ],
    "conflict_id": "manipulator_types",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
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
  "count": 934,
  "instructions": [
    {
      "address": "00587a20",
      "instruction": "SUB ESP,0x44"
    },
    {
      "address": "00587a23",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00587a24",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00587a25",
      "instruction": "PUSH ESI"
    },
    {
      "address": "00587a26",
      "instruction": "MOV ESI,ECX"
    },
    {
      "address": "00587a28",
      "instruction": "MOV ECX,dword ptr [ESI + 0x94]"
    },
    {
      "address": "00587a2e",
      "instruction": "XOR EBX,EBX"
    },
    {
      "address": "00587a30",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00587a32",
      "instruction": "JZ 0x00587a3b"
    },
    {
      "address": "00587a34",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00587a36",
      "instruction": "MOV EDX,dword ptr [EAX + 0x34]"
    },
    {
      "address": "00587a39",
      "instruction": "CALL EDX"
    },
    {
      "address": "00587a3b",
      "instruction": "MOV EAX,dword ptr [ESI + 0x450]"
    },
    {
      "address": "00587a41",
      "instruction": "MOV ECX,dword ptr [0x015fd918]"
    },
    {
      "address": "00587a47",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00587a48",
      "instruction": "PUSH 0xb"
    },
    {
      "address": "00587a4a",
      "instruction": "CALL 0x006a1880"
    },
    {
      "address": "00587a4f",
      "instruction": "MOV byte ptr [ESI + 0x2b0],BL"
    },
    {
      "address": "00587a55",
      "instruction": "CALL 0x0067caf0"
    },
    {
      "address": "00587a5a",
      "instruction": "TEST EAX,EAX"
    },
    {
      "address": "00587a5c",
      "instruction": "JZ 0x00587a6a"
    },
    {
      "address": "00587a5e",
      "instruction": "CALL 0x0067caf0"
    },
    {
      "address": "00587a63",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00587a65",
      "instruction": "CALL 0x0067a120"
    },
    {
      "address": "00587a6a",
      "instruction": "MOV dword ptr [ESP + 0x40],0x60c874f"
    },
    {
      "address": "00587a72",
      "instruction": "MOV dword ptr [ESP + 0x10],0x13eb90c"
    },
    {
      "address": "00587a7a",
      "instruction": "XOR ECX,ECX"
    },
    {
      "address": "00587a7c",
      "instruction": "LEA EDX,[ESP + 0x14]"
    },
    {
      "address": "00587a80",
      "instruction": "XCHG dword ptr [EDX],ECX"
    },
    {
      "address": "00587a82",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00587a84",
      "instruction": "MOV EDX,dword ptr [EAX + 0x44]"
    },
    {
      "address": "00587a87",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00587a89",
      "instruction": "MOV dword ptr [ESP + 0x10],0x13eb844"
    },
    {
      "address": "00587a91",
      "instruction": "MOV dword ptr [ESP + 0x48],EBX"
    },
    {
      "address": "00587a95",
      "instruction": "CALL EDX"
    },
    {
      "address": "00587a97",
      "instruction": "MOV dword ptr [ESP + 0x18],EAX"
    },
    {
      "address": "00587a9b",
      "instruction": "CALL 0x0067dcc0"
    },
    {
      "address": "00587aa0",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "00587aa2",
      "instruction": "MOV EDX,dword ptr [EDX + 0x14]"
    },
    {
      "address": "00587aa5",
      "instruction": "PUSH EBX"
    },
    {
      "address": "00587aa6",
      "instruction": "LEA ECX,[ESP + 0x14]"
    },
    {
      "address": "00587aaa",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00587aab",
      "instruction": "MOV ECX,dword ptr [ESP + 0x48]"
    },
    {
      "address": "00587aaf",
      "instruction": "PUSH ECX"
    },
    {
      "address": "00587ab0",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00587ab2",
      "instruction": "CALL EDX"
    },
    {
      "address": "00587ab4",
      "instruction": "MOV EAX,[0x016f6ee0]"
    },
    {
      "address": "00587ab9",
      "instruction": "AND dword ptr [EAX],0xfffffffe"
    },
    {
      "address": "00587abc",
      "instruction": "MOV EAX,dword ptr [ESI]"
    },
    {
      "address": "00587abe",
      "instruction": "MOV EDX,dword ptr [EAX + 0x4c]"
    },
    {
      "address": "00587ac1",
      "instruction": "MOV ECX,ESI"
    },
    {
      "address": "00587ac3",
      "instruction": "CALL EDX"
    },
    {
      "address": "00587ac5",
      "instruction": "MOV ECX,dword ptr [ESI + 0x380]"
    },
    {
      "address": "00587acb",
      "instruction": "CMP ECX,EBX"
    },
    {
      "address": "00587acd",
      "instruction": "JZ 0x00587adc"
    },
    {
      "address": "00587acf",
      "instruction": "MOV dword ptr [ESI + 0x380],EBX"
    },
    {
      "address": "00587ad5",
      "instruction": "MOV EAX,dword ptr [ECX]"
    },
    {
      "address": "00587ad7",
      "instruction": "MOV EDX,dword ptr [EAX + 0x8]"
    },
    {
      "address": "00587ada",
      "instruction": "CALL EDX"
    },
    {
      "address": "00587adc",
      "instruction": "CALL 0x0067cac0"
    },
    {
      "address": "00587ae1",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00587ae3",
      "instruction": "CALL 0x0067ca40"
    },
    {
      "address": "00587ae8",
      "instruction": "MOVZX EAX,byte ptr [ESI + 0x144]"
    },
    {
      "address": "00587aef",
      "instruction": "MOV EBP,0x1"
    },
    {
      "address": "00587af4",
      "instruction": "PUSH EBP"
    },
    {
      "address": "00587af5",
      "instruction": "PUSH EAX"
    },
    {
      "address": "00587af6",
      "instruction": "CALL 0x0067cac0"
    },
    {
      "address": "00587afb",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "00587afd",
      "instruction": "CALL 0x0067c420"
    },
    {
      "address": "00587b02",
      "instruction": "CALL 0x0067dd10"
    },
    {
      "address": "00587b07",
      "instruction": "TEST EAX,EAX"
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
  "original_bytes": 19612,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"__thiscall\",\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"receiver\": true,\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": \"RET\",\n    \"return_observation\": \"Ghidra resolves return_type void (analyze_function_complete, ghidra_function.return_type_resolved true). The derived openspore-abi-inference-1 record for this target abstained (conventions.confidence UNKNOWN, calling_convention null, candidate_conventions __cdecl) and its return claim is contradicted by the balanced FLD/FSTP pair; see conflicts_and_disagreements.\",\n    \"return_semantics\": \"void. The epilogue is POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET: a bare RET with no immediate, and no instruction after the last call reads a return register. The x87 pair at 0x00587b10 (FLD float ptr [ESI+0x4d0]) and 0x00587b1b (FSTP float ptr [ESP]) is balanced -- FSTP pops what FLD pushed -- so nothing is left on the x87 stack, and the value is a 4-byte stack argument, not a result. This DISAGREES with the derived ABI record for this target, which reports return_register ST0 and return_semantics float_or_x87_in_ST0; that reading is a false positive of the linear-sweep inference, p...\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\",\n      \"ESI\"\n    ],\n    \"stack_arguments\": [],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": [\n      \"RET at 0x0058856a, bare, no immediate\",\n      \"RET\"\n    ]\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"property_record_assign_pair_004279d0\",\n      \"va\": \"0x004279d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Byte\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_paint_commit_0043ac40\",\n      \"va\": \"0x0043ac40\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:Byte\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"editor_bake_select_004c4a30\",\n      \"va\": \"0x004c4a30\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-PALETTE-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"palette_safe_wave11_fill_node_array_005c7ff0\",\n      \"va\": \"0x005c7ff0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_005fa8d0\",\n      \"va\": \"0x005fa8d0\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-APP-SERVICES-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"service_0060ee90\",\n      \"va\": \"0x0060ee90\"\n    },\n    {\n      \"match_basis\": [\n        \"same_calling_convention\",\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 5,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"shared_types:void*\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-12-SIM-SPACE\",\n      \"score\": 5,\n      \"symbol\": \"FUN_00aea230\",\n      \"va\": \"0x00aea230\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [\n    \"48 of the 54 direct callees have no name in the SDK and no recovered body in this repository. Their conventions and argument counts are fixed from their own epilogues, which is enough to call them correctly, but not enough to say what they do.\",\n    \"No original-process trace exists in this repository, so nothing about this function's runtime behaviour is established. The five conflict-ledger entries that name 0x00587a20 (editor_input_routing, editor_runtime_validation, history_budget_semantics, manipulator_cancel, manipulator_types) all record that their transition contract is not established, and all five remain open: knowledgegraph/research/conflicts/track-c-state-events.json.\",\n    \"The canonical record associates vtable:0x013f57f8 with this target while the xref export records vtable_reference_count 0 for it, so the two contradict each other and neither is independent of the other. No table is claimed as a dispatch target as a result.\",\n    \"The canonical record associates vtable:0x013f57f8 with this target while the xref export records vtable_reference_count 0, so the two contradict each other and neither is independent of the other. No table is claimed as a dispatch target.\",\n    \"The xref export's edge list for this target is truncated at 30 of 78 rows (MAX_DEPENDENCY_EDGES), so the validator's CALLS check can only WARN: the machine callee set is a lower bound and cannot bound the source. The 54-target parity reported above was measured against GhidraMCP directly instead.\"\n  ],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004ad330\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573d70\
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
  "body_end": "0058856a",
  "body_span_bytes": 2891,
  "body_start": "00587a20",
  "callees": [
    "FUN_0067cad0",
    "FUN_00421cf0",
    "FUN_0045ab30",
    "FUN_0067de40",
    "FUN_006c10e0",
    "FUN_00573d70",
    "FUN_0062c910",
    "FUN_005bfb90",
    "FUN_0067cab0",
    "FUN_005cba90",
    "FUN_00401050",
    "FUN_004c4eb0",
    "App::cIDGenerator::Get",
    "FUN_0067ca40",
    "FUN_00f473a0",
    "FUN_005dbb60",
    "Graphics::IModelManager::Get",
    "FUN_005c5c20",
    "FUN_005dbb50",
    "FUN_00777ae0",
    "FUN_0059c640",
    "FUN_004581d0",
    "FUN_00ed0660",
    "FUN_005de870",
    "FUN_004ad280",
    "FUN_0113ae10",
    "FUN_00801bb0",
    "App::DirectPropertyList::SetInt",
    "Palettes::cSwatchManager::Get",
    "FUN_0059a3b0",
    "FUN_007c53d0",
    "FUN_0067a120",
    "FUN_0043a9a0",
    "FUN_004b27c0",
    "FUN_0067caf0",
    "FUN_00579c80",
    "FUN_00571db0",
    "Graphics::IRenderer::Get",
    "Editors::cEditor::SetActiveMode",
    "FUN_0067cac0",
    "Graphics::IShadowWorld::Get",
    "App::IAppSystem::Get",
    "FUN_00a206f0",
    "FUN_004ad330",
    "FUN_00801920",
    "FUN_0067caa0",
    "FUN_005d31b0",
    "FUN_008130a0",
    "FUN_005772b0",
    "FUN_00573c00",
    "FUN_0047e6c0",
    "FUN_0067c420",
    "FUN_0067ddd0",
    "Graphics::ILightingManager::Get"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00587a20",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Editors::cEditor::OnExit",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 1,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "void",
  "return_type_resolved": true,
  "rva": "0x187a20",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "void Editors::cEditor::OnExit(cEditor * this)",
  "size_bytes": 2891,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00587a20",
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
      "from": "013f5814"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnExit.c",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-dogfood-00587a20-a1/editor_onexit_00587a20.hpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.cpp",
    "reconstruction/staging/pkg-editor-onexit-smoke01/editor_onexit_00587a20.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-dogfood-00587a20-a1/00587a20.json",
    "reconstruction/metadata/pkg-editor-onexit-smoke01/00587a20.json"
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
    "runtime validation not run: no positive hash-pinned original-process trace reaches 0x00587a20 in the committed corpus"
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
  "status": "queued"
}
```

## types

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "Byte",
  "Dword",
  "HIGH",
  "LocalAppState",
  "U64",
  "float",
  "void",
  "void*"
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
[
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058ac10",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x00e818f0",
      "0x00b3d350",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587a20"
    ],
    "conflict_id": "editor_input_routing",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "resolution_status": "The input/UI surface is structurally present, but partition, focus, priority, and consume behavior are not proven.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x005737d0",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x0058ac10",
      "0x0058ac10"
    ],
    "conflict_id": "editor_runtime_validation",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "resolution_status": "A positive hash-pinned original-process trace is required; static naming or conceptual state names are not promoted to runtime behavior.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "No positive original-process trace reaches this transition in the committed corpus."
  },
  {
    "anchors": [
      "0x00574080",
      "0x00586410",
      "0x0058ac10",
      "0x0058ac10",
      "0x004af260",
      "0x00574080",
      "0x00576c50",
      "0x00576c50",
      "0x0057ce80",
      "0x0057ce80",
      "0x00584300",
      "0x00584300",
      "0x00586410",
      "0x00587a20",
      "0x00587a20",
      "0x0058be50"
    ],
    "conflict_id": "history_budget_semantics",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x00586b00",
      "0x00587270",
      "0x00587a20",
      "0x00588570",
      "0x00588570",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587270"
    ],
    "conflict_id": "manipulator_cancel",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "resolution_status": "The committed evidence does not establish the requested transition contract; the available observation is retained without semantic promotion.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
  {
    "anchors": [
      "0x005737d0",
      "0x00588570",
      "0x0058b650",
      "0x00588570",
      "0x0057f3e0",
      "0x005737d0",
      "0x005737d0",
      "0x005737d0",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00587a20",
      "0x00587a20",
      "0x00588570",
      "0x00588570"
    ],
    "conflict_id": "manipulator_types",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "resolution_status": "The address/layout alternatives are preserved; no owner or exact binary identity is selected without a typed body or constructor path.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  }
]
```
