#pragma once
#include "GameEngine.h"
#include "Global.h"
#include "Object/Player.h"
#include <codecvt>
#include <atlstr.h>
class CPublicData
{
private:
	class CPlayerDataTable* m_PlayerDataTable;
	class CItemDataTable* m_ItemDataTable;

public:
	bool Axe_ResourceCheck;
	bool Sniper_ResourceCheck;
	bool Wendy_ResourceCheck;
	bool Bullet_ResourceCheck;
	int m_Gold;
	int m_Crystal;

public:
	int GetGold()
	{
		return m_Gold;
	}
	int GetCrystal()
	{
		return m_Crystal;
	}
	void SetGold(int Gold)
	{
		m_Gold = Gold;
	}
	void SetCrystal(int Crystal)
	{
		m_Crystal = Crystal;
	}
	std::unordered_map<int, CSharedPtr<CPlayer>> m_mapPlayer;
	CPlayer* m_CurPlayer;
	float DistanceToPlayer(Vector3 Target);
	float AngleToPlayer(Vector3 Target);
	Vector3 MoveToPlayer(Vector3 Target);

	void SetCurPlayer(class CPlayer* Player)
	{
		m_CurPlayer = Player;
	}
	class CPlayer* GetCurPlayer()
	{
		return m_CurPlayer;
	}
	
public:
	PlayerStatus* FindPlayerData(const std::string& Name);
	class CPlayerDataTable* GetPlayerDataTable()
	{
		return m_PlayerDataTable;
	}

	class CItemDataTable* GetItemDataTable()
	{
		return m_ItemDataTable;
	}
	void PlayerMapInsert (int Index, CPlayer* Player)
	{
		m_mapPlayer.insert(std::make_pair(Index, Player));
	}
	void PlayerMapClear()
	{
		m_mapPlayer.clear();
	}
	class CPlayer* GetPlayer(int Index);

	class CPlayer* GetNextPlayer();

public:
	DECLARE_SINGLE(CPublicData);

};
//멀티바이트
static std::wstring stringToWstring(const std::string& str)
{
	return std::wstring(CA2W(str.c_str()));
}


#define Axe_NAttack_Dir		2
#define Axe_FAttack_1_Dir	2.5f
#define Axe_RAttack_Dir		10.f
#define Axe_Follow_Dir		3
#define Axe_FAttack_2_Dir	4
#define Axe_TAttack_Dir		4.5

#define Sniper_BulletSpeed		20
#define Sniper_FAttack_Dir		2
#define Sniper_GAttack_Dir		3
#define Sniper_RAttack_Dir		5
#define Sniper_NAttack_Dir		7
#define Sniper_AttEnd_Dir		5

#pragma region AxeStates

	enum class Axe_State
	{
		Spawn,
		Idle,
		Move,
		Attack,
		AttackRun,
		Hit,
		Dead
	};
	enum class Axe_AttState
	{
		None,
		NAttack,
		FAttack1,
		FAttack2,
		TAttack,
		RAttack,
		End
	};
	enum class Axe_MoveState
	{
		None,
		Front,
		Back,
		Left,
		Right,
		End
	};
	enum class Axe_HitState
	{
		None,
		Normal,
		HKnockback,
		LKnockback,
		End
	};
	enum class Axe_HitAniState
	{
		None,
		Normal,
		H_Fly,
		L_Fly,
		FlyToKnockBack,
		StandUp,
		StandBy,
		Stun,
		HThrow,
		LThrow,
		KnockBack,
		End
	};
#pragma endregion

#pragma region SniperStates

	enum class Sniper_State
	{
		Spawn,
		Idle,
		Move,
		Attack,
		Hit,
		Dead
	};
	enum class Sniper_AttState
	{
		None,
		NAttack,
		GAttack,
		RAttack,
		FAttack,
		End
	};
	enum class Sniper_HitState
	{
		None,
		Normal,
		Knockback,
		Stun,
		End
	};
	enum class Sniper_HitAniState
	{
		None,
		HNormal,
		LNormal,
		HFlyALL,
		HFly,
		HFlyToStand,
		LFly,
		FlyToKnockDown,
		StandUp,
		StandBy,
		Stun,
		End
	};
#pragma endregion

#pragma region WendyStates
	enum class Wendy_State
	{
		Spawn,
		Idle,
		Move,
		Attack,
		Hit,
		Dead
	};
	enum class Wendy_AttackState
	{
		None,
		AIrShoot,
		AirHole,
		Brandish,
		Storm,
		AirBullet,
		AirStar,
		Tornado,
		End
	};
#pragma endregion

#define Wendy_Search_Dir		10
#define Wendy_LongAttack_Dir	10
#define Wendy_ShortAttack_Dir	2.5f
