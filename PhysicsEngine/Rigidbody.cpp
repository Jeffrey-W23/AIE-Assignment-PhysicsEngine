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
Rigidbody::Rigidbody(EShapeType eShapeID, glm::vec3 v2Position, glm::vec3 v2Velocity, float fRotation, float fMass, float fLinearDrag, float fAngularDrag, float fElasticity) : PhysicsObject(eShapeID)
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
void Rigidbody::FixedUpdate(glm::vec3 v2Gravity, float fTimeStep)
{
	//if (m_isKinematic) 
		//return; 
	
	// remember when applying the force of gravity, mass cancels out 
	m_v2Velocity += v2Gravity * fTimeStep;
	m_v2Position += m_v2Velocity * fTimeStep; m_v2Velocity -= m_v2Velocity * m_fLinearDrag * fTimeStep;
	m_fRotation += m_fAngularVelocity * fTimeStep;
	m_fAngularVelocity -= m_fAngularVelocity * m_fAngularDrag * fTimeStep;
	
	if (glm::length(m_v2Velocity) < MIN_LINEAR_THRESHOLD)
	{ 
		m_v2Velocity = glm::vec3(0, 0, 0);
	} 
	
	if (glm::abs(m_fAngularVelocity) < MIN_ROTATION_THRESHOLD)
	{ 
		m_fAngularVelocity = 0;
	}
}

//--------------------------------------------------------------------------------------
// ApplyForce: Apply force to this rigid body.
//
// Param:
//		v2Force: a vector2 of the force to be applied.
//--------------------------------------------------------------------------------------
void Rigidbody::ApplyForce(glm::vec3 v2Force, glm::vec3 v2Position)
{
	m_v2Velocity += v2Force / m_fMass;
	
	m_fAngularVelocity += (v2Force.x * v2Position.y -
		v2Force.x * v2Position.z -
		v2Force.y * v2Position.x -
		v2Force.y * v2Position.z -
		v2Force.z * v2Position.x -
		v2Force.z * v2Position.y) / (m_fMoment);
}

//--------------------------------------------------------------------------------------
// ApplyForceToActor: Apply force to another rigidbody while applying negative 
// force to this object.
//
// Param:
//		pActor: Rigidbody pointer to apply force to.
//		v2Force: a vector2 of the force to be applied.
//--------------------------------------------------------------------------------------
//void Rigidbody::ApplyForceToActor(Rigidbody* pActor, glm::vec3 v2Force)
//{
//	pActor->ApplyForce(v2Force);
//	this->ApplyForce(-v2Force);
//}

//--------------------------------------------------------------------------------------
// ResolveCollision: Resolve a collision between 2 shapes with a rigidbody.
//
// Param:
//		pActor: the object being collided with.
//--------------------------------------------------------------------------------------
void Rigidbody::ResolveCollision(Rigidbody* pActor, glm::vec3 v2Contact, glm::vec3* v2pCollisionNormal)
{

	// find the vector between their centres, or use the provided direction 
	// of force 
	glm::vec3 v2Normal = v2pCollisionNormal ? *v2pCollisionNormal : glm::normalize(pActor->m_v2Position - m_v2Position);
	
	// get the vector perpendicular to the collision normal 
	glm::vec3 v2Perp(v2Normal.y, -v2Normal.x, v2Normal.z);
	
	// detemine the total velocity of the contact points for the two objects, 
	// for both linear and rotational 
	
	// 'r' is the radius from axis to application of force 
	float r1 = glm::dot(v2Contact - m_v2Position, -v2Perp);
	float r2 = glm::dot(v2Contact - pActor->m_v2Position, v2Perp);
	
	// velocity of the contact point on this object 
	float v1 = glm::dot(m_v2Velocity, v2Normal) - r1 * m_fAngularVelocity;
	
	// velocity of contact point on actor2 
	float v2 = glm::dot(pActor->m_v2Velocity, v2Normal) + r2 * pActor->m_fAngularVelocity;

	if (v1 > v2) // they're moving closer 
	{ 
		// calculate the effective mass at contact point for each object 
		// ie how much the contact point will move due to the force applied. 
		float mass1 = 1.0f / (1.0f / m_fMass + (r1*r1) / m_fMoment); 
		float mass2 = 1.0f / (1.0f / pActor->m_fMass + (r2*r2) / pActor->m_fMoment); 
		
		float elasticity = (m_fElasticity + pActor->GetElasticity()) / 2.0f; 
		
		glm::vec3 v2Force = (1.0f + elasticity)*mass1*mass2 / (mass1 + mass2)*(v1 - v2)*v2Normal;
		
		//apply equal and opposite forces 
		ApplyForce(-v2Force, v2Contact - m_v2Position);
		pActor->ApplyForce(v2Force, v2Contact - pActor->m_v2Position);
	}
}