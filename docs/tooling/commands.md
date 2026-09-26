# Commands

All commands accept `--json` after the command and return one JSON document on stdout. Errors retain a nonzero exit code and a machine-readable error envelope.

## `frontier`

```bash
python3 tools/openspore.py frontier --json --limit 20
python3 tools/openspore.py frontier --unclaimed --dependency ready --runtime none
```

Filters: `--package`, `--subsystem`, `--status`, `--semantic`, `--dependency`, `--runtime`, `--claimed/--no-claimed`, `--unclaimed`, `--gameplay`, `--limit`, and `--offset`.

Each target contains score components, dependency endpoints, disposition, claim state, evidence references, and reason codes.

## `evidence`

```bash
python3 tools/openspore.py evidence 0x00e5b790
python3 tools/openspore.py evidence 0x00576c50 --json --no-write
python3 tools/openspore.py evidence 0x00e5b790 --live --json
```

Default output writes `reconstruction/evidence/<va8>/evidence.json` and `evidence.md`. `--no-write` keeps the operation ephemeral. Live failures are recorded as live attempts and do not become live evidence.

## `context`

```bash
python3 tools/openspore.py context 0x00e5b790 --json
```

The command writes `context.json` and `context.md` in the same evidence directory. The brief always includes all 15 sections, including explicit missing/conflicted states.

## `recover`

```bash
python3 tools/openspore.py recover 0x00576c50 --json
```

Recover is evidence → context → validation. It does not claim a target, alter source, or update replacement status. Rerunning replaces only deterministic generated artifacts for the same target.

## `validate`

```bash
python3 tools/openspore.py validate 0x00e5b790 --json
```

Validation reports `ABI`, `CALLS`, `GLOBALS`, `FIELDS/OFFSETS`, `CONSTANTS`, `CONTROL FLOW`, `VIRTUAL DISPATCH`, `RETURN SEMANTICS`, coverage, and unresolved questions. A static warning is not runtime validation.

## `integrate`

```bash
python3 tools/openspore.py integrate status --json
python3 tools/openspore.py integrate check --json
python3 tools/openspore.py integrate apply --json
```

`check` regenerates in memory and compares generated projections. `apply` writes through the existing atomic writer and is the only integrating command.

## `swarm`

```bash
python3 tools/openspore.py swarm --json --limit 5
python3 tools/openspore.py swarm --json --limit 5 --out /tmp/openspore-plan.json
```

Swarm emits only eligible targets with dependencies, evidence readiness, claimability, and reason codes. It does not launch OpenCode or acquire claims.

## `orchestrate`

```bash
python3 tools/openspore.py orchestrate plan --limit 5 --json
python3 tools/openspore.py orchestrate brief 0x008db310 --json --worker-id worker-7
python3 tools/openspore.py orchestrate run --limit 20 --worker "opencode run --print-logs" --worker-id orch-main
python3 tools/openspore.py orchestrate run --limit 20 --worker "opencode run --print-logs" --worker-id orch-main --dry-run
python3 tools/openspore.py orchestrate reap --json
python3 tools/openspore.py orchestrate reclaim 0x008db310 --worker-id recovery-1 --allow-stale
```

`plan` is read-only and returns the dispatch plan: every classified target with its scheduling role, and the dependency waves. `brief` assembles the worker package for one target without claiming it. `run` executes the pipeline, dispatching one worker per dispatchable unit, concurrently within a wave and in wave order across waves. `reap` lists active leases and decides nothing. `reclaim` takes over one named row whose lease has gone stale, and only with `--allow-stale`.

`--worker` is the worker command, split once with `shlex` and spawned without a shell; the briefing arrives on stdin and the result is read from stdout. `--worker-id` is the lease holder identity and is required for `run`. `--max-workers`, `--ttl`, `--timeout` and `--allow-stale` bound the run. `--dry-run` returns the plan without taking a lease.

## `claim`

```bash
python3 tools/openspore.py claim 0x008db310 --json --worker-id worker-7
python3 tools/openspore.py claim 0x008db310 --json --worker-id recovery-1 --ttl 1800 --allow-stale --allow-blocked
```

`claim` inserts the investigation row if the target has none, then takes an atomic lease through the canonical `queue_op`. The lease is `implementer_id` plus `updated_at`; the TTL is 1800 seconds by default with a floor of 60. A claim held by another worker is refused with `already_claimed` unless the lease is stale and `--allow-stale` was passed.

## `release`

```bash
python3 tools/openspore.py release 0x008db310 --json --worker-id worker-7
python3 tools/openspore.py release 0x008db310 --json --worker-id worker-7 --to blocked --reason validation_warn
```

`release` ends a lease without ending the investigation: the row returns to `queued`, or to `blocked` with the recorded reason. It is refused with `not_owner` when the caller is not the lease holder, because a lease is never taken by releasing it. Releasing a row that is not `active` is a success no-op, so a retried sequence converges.

## `worker-template`

```bash
python3 tools/openspore.py worker-template 0x008db310
```

Prints the `openspore-worker-result-1` skeleton with the six outcomes, the five validation verdicts, and the worker rules, so a worker never has to guess the field names. A natural-language final message is not parsed; the worker must emit exactly one JSON document on stdout.
