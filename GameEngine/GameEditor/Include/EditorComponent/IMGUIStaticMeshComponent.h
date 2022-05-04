#pragma once

//이후 수정용 만들기

#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIStaticMeshComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIStaticMeshComponent();
	virtual ~CIMGUIStaticMeshComponent();

private:
	class CIMGUIText* m_MeshName;

	class CStaticMeshComponent* m_Component;

	class CIMGUIButton* m_SelectMeshButton;
	class CIMGUIButton* m_MeshLightResetButton;
	class CIMGUIFileDialogWidget* m_FileDialog;
public:
	virtual void ComponentUpdateInfo(CSceneComponent* Component);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
public:
	void MeshLightResetCallback();
	void SelectMeshButtonCallback();
	void PopupSelectMeshCallback(std::string FileName);
};
