#include "PlayerDataTable.h"

CPlayerDataTable::CPlayerDataTable()
{
}

CPlayerDataTable::~CPlayerDataTable()
{
	auto iter = m_vecData.begin();
	auto iterEnd = m_vecData.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_vecData.clear();
}

void CPlayerDataTable::Init()
{
	PlayerStatus* Data=new PlayerStatus;
	Data->Name = "Kiana";
	Data->PlayerName = TEXT("키아나 카스라나");
	Data->Level = 1;
	Data->LevelMax = 5;
	Data->HP = 2000;
	Data->HPMax = 2000;
	Data->Damage = 60;
	Data->DamageMax = 110;
	Data->SP = 0;
	Data->SPMax = 150;
	Data->Exp = 0;
	Data->ExpMax = 40;
	Data->starType = StarType::B;
	Data->attributeType = AttributeType::Psychic;
	Data->WeaponName = "USP45";
	m_vecData.insert(std::make_pair(Data->Name, Data));

	Data = new PlayerStatus;
	Data->Name = "Sakura";
	Data->PlayerName = TEXT("야에 사쿠라");
	Data->Level = 1;
	Data->LevelMax = 5;
	Data->HP = 2000;
	Data->HPMax = 2000;
	Data->Damage = 50;
	Data->DamageMax = 100;
	Data->SP = 0;
	Data->SPMax = 150;
	Data->Exp = 0;
	Data->ExpMax = 40;
	Data->starType = StarType::A;
	Data->attributeType = AttributeType::Biologic;
	Data->WeaponName = "세이슈 무라마사";
	m_vecData.insert(std::make_pair(Data->Name, Data));
}

PlayerStatus* CPlayerDataTable::FindData(const std::string& Name)
{
	auto iter = m_vecData.find(Name);
	if (iter == m_vecData.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CPlayerDataTable::LevelUp(const std::string& Name)
{
	auto iter = m_vecData.find(Name);
	if (iter == m_vecData.end())
	{
		return;
	}
	PlayerStatus* Status = iter->second;
	if (Status->Level == Status->LevelMax)
	{
		Status->Exp = 0;
		return;
	}
	while (Status->Exp >= Status->ExpMax)
	{
		Status->Exp -= Status->ExpMax;
		Status->HPMax += 20;
		Status->SPMax += 4;
		Status->Damage += 2;
		Status->DamageMax += 2;
	}

}

void CPlayerDataTable::AddExp(const std::string& Name, int Exp)
{
	auto iter = m_vecData.find(Name);
	if (iter == m_vecData.end())
	{
		return;
	}
	PlayerStatus* Status = iter->second;
	Status->Exp += Exp;
	while (Status->Exp >= Status->ExpMax)
	{
		if (Status->Level == Status->LevelMax)
		{
			Status->Exp = 0;
			return;
		}
		Status->Exp -= Status->ExpMax;
		Status->Level++;
		Status->HPMax += 20;
		Status->SPMax += 4;
		Status->Damage += 2;
		Status->DamageMax += 2;
	}
}

void CPlayerDataTable::SubExp(const std::string& Name, int Exp)
{
	auto iter = m_vecData.find(Name);
	if (iter == m_vecData.end())
	{
		return;
	}
	PlayerStatus* Status = iter->second;
	Status->Exp += Exp;
	if (Status->Level == Status->LevelMax)
	{
		Status->Exp = 0;
		return;
	}
	while (Status->Exp >= Status->ExpMax)
	{
		Status->Exp -= Status->ExpMax;
		Status->HPMax += 20;
		Status->SPMax += 4;
		Status->Damage += 2;
		Status->DamageMax += 2;
	}
}

void CPlayerDataTable::StageStart()
{
	auto iter = m_vecData.begin();
	auto iterEnd = m_vecData.end();
	for (; iter != iterEnd; ++iter)
	{
		iter->second->HP = iter->second->HPMax;
		iter->second->SP = 0;
	}
}
