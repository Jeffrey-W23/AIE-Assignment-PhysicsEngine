// #includes, using, etc
#include "Rigidbody.h"







static const float MIN_LINEAR_THRESHOLD = 0.02f;
static const float MIN_ROTATION_THRESHOLD = 0.02f;






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
Rigidbody::Rigidbody(EShapeType eShapeID, glm::vec2 v2Position, glm::vec2 v2Velocity, float fRotation, float fMass, float fLinearDrag, float fAngularDrag, float fElasticity) : PhysicsObject(eShapeID)
{
	// set defaults
	m_v2Position = v2Position;
	m_v2Velocity = v2Velocity;
	m_fMass = fMass;
	m_fRotation = fRotation;






	m_fLinearDrag = fLinearDrag;
	m_fAngularDrag = fAngularDrag;
	m_fElasticity = fElasticity;






}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Rigidbody::~Rigidbody()
{

}

//--------------------------------------------------------------------------------------
// FixedUpdate: A function to update objects over time.
//
// Param:
//		v2Gravity: vector2 gravity to apply to the update function.
//		fTimeStep: float value for the time time step of the update.
//--------------------------------------------------------------------------------------
void Rigidbody::FixedUpdate(glm::vec2 v2Gravity, float fTimeStep)
{
	ApplyForce(v2Gravity * m_fMass * fTimeStep);
	m_v2Position += m_v2Velocity * fTimeStep;








	m_v2Velocity -= m_v2Velocity * m_fLinearDrag * fTimeStep;

	if (glm::length(m_v2Velocity) < MIN_LINEAR_THRESHOLD)
	{
		m_v2Velocity = glm::vec2(0, 0);
	}






}

//--------------------------------------------------------------------------------------
// ApplyForce: Apply force to this rigid body.
//
// Param:
//		v2Force: a vector2 of the force to be applied.
//--------------------------------------------------------------------------------------
void Rigidbody::ApplyForce(glm::vec2 v2Force)
{
	m_v2Velocity += v2Force / m_fMass;
}

//--------------------------------------------------------------------------------------
// ApplyForceToActor: Apply force to another rigidbody while applying negative 
// force to this object.
//
// Param:
//		pActor: Rigidbody pointer to apply force to.
//		v2Force: a vector2 of the force to be applied.
//--------------------------------------------------------------------------------------
void Rigidbody::ApplyForceToActor(Rigidbody* pActor, glm::vec2 v2Force)
{
	pActor->ApplyForce(v2Force);
	this->ApplyForce(-v2Force);
}

//--------------------------------------------------------------------------------------
// ResolveCollision: Resolve a collision between 2 shapes with a rigidbody.
//
// Param:
//		pActor: the object being collided with.
//--------------------------------------------------------------------------------------
void Rigidbody::ResolveCollision(Rigidbody* pActor)
{















	// new values for normal, realative velocity and elasticity.
	glm::vec2 v2Normal = glm::normalize(pActor->GetPosition() - m_v2Position); 
	glm::vec2 v2RelativeVelocity = pActor->GetVelocity() - m_v2Velocity;
	float fElasticity = (m_fElasticity + pActor->GetElasticity()) * 0.5f;
	
	// Calculate the j formula
	float fJFormula = glm::dot(-(1 + fElasticity) * (v2RelativeVelocity), v2Normal) / glm::dot(v2Normal, v2Normal * ((1 / m_fMass) + (1 / pActor->GetMass())));
	
	// Calculate force.
	glm::vec2 v2Force = v2Normal * fJFormula;

	// Apply the force to the actor.
	ApplyForceToActor(pActor, v2Force);
}