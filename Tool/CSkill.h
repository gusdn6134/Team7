#pragma once
#include "CObj.h"
#include "Include.h"

class CToolView;

class CSkill : public CObj
{
public:
	CSkill();
	~CSkill();
	
	HRESULT Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

    HRESULT Init_Unit_Texture();

    void Set_Path(const TCHAR* _pStateKey, int _id)
    {
        if (_pStateKey)
            m_pStateKey.Format(_T("%s"), _pStateKey);
        else
            m_pStateKey.Empty();

        m_byDrawID = _id;
    }

public:
    CString m_pStateKey;

    INFO m_tinfo;
    CToolView* m_pMainView;

    int m_byDrawID;

};

