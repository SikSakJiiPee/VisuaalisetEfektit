#include "GlobalShaderUniforms.h"


GlobalShaderUniforms::GlobalShaderUniforms(graphics::Shader* shader, const SharedShaderValues* sharedShaderValues) : ShaderUniforms(shader)
{
	m_sharedShaderValues = sharedShaderValues;
}


GlobalShaderUniforms::~GlobalShaderUniforms()
{
}
