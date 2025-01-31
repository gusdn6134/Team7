#pragma once
#include "CObj.h"
#include "Include.h"

class CUnit : public CObj
{
public:
	CUnit();
	~CUnit();

	HRESULT Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void Set_Path(const TCHAR* _pStateKey, int _id)
	{
		m_pStateKey = _pStateKey;
		m_byDrawID = _id;
	}

public:
	INFO m_tinfo;
	CToolView* m_pMainView;


	int m_byDrawID;
	const TCHAR* m_pStateKey;

};

