#pragma once
#include "../PublicData.h"
#include <UI/Button.h>
class CImage;
class CText;
class CValkyrieImageButton :
	public CButton
{
	friend class CViewport;
	friend class CScene;
	friend class CWidgetWindow;

protected:
	CValkyrieImageButton();
	virtual ~CValkyrieImageButton();

protected:
	
	CTexture* m_ValkyrieTexture;

public:
	void SetValkyrieTexture(CTexture* Texture)
	{
		m_ValkyrieTexture = Texture;
	}
public:


	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CValkyrieImageButton* Clone();
};

