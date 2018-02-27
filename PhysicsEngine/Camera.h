// #includes, using, etc
#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//--------------------------------------------------------------------------------------
// Camera object.
//--------------------------------------------------------------------------------------
class Camera
{
public:
	
	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Camera();

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~Camera();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects over time.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	virtual void Update(float deltaTime) = 0; //GLFWwindow* pGLWindow
	
	//--------------------------------------------------------------------------------------
	// SetPerspective: 
	//
	// Param:
	//		fFieldOfView:
	//		fAspectRatio:
	//		fNear:
	//		fFar:
	//--------------------------------------------------------------------------------------
	void SetPerspective(float fFieldOfView, float fAspectRatio, float fNear, float fFar);

	//--------------------------------------------------------------------------------------
	// SetLookAt:
	//
	// Param:
	//		v3From:
	//		v3To:
	//		v3Up:
	//--------------------------------------------------------------------------------------
	void SetLookAt(glm::vec3 v3From, glm::vec3 v3To, glm::vec3 v3Up);

	//--------------------------------------------------------------------------------------
	// SetPosition:
	//
	// Param:
	//		v3Position: 
	//--------------------------------------------------------------------------------------
	void SetPosition(glm::vec3 v3Position);

	//--------------------------------------------------------------------------------------
	// UpdateProjectionViewTransform: 
	//--------------------------------------------------------------------------------------
	void UpdateProjectionViewTransform();

	//--------------------------------------------------------------------------------------
	// GetWorldTransform: Get the world transform for the camera.
	//
	// Return:
	//		mat4: Matrix4 value of the world transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetWorldTransform() { return m_m4WorldTransform; };

	//--------------------------------------------------------------------------------------
	// GetView: Get the viewTransform of the camera
	//
	// Return:
	//		mat4: Matrix4 value of the viewTransform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetView() { return m_m4ViewTransform; };

	//--------------------------------------------------------------------------------------
	// GetProjection: Get the projection transfrom of the camera.
	//
	// Return:
	//		mat4: Matrix4 value of the projection transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetProjection() { return m_m4ProjectionTransform; };

	//--------------------------------------------------------------------------------------
	// GetProjectionView: Get the projection view transform of the camera.
	//
	// Return:
	//		mat4: Matrix4 value of the projection view transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetProjectionView() { return m_m4ProjectionViewTransform; };

protected:

	//--------------------------------------------------------------------------------------
	// A matrix4 for the World Transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4WorldTransform;

	//--------------------------------------------------------------------------------------
	// A matrix4 for the ViewTransform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4ViewTransform;

	//--------------------------------------------------------------------------------------
	// A matrix4 for the Projection Transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4ProjectionTransform;

	//--------------------------------------------------------------------------------------
	// A matrix4 for the Projection View Transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4ProjectionViewTransform;
};