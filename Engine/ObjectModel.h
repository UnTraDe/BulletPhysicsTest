#pragma once
#include "Object.h"
#include "Model.h"

class ObjectModel :
	public Object
{
public:
	ObjectModel(const glm::vec3 startPos, Model* model, btCollisionShape* shape);
	~ObjectModel();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view, Shader* shader);

private:
	Model* model;
	btCollisionShape* mShape;
};

