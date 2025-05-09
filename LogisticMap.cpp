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

//config
bool create_csv = 1;

int main()
{
	std::cout << "Start" << '\n';

	/*
	Zahlenverteilung z(0.0, 1.0, 1024, "ExperimentalDefault 1,7,24 Bit");
	z.berechne_zahlenverteilung(ExperimentalDefault(2, 24, 7));
	z.print_zahlenverteilung_csv_format();

	
	double start = 0.25;
	double r = 4.00;

	while (r <= 4.00) {
		while (start < 1.0) {
			// std::cout << "Startwert: " << start << "r-Parameter: " << r << '\n';

			Logisticmap_float fl(start, r);
			std::cout << "Float, ";
			fl.list_screen_csv(fl.get_long_double_List());

			Logisticmap_Default32squareroot logMap(Default32squareroot::convert_to_Default32squareroot(2, start), Default32squareroot::convert_to_Default32squareroot(2, r));
			std::cout << "squareroot, ";
			logMap.list_screen_csv();
			start += 0.25;
		}
		start = 0.25;
		r += 0.01;
		std::cout << '\n' << '\n';
	}
	*/

	Default32squareroot fl(2);
	Default32squareroot testwert(2, 0, 0, 1);
	std::cout << "Testwert = " << testwert.calcX() << '\n';
	fl = Default32squareroot::convert_to_Default32squareroot(2, testwert.calcX());
	std::cout << "Ergebnis = " << fl.calcX() << '\n';

	fl.printAttributes();

	
	Default32squareroot_test test(2);
	test.test_Default32squareroot_operator_greater();
	
	
	std::cout << '\n' << "End" << '\n';
}
