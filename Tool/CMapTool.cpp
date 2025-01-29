// CMapTool.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CMapTool.h"
#include "MainFrm.h"
#include "CDevice.h"
#include "ToolView.h"
#include "Include.h"
#include "CTextureMgr.h"
#include "CMultiTexture.h"
#include "CObjMgr.h"

// CMapTool 대화 상자

IMPLEMENT_DYNAMIC(CMapTool, CDialogEx)

CMapTool::CMapTool(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMapTool, pParent)
	, m_MapSizeX(0)
	, m_MapSizeY(0)
	, m_strBackGroundName(_T("")), m_pBackGround(nullptr)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT2, m_MapSizeX);
	DDX_Text(pDX, IDC_EDIT3, m_MapSizeY);
	DDX_Control(pDX, IDC_LIST1, m_listBackGround);
	DDX_LBString(pDX, IDC_LIST1, m_strBackGroundName);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnMapSizeChange)

	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnBG_ListBox)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기

void CMapTool::OnMapSizeChange()
{
	UpdateData(TRUE);	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CScrollView* pScrollView = dynamic_cast<CScrollView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));

	if (pScrollView != nullptr)
	{
		pScrollView->SetScrollSizes(MM_TEXT, CSize(m_MapSizeX, m_MapSizeY));
	}

	/*if (FAILED(CDevice::Get_Instance()->Init_Device()))
	{
		AfxMessageBox(L"Init_Device Create Failed");
		return;
	}*/

	UpdateData(FALSE);		
}


BOOL CMapTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	/*--------------------------
	 백그라운드 이미지 추가
	--------------------------*/
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../MapleStory/BackGround/BackGround_%d.png",
		TEX_MULTI, L"BackGround", L"BackGround_", 5)))
	{
		AfxMessageBox(L"Terrain Texture Insert Failed");
		return E_FAIL;
	}

	const auto& texMap = CTextureMgr::Get_Instance()->Get_mapTex();
	auto it = texMap.find(L"BackGround");
	if (it != texMap.end()) 
	{
		CTexture* background = it->second;
		m_mutimapTex = dynamic_cast<CMultiTexture*>(background)->Get_MultiTex();
		auto iter = m_mutimapTex.find(L"BackGround_");
		
		for (size_t i = 0; i < iter->second.size(); i++)
		{
			CString temp;
			temp.Format(L"%s%d", L"BackGround_", i);
			m_listBackGround.AddString(temp);
		}
	}
	else 
	{
		return E_FAIL;
	}
	/*--------------------------
	--------------------------*/
	return TRUE;
}

void CMapTool::OnBG_ListBox()
{
	UpdateData(TRUE);

	int	iIndex = m_listBackGround.GetCurSel();
	{
		CString	strFindName;
		auto	iter = m_mutimapTex.find(L"BackGround_");
		if (iter == m_mutimapTex.end())
			return;

		m_MapSizeX = iter->second[iIndex]->tImgInfo.Width;
		m_MapSizeY = iter->second[iIndex]->tImgInfo.Height;
	}
	 
	GET_ScrollView // 스크롤 뷰 가져오는 매크로
	if (pScrollView != nullptr)
	{
		// 이미지 크기에 따른 스크롤 값 조정
		pScrollView->SetScrollSizes(MM_TEXT, CSize(m_MapSizeX, m_MapSizeY));
	}

	dynamic_cast<CBackGround*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BackGround)->front())->Set_Id(iIndex);

	pScrollView->Invalidate(TRUE);
	UpdateData(FALSE);
}
