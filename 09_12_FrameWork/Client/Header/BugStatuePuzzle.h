#pragma once
#include "GameObject.h"

class CBugStatuePuzzle :public Engine::CGameObject
{
private:
	explicit CBugStatuePuzzle(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBugStatuePuzzle();

public:
	virtual   HRESULT   Ready_GameObject();
	virtual   _int      Update_GameObject(const _float& fTimeDelta);
	virtual   void	    LateUpdate_GameObject(const _float& fTimeDelta);
	virtual   void      Render_GameObject();

public:
	static CBugStatuePuzzle* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void Add_Statue(CGameObject* _pStatue) { m_vecStatues.push_back(_pStatue); m_iStatueCount++; }
	void Add_StoneBlock(CGameObject* _pBlock) { m_vecStoneBlocks.push_back(_pBlock); }
	void Add_StoneBlockHole(CGameObject* _pBlockHole) { m_vecStoneBlocksHoles.push_back(_pBlockHole); }
	void Check_Matched();
	void Key_Input(const _float& fTimeDelta);

private:
	_bool m_bIsMatched;
	_int m_iStatueCount;
	vector<CGameObject*> m_vecStatues;
	vector<CGameObject*> m_vecStoneBlocks;
	vector<CGameObject*> m_vecStoneBlocksHoles;

private:
	virtual void Free();
};