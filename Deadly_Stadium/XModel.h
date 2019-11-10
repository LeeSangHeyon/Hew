#ifndef XMODEL_H
#define XMODEL_H

#include <vector>
#include <Polygon.h>

class CXModel : public CPolygon{
public:
	CXModel(CPolygon::LAYER_LIST LayerNum, CPolygon::OBJECT_TYPE ObjectType) :CPolygon(LayerNum, ObjectType){}
	void Init(CXModelList::LABEL_XMODEL XModelNum);
	void Uninit();
	void Update();
	void Draw();
	void DrawWithOutRenderState();
	void MatrixTrans();
	void DrawSubSet(int nIndex, int nNum);
	void DrawSubSetSpeEv(int nIndex, int nNum, int nIndexEv, LPDIRECT3DCUBETEXTURE9 pCubeTexture);

	void SetAxis(D3DXVECTOR3 vAxis) { m_vAxis = vAxis; }
	void SetRotWithQuat(float fAngle);

	void SetQuaternion(D3DXQUATERNION q) { m_Quaternion = q; m_bQuat = true; }
	void SetMatrix(D3DXMATRIX mtx) { m_MtxWorld = mtx; m_bMatrix = true; }

	static CXModel *Create(CXModelList::LABEL_XMODEL XModelNum, CPolygon::LAYER_LIST LayerNum = CPolygon::LAYER_LIST::LL_DEFAULT, CPolygon::POLYGON_TYPE PolygonType = CPolygon::POLYGON_TYPE::PT_DEFAULT, CPolygon::OBJECT_TYPE ObjectType = CPolygon::OBJECT_TYPE::OT_AUTO_DESTROY);
private:
	D3DXQUATERNION m_Quaternion;
	D3DXMATRIX m_MtxRotX;
	D3DXMATRIX m_MtxRotY;
	D3DXMATRIX m_MtxRotZ;
	D3DXVECTOR3 m_vAxis;
};

#endif // !XMODEL_H
