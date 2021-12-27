#include "entity.h"

//================================BASE ENTITY===============================================
Entity::Entity(int _entityID, int _entityType) : entityID(_entityID), entityType(_entityType) {}

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

void Entity::remove_attribute_by_key(int _key)
{
	int index = attributeMap[_key];
	attributes.erase(attributes.begin() + index);
	remap();
}

void Entity::output_all(AttributeDictionary& _dictionary, std::ostream& _out)
{
	_out << "\nID | " << entityID;
	for (std::shared_ptr<_Attribute> attribute : attributes)
	{
		_out << "\n" << _dictionary.get_definition(attribute->get_key()) << " | ";
		_out << attribute->get_value();
	}
}

std::shared_ptr<_Attribute> Entity::get_attribute_by_key(int _key)
{
	int index = attributeMap[_key];
	return attributes[index];
}

