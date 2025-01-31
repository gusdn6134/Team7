// CUnitTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CUnitTool.h"
#include "CTextureMgr.h"
#include "CMultiTexture.h"
#include "CUnit.h"
#include "CObjMgr.h"
#include "MainFrm.h"


// CUnitTool 대화 상자

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CUnitTool, pParent)
{

}

CUnitTool::~CUnitTool()
{
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, ListBox_ImageKey);
    DDX_Control(pDX, IDC_LIST2, ListBox_Frame);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)

	ON_BN_CLICKED(IDC_BUTTON7, &CUnitTool::OnAnimePlayButton)
    ON_WM_TIMER()
    ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnImgKeySelChange)
    ON_LBN_SELCHANGE(IDC_LIST2, &CUnitTool::OnFrameSelChange)
END_MESSAGE_MAP()



void CUnitTool::OnAnimePlayButton()
{
    UpdateData(TRUE);

    if (ListBox_Frame.GetCount() != 0)
    {
        // 기존 타이머가 있으면 제거 (중복 방지)
        if (m_AnimationTimer != 0)
        {
            KillTimer(m_AnimationTimer);
        }

        m_CurrentFrameIndex = 0;  // 애니메이션 시작 시 첫 프레임부터
        ListBox_Frame.SetCurSel(m_CurrentFrameIndex);  // 첫 프레임 선택
        m_AnimationTimer = SetTimer(1, 200, NULL); // 100ms 간격으로 타이머 실행
    }

    UpdateData(FALSE);
}


void CUnitTool::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1 && ListBox_Frame.GetCount() != 0)
    {
        // 다음 프레임으로 이동
        m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % ListBox_Frame.GetCount();
        ListBox_Frame.SetCurSel(m_CurrentFrameIndex);
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(m_ImgFindName.GetString(), m_CurrentFrameIndex);

        m_Scrollview->Invalidate(TRUE);
    }

    CDialog::OnTimer(nIDEvent);
}


BOOL CUnitTool::OnInitDialog()
{
    // DDX_Control()이 실행되기 전에 직접 핸들을 가져옴
    if (ListBox_ImageKey.m_hWnd == NULL)
    {
        ListBox_ImageKey.SubclassDlgItem(IDC_LIST1, this);
    }

    if (ListBox_Frame.m_hWnd == NULL)
    {
        ListBox_Frame.SubclassDlgItem(IDC_LIST2, this);
    }

    GET_ScrollView
    m_Scrollview = pScrollView;
   

    Insert_Unit_Texture(); // 멀티 택스쳐 추가
    Link_ImageKey(); // 이미지 키 연결
   

















    return 0;
}

HRESULT CUnitTool::Insert_Unit_Texture()
{

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Fly/fly_%d.png",
        TEX_MULTI, L"Player", L"Fly", 2);

    INSERT_TEXTURE(L"../MapleStory/01.Player_Resource/Motion/Heal/heal_%d.png",
        TEX_MULTI, L"Player", L"Heal", 2);

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
}

void CUnitTool::Link_ImageKey()
{
    // 이미지 키 연결
    const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();
    auto it = texMap.find(L"Player");
    if (it != texMap.end())
    {
        CTexture* Motion = it->second;
        m_mutimapTex = dynamic_cast<CMultiTexture*>(Motion)->Get_MultiTex();

        for (auto& player : m_mutimapTex)
        {
            CString temp;
            temp.Format(L"%s", player.first.c_str());
            ListBox_ImageKey.AddString(temp);
        }
    }
}



void CUnitTool::OnImgKeySelChange()
{
    UpdateData(TRUE);

    int	iIndex = ListBox_ImageKey.GetCurSel();

    ListBox_ImageKey.GetText(iIndex, m_ImgFindName);
    auto	iter = m_mutimapTex.find(m_ImgFindName.GetString());
    if (iter == m_mutimapTex.end()) return;

    // 리스트 클리어 해야함
    ListBox_Frame.ResetContent();

    for (size_t i = 0; i < iter->second.size(); i++)
	{
		CString temp;
		temp.Format(L"%d", i);
        ListBox_Frame.AddString(temp);
	}


    UpdateData(FALSE);
}


void CUnitTool::OnFrameSelChange()
{
    UpdateData(TRUE);

    int	iIndex = ListBox_Frame.GetCurSel();

    const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();
   
    dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(m_ImgFindName.GetString(), iIndex);

    m_Scrollview->Invalidate(TRUE);

    UpdateData(FALSE);
}
