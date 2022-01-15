
#pragma once
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ObjectBuffer
{
private:
	bool lock;
	std::vector<glm::vec3> positions;
	std::map<size_t, int> object_index;
	
	void set_lock(bool state);
public:
	void complete();
	bool is_locked();
	void position_add(int _id, glm::vec3 _position);
};

void ObjectBuffer::set_lock(bool state)
{
	lock = state;
}

void ObjectBuffer::complete()
{
	set_lock(false);
}

bool ObjectBuffer::is_locked()
{
	return !lock;
}

void ObjectBuffer::position_add(int _id, glm::vec3 _position)
{
	set_lock(true);
	positions.push_back(_position);
	object_index.emplace(positions.size(), _id);
	set_lock(false);
}