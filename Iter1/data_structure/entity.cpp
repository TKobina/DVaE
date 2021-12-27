#include "entity.h"

//================================BASE ENTITY===============================================
Entity::Entity(int _entityID) {}

void Entity::remap()
{
	attributeMap.clear();
	for (size_t i = 0; i < attributes.size(); ++i)
	{
		attributeMap.emplace(attributes[i]->get_key(), i);
	}
}

void Entity::add_attribute(std::shared_ptr<_Attribute> attribute)
{
	attributes.push_back(attribute);
	attributeMap.emplace(attribute->get_key(), attributes.size() - 1);
}

std::shared_ptr<_Attribute> Entity::get_attribute(int _key)
{
	int index = attributeMap[_key];
	return attributes[index];
}

void Entity::remove_attribute(int _key)
{
	int index = attributeMap[_key];
	attributes.erase(attributes.begin() + index);
	remap();
}


std::vector<std::shared_ptr<Entity>>& Entity::get_entities()
{
	std::vector<std::shared_ptr<Entity>> temp;
	return temp;
}
