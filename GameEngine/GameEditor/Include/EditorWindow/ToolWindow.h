#pragma once
#include "IMGUIWindow.h"
#include "GameEngine.h"
class CToolWindow :
	public CIMGUIWindow
{
public:
	CToolWindow();
	virtual ~CToolWindow();

private:
	class CIMGUIGizmoComponent* m_GizmoComponent;
	class CIMGUICurCameraComponent* m_CurCameraComponent;
	class CIMGUIRenderOptionComponent* m_RenderOptionComponent;

public:
	class CIMGUIGizmoComponent* GetGizmoComponent()
	{
		return m_GizmoComponent;
	}
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void GizmoComponentUpdate(class CSceneComponent* Obj);
	void CreateGizmoComponent();
	void CreateCameraComponent();
	void CreateRenderOptionComponent();
	void AllComponentClose();
};
