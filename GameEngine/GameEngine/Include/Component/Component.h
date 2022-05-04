#pragma once

#include "../Ref.h"

class CComponent :
    public CRef
{
    friend class CGameObject;

protected:
    CComponent();
    CComponent(const CComponent& com);
    virtual ~CComponent() = 0;

protected:
    class CScene* m_pScene;
    class CGameObject* m_pOwner;
    Component_Class_Type m_ClassType;
public:

	void SetOwner(class CGameObject* Owner)
	{
		m_pOwner = Owner;
	}

    class CGameObject* GetOwner()   const
    {
        return m_pOwner;
    }

    Component_Class_Type GetComponent_Class_Type()   const
	{
		return m_ClassType;
	}
    virtual void Active(bool bActive);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void PrevRender(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual void RenderDebug(float DeltaTime);
    virtual CComponent* Clone() = 0;

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

