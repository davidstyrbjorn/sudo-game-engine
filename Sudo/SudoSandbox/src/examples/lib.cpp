#include<sudo.h>

using namespace sudo;

int main()
{
	sudo_system::WindowSystem *window = sudo_system::WindowSystem::Instance();

	while (window->IsOpen()) {
		window->Clear();

		window->Display();
	}

	std::cin.get();
	return 0;
}