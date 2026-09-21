// Decompiler capture (Ghidra 12.1.2, SporeApp.exe 3.1.0.22) of FUN_00e806b0
// @ 0x00e806b0.  EVIDENCE ONLY, NOT TRUTH.
// NOTE: no MSVC RTTI in this binary; Ghidra's type casts (ITextureManager,
// D3DFORMAT, ITextureManager*) are the decompiler's GUESSES and are not trusted.
// SDK-confirmed symbol names (Simulator::Cell::*) ARE real.

void FUN_00e806b0(ITextureManager *param_1, float param_2, int param_3, int param_4,
                  int param_5, D3DFORMAT param_6, int param_7)
{
  char cVar1;
  cIDGenerator *pcVar2;
  ITextureManager *pIVar3;
  cSpaceTrading *pcVar4;
  int iVar5;
  int *piVar6;
  float unaff_ESI;
  float fVar7;
  undefined4 unaff_retaddr;

  FUN_00e84bf0();
  iVar5 = *(int *)(Simulator__Cell__sCellGame + 0x51e0);   // game-state word
  if (iVar5 == 0) {
    if ((*(int *)(Simulator__Cell__sCellGame + 0x515c) == 0) && ((float)param_1 != 0.0)) {
      *(int *)(Simulator__Cell__sCellGame + 0x5160) = *(int *)(Simulator__Cell__sCellGame + 0x5160) + 1;
      fVar7 = (float)param_1 * 1000.0;       // dt -> ms
      param_2 = param_2 * 1000.0;
      FUN_00e82de0((int)ROUND(param_2), (int)ROUND(fVar7));
      pcVar4 = Simulator__cSpaceTrading__Get();
      (*pcVar4->_vftable1[0xe]._virtual_dtor)((IVirtual *)(int)ROUND(param_2), (int)ROUND(fVar7));
      iVar5 = FUN_00b3d3f0();
      (**(code **)(*(int *)(iVar5 + 4) + 0x38))((int)ROUND(param_2), (int)ROUND(fVar7));
      piVar6 = (int *)(*(int *)(Simulator__Cell__sCellGame + 0x5190) + 0x74);
      *piVar6 = *piVar6 + (int)ROUND(unaff_ESI);
      Simulator__Cell__MovePlayerToMousePosition(param_2);   // << MOVEMENT: mouse-ray -> move plane
      FUN_00e7f3a0(param_2);
      if (*(char *)(Simulator__Cell__sCellGame + 0x51d8) == 1) {
        // ... eat / interact branch (sCellGame+0x51d8 gate) ...
      }
      FUN_00e73f60();
      FUN_00e53b00(param_2);
      FUN_00e600a0(param_2, 0);
      FUN_00e6c9f0(param_2);
      return;
    }
    // idle / not-active branch
  }
  else if ((float)param_1 != 0.0) {
    if (iVar5 == 1) { /* texture-gen branch (decompiler guess) */ }
    else if (iVar5 == 2) { /* id-generation branch (decompiler guess) */ }
  }
}
