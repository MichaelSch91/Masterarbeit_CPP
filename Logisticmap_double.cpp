#include "Logisticmap_double.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

Logisticmap_double::Logisticmap_double() {
	this->list = logistischeAbbildungDouble();
	this->long_double_list = cast_list(this->list);
}

Logisticmap_double::Logisticmap_double(double start, double r) {
	this->setS(start);
	this->setR(r);
	this->list = logistischeAbbildungDouble();
	this->long_double_list = cast_list(this->list);
}

std::list<double> Logisticmap_double::getList() {
	return this->list;
}
std::list<long double> Logisticmap_double::get_long_double_List() {
	return this->long_double_list;
}

std::list<double> Logisticmap_double::calcNewList() {
	return this->logistischeAbbildungDouble();
}

void Logisticmap_double::setList(std::list<double> newList) {
	this->list = newList;
	this->calcLongDoubleList();
}

void Logisticmap_double::calcLongDoubleList() {
	this->long_double_list = this->cast_list(this->getList());
}

// mit Startwert s
std::list<double> Logisticmap_double::logistischeAbbildungDouble() {
	double x = this->s;
	std::list<double> list = { x };
	for (int j = 0; j <= this->i; j++) {
		list.push_back(logistischeAbbildungRechnerDouble(x, this->r));
		// std::cout << list.back() << '\n';
		x = list.back();
		// std::cout << x << '\n';
	}
	return list;
}

double Logisticmap_double::logistischeAbbildungRechnerDouble(double x, double r) {
	return r * x * (1 - x);
}

std::list<long double> Logisticmap_double::cast_list(std::list<double> doubleList) {
	std::list<long double> list = {};
	for (double d : doubleList) {
		list.push_back(d);
	}
	return list;
}