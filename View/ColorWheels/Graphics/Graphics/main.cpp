
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"

const int W = 600;
const int H = 600;

const double PI = 3.14156;

double angle = 0;
double bicycleAngle = 0;
int direction = 1;
double cloudOneMove = -0.3;
double cloudtwoMove = 0;
double wheel_radius = 0.11;

void init()
{
	glClearColor(0.5,0.7,0.9,0);// color of window background
	glOrtho(-1, 1, -1, 1, -1, 1); // set the coordinates system
}

void DrawCircle(int n)
{
	double alpha, teta = 2 * PI / n;
	double x, y;
	for (alpha = 0;alpha <= 2 * PI;alpha += teta)
	{
	glBegin(GL_POLYGON);
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();

}

void DrawWheel()
{
	int n = 18;
	double alpha, teta = 2 * PI / n;
	double x, y;

	glColor3d(0.3, 0.3, 0.3); // light gray
	glBegin(GL_LINES);
	for (alpha = 0; alpha <= 2 * PI;alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
		glVertex2d(0, 0);
	}

	glEnd();

	n = 60;
	teta = 2 * PI / n;

	glColor3d(0, 0, 0); // black
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (alpha = 0; alpha <= 2 * PI;alpha += teta)
	{
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();

	glLineWidth(1);

}

void DrawBicycle()
{
	// front wheel
	glPushMatrix();
	glTranslated(-0.2, 0, 0);
	glRotated(bicycleAngle *direction, 0, 0, 1);
	glScaled(wheel_radius, wheel_radius, 1);

	DrawWheel();
	glPopMatrix();

	// rear wheel
	glPushMatrix();
	glTranslated(0.2, 0, 0);
	glRotated(bicycleAngle * direction, 0, 0, 1);
	glScaled(wheel_radius, wheel_radius, 1);
	DrawWheel();
	glPopMatrix();

	// center wheel
	glPushMatrix();
	glRotated(bicycleAngle, 0, 0, 1);
	glScaled(0.03, 0.03, 1);
	DrawWheel();
	glPopMatrix();

	glLineWidth(2);
	glColor3d(1, 0, 0);

	glBegin(GL_LINE_LOOP);
	glVertex2d(0, 0);
	glVertex2d(0.2, 0);
	glVertex2d(0.08, 0.14);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(0, 0);
	glVertex2d(-0.17, 0.13);
	glVertex2d(-0.2, 0);
	glVertex2d(-0.15, 0.2);
	glVertex2d(-0.24, 0.2);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(-0.16, 0.16);
	glVertex2d(0.08, 0.14);
	glVertex2d(0.1, 0.17);
	glVertex2d(0.05, 0.17);
	glVertex2d(0.13, 0.17);
	glEnd();

	glLineWidth(1);

}
void DrawClouds() {
	glColor3d(0.89, 0.89, 0.89);

	glPushMatrix();
	glTranslated(0.16,0.65, 0);
	glScaled(0.1, 0.1, 1);
	DrawCircle(40);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.3, 0.68, 0);
	glScaled(0.1, 0.1, 1);
	DrawCircle(40);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, 0.7, 0);
	glScaled(0.1, 0.1, 1);
	DrawCircle(40);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.6, 0);
	glScaled(0.1, 0.1, 1);
	DrawCircle(40);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, 0.6, 0);
	glScaled(0.1, 0.1, 1);
	DrawCircle(40);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0.65, 0);
	glScaled(0.1, 0.1, 1);
	DrawCircle(40);
	glPopMatrix();
}
void DrawVane() {
	double alpha, teta = 2 * PI / 10;
	double x, y;
	glColor3d(1, 1, 1);
	for (alpha = 0;alpha <= 2 * PI;alpha += teta)
	{
		glBegin(GL_POLYGON);
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
		glVertex2d(0, 0);
		alpha += teta;
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
		glEnd();
	}
}
void DrawWindmill() {
	glColor3d(0.347, 0.165, 0.165);
	glBegin(GL_POLYGON);
	glVertex2d(-0.5, -0.3);
	glVertex2d(-0.3, -0.3);
	glVertex2d(-0.35, 0);
	glVertex2d(-0.4, 0.05);
	glVertex2d(-0.45, 0);	
	glEnd();

	glPushMatrix();
	glTranslated(-0.4, 0.05, 0);
	glRotated(-angle*1.5, 0, 0, 1);
	glScaled(0.2, 0.2, 1);
	DrawVane();
	glPopMatrix();
}

void DrawSun() {
	double alpha, teta = 2 * PI / 20;
	double x, y;
	for (alpha = 0;alpha <= 2 * PI;alpha += teta)
	{
		glBegin(GL_POLYGON);
		x = cos(alpha);
		y = sin(alpha);
		glColor3d(1.0, 1.0, 0.0);
		glVertex2d(x, y);
		glVertex2d(0, 0);
		alpha += teta;
		x = cos(alpha);
		y = sin(alpha);
		glVertex2d(x, y);
		glEnd();

	}
	glPushMatrix();
	glScaled(0.4, 0.4, 1);
	DrawCircle(40);
	glPopMatrix();
}
void DrawRiver() {
	glColor3d(0, 0.2, 0.6);
	glBegin(GL_POLYGON);
	glVertex2d(-0.35, -0.3);//left up
	glVertex2d(-0.2, -0.3); // right up
	glVertex2d(-0.3, -1);//right dowen
	glVertex2d(-0.58, -1);//left dowen
	glEnd();
}

void DrawRail(double cx, double cy, double radius, int num_pts)
{
	double alpha, teta = 2 * PI / num_pts;
	double x, y;

	for (alpha = 0;alpha <= PI;alpha += teta)
	{
		glBegin(GL_LINE_STRIP);
		x = cx + radius * cos(alpha);
		y = cy + radius * sin(alpha);
		if(x >= -0.47 && x <= -0.26) {
			glVertex2d(x, y);

			x = cx + (radius + 0.05) * cos(alpha);
			y = cy + (radius + 0.05) * sin(alpha);
			glVertex2d(x, y);

			glEnd();
		}
	}

	glBegin(GL_LINE_STRIP);
	for (alpha = 0;alpha <= PI;alpha += teta)
	{
		x = cx + (radius + 0.05) * cos(alpha);
		y = cy + (radius + 0.05) * sin(alpha);
		if (x >= -0.52 && x <= -0.21) {
			glVertex2d(x, y);
		}
	}
	glEnd();

}
void DrawGrass() {
	glColor3d(0, 0.7, 0.35);
	glBegin(GL_POLYGON);
	glVertex2d(-1, -0.3);//left up
	glVertex2d(1, -0.3); // right up
	glVertex2d(1, -1);//right dowen
	glVertex2d(-1, -1);//left dowen
	glEnd();
	glPushMatrix();
	glTranslated(0.45, -0.65 , 0);
	glScaled(0.5, 0.5, 1);
	DrawCircle(40);
	glPopMatrix();

}
void DrawBridge(double cx, double cy, double radius, int num_pts) {
	double alpha, teta = 2*PI/ num_pts;
	double x, y;
	glLineWidth(8);
	glColor3d(0.347, 0.165, 0.165);
	glBegin(GL_LINE_STRIP);
	for (alpha = 0;alpha < PI; alpha += teta)//bridge
	{
		x = cx + radius * cos(alpha);
		y = cy + radius * sin(alpha);
		if(x >= -0.49 && x <= -0.24)
		glVertex2d(x, y);
	}
	glEnd();

	glColor3d(0.296, 0.263, 0.129);
	glBegin(GL_LINE_STRIP);
	for (alpha = 0;alpha < 2 * PI; alpha += teta)//reflection
	{
		x = cx + radius * cos(alpha);
		y = cy + 0.18 + radius * sin(alpha);
		if (x >= -0.49 && x <= -0.24 && y <= -0.7)
		glVertex2d(x, y);
	}
	glEnd();
	glLineWidth(1);
	DrawRail(-0.365, -0.78, 0.15, 50);

}
void DrawRoad()
{
	double alpha, teta = 2 * PI / 100;
	double x, y;
	glColor3d(1.0, 0.647, 0.0);
	glLineWidth(5);

	glBegin(GL_LINE_STRIP);
	glVertex2d(-1, -0.7);//LEFT-LEFT
	glVertex2d(-0.48, -0.7);//RIGHT-LEFT
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2d(-0.26, -0.7);//LEFT-RIGHT
	glVertex2d(1, -0.7);//right-right
	glEnd();

	DrawBridge(-0.365,-0.78,0.15,100);
}
void display()
{
	double delta;
	double y;
	double beta;
	double sunRotate;
	sunRotate = 0.7;
	double cxBridge, cyBridge, radiusBridge; 


	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	// drawings

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // start matrix of transformations from identity
	DrawGrass();
	DrawRiver();
	DrawRoad();
	glPushMatrix();
	glTranslated(-0.8, 0.8, 0);
	glScaled(0.2, 0.2, 1);
	DrawSun();
	glPopMatrix();

	///windmill 1
	glPushMatrix();
	glTranslated(-0.2, 0, 0);
	DrawWindmill();
	glPopMatrix();
	///windmill 2
	glPushMatrix();
	glTranslated(0.85, 0.12, 0);
	DrawWindmill();
	glPopMatrix();

	//cloud 1
	glPushMatrix();
	glTranslated(cloudtwoMove, 0, 0);
	DrawClouds();
	glPopMatrix();

	//cloud 2
	glPushMatrix();
	glTranslated(cloudOneMove, 1, 0);
	glScaled(0.8, 0.8, 1);
	glRotated(-180, 0, 0, 1);
	DrawClouds();
	glPopMatrix();

	// delta is the offset of bicycle
	delta = -0.3*bicycleAngle*wheel_radius*2*PI/360; // 0.3 is the scale rate
	
	cxBridge = -0.365;
	cyBridge = -0.85;
	radiusBridge = 0.26;

	if (delta >= -0.52 && delta <= -0.22) {
		y = cyBridge + sqrt((radiusBridge)*(radiusBridge) - (delta - cxBridge)* (delta - cxBridge));
		beta = (-(delta - cxBridge)) / sqrt((radiusBridge) * (radiusBridge) - (delta - cxBridge) * (delta - cxBridge));
		beta = beta * 180 / PI;
	}
	else {
		y = -0.7 + wheel_radius * 0.3;
		beta = 0;
	}
	glPushMatrix();
	glTranslated(delta, y, 0);
	glScaled(0.3, 0.3, 0);
	if (direction < 0) glRotated(180, 0, 1, 0);
	if (direction > 0) glRotated(beta,0, 0, 1);
	else glRotated(-beta, 0, 0, 1);
	DrawBicycle();
	glPopMatrix();


	glutSwapBuffers(); // show all
}

void idle() 
{
	angle += 0.007;

	bicycleAngle += (0.2 * direction);

	if (cloudOneMove > 1.50) {
		cloudOneMove = cloudOneMove - 2.5;
	}
	else {
		cloudOneMove += 0.00007;
	}

	if (cloudtwoMove > 0.95) {
		cloudtwoMove = cloudtwoMove - 2.6;
	}
	else {
		cloudtwoMove += 0.00005;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		direction = -direction;
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);// defines buffer for virtual display
	glutInitWindowSize(W, H);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Bicycle example");

	glutDisplayFunc(display); // here will be all drawings
	glutIdleFunc(idle); // all the changes must be here and display must be invoked from here
	glutMouseFunc(mouse);

	init();

	glutMainLoop();
}