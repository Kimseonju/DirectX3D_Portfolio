#pragma once

#include "WidgetWindow.h"
#include "ProgressBar.h"

class CMultiProgressBar :
	public CWidgetWindow
{
	friend class CViewport;
	friend class CScene;
	friend class CWidgetWindow;

private:
	std::vector<CProgressBar*> m_vecProgressBar;

protected:
	CMultiProgressBar();
	CMultiProgressBar(const CMultiProgressBar& widget);
	virtual ~CMultiProgressBar();

protected:
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMultiProgressBar* Clone();
public:
	void SetBarCount(int Count);
	void SetPos(float x, float y);
	void SetPos(const Vector2& Pos);
	
	void SetSize(float x, float y);
	void SetSize(const Vector2& Size);
	void SetPercent(float Percent);
	bool SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);

	bool SetBackTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTint(float r, float g, float b, float a);
	void SetBackTint(float r, float g, float b, float a);
};

