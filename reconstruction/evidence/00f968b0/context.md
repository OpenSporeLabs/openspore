# Reconstruction context 0x00f968b0

- Status: `partial`
- Content SHA-256: `416c8421cef908c5f17cb241ce7f4d37ef75f7f4df77f1761484b0e328594cdd`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00f968b0",
  "phase": "reconstruction",
  "target": "0x00f968b0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "Terrain::cTerrainSphere::GetSimDataRTT",
  "package": null,
  "subsystem": "Terrain",
  "va": "0x00f968b0"
}
```

## 03_current_status

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "blocked": false,
  "reconstructed": false,
  "runtime_gated": false,
  "runtime_validated": 0,
  "status": "queued"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "2b70b7ac4c38b2b21b53aed5fb111c8847a7cc34c64c5a7a356deb6a3bda0967",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00f968b0 failed: Decompilation did not complete. Reason: ",
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
  "convention": "__thiscall",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "hidden_this_type": "cTerrainSphere *",
  "ordinary_stack_argument_slots": 1,
  "ordinary_stack_arguments": 1,
  "receiver_register": "ECX",
  "ret_form": "RET 0x4 at 0x00f968f5 (success) and at 0x00f968fd (failure)",
  "return_observation": "EAX is 1 only when the +0x58 slot answered the address of receiver+0x04 for selector id 0x8 AND for selector id 0x7; EAX is 0 on the first mismatch and on the second mismatch",
  "return_register": "EAX",
  "return_type": "bool",
  "return_width_bytes": 4,
  "saved_registers": "EBX, ESI, EDI - pushed at 0x00f968b0, 0x00f968b1 and 0x00f968b4, popped at 0x00f968ed/0x00f968ee and 0x00f968f8/0x00f968f9, with EBX popped last at 0x00f968f4 and 0x00f968fc",
  "stack_arguments": 1,
  "stack_cleanup_bytes": 4,
  "stack_cleanup_owner": "callee",
  "termination": "returns to the caller from either RET 0x4; there is no tail call, no exception path and no loop"
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
  "globals": [],
  "types": [
    "OpaqueSelectorProvider",
    "OpaqueTerrainSphere",
    "bool",
    "cTerrainSphere *",
    "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueRttData",
    "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueSelectorProvider",
    "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueSelectorProviderVTable",
    "openspore::reconstruction::pkg_terrain_getsimdatartt_00f968b0::OpaqueTerrainSphere"
  ],
  "vtables": [
    "vtable:0x00000058",
    "vtable:0x00f968b0",
    "vtable:0x01490be8",
    "vtable:0x01490c7c"
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
    "id": "scc-0571",
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
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00f9b7f0",
    "score": 12,
    "symbol": "re_00f9b7f0",
    "va": "0x00f9b7f0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 6,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 6,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 6,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 6,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 6,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01490be8",
      "same_calling_convention"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 6,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c",
    "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.cpp",
    "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.hpp",
    "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-terrain-getsimdatartt-00f968b0/00f968b0.json"
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
    "No caller exists in the image, so the caller's expected argument, whether the id 0x8/0x7 answers are meant to alias one object, and whether the null-receiver path is reachable are all unobserved.",
    "Return type: the machine writes EAX with 1 (0x00f968ef) or 0 (0x00f968fa) and nothing else, so the source span declares bool; Ghidra's persisted signature and the SDK-derived label say 'Raster *'. A 0/1-valued pointer return cannot be excluded from this body alone. If the integrator prefers the pointer reading, the span's return type and this sidecar's observed_original_abi.return_type must change together.",
    "The briefing's single analogue (PKG-16-SPOREPEDIA-ONLINE, 0x00641770, matched on shared_vtable vtable:0x01490be8) is not usable prior art: 0x00641770 sits at slot index 2 of that table and is a Sporepedia asset-data predicate, so the match basis is a slot-index coincidence, not a shared class.",
    "The declared type of the second parameter is unknown. Ghidra calls it 'int quadIndex', but the body dereferences it twice as an object pointer and passes it as the callee's this, so the label is wrong; the owning class of vtable slot +0x58 is unidentified (the dispatch is register-indirect, so no xref names the implementation).",
    "The extents are not observable here. Only addresses of the anchored sub-object are taken, so neither its size nor the receiver's size follows from this target; the receiver's 0x100 modelled extent and the sibling pointers at +0x30/+0x74/+0xb8/+0xfc are borrowed from the sibling virtual
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-terrain-getsimdatartt-00f968b0/00f968b0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/Terrain__cTerrainSphere__GetSimDataRTT.c",
      "source_class": "committed_artifact"
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
      "ref": "reconstruction/metadata/pkg-terrain-getsimdatartt-00f968b0/00f968b0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-terrain-getsimdatartt-00f968b0/terrain_get_sim_data_rtt_00f968b0.hpp",
      "source_class":
[TRUNCATED]
```
