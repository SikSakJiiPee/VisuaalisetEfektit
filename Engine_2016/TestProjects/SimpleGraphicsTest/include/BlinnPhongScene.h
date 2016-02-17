#pragma once

#include "scene.h"
#include "GlobalShaderUniforms.h"
#include "MyMaterials.h"
#include "teapot.h"

#include <core/log.h>
#include <graphics/Shader.h>
#include <graphics/Mesh.h>



class BlinnPhongScene : public Scene
{
public:
	BlinnPhongScene()
	{
		FRM_SHADER_ATTRIBUTE attributes[2] =
		{
			{ "g_vPositionsOS", graphics::ATTRIB_POSITION },
			{ "g_vNormalOS", graphics::ATTRIB_NORMAL }
		};

		core::Ref<graphics::Shader> shader =
			new graphics::Shader("assets/Simple3d.vs", "assets/Simple3d.fs",
			attributes, sizeof(attributes) / sizeof(FRM_SHADER_ATTRIBUTE));

		m_material = new GlobalShaderUniforms(shader, &m_sharedValues);

		//Create mesh
		m_mesh = createTeapotMesh();
	}
	virtual ~BlinnPhongScene(){}

	graphics::Mesh* createTeapotMesh()
	{
		//Create Index buffer
		graphics::IndexBuffer* ib = new graphics::IndexBuffer(TeapotData::indices, TeapotData::numIndices);

		//Create Vertex arrays
		graphics::VertexArray* va[] =
		{
			new graphics::VertexArrayImpl<slmath::vec3>(
			graphics::ATTRIB_POSITION, (slmath::vec3*)TeapotData::positions, TeapotData::numVertices),

			new graphics::VertexArrayImpl<slmath::vec3>(
			graphics::ATTRIB_NORMAL, (slmath::vec3*)TeapotData::normals, TeapotData::numVertices),
		};

		//Create vertex buffer from vertex arrays
		graphics::VertexBuffer* vb = new graphics::VertexBuffer(&va[0], sizeof(va) / sizeof(va[0]));

		//Return mesh from ib and vb
		return new graphics::Mesh(ib, vb);
	}


	virtual void update(graphics::ESContext *esContext, float m_totalTime)
	{
		time += m_totalTime;

		//Camera perspective matrix = field of view, ratio, near plane distance and far plane distance
		float fAspect = (float)esContext->width / (float)esContext->height;
		m_matProjection = slmath::perspectiveFovRH(
			slmath::radians(45.0f),
			fAspect,
			5.0f,
			1000.0f);

		//Look at view matrix = eye point, look at point and world up vector
		m_matView = slmath::lookAtRH(
			slmath::vec3(0.0f, 70.0f, 70.0f),
			slmath::vec3(0.0f, 15.0f, 0.0f),
			slmath::vec3(0.0f, 1.0f, 0.0f));

		//update teapot model matrix
		m_matModel = slmath::rotationX(-3.1415f*0.5f); //-90 degrees around x first
		m_matModel = slmath::rotationY(time) * m_matModel; //Rotate according to total time
		m_matModel = slmath::translation(slmath::vec3(0.0f, 0.0f, 0.0f)) * m_matModel; //Translate

		//calculate needed stuff for m_sharedValues
		m_sharedValues->matModel = m_matModel;
		m_sharedValues->matView = m_matView;
		m_sharedValues->matProj = m_matProjection;

		slmath::mat4 matModelView = m_matView * m_matModel;
		slmath::mat4 matModelViewProj = m_matProjection * matModelView;
		slmath::mat4 matNormal = slmath::transpose(slmath::inverse(matModelView));

		m_sharedValues->matModelView = matModelView;
		m_sharedValues->matNormal = matNormal;
		m_sharedValues->matModelViewProj = matModelViewProj;

		m_sharedValues->lightPos = slmath::vec3(0.0f, 70.0f, 70.0f);
		m_sharedValues->camPos = slmath::vec3(0.0f, 70.0f, 70.0f);
	}

	virtual void render(graphics::ESContext *esContext)
	{
		glViewport(0, 0, esContext->width, esContext->height);

		//Clear the backbuffer and depth-buffer
		glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		checkOpenGL();

		//Initialize GL state
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		checkOpenGL();

		//These values are needed to update for each mesh which is rendered (different model matrix)
		slmath::mat4 matModelView = m_matView * m_matModel;
		slmath::mat4 matModelViewProj = m_matProjection * matModelView;

		//Set matrix to shared values
		m_sharedValues.matModelViewProj = matModelViewProj;

		//Bind material (sets uniform values)
		m_material->bind();
		checkOpenGL();

		//Render the mesh using active material
		m_mesh->render();
		checkOpenGL();
	}

private:
	float time = 0;
	slmath::mat4 m_matProjection;
	slmath::mat4 m_matView;
	slmath::mat4 m_matModel;
	core::Ref<graphics::Mesh>m_mesh; 
	SharedShaderValues m_sharedValues;
	core::Ref<graphics::ShaderUniforms> m_material;
};
