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
	afx_msg void OnSelchangeList_SkillFrame();
	afx_msg void OnSkillPlayButton();
	afx_msg void OnPuaseSkillButton();

	afx_msg void Button_HideUnit();
	afx_msg void Button_HideSkill();

	afx_msg void OnAdd();
	afx_msg void OnDestroy();

	afx_msg void OnLbnSelchange_AnimeFrame();
	afx_msg void OnLbnSelchangeList_AnimeName();
	afx_msg void OnBnClickedButton_AnimePlay();

	afx_msg void OnNMReleasedcaptureSlider_X(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedcaptureSlider_Y(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedcaptureSlider_Z(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnBnClickedButton_0_indexSort();
	afx_msg void OnAddUnit();
	afx_msg void OnAddSkill();

	afx_msg void AnimePause();
	afx_msg void OnSave();
	afx_msg void OnLoad();

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

	bool m_bIsUnitShow;
	bool m_bIsSkillShow;

	// 저장 데이터
	map<CString, vector<IMG_INFO*>> ImgData;

	// 수정할 이름
	CString Edit_Name;
	CListBox m_ListBox_Animation;
	CListBox ListBox_AnimationFrame;

	int UnitFrameTime;
	int SkillFrameTime;

	CSliderCtrl m_Slider_PosX;
	CSliderCtrl m_Slider_PosY;
	CSliderCtrl m_Slider_PosZ;

	int  m_iAnimationFrame_Index;

	CEdit m_PosX;
	CEdit m_PosY;
	CEdit m_PosZ;
	
	CEdit AnimeFrameTime;

	CString name1, name2;
	int frame1, frame2;

	UINT_PTR m_Timer1;
	UINT_PTR m_Timer2;

};