#ifndef LOGISTICMAP_DEFAULT32SQUAREROOT_H
#define LOGISTICMAP_DEFAULT32SQUAREROOT_H

#include "LogisticmapCalc.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Default32squareroot.h"

class Logisticmap_Default32squareroot : public LogisticmapCalc {
public:
    Logisticmap_Default32squareroot();

    Logisticmap_Default32squareroot(Default32squareroot start, Default32squareroot parmeter_r);


    Default32squareroot getS();

    Default32squareroot getR();

    std::list<Default32squareroot> getList();

    std::list<long double> get_long_double_List();

    std::list<Default32squareroot> calcNewList();

    void setList(std::list<Default32squareroot> newList);

    void calcLongDoubleList();

    void print_list();

    void list_screen();
    static std::tuple<bool, Default32squareroot, int, int> list_screen_duplicates(std::list<Default32squareroot> list);
    int search_first_occurrence(std::list<Default32squareroot> list, Default32squareroot value);


private:
    std::list<Default32squareroot> list;
    std::list<long double> long_double_list;

    Default32squareroot s;
    Default32squareroot r;

    // mit Startwert s
    std::list<Default32squareroot> logistischeAbbildungDefault32squareroot();

    Default32squareroot logistischeAbbildungRechnerDefault32squareroot(Default32squareroot x, Default32squareroot r);

    std::list<long double> cast_list(std::list<Default32squareroot> Default32squarerootList);
};
#endif