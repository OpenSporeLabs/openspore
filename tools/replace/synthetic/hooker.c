// synthetic/hooker.c — in-process inline hook (x86 32-bit, non-PIE).
//
// A constructor (runs before main) patches the first 5 bytes of orig()
// with `jmp replacement` (0xE9 + rel32). The original bytes are saved so
// they can be restored; the text page is mprotected writable for the
// patch and returned to RX afterwards.
//
// This is the same mechanism planned for Spore function replacement:
// patch a function's entry to jmp a replacement thunk; the thunk reads
// the same args, touches the same globals, preserves the cdecl frame.

#include <stdint.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

extern int orig(int);
extern int replacement(int);

int g_hook_installed = 0;
uint8_t g_orig_bytes[5];

static void* page_of(void* p) {
    return (void*)(((uintptr_t)p) & ~(uintptr_t)(PAGE_SIZE - 1));
}

__attribute__((constructor))
static void install_hook(void) {
    void* site = (void*)orig;
    void* dest = (void*)replacement;
    void* page = page_of(site);

    // RWX (not just RW): this very hooker runs from the same page on the
    // synthetic target; RW would de-execute it mid-patch -> SIGSEGV.
    if (mprotect(page, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
        fprintf(stderr, "hook: mprotect(rwx) failed\n");
        return;
    }

    memcpy(g_orig_bytes, site, 5);
    uint32_t rel = (uint32_t)(uintptr_t)dest -
                  ((uint32_t)(uintptr_t)site + 5);
    // 0xE9 = jmp rel32 (5 bytes). 0xEB is jmp rel8 (2 bytes) — do NOT use it.
    uint8_t jmp[5] = {0xE9,
                      (uint8_t)(rel & 0xFF),
                      (uint8_t)((rel >> 8) & 0xFF),
                      (uint8_t)((rel >> 16) & 0xFF),
                      (uint8_t)((rel >> 24) & 0xFF)};
    memcpy(site, jmp, 5);

    // Self-check: read the patch back before restoring RX.
    uint8_t rb[5];
    memcpy(rb, site, 5);
    if (memcmp(rb, jmp, 5) != 0) {
        fprintf(stderr, "hook: PATCH FAILED readback %02x %02x %02x %02x %02x\n",
                rb[0], rb[1], rb[2], rb[3], rb[4]);
        mprotect(page, PAGE_SIZE, PROT_READ | PROT_EXEC);
        return;
    }

    mprotect(page, PAGE_SIZE, PROT_READ | PROT_EXEC);
    g_hook_installed = 1;
    fprintf(stderr,
            "hook: installed: %p -> %p (orig bytes %02x %02x %02x %02x %02x)\n",
            site, dest, g_orig_bytes[0], g_orig_bytes[1], g_orig_bytes[2],
            g_orig_bytes[3], g_orig_bytes[4]);
}
