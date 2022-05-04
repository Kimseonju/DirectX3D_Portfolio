#pragma once
#include "StaticMeshComponent.h"
class CSkyComponent :
    public CStaticMeshComponent
{
	friend class CGameObject;

protected:
	CSkyComponent();
	CSkyComponent(const CSkyComponent& com);
	virtual ~CSkyComponent();

protected:

public:
	CStaticMesh* GetStaticMesh();
	virtual class CMesh* GetMesh()  const;
	virtual void SetMesh(class CMesh* pMesh);
	virtual void SetMesh(const std::string& Name);
	void SetSkyTextureFullPath(const std::string& Name, const TCHAR* FullPath);
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSkyComponent* Clone();
	virtual void RenderShadow(float DeltaTime);
public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

