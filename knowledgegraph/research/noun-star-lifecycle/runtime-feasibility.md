# Noun/star lifecycle runtime feasibility

## Determination

- **Current environment:** technically capable of a human-gated, narrowly scoped WineDBG observation; **not safe or authorized for an unattended original-game run now**.
- **Existing observatory harness:** **insufficient**. `probe_tracer` can observe selected function entries, but it cannot sample the four global words, pair returns, or expose watchpoints. It also writes temporary `INT3` bytes into process memory, so it is not strictly process-memory-read-only.
- **WineDBG/GDB path:** technically feasible for stop-synchronized `x/1wx` reads at selected lifecycle breakpoints. Exact root-change detection requires hardware watchpoints or another debugger facility whose Wine remote-target support has not been verified here. Software breakpoints must be disclosed as process-memory writes.
- **Complete requested lifecycle experiment:** not currently established. Even with a debugger, manager-local noun/star lifecycles and mode boundaries are visible only if the relevant paths and a natural mode transition are reached. Historical boot/self-exit, registration/profile, and positive Cell reachability blockers remain applicable.
- **Runtime launched for this report:** no. No `SporeApp.exe` process was started or attached, no root word was sampled, and no manager, noun, star, or mode event was observed.

The four slots are the physically distinct noun alternate/canonical and star alternate/canonical observation words. Static evidence does not prove equality, publication, ownership, replacement, liveness, or unpublication (`knowledgegraph/research/noun-star-lifecycle.json:55-61`, `knowledgegraph/research/noun-star-lifecycle.json:275-303`). The proposed C1 experiment specifically requires timestamped values, owner/phase labels, and a natural mode entry/exit or teardown (`knowledgegraph/research/runtime-oracle/candidate-experiments.md:78-123`).

## Inspected capability

| Requirement | Existing `probe_tracer` | WineDBG/GDB | Result |
|---|---|---|---|
| Read four root words | No root-memory records; only selected registers at function entry | Can inspect memory while the inferior is stopped | Debugger can sample; harness cannot |
| Manager construction/teardown order | Arbitrary entry breakpoints, capped | Selected breakpoints plus stack context; return can be requested for a bounded call | Feasible only when paths execute |
| Noun/star create, materialization, invalidation, release | Can add function-entry probes, but no state sample or return pairing | Can stop at the bounded static surfaces and read roots | Potentially feasible; no current positive reachability |
| Mode boundary | Can add entry probes | Can stop at the concrete transition helper and listener | Requires a naturally reachable transition |
| Strictly no process-memory write | No: writes/replants `0xCC` and later restores it (`tools/observatory/probe_tracer.cpp:939-970`, `tools/observatory/probe_tracer.cpp:1042-1063`) | `x` reads are read-only; software `break` is not; hardware watchpoints/execpoints may be | No committed strict-read-only all-requirements harness exists |
| Exact root write observation | No watchpoints or store probes | Possible only if WineDBG/GDB reports usable hardware watchpoints; four x86 debug registers leave no hardware execute breakpoint when all four roots are watched | Unverified |

The tracer has useful module-host/reparenting support and bounded `INT3` tracing, but its event schema is entry-only and contains no memory snapshots, return frame, ESP/EFLAGS, or write provenance (`tools/observatory/probe_tracer.cpp:874-899`, `tools/observatory/probe_tracer.cpp:1033-1088`; `knowledgegraph/research/runtime-oracle/automation-audit.md:88-106`). Its output is opened only after breakpoints are planted, another reason it is not a fail-closed read-only memory oracle (`tools/observatory/probe_tracer.cpp:939-970`). No noun/star root, accessor, manager, or mode-boundary probe set exists under `tools/observatory/probes/`.

The runtime/oracle synthesis classifies the current tracer as `AVAILABLE_ENTRY_ONLY` and the memory/return oracle as missing (`knowledgegraph/research/runtime-oracle.json:190-209`, `knowledgegraph/research/runtime-oracle.json:300-305`). RE-02/C1 is proposed, human-only, and gated by a positive boot or an explicitly recorded boot investigation (`knowledgegraph/research/runtime-oracle.json:968-1003`).

## Runtime evidence — host environment preflight only

The following read-only, non-launching commands were run from the repository root:

```sh
set +e
for tool in wine wineserver winedbg gdb lldb x86_64-w64-mingw32-gdb i686-w64-mingw32-gdb strace; do command -v "$tool" || true; done
printenv DISPLAY || true
python3 tools/observatory/lock.py probe
pgrep -a -f 'SporeApp.exe|wineserver|wine64-preloader|wine-preloader' || true
stat -c '%n %s bytes %A' "SPORE/SporeBin/SporeApp.exe"
sha256sum "SPORE/SporeBin/SporeApp.exe"
wine --version
gdb --version
winedbg --help
ps -p 801929 -o pid=,ppid=,stat=,etimes=,comm=,args=
gdb -q -nx -batch -ex 'set architecture i386' -ex 'show architecture'
stat -c '%n %s bytes %y' "tools/observatory/probe_tracer" "tools/observatory/probe_tracer.cpp"
```

Observed results:

- `/usr/bin/wine`, `/usr/bin/wineserver`, `/usr/bin/winedbg`, `/usr/bin/gdb`, `/usr/bin/lldb`, and `/usr/bin/strace` are present.
- `DISPLAY=:0`.
- The OpenSpore machine lock reported `machine_locked: false`.
- `SPORE/SporeBin/SporeApp.exe` is 20,454,960 bytes and has SHA-256 `25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`, matching the committed identity.
- Wine is 11.17; GDB is 17.2 and accepts `i386` target architecture.
- PID 801929 is an already-running Proton CachyOS SLR `wineserver`, age 2259 seconds at the check. Its prefix and ownership were not inferred, and it was not killed. A fresh-prefix experiment may coexist, but any default-prefix `wineserver -k` requires operator coordination.
- `tools/observatory/probe_tracer` is dated 2026-09-21, while its source is dated 2026-09-24. The binary must not be treated as source-current without a reviewed rebuild.

**Interpretation limit:** this is runtime evidence only for host tool/display/identity/process availability. It is not evidence that WineDBG can set hardware watchpoints on the Wine target, that `SporeApp.exe` reaches any noun/star code, that the roots are mapped and readable, or that any lifecycle or mode transition occurred.

## Minimal experiment if approved

This is a **boot-only, no-input feasibility probe**. It can establish debugger attachment, module load bias, selected construction/teardown reachability, and stop-synchronized root reads if those paths execute. It cannot establish noun/star lifecycle or mode-boundary semantics unless a natural transition also becomes reachable.

### 1. Recheck immediately before launch

```sh
python3 tools/observatory/lock.py probe
sha256sum "$PWD/SPORE/SporeBin/SporeApp.exe"
pgrep -a -f 'SporeApp.exe|wineserver|wine64-preloader|wine-preloader' || true
```

Refuse the run if the hash differs, the lock is held, a user-owned Wine workload would be affected, or the operator has not approved use of `:0`.

### 2. Use an isolated prefix and inherited machine lock

```sh
RUN="$(mktemp -d /tmp/openspore-noun-star.XXXXXX)"
WINEPREFIX="$RUN/wineprefix"
python3 tools/observatory/lock.py acquire noun_star_lifecycle \
  --task-id "$RUN" -- \
  env WINEPREFIX="$WINEPREFIX" WINEDEBUG=-all \
  bash -c 'wineboot -u; wineserver -k; exec winedbg "$1"' \
  _ "$PWD/SPORE/SporeBin/SporeApp.exe"
```

Do not set `OPENSPORE_MCP_TRUSTED=1` from this report. A human operator may set trusted state only after explicit approval. The fresh prefix and all debugger output remain under `/tmp`; do not direct output into `SPORE/`, `tools/observatory/out/`, the canonical KG, or a worker-report directory.

### 3. Verify relocation before using linked addresses

At the initial WineDBG stop, run:

```text
info proc map
```

Resolve the `SporeApp.exe` load base `B`. For the linked addresses in this report, runtime addresses are:

```text
runtime = B + (linked - 0x00400000)
```

The commands below are valid only when `B == 0x00400000`, the historically observed layout. If `B` differs, recompute every address and record the formula; do not probe preferred-base addresses blindly.

### 4. Arm a bounded, state-read-only stop set

These are selected entry surfaces from the final static noun/star synthesis (`knowledgegraph/research/noun-star-lifecycle.json:404-443`, `knowledgegraph/research/noun-star-lifecycle.json:547-579`), not a claim that each will execute:

```text
break *0x00b60d80
break *0x00b232b0
break *0x00bae490
break *0x00b22440
break *0x00b237d0
break *0x00bb6390
break *0x00bb7250
break *0x007d85b0
break *0x00b63510
break *0x00b3d300
break *0x00b3d400
break *0x00b3d2a0
break *0x00b3d3a0
cont
```

At every selected stop, before resuming, record the stop address/context and all four raw words in this fixed order:

```text
x/1wx 0x0167eae0
x/1wx 0x0167eb60
x/1wx 0x0167eae4
x/1wx 0x0167eb0c
bt
cont
```

At one naturally reached noun or star constructor and one naturally reached teardown, `fin` may be used once to obtain a post-call sample; immediately repeat the four `x/1wx` commands before continuing. If return-to-caller behavior is ambiguous, record the sample as ambiguous rather than single-stepping broadly.

### 5. Detailed noun/star surfaces, only after the boot gate

Add only the selected surfaces needed for the naturally reached lifecycle:

```text
break *0x00b20c60
break *0x00b201a0
break *0x00b21340
break *0x00b225d0
break *0x00b20d30
break *0x00b22960
break *0x00bb5d80
break *0x00bb5b50
break *0x00baf130
break *0x00bb59b0
break *0x00c86760
break *0x00bb5640
break *0x00bb4af0
break *0x00bad7a0
break *0x01021300
break *0x01022460
```

Use the same four-root read at each stop. Do not infer root publication from manager construction, root unpublication from manager-local cleanup, or mode survival from a single frame.

### 6. Exact-write variant, conditional and currently unverified

After attaching through `winedbg --gdb`, first query the remote target:

```text
show can-use-hw-watchpoints
```

If hardware watchpoints are supported, a separate exact-change experiment may arm:

```text
watch -l *(unsigned int *)0x0167eae0
watch -l *(unsigned int *)0x0167eb60
watch -l *(unsigned int *)0x0167eae4
watch -l *(unsigned int *)0x0167eb0c
```

Do not combine four hardware data watchpoints with a claim of simultaneous hardware execution breakpoints on x86; there are only four architectural debug registers. If GDB falls back to software watchpoints, classify the run as debugger-modified rather than strictly read-only. This variant was not tested here and must not be claimed available from repository evidence.

## Safety and interpretation constraints

1. No root, manager, profile, save, or game-state writes; no hooks, patches, message injection, sentinel values, or forced transitions.
2. Do not dereference an opaque root merely because its bits resemble a pointer. Raw equality, null, change, and stale-window observations are permitted; object identity requires independent provenance.
3. Do not run `probe_tracer`, WineDBG, and GDB as concurrent ptrace owners on the same process or bytes.
4. Software breakpoints alter code bytes transiently. If “read-only” means zero process-memory writes, use only debugger attach-stop reads or verified hardware debug facilities and report the distinction explicitly.
5. Keep the breakpoint set bounded; no broad `strace`, instruction trace, payload dump, or full-process watchpoint sweep.
6. Use a disposable prefix, fixed short deadline, physical/operator stop, and a run directory under `/tmp`. Release the inherited lock on every exit and verify the disposable prefix's wineserver is gone.
7. Do not kill PID 801929 or any unknown Wine process without operator approval; use `WINEPREFIX="$WINEPREFIX" wineserver -k` for the isolated experiment.
8. A boot failure, clean exit, stall, missing root mapping, unreadable page, or absent breakpoint is a bounded negative only. It does not prove that a manager/root does not exist or that pairs are always unequal/equal.
9. A manager event without a root delta proves temporal order only. Root deltas without an identified owner/publication path do not establish aliasing or ownership.
10. A mode boundary requires the naturally reached transition helper/listener plus owner-qualified phase evidence. A screenshot, generic frame callback, or fixed navigation plan is not mode evidence.
11. The original noun/star compatibility blocker remains unresolved unless a complete natural publish/equal/replace/teardown matrix is captured. Save/load and allocator-reuse identity remain outside this minimal experiment.

## Final feasibility status

**Host capability: available. Existing harness coverage: insufficient. Strict read-only synchronous lifecycle coverage: not implemented. Human-gated boot sampling: conditionally feasible. Noun/star lifecycle and mode-boundary observation: blocked until a stable attributable original process and a natural transition are reached.**
