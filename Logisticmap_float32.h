#ifndef LOGISTICMAP_FLOAT32_H
#define LOGISTICMAP_FLOAT32_H

#include "LogisticmapCalc.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Float32.h"

class Logisticmap_float32 : public LogisticmapCalc {
public:
    Logisticmap_float32();

    Float32 getS();

    Float32 getR();

    std::list<Float32> getList();

    std::list<long double> get_long_double_List();

    std::list<Float32> calcNewList();

    void setList(std::list<Float32> newList);

    void calcLongDoubleList();
    
    void list_screen(std::list<Float32> checked_list);
    std::tuple<bool, Float32, int, int> list_screen_duplicates(std::list<Float32> list);
    int search_first_occurrence(std::list<Float32> list, Float32 value);


private:
    std::list<Float32> list;
    std::list<long double> long_double_list;

    Float32 s = Float32(0,123, 5033165);
    Float32 r = Float32(0, 128, 7969178);

    // mit Startwert s
    std::list<Float32> logistischeAbbildungFloat32();

    Float32 logistischeAbbildungRechnerFloat32(Float32 x, Float32 r);

    std::list<long double> cast_list(std::list<Float32> Float32List);
};
#endif