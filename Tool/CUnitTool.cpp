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
    DDX_Control(pDX, IDC_LIST6, ListBox_SkillName);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)

	ON_BN_CLICKED(IDC_BUTTON7, &CUnitTool::OnAnimePlayButton)
    ON_WM_TIMER()
    ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnImgKeySelChange)
    ON_LBN_SELCHANGE(IDC_LIST2, &CUnitTool::OnFrameSelChange)
    ON_BN_CLICKED(IDC_BUTTON6, &CUnitTool::OnPuaseButton)
    ON_LBN_SELCHANGE(IDC_LIST6, &CUnitTool::OnLbnSelchangeList_SkillName)
END_MESSAGE_MAP()


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
   
    Link_ImageKey(); // 이미지 키 연결
   




    return 0;
}



void CUnitTool::Link_ImageKey()
{
    // 유닛 이미지 키 연결
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

void CUnitTool::OnPuaseButton()
{
    if (m_AnimationTimer != 0)
    {
        KillTimer(m_AnimationTimer);
    }
}

void CUnitTool::OnLbnSelchangeList_SkillName()
{
   
}
