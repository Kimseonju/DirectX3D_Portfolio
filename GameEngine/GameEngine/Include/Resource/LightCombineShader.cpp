
#include "LightCombineShader.h"

CLightCombineShader::CLightCombineShader()
{
}

CLightCombineShader::~CLightCombineShader()
{
}

bool CLightCombineShader::Init()
{
    if (!LoadVertexShader(m_Name, "FullScreenVS", TEXT("PostProcess.fx"), SHADER_PATH))
        return false;

    if (!LoadPixelShader(m_Name, "LightCombinePS", TEXT("Light.fx"), SHADER_PATH))
        return false;

    return true;
}
