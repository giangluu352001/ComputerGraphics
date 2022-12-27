#define _USE_MATH_DEFINES
#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define PI			3.1415926
#define	COLORNUM		14

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};


class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize()
	{
		float magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

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
	VertexID* vert;
	Vector3		facenorm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
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
	Point3* pt;

	int		numFaces;
	Face* face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
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

float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.7,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };

void setFaces(Face* face, int numFaces, int part, int vertices[][4])
{
	int i, j = 0;

	for (i = 0; i < part; i++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j + 2;
		face[i].vert[3].vertIndex = j + 3;
		j = j + 2;
	}

	for (i = part; i < numFaces; i++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = vertices[i - part][0];
		face[i].vert[1].vertIndex = vertices[i - part][1];
		face[i].vert[2].vertIndex = vertices[i - part][2];
		face[i].vert[3].vertIndex = vertices[i - part][3];
	}
}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i, idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		if (i + 1 < numVerts)
			pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = numFaces - 1;

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = face[idx - nSegment].nVerts = 3;
		face[idx - 2 * nSegment].nVerts = 4;

		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx - nSegment].vert = new VertexID[face[idx - nSegment].nVerts];
		face[idx - 2 * nSegment].vert = new VertexID[face[idx - 2 * nSegment].nVerts];

		face[idx].vert[0].vertIndex = 0;
		face[idx - nSegment].vert[0].vertIndex = numVerts - 1;
		face[idx - 2 * nSegment].vert[0].vertIndex = i + 1;

		if (i < nSegment - 1)
		{
			face[idx].vert[2].vertIndex = i + 2;
			face[idx - nSegment].vert[2].vertIndex = i + 2 + nSegment;
			face[idx - 2 * nSegment].vert[1].vertIndex = i + 2;
		}
		else
		{
			face[idx].vert[2].vertIndex = 1;
			face[idx - nSegment].vert[2].vertIndex = 1 + nSegment;
			face[idx - 2 * nSegment].vert[1].vertIndex = 1;
		}
		face[idx].vert[1].vertIndex = i + 1;
		face[idx - nSegment].vert[1].vertIndex = i + 1 + nSegment;
		face[idx - 2 * nSegment].vert[2].vertIndex = face[idx - 2 * nSegment].vert[1].vertIndex + nSegment;
		face[idx - 2 * nSegment].vert[3].vertIndex = face[idx - 2 * nSegment].vert[0].vertIndex + nSegment;
		idx--;
	}

}

void Mesh::CreateCylinderWithHole(int nSegment, float fHeight, float fORadius, float fIRadius)
{
	numVerts = nSegment * 4;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	for (i = 0; i < nSegment; i++)
	{
		x = fORadius * cos(fAngle * i);
		z = fORadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i].set(x, y, z);

		y = -fHeight / 2;
		pt[i + nSegment].set(x, y, z);
	}

	for (i = 0; i < nSegment; i++)
	{
		x = fIRadius * cos(fAngle * i);
		z = fIRadius * sin(fAngle * i);
		y = fHeight / 2;
		pt[i + 2 * nSegment].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 3 * nSegment].set(x, y, z);
	}

	numFaces = nSegment * 4;
	face = new Face[numFaces];

	idx = 0;

	/////////////// Outside /////////////////////////
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;

		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 0;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	/////////////// Inside ///////////////////////
	for (i = 2 * nSegment; i < 3 * nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = i;

		if (i < 3 * nSegment - 1)
			face[idx].vert[0].vertIndex = i + 1;
		else
			face[idx].vert[0].vertIndex = 2 * nSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}
	////////////////  Top ////////////////////////////
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = i;

		if (i < nSegment - 1)
			face[idx].vert[0].vertIndex = i + 1;
		else
			face[idx].vert[0].vertIndex = 0;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}
	//////////////// Bottom ////////////////////////
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + nSegment;

		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + nSegment + 1;
		else
			face[idx].vert[1].vertIndex = nSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
	numVerts = 8;
	pt = new Point3[numVerts];

	pt[0].set(fSizeX, -fSizeY, fSizeZ);
	pt[1].set(-fSizeX, -fSizeY, fSizeZ);
	pt[2].set(-fSizeX, fSizeY, fSizeZ);
	pt[3].set(fSizeX, fSizeY, fSizeZ);
	pt[4].set(fSizeX, fSizeY, -fSizeZ);
	pt[5].set(-fSizeX, fSizeY, -fSizeZ);
	pt[6].set(-fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];
	int vertices[3][4] = { {0, 3, 4, 7}, {1, 2, 5, 6}, {7, 6, 1, 0} };
	setFaces(face, numFaces, 3, vertices);

}

void Mesh::CreateShape1(float fSizeX, float fSizeY, float fSizeZ)
{

	numVerts = 16;
	pt = new Point3[numVerts];

	pt[0].set(fSizeX, -fSizeY, fSizeZ);
	pt[1].set(-fSizeX, -fSizeY, fSizeZ);
	pt[2].set(-fSizeX, fSizeY, fSizeZ);
	pt[3].set(fSizeX, fSizeY, fSizeZ);
	pt[4].set(fSizeX, fSizeY, fSizeZ * 0.5);
	pt[5].set(-fSizeX, fSizeY, fSizeZ * 0.5);
	pt[6].set(-fSizeX, fSizeY * 0.3, fSizeZ * 0.5);
	pt[7].set(fSizeX, fSizeY * 0.3, fSizeZ * 0.5);
	pt[8].set(fSizeX, fSizeY * 0.3, -fSizeZ * 0.65);
	pt[9].set(-fSizeX, fSizeY * 0.3, -fSizeZ * 0.65);
	pt[10].set(-fSizeX, fSizeY, -fSizeZ * 0.65);
	pt[11].set(fSizeX, fSizeY, -fSizeZ * 0.65);
	pt[12].set(fSizeX, fSizeY, -fSizeZ);
	pt[13].set(-fSizeX, fSizeY, -fSizeZ);
	pt[14].set(-fSizeX, -fSizeY, -fSizeZ);
	pt[15].set(fSizeX, -fSizeY, -fSizeZ);

	numFaces = 14;
	face = new Face[numFaces];

	int vertices[7][4] = { {0, 3, 4, 7}, {0, 7, 8, 15}, {8, 11, 12, 15},
							{1, 2, 5, 6}, {1, 6, 9, 14}, {9, 10, 13, 14}, {15, 14, 1, 0} };
	setFaces(face, numFaces, 7, vertices);
}

void Mesh::CreateShape2(float fSizeX, float fSizeY, float fSizeZ)
{
	int j = 0;

	numVerts = 16;
	pt = new Point3[numVerts];

	pt[0].set(fSizeX, -fSizeY, fSizeZ);
	pt[1].set(-fSizeX, -fSizeY, fSizeZ);
	pt[2].set(-fSizeX, fSizeY, fSizeZ);
	pt[3].set(fSizeX, fSizeY, fSizeZ);
	pt[4].set(fSizeX, fSizeY, fSizeZ * 0.5);
	pt[5].set(-fSizeX, fSizeY, fSizeZ * 0.5);
	pt[6].set(-fSizeX, fSizeY * 1.7, fSizeZ * 0.5);
	pt[7].set(fSizeX, fSizeY * 1.7, fSizeZ * 0.5);
	pt[8].set(fSizeX, fSizeY * 1.7, -fSizeZ * 0.65);
	pt[9].set(-fSizeX, fSizeY * 1.7, -fSizeZ * 0.65);
	pt[10].set(-fSizeX, fSizeY, -fSizeZ * 0.65);
	pt[11].set(fSizeX, fSizeY, -fSizeZ * 0.65);
	pt[12].set(fSizeX, fSizeY, -fSizeZ);
	pt[13].set(-fSizeX, fSizeY, -fSizeZ);
	pt[14].set(-fSizeX, -fSizeY, -fSizeZ);
	pt[15].set(fSizeX, -fSizeY, -fSizeZ);

	numFaces = 12;
	face = new Face[numFaces];

	int vertices[5][4] = { {0, 3, 12, 15}, {4, 7, 8, 11}, {1, 2, 13, 14}, {5, 6, 9, 10}, {15, 14, 1, 0} };
	setFaces(face, numFaces, 7, vertices);

}

void Mesh::CreateShape3(int nSegment, float fHeight, float fRadius, float height)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i, idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, height + fHeight, 0);
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i);
		z = fRadius * sin(fAngle * i);
		y = fHeight / 2;
		if (i + 1 < numVerts)
			pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = numFaces - 1;

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = face[idx - nSegment].nVerts = 3;
		face[idx - 2 * nSegment].nVerts = 4;

		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx - nSegment].vert = new VertexID[face[idx - nSegment].nVerts];
		face[idx - 2 * nSegment].vert = new VertexID[face[idx - 2 * nSegment].nVerts];

		face[idx].vert[0].vertIndex = 0;
		face[idx - nSegment].vert[0].vertIndex = numVerts - 1;
		face[idx - 2 * nSegment].vert[0].vertIndex = i + 1;

		if (i < nSegment - 1)
		{
			face[idx].vert[2].vertIndex = i + 2;
			face[idx - nSegment].vert[2].vertIndex = i + 2 + nSegment;
			face[idx - 2 * nSegment].vert[1].vertIndex = i + 2;
		}
		else
		{
			face[idx].vert[2].vertIndex = 1;
			face[idx - nSegment].vert[2].vertIndex = 1 + nSegment;
			face[idx - 2 * nSegment].vert[1].vertIndex = 1;
		}
		face[idx].vert[1].vertIndex = i + 1;
		face[idx - nSegment].vert[1].vertIndex = i + 1 + nSegment;
		face[idx - 2 * nSegment].vert[2].vertIndex = face[idx - 2 * nSegment].vert[1].vertIndex + nSegment;
		face[idx - 2 * nSegment].vert[3].vertIndex = face[idx - 2 * nSegment].vert[0].vertIndex + nSegment;
		idx--;
	}
}

void drawFinalShape(Face* face, int nSegment, int idx, int first, int end)
{
	for (int i = 0; i < nSegment; i++) {
		face[i + idx].nVerts = 4;
		face[i + idx].vert = new VertexID[4];
		face[i + idx].vert[0].vertIndex = i + first;
		face[i + idx].vert[1].vertIndex = i + end;
		face[i + idx].vert[2].vertIndex = i + 1 + end;
		face[i + idx].vert[3].vertIndex = i + 1 + first;
	}
}

void Mesh::CreateShape4(int nSegment, float d, float fRadius, float fSizeX, float fSizeY, float fSizeZ)
{
	numVerts = nSegment * 8 + 8;
	pt = new Point3[numVerts];

	int		i;
	float	x, y, z, angle;
	float	fAngle = PI / nSegment;

	for (i = 0; i <= nSegment; i++)
	{
		angle = -PI / 2 + fAngle * i;
		x = fRadius * cos(angle) + d;
		z = fRadius * sin(angle);
		y = fSizeY;

		pt[i].set(x, y, z);
		pt[i + (nSegment + 1)].set(x, -y, z);
		pt[i + 2 * (nSegment + 1)].set(-x, y, z);
		pt[i + 3 * (nSegment + 1)].set(-x, -y, z);

		pt[i + 4 * (nSegment + 1)].set(fSizeX, fSizeY, -fSizeZ * (1 - 2.0 * i / nSegment));
		pt[i + 5 * (nSegment + 1)].set(fSizeX, -fSizeY, -fSizeZ * (1 - 2.0 * i / nSegment));
		pt[i + 6 * (nSegment + 1)].set(-fSizeX, fSizeY, -fSizeZ * (1 - 2.0 * i / nSegment));
		pt[i + 7 * (nSegment + 1)].set(-fSizeX, -fSizeY, -fSizeZ * (1 - 2.0 * i / nSegment));
	}

	numFaces = nSegment * 7;
	face = new Face[numFaces];

	drawFinalShape(face, nSegment, 0, 0, 4 * (nSegment + 1));
	drawFinalShape(face, nSegment, nSegment, 2 * (nSegment + 1), 6 * (nSegment + 1));
	drawFinalShape(face, nSegment, 2 * nSegment, nSegment + 1, 5 * (nSegment + 1));
	drawFinalShape(face, nSegment, 3 * nSegment, 3 * (nSegment + 1), 7 * (nSegment + 1));
	drawFinalShape(face, nSegment, 84, 0, (nSegment + 1));
	drawFinalShape(face, nSegment, 84 + nSegment, 2 * (nSegment + 1), 3 * (nSegment + 1));

	int vertices[8][4] = { {104, 125, 167, 146}, {84, 104, 125, 105}, {167, 146, 126, 147},
							{126, 147, 105, 84}, {104, 20, 62, 146}, {20, 61, 83, 41},
							{126, 42, 0, 84}, {42, 0, 21, 63} };

	for (int j = 0; j < 8; j++)
	{
		face[j + 126].nVerts = 4;
		face[j + 126].vert = new VertexID[4];
		face[j + 126].vert[0].vertIndex = vertices[j][0];
		face[j + 126].vert[1].vertIndex = vertices[j][1];
		face[j + 126].vert[2].vertIndex = vertices[j][2];
		face[j + 126].vert[3].vertIndex = vertices[j][3];
	}

}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::Draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int	iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++) {
		float mX = 0, mY = 0, mZ = 0;
		for (int v = 0; v < face[f].nVerts; v++) {
			int	idx = face[f].vert[v].vertIndex;
			int nextidx = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mX += (pt[idx].y - pt[nextidx].y) * (pt[idx].z + pt[nextidx].z);
			mY += (pt[idx].z - pt[nextidx].z) * (pt[idx].x + pt[nextidx].x);
			mZ += (pt[idx].x - pt[nextidx].x) * (pt[idx].y + pt[nextidx].y);
		}
		face[f].facenorm.set(mX, mY, mZ);
		face[f].facenorm.normalize();
	}
}


int		screenWidth = 1000;
int		screenHeight = 500;

Mesh	chande;
Mesh	ray1;
Mesh	ray2;
Mesh	tamtruot1;
Mesh	tamtruot2;
Mesh	butve1;
Mesh	butve2;
Mesh	butve3;
Mesh	chot1;
Mesh	thanhlienket;
Mesh	chot2;
Mesh	giado1;
Mesh	giado2;

bool	isColor = true;
bool	isViewing = true;
bool	isDrawing = false;

float	minRayPosY = 0.6 + 0.18 * 2, chot1PosY = 0.6 + 0.18 * 2;
float	butve1PosY = 0.6 + 0.18 * 2;

float minYEllipse = 0.8 + 0.18 * 2, maxYEllipse = 3.5;
float minXEllipse = minYEllipse - maxYEllipse, maxXEllipse = maxYEllipse - minYEllipse;
float centerXEllipse = 0, centerYEllipse = minYEllipse + (maxYEllipse - minYEllipse) / 2;
float centerZEllipse = 0.6 + 0.1 * 2 + 0.3 + 0.09, butve3X = 0.0, butve3Y = 1.5 * 0.96;
float radiusX = maxXEllipse, radiusY = radiusX / 2;
float butve2Angle = -90, butve2PosY = 0.18 * 2 + 0.6;

float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-20, 0, 0);
	glVertex3f(20, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 21, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -25);
	glVertex3f(0, 0, 25);
	glEnd();
}

void setupLight()
{

	GLfloat	lightDiffuse[] = { 1.2f, 1.2f, 1.2f, 1.0f };
	GLfloat	lightSpecular[] = { 0, 0, 0, 1.0f };
	GLfloat	lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };

	GLfloat light_position[] = { 20.0f, 20.0f, 20.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	GLfloat light_position1[] = { -20.0f, -20.0f, -20.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
}

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void drawChande()
{
	glPushMatrix();
	glTranslatef(0, 0.18, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) chande.Draw();
	else chande.DrawWireframe();
	glPopMatrix();
}

void drawRay1()
{
	glPushMatrix();
	glTranslatef(-0.25 * 3, 2.15 + 0.18 * 2, 0);
	glRotatef(-90, 0, 0, 1);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) ray1.Draw();
	else ray1.DrawWireframe();
	glPopMatrix();
}

void drawRay2()
{
	glPushMatrix();
	glTranslatef(0.25 * 3, 2.15 + 0.18 * 2, 0);
	glRotatef(90, 0, 0, 1);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) ray2.Draw();
	else ray2.DrawWireframe();
	glPopMatrix();
}

void drawTamtruot1()
{
	glPushMatrix();
	glTranslatef(-0.25, minRayPosY, 0);
	glRotatef(90, 0, 0, 1);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) tamtruot1.Draw();
	else tamtruot1.DrawWireframe();
	glPopMatrix();
}

void drawTamtruot2()
{
	glPushMatrix();
	glTranslatef(0.25, minRayPosY, 0);
	glRotatef(-90, 0, 0, 1);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) tamtruot2.Draw();
	else tamtruot2.DrawWireframe();
	glPopMatrix();
}

void drawButve1()
{
	glPushMatrix();
	glTranslatef(0, butve1PosY, 0.6);
	glRotatef(-90, 1, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) butve1.Draw();
	else butve1.DrawWireframe();
	glPopMatrix();
}

void drawButve2()
{
	glPushMatrix();
	glTranslatef(0, butve2PosY, 0.6);
	//glRotated(butve2Angle, 0, 0, 1);
	//glTranslatef(-1.5 + 0.2, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) butve2.Draw();
	else butve2.DrawWireframe();
	glPopMatrix();
}

void drawButve3()
{
	glPushMatrix();
	glTranslatef(1.5 * 0.96 - 0.2, butve2PosY, 0.6 + 0.1 * 2);
	glRotatef(90, 1, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) butve3.Draw();
	else butve3.DrawWireframe();
	glPopMatrix();
}

void drawChot1()
{
	glPushMatrix();
	glTranslatef(0, chot1PosY, 0.1);
	glRotatef(90, 1, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) chot1.Draw();
	else chot1.DrawWireframe();
	glPopMatrix();
}

void drawThanhlienket()
{
	glPushMatrix();
	glTranslatef(0, butve2PosY, -0.5);
	//glRotated(butve2Angle, 0, 0, 1);
	//glTranslatef(-1.1 + 0.2, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) thanhlienket.Draw();
	else thanhlienket.DrawWireframe();
	glPopMatrix();
}

void drawChot2()
{
	glPushMatrix();
	glTranslatef(0.59 - 0.2, butve2PosY, -0.6);
	glRotatef(90, 1, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) chot2.Draw();
	else chot2.DrawWireframe();
	glPopMatrix();
}

void drawGiado1()
{
	glPushMatrix();
	glTranslatef(0, 2.25, -0.85);
	glRotatef(90, 1, 0, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.7, 0.45, 0.17, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) giado1.Draw();
	else giado1.DrawWireframe();
	glPopMatrix();
}

void drawGiado2()
{
	glPushMatrix();
	glTranslatef(0, 0.82 + 0.18 * 2, -0.85);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.7, 0.45, 0.17, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 5.0;
	setupMaterial(ambient, diffuse, specular, shininess);

	if (isColor) giado2.Draw();
	else giado2.DrawWireframe();
	glPopMatrix();
}

void drawRectangle(float centerX, float centerZ, float width,
	float height, float red, float green, float blue)
{
	glBegin(GL_POLYGON);
	glColor4f(red, green, blue, 1.0);
	glVertex3f(centerX + width / 2, 0, -(centerZ + height / 2));
	glVertex3f(-(centerX + width / 2), 0, -(centerZ + height / 2));
	glVertex3f(-(centerX + width / 2), 0, centerZ + height / 2);
	glVertex3f(centerX + width / 2, 0, centerZ + height / 2);
	glEnd();
}

void drawTriangles(float size, float red, float green, float blue)
{
	glBegin(GL_TRIANGLES);
	glColor4f(red, green, blue, 1.0);

	glVertex3f(0, 0, 0);
	glVertex3f(-size, 0, -size);
	glVertex3f(-size, 0, size);

	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, -size);
	glVertex3f(size, 0, size);
	glEnd();
}

void drawTriangle(float size, float red, float green, float blue)
{
	glBegin(GL_POLYGON);
	glColor4f(red, green, blue, 1.0);

	glVertex3f(0, 0, 0);
	glVertex3f(-size, 0, -size);
	glVertex3f(-size, 0, size);
	glEnd();
}

void drawAnh()
{
	glPushMatrix();
	drawRectangle(0, 0, 0.5, 0.5, 0.5, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 0.5);
	drawRectangle(0, 0, 0.5, 0.5, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0, 0.5);
	drawRectangle(0, 0, 0.5, 0.5, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, -0.5);
	drawRectangle(0, 0, 0.5, 0.5, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0, -0.5);
	drawRectangle(0, 0, 0.5, 0.5, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	drawTriangles(0.25, 0.4, 0, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	drawTriangles(0.25, 0.4, 0, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawTriangles(0.25, 0.4, 0, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawTriangles(0.25, 0.4, 0, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	drawTriangle(0.25, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glRotatef(-90, 0, 1, 0);
	drawTriangle(0.25, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glRotatef(90, 0, 1, 0);
	drawTriangle(0.25, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glRotatef(180, 0, 0, 1);
	drawTriangle(0.25, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.875, 0, 0.875);
	drawRectangle(0, 0, 0.25, 0.25, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.875, 0, -0.875);
	drawRectangle(0, 0, 0.25, 0.25, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.875, 0, 0.875);
	drawRectangle(0, 0, 0.25, 0.25, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.875, 0, -0.875);
	drawRectangle(0, 0, 0.25, 0.25, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.875, 0, 0);
	drawRectangle(0, 0, 0.25, 1.5, 0.5, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.875, 0, 0);
	drawRectangle(0, 0, 0.25, 1.5, 0.5, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.875);
	glRotatef(90, 0, 1, 0);
	drawRectangle(0, 0, 0.25, 1.5, 0.5, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -0.875);
	glRotatef(90, 0, 1, 0);
	drawRectangle(0, 0, 0.25, 1.5, 0.5, 0.5, 0.5);
	glPopMatrix();

}

void drawSan()
{
	glDisable(GL_LIGHTING);
	for (int x = -20; x < 20; x += 2)
		for (int z = -20; z < 20; z += 2)
		{
			glPushMatrix();
			glTranslatef(x, 0, z);
			drawAnh();
			glPopMatrix();
		}
	glEnable(GL_LIGHTING);
}

void mySpecialFunc(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		camera_angle = camera_angle + 1;
	else if (key == GLUT_KEY_RIGHT)
		camera_angle = camera_angle - 1;
	else if (key == GLUT_KEY_UP)
		camera_height = camera_height + 0.25;
	else if (key == GLUT_KEY_DOWN)
		camera_height = camera_height - 0.25;

	glutPostRedisplay();
}

void calculatePosition(float& xPrevious, float& yPrevious, int direction)
{
	float x = (xPrevious - centerXEllipse) / radiusX;
	float y = (yPrevious - centerYEllipse) / radiusY;
	butve2Angle += direction * 180.0 / 274;
	xPrevious = (cos(M_PI / 274) * x - sin(direction * M_PI / 274) * y) * radiusX + centerXEllipse;
	yPrevious = (sin(direction * M_PI / 274) * x + cos(M_PI / 274) * y) * radiusY + centerYEllipse;
}

void DrawEllipse(int nSegment, float xPrevious, float yPrevious)
{
	if (isDrawing)
	{
		float incAngle = 2 * M_PI / nSegment;
		float temp;
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < nSegment; i++)
		{
			glVertex3f(xPrevious * radiusX + centerXEllipse, yPrevious * radiusY + centerYEllipse, centerZEllipse);
			temp = xPrevious;
			xPrevious = cos(incAngle) * xPrevious - sin(incAngle) * yPrevious;
			yPrevious = sin(incAngle) * temp + cos(incAngle) * yPrevious;
		}
		glEnd();
	}
}
void mymouse(int btn, int state, int x, int y) {
	cout << "Chuot ne" << endl;
}
void myNormalFunc(unsigned char key, int x, int y)
{
	cout << "Bao nhieu lan nhi" << endl;
	if (key == 'w' || key == 'W')
		isColor = !isColor;
	else if (key == 'v' || key == 'V')
		isViewing = !isViewing;
	else if (key == '2' && minRayPosY > 0.96)
	{
		int direction = butve3X < 0 || abs(butve3X) < 1e-5 ? 1 : -1;
		calculatePosition(butve3X, butve3Y, direction);
		minRayPosY -= 0.01;
		chot1PosY -= 0.01;
		butve1PosY -= 0.01;
		butve2PosY -= 0.01;

	}
	else if (key == 'a' || key == 'A')
		isDrawing = !isDrawing;
	else if (key == 'v' || key == 'V')
		isViewing = !isViewing;
	else if (key == '1' && minRayPosY < 3.699)
	{
		int direction = butve3X >= 0 ? 1 : -1;
		calculatePosition(butve3X, butve3Y, direction);
		minRayPosY += 0.01;
		chot1PosY += 0.01;
		butve1PosY += 0.01;
		butve2PosY += 0.01;
	}
	else if (key == '-')
		camera_dis = camera_dis - 0.25;
	else if (key == '+')
		camera_dis = camera_dis + 0.25;

	glutPostRedisplay();
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_X = camera_dis * sinf(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * PI / 180);

	if (isViewing) gluLookAt(camera_X, camera_Y, camera_Z, 0, 0, 0, 0, 1, 0);
	else gluLookAt(0, 20, 0, 0, 0, 0, 0, 0, -1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, -380, 1000, 1000);

	drawChande();
	drawRay1();
	drawRay2();
	drawButve1();

	glPushMatrix();
	glTranslatef(0, butve2PosY, 0);
	glRotatef(-butve2Angle, 0, 0, 1);
	glTranslatef(1.5 - 0.2, -butve2PosY, 0);
	drawButve2();
	drawButve3();
	glPopMatrix();

	drawChot1();

	glPushMatrix();
	glTranslatef(0, butve2PosY, 0);
	glRotatef(-butve2Angle, 0, 0, 1);
	glTranslatef(1.1 - 0.2, -butve2PosY, 0);
	drawChot2();
	drawThanhlienket();
	glPopMatrix();

	drawTamtruot1();
	drawTamtruot2();
	drawGiado1();
	drawGiado2();

	drawSan();
	DrawEllipse(100, 0, 1);

	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	camera_angle = -25;
	camera_height = 3.5;
	camera_dis = 16.25;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	setupLight();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 1000);
}

void createAll() {
	//chan de
	chande.CreateCuboid(3.1, 0.18, 1.1);
	chande.SetColor(0);
	chande.CalculateFacesNorm();
	// ray 1
	ray1.CreateShape1(2.15, 0.25, 0.25);
	ray1.SetColor(2);
	ray1.CalculateFacesNorm();
	// ray 2
	ray2.CreateShape1(2.15, 0.25, 0.25);
	ray2.SetColor(2);
	ray2.CalculateFacesNorm();
	// tam truot 1
	tamtruot1.CreateShape2(0.6, 0.25, 0.25);
	tamtruot1.SetColor(1);
	tamtruot1.CalculateFacesNorm();
	// tam truot 2
	tamtruot2.CreateShape2(0.6, 0.25, 0.25);
	tamtruot2.SetColor(1);
	tamtruot2.CalculateFacesNorm();
	// But ve 1
	butve1.CreateCylinderWithHole(20, 0.2, 0.35, 0.16);
	butve1.SetColor(3);
	butve1.CalculateFacesNorm();
	// But ve 2
	butve2.CreateCuboid(1.5, 0.19, 0.1);
	butve2.SetColor(3);
	butve2.CalculateFacesNorm();
	// But ve 3
	butve3.CreateShape3(20, 0.3, 0.1, 0.09);
	butve3.SetColor(0);
	butve3.CalculateFacesNorm();
	// Chot 1
	chot1.CreateCylinder(20, 1.8, 0.16);
	chot1.SetColor(0);
	chot1.CalculateFacesNorm();
	// Thanh lien ket
	thanhlienket.CreateCuboid(1.1, 0.2, 0.14);
	thanhlienket.SetColor(6);
	thanhlienket.CalculateFacesNorm();
	// Chot 2
	chot2.CreateCylinder(20, 0.7, 0.11);
	chot2.SetColor(0);
	chot2.CalculateFacesNorm();
	// Gia do 1
	giado1.CreateShape4(20, 1.5, 0.11, 1.9, 0.13, 0.25);
	giado1.SetColor(9);
	giado1.CalculateFacesNorm();
	// Gia do 2
	giado2.CreateCuboid(0.82, 0.13, 0.3);
	giado2.SetColor(9);
	giado2.CalculateFacesNorm();
}

int main(int argc, char* argv[])
{
	cout << "1     : Di chuyen tam truot len tren" << endl;
	cout << "2     : Di chuyen tam truot xuong duoi" << endl;
	cout << "W, w  : Chuyen doi qua lai giua che do khung day va to mau" << endl;
	cout << "V, v  : Chuyen doi qua lai giua che do 2D va 3D" << endl;
	cout << "A, a  : Bat/tat che do hoat hinh" << endl;
	cout << "+     : Tang khoang cach camera" << endl;
	cout << "-     : Giam khoang cach camera" << endl;
	cout << "up arrow  : Tang khoang cach camera" << endl;
	cout << "down arrow: Giam khoang cach camera" << endl;
	cout << "<-    : Quay camera theo chieu kim dong ho" << endl;
	cout << "->    : Quay camera nguoc chieu kim dong ho" << endl;
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(300, 200); // set window position on screen
	glutCreateWindow("Luu Truong Giang - 1913186"); // open the screen window

	myInit();

	createAll();
	glutSpecialFunc(mySpecialFunc);
	glutKeyboardFunc(myNormalFunc);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mymouse);
	glutMainLoop();
	return 0;
}
