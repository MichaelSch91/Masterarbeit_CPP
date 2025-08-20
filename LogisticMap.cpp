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


int main()
{
	std::cout << "Start" << '\n';

	/*
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
	*/
	double MAX = 1'000'000.0;

	long double x = 100000;
	long double highest_value = 1.0;
	long double first_value = 50'000.0;
	Default32squareroot result(2,0,126,0);

	// Auslöschung klassisch x−sqrt(x^2+1)

	while (x < MAX) {
		Default32squareroot d = Default32squareroot::convert_to_Default32squareroot(2, x);
		Default32squareroot d_incr = Default32squareroot::convert_to_Default32squareroot(2, sqrt(x * x + 1.0));

		if (d != d_incr) {
			d.printAttributes();
			d_incr.printAttributes();
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

	/*
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
	// Auslöschung Mantisse +1


	std::cout << '\n' << "End" << '\n';
}
