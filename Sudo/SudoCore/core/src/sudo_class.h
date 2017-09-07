#pragma once

namespace sudo {

	/* User class have to inherit from this class and then override Start and Update */

	class SudoClass {
	public:
		virtual ~SudoClass() { };

		virtual void Start() { };
		virtual void Update() { };
	};

}