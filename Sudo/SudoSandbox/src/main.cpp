#include"core\sudo.h"

using namespace sudo;

class Game : SudoClass {
public:
	SudoCore engine;

	Game() {
		engine.init(math::Vector2(100, 100), "wow", this);
	}

	void Start() override
	{
		config->SetBackgroundColor(math::Vector4(0.5, 1, 0.1, 1));
	}

	void Update(float deltaTime) override 
	{

	}

	void OnApplicationQuit() override
	{

	}
};

int main() {
	Game *game = new Game();

	return 0;
}