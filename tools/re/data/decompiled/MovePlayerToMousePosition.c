// Decompiler capture (Ghidra 12.1.2, SporeApp.exe 3.1.0.22) of
// Simulator::Cell::MovePlayerToMousePosition @ 0x00e5b790.
// EVIDENCE ONLY, NOT TRUTH. SDK name is CONFIRMED; cast types are guesses.

void Simulator__Cell__MovePlayerToMousePosition(float deltaTime)
{
  char cVar1;
  int iVar2, iVar3;
  float fVar6;

  if (*(int *)(Simulator__Cell__sCellGame + 0x5158) != 0)   // lock/paused flag
    return;

  iVar2 = FUN_00b721d0(*(undefined4 *)(Simulator__Cell__sCellGame + 0x411c)); // player entity by index
  if (iVar2 == 0) return;

  FUN_00e5b2e0(deltaTime);     // per-frame update
  FUN_00743b50();

  iVar3 = FUN_00e4ce40(local); // camera/scene struct
  iVar3 = *(int *)(iVar3 + 0xd4);  // camera mode
  FUN_00e82130();
  // ... UI selection gating (sCellUI +0x24/+0x26) ...

  // --- RAY-PLANE INTERSECTION ---
  FUN_007c4900(&origin, &dir);  // camera origin + view ray (via ILightingWorld)
  // plane normal: DAT_015a7c40/44/48 ; plane point: DAT_016b3c28/2c/30
  denom = dir.x*N.x + dir.y*N.y + dir.z*N.z;                 // fStack_30
  if (denom != 0.0) {
    t = -(origin . N + offset) / denom;                      // fVar6
    if (t >= 0.0) {
      *(player + 0x08) = origin.x + dir.x * t;   // target pos X
      *(player + 0x0c) = origin.y + dir.y * t;   // target pos Y
      *(player + 0x10) = origin.z + dir.z * t;   // target pos Z
      *(sCellGame + 0x5190 + 0xe0) = 1;          // 'moving' flag
      delta = -(target - current);               // current at player+0x4c/0x50/0x54
      FUN_0069b600(&orient, &delta, &N);         // orientation to face travel
      *(player + 0x14) = orient[0]; *(player + 0x18) = orient[1];
      *(player + 0x1c) = orient[2]; *(player + 0x20) = orient[3];
    }
  }
}
