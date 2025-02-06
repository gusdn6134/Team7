#pragma once
#include "CObj.h"
#include "Include.h"
#include "ToolView.h"

class CUnit : public CObj
{
public:
    CUnit();
    virtual ~CUnit();

public:
    HRESULT Initialize() override;
    void Update() override;
    void Render() override;
    void Release() override;

    void SetPos(D3DXVECTOR3 _add) { m_tinfo.vPos = _add; }

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

