package runtime

import (
	"bytes"
	"io"
	"path/filepath"
	"sort"
	"strings"
)

func bytesReader(b []byte) io.Reader { return bytes.NewReader(b) }

func isUnknownField(err error) bool { return strings.Contains(err.Error(), "unknown field") }

func dirOf(path string) string { return filepath.Dir(path) }

func sortCensus(in []CensusTarget) {
	sort.Slice(in, func(i, j int) bool { return in[i].VA < in[j].VA })
}
