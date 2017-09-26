#pragma once

namespace sudo { namespace math { 

	class Math {

	public:
		static void ClampFloat(float &a_value, const float &a_max, const float &a_min)
		{
			if ( (a_value) > (a_max) )
				a_value = a_max;
			if ( (a_value) < (a_min) )
				a_value = a_min;
		}

	};

} } 