#pragma once
#include "Item.h"
class CEnkyHat : public CItem
{
private:
	explicit CEnkyHat(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEnkyHat();

public:

	virtual   HRESULT   Ready_GameObject();
	virtual   _int      Update_GameObject(const _float& fTimeDelta);
	virtual   void      LateUpdate_GameObject(const _float& fTimeDelta);
	virtual   void      Render_GameObject();

private:
	HRESULT    Add_Component();

public:
	static CEnkyHat* Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

