# Reconstruction context 0x00b3d2a0

- Status: `partial`
- Content SHA-256: `07625e2b33bc9f21858fdc063f0e3048625886504c13ee83d0b96e5811132488`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00b3d2a0",
  "phase": "reconstruction",
  "target": "0x00b3d2a0"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": "OpaqueStarManager",
  "name": "FUN_00b3d2a0",
  "package": "PKG-01-SHARED-STATE-ROOTS",
  "subsystem": "Simulator",
  "va": "0x00b3d2a0"
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
  "content_sha256": "9b888700649ab2c6fe07466d050f51d84cf64ca3b4a09d526a2b9366d3cca32a",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00b3d2a0 failed: Decompilation did not complete. Reason: ",
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
- Provenance: `reconstruction/knowledge/index.json, GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089, GhidraMCP /disassemble_function`

```json
{
  "original_bytes": 5056,
  "preview": "{\n  \"abi\": {\n    \"architecture\": \"x86-32\",\n    \"receiver\": false,\n    \"ret_form\": \"RET\",\n    \"return_register\": \"EAX\",\n    \"return_semantics\": \"pointer_like_in_EAX\",\n    \"stack_cleanup_bytes\": 0,\n    \"stack_cleanup_owner\": \"caller\",\n    \"termination\": \"RET\"\n  },\n  \"abstained_because\": [\n    \"no_discriminator: no stack-argument read and no positive receiver evidence\"\n  ],\n  \"cleanup\": {\n    \"bytes\": 0,\n    \"confidence\": \"INFERRED\",\n    \"corroboration\": \"not_available\",\n    \"evidence\": \"ret with no immediate, no stack reads\",\n    \"side\": \"caller\"\n  },\n  \"completeness\": \"PARTIAL\",\n  \"conflicts\": [],\n  \"content_sha256\": \"cc6293a288da6da5da475c8010960a1c472a9b5a3df1ea00dadad13c444cbd4d\",\n  \"conventions\": {\n    \"ambiguities\": [],\n    \"calling_convention\": null,\n    \"candidate_conventions\": [\n      \"__cdecl\",\n      \"__stdcall\",\n      \"__thiscall\",\n      \"__fastcall\"\n    ],\n    \"confidence\": \"UNKNOWN\",\n    \"corroboration\": \"not_available\"\n  },\n  \"cross_validation\": {\n    \"agreement\": false,\n    \"ghidra\": \"no_information\",\n    \"ghidra_calling_convention\": null,\n    \"ghidra_parameter_count\": 0,\n    \"persisted\": \"no_information\",\n    \"persisted_calling_convention\": null\n  },\n  \"dispatch\": {\n    \"call_offsets\": [],\n    \"indirect_calls\": 0,\n    \"vtable_shaped_loads\": 0\n  },\n  \"inferences\": [\n    {\n      \"based_on\": [\n        \"obs-0002\"\n      ],\n      \"claim\": \"the caller 
[TRUNCATED]
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
      "va": "0x00ae9040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aecf90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b20790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b279e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b28070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b28850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b28da0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    }
  ],
  "edge_rows": [
    {
      "callsite": "0x00ae9046",
      "direction": "in",
      "other": "0x00ae9040",
[TRUNCATED]
```

## 08_types_fields_globals

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "globals": [],
  "types": [
    "32-bit pointer slot",
    "OpaqueStarManager"
  ],
  "vtables": []
}
```

## 09_state_event_relationships

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json, reconstruction/knowledge/index.json`

```json
{
  "original_bytes": 7289,
  "preview": "{\n  \"runtime\": {\n    \"blocking_reason\": null,\n    \"gates\": [\n      \"observe_global_slot_0167eae4\"\n    ],\n    \"validated\": 0\n  },\n  \"semantic\": {\n    \"category\": null,\n    \"classification\": \"NEEDS_RUNTIME\",\n    \"confidence\": {\n      \"mechanics\": 1.0\n    },\n    \"contradictions\": [],\n    \"downstream_unlock_count\": 314,\n    \"evidence\": [\n      {\n        \"independence\": \"same-binary disassembly corroborates decompilation\",\n        \"source\": \"Ghidra SporeApp.exe 0x00b3d2a0: MOV EAX,[0x0167eae4]; RET\",\n        \"supports\": \"exact body, no arguments, no branches, no writes\"\n      },\n      {\n        \"independence\": \"independent same-binary field consumers\",\n        \"source\": \"Ghidra SporeApp.exe 0x00ba9370, 0x00b3d2c0, 0x00c4f030, 0x01021300\",\n        \"supports\": \"cStarManager compatibility at mEmpires+0x150 and relationship manager+0x204\"\n      },\n      {\n        \"independence\": \"independent canonical sibling decompilation\",\n        \"source\": \"Ghidra SporeApp.exe 0x00b3d3a0 -> DAT_0167eb0c\",\n        \"supports\": \"target is an alternate path, not the SDK-named canonical cStarManager::Get\"\n      },\n      {\n        \"independence\": \"independent repository static adjudication\",\n        \"source\": \"knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:11-19,76-104,118-143\",\n        \"supports\": \"alternate-manager identity, physical separation, bounded publisher negative\"\n      },\n      {\n        \"independence\": \"independ
[TRUNCATED]
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
      "va": "0x00ae9040"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9500"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9590"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9930"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00ae9f50"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aeb3e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aebe90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aecf90"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00aed2c0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b20790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b26790"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b279e0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b28070"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b28850"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b28da0"
    },
    {
      "name": "ProfilePersistenceBoundary_run_candidate_00b28ec0",
      "reconstructed": true,
      "va": "0x00b28ec0"
    },
    {
      "name": null,
      "reconstructed": false,
      "va": "0x00b294c0"
 
[TRUNCATED]
```

## 11_related_functions

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
[
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:32-bit pointer slot",
      "same_semantic_family"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 22,
    "symbol": "FUN_00b3d300",
    "va": "0x00b3d300"
  },
  {
    "match_basis": [
      "same_package",
      "same_subsystem",
      "shared_types:32-bit pointer slot"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 17,
    "symbol": "Simulator_GetUIMissionLogManager",
    "va": "0x00b3d4f0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "direct_xref_neighbor"
    ],
    "package": "PKG-13-E4-EMPIRE-WAVE3",
    "score": 9,
    "symbol": "EmpirePoliticalColor_00c32cd0",
    "va": "0x00c32cd0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d3a0",
    "va": "0x00b3d3a0"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "FUN_00b3d400",
    "va": "0x00b3d400"
  },
  {
    "match_basis": [
      "same_package"
    ],
    "package": "PKG-01-SHARED-STATE-ROOTS",
    "score": 8,
    "symbol": "Simulator_cSpaceTrading_Get",
    "va": "0x00b3d4d0"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueStarManager"
    ],
    "package": "PKG-11-SIM-CORE",
    "score": 8,
    "symbol": "Simulator_LookupEmpireByPoliticalId",
    "va": "0x00ba9370"
  },
  {
    "match_basis": [
      "same_class",
      "shared_types:OpaqueStarManager"
    ],
    "package":
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "file": "src/reconstruction/pkg01_roots/pkg01_roots.cpp",
  "files": [
    "src/reconstruction/pkg01_roots/pkg01_roots.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg01-roots/00b3d2a0.json"
  ]
}
```

## 13_semantic_hypotheses

- State: `present`
- Provenance: `knowledgegraph/research/semantic-decomp.json`

```json
{
  "original_bytes": 6712,
  "preview": "{\n  \"category\": null,\n  \"classification\": \"NEEDS_RUNTIME\",\n  \"confidence\": {\n    \"mechanics\": 1.0\n  },\n  \"contradictions\": [],\n  \"downstream_unlock_count\": 314,\n  \"evidence\": [\n    {\n      \"independence\": \"same-binary disassembly corroborates decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b3d2a0: MOV EAX,[0x0167eae4]; RET\",\n      \"supports\": \"exact body, no arguments, no branches, no writes\"\n    },\n    {\n      \"independence\": \"independent same-binary field consumers\",\n      \"source\": \"Ghidra SporeApp.exe 0x00ba9370, 0x00b3d2c0, 0x00c4f030, 0x01021300\",\n      \"supports\": \"cStarManager compatibility at mEmpires+0x150 and relationship manager+0x204\"\n    },\n    {\n      \"independence\": \"independent canonical sibling decompilation\",\n      \"source\": \"Ghidra SporeApp.exe 0x00b3d3a0 -> DAT_0167eb0c\",\n      \"supports\": \"target is an alternate path, not the SDK-named canonical cStarManager::Get\"\n    },\n    {\n      \"independence\": \"independent repository static adjudication\",\n      \"source\": \"knowledgegraph/research/noun-star-lifecycle/track-a-root-identity.md:11-19,76-104,118-143\",\n      \"supports\": \"alternate-manager identity, physical separation, bounded publisher negative\"\n    },\n    {\n      \"independence\": \"independent repository architecture decision\",\n      \"source\": \"docs/analysis/architecture-decisions.md:37-43\",\n      \"supports\": \"preserve separate opaque star-root ports until publication and equality are observed\"\n  
[TRUNCATED]
```

## 14_conflicts_questions

- State: `conflicted`
- Provenance: `reconstruction/knowledge/index.json, knowledgegraph/research/semantic-decomp.json`

```json
{
  "conflicts": [
    {
      "anchors": [
        "0x00b3d300",
        "0x00b3d400",
        "0x00b3d2a0",
        "0x00b3d3a0",
        "0x00b5b800",
        "0xffffffff",
        "0x00b3d300",
        "0x00b3d2a0",
        "0x00b3d400",
        "0x00b3d3a0",
        "0x00b5b800"
      ],
      "conflict_id": "CF-002",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": null,
      "resolution_status": null,
      "source": "knowledgegraph/research/conflicts/track-f-cross-domain-impact.json",
      "subject": null,
      "unresolved_reason": {
        "missing_evidence": [
          "Direct or indirect publisher and teardown evidence for both alternate/canonical manager slot pairs.",
          "Pointer-equality checks across mode and service lifecycle boundaries.",
          "The concrete receiver class and physical storage type behind DAT_0167eaec and forwarded_object+0x20."
        ],
        "status": "blocked"
      }
    },
    {
      "anchors": [
        "0x00b3d440",
        "0x00b3d2a0",
        "0x00b3d440",
        "0x00b3d2a0",
        "0x00b3d2a0",
        "0x00b3d440",
        "0x00b3d440",
        "0x00b3d2a0",
        "0x00b3d2a0",
        "0x00b3d2a0",
        "0x00b3d440",
        "0x00b3d2a0",
        "0x00b3d2a0",
        "0x00b3d440",
        "0x00c7f060",
        "0x00b32b20"
      ],
      "conflict_id": "NM-011",
      "kind": "conflict_ledger",
      "rejected": [],
      "resolution": "RESOLVED_OBSERVED",
      "resolution_status": "RESOLVED_OBSERVED",
      "source": "knowledgegraph/research/conflicts/track-a-type-signat
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'derived'}, {'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg01-roots/00b3d2a0.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'src/reconstruction/pkg01_roots/pkg01_roots.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "reconstruction/metadata/pkg01-roots/00b3d2a0.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "src/reconstruction/pkg01_roots/pkg01_roots.cpp",
      "source_class": "committed_artifact"
    }
  ],
  "read_first": [
    "reconstruction/knowledge/index.json",
    "src/reconstruction/pkg01_roots/pkg01_roots.cpp"
  ],
  "r
[TRUNCATED]
```
