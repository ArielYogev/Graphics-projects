
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
/////////////////////////////guy&ariel
typedef struct
{
	int x, y;
} POINT2D;

const int W = 600;
const int H = 600;

unsigned char pixels[H][W][3] = { 0 };

double offset = 0;

POINT2D startPt = { 0,0 }; // start point

double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void init()
{
	int i, j;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	glutSwapBuffers(); // show all
}

void DrawLine(POINT2D s, POINT2D t)
{
	int row, col;
	double a, b;

	if (t.x != s.x)
	{
		a = (t.y - s.y) / ((double)t.x - s.x);
		b = s.y - a * s.x;
		if (fabs(a) < 1) // the absolute slope is below PI/4
		{

			if (s.x > t.x)
			{
				POINT2D tmp = s;
				s = t;
				t = tmp;
			}

			for (col = s.x;col <= t.x;col++)
			{
				row = a * col + b + 0.5;
				pixels[row][col][0] = 0;
				pixels[row][col][1] = 0;
				pixels[row][col][2] = 255;
			}
		}
		else // the absolute slope is above PI/4
		{
			b = -b / a; // new a and b
			a = 1 / a;

			if (s.y > t.y)
			{
				POINT2D tmp = s;
				s = t;
				t = tmp;
			}

			for (row = s.y;row <= t.y;row++)
			{
				col = a * row + b;
				pixels[row][col][0] = 0;
				pixels[row][col][1] = 0;
				pixels[row][col][2] = 255;
			}
		}
	}
}

void DrawMyBackground()
{
	int i, j, y, x;
	double dist;
	for (i = 0;i < H;i++) {
		for (j = 0;j < W;j++) {
			dist = distance(i, j, H / 2, -W);

			if ((i <= 200 && i >= 100) || (i <= 500 && i >= 400)) {
				pixels[i][j][2] = 200 + 50 * (sin(dist / 30.0 - offset));
			}
			else {
				pixels[i][j][0] = 200 + 50 * (sin(dist / 30.0 - offset));
				pixels[i][j][1] = 200 + 50 * (sin(dist / 30.0 - offset));
				pixels[i][j][2] = 200 + 50 * (sin(dist / 30.0 - offset));
			}
		}
	}

	// triangle 1
	POINT2D pt1 = { W/2, H/1.7 };
	POINT2D pt2 = { W/2 + W/8, H/1.7 - H/6 };
	POINT2D pt3 = { W/2 - W/8, H/1.7 - H/6 };
	DrawLine(pt1, pt2);
	DrawLine(pt2, pt3);
	DrawLine(pt3, pt1);

	// triangle 2
	POINT2D tr2pt1 = { W/2, H/2.7 };
	POINT2D tr2pt2 = { W/2 + W/8, H/2.7 + H/6 };
	POINT2D tr2pt3 = { W/2 - W/8, H/2.7 + H/6 };
	DrawLine(tr2pt1, tr2pt2);
	DrawLine(tr2pt2, tr2pt3);
	DrawLine(tr2pt3, tr2pt1);

}


void idle()
{
	offset += 0.1;
	DrawMyBackground();
	glutPostRedisplay();
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Pixels Example");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	init();

	glutMainLoop();
}