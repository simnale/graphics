#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "window.hpp"

class Camera
{
public:
		glm::vec3 position;
		glm::vec3 direction;
		glm::mat4 posMat;
		glm::mat4 rotMat;
		glm::mat4 viewMat;

		Camera();

		void moveLeft(float a);
		void moveForward(float a);
		void rotate(float a, glm::vec3 axis);
};

#endif
