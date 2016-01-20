#ifndef GLOBALSHADERUNIFORMS_H
#define GLOBALSHADERUNIFORMS_H

#include "graphics\Shader.h"
#include "MyMaterials.h"

class GlobalShaderUniforms :
	public graphics::ShaderUniforms
{
public:
	GlobalShaderUniforms(graphics::Shader* shader, const SharedShaderValues* sharedShaderValues = 0);
	~GlobalShaderUniforms();

	virtual void getUniformLocations(graphics::Shader* shader) {}
	virtual void bind(graphics::Shader* shader) {}

private:
	graphics::Shader* m_shader;
	const SharedShaderValues* m_sharedShaderValues;
};

#endif