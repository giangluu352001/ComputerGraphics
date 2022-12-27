#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	Vector3		facenorm;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void Draw();
	void SetColor(int colorIdx);
	void CalculateFacesNorm();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCylinderWithHole(int nSegment, float fHeight, float fORadius, float fIRadius);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateShape1(float fSizeX, float fSizeY, float fSizeZ);
	void CreateShape2(float fSizeX, float fSizeY, float fSizeZ);
	void CreateShape3(int nSegment, float fHeight, float fRadius, float height);
	void CreateShape4(int nSegment, float d, float fRadius, float fSizeX, float fSizeY, float fSizeZ);
};

#endif