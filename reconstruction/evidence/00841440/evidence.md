# Evidence 0x00841440

- Evidence state: `LIVE`
- Live requested: `True`
- Content SHA-256: `9388e237d2edc0a3550ad26ab490fd84158293b1376915517de14e45723731d6`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": [
    "x86-32 thiscall; receiver in ECX, two ordinary stack arguments, callee cleanup",
    "__thiscall"
  ],
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "hidden_this_type": "FormatParser * per the SDK/Ghidra import label; the object is opaque here because no FormatParser vtable could be corroborated (see vtables)",
  "ordinary_stack_argument_slots": 2,
  "ordinary_stack_arguments": [
    {
      "declared_name": "pName",
      "declared_type": "char *",
      "provenance": "SDK FUNCTION_DEF CreateDefinitionSafe(FormatParser* this, char* pName, Line* argumentsLine); the slot assignment is fixed by the unsafe sibling CreateDefinition (0x00844fb0..0x0084524e), which strlen-scans [EBP+0x8] and formats it as a name",
      "slot": "[ESP+0x4]"
    },
    {
      "declared_name": "argumentsLine",
      "declared_type": "Line *",
      "provenance": "the same unsafe sibling dereferences [EBP+0xc] as an object (MOV EDI,dword ptr [ECX + 0x10] at 0x008450b8) and hands the loaded word to a string-length helper, so this slot is the line pointer",
      "slot": "[ESP+0x8]"
    }
  ],
  "receiver_register": "ECX",
  "ret_form": [
    "absent in the target body; inherited RET 0x8 from 0x0083c780",
    "RET 0x8, inherited from 0x0083c78e rather than present in this body"
  ],
  "return_note": "declared. The target body never writes EAX; the value a caller observes is whatever 0x0083c780 leaves there, and that function's last write to EAX is MOV EAX,dword ptr [ESP + 0x4] at 0x0083c780, i.e. the first stack argument. So the observed return is the low byte of the pName word, consistent with the declared bool.",
  "return_register": "EAX",
  "return_type": "bool",
  "saved_registers": [],
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": [
    "the shared tail 0x0083c780, which ends in C2 08 00 (RET 0x8). 0x00841440 contains no RET and no ADD ESP, so the two argument words are popped by the callee.",
    "callee, and not this body: the RET 0x8 belongs to the shared tail 0x0083c780, which both JMPs enter. 0x00841440 contains no RET and no stack adjustment of any kind."
  ],
  "termination": "tail call, two sites"
}
```

## abi_derived

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function, tools/reconstruction_tooling/abi_infer.py#tail_target=0x0083c780`

```json
{
  "abi": {
    "architecture": "x86-32",
    "calling_convention": "__thiscall",
    "hidden_this": true,
    "hidden_this_register": "ECX",
    "ordinary_stack_argument_slots": [
      "entry_ESP+0x8"
    ],
    "ordinary_stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
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
    "return_register": "EAX",
    "return_semantics": "integral_in_EAX",
    "stack_arguments": [
      {
        "entry_offset": "entry_ESP+0x8",
        "observed": true,
        "ordinal": 2,
        "read": false,
        "size_inferred": false,
        "sizes": [
          4
        ],
        "written": false
      }
    ],
    "stack_cleanup_bytes": 8,
    "stack_cleanup_owner": "callee"
  },
  "abstained_because": [
    "no_terminal_ret: the only exit observed is a tail jump"
  ],
  "cleanup": {
    "bytes": 8,
    "confidence": "OBSERVED",
    "corroboration": "forwarded_from_tail_target",
    "evidence": "forwarded from the tail target 0x0083c780: ret 0x8",
    "side": "callee"
  },
  "completeness": "PARTIAL",
  "conflicts": [],
  "content_sha256": "65ca8163f8ef0669c5956158ea38934ba70d9a990005a36218836c31b107c5e2",
  "conventions": {
    "ambiguities": [],
    "calling_convention": "__thiscall",
    "candidate_conventions": [
      "__thiscall"
    ],
    "confidence": "INFERRED",
    "corroboration": "forwarded_from_tail_target"
  },
  "cross_validation": {
    "agreement": false,
    "ghidra": "no_information",
    "ghidra_calling_convention": null,
    "ghidra_parameter_count": 3,
    "persisted": "no_information",
    "persisted_calling_convention": "['x86-32 thiscall; receiver in ECX, two ordinary stack arguments, callee cleanup', '__thiscall']"
  },
  "dispatch": {
    "call_offsets": [],
    "indirect_calls": 0,
    "vtable_shaped_loads": 0
  },
  "inferences": [
    {
      "based_on": [
        "obs-0011"
      ],
      "claim": "no terminal return is present in the listing",
      "confidence": "UNKNOWN",
      "id": "C2"
    },
    {
      "based_on": [
        "obs-0002",
        "obs-0007",
        "obs-0010"
      ],
      "claim": "entry-relative argument slots",
      "confidence": "APPROXIMATION",
      "id": "A1",
      "value": {
        "gaps": 1,
        "observed_slots": 1,
        "total_bytes": 8
      }
    },
    {
      "based_on": [
        "obs-0006"
      ],
      "claim": "ECX carries a receiver and is dereferenced before any definite write to it",
      "confidence": "INFERRED",
      "id": "R1",
      "value": {
        "offsets": [
          48
        ],
        "register": "ECX",
        "written_through": 2
      }
    },
    {
      "based_on": [
        "obs-0011"
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
        "obs-0011"
      ],
      "claim": "this listing is a tail transfer: it inherits its caller's frame and never runs its own RET",
      "confidence": "UNKNOWN",
      "id": "T1",
      "value": {
        "form": "jmp"
      }
    },
    {
      "based_on": [
        "obs-0008",
        "obs-0011"
      ],
      "claim": "calling convention is __thiscall, forwarded from the tail target 0x0083c780: all 2 of this listing's direct jumps resolve to that one ESP-neutral target, inherits its caller's frame and never runs its own RET, so the two calls are one call (resolved from live listing for 0x0083c780)",
      "confidence": "INFERRED",
      "id": "T1-FWD",
      "value": "__thiscall"
    }
  ],
  "observations": [
    {
      "at": "0x00841440",
      "count": 3,
      "first_use": 0,
      "first_write_index": null,
      "id": "obs-0001",
      "index": 0,
      "kind": "REG_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "reg": "ESP"
    },
    {
      "at": "0x00841440",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0002",
      "index": 0,
      "key": 8,
      "kind": "STACK_SLOT_READ",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "resolved": true,
      "size": 4
    },
    {
      "at": "0x00841440",
      "definite": true,
      "id": "obs-0003",
      "index": 0,
      "kind": "REG_WRITE",
      "raw": "MOV EDX,dword ptr [ESP + 0x8]",
      "reg": "EDX",
      "write_kind": "mem_load"
    },
    {
      "at": "0x00841448",
      "count": 4,
      "first_use": 3,
      "first_write_index": 7,
      "id": "obs-0004",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EAX,[EDX + -0x4]",
      "reg": "EAX"
    },
    {
      "at": "0x00841448",
      "count": 3,
      "first_use": 3,
      "first_write_index": 0,
      "id": "obs-0005",
      "index": 3,
      "kind": "REG_READ",
      "raw": "LEA EAX,[EDX + -0x4]",
      "reg": "EDX"
    },
    {
      "at": "0x0084144b",
      "count": 2,
      "first_use": 4,
      "first_write_index": null,
      "id": "obs-0006",
      "index": 4,
      "kind": "REG_READ",
      "raw": "MOV dword ptr [ECX + 0x30],EAX",
      "reg": "ECX"
    },
    {
      "at": "0x0084144e",
      "base": "ESP",
      "disp": 8,
      "id": "obs-0007",
      "index": 5,
      "key": 8,
      "kind": "STACK_SLOT_WRITE",
      "raw": "MOV dword ptr [ESP + 0x8],EDX",
      "resolved": true,
      "size": 4,
      "via": "direct"
    },
    {
      "at": "0x00841452",
      "id": "obs-0008",
      "index": 6,
      "kind": "UNCOND_TRANSFER_OUT",
      "raw": "JMP 0x0083c780",
      "target": "0x0083c780"
    },
    {
      "at": "0x00841457",
      "definite": true,
      "id": "obs-0009",
      "index": 7,
      "kind": "REG_WRITE",
      "raw": "XOR EAX,EAX",
      "reg": "EAX",
      "write_kind": "zero"
    },
    {
      "at": "0x0084145c",
      "base": "ESP",
      "disp": 8,
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

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "anchors": [
      "0x00845310",
      "0x00b1fdb0",
      "0x00845310",
      "0x00b1fdb0",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000",
      "0x00845310",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:1",
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
      "0x005c7d00",
      "0x005c7d00",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x005c7d00",
      "0x005c7cb0",
      "0x005c7f10",
      "0x005c7f70",
      "0x00842d10",
      "0x00844180",
      "0x00843000",
      "0x00845310",
      "0x0067dd90"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:7",
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
      "0x00845310",
      "0x00845310",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:8",
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
  "count": 11,
  "instructions": [
    {
      "address": "00841440",
      "instruction": "MOV EDX,dword ptr [ESP + 0x8]"
    },
    {
      "address": "00841444",
      "instruction": "TEST EDX,EDX"
    },
    {
      "address": "00841446",
      "instruction": "JZ 0x00841457"
    },
    {
      "address": "00841448",
      "instruction": "LEA EAX,[EDX + -0x4]"
    },
    {
      "address": "0084144b",
      "instruction": "MOV dword ptr [ECX + 0x30],EAX"
    },
    {
      "address": "0084144e",
      "instruction": "MOV dword ptr [ESP + 0x8],EDX"
    },
    {
      "address": "00841452",
      "instruction": "JMP 0x0083c780"
    },
    {
      "address": "00841457",
      "instruction": "XOR EAX,EAX"
    },
    {
      "address": "00841459",
      "instruction": "MOV dword ptr [ECX + 0x30],EAX"
    },
    {
      "address": "0084145c",
      "instruction": "MOV dword ptr [ESP + 0x8],EDX"
    },
    {
      "address": "00841460",
      "instruction": "JMP 0x0083c780"
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
  "original_bytes": 13210,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": [\n      \"x86-32 thiscall; receiver in ECX, two ordinary stack arguments, callee cleanup\",\n      \"__thiscall\"\n    ],\n    \"hidden_this\": true,\n    \"hidden_this_register\": \"ECX\",\n    \"hidden_this_type\": \"FormatParser * per the SDK/Ghidra import label; the object is opaque here because no FormatParser vtable could be corroborated (see vtables)\",\n    \"ordinary_stack_argument_slots\": 2,\n    \"ordinary_stack_arguments\": [\n      {\n        \"declared_name\": \"pName\",\n        \"declared_type\": \"char *\",\n        \"provenance\": \"SDK FUNCTION_DEF CreateDefinitionSafe(FormatParser* this, char* pName, Line* argumentsLine); the slot assignment is fixed by the unsafe sibling CreateDefinition (0x00844fb0..0x0084524e), which strlen-scans [EBP+0x8] and formats it as a name\",\n        \"slot\": \"[ESP+0x4]\"\n      },\n      {\n        \"declared_name\": \"argumentsLine\",\n        \"declared_type\": \"Line *\",\n        \"provenance\": \"the same unsafe sibling dereferences [EBP+0xc] as an object (MOV EDI,dword ptr [ECX + 0x10] at 0x008450b8) and hands the loaded word to a string-length helper, so this slot is the line pointer\",\n        \"slot\": \"[ESP+0x8]\"\n      }\n    ],\n    \"receiver_register\": \"ECX\",\n    \"ret_form\": [\n      \"absent in the target body; inherited RET 0x8 from 0x0083c780\",\n      \"RET 0x8, inherited from 0x0083c78e rather than present in this body\"\n    ],\n    \"return_note\": \"declared. The target body never writes EAX; the value a caller observes is whatever 0x0083c780 leaves there, and that function's last write to EAX is MOV EAX,dword ptr [ESP + 0x4] at 0x0083c780, i.e. the first stack argument. So the observed return is the low byte of the pName word, consistent with the declared bool.\",\n    \"return_register\": \"EAX\",\n    \"return_type\": \"bool\",\n    \"saved_registers\": [],\n    \"stack_cleanup_bytes\": 8,\n    \"stack_cleanup_owner\": [\n      \"the shared tail 0x0083c780, which ends in C2 08 00 (RET 0x8). 0x00841440 contains no RET and no ADD ESP, so the two argument words are popped by the callee.\",\n      \"callee, and not this body: the RET 0x8 belongs to the shared tail 0x0083c780, which both JMPs enter. 0x00841440 contains no RET and no stack adjustment of any kind.\"\n    ],\n    \"termination\": \"tail call, two sites\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-ARGSCRIPT-WAVE9\",\n      \"score\": 6,\n      \"symbol\": \"pkg_argscript_get_current_scope_00d1dcd0\",\n      \"va\": \"0x00d1dcd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"scripting-content\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [],\n    \"callees_truncated\": false,\n    \"callers\": [],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00841452\",\n        \"direction\": \"out\",\n        \"other\": \"0x0083c780\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00841460\",\n        \"direction\": \"out\",\n        \"other\": \"0x0083c780\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 0,\n    \"fan_out\": 0,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [],\n    \"scc\": {\n      \"id\": \"scc-0260\",\n      \"size\": 1\n    },\n    \"vtable_reference_count\": 0\n  },\n  \"evidence_level\": \"CONFIRMED\",\n  \"globals\": [\n    \"global:PASS\"\n  ],\n  \"integration_status\": null,\n  \"name\": \"ArgScript::FormatParser::CreateDefinitionSafe\",\n  \"normalized_symbol\": \"ArgScript::FormatParser::CreateDefinitionSafe\",\n  \"observed_mechanics\": [],\n  \"ownership\": {\n    \"claimability\": \"queue_candidate\",\n    \"handoff_packages\": [],\n    \"manifest\": {\n      \"record\": null,\n      \"worker_ownership\": null\n    },\n    \"package\": null,\n    \"queue_state\": \"queued\"\n  },\n  \"package\": null,\n  \"reconstructed\": false,\n  \"review_status\": null,\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [],\n    \"validated\": 0\n  },\n  \"runtime_gated\": false,\n  \"runtime_validated\": 0,\n  \"semantic\": null,\n  \"semantic_status\": null,\n  \"services\": [],\n  \"source\": {\n    \"decomp\": \".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c\",\n    \"file\": null,\n    \"files\": [\n      \".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c\",\n      \"reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.cpp\",\n      \"reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.hpp\",\n      \"reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440_model_test.cpp\",\n      \"reconstruction/staging/pkg-dfw-00841440/dfw_00841440.cpp\",\n      \"reconstruction/staging/pkg-dfw-00841440/dfw_00841440_model_test.cpp\",\n      \"reconstruction/staging/pkg-dfw-00841440/dfw_00841440_types.hpp\"\n    ],\n    \"handoffs\": [],\n    \"metadata\": [\n      \"reconstruction/metadata/pkg-argscript-createdefsafe-00841440/00841440.json\",\n      \"reconstruction/metadata/pkg-dfw-00841440/00841440.json\"\n    ],\n    \"provenance\": []\n  },\n  \"status\": \"queued\",\n  \"subsystem\": \"ArgScript\",\n  \"triage\": {\n    \"category\": \"ENGINE_INTERFACE\",\n    \"cluster\": \"scripting-content\",\n    \"db_triage_status\": \"QUEUED\",\n    \"decomp_path\": \".spore-analy
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
  "body_end": "00841464",
  "body_span_bytes": 37,
  "body_start": "00841440",
  "callees": [
    "FUN_0083c780"
  ],
  "callers": [],
  "classification": "wrapper",
  "dispatch": null,
  "entry_point": "00841440",
  "evidence_note": "decompiler output = evidence, not truth; no MSVC RTTI in this binary",
  "ghidra_calling_convention": null,
  "ghidra_calling_convention_role": "cross-validation-only",
  "ghidra_calling_convention_signal": "no_information",
  "ghidra_has_calling_convention": false,
  "image_base": "0x400000",
  "locals": [],
  "locals_count": 0,
  "mode": "live",
  "name": "ArgScript::FormatParser::CreateDefinitionSafe",
  "namespace": "ArgScript",
  "namespace_source": "derived_from_symbol_name",
  "parameter_count": 3,
  "parameters": [
    {
      "name": "this",
      "ordinal": 0,
      "storage": "Stack[0x4]:4",
      "type": "FormatParser *"
    },
    {
      "name": "pName",
      "ordinal": 1,
      "storage": "Stack[0x8]:4",
      "type": "char *"
    },
    {
      "name": "argumentsLine",
      "ordinal": 2,
      "storage": "Stack[0xc]:4",
      "type": "Line *"
    }
  ],
  "program": "SporeApp.exe",
  "provenance": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
  "return_type": "bool",
  "return_type_resolved": true,
  "rva": "0x441440",
  "sdk_name": null,
  "sdk_type": null,
  "signature": "bool ArgScript::FormatParser::CreateDefinitionSafe(FormatParser * this, char * pName, Line * argumentsLine)",
  "size_bytes": 37,
  "status": "ok",
  "subsystem": null,
  "tool": "ghidra_function",
  "va": "0x00841440",
  "vtables": {
    "referenced_by_vtables": [
      "0x0141c0f4"
    ],
    "sdk_associations": [],
    "vtable_at": []
  },
  "xref_count": 1,
  "xrefs": [
    {
      "from": "0141c100"
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
  "global:PASS"
]
```

## reconstruction

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/ArgScript__FormatParser__CreateDefinitionSafe.c",
    "reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.cpp",
    "reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.hpp",
    "reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440_model_test.cpp",
    "reconstruction/staging/pkg-dfw-00841440/dfw_00841440.cpp",
    "reconstruction/staging/pkg-dfw-00841440/dfw_00841440_model_test.cpp",
    "reconstruction/staging/pkg-dfw-00841440/dfw_00841440_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-argscript-createdefsafe-00841440/00841440.json",
    "reconstruction/metadata/pkg-dfw-00841440/00841440.json"
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
  "FormatParser * per the SDK/Ghidra import label; the object is opaque here because no FormatParser vtable could be corroborated (see vtables)",
  "bool",
  "bool, declared. The target body never writes EAX; the value a caller observes is whatever 0x0083c780 leaves there, and that function's last write to EAX is MOV EAX,dword ptr [ESP + 0x4] at 0x0083c780, i.e. the first stack argument. So the observed return is the low byte of the pName word, consistent with the declared bool.",
  "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::CreateDefinitionSafePorts",
  "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::OpaqueFormatParser",
  "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::OpaqueLine",
  "openspore::reconstruction::pkg_argscript_createdefsafe_00841440::SharedTail0083c780"
]
```

## vtables

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  "vtable:0x0141c0f4"
]
```

## Conflicts

```json
[
  {
    "anchors": [
      "0x00845310",
      "0x00b1fdb0",
      "0x00845310",
      "0x00b1fdb0",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000",
      "0x00845310",
      "0x0067dd90",
      "0x00e66280",
      "0x00e66840"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:1",
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
      "0x005c7d00",
      "0x005c7d00",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x005c7d00",
      "0x005c7cb0",
      "0x005c7f10",
      "0x005c7f70",
      "0x00842d10",
      "0x00844180",
      "0x00843000",
      "0x00845310",
      "0x0067dd90"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:7",
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
      "0x00845310",
      "0x00845310",
      "0x00acd9a0",
      "0x00ace2c0",
      "0x00b25f40",
      "0x00ba0080",
      "0x00bf9820",
      "0x00e5c780",
      "0x00844f70",
      "0x00841440",
      "0x00846e60",
      "0x00841d40",
      "0x00845790",
      "0x00842d10",
      "0x00844180",
      "0x00843000"
    ],
    "conflict_id": "unresolved:knowledgegraph/research/state-machines/additional-domains.json:8",
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
