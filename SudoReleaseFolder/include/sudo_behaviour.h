#pragma once

namespace sudo {

	class SudoBehaviour {
	public:
		virtual void Start() { }
		virtual void Update(float deltaTime) { }
		virtual void Render() { }
		virtual void LateUpdate(float deltaTime) { }
	};

}