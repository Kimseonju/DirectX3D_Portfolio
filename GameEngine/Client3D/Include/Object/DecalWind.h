#pragma once

#include "GameObject.h"
#include "Component/DecalComponent.h"

class CDecalWind :
    public CGameObject
{
    friend class CScene;

protected:
    CDecalWind();
    CDecalWind(const CDecalWind& obj);
    virtual ~CDecalWind();

protected:
    CSharedPtr<CDecalComponent> m_Decal;
    bool        m_Enable;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CDecalWind* Clone();
};

