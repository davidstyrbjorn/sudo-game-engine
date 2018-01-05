#include"../include/sudo.h"

using namespace sudo;

class ShapesGame : SudoClass {
private:
	SudoCore engine;

	ecs::Entity *shape1, *shape2, *shape3, *shape4;
	ecs::Entity *shape5;

public:
	ShapesGame() {
		engine.init(math::Vector2(1200, 800), "Shapes!", this);
	}

	void Start() {
		// Create the shapes
		shape1 = new ecs::Entity("mieeh");
		shape2 = new ecs::Entity("rect1");
		shape3 = new ecs::Entity("rect2");
		shape4 = new ecs::Entity("sprite");
		shape5 = new ecs::Entity("empty");

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
		config->SetAutoRender(true);
	}

	void Update(float deltaTime) {
		if (input->GetKey("f")) {
			config->SetRenderMode(sudo_system::SudoRenderMode::WIRE_FRAME_MODE);
		}
	}

	void Render() override
	{
		//renderer->Submit(shape1->GetComponent<ecs::RectangleComponent>());
		//renderer->Submit(shape2->GetComponent<ecs::RectangleComponent>());
		//renderer->Submit(shape3->GetComponent<ecs::RectangleComponent>());
		//renderer->Submit(shape4->GetComponent<ecs::SpriteComponent>());
		//renderer->Submit(shape5->GetComponent<ecs::SpriteComponent>());

		textRenderer->DrawText("Debug Reeeest", math::Vector2(0, 0), math::Color(0, 255, 150));
	}
};

int main() {
	ShapesGame *game = new ShapesGame();

	return 0;
}