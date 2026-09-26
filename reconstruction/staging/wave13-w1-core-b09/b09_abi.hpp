#pragma once

// Every one of the six targets in this package is a __thiscall member: the
// receiver arrives in ECX and the body reads no stack argument (0x00c47cc0 is
// the one exception - it also takes one stack dword and ends in RET 0x4). The
// reconstructions carry this attribute so the emitted 32-bit code reproduces
// the original register form rather than the cdecl stack form.
#if defined(__i386__) && defined(__clang__)
#define B09_THISCALL __attribute__((thiscall))
#else
#define B09_THISCALL
#endif
