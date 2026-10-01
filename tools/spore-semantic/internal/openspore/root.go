// Package openspore reads OpenSpore's committed and exported artifacts and
// projects them into semantic.Passport records.
//
// Nothing in this package derives a fact. Every field is copied from a file
// that OpenSpore's Python systems already wrote, and every optional group
// either carries the source's provenance or carries an explicit reason for its
// own absence. The reader never opens a socket, never shells out to Python and
// never reads Ghidra.
package openspore

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"sort"
	"strings"
)

// Paths of the authoritative artifacts, relative to Root. They are named here
// once so the export can report an absent input by path rather than by
// whichever branch failed.
const (
	RelUniverse    = ".spore-analysis/ghidra-exports/functions.tsv"
	RelUniverseAlt = "knowledgegraph/research/21-decompilation-coverage.json"
	RelTriage      = "knowledgegraph/triage/triage-f0e310e0.triage-v6.jsonl"
	RelIndex       = "reconstruction/knowledge/index.json"
	RelXrefs       = "knowledgegraph/triage/xrefs-2540f2ca.tsv"
	RelDatarefs    = "knowledgegraph/triage/datarefs-2540f2ca.tsv"
	RelEvidenceDir = "reconstruction/evidence"
	RelVftableDir  = ".spore-analysis/cache"
)

// ResolveRoot finds the OpenSpore checkout that owns dir, walking upward.
// $OPENSPORE_ROOT wins outright. The markers are the knowledge index and the
// triage JSONL, both of which are git-tracked; the git-ignored Ghidra export
// directory is not used as a marker because a consumer may legitimately have
// the tracked artifacts without it.
func ResolveRoot(dir string) (string, error) {
	if v := os.Getenv("OPENSPORE_ROOT"); v != "" {
		return filepath.Abs(v)
	}
	start := dir
	if start == "" {
		wd, err := os.Getwd()
		if err != nil {
			return "", err
		}
		start = wd
	}
	abs, err := filepath.Abs(start)
	if err != nil {
		return "", err
	}
	markers := []string{RelIndex, RelTriage}
	for {
		found := 0
		for _, m := range markers {
			if st, err := os.Stat(filepath.Join(abs, m)); err == nil && st.Mode().IsRegular() {
				found++
			}
		}
		if found == len(markers) {
			return abs, nil
		}
		parent := filepath.Dir(abs)
		if parent == abs {
			return "", fmt.Errorf("no OpenSpore checkout at or above %s (looked for %s); pass --root, or set $OPENSPORE_ROOT",
				abs, strings.Join(markers, " and "))
		}
		abs = parent
	}
}

// Digest is a file's content hash, used to record reproducibility.
type Digest struct {
	Path   string
	SHA256 string
	Bytes  int64
}

// FileDigest hashes path and returns its Digest with a repo-relative Path.
func FileDigest(root, path string) (Digest, error) {
	f, err := os.Open(path)
	if err != nil {
		return Digest{}, err
	}
	defer f.Close()

	h := sha256.New()
	n, err := io.Copy(h, f)
	if err != nil {
		return Digest{}, err
	}
	rel, relErr := filepath.Rel(root, path)
	if relErr != nil {
		rel = path
	}
	return Digest{
		Path:   filepath.ToSlash(rel),
		SHA256: hex.EncodeToString(h.Sum(nil)),
		Bytes:  n,
	}, nil
}

// FileExists reports whether path names a regular file.
func FileExists(path string) bool {
	st, err := os.Stat(path)
	return err == nil && st.Mode().IsRegular()
}

// DirExists reports whether path names a directory.
func DirExists(path string) bool {
	st, err := os.Stat(path)
	return err == nil && st.IsDir()
}

// sortedDigests orders digests by path so the metadata inputs map is stable
// regardless of the order the export happened to read them in.
func sortedDigests(in []Digest) []Digest {
	out := append([]Digest(nil), in...)
	sort.Slice(out, func(i, j int) bool { return out[i].Path < out[j].Path })
	return out
}

// sortedAbsences orders absences by path.
func sortedAbsences(in []Absent) []Absent {
	out := append([]Absent(nil), in...)
	sort.Slice(out, func(i, j int) bool { return out[i].Path < out[j].Path })
	return out
}

// Absent records an authoritative artifact that was not in the checkout.
type Absent struct {
	Path   string
	Reason string
}
