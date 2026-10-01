# Reconstruction context 0x00c2e4e0

- Status: `partial`
- Content SHA-256: `874bf53c929b39c3f40f091e152756dbde20108cecbd030a7a816b4bc2515e60`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00c2e4e0",
  "phase": "reconstruction",
  "target": "0x00c2e4e0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00c2e4e0",
  "package": "pkg-sporepedia-nop-slot",
  "subsystem": "Sporepedia",
  "va": "0x00c2e4e0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": true,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "reconstructed"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "d955de24af726988f5e68d2e94d0642a50014dfa4e4eadd5f1e4a36a5c39fb53",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00c2e4e0 failed: Decompilation did not complete. Reason: ",
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
  "ret_form": "RET",
  "return_register": "EAX",
  "return_semantics": "VOID_PROVEN: the complete 1-instruction listing writes EAX on no path before the single reachable return, and the body makes no call that could clobber it",
  "return_type": "void",
  "saved_registers": [],
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
      "va": "0x00496d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b4470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b4930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b76c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577c40"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00599040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0060ceb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006275d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007e6470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0082f020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008639f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00987900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00999110"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x004973d6",
      "direction": "in",
      "other": "0x00496d30",
     
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [
    "global:none: the complete 1-instruction listing names no data-segment address"
  ],
  "types": [
    "void"
  ],
  "vtables": [
    "vtable:0x013f69b4",
    "vtable:0x013f7028",
    "vtable:0x013f70d4",
    "vtable:0x013f718c",
    "vtable:0x013f72ac",
    "vtable:0x013f74cc",
    "vtable:0x013f756c",
    "vtable:0x013f76c4",
    "vtable:0x013f7820",
    "vtable:0x013f78c0",
    "vtable:0x013f7cc0",
    "vtable:0x013f7de0"
  ]
}
```

## 09_state_event_relationships

- State: `missing`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "runtime": {
    "blocking_reason": null,
    "gates": [],
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
      "va": "0x00496d30"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b4470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b4930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x004b76c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00577c40"
    },
    {
      "name": "editor_input_00588570",
      "reconstructed": true,
      "va": "0x00588570"
    },
    {
      "name": "Editors::cEditor::Update",
      "reconstructed": false,
      "va": "0x0058be50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00599040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0059c640"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0060ceb0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x006275d0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x007e6470"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0082f020"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x008639f0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00987900"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00999110"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x0099ed90"
    },

[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013f7cc0,vtable:0x013f7de0",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00641410",
    "score": 12,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x0147c9e8",
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
      "shared_vtable:vtable:0x013ff648,vtable:0x0147ca30",
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
      "shared_vtable:vtable:0x0147ca30,vtable:0x0147ca70",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-slot-release",
    "score": 12,
    "symbol": "sporepedia_dispatch_owned_slot_FUN_00641e10",
    "va": "0x00641e10"
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [],
  "handoffs": [],
  "metadata": []
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
    "A pure read of the receiver with no effect is unobservable for a leaf body, in the original as much as in the model, so no test asserts the absence of one; the listing shows no read and the source declares none, which is the whole of the evidence.",
    "Is the receiver ever observed non-null at a call site? The body never reads it, so its value is unobservable from this function; the 254 incoming call sites are unreconstructed and none was traced.",
    "What does this slot override, if anything? A bare RET is the shape of an empty virtual function -- a default implementation derived classes inherit -- but no RTTI exists in this binary and the vtable pass never ran, so the base/override relationship is not established.",
    "Which class is this a virtual member of? The V1-VFT membership is established over 479 vptr-backed tables because identical-code folding collapses every no-op virtual member in this image onto 0x00c2e4e0, so no single class can be named and none is claimed.",
    "Why does the slot exist? An empty virtual member is the usual shape of a hook the game's classes override elsewhere, but which classes override it, and whether any do, is not established by any record for this target."
  ]
}
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}`

```json
{
  "provenance": [
    {
      "mode": "derived",
      "ref": "GhidraMCP /disassemble_function",
      "source_class": "derived"
    },
    {
      "mode": "derived",
      "ref": "GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089",
      "source_class": "derived"
    },
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
      "mode": "derived",
      "ref": "tools/reconstruction_tooling/vftables.py@25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e",
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
    "RETURN 
[TRUNCATED]
```
