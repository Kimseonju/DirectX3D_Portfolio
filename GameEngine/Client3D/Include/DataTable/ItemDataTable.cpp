#include "ItemDataTable.h"

CItemDataTable::CItemDataTable()
{
}

CItemDataTable::~CItemDataTable()
{
	auto iter = m_vecData.begin();
	auto iterEnd = m_vecData.end();

	for (; iter != iterEnd; ++iter)
	{
		size_t Size = iter->second.size();
		for (size_t i = 0; i < Size; ++i)
		{
			SAFE_DELETE(iter->second[i]);
		}
		iter->second.clear();
	}
	m_vecData.clear();
}

void CItemDataTable::Init()
{
	ItemData* Data= new ItemData;
	Data->Type = ItemType::Weapon;
	Data->Name = "USP45";
	Data->Info = "H&K사가 특별히 설계한 권총";
	Data->Level = 1;
	Data->LevelMax = 5;
	Data->Damage = 5;
	Data->Exp = 0;
	Data->ExpMax = 10;
	Data->FileName="Weapon_Pistol_K1_01_1";
	Data->FilePath = TEXT("UI/Equipment/Weapon_Pistol_K1_01_1.png");
	PushData(Data);

	 Data = new ItemData;
	Data->Type = ItemType::Weapon;
	Data->Name = "세이슈 무라마사";
	Data->Info = "고대 일본 무사의 검";
	Data->Level = 1;
	Data->LevelMax = 5;
	Data->Damage = 5;
	Data->Exp = 0;
	Data->ExpMax = 10;
	Data->FileName = "Weapon_Katana_M1_13_1";
	Data->FilePath = TEXT("UI/Equipment/Weapon_Katana_M1_13_1.png");
	PushData(Data);


	Data = new ItemData;
	Data->Type = ItemType::WeaponUpgradeItem;
	Data->Name = "영혼 결정";
	Data->Info = "무기 경험치 1증가";
	Data->Level = 0;
	Data->LevelMax = 0;
	Data->Damage = 0;
	Data->Exp = 1;
	Data->Count = 50;
	Data->FileName = "3007";
	Data->FilePath = TEXT("UI/Equipment/3007.png");
	PushData(Data);

	Data = new ItemData;
	Data->Type = ItemType::PlayerUpgradeItem;
	Data->Name = "학습 칩";
	Data->Info = "캐릭터 경험치 5증가";
	Data->Level = 0;
	Data->LevelMax = 0;
	Data->Damage = 0;
	Data->Exp = 5;
	Data->Count = 50;
	Data->FileName = "1002";
	Data->FilePath = TEXT("UI/Equipment/1002.png");
	PushData(Data);
}

std::vector<ItemData*>* CItemDataTable::FindvecData(ItemType Type)
{
	auto iter = m_vecData.find(Type);
	if (iter == m_vecData.end())
	{
		m_vecData.insert(std::pair<ItemType, std::vector<ItemData*> >(Type, std::vector<ItemData*>()));
		iter = m_vecData.find(Type);
	}
	return &iter->second;
}

ItemData* CItemDataTable::FindData(ItemType Type, const std::string& Name)
{
	auto vec = FindvecData(Type);
	size_t Size = vec->size();
	for (size_t i = 0; i < Size; ++i)
	{
		if ((*vec)[i]->Name == Name)
		{
			return (*vec)[i];
		}
	}
	return nullptr;
}

void CItemDataTable::AddExp(ItemType Type, const std::string& Name, int Exp)
{

	auto vec = FindvecData(Type);
	size_t Size = vec->size();
	for (size_t i = 0; i < Size; ++i)
	{
		if ((*vec)[i]->Name == Name)
		{
			ItemData* Status = (*vec)[i];
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
				Status->Damage += 2;
			}
			break;
		}
	}
}


void CItemDataTable::AddItemCount(ItemType Type, const std::string& Name)
{
	auto vec = FindvecData(Type);
	size_t Size = vec->size();
	for (size_t i = 0; i < Size; ++i)
	{
		if ((*vec)[i]->Name == Name)
		{
			(*vec)[i]->Count++;
			break;
		}
	}
}

void CItemDataTable::PushData(ItemData* Data)
{
	auto vec=FindvecData(Data->Type);
	(*vec).push_back(Data);
}

