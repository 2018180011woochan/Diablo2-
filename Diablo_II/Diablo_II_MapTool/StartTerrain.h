#pragma once

#ifndef __STARTTERRAIN_H__
#define __STARTTERRAIN_H__

class CDiablo_II_MapToolView;
class CStartTerrain
{
public:
	CStartTerrain();
	~CStartTerrain();

public:
	void Set_View(CDiablo_II_MapToolView* pView) { m_pView = pView; }
public:
	void TileChange_Terrain(const _vec3& vPos, const BYTE& byDrawID, const BYTE& byOption = 0);

	///////////////////////// 디폴트 타일로 바꾸기 /////////////////////////////////////////
	void InitTile(const _vec3& vPos, const BYTE& byDrawID);
	////////////////////////////////////////////////////////////////////////////////////////

	int Get_TileIndex(const _vec3& vPos);
	bool IsPicking(const _vec3& vPos, const int& iIndex);
	void Set_Ratio(_matrix& matWorld, float fRatioX, float fRatioY);
public:
	HRESULT Ready_Terrain();
	void Render_Terrain();
	void Mini_Render_Terrain();
	void Release();

	/////////////////////////// 저장 불러오기 위해서 만듬 ////////////////////////////
public:
	vector<TILE*> Get_Tile() { return m_vecTile; }
	void Set_Tile(vector<TILE*> _vecTile) { m_vecTile = _vecTile; }
	//////////////////////////////////////////////////////////////////////////////////

private:
	vector<TILE*> m_vecTile;
	CDiablo_II_MapToolView* m_pView;
};

#endif // !__STARTTERRAIN_H__

