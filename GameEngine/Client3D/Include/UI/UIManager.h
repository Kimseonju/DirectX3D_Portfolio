#pragma once
#include "GameEngine.h"
#include "../Object/Player.h"
class CUIManager
{

private:
	CScene* m_pScene;
	std::unordered_map<std::string, class CWidgetWindow*> m_vecWidgetWindow;

public:
	bool Init(CScene* Scene);
public:
	class CWidgetWindow* FindWidgetWindow(const std::string& Name);
	void AllWidgetClose();
public:
	DECLARE_SINGLE(CUIManager)
};

