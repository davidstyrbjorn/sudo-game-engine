#include"sudo.h"

using namespace sudo;

class ShapesGame : SudoClass {
private:
	SudoCore engine;
	
	ecs::Entity *shape1, *shape2, *shape3, *shape4;
	ecs::Entity *shape5, *shape6;

public:
	ShapesGame() {
		engine.init(math::Vector2(700, 700), "Shapes!", this);
	}

	void Start() {
		// Create the shapes
		shape1 = new ecs::Entity();
		shape2 = new ecs::Entity();
		shape3 = new ecs::Entity();
		shape4 = new ecs::Entity();
		shape5 = new ecs::Entity();
		shape6 = new ecs::Entity();

		// Add components and move them around
		shape1->AddComponent(new ecs::RectangleComponent(math::Vector2(80, 80), math::Color::Red()));
		shape1->transform->Move(math::Vector3(5, 10, 0));

		shape2->AddComponent(new ecs::RectangleComponent(math::Vector2(90, 120), math::Color(10, 5, 240)));
		shape2->transform->Move(math::Vector3(85, 110, 0));

		shape3->AddComponent(new ecs::RectangleComponent(math::Vector2(10, 220), math::Color(10, 240, 100)));
		shape3->transform->Move(math::Vector3(300, 110, 0));

		shape4->AddComponent(new ecs::RectangleComponent(math::Vector2(90, 120), math::Color(255, 100, 200)));
		shape4->transform->Move(math::Vector3(290, 290, 0));

		shape5->AddComponent(new ecs::TriangleComponent(math::Vector2(100, 100), math::Color::Blue()));
	}

	void Render() override {
		renderer->Submit(shape1->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape2->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape3->GetComponent<ecs::RectangleComponent>());
		renderer->Submit(shape4->GetComponent<ecs::RectangleComponent>());
		//renderer->Submit(shape5->GetComponent<ecs::TriangleComponent>());
	}
};

int main() {
	ShapesGame *game = new ShapesGame();

	return 0;
}