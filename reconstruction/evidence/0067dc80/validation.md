# Validation 0x0067dc80

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-app-imessage-manager-dtor/get_0067dc80.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x0067dc80; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 11-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x0067dc80..0x0067dc9b, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a012288f944a5e8a70fc87652bd088b6fda6709246cd863988fc9ea2a801216b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b3640b47527af5f496b7ab0e418d3d5e90155718f4c9a76cb495e35b4f5dcc3b`
- Pack digest quoted by the briefing: `a012288f944a5e8a70fc87652bd088b6fda6709246cd863988fc9ea2a801216b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the value this body returns safe to use on the path where it just released the receiver? The body releases the receiver at 0x00f47380 and then returns that same receiver at 0x0067dc98. Whether 0x00f47380 tolerates being called on an object whose destructor has already run, and whether the returned word is meant to be discarded, is not established by any record for this target.
- The argument's upper 24 bits: this body reads one byte and masks one bit. Whether a caller ever puts anything but 0 or 1 in the other three bytes is not observable from this body and is not claimed either way.
- What are the receiver's members? Nothing in any record for this target names one, and this body reads none. The header's port types are void for that reason alone, and the model declares no offset, so the question is open rather than answered by omission.
- Who dispatches this body, and with what argument? fan_in is 0, callers is [], and the only reference to the address is the vtable entry at 0x01401798. So the entry conditions under which bit 0 of the argument is set are not established by anything in this repository -- which matters, because the whole difference between the two paths in this body is that bit.
- Why does 0x0067db10 test the flag at [ESI+0x11] before releasing the members at [ESI+0x14] and [ESI+0x20]? That gating lives in the callee, not here, and this package claims nothing about what it means. It is recorded because it is the only other place in the immediate neighbourhood where a 'should I tear down' flag is consulted, and a reader comparing the two bodies will want to know that the question was seen and not answered.
- Why does the record name this body 'App::IMessageManager::Get'? The image shows a scalar deleting destructor at vtable slot 0 and nothing that reads like a getter. Either the SDK name is wrong, or the slot-0 destructor and the 'Get' are two different things the symbol table has conflated, and this body is only one of them. The bridge returns no sibling App::IMessageManager symbol, so the symbol table cannot settle it and no runtime observation of this target exists.
