// #includes, using, etc
#include "Rigidbody.h"

// #define values.
static const float MIN_LINEAR_THRESHOLD = 0.02f;
static const float MIN_ROTATION_THRESHOLD = 0.02f;

//--------------------------------------------------------------------------------------
// Default Constructor.
//
// Param:
//		eShapeID: the shapeID of the rigidbody.
//		v3Position: the position of the rigidbody.
//		v3Velocity: the velocity of the rigidbody. 
//		fRotation: the rotation of the rigidbody.
//		fMass: the mass of the rigidbody.
//--------------------------------------------------------------------------------------
Rigidbody::Rigidbody(EShapeType eShapeID, glm::vec3 v3Position, glm::vec3 v3Velocity, float fRotation, float fMass, float fLinearDrag, float fAngularDrag, float fElasticity) : PhysicsObject(eShapeID)
{
	// set defaults
	m_v3Position = v3Position;
	m_v3Velocity = v3Velocity;
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
// FixedUpdate: A function to update objects over time each tick.
//
// Param:
//		v3Gravity: vector3 gravity to apply to the update function.
//		fTimeStep: float value for the time time step of the update.
//--------------------------------------------------------------------------------------
void Rigidbody::FixedUpdate(glm::vec3 v3Gravity, float fTimeStep)
{
	// Update the rotation, position, etc of the rigidbody.
	m_v3Velocity += v3Gravity * fTimeStep;
	m_v3Position += m_v3Velocity * fTimeStep; 
	m_v3Velocity -= m_v3Velocity * m_fLinearDrag * fTimeStep;
	m_fRotation += m_fAngularVelocity * fTimeStep;
	m_fAngularVelocity -= m_fAngularVelocity * m_fAngularDrag * fTimeStep;
	
	// if the length of velocity is less than the minimum linear threshold. 
	if (glm::length(m_v3Velocity) < MIN_LINEAR_THRESHOLD)
	{ 
		m_v3Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	} 
	
	// if the abs of Anugular Velocity is less than minimum rotation threshold.
	if (glm::abs(m_fAngularVelocity) < MIN_ROTATION_THRESHOLD)
	{ 
		m_fAngularVelocity = 0.0f;
	}
}

//--------------------------------------------------------------------------------------
// ApplyForce: Apply force to this rigid body.
//
// Param:
//		v3Force: a vector3 of the force to be applied.
//--------------------------------------------------------------------------------------
void Rigidbody::ApplyForce(glm::vec3 v3Force, glm::vec3 v3Position)
{
	// Apply force to the velocity.
	m_v3Velocity += v3Force / m_fMass;
	
	// Apply force to the Angular Velocity.
	m_fAngularVelocity += (v3Force.x * v3Position.y -
		v3Force.x * v3Position.z -
		v3Force.y * v3Position.x -
		v3Force.y * v3Position.z -
		v3Force.z * v3Position.x -
		v3Force.z * v3Position.y) / (m_fMoment);
}

//--------------------------------------------------------------------------------------
// ResolveCollision: Resolve a collision between 2 shapes with a rigidbody.
//
// Param:
//		pActor: the object being collided with.
//--------------------------------------------------------------------------------------
void Rigidbody::ResolveCollision(Rigidbody* pActor, glm::vec3 v3Contact, glm::vec3* v3pCollisionNormal)
{
	// find the vector between their centres, or use the provided direction of force 
	glm::vec3 v3Normal = v3pCollisionNormal ? *v3pCollisionNormal : glm::normalize(pActor->m_v3Position - m_v3Position);
	
	// get the vector perpendicular to the collision normal 
	glm::vec3 v3Perp(v3Normal.y, -v3Normal.x, v3Normal.z);
	
	// detemine the total velocity of the contact points for the two objects, 
	// for both linear and rotational 
	
	// 'r' is the radius from axis to application of force 
	float r1 = glm::dot(v3Contact - m_v3Position, -v3Perp);
	float r2 = glm::dot(v3Contact - pActor->m_v3Position, v3Perp);
	
	// velocity of the contact point on this object 
	float v1 = glm::dot(m_v3Velocity, v3Normal) - r1 * m_fAngularVelocity;
	
	// velocity of contact point on actor2 
	float v2 = glm::dot(pActor->m_v3Velocity, v3Normal) + r2 * pActor->m_fAngularVelocity;

	if (v1 > v2) // they're moving closer 
	{ 
		// calculate the effective mass at contact point for each object 
		// ie how much the contact point will move due to the force applied. 
		float mass1 = 1.0f / (1.0f / m_fMass + (r1*r1) / m_fMoment); 
		float mass2 = 1.0f / (1.0f / pActor->m_fMass + (r2*r2) / pActor->m_fMoment); 
		
		// calculate elasticity
		float elasticity = (m_fElasticity + pActor->GetElasticity()) / 2.0f; 
		
		// Calculate force
		glm::vec3 v3Force = (1.0f + elasticity)*mass1*mass2 / (mass1 + mass2)*(v1 - v2)*v3Normal;
		
		//apply equal and opposite forces 
		ApplyForce(-v3Force, v3Contact - m_v3Position);
		pActor->ApplyForce(v3Force, v3Contact - pActor->m_v3Position);
	}
}

//--------------------------------------------------------------------------------------
// ApplyForceToActor: Apply force to another rigidbody while applying negative 
// force to this object.
//
// Param:
//		pActor: Rigidbody pointer to apply force to.
//		v3Force: a vector3 of the force to be applied.
//--------------------------------------------------------------------------------------
//void Rigidbody::ApplyForceToActor(Rigidbody* pActor, glm::vec3 v3Force)
//{
//	pActor->ApplyForce(v3Force);
//	this->ApplyForce(-v3Force);
//}