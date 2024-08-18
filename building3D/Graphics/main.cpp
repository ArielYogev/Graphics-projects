
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
#include <sstream>
#include <string>

const int W = 600;
const int H = 600;
double floorsAmount = 4.0;
double numWindows = 2.0;
double numColor = 1.0;

/// roof color ligher
double roofRlighter = 1.0;
double roofGlighter = 0.4;
double roofBlighter = 0.4;

/// roof color darker
double roofRDarker = 0.6;
double roofGDarker = 0.0;
double roofBDarker = 0.0;

const double PI = 3.14156;
bool isCapturedRoof = false;
bool isCapturedFloors = false;
bool isCapturedWimdows = false;



typedef struct
{
	double x, y, z;
} POINT3;

POINT3 eye = {0,15,25};

double sc[10];

void init()
{
	glClearColor(0.5,0.7,0.9,0);// color of window background
	glEnable(GL_DEPTH_TEST);

	srand(time(0));
	for (int i = 0;i < 10;i++)
		sc[i] = 1+(rand() % 100) / 100.0; // rand numbers in range 1:2

}

void DrawFloor()
{
	int i;
	// lines that are parallel to X axis
	glColor3d(0.1, 0.6, 0);
	glBegin(GL_POLYGON);
	for (i = -100;i <= 100;i++)
	{
		glVertex3d(-100, 0, i); // left end of line
		glVertex3d(100, 0, i); // right end of line
	}
	glEnd();


	// lines that are parallel to Z axis
	
	glBegin(GL_LINES);
	for (i = -100;i <= 100;i++)
	{
		glVertex3d(i, 0, 10); // nearest end of line
		glVertex3d(i, 0, -10); // far end of line
	}
	glEnd();

}

void drawButton(double x, double y) {
	glColor3d(0.7, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.025, y - 0.07);
	glVertex2d(x - 0.015, y + 0.07);
	glVertex2d(x , y + 0.13);
	glVertex2d(x, y - 0.07);
	glEnd();

	glColor3d(0.2, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x + 0.025, y - 0.07);
	glVertex2d(x + 0.015, y + 0.07);
	glVertex2d(x, y + 0.13);
	glVertex2d(x, y - 0.07);
	glEnd();
}

void drawString(const char* str, double x, double y, void* font = GLUT_BITMAP_TIMES_ROMAN_24) {
	glColor3d(1, 1, 1);           // Set color to white
	glRasterPos2d(x, y);          // Set position

	// Iterate over each character in the string
	while (*str) {
		glutBitmapCharacter(font, *str);
		str++;
	}
}

void DrawSlider()
{
	// background
	glColor3d(0.25, 0.25, 0.25);
	glBegin(GL_POLYGON);
	glVertex2d(-1, -1);
	glVertex2d(-1, 1);
	glVertex2d(1, 1);
	glVertex2d(1, -1);
	glEnd();

	glLineWidth(3);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(-0.33333, 1);
	glVertex2d(-0.33333, -1);
	glEnd();

	glLineWidth(3);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(0.33333 , 1);
	glVertex2d(0.33333 , -1);
	glEnd();

	///////////////////////////////////////// slider 1
	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2d(-0.95, 0.8);
	glVertex2d(-0.45, 0.8);
	glVertex2d(-0.45, 0.2);
	glVertex2d(-0.95, 0.2);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(-0.95, 0.5);
	glVertex2d(-0.45, 0.5);
	glEnd();

	drawButton(-0.95 - 0.025 + numColor * 0.16666667, 0.5);

	drawString("Roof", -0.75, -0.5);


	///////////////////////////////////////// slider 2
	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2d(-0.25, 0.8);
	glVertex2d(0.25, 0.8);
	glVertex2d(0.25, 0.2);
	glVertex2d(-0.25, 0.2);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(-0.25, 0.5);
	glVertex2d(0.25, 0.5);
	glEnd();

	drawButton(-0.25 - 0.025 + floorsAmount*0.125, 0.5);

	std::stringstream ss;
	ss << "Num stores: " << floorsAmount;
	std::string text = ss.str();

	drawString(text.c_str(), -0.25, -0.5);

	///////////////////////////////////////// slider 3
	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2d(0.95, 0.8);
	glVertex2d(0.45, 0.8);
	glVertex2d(0.45, 0.2);
	glVertex2d(0.95, 0.2);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(0.95, 0.5);
	glVertex2d(0.45, 0.5);
	glEnd();

	drawButton(0.45 - 0.025 + numWindows*0.125, 0.5);

	std::stringstream s;
	s << "Num windows: " << numWindows;
	std::string text1 = s.str();

	drawString(text1.c_str(), 0.42, -0.5);


}

void DrawWall(int kind)
{
	// left part
	if(kind ==1) 	glColor3d(0.8, 0.7, 0.5);
	else if( kind == 2) glColor3d(0.7, 0.6, 0.4);
	glBegin(GL_POLYGON);
	glVertex3d(-5, 0, 0);
	glVertex3d(-5, 10, 0);
	glVertex3d(-2, 10, 0);
	glVertex3d(-2, 0, 0);
	glEnd();

	// mid part
	glBegin(GL_POLYGON);
	glVertex3d(-2, 0, 0);
	glVertex3d(-2, 3, 0);
	glVertex3d(2, 3, 0);
	glVertex3d(2, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(-2, 7, 0);
	glVertex3d(-2, 10, 0);
	glVertex3d(2, 10, 0);
	glVertex3d(2, 7, 0);
	glEnd();

	// right part
	glBegin(GL_POLYGON);
	glVertex3d(2, 0, 0);
	glVertex3d(2, 10, 0);
	glVertex3d(5, 10, 0);
	glVertex3d(5, 0, 0);
	glEnd();

}

void DrawRoof()
{
	glColor3d(roofRDarker, roofGDarker, roofBDarker);
	glBegin(GL_POLYGON);
	glVertex3d(-1, 0, 0);
	glVertex3d(0, 3, 0);
	glVertex3d(0, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(1, 0, 0);
	glVertex3d(0, 3, 0);
	glVertex3d(0, 0, -1);
	glEnd();

	
	glColor3d(roofRlighter, roofGlighter, roofBlighter);
	glBegin(GL_POLYGON);
	glVertex3d(-1, 0, 0);
	glVertex3d(0, 3, 0);
	glVertex3d(0, 0, -1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(1, 0, 0);
	glVertex3d(0, 3, 0);
	glVertex3d(0, 0, 1);
	glEnd();


}
void DrawCylinderWindows(int n)
{
	double alpha, teta = 2 * PI / n;
	int numParts = 2 * numWindows + 1;
	for (alpha = 0;alpha < 2 * PI;alpha += teta)
	{
		////shadow colors
		double shadowFactor = (1 - cos(alpha)) / 2;
		double wallColorR = 0.96 - 0.2 * shadowFactor;
		double wallColorG = 0.76 - 0.2 * shadowFactor;
		double wallColorB = 0.56 - 0.2 * shadowFactor;

		double sinVector = sin(alpha + teta) - sin(alpha);
		double cosVector = cos(alpha + teta) - cos(alpha);
		double sinWidth = (sinVector/ numParts);
		double cosWidth = (cosVector/ numParts);
		for (int j = 0; j <= numParts; j += 2) {

			glBegin(GL_POLYGON); // upper points are darker
			glColor3d(wallColorR, wallColorG, wallColorB);
			glVertex3d(sin(alpha) + sinWidth * double(j), 1, cos(alpha) + cosWidth * (double)(j)); // point 1

			glColor3d(wallColorR, wallColorG, wallColorB);
			glVertex3d(sin(alpha) + sinWidth * double(j+1), 1, cos(alpha) + cosWidth * (double)(j+1)); // point 2
			// lower points are brighter
			glColor3d(wallColorR, wallColorG, wallColorB);
			glVertex3d(sin(alpha) + sinWidth * double(j+1), 0, cos(alpha) + cosWidth * (double)(j+1)); // point 3

			glColor3d(wallColorR, wallColorG, wallColorB);
			glVertex3d(sin(alpha) + sinWidth * double(j), 0, cos(alpha) + cosWidth * (double)(j)); //point 4
			glEnd();
		}
	}
}
void DrawCylinderNoWindows(int n)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = 0;alpha < 2 * PI;alpha += teta)
	{
		////shadow colors
		double shadowFactor = (1 - cos(alpha)) / 2;
		double wallColorR = 0.96 - 0.2 * shadowFactor;
		double wallColorG = 0.76 - 0.2 * shadowFactor;
		double wallColorB = 0.56 - 0.2 * shadowFactor;

		glBegin(GL_POLYGON); // upper points are darker
		glColor3d(wallColorR, wallColorG, wallColorB);
		glVertex3d(sin(alpha), 1, cos(alpha)); // point 1

		glColor3d(wallColorR, wallColorG, wallColorB);
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta)); // point 2
		// lower points are brighter
		glColor3d(wallColorR, wallColorG, wallColorB);
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta)); // point 3

		glColor3d(wallColorR, wallColorG, wallColorB);
		glVertex3d(sin(alpha), 0, cos(alpha)); //point 4
		glEnd();
	}
}

void DrawInsideBuilding(int n) {
	double alpha, teta = 2 * PI / n;

	for (alpha = 0;alpha < 2 * PI;alpha += teta)
	{

		glBegin(GL_POLYGON); // upper points are darker
		glColor3d(0, 0, 0.2);
		glVertex3d(sin(alpha), 1, cos(alpha)); // point 1

		glColor3d(0, 0, 0.2);
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta)); // point 2
		// lower points are brighter
		glColor3d(0, 0, 0.2);
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta)); // point 3

		glColor3d(0, 0, 0.2);
		glVertex3d(sin(alpha), 0, cos(alpha)); //point 4
		glEnd();
	}
}

void DrawHouse()
{
	int i;
	for (i = 0; i < 2*floorsAmount; i += 2) {
		glPushMatrix();
		glTranslated(0, i, 0);
		DrawCylinderNoWindows(4);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0, i + 1, 0);
		DrawCylinderWindows(4);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslated(0, i, 0);
	DrawCylinderNoWindows(4);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.95, 2 * floorsAmount + 0.5, 0.95);
	DrawInsideBuilding(4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2 * floorsAmount + 1, 0);
	DrawRoof();
	glPopMatrix();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean frame buffer and Z-buffer
	glViewport(0, 0, W, H);

	glMatrixMode(GL_PROJECTION); // matrix of projections / vision
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 0.7, 300); // camera definitions
	gluLookAt(eye.x, eye.y, eye.z, // eye definitions
		0, 0, 0,  // CENTER / Point of Interest
		0, 1, 0); // UP vector

	glMatrixMode(GL_MODELVIEW); // transformations on model objects
	glLoadIdentity(); // start matrix of transformations from identity

	DrawFloor();

	glPushMatrix();

	glScaled(5, 1.5, 5);
	DrawHouse();
	glPopMatrix();

	// control window (pitch slider)
	glViewport(0, 0, 600, 130);
	glMatrixMode(GL_PROJECTION); // matrix of projections / vision
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW); // transformations on model objects
	glLoadIdentity(); // start matrix of transformations from identity
	glDisable(GL_DEPTH_TEST); // because now it's 2D graphics
	DrawSlider();
	glEnable(GL_DEPTH_TEST); // prepare to 3D world

	glutSwapBuffers(); // show all

}

void idle() 
{
	glutPostRedisplay();
}


void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		eye.x -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
		eye.x += 0.5;
		break;

	case GLUT_KEY_UP:
		eye.z -= 0.5;
		break;
	case GLUT_KEY_DOWN:
		eye.z += 0.5;
		break;

	case GLUT_KEY_PAGE_UP:
		eye.y += 0.5;
		break;
	case GLUT_KEY_PAGE_DOWN:
		eye.y -= 0.5;
		break;

	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		int leftRoof = 15 - 7.5 + 150 * (numColor) / 3.0 - 4.5, rightRoof = 15 + 150 * (numColor) / 3.0 + 4.5;
		int leftFloors = 225 - 7.5 + 150 * (floorsAmount) / 4.0 - 4.5, rightFloors = 225 + 150 * (floorsAmount) / 4.0 + 4.5;
		int leftWin = 435 - 7.5 + 150 * (numWindows) / 4.0 - 4.5, rightWin = 435 + 150 * (numWindows) / 4.0 + 4.5;

		if (H - y > 92.95 && H - y < 111.15 && leftRoof < x && x < rightRoof)
			isCapturedRoof = true;

		if (H - y > 92.95 && H - y < 111.15 &&  leftFloors < x && x < rightFloors)
			isCapturedFloors = true;

		if (H - y > 92.95 && H - y < 111.15 && leftWin < x && x < rightWin)
			isCapturedWimdows = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (isCapturedRoof) isCapturedRoof = false;
		if (isCapturedFloors) isCapturedFloors = false;
		if (isCapturedWimdows) isCapturedWimdows = false;
	}
	
}

void MouseDrag(int x, int y)
{
	if (isCapturedRoof && 15 < x && x < 165)
	{
		if (x < 65) {
			numColor = 1.0; 

			roofRlighter = 1.0;
			roofGlighter = 0.4;
			roofBlighter = 0.4;

			roofRDarker = 0.6;
			roofGDarker = 0.0;
			roofBDarker = 0.0;
		}
		else if (x < 115) {
			numColor = 2.0;

			roofRlighter = 0.4;
			roofGlighter = 1.0;
			roofBlighter = 0.4;

			roofRDarker = 0.0;
			roofGDarker = 0.6;
			roofBDarker = 0.0;
		}
		else {
			numColor = 3.0;

			roofRlighter = 0.4;
			roofGlighter = 0.4;
			roofBlighter = 1.0;

			roofRDarker = 0.0;
			roofGDarker = 0.0;
			roofBDarker = 0.6;
		}
	}

	if (isCapturedFloors && 225 < x && x < 375)
	{
		if (x < 262.5)
			floorsAmount = 1; // updating pitch
		else if (x < 300)
			floorsAmount = 2;
		else if (x < 337.5)
			floorsAmount = 3;
		else
			floorsAmount = 4;
	}

	if (isCapturedWimdows && 435 < x && x < 585)
	{
		if (x < 472.5)
			numWindows = 1; // updating pitch
		else if (x < 510)
			numWindows = 2;
		else if (x < 547.5)
			numWindows = 3;
		else
			numWindows = 4;
	}
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);// defines buffer for virtual display
	glutInitWindowSize(W, H);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("3D example");

	glutDisplayFunc(display); // here will be all drawings
	glutIdleFunc(idle); // all the changes must be here and display must be invoked from here

	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(mouse);
	glutMotionFunc(MouseDrag);

	init();

	glutMainLoop();
}