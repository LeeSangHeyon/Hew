#pragma once

#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "common.h"
#include "player.h"

#define CRITICAL_X	(6.0f)
#define CRITICAL_Z	(4.0f)

class CAMERA	//カメラのクラス
{

private:
	
	//プロジェクション&カメラ行列
	D3DXMATRIX		mtxView;				//ビューマトリックス
	D3DXMATRIX		mtxProjection;		//プロジェクションマトリックス

		//カメラ用パラメータ
	D3DXVECTOR3		posCameraEye;			//カメラ位置
	D3DXVECTOR3		posCameraAt;			//カメラ注視点
	D3DXVECTOR3		vecCameraUp;			//カメラ上方向

	D3DXVECTOR3		cameraPos;
	float abx;
	float abz;
	float zRevise;
	bool maxflag;

public:

	CAMERA();	//初期設定

	void GetPlayerPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);

	void Update();

	void Set();

};