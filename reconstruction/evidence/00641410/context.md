# Reconstruction context 0x00641410

- Status: `partial`
- Content SHA-256: `e5f5d721380fc46927c83d5498925c3bf4b8a9b9c6238511f9e6867305dcf6ee`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641410",
  "phase": "reconstruction",
  "target": "0x00641410"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00641410",
  "package": "pkg-swarm-w1-00641410",
  "subsystem": "Sporepedia",
  "va": "0x00641410"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": true,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "b15caeba844c0e73fcc38be6714403a48f1076836326fac44891bce6b187f188",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641410 failed: Decompilation did not complete. Reason: ",
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
  "calling_convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 0,
  "receiver_register": "ECX",
  "ret_form": "RET (no immediate, both sites)",
  "return_register": "EAX",
  "return_type": "std::uint8_t",
  "saved_registers": [
    "ESI"
  ],
  "stack_cleanup_bytes": 0,
  "stack_cleanup_owner": "caller",
  "termination": "RET"
}
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [],
  "external_callees": []
}
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:none. No instruction in the body names a data-segment address."
  ],
  "types": [
    "PKG_SWARM_W1_00641410_THISCALL",
    "openspore::reconstruction::pkg_swarm_w1_00641410::AssetData",
    "openspore::reconstruction::pkg_swarm_w1_00641410::SlotFn",
    "openspore::reconstruction::pkg_swarm_w1_00641410::Vtable",
    "openspore::reconstruction::pkg_swarm_w1_00641410::byte_at",
    "openspore::reconstruction::pkg_swarm_w1_00641410::dispatch_target_at",
    "openspore::reconstruction::pkg_swarm_w1_00641410::kReceiverDispatchWordDisplacement",
    "openspore::reconstruction::pkg_swarm_w1_00641410::kReceiverResultByteDisplacement",
    "openspore::reconstruction::pkg_swarm_w1_00641410::kSlotDispatchedByteDisplacement",
    "openspore::reconstruction::pkg_swarm_w1_00641410::model_returned_eax",
    "openspore::reconstruction::pkg_swarm_w1_00641410::slot_at",
    "openspore::reconstruction::pkg_swarm_w1_00641410::slot_word_at",
    "openspore::reconstruction::pkg_swarm_w1_00641410::store_byte_at",
    "openspore::reconstruction::pkg_swarm_w1_00641410::store_pointer_at",
    "openspore::reconstruction::pkg_swarm_w1_00641410::store_slot_at",
    "openspore::reconstruction::pkg_swarm_w1_00641410::store_word_at"
  ],
  "vtables": [
    "vtable:0x013ff648",
    "vtable:0x01462764",
    "vtable:0x0147c9e8",
    "vtable:0x0147ca30",
    "vtable:0x0147caf8",
    "vtable:0x0147cbbc",
    "vtable:0x014893b0"
  ]
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
      "A trace records the dispatch word at each of 0x00641413 / 0x00641421 / 0x00641431 / 0x00641441, the slot-9 target loaded at each of the four following instructions, and the full 32-bit EAX each callee returns.",
      "An object whose dispatch word points at one of the six tables listed in mechanics.vtable_installations is constructed and FUN_00641410 is entered.",
      "The trace confirms or refutes that the four literals ever occur in practice, and if so with which receiver class -- this is the only way to name them.",
      "The trace shows a second call site whose use of the result (mask, compare, forward) would settle the bool-versus-raw-byte question in the unresolved list.",
      "The trace shows whether the dispatch word ever differs between two consecutive reads; if it never does, the three re-reads are confirmed redundant on every observed path and this package's D3 case remains a synthetic refutation only.",
      "not_required_for_the_structural_claims_but_unavailable"
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
  "callers": [],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0152",
    "size": 1
  },
  "vtable_reference_count": 0
}
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 12,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 12,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641780",
    "score": 12,
    "symbol": "re_00641780",
    "va": "0x00641780"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006417d0",
    "score": 12,
    "symbol": "re_006417d0",
    "va": "0x006417d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01462764,vtable:0x0147ca30",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-slot-release",
    "score": 12,
    "symbol": "sporepedia_dispatch_owned_slot_FUN_00641e10",
    "va": "0x00641e10"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641fa0",
    "score": 12,
    "symbol": "sporepedia_predicate_00641fa0",
    
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00641410/00641410.json"
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
    "A trace records the dispatch word at each of 0x00641413 / 0x00641421 / 0x00641431 / 0x00641441, the slot-9 target loaded at each of the four following instructions, and the full 32-bit EAX each callee returns.",
    "An object whose dispatch word points at one of the six tables listed in mechanics.vtable_installations is constructed and FUN_00641410 is entered.",
    "Does Ghidra have an SDK name for this member? It is FUN_00641410, it carries no namespace, and the live SDK-derived cSPAssetDataOTDB set that sibling packages enumerate does not reach this VA. A name from the ModAPI headers or a vtable-detector pass would settle it; neither was available to this worker.",
    "Does any real callee in this image ever change the receiver's dispatch word? The four independent `MOV EAX,[ESI]` prove the model must re-read it; whether the re-read ever matters at run time needs a trace. The model test proves only that the model is written to re-read it, which is a synthetic refutation.",
    "Is the canonical return-type token a C type or a register-class label? The machine-derived record's own vocabulary for this target is 'integral_in_EAX' (reconstruction/evidence/00641410: both the abi and abi_derived layers carry abi.return_semantics = 'integral_in_EAX', and the nested `return` sub-record carries register EAX, register_class 'integral', type null). That token is a REGISTER-CLASS CLASSIFICATION -- it says the value travels in EAX and is integral -- and it is NOT a C or C++ type name, so it can never string-agree with a C++ decl
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00641410/00641410.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00641410/00641410.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/kno
[TRUNCATED]
```
