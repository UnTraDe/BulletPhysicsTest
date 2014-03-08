#include "FPSCamera.h"

void FPSCamera::Initialize(glm::vec3 position)
{
	this->mPosition = position;
    this->mDirection = glm::vec3(0.0f, 0.0f, 0.0f);
    this->mUp = glm::vec3(0.0f, 1.0f, 0.0f);
	mHorizontalAngle = 0;
    mVerticalAngle = 0;
}

glm::mat4 FPSCamera::GetView()
{
	return glm::lookAt(mPosition, mPosition + mDirection, mUp);
}

void FPSCamera::MoveForward(float amount)
{
	mPosition += mDirection * amount;
}

void FPSCamera::MoveBackward(float amount)
{
	mPosition -= mDirection * amount;
}

void FPSCamera::MoveLeft(float amount)
{
	mPosition += glm::cross(mUp, mDirection) * amount;
}

void FPSCamera::MoveRight(float amount)
{
	mPosition -= glm::cross(mUp, mDirection) * amount;
}

void FPSCamera::Update()
{
	mDirection.x = glm::cos(mVerticalAngle) * glm::sin(mHorizontalAngle);
	mDirection.y = glm::sin(mVerticalAngle);
	mDirection.z = glm::cos(mVerticalAngle) * glm::cos(mHorizontalAngle);
	mRight = glm::vec3(glm::sin(mHorizontalAngle - 3.14f / 2.0f), 0, glm::cos(mHorizontalAngle - 3.14f / 2.0f));
	mUp = glm::cross(mRight, mDirection);
}