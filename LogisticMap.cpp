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

	double start = 0.25;
	double r = 3.98;

	Logisticmap_float fl(start,r);
	LogisticmapCalc::list_screen(fl.get_long_double_List());


	Logisticmap_Default32squareroot logMap(Default32squareroot::convert_to_Default32squareroot(2, start), Default32squareroot::convert_to_Default32squareroot(2, r));
	logMap.list_screen();

	std::cout << '\n' << "End" << '\n';
}
