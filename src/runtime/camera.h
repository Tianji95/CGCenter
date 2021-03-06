#ifndef CAMERA_H
#define CAMERA_H
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
namespace Zxen {
	class Camera {
	public:
		Camera()
		{
			UpdateViewMatrix();
			UpdateProjectionMatrix();
		}
		~Camera() = default;

		void MoveLeft(float distant);
		void MoveRight(float distant);
		void MoveForward(float distant);
		void MoveBack(float distant);
		void AddFov(float offset);
		void RotateCamera(float yaw, float pitch);
		void SetCameraSpeed(float spd);
		glm::vec3 GetPosition() const;
		glm::vec3 GetLookAt() const;
		glm::mat4x4 GetProjectionMatrix() const;
		glm::mat4x4 GetViewMatirx() const;
	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
	private:
		static constexpr float MAX_FOV = 120.0f;
		static constexpr float NEAR_PLANE = 0.1f;
		static constexpr float FAR_PLANE = 10000.0f;
		static constexpr float ASPECT_RATIO = 4.0f / 3.0f;

		glm::vec3 eye{ 3070,1300,5036 };
		glm::vec3 lookat{ 3070,1300,5035 };
		glm::vec3 up{ 0,1,0 };
		glm::mat4x4 viewMatrix;
		glm::mat4x4 projectionMatrix;
		float speed = 50.0f;
		float fov = 90;
		float yaw = -90;
		float pitch = 0;
	};

	using CameraPtr = std::shared_ptr<Camera>;
}
#endif // !CAMERA_H
