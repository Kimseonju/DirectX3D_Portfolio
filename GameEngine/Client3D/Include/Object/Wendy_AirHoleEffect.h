#pragma once

#include "GameObject.h"
#include "Component/DecalComponent.h"
#include "Component/BillboardComponent.h"

class CWendy_AirHoleEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CWendy_AirHoleEffect();
    CWendy_AirHoleEffect(const CWendy_AirHoleEffect& obj);
    virtual ~CWendy_AirHoleEffect();

protected:
protected:
    CSharedPtr<CBillboardComponent> m_BlackCircle;
    CSharedPtr<CBillboardComponent> m_BlackWind;
    bool        m_Enable;
    bool        m_Start;
    float       m_Scale1;
    float       m_Scale2;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CWendy_AirHoleEffect* Clone();

public:
    void EffectDeath()
    {
        m_Enable = false;
    }
};


