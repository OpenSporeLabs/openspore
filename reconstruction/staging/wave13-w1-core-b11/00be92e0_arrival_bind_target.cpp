// reconstruction/staging/wave13-w1-core-b11/00be92e0_arrival_bind_target.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00be92e0 (image base
// 0x00400000). Body 0x00be92e0..0x00be984c, 386 instructions, 1391 bytes.
// __thiscall: ECX receiver plus five caller-cleaned stack words (RET 0x14).
//
// ABI, derived from the prologue and the two epilogues:
//   entry ESP = E0.
//   0x00be92e0: MOV EAX,dword ptr [ESP + 0x8]   -> stack word 2 (arg2)
//   0x00be92e4: SUB ESP,0x80
//   0x00be92ea: PUSH EBP ; 0x00be92eb: PUSH ESI    -> ESP = E0 - 0x88
//   0x00be9301: MOV EBP,dword ptr [ESP + 0x8c]    -> (E0-0x88)+0x8c = E0+4,
//                                                   stack word 1 (arg1)
//   0x00be9310: PUSH EBX ; 0x00be9327: PUSH EDI    -> ESP = E0 - 0x90
//   0x00be9317: MOV dword ptr [ESP + 0xc],EBX     -> (E0-0x8c)+0xc = E0-0x80,
//                                                   a local holding the +0x590
//                                                   sub-object pointer
//   with ESP = E0 - 0x90 the further frames resolve to
//     [ESP+0x9c] = E0+0xc  = arg3
//     [ESP+0xa0] = E0+0x10 = arg4
//     [ESP+0xa4] = E0+0x14 = arg5
//     [ESP+0x10] = E0-0x80 = the saved +0x590 pointer
//   two epilogues converge at 0x00be9844:
//     0x00be9842 POP EDI / 0x00be9843 POP EBX    (only on the pushed path)
//     0x00be9844 POP ESI  / 0x00be9845 POP EBP
//     0x00be9846 ADD ESP,0x80 / 0x00be984c RET 0x14
//   The early exit at 0x00be930a jumps straight to 0x00be9844 because EBX and
//   EDI have not been pushed on that path. That is why the frame reserves four
//   saved registers but pops only two on one of the two exits.
//
// Control flow in order:
//  1. self->+0x29c = arg2.                                    0x00be92f4
//  2. current = v590_4c(self->+0x590)();  if (arg1 == current) return;
//                                                            0x00be92ee..0x930a
//  3. if (self->+0x590 != 0) v590_00(self->+0x590)();        0x00be931b..9325
//  4. PUSH arg1; registry = 0x00b3d300(); record = b25f40(registry, arg1)
//     0x00b3d300 has a bare RET, so the pushed arg1 survives it and becomes
//     b25f40's stack word; b25f40 retires it with RET 0x4. b25f40 was read:
//     it walks a registry built from five interface pointers and returns the
//     element whose virtual slot +0x4c returns the requested id, else 0.
//     if (record == 0) { if (self->+0x590) v590_04(self->+0x590)(); return; }
//                                                            0x00be9327..9356
//  5. v120_58(&self->+0x120)();                               0x00be9359..9368
//  6. local = b25fb0(0x00b3d300());  isLocal = (record == local);
//     0x00b25fb0 was read: it calls 0x01021300(), and on a non-null result
//     re-enters b25f40 with that result's +0x84 word; on a null result it
//     returns its own [ESP+4] word, which at this callsite is not pushed.
//                                                            0x00be936a..937a
//  7. record->+0x44c = self ; record->+0x4bc = befab0(self);  0x00be937d..938b
//  8. self->+0x2e0 .. +0x2e6 = 1 (seven byte flags);          0x00be9394..93be
//  9. three (float, int) pairs at +0x748/+0x74c, +0x750/+0x754, +0x758/+0x75c
//     become (0.0f, -1): XORPS XMM0,XMM0 and OR EAX,-1 feed six stores.
//                                                            0x00be9388..93e7
// 10. the three floats at record+0xc4, +0xc8, +0xcc are MOVSS-loaded and
//     written as dwords to 0x00b3d4e0()->+0x68, +0x6c, +0x70.
//     0x00b3d4e0 was read: MOV EAX,[0x0167eb54] / RET.
//                                                            0x00be93ef..9430
// 11. self->+0x7d8/+0x7dc/+0x7e0 = the dwords at self->+0x590 -> +0xc4, +0xc8,
//     +0xcc;  self->+0x7e4/+0x7e8/+0x7ec = the dwords at record+0xc4, +0xc8,
//     +0xcc.                                                      0x00be9436..9481
// 12. if (self->+0x29c == 0 or 1) { be45b0(self, 0);
//     App::IAppSystem::Get()->slot+0x18(0x66e0e11, 0, 0, 0); }  0x00be9487..94b2
// 13. gate: if (0x00b5b800() != 0x01654c04) goto bind_only;    0x00be94b4..94be
//     if (!isLocal)                  goto bind_only;            0x00be94c4..94c7
//     then, and only then:
//       if (self->+0x810 != 0 && v810_10(self->+0x810) != 0) {
//           v810_0c(self->+0x810, 0); dc4c60(self); bc3110(&self->+0x230);
//           for (i = 0; i < ([ESI+0x344]-[ESI+0x340]) >> 2; ++i)
//               bfc6a0(self, [ [ESI+0x340] + i*4 ] + 0x120);
//           be2440(self, 0, 0); }                                0x00be94cd..9552
//     Control FALLS THROUGH out of this block into step 14.
// 14. trading = 0x00f67d90(0x00b3d300());   (0x00f67d90 was read:
//     MOV EAX,dword ptr [ECX + 0x74] / RET)                 0x00be9555..9561
//     if (arg3 != 0)             goto bind_and_commit;      0x00be9563..956c
//     if (self->+0x762 != 0)     goto bind_and_commit;      0x00be9572..9578
//     else fall into the arrival path.
//     bind_only (0x00be958d):  be88d0(self, arg1, arg3, arg5);
//                              JMP 0x00be9837  (epilogue, no commit block)
// 15. arrival path, 0x00be957e..0x00be97fc:
//       a. host = self->+0x320 ? self->+0x320 + 0x34 : 0;  ad7a30(&host, host)
//       b. ae09b0(0x00b3d4d0(0x115fa309), &host, 0);
//          0x00b3d4d0 was read: MOV EAX,[0x0167eb50] / RET.
//       c. bd7f70(self, &out);  ad79d0(&out, ad7b70(), 0)
//       d. ae09b0(0x00b3d4d0(0x3f04cafe), &out, 0)
//       e. probing: for self->+0x540 == 0/1/2 the hash 0x46bddaa / 0x46bdddc /
//          0x46bdde0 is tested with c772c0(trading, hash); a zero answer calls
//          c77bf0(trading, hash) and sets BL = 1, the "fallback" flag.
//          0x00c772c0 was read: it divides the hash by [ECX+0x1124], indexes
//          the bucket array at [ECX+0x1120] and walks a chain comparing the
//          first dword, returning 1 when any link matches. 0x00be961b..968d
//       f. event id, from self->+0x29c (a) and self->+0x540 (b):
//            a == b            -> 0x803 / 0x804 / 0x805 for a == 0 / 1 / 2
//            b == 0, fallback  -> (a != 1) * 2 + 0x902, else (a != 1) * 8 + 0x908
//            b == 0, no fb    -> (a != 1) * 8 + 0x908
//            b == 1, fallback  -> (-(a != 0) & 5) + 0x900
//            b == 1, no fb    -> (-(a != 0) & 0xb) + 0x906
//            b == 2, fallback  -> (a != 0) * 2 + 0x901
//            b == 2, no fb    -> (a != 0) * 2 + 0x907
//          Any selector outside 0..2 leaves the local at 0.  0x00be968f..9784
//       g. adde90(0x00b3d4d0(0x3988d136), &eventId, 0)
//       h. name = arg4 != 0 ? 0x014688f4 : 0x014688e8, read live as
//          "CVG_Capture_Nuked" and "CVG_Capture";
//          ae0930(0x00b3d4d0(name), 1, 0, 0, 0, eventId);      0x00be979b..97bd
//       i. App::IAppSystem::Get()->slot+0x18(0x6130eb9, 0, 0, 0);
//          self->+0x6c0 = 0; bc3130(&self->+0x6c8);
//          ad7ad0(&host); ad7ad0(&out);                0x00be97c2..97fc
//     bind_and_commit (0x00be97fe):  be88d0(self, arg1, arg3, arg5);
//          if (cf75d0(cf74c0())) { cf8e00(cf74c0()); cf7520(cf74c0()); }
//          0x00cf74c0 was read: MOV EAX,[0x0169d2c8] / RET.
// 16. epilogue: if (self->+0x590 != 0) v590_04(self->+0x590)(); 0x00be9837..9840
//
// Not claimed: the owning class; what either 0..2 selector enumerates; what any
// of the eight hashed constants names; what the eight event ids mean; and the
// meaning of the +0x748..+0x75c pairs. Sibling 0x00be88d0 (744 instructions,
// RET 0xc) shares the receiver, the +0x29c selector, the +0x2e0..+0x2e6 flags
// and the +0x120 / +0x590 sub-objects and is called from this body with
// (arg1, arg3, arg5); 0x00be9850 and 0x00be9980 repeat the same shape, so the
// five functions are siblings of one class.

#include "b11_opaque_types.hpp"

namespace openspore {
namespace b11 {
namespace t00be92e0 {

// 0x00b3d4e0 and 0x00b3d4d0 were read as two-instruction global getters.
// Simulator::cUIEventLog::Get and Simulator::cSpaceTrading::Get are the
// SDK-importer names for them; the global slots are 0x0167eb54 and 0x0167eb50.
inline constexpr std::uintptr_t kSpaceTradingGlobal = 0x0167eb50u;
inline constexpr std::uintptr_t kUIEventLogGlobal = 0x0167eb54u;
inline constexpr std::uintptr_t kTradingGlobal0169d2c8 = 0x0169d2c8u;

// Hashed constants pushed and consumed by the getter chain. Read from the
// disassembly; NOT decoded into names.
inline constexpr Dword kHash_115fa309 = 0x115fa309u;
inline constexpr Dword kHash_3f04cafe = 0x3f04cafeu;
inline constexpr Dword kHash_3988d136 = 0x3988d136u;
inline constexpr Dword kHash_46bddaa = 0x46bddaau;
inline constexpr Dword kHash_46bdddc = 0x46bdddcu;
inline constexpr Dword kHash_46bdde0 = 0x46bdde0u;
inline constexpr Dword kHash_66e0e11 = 0x66e0e11u;
inline constexpr Dword kHash_6130eb9 = 0x6130eb9u;

// String addresses read live from .rdata by ghidra_search_strings.
inline constexpr std::uintptr_t kEventNameCaptureAddr = 0x014688e8u;
inline constexpr std::uintptr_t kEventNameCaptureNukedAddr = 0x014688f4u;

struct ArrivalPorts {
    // Two-instruction global getters, read live.
    GlobalGetterEae0Fn registryGlobal;      // 0x00b3d300 -> [0x0167eae0]
    ModeProbeFn probeMode;                  // 0x00b5b800
    Ptr appSystem;                          // App::IAppSystem::Get()
    SpaceTradingGetFn spaceTradingGlobal;   // 0x00b3d4d0 -> [0x0167eb50]
    UIEventLogGetFn eventLogGlobal;         // 0x00b3d4e0 -> [0x0167eb54]
    SingletonGetter0169d2c8Fn tradingGlobal;  // 0x00cf74c0 -> [0x0169d2c8]

    // 0x00b25f40: ECX registry, one caller-cleaned stack word (RET 0x4).
    B25f40Fn findById;
    // 0x00b25fb0: bare RET, takes an uninitialised [ESP+4] on its fallback path.
    B25fb0Fn findCurrent;

    Word74GetterFn managerSlot74;           // 0x00f67d90 -> [ECX + 0x74]

    // Sibling bodies in the same class.
    ArrivalOneArgFn preEnter;               // 0x00be45b0
    ArrivalThreeArgFn bindTarget;           // 0x00be88d0
    ArrivalVoidFn reenter;                  // 0x00be2440
    ArrivalVoidC1Fn teardown230;            // 0x00bc3110
    ArrivalVoidC8Fn teardown6c8;            // 0x00bc3130
    Dc4c60Fn release810;                    // 0x00dc4c60
    Bfc6a0Fn elementTeardown;               // 0x00bfc6a0
    Befab0Fn recordStamp;                   // 0x00befab0
    Bd7f70Fn fillOut;                       // 0x00bd7f70

    // Trading subsystem.
    SpaceTradingThreeFn propertyLookup;     // 0x00ae09b0
    SpaceTradingEventFn emitEvent;          // 0x00ae0930
    Adde90Fn bindEventId;                   // 0x00adde90
    LookupProbeFn containmentProbe;         // 0x00c772c0
    LookupReportFn reportMissing;           // 0x00c77bf0
    OwnerBoolFn tradingQuery;               // 0x00cf75d0
    OwnerVoidFn tradingPush;                // 0x00cf8e00
    OwnerVoidFn tradingCommit;              // 0x00cf7520

    Ad79d0Fn copyOut;                       // 0x00ad79d0
    Ad7a30Fn initLocal;                     // 0x00ad7a30
    Ad7ad0Fn destroyLocal;                  // 0x00ad7ad0
    Ad7b70Fn defaultSource;                 // 0x00ad7b70

    // Virtual slots. ECX is the sub-object, the table is read from [ECX].
    VirtualFn v590_00;                      // slot +0x00
    VirtualFn v590_04;                      // slot +0x04
    VirtualFn v590_4c;                      // slot +0x4c
    VirtualFn v120_2c;                      // slot +0x2c, not called by this body
    VirtualFn v120_58;                      // slot +0x58
    VirtualFn v810_0c;                      // slot +0x0c
    VirtualFn v810_10;                      // slot +0x10
    VirtualFn appSlot18;                    // App::IAppSystem slot +0x18
};

// Step 15f, transcribed from the observed arithmetic. `fallback` is BL.
Dword select_event_id(Dword a, Dword b, bool fallback) {
    if (a == b) {
        // 0x00be96bb SUB EAX,EBP / JZ ; SUB EAX,1 / JZ ; SUB EAX,1 / JNZ
        if (a == 0) return 0x803u;  // 0x00be96e7
        if (a == 1) return 0x804u;  // 0x00be96da
        if (a == 2) return 0x805u;  // 0x00be96cd
        return 0u;                 // 0x00be96c7 leaves the local at 0
    }
    if (b == 0) {
        // 0x00be975c..0x00be976f: (a != 1) * 2 + 0x902, else * 8 + 0x908
        return fallback ? static_cast<Dword>((a != 1u) * 2u + 0x902u)
                        : static_cast<Dword>((a != 1u) * 8u + 0x908u);
    }
    if (b == 1) {
        if (fallback) {
            // 0x00be9734 NEG EAX / SBB EAX,EAX / AND EAX,0x5 / ADD EAX,0x900
            return static_cast<Dword>((a != 0u) ? 0x5u + 0x900u : 0x900u);
        }
        // 0x00be9746 NEG EAX / SBB EAX,EAX / AND EAX,0xb / ADD EAX,0x906
        return static_cast<Dword>((a != 0u) ? 0xbu + 0x906u : 0x906u);
    }
    if (b == 2) {
        if (fallback) {
            // 0x00be970c XOR EDX,EDX / SETNZ DL / LEA EDX,[EDX+EDX*1+0x901]
            return static_cast<Dword>((a != 0u) * 2u + 0x901u);
        }
        // 0x00be9720 XOR ECX,ECX / SETNZ CL / LEA ECX,[ECX+ECX*1+0x907]
        return static_cast<Dword>((a != 0u) * 2u + 0x907u);
    }
    // 0x00be9706 JNZ 0x00be9784: any b outside 0..2 leaves the zeroed local.
    return 0u;
}

void arrival_bind_target(ArrivalOwner* self, Dword arg1, Dword arg2, Dword arg3, Dword arg4,
                         Dword arg5, ArrivalPorts& p) {
    // 0x00be92f4
    self->field29c = arg2;
    Ptr sub590 = reinterpret_cast<Ptr>(self->field590);

    // 0x00be92ee..0x00be9308
    const Dword current = p.v590_4c(sub590);
    if (arg1 == current) {
        return;  // 0x00be930a JZ 0x00be9844, which skips the EBX/EDI pops
    }

    // 0x00be931b..0x00be9325
    if (sub590 != nullptr) {
        p.v590_00(sub590);
    }

    // 0x00be9327..0x00be9335. PUSH EBP precedes the bare-RET global getter, so
    // arg1 reaches 0x00b25f40 as its stack word.
    Ptr registry = reinterpret_cast<Ptr>(p.registryGlobal());
    Ptr record = p.findById(registry, arg1);
    // 0x00be9337..0x00be9356
    if (record == nullptr) {
        if (sub590 != nullptr) {
            p.v590_04(sub590);
        }
        return;  // 0x00be9842
    }

    // 0x00be9359..0x00be9368
    p.v120_58(reinterpret_cast<Ptr>(&self->field120));

    // 0x00be936a..0x00be937a
    Ptr local = p.findCurrent(registry);
    const bool isLocal = (record == local);

    // 0x00be937d / 0x00be938b
    *reinterpret_cast<Dword*>(reinterpret_cast<std::uintptr_t>(record) + 0x44c) =
        reinterpret_cast<Dword>(self);
    *reinterpret_cast<Dword*>(reinterpret_cast<std::uintptr_t>(record) + 0x4bc) = p.recordStamp(self);

    // 0x00be9394..0x00be93be
    self->field2e0 = 1;
    self->field2e1 = 1;
    self->field2e2 = 1;
    self->field2e3 = 1;
    self->field2e4 = 1;
    self->field2e5 = 1;
    self->field2e6 = 1;

    // 0x00be9388 XORPS XMM0,XMM0 / 0x00be9391 OR EAX,0xffffffff, six stores.
    self->field748 = 0.0f;
    self->field74c = 0xffffffffu;
    self->field750 = 0.0f;
    self->field754 = 0xffffffffu;
    self->field758 = 0.0f;
    self->field75c = 0xffffffffu;

    // 0x00be93ef..0x00be9413 - three MOVSS loads staged on the stack, then three
    // dword stores at 0x00be9426/0x00be942d/0x00be9430. The bit pattern is
    // preserved, so the transfer is modelled as a dword copy of each float.
    const Float* const rfloats =
        reinterpret_cast<const Float*>(reinterpret_cast<std::uintptr_t>(record) + 0xc4);
    union FloatBits {
        Float f;
        Dword u;
    };
    const FloatBits r0 = {rfloats[0]};
    const FloatBits r1 = {rfloats[1]};
    const FloatBits r2 = {rfloats[2]};

    // 0x00be9419 CALL 0x00b3d4e0 - the UI event log singleton.
    Ptr log = p.eventLogGlobal();
    Dword* const logSlots =
        reinterpret_cast<Dword*>(reinterpret_cast<std::uintptr_t>(log) + 0x68);
    logSlots[0] = r0.u;  // 0x00be9426
    logSlots[1] = r1.u;  // 0x00be942d
    logSlots[2] = r2.u;  // 0x00be9430

    // 0x00be9436..0x00be9457 - self->+0x590 + 0xc4/+0xc8/+0xcc
    const Dword* const prevWords =
        reinterpret_cast<const Dword*>(reinterpret_cast<std::uintptr_t>(sub590) + 0xc4);
    self->field7d8 = prevWords[0];
    self->field7dc = prevWords[1];
    self->field7e0 = prevWords[2];
    // 0x00be945d..0x00be9481 - record + 0xc4/+0xc8/+0xcc
    const Dword* const newWords =
        reinterpret_cast<const Dword*>(reinterpret_cast<std::uintptr_t>(record) + 0xc4);
    self->field7e4 = newWords[0];
    self->field7e8 = newWords[1];
    self->field7ec = newWords[2];

    // 0x00be9487..0x00be94b2
    if (self->field29c == 0 || self->field29c == 1) {
        p.preEnter(self, 0);
        p.appSlot18(p.appSystem, kHash_66e0e11, 0, 0, 0);
    }

    // 0x00be94b4..0x00be94c7 - the fast-path gate. Either failure jumps to
    // 0x00be958d, which binds and leaves without the commit block.
    if (p.probeMode() != kTelescopeSentinel01654c04 || !isLocal) {
        p.bindTarget(self, arg1, arg3, arg5);
        return;  // 0x00be95a5 JMP 0x00be9837
    }

    // 0x00be94cd..0x00be9552
    Ptr sub810 = reinterpret_cast<Ptr>(self->field810);
    if (sub810 != nullptr && p.v810_10(sub810) != 0) {
        p.v810_0c(sub810, 0);
        p.release810(self);
        p.teardown230(reinterpret_cast<Ptr>(&self->field230), nullptr);
        // 0x00be9505..0x00be9546 - (end - begin) >> 2 iterations, re-read each
        // trip so the bounds are not hoisted.
        for (Dword i = 0; i < ((self->field344 - self->field340) >> 2); ++i) {
            const Dword element =
                *reinterpret_cast<const Dword*>(static_cast<std::uintptr_t>(self->field340) +
                                                i * 4);
            p.elementTeardown(self, reinterpret_cast<Ptr>(reinterpret_cast<std::uintptr_t>(element) +
                                                           0x120));
        }
        p.reenter(self, 0, 0);
    }

    // 0x00be9555..0x00be9561
    Ptr trading = reinterpret_cast<Ptr>(p.managerSlot74(registry));

    // 0x00be9563..0x00be9578
    if (arg3 != 0 || self->field762 != 0) {
        p.bindTarget(self, arg1, arg3, arg5);
        if (p.tradingQuery(p.tradingGlobal()) != 0) {
            p.tradingPush(p.tradingGlobal());
            p.tradingCommit(p.tradingGlobal());
        }
        return;  // 0x00be9835 JMP 0x00be9837
    }

    // 0x00be957e..0x00be95aa - host, or 0 when +0x320 is null.
    std::uintptr_t hostAddr = 0;
    if (self->field320 != 0) {
        hostAddr = reinterpret_cast<std::uintptr_t>(self->field320) + 0x34;
    }
    Ptr host = reinterpret_cast<Ptr>(hostAddr);
    // 0x00be95ac..0x00be95b1 - the destination and the source word are the same
    // stack slot, so the callee is handed its own address twice.
    p.initLocal(&host, host);

    // 0x00be95b6..0x00be95c9
    p.propertyLookup(p.spaceTradingGlobal(), kHash_115fa309, &host, 0);

    // 0x00be95ce..0x00be95f2
    Ptr out = nullptr;
    p.fillOut(self, &out);
    p.copyOut(&out, p.defaultSource(), 0);

    // 0x00be95fd..0x00be9616
    p.propertyLookup(p.spaceTradingGlobal(), kHash_3f04cafe, &out, 0);

    // 0x00be961b..0x00be968d
    bool fallback = false;
    const Dword selector = self->field540;
    if (selector == 0) {
        if (p.containmentProbe(trading, kHash_46bddaa) == 0) {
            p.reportMissing(trading, kHash_46bddaa);
            fallback = true;
        }
    } else if (selector == 1) {
        if (p.containmentProbe(trading, kHash_46bdddc) == 0) {
            p.reportMissing(trading, kHash_46bdddc);
            fallback = true;
        }
    } else if (selector == 2) {
        if (p.containmentProbe(trading, kHash_46bdde0) == 0) {
            p.reportMissing(trading, kHash_46bdde0);
            fallback = true;
        }
    }

    // 0x00be968f..0x00be9784
    Dword eventId = select_event_id(self->field29c, selector, fallback);

    // 0x00be9784..0x00be9796
    p.bindEventId(p.spaceTradingGlobal(), kHash_3988d136, &eventId, 0);

    // 0x00be979b..0x00be97bd
    const char* const name = (arg4 != 0)
                                 ? reinterpret_cast<const char*>(kEventNameCaptureNukedAddr)
                                 : reinterpret_cast<const char*>(kEventNameCaptureAddr);
    p.emitEvent(p.spaceTradingGlobal(), name, 1, 0, 0, eventId);

    // 0x00be97c2..0x00be97d6
    p.appSlot18(p.appSystem, kHash_6130eb9, 0, 0, 0);

    // 0x00be97d8..0x00be97f7
    self->field6c0 = 0;
    p.teardown6c8(reinterpret_cast<Ptr>(&self->field6c8), 0);
    p.destroyLocal(&host);
    p.destroyLocal(&out);

    // 0x00be9837..0x00be9840
    if (sub590 != nullptr) {
        p.v590_04(sub590);
    }
}

}  // namespace t00be92e0
}  // namespace b11
}  // namespace openspore
