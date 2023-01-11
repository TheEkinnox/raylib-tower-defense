#ifndef __LIBMATH__ARITHMETIC_H__
#define __LIBMATH__ARITHMETIC_H__

namespace LibMath
{
	float ceiling(float);				// Return lowest integer value higher or equal to parameter
	float clamp(float, float, float);	// Return parameter limited by the given range
	float floor(float);					// Return highest integer value lower or equal to parameter
	float squareRoot(float);			// Return square root of parameter
	float wrap(float, float, float);	// Return parameter as value inside the given range
	float min(float, float);			// Return smallest parameter
	float max(float, float);			// Return largest parameter
	float abs(float);					// Return absolute value of parameter

	bool floatEquals(float a, float b);
}

#endif // !__LIBMATH__ARITHMETIC_H__
