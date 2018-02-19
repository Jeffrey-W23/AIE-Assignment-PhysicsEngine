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
	//		v2Normal: a vector2 for the normal of the plane.
	//		fDistance: a float value for the distance of the plane. 
	//--------------------------------------------------------------------------------------
	Plane(glm::vec2 v2Normal, float fDistance);

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~Plane(); 

	//--------------------------------------------------------------------------------------
	// FixedUpdate: A function to update objects over time.
	//
	// Param:
	//		v2Gravity: vector2 gravity to apply to the update function.
	//		fTimeStep: float value for the time time step of the update.
	//--------------------------------------------------------------------------------------
	virtual void FixedUpdate(glm::vec2 v2Gravity, float fTimeStep) {}

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














	void ResolveCollision(Rigidbody* actor2);








	//--------------------------------------------------------------------------------------
	// GetNormal: Get the normal of the plane.
	//
	// Return:
	//		Vector2: the normal of the plane.
	//--------------------------------------------------------------------------------------
	glm::vec2 GetNormal() { return m_v2Normal; }

	//--------------------------------------------------------------------------------------
	// GetDistance: get the distance to orgin of the plane.
	//
	// Return:
	//		float: the distance to orgin of the plane.
	//--------------------------------------------------------------------------------------
	float GetDistance() { return m_fDistanceToOrigin; }

protected: 

	//--------------------------------------------------------------------------------------
	// A vector2 for the normal
	//--------------------------------------------------------------------------------------
	glm::vec2 m_v2Normal;

	//--------------------------------------------------------------------------------------
	// A float for the dsitance to Origin.
	//--------------------------------------------------------------------------------------
	float m_fDistanceToOrigin;
};

