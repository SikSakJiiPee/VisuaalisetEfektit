#ifndef MYMATERIALS_H
#define MYMATERIALS_H

struct SharedShaderValues : public core::Object
{
	float totalTime;
	slmath::mat4 matModelViewProj; //Model view projection matrix. Used to transform position vertices to clip space.
};




#endif