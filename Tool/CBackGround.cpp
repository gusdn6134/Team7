#include "pch.h"
#include "CBackGround.h"
#include "CTextureMgr.h"
#include "MainFrm.h"

CBackGround::CBackGround() : m_byDrawID(1), m_pMainView(nullptr)
{
    ZeroMemory(&m_tinfo, sizeof(INFO));
    D3DXMatrixIdentity(&m_tinfo.matWorld);
}

CBackGround::~CBackGround()
{
    Release();
}

HRESULT CBackGround::Initialize()
{
    GET_TOOLVIEW
    m_pMainView = pView;

    if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
        L"../MapleStory/BackGround/BackGround_%d.png",
        TEX_MULTI, L"BackGround", L"BackGround_", 5)))
    {
        AfxMessageBox(L"Terrain Texture Insert Failed");
        return 1;
    }
    return E_NOTIMPL;
}

void CBackGround::Update()
{
}

void CBackGround::Render()
{
    if (!m_bIsRender) return;

    D3DXMATRIX	matScale, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixTranslation(&matTrans,
        m_tinfo.vPos.x - m_pMainView->GetScrollPos(0),
        m_tinfo.vPos.y - m_pMainView->GetScrollPos(1),
        m_tinfo.vPos.z);


    m_tinfo.matWorld = matScale * matTrans;

    RECT	rc{};

    GetClientRect(m_pMainView->m_hWnd, &rc);

    float	fX = WINCX / float(rc.right - rc.left);
    float	fY = WINCY / float(rc.bottom - rc.top);

   Set_Ratio(&m_tinfo.matWorld, fX, fY);

    CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tinfo.matWorld);

    const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"BackGround", L"BackGround_", m_byDrawID);

    float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
    float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;
    D3DXVECTOR3	vTemp{ fCenterX, fCenterY, 0.f };

    CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //출력할 텍스처 컴객체
        nullptr,		// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0기준으로 출력
        nullptr,		// 출력할 이미지의 중심 좌표 vec3 주소, null인 경우 0, 0 이미지 중심
        nullptr,		// 위치 좌표에 대한 vec3 주소, null인 경우 스크린 상 0, 0 좌표 출력	
        D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 섞지 않고 원본 색상 유지
}

void CBackGround::Release()
{

}
