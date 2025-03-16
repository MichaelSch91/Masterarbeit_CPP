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

//config
bool create_csv = 1;

int main()
{
	std::cout << "Start" << '\n';

	/*
	Zahlenverteilung zahlenverteilung(0.0,4.0,0.001);

	Float16 fl(0, 0, 0);

	zahlenverteilung.berechne_zahlenverteilung(fl);

	zahlenverteilung.print_zahlenverteilung();

	zahlenverteilung.print_zahlenverteilung_csv_format();
	*/

	/*
	Logisticmap_double logisticmap_double;
	std::cout << "Double:" << '\n';
	LogisticmapCalc::list_screen(logisticmap_double.get_long_double_List());
	CSV_data::writeDoubleListToCSV(logisticmap_double.getList());
	*/


	/*
	Float32 fl(0, 0, 0);
	fl.test_Float32_operator_multiply();
	fl.test_Float32_operator_plus();
	fl.test_Float32_operator_minus();


	Float32 fl32 = fl.convert_to_Float32();

	std::cout << fl.calcX() << " = " << fl32.calcX() << '\n';

	Float16 flA(0, 515, 0);
	Float16 flB(0, 3, 30);
	Float16 flC=flA*flB;

	std::cout << "A = " << flA.calcX() << '\n';
	std::cout << "B = " << flB.calcX() << '\n';
	std::cout << "C = " << flC.calcX() << '\n';
	

	Float32 fl(0, 0, 0);
	// fl.test_Float32_operator_multiply();
	// fl.test_Float32_operator_plus();
	// fl.test_Float32_operator_minus();

	Logisticmap_float lm_f;
	std::cout << "Start = " << lm_f.getS() << " r = " << lm_f.getR() << '\n';
	LogisticmapCalc::list_screen(lm_f.get_long_double_List());
	CSV_data::writeFloatListToCSV(lm_f.getList());

	Default32squareroot square = square.convert_to_Default32squareroot(2,3.5);
	std::cout << square.getSign() << ", " << square.getExponent() << ", " << square.getMantissa() << '\n';
	std::cout << square.calcX() << '\n';
	
	*/

	Default32squareroot square = square.convert_to_Default32squareroot(2, 3.5);
	
	Default32squareroot flA(0, 128, 8'000'000);
	Default32squareroot flB(0, 120, 8'000'000);
	Default32squareroot flC = flA + flB;
	std::cout << "Ist: " << '\n';
	flC.printAttributes();

	Default32squareroot result = result.convert_to_Default32squareroot(2,(flA.calcX() + flB.calcX()));
	std::cout << "Soll: " << '\n';
	result.printAttributes();


	//square.test_Default32squareroot_operator_plus_with_conversion();

	/*
	Zahlenverteilung float16(0.0, 1.0, 1024, "float16");
	Zahlenverteilung float32(0.0, 1.0, 1024, "float32");
	Zahlenverteilung sqrtTwo(0.0, 1.0, 1024, "sqrtTwo");
	Zahlenverteilung sqrtTwoOverlapping(0.0, 1.0, 1024, "sqrtTwoOverlapping");

	float16.berechne_zahlenverteilung(Float16(0,0,0));
	float16.print_zahlenverteilung_csv_format();

	float32.berechne_zahlenverteilung(Float32(0, 0, 0));
	float32.print_zahlenverteilung_csv_format();

	sqrtTwo.berechne_zahlenverteilung(Default32squareroot(0, 0, 0));
	sqrtTwo.print_zahlenverteilung_csv_format();

	sqrtTwoOverlapping.berechne_zahlenverteilung(Default32squarerootOverlapping(0, 0, 0));
	sqrtTwoOverlapping.print_zahlenverteilung_csv_format();
	*/

	/*
	// Default32squareroot square(2);
	// square.test_Default32squareroot_convert_to_Default32squareroot();
	// square.test_Default32squareroot_convert_to_Default32squareroot_In_and_Out();

	
	Zahlenverteilung zahlenverteilung(0.0, 4.0, 0.1);
	Default32squareroot square(2,0,0, 0);
	// std::cout << square.calcX()<< '\n';

	// square.test_Default32squareroot_calcX();
	square.test_Default32squareroot_operator_plus();
	// square.test_Default32squareroot_operator_minus();
	// square.test_Default32squareroot_operator_multiply();

	// zahlenverteilung.berechne_zahlenverteilung(square);

	Float32 flx(0, 0, 0);
	// flx.test_Float32_operator_minus();

	Logisticmap_Default32squareroot def_sqrt;
	std::cout << "Start = " << def_sqrt.getS().calcX() << " r = " << def_sqrt.getR().calcX() << '\n';
	LogisticmapCalc::list_screen(def_sqrt.get_long_double_List());
	
	
	// CSV_data::writeDeltaLongDoubleListToCSV_double_float(LogisticmapCalc::abweichungsRechner(fl.get_long_double_List(), lm_f.get_long_double_List()));

	

	//todo: als Funktion in LogisticmapCalc oder Unterklassen einarbeiten
	Logisticmap_float logisticmap_float;

	std::cout << "Float \n r,Startwert,Wert,Iteration(erstes Vorkommen),Iteration(zweites Vorkommen) \n";

	while (logisticmap_float.getR() < 3.99) {
		while (logisticmap_float.getS() < 0.99) {
			logisticmap_float.setList(logisticmap_float.calcNewList());
			//std::cout << "Float, r = " << logisticmap_float.getR() << " Startwert = " << logisticmap_float.getS() << '\n';
			std::cout << logisticmap_float.getR() << ',' << logisticmap_float.getS() << ',';
			LogisticmapCalc::list_screen_csv_format(logisticmap_float.get_long_double_List());
			logisticmap_float.setS(logisticmap_float.getS() + logisticmap_float.getStartStep());
		}
		logisticmap_float.setR(logisticmap_float.getR() + logisticmap_float.getRStep());
		logisticmap_float.setS(0.1);
	}




	Logisticmap_float logisticmap_float;
	Logisticmap_double logisticmap_double;
	Logisticmap_long_double logisticmap_long_double;

	// loop finder / Periodizität
	std::cout << "Float:" << '\n';
	LogisticmapCalc::list_screen(logisticmap_float.get_long_double_List());

	std::cout << "Double:" <<  '\n';
	LogisticmapCalc::list_screen(logisticmap_double.get_long_double_List());

	std::cout << "Long Double:" << '\n';
	LogisticmapCalc::list_screen(logisticmap_long_double.get_long_double_List());

	// Abweichungen / Deltas / Vergleiche:
	std::list<long double> eval_longDouble_double_list = LogisticmapCalc::abweichungsRechner(logisticmap_long_double.get_long_double_List(), logisticmap_double.get_long_double_List());
	std::list<long double> eval_double_float_list = LogisticmapCalc::abweichungsRechner(logisticmap_double.get_long_double_List(), logisticmap_float.get_long_double_List());

	// CSV-Dateien erstellen
	if (create_csv) {
		std::cout << "CSV-Dateien werden erstellt.";
		CSV_data::writeFloatListToCSV(logisticmap_float.getList());
		CSV_data::writeDoubleListToCSV(logisticmap_double.getList());
		CSV_data::writeLongDoubleListToCSV(logisticmap_long_double.getList());
		CSV_data::writeDeltaLongDoubleListToCSV(eval_longDouble_double_list);
		CSV_data::writeDeltaLongDoubleListToCSV_double_float(eval_double_float_list);
	}else {
		std::cout << "Es wurden keine CSV-Dateien erstellt.";
	}
	*/



	std::cout << '\n' << "End" << '\n';
}
