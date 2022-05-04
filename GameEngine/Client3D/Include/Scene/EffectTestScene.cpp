#include "EffectTestScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "Scene/Viewport.h"
#include "GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/LightComponent.h"
#include "Component/BillboardComponent.h"
#include "Resource/Animation.h"
#include "../Object/MainLandScape.h"
#include "../Object/Player.h"
#include "Resource/Material.h"
#include "../Object/Monster.h"
#include "../Object/Effect.h"


CEffectTestScene::CEffectTestScene()
{
}

CEffectTestScene::~CEffectTestScene()
{
}

bool CEffectTestScene::Init()
{
	if (!CreateMaterial())
		return false;

	//m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::StaticMesh, "eff_Attack", "Effect/eff_Ring.fbx");

	CEffect* pEffect = m_pScene->SpawnObject<CEffect>("eff_Fire");
	pEffect->SetWorldPos(2.f,2.f,4.f);

	CMainLandScape* LandScape = m_pScene->SpawnObject<CMainLandScape>("LandScape");
	LandScape->SetWorldPos(-10.f, -10.f, -10.f);

	return true;
}

void CEffectTestScene::Start()
{
	// 나중에 테스트씬용 카메라로 따로 제작하기 

}

bool CEffectTestScene::CreateMaterial()
{
	m_pScene->GetResource()->CreateMaterial("MainLandScape");

	CMaterial* Mtrl = m_pScene->GetResource()->FindMaterial("MainLandScape");

	Mtrl->AddTexture("MainLandScapeDefault", TEXT("LandScape/Terrain_Pebbles_01.dds"));
	Mtrl->SetTextureLink("MainLandScapeDefault", Texture_Link::BaseTexture);

	Mtrl->AddTexture("MainLandScapeDefaultNormal", TEXT("LandScape/Terrain_Pebbles_01_NRM.bmp"));
	Mtrl->SetTextureLink("MainLandScapeDefaultNormal", Texture_Link::NormalTexture);

	Mtrl->AddTexture("MainLandScapeDefaultSpecular", TEXT("LandScape/Terrain_Pebbles_01_SPEC.bmp"));
	Mtrl->SetTextureLink("MainLandScapeDefaultSpecular", Texture_Link::SpecularTexture);

	std::vector<const TCHAR*>	vecAlbedo;
	std::vector<const TCHAR*>	vecNormal;
	std::vector<const TCHAR*>	vecSpecular;
	std::vector<const TCHAR*>	vecAlpha;

	TCHAR* FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cliff05.dds"));
	vecAlbedo.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cave_01.dds"));
	vecAlbedo.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/ROCK_01+MOSS_COLOR.png"));
	vecAlbedo.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/Terrain_Cliff_15_Large.dds"));
	vecAlbedo.push_back(FileName);

	Mtrl->AddTextureArray("MainLandScapeAlbedo", vecAlbedo);
	Mtrl->SetTextureLink("MainLandScapeAlbedo", Texture_Link::CustomTexture);
	Mtrl->SetTextureRegister("MainLandScapeAlbedo", 30);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cliff05_NRM.bmp"));
	vecNormal.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cave_01_NRM.bmp"));
	vecNormal.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/ROCK_01+MOSS_NRM.png"));
	vecNormal.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/Terrain_Cliff_15_Large_NRM.bmp"));
	vecNormal.push_back(FileName);

	Mtrl->AddTextureArray("MainLandScapeNormal", vecNormal);
	Mtrl->SetTextureLink("MainLandScapeNormal", Texture_Link::CustomTexture);
	Mtrl->SetTextureRegister("MainLandScapeNormal", 31);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cliff05_SPEC.bmp"));
	vecSpecular.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/BD_Terrain_Cave_01_SPEC.bmp"));
	vecSpecular.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/ROCK_01+MOSS_SPEC.png"));
	vecSpecular.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/Terrain_Cliff_15_Large_SPEC.bmp"));
	vecSpecular.push_back(FileName);

	Mtrl->AddTextureArray("MainLandScapeSpecular", vecSpecular);
	Mtrl->SetTextureLink("MainLandScapeSpecular", Texture_Link::CustomTexture);
	Mtrl->SetTextureRegister("MainLandScapeSpecular", 32);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/RoadAlpha.bmp"));
	vecAlpha.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/SandBaseAlpha.bmp"));
	vecAlpha.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/WaterBaseAlpha.bmp"));
	vecAlpha.push_back(FileName);

	FileName = new TCHAR[MAX_PATH];
	memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FileName, TEXT("LandScape/StonAlpha.bmp"));
	vecAlpha.push_back(FileName);

	Mtrl->AddTextureArray("MainLandScapeAlpha", vecAlpha);
	Mtrl->SetTextureLink("MainLandScapeAlpha", Texture_Link::CustomTexture);
	Mtrl->SetTextureRegister("MainLandScapeAlpha", 33);


	Mtrl->SetSpecularPower(2.f);
	Mtrl->SetAmbientColor(1.f, 1.f, 1.f, 1.f);

	Mtrl->SetShader("LandScapeShader");

	size_t	Size = vecAlbedo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE_ARRAY(vecAlbedo[i]);
		SAFE_DELETE_ARRAY(vecNormal[i]);
		SAFE_DELETE_ARRAY(vecSpecular[i]);
		SAFE_DELETE_ARRAY(vecAlpha[i]);
	}

	m_pScene->GetResource()->CreateMaterial("BillboardTest");

	Mtrl = m_pScene->GetResource()->FindMaterial("BillboardTest");

	Mtrl->AddTexture("BillboardTest", TEXT("teemo.png"));
	Mtrl->SetTextureLink("BillboardTest", Texture_Link::BaseTexture);

	Mtrl->SetShader("BillboardShader");

	return true;
}