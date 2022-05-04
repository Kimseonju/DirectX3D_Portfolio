#include "LoadingThread2.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"

CLoadingThread2::CLoadingThread2()
{
}

CLoadingThread2::~CLoadingThread2()
{
}

void CLoadingThread2::Run()
{

	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_030_PlugEarsStart", "BowHunter/co01/co01_030_PlugEarsStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_031_PlugEarsLoop", "BowHunter/co01/co01_031_PlugEarsLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_032_PlugEarsToIdle", "BowHunter/co01/co01_032_PlugEarsToIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co01_052_RollToIdle", "BowHunter/co01/co01_052_RollToIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co02_066_CarvingStart", "BowHunter/co02/co02_066_CarvingStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co02_067_CarvingLoop", "BowHunter/co02/co02_067_CarvingLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co02_068_CarvingEnd", "BowHunter/co02/co02_068_CarvingEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co06_001_PickUpSlinger", "BowHunter/co06/co06_001_PickUpSlinger.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co06_004_SlingerAiming", "BowHunter/co06/co06_004_SlingerAiming.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co06_004_SlingerAimingRun", "BowHunter/co06/co06_004_SlingerAimingRun.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co06_007_SlingerReload", "BowHunter/co06/co06_007_SlingerReload.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "co06_031_ShotSlingerFront", "BowHunter/co06/co06_031_ShotSlingerFront.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_001_DrawedIdle", "BowHunter/wp11/wp11_001_DrawedIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_002_DrawWeapon", "BowHunter/wp11/wp11_002_DrawWeapon.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_003_Sheathe", "BowHunter/wp11/wp11_003_Sheathe.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_004_DrawedWalk", "BowHunter/wp11/wp11_004_DrawedWalk.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_005_ChargingWalk", "BowHunter/wp11/wp11_005_ChargingWalk.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_006_DrawedWalkAndSheathe", "BowHunter/wp11/wp11_006_DrawedWalkAndSheathe.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_007_WalkAndDrawWeapon", "BowHunter/wp11/wp11_007_WalkAndDrawWeapon.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_008_DrawedWeaponToCharging", "BowHunter/wp11/wp11_008_DrawedWeaponToCharging.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_009_DrawedBackStep", "BowHunter/wp11/wp11_009_DrawedBackStep.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_010_DrawedEvadeToDrawedWalk", "BowHunter/wp11/wp11_010_DrawedEvadeToDrawedWalk.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_012_DrawedEvade", "BowHunter/wp11/wp11_012_DrawedEvade.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_013_DrawedWalkStart", "BowHunter/wp11/wp11_013_DrawedWalkStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_016_DrawedWalkEnd", "BowHunter/wp11/wp11_016_DrawedWalkEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_017_ChargingIdleToCharginWalk", "BowHunter/wp11/wp11_017_ChargingIdleToCharginWalk.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_020_ChargingWalkEnd", "BowHunter/wp11/wp11_020_ChargingWalkEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_021_AimIdle", "BowHunter/wp11/wp11_021_AimIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_024_IdleToAimIdle", "BowHunter/wp11/wp11_024_IdleToAimIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_027_AimIdleToIdle", "BowHunter/wp11/wp11_027_AimIdleToIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_028_AimChargingWalkFront", "BowHunter/wp11/wp11_028_AimChargingWalkFront.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_028_AimWalkFront", "BowHunter/wp11/wp11_028_AimWalkFront.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_029_AimChargingWalkLeft", "BowHunter/wp11/wp11_029_AimChargingWalkLeft.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_029_AimWalkLeft", "BowHunter/wp11/wp11_029_AimWalkLeft.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_030_AimChargingWalkRight", "BowHunter/wp11/wp11_030_AimChargingWalkRight.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_030_AimWalkRight", "BowHunter/wp11/wp11_030_AimWalkRight.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_031_AimChargingWalkBack", "BowHunter/wp11/wp11_031_AimChargingWalkBack.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_031_AimWalkBack", "BowHunter/wp11/wp11_031_AimWalkBack.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_033_AimWalkRightEnd", "BowHunter/wp11/wp11_033_AimWalkRightEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_034_AimWalkLeftEnd", "BowHunter/wp11/wp11_034_AimWalkLeftEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_037_ChargingWalkRightEnd", "BowHunter/wp11/wp11_037_ChargingWalkRightEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_038_ChargingWalkLeftEnd", "BowHunter/wp11/wp11_038_ChargingWalkLeftEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_057_ChargingStartIdleFirst", "BowHunter/wp11/wp11_057_ChargingStartIdleFirst.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_058_DrawnWalkToChargingStart", "BowHunter/wp11/wp11_058_DrawnWalkToChargingStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_061_FullChargingIdleLoop", "BowHunter/wp11/wp11_061_FullChargingIdleLoop.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_064_ChargingStartIdle", "BowHunter/wp11/wp11_064_ChargingStartIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_065_ChargingFrontStep", "BowHunter/wp11/wp11_065_ChargingFrontStep.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_066_ChargingRightStep", "BowHunter/wp11/wp11_066_ChargingRightStep.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_067_ChargingLeftStep", "BowHunter/wp11/wp11_067_ChargingLeftStep.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_068_ChargingBackStep", "BowHunter/wp11/wp11_068_ChargingBackStep.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_070_ChargingBackStepShot", "BowHunter/wp11/wp11_070_ChargingBackStepShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_070_ChargingFrontStepShot", "BowHunter/wp11/wp11_070_ChargingFrontStepShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_070_ChargingLeftStepShot", "BowHunter/wp11/wp11_070_ChargingLeftStepShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_070_ChargingRightStepShot", "BowHunter/wp11/wp11_070_ChargingRightStepShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_072_ChargedShotIdle", "BowHunter/wp11/wp11_072_ChargedShotIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_073_FullChargedShotIdle", "BowHunter/wp11/wp11_073_FullChargedShotIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_077_PowerShot", "BowHunter/wp11/wp11_077_PowerShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_078_ArcShot", "BowHunter/wp11/wp11_078_ArcShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_079_AimStartArcShot", "BowHunter/wp11/wp11_079_AimStartArcShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_080_AimLoopArcShot", "BowHunter/wp11/wp11_080_AimLoopArcShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_087_Coating", "BowHunter/wp11/wp11_087_Coating.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_095_QuickShot", "BowHunter/wp11/wp11_095_QuickShot.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_096_DragonPiercerStart", "BowHunter/wp11/wp11_096_DragonPiercerStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_098_DragonPiercer2", "BowHunter/wp11/wp11_098_DragonPiercer2.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_109_DrawnEvadeFront", "BowHunter/wp11/wp11_109_DrawnEvadeFront.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_114_DrawnHitFront", "BowHunter/wp11/wp11_114_DrawnHitFront.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_139_DrawnSlingerAimWalkFront", "BowHunter/wp11/wp11_139_DrawnSlingerAimWalkFront.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_140_DrawnSlingerAimWalkLeft", "BowHunter/wp11/wp11_140_DrawnSlingerAimWalkLeft.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_141_DrawnSlingerAimWalkRight", "BowHunter/wp11/wp11_141_DrawnSlingerAimWalkRight.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_142_DrawnSlingerAimWalkBack", "BowHunter/wp11/wp11_142_DrawnSlingerAimWalkBack.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_143_DrawnSlingerAimWalkEnd", "BowHunter/wp11/wp11_143_DrawnSlingerAimWalkEnd.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_146_DrawnSlingerFire", "BowHunter/wp11/wp11_146_DrawnSlingerFire.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_148_DrawnSlingerAimIdle", "BowHunter/wp11/wp11_148_DrawnSlingerAimIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_149_DrawnSlingerAimToAimIdle", "BowHunter/wp11/wp11_149_DrawnSlingerAimToAimIdle.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_152_ThousandDragons", "BowHunter/wp11/wp11_152_ThousandDragons.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_156_AimIdleToDrawnSlingerAim", "BowHunter/wp11/wp11_156_AimIdleToDrawnSlingerAim.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_163_ClawBowAttackStart", "BowHunter/wp11/wp11_163_ClawBowAttackStart.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_164_ClawBowAttackToShootLand", "BowHunter/wp11/wp11_164_ClawBowAttackToShootLand.FBX");
	m_pScene->GetResource()->LoadMeshMultibyte(Mesh_Type::AnimationMesh, "wp11_165_ClawBowAttackToChargingLand", "BowHunter/wp11/wp11_165_ClawBowAttackToChargingLand.FBX");

}
