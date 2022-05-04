#pragma once

enum class PlayerDir
{
	Left,
	Right,
	Front,
	Back
};
enum AnimType
{
	Appear,
	Attack1Combat,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	AttackSkill1,
	AttackSkill2,
	Skill1,
	Skill2,
	UltraSkill,
	IdleStart,
	Idle,
	StandBy,
	Hit_L,
	Hit_H,
	MoveStart,
	Move,
	MoveToIdle,
	Combat,
	CombatIdle,
	CombatMove,
	Failure,
	Die,
	Victory,
	VictoryIdle,
	EvadeBackward,
	EvadeForward,
	AttackCharge,
	UltraAttack,
	SwitchIn,
	SwitchOut,
	End
};

enum class PlayerState
{
	Appear,
	Idle,
	Move,
	Combat,
	CombatToIdle,
	Attack,
	AttackCombat,
	AttackIdle,
	Die,
	Failure,
	Hit_L,
	Hit_H,
	UltraSkill,
	Win,
	Evade,
	SwitchIn,
	SwitchOut,
	Victory,
	VictoryIdle

};

enum class ClientClassType
{
	Default,
	Kiana,
	Sakura,
	Axe,
	Sniper,
	LoadingStartObject,
	LobbyShip,
	Wendy,
	CameraMoveObject,
	BossSpawnObject,
	ColliderSpawnObject,
	MonsterSpawnObject,
	MapCollision,
	LobbyValkyieSelectZone
};

enum class ItemType
{
	Weapon,
	WeaponUpgradeItem,
	PlayerUpgradeItem,
	End
};

enum class MapItemType
{
	Heal,
	SpHeal,
	Coin
};
enum class SpawnType
{
	Default,
	Monster,
	Boss
};
enum class StarType
{
	B,
	A,
	S,
	SS,
	SSS
};
enum class AttributeType
{
	Biologic,
	Psychic,
	Mecha
};
enum Widget_ZOrder
{
	Widget_ZOrder_Widget,
	Widget_ZOrder_Dialog = 5
}; 
enum UI_ZOrder
{
	ZOrder_BG,
	ZOrder_BG1,
	ZOrder_IConBG,
	ZOrder_ICon,
	ZOrder_Text,
	ZOrder_Button,
	ZOrder_ButtonText
};
struct PlayerStatus
{
	std::string Name;
	std::wstring PlayerName;
	std::string WeaponName;
	int Level;
	int LevelMax;
	int HP;
	int HPMax;
	int Damage;
	int DamageMax;
	int SP;
	int SPMax;
	int Exp;
	int ExpMax;
	StarType starType;
	AttributeType attributeType;
	int GetDamage()
	{
		return GetRandom(Damage, DamageMax);
	}
};

struct ItemData
{
	ItemType Type;
	std::string Name;
	std::string PlayerName;
	std::string Info;
	std::string FileName;
	std::wstring FilePath;
	int Level;
	int LevelMax;
	int Damage;
	int Exp;
	int ExpMax;
	int Count;
};

enum class LoadingStartObjectState
{
	Loading,
	LoadEnd_GoLobbyShip,
	GoLobbyShipEnd_SeeLobbyShip,
	SeeLobbyShipEnd_OpenDoor,
	OpenDoorEnd_InLobbyShip,
};
//ClientGlobal
//ClientFlag
//Engine에 있던거랑 비슷하게

//CSharedPtr<CAnimationSequence>  m_Sequence_Attack1;
//CSharedPtr<CAnimationSequence>  m_Sequence_Attack2;
//CSharedPtr<CAnimationSequence>  m_Sequence_Attack3;
//CSharedPtr<CAnimationSequence>  m_Sequence_Attack4;
//CSharedPtr<CAnimationSequence>  m_Sequence_Attack5;
//
//CSharedPtr<CAnimationSequence>  m_Sequence_AttackSkill1;
//CSharedPtr<CAnimationSequence>  m_Sequence_AttackSkill2;
//
//CSharedPtr<CAnimationSequence>  m_Sequence_Skill1;
//CSharedPtr<CAnimationSequence>  m_Sequence_Skill2;
//
//CSharedPtr<CAnimationSequence>  m_Sequence_SpecialSkill;
//
//CSharedPtr<CAnimationSequence>  m_Sequence_Evasion;