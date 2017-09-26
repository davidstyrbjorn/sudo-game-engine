#pragma once

namespace sudo { namespace math { 
	
static void ClampFloat(float &a_value, const float &a_max, const float &a_min)
{
	if ( (a_value) > (a_max) )
		a_value = a_max;
	if ( (a_value) < (a_min) )
		a_value = a_min;
}

static void ClampInt(int &a_value, const int &a_max, const int &a_min)
{
	if ((a_value) > (a_max))
		a_value = a_max;
	if ((a_value) < (a_min))
		a_value = a_min;
}

static void ClampDouble(double &a_value, const double &a_max, const double &a_min)
{
	if ((a_value) > (a_max))
		a_value = a_max;
	if ((a_value) < (a_min))
		a_value = a_min;
}

} } 