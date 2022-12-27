#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.cpp"

using namespace std;

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

float	minRayPosY = 3.2, chot1PosY = 2 + 0.6 * 2;
float	maxRayPosY = 12, butve1PosY = 2 + 0.6 * 2;

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

	GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { 10, 9, 8.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);

	GLfloat lightDiffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position1[] = { 10, 9, -8.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
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
	glTranslatef(0, 0.6, 0);

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
	glTranslatef(-1.1 * 3, 8 + 0.6 * 2, 0);
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
	glTranslatef(1.1 * 3, 8 + 0.6 * 2, 0);
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
	glTranslatef(-1.1, minRayPosY, 0);
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
	glTranslatef(1.1, minRayPosY, 0);
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
	glTranslatef(0, butve1PosY, 1.6);
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
	glTranslatef(0, 6 + 0.6 * 2 + 1.3, 1.6);
	glRotatef(-90, 0, 0, 1);

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
	glTranslatef(0, 13, 1.6 + 0.8);
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
	glTranslatef(0, chot1PosY, 0);
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
	glTranslatef(0, 6 + 0.5, -1.5);
	glRotatef(-90, 0, 0, 1);

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
	glTranslatef(0, 8, -1.9);
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
	glTranslatef(0, 8, -2.7);
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
	glTranslatef(0, 4, -2.7);
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

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_X = camera_dis * sinf(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * PI / 180);

	gluLookAt(camera_X, camera_Y, camera_Z, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(200, 0, 500, 500);

	drawChande();
	drawRay1();
	drawRay2();
	drawButve1();
	drawButve2();
	drawButve3();
	drawChot1();
	drawChot2();
	drawThanhlienket();
	drawTamtruot1();
	drawTamtruot2();
	drawGiado1();
	drawGiado2();

	glFlush();
	glutSwapBuffers();
}

void mySpecialFunc(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		camera_angle = camera_angle - 5;
	else if (key == GLUT_KEY_RIGHT)
		camera_angle = camera_angle + 5;
	else if (key == GLUT_KEY_UP)
		camera_height = camera_height + 0.2;
	else if (key == GLUT_KEY_DOWN)
		camera_height = camera_height - 0.2;

	glutPostRedisplay();
}

void myNormalFunc(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
		isColor = !isColor;
	else if (key == '2' && minRayPosY > 3.2)
	{
		minRayPosY -= 0.02;
		chot1PosY -= 0.02;
		butve1PosY -= 0.02;
	}
	else if (key == '1' && minRayPosY < maxRayPosY)
	{
		minRayPosY += 0.02;
		chot1PosY += 0.02;
		butve1PosY += 0.02;
	}
	else if (key == '-')
		camera_dis = camera_dis - 0.2;
	else if (key == '+')
		camera_dis = camera_dis + 0.2;

	glutPostRedisplay();
}

void myInit()
{
	camera_angle = -0;
	camera_height = 5.5;
	camera_dis = 20;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	setupLight();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-18.0, 18.0, -5.0, 27.0, 0.1, 100);
	//glFrustum(-18.0, 18.0, -5.0, 27.0, 5, 1000);
}

void createAll() {
	//chan de
	chande.CreateCuboid(12, 0.6, 4);
	chande.SetColor(0);
	chande.CalculateFacesNorm();
	// ray 1
	ray1.CreateShape1(8, 1.1, 0.8);
	ray1.SetColor(2);
	ray1.CalculateFacesNorm();
	// ray 2
	ray2.CreateShape1(8, 1.1, 0.8);
	ray2.SetColor(2);
	ray2.CalculateFacesNorm();
	// tam truot 1
	tamtruot1.CreateShape2(2, 1.1, 0.8);
	tamtruot1.SetColor(1);
	tamtruot1.CalculateFacesNorm();
	// tam truot 2
	tamtruot2.CreateShape2(2, 1.1, 0.8);
	tamtruot2.SetColor(1);
	tamtruot2.CalculateFacesNorm();
	// But ve 1
	butve1.CreateCylinderWithHole(20, 0.7, 1.5, 0.6);
	butve1.SetColor(3);
	butve1.CalculateFacesNorm();
	// But ve 2
	butve2.CreateCuboid(6, 0.8, 0.35);
	butve2.SetColor(3);
	butve2.CalculateFacesNorm();
	// But ve 3
	butve3.CreateShape3(20, 1.3, 0.4, 0.5);
	butve3.SetColor(0);
	butve3.CalculateFacesNorm();
	// Chot 1
	chot1.CreateCylinder(20, 5.5, 0.6);
	chot1.SetColor(0);
	chot1.CalculateFacesNorm();
	// Thanh lien ket
	thanhlienket.CreateCuboid(4, 0.7, 0.5);
	thanhlienket.SetColor(6);
	thanhlienket.CalculateFacesNorm();
	// Chot 2
	chot2.CreateCylinder(16, 2, 0.4);
	chot2.SetColor(0);
	chot2.CalculateFacesNorm();
	// Gia do 1
	giado1.CreateShape4(20, 7, 0.4, 8, 0.5, 1);
	giado1.SetColor(9);
	giado1.CalculateFacesNorm();
	// Gia do 2
	giado2.CreateCuboid(3, 0.5, 1.2);
	giado2.SetColor(9);
	giado2.CalculateFacesNorm();
}

int main(int argc, char* argv[])
{
	cout << "1     : Di chuyen tam truot len tren" << endl;
	cout << "2     : Di chuyen tam truot xuong duoi" << endl;
	cout << "->    : Xoay khung canh sang trai" << endl;
	cout << "<-    : Xoay khung canh sang phai" << endl;
	cout << "W, w  : Chuyen doi qua lai giua che do khung day va to mau" << endl;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(600, 200); // set window position on screen
	glutCreateWindow("Luu Truong Giang - 1913186"); // open the screen window

	myInit();

	chande = Mesh();
	ray1 = Mesh();
	ray2 = Mesh();
	tamtruot1 = Mesh();
	tamtruot2 = Mesh();
	butve1 = Mesh();
	butve2 = Mesh();
	butve3 = Mesh();
	chot1 = Mesh();
	thanhlienket = Mesh();
	chot2 = Mesh();
	giado1 = Mesh();
	giado2 = Mesh();

	createAll();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);
	glutKeyboardFunc(myNormalFunc);
	glutMainLoop();
	return 0;
}
