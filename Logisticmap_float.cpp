#include "Logisticmap_float.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

Logisticmap_float::Logisticmap_float() {
	this->list = logistischeAbbildungFloat();
	this->long_double_list = cast_list(this->list);
}

std::list<float> Logisticmap_float::getList() {
	return this->list;
}

void Logisticmap_float::setList(std::list<float> newList) {
	this->list = newList;
	this->calcLongDoubleList();
}

std::list<float> Logisticmap_float::calcNewList() {
	return this->logistischeAbbildungFloat();
}

std::list<long double> Logisticmap_float::get_long_double_List() {
	return this->long_double_list;
}

void Logisticmap_float::calcLongDoubleList() {
	this->long_double_list = this->cast_list(this->getList());
}

std::list<float> Logisticmap_float::logistischeAbbildungFloat() {
	float x = this->s;
	std::list<float> list = { x };
	for (int j = 0; j <= i; j++) {
		list.push_back(logistischeAbbildungRechnerFloat(x, this->r)); // Übergabe von this->r statt Aufruf mit this in Methode, weil sonst Datentyp aus Klasse LogisticMap übergeben wird.
		x = list.back();
		// std::cout << x << '\n';
	}
	return list;
}

// Aufgegliedert in die unterschiedlichen Datentypen ...Float, ...Double, ...LongDouble, da der Compiler zwar die Methode 
// anhand der Parameter auswählt, aber auch automatisch typecasts durchführt. Um sicher zu gehen, dass die richtige Methode 
// mit den richtigen Parameter-Datentypen aufgerufen wird, wurde dieser etwas umständliche, aber (datentyp-)sicherer Umweg gewählt.
float Logisticmap_float::logistischeAbbildungRechnerFloat(float x, float r) {
	return r * x * (1 - x);
}

std::list<long double> Logisticmap_float::cast_list(std::list<float> floatList) {
	std::list<long double> list = {};
	for (float d : floatList) {
		list.push_back(d);
	}
	return list;
}

