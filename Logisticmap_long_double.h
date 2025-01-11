#ifndef LOGISTICMAP_LONG_DOUBLE_H
#define LOGISTICMAP_LONG_DOUBLE_H

#include "LogisticmapCalc.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

class Logisticmap_long_double : public LogisticmapCalc {
public:
    Logisticmap_long_double();

    std::list<long double> getList();

    std::list<long double> get_long_double_List();

    std::list<long double> calcNewList();

    void setList(std::list<long double> newList);

    void calcLongDoubleList();

private:
    std::list<long double> list;
    std::list<long double> long_double_list;

    // mit Startwert s
    std::list<long double> logistischeAbbildungLongDouble();

    long double logistischeAbbildungRechnerLongDouble(long double x, long double r);
};
#endif