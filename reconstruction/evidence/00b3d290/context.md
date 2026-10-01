# Reconstruction context 0x00b3d290

- Status: `partial`
- Content SHA-256: `d6db0acb8c0c909ea0ea66f3984d1595372aafc4c65ce7fd26134247726c0a33`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d290",
  "phase": "reconstruction",
  "target": "0x00b3d290"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": null,
  "package": null,
  "subsystem": null,
  "va": "0x00b3d290"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "unresolved"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "a5662fa2b6b17ac1ea7fe18893d0c1ab6e2ee11dcde5114a393c27047c9dbd07",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d290 failed: Decompilation did not complete. Reason: ",
      "mode": "LIVE",
      "status": "unavailable"
    }
  ],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `missing`
- Provenance: ``

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "calling_convention": "cdecl-compatible static accessor; convention is not discriminable and is not asserted",
  "hidden_receiver": "absent",
  "hidden_this_register": "ECX is never read; the body contains no register operand other than EAX in the MOV and the implicit ESP in the RET",
  "ordinary_stack_argument_slots": 0,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x00b3d290: MOV EAX,[0x0167EAD4] is the only write to EAX, so all 32 bits are defined and no truncation or zero-extension occurs.",
  "return_register": "EAX",
  "return_semantics": "the raw 32-bit contents of the .bss dword at 0x0167EAD4, verbatim",
  "return_type": "std::uint32_t",
  "return_width_bytes": 4,
  "saved_registers": [],
  "stack_arguments": [],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET at 0x00b3d295"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5490"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac6960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ce70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b8c330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9caa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be7bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf5cb0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ac5333",
      "direction": "in",
      "other": "0x00ac5330",
      "reference_type": "direct-call"
    },

[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint32_t"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [
      "A runtime differential test would have to establish (a) that 0x0167EAD4 is non-zero once the owning subsystem is up, and (b) the concrete type of the pointee, which is the withheld claim.",
      "Because the slot has no static writer, static analysis alone cannot enumerate the set of objects that can land there; a runtime write watchpoint on 0x0167EAD4 is the only way to close this.",
      "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static."
    ],
    "validated": 0
  },
  "semantic": {}
}
```

## 10_dependencies

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callees_truncated": false,
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5430"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac5490"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ac6960"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32aa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32c60"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b32e80"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33130"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33350"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b33540"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b5ce70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b8c330"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b9caa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ba1590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00be7bf0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00bf5cb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00c1c310"
    },
    {
      "name": null,
      "reconst
[TRUNCATED]
```

## 11_related_functions

- State: `missing`
- Provenance: `reconstruction/knowledge/index.json`

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/wave13-w1-core-b06/b3d290_global_slot_accessor.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
    "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/wave13-w1-core-b06/00b3d290.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

## 14_conflicts_questions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [],
  "unresolved_questions": [
    "A runtime differential test would have to establish (a) that 0x0167EAD4 is non-zero once the owning subsystem is up, and (b) the concrete type of the pointee, which is the withheld claim.",
    "Because the slot has no static writer, static analysis alone cannot enumerate the set of objects that can land there; a runtime write watchpoint on 0x0167EAD4 is the only way to close this.",
    "CONFLICT, recorded and NOT adopted: Spore-ModAPI 'Spore ModAPI/Spore/Simulator/SubSystem/GamePersistenceManager.h:65' declares `DeclareAddress(Get);  // 0xB3D2A0 0xB3D440`, and 0x00b3d290 falls inside that range. The attribution is not adopted because 0x00b3d2a0, the range's stated entry point, demonstrably returns an object read at +0x184 (ordered map header, 0x00bb99fc) and at +0x1F4 (lazily resolved pointer slot, 0x00c4b221), while the same header asserts ASSERT_SIZE(cGamePersistenceManager, 0x4C). The SDK's address range therefore covers a cluster of unrelated Simulator singleton accessors, and only 0x00b3d2a0 is claimed by name. Adopting cGamePersistenceManager for 0x00b3d290 would contradict an observed field offset.",
    "Is 0x0167EAD4 the same type as the neighbouring slot 0x0167EAD8 (read by 0x00b3d260, whose pointee is dereferenced through vtable slot +0x30 at 0x00b32ad0)? The two accessors are adjacent but nothing observed relates the two pointees.",
    "No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.",
    "T
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/wave13-w1-core-b06/00b3d290.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/b3d290_global_slot_accessor.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/wave13-w1-core-b06/sim_core_b06_ports_model.cpp', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
    },
    {
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/abi_infer.py",
      "source_class": "derived"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "ghidra"
    },
    {
      "mode": "live",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "ghidra"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/research/source-reconstruction-manifest.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "knowledgegraph/triage/queue-f0e310e0-v6.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/metadata/wave13-w1-core-b06/00b3d290.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/b3d290_global_slot_accessor.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/wave13-w1-core-b06/sim_core_b06_opaque.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstru
[TRUNCATED]
```
