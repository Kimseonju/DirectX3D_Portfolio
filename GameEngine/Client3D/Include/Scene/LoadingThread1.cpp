#include "LoadingThread1.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"

CLoadingThread1::CLoadingThread1()
{
}

CLoadingThread1::~CLoadingThread1()
{
}

void CLoadingThread1::Run()
{
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "BodyVer4", "BowHunter/BodyVer4.FBX");
	//머리..??
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "FaceIs255boneAndHair", "BowHunter/FaceIs255boneAndHair.FBX");
	//애니메이션들
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_001_Idle1", "BowHunter/co00/co00_001_Idle1.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_008_CrouchIdle", "BowHunter\\co00\\co00_008_CrouchIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_007_Crouch", "BowHunter\\co00\\co00_007_Crouch.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_009_StandUp", "BowHunter/co00/co00_009_StandUp.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_010_CrouchWalkLoop", "BowHunter/co00/co00_010_CrouchWalkLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_012_DropDown", "BowHunter/co00/co00_012_DropDown.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_013_DropDownLand", "BowHunter/co00/co00_013_DropDownLand.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_015_JumpStart2", "BowHunter/co00/co00_015_JumpStart2.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_018_Land2", "BowHunter/co00/co00_018_Land2.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_019_FallLoop", "BowHunter/co00/co00_019_FallLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_020_LandAndIdle", "BowHunter/co00/co00_020_LandAndIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_024_WalkEnd3", "BowHunter/co00/co00_024_WalkEnd3.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_025_ClimbMoveUp", "BowHunter/co00/co00_025_ClimbMoveUp.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_026_ClimbMoveDown", "BowHunter/co00/co00_026_ClimbMoveDown.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_027_ClimbStart", "BowHunter/co00/co00_027_ClimbStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_032_SpecialEvadeStart", "BowHunter/co00/co00_032_SpecialEvadeStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_033_SpecialEvadeEnd", "BowHunter/co00/co00_033_SpecialEvadeEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_034_Kick", "BowHunter/co00/co00_034_Kick.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_052_CilmbFinish", "BowHunter/co00/co00_052_CilmbFinish.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_055_UpStair3", "BowHunter/co00/co00_055_UpStair3.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_056_ClimbMoveRightQuick", "BowHunter/co00/co00_056_ClimbMoveRightQuick.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_057_ClimbMoveLeftQuick", "BowHunter/co00/co00_057_ClimbMoveLeftQuick.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_058_ClimbDownStart", "BowHunter/co00/co00_058_ClimbDownStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_059_ClimbMoveDownEnd", "BowHunter/co00/co00_059_ClimbMoveDownEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_060_ClimbMoveUpQuick", "BowHunter/co00/co00_060_ClimbMoveUpQuick.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_062_ClimbJump", "BowHunter/co00/co00_062_ClimbJump.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_063_ClimbMoveRight", "BowHunter/co00/co00_063_ClimbMoveRight.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_064_ClimbMoveLeft", "BowHunter/co00/co00_064_ClimbMoveLeft.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_084_ClimbIdle", "BowHunter/co00/co00_084_ClimbIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_088_WalkStart", "BowHunter/co00/co00_088_WalkStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_094_RunStart", "BowHunter/co00/co00_094_RunStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_104_Evade", "BowHunter/co00/co00_104_Evade.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_105_SlideStart", "BowHunter/co00/co00_105_SlideStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_106_SlideLoop", "BowHunter/co00/co00_106_SlideLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_113_LandAndRun2", "BowHunter/co00/co00_113_LandAndRun2.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_119_SlideAndRun2", "BowHunter/co00/co00_119_SlideAndRun2.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_134_ClimbStart", "BowHunter/co00/co00_134_ClimbStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_141_WalkFromRun", "BowHunter/co00/co00_141_WalkFromRun.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_145_SpecialClimb", "BowHunter/co00/co00_145_SpecialClimb.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_148_CrawlStart", "BowHunter/co00/co00_148_CrawlStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_149_CrawlLoop", "BowHunter/co00/co00_149_CrawlLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_150_CrouchFromCrawl", "BowHunter/co00/co00_150_CrouchFromCrawl.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_151_CrawlBackLoop", "BowHunter/co00/co00_151_CrawlBackLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_152_CrawlBackEnd", "BowHunter/co00/co00_152_CrawlBackEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_153_CrawlIdle", "BowHunter/co00/co00_153_CrawlIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_161_WalkLoop", "BowHunter/co00/co00_161_WalkLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_162_RunLoop", "BowHunter/co00/co00_162_RunLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_165_SlideFromRun", "BowHunter/co00/co00_165_SlideFromRun.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_166_RunQuickLoop", "BowHunter/co00/co00_166_RunQuickLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_173_LandAndRun3", "BowHunter/co00/co00_173_LandAndRun3.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_174_HitFly", "BowHunter/co00/co00_174_HitFly.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_191_RunEnd1", "BowHunter/co00/co00_191_RunEnd1.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co00_192_CrouchWalkEnd", "BowHunter/co00/co00_192_CrouchWalkEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_001_TrippingByFront", "BowHunter/co01/co01_001_TrippingByFront.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_003_RollByFrontStart", "BowHunter/co01/co01_003_RollByFrontStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_004_RollOverByFrontEnd", "BowHunter/co01/co01_004_RollOverByFrontEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_021_RollOverLoop", "BowHunter/co01/co01_021_RollOverLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_022_RollByFrontEnd", "BowHunter/co01/co01_022_RollByFrontEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_023_RollOverToIdle", "BowHunter/co01/co01_023_RollOverToIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_025_TrippingToIdle", "BowHunter/co01/co01_025_TrippingToIdle.FBX");
}
