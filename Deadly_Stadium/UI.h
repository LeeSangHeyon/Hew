#pragma once

#include <d3dx9.h>
#include "common.h"
#include "player.h"

class UI
{
private:
	BYTE Prof;
	PLAYER_STATUS player1;
	PLAYER_STATUS player2;
	bool bClear;
	int Count;

public:
	UI();
	void Init();
	void Update(PLAYER_STATUS p1, PLAYER_STATUS p2);
	void Draw();
};

bool GetTorchStart();