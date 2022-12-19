#include <math.h>
#include "X3DEasings.h"


namespace X3D
{
	float easeInOutCircf(float t, float b, float c, float d)
	{
		if ((t /= d / 2) < 1) 
			return float(-c / 2 * (sqrt(1 - t * t) - 1) + b);
		else
			return float(c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b);
	}
}