// CMyForm.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "CMyForm.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CBackGround.h"
#include "MainFrm.h"



// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_CMyForm)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyForm::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMyForm 진단

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_Font.CreatePointFont(180, L"궁서");

	// 탭 추가
	m_TabCtrl.InsertItem(0, _T("Map Tool"));
	m_TabCtrl.InsertItem(1, _T("Collision Tool"));
	m_TabCtrl.InsertItem(2, _T("Unit Tool"));


	m_TabCtrl.GetWindowRect(m_rcCtrl); // 탭 컨트롤의 클라이언트 영역 가져오기


	// 다이얼 로그 생성 및 위치 이동
	m_UnitTool.Create(IDD_CUnitTool, &m_TabCtrl);	// 해당 id에 맞는 다이얼로그 생성
	m_UnitTool.MoveWindow(0, 20, m_rcCtrl.Width(), m_rcCtrl.Height() - 20);
	m_UnitTool.ShowWindow(SW_HIDE);			// 초기 값은 HIDE



	m_MapTool.Create(IDD_CMapTool, &m_TabCtrl);	// 해당 id에 맞는 다이얼로그 생성
	m_MapTool.MoveWindow(0, 20, m_rcCtrl.Width(), m_rcCtrl.Height() - 20);
	m_MapTool.ShowWindow(SW_HIDE);			// 초기 값은 HIDE


	// 초기 선택 탭 설정
	m_TabCtrl.SetCurSel(0);
	m_MapTool.ShowWindow(SW_SHOW);	// 첫 페이지는 SHOW
	CObjMgr::Get_Instance()->Render_ID(OBJ_BackGround, true);

}

void CMyForm::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nCurSel = m_TabCtrl.GetCurSel();	// 현재 선택된 탭의 인덱스
	GET_ScrollView

	switch (nCurSel)
	{
	case 0:		// 첫번째 탭을 눌렀으면 
		m_MapTool.ShowWindow(SW_SHOW);
		m_UnitTool.ShowWindow(SW_HIDE);
		CObjMgr::Get_Instance()->Render_ID(OBJ_BackGround, true);
		break;
	case 1:		
		m_UnitTool.ShowWindow(SW_HIDE);
		m_MapTool.ShowWindow(SW_HIDE);
		CObjMgr::Get_Instance()->Render_ID(OBJ_BackGround, false);
		break;
	case 2:		
		m_MapTool.ShowWindow(SW_HIDE);
		m_UnitTool.ShowWindow(SW_SHOW);
		CObjMgr::Get_Instance()->Render_ID(OBJ_BackGround, false);
		break;
	}

	pScrollView->Invalidate(TRUE);

	*pResult = 0;
}
