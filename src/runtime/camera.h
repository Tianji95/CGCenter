#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
class Camera {
public:
	Camera() = default;
	~Camera() = default;

	void MoveLeft(float distant);
	void MoveRight(float distant);
	void MoveForward(float distant);
	void MoveBack(float distant);
	glm::mat4x4 GetViewMatirx() const;
private:
	void UpdateViewMatrix();
	glm::vec3 eye{ 0,0,0 };
	glm::vec3 lookat{ 0,0,-1 };
	glm::vec3 up{0,1,0};
	glm::mat4x4 viewMatrix;
};

#endif // !CAMERA_H
