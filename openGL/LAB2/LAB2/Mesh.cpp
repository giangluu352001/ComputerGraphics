#include "Mesh.h"
#include <math.h>
#include <iostream>

#define PI			3.1415926
#define	COLORNUM		14

using namespace std;

float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};

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

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
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
	
	numFaces = 5;
	face = new Face[numFaces];
	int vertices[2][4] = { {0, 3, 4, 7}, {1, 2, 5, 6} };
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
	
	numFaces = 13;
	face = new Face[numFaces];

	int vertices[6][4] = { {0, 3, 4, 7}, {0, 7, 8, 15}, {8, 11, 12, 15},
							{1, 2, 5, 6}, {1, 6, 9, 14}, {9, 10, 13, 14} };
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
	pt[4].set(fSizeX, fSizeY, fSizeZ * 0.6);
	pt[5].set(-fSizeX, fSizeY, fSizeZ * 0.6);
	pt[6].set(-fSizeX, fSizeY * 2.2, fSizeZ * 0.6);
	pt[7].set(fSizeX, fSizeY * 2.2, fSizeZ * 0.6);
	pt[8].set(fSizeX, fSizeY * 2.2, -fSizeZ * 0.6);
	pt[9].set(-fSizeX, fSizeY * 2.2, -fSizeZ * 0.6);
	pt[10].set(-fSizeX, fSizeY, -fSizeZ * 0.6);
	pt[11].set(fSizeX, fSizeY, -fSizeZ * 0.6);
	pt[12].set(fSizeX, fSizeY, -fSizeZ);
	pt[13].set(-fSizeX, fSizeY, -fSizeZ);
	pt[14].set(-fSizeX, -fSizeY, -fSizeZ);
	pt[15].set(fSizeX, -fSizeY, -fSizeZ);
	
	numFaces = 11;
	face = new Face[numFaces];

	int vertices[4][4] = { {0, 3, 12, 15}, {4, 7, 8, 11}, {1, 2, 13, 14}, {5, 6, 9, 10} };
	setFaces(face, numFaces, 7, vertices);

}

void Mesh::CreateShape3(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i, idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight * 0.9, 0);
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
			face[idx -nSegment].vert[2].vertIndex = i + 2 + nSegment;
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
	glColor3f(0, 0, 0);
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
			
			ic = f % COLORNUM;
			
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}




