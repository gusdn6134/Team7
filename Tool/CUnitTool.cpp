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
#include "CSkill.h"


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
    DDX_Control(pDX, IDC_LIST5, ListBoxFrame_Skill);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)

	ON_BN_CLICKED(IDC_BUTTON7, &CUnitTool::OnAnimePlayButton)
    ON_WM_TIMER()
    ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnImgKeySelChange)
    ON_LBN_SELCHANGE(IDC_LIST2, &CUnitTool::OnFrameSelChange)
    ON_BN_CLICKED(IDC_BUTTON6, &CUnitTool::OnPuaseButton)
    ON_LBN_SELCHANGE(IDC_LIST6, &CUnitTool::OnLbnSelchangeList_SkillName)
    ON_LBN_SELCHANGE(IDC_LIST5, &CUnitTool::OnSelchangeList_SkillFrame)
    ON_BN_CLICKED(IDC_BUTTON9, &CUnitTool::OnSkillPlayButton)
    ON_BN_CLICKED(IDC_BUTTON8, &CUnitTool::OnPuaseSkillButton)
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

    if (ListBox_SkillName.m_hWnd == NULL)
    {
        ListBox_SkillName.SubclassDlgItem(IDC_LIST6, this);
    }

    if (ListBoxFrame_Skill.m_hWnd == NULL)
    {
        ListBoxFrame_Skill.SubclassDlgItem(IDC_LIST5, this);
    }

    GET_ScrollView
    m_Scrollview = pScrollView;
   
    Link_ImageKey(); // 이미지 키 연결
    Link_SKillKey();




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
        m_mutimapTex_Unit = dynamic_cast<CMultiTexture*>(Motion)->Get_MultiTex();

        for (auto& player : m_mutimapTex_Unit)
        {
            CString temp;
            temp.Format(L"%s", player.first.c_str());
            ListBox_ImageKey.AddString(temp);
        }
    }
}

void CUnitTool::OnImgKeySelChange()
{
    // 유닛 이름 박스 클릭 시
    UpdateData(TRUE);

    int	iIndex = ListBox_ImageKey.GetCurSel();

    ListBox_ImageKey.GetText(iIndex, m_ImgFindName_Unit);
    auto	iter = m_mutimapTex_Unit.find(m_ImgFindName_Unit.GetString());
    if (iter == m_mutimapTex_Unit.end()) return;

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
    // 유닛 프레임 박스 클릭 시
    UpdateData(TRUE);

    int	iIndex = ListBox_Frame.GetCurSel();

    const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();
   
    dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(m_ImgFindName_Unit.GetString(), iIndex);

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
        m_AnimationTimer = SetTimer(1, 300, NULL); // 100ms 간격으로 타이머 실행
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
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(m_ImgFindName_Unit.GetString(), m_CurrentFrameIndex);

        m_Scrollview->Invalidate(TRUE);
    }

    if (nIDEvent == 2 && ListBoxFrame_Skill.GetCount() != 0)
    {
        // 다음 프레임으로 이동
        m_CurrentSkillIndex = (m_CurrentSkillIndex + 1) % ListBoxFrame_Skill.GetCount();
        ListBoxFrame_Skill.SetCurSel(m_CurrentSkillIndex);
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(m_ImgFindName_Skill.GetString(), m_CurrentSkillIndex);

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

void CUnitTool::Link_SKillKey()
{
    // 스킬 이름 연결
    const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();
    auto it = texMap.find(L"Skill");
    if (it != texMap.end())
    {
        CTexture* Skill = it->second;
        m_mutimapTex_Skill = dynamic_cast<CMultiTexture*>(Skill)->Get_MultiTex();

        for (auto& skill : m_mutimapTex_Skill)
        {
            CString temp;
            temp.Format(L"%s", skill.first.c_str());
            ListBox_SkillName.AddString(temp);
        }
    }
}

void CUnitTool::OnLbnSelchangeList_SkillName()
{
    UpdateData(TRUE);

    int	iIndex = ListBox_SkillName.GetCurSel();

    ListBox_SkillName.GetText(iIndex, m_ImgFindName_Skill);
    auto	iter = m_mutimapTex_Skill.find(m_ImgFindName_Skill.GetString());
    if (iter == m_mutimapTex_Skill.end()) return;

    // 리스트 클리어 해야함
    ListBoxFrame_Skill.ResetContent();

    for (size_t i = 0; i < iter->second.size(); i++)
    {
        CString temp;
        temp.Format(L"%d", i);
        ListBoxFrame_Skill.AddString(temp);
    }

    m_CurrentSkillIndex = 0;

    UpdateData(FALSE);

}


void CUnitTool::OnSelchangeList_SkillFrame()
{
    // 스킬 프레임 박스 클릭 시
    UpdateData(TRUE);

    int	iIndex = ListBoxFrame_Skill.GetCurSel();

    const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();

    dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(m_ImgFindName_Skill.GetString(), iIndex);

    m_Scrollview->Invalidate(TRUE);

    UpdateData(FALSE);
}


void CUnitTool::OnSkillPlayButton()
{
    UpdateData(TRUE);

    if (ListBoxFrame_Skill.GetCount() != 0)
    {
        // 기존 타이머가 있으면 제거 (중복 방지)
        if (m_SkillTimer != 0)
        {
            KillTimer(m_SkillTimer);
        }

        m_CurrentSkillIndex = 0;  // 애니메이션 시작 시 첫 프레임부터
        ListBoxFrame_Skill.SetCurSel(m_CurrentSkillIndex);  // 첫 프레임 선택
        m_SkillTimer = SetTimer(2, 250, NULL); // 100ms 간격으로 타이머 실행
    }

    UpdateData(FALSE);
}


void CUnitTool::OnPuaseSkillButton()
{
    if (m_SkillTimer != 0)
    {
        KillTimer(m_SkillTimer);
    }
}
