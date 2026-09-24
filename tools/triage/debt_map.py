#!/usr/bin/env python3
"""Build the UNKNOWN debt map for the v5 triage snapshot (deterministic, stdlib only).

Reads the frozen v5 triage projection + the call-type xref edges and emits,
for every UNKNOWN row, connectivity + likely-ownership + a documented
evidence score with UNKNOWN-HIGH/MEDIUM/LOW tiers.

Thresholds (all absolute, no percentages):

Call-graph connectivity — distinct endpoints over CALL-TYPE edges only
(direct-call, thunk, external, computed-call; vtable-ref and data-ref are
reference edges, not call edges, and are excluded):
  isolated : in_degree == 0 and out_degree == 0
  low      : 1 <= max(in_degree, out_degree) <= 3
  high     : max(in_degree, out_degree) >= 4

Likely ownership (mutually exclusive, first match wins, documented order):
  gameplay_affinity  : >=1 call-type edge to a v5 GAMEPLAY_LOGIC row, or the
                       ghidra name starts with a rules.game_global_prefixes
                       prefix, or contains a documented game-class stem
                       (cStar, cPlanet, cEmpire, cScenario, cSpace,
                       cModelObject, cPlayer, cCreature, cTribe, cCiv).
  engine_runtime     : >=1 call-type edge to a v5 ENGINE_* row.
  third_party_hint   : import_families non-empty.
  genuinely_unknown  : none of the above.

Evidence score (integer sum):
  +2  in_degree  >= 8
  +1  4 <= in_degree <= 7
  +1  out_degree >= 8
  +2  gameplay_affinity
  +1  engine_runtime (when not gameplay)
  +1  scc_size  > 1
  +1  named (ghidra name is not FUN_*)
  +1  import_families non-empty

Tiers:  UNKNOWN-HIGH score >= 4 | UNKNOWN-MEDIUM 2..3 | UNKNOWN-LOW <= 1

Outputs:  <outdir>/debtmap-<snap8>.json
"""
import argparse
import csv
import hashlib
import json
import os
import sys
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(REPO, 'tools', 'triage'))
from classify import _row_cluster  # noqa: E402  (same partition rule as v5)

CALL_TYPES = ('direct-call', 'thunk', 'external', 'computed-call')
GAME_CLASS_STEMS = ('cStar', 'cPlanet', 'cEmpire', 'cScenario', 'cSpace',
                    'cModelObject', 'cPlayer', 'cCreature', 'cTribe', 'cCiv')
TIERS = ('HIGH', 'MEDIUM', 'LOW')


def load_triage(path):
    rows = []
    with open(path) as f:
        for line in f:
            line = line.strip()
            if line:
                rows.append(json.loads(line))
    return rows


def load_edges(path):
    ins = defaultdict(set)
    outs = defaultdict(set)
    with open(path, newline='') as f:
        for r in csv.DictReader(f, delimiter='\t'):
            if r['reference_type'] not in CALL_TYPES:
                continue
            c, cc = r['caller_va'], r['callee_va']
            if not cc.startswith(('EXT:', 'VT:')):
                ins[cc].add(c)
            outs[c].add(cc)
    return ins, outs


def named_game(name, prefixes):
    if any(name.startswith(p) for p in prefixes):
        return True
    return any(s in name for s in GAME_CLASS_STEMS)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--triage', default=os.path.join(REPO, 'knowledgegraph/triage/triage-f0e310e0.jsonl'))
    ap.add_argument('--xrefs', default=os.path.join(REPO, 'knowledgegraph/triage/xrefs-2540f2ca.tsv'))
    ap.add_argument('--rules', default=os.path.join(REPO, 'tools/triage/rules-v5.json'))
    ap.add_argument('--outdir', default=os.path.join(REPO, 'knowledgegraph/triage'))
    ap.add_argument('--snap8', default='f0e310e0')
    args = ap.parse_args()

    rows = load_triage(args.triage)
    rules = json.load(open(args.rules))
    prefixes = rules['game_global_prefixes']
    cat = {r['va']: r['category'] for r in rows}
    ins, outs = load_edges(args.xrefs)

    snap8 = None
    with open(args.triage) as f:
        first = json.loads(f.readline())
    snap8 = first.get('snapshot_sha256', args.snap8)[:8]

    by_cluster = defaultdict(int)
    by_conn = {'isolated': 0, 'low': 0, 'high': 0}
    by_own = {'gameplay_affinity': 0, 'engine_runtime': 0, 'third_party_hint': 0, 'genuinely_unknown': 0}
    tiers = {t: 0 for t in TIERS}
    detail = []
    list_gameplay = []
    list_engine = []
    list_decomp = []

    for r in rows:
        if r['category'] != 'UNKNOWN':
            continue
        va = r['va']
        i = len(ins.get(va, set()))
        o = len(outs.get(va, set()))
        neigh = ins.get(va, set()) | outs.get(va, set())
        named = not r['ghidra_name'].startswith('FUN_')

        game = any(cat.get(c) == 'GAMEPLAY_LOGIC' for c in neigh)
        engine = any(cat.get(c, '').startswith('ENGINE') for c in neigh)
        ga = game or named_game(r['ghidra_name'], prefixes)
        ea = engine and not ga
        ti = bool(r['import_families'])
        if ga:
            own = 'gameplay_affinity'
        elif ea:
            own = 'engine_runtime'
        elif ti:
            own = 'third_party_hint'
        else:
            own = 'genuinely_unknown'

        m = max(i, o)
        if m == 0:
            conn = 'isolated'
        elif m <= 3:
            conn = 'low'
        else:
            conn = 'high'

        score = 0
        if i >= 8:
            score += 2
        elif i >= 4:
            score += 1
        if o >= 8:
            score += 1
        if ga:
            score += 2
        if ea:
            score += 1
        if r['scc_size'] > 1:
            score += 1
        if named:
            score += 1
        if ti:
            score += 1
        tier = 'HIGH' if score >= 4 else ('MEDIUM' if score >= 2 else 'LOW')

        cl = _row_cluster(r)
        by_cluster[cl] += 1
        by_conn[conn] += 1
        by_own[own] += 1
        tiers[tier] += 1

        detail.append({
            'va': va, 'name': r['ghidra_name'], 'cluster': cl,
            'in_degree': i, 'out_degree': o, 'connectivity': conn,
            'ownership': own, 'scc_size': r['scc_size'], 'score': score,
            'tier': 'UNKNOWN-' + tier,
        })
        if ga:
            list_gameplay.append({'va': va, 'name': r['ghidra_name'], 'cluster': cl,
                                  'in_degree': i, 'out_degree': o, 'score': score, 'tier': 'UNKNOWN-' + tier})
        if ea:
            list_engine.append({'va': va, 'name': r['ghidra_name']})
        if tier == 'HIGH' and not r['decomp_path']:
            list_decomp.append({'va': va, 'name': r['ghidra_name'], 'cluster': cl,
                                'in_degree': i, 'out_degree': o, 'score': score, 'ownership': own})

    detail.sort(key=lambda x: (x['tier'], -x['score'], x['va']))
    list_gameplay.sort(key=lambda x: (x['tier'], -x['score'], x['va']))
    list_engine.sort(key=lambda x: x['va'])
    list_decomp.sort(key=lambda x: (-x['score'], x['va']))

    out = {
        'artifact': 'spore-debtmap-v1',
        'classifier_version': 5,
        'snapshot_sha256': first.get('snapshot_sha256'),
        'source': {
            'triage': os.path.relpath(args.triage, REPO),
            'xrefs': os.path.relpath(args.xrefs, REPO),
            'rules': os.path.relpath(args.rules, REPO),
        },
        'total_unknown': len(detail),
        'thresholds': {
            'connectivity': {
                'edge_types': list(CALL_TYPES),
                'isolated': 'in_degree == 0 and out_degree == 0',
                'low': '1 <= max(in_degree, out_degree) <= 3',
                'high': 'max(in_degree, out_degree) >= 4',
            },
            'ownership_order': ['gameplay_affinity', 'engine_runtime', 'third_party_hint', 'genuinely_unknown'],
            'game_class_stems': list(GAME_CLASS_STEMS),
            'score': {
                '+2': 'in_degree >= 8',
                '+1a': '4 <= in_degree <= 7',
                '+1b': 'out_degree >= 8',
                '+2g': 'gameplay_affinity',
                '+1e': 'engine_runtime (when not gameplay)',
                '+1s': 'scc_size > 1',
                '+1n': 'named (not FUN_*)',
                '+1i': 'import_families non-empty',
            },
            'tiers': {'UNKNOWN-HIGH': 'score >= 4', 'UNKNOWN-MEDIUM': '2 <= score <= 3', 'UNKNOWN-LOW': 'score <= 1'},
        },
        'by_cluster': dict(sorted(by_cluster.items())),
        'by_connectivity': by_conn,
        'by_ownership': by_own,
        'tiers': {f'UNKNOWN-{t}': tiers[t] for t in TIERS},
        'lists': {
            'high_gameplay_affinity': list_gameplay,
            'likely_engine_runtime': list_engine,
            'manual_decomp_required': list_decomp,
        },
        'rows': detail,
    }

    os.makedirs(args.outdir, exist_ok=True)
    path = os.path.join(args.outdir, f'debtmap-{snap8}.json')
    with open(path, 'w') as f:
        json.dump(out, f, indent=1, sort_keys=True)
        f.write('\n')
    sha = hashlib.sha256(open(path, 'rb').read()).hexdigest()
    print(json.dumps({
        'output': os.path.relpath(path, REPO),
        'sha256': sha,
        'total_unknown': out['total_unknown'],
        'by_connectivity': by_conn,
        'by_ownership': by_own,
        'tiers': out['tiers'],
        'list_sizes': {k: len(v) for k, v in out['lists'].items()},
    }, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
