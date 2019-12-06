
#include "common.h"
#include "model.h"
#include "mydirect3d.h"

#define MODEL_FILENAME_MAX (64)
// モデルファイル管理構造体
typedef struct ModelFile_tag
{
	char filename[MODEL_FILENAME_MAX]; // モデルファイル名
	D3DXVECTOR3 scale;	//モデル大きさ
} ModelFile;

static const ModelFile g_ModelFiles[] = {
	{"asset/model/boxer.x",{3,3,3} },
	{"asset/model/fencing.x",{3,3,3}},
	{"asset/model/bow.x",{3,3,3}},
	{"asset/model/sample.x",{0.1f,0.05f,0.8f}},
	{"asset/model/sword.x",{0.3,0.4,0.3}},
	{"asset/model/zombie.x",{3,3,3}},
	{"asset/model/cube.x",{ 0.499,1,0.499 }},
	{"asset/model/torch.x",{ 0.499,0.8,0.499 }},
	{"asset/model/Heli.x",{10,10,10}},
	{"asset/model/HeliMotter.x",{10,10,10}},
};

// 読み込みテクスチャ数
static const int MODEL_FILE_COUNT = sizeof(g_ModelFiles) / sizeof(g_ModelFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// 読み込みモデル数とテクスチャ管理番号列挙数に差があった場合コンパイルエラーとする
static_assert(MODEL_INDEX_MAX == MODEL_FILE_COUNT, "MODEL_INDEX_MAX != MODEL_FILE_COUNT");

Model model[MODEL_FILE_COUNT];

void Model_Load()
{
	for (int i = 0; i < MODEL_FILE_COUNT; i++)
	{
		model[i].init(g_ModelFiles[i].filename, g_ModelFiles[i].scale);
	}
}

void Model_Render(ModelIndex index, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	model[index].set(pos, rot);
	model[index].draw();
}

Model::Model()
{

}

void Model::init(LPCSTR fileName, D3DXVECTOR3 scl)
{
	vScl = scl;

	//_device = device;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	HRESULT hr = 0;

	hr = D3DXLoadMeshFromX(
		fileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&pD3DXBuffModel,
		NULL,
		&nNumMatModel,
		&pD3DXMeshModel);

	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXLoadMeshFromX() - FAILED", 0, 0);
	}


	D3DXMATERIAL	*pD3DXMat;

	pD3DXMat = (D3DXMATERIAL*)pD3DXBuffModel->GetBufferPointer();
	pMeshMaterials = new D3DMATERIAL9[nNumMatModel];
	pMeshTextures = new LPDIRECT3DTEXTURE9[nNumMatModel];

	for (DWORD i = 0; i < nNumMatModel; i++)
	{
		pMeshMaterials[i] = pD3DXMat[i].MatD3D;
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
		pMeshTextures[i] = NULL;
		if (pD3DXMat[i].pTextureFilename != NULL &&
			lstrlen(pD3DXMat[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice, pD3DXMat[i].pTextureFilename, &pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}

}

void Model::init(LPCSTR fileName)
{
	//_device = device;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	HRESULT hr = 0;

	//
	// Load the XFile data.
	//

	hr = D3DXLoadMeshFromX(
		fileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&pD3DXBuffModel,
		NULL,
		&nNumMatModel,
		&pD3DXMeshModel);

	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXLoadMeshFromX() - FAILED", 0, 0);
		//return false;
	}

	//
	// Extract the materials, and load textures.
	//

	D3DXMATERIAL	*pD3DXMat;

	pD3DXMat = (D3DXMATERIAL*)pD3DXBuffModel->GetBufferPointer();
	pMeshMaterials = new D3DMATERIAL9[nNumMatModel];
	pMeshTextures = new LPDIRECT3DTEXTURE9[nNumMatModel];

	for (DWORD i = 0; i < nNumMatModel; i++)
	{
		pMeshMaterials[i] = pD3DXMat[i].MatD3D;
		pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;
		pMeshTextures[i] = NULL;
		if (pD3DXMat[i].pTextureFilename != NULL &&
			lstrlen(pD3DXMat[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice, pD3DXMat[i].pTextureFilename, &pMeshTextures[i])))
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
				break;
			}
		}
	}


}

Model::~Model()
{
	if (pD3DXMeshModel != NULL)
	{
		pD3DXMeshModel->Release();
		pD3DXMeshModel = NULL;
	}

	if (pD3DXBuffModel != NULL)
	{
		pD3DXBuffModel->Release();
		pD3DXBuffModel = NULL;
	}
}

void Model::draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (_world)
		pDevice->SetTransform(D3DTS_WORLD, &_world);

	for (int nCntMat = 0; nCntMat < nNumMatModel; nCntMat++)
	{
		pDevice->SetMaterial(&pMeshMaterials[nCntMat]);
		pDevice->SetTexture(0, pMeshTextures[nCntMat]);
		pD3DXMeshModel->DrawSubset(nCntMat);
	}
}

void Model::set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXMATRIX Scale;
	D3DXMATRIX Rotation;
	D3DXMATRIX Transform;

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	D3DXMatrixScaling(&Scale, vScl.x, vScl.y, vScl.z);
	D3DXMatrixMultiply(&world, &world, &Scale);

	D3DXMatrixRotationYawPitchRoll(&Rotation, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&world, &world, &Rotation);

	D3DXMatrixTranslation(&Transform, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&world, &world, &Transform);

	vPos = pos;
	vRot = rot;
	_world = world;
}

void Model::set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	D3DXMATRIX Scale;
	D3DXMATRIX Rotation;
	D3DXMATRIX Transform;

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	D3DXMatrixScaling(&Scale, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&world, &world, &Scale);

	D3DXMatrixRotationYawPitchRoll(&Rotation, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&world, &world, &Rotation);

	D3DXMatrixTranslation(&Transform, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&world, &world, &Transform);

	vPos = pos;
	vRot = rot;
	vScl = scl;
	_world = world;
}

D3DXMATRIX Model::getMatrix()
{
	return _world;
}

