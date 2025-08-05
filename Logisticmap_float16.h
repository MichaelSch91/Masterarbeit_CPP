#ifndef LOGISTICMAP_FLOAT16_H
#define LOGISTICMAP_FLOAT16_H

#include "LogisticmapCalc.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Float16.h"

class Logisticmap_float16 : public LogisticmapCalc {
public:
    Logisticmap_float16();

    Logisticmap_float16(double s, double r);

    Float16 getS();

    Float16 getR();

    std::list<Float16> getList();

    std::list<long double> get_long_double_List();

    std::list<Float16> calcNewList();

    void setList(std::list<Float16> newList);

    void calcLongDoubleList();

    void list_screen(std::list<Float16> checked_list);
    std::tuple<bool, Float16, int, int> list_screen_duplicates(std::list<Float16> list);
    int search_first_occurrence(std::list<Float16> list, Float16 value);


private:
    std::list<Float16> list;
    std::list<long double> long_double_list;

    Float16 s = Float16(0, 123, 5033165);
    Float16 r = Float16(0, 128, 7969178);

    // mit Startwert s
    std::list<Float16> logistischeAbbildungFloat16();

    Float16 logistischeAbbildungRechnerFloat16(Float16 x, Float16 r);

    std::list<long double> cast_list(std::list<Float16> Float16List);
};
#endif#pragma once
