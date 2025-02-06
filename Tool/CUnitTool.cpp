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
    , Edit_Name(_T(""))
    , UnitFrameTime(0)
    , SkillFrameTime(0)
    , m_iAnimationFrame_Index(0)

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

    DDX_Text(pDX, IDC_EDIT8, Edit_Name);
    DDX_Control(pDX, IDC_LIST3, m_ListBox_Animation);
    DDX_Control(pDX, IDC_LIST4, ListBox_AnimationFrame);
    DDX_Text(pDX, IDC_EDIT1, UnitFrameTime);
    DDX_Text(pDX, IDC_EDIT2, SkillFrameTime);

    DDX_Control(pDX, IDC_SLIDER4, m_Slider_PosX);
    DDX_Control(pDX, IDC_SLIDER5, m_Slider_PosY);
    DDX_Control(pDX, IDC_SLIDER6, m_Slider_PosZ);
    DDX_Control(pDX, IDC_EDIT5, m_PosX);
    DDX_Control(pDX, IDC_EDIT6, m_PosY);
    DDX_Control(pDX, IDC_EDIT7, m_PosZ);
    DDX_Control(pDX, IDC_EDIT3, AnimeFrameTime);
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
    ON_BN_CLICKED(IDC_CHECK1, &CUnitTool::Button_HideUnit)
    ON_BN_CLICKED(IDC_CHECK2, &CUnitTool::Button_HideSkill)
    ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnAdd)
    ON_WM_DESTROY()
    ON_LBN_SELCHANGE(IDC_LIST4, &CUnitTool::OnLbnSelchange_AnimeFrame)
    ON_LBN_SELCHANGE(IDC_LIST3, &CUnitTool::OnLbnSelchangeList_AnimeName)
    ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedButton_AnimePlay)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER4, &CUnitTool::OnNMReleasedcaptureSlider_X)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER5, &CUnitTool::OnNMReleasedcaptureSlider_Y)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER6, &CUnitTool::OnNMReleasedcaptureSlider_Z)
    ON_BN_CLICKED(IDC_BUTTON11, &CUnitTool::OnBnClickedButton_0_indexSort)
    ON_BN_CLICKED(IDC_BUTTON10, &CUnitTool::OnAddUnit)
    ON_BN_CLICKED(IDC_BUTTON12, &CUnitTool::OnAddSkill)
    ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::AnimePause)
    ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnSave)
    ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnLoad)
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

    if (m_ListBox_Animation.m_hWnd == NULL)
    {
        m_ListBox_Animation.SubclassDlgItem(IDC_LIST3, this);
    }

    if (ListBox_AnimationFrame.m_hWnd == NULL)
    {
        ListBox_AnimationFrame.SubclassDlgItem(IDC_LIST4, this);
    }

    if (m_Slider_PosX.m_hWnd == NULL)
    {
        m_Slider_PosX.SubclassDlgItem(IDC_SLIDER4, this);
    }

    if (m_Slider_PosY.m_hWnd == NULL)
    {
        m_Slider_PosY.SubclassDlgItem(IDC_SLIDER5, this);
    }

    if (m_Slider_PosZ.m_hWnd == NULL)
    {
        m_Slider_PosZ.SubclassDlgItem(IDC_SLIDER6, this);
    }

    if (m_PosX.m_hWnd == NULL)
    {
        m_PosX.SubclassDlgItem(IDC_EDIT5, this);
    }

    if (m_PosY.m_hWnd == NULL)
    {
        m_PosY.SubclassDlgItem(IDC_EDIT6, this);
    }

    if (m_PosZ.m_hWnd == NULL)
    {
        m_PosZ.SubclassDlgItem(IDC_EDIT7, this);
    }

  
    // 슬라이더 범위 설정
    m_Slider_PosX.SetRange(0, 800);
    m_Slider_PosX.SetPos(400);
    m_Slider_PosX.SetTicFreq(50);

    m_Slider_PosY.SetRange(0, 600);
    m_Slider_PosY.SetPos(300);
    m_Slider_PosY.SetTicFreq(50);

    m_Slider_PosZ.SetRange(0, 100);
    m_Slider_PosZ.SetPos(0);
    m_Slider_PosZ.SetTicFreq(50);

    // 에딧 컨트롤을 0으로 초기화
    m_PosX.SetWindowText(_T("400"));
    m_PosY.SetWindowText(_T("300"));
    m_PosZ.SetWindowText(_T("0"));


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

    dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->SetPos(D3DXVECTOR3(400.f,300.f,0.f));


    // 리스트 클리어 해야함
    ListBox_Frame.ResetContent();

    for (size_t i = 0; i < iter->second.size(); i++)
	{
		CString temp;
		temp.Format(L"%d", i);
        ListBox_Frame.AddString(temp);
	}

    m_Scrollview->Invalidate(TRUE);
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
        m_AnimationTimer = SetTimer(1, UnitFrameTime, NULL); // 100ms 간격으로 타이머 실행
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

        m_Scrollview->Invalidate(FALSE);
    }

    if (nIDEvent == 2 && ListBoxFrame_Skill.GetCount() != 0)
    {
        // 다음 프레임으로 이동
        m_CurrentSkillIndex = (m_CurrentSkillIndex + 1) % ListBoxFrame_Skill.GetCount();
        ListBoxFrame_Skill.SetCurSel(m_CurrentSkillIndex);
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(m_ImgFindName_Skill.GetString(), m_CurrentSkillIndex);

        m_Scrollview->Invalidate(FALSE);
    }

    if (nIDEvent == 3 && ImgData[name1].size() != 0)
    {
        frame1 = (frame1 + 1) % ImgData[name1].size();
        ListBox_AnimationFrame.SetCurSel(frame1);

        if (0 > ListBox_SkillName.FindString(-1, name1))
        {
            dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(name1.GetString(), frame1);
        }
        else
        {
            dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(name1.GetString(), frame1);
        }
        

        m_Scrollview->Invalidate(FALSE);
    }

    if (nIDEvent == 4 && ImgData[name2].size() != 0)
    {
        frame2 = (frame2 + 1) % ImgData[name2].size();
        ListBox_AnimationFrame.SetCurSel(frame2);

        if (0 < ListBox_SkillName.FindString(-1, name2))
        {
            dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(name2.GetString(), frame2);
        }
        else
        {
            dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(name2.GetString(), frame2);
        }

        m_Scrollview->Invalidate(FALSE);
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

    m_Scrollview->Invalidate(FALSE);

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
        m_SkillTimer = SetTimer(2, SkillFrameTime, NULL); // 100ms 간격으로 타이머 실행
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


void CUnitTool::Button_HideUnit()
{
    UpdateData(TRUE);

    if (m_bIsUnitShow)
    {
        CObjMgr::Get_Instance()->Render_ID(OBJ_Unit, true);
        m_bIsUnitShow = false;
    }
    else
    {
        CObjMgr::Get_Instance()->Render_ID(OBJ_Unit, false);
        m_bIsUnitShow = true;
    }
        
    m_Scrollview->Invalidate(FALSE);
    UpdateData(FALSE);
}


void CUnitTool::Button_HideSkill()
{
    UpdateData(TRUE);

    if (m_bIsSkillShow)
    {
        CObjMgr::Get_Instance()->Render_ID(OBJ_Effect, true);
        m_bIsSkillShow = false;
    }
    else
    {
        CObjMgr::Get_Instance()->Render_ID(OBJ_Effect, false);
        m_bIsSkillShow = true;
    }
        
    m_Scrollview->Invalidate(FALSE);
    UpdateData(FALSE);
}


void CUnitTool::OnAdd()
{
    UpdateData(TRUE);
   
    


    UpdateData(FALSE);

}


void CUnitTool::OnDestroy()
{
   CDialog::OnDestroy();

    for_each(ImgData.begin(), ImgData.end(), [](pair<const CString, std::vector<IMG_INFO*>>& pair)
        {
            for (auto& img : pair.second)
                Safe_Delete(img);
            pair.second.clear(); 
        });

    ImgData.clear(); 
}


void CUnitTool::OnLbnSelchangeList_AnimeName()
{
    UpdateData(TRUE);

    int maxSelections = 2; // 최대 선택 개수
    int count = m_ListBox_Animation.GetSelCount();
    CArray<int, int> selectedIndexes;

    if (count > maxSelections)
    {
        // 초과한 경우 마지막 선택을 취소
        selectedIndexes.SetSize(count);
        m_ListBox_Animation.GetSelItems(count, selectedIndexes.GetData());

        // 가장 마지막에 선택한 항목을 선택 취소
        m_ListBox_Animation.SetSel(selectedIndexes[count - 1], FALSE);
    }
    if (count == 2) // 두 개만 선택되었는지 확인
    {
        selectedIndexes.SetSize(count);
        m_ListBox_Animation.GetSelItems(count, selectedIndexes.GetData());

        int firstIndex = selectedIndexes[0]; // 첫 번째 선택된 인덱스
        int secondIndex = selectedIndexes[1]; // 두 번째 선택된 인덱스

        m_ListBox_Animation.GetText(firstIndex, name1);
        m_ListBox_Animation.GetText(secondIndex, name2);

        auto	iter = ImgData.find(Edit_Name.GetString());
        if (iter == ImgData.end()) return;
    }

    int	iIndex = m_ListBox_Animation.GetCurSel();
    m_ListBox_Animation.GetText(iIndex, Edit_Name);

    auto	iter = ImgData.find(Edit_Name.GetString());
    if (iter == ImgData.end()) return;

    ListBox_AnimationFrame.ResetContent();

    for (size_t i = 0; i < iter->second.size(); i++)
    {
        CString temp;
        temp.Format(L"%d", i);
        ListBox_AnimationFrame.AddString(temp);
    }

    CString temp;
    temp.Format(_T("%d"), ImgData[Edit_Name][0]->iFrameTime);
    AnimeFrameTime.SetWindowText(temp);

    if (count == 1)
    {
        name1 = Edit_Name;
        name2 = L"";
    }

    UpdateData(FALSE);
}

void CUnitTool::OnLbnSelchange_AnimeFrame()
{
    UpdateData(TRUE);

    const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();
    m_iAnimationFrame_Index = ListBox_AnimationFrame.GetCurSel();

    if (LB_ERR != ListBox_ImageKey.FindString(-1, Edit_Name))
    {
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }
    if (LB_ERR != ListBox_SkillName.FindString(-1, Edit_Name))
    {       
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }
    m_Scrollview->Invalidate(FALSE);

    int nPosX = ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos.x;
    int nPosY = ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos.y;
    int nPosZ = ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos.z;

    m_Slider_PosX.SetPos(nPosX);
    m_Slider_PosY.SetPos(nPosY);
    m_Slider_PosZ.SetPos(nPosZ);

    CString str;
    str.Format(_T("%d"), nPosX);
    m_PosX.SetWindowText(str);

    str.Format(_T("%d"), nPosY);
    m_PosY.SetWindowText(str);

    str.Format(_T("%d"), nPosZ);
    m_PosZ.SetWindowText(str);


    UpdateData(FALSE);
}

void CUnitTool::OnBnClickedButton_AnimePlay()
{
    UpdateData(TRUE);
    if (name1 == L"") return;

    if (0 < ListBox_ImageKey.FindString(-1, name1))
    {
        if (ImgData[name1].size() != 0)
        {

            if (m_AnimationTimer != 0)
            {
                KillTimer(m_AnimationTimer);
            }
            if (m_Timer1 != 0)
            {
                KillTimer(m_Timer1);
            }

            frame1 = 0;  // 애니메이션 시작 시 첫 프레임부터
            m_Timer1 = SetTimer(3, ImgData[name1][0]->iFrameTime, NULL); // 100ms 간격으로 타이머 실행
        }
        if (name2 == L"") return;
        if (0 < ListBox_ImageKey.FindString(-1, name2)) return;
        if (0 < ListBox_SkillName.FindString(-1, name2))
        {
            if (m_SkillTimer != 0)
            {
                KillTimer(m_SkillTimer);
            }
            if (m_Timer2 != 0)
            {
                KillTimer(m_Timer2);
            }

            frame2 = 0;  // 애니메이션 시작 시 첫 프레임부터
            m_Timer2 = SetTimer(4, ImgData[name2][0]->iFrameTime, NULL); // 100ms 간격으로 타이머 실행
        }

        return;
    }
    else if(0 < ListBox_SkillName.FindString(-1, name1))
    {
        if (ImgData[name1].size() != 0)
        {

            if (m_SkillTimer != 0)
            {
                KillTimer(m_SkillTimer);
            }
            if (m_Timer2 != 0)
            {
                KillTimer(m_Timer2);
            }

            frame2 = 0;  // 애니메이션 시작 시 첫 프레임부터
            m_Timer2 = SetTimer(4, ImgData[name1][0]->iFrameTime, NULL); // 100ms 간격으로 타이머 실행
        }

        if (name2 == L"") return;
        if (0 < ListBox_SkillName.FindString(-1, name2)) return;
        if (0 < ListBox_ImageKey.FindString(-1, name2))
        {
            if (m_AnimationTimer != 0)
            {
                KillTimer(m_AnimationTimer);
            }
            if (m_Timer1 != 0)
            {
                KillTimer(m_Timer1);
            }

            frame1 = 0;  // 애니메이션 시작 시 첫 프레임부터
            m_Timer1 = SetTimer(3, ImgData[name2][0]->iFrameTime, NULL); // 100ms 간격으로 타이머 실행
        }

        return;

    }

    UpdateData(FALSE);
}

void CUnitTool::AnimePause()
{
    if (m_Timer1 != 0)
    {
        KillTimer(m_Timer1);
    }
    if (m_Timer2 != 0)
    {
        KillTimer(m_Timer2);
    }
}

void CUnitTool::OnNMReleasedcaptureSlider_X(NMHDR* pNMHDR, LRESULT* pResult)
{
    UpdateData(TRUE);

    if (Edit_Name == L"" || ImgData.empty())
    {
        m_Slider_PosX.SetPos(400);
        return;
    }


    int  nPos = m_Slider_PosX.GetPos();
    ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos.x = nPos;


    if (LB_ERR != ListBox_ImageKey.FindString(-1, Edit_Name))
    {
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }
    if (LB_ERR != ListBox_SkillName.FindString(-1, Edit_Name))
    {
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }


    CString str;
    str.Format(_T("%d"), nPos);
    m_PosX.SetWindowText(str);

    m_Scrollview->Invalidate(FALSE);

    *pResult = 0;

    UpdateData(FALSE);
}

void CUnitTool::OnNMReleasedcaptureSlider_Y(NMHDR* pNMHDR, LRESULT* pResult)
{
    UpdateData(TRUE);

    if (Edit_Name == L"" || ImgData.empty())
    {
        m_Slider_PosY.SetPos(300);
        return;
    }

    int nPos = m_Slider_PosY.GetPos();
    ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos.y = nPos;

    if (LB_ERR != ListBox_ImageKey.FindString(-1, Edit_Name))
    {
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }
    if (LB_ERR != ListBox_SkillName.FindString(-1, Edit_Name))
    {
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }

    CString str;
    str.Format(_T("%d"), nPos);
    m_PosY.SetWindowText(str);

    m_Scrollview->Invalidate(FALSE);

    *pResult = 0;

    UpdateData(FALSE);
}

void CUnitTool::OnNMReleasedcaptureSlider_Z(NMHDR* pNMHDR, LRESULT* pResult)
{
    UpdateData(TRUE);

    if (Edit_Name == L"" || ImgData.empty())
    {
        m_Slider_PosZ.SetPos(0);
        return;
    }

    if (LB_ERR != ListBox_ImageKey.FindString(-1, Edit_Name))
    {
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CUnit*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Unit)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }
    if (LB_ERR != ListBox_SkillName.FindString(-1, Edit_Name))
    {
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->Set_Path(Edit_Name.GetString(), m_iAnimationFrame_Index);
        dynamic_cast<CSkill*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Effect)->front())->SetPos(ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos);
    }

    int nPos = m_Slider_PosZ.GetPos();
    ImgData[Edit_Name][m_iAnimationFrame_Index]->vPos.z = nPos;

    CString str;
    str.Format(_T("%d"), nPos);
    m_PosZ.SetWindowText(str);

    m_Scrollview->Invalidate(FALSE);

    *pResult = 0;

    UpdateData(FALSE);
}

void CUnitTool::OnBnClickedButton_0_indexSort()
{
    if (Edit_Name == L"" || ImgData.empty())
    {
        return;
    }

    D3DXVECTOR3 temp = ImgData[Edit_Name][0]->vPos;
    for (auto& vec : ImgData[Edit_Name])
    {
        vec->vPos = temp;
    }
    m_Scrollview->Invalidate(TRUE);
}

void CUnitTool::OnAddUnit()
{
    UpdateData(TRUE);

    int num = ListBox_ImageKey.GetCurSel();

    if (num < 0) return;
    ListBox_ImageKey.GetText(num, Edit_Name);

    auto	iter = m_mutimapTex_Unit.find(Edit_Name.GetString());
    if (iter == m_mutimapTex_Unit.end()) return;

    if (-1 != m_ListBox_Animation.FindString(-1, Edit_Name)) return;

    for (size_t i = 0; i < iter->second.size(); i++)
    {
        IMG_INFO* pImg = new IMG_INFO;

        pImg->vPos = { 400.f,300.f,0.f };
        pImg->vSize = { 0.f,0.f };
        pImg->iFrameTime = UnitFrameTime;

        ImgData[Edit_Name].push_back(pImg);
    }

    m_ListBox_Animation.AddString(Edit_Name);

    UpdateData(FALSE);
}

void CUnitTool::OnAddSkill()
{
    UpdateData(TRUE);

    int num = ListBox_SkillName.GetCurSel();

    if (num < 0) return;
    ListBox_SkillName.GetText(num, Edit_Name);

    auto	iter = m_mutimapTex_Skill.find(Edit_Name.GetString());
    if (iter == m_mutimapTex_Skill.end()) return;

    if (-1 != m_ListBox_Animation.FindString(-1, Edit_Name)) return;

    for (size_t i = 0; i < iter->second.size(); i++)
    {
        IMG_INFO* pImg = new IMG_INFO;

        pImg->vPos = { 400.f, 300.f, 0.f };
        pImg->vSize = { 0.f,0.f };
        pImg->iFrameTime = SkillFrameTime;

        ImgData[Edit_Name].push_back(pImg);
    }

    m_ListBox_Animation.AddString(Edit_Name);

    UpdateData(FALSE);

}


void CUnitTool::OnSave()
{
    CFileDialog		Dlg(FALSE,		// TRUE(불러오기), FALSE(다른 이름으로 저장) 모드 지정
        L"dat",		// default 확장자명
        L"*.dat",	// 대화 상자에 표시될 최초 파일명
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// 읽기 전용 체크 박스 숨김 | 중복된 이름으로 파일 저장 시 경고 메세지 띄움
        L"Data Files(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식
        this);	// 부모 윈도우 주소

    // DoModal : 대화 상자를 실행

    TCHAR	szPath[MAX_PATH] = L"";

    // 현재 프로젝트의 경로를 얻어오는 함수(절대 경로)
    GetCurrentDirectory(MAX_PATH, szPath);

    // PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라주는 함수
    // 경로 상에 파일 이름이 없을 경우엔 마지막 폴더명을 잘라낸다.

    PathRemoveFileSpec(szPath);

    lstrcat(szPath, L"\\Data");

    Dlg.m_ofn.lpstrInitialDir = szPath;

    if (IDOK == Dlg.DoModal())
    {
        // GetPathName : 선택된 경로를 반환
        // GetString : 원시 문자열의 형태로 반환

        CString	str = Dlg.GetPathName().GetString();
        const TCHAR* pGetPath = str.GetString();

        HANDLE hFile = CreateFile(pGetPath,
            GENERIC_WRITE,
            0, 0,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte(0), dwStrByte(0);
        int dwVecSize(0);

        for (auto& MyPair : ImgData)
        {
            // key 값 저장

            dwStrByte = sizeof(TCHAR) * (MyPair.first.GetLength() + 1);

            WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
            WriteFile(hFile, MyPair.first.GetString(), dwStrByte, &dwByte, nullptr);

            // value 값 저장
            dwVecSize = MyPair.second.size(); //벡터 사이즈
            WriteFile(hFile, &dwVecSize, sizeof(int), &dwByte, nullptr);

            for (int i = 0; i < dwVecSize; i++)
            {
                WriteFile(hFile, &(MyPair.second[i]->iFrameTime), sizeof(int), &dwByte, nullptr);
                WriteFile(hFile, &(MyPair.second[i]->vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
                WriteFile(hFile, &(MyPair.second[i]->vSize), sizeof(D3DXVECTOR2), &dwByte, nullptr);
            }
        }
        CloseHandle(hFile);
    }
}


void CUnitTool::OnLoad()
{
    UpdateData(TRUE);

    CFileDialog		Dlg(TRUE,		// TRUE(불러오기), FALSE(다른 이름으로 저장) 모드 지정
        L"dat",		// default 확장자명
        L"*.dat",	// 대화 상자에 표시될 최초 파일명
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// 읽기 전용 체크 박스 숨김 | 중복된 이름으로 파일 저장 시 경고 메세지 띄움
        L"Data Files(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식
        this);	// 부모 윈도우 주소

    // DoModal : 대화 상자를 실행

    TCHAR	szPath[MAX_PATH] = L"";

    // 현재 프로젝트의 경로를 얻어오는 함수(절대 경로)
    GetCurrentDirectory(MAX_PATH, szPath);

    // PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라주는 함수
    // 경로 상에 파일 이름이 없을 경우엔 마지막 폴더명을 잘라낸다.

    PathRemoveFileSpec(szPath);

    lstrcat(szPath, L"\\Data");

    Dlg.m_ofn.lpstrInitialDir = szPath;

    if (IDOK == Dlg.DoModal())
    {
        for (auto& MyPair : ImgData)
        {
            for(auto& value : MyPair.second)
                delete value;

            MyPair.second.clear();
        }
        ImgData.clear();

        // ResetContent : 리스트 박스 목록 초기화 함수
        m_ListBox_Animation.ResetContent();

        CString	str = Dlg.GetPathName().GetString();
        const TCHAR* pGetPath = str.GetString();

        HANDLE hFile = CreateFile(pGetPath,
            GENERIC_READ,
            0, 0,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte(0), dwStrByte(0);
        int dwVecSize(0);

        DWORD fileSize = GetFileSize(hFile, nullptr);

        while (true)
        {
            // key 값 로드

            // 문자열 크기를 저장
            BOOL a = ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

            // 문자열 크기만큼 동적 할당
            TCHAR* pName = new TCHAR[dwStrByte];
            BOOL b = ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

            // value 값 로드

            vector<IMG_INFO*> value;
            BOOL f = ReadFile(hFile, &dwVecSize, sizeof(int), &dwByte, nullptr);


            for (int i = 0; i < dwVecSize; i++)
            {
                IMG_INFO* img = new IMG_INFO();
                BOOL c = ReadFile(hFile, &(img->iFrameTime), sizeof(int), &dwByte, nullptr);
                BOOL d = ReadFile(hFile, &(img->vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
                BOOL e = ReadFile(hFile, &(img->vSize), sizeof(D3DXVECTOR2), &dwByte, nullptr);
                value.push_back(img);
            }


            if (0 == dwByte)
            {
                delete[] pName;
                break;
            }

            ImgData.insert({ pName, value });
            m_ListBox_Animation.AddString(CString(pName));


            
        }

        CloseHandle(hFile);
    }

    UpdateData(FALSE);
}
