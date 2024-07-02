
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"

const int W = 600;
const int H = 600;
const int NUM_STARS = 50;
const int MAX_FLOORS = 100;
const int MAX_COLUMNS = 50;
const int MAX_WAVES = 50;


typedef struct
{
	double x, y;
	int size;
}STAR;

typedef struct
{
	double wLong, loc;
}WAVE;

double PI = 3.14156;
STAR stars[NUM_STARS];
bool windows[MAX_FLOORS][MAX_COLUMNS];
WAVE waves[MAX_WAVES];


void init()
{
	int i, j;
	glClearColor(0, 0.5, 0.8, 0);// color of window background
	glOrtho(-1, 1, -1, 1, -1, 1); // set the coordinates system

	srand(time(0));

	for (i = 0;i < NUM_STARS;i++)
	{
		stars[i].x = ((rand() % 2000) - 1000) / 1000.0; // random numbers in range [-1,1)
		stars[i].y = ((rand() % 2000)) / 2000.0; // random numbers in range [0,1)
		stars[i].size = 1 + rand() % 3;
	}

	for (i = 0; i < MAX_FLOORS; i++) {
		for (j = 0; j < MAX_COLUMNS; j++) {
			windows[i][j] = rand() % 100 < 30;
		}
	}

	for (i = 0;i < MAX_WAVES;i++)
	{
		waves[i].wLong = ((rand() % 2000)) / 2000.0; // random numbers in range [0,1)
		waves[i].loc = ((rand() % 2000)) / 2000.0; // random numbers in range [0,1)
		waves[i].loc *= -1;
		if (waves[i].loc >= -0.3) waves[i].loc -= 0.3;
	}
}

void drawWaves() {
	glBegin(GL_LINE_STRIP);
	glColor3d(3, 0, 0);
	int index = 1;
	for (double i = -1; i < 1; i += 0.04) {
		glBegin(GL_LINE_STRIP);
		glColor3d(10, 10, 10);
		glVertex2d(i + waves[index].wLong, waves[index].loc);
		glVertex2d(i, waves[index].loc);
		index++;
		glEnd();
	}
}


void DrawWindows(double x, double y, double width, double height)
{
	int i, j;
	double wwidth = 0.01, wheight = 0.02;
	int num_stores = height / wheight;
	int windows_in_line = width / wwidth;

	glColor3d(1, 1, 0.6);
	glBegin(GL_POINTS);
	for (i = 0;i < num_stores;i++)
		for (j = 0;j < windows_in_line;j++)
		{
			if (windows[i][j]) glColor3d(1, 1, 0.6);
			else glColor3d(0, 0, 0);
			glVertex2d(x + j * wwidth, y - i * wheight);
		}
	glEnd();
}



void DrawOneBuilding(double x, double y, double width, double height, int type) {

	int move = 0.08;
	glBegin(GL_POLYGON);

	if (type == 1) {
		glColor3d(0.2, 0.2, 0.3);
	}
	else if (type == 2) {
		glColor3d(0.6, 0.6, 0.3);
	}
	else if (type == 3) {
		glColor3d(0.5, 0.2, 0.3);
	}
	glVertex2d(x, y); // 1

	if (y < 0) {
		glColor3d(0.3, 0.3, 0);
	}
	else if (type == 1) {
		glColor3d(0.4, (1 - fabs(0.5 * x)) * 0.4, 0.8);
	}
	else if (type == 2) {
		glColor3d(0.8, 0.8, 0.6);
	}
	else if (type == 3) {
		glColor3d(0.2, 0.2, 0.5);
	}
	glVertex2d(x, y - height); // 2
	glVertex2d(x + width, y - height); // 3
	

	if (type == 1) {
		glColor3d(0.2, 0.2, 0.2);
	}
	else if (type == 2) {
		glColor3d(0.6, 0.3, 0.3);
	}
	else if (type == 3) {
		glColor3d(0.2, 0.2, 0.4);
	}
	glVertex2d(x + width, y); // 4

	glEnd();

	if (y < 0) {
		DrawWindows(x, y, width, height);
	}
	else
		DrawWindows(x, y, width, height);

	// kind of 3D - lit by sunset
	glColor3d(0.9, 0.7, 0.2);

	glBegin(GL_POLYGON);
	glVertex2d(x + width - 0.02, y);  // 1
	glVertex2d(x + width - 0.02, y - height);  // 2
	glVertex2d(x + width, y - height);  // 3
	glVertex2d(x + width, y);  // 4
	glEnd();

}

void drawBuildings() {
	double x, y;
	glPointSize(2);

	//far buildings
	for (x = -1;x <= 1;x += 0.13)//how much crouded
	{
		y = 0.1 * cos(0.9 * PI * x) + 0.15 * sin(25 * PI * x) + 0.2;
		DrawOneBuilding(x, y, 0.1, y + 0.3, 1);
		DrawOneBuilding(x, -y - 0.4, 0.1, -y - 0.1, 1);
	}
	//near buildings
	for (x = -1;x <= 1;x += 0.25)
	{
		y = 0.1 * cos(1 * PI * x) + 0.09 * sin(5 * PI * x);

		DrawOneBuilding(x, y, 0.13, y + 0.3, 2);
		DrawOneBuilding(x, -y - 0.5, 0.1, -(y + 0.2), 2);

	}
	//private houses
	for (x = -1;x <= 1;x += 0.15)//how much crouded
	{
		y = 0.05 * cos(1 * PI * x) + 0.05 * sin(5 * PI * x) - 0.15;
		DrawOneBuilding(x, y, 0.1, y + 0.3, 3);
		DrawOneBuilding(x, -y - 0.5, 0.1, -(y + 0.2), 3);

	}
	glEnd();
}

void DrawMoon(double cx, double cy, double radius, int num_pts)
{
	double alpha, teta = 2 * PI / num_pts;
	double x, y;

	glColor3d(0.8, 0.8, 0.6);
	glBegin(GL_POLYGON);
	for (alpha = 0;alpha < 2 * PI;alpha += teta)
	{
		x = cx + radius * cos(alpha);
		y = cy + radius * sin(alpha);
		glVertex2d(x, y);
	}
	glEnd();

}

void drawBackground() {
	int i;
	//sky
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.2);
	glVertex2d(-1, 1);
	glVertex2d(1, 1);
	glColor3d(0.5, 0.6, 0.5);
	glVertex2d(1, -0.2);
	glVertex2d(-1, -0.2);
	glEnd();

	// reflections
	glBegin(GL_POLYGON);
	glColor3d(0.5, 0.6, 0.5);
	glVertex2d(-1, -0.2);
	glVertex2d(1, -0.2);
	glColor3d(0, 0, 0.2);
	glVertex2d(1, -1);
	glVertex2d(-1, -1);
	glEnd();

	// add stars
	glColor3d(0.8, 0.8, 0.6);
	for (i = 0;i < NUM_STARS;i++)
	{
		glPointSize(stars[i].size);
		glBegin(GL_POINTS);
		glVertex2d(stars[i].x, stars[i].y);
		glEnd();
	}
	DrawMoon(0.55, 0.45, 0.15, 360);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	drawBackground();
	drawBuildings();
	drawWaves();
	glutSwapBuffers(); // show all
}

void idle()
{
	int row, col;
	int index = rand() % NUM_STARS;
	int indexW = rand() % MAX_WAVES;

	if (rand() % 100 < 2)
		stars[index].size = 1 + rand() % 3;

	if (rand() % 10 < 0.08) {
		row = rand() % MAX_FLOORS;
		col = rand() % MAX_COLUMNS;
		windows[row][col] = !windows[row][col];
	}

	if (rand() % 100 < 5) {
		waves[indexW].loc -= ((rand() & 700) - 700) / 80000.0; // random numbers in range [-1,1);
		if (waves[index].loc >= -0.3) waves[index].loc = -1;
		waves[index].wLong += ((rand() % 2000) - 1000) / 1000.0; // random numbers in range [-1,1);
	}
	glutPostRedisplay();
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("First Example");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	init();

	glutMainLoop();
}