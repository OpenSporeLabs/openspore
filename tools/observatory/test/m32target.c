// m32target — 32-bit test target for probe_tracer validation (no Wine, no game).
// Build: gcc -m32 -O0 -o m32target m32target.c
// Runs `iters` iterations of alpha/beta calls, sleeping 5ms each.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void __attribute__((noinline, used)) alpha(int a) {
    volatile int s = 0;
    for (int i = 0; i < a; i++) s += i;
}

static int g_bcalls=0;
static void __attribute__((noinline, used)) beta(int a) {
    g_bcalls++;
    if (g_bcalls<=2) fprintf(stderr,"[beta #%d -> calling alpha]\n", g_bcalls);
    alpha(a / 2);
    alpha(a / 3);
    if (g_bcalls<=2) fprintf(stderr,"[beta #%d done]\n", g_bcalls);
}

int main(int argc, char** argv) {
    long iters = argc > 1 ? atol(argv[1]) : 100;
    printf("m32target up: %ld iterations\n", iters);
    fflush(stdout);
    for (long i = 0; i < iters; i++) {
        beta(1000);
        beta(2000);
        usleep(5000);
    }
    printf("m32target done\n");
    return 0;
}
