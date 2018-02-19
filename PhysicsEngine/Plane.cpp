// #includes, using, etc
#include "Plane.h"
#include <Gizmos.h>
#include "PhysicsObject.h"
#include <glm\ext.hpp>

//--------------------------------------------------------------------------------------
// Constructor.
//
// Param:
//		v2Normal: a vector2 for the normal of the plane.
//		fDistance: a float value for the distance of the plane. 
//--------------------------------------------------------------------------------------
Plane::Plane(glm::vec2 v2Normal, float fDistance) : PhysicsObject(ESHAPETYPE_PLANE)
{
	// set defaults
	m_fDistanceToOrigin = fDistance;
	m_v2Normal = v2Normal;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Plane::~Plane()
{
}

//--------------------------------------------------------------------------------------
// MakeGizmo: Create the plane gizmo.
//--------------------------------------------------------------------------------------
void Plane::MakeGizmo() 
{
	// make the plane object
	float fLineSegmentLength = 300; 
	glm::vec2 v2Parallel(m_v2Normal.y, -m_v2Normal.x);
	glm::vec2 v2CenterPoint = m_v2Normal * m_fDistanceToOrigin;
	glm::vec4 v4Colour(1, 1, 1, 1); 
	glm::vec2 v2Start = v2CenterPoint + (v2Parallel * fLineSegmentLength);
	glm::vec2 v2End = v2CenterPoint - (v2Parallel * fLineSegmentLength);
	aie::Gizmos::add2DLine(v2Start, v2End, v4Colour);
}









void Plane::ResolveCollision(Rigidbody* pActor)
{
	glm::vec2 v2Normal = m_v2Normal;
	glm::vec2 v2RelativeVelocity = pActor->GetVelocity();

	float fElasticity = 1;
	float fJFormula = glm::dot(-(1 + fElasticity) * (v2RelativeVelocity), v2Normal) / glm::dot(v2Normal, v2Normal * (1 / pActor->GetMass()));

	glm::vec2 v2Force = v2Normal * fJFormula;

	pActor->ApplyForce(v2Force);
}