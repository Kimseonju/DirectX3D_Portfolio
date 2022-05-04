#include "Sniper.h"
#include "../PublicData.h"
#include "Player.h"
#include "Scene/Scene.h"
void CSniper::CreateFSM()
{
	m_FSM.CreateState("Sniper_Spawn", this, &CSniper::Sniper_Spawn_Stay, &CSniper::Sniper_Spawn_Start, &CSniper::Sniper_Spawn_End);
	m_FSM.CreateState("Sniper_Idle", this, &CSniper::Sniper_Idle_Stay, &CSniper::Sniper_Idle_Start, &CSniper::Sniper_Idle_End);
	m_FSM.CreateState("Sniper_Move", this, &CSniper::Sniper_Move_Stay, &CSniper::Sniper_Move_Start, &CSniper::Sniper_Move_End);
	m_FSM.CreateState("Sniper_AttackHub", this, &CSniper::Sniper_AttackHub_Stay, &CSniper::Sniper_AttackHub_Start, &CSniper::Sniper_AttackHub_End);
	m_FSM.CreateState("Sniper_HitHub", this, &CSniper::Sniper_HitHub_Stay, &CSniper::Sniper_HitHub_Start, &CSniper::Sniper_HitHub_End);
	m_FSM.CreateState("Sniper_Dead", this, &CSniper::Sniper_Dead_Stay, &CSniper::Sniper_Dead_Start, &CSniper::Sniper_Dead_End);

	m_FSM.ChangeState("Sniper_Spawn");
}

void CSniper::IsFSMPlay(bool _Play)
{
	m_FSM.IsPlay(_Play);
}

void CSniper::Sniper_Spawn_Start()
{
	m_SpawnTimer1 = 1.f;
	m_SpawnTimer2 = 2.f;
	m_SpawnEffect = m_pScene->SpawnObject<CMonsterSpawnEffect>("Effect");
	m_SpawnEffect->SetWorldPos(GetWorldPos().x, GetWorldPos().y + 0.1f, GetWorldPos().z);
	//m_Animation->ChangeAnimation("Sniper_FAttack");  
}
void CSniper::Sniper_Spawn_Stay()
{
	m_SpawnEffect->ManualUpdate(m_DeltaTime);

	m_SpawnTimer1 -= m_DeltaTime;
	if (0 >= m_SpawnTimer1)
	{
		m_SpawnTimer1 = 0.f;

		m_SpawnTimer2 -= m_DeltaTime;
		m_Mesh->AddWorldPos(0.f, m_DeltaTime, 0.f);
		if (0>= m_SpawnTimer2)
		{
			m_SpawnEffect->EffectDeath();
			m_SpawnEffect = nullptr;
			m_FSM.ChangeState("Sniper_Idle");
		}
	}
	//m_FSM.ChangeState("Sniper_Idle");
}
void CSniper::Sniper_Spawn_End()
{
}

void CSniper::Sniper_Idle_Start()
{
	m_SniperCurState = Sniper_State::Idle;
	m_Animation->ChangeAnimation("Sniper_Idle");
	m_IdleTime = 1.0f;
}
void CSniper::Sniper_Idle_Stay()
{
	m_IdleTime -= m_DeltaTime;

	if (0 >= m_IdleTime)
	{
		m_IdleTime = 1.0f;
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());

		if (Sniper_AttEnd_Dir >= Dir)
		{
			m_FSM.ChangeState("Sniper_AttackHub");
		}
		else
		{
			m_FSM.ChangeState("Sniper_Move");
		}
	}
}
void CSniper::Sniper_Idle_End()
{
}

void CSniper::Sniper_Move_Start()
{
	m_SniperCurState = Sniper_State::Move;
	m_Animation->ChangeAnimation("Sniper_Run");
}
void CSniper::Sniper_Move_Stay()
{
	Vector3 WorldPos = GetWorldPos();
	WorldPos.y = 0.f;
	float Dir = CPublicData::GetInst()->DistanceToPlayer(WorldPos);
	Vector3 vec222=GetWorldPos();
	


	if (Sniper_AttEnd_Dir >= Dir)
	{
		m_FSM.ChangeState("Sniper_AttackHub");
	}
}
void CSniper::Sniper_Move_End()
{

}

void CSniper::Sniper_AttackHub_Start()
{
	m_SniperCurState = Sniper_State::Attack;
	m_IdleTime = 1.0f;
	// 공격 선택
	{
		if (m_SniperPrevAttState != Sniper_AttState::NAttack)
		{
			// 이 전 공격이 노말어택이 아니면 한번은 노말어택을 사용해준다.
			m_SniperCurAttState = Sniper_AttState::NAttack;
		}
		else
		{
			m_SniperCurAttState = (Sniper_AttState)GetRandom((int)Sniper_AttState::None + 1, (int)Sniper_AttState::End - 1);
		}
	}

	// 접근 거리에 따른 애니메이션 선택
	{
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());
		m_AttType = AttType::None;

		switch (m_SniperCurAttState)
		{
		case Sniper_AttState::NAttack:
		{
			if (Sniper_NAttack_Dir <= Dir)
			{
				m_AttType = AttType::Run;
				m_PointDir = Sniper_NAttack_Dir;
				m_Animation->ChangeAnimation("Sniper_Run");
			}
			else if ((Sniper_NAttack_Dir - 4) >= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Backward");
			}
			else
			{
				m_Animation->ChangeAnimation("Sniper_NAttack");
			}
		}
			break;
		case Sniper_AttState::GAttack:
		{
			if (Sniper_GAttack_Dir <= Dir)
			{
				m_AttType = AttType::Run;
				m_PointDir = Sniper_GAttack_Dir;
				m_Animation->ChangeAnimation("Sniper_Run");
			}
			else if ((Sniper_GAttack_Dir - 4) >= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Backward");
			}
			else
			{
				m_Animation->ChangeAnimation("Sniper_GAttack");
			}
		}
			break;
		case Sniper_AttState::RAttack:
		{
			if (Sniper_RAttack_Dir <= Dir)
			{
				m_AttType = AttType::Run;
				m_PointDir = Sniper_RAttack_Dir;
				m_Animation->ChangeAnimation("Sniper_Run");
			}
			else if ((Sniper_RAttack_Dir - 4) >= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Backward");
			}
			else
			{
				m_Animation->ChangeAnimation("Sniper_RAttack");
			}
		}
			break;
		case Sniper_AttState::FAttack:
		{
			if (Sniper_FAttack_Dir <= Dir)
			{
				m_AttType = AttType::Run;
				m_PointDir = Sniper_FAttack_Dir;
				m_Animation->ChangeAnimation("Sniper_Run");
			}
			else if ((Sniper_FAttack_Dir - 4) >= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Backward");
			}
			else
			{
				m_Animation->ChangeAnimation("Sniper_FAttack");
			}
		}
			break;
		default:
			break;
		}
	}
}
void CSniper::Sniper_AttackHub_Stay()
{
	switch (m_AttType)
	{
	case AttType::None:
	{
		if (m_Animation->GetSequence()->GetName() != "Sniper_NAttack" &&
			m_Animation->GetSequence()->GetName() != "Sniper_GAttack" && 
			m_Animation->GetSequence()->GetName() != "Sniper_RAttack" && 
			m_Animation->GetSequence()->GetName() != "Sniper_FAttack")
		{
			m_SniperPrevAttState = m_SniperCurAttState;
			m_SniperCurAttState = Sniper_AttState::None;
			m_SniperCurState = Sniper_State::Idle;
			m_FSM.ChangeState("Sniper_Idle");
		}
	}
		break;
	case AttType::Run:
	{
		float Dir = CPublicData::GetInst()->DistanceToPlayer(GetWorldPos());
		switch (m_SniperCurAttState)
		{
		case Sniper_AttState::NAttack:
		{
			if (Sniper_NAttack_Dir <= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Idle");
			}
		}
			break;
		case Sniper_AttState::GAttack:
		{
			if (Sniper_GAttack_Dir <= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Idle");
			}
		}
			break;
		case Sniper_AttState::RAttack:
		{
			if (Sniper_RAttack_Dir <= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Idle");
			}
		}
			break;
		case Sniper_AttState::FAttack:
		{
			if (Sniper_FAttack_Dir <= Dir)
			{
				m_AttType = AttType::Back;
				m_Animation->ChangeAnimation("Sniper_Idle");
			}
		}
			break;
		}
	}
		break;
	case AttType::Back:
	{
		if (m_Animation->GetSequence()->GetName() == "Sniper_Idle")
		{
			m_IdleTime -= m_DeltaTime;

			if (0 >= m_IdleTime)
			{
				switch (m_SniperCurAttState)
				{
				case Sniper_AttState::NAttack:
					m_Animation->ChangeAnimation("Sniper_NAttack");
					break;
				case Sniper_AttState::GAttack:
					m_Animation->ChangeAnimation("Sniper_GAttack");
					break;
				case Sniper_AttState::RAttack:
					m_Animation->ChangeAnimation("Sniper_RAttack");
					break;
				case Sniper_AttState::FAttack:
					m_Animation->ChangeAnimation("Sniper_FAttack");
					break;
				}
				m_AttType = AttType::None;
			}
		}
	}
		break;
	}
}
void CSniper::Sniper_AttackHub_End()
{
}

void CSniper::Sniper_HitHub_Start()
{
	m_SniperCurState = Sniper_State::Hit;

}
void CSniper::Sniper_HitHub_Stay()
{
	if (m_SniperCurState == Sniper_State::Idle)
	{
		m_FSM.ChangeState("Sniper_Idle");
	}

}
void CSniper::Sniper_HitHub_End()
{
}
void CSniper::IsHit(Sniper_HitState State)
{
	if (m_SniperCurState != Sniper_State::Hit)
	{
		m_FSM.ChangeState("Sniper_HitHub");
		m_SniperCurState = Sniper_State::Hit;

		switch (State)
		{
		case Sniper_HitState::Normal:
		{
			m_HitAniState = Sniper_HitAniState::HNormal;
			m_Animation->ChangeAnimation("Sniper_HHit");
		}
		break;
		case Sniper_HitState::Knockback:
		{
			m_HitAniState = Sniper_HitAniState::HFlyALL;
			m_Animation->ChangeAnimation("Sniper_HFlyALL");
		}
		break;
		case Sniper_HitState::Stun:
		{
			m_HitAniState = Sniper_HitAniState::Stun;
			m_Animation->ChangeAnimation("Sniper_Stun");
		}
		break;
		default:
			break;
		}
	}
	else
	{
		switch (State)
		{
		case Sniper_HitState::Normal:
		{
			switch (m_HitAniState)
			{
			case Sniper_HitAniState::HNormal:
			case Sniper_HitAniState::LNormal:
			{
				m_HitAniState = Sniper_HitAniState::HNormal;
				m_Animation->ChangeAnimation("Sniper_HHit");
			}
			break;
			case Sniper_HitAniState::HFlyALL:
			{
				int Frame = m_Animation->GetCurFrame();
				if (9 <= Frame)
				{
					m_HitAniState = Sniper_HitAniState::LFly;
					m_Animation->ChangeAnimation("Sniper_LFly");
				}
				else if (3 <= Frame)
				{
					m_HitAniState = Sniper_HitAniState::HFly;
					m_Animation->ChangeAnimation("Sniper_HFly");
				}
			}
			break;
			case Sniper_HitAniState::HFly:
			{
				m_Animation->ResetSequence();
			}
			break;
			case Sniper_HitAniState::HFlyToStand:
			{
				m_HitAniState = Sniper_HitAniState::LFly;
				m_Animation->ChangeAnimation("Sniper_LFly");
			}
			break;
			case Sniper_HitAniState::LFly:
			{
				m_Animation->ResetSequence();
			}
			break;
			case Sniper_HitAniState::FlyToKnockDown:
			{
				m_HitAniState = Sniper_HitAniState::LFly;
				m_Animation->ChangeAnimation("Sniper_LFly");
			}
			break;
			case Sniper_HitAniState::StandUp:
				break;
			case Sniper_HitAniState::StandBy:
				break;
			case Sniper_HitAniState::Stun:
				break;
			default:
				break;
			}
		}
		case Sniper_HitState::Knockback:
		{
			switch (m_HitAniState)
			{
			case Sniper_HitAniState::HFlyALL:
			{
				int Frame = m_Animation->GetCurFrame();
				if (9 <= Frame)
				{
					m_HitAniState = Sniper_HitAniState::LFly;
					m_Animation->ChangeAnimation("Sniper_LFly");
				}
				else if (3 <= Frame)
				{
					m_HitAniState = Sniper_HitAniState::HFly;
					m_Animation->ChangeAnimation("Sniper_HFly");
				}
			}
			break;
			case Sniper_HitAniState::HFly:
			{
				m_Animation->ResetSequence();
			}
			break;
			case Sniper_HitAniState::HFlyToStand:
			{
				m_HitAniState = Sniper_HitAniState::LFly;
				m_Animation->ChangeAnimation("Sniper_LFly");
			}
			break;
			case Sniper_HitAniState::LFly:
			{
				m_Animation->ResetSequence();
			}
			break;
			case Sniper_HitAniState::FlyToKnockDown:
			{
				m_HitAniState = Sniper_HitAniState::LFly;
				m_Animation->ChangeAnimation("Sniper_LFly");
			}
			break;
			case Sniper_HitAniState::StandUp:
				break;
			case Sniper_HitAniState::StandBy:
				break;
			case Sniper_HitAniState::Stun:
				break;
			default:
				break;
			}
		}
		break;
		case Sniper_HitState::Stun:
		{
			m_HitAniState = Sniper_HitAniState::Stun;
			m_Animation->ChangeAnimation("Sniper_Stun");
		}
		break;
		default:
			break;
		}
	}

}

void CSniper::Sniper_Dead_Start()
{
	m_Animation->ChangeAnimation("Sniper_Die");
	m_DeadGradientTimer = 1.0;
	m_DeadGradientOn = false;
}
void CSniper::Sniper_Dead_Stay()
{
}
void CSniper::Sniper_Dead_End()
{
}
void CSniper::IsDead(int DeadType)
{
	m_SniperCurState = Sniper_State::Dead;
	m_Body->Enable(false);
	LookAtObjectActive(false);
	m_FSM.ChangeState("Sniper_Dead");
}
