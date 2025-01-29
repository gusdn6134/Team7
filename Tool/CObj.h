#pragma once
class CObj
{
public:
	CObj() {}
	~CObj() {}

public:
	virtual HRESULT		Initialize() PURE;
	virtual void		Update() PURE; 
	virtual void		Render() PURE;
	virtual void		Release() PURE;

	virtual void		Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY);

};

