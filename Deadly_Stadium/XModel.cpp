#include "main.h"
#include "XModel.h"
#include "polygon3Dtest.h"
#include "debug.h"
#include "Light.h"
#include "ResourseManager.h"

void CXModel::Init(CXModelList::LABEL_XMODEL XModelNum)
{
	m_nModelNum = XModelNum;
	LPDIRECT3DDEVICE9 pDevice = CDXRenderer::GetDevice();
	//ワールド
	D3DXMatrixIdentity(&m_MtxWorld);

	HRESULT hr;	// Heap Memory

	bool bExist = CResourseManager::PushAndCheck(CResourseManager::RESOURSE_TYPE::RT_XMODEL, m_nModelNum);

	if (!bExist)
	{
		hr = D3DXLoadMeshFromX
		(
			CXModelList::GetStatus((CXModelList::LABEL_XMODEL)m_nModelNum).cFlieAddress,
			D3DXMESH_MANAGED,
			pDevice,
			&m_XModel.pAdjacency,
			&m_XModel.pMaterialBuffer,
			NULL,
			&m_XModel.nMaterialNum,
			&m_XModel.pMesh
		);

		hr = m_XModel.pMesh->OptimizeInplace
		(
			D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)m_XModel.pAdjacency->GetBufferPointer(),
			NULL,
			NULL,
			NULL
		);

		if (m_XModel.pAdjacency)
		{
			m_XModel.pAdjacency->Release();
		}

		D3DVERTEXELEMENT9 pElement[MAXD3DDECLLENGTH + 1];
		m_XModel.pMesh->GetDeclaration(pElement);
		hr = m_XModel.pMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, pElement, pDevice, &m_XModel.pTempMesh);

		if (m_XModel.pMesh)
		{
			m_XModel.pMesh->Release();
		}
		m_XModel.pMesh = m_XModel.pTempMesh;

		//マテリアルの取得
		m_XModel.pMaterial = (LPD3DXMATERIAL)m_XModel.pMaterialBuffer->GetBufferPointer();

		if (CXModelList::GetStatus((CXModelList::LABEL_XMODEL)m_nModelNum).bTexture)
		{
			for (int j = 0; j < m_XModel.nMaterialNum; j++)
			{
				if (m_XModel.pMaterial[j].pTextureFilename != NULL)
				{
					LPDIRECT3DTEXTURE9 pTexture;
					hr = D3DXCreateTextureFromFile
					(
						pDevice,
						m_XModel.pMaterial[j].pTextureFilename,
						&pTexture
					);

					m_XModel.pTexture.push_back(pTexture);

					if (FAILED(hr))
					{
						MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
					}
				}
				else
				{
					m_XModel.pTexture.push_back(NULL);
				}
			}
		}
	}
	else
	{
		m_XModel = CPolygon::CopyModel(m_nModelNum);
	}
	D3DXQuaternionIdentity(&m_Quaternion);
}

void CXModel::Uninit()
{
	int nNum = CResourseManager::PopAndCheck(CResourseManager::RESOURSE_TYPE::RT_XMODEL, m_nModelNum);

	if (nNum == 0)
	{
		if (m_XModel.pMesh)
		{
			m_XModel.pMesh->Release();
			m_XModel.pMesh = NULL;
		}
		if (m_XModel.pMaterialBuffer)
		{
			m_XModel.pMaterialBuffer->Release();
			m_XModel.pMaterialBuffer = NULL;
		}
		if (CXModelList::GetStatus((CXModelList::LABEL_XMODEL)m_nModelNum).bTexture)
		{
			for (unsigned int j = 0; j < m_XModel.nMaterialNum; j++)
			{
				if (m_XModel.pTexture[j] != NULL)
				{
					m_XModel.pTexture[j]->Release();
					m_XModel.pTexture[j] = NULL;
				}
			}
			m_XModel.pTexture.clear();
		}
	}
	else
	{
		m_XModel.pTexture.clear();
	}
}

void CXModel::Update()
{

}

void CXModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CDXRenderer::GetDevice();

	if (m_bMatrix)
	{

	}
	else
	{
		D3DXMatrixIdentity(&m_MtxWorld);

		if (m_vScale.x != 1.0f || m_vScale.y != 1.0f || m_vScale.z != 1.0f)
		{
			D3DXMatrixScaling(&m_MtxScale, m_vScale.x, m_vScale.y, m_vScale.z);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxScale);
		}

		if (m_bQuat)
		{
			D3DXMatrixRotationQuaternion(&m_MtxRot, &m_Quaternion);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRot);
		}
		else
		{
			if (m_vRotation.x != 0.0f)
			{
				D3DXMatrixRotationX(&m_MtxRotX, m_vRotation.x);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotX);
			}
			if (m_vRotation.y != 0.0f)
			{
				D3DXMatrixRotationY(&m_MtxRotY, m_vRotation.y);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotY);
			}
			if (m_vRotation.z != 0.0f)
			{
				D3DXMatrixRotationZ(&m_MtxRotZ, m_vRotation.z);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotZ);
			}
		}

		D3DXMatrixTranslation(&m_MtxTrans, m_vPos.x, m_vPos.y, m_vPos.z);

		D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxTrans);
	}
	CLight::Set(m_bLight);
	CRenderState::SetZBuffer(m_bZBuffer);
	CRenderState::SetFillMode(m_FillMode);
	pDevice->SetRenderState(D3DRS_CULLMODE, m_CullMode);

	for (int i = 0; i < m_XModel.nMaterialNum; i++)
	{
		//各種行列の設定
		pDevice->SetTransform
		(
			D3DTS_WORLD,
			&m_MtxWorld
		);
		pDevice->SetMaterial(&m_XModel.pMaterial[i].MatD3D);
		pDevice->SetViewport(&m_ViewPort);

		if (CXModelList::GetStatus((CXModelList::LABEL_XMODEL)m_nModelNum).bTexture)
		{
			pDevice->SetTexture(0, m_XModel.pTexture[i]);
		}
		m_XModel.pMesh->DrawSubset(i);
	}
}

void CXModel::DrawWithOutRenderState()
{
	LPDIRECT3DDEVICE9 pDevice = CDXRenderer::GetDevice();

	if (m_bMatrix)
	{

	}
	else
	{
		D3DXMatrixIdentity(&m_MtxWorld);

		if (m_vScale.x != 1.0f || m_vScale.y != 1.0f || m_vScale.z != 1.0f)
		{
			D3DXMatrixScaling(&m_MtxScale, m_vScale.x, m_vScale.y, m_vScale.z);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxScale);
		}

		if (m_bQuat)
		{
			D3DXMatrixRotationQuaternion(&m_MtxRot, &m_Quaternion);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRot);
		}
		else
		{
			if (m_vRotation.x != 0.0f)
			{
				D3DXMatrixRotationX(&m_MtxRotX, m_vRotation.x);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotX);
			}
			if (m_vRotation.y != 0.0f)
			{
				D3DXMatrixRotationY(&m_MtxRotY, m_vRotation.y);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotY);
			}
			if (m_vRotation.z != 0.0f)
			{
				D3DXMatrixRotationZ(&m_MtxRotZ, m_vRotation.z);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotZ);
			}
		}

		D3DXMatrixTranslation(&m_MtxTrans, m_vPos.x, m_vPos.y, m_vPos.z);

		D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxTrans);
	}
	//CLight::Set(m_bLight);

	for (int i = 0; i < m_XModel.nMaterialNum; i++)
	{
		//各種行列の設定
		pDevice->SetTransform
		(
			D3DTS_WORLD,
			&m_MtxWorld
		);
		pDevice->SetMaterial(&m_XModel.pMaterial[i].MatD3D);
		if (CXModelList::GetStatus((CXModelList::LABEL_XMODEL)m_nModelNum).bTexture)
		{
			pDevice->SetTexture(0, m_XModel.pTexture[i]);
		}
		m_XModel.pMesh->DrawSubset(i);
	}
	//pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
}

void CXModel::SetRotWithQuat(float fAngle)
{
	D3DXQuaternionRotationAxis(&m_Quaternion, &m_vAxis, fAngle);
	D3DXMatrixRotationQuaternion(&m_MtxRot, &m_Quaternion);
}

void CXModel::MatrixTrans()
{
	if (m_bMatrix)
	{

	}
	else
	{
		D3DXMatrixIdentity(&m_MtxWorld);

		if (m_vScale.x != 1.0f || m_vScale.y != 1.0f || m_vScale.z != 1.0f)
		{
			D3DXMatrixScaling(&m_MtxScale, m_vScale.x, m_vScale.y, m_vScale.z);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxScale);
		}

		if (m_bQuat)
		{
			D3DXMatrixRotationQuaternion(&m_MtxRot, &m_Quaternion);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRot);
		}
		else
		{
			if (m_vRotation.x != 0.0f)
			{
				D3DXMatrixRotationX(&m_MtxRotX, m_vRotation.x);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotX);
			}
			if (m_vRotation.y != 0.0f)
			{
				D3DXMatrixRotationY(&m_MtxRotY, m_vRotation.y);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotY);
			}
			if (m_vRotation.z != 0.0f)
			{
				D3DXMatrixRotationZ(&m_MtxRotZ, m_vRotation.z);
				D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxRotZ);
			}
		}

		D3DXMatrixTranslation(&m_MtxTrans, m_vPos.x, m_vPos.y, m_vPos.z);

		D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &m_MtxTrans);
	}
}

void CXModel::DrawSubSet(int nIndex, int nNum)
{
	LPDIRECT3DDEVICE9 pDevice = CDXRenderer::GetDevice();

	CRenderState::SetZBuffer(m_bZBuffer);

	pDevice->SetTexture(nIndex, m_XModel.pTexture[nNum]);

	m_XModel.pMesh->DrawSubset(nNum);
}

void CXModel::DrawSubSetSpeEv(int nIndex, int nNum, int nIndexEv, LPDIRECT3DCUBETEXTURE9 pCubeTexture)
{
	LPDIRECT3DDEVICE9 pDevice = CDXRenderer::GetDevice();

	CRenderState::SetZBuffer(m_bZBuffer);

	pDevice->SetTexture(nIndex, m_XModel.pTexture[nNum]);
	pDevice->SetTexture(nIndexEv, pCubeTexture);

	m_XModel.pMesh->DrawSubset(nNum);
}

CXModel *CXModel::Create(CXModelList::LABEL_XMODEL XModelNum, CPolygon::LAYER_LIST LayerNum, CPolygon::POLYGON_TYPE PolygonType, CPolygon::OBJECT_TYPE ObjectType)
{
	CXModel *p = new CXModel(LayerNum, ObjectType);
	p->Init(XModelNum);
	p->SetType(PolygonType);
	return p;
}