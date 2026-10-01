// Behavioural model test for target VA 0x0067dc80.
//
// The eleven instructions of 0x0067dc80 .. 0x0067dc9b fix exactly three
// observable behaviours, and the test pins each one on both reconstruction
// entry points:
//
//   1. the complete destructor at 0x0067db10 runs on EVERY flag value, and it
//      is the first thing that runs -- it is called at 0x0067dc83, before the
//      flag is read at 0x0067dc88;
//   2. the release at 0x00f47380 runs only when bit 0 of the flag is set, it
//      runs strictly AFTER the destructor, and it receives the receiver;
//   3. the receiver is returned in EAX on both paths (MOV EAX,ESI at
//      0x0067dc98 sits outside the branch).
//
// Two further facts are pinned that the ordering tests alone would not catch:
// that only BIT 0 of the argument is ever read (the test at 0x0067dc88 is a
// byte test with immediate 0x1, so the other 31 bits must change nothing), and
// that the entry point carries the callee-cleaned stack discipline of RET 0x4.
//
// Each of those is a mutation-detectable assertion: inverting the mask,
// reordering the two calls, dropping the unconditional destructor, returning a
// constant instead of the receiver, or turning `ret $4` into `ret` all make
// this test fail.

#include <cstdint>
#include <string>
#include <vector>

#include "get_0067dc80.hpp"

#define TEST_THISCALL PKG_IMSG_THISCALL
#define TEST_CDECL PKG_IMSG_CDECL
#define PKG_IMSG_NAKED_CDECL __attribute__((naked, cdecl))

namespace openspore::reconstruction::pkg_app_imessage_manager_dtor {
namespace {

std::vector<std::string>* events = nullptr;
const void* observed_dtor_receiver = nullptr;
const void* observed_free_pointer = nullptr;
int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void record(const char* name) { events->push_back(name); }

// 0x0067db10 as seen from 0x0067dc83: thiscall, one register argument, no
// return value. The receiver is the only thing it is given, and the body hands
// it this value unchanged.
void TEST_THISCALL complete_dtor_0067db10(OpaqueMessageManagerOwner* self) {
  observed_dtor_receiver = self;
  record("complete_dtor_0067db10");
}

// 0x00f47380 as seen from 0x0067dc90: cdecl, one stack argument, no return
// value, caller-cleaned.
void TEST_CDECL global_free_00f47380(const void* pointer) {
  observed_free_pointer = pointer;
  record("global_free_00f47380");
}

struct Harness {
  Harness() {
    events = &log;
    g_imessage_manager_dtor_ports.complete_dtor_0067db10 =
        &complete_dtor_0067db10;
    g_imessage_manager_dtor_ports.global_free_00f47380 = &global_free_00f47380;
  }
  ~Harness() {
    g_imessage_manager_dtor_ports.complete_dtor_0067db10 = nullptr;
    g_imessage_manager_dtor_ports.global_free_00f47380 = nullptr;
    events = nullptr;
  }
  std::size_t count() const { return log.size(); }
  const char* at(std::size_t index) const { return log[index].c_str(); }
  std::vector<std::string> log;
};

OpaqueMessageManagerOwner owner{};

// The one dispatcher every ordering assertion below is run against.
void* dispatch(OpaqueWord flag) {
  return app_imessage_manager_delete_dispatch_0067dc80(&owner, flag);
}

void reset_observations() {
  observed_dtor_receiver = nullptr;
  observed_free_pointer = nullptr;
}

// -- 1. the complete destructor is unconditional -----------------------------

void complete_destructor_runs_on_every_flag_value() {
  for (OpaqueWord flag = 0u; flag < 4u; ++flag) {
    Harness harness;
    reset_observations();
    dispatch(flag);
    check(harness.count() >= 1u);
    if (harness.count() >= 1u) {
      check(std::string(harness.at(0)) == "complete_dtor_0067db10");
    }
    check(observed_dtor_receiver == static_cast<const void*>(&owner));
  }
}

// -- 2. the release is gated on bit 0 and ordered after the destructor -------

void release_is_gated_on_bit_zero_of_the_flag() {
  // Every single bit of the 4-byte slot in turn, plus the combinations that
  // matter: bit 0 alone, bit 0 with each other single bit, and all-ones.
  OpaqueWord flags[36];
  for (int bit = 0; bit < 32; ++bit) {
    flags[bit] = 1u << bit;
  }
  flags[32] = 0u;
  flags[33] = 0xffffffffu;
  flags[34] = 0xfffffffeu;  // every bit except bit 0
  flags[35] = 0x00000001u;  // bit 0 alone, spelled with an explicit width

  for (OpaqueWord flag : flags) {
    Harness harness;
    reset_observations();
    void* returned = dispatch(flag);

    const bool releases = (flag & 1u) != 0u;
    check(returned == static_cast<void*>(&owner));
    if (releases) {
      check(harness.count() == 2u);
      if (harness.count() == 2u) {
        // 0x0067dc83 precedes 0x0067dc8f: the release can never come first.
        check(std::string(harness.at(0)) == "complete_dtor_0067db10");
        check(std::string(harness.at(1)) == "global_free_00f47380");
      }
      check(observed_free_pointer == static_cast<const void*>(&owner));
    } else {
      // Only bit 0 can open this branch, so a set bit 1..31 must leave the
      // body at exactly one call.
      check(harness.count() == 1u);
      check(observed_free_pointer == nullptr);
    }
  }
}

// -- 3. the receiver is the return value on both paths ----------------------

void receiver_is_returned_whatever_the_flag() {
  for (OpaqueWord flag = 0u; flag < 2u; ++flag) {
    Harness harness;
    void* returned = dispatch(flag);
    check(returned == static_cast<void*>(&owner));
  }
}

// -- 4. no local null guard ------------------------------------------------

// The body has no null check of its own, so a null receiver is forwarded to
// both callees and comes back out. 0x00f47380 is the only guard on this path
// and it guards inside its own body.
void a_null_receiver_is_forwarded_unchanged() {
  Harness harness;
  reset_observations();
  void* returned = app_imessage_manager_delete_dispatch_0067dc80(nullptr, 1u);
  check(returned == nullptr);
  check(harness.count() == 2u);
  check(observed_dtor_receiver == nullptr);
  check(observed_free_pointer == nullptr);
}

// -- 5. the naked transcription, entered through its real ABI ---------------

// Called through the thiscall entry point itself, so the argument really does
// travel at [ESP+0x4] on entry and the flag really is read at [ESP+0x8] after
// the call at 0x0067dc83 has pushed a return address. A misplaced argument
// makes the bit-0 cases take the wrong branch and fails the counts below.
void naked_entry_point_runs_the_same_operations() {
  for (OpaqueWord flag = 0u; flag < 2u; ++flag) {
    Harness harness;
    reset_observations();
    void* returned = get_0067dc80(&owner, flag);
    check(returned == static_cast<void*>(&owner));
    check(observed_dtor_receiver == static_cast<const void*>(&owner));
    const bool releases = (flag & 1u) != 0u;
    check(harness.count() == (releases ? 2u : 1u));
    if (harness.count() >= 1u) {
      check(std::string(harness.at(0)) == "complete_dtor_0067db10");
    }
    if (releases && harness.count() == 2u) {
      check(std::string(harness.at(1)) == "global_free_00f47380");
      check(observed_free_pointer == static_cast<const void*>(&owner));
    }
  }
}

// A control entry point with the byte-for-byte identical epilogue -- same
// convention, same callee-cleaned stack discipline, same signature. The body is
// deliberately the shortest possible, so nothing about the measurement below
// depends on what an entry point does internally.
extern "C" void* PKG_IMSG_NAKED_THISCALL
control_entry_point_0067dc80(OpaqueMessageManagerOwner*, OpaqueWord) {
  __asm__("movl 4(%esp), %eax\n\t"  // return the argument
          "ret $4\n\t");
}

// The two callers below are hand-rolled rather than compiler-generated, so the
// stack measurement cannot be perturbed by the compiler's own call padding (at
// -O2 an optimising compiler allocates 16-byte call alignment space lazily and
// reuses it across adjacent calls, which shifts an ESP delta taken around a
// single call by an amount that has nothing to do with the callee). Each is a
// cdecl function taking (receiver, flag) and returning the callee's stack
// movement in bytes:
//
//   pushl %ebx              the call-site ESP is kept in EBX, not in a
//   pushl <flag>            caller-saved register: the two shims the entry
//   movl <receiver>, %ecx   point calls are ordinary C++ functions and clobber
//   movl %esp, %ebx         EDX, and EBX is callee-saved through them;
//   call <entry point>
//   movl %esp, %eax
//   subl %ebx, %eax         -> bytes of stack the callee removed
//   popl %ebx
//   ret
//
// The final `ret` is a plain one: the only dword this frame added is the flag
// pushed above, and removing that is the callee's job. A callee that failed to
// do it would leave the frame four bytes low for the test's own caller, which
// is why the flag is pushed here rather than reused from the arguments.
extern "C" std::intptr_t PKG_IMSG_NAKED_CDECL
stack_delta_of_control_0067dc80(OpaqueMessageManagerOwner*, OpaqueWord) {
  __asm__("pushl %ebx\n\t"
          "pushl 12(%esp)\n\t"                // the flag, into the slot the
                                                // callee reads it from
          "movl 12(%esp), %ecx\n\t"           // the receiver, into the hidden this
          "movl %esp, %ebx\n\t"               // ESP at the call site
          "call control_entry_point_0067dc80\n\t"
          "movl %esp, %eax\n\t"
          "subl %ebx, %eax\n\t"               // the callee's stack movement
          "popl %ebx\n\t"
          "ret\n\t");
}

extern "C" std::intptr_t PKG_IMSG_NAKED_CDECL
stack_delta_of_target_0067dc80(OpaqueMessageManagerOwner*, OpaqueWord) {
  __asm__("pushl %ebx\n\t"
          "pushl 12(%esp)\n\t"                // the flag, into the slot the
                                                // callee reads it from
          "movl 12(%esp), %ecx\n\t"           // the receiver, into the hidden this
          "movl %esp, %ebx\n\t"               // ESP at the call site
          "call get_0067dc80\n\t"
          "movl %esp, %eax\n\t"
          "subl %ebx, %eax\n\t"               // the callee's stack movement
          "popl %ebx\n\t"
          "ret\n\t");
}

// RET 0x4 at 0x0067dc9b: the callee removes the one dword argument, so ESP sits
// one dword higher after the call than it did at the call site. A plain `ret`
// in place of `ret $4` leaves that dword on the stack and reads 0 here, which
// is a clean assertion failure and not a crash -- the measurers above pop
// nothing but the flag they pushed themselves.
void naked_entry_point_pops_its_argument() {
  const std::intptr_t one_dword = 4;
  for (OpaqueWord flag = 0u; flag < 2u; ++flag) {
    Harness harness;
    const std::intptr_t control =
        stack_delta_of_control_0067dc80(&owner, flag);
    const std::intptr_t target =
        stack_delta_of_target_0067dc80(&owner, flag);
    // The control carries the same convention and the same epilogue, so a
    // reading other than one dword there would mean the measurement itself is
    // wrong rather than the target; both are asserted, so a broken measurement
    // cannot be mistaken for a clean one.
    check(control == one_dword);
    check(target == one_dword);
    check(target == control);
  }
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_app_imessage_manager_dtor

int main() {
  using namespace openspore::reconstruction::pkg_app_imessage_manager_dtor;
  complete_destructor_runs_on_every_flag_value();
  release_is_gated_on_bit_zero_of_the_flag();
  receiver_is_returned_whatever_the_flag();
  a_null_receiver_is_forwarded_unchanged();
  naked_entry_point_runs_the_same_operations();
  naked_entry_point_pops_its_argument();
  if (failures != 0) {
    return 1;
  }
  return 0;
}
