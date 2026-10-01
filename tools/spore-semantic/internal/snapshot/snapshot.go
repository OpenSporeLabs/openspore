// Package snapshot writes and reads the deterministic semantic exchange file.
//
// Format: JSON Lines. Line 1 is the metadata record; lines 2..N are function
// records sorted ascending by identity.canonical_va. The stream contains no
// timestamps, PIDs, absolute paths or host names, and no map is ever
// serialised, so two exports from the same repository state are byte-identical.
package snapshot

import (
	"bufio"
	"bytes"
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"github.com/openspore/spore-semantic/internal/semantic"
)

// Errors a load can report. Callers map these onto stable exit codes; none of
// them is ever reported as an empty result.
var (
	// ErrCorrupt means the file is not a readable snapshot: bad JSON, a
	// truncated record, or a content digest that does not match.
	ErrCorrupt = errors.New("corrupted snapshot")
	// ErrSchema means the file is a readable document of a schema this build
	// does not implement, either because the schema id differs or because it
	// carries fields this build does not know.
	ErrSchema = errors.New("unsupported schema")
	// ErrBinaryMismatch means the snapshot describes a different binary than
	// the caller required.
	ErrBinaryMismatch = errors.New("binary mismatch")
	// ErrMissing means no snapshot file was found.
	ErrMissing = errors.New("snapshot not found")
)

// factGroupsPerPassport is the number of optional fact groups a passport can
// carry. It is the denominator for the "explicitly unavailable" ratio, so it
// must match the groups the exporter actually emits.
const factGroupsPerPassport = 7

// Options control a write.
type Options struct {
	// Binary is the join key recorded in the metadata line.
	Binary semantic.BinaryIdentity
	// Inputs and AbsentInputs record which artifacts the export read.
	Inputs       []semantic.InputDigest
	AbsentInputs []semantic.AbsentInput
	// Export carries what the write did, which the record bodies cannot show.
	Export semantic.ExportNotes
}

// Result reports what a write produced.
type Result struct {
	Path       string
	Bytes      int64
	Records    int
	ContentSHA string
	HeaderSHA  string
}

// Write serialises passports to path atomically.
//
// The metadata line is emitted first but its content_sha256 covers only the
// function record lines, so the digest is computed over a byte range that
// excludes the header. That keeps the header first -- a consumer can check
// binary identity before parsing 59k records -- without making the digest
// self-referential.
func Write(path string, passports []*semantic.Passport, counts semantic.Counts, opts Options) (Result, error) {
	// Sort here rather than trusting the caller: the ordering is part of the
	// format's contract, and an unsorted snapshot is a different file.
	ordered := append([]*semantic.Passport(nil), passports...)
	sort.Slice(ordered, func(i, j int) bool {
		return ordered[i].Identity.CanonicalVA < ordered[j].Identity.CanonicalVA
	})

	var body bytes.Buffer
	h := sha256.New()
	for _, p := range ordered {
		line, err := semantic.MarshalLine(p)
		if err != nil {
			return Result{}, fmt.Errorf("encoding %s: %w", p.Identity.CanonicalVA, err)
		}
		h.Write(line)
		body.Write(line)
	}

	meta := semantic.Metadata{
		Record:        semantic.RecordMetadata,
		Schema:        semantic.SnapshotSchema,
		Binary:        opts.Binary,
		Generator:     semantic.Generator{Name: semantic.GeneratorName, Version: semantic.GeneratorVersion},
		Inputs:        opts.Inputs,
		AbsentInputs:  opts.AbsentInputs,
		Counts:        counts,
		Export:        opts.Export,
		ContentSHA256: hex.EncodeToString(h.Sum(nil)),
	}
	if meta.Inputs == nil {
		meta.Inputs = []semantic.InputDigest{}
	}
	if meta.AbsentInputs == nil {
		meta.AbsentInputEmpty()
	}
	header, err := semantic.MarshalLine(&meta)
	if err != nil {
		return Result{}, err
	}

	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		return Result{}, err
	}
	tmp, err := os.CreateTemp(filepath.Dir(path), filepath.Base(path)+".*")
	if err != nil {
		return Result{}, err
	}
	tmpName := tmp.Name()
	defer os.Remove(tmpName)

	w := bufio.NewWriterSize(tmp, 1<<20)
	if _, err := w.Write(header); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if _, err := w.Write(body.Bytes()); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if err := w.Flush(); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if err := tmp.Sync(); err != nil {
		tmp.Close()
		return Result{}, err
	}
	if err := tmp.Close(); err != nil {
		return Result{}, err
	}
	if err := os.Chmod(tmpName, 0o644); err != nil {
		return Result{}, err
	}
	// os.Rename over an existing regular file is atomic on POSIX. Replace is
	// the stdlib spelling but only exists on Windows, which this tool does not
	// target.
	if err := os.Rename(tmpName, path); err != nil {
		return Result{}, err
	}

	return Result{
		Path:       path,
		Bytes:      int64(len(header) + body.Len()),
		Records:    len(ordered),
		ContentSHA: meta.ContentSHA256,
		HeaderSHA:  headerDigest(header),
	}, nil
}

func headerDigest(line []byte) string {
	h := sha256.Sum256(line)
	return hex.EncodeToString(h[:])
}

// Data is a loaded snapshot.
type Data struct {
	Path      string
	Metadata  *semantic.Metadata
	Passports map[uint32]*semantic.Passport
	// Order lists canonical VAs ascending.
	Order []uint32
}

// ImageBase returns the snapshot's declared image base, or the Spore default.
func (d *Data) ImageBase() semantic.Addr {
	if d.Metadata != nil {
		if base, ok := d.Metadata.Binary.ImageBaseAddr(); ok {
			return base
		}
	}
	return semantic.DefaultImageBase
}

// Size returns the on-disk byte length of the snapshot, or -1 when unknown.
func (d *Data) Size() int64 {
	st, err := os.Stat(d.Path)
	if err != nil {
		return -1
	}
	return st.Size()
}

// Load reads a snapshot into records, verifying the schema, the content digest
// and canonical-VA uniqueness.
//
// requireSHA, when non-empty, additionally asserts the snapshot describes that
// binary. Every consumer-facing command passes the expected digest; `validate`
// passes "" so it can report on a snapshot whose identity it does not know.
func Load(path string, requireSHA string) (*Data, error) {
	f, err := os.Open(path)
	if err != nil {
		if os.IsNotExist(err) {
			return nil, fmt.Errorf("%w: %s", ErrMissing, path)
		}
		return nil, err
	}
	defer f.Close()

	data := &Data{Path: path, Passports: map[uint32]*semantic.Passport{}}
	sc := bufio.NewScanner(f)
	sc.Buffer(make([]byte, 0, 1<<20), 1<<24)

	h := sha256.New()
	haveHeader := false
	lineNo := 0
	for sc.Scan() {
		lineNo++
		line := sc.Bytes()
		if len(bytes.TrimSpace(line)) == 0 {
			continue
		}
		if !haveHeader {
			if err := loadHeader(data, line, lineNo); err != nil {
				return nil, err
			}
			haveHeader = true
			continue
		}
		var p semantic.Passport
		if err := unmarshalStrict(line, &p); err != nil {
			return nil, fmt.Errorf("%w: %s:%d: %v", ErrCorrupt, path, lineNo, err)
		}
		if p.Record != semantic.RecordFunction {
			return nil, fmt.Errorf("%w: %s:%d: record is %q, expected %q", ErrCorrupt, path, lineNo, p.Record, semantic.RecordFunction)
		}
		addr, err := semantic.ParseAddr(p.Identity.CanonicalVA, 0)
		if err != nil {
			return nil, fmt.Errorf("%w: %s:%d: canonical_va %q: %v", ErrCorrupt, path, lineNo, p.Identity.CanonicalVA, err)
		}
		if _, dup := data.Passports[uint32(addr)]; dup {
			return nil, fmt.Errorf("%w: %s:%d: duplicate canonical VA %s", ErrCorrupt, path, lineNo, p.Identity.CanonicalVA)
		}
		// The digest covers the exact record bytes, so it is fed from the raw
		// line before the record is normalised into the index.
		h.Write(line)
		h.Write([]byte{'\n'})
		data.Passports[uint32(addr)] = &p
		data.Order = append(data.Order, uint32(addr))
	}
	if err := sc.Err(); err != nil {
		return nil, fmt.Errorf("%w: %s: %v", ErrCorrupt, path, err)
	}
	if !haveHeader {
		return nil, fmt.Errorf("%w: %s: no metadata record on line 1", ErrCorrupt, path)
	}
	if len(data.Order) == 0 {
		return nil, fmt.Errorf("%w: %s: metadata present but no function records", ErrCorrupt, path)
	}

	got := hex.EncodeToString(h.Sum(nil))
	if data.Metadata.ContentSHA256 != "" && got != data.Metadata.ContentSHA256 {
		return nil, fmt.Errorf("%w: %s: content_sha256 is %s, recomputed %s", ErrCorrupt, path, data.Metadata.ContentSHA256, got)
	}
	if requireSHA != "" && data.Metadata.Binary.SHA256 != requireSHA {
		return nil, fmt.Errorf("%w: snapshot describes %s, caller requires %s", ErrBinaryMismatch, short(data.Metadata.Binary.SHA256), short(requireSHA))
	}
	return data, nil
}

func loadHeader(data *Data, line []byte, lineNo int) error {
	var meta semantic.Metadata
	if err := unmarshalStrict(line, &meta); err != nil {
		return fmt.Errorf("%w: %s:%d: %v", ErrCorrupt, data.Path, lineNo, err)
	}
	if meta.Record != semantic.RecordMetadata {
		return fmt.Errorf("%w: %s:%d: first record is %q, expected %q", ErrCorrupt, data.Path, lineNo, meta.Record, semantic.RecordMetadata)
	}
	if meta.Schema != semantic.SnapshotSchema {
		return fmt.Errorf("%w: %s declares %q, this build implements %q", ErrSchema, data.Path, meta.Schema, semantic.SnapshotSchema)
	}
	if meta.Binary.SHA256 == "" {
		return fmt.Errorf("%w: %s:%d: metadata states no binary_sha256; a snapshot without binary identity is not addressable", ErrCorrupt, data.Path, lineNo)
	}
	data.Metadata = &meta
	return nil
}

// unmarshalStrict rejects unknown fields. That is deliberate: a snapshot whose
// header says this schema but whose records carry fields this build has never
// heard of is a schema this build does not implement, and reporting it as
// ErrSchema is more useful than reporting it as corruption.
func unmarshalStrict(line []byte, into any) error {
	dec := json.NewDecoder(bytes.NewReader(line))
	dec.DisallowUnknownFields()
	if err := dec.Decode(into); err != nil {
		if strings.Contains(err.Error(), "unknown field") {
			return fmt.Errorf("%w: %v", ErrSchema, err)
		}
		return err
	}
	return nil
}

// Recount recomputes the coverage counters from the loaded records.
func (d *Data) Recount() semantic.Counts {
	var counts semantic.Counts
	counts.Functions = len(d.Order)
	for _, addr := range d.Order {
		p := d.Passports[addr]
		accumulate(&counts, p)
	}
	return counts
}

func accumulate(c *semantic.Counts, p *semantic.Passport) {
	if p.Names.SDKName != nil {
		c.WithSDKName++
	}
	if p.ABI.IsAvailable() {
		if p.ABI.Value.Convention != nil {
			c.WithABIData++
		} else {
			c.WithUnknownABI++
		}
		if p.ABI.Value.Receiver != nil {
			switch p.ABI.Value.Receiver.Present {
			case semantic.TriTrue:
				c.WithReceiver++
			case semantic.TriNull:
				c.WithReceiverUnknown++
			}
		}
	}
	if p.VTable.IsAvailable() {
		if len(p.VTable.Value.Memberships) > 0 {
			c.WithVTableMembership++
		}
		if p.VTable.Value.ABIAttributed != nil {
			c.WithVTableAttributed++
		}
	}
	if p.Classification.Subsystem != nil {
		c.WithSubsystem++
	}
	if p.Classification.RenderwareRole != nil {
		c.WithRenderwareRole++
	}
	if p.Semantics.IsAvailable() {
		c.WithSemantics++
	}
	if p.Globals.IsAvailable() {
		c.WithGlobals++
	}
	if p.Types.IsAvailable() {
		c.WithTypes++
	}
	if len(p.Graph.Callers) > 0 {
		c.WithCallers++
	}
	if len(p.Graph.Callees) > 0 || len(p.Graph.ExternalCallees) > 0 {
		c.WithCallees++
	}
	if p.Names.IdentityRefuted != nil {
		c.RefutedIdentities++
	}
	c.ResolvedInteriorVAs += len(p.Identity.Requested)
	c.AttachedStrayPacks += len(p.Evidence.AdditionalPacks)
	if p.Evidence.Pack != nil {
		c.WithEvidencePack++
	}
	if p.Reconstruction.IsAvailable() {
		if p.Reconstruction.Value.Package != nil {
			c.WithReconstruction++
		}
		if p.Reconstruction.Value.Promoted == semantic.TriTrue {
			c.WithPromoted++
		}
		if p.Reconstruction.Value.Validation != nil {
			c.WithValidation++
		}
	}
	c.TotalFactGroups += factGroupsPerPassport
	for _, present := range []bool{
		p.ABI.IsAvailable(),
		p.VTable.IsAvailable(),
		p.Globals.IsAvailable(),
		p.Types.IsAvailable(),
		p.Semantics.IsAvailable(),
		p.Reconstruction.IsAvailable(),
		p.Reconstruction.IsAvailable() && p.Reconstruction.Value.Validation != nil,
	} {
		if !present {
			c.ExplicitlyUnavailable++
		}
	}
}

// Verify compares the recomputed counters against the metadata line. A
// disagreement means the header describes different bytes than the body, which
// is a corruption signal even when the content digest matches -- a hand-edited
// header, or a header copied from another snapshot.
func (d *Data) Verify() []string {
	got := d.Recount()
	want := d.Metadata.Counts
	checks := []struct {
		name        string
		got, stored int
	}{
		{"functions", got.Functions, want.Functions},
		{"with_sdk_name", got.WithSDKName, want.WithSDKName},
		{"with_abi_data", got.WithABIData, want.WithABIData},
		{"with_abi_unknown", got.WithUnknownABI, want.WithUnknownABI},
		{"with_receiver", got.WithReceiver, want.WithReceiver},
		{"with_vtable_membership", got.WithVTableMembership, want.WithVTableMembership},
		{"with_renderware_role", got.WithRenderwareRole, want.WithRenderwareRole},
		{"with_reconstruction_package", got.WithReconstruction, want.WithReconstruction},
		{"with_promotion", got.WithPromoted, want.WithPromoted},
		{"with_semantics", got.WithSemantics, want.WithSemantics},
		{"explicitly_unavailable", got.ExplicitlyUnavailable, want.ExplicitlyUnavailable},
		{"attached_stray_evidence_packs", got.AttachedStrayPacks, want.AttachedStrayPacks},
	}
	var problems []string
	for _, c := range checks {
		if c.got != c.stored {
			problems = append(problems, fmt.Sprintf("counts.%s: body has %d, metadata declares %d", c.name, c.got, c.stored))
		}
	}

	// Records must be strictly ascending by canonical VA. The writer sorts, so
	// an out-of-order line means the file was assembled by something else.
	ascending := sort.SliceIsSorted(d.Order, func(i, j int) bool { return d.Order[i] < d.Order[j] })
	if !ascending {
		problems = append(problems, "records are not sorted ascending by identity.canonical_va")
	}
	for i := 1; i < len(d.Order); i++ {
		if d.Order[i] == d.Order[i-1] {
			problems = append(problems, "duplicate canonical VA in record order")
			break
		}
	}
	return problems
}

func short(sha string) string {
	if len(sha) > 12 {
		return sha[:12]
	}
	return sha
}
