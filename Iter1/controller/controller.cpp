#include "controller.h"

Controller::Controller()
{
	book = std::make_unique<Book>();
	importer = std::make_unique<Importer_CSV>();
	graphics_engine = std::make_unique<GraphicsEngine>();
	escher = graphics_engine->get_escher();

	std::ifstream infile;
	infile.open("data/MOCK_NODES.CSV");
	importer->proc_import(*book, NODE, infile);
	infile.close();

	infile.open("data/MOCK_EDGES.CSV");
	importer->proc_import(*book, EDGE, infile);
	infile.close();
	
	populate_escher();	


	graphics_engine->run();

}

void Controller::export_book(std::string fname)
{
	std::ofstream ofile;
	ofile.open(fname);
	book->print_all(ofile);
}

void Controller::populate_escher()
{
	book->populate_node_buffer(ebuffer_add);
	for (std::shared_ptr<Entity> node : ebuffer_add.entities)
	{
		escherize_node(node);
	}
}

void Controller::escherize_node(std::shared_ptr<Entity> node)
{
	//Shape
	//Name
	//Color
	//X
	//Y
	//Z
	//Scale
	//Rotation
	float attrScale, attrX, attrY, attrZ;
	AttributeDictionary& dict = book->dictionary_get(NODE);
	int dictKey = dict.get_key("ip_address");
	int ip[4];
	std::string value =	node->get_attribute(dictKey)->get_value();
	std::string delimiter = ".";
	size_t pos = 0;
	size_t i = 0;
	while ((pos = value.find(delimiter)) != std::string::npos)
	{
		ip[i] = std::stoi(value.substr(0, pos));
		value.erase(0, pos + delimiter.length());
		++i;
	}
	ip[3] = std::stoi(value);

	int scalar = 10;
	float x = scalar*ip[0] / 255.0;
	float y = scalar*ip[1] / 255.0;
	float z = scalar*ip[2] / 255.0;
	float scale = 0.5 * ip[3] / 255.0;

	float angle = 360 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	std::shared_ptr<EscherNode> n = std::make_shared<EscherNode>();
	n->location = glm::vec3(x, y, z);
	n->angle = angle;
	n->scale = scale;
	escher->add_node(n);
}