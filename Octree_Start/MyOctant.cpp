#include "MyOctant.h"
using namespace ReEng;
//  MyOctant
void MyOctant::Init(void)
{
	m_v3Center = vector3(0.0f);
	m_fSize = 0.0f;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}
void MyOctant::Swap(MyOctant& other)
{

}
void MyOctant::Release(void)
{

}
//The big 3
MyOctant::MyOctant(float a_fSize)
{
	Init();
	m_fSize = a_fSize;
}
MyOctant::MyOctant(){Init();}
MyOctant::MyOctant(MyOctant const& other)
{

}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant(){Release();};
//Accessors

//--- Non Standard Singleton Methods

void MyOctant::Draw(void)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_v3Center) * glm::scale(vector3(m_fSize)), REWHITE, WIRE);
}

void MyOctant::Subdivide(void)
{
	m_pChildren = new MyOctant[8];
	for (uint index = 0; index < 8; index++)
	{
		m_pChildren[index].m_fSize = this->m_fSize / 2.0f;
		m_pChildren[index].m_v3Center = this->m_v3Center;
		m_pChildren[index].m_v3Center.x += m_pChildren[index].m_fSize / 2.0f;
		m_pChildren[index].m_v3Center.y += m_pChildren[index].m_fSize / 2.0f;
		m_pChildren[index].m_v3Center.z += m_pChildren[index].m_fSize / 2.0f;
	}
}
void MyOctant::DestroyOctant(void)
{
	if (m_pChildren != nullptr)
	{
		delete[] m_pChildren;
		m_pChildren = nullptr;
	}
}