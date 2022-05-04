#include "IMGUITabBarEnd.h"

CIMGUITabBarEnd::CIMGUITabBarEnd()
{
}

CIMGUITabBarEnd::~CIMGUITabBarEnd()
{
}


bool CIMGUITabBarEnd::Init()
{
	return true;
}

void CIMGUITabBarEnd::Render()
{
	ImGui::EndTabBar();
}

