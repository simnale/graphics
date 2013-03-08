#include <iostream>
#include <cmath>
#include <cstdlib>
#include "window.hpp"
#include "camera.hpp"

// Lighting values
GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat camPos[3] = {0.0, 0.0, 0.0};

Camera player;

int sizeX;
int sizeY;
int mouseX;
int mouseY;

glm::vec3 view(0.0f, 0.0f, 1.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);
glm::vec3 pos(0.0f, 0.0f, 0.0f);
glm::mat4 xform(1.0f);


void RenderSun()
{
		static float fMoonRot = 0.0;
		static float fEarthRot = 0.0;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glTranslatef(0.0, 0.0, -300.0);
		
		glColor3ub(255, 255, 0);
		glDisable(GL_LIGHTING);
		glutSolidSphere(15.0, 20, 20);
		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		glRotatef(fEarthRot, 0.0, 1.0, 0.0);

		glColor3ub(0, 0, 255);
		glTranslatef(105.0, 0.0, 0.0);
		glutSolidSphere(15.0, 20, 20);

		glColor3ub(200, 200, 200);
		glRotatef(fMoonRot, 0.0, 1.0, 0.0);
		glTranslatef(30.0, 0.0, 0.0);
		fMoonRot += 15.0/3.0;
		if (fMoonRot > 360.0)
				fMoonRot = 0.0;

		glutSolidSphere(6.0, 20, 20);
 		glPopMatrix();

		fEarthRot += 5.0/3.0;
		if (fEarthRot > 360.0)
				fEarthRot = 0.0;

}

void SunSetup()
{
		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);

		glEnable(GL_LIGHTING);
		// Setup and enable light 0
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
		glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
		glEnable(GL_LIGHT0);

		// Enable color tracking
		glEnable(GL_COLOR_MATERIAL);
	
		// Set Material properties to follow glColor values
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		// Black blue background
		glClearColor(0.0, 0.0, 0.0, 1.0);
}

Window::Window()
{
}

Window::~Window()
{
}

void DrawGround()
{
		GLfloat extent = 600.0;
		GLfloat stepSize = 20.0;
		GLfloat groundLevel = -50.0;

		glColor3ub(255, 255, 255);

		glBegin(GL_LINES);
		for (int loop = -extent; loop < extent; loop += stepSize)
		{
				glVertex3f(loop, groundLevel, extent);
				glVertex3f(loop, groundLevel, -extent);
				
				glVertex3f(-extent, groundLevel, loop);
				glVertex3f(extent, groundLevel, loop);
		}
		glEnd();
}


void Window::resize(GLsizei w, GLsizei h)
{
		GLfloat aspectRatio;
		if (h == 0) h = 1;
		glViewport(0, 0, w, h);

		sizeX = w;
		sizeY = h;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		aspectRatio = (GLfloat)w / (GLfloat)h;

		glm::mat4 Projection = glm::perspective(45.0f, aspectRatio, 1.0f, 10000.0f);
	
		glLoadMatrixf(glm::value_ptr(Projection));
}

void drawAxes()
{
		glPushMatrix();
		glBegin(GL_LINES);
		
		glColor3ub(255,0,0);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		
		glColor3ub(0, 255, 0);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		
		glColor3ub(0,0,255);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		
		glEnd();
		glPopMatrix();
}

void Window::run()
{ 
		sf::Window window(sf::VideoMode(1920, 1200), "Graphics", sf::Style::Fullscreen,
						  sf::ContextSettings(32, 0, 0, 3, 2));
		window.setVerticalSyncEnabled(true);
		sf::ContextSettings settings = window.getSettings();

		// init states, load resources
		resize(1920, 1200);

		SunSetup();
		glm::mat4 magic(1.0f);

		// main loop
		bool running = true;
		bool leftKeyDown, rightKeyDown, upKeyDown, downKeyDown, kKeyDown, jKeyDown, wKeyDown,
				aKeyDown, sKeyDown, dKeyDown; 

		while (running)
		{
				sf::Event event;
				while (window.pollEvent(event))
				{
						if (event.type == sf::Event::Closed)
						{
								running = false;
						}
						else if (event.type == sf::Event::Resized)
						{
								// window size changed
								resize(event.size.width, event.size.height);
						}
						else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
								running = false;
						}
					
						leftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
						rightKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
						upKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
						downKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
						jKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::J);
						kKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::K);
						wKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
						aKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
						sKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
						dKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
				}
				
				mouseX = sf::Mouse::getPosition(window).x;
				mouseY = sf::Mouse::getPosition(window).y;

				// legal input
				if (mouseX <= 0) mouseX = 1;
				if (mouseY <= 0) mouseY = 1;
													
				float delta;	
				if (mouseX < sizeX/2)
				{
						delta = sizeX/2 - mouseX;
						delta = delta / sizeX * 1.5f;
						player.rotateUp(-delta);
						
				}
				else if (mouseX > sizeX/2)
				{
						delta = mouseX - sizeX/2;
						delta = delta / sizeX * 1.5f;
						player.rotateUp(delta);
				}
					   
				if (mouseY < sizeY/2)
				{
						delta = sizeY/2 - mouseY;
						delta = delta / sizeY * 1.5f;
						player.rotateRight(-delta);
				}
				else if (mouseY > sizeY/2)
				{
						delta = mouseY - sizeY/2;
						delta = delta / sizeY * 1.5f;
						player.rotateRight(delta);
				}

				// apply input
				if (wKeyDown) player.position += player.getLook();
				if (sKeyDown) player.position -= player.getLook();
				if (aKeyDown) player.position -= player.getRight();
				if (dKeyDown) player.position += player.getRight();
				
				if (jKeyDown) player.rotateUp(2.0f);
				if (kKeyDown) player.rotateUp(-2.0f);

				if (leftKeyDown) player.rotateForward(2.0f);
				if (rightKeyDown) player.rotateForward(-2.0f);


				glm::mat4 View = player.orientation;
				View = glm::translate(View, -player.position);
				glMultMatrixf(glm::value_ptr(View));

				// clear buffers
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// render scene
				RenderSun();
				DrawGround();

			
			
				glLoadIdentity();

				// swap buffers
				window.display();
		}
}
