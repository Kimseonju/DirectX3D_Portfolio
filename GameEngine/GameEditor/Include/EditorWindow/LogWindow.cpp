#include "../pch.h"
#include "LogWindow.h"
#include "IMGUIConsole.h"
CLogWindow::CLogWindow()
{
}

CLogWindow::~CLogWindow()
{
}

bool CLogWindow::Init()
{
	CIMGUIConsole* Console = AddWidget<CIMGUIConsole>("Console");


	return true;
}

void CLogWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}
