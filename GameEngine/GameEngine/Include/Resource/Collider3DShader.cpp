
#include "Collider3DShader.h"

CCollider3DShader::CCollider3DShader()
{
}

CCollider3DShader::~CCollider3DShader()
{
}

bool CCollider3DShader::Init()
{
    if (!LoadVertexShader(m_Name, "ColliderVS", TEXT("Collider.fx"), SHADER_PATH))
        return false;

    if (!LoadPixelShader(m_Name, "Collider3DPS", TEXT("Collider.fx"), SHADER_PATH))
        return false;

    AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);

    if (!CreateInputLayout())
        return false;

    return true;
}
