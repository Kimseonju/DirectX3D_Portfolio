#include "Wendy.h"
#include "../PublicData.h"
#include "Player.h"

void CWendy::CreateFSM()
{

	m_FSM.CreateState("Spawn", this, &CWendy::Wendy_Spawn_Stay, &CWendy::Wendy_Spawn_Start, &CWendy::Wendy_Spawn_End);
	m_FSM.CreateState("Idle", this, &CWendy::Wendy_Idle_Stay, &CWendy::Wendy_Idle_Start, &CWendy::Wendy_Idle_End);
	m_FSM.CreateState("Move", this, &CWendy::Wendy_Move_Stay, &CWendy::Wendy_Move_Start, &CWendy::Wendy_Move_End);
	m_FSM.CreateState("AttackHub", this, &CWendy::Wendy_AttackHub_Stay, &CWendy::Wendy_AttackHub_Start, &CWendy::Wendy_AttackHub_End);
	m_FSM.CreateState("Death", this, &CWendy::Wendy_Death_Stay, &CWendy::Wendy_Death_Start, &CWendy::Wendy_Death_End);

	m_FSM.ChangeState("Spawn");
}

void CWendy::IsFSMPlay(bool _Play)
{
	m_FSM.IsPlay(_Play);
}

void CWendy::Wendy_Spawn_Start()
{
	m_State = Wendy_State::Spawn;
	LookObject();
}
void CWendy::Wendy_Spawn_Stay()
{
}
void CWendy::Wendy_Spawn_End()
{
}

void CWendy::Wendy_Idle_Start()
{
	m_State = Wendy_State::Move; 
	m_Animation->ChangeAnimation("Wendy_Idle");
	LookObject();
}
void CWendy::Wendy_Idle_Stay()
{
	static float IdleTimer = 0.5f;
	IdleTimer -= m_DeltaTime;

	if (0 >= IdleTimer)
	{
		IdleTimer = 0.f;

		m_FSM.ChangeState("AttackHub");
	}
}
void CWendy::Wendy_Idle_End()
{
}

void CWendy::Wendy_Move_Start()
{
	LookObject();

	m_State = Wendy_State::Move;
	m_Animation->ChangeAnimation("Wendy_RunStart");
}
void CWendy::Wendy_Move_Stay()
{

	if (m_PointDir >= m_PlayerDir)
	{
		m_FSM.ChangeState("AttackHub");
	}
}
void CWendy::Wendy_Move_End()
{
}

void CWendy::Wendy_AttackHub_Start()
{
	LookObject();
	m_State = Wendy_State::Attack;

	if (Wendy_AttackState::None != m_AttackState)
	{
		if (Wendy_AttackState::None != m_AttackState)
		{
			switch (m_AttackState)
			{
			case Wendy_AttackState::AIrShoot:
			{
				m_Animation->ChangeAnimation("Wendy_AirShoot");
			}
			break;
			case Wendy_AttackState::AirHole:
			{
				m_Animation->ChangeAnimation("Wendy_AirHole");
			}
			break;
			case Wendy_AttackState::Brandish:
			{
				m_Animation->ChangeAnimation("Wendy_Brandish");
			}
			break;
			case Wendy_AttackState::Storm:
			{
				m_Animation->ChangeAnimation("Wendy_Storm");
			}
			break;
			case Wendy_AttackState::AirBullet:
			{
				m_Animation->ChangeAnimation("Wendy_LongAttack");
			}
			break;
			case Wendy_AttackState::AirStar:
			{
				m_Animation->ChangeAnimation("Wendy_LongAttack");
			}
			break;
			case Wendy_AttackState::Tornado:
			{
				m_Animation->ChangeAnimation("Wendy_LongAttack");
			}
			break;
			}
		}

	}
	else
	{
		m_RandomCount = 0;
		m_RandomCount = GetRandom(0, 2);

		m_AttackState = (Wendy_AttackState)GetRandom( (int)Wendy_AttackState::None + 1 , (int)Wendy_AttackState::End -1);
		if (0 != m_RandomCount)
		{
			int Ani = GetRandom(1, 2);
		
			if (1 == Ani)
				m_Animation->ChangeAnimation("Wendy_GlideLeft");
			else
				m_Animation->ChangeAnimation("Wendy_GlideRight");

			m_RandomCount--;
		}
		else
		{
			switch (m_AttackState)
			{
			case Wendy_AttackState::AIrShoot:
			{
				if (Wendy_LongAttack_Dir >= m_PlayerDir)
				{
					if (Wendy_LongAttack_Dir-5 >= m_PlayerDir)
					{
						int Ani = GetRandom(1, 2);

						if (1 == Ani)
							m_Animation->ChangeAnimation("Wendy_GlideBack");
						else
							m_Animation->ChangeAnimation("Wendy_AirShoot");
					}
					else
						m_Animation->ChangeAnimation("Wendy_AirShoot");
				}
				else
				{
					m_PointDir = Wendy_LongAttack_Dir - 2;
					m_FSM.ChangeState("Move");
				}
			}
			break;
			case Wendy_AttackState::AirHole:
			{
				if (Wendy_ShortAttack_Dir >= m_PlayerDir)
				{
					m_Animation->ChangeAnimation("Wendy_AirHole");
				}
				else
				{
					m_PointDir = Wendy_ShortAttack_Dir;
					m_FSM.ChangeState("Move");
				}
			}
			break;
			case Wendy_AttackState::Brandish:
			{
				if (Wendy_ShortAttack_Dir >= m_PlayerDir)
				{
					m_Animation->ChangeAnimation("Wendy_Brandish");
				}
				else
				{
					m_PointDir = Wendy_ShortAttack_Dir;
					m_FSM.ChangeState("Move");
				}
			}
			break;
			case Wendy_AttackState::Storm:
			{
				if (Wendy_ShortAttack_Dir >= m_PlayerDir)
				{
					m_Animation->ChangeAnimation("Wendy_Storm");
				}
				else
				{
					m_PointDir = Wendy_ShortAttack_Dir;
					m_FSM.ChangeState("Move");
				}
			}
			break;
			case Wendy_AttackState::AirBullet:
			{
				if (Wendy_LongAttack_Dir >= m_PlayerDir)
				{
					if (Wendy_LongAttack_Dir - 5 >= m_PlayerDir)
					{
						int Ani = GetRandom(1, 2);

						if (1 == Ani)
							m_Animation->ChangeAnimation("Wendy_GlideBack");
						else
							m_Animation->ChangeAnimation("Wendy_LongAttack");
					}
					else
						m_Animation->ChangeAnimation("Wendy_LongAttack");
				}
				else
				{
					m_PointDir = Wendy_LongAttack_Dir - 2;
					m_FSM.ChangeState("Move");
				}
			}
			break;
			case Wendy_AttackState::AirStar:
			{
				if (Wendy_LongAttack_Dir >= m_PlayerDir)
				{
					if (Wendy_LongAttack_Dir - 5 >= m_PlayerDir)
					{
						int Ani = GetRandom(1, 2);

						if (1 == Ani)
							m_Animation->ChangeAnimation("Wendy_GlideBack");
						else
							m_Animation->ChangeAnimation("Wendy_LongAttack");
					}
					else
						m_Animation->ChangeAnimation("Wendy_LongAttack");
				}
				else
				{
					m_PointDir = Wendy_LongAttack_Dir - 2;
					m_FSM.ChangeState("Move");
				}
			}
			break;
			case Wendy_AttackState::Tornado:
			{
				if (Wendy_LongAttack_Dir >= m_PlayerDir)
				{
					if (Wendy_LongAttack_Dir - 5 >= m_PlayerDir)
					{
						int Ani = GetRandom(1, 2);

						if (1 == Ani)
							m_Animation->ChangeAnimation("Wendy_GlideBack");
						else
							m_Animation->ChangeAnimation("Wendy_LongAttack");
					}
					else
						m_Animation->ChangeAnimation("Wendy_LongAttack");
				}
				else
				{
					m_PointDir = Wendy_LongAttack_Dir - 2;
					m_FSM.ChangeState("Move");
				}
			}
			break;
			}
		}
	}
}
void CWendy::Wendy_AttackHub_Stay()
{
	
}
void CWendy::Wendy_AttackHub_End()
{
}

void CWendy::Wendy_Death_Start()
{
	m_State = Wendy_State::Dead;
	m_Animation->ChangeAnimation("Wendy_Die");


}
void CWendy::Wendy_Death_Stay()
{
	LookAtObject(nullptr);
	LookAtObjectActive(false);
}
void CWendy::Wendy_Death_End()
{
}
void CWendy::IsDeath()
{
	m_Body->Enable(false);
	m_FSM.ChangeState("Death");
}
