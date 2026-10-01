# Evidence 0x00e7b630

- Evidence state: `PERSISTED`
- Live requested: `False`
- Content SHA-256: `26e68bd248a3fbfc4bc8cc34692676f79f95c3459dee7009f2ef77a83f20fefd`

## abi

- Availability: `available`
- Evidence state: `PERSISTED`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": null,
  "hidden_this": false,
  "hidden_this_register": null,
  "ordinary_stack_argument_slots": 1,
  "receiver": "NONE. Undetermined with reason ecx_read_without_deref. ECX is read at 0x00e7b68b as a LOAD out of memory (MOV ECX,[EAX+0x1b0]) and immediately PUSHed at 0x00e7b691 as the first of 0x00e6d200's four ordinary stack arguments. It is read and written seventeen times across the body and dereferenced nowhere. The body works through EAX, EBX, EDX, EDI, EBP and ESI.",
  "ret_form": "RET",
  "return_register": "ST0",
  "return_semantics": "float_or_x87_in_ST0",
  "return_type": "void",
  "saved_registers": [
    "EBP",
    "EBX",
    "EDI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## abi_derived

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

## callees_dependencies

- Availability: `available`
- Evidence state: `DERIVED`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "name": "embedded_object_first_word_init_00743b50",
    "reconstructed": true,
    "va": "0x00743b50"
  },
  {
    "name": "Simulator::Cell::PlayAnimation",
    "reconstructed": false,
    "va": "0x00e6d200"
  },
  {
    "name": "FUN_00e780a0",
    "reconstructed": true,
    "va": "0x00e780a0"
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
    "va": "0x00e7e7f0"
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

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

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
  "original_bytes": 11453,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"calling_convention\": null,\n    \"hidden_this\": false,\n    \"hidden_this_register\": null,\n    \"ordinary_stack_argument_slots\": 1,\n    \"receiver\": \"NONE. Undetermined with reason ecx_read_without_deref. ECX is read at 0x00e7b68b as a LOAD out of memory (MOV ECX,[EAX+0x1b0]) and immediately PUSHed at 0x00e7b691 as the first of 0x00e6d200's four ordinary stack arguments. It is read and written seventeen times across the body and dereferenced nowhere. The body works through EAX, EBX, EDX, EDI, EBP and ESI.\",\n    \"ret_form\": \"RET\",\n    \"return_register\": \"ST0\",\n    \"return_semantics\": \"float_or_x87_in_ST0\",\n    \"return_type\": \"void\",\n    \"saved_registers\": [\n      \"EBP\",\n      \"EBX\",\n      \"EDI\"\n    ],\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"analogues\": [\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-11-H4-HELPER-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"address_window_offset_005c65e0\",\n      \"va\": \"0x005c65e0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"dispatch_key_00628450\",\n      \"va\": \"0x00628450\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"cycle_key_006286a0\",\n      \"va\": \"0x006286a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-SIMULATOR-SAFE-WAVE11\",\n      \"score\": 6,\n      \"symbol\": \"release_child_0062c910\",\n      \"va\": \"0x0062c910\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d2a0\",\n      \"va\": \"0x00b3d2a0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"FUN_00b3d300\",\n      \"va\": \"0x00b3d300\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-01-SHARED-STATE-ROOTS\",\n      \"score\": 6,\n      \"symbol\": \"Simulator_GetUIMissionLogManager\",\n      \"va\": \"0x00b3d4f0\"\n    },\n    {\n      \"match_basis\": [\n        \"same_subsystem\"\n      ],\n      \"package\": \"PKG-13-E4-EMPIRE-WAVE3\",\n      \"score\": 6,\n      \"symbol\": \"EmpirePoliticalColor_00c32cd0\",\n      \"va\": \"0x00c32cd0\"\n    }\n  ],\n  \"audit_evidence_boundary\": null,\n  \"audit_findings\": [],\n  \"audit_status\": null,\n  \"blocked\": false,\n  \"blockers\": [],\n  \"body_status\": null,\n  \"class_type\": null,\n  \"cluster\": \"unknown-fun-mass\",\n  \"confidence\": null,\n  \"dependencies\": {\n    \"callees\": [\n      {\n        \"name\": \"embedded_object_first_word_init_00743b50\",\n        \"reconstructed\": true,\n        \"va\": \"0x00743b50\"\n      },\n      {\n        \"name\": \"Simulator::Cell::PlayAnimation\",\n        \"reconstructed\": false,\n        \"va\": \"0x00e6d200\"\n      },\n      {\n        \"name\": \"FUN_00e780a0\",\n        \"reconstructed\": true,\n        \"va\": \"0x00e780a0\"\n      }\n    ],\n    \"callees_truncated\": false,\n    \"callers\": [\n      {\n        \"name\": null,\n        \"reconstructed\": false,\n        \"va\": \"0x00e7e7f0\"\n      }\n    ],\n    \"callers_truncated\": false,\n    \"data_reference_count\": 0,\n    \"edges\": [\n      {\n        \"callsite\": \"0x00e7e8f1\",\n        \"direction\": \"in\",\n        \"other\": \"0x00e7e7f0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b761\",\n        \"direction\": \"out\",\n        \"other\": \"0x00743b50\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b6ad\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72160\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b686\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b6bc\",\n        \"direction\": \"out\",\n        \"other\": \"0x00b72210\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b772\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e4cc40\",\n        \"reference_type\": \"thunk\"\n      },\n      {\n        \"callsite\": \"0x00e7b79d\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e59a70\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b77e\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e5d7b0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b696\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e6d200\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b793\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e780a0\",\n        \"reference_type\": \"direct-call\"\n      },\n      {\n        \"callsite\": \"0x00e7b7a6\",\n        \"direction\": \"out\",\n        \"other\": \"0x00e82130\",\n        \"reference_type\": \"direct-call\"\n      }\n    ],\n    \"edges_truncated\": false,\n    \"external_callees\": [],\n    \"fan_in\": 1,\n    \"fan_out\": 3,\n    \"manifest_callees\": [],\n    \"manifest_callers\": [],\n    \"nearby_reconstructed\": [\n      \"0x00743b50\",\n      \"0x00e780a0\"\n    ],\n    \"scc\": {\n      \"id\": \"scc-0552\",\n      \"size\": 1\n    },\n  
[TRUNCATED]
```

## ghidra_function

- Availability: `unavailable`
- Evidence state: `MISSING`
- Provenance: ``

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
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_entry.cpp",
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_model_test.cpp",
    "reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-w2-00e7b6c0/00e7b6c0.json"
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
  "openspore::reconstruction::pkg_w2_00e7b6c0::CalleeTerminator00e7b6c0",
  "openspore::reconstruction::pkg_w2_00e7b6c0::RecordValueSource00e7b6c0",
  "openspore::reconstruction::pkg_w2_00e7b6c0::RecordWrite00e7b6c0",
  "std::size_t",
  "std::uint32_t",
  "std::uint8_t",
  "void",
  "void, and that is a reading of the listing rather than a recovered fact. No instruction places a value in a return register at the single return site. EAX's last write is 0x00e7b79b, whose only consumer is the call that follows it; XMM0's last write is the XORPS at 0x00e7b6c5, consumed by the two MOVSS at 0x00e7b6ea and 0x00e7b6ef. The machine record's return_register ST0 with return_semantics float_or_x87_in_ST0 is at confidence APPROXIMATION under rule RT1, whose stated basis is that an x87 or SSE instruction appears in the body; it is carried in the header as data and is NOT adopted. The x87 balance is a fact of the listing and it points the same way: the body pushes twice and pops three times, so whatever ST0 held on entry is consumed and nothing is left."
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
