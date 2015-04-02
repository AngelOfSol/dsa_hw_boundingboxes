#include "BoundingBoxClass.h"
//  BoundingBoxClass
void BoundingBoxClass::Init(void)
{
	m_bInitialized = false;
	m_fExtents[0] = 0.0f;
	m_fExtents[1] = 0.0f;
	m_fExtents[2] = 0.0f;
	m_v3Centroid = vector3(0.0f);
	m_sName = "NULL";
}
void BoundingBoxClass::Swap(BoundingBoxClass& other)
{
	std::swap(m_bInitialized, other.m_bInitialized);
	std::swap(m_fExtents, other.m_fExtents);
	std::swap(m_v3Centroid, other.m_v3Centroid);
	std::swap(m_sName, other.m_sName);
}
void BoundingBoxClass::Release(void)
{
	//No pointers to release
}
//The big 3
BoundingBoxClass::BoundingBoxClass(){Init();}
BoundingBoxClass::BoundingBoxClass(BoundingBoxClass const& other)
{
	m_bInitialized = other.m_bInitialized;
	for(int i = 0; i < 3; i++)
		m_fExtents[i] = other.m_fExtents[i];
	m_v3Centroid = other.m_v3Centroid;
	m_sName = other.m_sName;
}
BoundingBoxClass& BoundingBoxClass::operator=(BoundingBoxClass const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		BoundingBoxClass temp(other);
		Swap(temp);
	}
	return *this;
}
BoundingBoxClass::~BoundingBoxClass(){Release();};
//Accessors
bool BoundingBoxClass::IsInitialized(void){ return m_bInitialized; }

float BoundingBoxClass::GetXExtents(void) { return this->m_fExtents[0]; }
float BoundingBoxClass::GetYExtents(void) { return this->m_fExtents[1]; }
float BoundingBoxClass::GetZExtents(void) { return this->m_fExtents[2]; }

vector3 BoundingBoxClass::GetCentroid(void){ return m_v3Centroid; }
String BoundingBoxClass::GetName(void){return m_sName;}
//Methods
void BoundingBoxClass::GenerateBoundingBox(String a_sInstanceName)
{
	//If this has already been initialized there is nothing to do here
	if(m_bInitialized)
		return;
	MeshManagerSingleton* pMeshMngr = MeshManagerSingleton::GetInstance();
	if(pMeshMngr->IsInstanceCreated(a_sInstanceName))
	{
		m_sName = a_sInstanceName;
		
		std::vector<vector3> lVertices = pMeshMngr->GetVertices(m_sName);
		unsigned int nVertices = lVertices.size();
		m_v3Centroid = lVertices[0];
		vector3 v3Max(lVertices[0]);
		vector3 v3Min(lVertices[0]);
		for(unsigned int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			//m_v3Centroid += lVertices[nVertex];
			if(v3Min.x > lVertices[nVertex].x)
				v3Min.x = lVertices[nVertex].x;
			else if(v3Max.x < lVertices[nVertex].x)
				v3Max.x = lVertices[nVertex].x;
			
			if(v3Min.y > lVertices[nVertex].y)
				v3Min.y = lVertices[nVertex].y;
			else if(v3Max.y < lVertices[nVertex].y)
				v3Max.y = lVertices[nVertex].y;

			if(v3Min.z > lVertices[nVertex].z)
				v3Min.z = lVertices[nVertex].z;
			else if(v3Max.z < lVertices[nVertex].z)
				v3Max.z = lVertices[nVertex].z;
		}
		m_v3Centroid = (v3Min + v3Max) / 2.0f;

		auto extents = (v3Max - v3Min) / 2.0f;
		
		m_fExtents[0] = extents.x;
		m_fExtents[1] = extents.y;
		m_fExtents[2] = extents.z;

		m_bInitialized = true;
	}
}
void BoundingBoxClass::AddBoxToRenderList(matrix4 a_mModelToWorld, vector3 a_vColor, bool a_bRenderCentroid)
{
	if(!m_bInitialized)
		return;
	MeshManagerSingleton* pMeshMngr = MeshManagerSingleton::GetInstance();
	if(a_bRenderCentroid)
		pMeshMngr->AddAxisToQueue(a_mModelToWorld * glm::translate(m_v3Centroid));
	pMeshMngr->AddCubeToQueue(a_mModelToWorld * glm::translate(m_v3Centroid) * glm::scale(vector3(m_fExtents[0] * 2.0f, m_fExtents[1] * 2.0f, m_fExtents[2] * 2.0f)), a_vColor, MERENDER::WIRE);
}