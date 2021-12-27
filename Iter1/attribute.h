#pragma once

#include <string>
#include <sstream>
#include <typeinfo>
#include "misc.h"

class _Attribute
{
protected:
	int key;
public:
	int get_key() { return key; }
	virtual void set_value(int _value) {}
	//virtual void set_value(long long int _value) {};
	virtual void set_value(double _value) {}
	virtual void set_value(std::string _value) {}
	//virtual void set_value(std::shared_ptr<Entity> _node) {}
	virtual std::string get_value() = 0;
};


template <typename T>
class Attribute : public _Attribute
{
private:
	T value;
public:
	Attribute(int _key, T _value)
	{
		key = _key;
		value = _value;
	}

	template <typename T>
	void set_value(T _value)
	{
		value = _value;
	}

	std::string get_value()
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}
};
