// LogisticMap.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

// list::max_size
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <cmath>
#include <iomanip>

#include "LogisticMapCalc.h"
#include "Logisticmap_float.h"
#include "Logisticmap_double.h"
#include "Logisticmap_long_double.h"

#include "Zahlendarstellung.h"
#include "Zahlenverteilung.h"
#include "Float16.h"
#include "Float32.h"
#include "ExperimentalDefault.h"
#include "Default32squareroot.h"
#include "Logisticmap_float16.h"
#include "Logisticmap_float32.h"
#include "Logisticmap_Default32squareroot.h"

#include "CSV_data.h"
#include "Default32squareroot_test.h"
#include <chrono>

//config
bool create_csv = 1;

static void logMap_default32squareroot(double s, double start_increment, double r);
static void logMap_float(double s, double start_increment, double r);


static void zeitmessung_logmap_default32squareroot(double s, double start_increment, double r) {
	auto start = std::chrono::high_resolution_clock::now();
	logMap_default32squareroot(s, start_increment, r);
	auto ende = std::chrono::high_resolution_clock::now();

	auto dauer = std::chrono::duration_cast<std::chrono::milliseconds>(ende -
		start);
	std::cout << "Default32Squareroot: r = " << r << " s = " << s << " s_incr = " << start_increment << std::endl;
	std::cout << "Die Simulation der logistischen Abbildung dauerte: " << dauer.count() << " Millisekunden." << std::endl;
}

static void zeitmessung_logmap_float(double s, double start_increment, double r) {
	auto start = std::chrono::high_resolution_clock::now();
	logMap_float(s, start_increment, r);
	auto ende = std::chrono::high_resolution_clock::now();

	auto dauer = std::chrono::duration_cast<std::chrono::milliseconds>(ende -
		start);
	std::cout << "Float: r = " << r << " s = " << s << " s_incr = " << start_increment << std::endl;
	std::cout << "Die Simulation der logistischen Abbildung dauerte: " << dauer.count() << " Millisekunden." << std::endl;
}

static void logMap_float(double s, double start_increment, double r) {
	double START = s;
	double START_INCREMENT = start_increment;

	double start = START;

	while (start < 1.0) {
		Logisticmap_float fl(start, r);
		// std::cout << "Float, ";
		// fl.list_screen_csv(fl.get_long_double_List());
		start += START_INCREMENT;
	}

	std::cout << '\n' << '\n';
}

static void logMap_default32squareroot(double s, double start_increment, double r) {
	double START = s;
	double START_INCREMENT = start_increment;

	double start = START;

	while (start < 1.0) {
		Logisticmap_Default32squareroot logMap(Default32squareroot::convert_to_Default32squareroot(2, start), Default32squareroot::convert_to_Default32squareroot(2, r));
		// std::cout << "squareroot, ";
		// logMap.list_screen_csv();
		start += START_INCREMENT;
	}
	std::cout << '\n' << '\n';
}

static float newtonVerfahren_float(long double a, long double s, int iterations) {
	float x = s; // Startwert
	float radikand = a;
	for (int i = 0; i <= iterations; i++) {
		x = (x + radikand / x) / 2.0f;
	}
	return x;
}

static long double newtonVerfahren_long_double(long double a, long double s, int iterations) {
	long double x = s; // Startwert
	for (int i = 0; i <= iterations; i++) {
		x = (x + a / x) / 2.0;
	}
	return x;
}

static Default32squareroot newtonVerfahren_Default32squareroot(long double a, long double s, int iterations) {
	Default32squareroot x = Default32squareroot::convert_to_Default32squareroot(2, s); // Startwert
	Default32squareroot radikand = Default32squareroot::convert_to_Default32squareroot(2, a);
	Default32squareroot zwei = Default32squareroot(2, 0, 129, 0);
	for (int i = 0; i <= iterations; i++) {
		x = (x + radikand / x) / zwei;
	}
	return x;
}

static void newtonVerfahren_Vergleich(long double a, long double s, int iterations, long double max) {
	int counter_float = 0;
	int counter_sqrt2 = 0;
	int counter_equal = 0;

	while (a <= max) {
		if (abs((long double)newtonVerfahren_float(a, s, iterations) - newtonVerfahren_long_double(a, s, iterations)) < abs(newtonVerfahren_Default32squareroot(a, s, iterations).calcX() - newtonVerfahren_long_double(a, s, iterations))) {
			//std::cout << "Float ist besser" << '\n';
			counter_float++;
		}
		else if (abs((long double)newtonVerfahren_float(a, s, iterations) - newtonVerfahren_long_double(a, s, iterations)) == abs(newtonVerfahren_Default32squareroot(a, s, iterations).calcX() - newtonVerfahren_long_double(a, s, iterations))) {
			//std::cout << "beide gleich" << '\n';
			counter_equal++;
		}
		else {
			//std::cout << "Sqrt2 ist besser" << '\n';
			counter_sqrt2++;
		}
		a += 1.0;
	}
	std::cout << iterations <<"Iterationen: ";
	std::cout << "Float: " << counter_float << " Sqrt2: " << counter_sqrt2 << " gleich: " << counter_equal << '\n';
}

static void newtonVerfahren_Vergleich_MathSqrt(long double a, long double s, int iterations, long double max) {
	int counter_float = 0;
	int counter_sqrt2 = 0;
	int counter_equal = 0;

	while (a <= max) {
		if (abs((long double)newtonVerfahren_float(a, s, iterations) - sqrt(a)) < abs(newtonVerfahren_Default32squareroot(a, s, iterations).calcX() - sqrt(a))) {
			//std::cout << "Float ist besser" << '\n';
			counter_float++;
		}
		else if (abs((long double)newtonVerfahren_float(a, s, iterations) - sqrt(a)) == abs(newtonVerfahren_Default32squareroot(a, s, iterations).calcX() - sqrt(a))) {
			//std::cout << "beide gleich" << '\n';
			counter_equal++;
		}
		else {
			//std::cout << "Sqrt2 ist besser" << '\n';
			counter_sqrt2++;
		}
		a += 1.0;
	}
	std::cout << iterations << "Iterationen: ";
	std::cout << "Float: " << counter_float << " Sqrt2: " << counter_sqrt2 << " gleich: " << counter_equal << '\n';
}

static void operatorTest() {
	std::vector<long double> values_1 = { 16, 32, 64 };
	std::vector<long double> values_2 = { 16, 32, 64 };

	operatorTestPlus(values_1, values_2);
	operatorTestMinus(values_1, values_2);
	operatorTestMultiply(values_1, values_2);
}

static void operatorTestPlus(std::vector<long double> values_1, std::vector<long double> values_2) {
	int counter_float = 0;
	int counter_sqrt2 = 0;
	int counter_equal = 0;
	
	Default32squareroot sqrt_result(2, 0, 126, 0);
	float fl_result = 0;
	long double comparator = 0;
	
	for (int i = 0; i < values_1.size(); i++) {
		sqrt_result = Default32squareroot::convert_to_Default32squareroot(2, values_1[i]) + Default32squareroot::convert_to_Default32squareroot(2, values_2[i]);
		fl_result = (float)values_1[i] + (float)values_2[i];
		comparator = values_1[i] + values_2[i];

		if (abs((long double)fl_result - comparator) < abs(sqrt_result.calcX() - comparator)) {
			//std::cout << "Float ist besser" << '\n';
			counter_float++;
		}
		else if (abs((long double)fl_result - comparator) == abs(sqrt_result.calcX() - comparator)) {
			//std::cout << "beide gleich" << '\n';
			counter_equal++;
		}
		else {
			//std::cout << "Sqrt2 ist besser" << '\n';
			counter_sqrt2++;
		}
	}
}

static void operatorTestMinus(std::vector<long double> values_1, std::vector<long double> values_2) {
	int counter_float = 0;
	int counter_sqrt2 = 0;
	int counter_equal = 0;

	Default32squareroot sqrt_result(2, 0, 126, 0);
	float fl_result = 0;
	long double comparator = 0;

	for (int i = 0; i < values_1.size(); i++) {
		sqrt_result = Default32squareroot::convert_to_Default32squareroot(2, values_1[i]) - Default32squareroot::convert_to_Default32squareroot(2, values_2[i]);
		fl_result = (float)values_1[i] - (float)values_2[i];
		comparator = values_1[i] - values_2[i];

		if (abs((long double)fl_result - comparator) < abs(sqrt_result.calcX() - comparator)) {
			//std::cout << "Float ist besser" << '\n';
			counter_float++;
		}
		else if (abs((long double)fl_result - comparator) == abs(sqrt_result.calcX() - comparator)) {
			//std::cout << "beide gleich" << '\n';
			counter_equal++;
		}
		else {
			//std::cout << "Sqrt2 ist besser" << '\n';
			counter_sqrt2++;
		}
	}
}

static void operatorTestMultiply(std::vector<long double> values_1, std::vector<long double> values_2) {
	int counter_float = 0;
	int counter_sqrt2 = 0;
	int counter_equal = 0;

	Default32squareroot sqrt_result(2, 0, 126, 0);
	float fl_result = 0;
	long double comparator = 0;

	for (int i = 0; i < values_1.size(); i++) {
		sqrt_result = Default32squareroot::convert_to_Default32squareroot(2, values_1[i]) * Default32squareroot::convert_to_Default32squareroot(2, values_2[i]);
		fl_result = (float)values_1[i] * (float)values_2[i];
		comparator = values_1[i] * values_2[i];

		if (abs((long double)fl_result - comparator) < abs(sqrt_result.calcX() - comparator)) {
			//std::cout << "Float ist besser" << '\n';
			counter_float++;
		}
		else if (abs((long double)fl_result - comparator) == abs(sqrt_result.calcX() - comparator)) {
			//std::cout << "beide gleich" << '\n';
			counter_equal++;
		}
		else {
			//std::cout << "Sqrt2 ist besser" << '\n';
			counter_sqrt2++;
		}
	}
}


int main()
{
	std::cout << "Start" << '\n';


	operatorTest();





	/*
	long double max = 5001.0;

	long double a = 2.0;
	long double s = a;
	std::vector<int> iterations = {16, 32, 64};

	for (int i : iterations) {
		std::cout << "Iterations: " << i << '\n';
		if (i == 3 or i == 5) {
			continue;
		}
		newtonVerfahren_Vergleich_MathSqrt(a, s, i, max);
	}

	
	double start = 0.01;
	double start_increment = 0.01;
	double r = 4.0;

	int iterations = 50;

	for (int i = 0; i < iterations; i++) {
		while (r <= 4) {
			zeitmessung_logmap_default32squareroot(start, start_increment, r);

			zeitmessung_logmap_float(start, start_increment, r);
		}
	}


	std::vector<double> s_ = { 0.01, 0.08, 0.13, 0.25, 0.33, 0.41, 0.5 };
	std::vector<double> r_ = { 3.8, 3.89, 3.92, 3.985, 3.99, 4.0 };


	for (const auto& r : r_) {
		for (const auto& start : s_) {


			Logisticmap_float16 fl16(start, r);
			std::cout << "Float16, ";
			fl16.list_screen_csv(fl16.get_long_double_List());
		}
	}


	double START = 0.01;
	double START_INCREMENT = 0.2;
	double R_INCREMENT = 0.01;

	double start = START;
	double r = 3.8;

	while (r < 4) {
		while (start < 1.0) {

			Logisticmap_Default32squareroot logMap(Default32squareroot::convert_to_Default32squareroot(2, start), Default32squareroot::convert_to_Default32squareroot(2, r));
			std::cout << "squareroot, ";
			logMap.list_screen_csv();

			Logisticmap_float fl(start, r);
			std::cout << "Float, ";
			fl.list_screen_csv(fl.get_long_double_List());

			Logisticmap_double d(start, r);
			std::cout << "Double, ";
			d.list_screen_csv(d.get_long_double_List());

			start += START_INCREMENT;
		}
		start = START;
		r += R_INCREMENT;
		std::cout << '\n' << '\n';
	}

	double MAX = 100'000.0;

	long double x = 30000;
	long double highest_value = 1.0;
	long double first_value = MAX;
	Default32squareroot result(2,0,126,0);

	// Auslöschung x−sqrt(x^2+1)

	while (x < MAX) {
		Default32squareroot d = Default32squareroot::convert_to_Default32squareroot(2, x);
		Default32squareroot d_incr = Default32squareroot::convert_to_Default32squareroot(2, sqrt(x * x + 1.0));
		result = d - d_incr;
		if (result != Default32squareroot(2, 0, 0, 0)) {
			std::cout << x << '\n';
			highest_value = x;
			std::cout << result.calcX() << '\n';
		}
		else {
			if (first_value > x) {
				first_value = x;
				std::cout << first_value << '\n';
			}
		}
		x += 0.1;
	}

	std::cout <<highest_value << '\n';


	float f = 0;
	float result_float = 1.0;
	float highest_value = 1.0;
	while (f < MAX) {
		result_float = f - sqrt(f * f + 1);
		if (result_float != 0) {
			std::cout << f << '\n';
			highest_value = f;
		}
		f += 0.1;
	}
	std::cout << highest_value << '\n';
	*/




	std::cout << '\n' << "End" << '\n';
}
