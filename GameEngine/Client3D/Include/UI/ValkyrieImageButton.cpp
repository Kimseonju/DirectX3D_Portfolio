#include "ValkyrieImageButton.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Scene/Viewport.h>
#include "Resource/UITransformConstantBuffer.h"
CValkyrieImageButton::CValkyrieImageButton():
	m_ValkyrieTexture(nullptr)
{
}

CValkyrieImageButton::~CValkyrieImageButton()
{
}

void CValkyrieImageButton::Start()
{
	CButton::Start();
}

bool CValkyrieImageButton::Init()
{
	CButton::Init();
	return true;
}

void CValkyrieImageButton::Update(float DeltaTime)
{
	CButton::Update(DeltaTime);
}

void CValkyrieImageButton::PostUpdate(float DeltaTime)
{
	CButton::PostUpdate(DeltaTime);
}

void CValkyrieImageButton::Render()
{
	CButton::Render();



	if (m_ValkyrieTexture)
	{
		m_TransformCBuffer->SetTextureEnable(true);
		m_TransformCBuffer->UpdateCBuffer();

		m_ValkyrieTexture->SetShader(0, TST_PIXEL);
		m_Mesh->Render();
		m_ValkyrieTexture->ResetShader(0, TST_PIXEL);

	}
}

CValkyrieImageButton* CValkyrieImageButton::Clone()
{
	return new CValkyrieImageButton(*this);
}

