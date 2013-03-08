#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "window.hpp"

class Camera
{
public:
		glm::vec3 position;
		glm::mat4 orientation;

		Camera();

		glm::vec3 getUp();
		glm::vec3 getLook();
		glm::vec3 getRight();

		void moveRight(float a);
		void moveForward(float a);
		void moveUp(float a);
		void rotateUp(float a);
		void rotateRight(float a);
		void rotateForward(float a);
		void rotate(float a, glm::vec3 axis);
};

#endif
