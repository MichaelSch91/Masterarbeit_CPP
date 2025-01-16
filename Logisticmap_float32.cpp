#include "Logisticmap_float32.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>
#include "Float32.h"

Logisticmap_float32::Logisticmap_float32() {
	this->list = logistischeAbbildungFloat32();
	this->long_double_list = cast_list(this->list);
}

std::list<Float32> Logisticmap_float32::getList() {
	return this->list;
}
std::list<long double> Logisticmap_float32::get_long_double_List() {
	return this->long_double_list;
}

Float32 Logisticmap_float32::getS() {
	return this->s;
}

Float32 Logisticmap_float32::getR() {
	return this->r;
}

std::list<Float32> Logisticmap_float32::calcNewList() {
	return this->logistischeAbbildungFloat32();
}

void Logisticmap_float32::setList(std::list<Float32> newList) {
	this->list = newList;
	this->calcLongDoubleList();
}

void Logisticmap_float32::calcLongDoubleList() {
	this->long_double_list = this->cast_list(this->getList());
}

// mit Startwert s
std::list<Float32> Logisticmap_float32::logistischeAbbildungFloat32() {
	// std::cout << "s = " << this->getS().calcX() << " r = " << this->getR().calcX() << '\n';
	Float32 x = this->s;
	std::list<Float32> list = { x };
	for (int j = 0; j <= this->i; j++) {
		// std::cout << "x = " << x.calcX() << " r = " << this->getR().calcX() << '\n';
		list.push_back(logistischeAbbildungRechnerFloat32(x, this->r));
		// std::cout << list.back() << '\n';
		x = list.back();
		// std::cout << x.calcX() << '\n';
	}
	return list;
}

Float32 Logisticmap_float32::logistischeAbbildungRechnerFloat32(Float32 x, Float32 r) {
	// std::cout << "r*x*(1-x) =  " << this->getR().calcX() << " * " << x.calcX() << " * ( " << Float32(0, 127, 0).calcX() << " - " << x.calcX() << ")" << '\n';
	// std::cout << "Double r*x*(1-x) =  " << this->getR().calcX()*x.calcX()*(Float32(0, 127, 0).calcX()-x.calcX()) << '\n';
	// std::cout << "Double (1-x) =  " << (Float32(0, 127, 0).calcX() - x.calcX())<< " Float32 (1-x) = " << (Float32(0, 127, 0)-x).calcX() << '\n';
	// std::cout << "Double r*x =  " << this->getR().calcX() * x.calcX() << " Float32 r*x = " << (this->getR() * x).calcX() << '\n';


	return r * x * (Float32(0,127,0) - x);
}

std::list<long double> Logisticmap_float32::cast_list(std::list<Float32> Float32List) {
	std::list<long double> list = {};
	for (Float32 d : Float32List) {
		list.push_back(d.calcX_long_double());
	}
	return list;
}

void Logisticmap_float32::list_screen(std::list<Float32> checked_list) {
	std::list<Float32> list(checked_list);
	std::tuple<bool, Float32, int, int> tuple = list_screen_duplicates(list);
	if (std::get<0>(tuple)) {
		std::cout << "Liste hat Wert doppelt: " << std::get<1>(tuple).calcX() << " bei " << std::get<2>(tuple) << " und " << std::get<3>(tuple) << " iterations." << '\n';;
	}
	else {
		std::cout << "Liste hat keinen Wert doppelt" << '\n';
	}
}

// Tupel: <hat Dopplung, Wert der ersten Dopplung, Iteration erstes Vorkommen, Iteration zweites Vorkommen>
std::tuple<bool, Float32, int, int> Logisticmap_float32::list_screen_duplicates(std::list<Float32> list) {
	int iteration_i = 0;
	int iteration_j = 0;
	Float32 value(0,0,0);
	bool has_duplicate = 0;
	int first_iteration = 0;
	int last_iteration = 0;

	for (Float32 obj_i : list) {
		for (Float32 obj_j : list) {
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
	return std::tuple<bool, Float32, int, int>(has_duplicate, value, first_iteration, last_iteration);
}

int Logisticmap_float32::search_first_occurrence(std::list<Float32> list, Float32 value) {
	int iteration = 0;
	for (Float32 obj : list) {
		if (obj == value) {
			return iteration;
		}
		iteration++;
	}
}