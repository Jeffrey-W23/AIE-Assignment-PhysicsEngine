#pragma once
#include "Camera.h"

class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	virtual void Update(float deltaTime);

protected:
	float m_fSpeed;
};

