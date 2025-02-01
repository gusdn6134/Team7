#pragma once
#include "afxdialogex.h"
#include "CTexture.h"
// CUnitTool 대화 상자

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUnitTool };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnAnimePlayButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnImgKeySelChange();
	afx_msg void OnFrameSelChange();

public:
	void Link_ImageKey();


public:
	// ImageKey
	CListBox ListBox_ImageKey;
	map<wstring, vector<TEXINFO*>> m_mutimapTex;
	CString	m_ImgFindName;

	//Frame
	CListBox ListBox_Frame;

	//Timer
	UINT_PTR m_AnimationTimer;
	int m_CurrentFrameIndex;


	CScrollView* m_Scrollview;
	afx_msg void OnPuaseButton();
	CListBox ListBox_SkillName;
	afx_msg void OnLbnSelchangeList_SkillName();
};