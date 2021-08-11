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
	eye += direction * distant;
	lookat += direction * distant;
	std::cout << " eye.x:" << eye.x << " eye.y " << eye.y << " eye.z " << eye.z << std::endl;
	UpdateViewMatrix();
}
void Camera::MoveForward(float distant)
{
	glm::vec3 direction = glm::normalize(lookat - eye);
	eye += direction * distant;
	lookat += direction * distant;
	std::cout << " eye.x:" << eye.x << " eye.y " << eye.y << " eye.z " << eye.z << std::endl;
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
}

void Camera::RotateCamera(float deltayaw, float deltapitch)
{
	pitch += deltapitch;
	yaw += deltayaw;
	pitch = pitch > 89.0f ? 89.0f : pitch;
	pitch = pitch < -89.0f ? -89.0f : pitch;

	//根据俯仰和偏航角度来算出此向量，也就是速度在三个维度的数值
	lookat.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	lookat.y = sin(glm::radians(pitch));
	lookat.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)) - 1;

	glm::vec3 right;
	right.x = -cos(yaw);
	right.y = 0.0;
	right.z = sin(yaw);

	up = glm::cross(lookat, right);

	UpdateViewMatrix();
}

glm::mat4x4 Camera::GetViewMatirx() const
{
	return viewMatrix;
}

