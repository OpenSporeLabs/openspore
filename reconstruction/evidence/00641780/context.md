# Reconstruction context 0x00641780

- Status: `partial`
- Content SHA-256: `e642387c1e334b5c563359d5d2133633c984d73a644913ca7464d7325152002f`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00641780",
  "phase": "reconstruction",
  "target": "0x00641780"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00641780",
  "package": "pkg-swarm-w1-00641780",
  "subsystem": "Sporepedia",
  "va": "0x00641780"
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
  "content_sha256": "a4f2c67221b88fa42108d63a543eb72bb18a4e8e3dab78a9d7230cda2e57109a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00641780 failed: Decompilation did not complete. Reason: ",
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
  "return_note": "The DECLARED type, spelled exactly as the target span declares it. The span's signature is `extern \"C\" Word PKG_SWARM_W1_00641780_THISCALL re_00641780(AssetData* receiver)`, so the type validate._return_type() reads out of it is `Word` -- the alias this package's header declares for std::uint32_t -- and that is what this field now says. The annotation that used to be packed into the same string is preserved here: the value is a full 32-bit word that is exactly 1 or exactly 0. 0x0064179b is `MOV EAX,0x1` (bytes B8 01 00 00 00) and 0x006417a2 is `XOR EAX,EAX`, so no bit of either callee's res...",
  "return_register": "EAX",
  "return_semantics": "integral_in_EAX",
  "return_type": "Word",
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
    "global:PASS",
    "global:none. No instruction in the body names a data-segment address, and the model names none."
  ],
  "types": [
    "PKG_SWARM_W1_00641780_THISCALL",
    "Word",
    "openspore::reconstruction::pkg_swarm_w1_00641780::AssetData",
    "openspore::reconstruction::pkg_swarm_w1_00641780::SlotFn"
  ],
  "vtables": [
    "vtable:0x00641810",
    "vtable:0x00642210",
    "vtable:0x013ff648",
    "vtable:0x013ff674",
    "vtable:0x01462764",
    "vtable:0x0147c9e8",
    "vtable:0x0147cbbc",
    "vtable:0x01489090",
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
      "A trace records the dispatch word's value at 0x00641783 and again at 0x0064178e, the two target addresses loaded at 0x00641785 and 0x00641790, and the full 32-bit EAX each callee returns.",
      "An object whose dispatch word points at one of the six tables listed above is constructed and FUN_00641780 is entered.",
      "The trace is repeated with the +0x1c sub-object null and non-null, since both candidate accessors 0x00641810 and 0x00641820 return zero when it is null and tail-transfer when it is not.",
      "The trace shows whether the dispatch word ever differs between the two reads; if it never does, the second load at 0x0064178e is confirmed redundant on every observed path and this package's case 7 remains a synthetic refutation only.",
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
    "id": "scc-0156",
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
      "shared_types:Word",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 15,
    "symbol": "re_006413d0",
    "va": "0x006413d0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00642700",
    "score": 15,
    "symbol": "sporepedia_append_five_lookups_00642700",
    "va": "0x00642700"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_types:Word",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00a649a0",
    "score": 15,
    "symbol": "re_00a649a0",
    "va": "0x00a649a0"
  },
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
    "package": "pkg-swarm-w1-00641410",
    "score": 12,
    "symbol": "re_00641410",
    "va": "0x00641410"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x013ff648,vtable:0x01462764",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-006417d0
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780_model_test.cpp",
    "reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780_types.hpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-swarm-w1-00641780/00641780.json"
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
    "A trace records the dispatch word's value at 0x00641783 and again at 0x0064178e, the two target addresses loaded at 0x00641785 and 0x00641790, and the full 32-bit EAX each callee returns.",
    "An object whose dispatch word points at one of the six tables listed above is constructed and FUN_00641780 is entered.",
    "Does Ghidra have an SDK name for this member that the live cSPAssetDataOTDB this_type set does not list? The set has ten members and this VA is not among them, so the export name stays the canonical VA-embedding form. A name from the ModAPI headers or a vtable-detector pass would settle it; neither was available to this worker.",
    "Does any real callee in this image ever change the receiver's dispatch word? 0x0064178e proves the model must re-read it; whether the re-read ever matters at run time needs a trace. Static analysis of the candidate callees found no store to a dispatch word, but that is an absence of evidence.",
    "The C type of the value EAX carries, which no machine record for this VA states and which nothing in this image can settle. The reconstruction declares `Word` (this package's alias for std::uint32_t) because the body itself produces a full 32-bit word and nothing narrows it: 0x0064179b is `MOV EAX,0x1` (bytes B8 01 00 00 00) and 0x006417a2 is `XOR EAX,EAX`, and the two callees' results are consumed whole by `TEST EAX,EAX` and then discarded. The machine side of the record is a register-CLASS classification rather than a type: abi_derived.value.return is {register EAX, register_cla
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-swarm-w1-00641780/00641780.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780_model_test.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780_types.hpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg-swarm-w1-00641780/00641780.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780_model_test.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780_types.hpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/kno
[TRUNCATED]
```
