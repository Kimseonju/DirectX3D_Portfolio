#pragma once

#include "GameObject.h"
#include "Component/DecalComponent.h"
#include "Component/BillboardComponent.h"

enum class ExplosionEffectType
{
    Type_1,
    Type_2,
    Type_3
};

class CExplosionEffect : public CGameObject
{
    friend class CScene;

protected:
    CExplosionEffect();
    CExplosionEffect(const CExplosionEffect& obj);
    virtual ~CExplosionEffect();

protected:
protected:
    CSharedPtr<CBillboardComponent> m_Effect;
    CAnimation3D_Tex* m_Animation;

    ExplosionEffectType     m_Type;
    bool        m_Setting;
    bool        m_Enable;
    float       m_EffectScaleMult;
private:
    void AnimationEnd(const std::string& Name);
public:
    void SetEffectMultScale(float Value)
    {m_EffectScaleMult = Value;}
    void AddEffectPos(Vector3 Pos)
    {m_Effect->AddWorldPos(Pos);}
    void SetEffectType(ExplosionEffectType Type)
    {m_Type = Type;}
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CExplosionEffect* Clone();

public:
    void EffectDeath()
    {
        m_Enable = false;
    }
};


