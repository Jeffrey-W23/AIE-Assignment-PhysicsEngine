#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}



void Camera::Update(float deltaTime) // remove
{}



void Camera::SetPerspective(float FieldOfView, float aspectRatio, float near, float far)
{
	projectionTransform = glm::perspective(FieldOfView, aspectRatio, near, far);
	UpdateProjectionViewTransform();
}

void Camera::SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	viewTransform = glm::lookAt(from, to, up);
	worldTransform = glm::inverse(viewTransform);
	UpdateProjectionViewTransform();
}

void Camera::SetPosition(glm::vec3 position)
{
	worldTransform[3] = glm::vec4(position.x, position.y, position.z, 1);
	viewTransform = glm::inverse(worldTransform);
	UpdateProjectionViewTransform();
}

void Camera::UpdateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}