#include "CameraMoveObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
#include "Custom/CollisionRay.h"
#include "../PublicData.h"
#include "Input.h"
#include "../UI/FadeInOut_White.h"
#include "../UI/FadeInOutUI.h"
#include "../UI/GameClearUI.h"
#include "Engine.h"
#include "../StageManager.h"
CCameraMoveObject::CCameraMoveObject() :
	m_PauseTime(0.f), 
	m_PauseTimeMax(0.f),
	m_End(false),
	m_ChangeFade(true),
	m_Camera(nullptr),
	m_Ratio(0.f),
	m_RatioRotation(0.f),
	m_Length(0.f),
	m_Bool(false),
	m_MoveInfo(nullptr),
	m_PrevCamera(nullptr),
	m_FadeIn(false),
	m_FadeBlack(false),
	m_FadeWhite(false),
	m_FadeOutBlack(false),
	m_FadeOutWhite(false),
	m_ChangeFadePlay(false)
{
	m_ClientClassType = ClientClassType::CameraMoveObject;
}

CCameraMoveObject::CCameraMoveObject(const CCameraMoveObject& com)
	: CClientObject(com)
{
	m_Camera = (CCamera*)FindSceneComponent("CameraMove");
	m_Camera->SetTransformState(Transform_State::None);
	auto iter = com.m_mapMoveInfo.begin();
	auto iterEnd = com.m_mapMoveInfo.end();
	m_Ratio = com.m_Ratio;
	m_RatioRotation = com.m_RatioRotation;
	m_Length = com.m_Length;
	m_MoveInfo = com.m_MoveInfo;
	m_PrevCamera = com.m_PrevCamera;
	m_PauseTime = com.m_PauseTime;
	m_PauseTimeMax = com.m_PauseTimeMax;

	for (; iter != iterEnd; ++iter)
	{
		AddCameraMoveInfo((*iter).second->Name, (*iter).second->NextName, (*iter).second->end, (*iter).second->Target,
			(*iter).second->StartRotation, (*iter).second->EndRotation,(*iter).second->StartMoveY, (*iter).second->EndMoveY,
			(*iter).second->StartLength, (*iter).second->EndLength, (*iter).second->StartFadeIn, (*iter).second->EndFadeIn,
			(*iter).second->StartFadeOut, (*iter).second->EndFadeOut);
		
	}
}

CCameraMoveObject::~CCameraMoveObject()
{
	auto iter = m_mapMoveInfo.begin();
	auto iterEnd = m_mapMoveInfo.end();


	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapMoveInfo.clear();
}


void CCameraMoveObject::StartCameraScene(const std::string& Name, CGameObject* Obj, bool ChangeFade, float PauseTimeMax)
{
	CameraMoveInfo* Info = FindMoveInfo(Name);
	if (!Info)
	{
		return;
	}
	m_PauseTimeMax = PauseTimeMax;
	m_ChangeFade = ChangeFade;
	m_MoveInfo = Info;
	m_MoveInfo->Target = Obj;
	m_PauseTime = 0.f;
	m_End = false;
	m_FadeIn = true;
	m_FadeOutBlack = true;
	m_ChangeFadePlay = false;
	m_pScene = CSceneManager::GetInst()->GetScene();
	m_PrevCamera = m_pScene->GetCameraManager()->GetCurrentCamera();
	m_pScene->GetCameraManager()->SetCurrentCamera(m_Camera);
	
}

void CCameraMoveObject::StartCameraScene_FadeInOut(const std::string& Name, CGameObject* Obj, bool ChangeFade, float PauseTimeMax)
{
	CameraMoveInfo* Info = FindMoveInfo(Name);
	if (!Info)
	{
		return;
	}
	Info->start = 0.f;
	Info->MoveStart = false;
	m_PauseTimeMax = PauseTimeMax;
	m_ChangeFade = ChangeFade;
	m_MoveInfo = Info;
	m_MoveInfo->Target = Obj;
	m_PauseTime = 0.f;
	m_pScene = CSceneManager::GetInst()->GetScene();
	m_PrevCamera = m_pScene->GetCameraManager()->GetCurrentCamera();
	m_End = false;
	m_FadeIn = true;
	m_FadeOutBlack = true;
	m_ChangeFadePlay = false;
	CFadeInOutUI* FadeInout = (CFadeInOutUI*)CUIManager::GetInst()->FindWidgetWindow("FadeInOutUI");
	FadeInout->SetFadeIn();
	m_FadeBlack = true;
}

void CCameraMoveObject::StartCameraScene_FadeInOutWhite(const std::string& Name, CGameObject* Obj, bool ChangeFade, float PauseTimeMax)
{
	CameraMoveInfo* Info = FindMoveInfo(Name);
	if (!Info)
	{
		return;
	}
	Info->start = 0.f;
	Info->MoveStart = false;
	m_PauseTimeMax = PauseTimeMax;
	m_ChangeFade = ChangeFade;
	m_MoveInfo = Info;
	m_MoveInfo->Target = Obj;
	m_PauseTime = 0.f;
	m_pScene = CSceneManager::GetInst()->GetScene();
	m_PrevCamera = m_pScene->GetCameraManager()->GetCurrentCamera();
	m_End = false;
	m_FadeIn = true;
	m_FadeOutWhite = true;
	m_FadeWhite = true;
	m_ChangeFadePlay = false;
	CFadeInOut_White* FadeInout = (CFadeInOut_White*)CUIManager::GetInst()->FindWidgetWindow("FadeInOut_WhiteUI");
	FadeInout->SetFadeIn();
	
}

void CCameraMoveObject::AddCameraMoveInfo(const std::string& _Name, const std::string& _NextName, float _EndTimer, CGameObject* _Target,
	const Vector3& _StartRotation, const Vector3& _EndRotation,	float _StartMoveY, float _EndMoveY, float _StartLength, 
	float _EndLength, float _StartFadeIn, float _EndFadeIn, float _StartFadeOut, float _EndFadeOut)
{
	CameraMoveInfo* Info = new CameraMoveInfo;
	Info->Name = _Name;
	Info->NextName = _NextName;
	Info->end = _EndTimer;
	Info->Target = _Target;
	Info->StartRotation = _StartRotation;
	Info->EndRotation = _EndRotation;
	Info->StartMoveY = _StartMoveY;
	Info->EndMoveY = _EndMoveY;
	Info->StartLength = _StartLength;
	Info->EndLength = _EndLength;
	Info->StartFadeIn = _StartFadeIn;
	Info->EndFadeIn = _EndFadeIn;
	Info->StartFadeOut = _StartFadeOut;
	Info->EndFadeOut = _EndFadeOut;

	m_mapMoveInfo.insert(std::make_pair(Info->Name, Info));
}

void CCameraMoveObject::Start()
{
	CClientObject::Start();
}

bool CCameraMoveObject::Init()
{
	if (!CClientObject::Init())
		return false;
	m_Camera = CreateSceneComponent<CCamera>("CameraMove");
	SetRootComponent(m_Camera);
	m_Camera->SetTransformState(Transform_State::None);

	AddCameraMoveInfo("SakuraVictory1", "SakuraVictory2", 0.6f, nullptr, Vector3(-2.3951f, -35.722f, -4.5f), Vector3(-2.8627f, -73.40f, -4.5f),
		1.5f, 0.f, 0.3f, 0.55f);

	AddCameraMoveInfo("SakuraVictory2", "", 3.f, nullptr, Vector3(-2.3951f, 17.20f, -4.5f), Vector3(-2.3951f, -35.722f, -4.5f),
		1.5f, 0.f, 0.55f, 0.55f);

	//아래왼쪽
	AddCameraMoveInfo("Wendy1", "Wendy2", 3.f, nullptr, Vector3(3.6312f, 5.8509f, 0.f), Vector3(2.1611f, -48.5176f, 0.f),
		3.f, 1.5f, 1.5f, 1.5f);
	//바라보기
	AddCameraMoveInfo("Wendy2", "Wendy3", 1.3f, nullptr, Vector3(3.6312f, 5.8509f, 0.f), Vector3(3.6312f, 5.8509f, 0.f),
		1.5f, 0.f, 1.5f, 1.5f);
	//살짝아래
	AddCameraMoveInfo("Wendy3", "Wendy4", 0.8f, nullptr, Vector3(3.6312f, 5.8509f, 0.f), Vector3(3.6312f, 5.8509f, 0.f),
		1.5f, 0.2f, 1.5f, 1.5f);
	//조금가까이
	AddCameraMoveInfo("Wendy4", "", 1.f, nullptr, Vector3(3.6312f, 5.8509f, 0.f), Vector3(3.6312f, 5.8509f, 0.f),
		1.3f, 0.1f, 1.5f, 1.4f);
	return true;
}

void CCameraMoveObject::Update(float DeltaTime)
{
	CClientObject::Update(DeltaTime);
	if (m_FadeIn)
	{
		if (m_FadeOutBlack)
		{
			CFadeInOut_White* FadeInout=(CFadeInOut_White*)CUIManager::GetInst()->FindWidgetWindow("FadeInOutUI");
			if (!FadeInout->IsFadeIn())
			{
				m_FadeIn = false;
				m_FadeOutBlack = false;
				FadeInout->SetFadeOut();
				m_pScene->GetCameraManager()->SetCurrentCamera(m_Camera);
				CClientObject* Obj = dynamic_cast<CClientObject*>(m_MoveInfo->Target);
				Obj->Enable(true);
				CUIManager::GetInst()->FindWidgetWindow("PlayerUI")->Enable(false);
				if (Obj)
				{
					Obj->CameraAction();
				}
			}
		}
		else if (m_FadeOutWhite)
		{
			CFadeInOutUI* FadeInout = (CFadeInOutUI*)CUIManager::GetInst()->FindWidgetWindow("FadeInOut_WhiteUI");
			if (!FadeInout->IsFadeIn())
			{
				m_FadeIn = false;
				m_FadeOutWhite = false;
				FadeInout->SetFadeOut();
				m_pScene->GetCameraManager()->SetCurrentCamera(m_Camera);
				CClientObject* Obj = dynamic_cast<CClientObject*>(m_MoveInfo->Target);
				Obj->Enable(true);
				//점수판 스폰도시키기
				CUIManager::GetInst()->FindWidgetWindow("PlayerUI")->Enable(false);
				if (Obj)
				{
					Obj->CameraAction();
				}
			}
		}
		return;
	}

	Vector3 Pos = Vector3::Zero;
	Vector3 Rot = Vector3::Zero;
	if (m_MoveInfo)
	{
		m_MoveInfo->start += DeltaTime;
		if (m_MoveInfo->start >= m_MoveInfo->end)
		{
			if (!m_MoveInfo->NextName.empty())
			{
				CameraMoveInfo* Info = FindMoveInfo(m_MoveInfo->NextName);
				Info->Target = m_MoveInfo->Target;
				if (Info)
				{
					m_MoveInfo = Info;
					m_MoveInfo->start = 0.f;
					m_MoveInfo->MoveStart = false;
					Pos = m_MoveInfo->Target->GetWorldPos();
					Pos.y += m_MoveInfo->StartMoveY;
					m_MoveInfo->StartMove = Pos;
					Pos.y -= m_MoveInfo->EndMoveY;
					m_MoveInfo->EndMove = Pos;
					//이동값 설정 완료
					Pos = m_MoveInfo->StartMove;
					Rot = m_MoveInfo->StartRotation;
				}
			}
			else
			{
				if (m_MoveInfo->Name == "SakuraVictory2" && !CEngine::GetInst()->IsEditor())
				{
					CGameClearUI* ClearUI = (CGameClearUI *)CUIManager::GetInst()->FindWidgetWindow("GameClearUI");
					ClearUI->Enable(true);
					CStageManager* Manager=CStageManager::GetInst();
					ClearUI->SetComboText(Manager->GetHitComboMax());
					ClearUI->SetClearTimeText((int)Manager->GetPlayTime());
				}
				m_PauseTime += DeltaTime;
				if (m_PauseTime > m_PauseTimeMax)
				{
					
					m_End = true;
					if (CEngine::GetInst()->IsEditor())
					{
						m_pScene->GetCameraManager()->SetCurrentCamera(m_PrevCamera);
						return;
					}
					if (m_ChangeFadePlay)
					{
						if (m_FadeBlack)
						{
							CFadeInOut_White* FadeInout = (CFadeInOut_White*)CUIManager::GetInst()->FindWidgetWindow("FadeInOutUI");
							if (!FadeInout->IsFadeIn()&&!CEngine::GetInst()->IsEditor())
							{
								m_pScene->GetCameraManager()->SetCurrentCamera(m_PrevCamera);
								FadeInout->SetFadeOut();
								m_MoveInfo = nullptr;
								CUIManager::GetInst()->FindWidgetWindow("PlayerUI")->Enable(true);
								return;
							}
						}
						if (m_FadeWhite)
						{
							CFadeInOut_White* FadeInout = (CFadeInOut_White*)CUIManager::GetInst()->FindWidgetWindow("FadeInOut_WhiteUI");
							if (!FadeInout->IsFadeIn())
							{
								m_pScene->GetCameraManager()->SetCurrentCamera(m_PrevCamera);
								FadeInout->SetFadeOut();
								m_MoveInfo = nullptr;
								return;
							}
						}
					}
					else if (m_ChangeFade)
					{
						if (m_FadeBlack)
						{
							CFadeInOut_White* FadeInout = (CFadeInOut_White*)CUIManager::GetInst()->FindWidgetWindow("FadeInOutUI");
							FadeInout->SetFadeIn();
							m_ChangeFadePlay = true;
							m_ChangeFade = false;
						}
						if (m_FadeWhite)
						{
							CFadeInOut_White* FadeInout = (CFadeInOut_White*)CUIManager::GetInst()->FindWidgetWindow("FadeInOut_WhiteUI");
							FadeInout->SetFadeIn();
							m_ChangeFadePlay = true;
							m_ChangeFade = false;
						}
					}
					else
					{
						m_pScene->GetCameraManager()->SetCurrentCamera(m_PrevCamera);
						m_MoveInfo = nullptr;
						return;
					}
				}
			}
		}

		//카메라 이름에 카운트확인해서 임의로 효과넣기..... 일단은..
		if (m_MoveInfo->Name == "")
		{

		}
		else
		{
			float Percent = (m_MoveInfo->start / m_MoveInfo->end);
			if (Percent >= 1.f)
				Percent = 1.f;
			CGameObject* Target = m_MoveInfo->Target;
			if (!m_MoveInfo->MoveStart)
			{
				m_MoveInfo->start = 0.f;
				m_MoveInfo->MoveStart = true;
				Pos = Target->GetWorldPos();
				Pos.y += m_MoveInfo->StartMoveY;
				m_MoveInfo->StartMove = Pos;
				Pos.y -= m_MoveInfo->EndMoveY;
				m_MoveInfo->EndMove = Pos;
				//이동값 설정 완료
				Pos = m_MoveInfo->StartMove;
				Rot = m_MoveInfo->EndRotation+Target->GetWorldRotation();
			}
			else
			{
				Pos = m_MoveInfo->StartMove;
				float y = m_MoveInfo->StartMove.y;
				Pos.y -= m_MoveInfo->EndMoveY * Percent;
				//카메라는 역으로돌아가있으므로 반대로계산
				Rot = Vector3::Lerp3D(m_MoveInfo->EndRotation + Target->GetWorldRotation(), m_MoveInfo->StartRotation + Target->GetWorldRotation(), Percent);
			}
			SetWorldPos(Pos);
			SetWorldRotation(Rot);
			//회전과 방향을 잡았다. 이제 거리를 계산한다.
			float StartLength = m_MoveInfo->StartLength;
			float EndLength = m_MoveInfo->EndLength;
			float RtnLength = m_MoveInfo->EndLength - m_MoveInfo->StartLength;

			RtnLength = StartLength + RtnLength * Percent;

			Vector3 NextPos = Pos + m_Offset + GetAxis(AXIS_Z) * -RtnLength;
			SetWorldPos(NextPos);
		}
		
	}
}

void CCameraMoveObject::PostUpdate(float DeltaTime)
{
	CClientObject::PostUpdate(DeltaTime);
}

void CCameraMoveObject::Collision(float DeltaTime)
{
	CClientObject::Collision(DeltaTime);
}

void CCameraMoveObject::PrevRender(float DeltaTime)
{
	CClientObject::PrevRender(DeltaTime);
}

void CCameraMoveObject::Render(float DeltaTime)
{
	CClientObject::Render(DeltaTime);
}

CCameraMoveObject* CCameraMoveObject::Clone()
{
	return new CCameraMoveObject(*this);
}

void CCameraMoveObject::CameraLeft(float Time)
{
	AddRelativeRotationY(90.f * Time);
}

void CCameraMoveObject::CameraRight(float Time)
{
	AddRelativeRotationY(-90.f * Time);
}

CameraMoveInfo* CCameraMoveObject::FindMoveInfo(const std::string& Name)
{
	auto iter = m_mapMoveInfo.find(Name);
	if (iter == m_mapMoveInfo.end())
		return nullptr;

	return iter->second;
}
