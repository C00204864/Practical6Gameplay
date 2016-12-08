#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include "Matrix3.h"

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	void ToOrigin();
	void ReturnToPos();
	const int primitives;

	GLuint index;
	Clock clock;
	Time elapsed;
	MyVector3 FTL;
	MyVector3 FTR;
	MyVector3 FBL;
	MyVector3 FBR;
	MyVector3 BTL;
	MyVector3 BTR;
	MyVector3 BBL;
	MyVector3 BBR;
	Matrix3 m;

	float rotationAngle = 0.0f;
};