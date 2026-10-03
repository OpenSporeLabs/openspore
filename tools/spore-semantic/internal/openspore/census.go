package openspore

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"github.com/openspore/spore-semantic/internal/runtime"
	"github.com/openspore/spore-semantic/internal/semantic"
)

// This file projects OpenSpore's OWN static blocker statements into the census
// the runtime bridge reads. It adds a reader to this package and changes nothing
// about the existing exporters or the snapshot's bytes.
//
// Why a census exists at all: the static Passport carries a function's validation
// verdicts, but NOT the knowledge index's `blockers` prose or its
// `unresolved_questions`. Those sentences are the statements that actually
// describe the remaining ceilings -- "STATIC AGGREGATE IS NOT PASS: ABI is a WARN
// because the derived record's verdict is ABI_UNKNOWN ...". Projecting them into
// the Passport would change the snapshot's content_sha256, which consumers pin.
//
// It is a PROJECTION, not a derivation: nothing is inferred, classified or
// scored. The census also deliberately does not reimplement the frontier.
// tools/reconstruction_tooling/frontier.py owns eligibility and scoring; the
// census has no opinion about either. `runtime frontier` classifies the list it
// is handed, and that list comes from the census or from explicit --va flags.

// RelPromotionMarkers is the glob the census reads promotion markers from.
// AGENTS.md records why the marker is the source of truth for "promoted" and the
// knowledge index is not: the index lags promotion by design, so 12 promoted VAs
// once sat outside the manifest and 2 more were gated behind them through the
// dependency path. The marker is the authoritative, self-maintaining record.
const RelPromotionMarkers = "src/reconstruction/*/promotion.json"

// RelCensusRel is the census's conventional path relative to the OpenSpore root.
const RelCensusRel = "knowledge/semantic/blocker-census-v1.json"

// BuildCensus projects reconstruction/knowledge/index.json plus the promotion
// markers into a census.
//
// Every record the index has is carried. A census that silently dropped records
// would make a later intersection unable to distinguish "this VA is not a blocker
// target" from "the census never looked at this VA", which is the difference
// between an empty report and a false one. Filtering is the caller's job, and is
// visible where it happens.
func BuildCensus(root string) (*runtime.Census, []Absent, []Digest, error) {
	idx, absent, digests, err := LoadIndex(root)
	if err != nil {
		return nil, absent, digests, err
	}
	promoted, promoCount, promoErr := promotedVAs(root)
	if promoErr != nil {
		// A census without promotion markers would report every promoted VA as
		// unreconstructed, which is exactly the manifest-lag bug the marker
		// exists to prevent. Hard failure, not a degradation.
		return nil, absent, digests, fmt.Errorf("promotion markers: %w", promoErr)
	}
	indexDigest := ""
	for _, d := range digests {
		if d.Path == RelIndex {
			indexDigest = d.SHA256
		}
	}

	c := &runtime.Census{
		Schema: runtime.CensusSchema,
		Binary: semantic.BinaryIdentity{
			SHA256:       idx.Binary.SHA256,
			ImageBase:    idx.Binary.ImageBase,
			Architecture: idx.Binary.Architecture,
			Program:      idx.Binary.Program,
			Version:      idx.Binary.Version,
		},
		Source: runtime.CensusSource{
			Index:            RelIndex,
			IndexSHA256:      indexDigest,
			PromotionMarkers: RelPromotionMarkers,
			PromotedCount:    promoCount,
			MarkerGlob:       RelPromotionMarkers,
		},
		Targets: make([]runtime.CensusTarget, 0, len(idx.Records)),
	}
	for key, rec := range idx.Records {
		if rec == nil {
			continue
		}
		t := runtime.CensusTarget{
			VA:                  canonicalVAOf(rec.VA, key),
			Name:                censusName(rec),
			Status:              orEmpty(rec.Status),
			Reconstructed:       rec.Reconstructed != nil && *rec.Reconstructed,
			EvidenceLevel:       rec.EvidenceLevel,
			RuntimeGated:        rec.RuntimeGated != nil && *rec.RuntimeGated,
			RuntimeValidated:    intOrZero(rec.RuntimeValidated),
			Blockers:            nonNilStrings(rec.Blockers),
			UnresolvedQuestions: nonNilStrings(rec.UnresolvedQuestions),
			RuntimeBlockReason:  []string{},
			Package:             rec.Package,
			Promoted:            promoted[stripVA(canonicalVAOf(rec.VA, key))],
		}
		if rec.Runtime != nil {
			t.RuntimeGates = nonNilStrings(rec.Runtime.Gates)
			t.RuntimeBlockReason = asStringList(rec.Runtime.BlockingReason)
		}
		if rec.Ownership != nil {
			t.Claimability = rec.Ownership.Claimability
		}
		if t.Name == "" {
			t.Name = t.VA
		}
		c.Targets = append(c.Targets, t)
	}
	sort.Slice(c.Targets, func(i, j int) bool { return c.Targets[i].VA < c.Targets[j].VA })
	return c, absent, digests, nil
}

// promotionDoc is the marker file's declared shape.
//
// Markers exist in TWO shapes in this repository and both are promoted:
// `openspore-promotion-1` carries a targets[] array, and the older
// `openspore-promotion-record-1` shape (the one reconstruction/evidence/<va8>/
// promotion.json uses) puts bare_va/va at the top level. Only the VA is read
// here; the reader supports both because a census that missed a promoted VA
// would put a closed target back on the frontier, which is the exact manifest-lag
// bug AGENTS.md documents.
type promotionDoc struct {
	Schema  string            `json:"schema"`
	VA      string            `json:"va"`
	BareVA  string            `json:"bare_va"`
	Package string            `json:"package"`
	Targets []promotionTarget `json:"targets"`
}

type promotionTarget struct {
	VA      string `json:"va"`
	BareVA  string `json:"bare_va"`
	Package string `json:"package"`
}

// promotedVAs reads the promotion markers under src/reconstruction/*/promotion.json.
//
// A marker that is unreadable or names no VA at all is a hard error: skipping one
// would put a promoted target back into the frontier, which is precisely the
// failure AGENTS.md documents.
func promotedVAs(root string) (map[string]bool, int, error) {
	pattern := filepath.Join(root, filepath.FromSlash(RelPromotionMarkers))
	paths, err := filepath.Glob(pattern)
	if err != nil {
		return nil, 0, err
	}
	out := map[string]bool{}
	for _, p := range paths {
		raw, err := os.ReadFile(p)
		if err != nil {
			return nil, 0, fmt.Errorf("%s: %w", p, err)
		}
		var doc promotionDoc
		if err := json.Unmarshal(raw, &doc); err != nil {
			return nil, 0, fmt.Errorf("%s: %w", p, err)
		}
		keys := make([]string, 0, 1+len(doc.Targets))
		if k := firstNonEmptyStr(doc.BareVA, stripVA(doc.VA)); k != "" {
			keys = append(keys, k)
		}
		for _, t := range doc.Targets {
			if k := firstNonEmptyStr(t.BareVA, stripVA(t.VA)); k != "" {
				keys = append(keys, k)
			}
		}
		if len(keys) == 0 {
			return nil, 0, fmt.Errorf("%s: promotion marker names no va (schema %q)", p, doc.Schema)
		}
		for _, k := range keys {
			out[k] = true
		}
	}
	return out, len(paths), nil
}

func firstNonEmptyStr(vals ...string) string {
	for _, v := range vals {
		if strings.TrimSpace(v) != "" {
			return strings.TrimSpace(v)
		}
	}
	return ""
}

// CensusDigest returns the digest a census should carry: SHA-256 over the
// canonical compact encoding of its target array.
//
// It is a function of the census CONTENT, not of the file's indentation, so it
// stays stable if the pretty-printer changes.
func CensusDigest(c *runtime.Census) (string, error) {
	sort.Slice(c.Targets, func(i, j int) bool { return c.Targets[i].VA < c.Targets[j].VA })
	if c.Targets == nil {
		c.Targets = []runtime.CensusTarget{}
	}
	canonical, err := json.Marshal(c.Targets)
	if err != nil {
		return "", err
	}
	sum := sha256.Sum256(canonical)
	return hex.EncodeToString(sum[:]), nil
}

func canonicalVAOf(recVA, key string) string {
	if strings.TrimSpace(recVA) != "" {
		return canonicalVA(recVA)
	}
	return canonicalVA(key)
}

// canonicalVA renders an address in the exchange's canonical "0x%08x" spelling.
// A key that will not parse keeps its own spelling rather than being dropped, so
// a census can carry the anomaly instead of hiding it.
func canonicalVA(raw string) string {
	a, err := semantic.ParseAddr(raw, 0)
	if err != nil {
		return strings.TrimSpace(raw)
	}
	return a.String()
}

func stripVA(raw string) string { return strings.TrimPrefix(strings.TrimSpace(raw), "0x") }

func censusName(r *IndexRecord) string {
	if r.NormalizedSymbol != nil && *r.NormalizedSymbol != "" {
		return *r.NormalizedSymbol
	}
	if r.Name != nil && *r.Name != "" {
		return *r.Name
	}
	return ""
}

func orEmpty(s *string) string {
	if s == nil {
		return ""
	}
	return *s
}

func intOrZero(p *int) int {
	if p == nil {
		return 0
	}
	return *p
}

// asStringList normalises index.json's runtime.blocking_reason, which is a string
// for 617 of 618 records and a LIST for one. The census states it as a list
// rather than dropping the odd record, because "one record has a different shape"
// is a fact about the source worth keeping rather than normalising away.
func asStringList(raw json.RawMessage) []string {
	if len(raw) == 0 || string(raw) == "null" {
		return []string{}
	}
	var one string
	if err := json.Unmarshal(raw, &one); err == nil {
		return []string{one}
	}
	var many []string
	if err := json.Unmarshal(raw, &many); err == nil {
		return many
	}
	return []string{string(raw)}
}
