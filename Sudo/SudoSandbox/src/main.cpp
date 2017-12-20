#include"sudo.h"

using namespace sudo;

class Game : sudo::SudoClass {
private:
	sudo::SudoCore engine;

public:
	Game() {
		engine.init(math::Vector2(300, 300), "Sudo", this);
	}

	void Update(float deltaTime) override {
		std::cout << "sun is shining in the sky" << std::endl;
	}

	void Start() {
		config->SetBackgroundColor(math::Color::Red());
	}
};

int main() {
	Game *game = new Game();

	system("pause>null");
	return 0;
}