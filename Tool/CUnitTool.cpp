// CUnitTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CUnitTool.h"
#include "CTextureMgr.h"
#include "CMultiTexture.h"


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
    //UpdateData(TRUE);

    //int iIndex = m_ListBox2.GetCurSel();
    //if (iIndex == LB_ERR)
    //{
    //    // 선택된 유닛이 없으면 초기화
    //    m_ImagePaths.clear();
    //    m_ListBox.ResetContent();
    //    KillTimer(m_AnimationTimer);
    //    CClientDC dc(&m_Picture);
    //    dc.FillSolidRect(CRect(0, 0, 100, 100), RGB(255, 255, 255)); // 빈 화면
    //    return;
    //}

    //CString strSelectedUnit;
    //m_ListBox2.GetText(iIndex, strSelectedUnit);

    //int iTypeIndex = m_ListBox3.GetCurSel();
    //if (iTypeIndex == LB_ERR)
    //    return;

    //CString strSelectedType;
    //m_ListBox3.GetText(iTypeIndex, strSelectedType);


    //m_ImagePaths.clear();
    //m_ListBox.ResetContent();
    //m_CurrentFrameIndex = 0;

    //auto itType = m_mapCategory.find(strSelectedType);
    //if (itType != m_mapCategory.end())
    //{
    //    auto itUnit = itType->second.find(strSelectedUnit);
    //    if (itUnit != itType->second.end())
    //    {

    //        for (auto& imagePath : itUnit->second)
    //        {
    //            m_ImagePaths.push_back(imagePath);

    //            CString fileName = PathFindFileName(imagePath);
    //            m_ListBox.AddString(fileName);
    //        }
    //    }
    //}


    //if (!m_ImagePaths.empty())
    //{
    //    m_AnimationTimer = SetTimer(1, 100, NULL); // 1번 타이머를 100ms 간격!!
    //}

    //UpdateData(FALSE);
}


void CUnitTool::OnTimer(UINT_PTR nIDEvent)
{
    //if (nIDEvent == 1 && !m_ImagePaths.empty())
    //{

    //    CString currentImagePath = m_ImagePaths[m_CurrentFrameIndex];


    //    CImage image;
    //    if (FAILED(image.Load(currentImagePath)))
    //    {
    //        AfxMessageBox(_T("이미지 로드 실패: ") + currentImagePath);
    //        KillTimer(m_AnimationTimer);
    //        return;
    //    }


    //    CClientDC dc(&m_Picture);
    //    CRect rect;
    //    m_Picture.GetClientRect(&rect);

    //    dc.FillSolidRect(rect, RGB(255, 255, 255));
    //    image.Draw(dc, rect);


    //    CString fileName = PathFindFileName(currentImagePath);
    //    for (int i = 0; i < m_ListBox.GetCount(); ++i)
    //    {
    //        CString listItem;
    //        m_ListBox.GetText(i, listItem);
    //        if (listItem == fileName)
    //        {
    //            m_ListBox.SetCurSel(i);
    //            break;
    //        }
    //    }

    //    m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % m_ImagePaths.size();
    //}

    //CDialog::OnTimer(nIDEvent);
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

   

    Insert_Unit_Texture(); // 멀티 택스쳐 추가
    Link_ImageKey(); // 이미지 키 연결
   

















    return 0;
}

HRESULT CUnitTool::Insert_Unit_Texture()
{
    if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
        L"../MapleStory/01.Player_Resource/Motion/Fly/fly_%d.png",
        TEX_MULTI, L"Player", L"Fly", 2)))
    {
        AfxMessageBox(L"Terrain Texture Insert Failed");
        return E_FAIL;
    }

    if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
        L"../MapleStory/01.Player_Resource/Motion/Heal/heal_%d.png",
        TEX_MULTI, L"Player", L"Heal", 2)))
    {
        AfxMessageBox(L"Terrain Texture Insert Failed");
        return E_FAIL;
    }

    if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
        L"../MapleStory/01.Player_Resource/Motion/Jump/jump_0.png",
        TEX_MULTI, L"Player", L"Jump", 1)))
    {
        AfxMessageBox(L"Terrain Texture Insert Failed");
        return E_FAIL;
    }
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

    int	iIndex = ListBox_ImageKey.GetCurSel();

    const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();
    auto it = texMap.find(L"BackGround");
    if (it != texMap.end())
    {
        CTexture* background = it->second;
        m_mutimapTex = dynamic_cast<CMultiTexture*>(background)->Get_MultiTex();
        auto iter = m_mutimapTex.find(m_ImgFindName.GetString());


    }


    UpdateData(FALSE);
}
