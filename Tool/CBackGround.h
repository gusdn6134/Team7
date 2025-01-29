#pragma once

#include "Include.h"
#include "ToolView.h"
#include "CObj.h"

class CBackGround : public CObj
{
public:
	CBackGround();
	~CBackGround();

public:
	HRESULT		Initialize() override;
	void		Update() override;
	void		Render() override;
	void		Release() override;

	void		Set_Id(int num) { m_byDrawID = num; }

private:
	INFO m_tinfo;

	CToolView* m_pMainView;
	int m_byDrawID;
};

