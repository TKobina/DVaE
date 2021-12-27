#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "attribute.h"
#include "attribute_dictionary.h"

//Entity Types
const int NODE = 0;
const int EDGE = 1;

class Entity
{
private:
	std::vector<std::shared_ptr<_Attribute>> attributes;
	std::map<int, int> attributeMap;
	void remap();
public:
	const int entityID;
	const int entityType;

	Entity(int _entityID, int _entityType);
	//~Entity() {}
	
	void add_attribute(std::shared_ptr<_Attribute> attribute);
	std::shared_ptr<_Attribute> get_attribute_by_key(int _key);
	
	//std::string get_attribute_by_key(int _key);
	void remove_attribute_by_key(int _key);

	void output_all(AttributeDictionary& _dictionary, std::ostream& _out = std::cout);

	//TEMPLATE METHOD DEFINITIONS
	template<typename T>
	void set_attribute_by_key(int _key, T _value)
	{
		int index;
		Attribute <T>* a = new Attribute<T>(_key, _value);

		if (attributeMap.count(_key))
		{
			index = attributeMap[_key];
			attributes.erase(attributes.begin() + index);
			attributes.insert(attributes.begin() + index, std::shared_ptr<_Attribute>(a));
		}
		else
		{
			index = attributes.size() - 1;
			attributes.push_back(std::shared_ptr<_Attribute>(a));
		}
		attributeMap.emplace(_key, index);
	}

	template<typename T>
	std::vector<int> search_attribute_by_value(T _value)
	{
		int key;
		std::vector<int> keys;
		
		std::stringstream ss;
		ss << _value;
		std::string toFind = ss.str();
		std::string found;

		for (size_t index = 0; index < attributes.size(); ++index)
		{
			attributes[index]->get_value(found);
			if (toFind == found)
			{
				key = attributes[index]->get_key();
				keys.push_back(key);
			}
		}
		return keys;
	}
};
