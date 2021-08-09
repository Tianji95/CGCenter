#include "camera.h"
#include<iostream>

void Camera::MoveLeft(float distant)
{
	MoveRight(-distant);
}
void Camera::MoveRight(float distant)
{
	glm::vec3 forwardDirection = glm::normalize(lookat - eye);
	glm::vec3 direction = glm::cross(forwardDirection, up);
	eye += direction * distant;
	lookat += direction * distant;
	std::cout << " eye.x:" << eye.x << " eye.y " << eye.y << " eye.z " << eye.z << std::endl;
}
void Camera::MoveForward(float distant)
{
	glm::vec3 direction = glm::normalize(lookat - eye);
	eye += direction * distant;
	lookat += direction * distant;
	std::cout << " eye.x:" << eye.x << " eye.y " << eye.y << " eye.z " << eye.z << std::endl;
}
void Camera::MoveBack(float distant)
{
	MoveForward(-distant);
}

glm::mat4x4 Camera::GetViewMatirx() const
{
	return viewMatrix;
}

