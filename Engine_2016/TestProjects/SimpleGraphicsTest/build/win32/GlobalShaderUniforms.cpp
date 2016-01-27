#include "GlobalShaderUniforms.h"


GlobalShaderUniforms::GlobalShaderUniforms(graphics::Shader* shader, const SharedShaderValues* sharedShaderValues = 0) : ShaderUniforms(shader)
{
	m_sharedShaderValues = sharedShaderValues;
}


GlobalShaderUniforms::~GlobalShaderUniforms()
{
}
