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
#include "CTerrain.h"

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
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT2, m_MapSizeX);
	DDX_Text(pDX, IDC_EDIT3, m_MapSizeY);
	DDX_Control(pDX, IDC_LIST1, m_listBackGround);
	DDX_LBString(pDX, IDC_LIST1, m_strBackGroundName);
	DDX_Control(pDX, IDC_LIST2, m_listTile);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnMapSizeChange)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnBG_ListBox)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMapTool::OnTile_ListBox)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::OnMapTooll)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTool::OnLoadMap)
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
		return 1;
	}

	/*--------------------------
		타일 이미지 추가
	--------------------------*/
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(
		L"../MapleStory/Tile/Tile_%d.png",
		TEX_MULTI, L"Tile", L"Tile_", 4)))
	{
		AfxMessageBox(L"Terrain Texture Insert Failed");
		return 1;
	}

	const auto& texTile = CTextureMgr::Get_Instance()->Get_mapTex();
	it = texTile.find(L"Tile");
	if (it != texTile.end())
	{
		CTexture* Tile = it->second;
		m_mutiTileTex = dynamic_cast<CMultiTexture*>(Tile)->Get_MultiTex();
		auto iter = m_mutiTileTex.find(L"Tile_");

		for (size_t i = 0; i < iter->second.size(); i++)
		{
			CString temp;
			temp.Format(L"%s%d", L"Tile_", i);
			m_listTile.AddString(temp);
			
		}
	}
	return TRUE;
}

void CMapTool::OnBG_ListBox()
{
	UpdateData(TRUE);

	int iTileX(0);
	int iTileY(0);

	int	iIndex = m_listBackGround.GetCurSel();
	{
		CString	strFindName;
		auto	iter = m_mutimapTex.find(L"BackGround_");
		if (iter == m_mutimapTex.end())
			return;

		if (!m_vecTile.empty())
		{
			for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
			m_vecTile.clear();
			m_vecTile.reserve(iTileX * iTileY); // 성능 최적화
		}

		pTerrain = dynamic_cast<CTerrain*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Tile)->front());

		m_MapSizeX = iter->second[iIndex]->tImgInfo.Width;
		m_MapSizeY = iter->second[iIndex]->tImgInfo.Height;

		iTileX = m_MapSizeX / TILECX;
		iTileY = m_MapSizeY / TILECY;

		pTerrain->Set_MapSizeX(iTileX);
		pTerrain->Set_MapSizeY(iTileY);


		for (int i = 0; i < iTileY; ++i)
		{
			for (int j = 0; j < iTileX; ++j)
			{
				TILE* pTile = new TILE;

				float fX = float(j * TILECX);
				float fY = float(i * TILECY);

				pTile->vPos = { fX, fY, 0.f };
				pTile->vSize = { (float)TILECX, (float)TILECY };
				pTile->byDrawID = 0;
				pTile->byOption = 0;
				m_vecTile.push_back(pTile);
			}
		}
		
		if (!m_vecTile.empty())
		{
			pTerrain->Set_vecTile(&m_vecTile);
		}
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

void CMapTool::OnTile_ListBox()
{
	UpdateData(TRUE);

	CString path;

	int iIndex = m_listTile.GetCurSel();
	{
		auto iter = m_mutiTileTex.find(L"Tile_");

		if (iter == m_mutiTileTex.end())
			return;

		pTerrain->Set_ChangeIndex(iIndex);
	
		HBITMAP hOldBitmap = (HBITMAP)m_Picture.GetBitmap();
		if (hOldBitmap)
		{
			m_Picture.SetBitmap(nullptr); // 기존 비트맵 해제
			DeleteObject(hOldBitmap);
		}

		path.Format(L"../MapleStory/Tile/Tile_%d.png", iIndex);
	
		CImage image;
		image.Load(path);

		m_Picture.SetBitmap(image);
		m_Picture.SetWindowPos(NULL, 0, 0, 100, 100, SWP_NOMOVE | SWP_NOZORDER);

		m_Picture.Invalidate(TRUE);
		m_Picture.UpdateWindow();

		m_MapSizeX = iter->second[iIndex]->tImgInfo.Width;
		m_MapSizeY = iter->second[iIndex]->tImgInfo.Height;
	}

	//GET_ScrollView
	/*if (pScrollView != nullptr)
	{
		pScrollView->SetScrollSizes(MM_TEXT, CSize(m_MapSizeX, m_MapSizeY));
	}*/
	//pScrollView->Invalidate(FALSE);

	UpdateData(FALSE);
}


void CMapTool::OnMapTooll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog		Dlg(FALSE,		// TRUE(불러오기), FALSE(다른 이름으로 저장) 모드 지정
		L"dat",		// default 확장자명
		L"*.dat",	// 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// 읽기 전용 체크 박스 숨김 | 중복된 이름으로 파일 저장 시 경고 메세지 띄움
		L"Data Files(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식
		this);	// 부모 윈도우 주소


	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
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

		pTerrain = dynamic_cast<CTerrain*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Tile)->front());

		vector<TILE*>* vecTile = pTerrain->Get_vecTile();
		
		int i = vecTile->size();



		if (vecTile->empty())
			return;

		DWORD dwByte(0);
		int iSize = vecTile->size();

		WriteFile(hFile, &iSize, sizeof(int), &dwByte, nullptr);

		for (auto& pTile : *vecTile)
		{
			WriteFile(hFile, &pTile->byDrawID, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &pTile->byOption, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &pTile->vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
			WriteFile(hFile, &pTile->vSize, sizeof(D3DXVECTOR2), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}


void CMapTool::OnLoadMap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
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

	pTerrain = dynamic_cast<CTerrain*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Tile)->front());

	vector<TILE*>* vecTile = pTerrain->Get_vecTile();

	if (IDOK == Dlg.DoModal())
	{
		
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

		DWORD	dwByte(0);
		int iSize(0);

		while (true)
		{
			// key 값 로드
			
			
			ReadFile(hFile, &iSize, sizeof(int), &dwByte, nullptr);

			for (int i = 0; i < iSize; ++i)
			{
				TILE* Tile = new TILE;
				ReadFile(hFile, &Tile->byDrawID, sizeof(BYTE), &dwByte, nullptr);
				ReadFile(hFile, &Tile->byOption, sizeof(BYTE), &dwByte, nullptr);
				ReadFile(hFile, &Tile->vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
				ReadFile(hFile, &Tile->vSize, sizeof(D3DXVECTOR2), &dwByte, nullptr);

				m_vecTile.push_back(Tile);
			}

			if (0 == dwByte)
			{
				break;
			}

		}

		CloseHandle(hFile);
	}

	CObjMgr::Get_Instance()->Render_ID(OBJ_Tile, true);
	pTerrain = dynamic_cast<CTerrain*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_Tile)->front());
	pTerrain->Set_vecTile(&m_vecTile);
	GET_TOOLVIEW
	pView->Invalidate(FALSE);
	UpdateData(FALSE);
}
