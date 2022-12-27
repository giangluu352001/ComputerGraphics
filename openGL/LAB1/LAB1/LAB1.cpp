#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define PI 3.1415926
#define DEG2RAD (PI / 180)

struct Point2D {
	float x;
	float y;
};

void drawPoint(Point2D p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
}

void drawLine(Point2D p1, Point2D p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

/* 1. Ve hinh tron bang cach xuat ra tap cac diem tren bien cua no.
Khoang cach giua cac diem tinh theo goc la 10 do */
float R = 4;
int angleinc = 0;
Point2D points[36];
Point2D center = { 0, 0 };

void calculate1() {
	for (int angle = 0; angle < 360; angle += 10) {
		points[angle / 10].x = R * cos(angle * DEG2RAD);
		points[angle / 10].y = R * sin(angle * DEG2RAD);
	}
}

void display1() {
	glPointSize(3);
	glColor3f(1, 0, 0);
	for (int i = 0; i < 36; i++)
		drawPoint(points[i]);
}

/* 2. Ve hinh tron bng cach noi cac dinh o cau 1. */
void display2() {
	glColor3f(1, 0.8, 0.8);
	int i;
	for (i = 0; i < 35; i++)
		drawLine(points[i], points[i + 1]);
	drawLine(points[i], points[0]);
}

/* 3. Chia hinh tron o cau 2 thanh cac tam giac bang cach ve duong noi
voi giua tam den cac dinh nam tren bien cua no */
void display3() {
	glColor3f(0.95, 1, 1);
	for (int i = 0; i < 36; i++)
		drawLine(center, points[i]);
}

/* 4. Chon 3 tam giac tu tap tam giac o sao cho chung nam can doi tren hinh tron. To
mau 3 tam giac nay. Khong ve cac tam giac khac, de cho 3 tam giac tao thanh cai quat 3
canh. Cho cai quat xoay quanh tam, cu sau 100milisec thi quay */
void display4() {
	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 360; i += 120) {
		int idx = (i + angleinc) / 10;
		glVertex2d(center.x, center.y);
		glVertex2d(points[idx].x, points[idx].y);
		glVertex2d(points[(idx + 1) % 36].x, points[(idx + 1) % 36].y);
	}
	glEnd();
}

void processTimer(int value) {
	angleinc += value;
	if (angleinc > 110) angleinc = 0;
	glutTimerFunc(100, processTimer, 10);
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	display1();
	display2();
	display3();
	display4();
	glFlush();
}
void init() {
	calculate1();
	glClearColor(1, 1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("LAB");
	glutDisplayFunc(display);
	glutTimerFunc(100, processTimer, 10);
	init();
	glutMainLoop();
}
