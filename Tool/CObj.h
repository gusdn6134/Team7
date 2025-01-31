#pragma once
class CObj
{
public:
	CObj() : m_bIsRender(false) {}
	virtual ~CObj() {}

public:
	virtual HRESULT		Initialize() PURE;
	virtual void		Update() PURE; 
	virtual void		Render() PURE;
	virtual void		Release() PURE;

	virtual void		Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY);

public:
	void Set_Render(bool render) { m_bIsRender = render; }
public:
	bool m_bIsRender;
};

