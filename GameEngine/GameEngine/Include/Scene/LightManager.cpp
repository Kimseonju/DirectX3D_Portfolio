
#include "LightManager.h"
#include "../Component/LightComponent.h"
#include "../GameObject.h"
#include "Scene.h"
#include "../Resource/ShaderManager.h"
#include "../Resource/Shader.h"
#include "../Device.h"
#include "SceneResource.h"
#include "../Render/RenderState.h"
#include "../Render/RenderStateManager.h"

CLightManager::CLightManager():
	m_pScene(nullptr),
	m_DepthWriteDisable(nullptr),
	m_LightVolumeBackState(nullptr),
	m_LightVolumeFrontState(nullptr),
	m_FrontFaceCull(nullptr),
	m_CullNone(nullptr),
	m_LightAccState(nullptr)
{
}

CLightManager::~CLightManager()
{
}

void CLightManager::SetGlobalLight(CGameObject* Obj)
{
	m_GlobalLight = Obj;
}

void CLightManager::SetGlobalLightComponent(CLightComponent* Component)
{
	m_GlobalLightComponent = Component; 
}

void CLightManager::AddLight(CLightComponent* Light)
{
	m_LightList.push_back(Light);
}

bool CLightManager::Init()
{

	//Com->SetLightType(Light_Type::Point);
	//Com->SetRelativePos(0.f, 1.5f, 0.f);
	//Com->SetDistance(2.5f);

	m_LightDirShader = CShaderManager::GetInst()->FindShader("LightDirAccShader");
	m_LightShader = CShaderManager::GetInst()->FindShader("LightAccShader");

	m_SphereMesh = m_pScene->GetResource()->FindMesh("SpherePos");

	m_DepthWriteDisable = CRenderStateManager::GetInst()->FindRenderState("DepthWriteDisable");
	m_LightVolumeBackState = CRenderStateManager::GetInst()->FindRenderState("LightVolumeBackState");
	m_LightVolumeFrontState = CRenderStateManager::GetInst()->FindRenderState("LightVolumeFrontState");
	m_FrontFaceCull = CRenderStateManager::GetInst()->FindRenderState("FrontFaceCulling");
	m_CullNone = CRenderStateManager::GetInst()->FindRenderState("CullNone");
	m_LightAccState = CRenderStateManager::GetInst()->FindRenderState("LightAcc");

	//Com->SetLightType(Light_Type::Point);
	//Com->SetDistance(5.f);

	return true;
}

void CLightManager::Update(float DeltaTime)
{
	auto	iter = m_LightList.begin();
	auto	iterEnd = m_LightList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_LightList.erase(iter);
			iterEnd = m_LightList.end();
			continue;
		}

		++iter;
	}
}

void CLightManager::SetShader()
{
	auto	iter = m_LightList.begin();
	auto	iterEnd = m_LightList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (!(*iter)->IsEnable())
			continue;

		(*iter)->SetShader();
	}
}

void CLightManager::Render()
{
	auto	iter = m_LightList.begin();
	auto	iterEnd = m_LightList.end();

	m_LightAccState->SetState();

	for (; iter != iterEnd; ++iter)
	{
		if (!(*iter)->IsEnable())
			continue;

		(*iter)->SetShader();

		// Transform�� Shader�� �Ѱ��ش�.
		(*iter)->Render(0.f);

		switch ((*iter)->GetLightType())
		{
		case Light_Type::Dir:
		{
			m_LightDirShader->SetShader();
			m_DepthWriteDisable->SetState();

			//CONTEXT->IASetInputLayout(nullptr);

			UINT Offset = 0;
			CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			CONTEXT->IASetVertexBuffers(0, 0, nullptr, nullptr, &Offset);
			CONTEXT->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);

			CONTEXT->Draw(4, 0);

			m_DepthWriteDisable->ResetState();
		}
			break;
		case Light_Type::Point:
			m_LightShader->SetShader();

			m_FrontFaceCull->SetState();
			m_LightVolumeBackState->SetState();

			m_SphereMesh->Render();

			m_LightVolumeBackState->ResetState();
			m_FrontFaceCull->ResetState();

			m_CullNone->SetState();
			m_LightVolumeFrontState->SetState();

			m_SphereMesh->Render();

			m_CullNone->ResetState();
			m_LightVolumeFrontState->ResetState();
			break;
		case Light_Type::Spot:
			m_LightShader->SetShader();
			break;
		}
	}

	m_LightAccState->ResetState();
}
