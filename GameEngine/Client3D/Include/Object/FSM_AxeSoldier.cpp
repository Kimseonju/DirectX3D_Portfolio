#include "AxeSoldier.h"
#include "../PublicData.h"
#include "Player.h"
#include "Scene/Scene.h"
void CAxeSoldier::CreateFSM()
{
	m_FSM.CreateState("Axe_Spawn",this, &CAxeSoldier::Axe_Spawn_Stay, &CAxeSoldier::Axe_Spawn_Start, &CAxeSoldier::Axe_Spawn_End);
	m_FSM.CreateState("Axe_Idle", this, &CAxeSoldier::Axe_Idle_Stay, &CAxeSoldier::Axe_Idle_Start, &CAxeSoldier::Axe_Idle_End);
	m_FSM.CreateState("Axe_Move", this, &CAxeSoldier::Axe_Move_Stay, &CAxeSoldier::Axe_Move_Start, &CAxeSoldier::Axe_Move_End);
	m_FSM.CreateState("Axe_AttackHub", this, &CAxeSoldier::Axe_AttackHub_Stay, &CAxeSoldier::Axe_AttackHub_Start, &CAxeSoldier::Axe_AttackHub_End);
	m_FSM.CreateState("Axe_HitHub", this, &CAxeSoldier::Axe_HitHub_Stay, &CAxeSoldier::Axe_HitHub_Start, &CAxeSoldier::Axe_HitHub_End);
	m_FSM.CreateState("Axe_Dead", this, &CAxeSoldier::Axe_Dead_Stay, &CAxeSoldier::Axe_Dead_Start, &CAxeSoldier::Axe_Dead_End);
	//m_FSM.CreateState("Axe_NAttack", this, &CAxeSoldier::Axe_NAttack_Stay, &CAxeSoldier::Axe_NAttack_Start, &CAxeSoldier::Axe_NAttack_End);
	//m_FSM.CreateState("Axe_FAttack", this, &CAxeSoldier::Axe_FAttack_Stay, &CAxeSoldier::Axe_FAttack_Start, &CAxeSoldier::Axe_FAttack_End);
	//m_FSM.CreateState("Axe_FAttack2", this, &CAxeSoldier::Axe_FAttack2_Stay, &CAxeSoldier::Axe_FAttack2_Start, &CAxeSoldier::Axe_FAttack2_End);
	//m_FSM.CreateState("Axe_TAttack", this, &CAxeSoldier::Axe_TAttack_Stay, &CAxeSoldier::Axe_TAttack_Start, &CAxeSoldier::Axe_TAttack_End);
	//m_FSM.CreateState("Axe_RAttack", this, &CAxeSoldier::Axe_RAttack_Stay, &CAxeSoldier::Axe_RAttack_Start, &CAxeSoldier::Axe_RAttack_End);

	m_FSM.ChangeState("Axe_Spawn");
}



//////////////////////////////////////////////////////////////////////	Spawn
void CAxeSoldier::Axe_Spawn_Start()
{
	m_AxeCurState = Axe_State::Spawn;

	LookAtObject(CPublicData::GetInst()->m_CurPlayer);
	LookAtObjectActive(true);

	SetWorldRotationY(0);

	m_SpawnTimer1 = 1.f;
	m_SpawnTimer2 = 2.f;
	m_SpawnEffect = m_pScene->SpawnObject<CMonsterSpawnEffect>("Effect");
	m_SpawnEffect->SetWorldPos(GetWorldPos().x, GetWorldPos().y + 0.1f, GetWorldPos().z);
}
void CAxeSoldier::Axe_Spawn_Stay()
{
	m_SpawnEffect->ManualUpdate(m_DeltaTime);

	m_SpawnTimer1 -= m_DeltaTime;
	if (0 >= m_SpawnTimer1)
	{
		m_SpawnTimer1 = 0.f;

		m_SpawnTimer2 -= m_DeltaTime;
		m_Mesh->AddWorldPos(0.f, m_DeltaTime, 0.f);
		if (0 >= m_SpawnTimer2)
		{
			m_SpawnEffect->EffectDeath();
			m_FSM.ChangeState("Axe_Idle");
		}
	}
}
void CAxeSoldier::Axe_Spawn_End()
{
	LookAtObjectActive(false);
}


//////////////////////////////////////////////////////////////////////	Idle
void CAxeSoldier::Axe_Idle_Start()
{
	// Reset State
	{
		m_AxeCurState = Axe_State::Idle;
		m_AxeCurAttState = Axe_AttState::None;
		m_NextAttack = Axe_AttState::None;
		m_MoveState = Axe_MoveState::None;
		m_BMoveState = Axe_MoveState::None;
		m_HitState = Axe_HitState::None;
		m_HitAniState = Axe_HitAniState::None;
	}
	m_Animation->ChangeAnimation("AxeSoldier_Idle");
}
void CAxeSoldier::Axe_Idle_Stay()
{
	m_FSM.ChangeState("Axe_Move");
}
void CAxeSoldier::Axe_Idle_End()
{
}


//////////////////////////////////////////////////////////////////////	Move
void CAxeSoldier::Axe_Move_Start()
{
	m_AxeCurState = Axe_State::Move;
	m_Animation->ChangeAnimation("AxeSoldier_Run");

	LookAtObject(CPublicData::GetInst()->m_CurPlayer);
	LookAtObjectActive(true);

}
void CAxeSoldier::Axe_Move_Stay()
{
	switch (m_MoveState)
	{
	case Axe_MoveState::None:
	{
		if (m_BMoveState != m_MoveState)
		{
			m_BMoveState = m_MoveState;
			m_Animation->ChangeAnimation("AxeSoldier_Run");
		}
		// Vector3 PlayerPos = CPublicData::GetInst()->m_CurPlayer->GetWorldPos();
		// Vector3 Vec = PlayerPos - GetWorldPos();
		// AddRelativePos(GetAxis(AXIS_Z) * -5.f * m_DeltaTime);
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());

		if (Axe_Follow_Dir >= Dir)
		{
			// 다음 총 움직일 양
			m_MoveRandom = GetRandom((int)Axe_MoveState::None + 1, (int)Axe_MoveState::End - 1);
			// 다음 움직일 애니메이션
			m_MoveState = (Axe_MoveState)GetRandom((int)Axe_MoveState::None + 2, (int)Axe_MoveState::End - 1);
		}
	}
		break;
	case Axe_MoveState::Front:
	{
		if (m_BMoveState != m_MoveState)
		{
			m_BMoveState = m_MoveState;
			m_Animation->ChangeAnimation("AxeSoldier_Run");
		}
		// Vector3 PlayerPos = CPublicData::GetInst()->m_CurPlayer->GetWorldPos();
		// Vector3 Vec = PlayerPos - GetWorldPos();
		// AddRelativePos(GetAxis(AXIS_Z) * -5.f * m_DeltaTime);
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());

		switch (m_AxeCurAttState)
		{
		case Axe_AttState::None:
			if (Axe_RAttack_Dir >= Dir)
			{
				m_FSM.ChangeState("Axe_AttackHub");
			}
			break;
		case Axe_AttState::NAttack:
			if (Axe_NAttack_Dir >= Dir)
			{
				m_FSM.ChangeState("Axe_AttackHub");
			}
			break;
		case Axe_AttState::FAttack1:
			if (Axe_FAttack_1_Dir >= Dir)
			{
				m_FSM.ChangeState("Axe_AttackHub");
			}
			break;
		case Axe_AttState::FAttack2:
			if (Axe_FAttack_2_Dir >= Dir)
			{
				m_FSM.ChangeState("Axe_AttackHub");
			}
			break;
		case Axe_AttState::TAttack:
			if (Axe_TAttack_Dir >= Dir)
			{
				m_FSM.ChangeState("Axe_AttackHub");
			}
			break;
		case Axe_AttState::RAttack:
			if (Axe_RAttack_Dir >= Dir)
			{
				m_FSM.ChangeState("Axe_AttackHub");
			}
			break;
		default:
			break;
		}
	}
		break;
	case Axe_MoveState::Back:
		if (m_BMoveState != m_MoveState)
		{
			m_BMoveState = m_MoveState;
			m_Animation->ChangeAnimation("AxeSoldier_BWalk");
		}
		else
		{
			if (m_MoveEnd)
			{
				m_MoveEnd = false;
				if (0 >= m_MoveRandom)
				{
					m_MoveRandom = 0;
					m_MoveState = Axe_MoveState::Front;
				}
				else
				{
					m_MoveRandom--;
					m_MoveState = (Axe_MoveState)GetRandom((int)Axe_MoveState::None + 2, (int)Axe_MoveState::End - 1);
				}
			}
		}
		break;
	case Axe_MoveState::Left:
		if (m_BMoveState != m_MoveState)
		{
			m_BMoveState = m_MoveState;
			m_Animation->ChangeAnimation("AxeSoldier_LWalk");
		}
		else
		{
			if (m_MoveEnd)
			{
				m_MoveEnd = false;
				if (0 >= m_MoveRandom)
				{
					m_MoveRandom = 0;
					m_MoveState = Axe_MoveState::Front;
				}
				else
				{
					m_MoveRandom--;
					m_MoveState = (Axe_MoveState)GetRandom((int)Axe_MoveState::None + 2, (int)Axe_MoveState::End - 1);
				}
			}
		}
		break;
	case Axe_MoveState::Right:
		if (m_BMoveState != m_MoveState)
		{
			m_BMoveState = m_MoveState;
			m_Animation->ChangeAnimation("AxeSoldier_RWalk");
		}
		else
		{
			if (m_MoveEnd)
			{
				m_MoveEnd = false;
				if (0 >= m_MoveRandom)
				{
					m_MoveRandom = 0;
					m_MoveState = Axe_MoveState::Front;
				}
				else
				{
					m_MoveRandom--;
					m_MoveState = (Axe_MoveState)GetRandom((int)Axe_MoveState::None + 2, (int)Axe_MoveState::End - 1);
				}
			}
		}
		break;
	default:
		break;
	}


}
void CAxeSoldier::Axe_Move_End()
{
	LookAtObjectActive(false);
}

//////////////////////////////////////////////////////////////////////	Attack Hub
void CAxeSoldier::Axe_AttackHub_Start()
{
	m_AxeCurState = Axe_State::Attack;

	m_AttackRun = false;
	
	m_AxeCurAttState = (Axe_AttState)GetRandom((int)Axe_AttState::None + 1, (int)Axe_AttState::End - 1);
	float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());

	switch (m_AxeCurAttState)
	{
	case Axe_AttState::NAttack:
		if (Axe_NAttack_Dir >= Dir)
		{
			m_Animation->ChangeAnimation("AxeSoldier_NAttack");
		}
		else
		{
			m_AttackRun = true;
			m_Animation->ChangeAnimation("AxeSoldier_Run");
		}
		break;
	case Axe_AttState::FAttack1:
		if (Axe_FAttack_1_Dir >= Dir)
		{
			m_Animation->ChangeAnimation("AxeSoldier_FAttack_1");
		}
		else
		{
			m_AttackRun = true;
			m_Animation->ChangeAnimation("AxeSoldier_Run");
		}
		break;
	case Axe_AttState::FAttack2:
	if (Axe_FAttack_2_Dir >= Dir)
	{
		m_Animation->ChangeAnimation("AxeSoldier_FAttack_2");
	}
	else
	{
		m_AttackRun = true;
		m_Animation->ChangeAnimation("AxeSoldier_Run");
	}
		break;
	case Axe_AttState::TAttack:
		if (Axe_TAttack_Dir >= Dir)
		{
			m_Animation->ChangeAnimation("AxeSoldier_TAttack");
		}
		else
		{
			m_AttackRun = true;
			m_Animation->ChangeAnimation("AxeSoldier_Run");
		}
		break;
	case Axe_AttState::RAttack:
		if (Axe_RAttack_Dir >= Dir)
		{
			m_Animation->ChangeAnimation("AxeSoldier_RAttack");
		}
		else
		{
			m_AttackRun = true;
			m_Animation->ChangeAnimation("AxeSoldier_Run");
		}
		break;
	default:
		break;
	}
}
void CAxeSoldier::Axe_AttackHub_Stay()
{
	if (m_AttackRun)
	{
		m_AxeCurState = Axe_State::AttackRun;
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());
		switch (m_AxeCurAttState)
		{
		case Axe_AttState::NAttack:
			if (Axe_NAttack_Dir >= Dir)
			{
				m_AxeCurState = Axe_State::Attack;
				m_AttackRun = false;
				m_Animation->ChangeAnimation("AxeSoldier_NAttack");
			}
			break;
		case Axe_AttState::FAttack1:
			if (Axe_FAttack_1_Dir >= Dir)
			{
				m_AxeCurState = Axe_State::Attack;
				m_AttackRun = false;
				m_Animation->ChangeAnimation("AxeSoldier_FAttack_1");
			}
			break;
		case Axe_AttState::FAttack2:
			if (Axe_FAttack_2_Dir >= Dir)
			{
				m_AxeCurState = Axe_State::Attack;
				m_AttackRun = false;
				m_Animation->ChangeAnimation("AxeSoldier_FAttack_2");
			}
			break;
		case Axe_AttState::TAttack:
			if (Axe_TAttack_Dir >= Dir)
			{
				m_AxeCurState = Axe_State::Attack;
				m_AttackRun = false;
				m_Animation->ChangeAnimation("AxeSoldier_TAttack");
			}
			break;
		case Axe_AttState::RAttack:
			if (Axe_RAttack_Dir >= Dir)
			{
				m_AxeCurState = Axe_State::Attack;
				m_AttackRun = false;
				m_Animation->ChangeAnimation("AxeSoldier_RAttack");
			}
			break;
		default:
			break;
		}
	}
}
void CAxeSoldier::Axe_AttackHub_End()
{
}

//////////////////////////////////////////////////////////////////////	Hit Hub
void CAxeSoldier::Axe_HitHub_Start()
{

}
void CAxeSoldier::Axe_HitHub_Stay()
{

}
void CAxeSoldier::Axe_HitHub_End()
{
}
void CAxeSoldier::IsHit(Axe_HitState State)
{
	// 함수가 호출되었을 때 처음 들어온건지 아니면 Hit 도중에 들어온건지를 판별한다.
	if (Axe_State::Hit == m_AxeCurState)
	{
		switch (m_HitAniState)
		{
		case Axe_HitAniState::None:
			break;
		case Axe_HitAniState::Normal:
			m_Animation->ResetSequence();
			break;
		case Axe_HitAniState::H_Fly:
			m_Animation->ResetSequence();
			break;
		case Axe_HitAniState::L_Fly:
			m_Animation->ResetSequence();
			break;
		case Axe_HitAniState::FlyToKnockBack:
			break;
		case Axe_HitAniState::StandUp:
		{
			int Frame = m_Animation->GetCurFrame();
			if (10 <= Frame)
			{
				m_Animation->ChangeAnimation("AxeSoldier_KnockBack");
			}
		}
			break;
		case Axe_HitAniState::StandBy:
			break;
		case Axe_HitAniState::Stun:
			break;
		case Axe_HitAniState::HThrow:
		{
			int Frame = m_Animation->GetCurFrame();
			if (10 <= Frame)
			{
				m_HitAniState = Axe_HitAniState::H_Fly;
				m_Animation->ChangeAnimation("AxeSoldier_Hit_HFly");
			}
		}
			break;
		case Axe_HitAniState::LThrow:
		{
			int Frame = m_Animation->GetCurFrame();
			if (10 <= Frame)
			{
				m_HitAniState = Axe_HitAniState::H_Fly;
				m_Animation->ChangeAnimation("AxeSoldier_Hit_LFly");
			}
		}
			break;
		case Axe_HitAniState::KnockBack:
			break;
		case Axe_HitAniState::End:
			break;
		default:
			break;
		}
	}
	else
	{
		// 만약 Hit 함수가 처음 호출되면 FSM을 Hit허브로 바꿔준다.
		m_AxeCurState = Axe_State::Hit;

		// 노말히트(움찔), 하이 넉백 , 로우 넉백에 따라 상태를 바꿔준다.
		m_HitState = State;

		// 변경된 상태에 따라 시작 애니메이션을 다르게 설정한다.
		switch (m_HitState)
		{
		case Axe_HitState::Normal:
			m_HitAniState = Axe_HitAniState::Normal;
			m_Animation->ChangeAnimation("AxeSoldier_Hit");
			break;
		case Axe_HitState::HKnockback:
			m_HitAniState = Axe_HitAniState::HThrow;
			m_Animation->ChangeAnimation("AxeSoldier_HThrow_1");
			break;
		case Axe_HitState::LKnockback:
			m_HitAniState = Axe_HitAniState::LThrow;
			m_Animation->ChangeAnimation("AxeSoldier_LThrow_1");
			break;
		default:
			break;
		}
		m_FSM.ChangeState("Axe_HitHub");
	}
}


void CAxeSoldier::Axe_Dead_Start()
{
	m_AxeCurState = Axe_State::Dead;
	m_Body->Enable(false);
}
void CAxeSoldier::Axe_Dead_Stay()
{
}
void CAxeSoldier::Axe_Dead_End()
{
}
void CAxeSoldier::IsDead(int DeadType)
{
	m_FSM.ChangeState("Axe_Dead");

	switch (DeadType)
	{
	case 0:
		m_Animation->ChangeAnimation("AxeSoldier_NDie");
		break;

	case 1:
		m_Animation->ChangeAnimation("AxeSoldier_BDie");
		break;

	case 2:
		m_Animation->ChangeAnimation("AxeSoldier_FDie");
		break;
	default:
		break;
	}
}