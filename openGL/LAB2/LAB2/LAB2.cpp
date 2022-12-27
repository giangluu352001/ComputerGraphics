#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.cpp"

using namespace std;

int		screenWidth = 800;
int		screenHeight = 400;

Mesh	cylinderWithHole;
Mesh	cylinder;
Mesh	cuboid;
Mesh	shape1;
Mesh	shape2;
Mesh	shape3;
Mesh	shape4;

int		nChoice = 1;
float	angle = 0;

void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 3, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 3);
	glEnd();
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 4.5, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(0, 0, screenWidth / 2, screenHeight);
	drawAxis();

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	if (nChoice == 1)
		cuboid.DrawWireframe();
	else if (nChoice == 2)
		cylinder.DrawWireframe();
	else if (nChoice == 3)
		cylinderWithHole.DrawWireframe();
	else if (nChoice == 4)
		shape1.DrawWireframe();
	else if (nChoice == 5)
		shape2.DrawWireframe();
	else if (nChoice == 6)
		shape3.DrawWireframe();
	else if (nChoice == 7)
		shape4.DrawWireframe();
	
	glPopMatrix();

	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);
	drawAxis();

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	if (nChoice == 1)
		cuboid.DrawColor();
	else if (nChoice == 2)
		cylinder.DrawColor();
	else if (nChoice == 3)
		cylinderWithHole.DrawColor();
	else if (nChoice == 4)
		shape1.DrawColor();
	else if (nChoice == 5)
		shape2.DrawColor();
	else if (nChoice == 6)
		shape3.DrawColor();
	else if (nChoice == 7)
		shape4.DrawColor();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void mySpecialFunc(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		angle = angle + 5;
	else if (key == GLUT_KEY_RIGHT)
		angle = angle - 5;
	glutPostRedisplay();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, char* argv[])
{
	cout << "Press -> or <- to rotate" << endl;
	cout << "1. Hinh hop chu nhat" << endl;
	cout << "2. Hinh tru" << endl;
	cout << "3. Hinh tru rong ruot" << endl;
	cout << "4. Shape 1" << endl;
	cout << "5. Shape 2" << endl;
	cout << "6. Shape 3" << endl;
	cout << "7. Shape 4" << endl;
	cout << "Input the choice: " << endl;
	cin >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

	cuboid.CreateCuboid(1.6, 0.8, 0.7);
	cylinder.CreateCylinder(20, 2, 0.8);
	cylinderWithHole.CreateCylinderWithHole(20, 2, 0.8, 0.5);
	shape1.CreateShape1(2, 0.5, 0.8);
	shape2.CreateShape2(2.5, 0.3, 0.8);
	shape3.CreateShape3(20, 4, 1);
	shape4.CreateShape4(20, 3, 0.4, 4, 0.3, 0.8);
	myInit();

	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	glutMainLoop();
	return 0;
}



