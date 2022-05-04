#pragma once

#include "GameObject.h"
#include "Component/DecalComponent.h"
#include "Component/BillboardComponent.h"

class CKnifeEffect : public CGameObject
{
    friend class CScene;

protected:
    CKnifeEffect();
    CKnifeEffect(const CKnifeEffect& obj);
    virtual ~CKnifeEffect();

protected:
    CSharedPtr<CBillboardComponent> m_Effect;
    CAnimation3D_Tex* m_Animation;

    bool        m_WendyAtt;
    bool        m_AxeAtt;
    bool        m_Setting;
private:
    void AnimationEnd(const std::string& Name);
public:
    void SetWendyAtt()
    {m_WendyAtt = true;}
    void SetAxeAtt()
    {m_AxeAtt = true;}
    void AddEffectPos(Vector3 Pos)
    {
        m_Effect->AddWorldPos(Pos);
    }
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CKnifeEffect* Clone();

public:
    void EffectDeath()
    {
        m_Enable = false;
    }
};


