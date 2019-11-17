
#include "common.h"
#include "xfile.h"
#include "mydirect3d.h"


//
// Framework functions
//
XFile::XFile()
{
	
}

void XFile::init(LPCSTR fileName)
{
	//_device = device;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	HRESULT hr = 0;

	//
	// Load the XFile data.
	//

	LPD3DXBUFFER adjBuffer = 0;
	LPD3DXBUFFER mtrlBuffer = 0;
	DWORD        numMtrls = 0;

	hr = D3DXLoadMeshFromX(
		fileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&Mesh);

	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXLoadMeshFromX() - FAILED", 0, 0);
		//return false;
	}

	//
	// Extract the materials, and load textures.
	//

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			// the MatD3D property doesn't have an ambient value set
			// when its loaded, so set it now:
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// save the ith material
			Mtrls.push_back(mtrls[i].MatD3D);

			// check if the ith material has an associative texture
			if (mtrls[i].pTextureFilename != 0)
			{
				// yes, load the texture for the ith subset
				LPDIRECT3DTEXTURE9 tex = 0;
				D3DXCreateTextureFromFile(
					pDevice,
					mtrls[i].pTextureFilename,
					&tex);

				// save the loaded texture
				Textures.push_back(tex);
			}
			else
			{
				// no texture for the ith subset
				Textures.push_back(0);
			}
		}
	}
	//d3d::Release<ID3DXBuffer*>(mtrlBuffer); // done w/ buffer
	mtrlBuffer->Release();
	mtrlBuffer = NULL;

	//
	// Optimize the mesh.
	//

	hr = Mesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0);

	//d3d::Release<ID3DXBuffer*>(adjBuffer); // done w/ buffer
	adjBuffer->Release();
	adjBuffer = NULL;


	if (FAILED(hr))
	{
		::MessageBox(0, "OptimizeInplace() - FAILED", 0, 0);
		//return false;
	}
}

XFile::~XFile()
{
	//d3d::Release<ID3DXMesh*>(Mesh);
	Mesh->Release();

	//for (int i = 0; i < Textures.size(); i++)
	//{
	//	//d3d::Release<IDirect3DTexture9*>(Textures[i]);
	//	Textures[i]->Release();
	//	Textures[i] = NULL;
	//}
}

void XFile::draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (_world)
		pDevice->SetTransform(D3DTS_WORLD, &_world);

	for (int i = 0; i < Mtrls.size(); i++)
	{
		pDevice->SetMaterial(&Mtrls[i]);
		pDevice->SetTexture(0, Textures[i]);
		Mesh->DrawSubset(i);
	}
}

void XFile::set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
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

	_pos = pos;
	_rot = rot;
	_sca = scl;
	_world = world;
}

D3DXMATRIX XFile::getMatrix()
{
	return _world;
}

