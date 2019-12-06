
#ifndef __xfileH__
#define __xfileH__

#include <d3dx9.h>

typedef enum ModelIndex
{
	MODEL_BOXER,
	MODEL_FENCING,
	MODEL_BOW,
	MODEL_SAMPLE,
	MODEL_SWORD,
	MODEL_ZOMBIE,
	MODEL_WALL,
	MODEL_TORCH,
	MODEL_HELI,
	MODEL_HELIMOTTER,

	MODEL_INDEX_MAX
};

class Model
{
public:
	Model();
	~Model();

	void init(LPCSTR fileName);
	void init(LPCSTR fileName, D3DXVECTOR3 scl);
	void draw();
	void set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	D3DXMATRIX getMatrix();

private:
	LPD3DXMESH		pD3DXMeshModel;
	LPD3DXBUFFER	pD3DXBuffModel;
	DWORD			nNumMatModel;
	D3DMATERIAL9*		pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;
	D3DXVECTOR3 vScl;
	D3DXMATRIX _world;
};

void Model_Load();
void Model_Render(ModelIndex index, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif // __xfileH__
