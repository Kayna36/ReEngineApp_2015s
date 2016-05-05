#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	//instantiate the locations for the sphere and the locations the little guy will move to
	locationVector.push_back(vector3(-4.0f, -2.0f, 5.0f));
	locationVector.push_back(vector3(1.0f, -2.0f, 5.0f));
	locationVector.push_back(vector3(-3.0f, -1.0f, 3.0f));
	locationVector.push_back(vector3(2.0f, -1.0f, 3.0f));
	locationVector.push_back(vector3(-2.0f, 0.0f, 0.0f));
	locationVector.push_back(vector3(3.0f, 0.0f, 0.0f));
	locationVector.push_back(vector3(-1.0f, 1.0f, -3.0f)); 
	locationVector.push_back(vector3(4.0f, 1.0f, -3.0f));
	locationVector.push_back(vector3(0.0f, 2.0f, -5.0f));
	locationVector.push_back(vector3(5.0f, 2.0f, -5.0f));
	locationVector.push_back(vector3(1.0f, 3.0f, -5.0f));
	
	//this is constant so to cut down on processor time, rather than find it each time
	locVectorSize = locationVector.size();


	//the following is to make the red sphere appear
	m_pSphere = new PrimitiveClass[locVectorSize];
	m_pMatrix = new matrix4[locVectorSize];

	for (int i = 0; i < locVectorSize; i++)
	{
		m_pSphere[i].GenerateSphere(0.1f, 8, RERED);
		m_pMatrix[i] = glm::translate(locationVector[i]);
	}


}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here

	if (fRunTime >= 100.0f)
	{
		fRunTime == 0.0f;
	} //start from 0 everytime it goes beyond 0;

	//current problem: not smooth transition and it starts to go off into the abyss after it reaches the next 
	float fPercentage = MapValue(fRunTime, 0.0, static_cast<double>(fDuration), 0.0, 1.0); //how fast can you go? 

	static int count = 0;
	count = count % locVectorSize;
	vector3 fPosition;
	if (count == locVectorSize-1)
	{
		fPosition= glm::lerp(locationVector[count], locationVector[0], fPercentage);
	}
	else
	{
		fPosition = glm::lerp(locationVector[count], locationVector[count + 1], fPercentage);
	}
	

	
		
	//vector3 fPosition = glm::lerp(locationVector[count+1], locationVector[count+2], fPercentage);
	matrix4 m4ModelMove = glm::translate(fPosition);
		m_pMeshMngr->SetModelMatrix(m4ModelMove, "WallEye");
		count++;
	
	

	
	//m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "WallEye");



#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	matrix4 mProjection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 mView = m_pCameraMngr->GetViewMatrix();

	//to render the sphere
	for (int i = 0; i< locVectorSize; i++)
	{
		m_pSphere[i].Render(mProjection, mView, m_pMatrix[i]);
	}

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	delete[] m_pSphere;
	delete[] m_pMatrix;
	super::Release(); //release the memory of the inherited fields
}