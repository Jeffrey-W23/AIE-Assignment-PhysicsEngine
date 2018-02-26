#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	virtual void Update(float deltaTime); // =0
	void SetPerspective(float FieldOfView, float aspectRatio, float near, float far);
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void SetPosition(glm::vec3 position);
	void UpdateProjectionViewTransform();

	glm::mat4 GetWorldTransform() { return worldTransform; };
	glm::mat4 GetView() { return viewTransform; };
	glm::mat4 GetProjection() { return projectionTransform; };
	glm::mat4 GetProjectionView() { return projectionViewTransform; };

protected:

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};

