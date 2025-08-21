#include "Logisticmap_Default32squareroot.h"

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>
#include "Default32squareroot.h"
#include <iomanip>

Logisticmap_Default32squareroot::Logisticmap_Default32squareroot(): s(Default32squareroot::convert_to_Default32squareroot(2,0.1)), r(Default32squareroot::convert_to_Default32squareroot(2, 3.9)) {
	this->list = logistischeAbbildungDefault32squareroot();
	this->long_double_list = cast_list(this->list);
}

Logisticmap_Default32squareroot::Logisticmap_Default32squareroot(Default32squareroot start, Default32squareroot parmeter_r) : s(start), r(parmeter_r) {
	this->list = logistischeAbbildungDefault32squareroot();
	this->long_double_list = cast_list(this->list);
};

template <typename T>
std::vector<T> listToVector(const std::list<T>& inputList) {
	std::vector<T> resultVector(inputList.begin(), inputList.end());
	return resultVector;
}

std::list<Default32squareroot> Logisticmap_Default32squareroot::getList() {
	return this->list;
}
std::list<long double> Logisticmap_Default32squareroot::get_long_double_List() {
	return this->long_double_list;
}

Default32squareroot Logisticmap_Default32squareroot::getS() {
	return this->s;
}

Default32squareroot Logisticmap_Default32squareroot::getR() {
	return this->r;
}

std::list<Default32squareroot> Logisticmap_Default32squareroot::calcNewList() {
	return this->logistischeAbbildungDefault32squareroot();
}

void Logisticmap_Default32squareroot::setList(std::list<Default32squareroot> newList) {
	this->list = newList;
	this->calcLongDoubleList();
}

void Logisticmap_Default32squareroot::calcLongDoubleList() {
	this->long_double_list = this->cast_list(this->getList());
}

// mit Startwert s
std::list<Default32squareroot> Logisticmap_Default32squareroot::logistischeAbbildungDefault32squareroot() {
	// std::cout << "s = " << this->getS().calcX() << " r = " << this->getR().calcX() << '\n';
	Default32squareroot x = this->s;
	std::list<Default32squareroot> list = { x };
	for (int j = 0; j <= this->i; j++) {
		// std::cout << "x = " << x.calcX() << " r = " << this->getR().calcX() << '\n';
		list.push_back(logistischeAbbildungRechnerDefault32squareroot(x, this->r));
		// std::cout << list.back() << '\n';
		x = list.back();
		// std::cout << x.calcX() << '\n';
		// x.printAttributes();

	}
	return list;
}

Default32squareroot Logisticmap_Default32squareroot::logistischeAbbildungRechnerDefault32squareroot(Default32squareroot x, Default32squareroot r) {
	// std::cout << "r*x*(1-x) =  " << this->getR().calcX() << " * " << x.calcX() << " * ( " << Default32squareroot(0, 127, 0).calcX() << " - " << x.calcX() << ")" << '\n';
	// std::cout << "Double r*x*(1-x) =  " << this->getR().calcX()*x.calcX()*(Default32squareroot(0, 127, 0).calcX()-x.calcX()) << '\n';
	// std::cout << "Double (1-x) =  " << (Default32squareroot(0, 127, 0).calcX() - x.calcX())<< " Default32squareroot (1-x) = " << (Default32squareroot(0, 127, 0)-x).calcX() << '\n';
	// std::cout << "Double r*x =  " << this->getR().calcX() * x.calcX() << " Default32squareroot r*x = " << (this->getR() * x).calcX() << '\n';


	return r * x * (Default32squareroot(0, 127, 0) - x);
}

std::list<long double> Logisticmap_Default32squareroot::cast_list(std::list<Default32squareroot> Default32squarerootList) {
	std::list<long double> list = {};
	for (Default32squareroot d : Default32squarerootList) {
		list.push_back(d.calcX_long_double());
	}
	return list;
}

void Logisticmap_Default32squareroot::list_screen() {
	std::tuple<bool, Default32squareroot, int, int> tuple = list_screen_duplicates(this->getList());
	if (std::get<0>(tuple)) {
		std::cout << "Liste hat Wert doppelt: " << std::get<1>(tuple).calcX() << " bei " << std::get<2>(tuple) << " und " << std::get<3>(tuple) << " iterations." << '\n';;
	}
	else {
		std::cout << "Liste hat keinen Wert doppelt" << '\n';
	}
}

void Logisticmap_Default32squareroot::list_screen_csv() {
	std::tuple<bool, Default32squareroot, int, int> tuple = list_screen_duplicates(this->getList());
	if (std::get<0>(tuple)) {
		// start, r, X, erstes Vorkommen, zweites Vorkommen
		std::cout << this->getS().calcX() << ", " << this->getR().calcX() << ", " << std::get<1>(tuple).calcX() << ", " << std::get<2>(tuple) << ", " << std::get<3>(tuple)  << '\n';
	}
	else {
		std::cout << this->getS().calcX() << ", " << this->getR().calcX() << ", " << "Liste hat keinen Wert doppelt" << '\n';
	}
}

// Tupel: <hat Dopplung, Wert der ersten Dopplung, Iteration erstes Vorkommen, Iteration zweites Vorkommen>
std::tuple<bool, Default32squareroot, int, int> Logisticmap_Default32squareroot::list_screen_duplicates(std::list<Default32squareroot> list) {
	int iteration_i = 0;
	int iteration_j = 0;
	Default32squareroot value(0, 0, 0);
	bool has_duplicate = 0;
	int first_iteration = 0;
	int last_iteration = 0;

	std::vector<Default32squareroot> vectorlist = listToVector(list);

	for (int i = 0; i < vectorlist.size()-1; i++) {
		for (int j = i+1; j < vectorlist.size(); j++) {
			if (vectorlist[i] == vectorlist[j]) {
				value = vectorlist[i];
				has_duplicate = 1;
				first_iteration = i;
				last_iteration = j;
				break;
			}
		}
		if (has_duplicate) {
			break;
		}
	}
	return std::tuple<bool, Default32squareroot, int, int>(has_duplicate, value, first_iteration, last_iteration);
}

int Logisticmap_Default32squareroot::search_first_occurrence(std::list<Default32squareroot> list, Default32squareroot value) {
	int iteration = 0;
	for (Default32squareroot obj : list) {
		if (obj == value) {
			return iteration;
		}
		iteration++;
	}
}

void Logisticmap_Default32squareroot::print_list() {
	std::cout << "Print list:" << '\n';
	int counter = 0;
	for (Default32squareroot i : this->getList()) {
		std::cout << counter << ": ";
		i.printAttributes();
		counter++;
	}

	std::cout << "End" << '\n';
}

