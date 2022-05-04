#pragma once
#include "GameObject.h"
#include "Component/Camera.h"
#include "Component/SpringArm3D.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

// 이펙트 스폰하기 위한 기반 클래스 (상속해서 사용)
class CEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CEffect();
    CEffect(const CEffect& obj);
    virtual ~CEffect();

protected:
    CSharedPtr<CSceneComponent> m_Root;
    CSharedPtr<CStaticMeshComponent> m_Mesh;
    CSharedPtr<CColliderSphere> m_Body;

    // Effect Test를 위한 카메라 (주석 처리하고 사용)
    CSharedPtr<CCamera> m_Camera;
    CSharedPtr<CSpringArm3D> m_Arm;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CEffect* Clone();

private:
    void LoadMeshEffectResource();
};

