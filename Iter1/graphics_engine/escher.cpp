#include  <random> //TEMPORARY, FOR GENERATING RANDOM OBJECTS

#include "escher.h"


Escher::Escher(
	std::shared_ptr<Shader> _shader,
	std::shared_ptr<Shapes> _shapes
)
{
	shapes = _shapes;
	shader = _shader;

	for (size_t i = 0; i < 20; ++i)
	{
		float x = 20 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		float y = 20 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		float z = 20 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		objects.push_back(std::make_pair<int, glm::vec3>(i, glm::vec3(x, y, z)));
	}
}


void Escher::escherize(unsigned int VAO)
{
	glBindVertexArray(VAO);
	for (size_t i = 0; i < objects.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, objects[i].second);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader->setMat4("model", model);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //for square
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}