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
		if (input->GetKey("d")) {
			printf("D down \n");
		}
		if (input->GetKeyDown("f")) {
			printf("F pressed \n");
		}

		system("cls");
	}

	void Render() override
	{

	}
};

int main() {
	ShapesGame *game = new ShapesGame();

	return 0;
}