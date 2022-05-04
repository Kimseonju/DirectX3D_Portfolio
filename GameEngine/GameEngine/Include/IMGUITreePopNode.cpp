#include "IMGUITreePopNode.h"

CIMGUITreePopNode::CIMGUITreePopNode()
{
}

CIMGUITreePopNode::~CIMGUITreePopNode()
{
}

bool CIMGUITreePopNode::Init()
{
	return true;
}

void CIMGUITreePopNode::Render()
{
	ImGui::TreePop();
}

