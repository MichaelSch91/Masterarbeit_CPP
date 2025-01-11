#include "Logisticmap_long_double.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

Logisticmap_long_double::Logisticmap_long_double() {
        this->list = logistischeAbbildungLongDouble();
        this->long_double_list = this->list; // ggf. copy sinnvoller, aber Verweis schneller
    }

    std::list<long double> Logisticmap_long_double::getList() {
        return this->list;
    }
    std::list<long double> Logisticmap_long_double::get_long_double_List() {
        return this->long_double_list;
    }

    std::list<long double> Logisticmap_long_double::calcNewList() {
        return this->logistischeAbbildungLongDouble();
    }

    void Logisticmap_long_double::setList(std::list<long double> newList) {
        this->list = newList;
        this->calcLongDoubleList();
    }

    void Logisticmap_long_double::calcLongDoubleList() {
        this->long_double_list = this->getList();
    }

    // mit Startwert s
    std::list<long double> Logisticmap_long_double::logistischeAbbildungLongDouble() {
        long double x = this->s;
        std::list<long double> list = { x };
        for (int j = 0; j <= this->i; j++) {
            list.push_back(logistischeAbbildungRechnerLongDouble(x, this->r));
            x = list.back();
            // std::cout << x << '\n';
        }
        return list;
    }

    long double Logisticmap_long_double::logistischeAbbildungRechnerLongDouble(long double x, long double r) {
        return r * x * (1 - x);
    }