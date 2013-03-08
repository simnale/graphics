#include "camera.hpp"
#include <iostream>

Camera::Camera():
		orientation(1.0f)
{

}

glm::vec3 Camera::getLook()
{
		glm::vec4 look = glm::inverse(orientation) * glm::vec4(0.0f,0.0f,-1.0f,1.0f);
		return glm::vec3(look);
}

glm::vec3 Camera::getRight()
{
		glm::vec4 right = glm::inverse(orientation) * glm::vec4(1.0f,0.0f,0.0f,1.0f);
		return glm::vec3(right);
}

glm::vec3 Camera::getUp()
{
		glm::vec4 up = glm::inverse(orientation) * glm::vec4(0.0f,1.0f,0.0f,1.0f);
		return glm::vec3(up);
}

void Camera::moveRight(float a)
{
		position += getRight() * a;
}

void Camera::moveForward(float a)
{
		position += getLook() * a;
}

void Camera::moveUp(float a)
{
		position += getUp() * a;
}

void Camera::rotateUp(float a)
{
		orientation = glm::rotate(orientation, a, getUp());
		
}

void Camera::rotateRight(float a)
{
		orientation = glm::rotate(orientation, a, getRight());
}		

void Camera::rotateForward(float a)
{
		orientation = glm::rotate(orientation, a, getLook());
}

void Camera::rotate(float a, glm::vec3 axis)
{
		orientation = glm::rotate(orientation, a, axis);
}
