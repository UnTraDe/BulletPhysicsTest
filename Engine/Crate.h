#include "Object.h"

class Crate : Object
{
public:
	Crate(Shader* shader);
	~Crate();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view);

private:
	static const glm::vec3 CrateVertices[];
};