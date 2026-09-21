# tools/replace/synthetic — inline-hook proof (32-bit native).
#
# make          — builds target (unhooked), target_hooked (hooked), probes.json
# make test     — headless before/after test (probe_tracer + assertions)

CC   ?= gcc
CXX  ?= g++
TRACER ?= ../../observatory/probe_tracer
CFLAGS = -m32 -O0 -fno-pie -no-pie -Wall

all: target target_hooked probes.json

target: target.c
	$(CC) $(CFLAGS) -o $@ target.c

target_hooked: target.c hooker.c
	$(CC) $(CFLAGS) -o $@ target.c hooker.c

probes.json: target gen_probes.sh
	./gen_probes.sh target > $@

$(TRACER):
	$(MAKE) -C ../../observatory

test: all $(TRACER)
	python3 test_hook.py

clean:
	rm -f target target_hooked probes.json out_before.jsonl out_after.jsonl

.PHONY: all test clean
