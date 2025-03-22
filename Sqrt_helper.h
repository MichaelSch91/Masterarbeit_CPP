#ifndef SQRT_HELPER_H
#define SQRT_HELPER_H

#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <cmath>

class Sqrt_helper {
public:
	static double sqrt_power(int base, int exponent);

	static long long sqrt_power_even(int base, int exponent);
};
#endif