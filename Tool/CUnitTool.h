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
	afx_msg void OnPuaseButton();
	afx_msg void OnLbnSelchangeList_SkillName();

public:
	void Link_ImageKey();
	void Link_SKillKey();


public:
	CScrollView* m_Scrollview;

	// ImageKey
	CListBox ListBox_ImageKey;
	map<wstring, vector<TEXINFO*>> m_mutimapTex_Unit;
	CString	m_ImgFindName_Unit;

	// Unit_Frame
	CListBox ListBox_Frame;

	// Timer
	UINT_PTR m_AnimationTimer;
	int m_CurrentFrameIndex;

	UINT_PTR m_SkillTimer;
	int m_CurrentSkillIndex;

	// SKill
	CListBox ListBox_SkillName;
	map<wstring, vector<TEXINFO*>> m_mutimapTex_Skill;
	CString	m_ImgFindName_Skill;

	// Skill_Frame
	CListBox ListBoxFrame_Skill;
	afx_msg void OnSelchangeList_SkillFrame();
	afx_msg void OnSkillPlayButton();
	afx_msg void OnPuaseSkillButton();
};