#include "book.h"

Book::Book()
{
	Collective* collective = new Collective(nodeDict, edgeDict);
	graph = std::unique_ptr<Graph>(collective);

	nodeDict.set_definition(0, "Name");
	edgeDict.set_definition(0, "Name");
}


//==============================DICTIONARY MANAGEMENT============================================
AttributeDictionary& Book::dictionary_get(int type)
{
	switch (type)
	{
	case NODE:
		return nodeDict;
	case EDGE:
		return edgeDict;
	default:
		throw std::invalid_argument("\ndictionary_get() not given a valid dictionary type");
	}
}

void Book::definition_add(int type, std::string _definition)
{
	AttributeDictionary& d = dictionary_get(type);
	d.add_definition(_definition);
}

void Book::definition_remove(int type, int _key)
{
	AttributeDictionary& d = dictionary_get(type);
	d.remove_definition(_key);
}

void Book::definition_change(int type, int _key, std::string _definition)
{
	AttributeDictionary& d = dictionary_get(type);
	d.set_definition(_key, _definition);
}

//================================ENTITY MANAGEMENT============================================
void Book::entity_create(int type, int _id)
{
	switch (type)
	{
	case NODE:
	{
		auto entity = std::make_shared<Node>(_id);
		graph->add_node(entity);
		break;
	}
	case EDGE:
	{
		auto entity = std::make_shared<Edge>(_id);
		graph->add_edge(entity);
		break;
	}
	}	
}

std::shared_ptr<Entity> Book::entity_get(int type, int _id)
{
	switch (type)
	{
	case NODE:
		return graph->get_node(_id);
	case EDGE:
		return graph->get_edge(_id);
	default:
		throw std::invalid_argument("\nentity_get() not given a valid dictionary type");
	}
}

void Book::entity_remove(int type, int _id)
{
	switch (type)
	{
	case NODE:
		graph->remove_node(_id);
		break;
	case EDGE:
		graph->remove_edge(_id);
		break;
	}
}

//==============================ATTRIBUTE MANAGEMENT============================================
void Book::attribute_add(int type, int _id, std::shared_ptr<_Attribute> _attribute)
{
	std::shared_ptr<Entity> e = entity_get(type, _id);
	e->add_attribute(_attribute);
}

std::shared_ptr<_Attribute> Book::get_attribute(int type, int _id, int _key)
{
	std::shared_ptr<Entity> e = entity_get(type, _id);
	return e->get_attribute(_key);
}

void Book::attribute_remove(int type, int _id, int _key)
{
	std::shared_ptr<Entity> e = entity_get(type, _id);
	e->remove_attribute(_key);
}

void Book::print_all(std::ostream& _out)
{
	graph->print_all(_out);
}