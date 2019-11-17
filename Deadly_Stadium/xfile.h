
#ifndef __xfileH__
#define __xfileH__

#include <d3dx9.h>
#include <vector>

class XFile
{
public:
	XFile();
	~XFile();

	void init(LPCSTR fileName);
	void draw();
	void set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	D3DXMATRIX getMatrix();

private:
	//LPDIRECT3DDEVICE9       _device;
	LPD3DXMESH                      Mesh = NULL;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<LPDIRECT3DTEXTURE9> Textures;

	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _rot;
	D3DXVECTOR3 _sca;
	D3DXMATRIX _world;
};
#endif // __xfileH__
