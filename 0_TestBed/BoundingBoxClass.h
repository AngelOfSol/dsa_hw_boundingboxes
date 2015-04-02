/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/03
*/
#ifndef __BOUNDINGBOXCLASS_H_
#define __BOUNDINGBOXCLASS_H_

#include "MyEngine.h"

//System Class
class BoundingBoxClass
{
	bool m_bInitialized; //Has the elements of this object been initialized before?
	float m_fExtents[3];//The extents of the bounding box
	vector3 m_v3Centroid;//Center point of the model, the origin in GSpace in which the Box is going to be located
	String m_sName;//Name of the BoundingBox (to relate to the instance)

public:
	/* Constructor */
	BoundingBoxClass(void);
	/* Copy Constructor */
	BoundingBoxClass(BoundingBoxClass const& other);
	/* Copy Assignment Operator*/
	BoundingBoxClass& operator=(BoundingBoxClass const& other);
	/* Destructor */
	~BoundingBoxClass(void);

	/* Swaps the contents of the object with another object's content */
	void Swap(BoundingBoxClass& other);

	/*
	IsInitialized
		Returns information about whether or not the object has been initialized
	*/
	bool IsInitialized(void);
	
	/*
	GetXExtents
		Returns the extents of the Box along the x-axis
	*/
	float GetXExtents(void);

	/*
	GetYExtents
		Returns the extents of the Box along the y-axis
	*/
	float GetYExtents(void);

	/*
	GetZExtents
		Returns the extents of the Box along the z-axis
	*/
	float GetZExtents(void);

	/*
	GetCentroid
		Returns the origin of the Cartesian Coordinate System in which the Box is drawn in GSpace
	*/
	vector3 GetCentroid(void);

	/*
	GetName
		Returns the name of the Box to associate it with an instance
	*/
	String GetName(void);

	/*
	ConstructBox
		Creates the Box in local space of the model specified in the instance name
	*/
	void GenerateBoundingBox(String a_sInstanceName);

	/*
	AddBoxToRenderList
		Adds the Box to the render list specifying also if rendering the centroid is necessary
	*/
	void AddBoxToRenderList(matrix4 a_mModelToWorld, vector3 a_vColor, bool a_bRenderCentroid = false);

	
private:
	/* Releases the object from memory */
	void Release(void);

	/* Initialize the object's fields */
	void Init(void);
};


#endif //__BOUNDINGBoxCLASS_H__