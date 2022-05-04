
#include "Stage1StoryUI.h"
#include "UIManager.h"
CStage1StoryUI::CStage1StoryUI()
{
}

CStage1StoryUI::~CStage1StoryUI()
{
}

bool CStage1StoryUI::Init()
{
	CWidgetWindow::Init();

	return true;
}

void CStage1StoryUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CStage1StoryUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CStage1StoryUI::Render()
{
	CWidgetWindow::Render();
}

CStage1StoryUI* CStage1StoryUI::Clone()
{
	return new CStage1StoryUI(*this);
}