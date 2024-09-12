#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTexture;
class CRcTex;
class CTransform;

END

class CPipeBoard :public Engine::CGameObject
{
private:
	explicit CPipeBoard(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPipeBoard();

public:	
	virtual   HRESULT   Ready_GameObject();
	virtual   _int      Update_GameObject(const _float& fTimeDelta);
	virtual   void	    LateUpdate_GameObject(const _float& fTimeDelta);
	virtual   void      Render_GameObject();

private:
	HRESULT    Add_Component();
	void Key_Input(const _float& fTimeDelta);

private:
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;

public:
	static CPipeBoard* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};