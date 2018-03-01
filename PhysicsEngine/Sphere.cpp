// #includes, using, etc
#include "Sphere.h"
#include <Gizmos.h>

//--------------------------------------------------------------------------------------
// Default Constructor.
//
// Param:
//		v3Position: a vector3 for sphere postion.
//		v3Velocity: a vector3 for sphere velocity.
//		fMass: a float value for sphere mass.
//		fRadius: a float value for sphere radius.
//		v4Color: a vector4 for sphere color.
//--------------------------------------------------------------------------------------
Sphere::Sphere(glm::vec3 v3Position, glm::vec3 v3Velocity, float fMass, float fRadius, glm::vec4 v4Color) : Rigidbody(ESHAPETYPE_SPHERE, v3Position, v3Velocity, 0, fMass, 0.2f, 0.2f, 0.8f)
{
	// set sphere radius
	m_fRadius = fRadius;
	
	// set sphere color.
	m_v4Color = v4Color;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Sphere::~Sphere()
{
}

//--------------------------------------------------------------------------------------
// MakeGizmo: Virtual function to make gizmo.
//--------------------------------------------------------------------------------------
void Sphere::MakeGizmo()
{
	// Add a sphere gizmo.
	aie::Gizmos::addSphere(m_v3Position, m_fRadius, 12, 12, m_v4Color);
}
