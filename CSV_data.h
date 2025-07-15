#ifndef CSV_DATA_H
#define CSV_DATA_H

#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <cmath>
#include "Logisticmap_Default32squareroot.h"

class CSV_data {
public:
    static void writeDefault32SquareRootListAsCalcXToCSV(Logisticmap_Default32squareroot d32s);

    static void writeFloatListToCSV(std::list<float> list);

    static void writeDoubleListToCSV(std::list<double> list);

    static void writeDoubleListToCSV(std::list<long double> list);

    static void writeLongDoubleListToCSV(std::list<long double> list);

    static void writeDeltaLongDoubleListToCSV(std::list<long double> list);

    static void writeDeltaLongDoubleListToCSV_double_float(std::list<long double> list);
};
#endif