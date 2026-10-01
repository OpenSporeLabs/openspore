// Package main_test exercises the installed executable rather than the Run
// function, so the argument parsing, the process exit codes and the stream
// separation are all covered end to end.
package main_test

import (
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"testing"

	"github.com/openspore/spore-semantic/internal/semantic"
	"github.com/openspore/spore-semantic/internal/testfixture"
)

var binary string

func TestMain(m *testing.M) {
	dir, err := os.MkdirTemp("", "spore-semantic-bin-*")
	if err != nil {
		panic(err)
	}
	defer os.RemoveAll(dir)
	binary = filepath.Join(dir, "spore-semantic")

	build := exec.Command("go", "build", "-o", binary, ".")
	build.Env = os.Environ()
	if out, err := build.CombinedOutput(); err != nil {
		panic("go build failed: " + err.Error() + "\n" + string(out))
	}
	os.Exit(m.Run())
}

type runResult struct {
	code   int
	stdout string
	stderr string
}

func exe(t *testing.T, args ...string) runResult {
	t.Helper()
	cmd := exec.Command(binary, args...)
	var so, se strings.Builder
	cmd.Stdout = &so
	cmd.Stderr = &se
	err := cmd.Run()
	code := 0
	if err != nil {
		var exitErr *exec.ExitError
		if ok := asExitError(err, &exitErr); ok {
			code = exitErr.ExitCode()
		} else {
			t.Fatalf("running the executable failed: %v", err)
		}
	}
	return runResult{code: code, stdout: so.String(), stderr: se.String()}
}

func asExitError(err error, target **exec.ExitError) bool {
	if e, ok := err.(*exec.ExitError); ok {
		*target = e
		return true
	}
	return false
}

func fixture(t *testing.T) (*testfixture.Tree, string) {
	t.Helper()
	tr := testfixture.New(t)
	t.Cleanup(func() { os.RemoveAll(tr.Root) })
	tr.Functions = []testfixture.Function{
		{VA: 0x00401000, Name: "FUN_00401000", Size: 0x20},
		{VA: 0x00401020, Name: "FUN_00401020", Size: 0x10},
		{VA: 0x00925000, Name: "FUN_00925000", Size: 0x4a},
		{VA: 0x009250c0, Name: "FUN_009250c0", Size: 0x30},
	}
	tr.Triage = []testfixture.Triage{
		{VA: 0x00401000, GhidraName: "FUN_00401000", Category: "ENGINE_IMPLEMENTATION", Priority: "P3", Evidence: "INFERRED", Subsystem: "App", SCCSize: 1},
		{VA: 0x00401020, GhidraName: "FUN_00401020", Category: "UNKNOWN", Priority: "P3", Evidence: "UNKNOWN", SCCSize: 1},
		{VA: 0x00925000, GhidraName: "FUN_00925000", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P1", Evidence: "SUPPORTED", Subsystem: "RenderWare", SCCSize: 1},
		{VA: 0x009250c0, GhidraName: "FUN_009250c0", Category: "THIRD_PARTY_OR_RUNTIME", Priority: "P2", Evidence: "SUPPORTED", Subsystem: "RenderWare", SCCSize: 1},
	}
	tr.Packs[0x00401000] = true
	tr.ABIRecords[0x00401000] = testfixture.ABIRecordJSON(ptr("__thiscall"), "INFERRED", ptrB(true), nil)
	tr.RecordOverrides["0x00401000"] = map[string]any{
		"package": "PKG-FIXTURE", "status": "reconstructed",
	}
	if err := tr.Write(); err != nil {
		t.Fatalf("fixture Write: %v", err)
	}
	snap := filepath.Join(tr.Root, "passport.jsonl")
	r := exe(t, "export", "--root", tr.Root, "--out", snap)
	if r.code != 0 {
		t.Fatalf("export via the executable failed (%d): %s%s", r.code, r.stdout, r.stderr)
	}
	return tr, snap
}

func ptr(s string) *string { return &s }
func ptrB(b bool) *bool    { return &b }

func TestExecutableExportLookupValidate(t *testing.T) {
	_, snap := fixture(t)

	r := exe(t, "lookup", "0x00401000", "--snapshot", snap)
	if r.code != 0 {
		t.Fatalf("lookup exited %d: %s", r.code, r.stderr)
	}
	for _, want := range []string{"0x00401000", "FUN_00401000", "__thiscall", "App"} {
		if !strings.Contains(r.stdout, want) {
			t.Fatalf("human lookup output is missing %q:\n%s", want, r.stdout)
		}
	}

	j := exe(t, "lookup", "0x00401000", "--snapshot", snap, "--json")
	if j.code != 0 {
		t.Fatalf("json lookup exited %d: %s", j.code, j.stderr)
	}
	if !strings.HasPrefix(strings.TrimSpace(j.stdout), "{") {
		t.Fatalf("json lookup did not emit an object:\n%s", j.stdout)
	}

	v := exe(t, "validate", "--snapshot", snap)
	if v.code != 0 {
		t.Fatalf("validate exited %d: %s", v.code, v.stderr)
	}
	if !strings.Contains(v.stdout, "OK") {
		t.Fatalf("validate output:\n%s", v.stdout)
	}
}

func TestExecutableExitCodesAreDistinct(t *testing.T) {
	tr, snap := fixture(t)
	cases := []struct {
		name string
		args []string
		want int
	}{
		{"ok", []string{"lookup", "0x00401000", "--snapshot", snap}, 0},
		{"usage: no args", []string{}, 1},
		{"usage: unknown command", []string{"frobnicate"}, 1},
		{"unknown function", []string{"lookup", "0x00925050", "--snapshot", snap}, 2},
		{"unknown symbol", []string{"lookup-symbol", "NoSuchName", "--snapshot", snap}, 3},
		{"missing snapshot", []string{"lookup", "0x00401000", "--snapshot", filepath.Join(tr.Root, "nope.jsonl")}, 7},
	}
	for _, c := range cases {
		t.Run(c.name, func(t *testing.T) {
			r := exe(t, c.args...)
			if r.code != c.want {
				t.Fatalf("exit %d, want %d (stderr=%q)", r.code, c.want, r.stderr)
			}
		})
	}
}

func TestExecutableBinaryMismatchThroughEnvironment(t *testing.T) {
	_, snap := fixture(t)
	cmd := exec.Command(binary, "lookup", "0x00401000", "--snapshot", snap)
	cmd.Env = append(os.Environ(), "OPENSPORE_REQUIRE_SHA="+testfixture.OtherSHA)
	var so, se strings.Builder
	cmd.Stdout = &so
	cmd.Stderr = &se
	err := cmd.Run()
	exitErr, ok := err.(*exec.ExitError)
	if !ok {
		t.Fatalf("a mismatched binary digest was accepted (err=%v, stdout=%s)", err, so.String())
	}
	if exitErr.ExitCode() != 4 {
		t.Fatalf("exit %d, want 4 (binary mismatch)", exitErr.ExitCode())
	}
	if !strings.Contains(se.String(), "binary mismatch") {
		t.Fatalf("stderr = %q", se.String())
	}
}

func TestExecutableDeterministicExport(t *testing.T) {
	tr, _ := fixture(t)
	var prev []byte
	for i := 0; i < 3; i++ {
		out := filepath.Join(t.TempDir(), semantic.SnapshotFile)
		r := exe(t, "export", "--root", tr.Root, "--out", out)
		if r.code != 0 {
			t.Fatalf("export %d failed: %s", r.code, r.stderr)
		}
		data, err := os.ReadFile(out)
		if err != nil {
			t.Fatalf("ReadFile: %v", err)
		}
		if prev != nil && string(data) != string(prev) {
			t.Fatalf("export %d is not byte-identical to export 0", i)
		}
		prev = data
	}
}

func TestExecutableVersionAndHelp(t *testing.T) {
	v := exe(t, "version")
	if v.code != 0 || !strings.Contains(v.stdout, semantic.SnapshotSchema) {
		t.Fatalf("version = %q (exit %d)", v.stdout, v.code)
	}
	h := exe(t, "--help")
	if h.code != 0 || !strings.Contains(h.stdout, "spore-semantic lookup") {
		t.Fatalf("help = %q (exit %d)", h.stdout, h.code)
	}
}
