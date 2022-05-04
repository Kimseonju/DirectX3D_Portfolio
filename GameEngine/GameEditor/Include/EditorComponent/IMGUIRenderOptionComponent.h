#pragma once
#include "IMGUIWidgetComponent.h"
//Transform
class CIMGUIRenderOptionComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIRenderOptionComponent();
	virtual ~CIMGUIRenderOptionComponent();

private:
	class CIMGUICheckBox* m_OutLine;
	class CIMGUICheckBox* m_CelShader;
	class CIMGUICheckBox* m_ToonShader;
	class CIMGUICheckBox* m_FXAA;
	class CRenderManager* m_RenderManager;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	void OutLineCheckBoxClick(bool Enable);
	void CelShaderCheckBoxClick(bool Enable);
	void ToonShaderCheckBoxClick(bool Enable);
	void FXAACheckBoxClick(bool Enable);
};
