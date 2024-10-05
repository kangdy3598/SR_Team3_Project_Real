#include "pch.h"
#include "ElectriceelBoss.h"
#include "Export_Utility.h"

CElectriceelBoss::CElectriceelBoss(LPDIRECT3DDEVICE9 pGraphicDev)
    :Engine::CGameObject(pGraphicDev)
    ,m_pComeTex(nullptr)
    ,m_eCurState(Electriceel_STATE::IN_OUT_9)   
    ,m_ePreState(Electriceel_STATE::IN_OUT_9)
{

}

CElectriceelBoss::~CElectriceelBoss()
{
}

HRESULT CElectriceelBoss::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_vecTexture.resize(10);


    //12시,1시,3시,9시 방향 텍스처
    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/ElectriceelBoss/Sprite_HarborElectricEel_InOut1.png", &m_vecTexture[0]);
    D3DXCreateTextureFromFile(m_pGraphicDev, L"../Bin/Resource/Texture/ElectriceelBoss/Sprite_HarborElectricEel_InOut2.png", &m_vecTexture[1]);
    //11시 텍스처

    m_pAnimatorCom->CreateAnimation(L"InOut12", m_vecTexture[0], _vec2(0.f, 0.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"InOut1",  m_vecTexture[0], _vec2(0.f, 512.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"InOut3",  m_vecTexture[0], _vec2(0.f, 1024.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"InOut9",  m_vecTexture[0], _vec2(0.f, 1536.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"InOut11", m_vecTexture[1], _vec2(0.f, 0.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.2f, 5);
    

    m_pAnimatorCom->CreateAnimation(L"IN_12", m_vecTexture[0], _vec2(2560.f, 0.f), _vec2(512.f, 512.f), _vec2(-512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"IN_1", m_vecTexture[0], _vec2(2560.f, 512.f), _vec2(512.f, 512.f), _vec2(-512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"IN_3", m_vecTexture[0], _vec2(2560.f, 1024.f), _vec2(512.f, 512.f), _vec2(-512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"IN_9", m_vecTexture[0], _vec2(2560.f, 1536.f), _vec2(512.f, 512.f), _vec2(-512.f, 0.f), 0.2f, 5);
    m_pAnimatorCom->CreateAnimation(L"IN_11", m_vecTexture[1], _vec2(2560.f, 0.f), _vec2(512.f, 512.f), _vec2(-512.f, 0.f), 0.2f, 5);


    m_pAnimatorCom->CreateAnimation(L"IDLE_12", m_vecTexture[2], _vec2(0.f, 0.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    m_pAnimatorCom->CreateAnimation(L"IDLE_1",  m_vecTexture[2], _vec2(0.f, 512.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    m_pAnimatorCom->CreateAnimation(L"IDLE_3",  m_vecTexture[2], _vec2(0.f, 1024.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    m_pAnimatorCom->CreateAnimation(L"IDLE_9",  m_vecTexture[2], _vec2(0.f, 1536.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    m_pAnimatorCom->CreateAnimation(L"IDLE_11", m_vecTexture[3], _vec2(0.f, 0.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);


    m_pAnimatorCom->CreateAnimation(L"PROJECT_SHOT_12", m_vecTexture[4], _vec2(0.f, 0.f),   _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    m_pAnimatorCom->CreateAnimation(L"PROJECT_SHOT_1",  m_vecTexture[4], _vec2(0.f, 512.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    m_pAnimatorCom->CreateAnimation(L"PROJECT_SHOT_3",  m_vecTexture[4], _vec2(0.f, 1024.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    m_pAnimatorCom->CreateAnimation(L"PROJECT_SHOT_9",  m_vecTexture[4], _vec2(0.f, 1536.f), _vec2(512.f, 512.f), _vec2(512.f, 0.f), 0.4f, 3);
    //m_pAnimatorCom->CreateAnimation(L"PROJECT_SHOT_11", m_vecTexture[5], _vec2(0.f ,)


    //m_pAnimatorCom->Play(L"InOut1", true);

    dwtime = GetTickCount64();  
    m_pTransformCom->Set_Pos(200.f, 30.f, 500.f);
    m_pTransformCom->m_vScale = { 50.f, 50.f, 20.f };

    return S_OK;
}



_int CElectriceelBoss::Update_GameObject(const _float& fTimeDelta)
{
    Add_RenderGroup(RENDER_ALPHA, this);

    Electriceel_STATE patterns[] =
    {
        Electriceel_STATE::IN_OUT_9,
        Electriceel_STATE::IN_OUT_11,   
        Electriceel_STATE::IN_OUT_12,
        Electriceel_STATE::IN_OUT_1,
        Electriceel_STATE::IN_OUT_3,
    };

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 4);

    if (dwtime + 1750 < GetTickCount64())
    {
        int randomIndex = dis(gen);     
        m_eCurState = patterns[randomIndex];    
        dwtime = GetTickCount64();  
    }

    m_ePreState = m_eCurState;  


    update_move();  
    update_state(); 
    update_sound(); 
    update_animation();


    return Engine::CGameObject::Update_GameObject(fTimeDelta);
}

void CElectriceelBoss::update_move()
{
    if (m_eCurState == Electriceel_STATE::IN_OUT_9)
    {

        m_pTransformCom->Set_Pos(200.f, 60.f, 500.f);

    }

    else if (m_eCurState == Electriceel_STATE::IN_OUT_11)
    {
        m_pTransformCom->Set_Pos(350.f, 30.f, 650.f);
    }

    else if (m_eCurState == Electriceel_STATE::IN_OUT_12)
    {

        m_pTransformCom->Set_Pos(500.f, 80.f, 700.f);

    }

    else if (m_eCurState == Electriceel_STATE::IN_OUT_1)
    {
        m_pTransformCom->Set_Pos(650.f, 30.f, 650.f);
    }

    else if (m_eCurState == Electriceel_STATE::IN_OUT_3)
    {
        m_pTransformCom->Set_Pos(700.f, 30.f, 500.f);
    }


}

void CElectriceelBoss::update_state()
{
}

void CElectriceelBoss::update_sound()
{
}


void CElectriceelBoss::update_animation()
{
    switch (m_eCurState)
    {
    case Electriceel_STATE::IN_OUT_9:
        m_pAnimatorCom->Play(L"InOut9", true);
        break;
    case Electriceel_STATE::IN_OUT_11: 
        m_pAnimatorCom->Play(L"InOut11", true);
        break;
    case Electriceel_STATE::IN_OUT_12:
        m_pAnimatorCom->Play(L"InOut12", true);
        break;
    case Electriceel_STATE::IN_OUT_1:
        m_pAnimatorCom->Play(L"InOut1", true);
        break;
    case Electriceel_STATE::IN_OUT_3:
        m_pAnimatorCom->Play(L"InOut3", true);
        break;
    case Electriceel_STATE::IDLE:
        break;
    case Electriceel_STATE::ATTACK:
        break;
    default:
        break;
    }
}

void CElectriceelBoss::LateUpdate_GameObject(const _float& fTimeDelta)
{
    Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CElectriceelBoss::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


    switch (m_eCurState)    
    {
    case Electriceel_STATE::IN_OUT_9:
        m_pGraphicDev->SetTexture(0, m_vecTexture[0]);
        break;
    case Electriceel_STATE::IN_OUT_11:
        m_pGraphicDev->SetTexture(0, m_vecTexture[1]);
        break;
    case Electriceel_STATE::IN_OUT_12:
        m_pGraphicDev->SetTexture(0, m_vecTexture[0]);
        break;
    case Electriceel_STATE::IN_OUT_1:
        m_pGraphicDev->SetTexture(0, m_vecTexture[0]);
        break;
    case Electriceel_STATE::IN_OUT_3:
        m_pGraphicDev->SetTexture(0, m_vecTexture[0]);
        break;
    case Electriceel_STATE::IDLE:

        break;
    case Electriceel_STATE::ATTACK:
        break;
    default:
        break;
    }

    m_pAnimatorCom->render();


    //맵툴 작성시 끄기 
    m_pBoundBox->Render_Buffer();   
    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CElectriceelBoss::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pAnimatorCom = dynamic_cast<CAnimator2*>(Engine::Clone_Proto(L"Proto_Animator"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);  
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Buffer", pComponent });        

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);  
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });    

    pComponent = m_pBoundBox = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Proto_Collider"));    
    NULL_CHECK_RETURN(pComponent, E_FAIL);  
    m_pBoundBox->SetGameObjectPtr(this);    
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent }); 

    return S_OK;
}

HRESULT CElectriceelBoss::SetUp_Material()
{
    return S_OK;
}

void CElectriceelBoss::Key_Input(const _float& fTimeDelta)
{
}

CElectriceelBoss* CElectriceelBoss::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CElectriceelBoss* pElectriceelBoss = new CElectriceelBoss(pGraphicDev);

    if (FAILED(pElectriceelBoss->Ready_GameObject()))
    {
        Safe_Release(pElectriceelBoss);
        MSG_BOX("pObject Create Failed");
        return nullptr;
    }

    return pElectriceelBoss;
}

void CElectriceelBoss::Free()
{
    Engine::CGameObject::Free();
}

void CElectriceelBoss::OnCollision(CGameObject* _pOther)
{
    int a = 4;
}
