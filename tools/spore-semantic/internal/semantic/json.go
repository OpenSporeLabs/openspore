package semantic

import (
	"bytes"
	"encoding/json"
	"fmt"
)

// Encoder produces the canonical byte form of a snapshot line.
//
// Two settings matter for determinism and neither is the json package default:
//
//   - SetEscapeHTML(false). The default escapes <, > and & to < and
//     friends. Free-text semantic notes and ABI detail strings contain all
//     three, so the default would both bloat the file and change bytes
//     depending on prose. The OpenSpore canonical_json helper uses
//     ensure_ascii=False for the same reason.
//   - no field reordering. Struct field order is the emission order, because
//     no map is ever serialised. The only map fields are
//     SemanticsBlock.Confidence and ValidationSummary.Coverage, and encoding/json
//     sorts map keys, so those are deterministic too.
type Encoder struct {
	enc *json.Encoder
	buf *bytes.Buffer
}

// NewEncoder returns an Encoder writing to buf.
func NewEncoder(buf *bytes.Buffer) *Encoder {
	e := &Encoder{buf: buf, enc: json.NewEncoder(buf)}
	e.enc.SetEscapeHTML(false)
	return e
}

// EncodeLine writes v as one compact JSON line terminated by '\n'.
func (e *Encoder) EncodeLine(v any) error {
	if err := e.enc.Encode(v); err != nil {
		return err
	}
	// json.Encoder.Encode already appends exactly one '\n'. Nothing to do;
	// the assertion below documents the invariant the digest depends on.
	if e.buf.Len() > 0 && e.buf.Bytes()[e.buf.Len()-1] != '\n' {
		return fmt.Errorf("semantic: encoder did not terminate line with newline")
	}
	return nil
}

// MarshalLine returns the canonical single-line JSON encoding of v.
func MarshalLine(v any) ([]byte, error) {
	var buf bytes.Buffer
	if err := NewEncoder(&buf).EncodeLine(v); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}
