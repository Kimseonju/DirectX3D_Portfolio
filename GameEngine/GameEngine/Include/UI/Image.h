#pragma once

#include "Widget.h"
#include "../Resource/Texture.h"
#include "../Resource/Animation2D.h"
#include "../Resource/UITransformConstantBuffer.h"

class CImage :
    public CWidget
{
    friend class CViewport;
    friend class CScene;
	friend class CWidgetWindow;
	friend class CWidgetComponent;

protected:
    CImage();
    CImage(const CImage& widget);
    virtual ~CImage();

protected:
    CSharedPtr<CTexture>    m_Texture;
    CSharedPtr<CAnimation2D>    m_Animation;

public:
    CAnimation2D* GetAnimation2D()  const
    {
        return m_Animation;

    }
    CTexture* GetTexture()
    {
        return m_Texture;
    }
    void SetTexture(CTexture* Texture);
    
    void SetTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CImage* Clone();
    virtual void SetCenter();
public:
    template <typename T>
    void CreateAnimation2D()
    {
        m_Animation = new T;

        m_Animation->SetScene(m_Scene);
        m_Animation->SetOwner(this);

        m_Animation->Init();

        m_Animation->Release();

        m_TransformCBuffer->SetAnimation2DEnable(true);
    }
};

