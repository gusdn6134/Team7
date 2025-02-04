#pragma once

#include "Include.h"
#include "ToolView.h"
#include "CObj.h"

class CTerrain : public CObj
{
public:
	CTerrain();
	~CTerrain();

public:
	HRESULT		Initialize() override;
	void		Update() override;
	void		Render() override;
	void		Release() override;

public:
	void	Tile_Change(const D3DXVECTOR3& vPos, const BYTE& byDrawID);
	void	Set_MainView(CToolView* pMainView) { m_pMainView = pMainView;  }
	void	Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY);

	void Set_vecTile(const vector<TILE*>& m_Tile) { m_vecTile = m_Tile; }
	//vector<TILE*>& Get_vecTile() { return m_vecTile; }

private:
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
	int		Get_TileIdx(const D3DXVECTOR3& vPos);


private:
	vector<TILE*>		m_vecTile;
	CToolView*			m_pMainView;
};

