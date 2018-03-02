// #includes, using, etc

#define GLM_ENABLE_EXPERIMENTAL 1

#include "FlyCamera.h"
#include "Input.h"
#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm\gtx\transform.hpp>

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
FlyCamera::FlyCamera()
{
	// set the default for the speed var
	m_fSpeed = 20.0f;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
FlyCamera::~FlyCamera()
{
}

//--------------------------------------------------------------------------------------
// Update: A virtual function to update objects over time.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//		pGLWindow: pointer to the glfw window.
//--------------------------------------------------------------------------------------
void FlyCamera::Update(float deltaTime, GLFWwindow* pGLWindow)
{
	// Get the instance of the aie input
	aie::Input* input = aie::Input::getInstance();

	// if W key is pressed, if want to go forward.
	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_m4WorldTransform[3] -= m_m4WorldTransform[2] * deltaTime * m_fSpeed;

	// if S key is pressed, if want to go backward.
	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_m4WorldTransform[3] += m_m4WorldTransform[2] * deltaTime * m_fSpeed;

	// if A key is pressed, if want to go left.
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_m4WorldTransform[3] -= m_m4WorldTransform[0] * deltaTime * m_fSpeed;

	// if D key is pressed, if want to go right.
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_m4WorldTransform[3] += m_m4WorldTransform[0] * deltaTime * m_fSpeed;

	// Unlock and lock the camera so that the mouse can be used to click imgui buttons
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		m_bCameraLock = !m_bCameraLock;

	// if camera is not lock
	if (!m_bCameraLock)
	{
		// Calculate delta XY of mouse
		glfwGetCursorPos(pGLWindow, &m_dMouseX, &m_dMouseY);

		// Radians to degrees
		m_dDeltaMouseX = (400 - m_dMouseX) * 0.0174533f;
		m_dDeltaMouseY = (300 - m_dMouseY) * 0.0174533f;

		// Keep mouse locked to screen.
		glfwSetCursorPos(pGLWindow, 400, 300);

		// Calculate reletive world up
		glm::vec4 up = glm::inverse(m_m4WorldTransform) * glm::vec4(0, 1, 0, 0);
		glm::mat4 rotMat(1.0f);

		// rotate around world up
		rotMat = glm::rotate((float)-m_dDeltaMouseX * deltaTime, glm::vec3(up[0], up[1], up[2]));
		m_m4ViewTransform = rotMat * m_m4ViewTransform;

		// Rotate up down
		rotMat = glm::rotate((float)-m_dDeltaMouseY * deltaTime, glm::vec3(1, 0, 0));
		m_m4ViewTransform = rotMat * m_m4ViewTransform;

		// Update world transform
		m_m4WorldTransform = glm::inverse(m_m4ViewTransform);
	}

	// Update the transform and projection view
	m_m4ViewTransform = glm::inverse(m_m4WorldTransform);
	UpdateProjectionViewTransform();
}