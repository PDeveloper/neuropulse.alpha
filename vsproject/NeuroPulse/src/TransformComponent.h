#include <ac\es.h>

#pragma once
class TransformComponent : public ac::es::Component
{
	AC_ES_COMPONENT(TransformComponent)
public:

	float x;
	float y;
	float z;
	float rotationX;
	float rotationY;
	float rotationZ;
	
	TransformComponent(void)
	{
		x = y = z = 0.0;
		rotationX = rotationY = rotationZ = 0.0;
	}

	~TransformComponent(void)
	{
	}
};

