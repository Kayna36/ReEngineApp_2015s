#include "MyBoundingSphereClass.h"
//  MyBoundingSphereClass
void MyBoundingSphereClass::Init(void)
{
	m_fRadius = 0.0f;
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
}
void MyBoundingSphereClass::Swap(MyBoundingSphereClass& other)
{
	std::swap(m_fRadius, other.m_fRadius);
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);
}
void MyBoundingSphereClass::Release(void)
{

}
//The big 3
MyBoundingSphereClass::MyBoundingSphereClass(std::vector<vector3> a_lVectorList)
{
}

MyBoundingSphereClass::MyBoundingSphereClass(MyBoundingSphereClass const& other)
{
	m_fRadius = other.m_fRadius;
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;
}
MyBoundingSphereClass& MyBoundingSphereClass::operator=(MyBoundingSphereClass const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyBoundingSphereClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingSphereClass::~MyBoundingSphereClass(){Release();};
//Accessors
<<<<<<< HEAD
void MyBoundingSphereClass::SetModelMatrix(matrix4 a_m4ToWorld)
{

	m_m4ToWorld = a_m4ToWorld; 
}
vector3 MyBoundingSphereClass::GetCenter(void){ return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
=======
void MyBoundingSphereClass::SetModelMatrix(matrix4 a_m4ToWorld){ m_m4ToWorld = a_m4ToWorld; }
<<<<<<< HEAD
vector3 MyBoundingSphereClass::GetCenterG(void){ return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
>>>>>>> eb437bb9cc18830401c10408dec5fccc326ac4f7
=======
vector3 MyBoundingSphereClass::GetCenter(void){ return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
>>>>>>> cbe613801c99970acfc1173d8d00852a60671581
float MyBoundingSphereClass::GetRadius(void) { return m_fRadius; }
//--- Non Standard Singleton Methods
bool MyBoundingSphereClass::IsColliding(MyBoundingSphereClass* const a_pOther)
{
<<<<<<< HEAD
<<<<<<< HEAD
	if (glm::distance(GetCenter(), a_pOther->GetCenter()) < (GetRadius() + a_pOther->GetRadius()))
	{
		return true;
	}
	else 
		return false;
}

void MyBoundingSphereClass::UpdatePosition(vector3 v3Input)
{
	m_m4ToWorld *= glm::translate(v3Input);
}
=======
	//Collision check goes here
	vector3 v3Temp = vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
	vector3 v3Temp1 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Center, 1.0f));
	
	bool bAreColliding = false;
	return (glm::distance(v3Temp, v3Temp1) < m_fRadius + a_pOther->m_fRadius);

	/*
	m_m4Steve = m_pMeshMngr->GetModelMatrix("Steve") * glm::translate(m_v3Center1);
	if (bAreColliding)
		m_pMeshMngr->AddSphereToQueue(m_m4Steve * glm::scale(vector3(m_fRadius1 * 2.0f)), RERED, WIRE);
	else
		m_pMeshMngr->AddSphereToQueue(m_m4Steve * glm::scale(vector3(m_fRadius1 * 2.0f)), REGREEN, WIRE);

	m_m4Creeper = m_pMeshMngr->GetModelMatrix("Creeper") * glm::translate(m_v3Center2);
	if (bAreColliding)
		m_pMeshMngr->AddSphereToQueue(m_m4Creeper * glm::scale(vector3(m_fRadius2 * 2.0f)), RERED, WIRE);
	else
		m_pMeshMngr->AddSphereToQueue(m_m4Creeper * glm::scale(vector3(m_fRadius2 * 2.0f)), REGREEN, WIRE);

	return false;
	*/
}
matrix4 MyBoundingSphereClass::GetModelMatrix(void) { return m_m4ToWorld; }
>>>>>>> eb437bb9cc18830401c10408dec5fccc326ac4f7
=======
	return false;
}
>>>>>>> cbe613801c99970acfc1173d8d00852a60671581
