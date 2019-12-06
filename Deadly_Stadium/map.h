#pragma once

bool IsWall(int x, int y);
void SetTorch();
D3DXVECTOR3 GetTorchPos();
void InitMap();
void UpdateMap();
void DrawMap();
void SetSpawnPoint();