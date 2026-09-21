# tools/replace/synthetic — inline-hook proof (32-bit, native)

Proves, end-to-end and headless, that an **in-process constructor can
patch a function's entry to `jmp` a replacement** — the exact mechanism
planned for replacing Spore functions (see `docs/REPLACEMENT-ABI.md`).

## What it is

A 32-bit **non-PIE** C binary (`gcc -m32 -O0 -fno-pie -no-pie`, base
`0x08048000`) with two functions:

- `orig(x)  → x*2`
- `replacement(x) → x*2 + 1000`, and sets `g_replacement_ran = 1`

`main` calls `orig(i)` 40× (with a `usleep` between calls so the
`probe_tracer` can observe each call) and prints the result of each.

`hooker.c` adds an `__attribute__((constructor))` that runs **before
main**: it `mprotect`s the code page RWX, overwrites `orig`'s first 5
bytes with `jmp replacement`, self-checks the readback, restores RX, and
saves the original bytes (so the hook is reversible).

## The one gotcha (and why)

- The `jmp` must be encoded `0xE9 <rel32>` (5 bytes). `0xEB` is
  `jmp rel8` (2 bytes) — using it with a 4-byte displacement jumps to the
  wrong place and corrupts execution.
- The page must be `mprotect`ed **RWX**, not just RW: the hooker runs
  from the same page it is patching; RW would de-execute it mid-patch
  (SIGSEGV).

## Evidence (`make test` → `RESULT: PASS`)

The `probe_tracer` (tools/observatory) is used for the **BEFORE** baseline
only; the **AFTER** case is run directly. Reason: the constructor's patch
and the tracer's INT3 both write the same bytes — they cannot coexist on
one address. The redirect is therefore proven by observable behavior.

```
== BEFORE: unhooked target ==
  stdout: first line: 'call  1: 2', last: 'replacement_ran=0'
  probe counts: {'orig': 40}
  [PASS] orig probe fires (calls reached orig)
  [PASS] replacement probe NEVER fires
  [PASS] output is x*2 (call 1 -> 2)
  [PASS] replacement_ran=0
== AFTER: hooked target (run directly; in-process patch) ==
  stdout: first line: 'call  1: 1002', last: 'replacement_ran=1'
  [PASS] output shifted +1000 (call 1 -> 1002)
  [PASS] replacement_ran=1 (replacement actually executed)
  [PASS] hook self-reported installed
RESULT: PASS
```

- BEFORE: 40 calls reach `orig`, zero reach `replacement`, output `x*2`,
  `replacement_ran=0`.
- AFTER: output is `x*2+1000` and `replacement_ran=1` — control was
  redirected to the replacement, which ran and changed the result.

## Build / run

```
make            # target, target_hooked, probes.json
make test       # headless before/after (needs tools/observatory/probe_tracer)
```

Files: `target.c` (functions+main), `hooker.c` (constructor patcher),
`gen_probes.sh` (probes.json from `nm`/`readelf`), `test_hook.py`
(assertions), `Makefile`.
