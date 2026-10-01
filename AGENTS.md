# AGENTS.md — OpenSpore

Rules and durable context for any agent (opencode) working in this repo.

## What this is
Clean-room, from-scratch C++ (C++17) reimplementation of *Spore* + expansions,
driven by a fully AI pipeline. **Never** commit proprietary EA code or assets.

## Hard rules (legal / ethics)
- No *Spore* assets, decompiled EA source, models, textures, sounds, scripts.
- Reimplement by analysis only (clean room). No DRM circumvention (use GOG).
- No trade secrets / leaked code. `SPORE/` is git-ignored — keep it that way.

## Knowledge-graph architecture (do NOT reinvent)
- **Analysis graph** = **Ghidra** (via `ghidra` MCP). Source of truth for
  functions/classes/structures/xrefs/decompilation. Spore-ModAPI SDK symbols live here.
- **Source graph** = **codegraph** (MCP). Indexes this C++ repo for navigation.
- **Shared memory** = **SQLite** at `knowledgegraph/spore.db` (see `kg.py`).
  Cross-tool results only: test outcomes, decisions, asset-format mappings.
- No Neo4j / no general graph DB.

## Environment (CachyOS / Arch — use `pacman`, NOT `apt`)
- Ghidra 12.1.2 at `/opt/ghidra`. **User profile is `ghidra_12.1.2_DEV`**
  (not `_PUBLIC`). GhidraMCP extension already deployed there.
- ghidra-mcp cloned at `~/apps/ghidra-mcp` (uv venv synced). Bridge → `127.0.0.1:8089`.
  The MCP server runs **headless** (no GUI):
  `GHIDRA_MCP_ALLOW_SCRIPTS=1 java -Xmx8g -Dghidra.home=/opt/ghidra \
     -classpath ~/.config/ghidra/ghidra_12.1.2_DEV/Extensions/GhidraMCP/lib/GhidraMCP-7.0.0.jar:$(find /opt/ghidra/Ghidra -name '*.jar' | tr '\n' ':') \
     com.xebyte.headless.GhidraMCPHeadlessServer --port 8089 --bind 127.0.0.1 --project /home/juanr/ghidra-spore-project`
  then verify with `curl 127.0.0.1:8089/check_connection`.
- Spore-ModAPI SDK at `~/apps/Spore-ModAPI`. GOG/digital build →
  `SDKtoGhidra/SporeGhidra_march2017.xml` (+ `GhidraScript/ImportSporeSDK.java`).
- Game (GOG, no DRM) at `./SPORE/`; main exe `SPORE/SporeBin/SporeApp.exe` (+ `SporebinEP1/`).
- codegraph installed via npm (global). `uv` at `~/.local/bin/uv`, `mvn` present.
- Ghidra headless project: `~/ghidra-spore-project/SporeProject` (imported SporeApp.exe).
  Rebuilt 2026-09-20 (original was corrupt; backup in `/tmp/opencode/ghidra/SporeProject.broken-backup/`).
  Full binary map: `docs/RECON-3.1.0.22.md`.

## Working with the game / analysis
- Headless import (defensive — use the committed script, NOT the upstream one):
  `/opt/ghidra/support/analyzeHeadless ~/ghidra-spore-project SporeProject \
     -import SPORE/SporeBin/SporeApp.exe \
     -scriptPath tools/ghidra \
     -postScript ImportSporeSDK.java ~/apps/Spore-ModAPI/SDKtoGhidra/SporeGhidra_march2017.xml`
  `tools/ghidra/ImportSporeSDK.java` is the defensive fork (try/catch per address; the
  upstream `~/apps/Spore-ModAPI` one aborts the symbol pass on the first non-function
  address). Result on 3.1.0.22: 1670/1671 functions named, 1895 structures.
- x86:LE:32 cspec is `windows` (Ghidra 12 has no `msvc:LE:32:msvc`).
- **SporeApp.exe has no MSVC RTTI** — class hierarchy only via vtable data + SDK
  structures. Vtable detection never ran headless (0 vtable labels); run a vtable
  pass before relying on class structure.
- `run_script_inline` compiles Java against the Ghidra 12 OSGi classpath — API renames
  that break common assumptions: `Symbol.getName()`/`getAddress()` (no
  `getPrimaryName`/`getPrimaryAddress`); `getSymbols(String)` returns `SymbolIterator`
  (no `SymbolType` overload); no for-each on `Function` (use
  `program.getInstructionIterator(setView)`); `AddressSetView.getMaxAddress()` (no
  `getEnd()`); no `AddressSpace.translateFromInteger`. Failed scripts accumulate as
  `McpInline_*.java` in `~/ghidra_scripts/` — delete them to stop build warnings.
- Query sidecar: `python3 knowledgegraph/kg.py <init|add-node|add-edge|query|neighbors|record-test|dump>`.

## Reference exports (two files, one run)
- `tools/ghidra/ExportXrefs.java` takes an **optional 8th param `outData`**. Without
  it the edge file is byte-for-byte what it always was; with it the same run also
  writes a data-reference sidecar. It is a *separate* file because
  `tools/triage/export_xrefs.py` proves on the edge file that every non-EXT/non-VT
  endpoint is in the pinned universe, and a data address is not.
- Edge: `knowledgegraph/triage/xrefs-2540f2ca.tsv` (223,704 rows).
  Canonicalize: `tools/triage/export_xrefs.py`.
- Sidecar: `knowledgegraph/triage/datarefs-2540f2ca.tsv` (157,633 rows).
  Canonicalize: `tools/triage/export_datarefs.py` (full-row dedupe key, NOT the
  edge file's triple — a read and a write of one address are two facts).
  Read by `tools/reconstruction_tooling/evidence_datarefs.py` for GLOBALS.
- Regenerate both: write `/tmp/opencode/xref-job/params.tsv` (the script's argless
  fallback) and run `ExportXrefs.java` through `ghidra_run_ghidra_script`. The
  `rangesTsv` column must be `<va8>\t<slot-count>`; `vtables.json`'s `slots` is a
  LIST, so `len()` it when converting.
- **The Ghidra DB drifts from the committed exports.** It now holds 83,820 live
  functions vs the 59,245 recorded at export time, so a re-export differs from
  `xrefs-2540f2ca.tsv` on its own (measured: 16 rows, from a body gap at
  `FUN_006ab120`). Always A/B an exporter change against a *same-DB* baseline,
  never against the committed file.

## Read-only exchange: `spore-semantic`
- `tools/spore-semantic/` is a standalone **Go 1.27.1** CLI, stdlib only (no
  `require` block), no network, no Python and no Ghidra at runtime. It is a
  *projection*, never a second source of truth: it copies facts from the
  artifacts listed in `docs/tooling/semantic-exchange.md` §1.1 with their
  provenance and derives **nothing**. Do not re-implement ABI inference,
  vftable detection or validation in it — if a fact is missing, it is missing.
- Export: `spore-semantic export --out knowledge/semantic/function-passport-v1.jsonl`
  (58,757 records, ~98 MB, ~1.0 s). Query: `lookup <VA>`, `lookup-symbol <NAME>`,
  `explain <VA>`, `stats`, `validate`; `--json` on each. Exit codes are stable
  (2 unknown function, 3 unknown symbol, 4 binary mismatch, 5 corrupt, 6 schema,
  7 unavailable, 8 ambiguous symbol). `OPENSPORE_REQUIRE_SHA` pins the binary;
  `OPENSPORE_ROOT` sets the checkout.
- JSON Lines: metadata on line 1, then one passport per line sorted ascending by
  `identity.canonical_va`. `metadata.content_sha256` covers the **record lines
  only**, so it is not self-referential. No timestamp, no PID, no absolute path.
  Two exports from the same state are byte-for-byte identical (tested).
- **Bare address digits are HEX everywhere in this repo**, and the CLI keeps
  that: decimal requires an explicit `dec:`/`0d` prefix and an RVA requires
  `rva:`. Reading `925050` as decimal would answer a different question
  silently. This is the AGENTS.md address-spelling trap in a new place.
- Optional fact groups are envelopes: `state: available|unavailable`,
  `evidence_level`, `evidence_state`, `provenance`, `value` (omitted when
  unavailable), and a **closed-vocabulary** `reason` code. An unavailable group
  is "we looked and found nothing", never a zero value and never a `false`.
  Inside `abi.receiver`, `present` is the *string* `"true"`/`"false"`/`"null"`
  and `"null"` is load-bearing (it makes `abi_infer` abstain).
- Interior VAs use the repo's existing rule
  (`reconstruction_knowledge.canonical_identity`: bisect on entries, then require
  `start <= a < start + size`), so padding resolves to nothing. Do not invent a
  second mapping algorithm.
- Consumers keep their own overlay keyed by `binary_sha256 + canonical_va` for
  runtime observations. Nothing in `spore-semantic` reads or writes it, and
  OpenSpore source is never imported as production code.
- Installed at `~/.local/bin/spore-semantic` (on PATH). Rebuild with
  `cd tools/spore-semantic && CGO_ENABLED=0 go build -trimpath -ldflags '-s -w' -o ~/.local/bin/spore-semantic ./cmd/spore-semantic`
  — `-trimpath`/`-ldflags` are cosmetic and do not change the exported bytes.
- Verify with `cd tools/spore-semantic && gofmt -l . && go vet ./... && go test ./...`.
  Docs: `docs/tooling/semantic-exchange.md`, `docs/tooling/semantic-exchange-consumer.md`.

## Build / test (once `src/` exists`)
- CMake + Clang/GCC. `mkdir -p build && cd build && cmake .. && make -j`.
- C++17, `clang-format` (modified Google), `fmt` for formatting.
- Differential tests run the original under Wine (11) as an oracle.
- `CTest` builds the 77 promoted model tests with `-m32`
  (`OPENSPORE_RECONSTRUCTION_M32=ON`). Pin the compiler:
  `cmake -DCMAKE_CXX_COMPILER=clang++` or `g++`. Six promoted packages currently
  fail clang-only on `-Wunused-variable`; they are pre-existing.

## Reusable traps (each cost real debugging time)
- **Address spelling must be canonicalised at every boundary.** A pack stores
  listing addresses bare (`00f9ff00`) while a decoded branch operand carries the
  prefix (`0x00f9ff00`). Comparing them as strings silently empties every set
  intersection. `evidence_returns._successors` had exactly this bug and it
  collapsed 0x00f9fef0's CFG to 8 of 112 instructions.
- **A duplicated literal is a bug waiting for the next edit.** `0x00f9fef0`'s
  model test sized its storage for 4 runs against 12 trials; the overrun clobbered
  a neighbouring table and the "guard band intact" check was the symptom.
- **Never subscript a vtable struct to reach a slot.** `table[1].slot1` advances
  by `sizeof(StateInterface)` — a WHOLE PAIR of slots — while `MOV EDX,[EAX+n]`
  advances by `n * kPointerSize`. They agree only at n == 0. `0x0068f9b0`'s body
  had exactly this bug: it read `table+0xC` where `MOV EDX,[EAX+0x4]` proves
  `table+0x4`. Reach a slot by BYTE displacement (`slot_at<kSlotIndex>(table)`),
  never by array subscript. The package header now says so.
- **A wrong offset that lands on a VALID neighbour is not caught by crashing.**
  That defect survived every case of `0x0068f9b0`'s test except one, because the
  fixture's two tables were adjacent and `plain+0xC` aliased `clobber+0x4`, a
  callable pointer. Put a *distinct, callable sentinel* immediately past the last
  modelled slot (or decoy values that differ at every candidate offset) so a wrong
  index is observable by VALUE. A crash is the weakest possible signal here.
- **A test defect and a reconstruction defect produce the same segfault.**
  `0x0068f9b0`'s prior investigation concluded "fixture bookkeeping"; it was
  actually the body. Reproduce with a minimal harness before attributing a crash
  to the test.
- **`evidence` WITHOUT `--live` overwrites a LIVE pack with a degraded one.**
  A plain `evidence <va>` silently drops `disassembly` (and everything that
  depends on it), turning 7 PASS checks into NOT_AVAILABLE while still exiting 0.
  Always use `recover <va> --live` before trusting a validation status.
- **The frontier's source of truth for "promoted" is the promotion marker, not
  the manifest.** `status_for` reads `body_status`/`integration_status` from the
  integrator-owned manifest, which lags promotion by design. 12 promoted VAs sat
  outside it and were re-offered, and 2 gated 4 more through the dependency path.
  Both are fixed by reading the markers via `build_gate.discover_packages` +
  `promotion_targets`. **Do not hand-write manifest state** — the marker is the
  authoritative, self-maintaining record.
- **Do NOT widen `evidence_dispatch.VIRTUAL_SOURCE_TOKENS` to a `slot\w*`
  pattern.** Measured: 40 promoted packages match a bare slot-ish identifier and
  25 of those have machine listings with NO indirect dispatch, so the
  `virtual_source and not sites -> FAIL` arm would fail 25 correct packages. The
  matches are `kReceiverSlot` (a receiver field), `PKG_..._THISCALL` (a convention
  macro) and `kStackArgumentSlots` (a stack-argument count) — none of which
  declares a vtable dispatch boundary. The token set is deliberately narrow.
- Python here is 3.14 with no system pytest: run the suite as
  `uv run --no-project --with pytest python3 -m pytest tests/ -q`.
- `test_agent_overlay` needs a real X display **and** the `Xlib` module. System
  `python3` has `Xlib`; the isolated `uv --no-project` env does not, so this one
  failure is ENVIRONMENTAL and provably passes under system Python. Report it as
  ENVIRONMENTAL, never as PASS. `test_stale_metadata_safety` and the two
  concurrency-isolation tests fail on this machine regardless of the change under
  test. Baseline is **1841 passed** (was 1771, then 1833), not the headline count.

## Genuine ceilings: do not "solve" these by inference
`0x0068f9b0` is CLOSED (promoted). The rest are machine properties, not defects:
- **`__thiscall` vs `__fastcall` is UNDECIDABLE** from one register argument and
  zero stack arguments — the two emit identical code. `0x01053db0`,
  `0x01053e00`, `0x00c70e00` and `0x00c71e30` all sit here, and the derived ABI
  record correctly abstains. Because `validate`'s ABI arm tests `ABI_UNKNOWN`
  *before* its "convention present in source" PASS arm, a genuinely ambiguous
  convention can never reach static PASS. **That ordering is correct policy, not a
  bug**: promoting an unproven ABI is worse than leaving it UNKNOWN.
- **A return width bounded only by a CALL result is undeterminable** by this
  listing. `0x00c70e00`, `0x00c71e30`, `0x00f9fef0`, `0x00f96840`. The callee's
  signature decides it, and that is another VA's evidence, which the dimension
  deliberately declines to read.
- `0x00fa5040`'s `LEA ESP,[ESP]` receiver/ESP heuristic stays rejected.

## Current status
See `docs/STATE.md` for Phase 0 completion and the next step (Phase 1).
