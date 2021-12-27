#include "importer.h"

void Importer_CSV::parse_line(std::string& _line, std::vector<std::string>& _data, char split_char)
{
	std::istringstream iss(_line);
	std::string buffer;
	_data.clear();
	while (std::getline(iss, buffer, split_char))
		_data.push_back(buffer);
}

void Importer_CSV::proc_import(Book& _book, int type, std::istream& _in)
{
	//std::ifstream& in = std::static_cast<std::ifstream>(_in);
	std::vector<std::string> fields;
	std::vector<std::string> data;
	std::string line;

	//Add attributes to dictionary
	std::getline(_in, line);
	parse_line(line, fields);
	fields.erase(fields.begin()); //strip first field from first row, as ID is built into entity, not for the dictionary
	for (std::string field : fields)
	{
		_book.definition_add(type, field);
	}

	//Parse all data
	while (std::getline(_in, line))
	{
		parse_line(line, data);
		int id = std::stoi(data[0]);
		_book.entity_create(type, id);

		if (data.size() == 1) continue;  //in case of series of ID entities without any other attributes		

		for (size_t i = 1; i < data.size(); ++i)
		{
			int key = _book.dictionary_get(type).get_key(fields[i - 1]);
			_book.attribute_create<std::string>(type, id, key, data[i]);
		}
	}
}
