#pragma once
#include "Scene\SceneMode.h"
#include "../Editor.h"
class CEditorScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CEditorScene();
    virtual ~CEditorScene();

private:
    class CPrefabWindow* m_PrefabWindow;
    class CObjectWindow* m_ObjectWindow;
    int m_CloneObjectCount;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);

private:
	void MoveFront(float DeltaTime);
	void MoveBack(float DeltaTime);
	void LeftMove(float DeltaTime);
	void RightMove(float DeltaTime);
    void MouseLButton(float DeltaTime);
    void MouseRButton(float DeltaTime);
private:
    void AddObjectMap();
    void CreateParticle();

private:
	void CreateCollisionProfile();

};

