#include"../include/sudo.h"

using namespace sudo;

class ShapesGame : SudoClass {
private:
	SudoCore engine;

	ecs::Entity *entity, *sprite, *shape;

public:
	ShapesGame() {
		engine.init(math::Vector2(1200, 800), "Shapes!", this);
	}

	void Start() {
		// Create the shapes
		entity = new ecs::Entity("entity");
		sprite = new ecs::Entity("sprite");
		shape = new ecs::Entity("shape");

		// Add components and move them around
		entity->AddComponent(new ecs::RectangleComponent(math::Vector2(80, 80), math::Color::GetRandomColor()));
		entity->transform->Move(math::Vector3(500, 300, 0));
		entity->AddComponent(new ecs::SoundComponent("default", "D:\\temp\\sound.wav"));
		entity->AddComponent(new ecs::BoxCollider2D());
		entity->AddComponent(new ecs::FourWayMoveComponent(math::Vector2(0.5,0.5), "w", "s", "d", "a"));

		sprite->AddComponent(new ecs::SpriteComponent("D:\\temp\\cat.png"));
		sprite->transform->Move(math::Vector3(350, 0, 0));

		shape->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 220), math::Color::GetRandomColor()));
		shape->transform->Move(math::Vector3(700, 110, 0));

		textRenderer->LoadFont("C:\\Windows\\Fonts\\arial.ttf", "arial", 50);
		textRenderer->SetFont("arial");

		config->SetBackgroundColor(math::Color(40, 15, 90));
		config->SetAutoRender(true);
	}

	void Update(float deltaTime) {

	}

	void Render() override
	{
		textRenderer->DrawText("Debug Reeeest", math::Vector2(10, 15), math::Color(0, 255, 150));
	}
};

int main() {
	ShapesGame *game = new ShapesGame();

	return 0;
}