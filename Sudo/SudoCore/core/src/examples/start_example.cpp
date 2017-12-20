#include"../../include/sudo.h"

using namespace sudo;

class YourGame : SudoClass
{
private:
	SudoCore engine;

public:
	// YourGame's constructor
	YourGame()
	{
		engine.init(math::Vector2(800, 600), "Your Window Caption!", this);
	}

	// Behaviour overrides
	void Start() SUDO_BEHAVIOUR { }
	void Update(float deltaTime) SUDO_BEHAVIOUR { }
	void Render() SUDO_BEHAVIOUR { }
};