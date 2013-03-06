#include "camera.hpp"
#include "glm/gtc/swizzle.hpp"

Camera::Camera()
{
		//viewMat = glm::mat4(1.0f);
}

void Camera::moveLeft(float a)
{
		glm::vec4 direction(a, 0.0f, 0.0f, 0.0f);
		direction = direction * rotMat;
		posMat = glm::translate(posMat, glm::vec3(direction));
}

void Camera::moveForward(float a)
{
		glm::vec4 direction(0.0f, 0.0f, a, 0.0f);
		direction = direction * rotMat;
		posMat = glm::translate(posMat, glm::vec3(direction));
}

void Camera::rotate(float a, glm::vec3 axis)
{
		rotMat = glm::rotate(rotMat, a, axis);
}
