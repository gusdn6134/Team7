#pragma once
#include "Include.h"
#include "CObj.h"

class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

public:
	CObjMgr();
	~CObjMgr();

public:
	void AddObject(OBJID m_eId, CObj* m_pName);
	list<CObj*>* Get_ObjList(OBJID _id) { return &m_ObjList[_id]; }

public:
	void Update();
	void Render();
	void Release();

	void Delete_ID(OBJID eID);
	void Render_ID(OBJID eID, bool _Render);

private:
	list<CObj*>		m_ObjList[OBJ_END];
};

