#pragma once

#include "Include.h"
#include "ToolView.h"

class CBackGround
{
public:
	CBackGround();
	~CBackGround();

public:
	HRESULT		Initialize();
	void		Update();
	void		Render();
	void		Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY);
	void		Release();

	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Id(int num) { m_byDrawID = num; }

private:
	INFO m_tinfo;

	CToolView* m_pMainView;
	int m_byDrawID;
};

