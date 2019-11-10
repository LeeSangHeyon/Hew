
#include "camera.h"


CAMERA::CAMERA()
{
	posCameraEye = D3DXVECTOR3(0, 8.0f, -4.0f);
	posCameraAt = D3DXVECTOR3(0, 0, 0);
	vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	zRevise = -4.0f;
	maxflag = false;
}

void CAMERA::GetPlayerPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	cameraPos = (pos1 + pos2) / 2;
	abx = fabsf(pos1.x - pos2.x);
	abz = fabsf(pos1.z - pos2.z);
}

void CAMERA::Update()
{
	float revise = 0;

	if (abx > CRITICAL_X)
	{
		revise += (abx - CRITICAL_X) * 0.6f;
	}

	if (abz > CRITICAL_Z)
	{
		revise += (abz - CRITICAL_Z) * 0.72f;
	}

	if (revise >= 2.4f)
	{
		revise = 2.4f;
		maxflag = true;
	}
	else
	{
		maxflag = false;
	}

	posCameraEye.y = 8.0f + revise;
	posCameraAt.y = -revise * 0.8f;
	zRevise = -4.0f - revise / 2.0f;

	

	posCameraEye.x = cameraPos.x;
	posCameraAt.x = cameraPos.x;
	posCameraEye.z = cameraPos.z + zRevise;
	posCameraAt.z = cameraPos.z;

}

void CAMERA::Set()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) return;

	//�r���[�s��̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&posCameraEye,	//�J�������_
		&posCameraAt,	//�J���������_
		&vecCameraUp);	//�J���������

	//�r���[�s��̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);


	//�v���W�F�N�V�����s��̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		VIEW_ANGLE,		//�r���[���ʂ̎���p
		VIEW_ASPECT,	//�r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,	//�r���[���ʂ�NearZ
		VIEW_FAR_Z);	//�r���[���ʂ�FarZ

	//�v���W�F�N�V�����s��̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

}