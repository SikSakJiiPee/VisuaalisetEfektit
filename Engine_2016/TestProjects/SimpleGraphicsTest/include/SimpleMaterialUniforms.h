#pragma once

#include <graphics\Shader.h>
#include <core/Ref.h>

#include "MyMaterials.h"
#include "GlobalShaderUniforms.h"

class SimpleMaterialUniforms : public graphics::ShaderUniforms
{
public:
	slmath::vec4 vAmbient; //Ambient color of the material (rgba)
	slmath::vec4 vDiffuse; //Ambient color of the material (rgba)
	slmath::vec4 vSpecular; //Specular color of the material (rgb). Specular exponent (a)

	SimpleMaterialUniforms(graphics::Shader* shader, SharedShaderValues* sharedValues = 0)
		: ShaderUniforms(shader)
		, m_globalShaderUniforms(new GlobalShaderUniforms(shader,sharedValues))
	{
	}

	virtual ~SimpleMaterialUniforms()
	{
	}

	virtual void getUniformLocations(graphics::Shader* shader)
	{
		m_globalShaderUniforms->getUniformLocations(shader);
		m_materialAmbientLoc = glGetUniformLocation(shader->getProgram(), "g_Material.vAmbient");
		m_materialDiffuseLoc = glGetUniformLocation(shader->getProgram(), "g_Material.vDiffuse");
		m_materialSpecularLoc = glGetUniformLocation(shader->getProgram(), "g_Material.vSpecular");
	}

	virtual void bind(graphics::Shader* shader)
	{
		shader->bind();
		m_globalShaderUniforms->bind(shader);
		glUniform4fv(m_materialAmbientLoc, 1, &vAmbient.x);
		glUniform4fv(m_materialDiffuseLoc, 1, &vDiffuse.x);
		glUniform4fv(m_materialSpecularLoc, 1, &vSpecular.x);
	}



private:
	core::Ref<GlobalShaderUniforms> m_globalShaderUniforms;
	GLint m_materialAmbientLoc;
	GLint m_materialDiffuseLoc;
	GLint m_materialSpecularLoc;
};