// #includes, using, etc
#pragma once
#include <glm\ext.hpp>
#include <glm\glm.hpp>

//--------------------------------------------------------------------------------------
// Enum EShapeType. Used for actor shape type
//--------------------------------------------------------------------------------------
enum EShapeType : unsigned short int 
{
	ESHAPETYPE_PLANE = 0,
	ESHAPETYPE_SPHERE,
	ESHAPETYPE_BOX,
	ESHAPETYPE_COUNT
};

//--------------------------------------------------------------------------------------
// PhysicsObject object.
//--------------------------------------------------------------------------------------
class PhysicsObject
{
protected:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//
	// Param:
	//		eShapeID: enum value of EShapeType.
	//--------------------------------------------------------------------------------------
	PhysicsObject(EShapeType eShapeID) : m_eShapeID(eShapeID) {}

public:

	//--------------------------------------------------------------------------------------
	// FixedUpdate: A virtual function of PhysicsObject for updating each frame.
	//
	// Param:
	//		gravity: a vector2 for an objects gravity.
	//		timeStep: a float for each timeStep
	//--------------------------------------------------------------------------------------
	virtual void FixedUpdate(glm::vec2 v2Gravity, float fTimeStep) = 0;
	
	//--------------------------------------------------------------------------------------
	// Debug: A virtual function of PhysicsObject for debugging.
	//--------------------------------------------------------------------------------------
	virtual void Debug() = 0;
	
	//--------------------------------------------------------------------------------------
	// MakeGizmo: A virtual function of PhysicsObject for making Gizmo.
	//--------------------------------------------------------------------------------------
	virtual void MakeGizmo() = 0;
	
	//--------------------------------------------------------------------------------------
	// ResetPosition: A virtual function of PhysicsObject for resetting object postion.
	//--------------------------------------------------------------------------------------
	virtual void ResetPosition() {};

	//--------------------------------------------------------------------------------------
	// EShapeType: 
	//--------------------------------------------------------------------------------------
	EShapeType GetShapeID() { return m_eShapeID; }

protected:

	//--------------------------------------------------------------------------------------
	// m_eShapeID an enum of EShapeType.
	//--------------------------------------------------------------------------------------
	EShapeType m_eShapeID;
};