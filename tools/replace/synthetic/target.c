// synthetic/target.c — 32-bit non-PIE inline-hook proof target.
// Build: gcc -m32 -O0 -fno-pie -no-pie -Wall -o target target.c
//
// orig() and replacement() produce different, detectable output.
// main() calls orig() N times (deterministic) and prints each result,
// then prints g_replacement_ran so a hook effect is observable end-to-end.
//
// The small per-call sleep keeps the target alive long enough for
// probe_tracer to discover the module and plant its INT3 probes before
// the calls finish (the tracer polls /proc/<pid>/maps ~every 100 ms).

#include <stdio.h>
#include <unistd.h>

volatile int g_replacement_ran = 0;

int __attribute__((noinline)) orig(int x) {
    return x * 2;
}

int __attribute__((noinline)) replacement(int x) {
    g_replacement_ran = 1;
    return x * 2 + 1000;
}

int main(void) {
    const int n = 40;
    for (int i = 1; i <= n; i++) {
        printf("call %2d: %d\n", i, orig(i));
        usleep(50000);
    }
    printf("replacement_ran=%d\n", g_replacement_ran);
    return 0;
}
