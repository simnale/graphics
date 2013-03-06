#include <iostream>
#include <cmath>
#include <cstdlib>
#include "window.h"
#include "camera.hpp"

// Lighting values
GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat camPos[3] = {0.0, 0.0, 0.0};

Camera player;

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
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		aspectRatio = (GLfloat)w / (GLfloat)h;

		glm::mat4 Projection = glm::perspective(45.0f, aspectRatio, 1.0f, 1000.0f);
		//glm::mat4 View = glm::translate(glm::mat4(1.0f), player.position);

		//glm::mat4 PV = Projection * View * player.rotMat;
		glLoadMatrixf(glm::value_ptr(Projection));
}


void Window::run()
{ 
		sf::Window window(sf::VideoMode(1920, 1200), "Graphics", sf::Style::Default,
						  sf::ContextSettings(32, 0, 0, 3, 2));
		window.setVerticalSyncEnabled(true);
		sf::ContextSettings settings = window.getSettings();

		// init states, load resources
		resize(1920, 1200);
		SunSetup();


		// main loop
		bool running = true;
		bool leftKeyDown, rightKeyDown, upKeyDown, downKeyDown, kKeyDown, jKeyDown; 

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
						// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						// {
						// 		end.position.x += 5.0;
						// 		end.position.z += 5.0;
						// }
						// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
						// {
						// 		end.position.x += 5.0;
						// }
						// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
						// {
						// 		end.position.x -= 5.0;
						// }
						// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						// {
						// 		end.position.z += 5.0;
						// }
						// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
						// {
						// 		end.position.z -= 5.0;
						// }
						// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
						// {
						// 		//rot_angle += 0.1;
						// 		player.rotMat = glm::rotate(player.rotMat, 3.0f, glm::vec3(0.0f, 1.0f, 0.0f));
						// }
						// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
						// {
						// 		//rot_angle -= 0.1;
						// 		player.rotMat = glm::rotate(player.rotMat, -3.0f, glm::vec3(0.0f, 1.0f, 0.0f));
						// }
						leftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
						rightKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
						upKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
						downKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
						jKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::J);
						kKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::K);
				}
				// apply input
				if (leftKeyDown) player.moveLeft(1.0f);
				if (rightKeyDown) player.moveLeft(-1.0f);
				if (upKeyDown) player.moveForward(1.0f);
				if (downKeyDown) player.moveForward(-1.0f);
				if (jKeyDown) player.rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); //player.rotMat = glm::rotate(player.rotMat, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				if (kKeyDown) player.rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

				// clear buffers
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// if (end.position != glm::vec3(0.0f))
				// {
				// 		//std::cout << "test" << std::endl;
				// 		if (end.position.x > 0.0f)
				// 		{
				// 				player.position.x += 1.0f;
				// 				end.position.x -= 1.0f;
				// 		} else if (end.position.x < 0.0f)
				// 		{
				// 				player.position.x -= 1.0f;
				// 				end.position.x += 1.0f;
				// 		} else if (end.position.y > 0.0f)
				// 		{
				// 				player.position.y += 1.0f;
				// 				end.position.y -= 1.0f;
				// 		} else if (end.position.y < 0.0f)
				// 		{
				// 				player.position.x -= 1.0f;
				// 				end.position.y += 1.0f;
				// 		} else if (end.position.z > 0.0f)
				// 		{
				// 				player.position.z += 1.0f;
				// 				end.position.z -= 1.0f;
				// 		} else if (end.position.z < 0.0f)
				// 		{
				// 				player.position.z -= 1.0f;
				// 				end.position.z += 1.0f;
				// 		}
				// }

				glm::mat4 View = glm::translate(glm::mat4(1.0f), player.position);
				glm::mat4 final = player.rotMat * player.posMat;
				glMultMatrixf(glm::value_ptr(final));
				
				RenderSun();
				DrawGround();

				glLoadIdentity();

				// swap buffers
				window.display();
		}
}
