// #includes, using, etc
#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include "Plane.h"
#include "Sphere.h"
#include "Box.h"
#include <algorithm>
#include <iostream>
#include <list>

// function pointer array for doing collisions 
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

// Array of PhysicsScene functions.
static fn collisionFunctionArray[] = { 
	PhysicsScene::PlaneToPlane, PhysicsScene::PlaneToSphere, PhysicsScene::PlaneToBox,
	PhysicsScene::SphereToPlane, PhysicsScene::SphereToSphere, PhysicsScene::SphereToBox,
	PhysicsScene::BoxToPlane, PhysicsScene::BoxToSphere, PhysicsScene::BoxToBox,
}; 

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
PhysicsScene::PhysicsScene()
{
	// set defalut for timestep
	m_fTimeStep = 0.01f;

	// set defualt for gravity
	m_v3Gravity = glm::vec3(0, 0, 0);
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
PhysicsScene::~PhysicsScene()
{
	// loop through each actor
	for (auto pActor : m_apActors)
	{
		// delete each actor
		delete pActor;
	}
}

//--------------------------------------------------------------------------------------
// AddActor: Add an object to the scene.
//
// Param:
//		pActor: the object to add to the scene.
//--------------------------------------------------------------------------------------
void PhysicsScene::AddActor(PhysicsObject* pActor)
{
	// Add actor to the array.
	m_apActors.push_back(pActor);
}

//--------------------------------------------------------------------------------------
// RemoveActor: An Object to remove from the scene.
//--------------------------------------------------------------------------------------
void PhysicsScene::RemoveActor() //PhysicsObject* pActor)
{
	// delete actor
	delete m_apActors.back();
	
	// pop actor from the array.
	m_apActors.pop_back();
	
	//std::remove(std::begin(m_apActors), std::end(m_apActors), pActor);
}

//--------------------------------------------------------------------------------------
// Update: A function to update objects over time.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void PhysicsScene::Update(float deltaTime)
{
	// update physics at a fixed time step
	static float fAccumulatedTime = 0.0f;

	// update accumulatedTime by deltaTime
	fAccumulatedTime += deltaTime;
	
	// while the accumulated time is greater than the Time step
	while (fAccumulatedTime >= m_fTimeStep)
	{
		// loop through actors array
		for (auto pActor : m_apActors)
		{
			// Update actors
			pActor->FixedUpdate(m_v3Gravity, m_fTimeStep);
		}

		// update accumulated time by the time step
		fAccumulatedTime -= m_fTimeStep;
	
		// Check for a collision.
		CheckCollision();
	}
}

//--------------------------------------------------------------------------------------
// UpdateGizmos: Update the scene and scene object gizmos.
//--------------------------------------------------------------------------------------
void PhysicsScene::UpdateGizmos()
{
	// loop through the actors
	for (auto pActor : m_apActors) 
	{	
		// Make actor Gizmos
		pActor->MakeGizmo();
	}
}

//--------------------------------------------------------------------------------------
// DebugScene: Debugging function for the scene.
//--------------------------------------------------------------------------------------
void PhysicsScene::DebugScene()
{
	// new int for count
	int nCount = 0;
	
	// loop through each actor
	for (auto pActor : m_apActors) 
	{
		// cout the count value
		std::cout << nCount << " : ";

		// run actor debug
		pActor->Debug();

		// increment count
		nCount++;
	}
}

//--------------------------------------------------------------------------------------
// PlaneToPlane: Check a collison between a plane and another plane.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::PlaneToPlane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Return to this later and finish. //TODO
	return false;
}

//--------------------------------------------------------------------------------------
// PlaneToSphere: Check a collison between a plane and a sphere.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::PlaneToSphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// return the result of SphereToPlane but with the objects flipped.
	return (SphereToPlane(obj2, obj1));
}

//--------------------------------------------------------------------------------------
// PlaneToBox: Check a collison between a plane and a box.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::PlaneToBox(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Plane* pPlane = dynamic_cast<Plane*>(obj1);
	Box* pBox = dynamic_cast<Box*>(obj2);

	// if plane and box are valid
	if (pPlane != nullptr || pBox != nullptr)
	{
		// Get the plane normal
		glm::vec3 v3Normal = pPlane->GetNormal();

		// calculate below box
		glm::vec3 v3BottomLeftBelow = pBox->GetMin();
		glm::vec3 v3BottomRightBelow = pBox->GetMin() + glm::vec3(pBox->GetX(), 0, 0);
		glm::vec3 v3TopLeftBelow = pBox->GetMin() + glm::vec3(0, pBox->GetY(), 0);
		glm::vec3 v3TopRightBelow = pBox->GetMax();

		// calculate top box
		glm::vec3 v3BottomLeftAbove = pBox->GetMin() + glm::vec3(0, 0, pBox->GetZ());
		glm::vec3 v3BottomRightAbove = pBox->GetMin() + glm::vec3(pBox->GetX(), 0, pBox->GetZ());
		glm::vec3 v3TopLeftAbove = pBox->GetMin() + glm::vec3(0, pBox->GetY(), pBox->GetZ());
		glm::vec3 v3TopRightAbove = pBox->GetMax() + glm::vec3(0, 0, pBox->GetZ());

		// new array of floats for overlaps
		float afOverlap[8] = { 0.0f };

		// Calculate overlaps.
		afOverlap[0] = glm::dot(v3Normal, v3BottomLeftBelow) - pPlane->GetDistance();
		afOverlap[1] = glm::dot(v3Normal, v3BottomRightBelow) - pPlane->GetDistance();
		afOverlap[2] = glm::dot(v3Normal, v3TopLeftBelow) - pPlane->GetDistance();
		afOverlap[3] = glm::dot(v3Normal, v3TopRightBelow) - pPlane->GetDistance();
		afOverlap[4] = glm::dot(v3Normal, v3BottomLeftAbove) - pPlane->GetDistance();
		afOverlap[5] = glm::dot(v3Normal, v3BottomRightAbove) - pPlane->GetDistance();
		afOverlap[6] = glm::dot(v3Normal, v3TopLeftAbove) - pPlane->GetDistance();
		afOverlap[7] = glm::dot(v3Normal, v3TopRightAbove) - pPlane->GetDistance();

		// float to keep track of the max overlaps.
		float fMaxOverlap = 0.0f;

		// loop through the array of overlap values.
		for (int i = 0; i < 8; ++i)
		{
			// check for overlap
			if (afOverlap[i] < fMaxOverlap)
			{
				fMaxOverlap = afOverlap[i];
			}
		}

		if (fMaxOverlap < 0)
		{
			// Resolve collision between plane and box
			pPlane->ResolveCollision(pBox);

			// Seperate the box from plane if overlapping.
			pBox->SetPosition(pBox->GetPosition() - pPlane->GetNormal() * fMaxOverlap);

			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}

//--------------------------------------------------------------------------------------
// SphereToPlane: Check a collison between a sphere and a plane.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::SphereToPlane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Sphere* pSphere = dynamic_cast<Sphere*>(obj1);
	Plane* pPlane = dynamic_cast<Plane*>(obj2);

	// if sphere and plane are valid
	if (pSphere != nullptr && pPlane != nullptr)
	{
		// new vector2 for the collision Normal
		glm::vec3 v3CollisionNormal = pPlane->GetNormal();

		// dot product of sphere position and plane normal minus plane distance
		float fSphereToPlane = glm::dot(pSphere->GetPosition(), pPlane->GetNormal()) - pPlane->GetDistance();

		// dot product value is less then 0
		if (SphereToPlane < 0)
		{
			v3CollisionNormal *= -1;
			fSphereToPlane *= -1;
		}

		// new float for collision intersection. 
		float fIntersection = pSphere->GetRadius() - fSphereToPlane;

		// if intersection is over 0
		if (fIntersection > 0)
		{
			// calculate the contact point.
			glm::vec3 v3Contact = pSphere->GetPosition() + (v3CollisionNormal * -pSphere->GetRadius());

			// Resolve collision between plane and sphere
			pPlane->ResolveCollision(pSphere); //, v3Contact);
			
			// Seperate the sphere from plane if overlapping.
			pSphere->SetPosition(v3Contact + v3CollisionNormal * pSphere->GetRadius() + fIntersection);

			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}

//--------------------------------------------------------------------------------------
// SphereToSphere: Check a collison between a sphere and another sphere.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::SphereToSphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Sphere* pSphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* pSphere2 = dynamic_cast<Sphere*>(obj2);

	// if sphere and sphere2 are valid
	if (pSphere1 != nullptr && pSphere2 != nullptr)
	{
		// new vector2 value for the dsitance between each sphere
		glm::vec3 v3Distance = pSphere1->GetPosition() - pSphere2->GetPosition();

		// new float value for the total radius of both spheres
		float fTotalRad = pSphere1->GetRadius() + pSphere2->GetRadius();

		// if the length of the distance is less then or equal to Total radius
		if (glm::length(v3Distance) <= fTotalRad)
		{
			// Resolve collision between sphere and sphere
			pSphere1->ResolveCollision(pSphere2); //, 0.5f * (pSphere1->GetPosition() + pSphere2->GetPosition()));

			// Resolve collision between spheres
			float fOverlap = glm::length(v3Distance) - fTotalRad;
			glm::vec3 v3Overlap = glm::normalize(v3Distance) * fOverlap;
			pSphere2->SetPosition(pSphere2->GetPosition() + v3Overlap);

			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}

//--------------------------------------------------------------------------------------
// SphereToBox: Check a collison between a sphere and a box.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::SphereToBox(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Sphere* pSphere = dynamic_cast<Sphere*>(obj1);
	Box* pBox = dynamic_cast<Box*>(obj2);

	// if plane and box are valid
	if (pSphere != nullptr && pBox != nullptr)
	{
		// clamp the sphere postion and the box min and max
		glm::vec3 v3Clamp = glm::clamp(pSphere->GetPosition(), pBox->GetMin(), pBox->GetMax());
		glm::vec3 v3Value = v3Clamp - pSphere->GetPosition();

		// if the length of v2Value is less than or equal to sphere radius
		if (glm::length(v3Value) <= pSphere->GetRadius())
		{
			// Resolve collision between sphere and box
			pSphere->ResolveCollision(pBox);

			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}

//--------------------------------------------------------------------------------------
// BoxToPlane: Check a collison between a box and a plane.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::BoxToPlane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// return the result of PlaneToBox but with the objects flipped.
	return (PlaneToBox(obj2, obj1));
}

//--------------------------------------------------------------------------------------
// BoxToSphere: Check a collison between a box and a sphere.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::BoxToSphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// return the result of SphereToBox but with the objects flipped.
	return (SphereToBox(obj2, obj1));
}

//--------------------------------------------------------------------------------------
// BoxToBox: Check a collison between a box and another box.
//
// Param:
//		obj1: Object 1 for the collison check.
//		obj2: Object 2 for the collision check.
// Return:
//		bool: Return true or false for if a collision has happened.
//--------------------------------------------------------------------------------------
bool PhysicsScene::BoxToBox(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// Cast each object to either a sphere or plane.
	Box* pBox1 = dynamic_cast<Box*>(obj1);
	Box* pBox2 = dynamic_cast<Box*>(obj2);

	// if boxes are valid
	if (pBox1 != nullptr && pBox2 != nullptr)
	{
		// get the min and max of box1
		glm::vec3 v3Min1 = pBox1->GetMin();
		glm::vec3 v3Max1 = pBox1->GetMax();

		// get the min and max of box2
		glm::vec3 v3Min2 = pBox2->GetMin();
		glm::vec3 v3Max2 = pBox2->GetMax();

		// if the boxes cross
		if (v3Min1.x <= v3Max2.x && 
			v3Min1.y <= v3Max2.y &&
			v3Min1.z <= v3Max2.z &&
			v3Max1.x >= v3Min2.x && 
			v3Max1.y >= v3Min2.y &&
			v3Max1.z >= v3Min2.z)
		{
			// Resolve collision between boxes
			pBox1->ResolveCollision(pBox2);

			// there was a collision return true
			return true;
		}
	}

	// else return false
	return false;
}

//--------------------------------------------------------------------------------------
// CheckCollision: Check for a collision between objects.
//--------------------------------------------------------------------------------------
void PhysicsScene::CheckCollision()
{
	// new int value for the actor array size
	auto nActorCount = m_apActors.size();

	//need to check for collisions against all objects except this one.
	// loop through each actor
	for (int o = 0; o < nActorCount - 1; o++)
	{
		// loop through each actor plus 1
		for (int i = o + 1; i < nActorCount; i++)
		{
			// Check the 2 objects that could be colliding.
			PhysicsObject* object1 = m_apActors[o];
			PhysicsObject* object2 = m_apActors[i];

			// get shapeIds of these objects.
			int nShapeId1 = object1->GetShapeID();
			int nShapeId2 = object2->GetShapeID();

			// figure out the shapes that are colliding and which function to run.
			int functionIdx = (nShapeId1 * ESHAPETYPE_COUNT) + nShapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];

			// if the function pointer is valid.
			if (collisionFunctionPtr != nullptr)
			{
				// Check collision of the 2 objects. 
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}