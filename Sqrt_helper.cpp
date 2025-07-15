#include "Sqrt_helper.h"

double Sqrt_helper::sqrt_power(int base, int exponent) {
	if (exponent % 2 == 0) {
		return sqrt_power_even(base, exponent);
	}
	else {
		return sqrt(base) * pow(base, (exponent - 1) / 2);
	}
}

long long Sqrt_helper::sqrt_power_even(int base, int exponent) {
	// ggf mit For/While-Schleife bei sehr hohen Werten besser?
	return pow(base, exponent/2);
}