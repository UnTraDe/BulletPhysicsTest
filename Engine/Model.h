#pragma once
#include <vector>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include "CommonData.h"
#include <fstream>

class Model
{
public:
	GLuint mVao;
	GLuint mVbo;
	GLuint count;

	Model()
	{
	}

	~Model()
	{
		/*glDeleteBuffers(1, &mVbo);
		mVbo = 0;

		glDeleteVertexArrays(1, &mVao);
		mVao = 0;*/
	}

	void RenderModel(const glm::mat4 &projection, const glm::mat4 &view) {
		ResourceManager* resources = ResourceManager::GetInstance();
		Shader *shader = resources->GetShader("default");

		shader->Bind();

		GLuint vpLocation = shader->GetUniformLocation("VP");
		GLuint modelLocation = shader->GetUniformLocation("Model");
		GLuint invTranLocation = shader->GetUniformLocation("InversedTransform");
		GLuint colorLocation = shader->GetUniformLocation("normalColor");

		btVector3 v = btVector3(10, 10, 10);
		glm::mat4 model = glm::translate(v.getX(), v.getY(), v.getZ());
		
		glUniformMatrix4fv(vpLocation, 1, GL_FALSE, &(projection * view)[0][0]);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(invTranLocation, 1, GL_FALSE, &(glm::translate(-glm::vec3(v.getX(), v.getY(), v.getZ())))[0][0]);
		glUniform3fv(colorLocation, 1, &(glm::vec3(0,0,0))[0]);

		glBindVertexArray(mVao);

		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	static Model* ReadModelFromObjFile(const char* filePath) {
		Model* model = new Model();
		std::ifstream file(filePath);
		if (!file)
		{
			std::cout << "Couldn't open model file: " << filePath << std::endl;
			return NULL;
		}

		std::string header;
		std::vector<glm::vec3> vertices;
		std::vector<Vertex> realVertices;

		while (file >> header) {
			if (header == "#")
				continue;
			if (header == "v") {
				float x, y, z;
				file >> x;
				file >> y;
				file >> z;
				vertices.push_back(glm::vec3(x, y, z));
			}
			if (header == "f") {
				std::string a, b, c;
				int v1, v2, v3;

				file >> a;
				file >> b;
				file >> c;

				v1 = atoi(a.substr(0, a.find('/')).c_str()) - 1;
				v2 = atoi(b.substr(0, b.find('/')).c_str()) - 1;
				v3 = atoi(c.substr(0, c.find('/')).c_str()) - 1;

				realVertices.push_back(Vertex{ vertices[v1], glm::vec3(0, 1, 0) });
				realVertices.push_back(Vertex{ vertices[v2], glm::vec3(0, 1, 0) });
				realVertices.push_back(Vertex{ vertices[v3], glm::vec3(0, 1, 0) });
				model->count += 3;
			}
		}
		realVertices.push_back(Vertex{ glm::vec3(0, 0, 0), glm::vec3(0, 1, 0) });
		realVertices.push_back(Vertex{ glm::vec3(100, 0, 0), glm::vec3(0, 1, 0) });
		realVertices.push_back(Vertex{ glm::vec3(100, 0, 100), glm::vec3(0, 1, 0) });
		model->count += 3;

		file.close();
		GLuint vbo = 0;
		GLuint vao = 0;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(realVertices), &realVertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*) 12);
		glBindVertexArray(0);

		model->mVao = vao;
		model->mVbo = vbo;
		
		return model;
	}
};

