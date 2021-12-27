#include "edge.h"

Edge::Edge(int _edgeID) : edgeID(_edgeID) {}

int Edge::get_id() { return edgeID; }

void Edge::remap_entities()
{
	entityMap.clear();
	for (size_t i = 0; i < entities.size(); ++i)
	{
		entityMap.emplace(entities[i]->get_id(), i);
	}
}

void Edge::add_entity(std::shared_ptr<Entity> _e)
{
	if (entityMap.count(_e->get_id()) == 0)
	{
		entities.push_back(_e);
		entityMap.emplace(_e->get_id(), entities.size() - 1);
	}
}

std::vector<std::shared_ptr<Entity>>& Edge::get_entities()
{
	return entities;
}

void Edge::remove_entity(int _key)
{
	int index = entityMap[_key];
	entities.erase(entities.begin() + index);
	remap_entities();
}

void Edge::output_all(AttributeDictionary& _dictionary, std::ostream& _out)
{
	_out << "\n" << LDIVIDE << "\nEdge ID | " << edgeID << SDIVIDE<<  "\nNodes:";
	for (std::shared_ptr<Entity> entity : entities)
	{
		_out << "\nID | " << entity->get_id();
	}
	_out << SDIVIDE << "\nAttributes:";
	for (std::shared_ptr<_Attribute> attribute : attributes)
	{
		_out << "\n" << _dictionary.get_definition(attribute->get_key()) << " | ";
		_out << attribute->get_value();
	}
}
