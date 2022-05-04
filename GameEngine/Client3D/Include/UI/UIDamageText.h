#pragma once
#include "GameObject.h"
#include "UI\WidgetWindow.h"
#include <UI/Text.h>
#include <UI/Image.h>
class CUIDamageText :
	public CWidgetWindow
{

public:
	CUIDamageText();
	CUIDamageText(const CUIDamageText& widget);
	~CUIDamageText();

private:
	bool m_Update;
	CSharedPtr<CImage> m_Image100;
	CSharedPtr<CImage> m_Image10;
	CSharedPtr<CImage> m_Image1;
	Vector3 m_TargetPos;
	float m_Alpha;
	float m_LifeTime;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CUIDamageText* Clone();

	void SetDamage(int Damage);
	void SetTargetPos(const Vector3& Pos)
	{
		m_TargetPos = Pos;
	}
	void SetNumberImage(CImage* Image, int Number);
};

