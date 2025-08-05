#ifndef LOGISTICMAP_DOUBLE_H
#define LOGISTICMAP_DOUBLE_H

#include "LogisticmapCalc.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

class Logisticmap_double : public LogisticmapCalc {
public:
    Logisticmap_double();

    Logisticmap_double(double start, double r);

    std::list<double> getList();

    std::list<long double> get_long_double_List();

    std::list<double> calcNewList();

    void setList(std::list<double> newList);

    void calcLongDoubleList();

private:
    std::list<double> list;
    std::list<long double> long_double_list;

    // mit Startwert s
    std::list<double> logistischeAbbildungDouble();

    double logistischeAbbildungRechnerDouble(double x, double r);

    std::list<long double> cast_list(std::list<double> doubleList);
};
#endif