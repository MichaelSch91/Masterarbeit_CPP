#include "Logisticmap_float16.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>
#include "Float16.h"

Logisticmap_float16::Logisticmap_float16() {
	this->list = logistischeAbbildungFloat16();
	this->long_double_list = cast_list(this->list);
}

Logisticmap_float16::Logisticmap_float16(double s, double r) {
	this->s = Float16::convert_to_Float16(s);
	this->r = Float16::convert_to_Float16(r);
	//this->s.printAttributes();
	//this->r.printAttributes();
	this->list = logistischeAbbildungFloat16();
	this->long_double_list = cast_list(this->list);
}

std::list<Float16> Logisticmap_float16::getList() {
	return this->list;
}
std::list<long double> Logisticmap_float16::get_long_double_List() {
	return this->long_double_list;
}

Float16 Logisticmap_float16::getS() {
	return this->s;
}

Float16 Logisticmap_float16::getR() {
	return this->r;
}

std::list<Float16> Logisticmap_float16::calcNewList() {
	return this->logistischeAbbildungFloat16();
}

void Logisticmap_float16::setList(std::list<Float16> newList) {
	this->list = newList;
	this->calcLongDoubleList();
}

void Logisticmap_float16::calcLongDoubleList() {
	this->long_double_list = this->cast_list(this->getList());
}

// mit Startwert s
std::list<Float16> Logisticmap_float16::logistischeAbbildungFloat16() {
	// std::cout << "s = " << this->getS().calcX() << " r = " << this->getR().calcX() << '\n';
	Float16 x = this->s;
	std::list<Float16> list = { x };
	for (int j = 0; j <= this->i; j++) {
		// std::cout << "x = " << x.calcX() << " r = " << this->getR().calcX() << '\n';
		list.push_back(logistischeAbbildungRechnerFloat16(x, this->r));
		// std::cout << list.back() << '\n';
		x = list.back();
		// std::cout << x.calcX() << '\n';
	}
	return list;
}

Float16 Logisticmap_float16::logistischeAbbildungRechnerFloat16(Float16 x, Float16 r) {
	// std::cout << "r*x*(1-x) =  " << this->getR().calcX() << " * " << x.calcX() << " * ( " << Float16(0, 127, 0).calcX() << " - " << x.calcX() << ")" << '\n';
	// std::cout << "Double r*x*(1-x) =  " << this->getR().calcX()*x.calcX()*(Float16(0, 127, 0).calcX()-x.calcX()) << '\n';
	// std::cout << "Double (1-x) =  " << (Float16(0, 127, 0).calcX() - x.calcX())<< " Float16 (1-x) = " << (Float16(0, 127, 0)-x).calcX() << '\n';
	// std::cout << "Double r*x =  " << this->getR().calcX() * x.calcX() << " Float16 r*x = " << (this->getR() * x).calcX() << '\n';

	// std::cout << "x = " << (r * x * (Float16(0, 15, 0) - x)).calcX() << '\n';
	return r * x * (Float16(0, 15, 0) - x);
}

std::list<long double> Logisticmap_float16::cast_list(std::list<Float16> Float16List) {
	std::list<long double> list = {};
	for (Float16 d : Float16List) {
		list.push_back(d.calcX());
	}
	return list;
}

void Logisticmap_float16::list_screen(std::list<Float16> checked_list) {
	std::list<Float16> list(checked_list);
	std::tuple<bool, Float16, int, int> tuple = list_screen_duplicates(list);
	if (std::get<0>(tuple)) {
		std::cout << "Liste hat Wert doppelt: " << std::get<1>(tuple).calcX() << " bei " << std::get<2>(tuple) << " und " << std::get<3>(tuple) << " iterations." << '\n';;
	}
	else {
		std::cout << "Liste hat keinen Wert doppelt" << '\n';
	}
}

// Tupel: <hat Dopplung, Wert der ersten Dopplung, Iteration erstes Vorkommen, Iteration zweites Vorkommen>
std::tuple<bool, Float16, int, int> Logisticmap_float16::list_screen_duplicates(std::list<Float16> list) {
	int iteration_i = 0;
	int iteration_j = 0;
	Float16 value(0, 0, 0);
	bool has_duplicate = 0;
	int first_iteration = 0;
	int last_iteration = 0;

	for (Float16 obj_i : list) {
		for (Float16 obj_j : list) {
			if (obj_i == obj_j) {
				value = obj_i;
				has_duplicate = 1;
				first_iteration = iteration_i;
				last_iteration = iteration_j;
				break;
			}
			iteration_j++;
		}
		if (has_duplicate) {
			break;
		}
	}
	/*
	if (has_duplicate) {
		first_iteration = search_first_occurrence(list, value);
	}
	*/
	return std::tuple<bool, Float16, int, int>(has_duplicate, value, first_iteration, last_iteration);
}

int Logisticmap_float16::search_first_occurrence(std::list<Float16> list, Float16 value) {
	int iteration = 0;
	for (Float16 obj : list) {
		if (obj == value) {
			return iteration;
		}
		iteration++;
	}
}