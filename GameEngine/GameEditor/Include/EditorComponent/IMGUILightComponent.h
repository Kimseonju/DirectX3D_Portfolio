#pragma once
#include "IMGUIWidgetComponent.h"
#include "Component/LightComponent.h"
#include "GameObject.h"
class CIMGUILightComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUILightComponent();
	virtual ~CIMGUILightComponent();

private:
	CSharedPtr<CLightComponent> m_Component;
	class CIMGUIRadioButton* m_LightTypeRadioBtn;

	class CIMGUIDrag* m_InputDistance;

	class CIMGUIDrag* m_InputDiffuseR;
	class CIMGUIDrag* m_InputDiffuseG;
	class CIMGUIDrag* m_InputDiffuseB;
	class CIMGUIDrag* m_InputDiffuseA;

	class CIMGUIDrag* m_InputAmbientR;
	class CIMGUIDrag* m_InputAmbientG;
	class CIMGUIDrag* m_InputAmbientB;
	class CIMGUIDrag* m_InputAmbientA;

	class CIMGUIDrag* m_InputSpecularR;
	class CIMGUIDrag* m_InputSpecularG;
	class CIMGUIDrag* m_InputSpecularB;
	class CIMGUIDrag* m_InputSpecularA;

public:
	void ComponentUpdateInfo(CSceneComponent* Component);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	void LightTypeRadiobtnListCallback(int SelectIndex, const char* Item);
public:
	void InputDistance();

	void InputDiffuseR();
	void InputDiffuseG();
	void InputDiffuseB();
	void InputDiffuseA();

	void InputAmbientR();
	void InputAmbientG();
	void InputAmbientB();
	void InputAmbientA();

	void InputSpecularR();
	void InputSpecularG();
	void InputSpecularB();
	void InputSpecularA();

};
