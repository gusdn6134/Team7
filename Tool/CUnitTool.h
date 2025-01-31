﻿#pragma once
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


public:
	void Link_ImageKey();
	HRESULT Insert_Unit_Texture();


public:
	// ImageKey
	CListBox ListBox_ImageKey;
	map<wstring, vector<TEXINFO*>> m_mutimapTex;
	CString	m_ImgFindName;

	//Frame
	CListBox ListBox_Frame;



	afx_msg void OnFrameSelChange();
};