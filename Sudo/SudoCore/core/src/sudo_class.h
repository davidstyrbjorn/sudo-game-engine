#pragma once

namespace sudo {

	/* User class have to inherit from this class and then override Start and Update */

	class SudoClass {
	public:
		virtual ~SudoClass() { };

		virtual void Start() = 0;
		virtual void Update() = 0;
	};

}