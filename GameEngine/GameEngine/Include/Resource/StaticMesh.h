#pragma once
#include "Mesh.h"
class CStaticMesh :
    public CMesh
{
    friend class CResourceManager;
    friend class CSceneResource;

protected:
    CStaticMesh();
    virtual ~CStaticMesh();
private:
    CSharedPtr<class CSkeleton> m_Skeleton;

public:
    class CSkeleton* GetSkeleton()  const
    {
        return m_Skeleton;
    }

public:
    virtual bool LoadMeshFullPathMultibyte(const char* FullPath);
    virtual void Render();
    virtual void Render(int MaterialSlotIndex);
    virtual void RenderInstancing(unsigned int Count);
    virtual void RenderInstancing(int MaterialSlotIndex, unsigned int Count);
    void SetSkeleton(class CSkeleton* Skeleton);

private:
    virtual bool ConvertFBX(class CFBXLoader* Loader, const char* FullPath);

protected:
    virtual bool SaveMesh(FILE* File);
    virtual bool LoadMesh(FILE* File);
};

