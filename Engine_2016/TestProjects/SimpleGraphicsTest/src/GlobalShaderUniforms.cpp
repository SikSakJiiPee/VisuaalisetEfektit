#include "GlobalShaderUniforms.h"


GlobalShaderUniforms::GlobalShaderUniforms(graphics::Shader* shader, const SharedShaderValues* sharedShaderValues) : ShaderUniforms(shader)
{
	m_sharedShaderValues = sharedShaderValues;
}


GlobalShaderUniforms::~GlobalShaderUniforms()
{
}


void GlobalShaderUniforms::getUniformLocations(graphics::Shader* shader) 
{
	m_id = glGetUniformLocation(shader->getProgram(), "totalTime");
}

void GlobalShaderUniforms::bind(graphics::Shader* shader) 
{
	shader->bind();
	if (m_sharedShaderValues)
	{
		glUniform1f(m_id, m_sharedShaderValues->totalTime);
	}
}