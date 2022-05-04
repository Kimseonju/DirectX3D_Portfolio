#pragma once
#include "IMGUIWindow.h"
#include "IMGUIWidget.h"

class CIMGUIWidgetComponent
{
	
public:
	CIMGUIWidgetComponent();
	virtual ~CIMGUIWidgetComponent();

protected:
	CIMGUIWindow* m_Owner;
	std::vector<CIMGUIWidget*> m_vecWidgetComponent;
	class CIMGUICollapsingHeader* m_Header;
	bool m_Enable;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Enable(bool Enable);
	virtual bool IsEnable() const
	{
		return m_Enable;
	}
	void SetOwner(CIMGUIWindow* Owner)
	{
		m_Owner = Owner;
	}

	template <typename T>
	T* AddComponentWidget(const std::string& Name, float SizeX = 100.f, float SizeY = 100.f)
	{
		T* Component=m_Owner->AddWidget<T>(Name, SizeX, SizeY);

		m_vecWidgetComponent.push_back(Component);
		return Component;
	}
public:
	virtual void ComponentUpdateInfo(CSceneComponent* Component);
};

