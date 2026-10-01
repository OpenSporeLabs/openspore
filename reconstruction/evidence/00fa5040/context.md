# Reconstruction context 0x00fa5040

- Status: `complete`
- Content SHA-256: `aadf2609edbbf6efda59b6941354f4a4607f91140a854a2b55397611cf241f07`

## 01_assignment

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "assignment_id": "openspore-context",
  "objective": "recover bounded source semantics for 0x00fa5040",
  "phase": "reconstruction",
  "target": "0x00fa5040"
}
```

## 02_function_identity

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "class_type": null,
  "name": "FUN_00fa5040",
  "package": null,
  "subsystem": "Sporepedia",
  "va": "0x00fa5040"
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
  "status": "candidate"
}
```

## 04_evidence_state

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "content_sha256": "9c7ae2db35920bfe2429685c030caf956eb2c1b1ffb7b93b39dbf11aa3a368d8",
  "live_attempts": [],
  "live_requested": true,
  "overall": "LIVE"
}
```

## 05_decompilation

- State: `present`
- Provenance: `GhidraMCP REST /decompile_function @ http://127.0.0.1:8089`

```json

undefined4 __thiscall FUN_00fa5040(int param_1,int param_2,char param_3)

{
  float *pfVar1;
  undefined4 *puVar2;
  uint *puVar3;
  uint uVar4;
  char cVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int local_18;
  uint local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar8 = *(int *)(param_1 + 0x788) - *(int *)(param_1 + 0x784);
  iVar12 = iVar8 >> 0x1f;
  iVar8 = iVar8 / 0xac + iVar12;
  uVar10 = 0;
  if (iVar8 != iVar12) {
    piVar9 = (int *)(*(int *)(param_1 + 0x784) + 0xa8);
    do {
      if (*piVar9 == param_2) {
        if (param_3 != '\0') {
          param_2 = 0;
          piVar9 = (int *)(param_1 + 0x218);
          do {
            uVar11 = piVar9[1] - *piVar9 >> 2;
joined_r0x00fa5106:
            uVar11 = uVar11 - 1;
            if (-1 < (int)uVar11) {
              piVar6 = (int *)(*piVar9 + uVar11 * 4);
              if ((*piVar6 != 0) && ((*(uint *)(*piVar6 + 0xb8) >> 3 & 1) != 0)) {
                iVar8 = 0;
                iVar12 = 0;
                do {
                  cVar5 = FUN_00fad140(iVar8,&local_10);
                  if ((((cVar5 != '\0') &&
                       (iVar7 = uVar10 * 0xac + iVar12,
                       pfVar1 = (float *)(iVar7 + 0x38 + *(int *)(param_1 + 0x784)),
                       iVar7 = iVar7 + 0x38 + *(int *)(param_1 + 0x784),
                       *pfVar1 <= local_8 && local_8 != *pfVar1)) &&
                      (local_10 < *(float *)(iVar7 + 8))) &&
                     ((*(float *)(iVar7 + 4) <= local
[TRUNCATED]
```

## 06_abi

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "architecture": "x86-32",
  "hidden_this": true,
  "hidden_this_register": "ECX",
  "ordinary_stack_argument_slots": 2,
  "receiver": "ECX carries the receiver, at INFERRED confidence, and is aliased into EBP at 0x00fa5045 for the rest of the body. The record's bounds_only flag is its own statement that the four enumerated displacements are an OPEN lower bound, and this package treats it as one: the offsets it reaches through the receiver alias are exactly the four the record enumerates (0x770, 0x774, 0x784, 0x788), and it asserts no field name, member, layout or size for any of them. Receiver is declared and left undefined.",
  "receiver_register": "ECX",
  "ret_form": "RET 0x8",
  "return_note": ". The WIDTH is the machine's: the last write before each of the two reachable terminators is a ONE-BYTE write to AL (XOR AL,AL at 0x00fa50d6, MOV AL,0x1 at 0x00fa5234 and 0x00fa5428) with no CALL between the write and the RET on either path. The exact C spelling is a source-side choice among the one-byte types and is not verified by the machine; bool is the width-computable choice and asserts no value constraint the machine does not show.",
  "return_observation": "Two reachable terminators, one byte each, and no bulk write. The record's return.aggregate_evidence.bulk_write is false and sret.present is false, so no hidden-pointer return is in play and the width read off the register is the width of the value.",
  "return_register": "EAX, low byte only. DIVERGENCE FROM THE RECORD, RECORDED NOT RESOLVED: the machine's own abi_derived.return reads {register XMM0, register_class 
[TRUNCATED]
```

## 07_callers_callees

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "callees": [],
  "callers": [],
  "edge_rows": [
    {
      "callsite": "0x00fa53ad",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa5214",
      "direction": "out",
      "other": "0x00f9f620",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa5408",
      "direction": "out",
      "other": "0x00f9f620",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa51b8",
      "direction": "out",
      "other": "0x00fa29b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa514d",
      "direction": "out",
      "other": "0x00fad140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa52b1",
      "direction": "out",
      "other": "0x00fad140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa534a",
      "direction": "out",
      "other": "0x00fadac0",
      "reference_type": "direct-call"
    }
  ],
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
    "bool",
    "bool. The WIDTH is the machine's: the last write before each of the two reachable terminators is a ONE-BYTE write to AL (XOR AL,AL at 0x00fa50d6, MOV AL,0x1 at 0x00fa5234 and 0x00fa5428) with no CALL between the write and the RET on either path. The exact C spelling is a source-side choice among the one-byte types and is not verified by the machine; bool is the width-computable choice and asserts no value constraint the machine does not show.",
    "openspore::reconstruction::pkg_sporepedia_dual_00fa5040::Real",
    "openspore::reconstruction::pkg_sporepedia_dual_00fa5040::Receiver",
    "openspore::reconstruction::pkg_sporepedia_dual_00fa5040::Word"
  ],
  "vtables": [
    "vtable:0x01490be8"
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
  "edges": [
    {
      "callsite": "0x00fa53ad",
      "direction": "out",
      "other": "0x004558a0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa5214",
      "direction": "out",
      "other": "0x00f9f620",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa5408",
      "direction": "out",
      "other": "0x00f9f620",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa51b8",
      "direction": "out",
      "other": "0x00fa29b0",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa514d",
      "direction": "out",
      "other": "0x00fad140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa52b1",
      "direction": "out",
      "other": "0x00fad140",
      "reference_type": "direct-call"
    },
    {
      "callsite": "0x00fa534a",
      "direction": "out",
      "other": "0x00fadac0",
      "reference_type": "direct-call"
    }
  ],
  "edges_truncated": false,
  "external_callees": [],
  "fan_in": 0,
  "fan_out": 0,
  "manifest_callees": [],
  "manifest_callers": [],
  "nearby_reconstructed": [],
  "scc": {
    "id": "scc-0578",
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
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w2-00f999e0",
    "score": 10,
    "symbol": "re_00f999e0",
    "va": "0x00f999e0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-fa0d50-atomic-inc",
    "score": 10,
    "symbol": "FUN_00fa0d50",
    "va": "0x00fa0d50"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-00fa5580",
    "score": 10,
    "symbol": "re_00fa5580",
    "va": "0x00fa5580"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-00fa6ec0",
    "score": 10,
    "symbol": "re_00fa6ec0",
    "va": "0x00fa6ec0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-00fa73c0",
    "score": 10,
    "symbol": "sw1_snap_and_dispatch_00fa73c0",
    "va": "0x00fa73c0"
  },
  {
    "match_basis": [
      "same_subsystem",
      "shared_vtable:vtable:0x01490be8"
    ],
    "package": "pkg-swarm-w1-0104c110",
    "score": 10,
    "symbol": "re_0104c110",
    "va": "0x0104c110"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-005c0dd0",
    "score": 6,
    "symbol": "re_005c0dd0",
    "va": "0x005c0dd0"
  },
  {
    "match_basis": [
      "same_subsystem"
    ],
    "package": "pkg-swarm-w1-006413d0",
    "score": 6,
    "symbol": "re_006413d0",
    "va": 
[TRUNCATED]
```

## 12_existing_reconstruction

- State: `present`
- Provenance: `reconstruction/knowledge/index.json`

```json
{
  "files": [
    "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.cpp",
    "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.hpp",
    "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040_model_test.cpp"
  ],
  "handoffs": [],
  "metadata": [
    "reconstruction/metadata/pkg-sporepedia-dual-00fa5040/00fa5040.json"
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
    "DECOMPILATION UNAVAILABLE. Both the persisted record and the live bridge report none for this target. Every claim in this package is from the disassembly listing, the machine-derived ABI record and the bytes the listing quotes.",
    "NO RUNTIME EVIDENCE. No trace of 0x00fa5040 running in the original binary exists in this repository, so nothing here is differentially validated and nothing here claims to be.",
    "THE CALLING CONVENTION. The record determines none: null, UNKNOWN, four candidates, ABI_UNKNOWN, three abstentions. __thiscall is the shape the receiver in ECX plus a callee that pops 8 bytes would suggest, and it is exactly the claim this package declines to make, because the record does not make it and the C11 abstention is specifically about the offsets that would settle it. The reconstruction therefore declares no convention token, and its own C++ linkage is a property of the model and not a claim about the original.",
    "THE PACK/UNPACK LOSSY ROUND TRIP ON THE SECOND-ARRAY PATH. 0x00fa5313..0x00fa531a packs (group << 0x18) | slot into one word and 0x00fa531e..0x00fa5332 unpacks it with SHR 0x18 and AND 0xffffff. If a slot index ever reached 0x1000000 the OR would corrupt the group half, and the machine would then compare against the wrong sub-table. The reconstruction models the round trip as lossless, which is right for every slot index a 32-bit object array can actually hold in practice and is not claimed to be a proof about the machine's behaviour at that boundary.",
    "THE RECEIVER WRITTEN-THROUGH
[TRUNCATED]
```

## 15_validation_and_provenance

- State: `present`
- Provenance: `{'mode': 'derived', 'ref': 'ephemeral reconstruction_knowledge.build_index', 'source_class': 'generated_index'}, {'mode': 'derived', 'ref': 'tools/reconstruction_tooling/abi_infer.py', 'source_class': 'derived'}, {'mode': 'live', 'ref': 'GhidraMCP /disassemble_function', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /decompile_function @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'live', 'ref': 'GhidraMCP REST /get_function_by_address + /analyze_function_complete @ http://127.0.0.1:8089', 'source_class': 'ghidra'}, {'mode': 'persisted', 'ref': 'knowledgegraph/research/source-reconstruction-manifest.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'knowledgegraph/triage/queue-f0e310e0-v6.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/metadata/pkg-sporepedia-dual-00fa5040/00fa5040.json', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.cpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.hpp', 'source_class': 'committed_artifact'}, {'mode': 'persisted', 'ref': 'reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040_model_test.cpp', 'source_class': 'committed_artifact'}`

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
      "ref": "GhidraMCP REST /decompile_function @ http://127.0.0.1:8089",
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
      "ref": "reconstruction/metadata/pkg-sporepedia-dual-00fa5040/00fa5040.json",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.cpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.hpp",
      "source_class": "committed_artifact"
    },
    {
      "mode": "persisted",
      "ref": "recon
[TRUNCATED]
```
