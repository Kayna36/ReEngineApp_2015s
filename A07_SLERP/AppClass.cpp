#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - Karen Navarro"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;

	
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	static double fRunning = 0.0f;
	fRunTime += fCallTime;
	fRunning += fCallTime;

	//Earth Orbit
	float fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//TRANSLATE for Earth and Moon
	matrix4 distanceEarth = glm::translate(11.0f, .0f, .0f);
	matrix4 distanceMoon = glm::translate(2.0f, 0.0f, 0.0f);
	
	//SCALE for all models
	matrix4 m4SunScale = glm::scale(vector3(5.936f, 5.936f, 5.936f));
	matrix4 m4EarthScale = glm::scale(vector3(.524f, .524f, .524f));
	matrix4 m4MoonScale = glm::scale(vector3(.27f, 0.27f, 0.27f));
	//0.14148
	

	//MATRIX WORK pt1
	m_m4Sun = m4SunScale;

	//lerping
	float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, m_fDay, 0.0f, 1.0f);
	float fPercentYear = MapValue(static_cast<float>(fRunTime), 0.0f, fEarthHalfOrbTime / 2.0f, 0.0f, 1.0f);
	float fPercentMoon = MapValue(static_cast<float>(fRunTime), 0.0f, fMoonHalfOrbTime / 2.0f, 0.0f, 1.0f);

	//EARTH Orbit fEarthHalfOrbTime
	glm::quat EarthRotQuat;
	glm::quat earthQuaternionRotStart;
	glm::quat earthQuaternionRotEnd = glm::angleAxis(90.0f, vector3(0.0f, 1.0f, 0.0f));
	EarthRotQuat = glm::mix(earthQuaternionRotStart, earthQuaternionRotEnd, fPercentYear);
	matrix4 RotEarth= glm::mat4_cast(EarthRotQuat);
	m_m4Earth = RotEarth * distanceEarth * m4EarthScale;
	
	//EARTH Rotation fEarthHalfRevTime
	glm::quat EarthOrbQuat;
	glm::quat earthQuaternionOrbStart;
	glm::quat earthQuaternionOrbEnd = glm::angleAxis(90.0f, vector3(0.0f, 1.0f, 0.0f));
	EarthOrbQuat = glm::mix(earthQuaternionOrbStart, earthQuaternionOrbEnd, fPercent);
	matrix4 OrbEarth = glm::mat4_cast(EarthOrbQuat);
	
	//MOON ORBIT fMoonHalfOrbTime
	glm::quat MoonQuat;
	glm::quat moonQuaternionStart;
	glm::quat moonQuaternionEnd = glm::angleAxis(90.0f, vector3(0.0f, 1.0f, 0.0f));
	MoonQuat = glm::mix(moonQuaternionStart, moonQuaternionEnd, fPercentMoon);
	matrix4 moonQ = glm::mat4_cast(MoonQuat);
	
	//MATRIX work pt2
	//m_m4Earth = m_m4Earth * RotEarth * OrbEarth;
	m_m4Moon = m_m4Earth * moonQ *  distanceMoon * m4MoonScale;
	m_m4Earth *=  OrbEarth ;
	/*
	glm::quat myQuaternion= glm::quat(vector3(0.0f,0.0f,0.0f));
	glm::mix(qfQuaternion, qSecondQuaternion, fPercentage / 365);
	glm::mat4_cast(myQuaternion);
	firstQuaternion and secondQuaternion are representative
	of the start and end points of the "orbit", 
	fPercentage says where it is in that orbit
	*/

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;

	static int nIndexMoon = 0; //resetting Earth Rotations

	static int nIndexYear = 0;

	if (fRunning > m_fDay)
	{
		fRunning = 0.0f;
		nEarthRevolutions++;
		nIndexMoon++;
		nIndexYear++;
	}

	if (nIndexMoon == 28)
	{
		nIndexMoon = 0.0f;
		nMoonOrbits++;
	}
	if (nIndexYear == 365.0)
	{
		nIndexYear = 0.0f;
		nEarthOrbits++;
	}

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}