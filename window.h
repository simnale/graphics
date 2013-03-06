#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glut.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Window
{
public:
		Window();
		~Window();

		void run();
		void resize(GLsizei w, GLsizei h);
		
};

#endif
