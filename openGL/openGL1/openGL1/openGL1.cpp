#include <windows.h>
#include <GL/glut.h>
#include <ctime>
#include <cmath>

#define PI 3.1415926
#define ARCDIV 19
#define LINEDIV 16
#define DEG2RAD (PI / 180.0)
float R = 4;
float verusR = 2.5;
float earthR = verusR * 149600 / 108200;
GLfloat angle;

struct Point2D {
	float x, y;
};
Point2D pointArr[10];

Point2D circleArr[ARCDIV * 5];
Point2D arcArr[5][ARCDIV];
Point2D lineArr[5][LINEDIV + 1];

Point2D lineIntersection(Point2D p1, Point2D p2, Point2D p3, Point2D p4) {
	Point2D t;
	float A1, B1, A2, B2;

	A1 = (p2.y - p1.y) / (p2.x - p1.x);
	B1 = p1.y - A1 * p1.x;

	A2 = (p4.y - p3.y) / (p4.x - p3.x);
	B2 = p3.y - A2 * p3.x;

	t.x = (B2 - B1) / (A1 - A2);
	t.y = A1 * t.x + B1;

	return t;
}

void calculatePoints() {
	for (int i = 0; i < 5; i++) {
		pointArr[i].x = R * cos(PI / 2 + i * 2 * PI / 5);
		pointArr[i].y = R * sin(PI / 2 + i * 2 * PI / 5);
	}
	pointArr[5] = lineIntersection(pointArr[0], pointArr[2],
		pointArr[1], pointArr[4]);
	pointArr[6] = lineIntersection(pointArr[0], pointArr[2],
		pointArr[1], pointArr[3]);
	pointArr[7] = lineIntersection(pointArr[1], pointArr[3],
		pointArr[2], pointArr[4]);
	pointArr[8] = lineIntersection(pointArr[2], pointArr[4],
		pointArr[0], pointArr[3]);
	pointArr[9] = lineIntersection(pointArr[0], pointArr[3],
		pointArr[1], pointArr[4]);
}

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

void drawFigure() {
	glBegin(GL_POLYGON);
	glVertex2f(-2.0, 0.0);
	glVertex2f(-2.0, 2.0);
	glVertex2f(0.0, 2.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.0, -4.0);
	glVertex2f(2.0, 0.0);
	glVertex2f(4.0, -4.0);
	glEnd();
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(320, 240, 320, 240);
	drawFigure();
	
	glViewport(0, 240, 320, 240);
	drawFigure();

	glViewport(0, 0, 320, 240);
	drawFigure();

	glViewport(320, 0, 320, 240);
	drawFigure();

	glFlush();
}

void init() {
	glClearColor(0, 0, 0, 1);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 4.0, -4.0, 3.0, -1.0, 1.0);
}

void displayChapter2() {
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat vertices[3][2] = {
		{ 0.0, 0.0 },
		{ 25.0, 50.0 },
		{ 50.0, 0.0 }
	};
	int j, k;
	srand(time(NULL));
	GLfloat p[2] = { 7.5, 5.0 };

	glBegin(GL_POINTS);
	for (k = 0; k < 500; k++) {
		j = rand() % 3;
		p[0] = (p[0] + vertices[j][0]) / 2.0;
		p[1] = (p[1] + vertices[j][1]) / 2.0;
		glVertex2fv(p);
	}
	glEnd();
	glFlush();
}

void initChapter2() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
}

void initChapter21() {
	calculatePoints();

	glClearColor(1, 0, 0, 1);
	glColor3f(0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.5, 4.5, -3.0, 3.0, -1.0, 1.0);
}

void displayChapter21() {
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(10);
	//for (int i = 0; i < 10; i++)
	//	drawPoint(pointArr[i]);

	glColor3f(1, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/* glBegin(GL_POLYGON);
	glVertex2f(pointArr[0].x, pointArr[0].y);
	glVertex2f(pointArr[5].x, pointArr[5].y);
	glVertex2f(pointArr[1].x, pointArr[1].y);
	glVertex2f(pointArr[6].x, pointArr[6].y);
	glVertex2f(pointArr[2].x, pointArr[2].y);
	glVertex2f(pointArr[7].x, pointArr[7].y);
	glVertex2f(pointArr[3].x, pointArr[3].y);
	glVertex2f(pointArr[8].x, pointArr[8].y);
	glVertex2f(pointArr[4].x, pointArr[4].y);
	glVertex2f(pointArr[9].x, pointArr[9].y);
	glEnd(); */

	/* glBegin(GL_TRIANGLE_FAN);
	glVertex2d(0, 0);
	glVertex2f(pointArr[0].x, pointArr[0].y);
	glVertex2f(pointArr[5].x, pointArr[5].y);
	glVertex2f(pointArr[1].x, pointArr[1].y);
	glVertex2f(pointArr[6].x, pointArr[6].y);
	glVertex2f(pointArr[2].x, pointArr[2].y);
	glVertex2f(pointArr[7].x, pointArr[7].y);
	glVertex2f(pointArr[3].x, pointArr[3].y);
	glVertex2f(pointArr[8].x, pointArr[8].y);
	glVertex2f(pointArr[4].x, pointArr[4].y);
	glVertex2f(pointArr[9].x, pointArr[9].y);
	glVertex2f(pointArr[0].x, pointArr[0].y);
	glEnd(); */
	glBegin(GL_TRIANGLES);
	glVertex2d(pointArr[0].x, pointArr[0].y);
	glVertex2d(pointArr[5].x, pointArr[5].y);
	glVertex2d(pointArr[9].x, pointArr[9].y);

	glVertex2d(pointArr[1].x, pointArr[1].y);
	glVertex2d(pointArr[5].x, pointArr[5].y);
	glVertex2d(pointArr[6].x, pointArr[6].y);

	glVertex2d(pointArr[6].x, pointArr[6].y);
	glVertex2d(pointArr[2].x, pointArr[2].y);
	glVertex2d(pointArr[7].x, pointArr[7].y);

	glVertex2d(pointArr[7].x, pointArr[7].y);
	glVertex2d(pointArr[3].x, pointArr[3].y);
	glVertex2d(pointArr[8].x, pointArr[8].y);

	glVertex2d(pointArr[4].x, pointArr[4].y);
	glVertex2d(pointArr[8].x, pointArr[8].y);
	glVertex2d(pointArr[9].x, pointArr[9].y);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(pointArr[5].x, pointArr[5].y);
	glVertex2f(pointArr[6].x, pointArr[6].y);
	glVertex2f(pointArr[7].x, pointArr[7].y);
	glVertex2f(pointArr[8].x, pointArr[8].y);
	glVertex2f(pointArr[9].x, pointArr[9].y);
	glEnd();

	glFlush();
}

void calculateData() {
	for (int i = 0; i < ARCDIV * 5; i++) {
		circleArr[i].x = R * cos(PI / 2 + i * 2 * PI / (ARCDIV * 5));
		circleArr[i].y = R * sin(PI / 2 + i * 2 * PI / (ARCDIV * 5));
	}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < ARCDIV; j++) {
			arcArr[i][j].x = circleArr[i * ARCDIV + j].x;
			arcArr[i][j].y = circleArr[i * ARCDIV + j].y;
 		}
	for (int i = 0; i < 5; i++) {
		lineArr[i][0].x = 0;
		lineArr[i][0].y = 0;
		lineArr[i][LINEDIV].x = arcArr[i][0].x;
		lineArr[i][LINEDIV].y = arcArr[i][0].y;
	}
	for (int i = 0; i < 5; i++) {
		float delX = (lineArr[i][LINEDIV].x - lineArr[i][0].x) / LINEDIV;
		float delY = (lineArr[i][LINEDIV].y - lineArr[i][0].y) / LINEDIV;
		for (int j = 1; j < LINEDIV; j++) {
			lineArr[i][j].x = delX * j;
			lineArr[i][j].y = delY * j;
		}
	}
}

void drawPart(int idx1, int idx2, float R, float G, float B) {
	glColor3f(R / 255, G / 255, B / 255);
	for (int i = 0; i < 9; i++)
		drawLine(lineArr[idx1][9 - i], lineArr[idx2][i + 1]);
	for (int i = 0; i < 10; i++)
		drawLine(lineArr[idx1][LINEDIV - i], lineArr[idx2][i + 7]);
	for (int i = 0; i < ARCDIV; i++)
		drawLine(arcArr[idx1][i], arcArr[idx2][i]);
}

void initChapter22() {
	calculateData();
	glClearColor(1, 1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.5, 4.5, -4.5, 4.5, -1.0, 1.0);
}

void drawCircle(float x0, float y0, float R, int n = 500) {
	float x, y, angle;
	float angleinc = 2 * PI / n;
	glBegin(GL_LINE_LOOP);
	angle = 0;
	x = R * cos(angle);
	y = R * sin(angle);
	glVertex2f(x, y);
	for (int i = 1; i < n; i++) {
		angle += angleinc;
		x = R * cos(angle);
		y = R * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawGrid() {
	glColor3f(0.6, 0.6, 0.6);

	glBegin(GL_LINES);
	for (int i = 0; i < 15; i++) {
		glVertex2f(i, 0);
		glVertex2f(i, 15);
	}
	for (int i = 0; i < 15; i++) {
		glVertex2f(0, i);
		glVertex2f(15, i);
	}
	glEnd();
}

void displayChapter22() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawCircle(0, 0, verusR);
	drawCircle(0, 0, earthR);
	
	float earthAngleInc = 4;
	float factor = 365.25636 / 224.7008;
	float verusAngleInc = factor * earthAngleInc;
	float earthX, earthY, verusX, verusY;
	float earthAngle = 90, verusAngle = 90;

	glBegin(GL_LINES);
	for (int i = 0; i <= (360.0 / earthAngleInc) * 8; i++) {
		earthAngle -= earthAngleInc;
		verusAngle -= verusAngleInc;
		earthX = earthR * cos(earthAngle * PI / 180);
		earthY = earthR * sin(earthAngle * PI / 180);

		verusX = verusR * cos(verusAngle * PI / 180);
		verusY = verusR * sin(verusAngle * PI / 180);

		glVertex2f(earthX, earthY);
		glVertex2f(verusX, verusY);
	}
	glEnd();

	glFlush();
}

void displayChapter23() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glColor3f(0, 1, 1);
	drawCircle(0, 0, R, 100);
	for (int i = 0; i < 5; i++)
		drawLine(lineArr[i][0], lineArr[i][LINEDIV]);
	drawPart(0, 1, 255, 128, 0);
	drawPart(1, 2, 0, 255, 0);
	drawPart(2, 3, 0, 0, 255);
	drawPart(3, 4, 255, 0, 255);
	drawPart(4, 0, 228, 27, 98);
	glFlush();
}

void displayChapter24() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	GLfloat cx, cy;
	cx = 0.5 * cos(DEG2RAD * angle);
	cy = 0.5 * sin(DEG2RAD * angle);
	glBegin(GL_POLYGON);
	glVertex2f(cx - 0.5, cy - 0.5);
	glVertex2f(cy - 0.5, cy + 0.5);
	glVertex2f(cx + 0.5, cy + 0.5);
	glVertex2f(cx + 0.5, cy - 0.5);
	glEnd();
	glFlush();
	//glutSwapBuffers();
}

void processTimer(int value) {
	angle += value;
	if (angle > 360) angle = angle - 360;
	glutTimerFunc(100, processTimer, 10);
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	angle = 0;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Example");
	glutDisplayFunc(displayChapter24);
	glutTimerFunc(100, processTimer, 10);
	initChapter22();
	glutMainLoop();
}