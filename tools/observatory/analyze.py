#!/usr/bin/env python3
"""analyze.py — summarize a probe_tracer JSONL observation log (stdlib only).

Usage:
    python3 analyze.py <obs.jsonl> [--json]

Reports:
  * per-function event count, first-seen time, min + median inter-arrival interval
  * thread (tid) histogram
  * 1s-window rate spikes: any window whose event rate exceeds 3x the previous
    non-empty window's rate

Timestamps: each event carries "t" (CLOCK_MONOTONIC ns) and "rel" (ns since the
first event in that capture). All timing uses "rel" so captures are comparable.
"""
import json
import statistics
import sys


def load_events(path):
    events = []
    with open(path) as f:
        for lineno, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            try:
                e = json.loads(line)
            except json.JSONDecodeError as exc:
                print(f"warn: line {lineno}: skip bad JSON ({exc})", file=sys.stderr)
                continue
            if "name" not in e or "rel" not in e:
                print(f"warn: line {lineno}: skip (missing name/rel)", file=sys.stderr)
                continue
            events.append(e)
    events.sort(key=lambda e: e["rel"])
    return events


def per_function(events):
    stats = {}
    for e in events:
        s = stats.setdefault(e["name"], {"rels": [], "tids": set()})
        s["rels"].append(e["rel"])
        s["tids"].add(e.get("tid"))
    out = {}
    for name, s in stats.items():
        rels = sorted(s["rels"])
        if len(rels) >= 2:
            ivals = [b - a for a, b in zip(rels, rels[1:])]
            min_i = min(ivals)
            med_i = statistics.median(ivals)
        else:
            min_i = None
            med_i = None
        out[name] = {
            "count": len(rels),
            "first_rel_ns": rels[0],
            "min_interval_ns": min_i,
            "median_interval_ns": med_i,
            "tids": sorted(t for t in s["tids"] if t is not None),
        }
    return out


def thread_histogram(events):
    hist = {}
    for e in events:
        tid = e.get("tid", "?")
        hist[tid] = hist.get(tid, 0) + 1
    return hist


def rate_spikes(events, window_ns=1_000_000_000, factor=3.0):
    """1s windows over rel-time; report windows with count > factor * prev count."""
    if not events:
        return []
    t_end = events[-1]["rel"]
    nwin = int(t_end // window_ns) + 1
    counts = [0] * nwin
    for e in events:
        counts[int(e["rel"] // window_ns)] += 1
    spikes = []
    prev = None
    for i, c in enumerate(counts):
        if prev is not None and prev > 0 and c > factor * prev:
            spikes.append(
                {
                    "window": [i * window_ns, (i + 1) * window_ns],
                    "count": c,
                    "prev_count": prev,
                    "ratio": c / prev,
                }
            )
        if c > 0:
            prev = c
    return spikes


def fmt_ns(v):
    if v is None:
        return "-"
    if v >= 1_000_000_000:
        return f"{v / 1e9:.3f}s"
    if v >= 1_000_000:
        return f"{v / 1e6:.3f}ms"
    if v >= 1_000:
        return f"{v / 1e3:.1f}us"
    return f"{v}ns"


def main(argv):
    args = [a for a in argv if not a.startswith("-")]
    as_json = "--json" in argv
    if not args:
        print("usage: analyze.py <obs.jsonl> [--json]", file=sys.stderr)
        return 2
    events = load_events(args[0])
    funcs = per_function(events)
    hist = thread_histogram(events)
    spikes = rate_spikes(events)
    if as_json:
        print(json.dumps({
            "events": len(events),
            "functions": funcs,
            "threads": hist,
            "spikes": spikes,
        }, indent=2))
        return 0
    print(f"events: {len(events)}")
    print()
    print(f"{'function':32} {'count':>7} {'first':>10} {'min-ival':>10} {'med-ival':>10} tids")
    for name in sorted(funcs, key=lambda n: -funcs[n]["count"]):
        s = funcs[name]
        print(f"{name:32} {s['count']:7d} {fmt_ns(s['first_rel_ns']):>10} "
              f"{fmt_ns(s['min_interval_ns']):>10} {fmt_ns(s['median_interval_ns']):>10} "
              f"{','.join(map(str, s['tids']))}")
    print()
    print("threads:")
    for tid in sorted(hist, key=lambda t: -hist[t]):
        print(f"  tid={tid}: {hist[tid]}")
    print()
    if spikes:
        print("rate spikes (>3x vs previous non-empty 1s window):")
        for sp in spikes:
            lo, hi = sp["window"]
            print(f"  [{fmt_ns(lo)}-{fmt_ns(hi)}): {sp['count']} events "
                  f"(prev {sp['prev_count']}, {sp['ratio']:.1f}x)")
    else:
        print("rate spikes: none")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
