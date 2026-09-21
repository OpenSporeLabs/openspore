CXX ?= g++
CXXFLAGS ?= -O2 -g -std=c++17 -Wall -Wextra

probe_tracer: probe_tracer.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f probe_tracer

.PHONY: clean
