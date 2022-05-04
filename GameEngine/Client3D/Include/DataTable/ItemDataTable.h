#pragma once
#include "GameEngine.h"
#include "../Global.h"
class CItemDataTable
{
public:
	CItemDataTable();
	~CItemDataTable();
private:
	std::unordered_map<ItemType, std::vector<ItemData*>> m_vecData;

public:
	void Init();

	std::vector<ItemData*>* FindvecData(ItemType Type);
	ItemData* FindData(ItemType Type, const std::string& Name);
	void AddExp(ItemType Type, const std::string& Name, int Exp);
	void AddItemCount(ItemType Type, const std::string& Name);

	void PushData(ItemData* Data);
};

