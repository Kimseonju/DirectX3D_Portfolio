#pragma once
#include "AttackObject.h"
#include "Component/BillboardComponent.h"
#include "Resource/Sound.h"
class CWendyBrandish : public CAttackObject
{
    friend class CScene;
private:
    CGameObject*    m_Wendy;
    float   m_DeltaTime;
    bool    m_Setting;
    bool    m_Coll;
    float   m_Timer;
    bool    m_FirstAttack;
    bool    m_Out;
    CSharedPtr<CBillboardComponent> m_Texture;
    CSharedPtr<CBillboardComponent> m_TextureBack;
protected:
    CWendyBrandish();
    CWendyBrandish(const CWendyBrandish& obj);
    virtual ~CWendyBrandish();
private:
    virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
    virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
    virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
public:
    void SetWendy(CGameObject* Obj)
    {m_Wendy = Obj;}
    void FirstAttack(bool Enable)
    {m_FirstAttack = Enable;}
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CWendyBrandish* Clone();
};