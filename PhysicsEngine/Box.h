// #includes, using, etc
#pragma once
#include "Rigidbody.h"

//--------------------------------------------------------------------------------------
// Box object. Inherits from Rigidbody.
//--------------------------------------------------------------------------------------
class Box : public Rigidbody
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Box() = delete;

	//--------------------------------------------------------------------------------------
	// Constructor.
	//
	// Param:
	//		v2Position: a vector2 for box postion.
	//		v2Velocity: a vector2 for box velocity.
	//		fMass: a float value for box mass.
	//		fWidth: a float value for the box width.
	//		fHeight: a float value for the box height.
	//		v4Color: a vector4 for box color.
	//--------------------------------------------------------------------------------------
	Box(glm::vec3 v2Position, glm::vec3 v2Velocity, float fMass, float fX, float fY, float fZ, glm::vec4 v4Colour);

	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	~Box();

	//--------------------------------------------------------------------------------------
	// MakeGizmo: Virtual function to make gizmo.
	//--------------------------------------------------------------------------------------
	virtual void MakeGizmo();

	//--------------------------------------------------------------------------------------
	// GetWidth: Get the width of the box.
	//
	// Return:
	//		float: a float value for the width of the box.
	//--------------------------------------------------------------------------------------
	float GetX() { return m_fX; }

	//--------------------------------------------------------------------------------------
	// GetHeight: Get the height of the box.
	//
	// Return:
	//		float: a float value for the height of the box.
	//--------------------------------------------------------------------------------------
	float GetY() { return m_fY; }







	//--------------------------------------------------------------------------------------
	// GetHeight: Get the height of the box.
	//
	// Return:
	//		float: a float value for the height of the box.
	//--------------------------------------------------------------------------------------
	float GetZ() { return m_fZ; }








	//--------------------------------------------------------------------------------------
	// GetDimensions: Get the dimensions of the box.
	//
	// Return:
	//		Vector2: a vector2 value for the dimensions of the box.
	//--------------------------------------------------------------------------------------
	glm::vec3 GetDimensions() { return m_v2Dimensions; }

	//--------------------------------------------------------------------------------------
	// GetMin: Get the min of the box.
	//
	// Return:
	//		Vector2: a vector2 value for the min of the box.
	//--------------------------------------------------------------------------------------
	glm::vec3 GetMin() { return glm::vec3(m_v2Position.x - m_fX, m_v2Position.y - m_fY, m_v2Position.z - m_fZ); }

	//--------------------------------------------------------------------------------------
	// GetMax: Get the max of the box.
	//
	// Return:
	//		Vector2: a vector2 value for the max of the box.
	//--------------------------------------------------------------------------------------
	glm::vec3 GetMax() { return glm::vec3(m_v2Position.x + m_fX, m_v2Position.y + m_fY, m_v2Position.z + m_fZ); }

	//--------------------------------------------------------------------------------------
	// GetColour: Get the color of the box.
	//
	// Return:
	//		Vector4: a vector4 value for the color of the box.
	//--------------------------------------------------------------------------------------
	glm::vec4 GetColour() { return m_v4Colour; }

protected:

	//--------------------------------------------------------------------------------------
	// a float for the box width.
	//--------------------------------------------------------------------------------------
	float m_fX;

	//--------------------------------------------------------------------------------------
	// a float for the box height.
	//--------------------------------------------------------------------------------------
	float m_fY;






	//--------------------------------------------------------------------------------------
	// a float for the box height.
	//--------------------------------------------------------------------------------------
	float m_fZ;





	//--------------------------------------------------------------------------------------
	// a vector42for the box dimensions.
	//--------------------------------------------------------------------------------------
	glm::vec3 m_v2Dimensions;

	//--------------------------------------------------------------------------------------
	// a vector2 for the box min.
	//--------------------------------------------------------------------------------------
	glm::vec3 m_v2Min;

	//--------------------------------------------------------------------------------------
	// a vector2 for the box max.
	//--------------------------------------------------------------------------------------
	glm::vec3 m_v2Max;

	//--------------------------------------------------------------------------------------
	// a vector4 for the box color.
	//--------------------------------------------------------------------------------------
	glm::vec4 m_v4Colour;
};