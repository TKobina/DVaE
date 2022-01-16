
#pragma once
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../graphics_engine/graphics_engine.h"
#include "../data_structure/importer.h"
#include "../data_structure/book.h"

class Controller
{
private:
	EntityBuffer ebuffer_add;

	std::unique_ptr<Book> book;
	std::unique_ptr<Importer> importer;
	std::unique_ptr<GraphicsEngine> graphics_engine;
	std::shared_ptr<Escher> escher;

	void populate_escher();
	void escherize_node(std::shared_ptr<Entity> node);
	void export_book(std::string fname); //export_book("output/output_log.txt");
public:
	Controller();
	~Controller() {}
};
/*
-Controller passes buffer to book
-Book populates buffer with pointers to Entities
	-Locks entity
	-Adds entity pointer to buffer
	-iterates to next entity
-Controller passes buffer to Escher
-Escher creates objects
	-Check object map
		-Generate object based on first Entity pointer if not extant
		-Find/update object if extant
	-unlocks entity
	-Remove pointer from buffer
	-iterate to next
*/