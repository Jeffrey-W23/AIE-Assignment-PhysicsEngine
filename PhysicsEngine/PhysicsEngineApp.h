// #includes, using, etc
#pragma once
#include "Application.h"
#include "PhysicsScene.h"
#include <glm/mat4x4.hpp>

//--------------------------------------------------------------------------------------
// PhysicsEngineApp object. Inherits from Application.
//--------------------------------------------------------------------------------------
class PhysicsEngineApp : public aie::Application {
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	PhysicsEngineApp();

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	virtual ~PhysicsEngineApp();

	//--------------------------------------------------------------------------------------
	// startup: Initialize the game.
	//
	// Returns:
	//		bool: Returns a true or false for if the startup is sucessful.
	//--------------------------------------------------------------------------------------
	virtual bool startup();
	
	//--------------------------------------------------------------------------------------
	// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
	//--------------------------------------------------------------------------------------
	virtual void shutdown();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	virtual void update(float deltaTime);
	
	//--------------------------------------------------------------------------------------
	// Draw: A virtual function to render (or "draw") objects to the screen.
	//--------------------------------------------------------------------------------------
	virtual void draw();

protected:






	//--------------------------------------------------------------------------------------
	// A pointer to PhysicsScene.
	//--------------------------------------------------------------------------------------
	PhysicsScene* m_pPhysicsScene;






	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;





	float cameraSpeed;
};