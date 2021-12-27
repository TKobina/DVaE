#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "attribute.h"
#include "attribute_dictionary.h"

const int NULL_ENTITY = 0;
//Entity Types
const int NODE = 0;
const int EDGE = 1;

class Entity
{
private:
	void remap();
protected:
	std::vector<std::shared_ptr<_Attribute>> attributes;
	std::map<int, int> attributeMap;
public:	
	Entity(int _entityID = NULL_ENTITY);
	virtual int get_id() = 0;

	void add_attribute(std::shared_ptr<_Attribute> attribute);
	std::shared_ptr<_Attribute> get_attribute(int _key);
	void remove_attribute(int _key);

	template<typename T>
	void set_attribute(int _key, T _value)
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
	std::vector<int> find_attribute(T _value)
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

	virtual void output_all(AttributeDictionary& _dictionary, std::ostream& _out = std::cout) {};
	
	virtual void add_entity(std::shared_ptr<Entity> _e) {}
	virtual void remove_entity(int _key) {}
	virtual std::vector<std::shared_ptr<Entity>>& get_entities();

};
