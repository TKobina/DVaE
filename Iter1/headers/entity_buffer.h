#pragma once
#include "../data_structure/entity.h"

struct EntityBuffer
{
	size_t current = 0;
	size_t max = 100000;
	std::vector<std::shared_ptr<Entity>> entities;
};
