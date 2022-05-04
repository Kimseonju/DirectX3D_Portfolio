
#include "ColliderBox3D.h"
#include "../Scene/Scene.h"
#include "../Collision.h"
#include "../Scene/SceneResource.h"
#include "../Render/RenderStateManager.h"
#include "ColliderSphere.h"
#include "../Input.h"

CColliderBox3D::CColliderBox3D()
{
	m_ColliderShape = Collider_Shape::Box3D;
	m_ColliderSpace = Collider_Space::Collider3D;
	m_ClassType = Component_Class_Type::ColliderBox3D;

	m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
	m_3DType = RT3D_Default;
	m_Info.Length[0] = 1.f;
	m_Info.Length[1] = 1.f;
	m_Info.Length[2] = 1.f;
}

CColliderBox3D::CColliderBox3D(const CColliderBox3D& com) :
	CCollider(com)
{
	m_Info = com.m_Info;
}

CColliderBox3D::~CColliderBox3D()
{
}

void CColliderBox3D::Start()
{
	CCollider::Start();

	SetWorldScale(m_Info.Length[0] * 2.f, m_Info.Length[1] * 2.f, m_Info.Length[2] * 2.f);

    // 생성과 동시에 각 점들의 위치정보를 저장해준다
    //CaculateVertexPos();
}

bool CColliderBox3D::Init()
{
	if (!CCollider::Init())
		return false;

	m_Info.Axis[AXIS_X] = Vector3(1.f, 0.f, 0.f);
	m_Info.Axis[AXIS_Y] = Vector3(0.f, 1.f, 0.f);
	m_Info.Axis[AXIS_Z] = Vector3(0.f, 0.f, 1.f);
	m_DebugMesh = m_pScene->GetResource()->FindMesh("CubeLine");

	m_WireFrame = CRenderStateManager::GetInst()->FindRenderState("WireFrame");
	return true;
}

void CColliderBox3D::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);
}

void CColliderBox3D::PostUpdate(float DeltaTime)
{
	CCollider::PostUpdate(DeltaTime);

    m_Info.Center = GetWorldPos() + m_Offset;

    m_Info.Axis[AXIS_X] = GetAxis(AXIS_X);

    m_Info.Axis[AXIS_Y] = GetAxis(AXIS_Y);

    m_Info.Axis[AXIS_Z] = GetAxis(AXIS_Z);

    Vector3	Pos[8] = {};
    //앞면
    Pos[0] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0] +
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] - m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    Pos[1] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0] +
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] - m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    Pos[2] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0] -
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] - m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    Pos[3] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0] -
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] - m_Info.Axis[AXIS_Z] * m_Info.Length[2];
    //뒷면
    Pos[4] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0] +
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] + m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    Pos[5] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0] +
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] + m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    Pos[6] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0] -
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] + m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    Pos[7] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0] -
        m_Info.Axis[AXIS_Y] * m_Info.Length[1] + m_Info.Axis[AXIS_Z] * m_Info.Length[2];



    m_Min.x = Pos[0].x;
    m_Min.y = Pos[0].y;
    m_Min.z = Pos[0].z;

    m_Max.x = Pos[0].x;
    m_Max.y = Pos[0].y;
    m_Max.z = Pos[0].z;

    for (int i = 1; i < 8; ++i)
    {
        if (m_Min.x > Pos[i].x)
            m_Min.x = Pos[i].x;

        if (m_Min.y > Pos[i].y)
            m_Min.y = Pos[i].y;

        if (m_Min.z > Pos[i].z)
            m_Min.z = Pos[i].z;

        if (m_Max.x < Pos[i].x)
            m_Max.x = Pos[i].x;

        if (m_Max.y < Pos[i].y)
            m_Max.y = Pos[i].y;


        if (m_Max.z < Pos[i].z)
            m_Max.z = Pos[i].z;
    }

    m_Info.Min = m_Min;
    m_Info.Max = m_Max;

    for (int i = 0; i < 8; ++i)
    {
        m_Info.PointPos[i] = Pos[i];
    }
   
    m_BottomPoint[0] = Pos[6];
    m_BottomPoint[1] = Pos[7];
    m_BottomPoint[2] = Pos[3];
    m_BottomPoint[3] = Pos[2];

    
   //m_BottomPoint[0] = Pos[7];
   //m_BottomPoint[1] = Pos[6];
   //m_BottomPoint[2] = Pos[2];
   //m_BottomPoint[3] = Pos[3];

    //CaculateVertexPos();
}

void CColliderBox3D::Collision(float DeltaTime)
{
	CCollider::Collision(DeltaTime);
}

void CColliderBox3D::PrevRender(float DeltaTime)
{
	CCollider::PrevRender(DeltaTime);
}

void CColliderBox3D::Render(float DeltaTime)
{
	CCollider::Render(DeltaTime);
}

CColliderBox3D* CColliderBox3D::Clone()
{
	return new CColliderBox3D(*this);
}

bool CColliderBox3D::Collision(CCollider* Dest)
{
	bool	result = false;

	switch (Dest->GetColliderShape())
	{
	case Collider_Shape::Box3D:
	{
		HitResult	DestResult = {};
		result = CCollision::CollisionBox3DToBox3D(m_HitResult, DestResult,
			this, (CColliderBox3D*)Dest);
		Dest->SetHitResult(DestResult);
        break;
	}
	case Collider_Shape::Sphere:
	{
		HitResult	DestResult = {};
		result = CCollision::CollisionBox3DToSphere(m_HitResult, DestResult,
			 this, (CColliderSphere*)Dest);
		Dest->SetHitResult(DestResult);
	}
		break;
	}
	return result;
}

bool CColliderBox3D::CollisionMouse(const Vector2& MousePos)
{
	m_MouseCollision = CCollision::CollisionBox3DPicking(m_HitResult, this,
		CInput::GetInst()->GetRay());

	return m_MouseCollision;
}

bool CColliderBox3D::CollisionRay(HitResult& _HitResult, const Vector3& Start, const Vector3& Dir, float Length)
{
	return  CCollision::CollisionBox3DRay(_HitResult, this, Start, Dir, Length);
}

std::vector<Vector2> CColliderBox3D::GetNormalVectorToLine(const Vector2& pointStart, const Vector2& pointEnd)
{
	std::vector<Vector2> normalVector;

	Vector2 Line = pointEnd - pointStart;

	Vector2 normal1 = { -Line.y, Line.x };
	Vector2 normal2 = { Line.y, -Line.x };

	normalVector.push_back(normal1);
	normalVector.push_back(normal2);

	return normalVector;

	return std::vector<Vector2>();
}

void CColliderBox3D::CaculateVertexPos()
{
  /*  m_Info.Center.x = GetWorldPos().x;
    m_Info.Center.y = GetWorldPos().y;
    m_Info.Center.z = GetWorldPos().z;


    m_Info.Axis[AXIS_X].x = GetAxis(AXIS_X).x;
    m_Info.Axis[AXIS_X].y = GetAxis(AXIS_X).y;
    m_Info.Axis[AXIS_X].z = GetAxis(AXIS_X).z;


    m_Info.Axis[AXIS_Y].x = GetAxis(AXIS_Y).x;
    m_Info.Axis[AXIS_Y].y = GetAxis(AXIS_Y).y;
    m_Info.Axis[AXIS_Y].z = GetAxis(AXIS_Y).z;

    m_Info.Axis[AXIS_Z].x = GetAxis(AXIS_Z).x;
    m_Info.Axis[AXIS_Z].y = GetAxis(AXIS_Z).y;
    m_Info.Axis[AXIS_Z].z = GetAxis(AXIS_Z).z;*/

    m_Info.Center = GetWorldPos() + m_Offset;

    m_Info.Axis[AXIS_X] = GetAxis(AXIS_X);
    m_Info.Axis[AXIS_Y] = GetAxis(AXIS_Y);
    m_Info.Axis[AXIS_Z] = GetAxis(AXIS_Z);

    Vector3   Pos[8] = {};

    // 전면 4개의 점 반시계 방향
    Pos[0] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0]
        + m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        - m_Info.Axis[AXIS_Z] * m_Info.Length[2];
    Pos[1] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0]
        + m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        - m_Info.Axis[AXIS_Z] * m_Info.Length[2];
    Pos[2] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0]
        - m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        - m_Info.Axis[AXIS_Z] * m_Info.Length[2];
    Pos[3] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0]
        - m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        - m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    Pos[4] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0]
        + m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        + m_Info.Axis[AXIS_Z] * m_Info.Length[2];
    Pos[5] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0]
        + m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        + m_Info.Axis[AXIS_Z] * m_Info.Length[2];
    Pos[6] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0]
        - m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        + m_Info.Axis[AXIS_Z] * m_Info.Length[2];
    Pos[7] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0]
        - m_Info.Axis[AXIS_Y] * m_Info.Length[1]
        + m_Info.Axis[AXIS_Z] * m_Info.Length[2];

    // 사각형을 구성하는 8개의 점의 위치정보를 저장
    for (int i = 0; i < 8; ++i)
    {
        m_Info.PointPos[i] = Pos[i];
    }

    // 바닥면 저장 (회전 상황을 아직 고려하지 않음)
    m_BottomPoint[0] = Pos[7];
    m_BottomPoint[1] = Pos[6];
    m_BottomPoint[2] = Pos[2];
    m_BottomPoint[3] = Pos[3];

    m_Min.x = Pos[0].x;
    m_Min.y = Pos[0].y;
    m_Min.z = Pos[0].z;

    m_Max.x = Pos[0].x;
    m_Max.y = Pos[0].y;
    m_Max.z = Pos[0].z;


    for (int i = 1; i < 8; ++i)
    {
        if (m_Min.x > Pos[i].x)
            m_Min.x = Pos[i].x;

        if (m_Min.y > Pos[i].y)
            m_Min.y = Pos[i].y;

        if (m_Min.z > Pos[i].z)
            m_Min.z = Pos[i].z;

        if (m_Max.x < Pos[i].x)
            m_Max.x = Pos[i].x;

        if (m_Max.y < Pos[i].y)
            m_Max.y = Pos[i].y;

        if (m_Max.z < Pos[i].z)
            m_Max.z = Pos[i].z;
    }

    m_Info.Min = m_Min;
    m_Info.Max = m_Max;
}

void CColliderBox3D::Save(FILE* pFile)
{
	CCollider::Save(pFile);
	fwrite(&m_Info.Length[0], sizeof(float), 1, pFile);
	fwrite(&m_Info.Length[1], sizeof(float), 1, pFile);
	fwrite(&m_Info.Length[2], sizeof(float), 1, pFile);
    
}

void CColliderBox3D::Load(FILE* pFile)
{
	CCollider::Load(pFile);
	
	fread(&m_Info.Length[0], sizeof(float), 1, pFile);
	fread(&m_Info.Length[1], sizeof(float), 1, pFile);
	fread(&m_Info.Length[2], sizeof(float), 1, pFile);
	SetExtent(m_Info.Length[0], m_Info.Length[1], m_Info.Length[2]);
}
