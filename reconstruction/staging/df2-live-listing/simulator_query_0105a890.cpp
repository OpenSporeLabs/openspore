// Candidate reconstruction of FUN_0105a890, x86-32.
// Body 0x0105a890 .. 0x0105aa4e, entry 0x0105a890, single exit 0x0105aa4d.
//
// PROVENANCE OF THE LISTING. The machine evidence this file was written from
// is the 155-instruction body read from the live GhidraMCP bridge
// (/disassemble_function at 127.0.0.1:8089), NOT the committed evidence pack:
// reconstruction/evidence/0105a890/evidence.json stores the disassembly
// category as a {"truncated": true, "preview": ...} envelope (12377 canonical
// bytes against the collector's 12000-byte compact() budget), so the pack holds
// no instruction array and its preview is a fragment, not a body. The pack's
// own machine parse record declares 155 instructions, which is the count the
// live bridge returned, so the listing below is the whole body.
//
// ABI, derived by hand from the listing. The decompiler emits a three-argument
// prototype with no receiver here, but that is a symptom of the same frame
// miscalibration the pack records ("ecx_read_without_deref", "push ebp with no
// mov ebp,esp"), not an observation: the body copies ECX into ESI at entry and
// loads it straight back into ECX before the 0x0105a050 call, so ECX carries a
// receiver that this body forwards and never dereferences.
//   ECX at entry      the receiver, forwarded and never dereferenced here
//   entry ESP + 0x4   the first ordinary stack argument; the body reads the
//                     word at displacement 0x124 of it three times
//   entry ESP + 0x8   the second ordinary stack argument
//   entry ESP + 0xc   the third ordinary stack argument
//   entry ESP + 0x10  a fourth slot the body pops and never reads, named in
//                     the signature below only so that the declared callee-pop
//                     width matches the RET 0x10 the listing shows
//   termination       RET 0x10, so the callee pops all four
//
// The receiver has no displacement in this body and no struct member is named
// anywhere in this file, because the listing establishes neither. The single
// displacement that is read (0x124) belongs to the first stack argument, not
// to the receiver. The four indirect transfers are the real ones the listing
// shows: a word is loaded out of an object and called through the register it
// was loaded into.

#include <cstddef>
#include <cstdint>
#include <cstring>

#if defined(_MSC_VER)
#define DF2_THISCALL __thiscall
#else
#define DF2_THISCALL __attribute__((thiscall))
#endif

extern "C" {

// 0x01021260 -- ECX = the receiver, no stack argument. The first thing the body
// does with the receiver.
void DF2_THISCALL op_01021260(void* receiver);

// 0x0105a050 -- ECX = the receiver and four stack arguments, callee-popped.
// Its result gates everything that follows; a zero result returns immediately.
bool DF2_THISCALL op_0105a050(void* receiver,
                              void* first,
                              unsigned int second,
                              unsigned int third,
                              unsigned int fourth);

// 0x006e87e0 -- ECX = the word the first argument holds at displacement 0x124,
// no stack argument. The body calls it twice and keeps the second result.
void* DF2_THISCALL op_006e87e0(void* anchor);

// 0x01058680 -- one stack argument, caller-cleaned (ADD ESP,0x4).
bool __cdecl op_01058680(void* subject);

// 0x010534c0 -- one stack argument, caller-cleaned (ADD ESP,0x4). The argument
// is the second match plus the displacement 0x7c.
bool __cdecl op_010534c0(const void* offset_subject);

// 0x00ae6760, 0x00b67720, 0x00b67740 -- one stack argument each,
// caller-cleaned (ADD ESP,0x4). Three alternative lookups tried in that order.
void* __cdecl op_00ae6760(const void* subject);
void* __cdecl op_00b67720(const void* subject);
void* __cdecl op_00b67740(const void* subject);

// 0x01053320, 0x01053240, 0x010533d0 -- one stack argument each,
// caller-cleaned (ADD ESP,0x4), one per lookup above and in the same order.
bool __cdecl op_01053320(void* found);
bool __cdecl op_01053240(void* found);
bool __cdecl op_010533d0(void* found);

// 0x01030e40 -- one stack argument, caller-cleaned (ADD ESP,0x4 at 0x0105a9a3).
// The PUSH EDI just before it belongs to the POP EDI at 0x0105aa0d, not to
// this call: the register is saved and restored around the whole block.
void* __cdecl op_01030e40(const void* subject);

// 0x00bd8460 -- one stack argument, caller-cleaned (ADD ESP,0x4).
void* __cdecl op_00bd8460(const void* subject);

// 0x00421c80 -- ECX = the address of the three-word local, one stack argument
// that the callee pops.
void DF2_THISCALL op_00421c80(unsigned int* local_words, unsigned int tag);

// 0x0067dcc0 -- ECX = the address of the same local, no stack argument. It is
// called on the local, not on a service root: the listing loads the local
// address into ECX immediately before both of its call sites.
void* DF2_THISCALL op_0067dcc0(unsigned int* local_words);

// 0x00421cf0 -- ECX = the address of the local, no stack argument. The
// counterpart of 0x00421c80 on the path that leaves the block.
void DF2_THISCALL op_00421cf0(unsigned int* local_words);

// 0x00cb5bb0 -- ECX = the word the first argument holds at displacement 0x124,
// no stack argument. Runs on every path that got past the two early returns.
void DF2_THISCALL op_00cb5bb0(void* anchor);

// 0x00a206f0 -- no stack argument and no ECX established at this site: the
// preceding call leaves ECX undefined, which the listing does not repair. The
// result is null-checked and then used as the receiver of an indirect call.
void* __cdecl op_00a206f0(void);

// 0x00435ed0 -- two stack arguments, caller-cleaned (ADD ESP,0x8).
void __cdecl op_00435ed0(unsigned int tag, unsigned int value);

}  // extern "C"

namespace {

// The two shapes of indirect transfer in this body: a word read out of an
// object at a displacement and called through the register it was loaded into.
typedef int (*TargetNoArgument)(void);
typedef void* (*TargetPointerFromWord)(const void* receiver, unsigned int word);
typedef int (*TargetThreeWords)(const void* receiver,
                                unsigned int first,
                                const void* second,
                                unsigned int third);

unsigned int load_word(const void* base, unsigned int displacement) {
  unsigned int value = 0;
  std::memcpy(&value,
              static_cast<const unsigned char*>(base) + displacement,
              sizeof(value));
  return value;
}

void* load_pointer(const void* base, unsigned int displacement) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(
      load_word(base, displacement)));
}

unsigned int word_of(const void* value) {
  unsigned int word = 0;
  std::memcpy(&word, &value, sizeof(word));
  return word;
}

unsigned int indirect_word(const void* object, unsigned int displacement) {
  return load_word(load_pointer(object, 0x0), displacement);
}

const void* offset_pointer(const void* base, std::size_t offset) {
  return static_cast<const unsigned char*>(base) + offset;
}

}  // namespace

extern "C" int DF2_THISCALL Simulator_query_FUN_0105a890(
    void* receiver,
    void* first_argument,
    unsigned int second_argument,
    unsigned int third_argument,
    unsigned int popped_but_never_read) {
  (void)popped_but_never_read;
  // 0x0105a895: the receiver is kept in ESI and forwarded, never dereferenced.
  op_01021260(receiver);

  // 0x0105a8af: the gate. A zero result leaves through the single exit, which
  // returns 1.
  if (!op_0105a050(receiver,
                   first_argument,
                   second_argument,
                   third_argument,
                   0)) {
    return 1;
  }

  // 0x0105a8bc: the word the first argument holds at displacement 0x124.
  if (load_pointer(first_argument, 0x124) == nullptr) {
    return 1;
  }

  // 0x0105a8ca: the first of two identical queries; the body then repeats it
  // and keeps the second result as the subject.
  if (op_006e87e0(load_pointer(first_argument, 0x124)) == nullptr) {
    return 1;
  }
  void* const subject = op_006e87e0(load_pointer(first_argument, 0x124));

  // The boolean the body carries in BL across the whole dispatch. It gates one
  // side effect at the end and is never returned.
  bool outcome = false;
  bool dispatched = false;

  if (subject != nullptr) {
    // 0x0105a8eb: the word at displacement 0xc, asked about the first key.
    void* const first_match = reinterpret_cast<TargetPointerFromWord>(
        indirect_word(subject, 0xc))(subject, 0xce9f6639);
    if (first_match != nullptr) {
      outcome = op_01058680(first_match);
      dispatched = true;
    } else {
      // 0x0105a90d: the same word asked about the second key. The word at
      // displacement 0x88 of the answer must be 0, 1 or 2.
      void* const second_match = reinterpret_cast<TargetPointerFromWord>(
          indirect_word(subject, 0xc))(subject, 0x3ed590d);
      if (second_match != nullptr) {
        const unsigned int kind = load_word(second_match, 0x88);
        if (kind == 0 || kind == 1 || kind == 2) {
          outcome = op_010534c0(offset_pointer(second_match, 0x7c));
          dispatched = true;
        }
      }
    }
  }

  if (!dispatched) {
    // 0x0105a946: three alternative lookups, each of which ends the dispatch
    // when it produces something.
    void* const alternative_one = op_00ae6760(subject);
    if (alternative_one != nullptr) {
      outcome = op_01053320(alternative_one);
    } else {
      void* const alternative_two = op_00b67720(subject);
      if (alternative_two != nullptr) {
        outcome = op_01053240(alternative_two);
      } else {
        void* const alternative_three = op_00b67740(subject);
        if (alternative_three != nullptr) {
          outcome = op_010533d0(alternative_three);
        } else {
          // 0x0105a99a: the last resort builds a three-word local, hands it to
          // a member of that local and destroys it again. The two immediates
          // are the only difference between the two arms.
          void* payload = op_01030e40(subject);
          bool have_payload = payload != nullptr;
          unsigned int tag = 0xf46092d3;
          if (!have_payload) {
            void* const alternate = op_00bd8460(subject);
            if (alternate == nullptr) {
              // 0x0105aa0d: nothing was built; the body restores the saved
              // register and falls into the shared tail.
            } else {
              payload = alternate;
              have_payload = true;
              tag = 0xf46093da;
            }
          }
          if (have_payload) {
            // 0x0105a9ac: the block is three words at frame displacement
            // 0x14 of the current ESP. The body never writes the words at
            // displacement 0x0 or 0x4, so they are left as the frame already
            // holds them; the only word it stores is the one at displacement
            // 0x8 (0x0105a9b5), and the same three addresses are the ones
            // 0x0105a9c0 and 0x0105aa04 hand on.
            unsigned int local_words[3];
            op_00421c80(&local_words[0], 0u);
            local_words[2] = word_of(payload);
            void* const built = op_0067dcc0(&local_words[0]);
            // 0x0105a9fb: the word at displacement 0x14 of the built object,
            // called with three stack arguments the callee pops.
            reinterpret_cast<TargetThreeWords>(indirect_word(built, 0x14))(
                built, tag, &local_words[0], 0u);
            op_00421cf0(&local_words[0]);
          }
        }
      }
    }
  }

  // 0x0105aa0e: the anchor is released on every path that reached this point.
  if (load_pointer(first_argument, 0x124) != nullptr) {
    op_00cb5bb0(load_pointer(first_argument, 0x124));
  }

  // 0x0105aa1d: the carried boolean gates one last notification.
  if (outcome) {
    void* const target = op_00a206f0();
    unsigned int produced = 0;
    if (target != nullptr) {
      // 0x0105aa2b: the word at displacement 0x20, with no argument.
      produced = static_cast<unsigned int>(
          reinterpret_cast<TargetNoArgument>(indirect_word(target, 0x20))());
    }
    op_00435ed0(0x75c412dd, produced);
  }

  // 0x0105aa47: the only exit. The body writes AL and nothing else, so the
  // value is the constant 1 and the upper three bytes of EAX are whatever the
  // last callee left; the declared int is the width the return claim is made
  // at, not a claim about those bytes.
  return 1;
}
