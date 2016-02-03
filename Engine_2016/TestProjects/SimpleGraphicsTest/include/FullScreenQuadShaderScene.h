#ifndef FSQ_H_
#define FSQ_H_

#include "scene.h"
#include "GlobalShaderUniforms.h"
#include "MyMaterials.h"

#include <core/log.h>
#include <graphics/Shader.h>


class FullScreenQuadShaderScene : public Scene
{
public:
	FullScreenQuadShaderScene()
	{
		
		LOG("TriangleScene construct");
		checkOpenGL();

		m_count = 0.0f;
		m_hShaderProgram = 0;
		m_sharedValues.totalTime = 0.0f;


		FRM_SHADER_ATTRIBUTE attributes[] = {
			{"g_vVertex", 0 },
			{"g_vColor", 1 },
			{"g_vTexCoord", 2 }
		};

		int numAttributes = sizeof(attributes) / sizeof(FRM_SHADER_ATTRIBUTE);
		m_shader = new graphics::Shader("assets/FullScreenQuad.vs", "assets/PlasmaEffect.fs", attributes, numAttributes);

		
		m_material = new GlobalShaderUniforms(m_shader, &m_sharedValues);
		m_material->bind();


		checkOpenGL();
	}


	virtual ~FullScreenQuadShaderScene()
	{
		glDeleteProgram( m_hShaderProgram );
		LOG("TriangleScene destruct");
	}


    virtual void update( graphics::ESContext* esContext, float deltaTime )
	{
		m_sharedValues.totalTime += deltaTime;

	/*	if( m_count > 1.0f )
			m_count = 0.0f;*/
	}


	virtual void render(graphics::ESContext* esContext)
	{
		checkOpenGL();

		// Set the viewport
		glViewport( 0, 0, esContext->width, esContext->height );
		checkOpenGL();

		float aspectRatio = float(esContext->width)/float(esContext->height);
		float fSize = 1.0;
		float VertexPositions[] =
		{
			fSize, fSize, 1.0f, 1.0f,
			-fSize, fSize, 1.0f, 1.0f,
			fSize, -fSize, 1.0f, 1.0f,
			fSize, -fSize, 1.0f, 1.0f,
			-fSize, -fSize, 1.0f, 1.0f,
			-fSize, fSize, 1.0f, 1.0f,

		};

		float VertexColors[] = {1.0f, 0.0f, 0.0f, 1.0f,
								0.0f, 1.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 1.0f, 1.0f,
								0.0f, 0.0f, 1.0f, 1.0f,
								1.0f, 0.0f, 0.0f, 1.0f,
								0.0f, 1.0f, 0.0f, 1.0f
							   };
		
		float VertexTexCoords[] = { 
			1.0f, 0.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
		};

		// Clear the backbuffer and depth-buffer
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		checkOpenGL();

		m_material->bind();
		m_material->getUniformLocations(m_shader);

		// Draw the colored triangle
		glVertexAttribPointer( 0, 4, GL_FLOAT, 0, 0, VertexPositions );
		checkOpenGL();

		glEnableVertexAttribArray( 0 );
		checkOpenGL();

		glVertexAttribPointer( 1, 4, GL_FLOAT, 0, 0, VertexColors);
		checkOpenGL();
		glEnableVertexAttribArray( 1 );
		checkOpenGL();

		glVertexAttribPointer(2, 2, GL_FLOAT, 0, 0, VertexTexCoords);
		checkOpenGL();
		glEnableVertexAttribArray(2);
		checkOpenGL();

		glDrawArrays( GL_TRIANGLE_STRIP, 0, 6 );
		checkOpenGL();

		glDisableVertexAttribArray( 0 );
		checkOpenGL();
		glDisableVertexAttribArray( 1 );
		checkOpenGL();
		glDisableVertexAttribArray(2);
		checkOpenGL();
	}
private:
	float m_count;
	
	GLuint       m_hShaderProgram;

	core::Ref<graphics::Shader> m_shader;

	SharedShaderValues m_sharedValues;
	core::Ref<graphics::ShaderUniforms> m_material;
};


#endif

