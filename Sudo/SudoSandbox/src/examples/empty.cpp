#include"sudo.h"

using namespace sudo;

class ShapesGame : SudoClass {
private:
	SudoCore engine;

public:
	ShapesGame() 
	{
		engine.init(math::Vector2(1200, 700), "Shapes!", this);
	}

	void Start() 
	{
		config->SetAutoRender(true);
	}

	void Update(float deltaTime)
	{
	}

	void Render() override
	{

	}
};

int maiwdwdwn() {
	ShapesGame *game = new ShapesGame();

	return 0;
}