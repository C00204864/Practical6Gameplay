#include "Game.h"

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube"), primitives(1), 
FTL(-1.0f, 1.0f, -5.0f),
FTR(1.0f, 1.0f, -5.0f),
FBL(-1.0f, -1.0f, -5.0f),
FBR(1.0f, -1.0f, -5.0f),
BTL(-1.0f, 1.0f, -7.0f),
BTR(1.0f, 1.0f, -7.0f),
BBL(-1.0f, -1.0f, -7.0f),
BBR(1.0f, -1.0f, -7.0f)
{
	index = glGenLists(primitives);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Front Face
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(FTR.GetX(), FTR.GetY(), FTR.GetZ());
			glVertex3f(FTL.GetX(), FTL.GetY(), FTL.GetZ());
			glVertex3f(FBL.GetX(), FBL.GetY(), FBL.GetZ());
			glVertex3f(FBR.GetX(), FBR.GetY(), FBR.GetZ());
		//Back Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(BTR.GetX(), BTR.GetY(), BTR.GetZ());
		glVertex3f(BTL.GetX(), BTL.GetY(), BTL.GetZ());
		glVertex3f(BBL.GetX(), BBL.GetY(), BBL.GetZ());
		glVertex3f(BBR.GetX(), BBR.GetY(), BBR.GetZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(FTR.GetX(), FTR.GetY(), FTR.GetZ());
		glVertex3f(FTL.GetX(), FTL.GetY(), FTL.GetZ());
		glVertex3f(BTL.GetX(), BTL.GetY(), BTL.GetZ());
		glVertex3f(BTR.GetX(), BTR.GetY(), BTR.GetZ());

		//Bottom Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(FBL.GetX(), FBL.GetY(), FBL.GetZ());
		glVertex3f(FBR.GetX(), FBR.GetY(), FBR.GetZ());
		glVertex3f(BBR.GetX(), BBR.GetY(), BBR.GetZ());
		glVertex3f(BBL.GetX(), BBL.GetY(), BBL.GetZ());

		//Left Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(FTL.GetX(), FTL.GetY(), FTL.GetZ());
		glVertex3f(FBL.GetX(), FBL.GetY(), FBL.GetZ());
		glVertex3f(BBL.GetX(), BBL.GetY(), BBL.GetZ());
		glVertex3f(BTL.GetX(), BTL.GetY(), BTL.GetZ());

		//Right Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(FTR.GetX(), FTR.GetY(), FTR.GetZ());
		glVertex3f(FBR.GetX(), FBR.GetY(), FBR.GetZ());
		glVertex3f(BBR.GetX(), BBR.GetY(), BBR.GetZ());
		glVertex3f(BTR.GetX(), BTR.GetY(), BTR.GetZ());
		

		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	/*if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
			current++;
			if (current > primitives)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		FTR = m.RotateAboutZ(FTR, 1.f);
		FTL = m.RotateAboutZ(FTL, 1.f);
		FBR = m.RotateAboutZ(FBR, 1.f);
		FBL = m.RotateAboutZ(FBL, 1.f);
		BTR = m.RotateAboutZ(BTR, 1.f);
		BTL = m.RotateAboutZ(BTL, 1.f);
		BBR = m.RotateAboutZ(BBR, 1.f);
		BBL = m.RotateAboutZ(BBL, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		ToOrigin();
		FTR = m.RotateAboutY(FTR, 1.f);
		FTL = m.RotateAboutY(FTL, 1.f);
		FBR = m.RotateAboutY(FBR, 1.f);
		FBL = m.RotateAboutY(FBL, 1.f);
		BTR = m.RotateAboutY(BTR, 1.f);
		BTL = m.RotateAboutY(BTL, 1.f);
		BBR = m.RotateAboutY(BBR, 1.f);
		BBL = m.RotateAboutY(BBL, 1.f);
		ReturnToPos();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		ToOrigin();
		FTR = FTR.Scale(1.001f);
		FTL = FTL.Scale(1.001f);
		FBR = FBR.Scale(1.001f);
		FBL = FBL.Scale(1.001f);
		BTR = BTR.Scale(1.001f);
		BTL = BTL.Scale(1.001f);
		BBR = BBR.Scale(1.001f);
		BBL = BBL.Scale(1.001f);
		ReturnToPos();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		ToOrigin();
		FTR = FTR.Scale(1 / 1.001f);
		FTL = FTL.Scale(1 / 1.001f);
		FBR = FBR.Scale(1 / 1.001f);
		FBL = FBL.Scale(1 / 1.001f);
		BTR = BTR.Scale(1 / 1.001f);
		BTL = BTL.Scale(1 / 1.001f);
		BBR = BBR.Scale(1 / 1.001f);
		BBL = BBL.Scale(1 / 1.001f);
		ReturnToPos();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		m.Translate(0.005, 0.005, FTR);
		m.Translate(0.005, 0.005, FTL);
		m.Translate(0.005, 0.005, BTR);
		m.Translate(0.005, 0.005, BTL);
		m.Translate(0.005, 0.005, FBR);
		m.Translate(0.005, 0.005, FBL);
		m.Translate(0.005, 0.005, BBR);
		m.Translate(0.005, 0.005, BBL);
	}
	
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << current << endl;
	glLoadIdentity();
	glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis
	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(FTR.GetX(), FTR.GetY(), FTR.GetZ());
		glVertex3f(FTL.GetX(), FTL.GetY(), FTL.GetZ());
		glVertex3f(FBL.GetX(), FBL.GetY(), FBL.GetZ());
		glVertex3f(FBR.GetX(), FBR.GetY(), FBR.GetZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(BTR.GetX(), BTR.GetY(), BTR.GetZ());
		glVertex3f(BTL.GetX(), BTL.GetY(), BTL.GetZ());
		glVertex3f(BBL.GetX(), BBL.GetY(), BBL.GetZ());
		glVertex3f(BBR.GetX(), BBR.GetY(), BBR.GetZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(FTR.GetX(), FTR.GetY(), FTR.GetZ());
		glVertex3f(FTL.GetX(), FTL.GetY(), FTL.GetZ());
		glVertex3f(BTL.GetX(), BTL.GetY(), BTL.GetZ());
		glVertex3f(BTR.GetX(), BTR.GetY(), BTR.GetZ());

		//Bottom Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(FBL.GetX(), FBL.GetY(), FBL.GetZ());
		glVertex3f(FBR.GetX(), FBR.GetY(), FBR.GetZ());
		glVertex3f(BBR.GetX(), BBR.GetY(), BBR.GetZ());
		glVertex3f(BBL.GetX(), BBL.GetY(), BBL.GetZ());

		//Left Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(FTL.GetX(), FTL.GetY(), FTL.GetZ());
		glVertex3f(FBL.GetX(), FBL.GetY(), FBL.GetZ());
		glVertex3f(BBL.GetX(), BBL.GetY(), BBL.GetZ());
		glVertex3f(BTL.GetX(), BTL.GetY(), BTL.GetZ());

		//Right Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(FTR.GetX(), FTR.GetY(), FTR.GetZ());
		glVertex3f(FBR.GetX(), FBR.GetY(), FBR.GetZ());
		glVertex3f(BBR.GetX(), BBR.GetY(), BBR.GetZ());
		glVertex3f(BTR.GetX(), BTR.GetY(), BTR.GetZ());


		//Complete the faces of the Cube
	}
	glEnd();

	

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

void Game::ToOrigin()
{
	FTR = MyVector3(FTR.GetX(), FTR.GetY(), FTR.GetZ() + 6);
	FTL = MyVector3(FTL.GetX(), FTL.GetY(), FTL.GetZ() + 6);
	FBR = MyVector3(FBR.GetX(), FBR.GetY(), FBR.GetZ() + 6);
	FBL = MyVector3(FBL.GetX(), FBL.GetY(), FBL.GetZ() + 6);
	BTR = MyVector3(BTR.GetX(), BTR.GetY(), BTR.GetZ() + 6);
	BTL = MyVector3(BTL.GetX(), BTL.GetY(), BTL.GetZ() + 6);
	BBR = MyVector3(BBR.GetX(), BBR.GetY(), BBR.GetZ() + 6);
	BBL = MyVector3(BBL.GetX(), BBL.GetY(), BBL.GetZ() + 6);
}

void Game::ReturnToPos()
{
	FTR = MyVector3(FTR.GetX(), FTR.GetY(), FTR.GetZ() - 6);
	FTL = MyVector3(FTL.GetX(), FTL.GetY(), FTL.GetZ() - 6);
	FBR = MyVector3(FBR.GetX(), FBR.GetY(), FBR.GetZ() - 6);
	FBL = MyVector3(FBL.GetX(), FBL.GetY(), FBL.GetZ() - 6);
	BTR = MyVector3(BTR.GetX(), BTR.GetY(), BTR.GetZ() - 6);
	BTL = MyVector3(BTL.GetX(), BTL.GetY(), BTL.GetZ() - 6);
	BBR = MyVector3(BBR.GetX(), BBR.GetY(), BBR.GetZ() - 6);
	BBL = MyVector3(BBL.GetX(), BBL.GetY(), BBL.GetZ() - 6);
}

