#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Object.h"
#include "ICamera.h"

class FPSCamera : public ICamera
{
public: 
	FPSCamera() { Initialize(glm::vec3(0.0f, 0.0f, 0.0f)); };
	FPSCamera(glm::vec3 position) : mPosition(position) { Initialize(position); };
    glm::mat4 GetView();

	void SetHorizontalAngle(float angle) { mHorizontalAngle = angle; };
	void SetVerticalAngle(float angle) { mVerticalAngle = angle; };
	void SetPosition(glm::vec3 position) { mPosition = position; };

	float GetHorizontalAngle() { return mHorizontalAngle; };
	float GetVerticalAngle() { return mVerticalAngle; };
	glm::vec3 GetPosition() { return mPosition; };
	glm::vec3 GetDirection() { return mDirection; };

	void MoveForward(float amount);
	void MoveBackward(float amount);
	void MoveLeft(float amount);
	void MoveRight(float amount);

	void AddHorizontalAngle(float angle) { mHorizontalAngle += angle; };
	void AddVerticalAngle(float angle) { mVerticalAngle += angle; };

	void Update();

private:
	void Initialize(glm::vec3 position);

    float mHorizontalAngle;
    float mVerticalAngle;
    
    glm::vec3 mPosition;
    glm::vec3 mDirection;
    glm::vec3 mUp;
    glm::vec3 mRight;
};
