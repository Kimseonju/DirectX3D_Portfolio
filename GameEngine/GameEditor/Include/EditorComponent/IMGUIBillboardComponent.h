#pragma once

//이후 수정용 만들기

#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIBillboardComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIBillboardComponent();
	virtual ~CIMGUIBillboardComponent();

private:
	class CIMGUIText* m_MaterialName;

	class CMaterial* m_Material;

	class CIMGUIText* m_TextureName;
	class CIMGUIButton* m_TextureChangeButton;
	class CIMGUIFileDialogWidget* m_FileDialog;

	class CIMGUIDrag* m_EditorTime;
public:
	void UpdateInfo(class CSceneComponent* _Component);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);


	void ButtonTextureChangeCallback();
	void FileDialogWidget_TextureChangeCallback(std::string FileName);
};
