#pragma once

// Forward decleration
namespace sudo { 
	namespace math {
		class Vector3;
	}
	namespace ecs {
		class Transform;
	}
} 

namespace sudo { namespace graphics { 

	/* Base class for 2D renderable shapes */

	class Renderable2D {
	public:
		/* Virtual desctructor */
		virtual ~Renderable2D() { }

		/* Sets position of the transform */
		virtual void SetPosition(math::Vector3 &a_newPosition) = 0;

		/* Sets scale of the transform */
		virtual void SetScale(math::Vector3 &a_newScale) = 0;

		/* Scales up transform by order of a_magnitude */
		virtual void Scale(float a_magnitude) = 0;

		/* Moves transform in a_direction at a_magnitude / frame */
		virtual void Move(math::Vector3 &a_direction, float a_magnitude) = 0;

	protected:							  	
		ecs::Transform *m_entityTransform;		
	};
} }