#include  <random> //TEMPORARY, FOR GENERATING RANDOM OBJECTS

#include "escher.h"


Escher::Escher(
	std::shared_ptr<Shader> _shader,
	std::shared_ptr<Shapes> _shapes
)
{
	shapes = _shapes;
	shader = _shader;
}

void Escher::add_node(std::shared_ptr<EscherNode> _en)
{
	objects.push_back(_en);
}

void Escher::draw(unsigned int VAO)
{
	glBindVertexArray(VAO);
	for (size_t i = 0; i < objects.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, objects[i]->location);
		model = glm::rotate(model, glm::radians(objects[i]->angle), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(objects[i]->scale));
		shader->setMat4("model", model);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //for square
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}