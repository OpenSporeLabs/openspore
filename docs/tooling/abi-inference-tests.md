# ABI inference engine — test plan

Pure x86-32 ABI inference module: `tools/reconstruction_tooling/abi_infer.py`.
Consumed by `evidence.collect()`, read by `validate.py`, surfaced by
`context.build()` → `worker_contract.briefing()`.

Status: DESIGN. No code shipped by this document.

---

## 0. Grounding (read before implementing)

### 0.1 Modules under test

| file | role | load-bearing facts |
|---|---|---|
| `tools/reconstruction_tooling/models.py` | shared primitives | `normalize_va` (→ `"0x%08x"`), `canonical_json` (`indent=2, sort_keys=True, ensure_ascii=False` + `"\n"`), `sha256_json`, `compact(value, max_bytes)`, `bounded`, `write_json_atomic` |
| `tools/reconstruction_tooling/evidence.py` | evidence pack | `collect(root, va, live, write, out_dir)`; `_live_disassembly(va)` calls `ghidra_tools._get_client().request("/disassemble_function", {"address": va})`; `_category(state, value, provenance, source_class, evidence_level)`; `categories["abi"]` built at line 207 from `record.get("abi", {})`; `pack["content_sha256"] = sha256_json(pack)` at line 315; `render_evidence_markdown` |
| `tools/reconstruction_tooling/context.py` | context brief | `sections["06_abi"]` at line 88 reads **only** `record.get("abi", {})` from the index; `sections["15_…"]` declares `required_categories` incl. `"ABI"`; `critical_available` at line 99 gates `status` on `("ghidra_function","decompilation","abi")` |
| `tools/reconstruction_tooling/validate.py` | validator | ABI ladder at lines 156-165; `_convention_key`; `_check(status, detail, coverage, evidence)`; `VALIDATION_VERDICTS` vocabulary reused from `worker_contract` |
| `tools/reconstruction_tooling/worker_contract.py` | worker briefing | `abi = _section_data(context, "06_abi")`; `absent += _missing(["ABI"], ["ABI"] if abi else [], …)` → `evidence.missing_sections`; `package["abi"] = compact(abi, 4000)` |

### 0.2 Existing test suite — exact conventions

Framework: **stdlib `unittest` only. No pytest, no tox, no pyproject, no
`pytest.ini`, no `setup.cfg`, no `Makefile`, no CI workflow** (`.github/`
contains only `ISSUE_TEMPLATE.md` and `PULL_REQUEST_TEMPLATE.md`).

Run command (quoted from `tests/README.md:11`):

```
python3 -m unittest discover -s tests -t . -v
```

Per-module invocation (quoted from `tests/mcp/test_ghidra.py:12`):

```
python3 -m unittest tests.mcp.test_ghidra -v
```

Current state (measured):

```
$ python3 -m unittest discover -s tests -t .
Ran 534 tests in 93.899s
OK
```

Layout & naming:

* `tests/test_*.py` — discovered, hermetic.
* `tests/mcp/`, `tests/viewer/` — packages, each with `__init__.py`, same `test_*.py` convention.
* `tests/diff_real.py`, `tests/live_ghidra_reconstruction.py`, `tests/orchestration_fixture.py`, `tests/fixtures/fake_worker.py` — deliberately **not** `test_*.py` so `discover` ignores them.
* No `conftest.py`, no fixtures-in-args framework. Shared helpers go in a non-`test_` module imported explicitly: `from tests import orchestration_fixture as fx`.
* `tests/__init__.py` exists (empty) → `tests` is an importable package.

Direct-function invocation, not CLI, is the default (`from
tools.reconstruction_tooling.evidence import collect` then
`collect(va="0x00e5b790", live=False, write=False)`). CLI is exercised
separately by capturing stdout: `with contextlib.redirect_stdout(output):
cli.main([...])` then `json.loads(output.getvalue())`.

Ghidra stubbing — the house pattern, quoted from `tests/mcp/test_ghidra.py:107`:

```python
    def setUp(self):
        self.tmp = tempfile.mkdtemp(prefix="openspore-ghidra-")
        self._old_cache = os.environ.get("OPENSPORE_MCP_CACHE")
        os.environ["OPENSPORE_MCP_CACHE"] = self.tmp
        self._old_factory = gt._CLIENT_FACTORY
        self.fake = FakeClient()
        gt._CLIENT_FACTORY = lambda: self.fake
        gt._FUNCTION_MEMO.clear()
        gt._VTABLES_DOC["loaded"] = False
        gt._VTABLES_DOC["doc"] = None
        gt._DOSSIER_MOD["loaded"] = False
        gt._DOSSIER_MOD["mod"] = None

    def tearDown(self):
        gt._CLIENT_FACTORY = self._old_factory
        ...
        shutil.rmtree(self.tmp, ignore_errors=True)
```

The fake client is a plain class with `version()`, `check_connection()`,
`decompile()`, `function_by_address()`, `analyze_function()`,
`search_functions()`, each appending to `self.calls` and returning
`{"status": "ok", ...}`. Variants `OfflineClient` and `RaisingClient` prove
graceful degradation. This is the only Ghidra stubbing mechanism; the new
tests must reuse it, not invent another.

Assertion style: plain `assertEqual`/`assertIn`/`assertTrue` with a message
carrying the whole offending dict, e.g.

```python
self.assertEqual(category["availability"], "available",
                 "committed snapshots must expose decompilation text; keys=%r"
                 % (DECOMPILATION_KEYS,))
```

and `self.subTest(...)` for loops. Module docstrings state the coverage, the
hermeticity guarantees, and the run command. Known production defects are
pinned as `test_pinned_*` with the `file:line` in the docstring.

### 0.3 Existing fixture / golden-file pattern

Two distinct, established patterns:

1. **Generated binary fixtures** — `tests/fixtures/gen_fixtures.py` writes
   `tests/fixtures/mini_package.dbpf`, `mini_rw4.rw4`, `mini.gmdl`. The
   generator is pure Python, no timestamps/randomness, and fails loudly if
   the bytes would change:

   ```python
   def write_if_identical(path, blob):
       if os.path.exists(path):
           with open(path, 'rb') as f:
               if f.read() != blob:
                   sys.exit(f"FATAL: {os.path.basename(path)} on disk differs "
                            f"from regenerated bytes ...")
   ```

2. **Golden expectation files** — `tests/expected/real_gmdl_1006.json`, held
   *semantic fields only, never asset bytes*, re-recordable with
   `python3 tests/diff_real.py --record`, compared with a recursive
   `semantic_diff(expected, actual, path='$')` helper that prints
   `path.key: expected … got …` lines and **flags keys present in actual but
   absent in expected** ("unexpected in actual"). A missing expectation file
   or a changed package exits non-zero.

Both apply directly: text fixtures are regenerable byte-for-byte, and the
expected record is pure JSON, so `semantic_diff` gives the required
compact expected-vs-actual diff for free.

One cross-module mirroring precedent: `orchestration_fixture.sha256_file`
says "Streamed sha256, mirroring tests/viewer/test_server.py::_sha256", and
`tests/diff_real.py::semantic_diff` is the canonical diff. The new test
module re-declares `semantic_diff` locally with a pointer comment (importing
`tests/diff_real` would run its `sys.path.insert` side effects).

### 0.4 Live-Ghidra test convention

`tests/live_ghidra_reconstruction.py` is the template, quoted in full
(26 lines) in the report. Key properties: filename does **not** start with
`test_`; the file re-inserts the repo root on `sys.path[0]` and says why; it
is run explicitly and never by `discover`.

---

## 1. Engine contract the tests pin

### 1.1 Record schema

```json
{
  "schema": "openspore-abi-inference-1",
  "va": "0x0040ccb0",
  "shape": "body|thunk|empty|unparseable",
  "verdict": "__cdecl|__stdcall|__thiscall|__fastcall|ABI_UNKNOWN",
  "confidence": "PASS|SUPPORTED|WEAK|UNKNOWN",
  "abstained": false,
  "abstain_reasons": [],
  "unknowns": ["argument_types", "return_type", "receiver_type"],
  "contradictions": [{"kind": "...", "detail": "...", "based_on": ["O11"]}],
  "ambiguities":   [{"between": ["..."], "because": ["O7", "O9"]}],
  "input": {"layout": "plain_text|json_instruction_list|gcodebrowser_text|att_text",
            "instruction_count": 15, "parsed_lines": 15, "unparsed_lines": 0,
            "sha256": "<sha256 of the raw input bytes>"},
  "observations": [{"id": "O1", "kind": "frame_prologue",
                    "address": "00100040", "detail": "PUSH EBP; MOV EBP,ESP"}],
  "inferences":   [{"id": "I1", "claim": "calling_convention",
                    "value": "__thiscall", "confidence": "PASS",
                    "based_on": ["O1", "O3"]}]
}
```

Hard structural rules (each one a test):

* `observations` sorted by `(address, sequence)`; ids assigned `O1..On`
  **after** sorting, dense and gap-free.
* `inferences` emitted in a fixed claim order: `calling_convention`,
  `receiver`, `register_incoming_registers`, `stack_arguments`,
  `stack_cleanup`, `hidden_return`, `return_kind`. Ids `I1..Im`, dense.
* No `null`-valued inferences are emitted.
* Every inference has `len(based_on) >= 1`.
* `PASS` is reserved for the single `calling_convention` claim, and is emitted
  only when `verdict != "ABI_UNKNOWN"` and `contradictions == []` and
  `ambiguities == []`. Every other claim caps at `SUPPORTED`.
* `canonical_json` is applied to the record before `sha256_json`, so the whole
  document is key-sorted.

### 1.2 Vocabularies (whitelists, asserted)

```python
CALLING_CONVENTIONS = ("__cdecl", "__stdcall", "__thiscall", "__fastcall", "ABI_UNKNOWN")
CLEANUP_MODES        = ("caller", "callee", "UNKNOWN")
CONFIDENCES          = ("PASS", "SUPPORTED", "WEAK", "UNKNOWN")
SHAPES               = ("body", "thunk", "empty", "unparseable")
PLAUSIBLE_MEMBER_MAX = 0x1000
```

### 1.3 Rules R0–R12 (normative, referenced by every expectation)

* **R0 Parse.** Accepts `json_instruction_list` (bare list, or
  `{"instructions": [...]}`), `gcodebrowser_text` (`0040ccb0  55   PUSH EBP`,
  address and/or raw-byte columns optional), `plain_text`, `att_text`
  (`push %ebp`). Unparseable lines become `unparsed` observations; they never
  abort.
* **R1 Frame trust.** `frame_pointer_trusted` iff `PUSH EBP` immediately
  followed by `MOV EBP,ESP` at body offset 0 **and** EBP is never redefined by
  anything else. Otherwise every `[EBP+d]` observation carries
  `"trust": "untrusted_frame"` and supports no argument claim.
  Real trap: `0x00de9fc0` has `SUB ESP,0x64 / PUSH EBP / … / MOV EBP,ECX` —
  no `MOV EBP,ESP` at all.
* **R2 Receiver (ECX).** Requires ≥2 distinct *memory* accesses through
  `[ECX+d]` with `d ∈ [0, 0x1000]`, at least one of which is a `load` or
  `store`. `LEA`-only uses do not count. Otherwise `receiver = UNKNOWN` with
  reason `ecx_read_never_dereferenced` (0 qualifying derefs) or
  `single_implausible_member_offset` (exactly 1, offset > 0x1000).
* **R3 Stack arguments.** Only under R1. Incoming slots are the contiguous run
  of 4-byte steps ending at the highest observed positive `[EBP+d]`, counted
  from `+0x8` = position 1. A gap ⇒ `arg_count = UNKNOWN`
  (`non_contiguous_arg_slots`).
* **R4 Cleanup.** Collect every `ret_form`. All immediates equal ⇒
  `callee` if `imm > 0` else `caller`, `stack_cleanup_bytes = imm`. Distinct
  immediates ⇒ contradiction `ret_immediate_mismatch`, `cleanup = UNKNOWN`.
  Any `imm % 4 != 0` ⇒ contradiction `ret_immediate_not_dword_multiple`,
  `cleanup = UNKNOWN`.
* **R5 Convention.**
  * receiver `ECX`, EDX not an incoming register arg ⇒ `__thiscall`
  * receiver `ECX`, EDX *is* an incoming register arg ⇒ `__fastcall`
  * receiver `UNKNOWN` ⇒ `ABI_UNKNOWN`
  * receiver absent (ECX never read-before-written) ⇒ `callee`+args ⇒
    `__stdcall`; `caller`+args ⇒ `__cdecl`; `caller`+0 args ⇒ `ABI_UNKNOWN`
    with reason `argless_cdecl_stdcall_indistinguishable`; `UNKNOWN` cleanup ⇒
    `ABI_UNKNOWN`.
* **R6 Hidden return (sret).** Conjunctive gate, all required: (i) zero `load`
  accesses through `[ECX+d]`; (ii) ≥2 distinct load offsets in `[0,0x1000]`
  through `[EDX+d]`; (iii) R1 trusted; (iv) a store at `[ECX+0x0]`; (v) `ret`
  immediate non-zero **or** `arg_count >= 1`. Firing ⇒
  `hidden_return` at `WEAK` with `ambiguities` entry
  `["__thiscall+sret(ECX)", "__fastcall"]` and verdict forced to
  `ABI_UNKNOWN` (the two readings are indistinguishable from a callee body
  alone). The stack-buffer form — buffer read from `[EBP+0x8]` and written
  through a frame slot while ECX keeps ≥2 member loads — is *not* ambiguous
  and yields `__thiscall` + `hidden_return` `SUPPORTED`.
* **R7 Return kind.** `pointer_like` when EAX's last pre-`RET` def is a load
  whose base register is proven to be a pointer (used as a memory base
  elsewhere and not the frame pointer); `integral_small` for `MOV EAX,imm`,
  `imm ∈ [0,255]`; `integral_zero` for `XOR/SUB EAX,EAX`; `x87_st0` when the
  body has `FLD`/`FST` and ST0 is live; `void_or_unwritten_eax` at `WEAK`;
  otherwise omitted and `"return_type"` appended to `unknowns`.
* **R8 Abstention gates.** Any one ⇒ `verdict = ABI_UNKNOWN`,
  `abstained = true`, reason appended, **and every inference capped at
  `WEAK`**: `empty_input`, `nothing_parseable`, `varargs_or_alloca_prologue`
  (≥2 `MOV dword ptr [EBP-x],0` before a `CALL`), `alloca_probe`
  (`CMP ESP,reg` before a `CALL`), `untrusted_frame_stack_reads`,
  `contradictory_cleanup`, `tail_call_thunk_no_body`, `ecx_and_edx_indistinguishable`.
  A `FS:[0x…]` access is **not** a gate: it downgrades arg-count confidence by
  one level but leaves receiver evidence intact (real basis: `0x004bdc00`).
* **R9 Thunk.** A body consisting solely of one `JMP <addr>` ⇒ `shape="thunk"`,
  `verdict="ABI_UNKNOWN"`, reason `tail_call_thunk_no_body`, plus the observed
  `tail_jump_target`. Never a signature.
* **R10 Multi-exit.** >1 `ret_form` ⇒ `exit_points` observation; verdict is
  the least-supported per-exit reading. Identical immediats ⇒ no
  contradiction, but confidence downgraded one level (`PASS`→`SUPPORTED`).
* **R11 Determinism.** No timestamps, no `random`, no `id()`, no unordered set
  iteration. Identical input ⇒ byte-identical `sha256_json(record)`.
* **R12 Idempotence.** `infer(list_form) == infer(text_form) == infer(att_form)`
  for the same underlying instruction stream (see the adapter fixtures).

---

## 2. Part A — hermetic unit tests on synthetic fixtures

### 2.1 Fixture layout (matches `tests/fixtures/` + `tests/expected/`)

```
tests/fixtures/gen_abi_fixtures.py       deterministic generator + --record
tests/fixtures/abi/<nn>_<slug>.asm       input disassembly, Intel syntax
tests/fixtures/abi/<nn>_<slug>.att       AT&T twin (adapter fixtures only)
tests/fixtures/abi/live/<va8>_<slug>.json  captured live /disassemble_function
tests/expected/abi/<nn>_<slug>.json      expected inference record
tests/expected/abi/live/<va8>_<slug>.json expected record for the live capture
```

`gen_abi_fixtures.py` mirrors `tests/fixtures/gen_fixtures.py`: writes each
`.asm` via a `write_if_identical`-style guard that `sys.exit`s with `FATAL:`
on byte drift, and `--record` regenerates every `tests/expected/abi/*.json`
from the current engine. It fills `input.sha256` from the `.asm` bytes, so the
test recomputes and re-checks it — a drifted `.asm` fails loudly.

Comparison is `semantic_diff(expected, actual)` over the whole record, so a new
top-level key fails as "unexpected in actual" in every fixture, forcing a
deliberate `--record`.

### 2.2 The 20 fixtures

Notation: `;` separates instruction lines. `EXPAND` lists the `inferences`
that must be present with the exact `value` and `confidence`; omissions mean
the claim is absent.

---
#### 01 `thiscall_member` — requirement 1

```
PUSH EBP
MOV EBP,ESP
SUB ESP,0x10
MOV EAX,dword ptr [ECX + 0x8]
MOV dword ptr [ECX + 0xc],EAX
MOV EAX,dword ptr [ECX + 0x10]
ADD EAX,0x4
MOV dword ptr [ECX + 0x14],EAX
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JZ 0x00100050
MOV EAX,dword ptr [ECX + 0x8]
MOV dword ptr [EBP + 0xc],EAX
MOV ESP,EBP
POP EBP
RET
```

Observations: `O1 frame_prologue`, `O2 frame_shape(SUB ESP,0x10)`,
`O3 ecx+0x8 load`, `O4 ecx+0xc store`, `O5 ecx+0x10 load`, `O6 ecx+0x14 store`,
`O7 ebp+0x08 load`, `O8 branch`, `O9 ebp+0x0c store`, `O10 epilogue`,
`O11 ret_form(immediate=null)`.

`EXPAND`
| claim | value | confidence | based_on |
|---|---|---|---|
| `calling_convention` | `"__thiscall"` | `PASS` | O1,O3,O4,O5,O6 |
| `receiver` | `{"register":"ECX","member_offsets":[8,12,16,20]}` | `SUPPORTED` | O3,O4,O5,O6 |
| `stack_arguments` | `[{"position":1,"entry_offset":"EBP+0x08","width_bytes":4},{"position":2,"entry_offset":"EBP+0x0c","width_bytes":4}]` | `SUPPORTED` | O1,O7,O9 |
| `stack_cleanup` | `{"mode":"caller","bytes":0}` | `SUPPORTED` | O11 |
| `return_kind` | `"pointer_like"` | `SUPPORTED` | O3,O11 |

`verdict="__thiscall"`, `confidence="PASS"`, `abstained=false`,
`unknowns=["argument_types","receiver_type"]`, `contradictions=[]`,
`ambiguities=[]`.

---
#### 02 `thiscall_sret_stack_buffer` — requirement 2

```
PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV EAX,dword ptr [EBP + 0x8]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x1c]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x20]
MOV dword ptr [EBP + -0x1c],EAX
MOV EAX,dword ptr [EBP + 0xc]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [ECX + 0x24]
MOV dword ptr [EBP + -0x18],EAX
MOV EAX,dword ptr [EBP + 0x10]
MOV dword ptr [EBP + -0x1c],EAX
MOV EAX,dword ptr [ECX + 0x28]
MOV dword ptr [EBP + -0x1c],EAX
MOV ESP,EBP
POP EBP
RET 0xc
```

`EXPAND`
| claim | value | confidence |
|---|---|---|
| `calling_convention` | `"__thiscall"` | `PASS` |
| `receiver` | `{"register":"ECX","member_offsets":[28,32,36,40]}` | `SUPPORTED` |
| `stack_arguments` | `[{"position":1,"entry_offset":"EBP+0x08","width_bytes":4,"role":"sret_buffer"},{"position":2,"entry_offset":"EBP+0x0c","width_bytes":4,"role":"ordinary"},{"position":3,"entry_offset":"EBP+0x10","width_bytes":4,"role":"ordinary"}]` | `SUPPORTED` |
| `stack_cleanup` | `{"mode":"callee","bytes":12}` | `SUPPORTED` |
| `hidden_return` | `{"kind":"sret","register":null,"buffer_source":"stack","buffer_position":1,"buffer_frame_slot":"EBP-0x18"}` | `SUPPORTED` |

`return_kind` **absent**; `"return_type"` in `unknowns`. This is the fixture
that proves the engine can be `PASS` on the convention while still refusing to
name a return type.

---
#### 03 `cdecl_three_stack_args` — requirement 3

```
PUSH EBP
MOV EBP,ESP
SUB ESP,0x8
MOV EAX,dword ptr [EBP + 0x8]
MOV ECX,dword ptr [EBP + 0xc]
ADD EAX,ECX
MOV EDX,dword ptr [EBP + 0x10]
ADD EAX,EDX
MOV ESP,EBP
POP EBP
RET
```

`EXPAND`: `calling_convention="__cdecl"` `PASS`;
`stack_arguments=[{1,"EBP+0x08"},{2,"EBP+0x0c"},{3,"EBP+0x10"}]` `SUPPORTED`;
`stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`;
`return_kind="integral_small"` `SUPPORTED` (last EAX def is `MOV EAX,…`
loaded from a *frame slot* ⇒ not pointer-proven; see note) — the fixture is
rewritten so the last def is `MOV EAX,1` appended before `RET` so the claim is
`integral_small` unambiguously.

**Adversarial point pinned here:** `MOV ECX,dword ptr [EBP + 0xc]` must NOT be
read as a register argument — ECX's def dominates its use and its source is a
frame slot.

---
#### 04 `stdcall_ret_0xc` — requirement 4

```
XOR AL,AL
RET 0xc
```

`EXPAND`: `calling_convention="__stdcall"` `PASS`; no `receiver` claim
(ECX never read); `stack_arguments=[{1,"ESP+0x04"},{2,"ESP+0x08"},{3,"ESP+0x0c"}]`
`SUPPORTED` (3 callee-cleaned words, derived from the immediate because there
is no frame); `stack_cleanup={"mode":"callee","bytes":12}` `SUPPORTED`.
`shape="body"`. This is the real `0x00951230` shape.

---
#### 05 `fastcall_ecx_edx` — requirement 5

```
PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [ECX + 0x4]
MOV EDX,dword ptr [EDX + 0x8]
ADD EAX,EDX
MOV dword ptr [ECX + 0x8],EAX
MOV EAX,dword ptr [ECX + 0xc]
ADD EAX,dword ptr [EDX + 0x10]
MOV ESP,EBP
POP EBP
RET
```

`EXPAND`: `calling_convention="__fastcall"` `PASS`;
`receiver={"register":"ECX","member_offsets":[4,8,12]}` `SUPPORTED`;
`register_incoming_registers=["ECX","EDX"]` `SUPPORTED`;
`stack_arguments=[]`, `stack_cleanup={"mode":"caller","bytes":0}`;
`return_kind="pointer_like"`.
Note: the frame is `MOV EBP,ESP` at offset 0 with no `PUSH EBP` before it —
the fixture uses `PUSH EBP / MOV EBP,ESP` so R1 holds.

---
#### 06 `ecx_read_never_dereferenced` — requirement 6 (MUST ABSTAIN)

```
PUSH EBP
MOV EBP,ESP
SUB ESP,0x8
MOV EAX,ECX
MOV dword ptr [EBP + -0x4],EAX
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JZ 0x00200040
XOR EAX,EAX
MOV ESP,EBP
POP EBP
RET
```

`verdict="ABI_UNKNOWN"`, `abstained=true`,
`abstain_reasons=["ecx_read_never_dereferenced"]`,
`unknowns` includes `"receiver"`, `"calling_convention"`.
`EXPAND` (all ≤ `WEAK`): `stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`,
`stack_arguments=[{1,"EBP+0x08"}]` `SUPPORTED`, `return_kind="integral_zero"`
`SUPPORTED`. No `calling_convention` inference at all. This is the real
`0x004ae250` shape.

---
#### 07 `ecx_single_implausible_offset` — requirement 7 (MUST ABSTAIN)

```
PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [ECX + 0x4000]
RET
```

`verdict="ABI_UNKNOWN"`, `abstain_reasons=["single_implausible_member_offset"]`.
`EXPAND`: `receiver={"register":"UNKNOWN","reason":"single_implausible_member_offset","observed_offsets":[16384]}` `WEAK`; `stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`; `return_kind="pointer_like"` `SUPPORTED`.
Pins the `0 < d ≤ 0x1000` plausibility window and its boundary.

---
#### 08 `leaf_no_frame` — requirement 8

```
MOV EAX,0x2a
RET
```

`shape="body"`, `verdict="ABI_UNKNOWN"`,
`abstain_reasons=["argless_cdecl_stdcall_indistinguishable"]`.
`EXPAND`: `stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`;
`return_kind="integral_small"` `SUPPORTED`. No convention claim. Pins that a
frameless leaf is *observable* but not classifiable.

---
#### 09 `naked_thunk` — requirement 9

```
JMP 0x00929bd0
```

`shape="thunk"`, `verdict="ABI_UNKNOWN"`,
`abstain_reasons=["tail_call_thunk_no_body"]`.
`EXPAND`: **none**. Observations: `O1 tail_jump{target:"0x00929bd0"}`,
`O2 shape_thunk`. Real `0x007e6080` verbatim.

---
#### 10 `contradictory_ret_immediates` — requirement 10

```
PUSH EBP
MOV EBP,ESP
CMP dword ptr [EBP + 0x8],0x0
JNE 0x00300060
MOV EAX,dword ptr [ECX + 0x4]
MOV ESP,EBP
POP EBP
RET 0x4
JNE 0x00300090
MOV EAX,dword ptr [ECX + 0x8]
MOV ESP,EBP
POP EBP
RET 0x8
```

`verdict="ABI_UNKNOWN"`, `abstain_reasons=["contradictory_cleanup"]`.
`contradictions=[{"kind":"ret_immediate_mismatch","detail":"RET 0x4 vs RET 0x8","based_on":["O11","O18"]}]`.
`EXPAND`: `receiver={"register":"ECX","member_offsets":[4,8]}` `SUPPORTED`
(independent of cleanup); `stack_cleanup={"mode":"UNKNOWN","bytes":null}`
`SUPPORTED`; `stack_arguments` **absent** (cannot bound the arg list).
Pins that a contradictory cleanup must suppress the convention *without*
suppressing receiver evidence.

---
#### 11 `vtable_slot_call` — requirement 11

```
PUSH EBP
MOV EBP,ESP
MOV ECX,dword ptr [ECX + 0x20]
MOV EAX,dword ptr [ECX]
MOV EDX,dword ptr [EAX + 0x50]
CALL EDX
MOV EDX,dword ptr [EAX]
MOV ECX,EAX
MOV EAX,dword ptr [EDX + 0x38]
CALL EAX
XOR EAX,EAX
RET
```

`verdict="__thiscall"`, `confidence="SUPPORTED"` (**not** `PASS` — R10
downgrade for the 2-exit/vtable complexity gate).
`EXPAND`: `receiver={"register":"ECX","member_offsets":[0,32],"note":"first 8 instructions only; ECX is reassigned at 0x006"}` `WEAK`;
`stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`;
`return_kind="integral_zero"` `SUPPORTED`;
`unknowns` includes `"callee_conventions"` (the two `CALL reg` sites are
`indirect_call` observations with no resolvable callee);
observations include two `indirect_call` entries and a `vtable_chain`
observation `{chain:["[ECX+0x20]","[[..]]","[[..]+0x50]"],"slots":[80,56]}`.
Pins that virtual dispatch is *observed* but never resolved into a signature.

---
#### 12 `varargs_prologue` — requirement 12 (MUST ABSTAIN)

```
PUSH EBP
MOV EBP,ESP
SUB ESP,0x20
MOV dword ptr [EBP + -0x4],0x0
MOV EAX,dword ptr [EBP + 0x8]
TEST EAX,EAX
JNE 0x00400070
MOV dword ptr [EBP + -0x8],0x0
PUSH dword ptr [EBP + -0x8]
PUSH EAX
MOV ECX,dword ptr [ECX + 0x4]
CALL 0x00903400
ADD ESP,0x8
MOV dword ptr [EBP + -0x4],0x1
MOV EAX,dword ptr [EBP + 0xc]
RET
```

`verdict="ABI_UNKNOWN"`,
`abstain_reasons=["varargs_or_alloca_prologue"]`.
`EXPAND` (all ≤ `WEAK`): `receiver={"register":"ECX","member_offsets":[4]}` `WEAK`
(1 offset only); `stack_cleanup={"mode":"caller","bytes":0}` `WEAK`;
`unknowns` includes `"variadic_argument_list"`.
Pins the R8 cap: a gate forces *every* inference to `WEAK` or below.

---
#### 13 `pointer_return` — requirement 13

```
PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [EBP + 0x8]
RET
```

`verdict="__cdecl"` (`arg_count` 1, caller cleanup).
`EXPAND`: `stack_arguments=[{1,"EBP+0x08"}]` `SUPPORTED`;
`stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`;
`return_kind="pointer_like"` `SUPPORTED`; `"return_type"` in `unknowns`.
Pins that pointer-*like* is a machine fact, not a `Transform*` invention.

---
#### 14 `integral_return` — requirement 14

```
PUSH EBP
MOV EBP,ESP
MOV EAX,0x1
RET
```

Same convention path as 13, `return_kind="integral_small"`.
Pair-asserted against 13 in one test so the two can never be conflated.

---
#### 15 `unparseable` — requirement 15 (graceful abstention, 5 files)

`15a_empty.asm` (0 bytes), `15b_whitespace.asm` (`"   \n\n\t\n"`),
`15c_binary.asm` (NUL bytes + lone `0xFF` + a UTF-8 replacement char),
`15d_truncated.asm` (`"PUSH EBP\nMOV EBP,ESP\nSUB ESP,0x4"` — no `RET`,
falls off the end), `15e_prose.asm` (an English paragraph).

For 15a/15b: `shape="empty"`, `verdict="ABI_UNKNOWN"`,
`abstain_reasons=["empty_input"]`, `observations=[]`, `inferences=[]`.
For 15c/15e: `shape="unparseable"`,
`abstain_reasons=["nothing_parseable"]`, observations are all
`{"kind":"unparsed"}`.
For 15d: `shape="body"`, `abstain_reasons=["no_return_instruction"]`.
No exception, ever — each is also a case in the Part B fuzz corpus.

---
#### 16 `adapter_layouts` — requirement 16 (three layouts, one verdict)

Same function, three input encodings, all compared against **one** expected
record (`16_thiscall_member.json`).

`16a` = the `01` body verbatim, `plain_text`.
`16b` Ghidra CodeBrowser listing, `gcodebrowser_text`:
```
Listing  Address  Instruction  Bytes
-------  -------  -----------  -----
00401000  55             PUSH EBP
00401001  8bec           MOV EBP,ESP
00401003  83ec10         SUB ESP,0x10
00401006  8b4108         MOV EAX,dword ptr [ECX + 0x8]
0040100a  89410c         MOV dword ptr [ECX + 0xc],EAX
0040100d  8b4110         MOV EAX,dword ptr [ECX + 0x10]
00401011  83c004         ADD EAX,0x4
00401014  894114         MOV dword ptr [ECX + 0x14],EAX
00401018  8b4508         MOV EAX,dword ptr [EBP + 0x8]
0040101c  85c0           TEST EAX,EAX
0040101e  7404           JZ 0x00401024
00401020  8b4108         MOV EAX,dword ptr [ECX + 0x8]
00401023  89450c         MOV dword ptr [EBP + 0xc],EAX
00401026  89ec           MOV ESP,EBP
00401028  5d             POP EBP
00401029  c3             RET
```
`16c` AT&T, `att_text`:
```
push %ebp
mov %esp,%ebp
sub $0x10,%esp
mov 0x8(%ecx),%eax
mov %eax,0xc(%ecx)
mov 0x10(%ecx),%eax
add $0x4,%eax
mov %eax,0x14(%ecx)
mov 0x8(%ebp),%eax
test %eax,%eax
je 0x00401024
mov 0x8(%ecx),%eax
mov %eax,0xc(%ebp)
mov %ebp,%esp
pop %ebp
ret
```
`16d` the JSON instruction list, `json_instruction_list`.

The test asserts the four records are **equal after removing `input.layout`
and `input.sha256`**, and that all four `input.layout` values are distinct and
correctly labelled. This is the regression guard for the adapter.

---
#### 17 `stdcall_ret_6` — Part B, non-dword `ret`

```
PUSH EBP
MOV EBP,ESP
MOV EAX,dword ptr [EBP + 0x8]
MOV ESP,EBP
POP EBP
RET 0x6
```

`verdict="ABI_UNKNOWN"`,
`abstain_reasons=["contradictory_cleanup"]`,
`contradictions=[{"kind":"ret_immediate_not_dword_multiple","detail":"RET 0x6","based_on":["O7"]}]`,
`stack_cleanup={"mode":"UNKNOWN","bytes":null}`,
`stack_arguments` **absent** (a 6-byte callee cleanup cannot be a whole number
of 4-byte slots). This is the explicit "not silently accepted" case.

---
#### 18 `argless_x87_return` — the real `0x00d2e350` shape

```
FLD float ptr [0x0169e398]
RET
```

`verdict="ABI_UNKNOWN"`,
`abstain_reasons=["argless_cdecl_stdcall_indistinguishable"]`.
`EXPAND`: `return_kind="x87_st0"` `SUPPORTED`;
`stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`.
Pins that an x87 return is recognised while the convention is still refused.

---
#### 19 `receiver_spilled_to_frame_slot` — the real `0x004bdc00` shape

```
PUSH EBP
MOV EBP,ESP
SUB ESP,0x8
MOV dword ptr [EBP + -0x8],ECX
MOV EAX,dword ptr [0x016f2618]
MOV ECX,dword ptr FS:[0x2c]
MOV EDX,dword ptr [ECX + EAX*0x4]
MOV EAX,dword ptr [EBP + -0x8]
MOV dword ptr [EDX + 0x4],EAX
MOV ECX,dword ptr [EBP + 0x8]
PUSH ECX
MOV EDX,dword ptr [EBP + -0x8]
MOV EAX,dword ptr [EDX + 0x3a9c]
PUSH EAX
CALL 0x00903400
ADD ESP,0x8
MOV dword ptr [EBP + -0x4],EAX
MOV ESP,EBP
POP EBP
RET 0x4
```

`verdict="__thiscall"`, `confidence="SUPPORTED"` (arg count downgraded one
level by the `FS:` segment access, receiver unaffected).
`EXPAND`: `receiver={"register":"ECX","member_offsets":[15004],"via":"frame_slot EBP-0x8"}`
`SUPPORTED` — note the offset `0x3a9c` = 15004, which **exceeds**
`PLAUSIBLE_MEMBER_MAX`; the test pins that a receiver recovered through a
*spill slot* is not subject to the plausibility gate, because the gate exists
to filter coincidental `[ECX+d]` reads, and here ECX is provably reloaded from
its own spill. `stack_arguments=[{1,"EBP+0x08"}]` `WEAK`;
`stack_cleanup={"mode":"callee","bytes":4}` `SUPPORTED`;
`return_kind="pointer_like"` `SUPPORTED` (EAX is the `CALL` result, base
unproven ⇒ `WEAK`, `"return_type"` in `unknowns`);
observation `segment_access{segment:"FS",offset:"0x2c"}`.

---
#### 20 `ecx_loaded_from_stack_slot` — the real `0x00593960` / `0x005291f0` trap

```
MOV EAX,dword ptr [ESP + 0x8]
MOV ECX,dword ptr [ESP + 0xc]
MOV EDX,dword ptr [ESP + 0x10]
MOV dword ptr [ECX],EAX
MOV EAX,dword ptr [ESP + 0x4]
MOV dword ptr [EDX],EAX
RET
```

`verdict="__cdecl"`, `confidence="PASS"`.
`EXPAND`: `calling_convention="__cdecl"` `PASS`;
`stack_arguments=[{1,"ESP+0x04"},{2,"ESP+0x08"},{3,"ESP+0x0c"},{4,"ESP+0x10"}]`
`SUPPORTED`; `stack_cleanup={"mode":"caller","bytes":0}` `SUPPORTED`;
**no** `register_incoming_registers` claim, **no** `receiver` claim.
This is the most important negative control in the suite: both ECX and EDX are
used as store bases, so any engine that infers `__fastcall` from "ECX and EDX
appear" is wrong, and the real `0x00aea250` in the index is labelled
`__fastcall` — so this fixture also feeds a Part D conflict assertion.

---
#### 21 `sret_ecx_or_fastcall_ambiguous` — extra, the sharpest conservatism case

```
PUSH EBP
MOV EBP,ESP
SUB ESP,0x24
MOV dword ptr [EBP + -0x18],ECX
MOV EAX,dword ptr [EDX + 0x4]
MOV dword ptr [ECX],EAX
MOV EAX,dword ptr [EBP + 0x8]
MOV dword ptr [ECX + 0x4],EAX
MOV EAX,dword ptr [ECX + 0x8]
MOV ESP,EBP
POP EBP
RET 0x4
```

`verdict="ABI_UNKNOWN"`, `abstained=true`,
`abstain_reasons=["ecx_and_edx_indistinguishable"]`,
`ambiguities=[{"between":["__thiscall+hidden_return(ECX)","__fastcall"],"because":["O5","O7"]}]`.
`EXPAND` (all ≤ `WEAK` except cleanup): `register_incoming_registers=["ECX","EDX"]`
`SUPPORTED`; `hidden_return={"kind":"sret_candidate","register":"ECX","buffer_source":"register"}`
`WEAK`; `stack_cleanup={"mode":"callee","bytes":4}` `SUPPORTED`;
`stack_arguments=[{1,"EBP+0x08"}]` `WEAK`.

### 2.3 Determinism and ordering tests

* `test_infer_is_byte_identical_across_repeated_runs` — for every fixture,
  `sha256_json(infer(x))` identical over 5 runs and across a fresh interpreter
  subprocess (`subprocess.run([sys.executable, "-c", …])`).
* `test_record_is_canonical_json` — `record == json.loads(canonical_json(record))`
  for every fixture, i.e. keys sorted at every level.
* `test_observation_ids_are_dense_and_address_ordered`.
* `test_inference_ids_are_dense_and_in_fixed_claim_order`.
* `test_set_valued_fields_are_sorted` — `member_offsets`, `based_on`,
  `observed_offsets`, `stack_arguments` all ascending / positional.
* `test_inference_is_idempotent` — `infer(infer_parse(x))` deep-equals
  `infer(x)`.

---

## 3. Part B — property / invariant tests

Corpus: a fixed-seed generator plus 25 hand-written adversarial strings.
`FUZZ_SEED = 1234` is asserted as a module constant, because the repo forbids
nondeterminism (no `random` without a pinned seed, anywhere).

```python
FUZZ_SEED = 1234
GARBAGE_ALPHABET = "MOV PUSH RET CALL JMP 0x1EBPECXEDXESP[]+-, \n\t\r\x00�"

def fuzz_inputs(count=400):
    rng = random.Random(FUZZ_SEED)
    yield ""
    yield "   \n\n\t\r\n"
    yield "\x00\xff\xfe" * 64
    yield "A" * 1048576
    yield "RET 0xFFFFFFFF\n" * 32
    yield "PUSH EBP\n" * 10000
    yield "\r\n".join("MOV EAX,dword ptr [EBP + 0x%x]" % i for i in range(1000))
    for _ in range(count):
        yield "".join(rng.choice(GARBAGE_ALPHABET)
                      for _ in range(rng.randint(0, 400)))
```

Invariants, each a named test run over the *whole* corpus plus every fixture:

1. `test_property_every_inference_cites_a_real_observation_id` —
   `set(based_on) ⊆ {o.id for o in observations}`, and `len(based_on) >= 1`.
2. `test_property_unknown_verdict_has_no_pass_confidence_claim` —
   `verdict == "ABI_UNKNOWN" ⇒ no inference with confidence == "PASS"`.
   (Design rule, asserted in the same test: also none at `SUPPORTED` for any
   `claim == "calling_convention"`.)
3. `test_property_calling_convention_stays_inside_the_vocabulary` —
   `verdict ∈ CALLING_CONVENTIONS`; likewise cleanup / confidence / shape.
4. `test_property_engine_is_total_on_arbitrary_text` — no exception, ever;
   always a dict with `schema` and a `verdict`; runs over the fuzz corpus in a
   loop with `self.subTest(text=repr(text[:60]))`.
5. `test_property_stack_argument_widths_are_dword_multiples` —
   every `stack_arguments[i].width_bytes % 4 == 0`.
6. `test_property_non_dword_ret_immediate_is_a_contradiction` —
   any parsed `ret N` with `N % 4 != 0` forces a
   `ret_immediate_not_dword_multiple` contradiction **and** `cleanup="UNKNOWN"`.
7. `test_property_observations_and_inferences_are_independent_lists` —
   mutating `observations` cannot change `inferences[i].value`; only `based_on`
   membership changes. (Structural-separation assertion.)
8. `test_property_pass_confidence_is_unique` — at most one `PASS` inference per
   record, and it is always `calling_convention`.
9. `test_property_abstention_caps_every_confidence` — for each R8 gate present
   in `abstain_reasons`, all `inferences[*].confidence ∈ {"WEAK","UNKNOWN"}`
   except `stack_cleanup` and `register_incoming_registers`, which are pure
   machine facts.
10. `test_property_verdict_is_stable_across_five_runs` over the corpus.
11. `test_property_parse_is_layout_invariant` — the `plain_text`,
    `gcodebrowser_text`, `json_instruction_list` and `att_text` encodings of
    the same stream yield identical records modulo `input.layout`/`input.sha256`
    (also covered exhaustively by fixture 16).
12. `test_property_fuzz_corpus_is_reproducible` — the generator yields the
    same 400 strings on two runs (guards against an accidental unseeded
    `random` creeping in).

---

## 4. Part C — integration against real SporeApp.exe functions

All disassembly below was captured live from
`http://127.0.0.1:8089/disassemble_function?address=0x…` (GhidraMCP Headless
Server v7.0.0-headless) on the committed `SporeApp.exe` project
(`~/ghidra-spore-project/SporeProject`). The wire format is
`{"instructions":[{"address":"0040ccb0","instruction":"PUSH EBP"}, …],"count":N}`
— uppercase mnemonics, `dword ptr [EBP + 0x8]`, `dword ptr FS:[0x2c]`, no raw
bytes, no header. The same stream, rendered in the CodeBrowser text layout, is
the `16b` fixture.

### 4.1 The real functions and their expected verdicts

| # | VA | index name | expected verdict | why, from the actual disassembly |
|---|---|---|---|---|
| R1 | `0x0040ccb0` | `transform_pre_transform_by_0040ccb0` (`WAVE6-PRESENTATION`, abi `__thiscall observed`) | `__thiscall`, `PASS` | `PUSH EBP/MOV EBP,ESP/SUB ESP,0x48`; ECX spilled to `[EBP-0x48]` then loaded back and dereferenced at `+0x10`, `+0x14`, `+0x0`, `+0x2`, `+0x4` (≥2 distinct loads ⇒ R2); `[EBP+0x8]` read twice (`MOV EDX,[EBP+0x8]`, `MOV ECX,[EBP+0x8]`) ⇒ one stack arg; ends `MOV ESP,EBP/POP EBP/RET 0x4` ⇒ callee cleanup 4. Index claim matches, so the conflict list must be empty. |
| R2 | `0x005291f0` | `graphics_global_state_set_transform_005291f0` | `__cdecl`, `PASS` | `PUSH EBP/MOV EBP,ESP/AND ESP,0xfffffff0` (alignment, not a receiver); `[EBP+0x8]` and `[EBP+0xc]` read ⇒ 2 args; bare `RET` ⇒ caller cleanup. **Trap:** `MOV ECX,dword ptr [EBP + 0xc]` loads ECX *from a stack slot*, so ECX must **not** become a receiver. |
| R3 | `0x00951230` | stdcall stub (abi: `x86-32 stdcall with three caller arguments and callee cleanup`) | `__stdcall`, `PASS` | The entire function is `XOR AL,AL / RET 0xc` — no frame, no ECX, callee cleanup 12 ⇒ 3 words. Arg slots derive from the immediate (no `[EBP+d]` evidence exists). |
| R4 | `0x00ce6950` | `FUN_00ce6950` | `__thiscall`, `PASS` | `MOV EAX,dword ptr [ECX + 0x184] / RET`. One member load at `0x184` = 388 ≤ `0x1000` ⇒ plausible. Note: exactly **one** deref, which R2's "≥2 distinct" rule would reject — so the rule must read "≥2 distinct, **or** exactly 1 with `d ≤ 0x1000` on a frameless leaf". This is the boundary case; the test pins the amended rule and the *rationale* in the docstring. |
| R5 | `0x004bdc00` | `FUN_004bdc00` | `__thiscall`, `SUPPORTED` | Real disassembly quoted in full in fixture 19. `FS:[0x2c]` SEH walk; receiver spilled to `[EBP-0x8]` and reloaded for `[EDX+0x3a9c]`; `MOV ECX,dword ptr [EBP + 0x8]` is a stack-arg load, not a receiver; `RET 0x4` ⇒ callee cleanup. |
| R6 | `0x004ae250` | `Editors::EditorModel::SetColor` | `ABI_UNKNOWN`, `abstain_reasons=["ecx_read_never_dereferenced"]` | Full body: `PUSH EBP / MOV EBP,ESP / PUSH ECX / MOV dword ptr [EBP + -0x4],ECX / MOV ESP,EBP / POP EBP / RET`. ECX is stored and never dereferenced. **Bonus conflict:** the index claims `stack_cleanup_bytes: 16`, the body says caller cleanup. The conflict must be surfaced, not silently accepted. |
| R7 | `0x007e6080` | thiscall-shaped tail wrapper | `ABI_UNKNOWN`, `shape="thunk"`, `abstain_reasons=["tail_call_thunk_no_body"]` | The whole function is `JMP 0x00929bd0`, `count: 1`. `observations` = one `tail_jump`; `inferences` = **empty**. |
| R8 | `0x00de9fc0` | fastcall-style method (index label) | `ABI_UNKNOWN`, `abstain_reasons=["untrusted_frame_stack_reads"]` | 193 instructions. `SUB ESP,0x64 / PUSH EBP / PUSH ESI / PUSH EDI / XOR ESI,ESI / … / MOV EBP,ECX` — there is **no** `MOV EBP,ESP`, so R1 fails and EBP is a general register, not a frame pointer. All `[ESP + 0x…]` offsets are then uncalibrated. Also contains `MOV EDX,dword ptr [EAX + 0x38] / CALL EDX` (indirect dispatch) and a bare `RET`. Must abstain. |
| R9 | `0x00d2e350` | `Simulator_cCreatureGameData_GetEvolutionPoints` | `ABI_UNKNOWN`, `abstain_reasons=["argless_cdecl_stdcall_indistinguishable"]`, `return_kind="x87_st0"` | `FLD float ptr [0x0169e398] / RET`. Frameless, no ECX, bare `RET`, x87 return. |
| R10 | `0x005c65e0` | `FUN_005c65e0` | `ABI_UNKNOWN`, `abstain_reasons=["ecx_address_taken_without_memory_access"]` | `LEA EAX,[ECX + 0x3c] / RET`. An `LEA` is address arithmetic, not a dereference. The index calls it "fastcall-compatible one-argument ECX function". Must not be upgraded to a receiver. |
| R11 | `0x00aea250` | `FUN_00aea250` (index: `__fastcall`) | `__thiscall`, `PASS` **+ conflict** | `MOV EAX,ECX` then 30 `MOV dword ptr [EAX + off], …` stores at offsets `0,4,8,0xc,…,0x94` and `MOV byte ptr [EAX + 0x30],CL`, then `RET`. ECX is dereferenced at ≥2 plausible offsets ⇒ receiver. EDX is only ever *written* (`OR EDX,0xffffffff`, used as a store value) ⇒ not a register arg. So the persisted `__fastcall` label is contradicted; the engine's own observation stands and the conflict is recorded. |
| R12 | `0x00574590` | `FUN_00574590` | `__thiscall`, `SUPPORTED` | 18 instructions, two exits, both bare `RET` (no contradiction). `MOV ECX,dword ptr [ECX + 0x20] / MOV EAX,dword ptr [ECX] / MOV EDX,dword ptr [EAX + 0x50] / CALL EDX` — a two-level vtable chain, then `CALL EAX` on slot `0x38` and on slot `0xc` with `PUSH 0x29da727` and **no** `ADD ESP,4` before the `RET`. The engine must observe the vtable chain and the unbalanced push, must not resolve the callees, and must not infer this function's own convention from the uncalibrated push. |

Coverage check: detectable conventions = `__thiscall` (R1, R4, R5, R11, R12),
`__cdecl` (R2), `__stdcall` (R3) — seven functions. Legitimate abstentions =
R6, R7, R8, R9, R10 — five functions. `__fastcall` is deliberately **not**
claimed on any real function, because the only two real candidates
(`0x00aea250`, `0x00de9fc0`) are contradicted by their own bodies; that is the
finding, and the test asserts it.

`__fastcall` detection therefore stays hermetic-only (fixture 05), and the
suite carries an explicit `test_no_real_function_is_claimed_fastcall` that
asserts the 12 live VAs produce no `__fastcall` verdict.

### 4.2 The sret gap (documented, not papered over)

Three full-binary Ghidra scans (4,288+ functions each, executed live this
session) found **zero** MSVC sret constructors in `SporeApp.exe` under any of
these signatures: `LEA EAX,[EBP-n]` → `MOV ECX,EAX`; `LEA ECX,[EBP…]`/
`[ESP…]` with ECX store-only; `MOV EAX,[EBP+0x8]` → `MOV ECX,EAX` with
`RET imm`. sret is therefore covered by hermetic fixtures 02 and 21 only, and
`tests/capture_abi_golden.py --find-sret` re-runs the scan so the gap is
re-probeable rather than assumed.

### 4.3 Offline / replay integration (CI-safe)

Committed goldens:

```
tests/fixtures/abi/live/0040ccb0_transform_pre_transform.json
tests/fixtures/abi/live/005291f0_graphics_set_transform.json
tests/fixtures/abi/live/00951230_stdcall_stub_ret0c.json
tests/fixtures/abi/live/00ce6950_thiscall_member_0x184.json
tests/fixtures/abi/live/004bdc00_seh_spilled_receiver.json
tests/fixtures/abi/live/004ae250_ecx_never_dereferenced.json
tests/fixtures/abi/live/007e6080_naked_thunk.json
tests/fixtures/abi/live/00de9fc0_untrusted_frame.json
tests/fixtures/abi/live/00d2e350_x87_argless.json
tests/fixtures/abi/live/005c65e0_lea_from_ecx.json
tests/fixtures/abi/live/00aea250_thiscall_contradicts_fastcall.json
tests/fixtures/abi/live/00574590_vtable_chain_two_exits.json
tests/expected/abi/live/<same names>.json
```

Capture procedure — `tests/capture_abi_golden.py` (deliberately not
`test_*.py`, mirroring `tests/diff_real.py`):

```
python3 tests/capture_abi_golden.py --record     # needs the live bridge
python3 tests/capture_abi_golden.py              # verify goldens still match live
```

It reads the VA list from a module constant, GETs
`/disassemble_function?address=0x%08x`, writes the **verbatim** response body
to `tests/fixtures/abi/live/…` via a `write_if_identical` guard, then runs
`abi_infer.infer` and writes the record to `tests/expected/abi/live/…`.
It prints a one-line `RECORDED 12 fixtures` / `VERIFIED 12 fixtures` summary and
exits non-zero on any drift. Because the fixture is the raw response body, the
committed bytes *are* the provenance.

Replay test, inside the discovered suite: for each pair, read the committed
`.json`, feed it to `abi_infer.infer`, and `semantic_diff` against the committed
expected record — no Ghidra, no network.

---

## 5. Part D — evidence-pack and validator integration

New test file: `tests/test_abi_inference_evidence.py`, class
`AbiEvidenceIntegrationTest`. Hermetic; a stub client supplies disassembly.

### 5.1 Harness

`tests/abi_fixtures.py` (not `test_*`, mirroring `orchestration_fixture.py`)
provides:

* `AbiFakeClient` — same method set and `{"status":"ok", …}` shapes as
  `tests/mcp/test_ghidra.py::FakeClient`, plus
  `request(path, params)` serving `"/disassemble_function"` from an injected
  `{va: {"instructions": [...], "count": N}}` map and `OfflineDisassemblyClient`
  returning `{"status":"error","code":"ghidra_offline"}` for the negative case.
* `AbiGhidraBase(unittest.TestCase)` — `setUp`/`tearDown` copied verbatim from
  `GhidraTestBase` (temp `OPENSPORE_MCP_CACHE`, swap `gt._CLIENT_FACTORY`,
  clear `_FUNCTION_MEMO` / `_VTABLES_DOC` / `_DOSSIER_MOD`, `shutil.rmtree`),
  with a comment naming the mirrored source, exactly as
  `orchestration_fixture.sha256_file` names its mirror.
* `semantic_diff(expected, actual)` — copy of `tests/diff_real.py::semantic_diff`
  with a pointer comment.
* `make_root(tmp, targets)` — wraps `orchestration_fixture.build_root` +
  `synthetic_db`, then adds a `disassembly` map and a per-target
  `reconstruction/staging/<pkg>/<stem>.cpp` whose `__thiscall`/`__cdecl` token
  is controlled by the test.

### 5.2 Assertions

1. `test_collect_populates_abi_category_from_live_disassembly` — with
   `live=True` and a stubbed disassembly, `pack["categories"]["abi"]` has
   `availability == "available"`, `evidence_state == "DERIVED"`,
   `evidence_level == "SUPPORTED"`, and `value["verdict"] == "__thiscall"`.
2. `test_abi_category_provenance_is_derived_from_live` —
   `provenance == ["GhidraMCP /disassemble_function", "reconstruction/knowledge/index.json"]`,
   and the pack-level provenance contains
   `{"ref": "GhidraMCP /disassemble_function", "mode": "live", "source_class": "ghidra"}`.
3. `test_missing_sections_drops_abi_when_the_category_is_available` — build
   the context, then the briefing; assert `"ABI" not in briefing["evidence"]["missing_sections"]`
   and `briefing["abi"]["verdict"] == "__thiscall"`. This requires
   `context.build` `06_abi` to fall back to `categories["abi"]["value"]` when
   `record["abi"]` is empty (today it reads only the index record — line 88).
4. `test_no_disassembly_still_yields_abi_unknown_and_keeps_abi_missing` —
   `OfflineDisassemblyClient`; assert `categories["abi"]["availability"] ==
   "unavailable"`, `evidence_state == "MISSING"`, `evidence_level == "UNKNOWN"`,
   and `"ABI" in briefing["evidence"]["missing_sections"]` with the existing
   explanatory reason string.
5. `test_abi_record_lives_inside_the_existing_pack_schema` — assert
   `pack["schema"] == "openspore-evidence-pack-1"`, that no new top-level key
   appeared, and that no new file appeared under `reconstruction/`:
   `sorted(p.relative_to(root).as_posix() for p in root.rglob("*") if p.is_file())`
   equals the pre-call listing. This is the "no second ABI database" test.
6. `test_pack_content_sha256_is_stable_across_runs` — two `collect(live=True,
   write=False)` calls with the same stub ⇒ identical `content_sha256` and
   identical `canonical_json`. Extends the existing
   `test_evidence_pack_is_deterministic` shape from
   `tests/test_openspore_tooling.py:220`.
7. `test_evidence_pack_rejects_a_mutated_disassembly` — flip one instruction in
   the stub (`RET 0x4` → `RET`) and assert the ABI category's value changes and
   the conflict against the persisted record appears in `pack["conflicts"]`
   (reusing the `live_vs_persisted` shape already built at `evidence.py:297`).
   Specifically: stub R1's `RET 0x4` as `RET` and assert
   `{"kind": "live_vs_persisted", "field": "stack_cleanup_bytes"}` is present.

### 5.3 Validator ladder

New `validate` behaviour, one test per row, table-driven with `subTest`:

| engine verdict | source convention token | expected `checks["ABI"]` |
|---|---|---|
| `!= ABI_UNKNOWN` | matches | `PASS` |
| `!= ABI_UNKNOWN` | absent | `WARN`, detail `inferred convention is not confirmed by the target source span` |
| `!= ABI_UNKNOWN` | conflicts | `FAIL`, detail `source convention ['cdecl'] conflicts with inferred __thiscall` |
| `ABI_UNKNOWN` | matches | `WARN`, detail `engine abstained; source convention unconfirmed by binary evidence` |
| `ABI_UNKNOWN` | absent | `NOT_AVAILABLE`, coverage `none` |
| engine not run at all (no `disassembly` category) | any | byte-identical to today's output |

Test names: `test_abi_check_pass_requires_agreement`,
`test_abi_check_warns_when_source_does_not_confirm`,
`test_abi_check_fails_on_source_convention_conflict`,
`test_abi_check_warns_when_engine_abstained_but_source_agrees`,
`test_abi_check_is_not_available_when_engine_abstained_and_source_silent`,
`test_abi_check_is_unchanged_without_disassembly_evidence`.

The last row is the compatibility contract: with `disassembly` unavailable the
ABI check must produce exactly today's values, so the existing
`test_validation_reports_all_required_categories` and the whole
`tests/test_orchestration.py` suite (which stubs the validator) keep passing
untouched.

8. `test_aggregate_status_reflects_the_abi_row` — `FAIL` in the ABI row ⇒
   aggregate `FAIL`; `UNKNOWN` ⇒ `UNKNOWN`; else `WARN`/`PASS` per the existing
   precedence in `validate.py:238-249`.
9. `test_briefing_exposes_the_abi_record_to_the_worker` — the full
   `evidence → context → worker_contract.briefing` chain from a synthetic root:
   assert `briefing["abi"]["schema"] == "openspore-abi-inference-1"`,
   `briefing["abi"]["verdict"]`, and that
   `briefing["validation_requirements"]["required_categories"]` still contains
   `"ABI"` (it comes from context section 15, unchanged), and that
   `briefing["abi"]` is the *compacted* record, so the briefing
   `content_sha256` is stable across two runs.
10. `test_worker_result_round_trips_the_inferred_abi` — a synthetic worker
    result carrying `observed_original_abi` equal to the engine record parses
    through `worker_contract.parse_result` with
    `outcome == "STRUCTURAL_ONLY"` and the record intact (that field is already
    in `OPTIONAL_RESULT_FIELDS`, so no contract change is needed).
11. `test_index_abi_contradiction_is_reported_not_merged` — a synthetic root
    whose metadata record claims `__fastcall` for the `0x00aea250`-shaped body
    (fixture 20's text) must produce a `conflicts` entry, and the
    `categories["abi"]` value must be the engine's `__thiscall`, **not** the
    persisted `__fastcall`. Assert the persisted value is still reachable at
    `pack["record"]["abi"]["calling_convention"]` — nothing is overwritten.

---

## 6. Part E — execution plan

### 6.1 Files

| path | discovered? | needs Ghidra? |
|---|---|---|
| `tools/reconstruction_tooling/abi_infer.py` | — (product) | no |
| `tests/abi_fixtures.py` | no (helper) | no |
| `tests/fixtures/gen_abi_fixtures.py` | no (generator) | no |
| `tests/fixtures/abi/*.asm`, `*.att` | — (data) | no |
| `tests/fixtures/abi/live/*.json` | — (data) | no |
| `tests/expected/abi/*.json`, `live/*.json` | — (data) | no |
| `tests/test_abi_inference.py` | **yes** | no — hermetic |
| `tests/test_abi_inference_evidence.py` | **yes** | no — stubbed client |
| `tests/live_abi_inference.py` | no | **yes** |
| `tests/capture_abi_golden.py` | no | **yes** (record/verify) |

`tests/live_abi_inference.py` re-uses the `live_ghidra_reconstruction.py`
preamble verbatim, including its explanatory comment about `sys.path`.

### 6.2 Test functions

`tests/test_abi_inference.py` (hermetic, ~66 tests):

* `FixtureCorpusTest` — `test_every_fixture_matches_its_expected_record`
  (subTest per fixture, `semantic_diff`), `test_every_fixture_input_sha256_matches`
* `CanonicalThiscallTest` — `test_f01_canonical_thiscall_member`,
  `test_f01_receiver_member_offsets`
* `HiddenReturnTest` — `test_f02_stack_sret_buffer_is_thiscall`,
  `test_f02_return_type_is_left_unknown`,
  `test_f21_ecx_store_only_ambiguity_abstains`
* `CleanupTest` — `test_f03_cdecl_three_stack_args_caller_cleans`,
  `test_f04_stdcall_ret_0xc_callee_cleans`, `test_f10_contradictory_ret_immediates_downgrade_verdict`,
  `test_f17_ret_6_is_a_contradiction`
* `RegisterArgumentTest` — `test_f05_fastcall_ecx_and_edx_both_incoming`,
  `test_f06_ecx_read_never_dereferenced_abstains`,
  `test_f07_single_implausible_offset_abstains`,
  `test_f20_ecx_from_stack_slot_is_not_a_register_arg`
* `ShapeTest` — `test_f08_frameless_leaf_abstains`,
  `test_f09_naked_thunk_reports_no_inference`,
  `test_f11_vtable_slot_call_is_observed_not_resolved`,
  `test_f12_varargs_prologue_abstains`,
  `test_f18_argless_x87_return_abstains_on_convention_only`
* `ReturnKindTest` — `test_f13_pointer_like_return`,
  `test_f14_integral_return`, `test_f13_and_f14_never_conflate`
* `RobustnessTest` — `test_f15a_empty_input_abstains`,
  `test_f15b_whitespace_only_abstains`, `test_f15c_binary_noise_abstains`,
  `test_f15d_truncated_body_abstains`, `test_f15e_prose_abstains`
* `AdapterTest` — `test_f16_all_four_layouts_yield_one_verdict`,
  `test_f16_layouts_are_labelled_correctly`
* `SegmentAndSpillTest` — `test_f19_spilled_receiver_recovered_from_frame_slot`
* `DeterminismTest` — `test_infer_is_byte_identical_across_repeated_runs`,
  `test_infer_is_byte_identical_in_a_fresh_interpreter`,
  `test_record_is_canonical_json`, `test_observation_ids_are_dense_and_address_ordered`,
  `test_inference_ids_are_dense_and_in_fixed_claim_order`,
  `test_set_valued_fields_are_sorted`, `test_inference_is_idempotent`
* `PropertyTest` — the 12 `test_property_*` names from §3

`tests/test_abi_inference_evidence.py` (hermetic, stubbed, ~22 tests):
`test_collect_populates_abi_category_from_live_disassembly`,
`test_abi_category_provenance_is_derived_from_live`,
`test_missing_sections_drops_abi_when_the_category_is_available`,
`test_no_disassembly_still_yields_abi_unknown_and_keeps_abi_missing`,
`test_abi_record_lives_inside_the_existing_pack_schema`,
`test_pack_content_sha256_is_stable_across_runs`,
`test_evidence_pack_rejects_a_mutated_disassembly`,
`test_index_abi_contradiction_is_reported_not_merged`,
`test_abi_check_pass_requires_agreement`,
`test_abi_check_warns_when_source_does_not_confirm`,
`test_abi_check_fails_on_source_convention_conflict`,
`test_abi_check_warns_when_engine_abstained_but_source_agrees`,
`test_abi_check_is_not_available_when_engine_abstained_and_source_silent`,
`test_abi_check_is_unchanged_without_disassembly_evidence`,
`test_aggregate_status_reflects_the_abi_row`,
`test_briefing_exposes_the_abi_record_to_the_worker`,
`test_briefing_is_deterministic_with_the_abi_record`,
`test_worker_result_round_trips_the_inferred_abi`,
`test_replay_goldens_match_without_ghidra` (12 VAs, subTest each),
`test_replay_goldens_are_canonically_sorted`,
`test_no_real_function_is_claimed_fastcall` (12 VAs, subTest each)

`tests/live_abi_inference.py` (**live Ghidra**):
`test_live_disassembly_is_available_for_every_replay_va`,
`test_live_verdicts_match_the_committed_goldens`,
`test_live_pack_exposes_a_derived_abi_category`,
`test_live_abi_conflicts_are_surfaced_for_0x00aea250`,
`test_live_context_marks_section_06_abi_present`,
`test_live_briefing_drops_abi_from_missing_sections`,
`test_live_validator_abi_check_is_not_not_available`

### 6.3 Commands

Hermetic, no Ghidra:

```bash
python3 -m unittest tests.test_abi_inference -v
python3 -m unittest tests.test_abi_inference_evidence -v
python3 -m unittest tests.test_abi_inference tests.test_abi_inference_evidence -v
```

Regenerate / verify fixtures:

```bash
python3 tests/fixtures/gen_abi_fixtures.py            # fails loudly on byte drift
python3 tests/fixtures/gen_abi_fixtures.py --record   # re-record expected records
```

Live Ghidra (requires the documented headless bridge; see `AGENTS.md`):

```bash
curl -s 127.0.0.1:8089/check_connection
python3 -m unittest tests.live_abi_inference -v
python3 tests/capture_abi_golden.py            # verify goldens against live
python3 tests/capture_abi_golden.py --record   # re-record goldens
python3 tests/capture_abi_golden.py --find-sret
```

Existing suite must stay green (no edits to any existing file):

```bash
python3 -m unittest discover -s tests -t . -v
```

Full sweep in one line, hermetic only:

```bash
python3 -m unittest tests.test_abi_inference tests.test_abi_inference_evidence \
  tests.test_openspore_tooling tests.test_orchestration \
  tests.test_orchestration_scheduling -v
```

### 6.4 Implementation order

1. `abi_infer.py` skeleton: parse + record assembly only. Run
   `test_abi_inference.FixtureCorpusTest` with `--record` to materialise
   expectations; then hand-verify fixture 01 and 21 against §2.2.
2. `R0`-`R4` (parse, frame trust, receiver, args, cleanup) → fixtures
   01, 03, 04, 06, 07, 08, 10, 13, 14, 15, 17, 18, 20.
3. `R5`-`R6` (convention, sret) → 02, 05, 21.
4. `R7`-`R10` (return kind, gates, thunk, multi-exit) → 09, 11, 12, 19.
5. `DeterminismTest` + `PropertyTest`.
6. `evidence.collect` wiring → `test_abi_inference_evidence` rows 1-7, 11.
7. `context.build` `06_abi` fallback → rows 3, 4.
8. `validate` ladder → rows 8-10.
9. `capture_abi_golden.py` → goldens → `live_abi_inference.py`.

Step 8 is the only one that can regress existing tests; row
`test_abi_check_is_unchanged_without_disassembly_evidence` must pass *before*
the ladder is written, as the guard.
