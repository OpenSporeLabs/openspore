# Validation 0x00841440

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-argscript-createdefsafe-00841440/argscript_createdefsafe_00841440.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 1 distinct address(es) for 0x00841440; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 11-instruction listing names through ECX (0x30) are all within the machine-derived receiver bounds (0x30), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x00841440..0x00841460, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9388e237d2edc0a3550ad26ab490fd84158293b1376915517de14e45723731d6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `768933d9fc5108eb8a0bb4c956caeefc884623fecb47b9ec3f287379f756ccc5`
- Pack digest quoted by the briefing: `9388e237d2edc0a3550ad26ab490fd84158293b1376915517de14e45723731d6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x0141c100 a genuine second reference to this function, and is 0x0141c0f4 a vtable? Both are outside the body. The record's own check says 0x0141c0f4 is the NUL of the string 'Sets a vector4 variable' and that no other incoming reference exists. Neither is used here as evidence for anything.
- Is 0x0141c100 a genuine second reference to this function, and is the briefing's vtable:0x0141c0f4 real? read_memory 0x0141c0e0 shows 0x0141c0f4 holding 62 6c 65 00, the NUL of the string "Sets a vector4 variable", so the vtable claim is a false positive. What reads the code-pointer run beginning at 0x0141c0f8, of which this function is the third entry, is unresolved, and that bears directly on whether the function is dispatched virtually at all.
- Is the declared bool a deliberate success flag on the first word, or does the first word simply leak through EAX because the tail had no other choice? No caller of this function has been found, so nothing constrains it. The model implements the observed machine behaviour (the first word, read as a byte) and adds no meaning to it.
- Is the returned bool a deliberate success flag on the first word, or does the first word simply leak through EAX because the tail had no other choice? EAX is never written by this body; the observed value is whatever 0x0083c780 leaves there, which its first instruction MOV EAX,[ESP+0x4] loaded from the first stack argument. Nothing in the static evidence distinguishes the two, and no caller of this function has been found to read the result. The model implements the observed behaviour and adds no meaning to it.
- Were the three conflict-ledger entries anchored on this VA ever adjudicated? All three record resolution 'the available observation is retained without semantic promotion' with reason 'Runtime reachability is absent or the required direct body/call path is not recovered'. This package supplies the static mechanics and does not supply the missing reachability, so those entries stay exactly as they are.
- Were the three conflict-ledger entries anchored on this VA ever adjudicated? All three record the resolution 'the available observation is retained without semantic promotion', with the reason 'Runtime reachability is absent or the required direct body/call path is not recovered'. This package supplies the static mechanics and does not supply the missing reachability, so those entries stand unchanged.
- What is 0x0083c780, and how many targets share it? Its five instructions are read, but its name, class and call-site population are not established here, so it is not promoted to a record. Its name suggests a two-word setter and this package does not go further than that.
- What is the true FormatParser layout, and how wide is the receiver? This package models 0x34 bytes, the minimum covering every displacement this call writes, and claims nothing beyond. The SDK structure places +0x30 inside a 0x20-byte mParsers at +0x2c, which contradicts a single biased-pointer store performed on every call, so at least one of the two is wrong.
- What is the word at receiver displacement 0x30? The body writes it on every call and reads it on none, biasing the second stack word down by one dword. Nothing read for this target names the member or says what an address one dword below the second argument denotes. The arithmetic is modelled; the meaning is not asserted, and the model deliberately gives the word no member name.
- What is the word at receiver displacement 0x30? The body writes it on every call and reads it on none, biasing the second stack word down by one dword. Nothing read for this target names the member or says what an address one dword below the second argument denotes. The arithmetic is modelled; the meaning is not asserted.
- Which parameter name belongs to the tested slot? The machine fixes that the body tests the second ordinary stack word, entry [ESP+0x8]. The persisted record calls entry [ESP+0x4] pName and entry [ESP+0x8] argumentsLine on the SDK prototype and the unsafe sibling 0x00844fb0; the exported decompilation labels the tested slot pName, which follows from that export placing the receiver at [ESP+0x4] and is refuted by the tail's RET 0x8. This package follows the persisted record. The model test asserts against the second stack word directly, so resolving the naming question cannot change any modelled effect. Settling it needs a caller or a native rebuild.
- Which parameter name belongs to the tested slot? The machine fixes that the body tests the second ordinary stack word, entry [ESP+0x8]. The persisted record calls entry [ESP+0x4] pName and entry [ESP+0x8] argumentsLine on the SDK prototype and the unsafe sibling; the exported decompilation labels the tested slot pName, which follows from Ghidra placing the receiver at [ESP+0x4] and is refuted by the tail's RET 0x8. This package follows the persisted record and states the dispute. The model test asserts the behaviour against the second word directly, so resolving the naming question cannot change any modelled effect. Settling it needs a native rebuild or a caller.
- Why does the derived ABI record abstain (ABI_UNKNOWN, confidence UNKNOWN) when the body plainly tail-jumps a single target from both arms? tools/reconstruction_tooling/abi_infer.py gates tail forwarding on len(state.jmps_direct) == 1 and this body has two direct jumps (0x00841452 and 0x00841460), so the forward is never attempted and the convention is left unnamed. This is a property of the machine evidence and of the inference engine, not of the reconstruction, and it is the sole remaining WARN on the static dimension.
- Why is the line pointer biased by four bytes before being stored at +0x30, and who reads that word back? The idiom recurs in the adjacent thunk at 0x00841410 against +0x0c, whose two jumps decode to 0x0083c7f0, so it is a family-wide shape rather than an artefact of this body. Its meaning is not recoverable from this VA alone.
