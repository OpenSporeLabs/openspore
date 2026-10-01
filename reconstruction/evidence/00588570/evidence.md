# Evidence 0x00588570

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `49bb46426b6d9f586d78ebeb4ab9d816253454eb1aa0331afd9cacbe1ca1ccb3`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup",
  "return_semantics": "bool in AL from the selected mouse-down path",
  "return_type": "bool",
  "stack_cleanup_bytes": 16,
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
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x4",
      "entry_ESP+0x7"
    ],
    "ordinary_stack_argument_slots_bounded": {
      "kept": 2,
      "omitted": 22
    },
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
      },
      {
        "entry_offset": "entry_ESP+0x7",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "ordinary_stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "receiver": true,
    "receiver_register": "ECX",
    "ret_form": "RET 0x10",
    "return_register": "ST0",
    "return_semantics": "float_or_x87_in_ST0",
    "saved_registers": [
      "EBP",
      "EBX",
      "EDI",
      "ESI"
    ],
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
      },
      {
        "entry_offset": "entry_ESP+0x7",
        "observed": true,
        "ordinal": 1,
        "read": false,
        "size_inferred": false,
        "sizes": [
          1
        ],
        "written": false
      }
    ],
    "stack_arguments_bounded": {
      "kept": 2,
      "omitted": 22
    },
    "termination": "RET 0x10"
  },
  "abstained_because": [
    "flow_not_modelled: the linear ESP walk ends at -180, so the listing is not one path",
    "unparsed_lines_present: 2 line(s) matched no grammar rule",
    "untrusted_frame_stack_reads: push ebp with no mov ebp,esp: EBP is a general register, so every frame-relative offset is uncalibrated",
    "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is loaded from a register or used as a memory base, so it is a general register",
    "ret_imm_below_highest_slot: ret 0x10 pops less than the highest read slot 0x20c; everything above it belongs to the caller's frame",
    "slot_width_ambiguous: one entry slot is read at more than one width",
    "slot_gaps_present: argument ordinal(s) below the highest read slot are never touched",
    "no_discriminator: the callee pop of 0x10 is not a whole number of dword stack arguments, so no convention follows from it"
  ],
  "cleanup": {
    "bytes": 16,
    "confidence": "UNKNOWN",
    "corroboration": "not_available",
    "evidence": "ret 0x10 but entry slot 0x20c is read",
    "side": null
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "15fbac6d233ea06957873cd36b27d9c5259691375e6e27732f3abba4c826d312",
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
    "ghidra_parameter_count": 5,
    "persisted": "no_information",
    "persisted_calling_convention": "x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 21,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0030",
        "obs-0101",
        "obs-0125",
        "obs-0559",
        "obs-0565",
        "obs-0571",
        "obs-0580"
      ],
      "claim": "the callee pops 16 byte(s) of stack arguments",
      "confidence": "OBSERVED",
      "id": "C3",
      "value": {
        "bytes": 16,
        "side": "callee"
      }
    },
    {
      "based_on": [
        "obs-0030",
        "obs-0101",
        "obs-0125",
        "obs-0559",
        "obs-0565",
        "obs-0571",
        "obs-0580"
      ],
      "claim": "cleanup side is undetermined: a slot above the popped area is read",
      "confidence": "UNKNOWN",
      "id": "C4",
      "value": {
        "bytes": 16,
        "side": null
      }
    },
    {
      "based_on": [
        "obs-0018",
        "obs-0046",
        "obs-0047",
        "obs-0048",
        "obs-0055",
        "obs-0059",
        "obs-0063",
        "obs-0064",
        "obs-0065",
        "obs-0066",
        "obs-0067",
        "obs-0068",
        "obs-0069",
        "obs-0070",
        "obs-0103",
        "obs-0104",
        "obs-0126",
        "obs-0127",
        "obs-0128",
        "obs-0129",
        "obs-0130",
        "obs-0131",
        "obs-0132",
        "obs-0133",
        "obs-0134",
        "obs-0135",
        "obs-0136",
        "obs-0137",
        "obs-0139",
        "obs-0140",
        "obs-0141",
        "obs-0142",
        "obs-0145",
        "obs-0147",
        "obs-0150",
        "obs-0152",
        "obs-0153",
        "obs-0154",
        "obs-0156",
        "obs-0157",
        "obs-0158",
        "obs-0159",
        "obs-0160",
        "obs-0161",
        "obs-0162",
        "obs-0163",
        "obs-0164",
        "obs-0166",
        "obs-0168",
        "obs-0169",
        "obs-0170",
        "obs-0171",
        "obs-0172",
        "obs-0173",
        "obs-0174",
        "obs-0175",
        "obs-0176",
        "obs-0177",
        "obs-0179",
        "obs-0183",
        "obs-0184",
        "obs-0185",
        "obs-0186",
        "obs-0188",
        "obs-0190",
        "obs-0192",
        "obs-0193",
        "obs-0194",
        "obs-0195",
        "obs-0198",
        "obs-0200",
        "obs-0202",
        "obs-0203",
        "obs-0204",
        "obs-0205",
        "obs-0206",
        "obs-0207",
        "obs-0222",
        "obs-0231",
        "obs-0232",
        "ob
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
    "va": "0x0045ae10"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004a88d0"
  },
  {
    "name": "FUN_004adc40",
    "reconstructed": false,
    "va": "0x004adc40"
  },
  {
    "name": "Editors_EditorModel_SetColor_raw_004ae250",
    "reconstructed": true,
    "va": "0x004ae250"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x004b09b0"
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
    "va": "0x005766e0"
  },
  {
    "name": null,
    "reconstructed": false,
    "va": "0x005772b0"
  },
  {
    "name": "utfwin_safe_wave11_005ac9f0",
    "reconstructed": true,
    "va": "0x005ac9f0"
  },
  {
    "name": "FUN_00c2e4e0",
    "reconstructed": false,
    "va": "0x00c2e4e0"
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
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058a5a0"
    ],
    "conflict_id": "U-002-tribe-plans",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
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
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
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
  "count": 1749,
  "instructions": [
    {
      "address": "00588570",
      "instruction": "XORPS XMM0,XMM0"
    },
    {
      "address": "00588573",
      "instruction": "SUB ESP,0xc4"
    },
    {
      "address": "00588579",
      "instruction": "PUSH EBX"
    },
    {
      "address": "0058857a",
      "instruction": "PUSH EBP"
    },
    {
      "address": "0058857b",
      "instruction": "PUSH ESI"
    },
    {
      "address": "0058857c",
      "instruction": "MOV EBP,ECX"
    },
    {
      "address": "0058857e",
      "instruction": "PUSH EDI"
    },
    {
      "address": "0058857f",
      "instruction": "XOR EDI,EDI"
    },
    {
      "address": "00588581",
      "instruction": "CMP byte ptr [EBP + 0x397],0x0"
    },
    {
      "address": "00588588",
      "instruction": "MOVSS dword ptr [EBP + 0x68],XMM0"
    },
    {
      "address": "0058858d",
      "instruction": "JNZ 0x00589cc6"
    },
    {
      "address": "00588593",
      "instruction": "CMP dword ptr [EBP + 0x148],EDI"
    },
    {
      "address": "00588599",
      "instruction": "JNZ 0x005885c8"
    },
    {
      "address": "0058859b",
      "instruction": "CMP dword ptr [EBP + 0x34],EDI"
    },
    {
      "address": "0058859e",
      "instruction": "JNZ 0x005885c8"
    },
    {
      "address": "005885a0",
      "instruction": "CMP byte ptr [EBP + 0x472],0x0"
    },
    {
      "address": "005885a7",
      "instruction": "MOV ESI,dword ptr [ESP + 0xd8]"
    },
    {
      "address": "005885ae",
      "instruction": "MOV dword ptr [EBP + 0x34],ESI"
    },
    {
      "address": "005885b1",
      "instruction": "JZ 0x005885b8"
    },
    {
      "address": "005885b3",
      "instruction": "CALL 0x00586960"
    },
    {
      "address": "005885b8",
      "instruction": "CMP byte ptr [EBP + 0x4d4],0x0"
    },
    {
      "address": "005885bf",
      "instruction": "JZ 0x005885d7"
    },
    {
      "address": "005885c1",
      "instruction": "MOV ECX,EBP"
    },
    {
      "address": "005885c3",
      "instruction": "CALL 0x005724a0"
    },
    {
      "address": "005885c8",
      "instruction": "MOV AL,0x1"
    },
    {
      "address": "005885ca",
      "instruction": "POP EDI"
    },
    {
      "address": "005885cb",
      "instruction": "POP ESI"
    },
    {
      "address": "005885cc",
      "instruction": "POP EBP"
    },
    {
      "address": "005885cd",
      "instruction": "POP EBX"
    },
    {
      "address": "005885ce",
      "instruction": "ADD ESP,0xc4"
    },
    {
      "address": "005885d4",
      "instruction": "RET 0x10"
    },
    {
      "address": "005885d7",
      "instruction": "CALL 0x0067cab0"
    },
    {
      "address": "005885dc",
      "instruction": "MOV EDX,dword ptr [EAX]"
    },
    {
      "address": "005885de",
      "instruction": "MOV EDX,dword ptr [EDX + 0x34]"
    },
    {
      "address": "005885e1",
      "instruction": "LEA ECX,[EBP + 0xc4]"
    },
    {
      "address": "005885e7",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005885e8",
      "instruction": "LEA ECX,[EBP + 0xc0]"
    },
    {
      "address": "005885ee",
      "instruction": "PUSH ECX"
    },
    {
      "address": "005885ef",
      "instruction": "MOV ECX,EAX"
    },
    {
      "address": "005885f1",
      "instruction": "CALL EDX"
    },
    {
      "address": "005885f3",
      "instruction": "CMP ESI,0x3e9"
    },
    {
      "address": "005885f9",
      "instruction": "JZ 0x00589ca0"
    },
    {
      "address": "005885ff",
      "instruction": "CMP ESI,0x3ea"
    },
    {
      "address": "00588605",
      "instruction": "JZ 0x00589ca0"
    },
    {
      "address": "0058860b",
      "instruction": "CMP ESI,0x3e8"
    },
    {
      "address": "00588611",
      "instruction": "JNZ 0x00588641"
    },
    {
      "address": "00588613",
      "instruction": "CMP dword ptr [EBP + 0xcc],EDI"
    },
    {
      "address": "00588619",
      "instruction": "JNZ 0x00588641"
    },
    {
      "address": "0058861b",
      "instruction": "CMP dword ptr [EBP + 0xe4],EDI"
    },
    {
      "address": "00588621",
      "instruction": "JNZ 0x00588641"
    },
    {
      "address": "00588623",
      "instruction": "CMP byte ptr [EBP + 0xe8],0x0"
    },
    {
      "address": "0058862a",
      "instruction": "JNZ 0x00588641"
    },
    {
      "address": "0058862c",
      "instruction": "CMP dword ptr [EBP + 0x31c],0x2"
    },
    {
      "address": "00588633",
      "instruction": "JZ 0x00588641"
    },
    {
      "address": "00588635",
      "instruction": "CMP dword ptr [EBP + 0xd0],EDI"
    },
    {
      "address": "0058863b",
      "instruction": "JZ 0x00589ca0"
    },
    {
      "address": "00588641",
      "instruction": "CALL 0x0067dd80"
    },
    {
      "address": "00588646",
      "instruction": "CMP EAX,EDI"
    },
    {
      "address": "00588648",
      "instruction": "JZ 0x00589cc6"
    },
    {
      "address": "0058864e",
      "instruction": "CMP dword ptr [EBP + 0x84],EDI"
    },
    {
      "address": "00588654",
      "instruction": "JZ 0x00589cc6"
    },
    {
      "address": "0058865a",
      "instruction": "MOV EAX,dword ptr [EBP + 0x31c]"
    },
    {
      "address": "00588660",
      "instruction": "FLD float ptr [ESP + 0xe0]"
    },
    {
      "address": "00588667",
      "instruction": "SUB EAX,EDI"
    },
    {
      "address": "00588669",
      "instruction": "FLD float ptr [ESP + 0xdc]"
    },
    {
      "address": "00588670",
      "instruction": "JZ 0x0058883e"
    },
    {
      "address": "00588676",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "00588679",
      "instruction": "JZ 0x005886b4"
    },
    {
      "address": "0058867b",
      "instruction": "SUB EAX,0x1"
    },
    {
      "address": "0058867e",
      "instruction": "JNZ 0x00589ba0"
    },
    {
      "address": "00588684",
      "instruction": "CMP ESI,0x3e8"
    },
    {
      "address": "0058868a",
      "instruction": "JNZ 0x00589ba0"
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
  "original_bytes": 13988,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": \"x86-32 thiscall with first explicit editor receiver in ECX and caller cleanup\",\n    \"return_semantics\": \"bool in AL from the selected mouse-down path\",\n    \"return_type\": \"bool\",\n    \"stack_cleanup_bytes\": 16,\n    \"stack_cleanup_owner\": \"caller\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_005737d0\",\n      \"va\": \"0x005737d0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585890\",\n      \"va\": \"0x00585890\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_00585d10\",\n      \"va\": \"0x00585d10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058ac10\",\n      \"va\": \"0x0058ac10\"\n    },\n    {\n      \"match_basis\": [\n        \"same_package\",\n        \"same_subsystem\",\n        \"shared_types:openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor,openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks,openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget,openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget\",\n        \"shared_vtable:vtable:0x013f57f8\",\n        \"same_calling_convention\"\n      ],\n      \"package\": \"PKG-EDITOR-INPUT-WAVE6\",\n      \"score\": 29,\n      \"symbol\": \"editor_input_0058b650\",\n      \"va\": \"0x0058b650\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-10-EDITOR-DISPATCH\",\n      \"score\": 3,\n      \"symbol\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n      \"va\": \"0x004ae250\"\n    },\n    {\n      \"match_basis\": [\n        \"direct_xref_neighbor\"\n      ],\n      \"package\": \"PKG-UTFWIN-SAFE-WAVE11\",\n      \"score\": 3,\n      \"symbol\": \"utfwin_safe_wave11_005ac9f0\",\n      \"va\": \"0x005ac9f0\"\n    }\n  ],\n  \"audit_evidence_boundary\": \"Reviewed static mechanics and x86-32 ABI are preserved; opaque runtime ports and ownership remain gated.\",\n  \"audit_findings\": [],\n  \"audit_status\": \"clean_after_reviewed_repairs\",\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": \"integrated\",\n  \"class_type\": null,\n  \"cluster\": \"editor-core\",\n  \"confidence\": 0.9,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x0045ae10\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004a88d0\"\n      },\n      {\n        \"name\": \"FUN_004adc40\",\n        \"reconstructed\": false,\n        \"va\": \"0x004adc40\"\n      },\n      {\n        \"name\": \"Editors_EditorModel_SetColor_raw_004ae250\",\n        \"reconstructed\": true,\n        \"va\": \"0x004ae250\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x004b09b0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573c00\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00573d70\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005766e0\"\n      },\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x005772b0\"\n      },\n      {\n        \"name\": \"utfwin_safe_wave11_005ac9f0\",\n        \"reconstructed\": true,\n        \"va\": \"0x005ac9f0\"\n      },\n      {\n        \"name\": \"FUN_00c2e4e0\",\n        \"reconstructed\": false,\n        \"va\": \"0x00c2e4e0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"ca
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
  "body_end": "00589cd4",
  "body_span_bytes": 5989,
  "body_start": "00588570",
  "callees": [
    "FUN_005ca950",
    "FUN_0043cfc0",
    "FUN_005bd750",
    "FUN_00440f60",
    "FUN_0048f790",
    "FUN_0044b550",
    "FUN_00577580",
    "FUN_005bc7f0",
    "FUN_007c3d30",
    "FUN_0043ca10",
    "FUN_0057c530",
    "FUN_00573d70",
    "FUN_0047e680",
    "FUN_0067cab0",
    "FUN_0093a560",
    "FUN_00438a40",
    "FUN_00575f20",
    "FUN_005b23d0",
    "FUN_00401050",
    "FUN_005b7a70",
    "FUN_005ae610",
    "FUN_005ad9a0",
    "FUN_00573a60",
    "FUN_00496bb0",
    "FUN_0057e790",
    "FUN_00f473a0",
    "FUN_005b9840",
    "FUN_005aab00",
    "FUN_005b53c0",
    "FUN_00c2e4e0",
    "FUN_005b7460",
    "FUN_0044f420",
    "FUN_0045ae10",
    "FUN_005766e0",
    "FUN_005b5110",
    "FUN_004adfc0",
    "FUN_0044eea0",
    "FUN_005aac30",
    "FUN_004b09b0",
    "FUN_005b4b40",
    "FUN_005bc860",
    "FUN_005accc0",
    "FUN_004aa030",
    "FUN_005ba060",
    "FUN_00571e80",
    "FUN_004a88d0",
    "FUN_00573a10",
    "FUN_005b85d0",
    "FUN_00435a10",
    "FUN_005ac9f0",
    "FUN_00440c40",
    "FUN_00577dd0",
    "FUN_005bdca0",
    "FUN_004a6d20",
    "Graphics::IRenderer::Get",
    "FUN_004a5e10",
    "FUN_005ac980",
    "FUN_005aa420",
    "FUN_004a6120",
    "FUN_005ad930",
    "Graphics::IShadowWorld::Get",
    "FUN_0044bcf0",
    "FUN_00586960",
    "FUN_0045ae40",
    "FUN_00435f40",
    "FUN_004b2800",
    "FUN_00448d60",
    "FUN_005b7490",
    "FUN_005aa3d0",
    "FUN_005b2180",
    "FUN_004a60a0",
    "FUN_0061df40",
    "FUN_005740e0",
    "Editors::cEditor::SetCreatureToNeutralPose",
    "FUN_0044f220",
    "Editors::EditorModel::SetColor",
    "FUN_005772b0",
    "FUN_004adc40",
    "FUN_00573c00",
    "Editors::cEditor::CommitEditHistory",
    "FUN_005b4ad0",
    "FUN_00ac9480",
    "FUN_0047e6c0",
    "FUN_00440d80",
    "FUN_00ac8980",
    "FUN_005cb1b0",
    "FUN_00572750",
    "FUN_00b5f950",
    "FUN_004a7f30",
    "FUN_0057af00",
    "FUN_005724a0",
    "FUN_005ae870"
  ],
  "callers": [],
  "classification": "worker",
  "dispatch": null,
  "entry_point": "00588570",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "Editors::cEditor::OnMouseDown",
  "namespace": "Editors",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 5,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "cEditor *"
    },
    {
      "name": "mouseButton",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "MouseButton"
    },
    {
      "name": "mouseX",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "float"
    },
    {
      "name": "mouseY",
      "ordinal": 3,
      "storage": "Stack[0x10]:4",
      "type": "float"
    },
    {
      "name": "mouseState",
      "ordinal": 4,
      "storage": "Stack[0x14]:4",
      "type": "MouseState"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x188570",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool Editors::cEditor::OnMouseDown(cEditor * this, MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState)",
  "size_bytes": 5989,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00588570",
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
      "from": "013f5824"
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
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseDown.c",
  "file": "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__OnMouseDown.c",
    "src/reconstruction/pkg_editor_input_wave6/editor_input.cpp"
  ],
  "handoffs": [
    "reconstruction/integrated/batch-2026-09-25-wave6-integrator-clean/handoff.json"
  ],
  "metadata": [
    "reconstruction/metadata/pkg-editor-input-wave6/00588570.json"
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
    "graphics availability, mode-specific input targets, and runtime button ownership remain gated",
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
  "bool",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueEditor",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueInputHooks",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueModeTarget",
  "openspore::reconstruction::pkg_editor_input_wave6::OpaqueSelectionTarget",
  "openspore::reconstruction::pkg_editor_input_wave6::TargetWord"
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
      "0x00d2e4a0",
      "0x00d2e4a0",
      "0x00aeb7b0",
      "0x005737d0",
      "0x005737d0",
      "0x00585d10",
      "0x00585d10",
      "0x00586410",
      "0x00586410",
      "0x00586b00",
      "0x00586b00",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058a5a0"
    ],
    "conflict_id": "U-002-tribe-plans",
    "kind": "conflict_ledger",
    "rejected": [],
    "resolution": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "resolution_status": "The declared state surface is retained, but the complete writer/callback chain and runtime transition order are not recovered.",
    "source": "knowledgegraph/research/conflicts/track-c-state-events.json",
    "subject": null,
    "unresolved_reason": "Runtime reachability is absent or the required direct body/call path is not recovered."
  },
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
      "0x005e0000",
      "0x70218642",
      "0xb006ef6e",
      "0xf006efa5",
      "0xf019c2e7",
      "0xf019c2f3",
      "0x005e0000",
      "0x004af260",
      "0x005dda30",
      "0x005737d0",
      "0x005737d0",
      "0x00587270",
      "0x00587270",
      "0x00588570",
      "0x00588570",
      "0x0058ac10"
    ],
    "conflict_id": "editor_ui_command_names",
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
      "0x005
[TRUNCATED]
```
