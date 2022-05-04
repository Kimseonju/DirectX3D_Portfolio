#pragma once
#include "IMGUIWidget.h"
class CIMGUIGizmo :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;
	friend class CIMGUIGizmoTool;
protected:
	CIMGUIGizmo();
	virtual ~CIMGUIGizmo();

protected:
	class CScene* m_Scene;
	class CIMGUIGizmoComponent* m_GizmoComponent;

public:
	void SetGizmoComponent(class CIMGUIGizmoComponent* _GizmoComponent)
	{
		m_GizmoComponent = _GizmoComponent;
	}
public:
	virtual bool Init();
	virtual void Render();
public:
	bool IsUsing();
	void GizmoStart(class CScene* Scene);
	void EditTransform(float* cameraView, float* cameraProjection, bool editTransformDecomposition);

	void SetCurrentGizmoOperation(int Option);
};
