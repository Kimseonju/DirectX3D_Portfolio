
#include "FullScreenShader.h"

CFullScreenShader::CFullScreenShader()
{
}

CFullScreenShader::~CFullScreenShader()
{
}

bool CFullScreenShader::Init()
{
    if (!LoadVertexShader(m_Name, "FullScreenVS", TEXT("PostProcess.fx"), SHADER_PATH))
        return false;

    if (!LoadPixelShader(m_Name, "FullScreenPS", TEXT("PostProcess.fx"), SHADER_PATH))
        return false;

    return true;
}
