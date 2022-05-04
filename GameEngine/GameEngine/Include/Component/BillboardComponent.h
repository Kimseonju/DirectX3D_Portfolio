#pragma once

#include "PrimitiveComponent.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/Animation3D_Tex.h"

class CBillboardComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;

protected:
    CBillboardComponent();
    CBillboardComponent(const CBillboardComponent& com);
    virtual ~CBillboardComponent();

protected:
	CSharedPtr<CMesh>     m_pMesh;
	CSharedPtr<CAnimation3D_Tex>    m_Animation;
    bool                    m_YRotEnable;
    Vector3                 m_OriginDir;
    bool                    m_bBillboardEnable;
    
public:
    CAnimation3D_Tex* GetAnimation3D_Tex()
    {
        return m_Animation;
    }
    void EnableYBillboard()
    {
        m_YRotEnable = true;
    }

	void SetBillboardEnable(bool Enable)
	{
        m_bBillboardEnable = Enable;
	}
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CBillboardComponent* Clone();

public:
	template <typename T>
	void CreateAnimation3D_Tex()
	{
		m_Animation = new T;

		m_Animation->SetScene(m_pScene);
		m_Animation->SetOwner(this);

		m_Animation->Init();

		m_Animation->Release();
	}
};

