package runtime

import (
	"fmt"
	"sort"
	"strings"

	"github.com/openspore/spore-semantic/internal/index"
	"github.com/openspore/spore-semantic/internal/semantic"
)

// This file is the JOIN. It is the only place a static fact and a runtime fact
// appear in the same output, and it is written so that the two can never be
// confused:
//
//   - nothing here mutates a Passport, an ABI record, a validation verdict or a
//     promotion marker. There is no code path from a RuntimeObservation to any
//     of them, and none is added here;
//   - every static blocker is read from an artifact OpenSpore already wrote
//     (a validation dimension, a derived ABI verdict, the knowledge index's own
//     blocker prose). None is recomputed, and none is invented;
//   - every runtime fact is copied from the overlay with the producer's own
//     provenance attached;
//   - "the runtime evidence is relevant to this blocker" is a statement about
//     which OBSERVATION CATEGORIES the overlay contains. It is not a claim that
//     the observation resolves the blocker, and no field in this file says it
//     does.

// ResolutionClass is the closed vocabulary `runtime frontier` classifies each
// target with. It answers "what would a human do next", never "what is true".
const (
	// ResolutionAlreadyClosed: OpenSpore has already promoted a package for this
	// VA. Runtime evidence is interesting but changes nothing about the verdict.
	ResolutionAlreadyClosed = "already_reconstructed"
	// ResolutionEvidenceCandidate: the overlay carries observations in
	// categories the static blocker is sensitive to. This is the state worth a
	// focused static investigation -- and it is a PRIORITISATION signal only.
	ResolutionEvidenceCandidate = "runtime_evidence_relevant"
	// ResolutionReachedOnly: the address was reached, but the overlay records
	// nothing in a relevant category. The missing evidence is not what this
	// producer run collected.
	ResolutionReachedOnly = "reached_without_relevant_observation"
	// ResolutionNotReached: the overlay says nothing about this address.
	ResolutionNotReached = "not_reached"
	// ResolutionRuntimeOnly: the producer reached an address OpenSpore cannot
	// place in its function universe. This needs a STATIC IDENTITY
	// investigation, not a blocker resolution: the question is whether the
	// address is a function at all.
	ResolutionRuntimeOnly = "runtime_only_address"
	// ResolutionNoBlocker: the target carries no static blocker statement, so
	// there is nothing for runtime evidence to bear on.
	ResolutionNoBlocker = "no_static_blocker"
)

// ResolutionClasses lists the vocabulary in declaration order.
var ResolutionClasses = []string{
	ResolutionAlreadyClosed, ResolutionEvidenceCandidate, ResolutionReachedOnly,
	ResolutionNotReached, ResolutionRuntimeOnly, ResolutionNoBlocker,
}

// KnownResolutionClass reports whether s is a member of the vocabulary.
func KnownResolutionClass(s string) bool {
	for _, v := range ResolutionClasses {
		if v == s {
			return true
		}
	}
	return false
}

// blockerRelevance declares which runtime observation categories bear on which
// static validation dimension.
//
// It is a CLOSED table written here, in the consumer, and it encodes no
// conclusion. Its only claim is the structural one: a stack observation is
// evidence of the sort of thing a RETURN SEMANTICS dimension asks about, and a
// virtual-dispatch observation is not. Whether an observation actually settles a
// dimension is decided by a human, against the overlay and the machine evidence
// together, with the same proof/falsifier discipline as any other inference.
//
// A dimension absent from the table yields no relevance at all rather than a
// default "unknown relevance": an unrecognised dimension name is a vocabulary
// this build does not implement, and defaulting it would quietly claim coverage.
var blockerRelevance = map[string][]ObservationKind{
	"ABI":               {ObsCall, ObsIndirectCall, ObsStack, ObsReturn, ObsRegister},
	"RETURN SEMANTICS":  {ObsReturn, ObsStack, ObsRegister},
	"CALLS":             {ObsCall, ObsIndirectCall, ObsImport},
	"VIRTUAL DISPATCH":  {ObsIndirectCall},
	"GLOBALS":           {ObsMemory},
	"FIELDS/OFFSETS":    {ObsRegister, ObsMemory},
	"CONSTANTS":         {ObsMemory},
	"CONTROL FLOW":      {ObsCall, ObsIndirectCall, ObsException, ObsReturn},
	"EVIDENCE COVERAGE": {ObsEntry, ObsCall, ObsIndirectCall, ObsImport, ObsException, ObsMemory, ObsRegister, ObsStack},
}

// KnownValidationDimensions is the validation dimension vocabulary
// (tools/reconstruction_tooling/validate.py::STATIC_CHECKS plus its coverage
// check). It is listed here so a dimension this build has never heard of can be
// reported as unrecognised rather than silently given default relevance.
var KnownValidationDimensions = []string{
	"ABI", "CALLS", "GLOBALS", "FIELDS/OFFSETS", "CONSTANTS",
	"CONTROL FLOW", "VIRTUAL DISPATCH", "RETURN SEMANTICS", "EVIDENCE COVERAGE",
}

// blockerValidationStatuses are the statuses that mean "not settled". PASS is
// the only settled one; the rest are OpenSpore's own verdicts and are reproduced,
// not reinterpreted.
var blockerValidationStatuses = map[string]bool{
	"WARN": true, "FAIL": true, "UNKNOWN": true, "NOT_AVAILABLE": true,
}

// Blocker is one static reason a target is not closed, attributed to the
// artifact that stated it.
type Blocker struct {
	// Dimension is the validation dimension name, or "ABI_RECORD" for the
	// derived-record abstention and "INDEX" for the knowledge index's prose.
	Dimension string `json:"dimension"`
	Status    string `json:"status"`
	Detail    string `json:"detail"`
	Source    string `json:"source"`
}

// RuntimeSummary is the runtime half of a joined view: everything the producer
// said about one address, with no static content mixed in.
type RuntimeSummary struct {
	RequestedVA      string             `json:"requested_va"`
	CanonicalVA      *string            `json:"canonical_va"`
	Reached          semantic.TriBool   `json:"reached"`
	EntryCount       *int               `json:"entry_count"`
	FirstReachedFrom *string            `json:"first_reached_from"`
	MaxCallDepth     *int               `json:"max_call_depth"`
	RuntimeCallers   []RuntimeCaller    `json:"runtime_callers"`
	RuntimeTargets   []RuntimeTarget    `json:"runtime_targets"`
	RuntimeImports   []RuntimeImportRef `json:"runtime_imports"`
	ObservationKinds []ObservationKind  `json:"observation_kinds"`
	// Observations are the typed facts themselves, not just their categories: a
	// consumer reading a joined view needs the row, and a kind list would send it
	// back to the overlay for the part that actually matters.
	Observations     []Observation     `json:"observations"`
	ObservationCount int               `json:"observation_count"`
	ExceptionCount   int               `json:"exception_count"`
	Provenance       []ProvenanceEntry `json:"provenance"`
}

// StaticStatus names what OpenSpore's own artifacts say about an address. The
// values are deliberately the resolution-kind vocabulary, so "the runtime
// discovered an address the static universe cannot place" is a single
// unambiguous word rather than a sentence a reader has to interpret.
const (
	StaticStatusKnown         = "static_function_entry"
	StaticStatusInterior      = "static_interior_address"
	StaticStatusUnknownEntity = "static_non_function_entity"
	StaticStatusAbsent        = "no_static_identity"
)

// ResolveIdentity applies OpenSpore's canonical-identity rule to a requested VA
// and reports what it found, WITHOUT changing anything.
//
// When no snapshot is available the identity is reported as absent and the
// runtime half of the answer stands alone: a consumer with no static snapshot
// can still consume an overlay. That is why the snapshot is optional everywhere
// in this package.
func ResolveIdentity(ix *index.Index, va semantic.Addr) (canonicalVA *string, kind, status string, offset int, end semantic.Addr) {
	if ix == nil {
		return nil, CanonicalUnknown, StaticStatusAbsent, 0, 0
	}
	res := ix.Resolve(va)
	switch res.Kind {
	case index.KindExact:
		s := res.Passport.Identity.CanonicalVA
		return &s, CanonicalEntry, StaticStatusKnown, 0, 0
	case index.KindInterior:
		s := res.Passport.Identity.CanonicalVA
		return &s, CanonicalInterior, StaticStatusInterior, res.Offset, res.End
	default:
		return nil, CanonicalNonEntity, StaticStatusUnknownEntity, 0, 0
	}
}

// Summarize builds the runtime half of a joined view for one address.
func (o *Overlay) Summarize(va semantic.Addr) *RuntimeSummary {
	entries := o.EntriesFor(va)
	if len(entries) == 0 {
		return nil
	}
	// One address can carry several overlay entries (the exact one plus any
	// non-entry address whose producer claimed this canonical VA). They are
	// merged into one summary and every producer statement is preserved, because
	// hiding the extra entries would hide the fact that a producer saw a
	// non-entry address at all.
	out := &RuntimeSummary{
		RequestedVA:      semantic.Addr(va).String(),
		Reached:          TriNull,
		RuntimeCallers:   []RuntimeCaller{},
		RuntimeTargets:   []RuntimeTarget{},
		RuntimeImports:   []RuntimeImportRef{},
		ObservationKinds: []ObservationKind{},
		Observations:     []Observation{},
	}
	kinds := map[ObservationKind]bool{}
	var provs [][]ProvenanceEntry
	for _, e := range entries {
		out.CanonicalVA = e.CanonicalVA
		// reached is merged true-dominant, and a null tri-state NEVER becomes
		// true from an entry_count. A count says how many transfer edges touched
		// the address; it does not say the address was entered as a function, and
		// promoting one to the other is exactly the inference this package
		// refuses to make.
		switch e.Reached {
		case TriTrue:
			out.Reached = TriTrue
		case TriFalse:
			if out.Reached == TriNull {
				out.Reached = TriFalse
			}
		}
		if e.EntryCount != nil {
			if out.EntryCount == nil {
				out.EntryCount = Ptr(0)
			}
			*out.EntryCount += *e.EntryCount
		}
		if e.FirstReachedFrom != nil && out.FirstReachedFrom == nil {
			out.FirstReachedFrom = e.FirstReachedFrom
		}
		if e.MaxCallDepth != nil {
			out.MaxCallDepth = maxPtr(out.MaxCallDepth, *e.MaxCallDepth)
		}
		out.RuntimeCallers = append(out.RuntimeCallers, e.RuntimeCallers...)
		out.RuntimeTargets = append(out.RuntimeTargets, e.RuntimeTargets...)
		out.RuntimeImports = append(out.RuntimeImports, e.RuntimeImports...)
		out.ObservationCount += len(e.Observations)
		out.Observations = append(out.Observations, e.Observations...)
		for _, ob := range e.Observations {
			kinds[ob.Kind] = true
			if ob.Kind == ObsException {
				out.ExceptionCount++
			}
		}
		provs = append(provs, e.Provenance)
	}
	out.Provenance = MergeProvenance(provs...)
	out.RuntimeCallers = dedupeCallers(out.RuntimeCallers)
	sort.SliceStable(out.RuntimeCallers, func(i, j int) bool {
		a, b := out.RuntimeCallers[i], out.RuntimeCallers[j]
		if a.CallsiteVA != b.CallsiteVA {
			return a.CallsiteVA < b.CallsiteVA
		}
		return derefStr(a.CallerFunctionVA) < derefStr(b.CallerFunctionVA)
	})
	out.RuntimeTargets = dedupeTargets(out.RuntimeTargets)
	out.RuntimeImports = dedupeImports(out.RuntimeImports)
	out.Observations = dedupeObservations(out.Observations)
	sort.SliceStable(out.Observations, func(i, j int) bool {
		ki, kj := observationSortKey(&out.Observations[i]), observationSortKey(&out.Observations[j])
		if ki != kj {
			return ki < kj
		}
		return string(out.Observations[i].Kind) < string(out.Observations[j].Kind)
	})
	for k := range kinds {
		out.ObservationKinds = append(out.ObservationKinds, k)
	}
	sort.Slice(out.ObservationKinds, func(i, j int) bool { return out.ObservationKinds[i] < out.ObservationKinds[j] })
	return out
}

// KindsPresent returns the observation categories an entry recorded, which is
// what blockerRelevance is matched against.
func (e *Entry) KindsPresent() []ObservationKind {
	seen := map[ObservationKind]bool{}
	var out []ObservationKind
	for _, o := range e.Observations {
		if !seen[o.Kind] {
			seen[o.Kind] = true
			out = append(out, o.Kind)
		}
	}
	sort.Slice(out, func(i, j int) bool { return out[i] < out[j] })
	return out
}

// StaticBlockers reads the static reasons a passport is not closed, from the
// artifacts OpenSpore already wrote.
//
// Order matters for determinism only: the map in ValidationSummary.Coverage is
// unordered, so the result is sorted by dimension.
func StaticBlockers(p *semantic.Passport) []Blocker {
	if p == nil {
		return nil
	}
	var out []Blocker
	if p.Reconstruction.IsAvailable() {
		v := p.Reconstruction.Deref()
		if v.Validation != nil {
			dims := make([]string, 0, len(v.Validation.Coverage))
			for d := range v.Validation.Coverage {
				dims = append(dims, d)
			}
			sort.Strings(dims)
			for _, d := range dims {
				chk := v.Validation.Coverage[d]
				if blockerValidationStatuses[chk.Status] {
					out = append(out, Blocker{
						Dimension: d,
						Status:    chk.Status,
						Detail:    chk.Detail,
						Source:    "reconstruction/evidence validation.json",
					})
				}
			}
		}
	}
	// The derived ABI record's own abstention, when no validation report stated
	// an ABI verdict. It is a weaker signal than an adjudicated dimension and is
	// labelled as the derived record it is.
	if p.ABI.IsAvailable() && p.ABI.Deref().Verdict != nil && *p.ABI.Deref().Verdict == "ABI_UNKNOWN" {
		if !hasDimension(out, "ABI") {
			out = append(out, Blocker{
				Dimension: "ABI_RECORD",
				Status:    "UNKNOWN",
				Detail:    "the derived ABI record abstained: verdict ABI_UNKNOWN",
				Source:    "reconstruction/evidence abi_derived",
			})
		}
	}
	if v := p.Reconstruction.IsAvailable(); v {
		r := p.Reconstruction.Deref()
		if r.RuntimeGated != nil && *r.RuntimeGated {
			out = append(out, Blocker{
				Dimension: "RUNTIME",
				Status:    "GATED",
				Detail:    "the reconstruction is gated on a runtime observation that this repository has never had",
				Source:    "reconstruction/knowledge/index.json runtime_gated",
			})
		}
	}
	sort.SliceStable(out, func(i, j int) bool { return out[i].Dimension < out[j].Dimension })
	return out
}

func hasDimension(in []Blocker, dim string) bool {
	for _, b := range in {
		if b.Dimension == dim {
			return true
		}
	}
	return false
}

// Relevance reports whether an entry's recorded observation categories bear on a
// static blocker, and which categories were relevant.
//
// It returns false for a dimension absent from blockerRelevance. That is a real
// answer ("this build has no relevance model for that dimension"), not a
// default true.
func Relevance(blocker Blocker, entry *Entry) (bool, []ObservationKind) {
	wanted := blockerRelevance[blocker.Dimension]
	if len(wanted) == 0 || entry == nil {
		return false, nil
	}
	present := map[ObservationKind]bool{}
	for _, k := range entry.KindsPresent() {
		present[k] = true
	}
	var hits []ObservationKind
	for _, k := range wanted {
		if present[k] {
			hits = append(hits, k)
		}
	}
	sort.Slice(hits, func(i, j int) bool { return hits[i] < hits[j] })
	return len(hits) > 0, hits
}

// RelevantObservations returns, for one address and one blocker, the specific
// observations in relevant categories -- the rows a human would read.
func RelevantObservations(o *Overlay, va semantic.Addr, blocker Blocker) []Observation {
	wanted := blockerRelevance[blocker.Dimension]
	if len(wanted) == 0 {
		return nil
	}
	keep := map[ObservationKind]bool{}
	for _, k := range wanted {
		keep[k] = true
	}
	var out []Observation
	for _, e := range o.EntriesFor(va) {
		for _, ob := range e.Observations {
			if keep[ob.Kind] {
				out = append(out, ob)
			}
		}
	}
	sort.SliceStable(out, func(i, j int) bool {
		ki, kj := observationSortKey(&out[i]), observationSortKey(&out[j])
		if ki != kj {
			return ki < kj
		}
		return string(out[i].Kind) < string(out[j].Kind)
	})
	return out
}

// Interpretation is the compact human-readable reading of a joined view. It
// states a static blocker and the runtime facts beside it, and it ends with an
// explicit statement that nothing was concluded.
type Interpretation struct {
	StaticBlockers []string `json:"static_blockers"`
	RuntimeFacts   []string `json:"runtime_facts"`
	StaticStatus   string   `json:"static_status"`
	// VerdictUnchanged is always the literal "no static verdict was modified".
	// It is emitted on every joined view so a reader of the JSON cannot mistake
	// the join for an upgrade.
	VerdictUnchanged string `json:"verdict_unchanged"`
}

// Interpret builds the compact reading. It takes the blockers and the runtime
// summary as computed elsewhere so it stays a pure formatting function.
func Interpret(staticStatus string, blockers []Blocker, rt *RuntimeSummary, rel map[string][]ObservationKind) Interpretation {
	out := Interpretation{
		StaticStatus:     staticStatus,
		VerdictUnchanged: "no static verdict was modified",
	}
	for _, b := range blockers {
		line := fmt.Sprintf("%s %s: %s", b.Dimension, b.Status, b.Detail)
		if hits := rel[b.Dimension]; len(hits) > 0 {
			line += fmt.Sprintf("  [runtime observations relevant: %s]", kindList(hits))
		}
		out.StaticBlockers = append(out.StaticBlockers, line)
	}
	if out.StaticBlockers == nil {
		out.StaticBlockers = []string{}
	}
	if rt == nil {
		out.RuntimeFacts = []string{"the overlay records nothing for this address"}
		return out
	}
	fact := func(format string, args ...any) {
		out.RuntimeFacts = append(out.RuntimeFacts, fmt.Sprintf(format, args...))
	}
	fact("reached = %s", rt.Reached)
	if rt.EntryCount != nil {
		fact("entry_count = %d", *rt.EntryCount)
	} else {
		fact("entry_count = null (the producer did not count)")
	}
	if rt.MaxCallDepth != nil {
		fact("max_call_depth = %d", *rt.MaxCallDepth)
	}
	if rt.FirstReachedFrom != nil {
		fact("first_reached_from = %s", *rt.FirstReachedFrom)
	}
	if len(rt.RuntimeCallers) > 0 {
		fact("runtime callers = %s", callerList(rt.RuntimeCallers))
	}
	for _, t := range rt.RuntimeTargets {
		switch t.Indirect {
		case TriTrue:
			fact("indirect target = %s (unresolved=%s, %s)", t.TargetVA, t.Unresolved, t.Classification)
		case TriFalse:
			fact("direct target = %s", t.TargetVA)
		default:
			fact("target = %s (dispatch kind not established, %s)", t.TargetVA, t.Classification)
		}
	}
	for _, im := range rt.RuntimeImports {
		fact("import %s!%s slot=%s bound=%s (reached_count=%s)",
			im.Module, im.Symbol, derefStr(im.SlotVA), im.Bound, countText(im.ReachedCount))
	}
	if len(rt.ObservationKinds) > 0 {
		fact("observation kinds = %s", kindList(rt.ObservationKinds))
	}
	if rt.ExceptionCount > 0 {
		fact("exceptions = %d", rt.ExceptionCount)
	}
	for _, p := range rt.Provenance {
		fact("provenance: source_class=%s producer=%s artifact=%s", p.SourceClass, p.Producer, p.Artifact)
	}
	if out.RuntimeFacts == nil {
		out.RuntimeFacts = []string{}
	}
	return out
}

func kindList(in []ObservationKind) string {
	out := make([]string, 0, len(in))
	for _, k := range in {
		out = append(out, string(k))
	}
	return strings.Join(out, ", ")
}

func callerList(in []RuntimeCaller) string {
	out := make([]string, 0, len(in))
	for _, c := range in {
		s := c.CallsiteVA
		if c.CallerFunctionVA != nil {
			s = *c.CallerFunctionVA + "@" + s
		}
		if c.Count != nil {
			s += fmt.Sprintf(" x%d", *c.Count)
		}
		out = append(out, s)
	}
	return strings.Join(out, ", ")
}

func countText(p *int) string {
	if p == nil {
		return "null"
	}
	return fmt.Sprintf("%d", *p)
}

// ---- frontier -------------------------------------------------------------

// FrontierRow is one target of the runtime-assisted blocker report.
type FrontierRow struct {
	VA            string `json:"va"`
	Name          string `json:"name"`
	Reconstructed bool   `json:"reconstructed"`
	Promoted      bool   `json:"promoted"`
	RuntimeGated  bool   `json:"runtime_gated"`
	// Blockers is the static side: validation dimensions that are not PASS, an
	// abstaining derived ABI record, an open runtime gate, and (when a census was
	// supplied) the knowledge index's own blocker prose.
	Blockers []Blocker `json:"blockers"`
	// CensusProse is the knowledge index's verbatim blocker text and unresolved
	// questions, when a census was supplied. It is prose and is labelled as such;
	// it is never reduced to a code.
	CensusProse []string `json:"census_prose,omitempty"`
	// Runtime is null when the overlay records nothing for this address. It is
	// deliberately NOT a summary with reached=false: "not observed" and
	// "observed not reached" are different facts and only the producer can tell
	// them apart.
	Runtime *RuntimeSummary `json:"runtime"`
	// RelevantByDimension maps a blocker dimension to the observation categories
	// the overlay actually holds for it.
	RelevantByDimension map[string][]ObservationKind `json:"relevant_by_dimension,omitempty"`
	ResolutionClass     string                       `json:"resolution_class"`
	// NewStaticTaskJustified is a prioritisation answer, not a verdict change.
	NewStaticTaskJustified bool   `json:"new_static_task_justified"`
	Justification          string `json:"justification"`
}

// FrontierInput is one row to classify.
type FrontierInput struct {
	VA       semantic.Addr
	Name     string
	Blockers []Blocker
	// CensusProse carries the knowledge index's verbatim statements.
	CensusProse []string
	// Reconstructed and Promoted come from the census (promotion markers) or
	// from the snapshot's reconstruction block.
	Reconstructed bool
	Promoted      bool
	RuntimeGated  bool
	// HasStaticIdentity says whether OpenSpore can place this VA at all.
	HasStaticIdentity bool
}

// Frontier classifies each target against the overlay.
//
// It writes nothing. Every row is a reading of two artifacts that already exist,
// and the returned rows are ordered by VA so two runs against the same inputs
// produce identical output.
func Frontier(o *Overlay, inputs []FrontierInput) []FrontierRow {
	rows := make([]FrontierRow, 0, len(inputs))
	for _, in := range inputs {
		row := FrontierRow{
			VA:            in.VA.String(),
			Name:          in.Name,
			Reconstructed: in.Reconstructed,
			Promoted:      in.Promoted,
			RuntimeGated:  in.RuntimeGated,
			Blockers:      in.Blockers,
			CensusProse:   in.CensusProse,
			Runtime:       o.Summarize(in.VA),
		}
		if row.Blockers == nil {
			row.Blockers = []Blocker{}
		}
		class, justified, why := classify(o, in, &row)
		row.ResolutionClass = class
		row.NewStaticTaskJustified = justified
		row.Justification = why
		rows = append(rows, row)
	}
	sort.Slice(rows, func(i, j int) bool { return rows[i].VA < rows[j].VA })
	return rows
}

func classify(o *Overlay, in FrontierInput, row *FrontierRow) (string, bool, string) {
	relevant := map[string][]ObservationKind{}
	anyRelevant := false
	for _, b := range in.Blockers {
		var hits []ObservationKind
		for _, e := range o.EntriesFor(in.VA) {
			if ok, h := Relevance(b, e); ok {
				hits = append(hits, h...)
			}
		}
		sort.Slice(hits, func(i, j int) bool { return hits[i] < hits[j] })
		if len(hits) > 0 {
			relevant[b.Dimension] = dedupeKinds(hits)
			anyRelevant = true
		}
	}
	if len(relevant) > 0 {
		row.RelevantByDimension = relevant
	}

	switch {
	case row.Runtime == nil:
		if !in.HasStaticIdentity {
			return ResolutionNotReached, false,
				"OpenSpore has no static identity for this address and the overlay records nothing for it either"
		}
		if len(in.Blockers) == 0 && len(in.CensusProse) == 0 {
			return ResolutionNoBlocker, false, "no static blocker statement is recorded for this VA"
		}
		return ResolutionNotReached, false,
			"the overlay carries no entry for this VA, so no runtime evidence bears on any recorded blocker"
	case !in.HasStaticIdentity:
		return ResolutionRuntimeOnly, true,
			"runtime reached an address OpenSpore cannot place in its function universe; the open question is a STATIC IDENTITY one (is this a function entry at all), not a blocker resolution"
	case in.Promoted:
		return ResolutionAlreadyClosed, false,
			"a promotion record already exists for this VA; runtime evidence cannot change a promoted verdict"
	case anyRelevant:
		return ResolutionEvidenceCandidate, true,
			fmt.Sprintf("the overlay holds observations in %s, categories this build maps to at least one recorded blocker; a focused static investigation is justified, and nothing is decided here",
				kindList(flattenKinds(relevant)))
	case len(in.Blockers) == 0 && len(in.CensusProse) == 0:
		return ResolutionNoBlocker, false, "no static blocker statement is recorded for this VA"
	default:
		return ResolutionReachedOnly, false,
			"the address was reached, but the overlay records no observation category this build maps to a recorded blocker; the missing evidence is not what this producer run collected"
	}
}

func dedupeKinds(in []ObservationKind) []ObservationKind {
	seen := map[ObservationKind]bool{}
	var out []ObservationKind
	for _, k := range in {
		if !seen[k] {
			seen[k] = true
			out = append(out, k)
		}
	}
	sort.Slice(out, func(i, j int) bool { return out[i] < out[j] })
	return out
}

func flattenKinds(m map[string][]ObservationKind) []ObservationKind {
	var out []ObservationKind
	for _, v := range m {
		out = append(out, v...)
	}
	return dedupeKinds(out)
}

// ---- statistics -----------------------------------------------------------

// Stats are aggregate views over an overlay joined with a static snapshot. They
// are analysis, not new authoritative facts: every number here is a count of
// things two existing artifacts already say.
type Stats struct {
	Overlay struct {
		Entries           int `json:"entries"`
		Reached           int `json:"reached"`
		ReachedUnknown    int `json:"reached_unknown"`
		NotReached        int `json:"not_reached"`
		TotalEntryCount   int `json:"total_entry_count"`
		Observations      int `json:"observations"`
		Exceptions        int `json:"exceptions"`
		Imports           int `json:"imports"`
		UnresolvedTargets int `json:"unresolved_targets"`
		IndirectTargets   int `json:"indirect_targets"`
		DistinctProducers int `json:"distinct_producers"`
	} `json:"overlay"`
	// Joined counts are reported only when a snapshot was supplied; without one
	// they are null rather than zero, because "no snapshot" is not "none of
	// them".
	Joined *JoinedStats `json:"joined"`
}

// JoinedStats are the snapshot-dependent views.
type JoinedStats struct {
	// FunctionsIndexed is the snapshot's population, so the ratios below have a
	// stated denominator.
	FunctionsIndexed int      `json:"functions_indexed"`
	WithPassport     int      `json:"runtime_observed_with_static_passport"`
	RuntimeOnly      int      `json:"runtime_observed_absent_from_static_universe"`
	InteriorAddress  int      `json:"runtime_observed_interior_address"`
	Reconstructed    int      `json:"runtime_observed_statically_reconstructed"`
	Promoted         int      `json:"runtime_observed_promoted"`
	ABIUnknown       int      `json:"runtime_observed_abi_unknown"`
	ReturnUnknown    int      `json:"runtime_observed_return_semantics_unknown"`
	Renderware       int      `json:"runtime_observed_renderware"`
	WithBlockers     int      `json:"runtime_observed_with_static_blockers"`
	RuntimeOnlyList  []string `json:"runtime_only_addresses"`
}

// ComputeStats builds the aggregate views.
func ComputeStats(o *Overlay, ix *index.Index) Stats {
	var s Stats
	counts := o.Recount()
	s.Overlay.Entries = counts.Entries
	s.Overlay.Reached = counts.Reached
	s.Overlay.ReachedUnknown = counts.ReachedUnknown
	s.Overlay.NotReached = counts.NotReached
	s.Overlay.TotalEntryCount = counts.TotalEntryCount
	s.Overlay.Observations = counts.Observations
	s.Overlay.Exceptions = counts.Exceptions
	s.Overlay.Imports = counts.RuntimeImports
	s.Overlay.DistinctProducers = counts.DistinctProducer
	for _, addr := range o.Order {
		for _, t := range o.Entries[addr].RuntimeTargets {
			if t.Unresolved == TriTrue {
				s.Overlay.UnresolvedTargets++
			}
			if t.Indirect == TriTrue {
				s.Overlay.IndirectTargets++
			}
		}
	}
	if ix == nil {
		return s
	}
	j := &JoinedStats{FunctionsIndexed: ix.Len(), RuntimeOnlyList: []string{}}
	// Every count below is over DISTINCT FUNCTIONS, not distinct observation
	// addresses. One function observed at both its entry and an interior address
	// is one function; counting the interior separately would report a promoted
	// VA twice and inflate every ratio. The key is the resolved canonical VA, or
	// the requested VA when nothing resolves it (in which case two addresses that
	// resolve to nothing really are two distinct unknowns).
	counted := map[uint32]bool{}
	for _, addr := range o.Order {
		va := semantic.Addr(addr)
		res := ix.Resolve(va)
		key := uint32(va)
		if res.Passport != nil {
			if a, err := canonicalAddr(res.Passport.Identity.CanonicalVA); err == nil {
				key = uint32(a)
			}
		}
		if counted[key] {
			continue
		}
		counted[key] = true
		if res.Passport == nil {
			j.RuntimeOnly++
			j.RuntimeOnlyList = append(j.RuntimeOnlyList, va.String())
			continue
		}
		p := res.Passport
		j.WithPassport++
		// InteriorAddress counts functions whose observation set includes a
		// non-entry address that resolves INTO them, which is the interesting
		// case for a runtime-only lookup; the flag records that the first address
		// seen for this function was not its entry.
		if res.Kind == index.KindInterior {
			j.InteriorAddress++
		}
		if len(StaticBlockers(p)) > 0 {
			j.WithBlockers++
		}
		if p.Reconstruction.IsAvailable() {
			r := p.Reconstruction.Deref()
			if r.Reconstructed != nil && *r.Reconstructed {
				j.Reconstructed++
			}
			if r.Promoted == semantic.TriTrue {
				j.Promoted++
			}
		}
		if !p.ABI.IsAvailable() || p.ABI.Deref().Convention == nil {
			j.ABIUnknown++
		}
		if p.Reconstruction.IsAvailable() {
			if v := p.Reconstruction.Deref().Validation; v != nil {
				if chk, ok := v.Coverage["RETURN SEMANTICS"]; ok && chk.Status != "PASS" {
					j.ReturnUnknown++
				}
			}
		}
		if p.Classification.RenderwareRole != nil || strings.Contains(orEmpty(p.Classification.Subsystem), "RenderWare") {
			j.Renderware++
		}
	}
	s.Joined = j
	return s
}

func orEmpty(p *string) string {
	if p == nil {
		return ""
	}
	return *p
}
