#include "../pch.h"
#include "PrefabWindow.h"
#include "IMGUIListBox.h"
#include "../GlobalValue.h"
CPrefabWindow::CPrefabWindow() :
	m_Start(false),
	m_ObjListBox(nullptr)
{
}

CPrefabWindow::~CPrefabWindow()
{
	
}

bool CPrefabWindow::Init()
{
	m_ObjListBox = AddWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);

	m_ObjListBox->SetSelectCallback<CPrefabWindow>(this, &CPrefabWindow::ListCallback);
	m_ObjListBox->SetBorder(false);
	return true;
}

void CPrefabWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);


	m_ObjListBox->Clear();
	for (size_t i = 0; i < m_VecPrefab.size(); i++)
	{
		m_ObjListBox->AddItem(m_VecPrefab[i]->GetName().c_str());
	}
}

void CPrefabWindow::ListCallback(int SelectIndex, const char* Item)
{
	CGlobalValue::MouseState = Mouse_State::Prefab;
	m_SelectPrefab = m_VecPrefab[SelectIndex];
}
