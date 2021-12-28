#include "attribute_dictionary.h"

void AttributeDictionary::add_definition(std::string _definition)
{
	int key = ++lastKey;
	set_definition(key, _definition);
}

void AttributeDictionary::set_definition(int _key, std::string _definition)
{
	size_t extant = dictionary.count(_key);
	if (extant == 0)
	{
		dictionary.emplace(_key, _definition);
		rdictionary.emplace(_definition, _key);
	}

	else
	{
		dictionary.at(_key) = _definition;
		rdictionary.at(_definition) = _key;
	}
	
}

std::string AttributeDictionary::get_definition(int _key)
{
	return dictionary.at(_key);
}

void AttributeDictionary::remove_definition(int _key)
{
	dictionary.erase(_key);
}

int AttributeDictionary::get_key(std::string _definition)
{
	return rdictionary.at(_definition);
}

void AttributeDictionary::output_dictionary(std::ostream& _out=std::cout)
{
	std::stringstream ss;
	ss << LDIVIDE;
	ss << "\nKEY | VALUE";
	for (const auto& definition : dictionary)
	{
		ss << "\n" << definition.first << " | " << definition.second;
	}
	ss << "\n";
	_out << ss.str();
}