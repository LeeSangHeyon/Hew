
#include "Light.h"

static D3DLIGHT9 g_light;
static D3DXVECTOR3 g_vDir(2.0f, -6.0f, 0.0f);

void CLight::Init()
{
	ZeroMemory(&g_light, sizeof(g_light));
	g_light.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVec3Normalize((D3DXVECTOR3*)&g_light.Direction, &g_vDir);

	g_light.Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	g_light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	g_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	//g_light.Falloff = 10;
}

void CLight::Uninit()
{

}

void CLight::Set(bool bStatus)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (bStatus)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
		pDevice->SetLight(0, &g_light);
		pDevice->LightEnable(0, TRUE);
	}
	else
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}
}

D3DXVECTOR3 CLight::GetDir()
{
	return g_vDir;
}

D3DLIGHT9 CLight::GetLight()
{
	return g_light;
}