#pragma once
#include "Scene/SceneMode.h"
#include "Component/Camera.h"
#include "Component/SpringArm3D.h"

class CEffectTestScene :
    public CSceneMode
{
    friend class CScene;

private:

protected:
    CEffectTestScene();
    virtual ~CEffectTestScene();

public:
    virtual bool Init();
    virtual void Start();

public:
    bool CreateMaterial();

};

