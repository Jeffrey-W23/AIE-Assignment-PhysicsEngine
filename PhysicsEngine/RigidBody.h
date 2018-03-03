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
	//		v3Position: the position of the rigidbody.
	//		v3Velocity: the velocity of the rigidbody. 
	//		fRotation: the rotation of the rigidbody.
	//		fMass: the mass of the rigidbody.
	//		fLinearDrag: the linear drag of the rigidbody.
	//		fAngularDrag: the angular drag of the rigidbody.
	//		fElasticity: the elasticity of the rigidbody.
	//--------------------------------------------------------------------------------------
	Rigidbody(EShapeType eShapeID, glm::vec3 v3Position, glm::vec3 v3Velocity, float fRotation, float fMass, float fLinearDrag, float fAngularDrag, float fElasticity);

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~Rigidbody();

	//--------------------------------------------------------------------------------------
	// FixedUpdate: A function to update objects over time each tick.
	//
	// Param:
	//		v3Gravity: vector3 gravity to apply to the update function.
	//		fTimeStep: float value for the time time step of the update.
	//--------------------------------------------------------------------------------------
	virtual void FixedUpdate(glm::vec3 v3Gravity, float fTimeStep);

	//--------------------------------------------------------------------------------------
	// Debug: Debugging function for this object.
	//--------------------------------------------------------------------------------------
	virtual void Debug() {}

	//--------------------------------------------------------------------------------------
	// ApplyForce: Apply force to this rigid body.
	//
	// Param:
	//		v3Force: a vector3 of the force to be applied.
	//--------------------------------------------------------------------------------------
	void ApplyForce(glm::vec3 v3Force);//, glm::vec3 v3Position);

	//--------------------------------------------------------------------------------------
	// ApplyForceToActor: Apply force to another rigidbody while applying negative 
	// force to this object.
	//
	// Param:
	//		pActor: Rigidbody pointer to apply force to.
	//		v3Force: a vector3 of the force to be applied.
	//--------------------------------------------------------------------------------------
	void ApplyForceToActor(Rigidbody* pActor, glm::vec3 v3Force);

	//--------------------------------------------------------------------------------------
	// ResolveCollision: Resolve a collision between 2 shapes with a rigidbody.
	//
	// Param:
	//		pActor: the object being collided with.
	//--------------------------------------------------------------------------------------
	void ResolveCollision(Rigidbody* pActor); //, glm::vec3 v3Contact, glm::vec3* v3pCollisionNormal=nullptr);
	
	//--------------------------------------------------------------------------------------
	// SetPosition: Set the position of the rigidbody.
	//
	// Param:
	//		v3Position: the position to set the rigidbody to.
	//--------------------------------------------------------------------------------------
	void SetPosition(glm::vec3 v3Position) { m_v3Position = v3Position; }

	//--------------------------------------------------------------------------------------
	// GetPosition: Get the position of the rigidbody.
	//
	// Return:
	//		Vector3: the postion of the rigidbody
	//--------------------------------------------------------------------------------------
	glm::vec3 GetPosition() { return m_v3Position; }

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
	//		Vector3: the velocity of the rigidbody.
	//--------------------------------------------------------------------------------------
	glm::vec3 GetVelocity() { return m_v3Velocity; }

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
	//		v3Value: A vector3 value to set the velocity.
	//--------------------------------------------------------------------------------------
	void SetVelocity(glm::vec3 v3Value) { m_v3Velocity = v3Value; }

	//--------------------------------------------------------------------------------------
	// GetLinearDrag: Get the linear drag of the rigidbody.
	//
	// Return:
	//		float: the linear drag of the rigidbody.
	//--------------------------------------------------------------------------------------
	float GetLinearDrag() { return m_fLinearDrag; }

	//--------------------------------------------------------------------------------------
	// GetAngularDrag: Get the angular drag of the rigidbody.
	//
	// Return:
	//		float: the angular drag of the rigidbody.
	//--------------------------------------------------------------------------------------
	float GetAngularDrag() { return m_fAngularDrag; }

	//--------------------------------------------------------------------------------------
	// GetElasticity: Get the elasticity of the rigidbody.
	//
	// Return:
	//		float: the elasticity of the rigidbody.
	//--------------------------------------------------------------------------------------
	float GetElasticity() { return m_fElasticity; }

protected:
	
	//--------------------------------------------------------------------------------------
	// A Vector3 for the position of the rigidbody.
	//--------------------------------------------------------------------------------------
	glm::vec3 m_v3Position;

	//--------------------------------------------------------------------------------------
	// A Vector3 for the velocity of rigidbody.
	//--------------------------------------------------------------------------------------
	glm::vec3 m_v3Velocity;

	//--------------------------------------------------------------------------------------
	// A float for the mass of the rigidbody.
	//--------------------------------------------------------------------------------------
	float m_fMass;

	//--------------------------------------------------------------------------------------
	// A float for the roaation of the rigidbody
	//--------------------------------------------------------------------------------------
	float m_fRotation;

	//--------------------------------------------------------------------------------------
	// A float for the angular velocity of the rigidbody.
	//--------------------------------------------------------------------------------------
	float m_fAngularVelocity;

	//--------------------------------------------------------------------------------------
	// A float for the linear drag of the rigidbody.
	//--------------------------------------------------------------------------------------
	float m_fLinearDrag;
	
	//--------------------------------------------------------------------------------------
	// A float for the angular drag of the rigidbody.
	//--------------------------------------------------------------------------------------
	float m_fAngularDrag;
	
	//--------------------------------------------------------------------------------------
	// A float for the elasticity of the rigidbody.
	//--------------------------------------------------------------------------------------
	float m_fElasticity;

	//--------------------------------------------------------------------------------------
	// A float for the moment of the rigidbody.
	//--------------------------------------------------------------------------------------
	float m_fMoment;
};