#pragma once

#include "Include.h"
#include "ToolView.h"
#include "CObj.h"
#include "CMapTool.h"

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
	void	Picking_Tile(const D3DXVECTOR3& vPos, const BYTE& byDrawID);


	void	Set_MainView(CScrollView* pMainView) { m_pMainView = pMainView; }
	void	Set_Ratio(D3DXMATRIX* pOut, float _fX, float _fY);
	void	Set_vecTile(vector<TILE*>* m_Tile) { m_vecTile = m_Tile; }
	void	Set_Picking(bool _bPicing) { m_bPicking = _bPicing; }
	void	Set_MapSizeX(int _MapSizeX) { m_MapSizeX = _MapSizeX; }
	void	Set_MapSizeY(int _MapSizeY) { m_MapSizeY = _MapSizeY; }
	void	Set_ChangeIndex(int _ChangeIndex) { m_iChangeIndex = _ChangeIndex; }

	bool	Get_Picking() { return m_bPicking; }
	int		Get_ChangeIndex() { return m_iChangeIndex; }
	vector<TILE*>*  Get_vecTile() { return m_vecTile; }
	
private:

private:
	int		m_iTileIndex;
	bool	m_bPicking;

	int		m_MapSizeX;
	int		m_MapSizeY;
	int		m_iChangeIndex;

private:
	vector<TILE*>*		m_vecTile;
	CScrollView*		m_pMainView;
	const TEXINFO*		pTexInfo;
};

