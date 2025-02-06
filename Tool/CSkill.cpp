#include "pch.h"
#include "CSkill.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "CTextureMgr.h"

CSkill::CSkill() : m_byDrawID(0), m_pMainView(nullptr)
{
    ZeroMemory(&m_tinfo, sizeof(INFO));
    D3DXMatrixIdentity(&m_tinfo.matWorld);
}

CSkill::~CSkill()
{
    Release();
}

HRESULT CSkill::Initialize()
{
    GET_TOOLVIEW
    m_pMainView = pView;

    m_tinfo.vPos = { 400.f, 300.f, 0.f };

    Init_Unit_Texture();
    return E_NOTIMPL;
}

void CSkill::Update()
{
}

void CSkill::Render()
{
    if (!m_bIsRender) return;
    if (m_pStateKey == L"") return;

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

    const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Skill", m_pStateKey.GetString(), m_byDrawID);

    float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
    float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;
    D3DXVECTOR3	vTemp{ fCenterX, fCenterY, 0.f };

    CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //출력할 텍스처 컴객체
        nullptr,		// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0기준으로 출력
        &vTemp,		// 출력할 이미지의 중심 좌표 vec3 주소, null인 경우 0, 0 이미지 중심
        nullptr,		// 위치 좌표에 대한 vec3 주소, null인 경우 스크린 상 0, 0 좌표 출력	
        D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 섞지 않고 원본 색상 유지
}

void CSkill::Release()
{
}

HRESULT CSkill::Init_Unit_Texture()
{
    INSERT_TEXTURE(L"../MapleStory/02.Skill/01.Elec_Axe/effect_%d.png",
        TEX_MULTI, L"Skill", L"Elec_Axe", 15);

   INSERT_TEXTURE(L"../MapleStory/02.Skill/02.Annihilation/effect_%d.png",
        TEX_MULTI, L"Skill", L"Annihilation", 13);

   INSERT_TEXTURE(L"../MapleStory/02.Skill/03.Ascension/effect_%d.png",
       TEX_MULTI, L"Skill", L"Ascension", 10);

   INSERT_TEXTURE(L"../MapleStory/02.Skill/04.Lightning/effect_%d.png",
       TEX_MULTI, L"Skill", L"Lightning", 10);

   INSERT_TEXTURE(L"../MapleStory/02.Skill/05.Typhoon/effect_%d.png",
       TEX_MULTI, L"Skill", L"Typhoon", 21);

   INSERT_TEXTURE(L"../MapleStory/02.Skill/06.Basic_Attack/effect_%d.png",
       TEX_MULTI, L"Skill", L"Basic_Attack", 5);

    return E_NOTIMPL;
}
