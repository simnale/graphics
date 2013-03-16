#include <iostream>
#include <cmath>
#include <cstdlib>
#include "window.hpp"
#include "camera.hpp"

Camera player;

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
		window.setMouseCursorVisible(false);
	
		int sizeX = 1920;
		int sizeY = 1200;
		int mouseX, mouseY;

		// init states, load resources
		resize(1920, 1200);
		sf::Mouse::setPosition(sf::Vector2i(sizeX/2, sizeY/2), window);

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
			
				// apply input

				if (wKeyDown) player.position += player.getLook();
				if (sKeyDown) player.position -= player.getLook();
				if (aKeyDown) player.position -= player.getRight();
				if (dKeyDown) player.position += player.getRight();
			
				glm::mat4 View = player.orientation;
				View = glm::translate(View, -player.position);
				glMultMatrixf(glm::value_ptr(View));

				// clear buffers
			
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// render scene
				
				glMatrixMode(GL_MODELVIEW);
				DrawGround();

				glShadeModel(GL_SMOOTH);
				glEnable(GL_LIGHTING);
				glm::vec4 ambientLight(1.0f,1.0f,1.0f,1.0f);
				glEnable(GL_COLOR_MATERIAL);
				glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

				glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambientLight));
				
				glBegin(GL_POLYGON);
				glColor3ub(255,0,0);
				glVertex3f(-10.0,-10.0,0);
				glColor3ub(0,255,0);
				glVertex3f(10.0,-10.0,0.0);
				glColor3ub(0,0,255);
				glVertex3f(0.0,10.0,0.0);
				glEnd();
				
				glLoadIdentity();

				// move mouse 

				float delta;
				delta = mouseX - sizeX/2;
				player.rotate(delta * 0.2f, glm::vec3(0.0f,1.0f,0.0f));

				delta = mouseY - sizeY/2;
				player.rotateRight(delta * 0.2f);
				
				sf::Mouse::setPosition(sf::Vector2i(sizeX/2, sizeY/2), window);

				// swap buffers
				window.display();
		}
}
