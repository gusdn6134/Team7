#include "pch.h"
#include "CTerrain.h"
#include "CTextureMgr.h"
#include "CDevice.h"
#include "MainFrm.h"
#include "CMapTool.h"


CTerrain::CTerrain() : m_pMainView(nullptr), m_iTileIndex(0), m_bPicking(false), m_MapSizeX(0), m_MapSizeY(0), m_iChangeIndex(0)
{
	//TILE
	ZeroMemory(&pTexInfo, sizeof(TEXINFO));
	//ZeroMemory(&pTexInfo, sizeof(TILE));
	//m_vecTile.reserve(TILEX * TILEY);

}
CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Initialize()
{
	//if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
	//	L"../Texture/Stage/Terrain/Tile/Tile%d.png",
	//	TEX_MULTI, L"Terrain", L"Tile", 36)))
	//{
	//	AfxMessageBox(L"Terrain Texture Insert Failed");
	//	return E_FAIL;
	//}

	GET_ScrollView																		   
	m_pMainView = pScrollView;


	//pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Tile", L"Tile_", 0);

	return S_OK;
}

void CTerrain::Update()
{
	
}

void CTerrain::Render()
{
	if(!m_bIsRender) return;
	if (m_vecTile == nullptr) return;

	D3DXMATRIX matWorld, matScale, matTrans;

	TCHAR szBuf[MIN_STR] = L"";
	//int iIndex(0);

	for (auto pTile : *m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			pTile->vPos.x - m_pMainView->GetScrollPos(0),
			pTile->vPos.y - m_pMainView->GetScrollPos(1),
			pTile->vPos.z);

		matWorld = matScale * matTrans;

		RECT	rc{};

		GetClientRect(m_pMainView->m_hWnd, &rc);

		float	fX = WINCX / float(rc.right - rc.left);
		float	fY = WINCY / float(rc.bottom - rc.top);
		Set_Ratio(&matWorld, fX, fY);
		
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		if (pTile->byDrawID == 205)
			return;
		
		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Tile", L"Tile_", pTile->byDrawID);
	
		CDevice::Get_Instance()->Get_Sprite()->Draw(
			pTexInfo->pTexture,  
			nullptr,  
			nullptr,  
			nullptr,  
			D3DCOLOR_ARGB(255, 255, 255, 255));
	
	/*	swprintf_s(szBuf, L"%d", iIndex);

		CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
			szBuf,
			lstrlen(szBuf),
			nullptr,
			0,
			D3DCOLOR_ARGB(255, 255, 255, 255));*/

		//iIndex++;

	}
}

void CTerrain::Release()
{
	for_each(m_vecTile->begin(), m_vecTile->end(), Safe_Delete<TILE*>);
	m_vecTile->clear();
	m_vecTile->shrink_to_fit();
}

void CTerrain::Picking_Tile(const D3DXVECTOR3& vPos, const BYTE& byDrawID)
{

	if (vPos.x < 0 || vPos.y < 0)
		return;

	// 스크롤 값 보정
	int scrollX = m_pMainView->GetScrollPos(SB_HORZ);
	int scrollY = m_pMainView->GetScrollPos(SB_VERT);

	float worldX = vPos.x + scrollX;
	float worldY = vPos.y + scrollY;

	

	int iTileX = m_MapSizeX; //1500 / TILECX;  // 가로 타일 개수
	int iTileY = m_MapSizeY; // 920 / TILECY;  // 세로 타일 개수

	int x = int(worldX / TILECX);
	int y = int(worldY / TILECY);

	m_iTileIndex = y * iTileX + x;  // `1500` 대신 `iTileX` 사용

	if (m_vecTile->empty() || m_iTileIndex >= m_vecTile->size())
		return;

	if (m_iTileIndex < 0 || m_iTileIndex >= (int)m_vecTile->size())
		return;


	m_vecTile->at(m_iTileIndex)->byDrawID = byDrawID;
	m_vecTile->at(m_iTileIndex)->byOption = 1;
}


void CTerrain::Tile_Change(const D3DXVECTOR3& vPos, const BYTE& byDrawID)
{
	/*int iIndex = Get_TileIdx(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile-at(iIndex)->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = 1;*/
}

void CTerrain::Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY)
{
	pOut->_11 *= _fX;
	pOut->_21 *= _fX;
	pOut->_31 *= _fX;
	pOut->_41 *= _fX;

	pOut->_12 *= _fY;
	pOut->_22 *= _fY;
	pOut->_32 *= _fY;
	pOut->_42 *= _fY;

}



//bool CTerrain::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
//{
//	// 12 -> 3 -> 6 -> 9
//	float	fGradient[4] =
//	{
//		(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
//		(TILECY / 2.f) / (TILECX / 2.f),
//		(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
//		(TILECY / 2.f) / (TILECX / 2.f)
//	};
//
//	// 12 -> 3 -> 6 -> 9
//	D3DXVECTOR3	vPoint[4] =
//	{
//		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
//		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
//		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
//		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
//
//	};
//
//	// y = ax + b;
//	// -b = ax - y
//	// b = y - ax
//
//	float	fB[4] =
//	{
//		vPoint[0].y - fGradient[0] * vPoint[0].x,
//		vPoint[1].y - fGradient[1] * vPoint[1].x,
//		vPoint[2].y - fGradient[2] * vPoint[2].x,
//		vPoint[3].y - fGradient[3] * vPoint[3].x
//	};
//
//	// 0 == ax + b - y // 선 상에 있음
//	// 0 > ax + b - y // 선분 위쪽
//	// 0 < ax + b - y // 선분 아래쪽
//
//	bool	bCheck[4]{ false };
//
//	// 12 -> 3
//	if (0 < fGradient[0] * vPos.x + fB[0] - vPos.y)
//		bCheck[0] = true;
//
//	// 3 -> 6
//	if (0 >= fGradient[1] * vPos.x + fB[1] - vPos.y)
//		bCheck[1] = true;
//
//	// 6 -> 9
//	if (0 >= fGradient[2] * vPos.x + fB[2] - vPos.y)
//		bCheck[2] = true;
//
//	// 9 -> 12
//	if (0 < fGradient[3] * vPos.x + fB[3] - vPos.y)
//		bCheck[3] = true;
//
//
//	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
//}

//bool CTerrain::Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex)
//{
//	// 12 -> 3 -> 6 -> 9
//	D3DXVECTOR3	vPoint[4] =
//	{
//		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
//		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
//		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
//		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
//
//	};
//
//	D3DXVECTOR3	vDir[4] =
//	{
//		vPoint[1] - vPoint[0],
//		vPoint[2] - vPoint[1],
//		vPoint[3] - vPoint[2],
//		vPoint[0] - vPoint[3]
//	};
//
//	D3DXVECTOR3		vNormal[4] =
//	{
//		{ -vDir[0].y , vDir[0].x, 0.f },
//		{ -vDir[1].y , vDir[1].x, 0.f },
//		{ -vDir[2].y , vDir[2].x, 0.f },
//		{ -vDir[3].y , vDir[3].x, 0.f },
//	};
//
//	D3DXVECTOR3		vMouseDir[4] =
//	{
//		vPos - vPoint[0],
//		vPos - vPoint[1],
//		vPos - vPoint[2],
//		vPos - vPoint[3]
//	};
//
//	for (int i = 0; i < 4; ++i)
//	{
//		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
//		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
//	}
//
//	for (int i = 0; i < 4; ++i)
//	{
//		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
//			return false;
//	}
//
//	return true;
//}
