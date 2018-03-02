// #includes, using, etc
#include "Plane.h"
#include <Gizmos.h>
#include "PhysicsObject.h"
#include <glm\ext.hpp>

//--------------------------------------------------------------------------------------
// Constructor.
//
// Param:
//		v3Normal: a vector3 for the normal of the plane.
//		fDistance: a float value for the distance of the plane. 
//--------------------------------------------------------------------------------------
Plane::Plane(glm::vec3 v3Normal, float fDistance) : PhysicsObject(ESHAPETYPE_PLANE)
{
	// set defaults
	m_fDistanceToOrigin = fDistance;
	m_v3Normal = v3Normal;
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
	glm::vec3 v3Parallel(m_v3Normal.y, -m_v3Normal.x, 0);
	glm::vec3 v3CenterPoint = m_v3Normal * m_fDistanceToOrigin;
	glm::vec4 v4Colour(1, 1, 1, 1); 
	glm::vec3 v3Start = v3CenterPoint + (v3Parallel * fLineSegmentLength);
	glm::vec3 v3End = v3CenterPoint - (v3Parallel * fLineSegmentLength);
	
	// Having trouble getting this to draw. add back later
	//aie::Gizmos::add2DLine(v2Start, v2End, v4Colour);
	//aie::Gizmos::addDisk(v3Start, 100, 4, v4Colour);
	//aie::Gizmos::addAABB(v3Start, v3End, v4Colour);
}

//--------------------------------------------------------------------------------------
// ResolveCollision: Resolve a collision between 2 shapes with a rigidbody.
//
// Param:
//		pActor: the object being collided with.
//		v3Contact: contact point between 2 shapes.
//--------------------------------------------------------------------------------------
void Plane::ResolveCollision(Rigidbody* pActor)//, glm::vec3 v3Contact)
{
	// Calculate velocity and normal
	glm::vec3 v3Normal = m_v3Normal;
	glm::vec3 v3RelativeVelocity = pActor->GetVelocity();

	//Calculate the J formula and the elastcity.
	float fElasticity = pActor->GetElasticity();
	
	//float fJFormula = glm::dot(-(1 + fElasticity) * (v3RelativeVelocity), v3Normal) / (1 / pActor->GetMass());

	float fJFormula = glm::dot(-(1 + fElasticity) * (v3RelativeVelocity), v3Normal) / glm::dot(v3Normal, v3Normal * (1 / pActor->GetMass()));

	// Calculate force.
	glm::vec3 v3Force = v3Normal * fJFormula;

	// Apply the force to other object.
	pActor->ApplyForce(v3Force);//, v3Contact - pActor->GetPosition());
}