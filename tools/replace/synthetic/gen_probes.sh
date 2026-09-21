#!/bin/sh
# gen_probes.sh — write a probe_tracer probes.json for a native 32-bit ELF.
# Usage: gen_probes.sh <elf> > probes.json
#
# For a non-PIE ET_EXEC, linked address == runtime address, so
# rva (== image_base + rva offset) comes straight from nm.

elf="$1"
base=$(readelf -lW "$elf" | awk '$1 == "LOAD" {print $3; exit}')
orig=$(nm "$elf" | awk '$3 == "orig" {print $1}')
repl=$(nm "$elf" | awk '$3 == "replacement" {print $1}')

printf '{\n'
printf '  "name": "synthetic_hook",\n'
printf '  "description": "Inline-hook proof: INT3 probes on orig and replacement entries (non-PIE, linked == runtime).",\n'
printf '  "image_base": "%s",\n' "$base"
printf '  "probes": [\n'
printf '    { "name": "orig", "rva": "0x%s", "thiscall": false },\n' "$orig"
printf '    { "name": "replacement", "rva": "0x%s", "thiscall": false }\n' "$repl"
printf '  ]\n'
printf '}\n'
