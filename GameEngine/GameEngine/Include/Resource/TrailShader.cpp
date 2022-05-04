
#include "TrailShader.h"

CTrailShader::CTrailShader()
{
}

CTrailShader::~CTrailShader()
{
}

bool CTrailShader::Init()
{
	if (!LoadVertexShader(m_Name, "TrailVS", TEXT("Trail.fx"),
		SHADER_PATH))
		return false;

	if (!LoadGeometryShader(m_Name, "TrailGS", TEXT("Trail.fx"),
		SHADER_PATH))
		return false;

	if (!LoadPixelShader(m_Name, "TrailPS", TEXT("Trail.fx"),
		SHADER_PATH))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,
		D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout())
		return false;

	return true;
}
