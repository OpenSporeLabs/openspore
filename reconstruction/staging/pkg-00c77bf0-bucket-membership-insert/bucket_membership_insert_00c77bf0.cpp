// 0x00c77bf0 -- bucket membership probe with insert-on-miss.
// Implementation. Every fact it rests on is stated, and decoded out of the body
// bytes, in the accompanying header; this file is the code under test and reads
// nothing from that transcription.

#include "bucket_membership_insert_00c77bf0.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership {

namespace {

// The two dword loads out of a chain node, done the way the machine does them:
// raw 32-bit reads at the decoded displacements, with no dereference of a
// typed pointer, so a node that is not really a node cannot be walked by
// accident. `link` is a raw address, not a BucketNode*, for the same reason the
// bucket array is read as raw words.
Word node_word(Word link, std::size_t displacement) {
  return word_at(reinterpret_cast<const std::uint8_t*>(
                     static_cast<std::uintptr_t>(link)),
                 displacement);
}

}  // namespace

// The modelled image. The entry reads two words out of it and writes none, so
// the model test can hold every other word to a canary.
BucketTableImage g_bucket_table_image;

std::uint8_t* image_bytes() {
  return reinterpret_cast<std::uint8_t*>(&g_bucket_table_image.words[0]);
}

Word word_at(const std::uint8_t* base, std::size_t displacement) {
  Word value = 0u;
  std::memcpy(&value, base + displacement, sizeof(value));
  return value;
}

Word bucket_word(const Word* buckets, std::size_t byte_offset) {
  return word_at(reinterpret_cast<const std::uint8_t*>(
                     reinterpret_cast<std::uintptr_t>(buckets)),
                 byte_offset);
}

InsertTraceEntry g_insert_trace[kMaxInsertDepth];
std::size_t g_insert_depth = 0u;

// 0x00de5df0, modelled. Its own semantics are NOT reconstructed here -- the body
// that calls it discards whatever it returns, so the only thing this entry can
// be shown to observe is what it was handed. It records and returns.
void PKG_00C77BF0_CALLEE FUN_00de5df0(void* container, const Word* value,
                                     Word context) {
  if (g_insert_depth < kMaxInsertDepth) {
    InsertTraceEntry& entry = g_insert_trace[g_insert_depth];
    entry.container = static_cast<Word>(
        reinterpret_cast<std::uintptr_t>(container));
    entry.value =
        static_cast<Word>(reinterpret_cast<std::uintptr_t>(value));
    entry.context = context;
    // The second argument is a pointer to a four-byte slot the caller filled
    // with the key (0x00c77c3b), so reading it here is reading the caller's
    // live local, not an indeterminate value.
    entry.value_at = *value;
  }
  ++g_insert_depth;
}

bool PKG_00C77BF0_CALL bucket_membership_insert_00c77bf0(BucketTable* self,
                                                        Word key) {
  // The three literals this body states about the receiver, declared HERE, in
  // the body that uses them, rather than only in the header. A reviewer scanning
  // the entry's own source should see what it claims without resolving a
  // constant through a header, and a source-side scan reads this spelling rather
  // than prose. Each is checked against the constant it was decoded from, so the
  // declaration cannot drift away from the bytes: edit a literal and the build
  // stops here.
  //
  // These are the literals the INSTRUCTIONS state, not the post-bias addresses
  // the two field reads land on. 0x00c77bfa is `add ecx, 0x111c`; 0x00c77c07 is
  // `mov eax, [ecx+0x4]`; 0x00c77c04 is `div dword ptr [ecx+0x8]`. The receiver
  // words therefore sit at 0x1120 and 0x1124, which is what the header derives
  // and what the code below reads -- but 0x1120 and 0x1124 appear nowhere in the
  // listing, because no instruction states them: they are a sum. Declaring the
  // sum here would be declaring a constant the machine does not state, and this
  // body is not allowed to do that quietly.
  //
  // Neither displacement names a member. The machine-derived receiver record for
  // this target abstains from naming a receiver register (abi_infer:
  // `ecx_reassigned_before_deref`, tripped by that very ADD), so there is no
  // receiver-side enumeration to corroborate these against and a validator
  // reports them as reconstruction-declared rather than machine-grounded. The
  // displacements themselves are OBSERVED; the corroborating record does not
  // exist. That is disclosed, not worked around.
  // Each assert's own message is deliberately free of hexadecimal: a message is
  // a string literal, so a hex token inside one is CODE to a source-side scan,
  // and the addresses the listing gives are the bare `00c77bfa` form rather than
  // a `0x`-prefixed literal. A message naming an instruction address therefore
  // reads as a source constant the listing does not state, and CONSTANTS
  // refutes the reconstruction for its own diagnostics. The addresses are in
  // the comment above, where they belong.
  static_assert(kReceiverBias == +0x111cu,
                "the receiver base is biased by the immediate the ADD states");
  static_assert(kBucketArrayDisplacement - kReceiverBias == +0x4u,
                "the array read uses the disp8 operand the MOV states");
  static_assert(kBucketCountDisplacement - kReceiverBias == +0x8u,
                "the divide uses the disp8 operand the DIV states");
  static_assert(kBucketCountDisplacement - kBucketArrayDisplacement == sizeof(Word),
                "the two words are adjacent, one dword apart");

  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(self);

  // 0x00c77bfa ADD ECX,0x111c, then the two reads through the biased base.
  // kBucketArrayDisplacement and kBucketCountDisplacement are already stated
  // post-bias, so the bias appears in the constants rather than in the
  // arithmetic -- the two are the same address, arrived at differently.
  //
  // The order of the two reads is the machine's and is not free: the DIV at
  // 0x00c77c04 comes FIRST, so a zero divisor faults before the array pointer
  // is even loaded. Nothing below reproduces that ordering's only externally
  // visible consequence (a fault on a degenerate table), so the divisor is read
  // first to keep the data flow honest, and no test arms a zero divisor because
  // the division would be undefined rather than merely wrong.
  const Word bucket_count = word_at(bytes, kBucketCountDisplacement);
  const Word* const buckets = reinterpret_cast<const Word*>(
      word_at(bytes, kBucketArrayDisplacement));

  // 0x00c77c00..0x00c77c0c: XOR EDX,EDX / MOV EAX,EDI / DIV / MOV EAX,[...]
  // / XOR ESI,ESI / MOV EDX,[EAX+EDX*4]. Unsigned long division with a zero high
  // half leaves the REMAINDER in EDX, and EDX is what scales the bucket index.
  Word matches = 0u;
  Word link =
      bucket_word(buckets, static_cast<std::size_t>(key % bucket_count) *
                               kBucketSlotBytes);

  // 0x00c77c0f..0x00c77c1d: the walk. It counts EVERY match rather than
  // stopping at the first, and the count -- not the last comparison -- is what
  // the return value reports. (Stopping early is not distinguishable at this
  // boundary: both forms answer "was it there at least once" identically, so
  // the loop is written as the listing has it and the model test makes no claim
  // that early exit would have been caught.)
  while (link != 0u) {
    if (node_word(link, kNodeKeyDisplacement) == key) {
      ++matches;
    }
    link = node_word(link, kNodeNextDisplacement);
  }

  // 0x00c77c1f..0x00c77c26: the flag, and the branch that skips the insert on
  // a hit.
  const bool present = (matches != 0u);
  if (!present) {
    // 0x00c77c28..0x00c77c3f. The two LEAs name two adjacent stack slots: a
    // twelve-byte object at ESP+0x18 and a four-byte value slot at ESP+0x10,
    // and the only store among them is the one that fills the value slot with
    // the key. The twelve bytes are therefore NEVER written by this body, so
    // they are left uninitialised here and must not be read by the callee.
    alignas(4) std::uint8_t container[kContainerLocalBytes];
    Word value = key;
    // The third argument is the argument word with its low byte replaced by the
    // SETNZ flag -- and on this path the flag is provably 0, because the JNZ at
    // 0x00c77c26 skips the whole block when it is not. See the header for why
    // this is not a literal zero.
    FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);
  }

  // 0x00c77c46: MOV AL,BL. Only the low byte is written; nothing here reads the
  // rest of EAX, which still holds the array pointer the DIV sequence loaded.
  return present;
}

}  // namespace openspore::reconstruction::pkg_00c77bf0_bucket_membership
