#ifndef LOGISTICMAP_FLOAT_H
#define LOGISTICMAP_FLOAT_H

#include "LogisticmapCalc.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>


class Logisticmap_float : public LogisticmapCalc {
public:
    Logisticmap_float();

    Logisticmap_float(double start, double r);

    std::list<float> getList();

    void setList(std::list<float> newList);

    std::list<float> calcNewList();

    std::list<long double> get_long_double_List();

    void calcLongDoubleList();

private:
    std::list<float> list;
    std::list<long double> long_double_list;

    std::list<float> logistischeAbbildungFloat();

    // Aufgegliedert in die unterschiedlichen Datentypen ...Float, ...Double, ...LongDouble, da der Compiler zwar die Methode 
    // anhand der Parameter auswählt, aber auch automatisch typecasts durchführt. Um sicher zu gehen, dass die richtige Methode 
    // mit den richtigen Parameter-Datentypen aufgerufen wird, wurde dieser etwas umständliche, aber (datentyp-)sicherer Umweg gewählt.
    float logistischeAbbildungRechnerFloat(float x, float r);

    std::list<long double> cast_list(std::list<float> floatList);
};
#endif