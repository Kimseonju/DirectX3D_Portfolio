#include "../pch.h"
#include "IMGUIAnimationMeshComponent.h"
#include "IMGUICollapsingHeader.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUISameLine.h"
#include "IMGUICheckBox.h"
#include "IMGUIButton.h"
#include "IMGUIDrag.h"
#include "IMGUIComboBox.h"
#include "Component/AnimationMeshComponent.h"
#include "Resource/Animation.h"
#include <Resource/Skeleton.h>
#include "IMGUIFileDialogWidget.h"
#include "IMGUISlider.h"
CIMGUIAnimationMeshComponent::CIMGUIAnimationMeshComponent()
{
}

CIMGUIAnimationMeshComponent::~CIMGUIAnimationMeshComponent()
{
}

void CIMGUIAnimationMeshComponent::ComponentUpdateInfo(CSceneComponent* Component)
{
	CAnimationMeshComponent* MeshComponent = (CAnimationMeshComponent*)Component;
	m_Component = MeshComponent;
	CMesh* Mesh = m_Component->GetMesh();
	m_MeshName->SetText(Mesh->GetName().c_str());
	m_Animation = m_Component->GetAnimation();

	m_Frame->SetInt(m_Animation->GetCurFrame());
	m_Frame->SetIntMinMax(0, m_Animation->GetEndFrame());
	m_RootBoneName->SetText(m_Animation->GetRootBoneName().c_str());
}

bool CIMGUIAnimationMeshComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("AnimationMesh");

#pragma region Name
	Text = AddComponentWidget<CIMGUIText>("AnimationMesh2");
	Text->SetText("MeshName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");

	m_MeshName = AddComponentWidget<CIMGUIText>("##AnimationMesh2", 100.f, 20.f);

#pragma endregion

#pragma region AnimationInfo

	Text = AddComponentWidget<CIMGUIText>("##AnimationInfo", 140.f,20.f);
	Text->SetText("AnimationInfo");


	Text = AddComponentWidget<CIMGUIText>("##AnimationName", 100.f, 20.f);
	Text->SetText("AnimationName");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_AnimationName = AddComponentWidget<CIMGUIText>("##AnimationName1", 200.f, 20.f);

	Text = AddComponentWidget<CIMGUIText>("##FrameText", 40.f,20.f);
	Text->SetText("Frame");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_Frame = AddComponentWidget<CIMGUISlider>("##Frame", 200.f, 20.f);
	m_Frame->SetNumberInt(true);
	m_Frame->SetInputCallback(this, &CIMGUIAnimationMeshComponent::EditorFrameCallback);

	Text = AddComponentWidget<CIMGUIText>("##RootBoneIndex",100.f,20.f);
	Text->SetText("RootBoneIndex");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_RootBoneName = AddComponentWidget<CIMGUIText>("##RootBoneName", 150.f,20.f);

	Text = AddComponentWidget<CIMGUIText>("##RootMotionPos");
	Text->SetText("RootMotionPos");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_MoveRootMotionPosX = AddComponentWidget<CIMGUIDrag>("##MoveRootMotionPosX", 60.f, 20.f);
	m_MoveRootMotionPosX->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_MoveRootMotionPosY = AddComponentWidget<CIMGUIDrag>("##MoveRootMotionPosY", 60.f, 20.f);
	m_MoveRootMotionPosY->SetNumberFloat(true);
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_MoveRootMotionPosZ = AddComponentWidget<CIMGUIDrag>("##MoveRootMotionPosZ", 60.f, 20.f);
	m_MoveRootMotionPosZ->SetNumberFloat(true);

	Text = AddComponentWidget<CIMGUIText>("##EditorFrameTime");
	Text->SetText("FrameTime");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_EditorFrameTime = AddComponentWidget<CIMGUIDrag>("##EditorFrameTime");
	m_EditorFrameTime->SetInputCallback<CIMGUIAnimationMeshComponent>(this, &CIMGUIAnimationMeshComponent::EditorFrameTimeCallback);
	m_EditorFrameTime->SetNumberFloat(true);

	Text = AddComponentWidget<CIMGUIText>("##EditorText");
	Text->SetText("Editor");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_Editor = AddComponentWidget<CIMGUICheckBox>("##EditorCheckBox");
	m_Editor->SetCheckCallback(this, &CIMGUIAnimationMeshComponent::EditorCallback);

	Text = AddComponentWidget<CIMGUIText>("##RootMotion1");
	Text->SetText("RootMotion");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_RootMotionEnable = AddComponentWidget<CIMGUICheckBox>("##RootMotionEnable", 20.f, 20.f);
	m_RootMotionEnable->SetCheckCallback(this, &CIMGUIAnimationMeshComponent::RootMotionEnableCallback);

	Text = AddComponentWidget<CIMGUIText>("##RootMotionPosText");
	Text->SetText("RootMotionPos");
	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_RootMotionX = AddComponentWidget<CIMGUICheckBox>("##RootMotionXCheckBox", 20.f, 20.f);
	m_RootMotionX->SetCheckCallback(this, &CIMGUIAnimationMeshComponent::RootMotionXCallback);

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_RootMotionY = AddComponentWidget<CIMGUICheckBox>("##RootMotionYCheckBox", 20.f, 20.f);
	m_RootMotionY->SetCheckCallback(this, &CIMGUIAnimationMeshComponent::RootMotionYCallback);

	SameLine = AddComponentWidget<CIMGUISameLine>("SameLine");
	m_RootMotionZ = AddComponentWidget<CIMGUICheckBox>("##RootMotionZCheckBox", 20.f, 20.f);
	m_RootMotionZ->SetCheckCallback(this, &CIMGUIAnimationMeshComponent::RootMotionZCallback);





	m_SelectRootBoonButton = AddComponentWidget<CIMGUIButton>("SelectRootBoon", 120.f, 20.f);
	m_SelectRootBoonButton->SetClickCallback(this, &CIMGUIAnimationMeshComponent::PopupBoonButtonCallback);


	m_SelectAnimSequenceButton = AddComponentWidget<CIMGUIButton>("SelectAnimSequence");
	m_SelectAnimSequenceButton->SetClickCallback(this, &CIMGUIAnimationMeshComponent::AnimSequenceCallback);
#pragma endregion

	m_Header->WidgetPush(m_vecWidgetComponent);
	m_vecWidgetComponent.push_back(m_Header);

	return true;
}

void CIMGUIAnimationMeshComponent::Update(float DeltaTime)
{
	if (m_Component)
	{

		m_Frame->SetInt(m_Animation->GetCurFrame());
		Vector3 RootMotionPos = m_Animation->GetRootMotionPos();

		m_MoveRootMotionPosX->SetFloat(RootMotionPos.x);
		m_MoveRootMotionPosY->SetFloat(RootMotionPos.y);
		m_MoveRootMotionPosZ->SetFloat(RootMotionPos.z);

		CAnimationSequence* Sequence = m_Animation->GetSequence();
		m_AnimationName->SetText(Sequence->GetName().c_str());
		m_RootMotionEnable->SetCheck(Sequence->IsRootMotion());
		m_RootMotionX->SetCheck(Sequence->IsRootMotionX());
		m_RootMotionY->SetCheck(Sequence->IsRootMotionY());
		m_RootMotionZ->SetCheck(Sequence->IsRootMotionZ());

		m_Frame->SetIntMinMax(0, m_Animation->GetEndFrame());
		//Sequence->


	}
}

void CIMGUIAnimationMeshComponent::EditorCallback(bool _Editor)
{
	m_Editor->SetCheck(_Editor);
	m_Animation->SetEditor(_Editor);
}

void CIMGUIAnimationMeshComponent::EditorFrameCallback()
{
	if (m_Editor)
	{
		int Frame = m_Frame->GetValueInt();

		float AnimationTime = Frame * m_Animation->GetSequence()->GetFrameTime();
		m_Animation->SetEditorTime(AnimationTime);
	}
}

void CIMGUIAnimationMeshComponent::EditorFrameTimeCallback()
{
	if (m_Editor)
	{
		float Time=m_EditorFrameTime->GetValueFloat();
		m_Animation->SetEditorTime(Time);
	}
}

void CIMGUIAnimationMeshComponent::PopupBoonButtonCallback()
{

	CIMGUIText* Text = m_Owner->AddPopupWidget<CIMGUIText>("RootBone");
	Text->SetText("RootBone");

	CIMGUIComboBox* ComponentCombo = m_Owner->AddPopupWidget<CIMGUIComboBox>("##AnimationMeshRootBoneCombo", 100.f, 100.f);

	ComponentCombo->SetSelectCallback<CIMGUIAnimationMeshComponent>(this, &CIMGUIAnimationMeshComponent::RootBonePopupComboCallback);


	std::vector<Bone*> vecBone;
	m_Animation->GetAllBone(vecBone);
	size_t Size = vecBone.size();

	for (size_t i = 0; i < Size; ++i)
	{
		ComponentCombo->AddItem(vecBone[i]->strName.c_str());
	}

	CIMGUIButton* PopupCloseButton = m_Owner->AddPopupWidget<CIMGUIButton>("BoneSelect", 100.f, 20.f);
	PopupCloseButton->SetText("BoneSelect");
	PopupCloseButton->SetClickCallback<CIMGUIAnimationMeshComponent>(this, &CIMGUIAnimationMeshComponent::PopupBoonCloseButtonCallback);

	m_Owner->SetPopupTitle("BoneSet");
	m_Owner->EnableModalPopup();
}

void CIMGUIAnimationMeshComponent::PopupBoonCloseButtonCallback()
{
	m_Owner->ClosePopup();
}

void CIMGUIAnimationMeshComponent::AnimSequenceCallback()
{
	if (m_FileDialog)
		return;
	m_FileDialog = m_Owner->AddWidget<CIMGUIFileDialogWidget>("IMGUIFileDialogWidget");
	m_FileDialog->FileDialogSetting("AnimSequenceSelect", "Choose File", ".sqc", "../Bin/Mesh", Vector2(300.f,200.f));
	m_FileDialog->SetClickCallback(this, &CIMGUIAnimationMeshComponent::PopupAnimSequenceCallback);
}

void CIMGUIAnimationMeshComponent::RootBonePopupComboCallback(int SelectIndex, const char* Item)
{
	m_Animation->SetRootBoneIndex(Item);
	m_RootBoneName->SetText(Item);
}

void CIMGUIAnimationMeshComponent::PopupAnimSequenceCallback(std::string FileName)
{
	CAnimationSequence* Sequence = m_Animation->FindSequence(FileName);

	if (Sequence)
	{
		m_Animation->ChangeAnimation(FileName);
	}
	else
	{
		//없음 적용안되면 이쪽확인하세요
		
	}
	m_Owner->DeleteWidget(m_FileDialog);
	m_FileDialog = nullptr;
}

void CIMGUIAnimationMeshComponent::RootMotionEnableCallback(bool _Enable)
{
	CAnimationSequence* Sequence = m_Animation->GetSequence();
	Sequence->SetRootMotion(_Enable);
}

void CIMGUIAnimationMeshComponent::RootMotionXCallback(bool _Enable)
{
	CAnimationSequence* Sequence = m_Animation->GetSequence();
	Sequence->SetRootMotionX(_Enable);
}

void CIMGUIAnimationMeshComponent::RootMotionYCallback(bool _Enable)
{
	CAnimationSequence* Sequence = m_Animation->GetSequence();
	Sequence->SetRootMotionY(_Enable);
}

void CIMGUIAnimationMeshComponent::RootMotionZCallback(bool _Enable)
{
	CAnimationSequence* Sequence = m_Animation->GetSequence();
	Sequence->SetRootMotionZ(_Enable);
}
