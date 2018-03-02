// #includes, using, etc
#pragma once
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include <glm\glm.hpp>

//--------------------------------------------------------------------------------------
// Plane object. Inherits from PhysicsObject.
//--------------------------------------------------------------------------------------
class Plane : public PhysicsObject
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Plane() = delete;

	//--------------------------------------------------------------------------------------
	// Constructor.
	//
	// Param:
	//		v3Normal: a vector3 for the normal of the plane.
	//		fDistance: a float value for the distance of the plane. 
	//--------------------------------------------------------------------------------------
	Plane(glm::vec3 v3Normal, float fDistance);

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~Plane(); 

	//--------------------------------------------------------------------------------------
	// FixedUpdate: A function to update objects over time.
	//
	// Param:
	//		v3Gravity: vector3 gravity to apply to the update function.
	//		fTimeStep: float value for the time time step of the update.
	//--------------------------------------------------------------------------------------
	virtual void FixedUpdate(glm::vec3 v3Gravity, float fTimeStep) {}

	//--------------------------------------------------------------------------------------
	// Debug: Debugging function for this object.
	//--------------------------------------------------------------------------------------
	virtual void Debug() {} 

	//--------------------------------------------------------------------------------------
	// MakeGizmo: Create the plane gizmo.
	//--------------------------------------------------------------------------------------
	virtual void MakeGizmo(); 

	//--------------------------------------------------------------------------------------
	// ResetPosition: Reset the postion of the plane.
	//--------------------------------------------------------------------------------------
	virtual void ResetPosition() {}

	//--------------------------------------------------------------------------------------
	// ResolveCollision: Resolve a collision between 2 shapes with a rigidbody.
	//
	// Param:
	//		pActor: the object being collided with.
	//		v3Contact: contact point between 2 shapes.
	//--------------------------------------------------------------------------------------
	void ResolveCollision(Rigidbody* pActor);//, glm::vec3 v3Contact);

	//--------------------------------------------------------------------------------------
	// GetNormal: Get the normal of the plane.
	//
	// Return:
	//		Vector3: the normal of the plane.
	//--------------------------------------------------------------------------------------
	glm::vec3 GetNormal() { return m_v3Normal; }

	//--------------------------------------------------------------------------------------
	// GetDistance: get the distance to orgin of the plane.
	//
	// Return:
	//		float: the distance to orgin of the plane.
	//--------------------------------------------------------------------------------------
	float GetDistance() { return m_fDistanceToOrigin; }

protected: 

	//--------------------------------------------------------------------------------------
	// A vector3 for the normal
	//--------------------------------------------------------------------------------------
	glm::vec3 m_v3Normal;

	//--------------------------------------------------------------------------------------
	// A float for the dsitance to Origin.
	//--------------------------------------------------------------------------------------
	float m_fDistanceToOrigin;
};

