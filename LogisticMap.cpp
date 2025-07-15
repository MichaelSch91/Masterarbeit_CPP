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
#include "Logisticmap_float32.h"
#include "Logisticmap_Default32squareroot.h"

#include "CSV_data.h"
#include "Default32squareroot_test.h"
#include <chrono>

//config
bool create_csv = 1;

static void logMap_default32squareroot();
static void logMap_float();


static void zeitmessung_logmap_default32squareroot() {
	auto start = std::chrono::high_resolution_clock::now();
	logMap_default32squareroot();
	auto ende = std::chrono::high_resolution_clock::now();

	auto dauer = std::chrono::duration_cast<std::chrono::milliseconds>(ende -
		start);
	std::cout << "Die Simulation der logistischen Abbildung mit Default32squareroot dauerte: " << dauer.count() << " Millisekunden." << std::endl;
}

static void zeitmessung_logmap_float() {
	auto start = std::chrono::high_resolution_clock::now();
	logMap_float();
	auto ende = std::chrono::high_resolution_clock::now();

	auto dauer = std::chrono::duration_cast<std::chrono::milliseconds>(ende -
		start);
	std::cout << "Die Simulation der logistischen Abbildung mit Float dauerte: " << dauer.count() << " Millisekunden." << std::endl;
}

static void logMap_float() {
	double START = 0.01;
	double START_INCREMENT = 0.01;
	double R_INCREMENT = 0.01;

	double start = START;
	double r = 4.00;

	while (r <= 4.00) {
		while (start < 1.0) {
			Logisticmap_float fl(start, r);
			std::cout << "Float, ";
			// fl.list_screen_csv(fl.get_long_double_List());
			start += START_INCREMENT;
		}
		start = START;
		r += R_INCREMENT;
		std::cout << '\n' << '\n';
	}
}

static void logMap_default32squareroot() {
	double START = 0.01;
	double START_INCREMENT = 0.01;
	double R_INCREMENT = 0.01;

	double start = START;
	double r = 4.00;

	while (r <= 4.00) {
		while (start < 1.0) {

			Logisticmap_Default32squareroot logMap(Default32squareroot::convert_to_Default32squareroot(2, start), Default32squareroot::convert_to_Default32squareroot(2, r));
			std::cout << "squareroot, ";
			// logMap.list_screen_csv();
			start += START_INCREMENT;

		}
		start = START;
		r += R_INCREMENT;
		std::cout << '\n' << '\n';
	}
}


int main()
{
	std::cout << "Start" << '\n';

	double START = 0.01;
	double START_INCREMENT = 0.01;
	double R_INCREMENT = 0.01;

	double start = START;
	double r = 3.80;

	while (r <= 4.00) {
		while (start < 1.0) {

			Logisticmap_float fl(start, r);
			std::cout << "Float, ";
			fl.list_screen_csv(fl.get_long_double_List());

			Logisticmap_Default32squareroot logMap(Default32squareroot::convert_to_Default32squareroot(2, start), Default32squareroot::convert_to_Default32squareroot(2, r));
			std::cout << "squareroot, ";
			logMap.list_screen_csv();
			start += START_INCREMENT;

		}
		start = START;
		r += R_INCREMENT;
		std::cout << '\n' << '\n';
	}


	std::cout << '\n' << "End" << '\n';
}
