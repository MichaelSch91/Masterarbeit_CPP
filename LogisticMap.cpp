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


	Default32squareroot square = square.convert_to_Default32squareroot(2, 3.5);
	
	Default32squareroot flA(0, 51, 567663);
	Default32squareroot flB(0, 99, 2770307);
	Default32squareroot flC = flA + flB;
	std::cout << "Ist: " << '\n';
	flC.printAttributes();

	Default32squareroot result = result.convert_to_Default32squareroot(2,(flA.calcX() * flB.calcX()));
	std::cout << "Soll: " << '\n';
	result.printAttributes();

	Default32squareroot_test test(2);
	test.test_Default32squareroot_operator_multiply_with_conversion();



	std::cout << '\n' << "End" << '\n';
}
