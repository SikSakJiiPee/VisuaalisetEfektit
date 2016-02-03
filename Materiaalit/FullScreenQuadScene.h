#ifndef FSQ_H_
#define FSQ_H_

#include "scene.h"
#include <core/log.h>

class FullScreenQuadScene : public Scene
{
public:
	FullScreenQuadScene()
	{
		
		LOG("TriangleScene construct");
		checkOpenGL();

		m_count = 0.0f;
		m_hShaderProgram = 0;

		const char* g_strVSProgram = 
			"attribute vec4 g_vVertex;											 \n"
			"attribute vec4 g_vColor;											 \n"
			"attribute vec2 g_vTexCoord;										 \n"
			"varying   vec4 g_vVSColor;                                          \n"
			"varying   vec2 g_vVSTexCoord;                                       \n"
			"																	 \n"
			"void main()														 \n"
			"{																	 \n"
			"    gl_Position  = vec4( g_vVertex.x, g_vVertex.y,                  \n"
			"                         g_vVertex.z, g_vVertex.w );                \n"
			"    g_vVSColor = g_vColor;                                          \n"
			"    g_vVSTexCoord = g_vTexCoord;                                    \n"
			"}																	 \n";


		const char* g_strFSProgram =
			"#ifdef GL_FRAGMENT_PRECISION_HIGH									 \n"
			"   precision highp float;											 \n"
			"#else																 \n"
			"   precision mediump float;										 \n"
			"#endif																 \n"
			"																	 \n"
			"varying   vec4 g_vVSColor;                                          \n"
			"varying   vec2 g_vVSTexCoord;                                       \n"
			"\n"
			"uniform float totalTime;\n"
			"																	 \n"
			"void main()														 \n"
			"{																	 \n"
			"    float x = 256*g_vVSTexCoord.x;\n"
			"    float y = 256*g_vVSTexCoord.y;\n"
			"    float t = totalTime; \n"
			"    float v = 0.0;\n"
			"    v += 0.5 + (0.5 * sin(x/7.0+t));"
			"    v += 0.5 + (0.5 * sin(y/5.0-t));"
			"    v += 0.5 + (0.5 * sin((x+y)/6.0-t));"
			"    v += 0.5 + (0.5 * sin(sqrt((x*x + y*y))/4.0-t));"
			"    v = 0.25 * tan(2*v);\n"
			"    gl_FragColor = vec4(v,v*g_vVSTexCoord.x,v*g_vVSTexCoord.y,1.0);     \n"
			"}																	 \n";

		FRM_SHADER_ATTRIBUTE attributes[] = {
			{"g_vVertex", 0 },
			{"g_vColor", 1 },
			{"g_vTexCoord", 2 }
		};


		FrmCompileShaderProgram(g_strVSProgram,g_strFSProgram,
			&m_hShaderProgram,attributes,sizeof(attributes)/sizeof(FRM_SHADER_ATTRIBUTE) );

		checkOpenGL();
	}


	virtual ~FullScreenQuadScene()
	{
		glDeleteProgram( m_hShaderProgram );
		LOG("TriangleScene destruct");
	}


    virtual void update( graphics::ESContext* esContext, float deltaTime )
	{
		m_count += deltaTime;

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

		// Set the shader program and the texture
		glUseProgram( m_hShaderProgram );
		checkOpenGL();

		GLint loc = glGetUniformLocation(m_hShaderProgram, "totalTime");
		if (loc != -1)
		{
			glUniform1f(loc, 10.0f*m_count);
		}

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

};


#endif

