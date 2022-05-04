#include "IMGUITabItemEnd.h"

CIMGUITabItemEnd::CIMGUITabItemEnd()
{
}

CIMGUITabItemEnd::~CIMGUITabItemEnd()
{
}


bool CIMGUITabItemEnd::Init()
{
	return true;
}

void CIMGUITabItemEnd::Render()
{
	ImGui::EndTabItem();
}

