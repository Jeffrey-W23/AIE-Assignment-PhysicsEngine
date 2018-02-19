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
	Box(glm::vec2 v2Position, glm::vec2 v2Velocity, float fMass, float fWidth, float fHeight, glm::vec4 v4Colour);

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
	float GetWidth() { return m_fWidth; }

	//--------------------------------------------------------------------------------------
	// GetHeight: Get the height of the box.
	//
	// Return:
	//		float: a float value for the height of the box.
	//--------------------------------------------------------------------------------------
	float GetHeight() { return m_fHeight; }

	//--------------------------------------------------------------------------------------
	// GetDimensions: Get the dimensions of the box.
	//
	// Return:
	//		Vector2: a vector2 value for the dimensions of the box.
	//--------------------------------------------------------------------------------------
	glm::vec2 GetDimensions() { return m_v2Dimensions; }

	//--------------------------------------------------------------------------------------
	// GetMin: Get the min of the box.
	//
	// Return:
	//		Vector2: a vector2 value for the min of the box.
	//--------------------------------------------------------------------------------------
	glm::vec2 GetMin() { return glm::vec2(m_v2Position.x - m_fWidth, m_v2Position.y - m_fHeight); }

	//--------------------------------------------------------------------------------------
	// GetMax: Get the max of the box.
	//
	// Return:
	//		Vector2: a vector2 value for the max of the box.
	//--------------------------------------------------------------------------------------
	glm::vec2 GetMax() { return glm::vec2(m_v2Position.x + m_fWidth, m_v2Position.y + m_fHeight); }

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
	float m_fWidth;

	//--------------------------------------------------------------------------------------
	// a float for the box height.
	//--------------------------------------------------------------------------------------
	float m_fHeight;

	//--------------------------------------------------------------------------------------
	// a vector42for the box dimensions.
	//--------------------------------------------------------------------------------------
	glm::vec2 m_v2Dimensions;

	//--------------------------------------------------------------------------------------
	// a vector2 for the box min.
	//--------------------------------------------------------------------------------------
	glm::vec2 m_v2Min;

	//--------------------------------------------------------------------------------------
	// a vector2 for the box max.
	//--------------------------------------------------------------------------------------
	glm::vec2 m_v2Max;

	//--------------------------------------------------------------------------------------
	// a vector4 for the box color.
	//--------------------------------------------------------------------------------------
	glm::vec4 m_v4Colour;
};