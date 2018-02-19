// #includes, using, etc
#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <vector>

// forward declarations
class PhysicsObject;

//--------------------------------------------------------------------------------------
// PhysicsScene object.
//--------------------------------------------------------------------------------------
class PhysicsScene
{
public:
	
	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	PhysicsScene();

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~PhysicsScene();

	//--------------------------------------------------------------------------------------
	// AddActor: Add an object to the scene.
	//
	// Param:
	//		pActor: the object to add to the scene.
	//--------------------------------------------------------------------------------------
	void AddActor(PhysicsObject* pActor);

	//--------------------------------------------------------------------------------------
	// RemoveActor: An Object to remove from the scene.
	//
	// Param:
	//		pActor: the object to remove from the scene.
	//--------------------------------------------------------------------------------------
	void RemoveActor(PhysicsObject* pActor);

	//--------------------------------------------------------------------------------------
	// Update: A function to update objects over time.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	void Update(float deltaTime);

	//--------------------------------------------------------------------------------------
	// UpdateGizmos: Update the scene and scene object gizmos.
	//--------------------------------------------------------------------------------------
	void UpdateGizmos();

	//--------------------------------------------------------------------------------------
	// DebugScene: Debugging function for the scene.
	//--------------------------------------------------------------------------------------
	void DebugScene();
	
	//--------------------------------------------------------------------------------------
	// SetGravity: Set the grtavity of the scene.
	//
	// Param:
	//		v2Gravity: vector2 for gravity to set.
	//--------------------------------------------------------------------------------------
	void SetGravity(const glm::vec2 v2Gravity) { m_v2Gravity = v2Gravity; }

	//--------------------------------------------------------------------------------------
	// GetGravity: Get the gravity of the scene.
	//
	// Return:
	//		Vector2: Current gravity of the scene.
	//--------------------------------------------------------------------------------------
	glm::vec2 GetGravity() const { return m_v2Gravity; }

	//--------------------------------------------------------------------------------------
	// SetTimeStep: Set the timestep of the physicsScene.
	//
	// Param:
	//		fTimeStep: set a float value for the current time step.
	//--------------------------------------------------------------------------------------
	void SetTimeStep(const float fTimeStep) { m_fTimeStep = fTimeStep; }

	//--------------------------------------------------------------------------------------
	// GetTimeStep: Return the timestep of the PhysicsScene.
	//
	// Return:
	//		float: returns a float value of the current time step.
	//--------------------------------------------------------------------------------------
	float GetTimeStep() const { return m_fTimeStep; }
	
	//--------------------------------------------------------------------------------------
	// CheckCollision: Check for a collision between objects.
	//--------------------------------------------------------------------------------------
	void CheckCollision();

	//--------------------------------------------------------------------------------------
	// PlaneToPlane: Check a collison between a plane and another plane.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool PlaneToPlane(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// PlaneToSphere: Check a collison between a plane and a sphere.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool PlaneToSphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// PlaneToBox: Check a collison between a plane and a box.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool PlaneToBox(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// SphereToPlane: Check a collison between a sphere and a plane.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool SphereToPlane(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// SphereToSphere: Check a collison between a sphere and another sphere.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool SphereToSphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// SphereToBox: Check a collison between a sphere and a box.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool SphereToBox(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// BoxToPlane: Check a collison between a box and a plane.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool BoxToPlane(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// BoxToSphere: Check a collison between a box and a sphere.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool BoxToSphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//--------------------------------------------------------------------------------------
	// BoxToBox: Check a collison between a box and another box.
	//
	// Param:
	//		obj1: Object 1 for the collison check.
	//		obj2: Object 2 for the collision check.
	// Return:
	//		bool: Return true or false for if a collision has happened.
	//--------------------------------------------------------------------------------------
	static bool BoxToBox(PhysicsObject* obj1, PhysicsObject* obj2);

protected:
	
	//--------------------------------------------------------------------------------------
	// A vector2 for gravity
	//--------------------------------------------------------------------------------------
	glm::vec2 m_v2Gravity;

	//--------------------------------------------------------------------------------------
	// A float for time step
	//--------------------------------------------------------------------------------------
	float m_fTimeStep;

	//--------------------------------------------------------------------------------------
	// A dynamic array of PhysicsObject pointers.
	//--------------------------------------------------------------------------------------
	std::vector<PhysicsObject*> m_apActors;
};

