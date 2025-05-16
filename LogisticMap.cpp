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

void zeitmessung_converter_steps(double konvertierenderWert, int schritte) {
	auto start = std::chrono::high_resolution_clock::now();

	Default32squareroot::convert_to_Default32squareroot(2, konvertierenderWert, schritte);

	auto ende = std::chrono::high_resolution_clock::now();

	std::cout << "Testwert = " << konvertierenderWert << " Ergebnis = " << Default32squareroot::convert_to_Default32squareroot(2, konvertierenderWert, schritte).calcX() << '\n';
	Default32squareroot::convert_to_Default32squareroot(2, konvertierenderWert, schritte).printAttributes();

	auto dauer = std::chrono::duration_cast<std::chrono::milliseconds>(ende - start);


	std::cout << "Schritte: " << schritte << " Die Ausfuehrung der Methode dauerte: " << dauer.count() << " Millisekunden." << std::endl;
}

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
	

	Default32squareroot fl(2);
	Default32squareroot testwert(2, 1, 0, 1);
	std::cout << "Testwert = " << testwert.calcX() << '\n';
	fl = Default32squareroot::convert_to_Default32squareroot(2, testwert.calcX());
	std::cout << "Ergebnis = " << fl.calcX() << '\n';

	fl.printAttributes();
	*/

	zeitmessung_converter_steps(1.2, 100);
	zeitmessung_converter_steps(1.2, 1);


	Default32squareroot::convert_to_Default32squareroot(2, 50.0).printAttributes();

	// Alternativ: std::chrono::milliseconds, std::chrono::nanoseconds, etc.
	// Alternativ für Millisekunden:
	// auto dauer_ms = std::chrono::duration_cast<std::chrono::milliseconds>(ende - start);
	// std::cout << "Die Ausführung von meineMethode dauerte: "
	//           << dauer_ms.count() << " Millisekunden." << std::endl;
	
	
	std::cout << '\n' << "End" << '\n';
}

