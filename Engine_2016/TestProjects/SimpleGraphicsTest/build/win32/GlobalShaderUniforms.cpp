#include "GlobalShaderUniforms.h"


GlobalShaderUniforms::GlobalShaderUniforms(graphics::Shader* shader, const SharedShaderValues* sharedShaderValues)
{
	m_shader = shader;
	m_sharedShaderValues = sharedShaderValues;
}


GlobalShaderUniforms::~GlobalShaderUniforms()
{
}
