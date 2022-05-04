#pragma once

#include "GameObject.h"
#include "Component/DecalComponent.h"
#include "Component/BillboardComponent.h"

class CMonsterSpawnEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CMonsterSpawnEffect();
    CMonsterSpawnEffect(const CMonsterSpawnEffect& obj);
    virtual ~CMonsterSpawnEffect();

protected:
protected:
    CSharedPtr<CBillboardComponent> m_BlackCircle;
    CSharedPtr<CBillboardComponent> m_BlackWind;
    CSharedPtr<CBillboardComponent> m_BlackWind2;
    CSharedPtr<CBillboardComponent> m_BlackWind3;
    CAnimation3D_Tex* m_Animation;
    float       m_Scale;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    void ManualUpdate(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CMonsterSpawnEffect* Clone();

public:
    void EffectDeath()
    {m_Enable = false;}
};


