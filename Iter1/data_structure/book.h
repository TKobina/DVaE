/*
Handles graph objects, attribute dictionaries, and manages entities' attributes
*/
#pragma once

#include "graph.h"
#include "collective.h"


class Book
{
private:
	std::unique_ptr<Graph> graph;
	AttributeDictionary nodeDict;
	AttributeDictionary edgeDict;

public:
	Book();
	void print_all(std::ostream& _out = std::cout);

	//Dictionary Management
	AttributeDictionary& dictionary_get(int type);
	void definition_add(int type, std::string _definition);
	void definition_remove(int type, int _key);
	void definition_change(int type, int _key, std::string _definition);

	//Entity Management
	void entity_create(int type, int _id);
	void entity_remove(int type, int _id);
	std::shared_ptr<Entity> entity_get(int type, int _id);

	//Attribute Management
	void attribute_add(int type, int _id, std::shared_ptr<_Attribute> _attribute);
	std::shared_ptr<_Attribute> get_attribute(int type, int _id, int _key);
	void attribute_remove(int type, int _id, int _key);

	template <typename T>
	void attribute_create(int type, int _id, int _key, T _value)
	{
		std::shared_ptr<Entity> e = entity_get(type, _id);
		Attribute<T>* attribute = new Attribute<T>(_key, _value);
		e->add_attribute(std::shared_ptr<_Attribute>(attribute));
	}

	template <typename T>
	void attribute_change(int type, int _id, int _key, T _value)
	{
		attribute_remove(type, _id, _key);
		attribute_create(type, _id, _key, _value);
	}
};
