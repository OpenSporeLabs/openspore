# Reconstruction context 0x00fc7e10

- Status: `partial`
- Content SHA-256: `6877fceb9b1af6b1a216e89228eba30d5484301fc49c8679a971b183cd32a7d4`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00fc7e10",
  "phase": "reconstruction",
  "target": "0x00fc7e10"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "UTFWin::ImageDrawable::GetTiling",
  "package": "pkg-utfwin-slot7-wave12",
  "subsystem": "UTFWin",
  "va": "0x00fc7e10"
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
  "content_sha256": "44995772e3c70c4e226b3cb9104adbb6822822e75016d7e514f850fa2479093d",
  "live_attempts": [
    {
      "code": "ghidra_rest_error",
      "kind": "decompilation",
      "message": "decompile 0x00fc7e10 failed: Decompilation did not complete. Reason: ",
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
  "ordinary_stack_argument_slots": [
    "entry_ESP+0x4",
    "entry_ESP+0x8"
  ],
  "ordinary_stack_arguments": [
    {
      "entry_offset": "entry_ESP+0x4",
      "name": "first_word",
      "observed": true,
      "ordinal": 1,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "type": "opaque 32-bit word"
    },
    {
      "entry_offset": "entry_ESP+0x8",
      "name": "second_word",
      "observed": true,
      "ordinal": 2,
      "size_inferred": false,
      "sizes": [
        4
      ],
      "type": "opaque 32-bit word"
    }
  ],
  "receiver": true,
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_observation": "EAX exits holding the first stack word. No instruction produces a result in EAX, so the machine level fact is a 4-byte value in EAX whose value equals the first argument; whether the original source produced it deliberately is NOT established by this evidence.",
  "return_register": "EAX",
  "return_semantics": "opaque 32-bit word in EAX, equal to the first stack argument; intended-return semantics unresolved",
  "return_type": "OpaqueWord",
  "return_width_bytes": 4,
  "saved_registers": "none; no register is pushed and no callee-saved register is written",
  "stack_cleanup_bytes": 8,
  "stack_cleanup_owner": "callee",
  "termination": "RET 0x8"
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
    "OpaqueWord",
    "opaque 32-bit word"
  ],
  "vtables": [
    "vtable:0x01491730",
    "vtable:0x01492140",
    "vtable:0x01493990"
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
      "No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the argument values a real caller passes cannot be observed.",
      "The declared types of the words at receiver +0x08 and +0x10 are not established. Their observed uses are a CALL target and a call argument respectively, which constrains but does not prove them.",
      "The owning C++ class name and the interface identity of slot +0x1c are not established. SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary; the 0x01493990 class is known only to derive from the 0x01491730 class because its constructor calls the latter's constructor.",
      "Whether the +0x10 and +0x14 words belong to the same sub-object as the constructor-initialised words is unresolved; none of the three constructors initialises them."
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
    "id": "scc-0583",
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
      "shared_types:opaque 32-bit word",
      "same_calling_convention"
    ],
    "package": "pkg-utfwin-settiling-wave13",
    "score": 11,
    "symbol": "set_tiling_00fd9460",
    "va": "0x00fd9460"
  },
  {
    "match_basis": [
      "same_subsystem",
      "same_calling_convention"
    ],
    "package": "pkg-dfw-00980510",
    "score": 8,
    "symbol": "dfw_get_proxy_id_00980510",
    "va": "0x00980510"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-0095fa30-utfwin-isancestorof",
    "score": 6,
    "symbol": "is_ancestor_of_0095fa30",
    "va": "0x0095fa30"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-utfwin-func35-wave12",
    "score": 6,
    "symbol": "func35_0095fd60",
    "va": "0x0095fd60"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-0096ff70",
    "score": 6,
    "symbol": "dfw_func88h_0096ff70",
    "va": "0x0096ff70"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-dfw-00980c50",
    "score": 6,
    "symbol": "dfw_00980c50_func88h",
    "va": "0x00980c50"
  },
  {
    "match_basis": [
      "shared_vtable:vtable:0x01491730,vtable:0x01492140",
      "same_calling_convention"
    ],
    "package": "pkg-sporepedia-nop-slot",
    "score": 6,
    "symbol": "sporepedia_nop_slot_FUN_00c2e4e0",
    "va": "0x00c2e4e0"
  },
  {
    "match_basis": [
      "shared_types:OpaqueWord",
      "same_calling_convention"
    ],
    "package": "PKG-APP-SERVICES-SAFE-WAVE11",
    "score": 5,
  
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "decomp": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__GetTiling.c",
  "files": [
    ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__GetTiling.c",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/.clang-format",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.cpp",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.hpp",
    "reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-utfwin-slot7-wave12/00fc7e10.json"
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
    "Do the two arguments form a related pair, such as a callback and its context? 0x00fc7ec0 consumes them together as a call target and a call argument, which is consistent with that reading, but no arithmetic or relation is applied between them in this function.",
    "Is the return register value intentional? No instruction produces a result in EAX, so the source level return type is unknown; the SDK label says ImageTiling but the body is setter shaped.",
    "No original-process invocation or indirect-caller trace was captured, so no concrete caller is known and the argument values a real caller passes cannot be observed.",
    "The declared types of the words at receiver +0x08 and +0x10 are not established. Their observed uses are a CALL target and a call argument respectively, which constrains but does not prove them.",
    "The owning C++ class name and the interface identity of slot +0x1c are not established. SporeApp.exe carries no MSVC RTTI, so class identity cannot be read from the binary; the 0x01493990 class is known only to derive from the 0x01491730 class because its constructor calls the latter's constructor.",
    "What is the declared type and role of the word at receiver +0x10? 0x00fc7ec0 passes it as the third stack word to the +0x08 call, so its role is a call argument, but its type is not proven.",
    "What is the declared type of the word at receiver +0x08? It is executed as a code address by 0x00fc7ec0 and returned as a dword by 0x0093b6c0, but no declared type is proven.",
    "Whether the +0x10 and
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': '.spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__GetTiling.c', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-utfwin-slot7-wave12/00fc7e10.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-slot7-wave12/.clang-format', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": ".spore-analysis/ghidra-exports/decompiled_sdk/UTFWin__ImageDrawable__GetTiling.c",
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
      "ref": "reconstruction/metadata/pkg-utfwin-slot7-wave12/00fc7e10.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-slot7-wave12/.clang-format",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-utfwin-slot7-wave12/utfwin_slot7_wave12.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "r
[TRUNCATED]
```
