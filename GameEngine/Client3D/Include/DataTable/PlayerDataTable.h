#pragma once
#include "GameEngine.h"
#include "../Global.h"
class CPlayerDataTable
{

public:
	CPlayerDataTable();
	~CPlayerDataTable();
private:
	std::unordered_map<std::string, PlayerStatus*> m_vecData;

public:
	void Init();
	PlayerStatus* FindData(const std::string& Name);
	std::unordered_map<std::string, PlayerStatus*>& GetDatas()
	{
		return m_vecData;
	}
	void LevelUp(const std::string& Name);
	void AddExp(const std::string& Name, int Exp);
	void SubExp(const std::string& Name, int Exp);
	void StageStart();
};

