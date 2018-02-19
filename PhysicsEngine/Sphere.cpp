// #includes, using, etc
#include "Sphere.h"
#include <Gizmos.h>

//--------------------------------------------------------------------------------------
// Default Constructor.
//
// Param:
//		v2Position: a vector2 for sphere postion.
//		v2Velocity: a vector2 for sphere velocity.
//		fMass: a float value for sphere mass.
//		fRadius: a float value for sphere radius.
//		v4Color: a vector4 for sphere color.
//--------------------------------------------------------------------------------------
Sphere::Sphere(glm::vec2 v2Position, glm::vec2 v2Velocity, float fMass, float fRadius, glm::vec4 v4Color) : Rigidbody(ESHAPETYPE_SPHERE, v2Position, v2Velocity, 0, fMass, 0.2f, 0.2f, 0.8f)
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
	// Add a 2d circe gizmo.
	aie::Gizmos::add2DCircle(m_v2Position, m_fRadius, 12, m_v4Color);
}
