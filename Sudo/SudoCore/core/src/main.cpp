#include"../include/sudo.h"

using namespace sudo;

class ShapesGame : SudoClass {
private:
	SudoCore engine;

	ecs::Entity *shape1, *shape2, *shape3, *shape4;
	ecs::Entity *shape5, *shape6;

public:
	ShapesGame() {
		engine.init(math::Vector2(900, 700), "Shapes!", this);
	}

	void Start() {
		// Create the shapes
		shape1 = new ecs::Entity("shape1");
		shape2 = new ecs::Entity("shape2");
		shape3 = new ecs::Entity("shape3");
		shape4 = new ecs::Entity("shape4");
		shape5 = new ecs::Entity("shape5");
		shape6 = new ecs::Entity("shape6");

		// Add components and move them around
		shape1->AddComponent(new ecs::RectangleComponent(math::Vector2(80, 80), math::Color::GetRandomColor()));
		shape1->transform->Move(math::Vector3(500, 300, 0));
		shape1->AddComponent(new ecs::SoundComponent("default", "D:\\temp\\sound.wav"));
		shape1->AddComponent(new ecs::BoxCollider2D());
		shape1->AddComponent(new ecs::FourWayMoveComponent(math::Vector2(0.5,0.5), "w", "s", "d", "a"));

		shape2->AddComponent(new ecs::RectangleComponent(math::Vector2(90, 120), math::Color::GetRandomColor()));
		shape2->transform->Move(math::Vector3(250, 450, 0));

		shape3->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 220), math::Color::GetRandomColor()));
		shape3->transform->Move(math::Vector3(700, 110, 0));

		shape4->AddComponent(new ecs::SpriteComponent("D:\\temp\\cat.png"));
		shape4->transform->Move(math::Vector3(350, 290, 0));

		textRenderer->LoadFont("C:\\Windows\\Fonts\\arial.ttf", "arial", 50);
		textRenderer->SetFont("arial");

		config->SetBackgroundColor(math::Color(30, 50, 30));
	}

	void Update(float deltaTime) {

	}

	void Render() override
	{
		renderer->Submit(shape1->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape2->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape3->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape4->GetComponent<ecs::SpriteComponent>());

		textRenderer->DrawText("Debug Reeeest", math::Vector2(0, 0), math::Color(0, 255, 150));
	}
};

int main() {
	ShapesGame *game = new ShapesGame();

	return 0;
}