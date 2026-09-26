#include "editor_onexit_00587a20.hpp"

// The header undefines its convention tokens at the end of the file, so the
// translation unit redefines them to spell the entry point's convention. Same
// spelling on both sides, so the declaration and the definition agree.
#if defined(_MSC_VER)
#define PKG_EDITOR_ONEXIT_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_ONEXIT_THISCALL __attribute__((thiscall))
#else
#error "PKG-EDITOR-ONEXIT-SMOKE01 requires an MSVC or GCC calling convention"
#endif

// PKG-EDITOR-ONEXIT-SMOKE01 -- body of 0x00587a20.
//
// Every statement below stands for one machine step and every address in a
// comment is the address of the instruction it stands for. The body is a
// 167-block acyclic DAG with no back edge, so "in control-flow order" is a
// total order over all 934 instructions and nothing is emitted twice. The
// out-of-line blocks at 0x00588223 and 0x0058822a..0x005884f6 are placed where
// the CFG reaches them rather than at their addresses, because address order
// is not execution order in this function.
//
// Three register facts the transliteration rests on, each read off the listing:
//
//   * EBX is zero for the whole body. `XOR EBX,EBX` at 0x00587a2e is its only
//     definition and `POP EBX` at 0x00588566 its only other mention, so every 0
//     written through EBX below is the constant 0, not a carried value.
//   * EBP is not a frame pointer. There is no `MOV EBP,ESP`. It holds the
//     constant 1 from 0x00587aef, is loaded with a pointer at 0x00587be8 and
//     used as a general register until 0x00587c78 puts the constant back, and
//     the epilogue's POP restores the caller's. Every frame offset in this body
//     is therefore an ESP displacement.
//   * EDI is the caller's register: PUSH EDI at 0x00587b61, POP EDI at
//     0x0058833f, and a scratch register in between.
//
// The stack is balanced at 0x0058833f, and that is what makes the callee-cleanup
// claims provable rather than assumed. The epilogue is
// `POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET`, reachable only with ESP
// at the value the prologue left, so no argument pushed between 0x00587b61 and
// 0x0058833f is still on the stack at the POP. Every indirect call in that
// window therefore pops its own arguments.

namespace openspore::reconstruction::pkg_editor_onexit_smoke01 {
namespace {

// `MOV EAX,dword ptr [object]` then `MOV <reg>,dword ptr [EAX+offset]`, the
// shape every pointee-side read in this body takes. The offset is the argument
// rather than a name, so no pointee layout is asserted that the listing does
// not show at a named instruction.
inline Dword dword_at(const void* object, Dword offset) noexcept {
  return *reinterpret_cast<const Dword*>(static_cast<const Byte*>(object) + offset);
}

inline void* as_ptr(Dword value) noexcept { return reinterpret_cast<void*>(value); }

inline void set_dword_at(void* object, Dword offset, Dword value) noexcept {
  *reinterpret_cast<Dword*>(static_cast<Byte*>(object) + offset) = value;
}

// The dword at `member`, i.e. the receiver field itself. `member` is always one
// of OpaqueEditor's declared fields, so its offset is pinned by an offsetof
// assertion in the header rather than restated here.
inline void* load(void* const* member) noexcept { return *member; }
inline void clear(void** member) noexcept { *member = nullptr; }

// Family 1 -- guarded clear, then one table entry. 22 of the 167 blocks.
//
//   MOV ECX,[ESI+off] ; CMP ECX,EBX ; JZ skip
//   MOV [ESI+off],EBX
//   MOV EAX,[ECX] ; MOV EDX,[EAX+slot] ; CALL EDX
inline void release_slot(void** member, Dword slot) noexcept {
  void* p = load(member);
  if (p == nullptr) return;
  clear(member);
  reinterpret_cast<Fn0>(entry_at(p, slot))();
}

// Family 2 -- guarded clear, one preparatory direct call on the member, then
// the release. The preparatory call runs while the member is still set and the
// member is re-read afterwards, so a preparatory call that clears it is
// observable in the release that follows.
//
//   if (p) { prep(p); if (member) { member = 0; p->slot(); } }
inline void prep_release_slot(void** member, Dword slot, PrepFn prep) noexcept {
  void* p = load(member);
  if (p == nullptr) return;
  prep(p);
  release_slot(member, slot);
}

// Family 3 -- refcounted release where the count sits at pointee+0x08 and the
// pointee's table at pointee+0x04. `LEA ECX,[EAX+4]` at 0x00587e24 and
// 0x00587e66 is what fixes the block head at +4.
//
//   LEA ECX,[p+4] ; member = 0 ; DEC [ECX+4] ; if (0) { [ECX+4] = 1 ; (*[ECX])(1) }
inline void release_counted_at_8(void** member) noexcept {
  void* p = load(member);
  if (p == nullptr) return;
  clear(member);
  void* block = static_cast<Byte*>(p) + 4;
  Dword count = dword_at(block, 0x04);
  --count;
  set_dword_at(block, 0x04, count);
  if (count == 0) {
    set_dword_at(block, 0x04, 1);
    reinterpret_cast<Fn1>(entry_at(*reinterpret_cast<void**>(block), 0x00))(1);
  }
}

// Family 2b -- as family 2, with a second preparatory call whose receiver is
// the member re-read after the first. Two members use it (+0x98, +0x9c).
inline void prep2_release_slot(void** member,
                               PrepFn prep1, PrepFn prep2) noexcept {
  void* p = load(member);
  if (p == nullptr) return;
  prep1(p);
  prep2(load(member));
  release_counted_at_8(member);
}

// Family 4 -- two table entries with a re-test between them, then the clear.
// Six members use it (+0x494..+0x4a4 and +0x2a4).
//
//   if (p) { p->slot(first)(); if (p) { p = 0; p->slot(second)(); } }
inline void release_two_phase(void** member, Dword first, Dword second) noexcept {
  void* p = load(member);
  if (p == nullptr) return;
  reinterpret_cast<Fn0>(entry_at(p, first))();
  p = load(member);
  if (p == nullptr) return;
  clear(member);
  reinterpret_cast<Fn0>(entry_at(p, second))();
}

// Family 5 -- the four weak teardown members +0xa0, +0xa4, +0xa8, +0xac.
//
//   if (p) { (*p)->slot(0x16c)(p, 0);
//            if (p) { p = 0;
//                     if (p[0x40] > 1) p[0x40] -= 1;
//                     else (*p)->slot(0x170)(p, (p[0x04] >> 31) & 1); } }
//
// The `>1` comparison is signed (JLE at 0x0058821b, 0x00588273, 0x005882c4 and
// 0x00588315), so a count at or below 1 -- including a negative one -- takes the
// slot 0x170 branch.
inline void release_weak_teardown(void** member) noexcept {
  void* p = load(member);
  if (p == nullptr) return;
  reinterpret_cast<Fn2p>(entry_at(*reinterpret_cast<void**>(p), 0x16c))(p, 0);
  p = load(member);
  if (p == nullptr) return;
  clear(member);
  const Dword count = dword_at(p, 0x40);
  if (count > 1) {
    set_dword_at(p, 0x40, count - 1);
    return;
  }
  void* inner = *reinterpret_cast<void**>(p);
  reinterpret_cast<Fn2p>(entry_at(inner, 0x170))(p, (dword_at(p, 0x04) >> 31) & 1u);
}

// The object self->p_1cc points at, as far as the 0x00587b93 block reads it.
// +0x90 and +0x94 at 0x00587bd6 and 0x00587be8, then +0x10/+0x14/+0x18 at
// 0x00587c1d..0x00587c2f.
struct alignas(4) PeerState {
  Byte opaque_00[0x10];
  Dword a_10;
  Dword a_14;
  Dword a_18;
  Byte opaque_1c[0x74];
  Dword a_90;
  Dword a_94;
};

static_assert(offsetof(PeerState, a_10) == 0x10, "0x00587c1d reads peer+0x10");
static_assert(offsetof(PeerState, a_14) == 0x14, "0x00587c26 reads peer+0x14");
static_assert(offsetof(PeerState, a_18) == 0x18, "0x00587c2c reads peer+0x18");
static_assert(offsetof(PeerState, a_90) == 0x90, "0x00587bd6 reads peer+0x90");
static_assert(offsetof(PeerState, a_94) == 0x94, "0x00587be8 reads peer+0x94");

// The object that block builds. 0x00579c80 is its constructor -- 21
// instructions, `MOV EAX,ECX` then 20 stores -- and the writes below at
// 0x00587bdc..0x00587c3e are the only ones this body makes to those fields.
struct alignas(4) CreatedState {
  Byte opaque_00[0x0c];  // the table 0x00579c80 installs at +0x00
  Dword v_0c;
  void* sub_10;
  Dword v_14;
  Dword v_18;
  Dword v_1c;
  Dword v_20;
  Byte opaque_24[0x20];
  Byte flag_44;
};

static_assert(offsetof(CreatedState, v_0c) == 0x0c, "0x00587bdc writes created+0x0c");
static_assert(offsetof(CreatedState, sub_10) == 0x10, "0x00587c03 writes created+0x10");
static_assert(offsetof(CreatedState, v_14) == 0x14, "0x00587c3b writes created+0x14");
static_assert(offsetof(CreatedState, v_18) == 0x18, "0x00587c23 writes created+0x18");
static_assert(offsetof(CreatedState, v_1c) == 0x1c, "0x00587c29 writes created+0x1c");
static_assert(offsetof(CreatedState, v_20) == 0x20, "0x00587c2f writes created+0x20");
static_assert(offsetof(CreatedState, flag_44) == 0x44, "0x00587c3e writes created+0x44");

}  // namespace
}  // namespace openspore::reconstruction::pkg_editor_onexit_smoke01

namespace openspore::reconstruction::pkg_editor_onexit_smoke01 {

extern "C" void PKG_EDITOR_ONEXIT_THISCALL
Editors_cEditor_OnExit_00587a20(OpaqueEditor* self) {
  using openspore::reconstruction::pkg_editor_onexit_smoke01::as_ptr;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::clear;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::dword_at;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::load;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::prep2_release_slot;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::prep_release_slot;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::release_slot;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::release_two_phase;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::release_weak_teardown;
  using openspore::reconstruction::pkg_editor_onexit_smoke01::set_dword_at;

  // -- 0x00587a20..0x00587a26: prologue -------------------------------------
  // SUB ESP,0x44 ; PUSH EBX ; PUSH EBP ; PUSH ESI ; MOV ESI,ECX
  // ECX is the hidden receiver; ESI carries it for the rest of the body.

  // -- 0x00587a28..0x00587a39: notify +0x94, no null guard beyond the test --
  if (self->p_094 != nullptr) {
    reinterpret_cast<Fn0>(entry_at(self->p_094, 0x34))();
  }

  // -- 0x00587a3b..0x00587a4a: index 0xb against a bound, callee pops 8 ----
  // 0x006a1880 reads its own [ESI+0x38] and compares arg0 against it unsigned
  // (CMP EDI,[ESI+0x38] ; JNC), so +0x450 is a count and not a pointer.
  sub_006a1880(g_015fd918(), self->w_450, 0xb);

  // -- 0x00587a4f -----------------------------------------------------------
  self->b_2b0 = 0;

  // -- 0x00587a55..0x00587a65: test one fetch, act on a second -------------
  // The EAX of the first fetch is tested and discarded; the receiver handed to
  // 0x0067a120 is the result of a separate second fetch.
  if (sub_0067caf0() != nullptr) {
    sub_0067a120(sub_0067caf0());
  }

  // -- 0x00587a6a..0x00587a97: build the stack object, then call slot 0x44 --
  // The five stores are the only writes to those words, in this order. With
  // ESP 0xc below the frame base after the three pushes, [ESP+0x10] is
  // object+0x00, [ESP+0x14] is object+0x04, [ESP+0x18] is object+0x08,
  // [ESP+0x40] is object+0x30 and [ESP+0x48] is object+0x38.
  LocalAppState app_state;
  app_state.tag_30 = 0x60c874f;    // 0x00587a6a  MOV [ESP+0x40],0x60c874f
  // 0x13eb90c and 0x13eb844 are table addresses: 0x13eb844 holds
  // {0x004230e0, 0x00432a50, 0x00404f90} and 0x13eb90c holds
  // {0x0040fdc0, 0x00432a50, 0x00404f90, 0x0040fd90, ...}.
  app_state.dispatch = as_ptr(0x13eb90c);  // 0x00587a72  MOV [ESP+0x10],0x13eb90c
  app_state.zero_04 = 0;           // 0x00587a7a  XOR ECX,ECX
                                   // 0x00587a80  XCHG dword ptr [EDX],ECX
  app_state.dispatch = as_ptr(0x13eb844);  // 0x00587a89  MOV [ESP+0x10],0x13eb844
  app_state.sub_mask = 0;          // 0x00587a91  MOV [ESP+0x48],EBX
  // 0x00587a95 CALL EDX, EDX = self's table entry at +0x44, ECX = self. The
  // listing pushes no argument for this call, and the object address is not in
  // a pushed register either: it occupies the callee's third stack-argument
  // position inside this frame, and the callee pops it. The callee's arity is
  // therefore not decidable from this body; see unresolved_questions.
  app_state.sub_08 = reinterpret_cast<Fn0p>(entry_at(self, 0x44))();
  // 0x00587a97  MOV [ESP+0x18],EAX -- the assignment above is that store.

  // -- 0x00587a9b..0x00587ab2: a 3-argument slot on a fetched singleton -----
  // Pushes in the order 0, &app_state, 0x60c874f, so arg0 = 0x60c874f.
  reinterpret_cast<Fn3w>(entry_at(sub_0067dcc0(), 0x14))(
      0x60c874f, &app_state, 0);

  // -- 0x00587ab4 -----------------------------------------------------------
  *g_016f6ee0() &= 0xfffffffeu;

  // -- 0x00587abc..0x00587ac3: slot 0x4c, no arguments ---------------------
  reinterpret_cast<Fn0>(entry_at(self, 0x4c))();

  // -- 0x00587ac5..0x00587ada ----------------------------------------------
  release_slot(&self->p_380, 0x08);

  // -- 0x00587adc..0x00587ae3: one singleton, two direct calls -------------
  sub_0067ca40(sub_0067cac0());

  // -- 0x00587ae8..0x00587afd: two words pushed before a getter call --------
  // PUSH EBP ; PUSH EAX ; CALL 0x0067cac0 ; MOV ECX,EAX ; CALL 0x0067c420.
  // 0x0067cac0 is `MOV EAX,[0x015fcc54] ; RET` and takes no argument, so the two
  // pushed words are the arguments of 0x0067c420, which ends in RET 0x8.
  // Attributing the pushes to 0x0067cac0 is a decompiler artefact.
  sub_0067c420(sub_0067cac0(), self->b_144, 1);

  // -- 0x00587b02..0x00587b25: the +0x4d0 float, to two callees -----------
  // FLD float ptr [ESI+0x4d0] ; PUSH ECX ; FSTP float ptr [ESP] : the PUSH ECX
  // is dead, because FSTP overwrites the same dword. The single argument
  // 0x007c53d0 receives is the float, not the register Ghidra prints as
  // `unaff_ESI`. FLD/FSTP balance, so nothing is left on the x87 stack.
  if (sub_0067dd10() != nullptr) {
    const float f = self->f_4d0;
    void* app = sub_0067dd10();
    // FSTP float ptr [ESP] writes the 4-byte stack argument at the current ESP
    // and the callee pops it, so this entry takes the float and returns the
    // pointer 0x007c53d0 is then given.
    void* result = reinterpret_cast<Fn1f>(entry_at(app, 0x58))(f);
    sub_007c53d0(result, f);
  }

  // -- 0x00587b2a..0x00587b3f ----------------------------------------------
  release_slot(&self->p_4bc, 0x08);

  // -- 0x00587b41..0x00587b4c: one argument, callee pops 4 ----------------
  sub_005dbb60(self, 1);

  // -- 0x00587b49..0x00587b5c: a word two levels down gates a call ----------
  // MOV ECX,[0x015fd918] ; MOV EDX,[ECX+0x3c] ; CMP dword ptr [EDX+0x118],EBX
  {
    void* level1 = g_015fd918();
    void* level2 = reinterpret_cast<void*>(dword_at(level1, 0x3c));
    if (dword_at(level2, 0x118) != 0) {
      sub_005dbb50(self);
    }
  }

  // -- 0x00587b61..0x00587b91: two singletons, a key string, a global word --
  // PUSH EDI saves the caller's EDI and POP EDI at 0x0058833f restores it; the
  // stack is balanced there, so all four calls below pop their own arguments.
  // 0x13f5ca0 is the string "editor".
  {
    void* first = sub_0067de20();
    reinterpret_cast<Fn1>(entry_at(first, 0x1c))(0x13f5ca0);
    void* second = sub_0067de40();
    void* third = reinterpret_cast<Fn0p>(entry_at(second, 0x20))();
    reinterpret_cast<Fn1p>(entry_at(third, 0x20))(as_ptr(g_015eebec()));
  }

  // -- 0x00587b93..0x00587c78: the one allocating block --------------------
  //
  // On allocation failure the machine runs XOR EDI,EDI ; JMP 0x00587bd0 at
  // 0x00588223, and there are then two null dereferences on that path: the
  // stores below are UNCONDITIONAL, so the first one writes through a null
  // pointer at address 0x0000000c, and 0x00587c6f reads [EDI] before the
  // created object is released. Both are reproduced here rather than guarded:
  // adding a check would be a behaviour the original does not have, and
  // reporting it is the point.
  {
    void* created = nullptr;  // EDI
    if (self->p_1cc != nullptr) {
      // 0x48 is the size; 0x13eb430 is the string "Editor".
      void* raw = sub_00f473a0(0x48, 0x13eb430, 0, 0, 0, 0);
      if (raw != nullptr) {
        created = sub_00579c80(raw);
        if (created != nullptr) {
          reinterpret_cast<Fn0>(entry_at(created, 0x04))();  // 0x00587bce
        }
      }
    }

    PeerState* peer = reinterpret_cast<PeerState*>(self->p_1cc);
    CreatedState* made = reinterpret_cast<CreatedState*>(created);

    made->v_0c = peer->a_90;                                 // 0x00587bdc
    // 0x00587be5..0x00587c15: install peer+0x94 over created+0x10, running the
    // new object's entry at +0x00 first and the replaced one's at +0x04 second.
    // 0x00587bf2 CMP EBP,EAX ; JZ 0x00587c17 is a plain 32-bit compare, so a
    // null peer+0x94 against a non-null created+0x10 still enters the block: the
    // inner `CMP EBP,EBX ; JZ` then skips only the first dispatch and the null is
    // installed anyway. Both tests are kept separate for that reason.
    if (as_ptr(peer->a_94) != made->sub_10) {
      if (peer->a_94 != 0) {
        // 0x00587bf6..0x00587c01: CMP EBP,EBX ; JZ ; then the table entry at
        // +0x00 of the pointee, with no argument pushed.
        reinterpret_cast<Fn0>(entry_at(as_ptr(peer->a_94), 0x00))();  // 0x00587c01
      }
      made->sub_10 = as_ptr(peer->a_94);                     // 0x00587c03
      if (made->sub_10 != nullptr) {
        reinterpret_cast<Fn0>(entry_at(made->sub_10, 0x04))();  // 0x00587c15
      }
    }
    made->v_18 = peer->a_10;                                  // 0x00587c23
    made->v_1c = peer->a_14;                                  // 0x00587c29
    made->v_20 = peer->a_18;                                  // 0x00587c2f
    made->v_14 = dword_at(self->p_098, 0x58);                 // 0x00587c3b
    made->flag_44 = 1;                                        // 0x00587c3e
    // 0x00587c42..0x00587c56: four pushes, so arg0 = 0x30c11c7
    reinterpret_cast<Fn4p>(entry_at(sub_0067dcc0(), 0x18))(
        0x30c11c7, created, 0, 0);
    release_slot(&self->p_1cc, 0x08);                         // 0x00587c6d
    reinterpret_cast<Fn0>(entry_at(created, 0x08))();         // 0x00587c76
    // 0x00587c78 MOV EBP,0x1 -- the constant is back in EBP.
  }

  // -- 0x00587c7d..0x00587c8a: a singleton gates a 2-argument call ---------
  if (sub_0067dd10() != nullptr) {
    sub_00587270(self, 0, 1);
  }

  // -- 0x00587c8f..0x00587cc6: two fetches of one manager, then slot 0x140 -
  // 0x0067cad0 is `MOV EAX,[0x015fcc58] ; RET` and 0x006c10e0 is
  // `MOV EAX,[ECX+0x3c] ; RET`, so the manager is the word at +0x3c of that
  // singleton, fetched twice.
  {
    void* mgr = sub_006c10e0(sub_0067cad0());
    if (mgr != nullptr && self->p_1ac != nullptr) {
      void* mgr2 = sub_006c10e0(sub_0067cad0());
      reinterpret_cast<Fn3p>(entry_at(mgr2, 0x140))(self->p_1ac, 0, 1);
    }
  }

  // -- 0x00587cc8 -----------------------------------------------------------
  sub_005772b0(self);

  // -- 0x00587ccf..0x00587cd4: two arguments, callee pops 8 ----------------
  sub_00573c00(self, 0, 0xffffffffu);

  // -- 0x00587cd9..0x00587d2d: a flag bit, an identity test, then release ---
  {
    void* d4 = self->p_0d4;
    if (d4 != nullptr) {
      // 0x00587ce3..0x00587ced: bit 1 of d4[0xdc8] skips both calls below.
      if (((dword_at(d4, 0xdc8) >> 1) & 1u) == 0) {
        // 0x00587cef..0x00587d06: only when +0xe4 is the object 0x0047e6c0
        // returns -- a pointer identity test against EDI.
        if (self->p_0e4 != nullptr && sub_0047e6c0(self->p_0e4) == d4) {
          sub_00573d70(self, 0, 1);
        }
        sub_0043a9a0(self->p_0d4, 0, 1);  // 0x00587d13, re-reads +0xd4
      }
      release_slot(&self->p_0d4, 0x08);   // 0x00587d2d
    }
  }

  // -- 0x00587d2f..0x00587d4c: two flag bytes, one of them with a call ------
  if (self->b_0e8 != 0) self->b_0e8 = 0;
  if (self->b_0e9 != 0) {
    sub_005772b0(self);
    self->b_0e9 = 0;
  }

  // -- 0x00587d52..0x00587d94: the first of two 4-call blocks --------------
  // 0x00a206f0 is `MOV EAX,[0x0166d9f4] ; RET`. The whole block runs only when
  // the fetch is non-null. 0x347536b, 0x3475385 and 0x34753a0 are literals the
  // listing pushes; nothing here identifies what they index.
  {
    void* rec = sub_00a206f0();
    if (rec != nullptr) {
      reinterpret_cast<Fn1>(entry_at(rec, 0x38))(0x347536b);
      reinterpret_cast<Fn2>(entry_at(rec, 0x40))(0x3475385, 0x1d6253c0);
      reinterpret_cast<Fn2>(entry_at(rec, 0x40))(0x34753a0, 0);
      reinterpret_cast<Fn0>(entry_at(rec, 0x58))();
    }
  }

  // -- 0x00587d96..0x00587dd8: the second block, one literal different ------
  // The two blocks are identical but for the second argument of the 0x40 slot:
  // 0x1d6253c0 here, 0xb07c3bbf above. Ghidra's decompilation folds the two
  // into one 5-call block and loses that difference; the listing keeps it.
  {
    void* rec = sub_00a206f0();
    if (rec != nullptr) {
      reinterpret_cast<Fn1>(entry_at(rec, 0x38))(0x347536b);
      reinterpret_cast<Fn2>(entry_at(rec, 0x40))(0x3475385, 0xb07c3bbf);
      reinterpret_cast<Fn2>(entry_at(rec, 0x40))(0x34753a0, 0);
      reinterpret_cast<Fn0>(entry_at(rec, 0x58))();
    }
  }

  // -- 0x00587dda -----------------------------------------------------------
  self->b_20e = 0;

  // -- 0x00587de0..0x00587de7: two direct calls, no arguments --------------
  sub_0045ab30(sub_00401050());

  // -- 0x00587dec..0x00587dfe: two arguments, last push is arg0 ------------
  // PUSH EBX ; PUSH 0x10, so arg0 = 0x10 and arg1 = 0.
  reinterpret_cast<Fn2>(entry_at(sub_0067ddd0(), 0x98))(0x10, 0);

  // -- 0x00587e00..0x00587e82: two refcounted releases, identical shape ----
  prep2_release_slot(&self->p_098, sub_004ad280, sub_004ad330);
  prep2_release_slot(&self->p_09c, sub_004ad280, sub_004ad330);

  // -- 0x00587e84..0x00587ee4: three preparatory-then-release members ------
  prep_release_slot(&self->p_14c, 0x08, sub_005d31b0);
  prep_release_slot(&self->p_150, 0x04, sub_004c4eb0);
  prep_release_slot(&self->p_154, 0x04, sub_004c4eb0);

  // -- 0x00587ef6..0x00587f28: copy one byte into two fetched objects -------
  {
    void* base = sub_00401020();
    void* p = sub_0113ae10(base);
    if (p != nullptr) {
      *static_cast<Byte*>(static_cast<Byte*>(p) + 0xb9) = self->b_4b6;
    }
    void* q = sub_00801920(base);
    if (q != nullptr) {
      *static_cast<Byte*>(static_cast<Byte*>(q) + 0xb9) = self->b_4b6;
    }
  }

  // -- 0x00587f2e..0x0058801c: six two-phase releases -----------------------
  release_two_phase(&self->p_494, 0x24, 0x04);
  release_two_phase(&self->p_498, 0x24, 0x04);
  release_two_phase(&self->p_49c, 0x24, 0x04);
  release_two_phase(&self->p_4a0, 0x24, 0x04);
  release_two_phase(&self->p_4a4, 0x24, 0x04);
  release_two_phase(&self->p_2a4, 0x18, 0x04);

  // -- 0x0058801e..0x005881b5: eleven preparatory-then-release members -----
  prep_release_slot(&self->p_350, 0x0c, sub_004581d0);
  prep_release_slot(&self->p_354, 0x04, sub_00ed0660);
  prep_release_slot(&self->p_35c, 0x04, sub_0059a3b0);
  prep_release_slot(&self->p_358, 0x04, sub_005bfb90);
  prep_release_slot(&self->p_07c, 0x08, sub_0062c910);
  prep_release_slot(&self->p_29c, 0x04, sub_004b27c0);
  prep_release_slot(&self->p_2a0, 0x04, sub_004b27c0);
  prep_release_slot(&self->p_3bc, 0x04, sub_005cba90);
  prep_release_slot(&self->p_3b8, 0x08, sub_005c5c20);
  prep_release_slot(&self->p_3c4, 0x04, sub_005cba90);
  prep_release_slot(&self->p_3c0, 0x08, sub_005c5c20);

  // -- 0x005881be..0x005881d5: +0x78, released through pointee+0x04 ---------
  // No refcount and no re-test between the clear and the call, which is what
  // distinguishes it from the two members above: `LEA ECX,[EAX+4]` then
  // MOV EAX,[ECX] ; MOV EDX,[EAX+0x4] ; CALL EDX, with ECX = pointee+4.
  {
    void* p = self->p_078;
    if (p != nullptr) {
      sub_005de870(p);
      p = self->p_078;
      if (p != nullptr) {
        clear(&self->p_078);
        reinterpret_cast<Fn0>(entry_at(static_cast<Byte*>(p) + 4, 0x04))();
      }
    }
  }

  // -- 0x005881d7..0x005881ec: +0xe4, released here after being read at
  //    0x00587cef for the identity test; nothing writes it in between -------
  release_slot(&self->p_0e4, 0x04);

  // -- 0x005881ee..0x00588337: four weak teardown members -------------------
  // The four else-halves sit out of line at 0x0058822a, 0x0058827b, 0x005882cc
  // and 0x0058831d; each ends in JMP to the next member's block.
  release_weak_teardown(&self->p_0a0);
  release_weak_teardown(&self->p_0a4);
  release_weak_teardown(&self->p_0a8);
  release_weak_teardown(&self->p_0ac);

  // -- 0x00588339..0x0058836c: +0x360, refcount at pointee+0x04 ------------
  // POP EDI at 0x0058833f restores the caller's register saved at 0x00587b61.
  // Here the count is at +0x04 and the table at +0x00, the mirror image of the
  // +0x98 family.
  {
    void* p = self->p_360;
    if (p != nullptr) {
      sub_0059c640(p);
      p = self->p_360;
      if (p != nullptr) {
        clear(&self->p_360);
        Dword count = dword_at(p, 0x04);
        --count;
        set_dword_at(p, 0x04, count);
        if (count == 0) {
          set_dword_at(p, 0x04, 1);
          reinterpret_cast<Fn1>(entry_at(*reinterpret_cast<void**>(p), 0x00))(1);
        }
      }
    }
  }

  // -- 0x0058836e..0x005883ac: four unconditional stores, then a two-phase --
  // The load of +0x148 happens BEFORE the four stores and the stores are
  // unconditional, so they run even when +0x148 is null.
  {
    void* p = self->p_148;
    self->b_385 = 0;
    self->b_384 = 0;
    self->w_364 = 0;
    self->w_368 = 0;
    if (p != nullptr) {
      reinterpret_cast<Fn0>(entry_at(p, 0x30))();
      p = self->p_148;
      if (p != nullptr) {
        clear(&self->p_148);
        reinterpret_cast<Fn0>(entry_at(p, 0x04))();
      }
    }
  }

  // -- 0x005883ae..0x005883c3 ----------------------------------------------
  release_slot(&self->p_0d0, 0x08);

  // -- 0x005883c5..0x005883f9: a three-entry member, with one missing re-test -
  // 0x005883d4 runs slot 0x28 with one argument. 0x005883dd..0x005883e2 then
  // reloads the member and runs slot 0x24 with NO comparison, so a slot 0x28
  // that clears the member faults there. The re-test the six +0x494-family
  // members carry between their two slots is absent here; Ghidra's decompilation
  // supplies it by conflating the two shapes.
  {
    void* p = self->p_294;
    if (p != nullptr) {
      reinterpret_cast<Fn1>(entry_at(p, 0x28))(0);
      p = self->p_294;
      reinterpret_cast<Fn0>(entry_at(p, 0x24))();
      p = self->p_294;
      if (p != nullptr) {
        clear(&self->p_294);
        reinterpret_cast<Fn0>(entry_at(p, 0x04))();
      }
    }
  }

  // -- 0x005883fb..0x00588423: two members, one slot, one argument, no clear -
  {
    void* p = self->p_084;
    if (p != nullptr) reinterpret_cast<Fn1>(entry_at(p, 0x134))(0);
    p = self->p_08c;
    if (p != nullptr) reinterpret_cast<Fn1>(entry_at(p, 0x134))(0);
  }

  // -- 0x00588425..0x00588432: one 1-argument slot --------------------------
  reinterpret_cast<Fn1>(entry_at(sub_0067dd80(), 0x24))(0);

  // -- 0x00588434..0x00588492: six 1-argument slots on the same singleton ----
  // Six separate `CALL 0x0067dd50` fetches, one per literal, in this order.
  {
    void* rec = sub_0067dd50();
    reinterpret_cast<Fn1>(entry_at(rec, 0x50))(0x0f);
  }
  {
    void* rec = sub_0067dd50();
    reinterpret_cast<Fn1>(entry_at(rec, 0x50))(0x0c);
  }
  {
    void* rec = sub_0067dd50();
    reinterpret_cast<Fn1>(entry_at(rec, 0x50))(0x0d);
  }
  {
    void* rec = sub_0067dd50();
    reinterpret_cast<Fn1>(entry_at(rec, 0x50))(0x1a);
  }
  {
    void* rec = sub_0067dd50();
    reinterpret_cast<Fn1>(entry_at(rec, 0x50))(0x11);
  }
  {
    void* rec = sub_0067dd50();
    reinterpret_cast<Fn1>(entry_at(rec, 0x50))(0x14);
  }

  // -- 0x00588494..0x005884b4: +0x94 again, then a 1-argument slot ---------
  // The +0x94 test is the same as at 0x00587a30 but the slot differs, and the
  // 0x0067ddd0 call sits INSIDE the guard, so it is skipped with it.
  if (self->p_094 != nullptr) {
    void* p = self->p_094;
    reinterpret_cast<Fn1>(entry_at(p, 0x0c))(2);
    reinterpret_cast<Fn1>(entry_at(sub_0067ddd0(), 0x58))(0);
  }

  // -- 0x005884b6..0x005884c2: a 0-argument slot ----------------------------
  reinterpret_cast<Fn0>(entry_at(sub_0067dd40(), 0x2c))();

  // -- 0x005884c4..0x005884f6: five members, one 5-argument direct call ----
  // The five words are pushed first, the +0x5d4 word is cleared, and only then
  // is 0x00571db0 called; the caller pops 0x14. 0x00571db0 reads arg1 as an
  // object with a table, arg2 as a loop bound, arg3 as a dword array and arg4
  // straight through, and never reads arg0 -- so +0x5d4 is a guard only. Its
  // own prologue saves ECX and never reloads it, so it is a plain __cdecl
  // function of five arguments and not a thiscall.
  {
    void* head = self->p_5d4;
    if (head != nullptr) {
      void* a1 = self->p_5d8;
      Dword a2 = self->w_5dc;
      void* a3 = self->p_5e0;
      Dword a4 = self->w_5e4;
      clear(&self->p_5d4);
      sub_00571db0(head, a1, a2, a3, a4);
    }
  }

  // -- 0x005884f9..0x0058852e: a 64-bit accumulate --------------------------
  // CMP EAX,EBX ; JZ 0x00588510 ; LEA ECX,[EAX + -0x4] ; XOR ECX,ECX, so the
  // anchor passed to 0x008130a0 is (result - 4) when the call returned non-null
  // and 0 otherwise. 0x008130a0 returns 64 bits in EDX:EAX, which are then
  // subtracted from the 64-bit word at +0x438 and added into the one at +0x448.
  {
    void* app = sub_0067caa0();
    void* result = reinterpret_cast<Fn0p>(entry_at(app, 0x04))();
    void* anchor = nullptr;
    if (result != nullptr) anchor = static_cast<Byte*>(result) - 4;
    const U64 delta = sub_008130a0(anchor);
    const U64 base = self->u_438;
    U64 diff;
    diff.lo = delta.lo - base.lo;
    diff.hi = delta.hi - base.hi - (diff.lo > delta.lo ? 1u : 0u);
    const U64 acc = self->u_448;
    U64 sum;
    sum.lo = acc.lo + diff.lo;
    sum.hi = acc.hi + diff.hi + (sum.lo < acc.lo ? 1u : 0u);
    self->u_448 = sum;
  }

  // -- 0x00588534..0x0058853b: one argument, callee pops 4 ------------------
  sub_00801bb0(sub_0067cab0(), 0x1002);

  // -- 0x00588540..0x00588558: two 3-argument direct calls, 0x18 of cleanup -
  // 0x00777ae0 indexes a table at 0x16f65a8 with its first argument, so these
  // two literals are small indices rather than pointers.
  sub_00777ae0(0x238, 0, 1);
  sub_00777ae0(0x236, 0, 1);

  // -- 0x0058855b..0x0058855f: the stack object's teardown ------------------
  // LEA ECX,[ESP+0x10] is the object base, so this is sub_00421cf0(&app_state).
  // It re-points app_state.dispatch, releases every sub-object whose bit is set
  // in app_state.sub_mask -- zero here, so the loop body never runs -- and then
  // re-points dispatch twice more before its bare RET.
  sub_00421cf0(&app_state);

  // -- 0x00588564..0x0058856a: epilogue -------------------------------------
  // POP ESI ; POP EBP ; POP EBX ; ADD ESP,0x44 ; RET -- bare, no immediate.
}

}  // namespace openspore::reconstruction::pkg_editor_onexit_smoke01

#undef PKG_EDITOR_ONEXIT_THISCALL
