#pragma once

//이후 수정용 만들기

#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIAnimationMeshComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIAnimationMeshComponent();
	virtual ~CIMGUIAnimationMeshComponent();

private:
	class CAnimation* m_Animation;

private:
	class CIMGUIText* m_MeshName;
	class CIMGUIText* m_AnimationName;
	
	class CIMGUIFileDialogWidget* m_FileDialog;
	class CAnimationMeshComponent* m_Component;

	class CIMGUISlider* m_Frame;
	class CIMGUIText* m_RootBoneName;
	class CIMGUIButton* m_SelectRootBoonButton;
	class CIMGUIButton* m_SelectAnimSequenceButton;
	class CIMGUIDrag* m_MoveRootMotionPosX;
	class CIMGUIDrag* m_MoveRootMotionPosY;
	class CIMGUIDrag* m_MoveRootMotionPosZ;
	class CIMGUIDrag* m_EditorFrameTime;

	class CIMGUICheckBox* m_Editor;

	class CIMGUICheckBox* m_RootMotionEnable;
	class CIMGUICheckBox* m_RootMotionX;
	class CIMGUICheckBox* m_RootMotionY;
	class CIMGUICheckBox* m_RootMotionZ;
public:
	virtual void ComponentUpdateInfo(CSceneComponent* Component);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	void EditorCallback(bool _Editor);
	void EditorFrameCallback();
	void EditorFrameTimeCallback();

	void PopupBoonButtonCallback();
	void PopupBoonCloseButtonCallback();
	void AnimSequenceCallback();

	void RootBonePopupComboCallback(int SelectIndex, const char* Item);
	void PopupAnimSequenceCallback(std::string FileName);

	void RootMotionEnableCallback(bool _Enable);
	void RootMotionXCallback(bool _Enable);
	void RootMotionYCallback(bool _Enable);
	void RootMotionZCallback(bool _Enable);
};
