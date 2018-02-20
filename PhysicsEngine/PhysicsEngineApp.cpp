// #includes, using, etc
#include "PhysicsEngineApp.h"
#include <Gizmos.h>
#include "Input.h"
#include "Sphere.h"
#include "Box.h"
#include "Plane.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
PhysicsEngineApp::PhysicsEngineApp() {

}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
PhysicsEngineApp::~PhysicsEngineApp() {

}

//--------------------------------------------------------------------------------------
// startup: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
//--------------------------------------------------------------------------------------
bool PhysicsEngineApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(glm::vec3(50), glm::vec3(0), glm::vec3(0, 1, 0)); //10
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);


	cameraSpeed = 10.0f;






	// Set up the physics scene
	m_pPhysicsScene = new PhysicsScene();
	m_pPhysicsScene->SetGravity(glm::vec3(0, -9.8, 0));
	m_pPhysicsScene->SetTimeStep(0.003f);

	Sphere* ball1 = new Sphere(glm::vec3(-16, 0, 32), glm::vec3(50, 0, 0), 3.0f, 1.0f, glm::vec4(1, 0, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec3(16, 0, -16), glm::vec3(-50, 0, 0), 3.0f, 1.0f, glm::vec4(0, 1, 0, 1));
	Sphere* ball3 = new Sphere(glm::vec3(32, 16, 0), glm::vec3(0, -25, 0), 3.0f, 1.0f, glm::vec4(0.75f, 0.75f, 0.75f, 1));
	Sphere* ball4 = new Sphere(glm::vec3(-16, 16, 10), glm::vec3(50, 0, 0), 3.0f, 1.0f, glm::vec4(1, 0.5f, 0, 1));

	Box* box1 = new Box(glm::vec3(-16, 32, 0), glm::vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(0, 0, 1, 1));
	Box* box2 = new Box(glm::vec3(16, 32, 0), glm::vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(1, 1, 0, 1));
	Box* box3 = new Box(glm::vec3(-32, 16, 0), glm::vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(1, 0.5f, 0.76f, 1));
	Box* box4 = new Box(glm::vec3(16, 16, 0), glm::vec3(0, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(0.5f, 0, 0.7f, 1));

	Plane* plane1 = new Plane(glm::normalize(glm::vec3(-1, 10, 0)), -30);
	Plane* plane2 = new Plane(glm::normalize(glm::vec3(-10, 10, 0)), -30);
	Plane* plane3 = new Plane(glm::normalize(glm::vec3(10, 0, 0)), -50);

	m_pPhysicsScene->AddActor(ball1);
	m_pPhysicsScene->AddActor(ball2);
	m_pPhysicsScene->AddActor(ball3);
	m_pPhysicsScene->AddActor(ball4);

	m_pPhysicsScene->AddActor(box1);
	m_pPhysicsScene->AddActor(box2);
	m_pPhysicsScene->AddActor(box3);
	m_pPhysicsScene->AddActor(box4);

	m_pPhysicsScene->AddActor(plane1);
	m_pPhysicsScene->AddActor(plane2);
	m_pPhysicsScene->AddActor(plane3);

	//ball1->ApplyForce(glm::vec3(50, 0, 0));
	//ball2->ApplyForce(glm::vec3(-50, 0, 0));
	//ball3->ApplyForce(glm::vec3(0, -25, 0));
	//ball4->ApplyForce(glm::vec3(50, 0, 0));

	//box1->ApplyForce(glm::vec3(50, 0, 0));
	//box2->ApplyForce(glm::vec3(-50, 0, 0));
	//box3->ApplyForce(glm::vec3(0, -25, 0));
	//box4->ApplyForce(glm::vec3(-50, 0, 0));









	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void PhysicsEngineApp::shutdown() {

	aie::Gizmos::destroy();







	// delete scene
	delete m_pPhysicsScene;
}

//--------------------------------------------------------------------------------------
// Update: A virtual function to update objects.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void PhysicsEngineApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	aie::Gizmos::clear();

	// Update scene
	m_pPhysicsScene->Update(deltaTime);
	m_pPhysicsScene->UpdateGizmos();

	// draw a simple grid with gizmos
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
						glm::vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
						glm::vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	aie::Gizmos::addTransform(glm::mat4(1));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();





	/*if (input->isKeyDown(aie::INPUT_KEY_W))
		
	if (input->isKeyDown(aie::INPUT_KEY_A))
		
	if (input->isKeyDown(aie::INPUT_KEY_S))
		
	if (input->isKeyDown(aie::INPUT_KEY_D))*/
		
}

//--------------------------------------------------------------------------------------
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void PhysicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	aie::Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}