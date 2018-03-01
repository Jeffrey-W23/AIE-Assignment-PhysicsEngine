// #includes, using, etc
#pragma once
#include "Rigidbody.h"

//--------------------------------------------------------------------------------------
// Sphere object. Inherits from Rigidbody.
//--------------------------------------------------------------------------------------
class Sphere : public Rigidbody
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	Sphere() = delete;
	//--------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	// Constructor.
	//
	// Param:
	//		v3Position: a vector3 for sphere postion.
	//		v3Velocity: a vector3 for sphere velocity.
	//		fMass: a float value for sphere mass.
	//		fRadius: a float value for sphere radius.
	//		v4Color: a vector4 for sphere color.
	//--------------------------------------------------------------------------------------
	Sphere(glm::vec3 v3Position, glm::vec3 v3Velocity, float fMass, float fRadius, glm::vec4 v4Color);

	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	~Sphere();

	//--------------------------------------------------------------------------------------
	// MakeGizmo: Virtual function to make gizmo.
	//--------------------------------------------------------------------------------------
	virtual void MakeGizmo();

	//--------------------------------------------------------------------------------------
	// GetRadius: Get the radius of the sphere.
	//
	// Return:
	//		float: a float value for the radius of the sphere.
	//--------------------------------------------------------------------------------------
	float GetRadius() { return m_fRadius; }

	//--------------------------------------------------------------------------------------
	// GetColour: Get the color of the sphere.
	//
	// Return:
	//		Vector4: a Vector4 for the sphere color.
	//--------------------------------------------------------------------------------------
	glm::vec4 GetColour() { return m_v4Color; }

protected:
	
	//--------------------------------------------------------------------------------------
	// float value for the readius of the sphere.
	//--------------------------------------------------------------------------------------
	float m_fRadius;

	//--------------------------------------------------------------------------------------
	// a vector4 for the sphere color.
	//--------------------------------------------------------------------------------------
	glm::vec4 m_v4Color;
};

