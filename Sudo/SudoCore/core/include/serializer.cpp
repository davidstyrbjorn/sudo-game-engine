#include "serializer.h"

#include<fstream>
//#include<assert.h>
#include<cassert>

namespace sudo 
{

void Serializer::SerializeWorld(const sudo_system::WorldSystem & a_world)
{
	std::ofstream file("C:\\level.txt");
	assert(file.is_open());

	file << "test\n";

	file.close();
}

char * Serializer::GetSeralizedata(const ecs::Entity & a_entity)
{
	return nullptr;
}

}
