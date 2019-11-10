#pragma once

#include <d3dx9.h>
#include <math.h>
#include "mydirect3d.h"
#include "texture.h"
#include "common.h"
#include "player.h"

#define CRITICAL_X	(6.0f)
#define CRITICAL_Z	(4.0f)

class CAMERA	//�J�����̃N���X
{

private:
	
	//�v���W�F�N�V����&�J�����s��
	D3DXMATRIX		mtxView;				//�r���[�}�g���b�N�X
	D3DXMATRIX		mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X

		//�J�����p�p�����[�^
	D3DXVECTOR3		posCameraEye;			//�J�����ʒu
	D3DXVECTOR3		posCameraAt;			//�J���������_
	D3DXVECTOR3		vecCameraUp;			//�J���������

	D3DXVECTOR3		cameraPos;
	float abx;
	float abz;
	float zRevise;
	bool maxflag;

public:

	CAMERA();	//�����ݒ�

	void GetPlayerPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);

	void Update();

	void Set();

};