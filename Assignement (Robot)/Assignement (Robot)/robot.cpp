/**
	Name:		Goh Kok Dong, Koh Xin Hao
	StudID:		20WMR09455, 20WMR09471
	Group:		RSF2 G4
	Date:		7/9/2020
	Project:	robot.cpp
	Assignment:	Giant Robot
*/

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Giant Robot"

// Instructions

#pragma region Functions Declaration
void drawSquareLine(float width, float height, float r, float g, float b);
void drawSquare(float width, float height, float r, float g, float b);
void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, float r, float g, float b);
void drawCircle(float radius, float r, float g, float b);
void drawPillar(float width, float height, float depth);
void drawSphere(double radius, int sliceNo, int stackNo);
void drawCylinderLine(double baseRadius, double topRadius, double height, int sliceNo, int stackNo);

void legFirstcomponent();
void legSecondComponent();
void legThirdComponent();
void legFourthComponent();
void drawLeftNut();
void drawRightNut();
void leg();
void drawLeg();

void drawFirstWeapon();
void mainBody();
void bodyFirstComponents();
void bodySecondComponents();
void drawBody();

void projection();
void drawStar();
void drawBackground();
void lighting(float x, float y, float z);
void clearScreen();

void drawMainHead();
void headFirstComponent();
void drawHead();

void drawHand();
void drawHandFirstPart();
void drawHandSecondPart();
void drawHandThirdPart();
void drawPalm();
void drawFinger();
void drawFingerPart();

void walkingAnimation();
void fingerAnimation();
void shootingAnimation();
void spawnBullet();
void armsDown();

void drawing();
void display();

#pragma endregion

#pragma region Variables Declaration
// Background Color
float r = 1, g = 1, b = 1;

// Variables declaration for projection
bool isOrtho = true;

// Genaral rotation
int Tx = 0, Ry = 0, Rx = 0, Tz = 0, tSpeed = 1, rSpeed = 1, rotate = 0;
float walkingSpeed = 0.5, bulletSpeed = 0.1;

// Movement speed
float headRotationSpeed = 0;
float leftLegRotationSpeed = 0, rightLegRotationSpeed = 0;
float leftSubLegRotationSpeed = 0, rightSubLegRotationSpeed = 0;
float bodyRotation = 0;
float armLeftRotation = 0, armRightRotation = 0;
float fingerRotation = 0;
float bulletMovement = 0;

// Circle variables
float x = 0, y = 0, x2 = 0, y2 = 0;
float angle = 0;// radius = 1;

// Texture variable declaration
BITMAP BMP;          // Bitmap structure
HBITMAP hBMP = NULL;  // Bitmap handle

// Lighthing declaration
float diff[] = { 0.0, 1.0, 1.0 };
bool isLightOn = false;
bool ambLightOn = true;
float posX = 0, posY = 50, posZ = 50;
float posL[3];
float ambM[] = { 0.0, 0.0, 1.0 };
float amb[] = { 1.0, 0.0, 1.0 };

// Variables declatation for customization
bool showBodyUltility = true, showfirstWeapon = true, showRocket = true;
bool showStar = false;

// Variables declaration for texture 
bool textureOn = false;

bool leftLeg = true;
bool rightLeg = true;
bool leftArm = true;
bool rightArm = true;
bool leftFoot = true;
bool rightFoot = true;
bool moveFinger = true;

// Variables declaration for animation
bool walking = false;
bool moveFingerAnimate = false;
bool shooting = false;
bool armValidate = false;

#pragma endregion

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == VK_UP) {
			if (isOrtho) {
				if (Tz < 40.0)
					Tz += tSpeed;
			}
			else {
				if (Tz < 55.0)
					Tz += tSpeed;
			}
		}
		else if (wParam == VK_DOWN) {
			if (isOrtho) {
				if (Tz > -45.0)
					Tz -= tSpeed;
			}
			else {
				if (Tz > 10.0)
					Tz -= tSpeed;
			}
		}
		else if (wParam == 'O') {
			Tz = 0;
			isOrtho = true;
		}
		else if (wParam == 'P')
		{
			Tz = 60.0;
			isOrtho = false;
		}
		else if (wParam == VK_LEFT) {
			Ry += rSpeed;
		}
		else if (wParam == VK_RIGHT) {
			Ry -= rSpeed;
		}
		else if (wParam == 'L') {
			if (Tx > -50)
				Tx -= tSpeed;
		}
		else if (wParam == 'R') {
			if (Tx < 50)
				Tx += tSpeed;
		}
		else if (wParam == 'A') {
			Rx -= rSpeed;
		}
		else if (wParam == 'Z') {
			Rx += rSpeed;
		}
		else if (wParam == VK_SPACE) {  // Open and close light
			if (isLightOn == false) {
				isLightOn = true;
				ambLightOn = true;
			}
			else {
				isLightOn = false;
				ambLightOn = false;
			}
		}
		else if (wParam == 'Q') {  // Move head
			if (headRotationSpeed > -10)
				headRotationSpeed -= rSpeed;
		}
		else if (wParam == 'E') {  // Move head
			if (headRotationSpeed < 8)
				headRotationSpeed += rSpeed;
		}
		else if (wParam == 'W') {  // Move leg
			if (leftLegRotationSpeed < 10) {
				leftLegRotationSpeed += rSpeed;
				rightLegRotationSpeed -= rSpeed;
			}
		}
		else if (wParam == 'S') {  // Move leg
			if (leftLegRotationSpeed > -10) {
				leftLegRotationSpeed -= rSpeed;
				rightLegRotationSpeed += rSpeed;
			}
		}
		else if (wParam == 0x31) {  // Customization : shows utility
			if (showBodyUltility)
				showBodyUltility = false;
			else
				showBodyUltility = true;
		}
		else if (wParam == 0x32) {  // Customization : shows body weapon
			if (showfirstWeapon)
				showfirstWeapon = false;
			else
				showfirstWeapon = true;
		}
		else if (wParam == 0x33) {   // Customization : shows rocket
			if (showRocket)
				showRocket = false;
			else
				showRocket = true;
		}
		else if (wParam == 'T') {
			if (bodyRotation > -5)
				bodyRotation -= rSpeed;
		}
		else if (wParam == 'Y') {
			if (bodyRotation < 4)
				bodyRotation += rSpeed;
		}
		else if (wParam == 0x10) {
			if (textureOn == false)
				textureOn = true;
			else
				textureOn = false;
		}
		else if (wParam == VK_F1)
			posX -= 5;
		else if (wParam == VK_F2)
			posX += 5;
		else if (wParam == VK_F3)
			posY -= 5;
		else if (wParam == VK_F4)
			posY += 5;
		else if (wParam == VK_F5)
			posZ += 5;
		else if (wParam == VK_F6)
			posZ -= 5;
		else if (wParam == 'D') {
			if (leftSubLegRotationSpeed < 2) {
				leftSubLegRotationSpeed += rSpeed;
				rightSubLegRotationSpeed += rSpeed;
			}

		}
		else if (wParam == 'F') {
			if (leftSubLegRotationSpeed > -2) {
				leftSubLegRotationSpeed -= rSpeed;
				rightSubLegRotationSpeed -= rSpeed;
			}
		}
		else if (wParam == 0x34) {  // Change background color
			r = 0.69;
			g = 1;
			b = 1;
		}
		else if (wParam == 0x35) {  // Change background color
			r = 1;
			g = 0.92;
			b = 0.69;
		}
		else if (wParam == 0x36) {  // Change background color
			r = 1;
			g = 1;
			b = 1;
		}
		else if (wParam == 0x37) {

			if (showStar == false) {
				showStar = true;
			}
			else
				showStar = false;
		}
		else if (wParam == 'N') {
			if (armLeftRotation < 15)
			{
				armLeftRotation += rSpeed;
				armRightRotation -= rSpeed;
			}
			
		}
		else if (wParam == 'M') {
			if (armLeftRotation > -15)
			{
				armLeftRotation -= rSpeed;
				armRightRotation += rSpeed;
			}

		}
		else if (wParam == 0x38) {
			if (walking)
				walking = false;
			else
				walking = true;
		}
		else if (wParam == 0x39) {
			if(moveFingerAnimate)
				moveFingerAnimate = false;
			else
				moveFingerAnimate = true;
		}
		else if (wParam == 'X') {
			if (shooting)
				shooting = false;
			else
				shooting = true;
		}
		else if (wParam == 'K') {
			Tx = 0, Ry = 0, Rx = 0, Tz = 0, tSpeed = 1, rSpeed = 1, rotate = 0;
			headRotationSpeed = 0;
			leftLegRotationSpeed = 0, rightLegRotationSpeed = 0;
			leftSubLegRotationSpeed = 0, rightSubLegRotationSpeed = 0;
			bodyRotation = 0;
			armLeftRotation = 0, armRightRotation = 0;
			fingerRotation = 0;
			bulletMovement = 0;
			showBodyUltility = true, showfirstWeapon = true, showRocket = true;
			showStar = false;
			textureOn = false;
			walking = false;
			moveFingerAnimate = false;
			shooting = false;
			armValidate = false;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

GLuint loadTexture(LPCSTR filename) {

	// take from step 1
	GLuint texture = 0;  //texture name

	// Step 3 : Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	// Step 4 : Assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// 5. Step 5: Remove texture info
	DeleteObject(hBMP);


	return texture;

}

#pragma region Reusable Object code
void drawSquareLine(float width, float height, float r, float g, float b) {

	glColor3f(r, g, b);
	glBegin(GL_LINE_LOOP);

	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height);
	glVertex2f(0, height);

	glEnd();
}

void drawSquare(float width, float height, float r, float g, float b) {

	glColor3f(r, g, b);
	glBegin(GL_POLYGON);

	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height);
	glVertex2f(0, height);

	glEnd();
}

void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, float r, float g, float b) {

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(r, g, b);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, baseRadius, topRadius, height, slices, stacks);
	gluDeleteQuadric(cylinder);
	glPopMatrix();
}

void drawCircle(float radius, float r, float g, float b) {

	glBegin(GL_TRIANGLE_FAN);

	glColor3f(r, g, b);
	glVertex2f(x, y);

	for (angle = 0; angle <= 360; angle += 0.1) {

		x2 = x + radius * (cos(angle));
		y2 = y + radius * (sin(angle));
		glVertex2f(x2, y2);

	}


	glEnd();
}

void drawPillar(float width, float height, float depth) {

	GLuint textures[2];

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	glColor3f(1, 0, 0);
	// Front face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, depth);
	glTexCoord2f(0.5, 1);
	glVertex3f(width, 0, depth);
	glTexCoord2f(0.5, 0);
	glVertex3f(width, -height, depth);
	glTexCoord2f(0, 0);
	glVertex3f(0, -height, depth);

	glEnd();

	glColor3f(0, 1, 0);

	// Back face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1);
	glVertex3f(width, 0, 0);
	glTexCoord2f(0.5, 0);
	glVertex3f(width, -height, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, -height, 0);

	glEnd();

	glColor3f(0, 0, 1);

	// Left face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1);
	glVertex3f(0, 0, depth);
	glTexCoord2f(0.5, 0);
	glVertex3f(0, -height, depth);
	glTexCoord2f(0, 0);
	glVertex3f(0, -height, 0);

	glEnd();

	glColor3f(1, 0, 1);

	// Right face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(width, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, depth);
	glTexCoord2f(0.5, 0);
	glVertex3f(width, -height, depth);
	glTexCoord2f(0, 0);
	glVertex3f(width, -height, 0);

	glEnd();

	glColor3f(1, 1, 0);
	// Top face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1);
	glVertex3f(0, 0, depth);
	glTexCoord2f(0.5, 0);
	glVertex3f(width, 0, depth);
	glTexCoord2f(0, 0);
	glVertex3f(width, 0, 0);

	glEnd();

	glColor3f(0, 1, 1);
	// Bottom face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(0, -height, 0);
	glTexCoord2f(0.5, 1);
	glVertex3f(0, -height, depth);
	glTexCoord2f(0.5, 0);
	glVertex3f(width, -height, depth);
	glTexCoord2f(0, 0);
	glVertex3f(width, -height, 0);

	glEnd();

	glDeleteTextures(1, &textures[0]);

}

void drawSphere(double radius, int sliceNo, int stackNo) {

	GLuint textures[2];

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	// gluSphere(sphere, radius, slides, stacks);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, radius, sliceNo, stackNo);
	gluDeleteQuadric(sphere);

	glDeleteTextures(1, &textures[0]);

}

void drawCylinderLine(double baseRadius, double topRadius, double height, int sliceNo, int stackNo) {

	GLuint textures[2];

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GLU_LINE);
	// gluSphere(sphere, radius, slides, stacks);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, baseRadius, topRadius, height, sliceNo, stackNo);
	gluDeleteQuadric(cylinder);

	glDeleteTextures(1, &textures[0]);
}

#pragma endregion

#pragma region Display Leg
void legFirstcomponent() {

	GLuint textures[2];

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	glColor3f(1, 0, 0);

	// Front face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -25, 11);
	glTexCoord2f(1, 1);
	glVertex3f(11, -25, 11);
	glTexCoord2f(1, 0);
	glVertex3f(12, -40, 12);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -40, 12);

	glEnd();

	glColor3f(0, 1, 0);

	// Back face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(11, -25, -1);
	glTexCoord2f(1, 0);
	glVertex3f(12, -40, -2);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -40, -2);

	glEnd();

	glColor3f(0, 0, 1);

	// Left face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -25, 11);
	glTexCoord2f(1, 0);
	glVertex3f(-2, -40, 12);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -40, -2);

	glEnd();

	glColor3f(1, 0, 1);

	// Right face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(11, -25, -1);
	glTexCoord2f(1, 1);
	glVertex3f(11, -25, 11);
	glTexCoord2f(1, 0);
	glVertex3f(12, -40, 12);
	glTexCoord2f(0, 0);
	glVertex3f(12, -40, -2);

	glEnd();

	glColor3f(1, 1, 0);
	// Top face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -25, 11);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -25, -1);
	glTexCoord2f(1, 0);
	glVertex3f(11, -25, -1);
	glTexCoord2f(0, 0);
	glVertex3f(11, -25, 11);

	glEnd();

	glColor3f(0, 1, 1);
	// Bottom face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-2, -40, -2);
	glTexCoord2f(1, 1);
	glVertex3f(-2, -40, 12);
	glTexCoord2f(1, 0);
	glVertex3f(12, -40, 12);
	glTexCoord2f(0, 0);
	glVertex3f(12, -40, -2);

	glEnd();

	glDeleteTextures(1, &textures[0]);

}

void legSecondComponent() {

	GLuint textures[2];

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	glColor3f(1, 1, 0);
	// Top Front face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 0);
	glVertex3f(-2, -42, 11);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -42, -2);
	glTexCoord2f(0.5, 1);
	glVertex3f(12, -42, -2);
	glTexCoord2f(0.5, 0);
	glVertex3f(12, -42, 11);

	glEnd();

	glColor3f(0, 1, 0);
	// First front face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-2, -42, 11);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, -45.1, 13);
	glTexCoord2f(1, 0);
	glVertex3f(12.25, -45.1, 13);
	glTexCoord2f(1, 1);
	glVertex3f(12, -42, 11);

	glEnd();

	glColor3f(1, 0, 0);
	//Second front face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-2.25, -45, 13);
	glTexCoord2f(0, 0);
	glVertex3f(-2.25, -46, 13);
	glTexCoord2f(1, 0);
	glVertex3f(12.25, -46, 13);
	glTexCoord2f(1, 1);
	glVertex3f(12.25, -45, 13);

	glEnd();

	glColor3f(1, 0, 1);
	// Bottom Face
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-2.5, -46, 13);
	glTexCoord2f(1, 1);
	glVertex3f(12.5, -46, 13);
	glTexCoord2f(1, 0);
	glVertex3f(12.5, -46, -2.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, -46, -2.5);

	glEnd();

	// Back face
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-2, -42, -2);
	glTexCoord2f(1, 1);
	glVertex3f(12, -42, -2);
	glTexCoord2f(1, 0);
	glVertex3f(12.5, -46, -2.5);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, -46, -2.5);

	glEnd();

	// Left face
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.8, 1);
	glVertex3f(-2, -42, 11);
	glTexCoord2f(0.2, 1);
	glVertex3f(-2, -42, -2);
	glTexCoord2f(0, 0);
	glVertex3f(-2.5, -46, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(-2.5, -46, 13);
	glTexCoord2f(1, 0.1);
	glVertex3f(-2.5, -45, 13);

	glEnd();

	// Right face
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.8, 1);
	glVertex3f(12, -42, 11);
	glTexCoord2f(0.2, 1);
	glVertex3f(12, -42, -2);
	glTexCoord2f(0, 0);
	glVertex3f(12.5, -46, -2.5);
	glTexCoord2f(1, 0);
	glVertex3f(12.5, -46, 13);
	glTexCoord2f(1, 0.1);
	glVertex3f(12.25, -45, 13);

	glEnd();

	// Top pentagon
	// Front face
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -41, 10);
	glTexCoord2f(1, 1);
	glVertex3f(11, -41, 10);
	glTexCoord2f(1, 0);
	glVertex3f(12, -42, 11);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -42, 11);

	glEnd();

	// Back Face
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-1, -41, -1);
	glTexCoord2f(1, 1);
	glVertex3f(11, -41, -1);
	glTexCoord2f(1, 0);
	glVertex3f(12, -42, -2);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -42, -2);

	glEnd();

	// Left Face
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.9, 1);
	glVertex3f(-1, -41, 10);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -41, -1);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -42, -2);
	glTexCoord2f(0.1, 1);
	glVertex3f(-2, -42, 11);

	glEnd();

	// Right Face
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.9, 1);
	glVertex3f(11, -41, 10);
	glTexCoord2f(1, 0);
	glVertex3f(11, -41, -1);
	glTexCoord2f(0, 0);
	glVertex3f(12, -42, -2);
	glTexCoord2f(0.1, 1);
	glVertex3f(12, -42, 11);

	glEnd();

	// Top Face
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(1, 0);
	glVertex3f(-1, -41, -1);
	glTexCoord2f(1, 1);
	glVertex3f(11, -41, -1);
	glTexCoord2f(0, 1);
	glVertex3f(11, -41, 10);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -41, 10);

	glEnd();

	// Bottom Face
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(1, 0);
	glVertex3f(-2, -42, 11);
	glVertex3f(-1, -41, -1);
	glTexCoord2f(1, 1);
	glVertex3f(12, -42, 11);
	glTexCoord2f(0, 1);
	glVertex3f(12, -42, -2);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -42, -2);

	glEnd();

	glDeleteTextures(1, &textures[0]);

	glColor3f(0, 0, 0);
	//glLineWidth(10);
	//Second front face

	//glTranslatef(1, 0, 0);

	// Draw leg lines
	glBegin(GL_LINES);

	glVertex3f(0.8, -45, 13.1);
	glVertex3f(0.8, -46, 13.1);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(3.6, -45, 13.1);
	glVertex3f(3.6, -46, 13.1);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(6.4, -45, 13.1);
	glVertex3f(6.4, -46, 13.1);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(9.2, -45, 13.1);
	glVertex3f(9.2, -46, 13.1);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(0.8, -42, 11);
	glVertex3f(0.8, -45, 13);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(3.6, -42, 11);
	glVertex3f(3.6, -45, 13);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(6.4, -42, 11);
	glVertex3f(6.4, -45, 13);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(9.2, -42, 11);
	glVertex3f(9.2, -45, 13);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(12, -42, 11);
	glVertex3f(12.6, -46, 8);

	glEnd();

	glBegin(GL_LINES);

	glVertex3f(-2.2, -42, 11);
	glVertex3f(-2.2, -46, 8);

	glEnd();
}

void legThirdComponent() {

	GLuint textures[2];

	GLUquadricObj* cylinder1 = NULL;
	cylinder1 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder1, GLU_FILL);

	GLUquadricObj* cylinder2 = NULL;
	cylinder2 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder2, GLU_FILL);

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	// Draw Cylinder 1
	glPushMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-5, -5, 0);
	glColor3f(1, 0, 0);
	gluQuadricTexture(cylinder1, true);
	gluCylinder(cylinder1, 0.75, 0.75, 10, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder1);

	// Draw Cylinder 2
	glPushMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-5, -2, 0);
	glColor3f(0, 1, 0);
	gluQuadricTexture(cylinder2, true);
	gluCylinder(cylinder2, 0.75, 0.75, 10, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder2);
	glDeleteTextures(1, &textures[0]);

	glPushMatrix();
	glTranslatef(2.25, 2, 2);
	drawPillar(3, 10, 5);
	glPopMatrix();

}

void legFourthComponent() {

	glPushMatrix();
	glTranslatef(-10, 2.5, 0);
	drawPillar(30, 1, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.75, 3.5, 0);
	drawPillar(20, 1.5, 10);
	glPopMatrix();

}

void drawLeftNut() {

	// Draw Nut
	glPushMatrix();
	glTranslatef(-6, -31, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Front Nut
	// Draw Nut
	glPushMatrix();
	glTranslatef(-2, -31, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-6, -13.5, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-2, -13.5, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-6, -2, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-2, -2, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Back Nut
	// Draw Nut
	glPushMatrix();
	glTranslatef(-6, -31, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -31, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-6, -13.5, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-2, -13.5, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-6, -2, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(-2, -2, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

}

void drawRightNut() {

	// Draw Nut
	glPushMatrix();
	glTranslatef(10, -31, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Front Nut
	// Draw Nut
	glPushMatrix();
	glTranslatef(14, -31, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(10, -13.5, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(14, -13.5, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(10, -2, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(14, -2, 10.1);
	drawCircle(0.7, 0, 1, 0);
	glPopMatrix();

	// Back Nut
	// Draw Nut
	glPushMatrix();
	glTranslatef(10, -31, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, -31, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(14, -13.5, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(10, -13.5, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(14, -2, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

	// Draw Nut
	glPushMatrix();
	glTranslatef(10, -2, -0.1);
	drawCircle(0.7, 1, 0, 0);
	glPopMatrix();

}

void leg() {

	glPushMatrix();
	drawPillar(10, 33, 10);
	glPushMatrix();
	glTranslatef(0, 10, 0);
	legFirstcomponent();
	glPopMatrix();
	glPopMatrix();

}

void drawLeg() {

	legThirdComponent();

	// Left leg
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glScalef(0.8, 1, 1);
	glTranslatef(-10, 0, 0);
	glRotatef(leftLegRotationSpeed, 1, 0, 0);
	leg();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(leftLegRotationSpeed, 1, 0, 0);
	drawLeftNut();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glScalef(0.8, 1, 1);
	glTranslatef(-10, 10, 0);
	glPushMatrix();
	glRotatef(leftLegRotationSpeed, 1, 0, 0);
	glRotatef(leftSubLegRotationSpeed, 1, 0, 0);
	legSecondComponent();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// Right leg
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glScalef(0.8, 1, 1);
	glTranslatef(10, 0, 0);
	glRotatef(rightLegRotationSpeed, 1, 0, 0);
	leg();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(rightLegRotationSpeed, 1, 0, 0);
	drawRightNut();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glScalef(0.8, 1, 1);
	glTranslatef(10, 10, 0);
	glPushMatrix();
	glRotatef(rightLegRotationSpeed, 1, 0, 0);
	glRotatef(rightSubLegRotationSpeed, 1, 0, 0);
	legSecondComponent();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 0, 0);
	legFourthComponent();
	glPopMatrix();

}

#pragma endregion

#pragma region Display Body
// Draw Katana
void drawFirstWeapon() {

	GLuint textures[2];

	GLUquadricObj* cylinder1 = NULL;
	cylinder1 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder1, GLU_FILL);

	GLUquadricObj* cylinder2 = NULL;
	cylinder2 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder2, GLU_FILL);

	GLUquadricObj* cylinder3 = NULL;
	cylinder3 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder3, GLU_FILL);

	if (textureOn)
		textures[0] = loadTexture("FirstWeopon.bmp");

	glPushMatrix();
	glPushMatrix();

	glRotatef(-20, 0, 0, 1);
	glTranslatef(-23, 5, -9);

	// Draw Cylinder 1
	glPushMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(35, 10, -40);
	glColor3f(1, 0, 0);
	gluQuadricTexture(cylinder1, true);
	gluCylinder(cylinder1, 1.5, 1.5, 10, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix();

	glRotatef(-20, 0, 0, 1);
	glTranslatef(-23, 5, -9);

	glPushMatrix();
	glRotatef(bodyRotation, 0, 1, 0);

	// Draw Cylinder 2
	glPushMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(35, 10, -30);
	glColor3f(0, 1, 0);
	gluQuadricTexture(cylinder2, true);
	gluCylinder(cylinder2, 3, 3, 2, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix();

	glRotatef(-20, 0, 0, 1);
	glTranslatef(-23, 5, -9);

	glPushMatrix();
	glRotatef(bodyRotation, 0, 1, 0);
	// Draw Cylinder 3
	glPushMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(35, 10, -28);
	glColor3f(0, 0, 1);
	gluQuadricTexture(cylinder3, true);
	gluCylinder(cylinder3, 1.5, 1.5, 20, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glDeleteTextures(1, &textures[0]);

}

void mainBody() {

	GLuint textures[2];

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	// Back face
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-25, 20, -3);
	glTexCoord2f(1, 1);
	glVertex3f(25, 20, -3);
	glTexCoord2f(0.8, 0);
	glVertex3f(15, 2.5, 0);
	glTexCoord2f(0.2, 0);
	glVertex3f(-15, 2.5, 0);

	glEnd();

	// Bottom face
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 0.75);
	glVertex3f(-15, 2.5, 10);
	glTexCoord2f(0, 0.25);
	glVertex3f(-15.0, 2.5, 0);
	glTexCoord2f(0, 0.75);
	glVertex3f(15, 2.5, 0);
	glTexCoord2f(1, 0.25);
	glVertex3f(15, 2.5, 10);

	glEnd();

	// Left face
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-15, 2.5, 10);
	glTexCoord2f(0.5, 1);
	glVertex3f(-15.0, 2.5, 0);
	glTexCoord2f(0.5, 0);
	glVertex3f(-25, 20, -3);
	glTexCoord2f(0, 0);
	glVertex3f(-25, 20, 13);

	glEnd();

	// Right face
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(15, 2.5, 10);
	glTexCoord2f(0.5, 1);
	glVertex3f(15.0, 2.5, 0);
	glTexCoord2f(0.5, 0);
	glVertex3f(25, 20, -3);
	glTexCoord2f(0, 0);
	glVertex3f(25, 20, 13);

	glEnd();

	// Front Main face
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-18, 16, 15);
	glTexCoord2f(0, 0);
	glVertex3f(-12.5, 6.5, 15);
	glTexCoord2f(1, 0);
	glVertex3f(12.5, 6.5, 15);
	glTexCoord2f(1, 1);
	glVertex3f(18, 16, 15);

	glEnd();

	// Top front face
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-25, 20, 13);
	glTexCoord2f(1, 1);
	glVertex3f(25, 20, 13);
	glTexCoord2f(0.8, 0);
	glVertex3f(18, 16, 15);
	glTexCoord2f(0.2, 0);
	glVertex3f(-18, 16, 15);

	glEnd();

	// Bottom front face
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-12.5, 6.5, 15);
	glTexCoord2f(0.8, 1);
	glVertex3f(12.5, 6.5, 15);
	glTexCoord2f(1, 0);
	glVertex3f(15, 2.5, 10);
	glTexCoord2f(0, 0);
	glVertex3f(-15, 2.5, 10);

	glEnd();

	// Left front face
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-25, 20, 13);
	glTexCoord2f(0.5, 0.8);
	glVertex3f(-18, 16, 15);
	glTexCoord2f(0.5, 0.2);
	glVertex3f(-12.5, 6.5, 15);
	glTexCoord2f(0, 0);
	glVertex3f(-15, 2.5, 10);

	glEnd();

	// Right front face
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(25, 20, 13);
	glTexCoord2f(0.5, 0.8);
	glVertex3f(18, 16, 15);
	glTexCoord2f(0.5, 0.2);
	glVertex3f(12.5, 6.5, 15);
	glTexCoord2f(0, 0);
	glVertex3f(15, 2.5, 10);

	glEnd();

	// Top face
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-25, 20, -3);
	glTexCoord2f(1, 1);
	glVertex3f(-25, 20, 13);
	glTexCoord2f(1, 0);
	glVertex3f(25, 20, 13);
	glTexCoord2f(0, 0);
	glVertex3f(25, 20, -3);

	glEnd();

	glDeleteTextures(1, &textures[0]);

	// Line for left front face
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	glVertex3f(-25.1, 20, 13);
	glVertex3f(-12.6, 6.5, 15);

	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	glVertex3f(-18, 16, 15);
	glVertex3f(-15, 2.5, 10);

	glEnd();

	// Line for right front face
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	glVertex3f(18, 16, 15);
	glVertex3f(15, 2.5, 10);

	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	glVertex3f(25, 20, 13);
	glVertex3f(12.5, 6.5, 15);

	glEnd();



}

void bodyFirstComponents() {

	float rotateBall = 0;

	rotateBall += rSpeed;

	GLuint textures[4];

	GLUquadricObj* cylinder1 = NULL;
	cylinder1 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder1, GLU_FILL);

	GLUquadricObj* cylinder2 = NULL;
	cylinder2 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder2, GLU_FILL);

	GLUquadricObj* cylinder3 = NULL;
	cylinder3 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder3, GLU_FILL);

	GLUquadricObj* cylinder4 = NULL;
	cylinder4 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder4, GLU_FILL);

	GLUquadricObj* cylinder5 = NULL;
	cylinder5 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder5, GLU_FILL);

	GLUquadricObj* cylinder6 = NULL;
	cylinder6 = gluNewQuadric();
	gluQuadricDrawStyle(cylinder6, GLU_FILL);

	GLUquadricObj* sphere1 = NULL;
	sphere1 = gluNewQuadric();

	GLUquadricObj* sphere2 = NULL;
	sphere2 = gluNewQuadric();

	// Draw roket
	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 0, 1);
	glRotatef(110, 1, 0, 0);
	glTranslatef(3, -6, -18);
	if (textureOn)
		textures[0] = loadTexture("Harzard.bmp");
	gluQuadricTexture(cylinder1, true);
	gluCylinder(cylinder1, 2, 2, 12, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder1);

	glPushMatrix();
	glPushMatrix();
	glColor3f(0, 1, 1);
	glRotatef(110, 1, 0, 0);
	glTranslatef(8, -6, -18);
	gluQuadricTexture(cylinder2, true);
	gluCylinder(cylinder2, 2, 2, 12, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder2);

	glDeleteTextures(1, &textures[0]);

	// Draw light

	if (textureOn)
		textures[2] = loadTexture("Body.bmp");

	glPushMatrix();
	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-12, 6, -27);
	gluQuadricTexture(cylinder3, true);
	gluCylinder(cylinder3, 3.5, 3.5, 5, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder3);
	glDeleteTextures(1, &textures[2]);

	if (textureOn)
		textures[1] = loadTexture("HarzardLight.bmp");

	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 0.6, 0);
	glTranslatef(-12, 27, 6);
	gluQuadricTexture(sphere1, true);
	glRotatef(rotateBall, 1, 0, 0);
	gluQuadricDrawStyle(sphere1, GLU_FILL);
	gluSphere(sphere1, 3, 20, 30);
	gluDeleteQuadric(sphere1);
	glPopMatrix();
	glPopMatrix();

	glDeleteTextures(1, &textures[1]);

	if (textureOn)
		textures[2] = loadTexture("Body.bmp");

	glPushMatrix();
	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(22, 7, -27);
	gluQuadricTexture(cylinder4, true);
	gluCylinder(cylinder4, 3.5, 3.5, 5, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder4);
	glDeleteTextures(1, &textures[2]);

	if (textureOn)
		textures[1] = loadTexture("HarzardLight.bmp");

	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 0.6, 0);
	glTranslatef(22, 27, 7);
	gluQuadricTexture(sphere2, true);
	glRotatef(rotateBall, 1, 0, 0);
	gluQuadricDrawStyle(sphere2, GLU_FILL);
	gluSphere(sphere2, 3, 20, 30);
	gluDeleteQuadric(sphere2);
	glPopMatrix();
	glPopMatrix();

	glDeleteTextures(1, &textures[1]);

	glPushMatrix();
	glTranslatef(10, 16, -3);
	drawPillar(4, 8, 2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 16, -3);
	drawPillar(4, 8, 2.5);
	glPopMatrix();

	if (textureOn)
		textures[1] = loadTexture("HarzardLight.bmp");

	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(12, -2, -9);
	gluQuadricTexture(cylinder5, true);
	gluCylinder(cylinder5, 1, 1, 3, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder5);

	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1, -2, -9);
	gluQuadricTexture(cylinder6, true);
	gluCylinder(cylinder6, 1, 1, 3, 30, 30);
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(cylinder6);
	glDeleteTextures(1, &textures[1]);

}

void bodySecondComponents() {

	// draw line
	glPushMatrix();
	glTranslatef(-7, 10, 15.3);
	drawSquareLine(1.5, 7, 1, 1, 1);
	drawSquare(1.5, 7, 0, 0, 0);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-5.5, 10, 15.3);
	drawSquareLine(1.5, 7, 1, 1, 1);
	drawSquare(1.5, 7, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0, 10, 15.3);
	drawSquareLine(1.5, 7, 1, 1, 1);
	drawSquare(1.5, 7, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 10, 15.3);
	drawSquareLine(1.5, 7, 1, 1, 1);
	drawSquare(1.5, 7, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 13.5, 15.3);
	drawSquare(3.5, 3.5, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 10, 15.3);
	drawSquare(9, 2, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, 17, 15.3);
	drawCircle(1.5, 0, 0, 0);
	glPopMatrix();

}

void drawBody() {

	GLuint textures[2];

	glPushMatrix();
	glPushMatrix();
	glScalef(1, 1.2, 1);
	glTranslatef(4, 0.4, 0);
	glPushMatrix();
	glRotatef(bodyRotation, 0, 1, 0);
	if (textureOn)
		textures[0] = loadTexture("Body.bmp");
	mainBody();
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();
	glPopMatrix();
	//textures[1] = loadTexture("Harzard.bmp");

	if (showRocket)
		bodyFirstComponents();
	//glDeleteTextures(1, &textures[1]);

	if (showfirstWeapon) {
		drawFirstWeapon();
	}


	if (showBodyUltility) {
		glPushMatrix();
		glRotatef(bodyRotation, 0, 1, 0);
		bodySecondComponents();
		glPopMatrix();
	}

	glPopMatrix();
}

#pragma endregion

#pragma region Ultilities
void projection() {

	// Orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glTranslatef(Tx, 0.0, 0.0);
	glRotatef(Ry, 0.0, 1.0, 0.0);
	glRotatef(Rx, 1, 0, 0);

	if (isOrtho)
		glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
	else {
		//Prepective
		//gluPerspective(200, 1.00, -1.0, 1.0);
		//glFrustum(-100.0, 100.0, -100.0, 100.0, 1, 50.0);
		gluPerspective(40, 1.00, -1.0, 1.0);
		glFrustum(-20.0, 20.0, -20.0, 20.0, Tz, 120.0);
	}


}

void drawStar() {

	glColor3f(1, 0.95, 0);

	glPushMatrix();

	glScalef(1, 1, 1.0);


	glBegin(GL_POLYGON);

	glVertex2f(-0.8, 0.0);
	glVertex2f(-0.6, 1);
	glVertex2f(0.6, 1.0);
	glVertex2f(0.8, 0.0);
	glVertex2f(0.0, -0.8);

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(-0.6, 1.0);
	glVertex2f(0.0, 2.4);
	glVertex2f(0.6, 1.0);

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(0.6, 1.0);
	glVertex2f(2.0, 1);
	glVertex2f(0.8, 0.0);

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(0.0, -0.8);
	glVertex2f(0.8, 0.0);
	glVertex2f(1.4, -1.8);

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(-1.4, -1.8);
	glVertex2f(-0.8, 0.0);
	glVertex2f(0.0, -0.8);

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(-2, 1);
	glVertex2f(-0.6, 1.0);
	glVertex2f(-0.8, 0.0);

	glEnd();

	glPopMatrix();

}

void drawBackground() {

	glPushMatrix();
	glTranslatef(-20, 40, -40);
	drawStar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 40, -40);
	drawStar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 45, -40);
	drawStar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 35, -40);
	drawStar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 35, -40);
	drawStar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 45, -40);
	drawStar();
	glPopMatrix();

}

void lighting(float x, float y, float z) {

	//float posL[] = { 0, 50, 50 };
	posL[0] = x;
	posL[1] = y;
	posL[2] = z;

	if (isLightOn) {
		glEnable(GL_LIGHTING);  // Enable lighting for the whole scene
	}
	else {
		glDisable(GL_LIGHTING); //Disable lighting for whole scene
	}

	if (ambLightOn) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_POSITION, posL);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
		glLightfv(GL_LIGHT1, GL_POSITION, posL);
		glEnable(GL_LIGHT1);
	}


}

void clearScreen() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#pragma endregion

#pragma region Display head
void drawMainHead() {

	GLuint textures[2];

	glPushMatrix();
	glScalef(1.5, 1.5, 1);

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	// Front Face
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-5, 10, 5);
	glTexCoord2f(0.8, 1);
	glVertex3f(5, 10, 5);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, 6);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 0, 6);

	glEnd();

	// Back Face
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-5, 10, -5);
	glTexCoord2f(0.8, 1);
	glVertex3f(5, 10, -5);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 0, -6);

	glEnd();

	glDeleteTextures(1, &textures[0]);

	if (textureOn)
		textures[1] = loadTexture("RobotEar.bmp");

	// Right Face
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(5, 10, 5);
	glTexCoord2f(0.8, 1);
	glVertex3f(5, 10, -5);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(0, 0);
	glVertex3f(6, 0, 6);

	glEnd();

	// Left Face
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-5, 10, 5);
	glTexCoord2f(0.8, 1);
	glVertex3f(-5, 10, -5);
	glTexCoord2f(1, 0);
	glVertex3f(-6, 0, -6);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 0, 6);

	glEnd();

	glDeleteTextures(1, &textures[1]);

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	// Top Face
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-5, 10, 5);
	glTexCoord2f(0.8, 1);
	glVertex3f(-5, 10, -5);
	glTexCoord2f(1, 0);
	glVertex3f(5, 10, -5);
	glTexCoord2f(0, 0);
	glVertex3f(5, 10, 5);

	glEnd();

	//  Bottom Face
	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-6, 0, 6);
	glTexCoord2f(0.8, 1);
	glVertex3f(6, 0, 6);
	glTexCoord2f(1, 0);
	glVertex3f(6, 0, -6);
	glTexCoord2f(0, 0);
	glVertex3f(-6, 0, -6);

	glEnd();
	glPopMatrix();

	glDeleteTextures(1, &textures[0]);
}

void headFirstComponent() {

	float ambA[] = { 1, 1, 0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambA);

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	// Draw eye ball : left 
	glPushMatrix();
	glTranslatef(-2.3, 6.5, 5.5);
	drawCircle(1.5, 0, 1, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	// Draw eye ball : right
	glPushMatrix();
	glTranslatef(2.7, 6.5, 5.5);
	drawCircle(1.5, 0, 1, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	// Draw eye : left
	glPushMatrix();
	glTranslatef(-2.9, 6.0, 5.6);
	drawSquare(1, 1, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	// Draw eye : right
	glPushMatrix();
	glTranslatef(2.2, 6.0, 5.6);
	drawSquare(1, 1, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	// Draw mounth
	glPushMatrix();
	glTranslatef(-3, 0, 6);
	drawSquare(6, 3, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	// Draw back head utilities
	glPushMatrix();
	glTranslatef(2, 6, -5.5);
	drawSquareLine(1.5, 1.5, 1, 1, 1);
	drawSquare(1.5, 1.5, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	glPushMatrix();
	glTranslatef(2, 4.5, -5.7);
	drawSquareLine(1.5, 1.5, 1, 1, 1);
	drawSquare(1.5, 1.5, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	glPushMatrix();
	glTranslatef(2, 3, -6);
	drawSquareLine(1.5, 1.5, 1, 1, 1);
	drawSquare(1.5, 1.5, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	glPushMatrix();
	glTranslatef(0, 4.5, -5.7);
	drawSquareLine(1.5, 1.5, 1, 1, 1);
	drawSquare(1.5, 1.5, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5, 1.5, 1);
	glPushMatrix();
	glTranslatef(0, 3, -6);
	drawSquareLine(1.5, 1.5, 1, 1, 1);
	drawSquare(1.5, 1.5, 0, 0, 0);
	glPopMatrix();

	glPopMatrix();
}

void drawHead() {

	glRotatef(headRotationSpeed, 0, 1, 0);  // Rotate head
	glPushMatrix();
	//glLoadIdentity();
	glTranslatef(4, 23, 5);
	drawMainHead();
	headFirstComponent();
	glPopMatrix();
}

#pragma endregion

#pragma region Display Arm
void drawHand() {

	glPushMatrix();

	drawHandFirstPart();

	glPushMatrix();
	glTranslatef(0, -0.55, 0);
	drawHandSecondPart();
	
	glPushMatrix();
	glTranslatef(-0.2, -0.15, 0.15);
	drawHandThirdPart();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void drawHandFirstPart() {

	glPushMatrix();
	glRotatef(90, 1, 0, 0);

	glColor3f(1, 0, 0);
	drawSphere(0.08, 30, 30);

	glColor3f(1, 0, 0);
	drawCylinderLine(0.05, 0.05, 0.4, 30, 30);

	glPopMatrix();
}

void drawHandSecondPart() {

	glPushMatrix();

	glColor3f(1, 0, 0);
	drawPalm();

	glPopMatrix();
}

void drawHandThirdPart() {
	
	glPushMatrix();
	drawFinger();

	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	drawFinger();

	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	drawFinger();
	
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	drawFinger();

	glPushMatrix();
	glTranslatef(0.1, 0, -0.3);
	glRotatef(180, 0, -1, 0);
	drawFinger();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	
}

void drawPalm() {
	GLuint textures[2];


	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	// front
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-0.1, 0.15, 0.1);
	glTexCoord2f(0.8, 1);
	glVertex3f(0.1, 0.15, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.15, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.15, 0.2);

	glEnd();

	// back
	glBegin(GL_POLYGON);

	glTexCoord2f(0.2, 1);
	glVertex3f(-0.1, 0.15, -0.1);
	glTexCoord2f(0.8, 1);
	glVertex3f(0.1, 0.15, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.15, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.15, -0.2);

	glEnd();

	// left side
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.15, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -0.15, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.15, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, -0.1);

	glEnd();

	// right side
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(0.1, 0.15, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.15, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.15, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, -0.1);

	glEnd();

	// down side 
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(0.2, -0.15, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.15, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.15, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.15, 0.2);

	glEnd();

	// up side
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(0.1, 0.15, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.15, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.15, -0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, 0.1);

	glEnd();

	glDeleteTextures(1, &textures[0]);

}

void drawFinger() {
	
	glPushMatrix();
	glColor3f(0, 0, 1);
	drawFingerPart();

	glPushMatrix();
	glColor3f(0, 1, 0);

	glTranslatef(0, -0.15, 0);
	glRotatef(fingerRotation, 1, 0, 0);
	
	drawFingerPart();

	glPushMatrix();
	glColor3f(1, 0, 0);

	glTranslatef(0, -0.15, 0);
	glRotatef(fingerRotation, 1, 0, 0);
	
	drawFingerPart();
	
	glPushMatrix();
	glTranslatef(0.025, -0.15, 0.025);
	drawSphere(0.02, 30, 30);

	if (shooting) {
		shootingAnimation();
	}
	else
		armsDown();
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawFingerPart() {
	GLuint textures[2];

	if (textureOn)
		textures[0] = loadTexture("Body.bmp");

	// top side
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0.05);

	glEnd();

	// bottom side
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(0, -0.15, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.15, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.15, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.15, 0.05);

	glEnd();

	// left side
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.15, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.15, 0);

	glEnd();

	// front side
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.15, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.15, 0.05);

	glEnd();

	// right side
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.15, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.15, 0.05);

	glEnd();

	// back side
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.15, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.15, 0);

	glEnd();

	glDeleteTextures(1, &textures[0]);

	glColor3f(0, 0, 0);
	// top LINE side
	glBegin(GL_LINE_LOOP);

	glVertex3f(0, 0, 0);
	glVertex3f(0.05, 0, 0);
	glVertex3f(0.05, 0, 0.05);
	glVertex3f(0, 0, 0.05);

	glEnd();

	// bottom LINE side
	glBegin(GL_LINE_LOOP);

	glVertex3f(0, -0.15, 0);
	glVertex3f(0.05, -0.15, 0);
	glVertex3f(0.05, -0.15, 0.05);
	glVertex3f(0, -0.15, 0.05);

	glEnd();

	// left LINE side
	glBegin(GL_LINE_LOOP);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.05);
	glVertex3f(0, -0.15, 0.05);
	glVertex3f(0, -0.15, 0);

	glEnd();

	// front LINE side
	glBegin(GL_LINE_LOOP);

	glVertex3f(0, 0, 0.05);
	glVertex3f(0.05, 0, 0.05);
	glVertex3f(0.05, -0.15, 0.05);
	glVertex3f(0, -0.15, 0.05);

	glEnd();

	// right LINE side
	glBegin(GL_LINE_LOOP);

	glVertex3f(0.05, 0, 0.05);
	glVertex3f(0.05, 0, 0);
	glVertex3f(0.05, -0.15, 0);
	glVertex3f(0.05, -0.15, 0.05);

	glEnd();

	// back LINE side
	glBegin(GL_LINE_LOOP);

	glVertex3f(0.05, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -0.15, 0);
	glVertex3f(0.05, -0.15, 0);

	glEnd();
}

#pragma endregion

#pragma region Animation
void walkingAnimation() {
	if (leftLeg) {
		if (leftLegRotationSpeed < 9) {

			leftLegRotationSpeed += walkingSpeed;

			if (leftSubLegRotationSpeed > -2)
				leftSubLegRotationSpeed -= walkingSpeed - 0.3;
		}
		else
			leftLeg = false;
	}
	else {
		if (leftLegRotationSpeed > -9) {

			leftLegRotationSpeed -= walkingSpeed;

			if (leftSubLegRotationSpeed < 2)
				leftSubLegRotationSpeed += walkingSpeed - 0.3;
		}
		else
			leftLeg = true;
	}

	if (rightLeg) {
		if (rightLegRotationSpeed > -9) {

			rightLegRotationSpeed -= walkingSpeed;

			if (rightSubLegRotationSpeed < 2)
				rightSubLegRotationSpeed += walkingSpeed - 0.3;
		}
		else
			rightLeg = false;
	}
	else {
		if (rightLegRotationSpeed < 9) {

			rightLegRotationSpeed += walkingSpeed;

			if (rightSubLegRotationSpeed > -2)
				rightSubLegRotationSpeed -= walkingSpeed - 0.3;
		}
		else
			rightLeg = true;
	}

	if (leftArm) {

		if (armLeftRotation > -15) {
			armLeftRotation -= walkingSpeed;
		}
		else
			leftArm = false;
	}
	else {
		if (armLeftRotation < 15) {
			armLeftRotation += walkingSpeed;
		}
		else
			leftArm = true;
	}

	if (rightArm) {

		if (armRightRotation < 15) {
			armRightRotation += walkingSpeed;
		}
		else
			rightArm = false;
	}
	else {
		if (armRightRotation > -15) {
			armRightRotation -= walkingSpeed;
		}
		else
			rightArm = true;
	}

	fingerAnimation();

}

void fingerAnimation() {
	if (moveFinger) {
		if (fingerRotation < 15) {

			fingerRotation += walkingSpeed;
		}
		else
			moveFinger = false;
	}
	else {
		if (fingerRotation > 0) {

			fingerRotation -= walkingSpeed;
		}
		else
			moveFinger = true;
	}
}

void shootingAnimation() {

	if (armLeftRotation > -90.0 || armRightRotation > -90.0) {

		if (armLeftRotation > -90.0)
			armLeftRotation -= 0.5;

		if (armRightRotation > -90.0)
			armRightRotation -= 0.5;
	}
	else
		armValidate = true;

	if (fingerRotation != 0) {
		if (fingerRotation > 0)
			fingerRotation -= 0.1;
		else if (fingerRotation < 0)
			fingerRotation += 0.1;
	}

	if (armValidate)
		spawnBullet();
	else {
		bulletMovement = 0;
	}

}

void spawnBullet() {

	if (bulletMovement < 3) {
		glTranslatef(0, -bulletMovement, 0);
		glColor3f(0, 0, 1);
		drawSphere(0.02, 30, 30);

		bulletMovement += 0.1;
	}
	else {
		bulletMovement = 0;
	}
}

void armsDown() {
	if (armLeftRotation <= 0 && armRightRotation <= 0) {
		armLeftRotation += 0.1;
		armRightRotation += 0.1;
	}
}

#pragma endregion

// All drawing code here
void drawing() {

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);

	if (showStar)
		drawBackground();

	if (walking)
		walkingAnimation();

	if (moveFingerAnimate)
		fingerAnimation();

	drawLeg();
	drawBody();

	// Draw Hand
	// Left hand
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-19, 18, 5);
	glScalef(30, 25, 35);
	glPushMatrix();
	glRotatef(armLeftRotation, 1, 0, 0);
	drawHand();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// Right hand
	glPushMatrix();
	glPushMatrix();
	glTranslatef(27, 18, 5);
	glScalef(30, 25, 35);
	glPushMatrix();
	glRotatef(armRightRotation, 1, 0, 0);
	drawHand();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	drawHead();

}

void display()
{
	//glClearColor(1.0, 1.0, 1.0, 0.0);

	glClearColor(r, g, b, 0.0);

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projection();

	lighting(posX, posY, posZ);

	glTranslatef(0, 0, Tz);

	if (!isOrtho) {
		glPushMatrix();
		//glScalef(1, 1, 0.01);
		//glTranslatef(0, 0, 0);
		drawing();
		glPopMatrix();
	}
	else {
		glTranslatef(0, 0, -5);
		drawing();
	}

}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));



	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
