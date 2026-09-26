# Reconstruction context 0x00b1fbf0

- Status: `partial`
- Content SHA-256: `b99e84579e52743ca98270ef093663900ef456d012b0c5daf44759fd6fb08ee9`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b1fbf0",
  "phase": "reconstruction",
  "target": "0x00b1fbf0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00b1fbf0",
  "package": null,
  "subsystem": "Editor",
  "va": "0x00b1fbf0"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "78f01b2af698ca5c3c324c6b26960b2b29ce9eff248df6083e013f9520a2609b",
  "live_attempts": [],
  "live_requested": false,
  "overall": "PERSISTED"
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
  "calling_convention": null,
  "hidden_receiver": "unread",
  "hidden_this_register": "ECX is never read; 0x00b1fbf0 has no instruction that mentions any register other than AL",
  "ordinary_stack_argument_slots": 0,
  "receiver": false,
  "ret_form": "RET",
  "return_observation": "0x00b1fbf0: MOV AL,0x1 writes only the low byte of EAX, so bits 8..31 of EAX are undefined on exit rather than zero. Every consumer inspected tests the AL byte, never the full dword.",
  "return_register": "EAX",
  "return_semantics": "std::uint8_t",
  "return_type": "std::uint8_t",
  "return_width_bytes": 1,
  "saved_registers": [],
  "stack_arguments": [],
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
  "callers": [
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007f53d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0082c210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096a670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096b3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0097c6d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098cc70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098f3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00993fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a43050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a51f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d73ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e0eab0"
    },
    {
      "name": "cell_mode_strategy_on_mouse_wheel_00e7d660",
      "reconstructed": true,
      "va": "0x00e7d660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee8860"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x007f53fe",
      "direction": "in",
      "other": "0x007f53d0",
      
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "std::uint8_t"
  ],
  "vtables": [
    "vtable:0x013f57f8",
    "vtable:0x013f625c",
    "vtable:0x013f85a4",
    "vtable:0x013fc06c",
    "vtable:0x013fc1a4",
    "vtable:0x013fc474",
    "vtable:0x013fc6cc",
    "vtable:0x013fc6f4",
    "vtable:0x013fc744",
    "vtable:0x013fc854",
    "vtable:0x013fcc08",
    "vtable:0x013fcc48"
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
      "No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.",
      "The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named."
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
      "va": "0x007f53d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0082c210"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096a670"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0096b3a0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0097c6d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098cc70"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0098f3d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00993fa0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a43050"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00a51f40"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ccefb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00d73ca0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e0eab0"
    },
    {
      "name": "cell_mode_strategy_on_mouse_wheel_00e7d660",
      "reconstructed": true,
      "va": "0x00e7d660"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00e81120"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ee8860"
    }
  ],
  "callers_truncated": false,
  "data_reference_count": 0,
  "edges": [
    {
      "
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "shared_vtable:vtable:0x01485550",
      "direct_xref_neighbor"
    ],
    "package": "PKG-GAME-INPUT-WAVE8",
    "score": 7,
    "symbol": "cell_mode_strategy_on_mouse_wheel_00e7d660",
    "va": "0x00e7d660"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013fc06c,vtable:0x01409bec"
    ],
    "package": "PKG-WAVE6-CONTAINERS-MEMORY",
    "score": 4,
    "symbol": "wave6_reference_00432a50",
    "va": "0x00432a50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_005737d0",
    "va": "0x005737d0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x014186c4"
    ],
    "package": "PKG-UTFWIN-CORE-WAVE6",
    "score": 4,
    "symbol": "re_00575ea0",
    "va": "0x00575ea0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00585890",
    "va": "0x00585890"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00585d10",
    "va": "0x00585d10"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_00588570",
    "va": "0x00588570"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x013f57f8"
    ],
    "package": "PKG-EDITOR-INPUT-WAVE6",
    "score": 4,
    "symbol": "editor_input_0058a
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp",
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.hpp",
    "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-shared-default-true-wave12/00b1fbf0.json"
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
    "Is the address a compiler-folded COMDAT shared by many unrelated 'return true' defaults, or a single default deliberately emitted once? Both fit every observation.",
    "Is the always-true body a shipped default, a build-configuration stub, or a patch target at runtime? No differential trace has been captured for this function, so runtime patching cannot be excluded.",
    "No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.",
    "The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named.",
    "The 356 and 20 vtable-reference counts are raw pointer-scan totals, not proven distinct vtables. The true count is unmeasured.",
    "What is the correct port spelling for a slot that is dispatched with ECX populated but implemented as a bare RET? The reconstruction keeps an unread receiver parameter, which is a modelling choice rather than an observed fact.",
    "What predicate is this? The body is a constant yes, but nothing in the observed evidence names the question it answers.",
    "Which class or classes own the slots that point here? Three distinct slot offsets across three distinct tables are recorded above and they cannot all describe one method.",
    "Why does caller 0x00a43050 and caller 0x0082c210 call the function and discard the answer? A constant with no side effects make
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'ref': 'ephemeral reconstruction_knowledge.build_index', 'mode': 'derived', 'source_class': 'generated_index'}, {'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/metadata/pkg-shared-default-true-wave12/00b1fbf0.json', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.hpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}, {'ref': 'reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true_model_test.cpp', 'mode': 'persisted', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "ephemeral reconstruction_knowledge.build_index",
      "source_class": "generated_index"
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
      "ref": "reconstruction/metadata/pkg-shared-default-true-wave12/00b1fbf0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true_model_test.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json"
  ],
  "required_categories": [
    "ABI",
    "CALLS",
    "GLOBALS",
    "FIELDS/OFFSETS",
    "CONSTANTS",
    "CONTROL FLOW",
    "VIRTUAL DISPATCH",
    "RETURN SEMANTICS",
    "EVIDENCE COVERAGE"
  ]
}
```
