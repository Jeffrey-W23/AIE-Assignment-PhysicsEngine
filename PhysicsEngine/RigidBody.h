// #includes, using, etc
#pragma once
#include "PhysicsObject.h"

//--------------------------------------------------------------------------------------
// Rigidbody object. Inherits from PhysicsObject.
//--------------------------------------------------------------------------------------
class Rigidbody : public PhysicsObject 
{
public:
	
	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//
	// Param:
	//		eShapeID: the shapeID of the rigidbody.
	//		v2Position: the position of the rigidbody.
	//		v2Velocity: the velocity of the rigidbody. 
	//		fRotation: the rotation of the rigidbody.
	//		fMass: the mass of the rigidbody.
	//--------------------------------------------------------------------------------------
	Rigidbody(EShapeType eShapeID, glm::vec2 v2Position, glm::vec2 v2Velocity, float fRotation, float fMass, float fLinearDrag, float fAngularDrag, float fElasticity);

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~Rigidbody();

	//--------------------------------------------------------------------------------------
	// FixedUpdate: A function to update objects over time.
	//
	// Param:
	//		v2Gravity: vector2 gravity to apply to the update function.
	//		fTimeStep: float value for the time time step of the update.
	//--------------------------------------------------------------------------------------
	virtual void FixedUpdate(glm::vec2 v2Gravity, float fTimeStep);

	//--------------------------------------------------------------------------------------
	// Debug: Debugging function for this object.
	//--------------------------------------------------------------------------------------
	virtual void Debug() {}

	//--------------------------------------------------------------------------------------
	// ApplyForce: Apply force to this rigid body.
	//
	// Param:
	//		v2Force: a vector2 of the force to be applied.
	//--------------------------------------------------------------------------------------
	void ApplyForce(glm::vec2 v2Force);

	//--------------------------------------------------------------------------------------
	// ApplyForceToActor: Apply force to another rigidbody while applying negative 
	// force to this object.
	//
	// Param:
	//		pActor: Rigidbody pointer to apply force to.
	//		v2Force: a vector2 of the force to be applied.
	//--------------------------------------------------------------------------------------
	void ApplyForceToActor(Rigidbody* pActor, glm::vec2 v2Force);





	//--------------------------------------------------------------------------------------
	// ResolveCollision: Resolve a collision between 2 shapes with a rigidbody.
	//
	// Param:
	//		pActor: the object being collided with.
	//--------------------------------------------------------------------------------------
	void ResolveCollision(Rigidbody* pActor);
	





	//--------------------------------------------------------------------------------------
	// SetPosition: Set the position of the rigidbody.
	//
	// Param:
	//		v2Position: the position to set the rigidbody to.
	//--------------------------------------------------------------------------------------
	void SetPosition(glm::vec2 v2Position) { m_v2Position = v2Position; }






	//--------------------------------------------------------------------------------------
	// GetPosition: Get the position of the rigidbody.
	//
	// Return:
	//		Vector2: the postion of the rigidbody
	//--------------------------------------------------------------------------------------
	glm::vec2 GetPosition() { return m_v2Position; }

	//--------------------------------------------------------------------------------------
	// GetRotation: Get the rotation of the rigidbody.
	//
	// Return:
	//		float: the rotation of the rigidbody.
	//--------------------------------------------------------------------------------------
	float GetRotation() { return m_fRotation; }

	//--------------------------------------------------------------------------------------
	// GetVelocity: Get the velocity of the rigidbody.
	//
	// Return:
	//		Vector2: the velocity of the rigidbody.
	//--------------------------------------------------------------------------------------
	glm::vec2 GetVelocity() { return m_v2Velocity; }

	//--------------------------------------------------------------------------------------
	// GetMass: Get the mass of the rigidbody.
	//
	// Return:
	//		float: the mass of the rigidbody.
	//--------------------------------------------------------------------------------------
	float GetMass() { return m_fMass; }

	//--------------------------------------------------------------------------------------
	// SetVelocity: Set the velocity of the rigidbody.
	//
	// Param:
	//		v2Value: A vector2 value to set the velocity.
	//--------------------------------------------------------------------------------------
	void SetVelocity(glm::vec2 v2Value) { m_v2Velocity = v2Value; }









	float GetLinearDrag() { return m_fLinearDrag; }
	float GetAngularDrag() { return m_fAngularDrag; }
	float GetElasticity() { return m_fElasticity; }










protected:
	
	//--------------------------------------------------------------------------------------
	// A Vector2 for the position of the rigidbody.
	//--------------------------------------------------------------------------------------
	glm::vec2 m_v2Position;

	//--------------------------------------------------------------------------------------
	// A Vector2 for the velocity of rigidbody.
	//--------------------------------------------------------------------------------------
	glm::vec2 m_v2Velocity;

	//--------------------------------------------------------------------------------------
	// A float for the mass of the rigidbody.
	//--------------------------------------------------------------------------------------
	float m_fMass;

	//--------------------------------------------------------------------------------------
	// A float for the roaation of the rigidbody
	//--------------------------------------------------------------------------------------
	float m_fRotation;








	float m_fAngularVelocity;
	float m_fLinearDrag;
	float m_fAngularDrag;
	float m_fElasticity;
};