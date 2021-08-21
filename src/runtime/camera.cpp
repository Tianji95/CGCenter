#include "camera.h"
#include <iostream>
#include<glm/gtx/transform.hpp>
void Camera::MoveLeft(float distant)
{
	MoveRight(-distant);
}
void Camera::MoveRight(float distant)
{
	glm::vec3 forwardDirection = glm::normalize(lookat - eye);
	glm::vec3 direction = glm::cross(forwardDirection, up);
	eye += direction * distant * speed;
	lookat += direction * distant * speed;
	UpdateViewMatrix();
}
void Camera::MoveForward(float distant)
{
	glm::vec3 direction = glm::normalize(lookat - eye);
	eye += direction * distant * speed;
	lookat += direction * distant * speed;
	UpdateViewMatrix();
}
void Camera::MoveBack(float distant)
{
	MoveForward(-distant);
}

void Camera::AddFov(float offset)
{
	if (fov >= 1.0f && fov <= MAX_FOV) {
	    fov -= offset;
	}

	fov = fov <= 1.0f ? 1.0f : fov;
	fov = fov >= MAX_FOV ? MAX_FOV : fov;
	UpdateProjectionMatrix();
}
void Camera::SetCameraSpeed(float spd)
{
	speed = spd;
}

void Camera::UpdateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fov), ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
}

glm::mat4x4 Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

void Camera::UpdateViewMatrix()
{
	viewMatrix = glm::lookAt(eye, lookat, up);
	std::cout << " eye.x:" << eye.x << " eye.y " << eye.y << " eye.z " << eye.z << std::endl;
	std::cout << " lookat.x:" << lookat.x << " lookat.y " << lookat.y << " lookat.z " << lookat.z << std::endl;
	std::cout << " up.x:" << up.x << " up.y " << up.y << " up.z " << up.z << std::endl;
}

void Camera::RotateCamera(float deltayaw, float deltapitch)
{
	pitch += deltapitch;
	yaw += deltayaw;

	//根据俯仰和偏航角度来算出此向量，也就是速度在三个维度的数值
	glm::vec3 alpha(1.0f, 1.0f, 1.0f);
	lookat.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//if (cos(glm::radians(yaw)) < 0 && cos(glm::radians(pitch)) > 0) {
	//	lookat.x = -lookat.x;
	//}
	lookat.y = sin(glm::radians(pitch));
	lookat.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	lookat = glm::normalize(lookat) + eye;
	while (pitch > 360.0f) {
		pitch -= 360.0f;
	}
	while (pitch < -360.0f) {
		pitch += 360.0f;
	}
	if ((pitch < 90.0 && pitch > -90) || (pitch < -270.0f) || pitch > 270.0f) {
		up = glm::vec3(0, 1, 0);
	}
	else {
		up = glm::vec3(0, -1, 0);
	}
	std::cout << "pitch : " << pitch << std::endl;
	std::cout << "yaw : " << yaw << std::endl;
	UpdateViewMatrix();
}

glm::mat4x4 Camera::GetViewMatirx() const
{
	return viewMatrix;
}

