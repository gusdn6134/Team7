#include "pch.h"
#include "CUnit.h"
#include "CTextureMgr.h"
#include "MainFrm.h"

CUnit::CUnit() : m_byDrawID(0), m_pMainView(nullptr)
{
    ZeroMemory(&m_tinfo, sizeof(INFO));
    D3DXMatrixIdentity(&m_tinfo.matWorld);
}

CUnit::~CUnit()
{
    Release();
}

HRESULT CUnit::Initialize()
{
    GET_TOOLVIEW
    m_pMainView = pView;

    Init_Unit_Texture();

    return E_NOTIMPL;
}

void CUnit::Update()
{
   
}

void CUnit::Render()
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

    const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Player", m_pStateKey.GetString(), m_byDrawID);

    float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
    float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;
    D3DXVECTOR3	vTemp{ fCenterX, fCenterY, 0.f };

    D3DXVECTOR3 vPos{ 400.f, 300.f, 0.f };

    CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, //����� �ؽ�ó �İ�ü
        nullptr,		// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0�������� ���
        &vTemp,		// ����� �̹����� �߽� ��ǥ vec3 �ּ�, null�� ��� 0, 0 �̹��� �߽�
        &vPos,		// ��ġ ��ǥ�� ���� vec3 �ּ�, null�� ��� ��ũ�� �� 0, 0 ��ǥ ���	
        D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� �ʰ� ���� ���� ����

}

void CUnit::Release()
{
    m_pStateKey.ReleaseBuffer();
}

HRESULT CUnit::Init_Unit_Texture()
{
    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Fly/fly_%d.png",
        TEX_MULTI, L"Player", L"Fly", 2);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Idle/alert_%d.png",
        TEX_MULTI, L"Player", L"Idle", 5);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Jump/jump_0.png",
        TEX_MULTI, L"Player", L"Jump", 1);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Ladder/ladder_%d.png",
        TEX_MULTI, L"Player", L"Ladder", 2);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Prone/prone_%d.png",
        TEX_MULTI, L"Player", L"Prone", 1);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/ProneStab/proneStab_%d.png",
        TEX_MULTI, L"Player", L"ProneStab", 2);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Rope/rope_%d.png",
        TEX_MULTI, L"Player", L"Rope", 2);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Shoot1/shoot1_%d.png",
        TEX_MULTI, L"Player", L"Shoot1", 3);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Shoot2/shoot2_%d.png",
        TEX_MULTI, L"Player", L"Shoot2", 5);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/ShootF/shootF_%d.png",
        TEX_MULTI, L"Player", L"ShootF", 3);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Sit/sit_%d.png",
        TEX_MULTI, L"Player", L"Sit", 1);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/StabO1/stabO1_%d.png",
        TEX_MULTI, L"Player", L"StabO1", 2);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/StabO2/stabO2_%d.png",
        TEX_MULTI, L"Player", L"StabO2", 2);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/StabOF/stabOF_%d.png",
        TEX_MULTI, L"Player", L"StabOF", 3);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/StabT1/stabT1_%d.png",
        TEX_MULTI, L"Player", L"StabT1", 3);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/StabT2/stabT2_%d.png",
        TEX_MULTI, L"Player", L"StabT2", 3);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/StabTF/stabTF_%d.png",
        TEX_MULTI, L"Player", L"StabTF", 4);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Stand1/stand1_%d.png",
        TEX_MULTI, L"Player", L"Stand1", 5);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/SwingO1/swingO1_%d.png",
        TEX_MULTI, L"Player", L"SwingO1", 3);


    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Walk/walk1_%d.png",
        TEX_MULTI, L"Player", L"Walk", 4);

}
