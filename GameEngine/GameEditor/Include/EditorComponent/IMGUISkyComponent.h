#pragma once

//이후 수정용 만들기

#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUISkyComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUISkyComponent();
	virtual ~CIMGUISkyComponent();

private:
	class CIMGUIText* m_TexName;

	class CSkyComponent* m_Component;

	class CIMGUIButton* m_SelectTexBtn;
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
	void SelectTexBtnCallback();
	void PopupSelectTexBtnCallback(std::string FileName);
};
