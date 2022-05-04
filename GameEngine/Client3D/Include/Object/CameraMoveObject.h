#pragma once
#include "Component\Camera.h"
#include "ClientObject.h"
struct CameraMoveInfo
{
	std::string Name;
	std::string NextName;
	bool	MoveStart;
	//현재위치에서 이어서 재생할건지에 대한 여부확인입니다.
	//이어재생할시 StartMoveY값을 0으로 해두셔야됩니다.
	CGameObject* Target;
	float start;
	float end;
	Vector3 StartRotation;
	Vector3 EndRotation;
	Vector3 StartMove;
	Vector3 EndMove;
	float StartMoveY; //타겟에서 +해줍니다.
	float EndMoveY; //타겟에서 -해줍니다. 반대방향도 가능
	float StartLength;
	float EndLength;
	float StartFadeIn;
	float EndFadeIn;
	float StartFadeOut;
	float EndFadeOut;
	Vector4 Fade;
	
	CameraMoveInfo() :
		start(0.f),
		EndMoveY(0.f),
		MoveStart(false),
		Fade(Vector4(1.f,1.f,1.f,1.f)),
		Target(nullptr),
		end(0.f),
		StartMoveY(0.f),
		StartLength(0.f),
		EndLength(0.f),
		StartFadeIn(0.f),
		EndFadeIn(0.f),
		StartFadeOut(0.f),
		EndFadeOut(0.f)
	{

	}
};


class CCameraMoveObject :
	public CClientObject
{
public:
	CCameraMoveObject();
	CCameraMoveObject(const CCameraMoveObject& com);
	virtual ~CCameraMoveObject();

protected:
	CCamera* m_Camera;
	Vector3 m_PrevPos;
	Vector3 m_PrevTargetPos;
	Vector3 m_PrevRotation;
	Vector3 m_TargetRotation;
	float m_Ratio;
	float m_RatioRotation;

	Vector3 m_Offset;
	float m_Length;

	bool m_Bool;
	std::unordered_map<std::string, CameraMoveInfo*> m_mapMoveInfo;
	CameraMoveInfo* m_MoveInfo;
	CCamera* m_PrevCamera;
	//CColliderBox3D* CollisionBox;
	bool m_FadeIn;

	bool m_FadeBlack;
	bool m_FadeWhite;
	
	bool m_FadeOutBlack;
	bool m_FadeOutWhite;
	float m_PauseTime;
	float m_PauseTimeMax;

	bool m_End;
	bool m_ChangeFade;
	bool m_ChangeFadePlay;
	//돌아갈때 작업
	
public:
	bool IsEnd()
	{
		return m_End;
	}
	
	std::unordered_map<std::string, CameraMoveInfo*>& GetMapMoveInfo()
	{
		return m_mapMoveInfo;
	}
	
	void StartCameraScene(const std::string& Name, CGameObject* Obj, bool Change =true, float PauseTimeMax = 0.f);
	void StartCameraScene_FadeInOut(const std::string& Name, CGameObject* Obj, bool Change =true, float PauseTimeMax = 0.f);
	void StartCameraScene_FadeInOutWhite(const std::string& Name, CGameObject* Obj, bool Change=true, float PauseTimeMax = 0.f);


	void AddCameraMoveInfo(const std::string& _Name, const std::string& _NextName, float EndTimer, CGameObject* _Target, const Vector3& _StartRotation
		, const Vector3& _EndRotation, float _StartMoveY=0.f, float _EndMoveY=0.f
		, float _StartLength=2.f, float _EndLength=2.f, float StartFadeIn=-1.f, float EndFadeIn=-1.f, float StartFadeOut=-1.f, float EndFadeOut=-1.f);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCameraMoveObject* Clone();
	
public:
	void CameraLeft(float Time);
	void CameraRight(float Time);

	CameraMoveInfo* FindMoveInfo(const std::string& Name);
};

