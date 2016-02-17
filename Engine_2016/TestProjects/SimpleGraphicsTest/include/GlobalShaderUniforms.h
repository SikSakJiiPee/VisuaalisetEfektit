#ifndef GLOBALSHADERUNIFORMS_H
#define GLOBALSHADERUNIFORMS_H

#include "graphics\Shader.h"
#include "MyMaterials.h"

class GlobalShaderUniforms : public graphics::ShaderUniforms
{
public:
	GlobalShaderUniforms(graphics::Shader* shader, const SharedShaderValues* sharedShaderValues = 0);
	virtual ~GlobalShaderUniforms();

	virtual void getUniformLocations(graphics::Shader* shader);
	virtual void bind(graphics::Shader* shader);

private:
	const SharedShaderValues* m_sharedShaderValues;
	GLint m_ids[8];
};

#endif