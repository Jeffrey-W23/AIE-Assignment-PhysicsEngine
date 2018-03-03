// #includes, using, etc
#include "PhysicsEngineApp.h"
#include <Gizmos.h>
#include "Input.h"
#include "Sphere.h"
#include "Box.h"
#include "Plane.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "FlyCamera.h"
#include "imgui.cpp"
#include "imgui_draw.cpp"

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
PhysicsEngineApp::PhysicsEngineApp() 
{
	// Set defaults
	m_bCameraLock = false;
	m_nAddCount = 0;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
PhysicsEngineApp::~PhysicsEngineApp() 
{
}

//--------------------------------------------------------------------------------------
// startup: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
//--------------------------------------------------------------------------------------
bool PhysicsEngineApp::startup() 
{
	// Set background color
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// initialize camera.
	m_pCamera = new FlyCamera();

	// create simple camera transforms
	m_pCamera->SetLookAt(glm::vec3(50), glm::vec3(0), glm::vec3(0, 1, 0)); //10
	m_pCamera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	// Set up the physics scene
	m_pPhysicsScene = new PhysicsScene();
	m_pPhysicsScene->SetGravity(glm::vec3(0, -9.8, 0));
	m_pPhysicsScene->SetTimeStep(0.003f);

	// Box vs Box
	Box* box1 = new Box(glm::vec3(-16, 32, 0), glm::vec3(15, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(0, 0, 1, 1));
	Box* box2 = new Box(glm::vec3(16, 32, 0), glm::vec3(-15, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(1, 1, 0, 1));
	
	// Box vs sphere
	Box* box3 = new Box(glm::vec3(-16, 12, 0), glm::vec3(15, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(1, 0, 1, 1));
	Sphere* ball1 = new Sphere(glm::vec3(16, 12, 0), glm::vec3(-15, 0, 0), 3.0f, 1.0f, glm::vec4(1, 0.5f, 0, 1));

	// Box vs sphere
	Sphere* ball2 = new Sphere(glm::vec3(-16, 0, 0), glm::vec3(15, 0, 0), 3.0f, 1.0f, glm::vec4(1, 1.5f, 0, 1));
	Sphere* ball3 = new Sphere(glm::vec3(16, 0, 0), glm::vec3(-15, 0, 0), 3.0f, 1.0f, glm::vec4(1, 0.5f, 1, 1));

	// Everything vs Planes
	Plane* plane1 = new Plane(glm::normalize(glm::vec3(0, 1, 0)), 0);

	// Add ball actors to scene
	m_pPhysicsScene->AddActor(ball1);
	m_pPhysicsScene->AddActor(ball2);
	m_pPhysicsScene->AddActor(ball3);

	// Add box actors to scene
	m_pPhysicsScene->AddActor(box1);
	m_pPhysicsScene->AddActor(box2);
	m_pPhysicsScene->AddActor(box3);

	// Add plane actors to scene
	m_pPhysicsScene->AddActor(plane1);

	// return true.
	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void PhysicsEngineApp::shutdown() 
{
	// Delete gizmos
	aie::Gizmos::destroy();

	// delete fly camera
	delete m_pCamera;

	// delete scene
	delete m_pPhysicsScene;
}

//--------------------------------------------------------------------------------------
// Update: A virtual function to update objects.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
//--------------------------------------------------------------------------------------
void PhysicsEngineApp::update(float deltaTime) 
{
	// Start imgui box
	ImGui::Begin("Add/Remove Shapes");

	// If Add box button is pressed
	if (ImGui::Button("Add Box"))
	{
		// new box pointer
		Box* pBox = new Box(glm::vec3(-16, 32, 0), glm::vec3(15, 0, 0), 3.0f, 1.0f, 1.0f, 1.0f, glm::vec4(0, 0, 1, 1));
		
		// add box to the scene
		m_pPhysicsScene->AddActor(pBox);
		
		// increase the count
		m_nAddCount++;
	}
	
	// If Add sphere button is pressed
	if (ImGui::Button("Add Sphere"))
	{
		// new sphere pointer
		Sphere* pSphere = new Sphere(glm::vec3(-16, 32, 0), glm::vec3(15, 0, 0), 3.0f, 1.0f, glm::vec4(0, 0, 1, 1));
		
		// Add sphere to the scene
		m_pPhysicsScene->AddActor(pSphere);
	
		// increase count
		m_nAddCount++;
	}

	// If the remove shape button is pressed
	if (ImGui::Button("Remove Shapes"))
	{
		// if the count is greater than 0
		if (m_nAddCount > 0)
		{
			// Remove from the scene
			m_pPhysicsScene->RemoveActor();

			// decrease the count
			m_nAddCount--;
		}
	}

	// End imgui box
	ImGui::End();

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

	// if esc key pressed close program.
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// Unlock and lock the camera so that the mouse can be used to click imgui buttons
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		m_bCameraLock = !m_bCameraLock;

	// if camera is not lock
	if (m_bCameraLock)
	{
		// Update the fly camera.
		m_pCamera->Update(deltaTime, getWindowPtr());

	}	
}

//--------------------------------------------------------------------------------------
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void PhysicsEngineApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	//m_m4ProjectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	// Draw camera perspective.
	aie::Gizmos::draw(m_pCamera->GetProjectionView());
}