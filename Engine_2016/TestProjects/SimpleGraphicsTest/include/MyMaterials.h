#ifndef MYMATERIALS_H
#define MYMATERIALS_H

struct SharedShaderValues : public core::Object
{
	slmath::mat4 matModel;			
	slmath::mat4 matView;
	slmath::mat4 matProj;
	slmath::mat4 matModelView;
	slmath::mat4 matNormal;
	slmath::mat4 matModelViewProj; //Model view projection matrix. Used to transform position vertices to clip space.
	slmath::vec3 lightPos;
	slmath::vec3 camPos;
};




#endif