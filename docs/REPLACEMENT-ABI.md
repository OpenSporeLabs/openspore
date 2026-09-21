# REPLACEMENT-ABI — `Simulator::Cell::MovePlayerToMousePosition`

Contract for a clean-room **replacement** of the original
`MovePlayerToMousePosition`, installed via the in-process inline-hook
mechanism proven in `tools/replace/synthetic/` (Objective 36A).

Evidence vocabulary (see RECON appendix A):
`OBSERVED / VERIFIED / CONFIRMED / SUPPORTED / INFERRED / APPROXIMATION /
UNKNOWN`. Decompilation is **EVIDENCE-NOT-TRUTH**.

---

## 1. Target

| field | value | evidence |
|---|---|---|
| symbol | `Simulator::Cell::MovePlayerToMousePosition` | CONFIRMED (SDK march2017, `FUNCTION` line) |
| mangled name | UNKNOWN | not present in SDK XML (SDK stores demangled names) |
| linked VA | `0x00e5b790` | CONFIRMED (SDK `FUNCTION ADDRESS`) |
| file offset (SporeApp.exe 3.1.0.22) | `0xA5AB90` | VERIFIED (`0x00e5b790` − image-base delta; `.text` VMA `0x401000` @ file `0x400`) |
| return | `void` | CONFIRMED (SDK `RETURN_TYPE`) |
| params | `float deltaTime` (1 param, 4 bytes) | CONFIRMED (SDK `PARAMETER ORDINAL=0`) |
| calling convention | cdecl | INFERRED — no `CONVENTION` attribute in SDK; 32-bit Spore global functions are cdecl; single 4-byte arg is pushed on the stack |

### Entry bytes (VERIFIED — read from `SPORE/SporeBin/SporeApp.exe`)

```
offset 0xA5AB90:  a1 04 3c 6b 01  83 ec 38  83 b8 58 51 00
                  └──── 5 ──────┘  └── ...
```

Decode: `mov eax, [0x016b3c04]` (load `sCellGame`); `sub esp, 0x38`;
`cmp [eax+0x5158], 0` (the lock/paused early-out).

The **first 5 bytes** (`a1 04 3c 6b 01`) are one complete, self-contained
`mov` — a clean 5-byte hook boundary. Overwriting them with `jmp
replacement` (5-byte `0xE9 rel32`, see 36A) leaves the rest of the
function intact but unreachable; that is the intended seam.

## 2. Global state touched (all INFERRED field meanings; addresses VERIFIED from decompilation)

`Simulator::Cell::sCellGame` is a global at **`0x16b3c04`** (CONFIRMED,
SDK `SYMBOL`, `TYPE=GLOBAL`). It is the first thing the function loads.

| offset (from sCellGame) | role | evidence |
|---|---|---|
| `+0x5158` | lock/paused flag; non-zero ⇒ early return | INFERRED (decomp: `!= 0 → return`) |
| `+0x411c` | player entity index (passed to a pool-lookup `FUN_00b721d0`) | INFERRED (decomp) |
| `+0x5270` (`0x5190+0xe0`) | "moving" flag; set to 1 when a hit is registered | INFERRED (decomp) |

Plane constants (addresses VERIFIED, values **never read** → APPROXIMATION):
normal `DAT_015a7c40/44/48`, point `DAT_016b3c28/2c/30`.

## 3. Player entity layout (INFERRED — decompilation only)

The entity pointer is resolved at runtime from `sCellGame+0x411c`.

| offset (from player) | role | evidence |
|---|---|---|
| `+0x08 / +0x0c / +0x10` | **target** position X/Y/Z (ray∩plane hit) | INFERRED (decomp) |
| `+0x14 / +0x18 / +0x1c / +0x20` | orientation quaternion (face travel dir) | INFERRED (decomp) |
| `+0x4c / +0x50 / +0x54` | **current** position X/Y/Z (used for `target−current`) | INFERRED (decomp) |

## 4. Behavioral contract (what the function does — from decompilation)

1. If `sCellGame+0x5158 != 0` (locked/paused) → return.
2. Resolve the player entity from `sCellGame+0x411c`; if null → return.
3. Per-frame update `FUN_00e5b2e0(deltaTime)` + `FUN_00743b50()`.
4. Camera mode `FUN_00e4ce40()+0xd4`; UI-selection gating.
5. Get camera **origin + view ray** (`FUN_007c4900`, via ILightingWorld).
6. Intersect the ray with the movement plane:
   - `denom = dir·N`; if `denom == 0` → no hit.
   - `t = −(origin·N + off)/denom`; if `t < 0` → no hit.
   - On hit: write `player+0x08/0c/10 = origin + dir·t` (target).
   - Set `sCellGame+0x5270 = 1` (moving).
   - `delta = −(target − current)`; compute orientation `FUN_0069b600`
     and write `player+0x14..0x20`.

**The ray∩plane hit is the movement TARGET; the player then turns to face
it.** (This is the steering model already used by `src/sim/Sim.cpp`, see
`docs/CELL-CONTRACT.md` / `replacement-status.json` →
`cell-sim-movement-interaction`.)

## 5. Replacement contract

A clean-room replacement `replacement(float deltaTime)` may be installed at
`0x00e5b790` iff it:

1. Takes the single cdecl `float deltaTime` from the stack (the caller frame
   is the original's — the hook is a `jmp`, so `esp`/arg layout is
   inherited unchanged).
2. Reads only the globals/fields in §2–§3 (by address) — it must NOT depend
   on any EA code.
3. Reproduces the observable effects in §4 (target+orientation written,
   moving flag set) using **our** plane constants and entity model.
4. Returns with the stack as found (`void` return; `esp` balanced).

It is then swapped in by patching the 5-byte entry to `jmp
replacement` (the 36A mechanism). The original bytes are preserved so the
hook is reversible.

## 6. Proven mechanism (Objective 36A)

`tools/replace/synthetic/` builds a 32-bit non-PIE `target` (+ `hooker.c`
constructor). The constructor `mprotect`s the code page RWX, overwrites the
first 5 bytes with `0xE9 rel32` → replacement, self-checks the readback,
restores RX, and saves the original bytes. Headless evidence
(`make test` → PASS):

- **BEFORE** (unhooked, traced): `orig` probe fires 40×, `replacement` 0×,
  output `x*2`, `replacement_ran=0`.
- **AFTER** (hooked, run directly): output `x*2+1000`,
  `replacement_ran=1`, hook self-reports installed.

The in-process patcher and the external `probe_tracer` **cannot both write
the same bytes** — the tracer's INT3 would be clobbered by the
constructor's patch. Hence the AFTER case is verified by behavior (stdout +
flag), not by re-tracing. See `tools/replace/synthetic/README.md`.

## 7. Status

- Hook mechanism: **VERIFIED** (36A, synthetic, headless).
- Target symbol/signature: **CONFIRMED** (SDK).
- Entry-byte hook boundary: **VERIFIED**.
- Field offsets / plane constants: **INFERRED / APPROXIMATION** — a
  cell-mode runtime trace (Wine) is required to promote them to VERIFIED
  before a real Spore replacement is considered `replaced-verified`.
