// PKG-SWARM-W1-005C0DD0 -- VA 0x005c0dd0
// Behavioural model test for FUN_005c0dd0 @ 0x005c0dd0.
//
// THE BODY UNDER TEST IS TWO INSTRUCTIONS, so this test is not walking a
// sequence. It is attacking the four things a four-byte leaf can get wrong, and
// measuring the three the listing settles:
//
//   measured, not asserted by convention:
//     * the return WIDTH, from the full 32-bit EAX sampled at the return and
//       compared across two probe runs that differ only in the bytes a wider
//       read would have swallowed, so no assumption is made about what the
//       upper bytes contain (cases C6, I1);
//     * the STACK SHAPE, by pushing a decoy word, calling, and sampling ESP
//       after the return: a residual of exactly four bytes is what zero bytes of
//       callee cleanup looks like, and it is not what a `RET 4` reconstruction
//       produces (case H);
//     * the RECEIVER IDENTITY, by calling the same function with two different
//       objects in ECX through a trampoline and requiring the two results to
//       follow the register, not the address (case F).
//
// THERE IS NO DIRECT CALLEE, and that is itself the tested fact. The complete
// listing is `8A 41 24` / `C3`: neither instruction is a transfer, `callees` is
// empty, the xref export records no outgoing edge, and dispatch records
// indirect_calls 0. So there is no callee to define as an observer here, and
// inventing one would invent a transfer the bytes do not contain. What stands in
// for the observer is (a) a byte-level snapshot of the receiver taken on both
// sides of every call, which shows every effect the body had, and (b) a decoy
// dispatch table whose slots count their own invocations, which shows the body
// dispatched nowhere.
//
// What is asserted, and it is only what the listing fixes:
//
//   * the returned byte is the receiver's byte at displacement 0x24 and nothing
//     else -- checked with a decoy field that differs at every other offset;
//   * the returned byte is the byte verbatim: 0x00, 0x01, 0x7f, 0x80, 0xfe and
//     0xff all round-trip, so nothing normalises the value to {0, 1};
//   * the width is one byte: 0x24..0x27 carry EF BE AD DE and the result is
//     0xEF, not 0xBEEF and not 0xDEADBEEF;
//   * NO byte of the receiver changes, anywhere in the fixture -- the body is a
//     load and a return;
//   * the value comes out of the RECEIVER, at one dereference level: a receiver
//     whose first word is a pointer to a second object still yields the first
//     object's own byte;
//   * the value does NOT come out of a dispatch word: a table at the receiver's
//     +0x00 whose occupied slots would each return a different byte and count
//     their own invocation changes nothing and is never called;
//   * the recorded evidence constants themselves: the four body bytes, the
//     span length, the instruction count, the displacement, the observed extent,
//     and the twelve-table / six-slot-index record.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction. Each names
// the wrong reconstruction it is aimed at, and the decoy it uses to do it:
//
//   A  the value is a constant, or a "default true" predicate: 0x00 and 0xff
//      both have to come back verbatim, and a stub that returns 1 dies on 0x00;
//   B  the displacement is not 0x24 (0x20, 0x23, 0x25, 0x28, 0x2c and every
//      other byte in the fixture are decoys that differ from the planted one);
//   C  the read is a WORD or a DWORD at 0x24 rather than a byte;
//   D  the body also WRITES something -- a write-back, a lazy flag, a counter;
//   E  the receiver is a HOLDER and the field belongs to the object it points at
//      (the two-level dereference that is a real, previously-observed failure
//      mode in this corpus);
//   F  the value comes from a baked-in address, a global, or a register other
//      than the one the trampoline loaded;
//   G  the value is read through the dispatch word at the receiver's +0x00,
//      which is the one-level-vs-two-level question a body with a vtable
//      footprint invites and this body has no evidence for;
//   H  the function takes a stack argument, or its terminator is `RET 4`;
//   I  the return is a 32-bit value whose upper three bytes this body was
//      supposed to have set (the 8A form does not set them, and the two direct
//      callers read AL alone);
//   J  a transcription slip in a recorded constant (a wrong byte, a wrong
//      length, a wrong displacement, a lost table).
//
// What is NOT asserted, and why:
//
//   * Bits 8..31 of EAX AT A REAL CALL SITE. The load is 8A 41 24, a PARTIAL
//     register write: it is not 0F B6 41 24 (MOVZX EAX, byte ptr [ECX+0x24],
//     four bytes), so the body leaves the upper three bytes of EAX exactly as
//     the caller left them. Asserting a zero-extension here would assert an
//     instruction the image does not contain, and asserting they equal anything
//     particular would assert a property of the CALLER's EAX that the machine
//     never established. What settles it as unobservable at the two known call
//     sites is that both consume AL alone -- 0x00adfeb2
//     `MOV byte ptr [ESI+0x170], AL` and 0x00de5278 `TEST AL, AL`. The probe
//     does still zero EAX before the call, and case C6 does still measure the
//     return register in full, but C6's control is DIFFERENTIAL -- it compares
//     two probe runs that differ only in the bytes a wider read would have
//     swallowed -- precisely so that it does not depend on the probe's entry
//     state surviving into the return. See the note at C6 for why that is not
//     something a compiler may be relied on to do.
//   * The value domain. Nothing masks the byte to {0, 1} in these two
//     instructions, and no record for this target says the field is a flag, so
//     the test refuses to assert that 0x80 is impossible and instead requires
//     every byte to survive unchanged. The model test is deliberately agnostic
//     about bool-versus-unsigned-char; the declared type is the least committal
//     one-byte spelling and the width is what the machine fixes.
//   * The identity of the byte at 0x24. The machine-derived receiver record is
//     bounds_only, so it states the displacement and identifies nothing. No case
//     names a field, and the model's own span declares a displacement and no
//     member.
//   * The receiver's size and class. The fixture is larger than the observed
//     extent on purpose, so no case can be passing because the decoys had no
//     room to exist.
//   * The slot this body occupies in the twelve tables that reference it. The
//     committed export puts it at SIX different indices, so no single slot is
//     asserted as correct; case J only checks that the recorded set is intact.

#include "swarm_w1_005c0dd0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

// -- the trampoline ----------------------------------------------------------
// Emitted by the assembler, not by the compiler, and for a measured reason.
//
// This used to be one extended `__asm__` block with four register operands
// (a `"=&r"` probe pointer and three `"r"` inputs). That shape is not portable
// between the two compilers this package has to pass, and the divergence is
// entirely inside the compilers' operand allocation:
//
//   g++ 16.2  -m32 -O0  materialises every input into a register immediately
//                      before the block -- `leal -40(%ebp), %edx` -- so the
//                      block reads a register that was set for it.
//   clang++ 22 -m32 -O0 allocates a register for the `"=&r"` probe pointer,
//                      spills the pointer to -0x24(%ebp) at +76, and then never
//                      loads it: the block executes `movl %esp, (%edx)` with
//                      whatever EDX the enclosing frame last held, which under
//                      the gate's PIE link is an address inside .text, and the
//                      store faults. Dropping the `&` is no better -- clang then
//                      assigns the probe pointer and the call target the SAME
//                      register.
//
// g++ therefore exited 0 and clang++ died in `call_probe`, which is exactly
// the gate failure. The fix is to take the operand allocator out of the loop:
// the call sequence below is a real function whose body the assembler sees
// verbatim, so no constraint model, no register choice and no compiler stack
// layout can change it.
//
// It is also POSITION-INDEPENDENT BY CONSTRUCTION: the block names no symbol
// at all, because the target address arrives as an argument. That is what lets
// it work under the gate's default PIE link without needing a GOT base held in
// EBX, which is the usual way an i386 hand-written stub goes wrong.
//
// The three samples are written through ONE caller-owned block, so the block
// needs no memory operand of any kind. That is deliberate: the `pushl` below
// moves ESP, and an ESP-relative `"m"` operand would then be addressed against
// the wrong ESP -- a defect another package in this corpus shipped until it
// only fired at -O2. The push lands strictly below this frame, so it cannot
// touch the block, and the trailing `addl $4` restores it.
//
// Frame layout on entry (cdecl, i386): the return address is at 0(%esp), the
// first argument at 4(%esp), and after `pushl %ebp` the arguments sit at
// 8(%ebp), 12(%ebp), 16(%ebp) and 20(%ebp).
//
// Register discipline, and it is stricter than it looks. This block makes an
// INDIRECT call to a function it knows nothing about, so it may keep nothing
// across that call in a caller-saved register: EDX, ECX, EAX and the flags are
// all the callee's to destroy. Only EBX, ESI, EDI, EBP and ESP survive, which
// is why the samples pointer lives in EBX (saved and restored here, and
// preserved by any well-formed callee) while the decoy word goes in EDX, which
// is consumed by the `pushl` before the call and never needed again. The target
// in ESI and the receiver in ECX are both live only up to the `call` itself, and
// no instruction between their load and the call touches them.
//
// The measurement is the same one the inline-asm block made, and the ENTRY state
// it controls is the same. EAX is zeroed before the call on purpose: the
// machine's load is 8A 41 24, a PARTIAL register write, so it does not set bits
// 8..31 of EAX itself. See case C6 for why the probe's entry state is not by
// itself a portable control, and for the differential measurement that replaced
// that dependence.
__asm__(
    ".text\n\t"
    ".globl openspore_probe_trampoline_005c0dd0\n\t"
    ".type openspore_probe_trampoline_005c0dd0, @function\n\t"
    "openspore_probe_trampoline_005c0dd0:\n\t"
    "pushl %ebp\n\t"
    "movl %esp, %ebp\n\t"
    "pushl %ebx\n\t"
    "pushl %esi\n\t"
    "pushl %edi\n\t"
    "movl 8(%ebp), %esi\n\t"
    "movl 12(%ebp), %ecx\n\t"
    "movl 16(%ebp), %edx\n\t"
    "movl 20(%ebp), %ebx\n\t"
    "movl %esp, 0(%ebx)\n\t"
    "xorl %eax, %eax\n\t"
    "pushl %edx\n\t"
    "call *%esi\n\t"
    "movl %esp, 4(%ebx)\n\t"
    "movl %eax, 8(%ebx)\n\t"
    "addl $4, %esp\n\t"
    "popl %edi\n\t"
    "popl %esi\n\t"
    "popl %ebx\n\t"
    "popl %ebp\n\t"
    "ret\n\t");

// cdecl on i386: every argument arrives on the stack, the callee keeps nothing
// and pops nothing, and the return is void. `samples` receives three
// consecutive words -- ESP before the push, ESP after the return, and the full
// 32-bit EAX at the return.
extern "C" void openspore_probe_trampoline_005c0dd0(void* target, void* receiver,
                                                    std::uint32_t decoy_word,
                                                    std::uint32_t* samples);

namespace openspore::reconstruction::pkg_swarm_w1_005c0dd0 {
namespace {

// The fixture is deliberately much larger than the observed extent, so a decoy
// can be planted anywhere from the receiver's own first word out to +0x5f and a
// passing case can never be explained by "there was no room for a decoy".
constexpr std::size_t kFixtureBytes = 0x60;

// How many times the decoy dispatch table was entered. It must stay 0.
int g_decoy_slot_calls = 0;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The decoy table's slots. Each would return a different byte if the body ever
// dispatched, and each counts its own entry so a dispatch is observable even if
// the returned value happened to coincide. Never called.
std::uint8_t decoy_slot_4() {
  ++g_decoy_slot_calls;
  return 0xa1;
}
std::uint8_t decoy_slot_14() {
  ++g_decoy_slot_calls;
  return 0xa2;
}
std::uint8_t decoy_slot_15() {
  ++g_decoy_slot_calls;
  return 0xa3;
}
std::uint8_t decoy_slot_26() {
  ++g_decoy_slot_calls;
  return 0xa4;
}
std::uint8_t decoy_slot_29() {
  ++g_decoy_slot_calls;
  return 0xa5;
}
std::uint8_t decoy_slot_33() {
  ++g_decoy_slot_calls;
  return 0xa6;
}

using DecoySlot = std::uint8_t (*)();

// The value each decoy slot would return, in the same order as the recorded slot
// indices below. All six are distinct from one another and from every value the
// other cases plant, so a dispatch reconstruction would have been visible in the
// return value as well as in the invocation counter.
constexpr std::uint8_t kDecoySlotValues[kReferencedSlotCount] = {0xa1, 0xa2, 0xa3,
                                                                 0xa4, 0xa5, 0xa6};

// A dispatch-shaped table, occupied at exactly the six indices the committed
// vtables export records for this body and empty everywhere else -- sparse in
// the same way the real tables are. The indices come from the recorded constant
// rather than from a hand-counted initialiser list, so case J7 is what ties the
// decoy to the evidence.
DecoySlot* decoy_table() {
  static DecoySlot table[34];
  static const DecoySlot slots[kReferencedSlotCount] = {
      decoy_slot_4, decoy_slot_14, decoy_slot_15,
      decoy_slot_26, decoy_slot_29, decoy_slot_33};
  for (std::size_t index = 0; index < 34u; ++index) {
    table[index] = nullptr;
  }
  for (std::size_t index = 0; index < kReferencedSlotCount; ++index) {
    table[kReferencedSlotIndices[index]] = slots[index];
  }
  return table;
}

// A receiver, as raw bytes. The struct exists so a fixture can be byte-copied
// and compared; the reconstruction never sees it.
struct ReceiverFixture {
  std::uint8_t bytes[kFixtureBytes];
};

// A decoy byte for offset `index` that is guaranteed to differ from `planted`, so
// every neighbour of the real field is a real decoy and no case can pass by
// accidentally planting the same value twice.
std::uint8_t decoy_for(std::size_t index, std::uint8_t planted) {
  std::uint8_t candidate =
      static_cast<std::uint8_t>(0x40u + ((index * 11u) % 0x3fu));
  while (candidate == planted) {
    candidate = static_cast<std::uint8_t>(candidate + 0x20u);
  }
  return candidate;
}

// A receiver whose byte at 0x24 is `value_at_flag` and whose every other byte in
// the fixture is a decoy.
ReceiverFixture make_receiver(std::uint8_t value_at_flag) {
  ReceiverFixture receiver;
  for (std::size_t index = 0; index < kFixtureBytes; ++index) {
    receiver.bytes[index] = decoy_for(index, value_at_flag);
  }
  receiver.bytes[kReceiverFlagByteDisplacement] = value_at_flag;
  return receiver;
}

SporepediaByteRecord* as_record(ReceiverFixture& receiver) {
  return reinterpret_cast<SporepediaByteRecord*>(&receiver);
}

std::uint8_t byte_of(const ReceiverFixture& receiver, std::size_t offset) {
  return receiver.bytes[offset];
}

void write_word(ReceiverFixture& receiver, std::size_t offset,
                const void* value) {
  std::memcpy(&receiver.bytes[offset], value, sizeof(void*));
}

// -- the probe ---------------------------------------------------------------
// Three facts are measured through the trampoline above and not through the C++
// calling convention, because the convention is the thing under test: what
// register carried the receiver, what the full 32-bit return register held, and
// what was left on the stack.
//
// `esp_before_push` is the trampoline's own ESP, i.e. the caller's ESP at the
// call. The residual it is compared against is unchanged from the inline-asm
// form this replaced: the push moves ESP down four, the call moves it down four
// more, and a bare `RET` gives one of those back, so a callee that popped
// nothing leaves the pushed word in place and a `RET 4` leaves nothing.
struct CallSamples {
  std::uint32_t esp_before_push;
  std::uint32_t esp_after_return;
  std::uint32_t eax_after_return;
};
// The trampoline writes the three samples as three consecutive 32-bit words
// through a plain `std::uint32_t*`, so the block it fills must be exactly that:
// no padding, no tail padding, nothing reordered.
static_assert(sizeof(CallSamples) == 3 * sizeof(std::uint32_t),
              "the trampoline writes the three samples as three consecutive words");
static_assert(alignof(CallSamples) == alignof(std::uint32_t),
              "the trampoline writes the three samples as three consecutive words");

struct CallProbe {
  std::uint32_t esp_before_push = 0;
  std::uint32_t esp_after_return = 0;
  std::uint32_t eax_after_return = 0;
  std::uint8_t al_after_return = 0;
};

CallProbe call_probe(SporepediaByteRecord* receiver, std::uint32_t decoy_word) {
  CallSamples samples = {0u, 0u, 0u};

  // The address of an extern "C" function is handed to the trampoline as a
  // pointer, so the trampoline can call it indirectly without either compiler
  // needing to know which function it is. Under the PIE link the taking of this
  // address is a GOT load, and the value that reaches the trampoline is the
  // runtime address, which is what a `call *` needs.
  ::openspore_probe_trampoline_005c0dd0(
      reinterpret_cast<void*>(&re_005c0dd0), receiver, decoy_word,
      reinterpret_cast<std::uint32_t*>(&samples));

  CallProbe probe;
  probe.esp_before_push = samples.esp_before_push;
  probe.esp_after_return = samples.esp_after_return;
  probe.eax_after_return = samples.eax_after_return;
  probe.al_after_return = static_cast<std::uint8_t>(samples.eax_after_return & 0xffu);
  return probe;
}

// -- the cases ---------------------------------------------------------------

// A. REFUTE "a constant stub" and REFUTE "a predicate that normalises to 0/1".
// Six byte values, each planted in a receiver whose every other byte is a
// decoy. A body that returned a fixed value, or that folded the byte to 0/1,
// cannot return all six unchanged.
void case_value_is_the_byte_verbatim() {
  static const std::uint8_t values[] = {0x00, 0x01, 0x7f, 0x80, 0xfe, 0xff};
  for (std::size_t index = 0; index < sizeof values / sizeof values[0]; ++index) {
    const std::uint8_t planted = values[index];
    ReceiverFixture receiver = make_receiver(planted);
    const std::uint8_t got = re_005c0dd0(as_record(receiver));
    if (got != planted) {
      std::fprintf(stderr,
                   "FAILED: A: the returned byte is 0x%02x for a planted 0x%02x\n",
                   static_cast<unsigned>(got), static_cast<unsigned>(planted));
      ++g_failures;
    }
  }
  // The "default true" stub specifically: a zero byte has to come back as zero.
  ReceiverFixture zero = make_receiver(0x00);
  check(re_005c0dd0(as_record(zero)) == 0x00u,
        "A: a zero byte in the receiver comes back as zero, so nothing defaults to true");
  // The "predicate" stub: a byte that is neither 0 nor 1 has to survive.
  ReceiverFixture odd = make_receiver(0x80);
  check(re_005c0dd0(as_record(odd)) == 0x80u,
        "A: 0x80 is returned as 0x80, so the value is not folded to 0 or 1");
}

// B. REFUTE a wrong displacement. Every byte of the fixture other than 0x24
// differs from the planted one, so a read anywhere else returns a different
// number. For each candidate displacement below the case first asserts that the
// byte really is a decoy, and only then that the result is not it, so no part of
// the case can pass vacuously.
void case_displacement_is_0x24() {
  const std::uint8_t planted = 0x5c;
  ReceiverFixture receiver = make_receiver(planted);
  const std::uint8_t got = re_005c0dd0(as_record(receiver));

  static const std::size_t kCandidateDisplacements[] = {
      0x00, 0x01, 0x20, 0x21, 0x22, 0x23, 0x25, 0x26, 0x27, 0x28, 0x2c, 0x3f};
  for (std::size_t index = 0;
       index < sizeof kCandidateDisplacements / sizeof kCandidateDisplacements[0];
       ++index) {
    const std::size_t displacement = kCandidateDisplacements[index];
    if (displacement == kReceiverFlagByteDisplacement) {
      continue;
    }
    if (byte_of(receiver, displacement) == planted) {
      std::fprintf(stderr, "FAILED: B0: the decoy at +0x%02zX is not a decoy\n",
                   static_cast<unsigned>(displacement));
      ++g_failures;
    }
  }
  check(got == planted,
        "B1: the byte returned is the one at +0x24, not the decoy at any of the twelve "
        "other candidate displacements (0x00, 0x01, 0x20..0x23, 0x25..0x28, 0x2c, 0x3f)");

  // And the mirror: change ONLY the byte at 0x24 and the result must follow it,
  // with every decoy left alone.
  ReceiverFixture moved = receiver;
  moved.bytes[kReceiverFlagByteDisplacement] = 0x2b;
  check(re_005c0dd0(as_record(moved)) == 0x2bu,
        "B2: moving only the byte at +0x24 moves only the result");
  check(moved.bytes[0x23] == receiver.bytes[0x23] &&
            moved.bytes[0x25] == receiver.bytes[0x25],
        "B3: the neighbouring decoys were not touched on the way");
}

// C. REFUTE a word- or dword-wide read at the right displacement. 0x24..0x27
// are EF BE AD DE, so the dword the receiver holds at 0x24 is 0xDEADBEEF.
//
// An honest limit on what the RETURNED VALUE can show, stated because it would
// otherwise look like a stronger check than it is: a word read at 0x24 and a
// byte read at 0x24 have the SAME low byte, so no assertion about the returned
// value alone can separate them. Three things can, and all three are here: the
// declared width (C4), the machine width read off the instruction length (C5),
// and the full-register differential measurement (C6), which is the one that a
// wider read actually fails.
void case_width_is_one_byte() {
  ReceiverFixture receiver = make_receiver(0xef);
  receiver.bytes[0x25] = 0xbe;
  receiver.bytes[0x26] = 0xad;
  receiver.bytes[0x27] = 0xde;

  std::uint32_t dword_at_flag = 0;
  std::memcpy(&dword_at_flag, &receiver.bytes[kReceiverFlagByteDisplacement],
              sizeof dword_at_flag);

  check(dword_at_flag == 0xdeadbeefu,
        "C1: the receiver really does hold 0xDEADBEEF at +0x24, so the decoys are in place");
  check(re_005c0dd0(as_record(receiver)) == 0xefu,
        "C2: the returned byte is 0xEF and not the dword the receiver holds there");
  check(kReturnWidthBytes == 1u,
        "C3: the recorded machine return width is the one byte AL was written");
  // The reconstruction's own declared width, taken off the call expression
  // itself rather than off a comment.
  check(sizeof(decltype(re_005c0dd0(as_record(receiver)))) == 1u,
        "C4: the reconstruction's declared return type is one byte wide");
  // The machine width, from the instruction length: 8A 41 24 is three bytes and
  // 0F B6 41 24 is four, so a zero-extending form cannot fit in a four-byte body
  // that also has to contain its terminator.
  check(kLoadLength == 3u && kLoadLength + 1u == kSpanBytes && kBodyBytes[0] == 0x8au,
        "C5: the load is the three-byte 0x8A form, so it cannot be the four-byte 0x0F 0xB6 form");
  // And the width, MEASURED. This is the check a returned value alone cannot
  // supply, and it is the one that kills a wider read.
  //
  // The shape matters, and it changed once. The first version zeroed EAX in the
  // probe and asserted `bits 8..31 == 0` afterwards, on the reasoning that a
  // zero entry state would make the upper bytes a measurement rather than an
  // unknown. That reasoning depends on the MODEL BUILD carrying the probe's
  // entry state through to the return, and it does not: `re_005c0dd0` compiled
  // at -O0 by clang is
  //     movl -4(%ebp), %eax ; movl %eax, -8(%ebp) ; movl -8(%ebp), %eax
  //     movb 36(%eax), %al
  // -- the receiver POINTER is materialised in EAX and then only AL is written,
  // so what arrives above the field is the receiver's own address, not the
  // probe's zero. g++ happens to emit `movzbl (%eax), %eax` instead, which
  // zero-extends and made the old check pass. The check was therefore a
  // statement about one compiler's codegen, not about the width, and the gate
  // caught it once the segfault was out of the way.
  //
  // So the control is differential instead, and it needs NO assumption at all
  // about what the upper bytes contain. The receiver's ADDRESS and its byte at
  // +0x24 are held fixed and the probe is run twice, changing only the three
  // bytes that follow the field. A read of exactly one byte cannot see them, so
  // the whole 32-bit return register must come back bit-identical; a word read
  // would carry +0x25 into bits 8..15 and a dword read would carry
  // +0x25..+0x27. That kills BOTH wider forms, including the word read the old
  // zeroing formulation could not have distinguished on its own.
  const CallProbe probe = call_probe(as_record(receiver), 0u);
  receiver.bytes[0x25] = 0x11;
  receiver.bytes[0x26] = 0x22;
  receiver.bytes[0x27] = 0x33;
  const CallProbe probe_moved = call_probe(as_record(receiver), 0u);
  // Same object, same address, same byte at the field -- only the bytes a wider
  // read would have swallowed have moved. If they still do not reach the return
  // register, nothing wider than one byte was read at +0x24.
  check(receiver.bytes[kReceiverFlagByteDisplacement] == 0xefu &&
            (probe.eax_after_return & 0xffu) == 0xefu &&
            (probe_moved.eax_after_return & 0xffu) == 0xefu,
        "C6: the two probe runs differ only at +0x25..+0x27, and both still returned "
        "the planted byte, so the runs really are comparable");
  check(probe.eax_after_return == probe_moved.eax_after_return,
        "C6: holding the receiver's address and its byte at +0x24 fixed, moving the three "
        "bytes that follow the field does not change any bit of the 32-bit return "
        "register: a one-byte read cannot see them, a word read would carry +0x25 and a "
        "dword read would carry +0x25..+0x27, so nothing wider than one byte was read");
}

// D. REFUTE a model that also writes. The body is a load and a return; every
// byte of the fixture, in both directions of the observed extent, is compared
// before and after.
void case_no_receiver_byte_changes() {
  ReceiverFixture receiver = make_receiver(0x9d);
  const ReceiverFixture before = receiver;

  re_005c0dd0(as_record(receiver));

  std::size_t changed = 0;
  for (std::size_t index = 0; index < kFixtureBytes; ++index) {
    if (receiver.bytes[index] != before.bytes[index]) {
      ++changed;
    }
  }
  check(changed == 0u,
        "D: no byte of the receiver changes, at +0x24 or anywhere else in the fixture");
  check(kReceiverFlagByteDisplacement < kFixtureBytes,
        "D: the field lies inside the compared region, so D is not vacuous");
}

// E. REFUTE the two-level dereference. The receiver's first word is made a
// POINTER to a second object whose byte at 0x24 is different. A reconstruction
// that treated the receiver as a holder and read through its first word would
// return the second object's byte.
void case_receiver_is_not_a_holder() {
  ReceiverFixture pointee = make_receiver(0x77);
  ReceiverFixture holder = make_receiver(0x2c);
  write_word(holder, 0x00, &pointee);

  check(byte_of(holder, 0x00) != byte_of(holder, kReceiverFlagByteDisplacement),
        "E0: the receiver's first word is a decoy that differs from its own +0x24");
  check(byte_of(pointee, kReceiverFlagByteDisplacement) == 0x77u,
        "E0: the pointee carries a different byte at +0x24");

  const std::uint8_t got = re_005c0dd0(as_record(holder));
  check(got == 0x2cu, "E1: the result is the HOLDER's own byte at +0x24");
  check(got != 0x77u,
        "E2: the result is not the pointee's byte at +0x24, so there is no second dereference");

  // And the mirror: the same receiver address now holding the other object.
  ReceiverFixture first = make_receiver(0x11);
  ReceiverFixture second = make_receiver(0x22);
  check(re_005c0dd0(as_record(first)) == 0x11u && re_005c0dd0(as_record(second)) == 0x22u,
        "E3: two receivers at two addresses give two different results");
}

// F. REFUTE a value that came from a baked-in address, a global, or a register
// other than ECX. Two objects, handed to the SAME function through the
// trampoline so the receiver really arrives in ECX each time.
void case_receiver_is_the_object_in_ecx() {
  ReceiverFixture first = make_receiver(0x33);
  ReceiverFixture second = make_receiver(0xcc);

  const CallProbe probe_first = call_probe(as_record(first), 0x1234u);
  const CallProbe probe_second = call_probe(as_record(second), 0x4321u);

  check(probe_first.al_after_return == 0x33u,
        "F1: ECX carrying the first object yields the first object's byte");
  check(probe_second.al_after_return == 0xccu,
        "F2: ECX carrying the second object yields the second object's byte");
  check(probe_first.al_after_return != probe_second.al_after_return,
        "F3: the result follows the register, so no address is baked into the body");
  check(re_005c0dd0(as_record(first)) == 0x33u && re_005c0dd0(as_record(second)) == 0xccu,
        "F4: and the direct C++ calls agree with the measured ones");
}

// G. REFUTE a dispatch-based reconstruction. The receiver's +0x00 is made to
// point at a table whose six occupied slots would each return a different byte
// and count their own entry. Nothing may change and nothing may be entered.
void case_no_dispatch_through_the_receiver() {
  ReceiverFixture receiver = make_receiver(0x6b);
  write_word(receiver, 0x00, decoy_table());
  g_decoy_slot_calls = 0;

  const std::uint8_t got = re_005c0dd0(as_record(receiver));

  check(got == 0x6bu,
        "G1: a dispatch word at +0x00 does not change the returned byte");
  check(g_decoy_slot_calls == 0,
        "G2: no decoy slot was entered, so nothing dispatched through +0x00");
  // Every one of the six slot values is distinct from the planted byte, so a
  // dispatch reconstruction would have been visible in the return value too.
  bool any_slot_matches = false;
  for (std::size_t index = 0; index < kReferencedSlotCount; ++index) {
    any_slot_matches = any_slot_matches || kDecoySlotValues[index] == got;
  }
  check(!any_slot_matches,
        "G3: none of the six decoy slot values equals the result, so G1 is not a coincidence");
  check(kReturnWidthBytes == 1u,
        "G4: the body declares no slot boundary, which is what the dispatch record's zero says");
  // And the pointer really is there, so G1 is not passing for want of a decoy.
  check(decoy_table()[kReferencedSlotIndices[0]] != nullptr &&
            decoy_table()[kReferencedSlotIndices[kReferencedSlotCount - 1]] != nullptr,
        "G5: the decoy table really is occupied at the first and last recorded indices");
}

// H. REFUTE "the function takes an argument" and REFUTE a `RET 4` terminator.
// A word is pushed, the function is called, and ESP is sampled after the return.
// A zero-byte callee cleanup leaves the pushed word on the stack, so the residual
// is exactly four; a `RET 4` would have eaten it and left a residual of zero.
void case_stack_shape_is_a_bare_ret() {
  ReceiverFixture receiver = make_receiver(0x3e);
  const CallProbe probe = call_probe(as_record(receiver), 0xdeadbeefu);

  check(probe.esp_after_return + 4u == probe.esp_before_push,
        "H1: the pushed word is still on the stack after the return, so the callee popped 0 bytes");
  check(kStackCleanupBytes == 0u && kStackArgumentSlots == 0u,
        "H2: the recorded cleanup is zero bytes over zero argument slots");
  check(kRetOffset == 3u && kBodyBytes[kRetOffset] == 0xc3u,
        "H3: the fourth body byte is a bare RET (0xC3), not a RET with an immediate");
  check(kLoadLength + 1u == kSpanBytes,
        "H4: a three-byte load plus a one-byte RET is the whole four-byte span, so no immediate can hide");
  check(probe.al_after_return == 0x3eu,
        "H5: and the call still produced the right byte, so the measurement reached the body");
}

// I. The return register, sampled in full. Bits 0..7 are asserted as the field's
// byte. Bits 8..31 are NOT claimed as a property of the MACHINE at an arbitrary
// call site, because the 8A form never sets them and their value is whatever the
// caller left. The controlled-EAX measurement in case C6 is a claim about this
// reconstruction under a probe-chosen entry state; this case is the one that says
// plainly what stays open.
void case_return_register_width() {
  ReceiverFixture receiver = make_receiver(0xb6);
  const CallProbe probe = call_probe(as_record(receiver), 0u);

  check((probe.eax_after_return & 0xffu) == 0xb6u,
        "I1: bits 0..7 of the return register carry the field's byte");
  // NOT ASSERTED for the machine, and deliberately: what bits 8..31 of EAX hold
  // at a real call site. The load is 8A 41 24, a PARTIAL register write -- 0F B6
  // 41 24 would be the zero-extending form and is four bytes -- so the body
  // leaves them as the caller had them, and both direct callers read AL alone:
  // 0x00adfeb2 `MOV byte ptr [ESI+0x170], AL` and 0x00de5278 `TEST AL, AL`. No
  // value for them is claimed, here or in the model. (The probe does zero EAX on
  // entry, so C6 and I2 measure what happens under that controlled state; that is
  // a statement about the probe, and it is labelled as one.)
  check(kLoadIsPartialRegisterWrite,
        "I2: the recorded form is a partial register write, which is why the upper bytes are excluded");
  check(probe.eax_after_return != 0u,
        "I3: the low byte is non-zero here, so the return register was not left dead");
}

// J. The recorded evidence, checked against itself. A transcription slip in a
// constant would otherwise be reproduced faithfully by the test and never
// noticed.
void case_recorded_constants() {
  check(kBodyBytes[0] == 0x8au && kBodyBytes[1] == 0x41u &&
            kBodyBytes[2] == 0x24u && kBodyBytes[3] == 0xc3u,
        "J1: the recorded body is 8A 41 24 C3");
  check(kSpanBytes == 4u && kInstructionCount == 2u,
        "J2: the span is 4 bytes over 2 instructions");
  check(kLoadLength == 3u && kLoadDisplacementByte == 0x24u,
        "J3: the load is 3 bytes and its displacement byte is 0x24");
  check(kReceiverFlagByteDisplacement == 0x24u,
        "J4: the receiver displacement is 0x24, the same byte as the disp8");
  check(kReceiverObservedExtent == 0x25u &&
            sizeof(SporepediaByteRecord) == 0x25u,
        "J5: the observed extent is the displacement plus the one byte read");
  check(kReferencedTableCount == 12u && kReferencedSlotCount == 6u,
        "J6: twelve tables reference this body at six different slot indices");
  check(kReferencedSlotIndices[0] == 4u && kReferencedSlotIndices[1] == 14u &&
            kReferencedSlotIndices[2] == 15u && kReferencedSlotIndices[3] == 26u &&
            kReferencedSlotIndices[4] == 29u && kReferencedSlotIndices[5] == 33u,
        "J7: the six recorded slot indices are intact and all distinct");
  check(kReferencedTableAddresses[0] == 0x013f7cc0u &&
            kReferencedTableAddresses[11] == 0x01489414u,
        "J8: the first and last recorded table addresses are intact");
  // Six distinct indices is the reason no slot is declared anywhere: a single
  // slot number cannot be right for six different ones.
  bool indices_distinct = true;
  for (std::size_t outer = 0; outer < kReferencedSlotCount; ++outer) {
    for (std::size_t inner = outer + 1; inner < kReferencedSlotCount; ++inner) {
      indices_distinct = indices_distinct &&
                         kReferencedSlotIndices[outer] != kReferencedSlotIndices[inner];
    }
  }
  check(indices_distinct, "J9: the recorded slot indices really are six different slots");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_005c0dd0

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_005c0dd0;
  case_recorded_constants();
  case_value_is_the_byte_verbatim();
  case_displacement_is_0x24();
  case_width_is_one_byte();
  case_no_receiver_byte_changes();
  case_receiver_is_not_a_holder();
  case_receiver_is_the_object_in_ecx();
  case_no_dispatch_through_the_receiver();
  case_stack_shape_is_a_bare_ret();
  case_return_register_width();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
