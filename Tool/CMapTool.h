#pragma once
#include "afxdialogex.h"
#include "CTexture.h"
#include "CBackGround.h"
#include "resource.h"

// CMapTool 대화 상자

class CMapTool : public CDialogEx
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMapTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMapSizeChange();

public:	//value
	int m_MapSizeX;
	int m_MapSizeY;

public: //BackGround
	CString m_strBackGroundName;
	CListBox m_listBackGround;
	CListBox m_listTile;

	map<wstring, vector<TEXINFO*>> m_mutimapTex;
	map<wstring, vector<TEXINFO*>> m_mutiTileTex;
	map<CString, CImage*>		m_mapPngImage;

	CBackGround* m_pBackGround;

public: //TilePath
	virtual BOOL OnInitDialog();

	afx_msg void OnBG_ListBox();
	afx_msg void OnTile_ListBox();


	CStatic m_Picture;
};
