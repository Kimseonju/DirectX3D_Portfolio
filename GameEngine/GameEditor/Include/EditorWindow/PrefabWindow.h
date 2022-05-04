#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"
class CPrefabWindow :
	public CIMGUIWindow
{
public:
	CPrefabWindow();
	virtual ~CPrefabWindow();

private:
	bool m_Start;
	class CIMGUIListBox* m_ObjListBox;
	CSharedPtr<CGameObject> m_SelectPrefab;
	std::vector<CSharedPtr<CGameObject>> m_VecPrefab;
	
public:
	void AddPrefab(CGameObject* Prefab)
	{
		CGameObject* Clone=Prefab->Clone();
		m_VecPrefab.push_back(Clone);
		Clone->Enable(false);
		Clone->Release();
		//CSceneComponent* Component = Prefab->GetRootComponent()->Clone();
		//Clone->SetRootCloneComponent(Component, false);
		//Clone->SetWorldPos(0.f, 0.f, 0.f);
	}

	CGameObject* GetSelectObject()
	{
		return m_SelectPrefab.Get();
	}
public:

	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void ListCallback(int SelectIndex, const char* Item);
};
