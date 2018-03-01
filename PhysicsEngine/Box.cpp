// #includes, using, etc
#include "Box.h"
#include <Gizmos.h>

//--------------------------------------------------------------------------------------
// Constructor.
//
// Param:
//		v3Position: a vector3 for box postion.
//		v3Velocity: a vector3 for box velocity.
//		fMass: a float value for box mass.
//		fWidth: a float value for the box width.
//		fHeight: a float value for the box height.
//		v4Color: a vector4 for box color.
//--------------------------------------------------------------------------------------
Box::Box(glm::vec3 v3Position, glm::vec3 v3Velocity, float fMass, float fX, float fY, float fZ, glm::vec4 v4Color) : Rigidbody(ESHAPETYPE_BOX, v3Position, v3Velocity, 0, fMass, 0.2f, 0.2f, 0.8f)
{
	// set defaults
	m_fX = fX;
	m_fY = fY;
	m_fZ = fZ;
	m_v3Dimensions = glm::vec3(m_fX, m_fY, m_fZ);
	m_v4Colour = v4Color;
}

//--------------------------------------------------------------------------------------
// Default Destructor.
//--------------------------------------------------------------------------------------
Box::~Box()
{
}

//--------------------------------------------------------------------------------------
// MakeGizmo: Virtual function to make gizmo.
//--------------------------------------------------------------------------------------
void Box::MakeGizmo()
{
	// Create a filled aabb box
	aie::Gizmos::addAABBFilled(m_v3Position, m_v3Dimensions, m_v4Colour);
}