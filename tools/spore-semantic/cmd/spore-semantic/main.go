// Command spore-semantic is a read-only exchange interface over OpenSpore's
// accumulated per-function knowledge.
//
// It exports a deterministic snapshot from OpenSpore's authoritative artifacts
// and answers binary_sha256 + VA lookups against that snapshot. It derives
// nothing: ABI conventions, vftable membership, validation verdicts and
// semantic interpretations are all copied from artifacts the Python systems
// already wrote, with their provenance intact.
//
// It needs no network, no Python and no Ghidra at runtime, and the stdlib
// only.
package main

import (
	"os"

	"github.com/openspore/spore-semantic/internal/cli"
)

func main() {
	os.Exit(cli.Run(os.Args[1:], cli.Env{
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}))
}
