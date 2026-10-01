// Candidate reconstruction of App::cCameraManager::SetActiveCameraByID
// 0x007c6750 .. 0x007c6b7c, x86-32.
//
// PROVENANCE OF THE LISTING. The machine evidence this file was written from
// is the 360-instruction body read from the live GhidraMCP bridge
// (/disassemble_function at 127.0.0.1:8089), NOT the committed evidence pack:
// reconstruction/evidence/007c6750/evidence.json stores the disassembly
// category as a {"truncated": true, "preview": ...} envelope (29965 canonical
// bytes against the collector's 12000-byte compact() budget), so the pack
// holds no instruction array and its preview is a fragment, not a body. The
// pack's own machine parse record declares 360 instructions, which is the
// count the live bridge returned, so the listing below is the whole body.
//
// FRAME ARITHMETIC, derived by hand from the listing. The decompiler warns
// "Unknown calling convention" for this body because of the SEH prologue, so
// none of the parameter recovery below comes from the decompiler:
//   entry ESP + 0x0   return address
//   entry ESP + 0x4   the single ordinary stack argument; the body copies it
//                     into EBX at 0x007c6769 and reuses EBX as a receiver for
//                     the 0x0083xxxx helpers
//   ECX at entry      the receiver
//   prologue  3 SEH pushes + SUB ESP,0x30 + PUSH EBX + PUSH ESI
//             (+ PUSH EBP + PUSH EDI on the long path)
//   epilogue  POP EDI/EBP/ESI/EBX + ADD ESP,0x3c + RET 0x4
//   early exit POP ESI + POP EBX + ADD ESP,0x3c + RET 0x4
//
// RECEIVER WORDS are addressed by machine displacement only. The two
// displacements the body reaches through ECX are 0x4 and 0x10, which is the
// set the machine-derived receiver record enumerates; no struct member is
// named anywhere in this file, because the listing does not establish one.
// The indirect transfers are the real ones the listing shows: the body loads a
// word out of an object and calls through the register it loaded, and each
// call site is spelled with the displacement that word was read at.
//
// STRING POOL contents were read out of the binary at the exact immediates
// the body pushes (live bridge, /read_memory). No data-segment address is
// written as code in this file.

#include <cstddef>
#include <cstdint>
#include <cstring>

#if defined(_MSC_VER)
#define DF2_THISCALL __thiscall
#define DF2_STDCALL __stdcall
#else
#define DF2_THISCALL __attribute__((thiscall))
#define DF2_STDCALL __attribute__((stdcall))
#endif

extern "C" {

// 0x00837f30 -- ECX = the stack argument, no stack argument of its own. The
// body compares the result against 1 and takes the "current controller" branch
// when it equals 1.
int DF2_THISCALL op_00837f30(unsigned int identifier);

// 0x00838020 -- ECX = the stack argument; three stack arguments and no ADD ESP
// after the call, so the callee pops all three. The first argument is an
// out-word the body compares against 1.
void* DF2_THISCALL op_00838020(unsigned int* resolved_out,
                                 unsigned int second,
                                 unsigned int third);

// 0x00838330 -- ECX = the stack argument; two stack arguments (a string-pool
// name and a default), callee-popped. Called three times, with the property
// names read at 0x013f2ce4, 0x01410624 and 0x01410618.
void* DF2_THISCALL op_00838330(const char* name, unsigned int fallback);

// 0x008380b0 -- ECX = the stack argument; one stack argument, callee-popped.
// Called with the property name read at 0x01409070.
bool DF2_THISCALL op_008380b0(const char* name);

// 0x00841000 -- the logging entry, called four times. ECX is not established at
// any of those sites and the body always pops the arguments itself (ADD
// ESP,0xc / 0x14 / 0x18), so it is transcribed as a plain C variadic.
int __cdecl op_00841000(void* sink, const char* format, ...);

// 0x0093c5a0 -- three stack arguments, caller-cleaned (ADD ESP,0xc). The first
// is the address of a three-word local the body itself never writes; the third
// is the immediate -1.
void __cdecl op_0093c5a0(unsigned int* out_words,
                            const void* source_string,
                            int limit);

// 0x0052df30 -- three stack arguments, caller-cleaned (ADD ESP,0xc).
void __cdecl op_0052df30(unsigned int* out_words,
                           const char* format,
                           const void* value);

// 0x011e0912 -- the throw helper, reached through a thunk, with two stack
// arguments and no stack cleanup after the call, so the callee pops both.
// Control does not return. The first argument is a committed ThrowInfo record
// in the data segment (its four words are 0, a code address, 0 and the
// catchable-type array), which this reconstruction deliberately does not name,
// so it is carried as a null placeholder; the record is reachable from the
// throw helper itself.
[[noreturn]] void DF2_STDCALL op_011e0912(const void* type_record,
                                          const void* object);

// 0x00f47380 -- one stack argument, caller-cleaned (ADD ESP,0x4). Its result is
// what the body returns on the path that reaches 0x007c6942.
bool __cdecl op_00f47380(const void* released);

// 0x0067dd10 -- no stack argument and no ECX set at either call site; the
// returned word is then used as the receiver of an indirect call.
void* __cdecl op_0067dd10();

// 0x007c3c20 and 0x007c3ce0 -- ECX = the word returned by the preceding
// indirect call, no stack argument. Neither result is consumed by the body;
// each one is simply left in EAX, so each is what the common epilogue returns
// on the path that arrives straight after it.
bool DF2_THISCALL op_007c3c20(void* subject);
bool DF2_THISCALL op_007c3ce0(void* subject);

// 0x007c65a0 -- the type word is the only thing the body supplies and it is
// supplied in ECX, with no stack argument at the call site; the result is the
// object it names. The body does not establish the callee's convention beyond
// that register.
void* DF2_THISCALL op_007c65a0(unsigned int type_word);

// The two memory-indirect transfers in this body are the import-table slots
// at 0x013cc4cc and 0x013cc50c, which the xref export names as the CRT
// isdigit and _wcsicmp. The original compares 16-bit characters, so the wide
// type is spelled out rather than left to wchar_t.
int __cdecl isdigit(int character);
int __cdecl _wcsicmp(const unsigned short* left, const unsigned short* right);

}  // extern "C"

namespace {

// The body computes each indirect transfer target by loading a word out of an
// object and calling through the register it loaded. These typedefs are that
// shape, one per observed call shape; no dispatch table is named.
typedef int (*TargetNoArgument)(void);
typedef int (*TargetOneWord)(const void* receiver, unsigned int word);
typedef int (*TargetWordAndWord)(const void* receiver, unsigned int word);
typedef int (*TargetWordAndPointer)(const void* receiver, const void* argument);
typedef void* (*TargetPointerFromWord)(const void* receiver, unsigned int word);
typedef int (*TargetReceiverAndTwoWords)(const void* receiver,
                                         const void* first,
                                         unsigned int second);
typedef void* (*TargetPointerNoArgument)(void);
typedef void* (*TargetPointerFromPointer)(const void* receiver,
                                          const void* argument);
typedef void* (*TargetPointerFromTwoWords)(const void* receiver,
                                            unsigned int first,
                                            unsigned int second);

unsigned int load_word(const void* base, unsigned int displacement) {
  unsigned int value = 0;
  std::memcpy(&value,
              static_cast<const unsigned char*>(base) + displacement,
              sizeof(value));
  return value;
}

unsigned int load_halfword(const void* base, unsigned int displacement) {
  unsigned short value = 0;
  std::memcpy(&value,
              static_cast<const unsigned char*>(base) + displacement,
              sizeof(value));
  return value;
}

unsigned int word_of(const void* value) {
  unsigned int word = 0;
  std::memcpy(&word, &value, sizeof(word));
  return word;
}

void* load_pointer(const void* base, unsigned int displacement) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(
      load_word(base, displacement)));
}

// The shape every indirect transfer in this body has: the object's first word
// is the pointer the transfer target is read through, and the target sits at a
// displacement inside it.
unsigned int indirect_word(const void* object, unsigned int displacement) {
  return load_word(load_pointer(object, 0x0), displacement);
}

// The element count the body derives from the two words at 0x94 and 0x98:
// their difference arithmetic-shifted right by 4.
int element_count(const void* container) {
  return (static_cast<int>(load_word(container, 0x98)) -
          static_cast<int>(load_word(container, 0x94))) >> 4;
}

// The base of the array element with the given index: the word at 0x94 plus
// the index scaled by the 0x10 stride the body carries in EBX.
const void* element_at(const void* container, int index) {
  return static_cast<const unsigned char*>(reinterpret_cast<const void*>(
             static_cast<std::uintptr_t>(load_word(container, 0x94)))) +
         static_cast<std::size_t>(index) * 0x10;
}

}  // namespace

extern "C" bool DF2_THISCALL
App_cCameraManager_SetActiveCameraByID_007c6750(const void* receiver,
                                               unsigned int camera_id) {
  void* const sink = load_pointer(receiver, 0x4);
  void* const container = load_pointer(receiver, 0x10);

  // AL is what the epilogue hands back. The listing establishes that value
  // wherever it assigns AL and says nothing about the paths that do not, so
  // this starts at false purely as a modelling default and is reassigned only
  // where the machine writes AL.
  bool pending = false;

  // 0x007c6770: the identifier is itself the receiver of this query.
  if (op_00837f30(camera_id) == 1) {
    // 0x007c677c: the container's word at displacement 0x58 yields the active
    // index, which is then used to index the array bounded by the words at
    // 0x94 and 0x98.
    const int active = reinterpret_cast<TargetNoArgument>(
        indirect_word(container, 0x58))();
    unsigned int name = 0;
    if (active >= 0 && active < element_count(container)) {
      const void* const slot = element_at(container, active);
      const unsigned int first = load_word(slot, 0x0);
      if (first != load_word(slot, 0x4)) {
        name = first;
      }
    }
    // 0x007c67b9: format read at 0x0141067c.
    return op_00841000(sink, "Current controller: %ls\n", name) != 0;
  }

  // 0x007c67de: resolve the identifier into a wide string. The out-word says
  // whether that result is used directly or replaced by a property lookup.
  unsigned int resolved_flag = 0;
  void* resolved = op_00838020(&resolved_flag, 0, 1);
  if (resolved_flag != 1) {
    // 0x007c67fe: property name read at 0x013f2ce4, "set".
    void* const from_property = op_00838330("set", 1);
    if (from_property == nullptr) {
      // 0x007c6812 jumps to 0x007c6966, not to the epilogue: a null "set"
      // result skips the digit test and both the numeric and the name arm and
      // lands straight in the render block, with the pointer the direct
      // resolve returned still in the frame slot.
      goto render_block;
    }
    resolved = from_property;
  }

  // 0x007c681a: the first character decides which of the two paths runs. The
  // body reads the low byte of the first word, which is the low byte of the
  // first 16-bit character.
  {
    const unsigned short* const wide =
        reinterpret_cast<const unsigned short*>(load_pointer(resolved, 0x0));
    if (isdigit(static_cast<int>(static_cast<unsigned char>(wide[0]))) != 0) {
      // ---- numeric path, 0x007c6945 -------------------------------------
      // The value is converted through the word at displacement 0xa0 of the
      // receiver word at 0x4, then handed to the word the container's first
      // word points at, offset by 0x34 (0x007c6959: ADD EDI,0x34).
      void* const subject = load_pointer(receiver, 0x4);
      const unsigned int converted =
          reinterpret_cast<TargetWordAndPointer>(
              indirect_word(subject, 0xa0))(
              subject, load_pointer(resolved, 0x0));
      const std::size_t table_offset = 0x34;
      const void* const container_table = load_pointer(container, 0x0);
      reinterpret_cast<TargetWordAndWord>(load_word(
          static_cast<const unsigned char*>(container_table) + table_offset,
          0x0))(container, converted);

      // 0x007c6964 falls into 0x007c6966, so the numeric arm ends in the same
      // render block the null-property arm reaches.
      goto render_block;
    }

    // ---- name path, 0x007c6832 ------------------------------------------
    // 0x007c6835: convert the resolved string into a three-word local. The
    // body never writes those three words itself; it only measures the
    // distance from the first to the third and masks it (0x007c6913).
    unsigned int converted_words[3] = {0u, 0u, 0u};
    op_0093c5a0(&converted_words[0], load_pointer(resolved, 0x0), -1);

    // 0x007c6845: the container's word at displacement 0x48 is the count, read
    // once here and kept in a register for the whole loop.
    const int total = reinterpret_cast<TargetNoArgument>(
        indirect_word(container, 0x48))();

    bool matched = false;
    for (int index = 0; total > 0 && index < total; ++index) {
      unsigned int candidate = 0;
      // 0x007c6860: the body checks the index against the array bounds twice
      // and re-derives the same slot before comparing. The second pass is
      // kept because the listing performs it.
      if (index >= 0 && index < element_count(container)) {
        const void* const slot = element_at(container, index);
        const unsigned int first = load_word(slot, 0x0);
        if (first != load_word(slot, 0x4) && first != 0) {
          if (index < element_count(container)) {
            const unsigned int again = load_word(slot, 0x0);
            candidate = (again != load_word(slot, 0x4)) ? again : 0u;
          }
        }
      }
      if (candidate != 0 &&
          _wcsicmp(reinterpret_cast<const unsigned short*>(
                       static_cast<std::uintptr_t>(converted_words[0])),
                   reinterpret_cast<const unsigned short*>(
                       static_cast<std::uintptr_t>(candidate))) == 0) {
        // 0x007c68fc: the container's word at displacement 0x54 is called
        // with the matching index.
        pending = reinterpret_cast<TargetOneWord>(
            indirect_word(container, 0x54))(
            container, static_cast<unsigned int>(index)) != 0;
        matched = true;
        break;
      }
    }

    if (matched) {
      // 0x007c6909: the converted name is released and its result returned
      // when the measured length exceeds 2 and the first word is non-null.
      const unsigned int used =
          (converted_words[2] - converted_words[0]) & 0xfffffffeu;
      if (used > 2 && converted_words[0] != 0) {
        return op_00f47380(reinterpret_cast<const void*>(
            static_cast<std::uintptr_t>(converted_words[0])));
      }
      goto common_tail;
    }

    // 0x007c68d4: the name matched nothing, so the body formats a message
    // and throws. Format read at 0x01410664, "No such camera: '%s'".
    {
      unsigned int throw_words[3] = {0u, 0u, 0u};
      op_0052df30(&throw_words[0],
                    "No such camera: '%s'",
                    load_pointer(resolved, 0x0));
      op_011e0912(nullptr, &throw_words[0]);
    }
  }

render_block:
  // 0x007c6966: property name read at 0x01409070, "list".
  if (op_008380b0("list")) {
    // 0x007c697a: walk the array and log one line per entry. The count is
    // fetched again at the bottom of every iteration (0x007c6aa4) and the loop
    // continues while the index is below that fresh value, so the bound is not
    // cached here the way the name path's is.
    for (int index = 0;
         index < reinterpret_cast<TargetNoArgument>(
                     indirect_word(container, 0x48))();
         ++index) {
      unsigned int entry_name = 0;
      if (index >= 0 && index < element_count(container)) {
        const void* const slot = element_at(container, index);
        const unsigned int first = load_word(slot, 0x0);
        if (first != load_word(slot, 0x4)) {
          entry_name = first;
        }
      }

      // 0x007c69d0: the marker is "*" for the active entry and " "
      // otherwise (read at 0x01401b58 and 0x013ed024). It is stored into the
      // frame slot the resolve step used, and that slot is what the two
      // logging arms below read back, so the marker is the first vararg on
      // both of them.
      const int active = reinterpret_cast<TargetNoArgument>(
          indirect_word(container, 0x58))();
      const char* const marker = (index == active) ? "*" : " ";

      // 0x007c69f3: the entry's object, then a word off that object.
      void* const owner =
          reinterpret_cast<TargetPointerFromWord>(
              indirect_word(container, 0x4c))(
              container, static_cast<unsigned int>(index));
      void* const described =
          reinterpret_cast<TargetPointerNoArgument>(
              indirect_word(owner, 0x4c))();

      // The immediate at 0x013ec468 reads as a null word, and it is the
      // value the loop carries when there is no described object.
      const void* fallback = nullptr;
      if (described != nullptr) {
        if (reinterpret_cast<TargetOneWord>(
                indirect_word(described, 0x1c))(
                described, 0xb2ccca) != 0) {
          void* const tagged =
              reinterpret_cast<TargetPointerFromWord>(
                  indirect_word(described, 0x28))(
                  described, 0xb2ccca);
          const unsigned int kind = load_halfword(tagged, 0x12);
          const void* chosen = nullptr;
          if (kind == 0x13 || kind == 0x10) {
            // 0x007c6a44: bit 0x30 of the byte at displacement 0x10
            // selects between the word the object holds and the object.
            chosen = (load_word(tagged, 0x10) & 0x30) != 0
                         ? load_pointer(tagged, 0x0)
                         : tagged;
          } else {
            // 0x007c6a3d: the type word travels in ECX, not on the stack.
            chosen = op_007c65a0(kind);
          }
          fallback = load_pointer(chosen, 0x0);
        }
      }

      if (entry_name != 0) {
        // 0x007c6a64: format read at 0x01410648. Three varargs: the marker,
        // the entry name and the fallback.
        pending = op_00841000(sink,
                                " %s  %-40.40ls    '%ls'\n",
                                marker,
                                entry_name,
                                fallback) != 0;
      } else {
        // 0x007c6a7d: the container's word at displacement 0x50 yields the
        // wide name for the index. The second immediate, at 0x013ec47c,
        // reads as a null word and is not carried here, and the entry-name
        // slot is null on this path by construction. The format read at
        // 0x01410628 carries four conversions but the body pushes only three
        // varargs and then drops six words, so the callee reads a fourth one
        // this body never supplies.
        void* const wide_name =
            reinterpret_cast<TargetPointerFromWord>(
                indirect_word(container, 0x50))(
                container, static_cast<unsigned int>(index));
        pending =
            op_00841000(sink,
                          " %s  0x%08x%-30.30s    '%ls'\n",
                          marker,
                          wide_name,
                          static_cast<const void*>(nullptr)) != 0;
      }
    }
  }

  // 0x007c6ac0: property name read at 0x01410624, "bg".
  {
    void* const background = op_00838330("bg", 1);
    if (background != nullptr) {
      // 0x007c6ae0: the receiver word at 0x4 fills a four-float frame block,
      // and the body then copies that block 0xc bytes lower before handing
      // the copy to the renderer, so the two buffers are distinct.
      float produced_vector[4] = {0.0f, 0.0f, 0.0f, 0.0f};
      void* const subject = load_pointer(receiver, 0x4);
      reinterpret_cast<TargetReceiverAndTwoWords>(
          indirect_word(subject, 0xb4))(
          subject, produced_vector, load_word(background, 0x0));
      float render_vector[4] = {produced_vector[0], produced_vector[1],
                                produced_vector[2], produced_vector[3]};
      // 0x007c6b12: the renderer is fetched and the word at displacement
      // 0x58 of its first word is called with the copy.
      void* const renderer = op_0067dd10();
      void* const placed =
          reinterpret_cast<TargetPointerFromPointer>(
              indirect_word(renderer, 0x58))(renderer, render_vector);
      pending = op_007c3c20(placed);
    }
  }

  // 0x007c6b2c: property name read at 0x01410618, "renderType".
  {
    void* const render_type = op_00838330("renderType", 1);
    if (render_type != nullptr) {
      void* const subject = load_pointer(receiver, 0x4);
      void* const converted =
          reinterpret_cast<TargetPointerFromWord>(
              indirect_word(subject, 0x9c))(
              subject, load_word(render_type, 0x0));
      void* const renderer = op_0067dd10();
      // 0x007c6b59: the converted value is pushed first and the zero second,
      // so the converted value is the callee's first stack argument.
      void* const placed =
          reinterpret_cast<TargetPointerFromTwoWords>(
              indirect_word(renderer, 0x58))(
              renderer, word_of(converted), 0u);
      pending = op_007c3ce0(placed);
    }
  }

common_tail:
  // 0x007c6b6a: the common epilogue returns whatever AL holds on the arriving
  // path, which is what `pending` carries.
  return pending;
}
