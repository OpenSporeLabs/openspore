package openspore

import (
	"encoding/json"
	"fmt"
	"sort"
	"strings"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// Sources is every authoritative artifact the export reads, already loaded.
type Sources struct {
	Universe   *Universe
	Triage     *Triage
	Index      *IndexDoc
	Evidence   map[uint32]*PerVAArtifacts
	Graph      *Graph
	DataRefs   map[uint32]int
	VTable     map[uint32][]Membership
	VTablesNil bool

	Digests []Digest
	Absent  []Absent
}

// LoadSources reads every authoritative artifact under root.
func LoadSources(root string) (*Sources, error) {
	s := &Sources{Evidence: map[uint32]*PerVAArtifacts{}, VTablesNil: true}

	uni, absent, err := LoadUniverse(root)
	if err != nil {
		return nil, err
	}
	s.Universe = uni
	s.Absent = append(s.Absent, absent...)
	if dg, err := FileDigest(root, root+"/"+uni.Source); err == nil {
		s.Digests = append(s.Digests, dg)
	}

	tri, absent, err := LoadTriage(root)
	if err != nil {
		return nil, err
	}
	s.Triage = tri
	s.Absent = append(s.Absent, absent...)
	if tri != nil {
		if dg, err := FileDigest(root, root+"/"+RelTriage); err == nil {
			s.Digests = append(s.Digests, dg)
		}
	}

	idx, absent, digests, err := LoadIndex(root)
	if err != nil {
		return nil, err
	}
	s.Index = idx
	s.Absent = append(s.Absent, absent...)
	s.Digests = append(s.Digests, digests...)

	ev, absent, digests, err := LoadEvidence(root)
	if err != nil {
		return nil, err
	}
	s.Evidence = ev
	s.Absent = append(s.Absent, absent...)
	s.Digests = append(s.Digests, digests...)

	g, absent, digests, err := LoadGraph(root)
	if err != nil {
		return nil, err
	}
	s.Graph = g
	s.Absent = append(s.Absent, absent...)
	s.Digests = append(s.Digests, digests...)

	dr, absent, digests, err := LoadDataRefCounts(root)
	if err != nil {
		return nil, err
	}
	s.DataRefs = dr
	s.Absent = append(s.Absent, absent...)
	s.Digests = append(s.Digests, digests...)

	var vtAbsent []Absent
	if idx != nil && idx.Binary.SHA256 != "" {
		memb, _, absent, err := LoadVTableScan(root, idx.Binary.SHA256)
		if err != nil {
			return nil, err
		}
		if memb != nil {
			s.VTable = memb
			s.VTablesNil = false
			path := root + "/" + RelVftableDir + "/vftables-" + idx.Binary.SHA256 + ".json"
			if dg, err := FileDigest(root, path); err == nil {
				s.Digests = append(s.Digests, dg)
			}
		}
		vtAbsent = absent
	} else {
		vtAbsent = []Absent{{
			Path:   RelVftableDir,
			Reason: "the sound vftable scan is named by binary digest and the knowledge index did not state a binary_sha256 to look it up by",
		}}
	}
	s.Absent = append(s.Absent, vtAbsent...)

	s.Digests = sortedDigests(s.Digests)
	s.Absent = sortedAbsences(s.Absent)
	return s, nil
}

// BinaryIdentity returns the cross-project join key, preferring the knowledge
// index's binary manifest (which carries version and architecture) and falling
// back to the evidence-pack binary block.
func (s *Sources) BinaryIdentity() (semantic.BinaryIdentity, error) {
	var out semantic.BinaryIdentity
	if s.Index != nil && s.Index.Binary.SHA256 != "" {
		out = semantic.BinaryIdentity{
			SHA256:       s.Index.Binary.SHA256,
			ImageBase:    s.Index.Binary.ImageBase,
			Architecture: s.Index.Binary.Architecture,
			Program:      s.Index.Binary.Program,
			Version:      s.Index.Binary.Version,
		}
	}
	if out.Program == "" && s.Index != nil {
		out.Program = s.Index.Binary.GHIDRAProg
	}
	base, ok := out.ImageBaseAddr()
	if !ok {
		base = semantic.DefaultImageBase
		if out.ImageBase == "" {
			out.ImageBase = base.String()
		}
	}
	if out.SHA256 == "" {
		return out, fmt.Errorf("no authoritative binary_sha256 available: the knowledge index did not state one")
	}
	return out, nil
}

// BuildPassports projects every universe entry into a passport, ordered
// ascending by canonical VA.
func BuildPassports(s *Sources) ([]*semantic.Passport, semantic.Counts, semantic.ExportNotes, error) {
	bin, err := s.BinaryIdentity()
	if err != nil {
		return nil, semantic.Counts{}, semantic.ExportNotes{}, err
	}
	base, _ := bin.ImageBaseAddr()

	families := semanticFamilyIndex(s.Index)

	counts := semantic.Counts{Functions: len(s.Universe.Entries)}
	notes := attachStrayPacks(s, &counts)

	passports := make([]*semantic.Passport, 0, len(s.Universe.Entries))
	for i := range s.Universe.Entries {
		entry := s.Universe.Entries[i]
		p, c := s.buildOne(entry, base, bin, families)
		passports = append(passports, p)
		counts = addCounts(counts, c)
	}
	counts.TotalFactGroups = counts.Functions * factGroupsPerPassport
	counts.ExplicitlyUnavailable = countUnavailable(passports)
	notes.UniverseSource = s.Universe.Source
	notes.UniverseFallback = s.Universe.Fallback
	notes.EvidencePackDirsRead = len(s.Evidence)
	return passports, counts, notes, nil
}

// attachStrayPacks files each evidence pack whose directory VA is not a
// function entry under the entry that contains it.
//
// OpenSpore has packs for a handful of interior addresses (the addresses the
// canonical-identity rule has already corrected, plus some mid-body SDK labels).
// Those directories match no canonical VA, so without this step their content
// would be unreachable through the snapshot. Packs whose VA lies in no known
// body at all are counted as orphans and reported in the export, because
// silently dropping them would understate what was read.
func attachStrayPacks(s *Sources, counts *semantic.Counts) semantic.ExportNotes {
	var notes semantic.ExportNotes
	if s.Evidence == nil {
		notes.OrphanEvidencePackPaths = []string{}
		return notes
	}
	for addr, art := range s.Evidence {
		if _, isEntry := s.Universe.Lookup(addr); isEntry {
			continue
		}
		res, ok := s.Universe.CanonicalIdentity(addr)
		if !ok {
			notes.OrphanEvidencePacks++
			notes.OrphanEvidencePackPaths = append(notes.OrphanEvidencePackPaths,
				RelEvidenceDir+"/"+fmt.Sprintf("%08x", addr)+"/evidence.json")
			continue
		}
		entryArt := s.Evidence[res.Entry]
		if entryArt == nil {
			entryArt = &PerVAArtifacts{
				Addr:    res.Entry,
				RelPath: RelEvidenceDir + "/" + fmt.Sprintf("%08x", res.Entry) + "/evidence.json",
			}
			s.Evidence[res.Entry] = entryArt
		}
		extra := AdditionalPackRecord{
			Pack:        RelEvidenceDir + "/" + fmt.Sprintf("%08x", addr) + "/evidence.json",
			RequestedVA: semantic.Addr(addr).String(),
			Offset:      res.Offset,
			Rule:        semantic.CanonicalIdentityRule,
		}
		if art.Evidence != nil {
			extra.PackState = strp(art.Evidence.EvidenceState)
			extra.PackContentSHA256 = strp(art.Evidence.ContentSHA256)
		}
		entryArt.Extra = append(entryArt.Extra, extra)
		counts.AttachedStrayPacks++
	}
	for _, art := range s.Evidence {
		sort.Slice(art.Extra, func(i, j int) bool { return art.Extra[i].RequestedVA < art.Extra[j].RequestedVA })
	}
	sort.Strings(notes.OrphanEvidencePackPaths)
	return notes
}

const factGroupsPerPassport = 7 // abi, vtable, globals, types, semantics, reconstruction, validation

func (s *Sources) buildOne(entry Entry, base semantic.Addr, bin semantic.BinaryIdentity, families map[uint32]semanticFamily) (*semantic.Passport, semantic.Counts) {
	var c semantic.Counts
	addr := semantic.Addr(entry.Addr)
	p := &semantic.Passport{Record: semantic.RecordFunction}

	var rec *IndexRecord
	if s.Index != nil {
		rec = s.Index.Records[addr.String()]
	}
	var row *TriageRow
	if s.Triage != nil {
		row = s.Triage.ByAddr[entry.Addr]
	}

	// --- identity -----------------------------------------------------------
	rva, ok := addr.RVA(base)
	p.Identity = semantic.IdentityBlock{
		CanonicalVA: addr.String(),
		Size:        entry.Size,
		SizeKnown:   entry.Known,
		IsThunk:     entry.Thunk,
		Section:     entry.Section,
		Requested:   []semantic.RequestedAddr{},
	}
	if ok {
		p.Identity.RVA = rva.String()
	}
	if rec != nil && rec.IdentityResolution != nil {
		p.Identity.IdentityResolution = &semantic.IdentityResolution{
			Rule:        rec.IdentityResolution.Rule,
			CanonicalVA: addr.String(),
			Requested:   []semantic.RequestedAddr{},
		}
		for _, r := range rec.IdentityResolution.Requested {
			va := "0x" + semantic.CutPrefixAddr(r.VA)
			entry := semantic.RequestedAddr{VA: va, Offset: r.Offset}
			p.Identity.Requested = append(p.Identity.Requested, entry)
			p.Identity.IdentityResolution.Requested = append(p.Identity.IdentityResolution.Requested, entry)
		}
		byVA := func(list []semantic.RequestedAddr) {
			sort.Slice(list, func(i, j int) bool { return list[i].VA < list[j].VA })
		}
		byVA(p.Identity.Requested)
		byVA(p.Identity.IdentityResolution.Requested)
		c.ResolvedInteriorVAs += len(p.Identity.Requested)
	}

	// --- names --------------------------------------------------------------
	p.Names = semantic.NamesBlock{GhidraName: firstNonEmpty(entry.Name, nameOf(row), nameOfRec(rec))}
	if row != nil {
		p.Names.SDKName = row.SDKName
		if row.SDKName != nil {
			p.Names.SDKNameSource = semantic.StrPtr(SDKNameSource)
			c.WithSDKName++
		}
	}
	if rec != nil {
		p.Names.NormalizedSymbol = firstStr(rec.NormalizedSymbol, rec.Name)
		p.Names.IdentityRefuted = rec.IdentityRefuted
		if rec.IdentityRefuted != nil {
			c.RefutedIdentities++
		}
	}
	if row != nil {
		p.Names.NormalizedSymbol = firstStr(p.Names.NormalizedSymbol, strp(row.NormName))
	}

	// --- classification -----------------------------------------------------
	p.Classification = semantic.ClassificationBlock{
		Category:   firstNonEmpty(deref(rowCategory(row)), deref(recCategory(rec))),
		Priority:   firstNonEmpty(deref(rowPriority(row)), deref(recPriority(rec))),
		Evidence:   firstNonEmpty(deref(rowEvidence(row)), deref(recEvidence(rec))),
		SDKStructs: nonNil(rowStructs(row)),
	}
	// The knowledge index's subsystem wins, because it IS the reconciled value:
	// tools/reconstruction_knowledge.py resolves subsystem as
	// manifest functions[].subsystem, else the triage queue's, else
	// semantic-decomp. Reading the triage JSONL directly first would report
	// "Transform" where the index says "Graphics.Transform" for the same VA.
	if rec != nil && rec.Subsystem != nil {
		p.Classification.Subsystem = rec.Subsystem
		p.Classification.SubsystemSource = rec.SubsystemSource()
	} else if row != nil && row.Subsystem != nil {
		p.Classification.Subsystem = row.Subsystem
		p.Classification.SubsystemSource = semantic.StrPtr("triage_jsonl")
	}
	// RenderWare membership is detected two ways because the two vocabularies
	// disagree: the triage classifier uses "RenderWare", the manifest-driven
	// knowledge index uses "Graphics.RenderWare", and the SDK namespace prefix
	// "RenderWare::" is the one spelling both agree on. Detecting only the first
	// would miss the two functions the index labels Graphics.RenderWare.
	if role := renderwareRole(p.Classification.Subsystem, row, rec); role != "" {
		p.Classification.RenderwareRole = semantic.StrPtr(role)
		c.WithRenderwareRole++
	}
	if p.Classification.Subsystem != nil {
		c.WithSubsystem++
	}
	p.Classification.Cluster = firstStr(recCluster(rec), rowCluster(row))

	// --- evidence artifacts -------------------------------------------------
	art := s.Evidence[entry.Addr]
	var pack *EvidencePack
	if art != nil {
		pack = art.Evidence
	}
	if pack != nil {
		c.WithEvidencePack++
	}

	// --- ABI ----------------------------------------------------------------
	p.ABI = s.buildABI(pack, rec, &c)

	// --- vtable -------------------------------------------------------------
	p.VTable = buildVTable(entry.Addr, art, row, s, &c)

	// --- graph --------------------------------------------------------------
	callers := addrList(s.Graph.Callers[entry.Addr])
	callees := addrList(s.Graph.Callees[entry.Addr])
	external := nonNilStrings(s.Graph.ExternalCallees[entry.Addr])
	p.Graph = semantic.GraphBlock{
		CallerCount:          len(callers),
		CalleeCount:          len(callees) + len(external),
		Callers:              callers,
		Callees:              callees,
		ExternalCallees:      external,
		VTableReferenceCount: s.Graph.VTableRefs[entry.Addr],
		DataReferenceCount:   s.DataRefs[entry.Addr],
	}
	if len(callers) > 0 {
		c.WithCallers++
	}
	if len(callees) > 0 || len(external) > 0 {
		c.WithCallees++
	}
	if row != nil && row.SCCSize != nil {
		p.Graph.SCCSize = row.SCCSize
	}

	// --- globals / types ----------------------------------------------------
	globals := nonNil(recGlobals(rec))
	if len(globals) > 0 {
		p.Globals = semantic.Available(globals, levelOrUnknown(recEvidenceLevel(rec)), semantic.EvidencePersisted, RelIndex)
		c.WithGlobals++
	} else {
		p.Globals = semantic.Unavailable[[]string](semantic.ReasonNoGlobalRefs, RelIndex)
	}
	types := nonNil(recTypes(rec))
	if len(types) > 0 {
		p.Types = semantic.Available(types, levelOrUnknown(recEvidenceLevel(rec)), semantic.EvidencePersisted, RelIndex)
		c.WithTypes++
	} else {
		p.Types = semantic.Unavailable[[]string](semantic.ReasonNoTypes, RelIndex)
	}

	// --- semantics ----------------------------------------------------------
	p.Semantics = buildSemantics(rec, families[entry.Addr], &c)

	// --- reconstruction -----------------------------------------------------
	p.Reconstruction = buildReconstruction(rec, art, &c)

	// --- evidence artifacts -------------------------------------------------
	p.Evidence = evidenceBlock(art)

	// --- provenance ---------------------------------------------------------
	p.Provenance = []semantic.ProvenanceEntry{}
	if pack != nil {
		for _, pv := range pack.Provenance {
			p.Provenance = append(p.Provenance, semantic.ProvenanceEntry{
				Mode: pv.Mode, Ref: pv.Ref, SourceClass: pv.SourceClass,
			})
		}
	}
	sort.SliceStable(p.Provenance, func(i, j int) bool {
		if p.Provenance[i].SourceClass != p.Provenance[j].SourceClass {
			return p.Provenance[i].SourceClass < p.Provenance[j].SourceClass
		}
		if p.Provenance[i].Mode != p.Provenance[j].Mode {
			return p.Provenance[i].Mode < p.Provenance[j].Mode
		}
		return p.Provenance[i].Ref < p.Provenance[j].Ref
	})

	return p, c
}

const (
	renderwareSubsystem = "RenderWare"
	renderwarePrefix    = "RenderWare::"
	// packRel names the per-function evidence-pack root for provenance when a
	// specific pack path is not available.
	packRel = "reconstruction/evidence/<va>/evidence.json"
)

func isRenderwareName(name string) bool {
	return strings.HasPrefix(name, renderwarePrefix)
}

// renderwareRole returns the RenderWare classification of a function, or "" if
// it has none. Subsystem spelling wins; the SDK namespace prefix is the
// fallback and is reported as such so the two are distinguishable.
func renderwareRole(subsystem *string, row *TriageRow, rec *IndexRecord) string {
	if subsystem != nil {
		sub := *subsystem
		if strings.EqualFold(sub, renderwareSubsystem) || strings.EqualFold(sub, renderwareSubsystem+".Graphics") || strings.HasPrefix(sub, "Graphics."+renderwareSubsystem) {
			return sub
		}
		return ""
	}
	if row != nil && isRenderwareName(row.GhidraName) {
		return renderwareSubsystem + " (by SDK namespace, subsystem unstated)"
	}
	if rec != nil && rec.NamesLikeRenderWare() {
		return renderwareSubsystem + " (by SDK namespace, subsystem unstated)"
	}
	return ""
}

type semanticFamily struct {
	Family  string
	Workers []string
}

func semanticFamilyIndex(idx *IndexDoc) map[uint32]semanticFamily {
	out := map[uint32]semanticFamily{}
	if idx == nil {
		return out
	}
	for _, f := range idx.SemanticFamilies {
		for _, m := range f.Members {
			addr, err := parseHexAddrLoose(m)
			if err != nil {
				continue
			}
			existing := out[addr]
			existing.Family = f.Family
			existing.Workers = append(existing.Workers, f.SourceWorkers...)
			out[addr] = existing
		}
	}
	for addr, f := range out {
		sort.Strings(f.Workers)
		f.Workers = dedupeStrings(f.Workers)
		out[addr] = f
	}
	return out
}

func (s *Sources) buildABI(pack *EvidencePack, rec *IndexRecord, c *semantic.Counts) semantic.Envelope[semantic.ABIBlock] {
	if pack == nil {
		return semantic.Unavailable[semantic.ABIBlock](semantic.ReasonNoEvidencePack, RelEvidenceDir)
	}
	cat, ok := pack.Categories["abi_derived"]
	if !ok || len(cat.Value) == 0 || string(cat.Value) == "null" {
		// The pack's own reason, when it supplied one, is carried verbatim: it
		// is per-function text, not a generic code.
		if cat.Reason != nil && *cat.Reason != "" {
			return semantic.Envelope[semantic.ABIBlock]{
				State: semantic.StateUnavailable, EvidenceLevel: semantic.LevelUnknown,
				EvidenceState: semantic.EvidenceMissing, Provenance: cat.Provenance,
				Reason: *cat.Reason,
			}
		}
		return semantic.Unavailable[semantic.ABIBlock](semantic.ReasonNoABIDerived, packRel)
	}
	var rec2 ABIRecord
	if err := json.Unmarshal(cat.Value, &rec2); err != nil {
		return semantic.Unavailable[semantic.ABIBlock](
			"abi_derived value did not decode as an openspore-abi-inference-1 record: "+err.Error(),
			cat.Provenance...)
	}

	block := semantic.ABIBlock{
		Origin:               "abi_inference",
		Schema:               rec2.Schema,
		Convention:           rec2.Conventions.CallingConvention,
		ConventionConfidence: LevelOf(rec2.Conventions.Confidence),
		Verdict:              strpIf(rec2.Verdict),
		Completeness:         strpIf(rec2.Completeness),
		Variadic:             rec2.Variadic,
		SEHorCookie:          rec2.SEHorCookie,
	}
	block.Receiver = &semantic.ReceiverBlock{
		Present:        semantic.TriBoolOf(rec2.Receiver.Present),
		Register:       rec2.Receiver.Register,
		Confidence:     LevelOf(rec2.Receiver.Confidence),
		Shape:          rec2.Receiver.Shape,
		Provenance:     rec2.Receiver.Provenance,
		BoundsOnly:     rec2.Receiver.BoundsOnly,
		MaxOffset:      rec2.Receiver.MaxOffset,
		WrittenThrough: rec2.Receiver.WrittenThrough,
	}
	block.Cleanup = &semantic.CleanupBlock{
		Side:          rec2.Cleanup.Side,
		Bytes:         rec2.Cleanup.Bytes,
		Confidence:    LevelOf(rec2.Cleanup.Confidence),
		Corroboration: rec2.Cleanup.Corroboration,
		Evidence:      rec2.Cleanup.Evidence,
	}
	block.Return = &semantic.ReturnBlock{
		Register:          rec2.Return.Register,
		RegisterClass:     rec2.Return.RegisterClass,
		Confidence:        LevelOf(rec2.Return.Confidence),
		Type:              rec2.Return.Type,
		VoidPossible:      rec2.Return.VoidPossible,
		BulkWriteEvidence: semantic.BoolPtr(rec2.Return.AggregateEvidence.BulkWrite),
	}
	block.SRET = &semantic.SRETBlock{
		Present:              semantic.TriBoolOf(rec2.SRET.Present),
		Slot:                 rec2.SRET.Slot,
		Confidence:           LevelOf(rec2.SRET.Confidence),
		Ambiguity:            rec2.SRET.Ambiguity,
		HypothesisConfidence: levelPtr(rec2.SRET.HypothesisConfidence),
	}
	slots := rec2.StackArguments.TotalSlots
	block.StackArgSlots = &slots
	if block.Convention != nil {
		c.WithABIData++
	} else {
		c.WithUnknownABI++
	}
	switch block.Receiver.Present {
	case semantic.TriTrue:
		c.WithReceiver++
	case semantic.TriNull:
		c.WithReceiverUnknown++
	}

	if rec != nil && len(rec.ABI) > 0 && string(rec.ABI) != "null" {
		var declared semantic.DeclaredABI
		if err := json.Unmarshal(rec.ABI, &declared); err == nil {
			if declared.SavedRegisters == nil {
				declared.SavedRegisters = []string{}
			}
			block.Declared = &declared
		}
	}
	// The group's level is floored at the decision the record itself carries.
	// An ABI_UNKNOWN record cannot be reported as INFERRED evidence just
	// because its category envelope says so: that would let a consumer read an
	// abstention as a finding.
	level := LevelOf(cat.EvidenceLevel)
	if decision := LevelOf(rec2.Conventions.Confidence); weaker(decision, level) {
		level = decision
	}
	if rec2.Verdict == "ABI_UNKNOWN" && level != semantic.LevelUnknown {
		level = semantic.LevelUnknown
	}
	return semantic.Available(block, level, evidenceStateOf(cat.EvidenceState, pack), cat.Provenance...)
}

// weaker reports whether a is strictly weaker than b on the shared scale.
func weaker(a, b semantic.EvidenceLevel) bool {
	return levelRank(a) < levelRank(b)
}

func levelRank(l semantic.EvidenceLevel) int {
	switch l {
	case semantic.LevelUnknown:
		return 0
	case semantic.LevelApprox:
		return 1
	case semantic.LevelInferred:
		return 2
	case semantic.LevelSupported:
		return 3
	case semantic.LevelObserved:
		return 4
	case semantic.LevelConfirmed:
		return 5
	case semantic.LevelVerified:
		return 6
	default:
		return -1
	}
}

func buildVTable(entryAddr uint32, art *PerVAArtifacts, row *TriageRow, s *Sources, c *semantic.Counts) semantic.Envelope[semantic.VTableBlock] {
	block := semantic.VTableBlock{
		Memberships:     []semantic.VTableMembership{},
		TriageAddresses: []string{},
	}
	if row != nil {
		for _, a := range row.VTableAddrs {
			block.TriageAddresses = append(block.TriageAddresses, "0x"+a)
		}
		sort.Strings(block.TriageAddresses)
		block.TriageFamily = row.VTableFamily
	}
	// Membership is keyed by the function VA, which is the canonical entry, not
	// by the evidence-pack directory: most functions have no pack at all.
	for _, m := range s.VTable[entryAddr] {
		mem := semantic.VTableMembership{TableVA: semantic.Addr(m.TableVA).String(), Slot: m.Slot}
		if m.Known {
			mem.SlotWidth = semantic.IntPtr(m.Width)
		}
		block.Memberships = append(block.Memberships, mem)
	}
	if len(block.Memberships) > 0 {
		c.WithVTableMembership++
	}
	if art != nil && art.Evidence != nil {
		if cat, ok := art.Evidence.Categories["abi_derived"]; ok && len(cat.Value) > 0 {
			var rec ABIRecord
			if json.Unmarshal(cat.Value, &rec) == nil {
				for _, inf := range rec.Inferences {
					if !IsVFTRule(inf.ID) {
						continue
					}
					var v VFTInference
					if json.Unmarshal(inf.Value, &v) == nil && v.Table != "" && v.SlotIndex != nil {
						block.ABIAttributed = &semantic.VTableAttribution{
							Rule:               inf.ID,
							TableVA:            v.Table,
							Slot:               *v.SlotIndex,
							Confidence:         LevelOf(inf.Confidence),
							ReceiverProvenance: v.ReceiverProvenance,
							MembershipCount:    v.MembershipCount,
						}
						c.WithVTableAttributed++
					}
				}
			}
		}
	}

	if len(block.Memberships) == 0 && len(block.TriageAddresses) == 0 && block.ABIAttributed == nil {
		if s.VTablesNil {
			return semantic.Unavailable[semantic.VTableBlock](semantic.ReasonVTableScanAbsent, RelTriage)
		}
		return semantic.Unavailable[semantic.VTableBlock](semantic.ReasonNoVTableMembership, RelVftableDir, RelTriage)
	}
	// The group's level is the strongest statement it actually carries, so a
	// record that has an ABI-engine attribution but an empty membership list
	// (the two sources can disagree) is not demoted to UNKNOWN.
	level := semantic.LevelUnknown
	switch {
	case block.ABIAttributed != nil:
		level = block.ABIAttributed.Confidence
		if level == semantic.LevelUnknown {
			level = semantic.LevelInferred
		}
	case len(block.Memberships) > 0:
		level = semantic.LevelInferred
	case len(block.TriageAddresses) > 0:
		level = semantic.LevelSupported
	}
	return semantic.Available(block, level, semantic.EvidenceDerived, RelVftableDir, RelTriage)
}

func buildSemantics(rec *IndexRecord, fam semanticFamily, c *semantic.Counts) semantic.Envelope[semantic.SemanticsBlock] {
	block := semantic.SemanticsBlock{
		Confidence:          map[string]json.RawMessage{},
		Evidence:            []semantic.SemanticClaim{},
		Notes:               []string{},
		UnresolvedQuestions: []string{},
		SourceWorkers:       []string{},
	}
	if rec != nil {
		block.Status = rec.SemanticStatus
		if rec.Semantic != nil {
			s := rec.Semantic
			block.Classification = s.Classification
			block.Family = firstStr(s.Family, fam2ptr(fam.Family))
			for k, v := range s.Confidence {
				block.Confidence[k] = v
			}
			for _, e := range s.Evidence {
				block.Evidence = append(block.Evidence, semantic.SemanticClaim{Claim: e.Claim, Class: e.Class, Source: e.Source})
			}
			block.UnresolvedQuestions = append(block.UnresolvedQuestions, s.Unresolved...)
			block.Name = s.Name
			block.Subsystem = s.Subsystem
			block.Triangulation = s.Triangulation
			block.DownstreamUnlocks = s.DownstreamUnlocks
			if s.Source != nil {
				block.Source = s.Source
			}
		}
		block.UnresolvedQuestions = append(block.UnresolvedQuestions, rec.UnresolvedQuestions...)
		block.SourceWorkers = append(block.SourceWorkers, fam.Workers...)
	}
	block.SourceWorkers = dedupeStrings(block.SourceWorkers)
	sort.Strings(block.SourceWorkers)
	block.UnresolvedQuestions = dedupeStrings(block.UnresolvedQuestions)
	sort.Strings(block.UnresolvedQuestions)

	populated := block.Classification != nil || block.Status != nil ||
		len(block.Evidence) > 0 || len(block.UnresolvedQuestions) > 0 || len(block.Notes) > 0
	if !populated {
		return semantic.Unavailable[semantic.SemanticsBlock](semantic.ReasonNoSemanticRecord, RelIndex)
	}
	c.WithSemantics++
	return semantic.Available(block, semantic.LevelInferred, semantic.EvidencePersisted, RelIndex)
}

func buildReconstruction(rec *IndexRecord, art *PerVAArtifacts, c *semantic.Counts) semantic.Envelope[semantic.ReconstructionBlock] {
	block := semantic.ReconstructionBlock{
		GeneratedSource: []string{},
		Handoffs:        []string{},
		Metadata:        []string{},
	}
	if rec != nil {
		block.Package = rec.Package
		block.Status = rec.Status
		block.ReviewStatus = rec.ReviewStatus
		block.IntegrationStatus = rec.IntegrationStatus
		block.Reconstructed = rec.Reconstructed
		block.Blocked = rec.Blocked
		block.RuntimeGated = rec.RuntimeGated
		block.RuntimeValidated = rec.RuntimeValidated
		if rec.Source != nil {
			block.GeneratedSource = nonNil(rec.Source.Files)
			block.Handoffs = nonNil(rec.Source.Handoffs)
			block.Metadata = nonNil(rec.Source.Metadata)
		}
		if rec.Runtime != nil && len(rec.Runtime.BlockingReason) > 0 && string(rec.Runtime.BlockingReason) != "null" {
			block.RuntimeBlockingReason = rec.Runtime.BlockingReason
		}
	}
	if rec != nil && rec.Package != nil {
		c.WithReconstruction++
	}
	if art != nil && art.Promotion != nil {
		pr := art.Promotion
		block.Promoted = semantic.TriTrue
		block.PromotionSchema = strpIf(pr.Schema)
		block.StaticStatus = strpIf(pr.StaticStatus)
		if len(pr.Supersedes) > 0 && string(pr.Supersedes) != "null" {
			block.Supersedes = pr.Supersedes
		}
		c.WithPromoted++
	} else {
		block.Promoted = semantic.TriFalse
	}

	prov := []string{RelIndex}
	if art != nil {
		if art.Evidence != nil {
			prov = append(prov, art.RelPath)
		}
		if art.Validation != nil {
			block.Validation = validationSummary(art.Validation)
			c.WithValidation++
			prov = append(prov, RelEvidenceDir+"/<va>/validation.json")
		}
	}

	populated := block.Package != nil || block.Status != nil || block.Promoted == semantic.TriTrue ||
		block.Validation != nil || len(block.GeneratedSource) > 0
	if !populated {
		return semantic.Unavailable[semantic.ReconstructionBlock](semantic.ReasonNoReconstruction, RelIndex)
	}
	level := semantic.LevelInferred
	if rec != nil && rec.EvidenceLevel != nil {
		level = LevelOf(*rec.EvidenceLevel)
	}
	return semantic.Available(block, level, semantic.EvidencePersisted, prov...)
}

func evidenceBlock(art *PerVAArtifacts) semantic.EvidenceBlock {
	var out semantic.EvidenceBlock
	if art == nil {
		return out
	}
	out.AdditionalPacks = make([]semantic.AdditionalPack, 0, len(art.Extra))
	for _, e := range art.Extra {
		out.AdditionalPacks = append(out.AdditionalPacks, semantic.AdditionalPack{
			Pack: e.Pack, RequestedVA: e.RequestedVA, Offset: e.Offset, Rule: e.Rule,
			PackState: e.PackState, PackContentSHA256: e.PackContentSHA256,
		})
	}
	out.ValidationReport = semantic.StrPtr(RelEvidenceDir + "/" + fmt.Sprintf("%08x", art.Addr) + "/validation.json")
	if art.Promotion != nil {
		out.PromotionRecord = semantic.StrPtr(RelEvidenceDir + "/" + fmt.Sprintf("%08x", art.Addr) + "/promotion.json")
	}
	if art.Evidence != nil {
		out.Pack = semantic.StrPtr(art.RelPath)
		out.PackState = strp(art.Evidence.EvidenceState)
		out.PackContentSHA256 = strp(art.Evidence.ContentSHA256)
		out.TargetAddressKind = strp(art.Evidence.Target.AddressKind)
	}
	return out
}

func validationSummary(doc *ValidationDoc) *semantic.ValidationSummary {
	out := &semantic.ValidationSummary{
		Schema:       doc.Schema,
		Coverage:     map[string]semantic.ValidationCheck{},
		StaticRollup: map[string]json.RawMessage{},
	}
	for name, chk := range doc.Checks {
		out.Coverage[name] = semantic.ValidationCheck{
			Status:   chk.Status,
			Coverage: chk.Coverage,
			Detail:   chk.Detail,
			Evidence: nonNilStrings(chk.Evidence),
		}
	}
	if doc.Runtime != nil {
		out.Runtime = &semantic.ValidationCheck{
			Status:   doc.Runtime.Status,
			Coverage: "gated",
			Detail:   doc.Runtime.Reason,
			Evidence: []string{},
		}
	}
	if doc.Static != nil && doc.Static.Coverage != nil {
		for k, v := range doc.Static.Coverage {
			out.StaticRollup[k] = v
		}
	}
	return out
}

func addCounts(a, b semantic.Counts) semantic.Counts {
	a.WithSDKName += b.WithSDKName
	a.WithABIData += b.WithABIData
	a.WithUnknownABI += b.WithUnknownABI
	a.WithReceiver += b.WithReceiver
	a.WithReceiverUnknown += b.WithReceiverUnknown
	a.WithVTableMembership += b.WithVTableMembership
	a.WithVTableAttributed += b.WithVTableAttributed
	a.WithSubsystem += b.WithSubsystem
	a.WithRenderwareRole += b.WithRenderwareRole
	a.WithReconstruction += b.WithReconstruction
	a.WithPromoted += b.WithPromoted
	a.WithEvidencePack += b.WithEvidencePack
	a.WithValidation += b.WithValidation
	a.WithSemantics += b.WithSemantics
	a.WithGlobals += b.WithGlobals
	a.WithTypes += b.WithTypes
	a.WithCallers += b.WithCallers
	a.WithCallees += b.WithCallees
	a.RefutedIdentities += b.RefutedIdentities
	a.ResolvedInteriorVAs += b.ResolvedInteriorVAs
	return a
}

func countUnavailable(passports []*semantic.Passport) int {
	n := 0
	for _, p := range passports {
		if !p.ABI.IsAvailable() {
			n++
		}
		if !p.VTable.IsAvailable() {
			n++
		}
		if !p.Globals.IsAvailable() {
			n++
		}
		if !p.Types.IsAvailable() {
			n++
		}
		if !p.Semantics.IsAvailable() {
			n++
		}
		if !p.Reconstruction.IsAvailable() {
			n++
		}
		if !p.Reconstruction.IsAvailable() || p.Reconstruction.Value.Validation == nil {
			n++
		}
	}
	return n
}

// ---- small helpers -------------------------------------------------------

func evidenceStateOf(catState string, pack *EvidencePack) string {
	switch catState {
	case semantic.EvidenceLive, semantic.EvidenceDerived, semantic.EvidencePersisted:
		return catState
	}
	if pack != nil && pack.EvidenceState != "" {
		return pack.EvidenceState
	}
	return semantic.EvidencePersisted
}

func levelOrUnknown(v *string) semantic.EvidenceLevel {
	if v == nil {
		return semantic.LevelUnknown
	}
	return LevelOf(*v)
}

func levelPtr(v *string) semantic.EvidenceLevel {
	if v == nil {
		return semantic.LevelUnknown
	}
	return LevelOf(*v)
}

func strpIf(s string) *string {
	if s == "" {
		return nil
	}
	return semantic.StrPtr(s)
}

func strp(s string) *string {
	if s == "" {
		return nil
	}
	return semantic.StrPtr(s)
}

func deref(p *string) string {
	if p == nil {
		return ""
	}
	return *p
}

func firstNonEmpty(vals ...string) string {
	for _, v := range vals {
		if v != "" {
			return v
		}
	}
	return ""
}

func firstStr(vals ...*string) *string {
	for _, v := range vals {
		if v != nil && *v != "" {
			return v
		}
	}
	return nil
}

func fam2ptr(s string) *string { return strp(s) }

func addrList(v []uint32) []string {
	out := make([]string, 0, len(v))
	for _, a := range v {
		out = append(out, semantic.Addr(a).String())
	}
	return out
}

func nonNil(v []string) []string {
	if v == nil {
		return []string{}
	}
	return v
}

func nonNilStrings(v []string) []string {
	if v == nil {
		return []string{}
	}
	return v
}

func dedupeStrings(in []string) []string {
	if len(in) == 0 {
		return []string{}
	}
	cp := append([]string(nil), in...)
	sort.Strings(cp)
	out := cp[:0]
	var prev string
	for i, v := range cp {
		if i > 0 && v == prev {
			continue
		}
		out = append(out, v)
		prev = v
	}
	return out
}

func nameOf(r *TriageRow) string {
	if r == nil {
		return ""
	}
	return r.GhidraName
}

func nameOfRec(r *IndexRecord) string {
	if r == nil {
		return ""
	}
	if r.Name != nil {
		return *r.Name
	}
	return ""
}

func rowCategory(r *TriageRow) *string {
	if r == nil {
		return nil
	}
	return strp(r.Category)
}
func rowPriority(r *TriageRow) *string {
	if r == nil {
		return nil
	}
	return strp(r.Priority)
}
func rowEvidence(r *TriageRow) *string {
	if r == nil {
		return nil
	}
	return strp(r.Evidence)
}
func rowStructs(r *TriageRow) []string {
	if r == nil {
		return []string{}
	}
	return r.StructNames
}
func rowCluster(r *TriageRow) *string {
	if r == nil {
		return nil
	}
	return r.Cluster
}
func recCluster(r *IndexRecord) *string {
	if r == nil {
		return nil
	}
	if r.Cluster != nil {
		return r.Cluster
	}
	if r.Triage != nil {
		return r.Triage.Cluster
	}
	return nil
}
func recCategory(r *IndexRecord) *string {
	if r == nil || r.Triage == nil {
		return nil
	}
	return r.Triage.Category
}
func recPriority(r *IndexRecord) *string {
	if r == nil || r.Triage == nil {
		return nil
	}
	return r.Triage.Priority
}
func recEvidence(r *IndexRecord) *string {
	if r == nil || r.Triage == nil {
		return nil
	}
	return r.Triage.Evidence
}
func recGlobals(r *IndexRecord) []string {
	if r == nil {
		return nil
	}
	return r.Globals
}
func recTypes(r *IndexRecord) []string {
	if r == nil {
		return nil
	}
	return r.Types
}
func recEvidenceLevel(r *IndexRecord) *string {
	if r == nil {
		return nil
	}
	return r.EvidenceLevel
}
