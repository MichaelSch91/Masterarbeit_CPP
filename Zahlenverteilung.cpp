#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "Zahlenverteilung.h"
#include "Zahlendarstellung.h"
#include "Float16.h"
#include "Float32.h"
#include "ExperimentalDefault.h"
#include "Default32squareroot.h"
#include <cassert>
#include <string>


Zahlenverteilung::Zahlenverteilung(double min, double max, double st, std::string name){
	this->name = name;
	this->minimum = min;
	this->maximum = max;
	this->steps = st;
	this->list_klassen = this->berechne_klassen();
	};

Zahlenverteilung::Zahlenverteilung(double min, double max, int klassen, std::string name) {
	this->name = name;
	this->minimum = min;
	this->maximum = max;
	this->steps = (max - min) / klassen;
	this->list_klassen = this->berechne_klassen();
	assert(this->list_klassen.size() == klassen);
};

std::vector<double> Zahlenverteilung::getList_klassen() {
	return this->list_klassen;
}

// wegen Performanz alles in einer Methode
void Zahlenverteilung::berechne_zahlenverteilung(Zahlendarstellung fl) {
	std::cout << "Berechnung Zahlenverteilung Start" << '\n';
	init_list_zahlenverteilung();
	double x = 0.0;

	int max_exponent = pow(fl.getBase(), fl.getExponent_bits());
	int max_mantissa = pow(fl.getBase(), fl.getMantissa_bits());

	while (fl.getExponent() < max_exponent) {
		while (fl.getMantissa() < max_mantissa) {
			x = fl.calcX();
			if (x > this->maximum) {
				break;
			}
			// std::cout << "x: " << x << '\n';
			for (int i = 0; i < this->list_zahlenverteilung.size();i++) {
				// std::cout << "checking ob zwischen: " << this->list_klassen[i] << " und " << this->list_klassen[i + 1] << '\n';
				if ((x >= this->list_klassen[i]) and (x < this->list_klassen[i + 1])) {
					this->list_zahlenverteilung[i]++;
					//std::cout << "Listenwert: " << this->list_zahlenverteilung[i] << '\n';
				}
			}
			fl.setMantissa(fl.getMantissa() + 1);
		}
		std::cout << "Exponent: " << fl.getExponent() << '\n';
		// this->print_zahlenverteilung();
		fl.setExponent(fl.getExponent() + 1);
		fl.setMantissa(0);
	}
	std::cout << "Liste Zahlenverteilung erstellt" << '\n';
}

// wegen Performanz alles in einer Methode
void Zahlenverteilung::berechne_zahlenverteilung(Float16 fl) {
	std::cout << "Berechnung Zahlenverteilung Start" << '\n';
	init_list_zahlenverteilung();
	double x = 0.0;

	int max_exponent = pow(fl.getBase(), fl.getExponent_bits());
	int max_mantissa = pow(fl.getBase(), fl.getMantissa_bits());

	while (fl.getExponent() < max_exponent) {
		while (fl.getMantissa() < max_mantissa) {
			x = fl.calcX();
			if (x > this->maximum) {
				break;
			}
			// std::cout << "x: " << x << '\n';
			for (int i = 0; i < this->list_zahlenverteilung.size(); i++) {
				// std::cout << "checking ob zwischen: " << this->list_klassen[i] << " und " << this->list_klassen[i + 1] << '\n';
				if ((x >= this->list_klassen[i]) and (x < this->list_klassen[i + 1])) {
					this->list_zahlenverteilung[i]++;
					//std::cout << "Listenwert: " << this->list_zahlenverteilung[i] << '\n';
				}
			}
			fl.setMantissa(fl.getMantissa() + 1);
		}
		std::cout << "Exponent: " << fl.getExponent() << '\n';
		// this->print_zahlenverteilung();
		fl.setExponent(fl.getExponent() + 1);
		fl.setMantissa(0);
	}
	std::cout << "Liste Zahlenverteilung erstellt" << '\n';
}

// wegen Performanz alles in einer Methode
void Zahlenverteilung::berechne_zahlenverteilung(Float32 fl) {
	std::cout << "Berechnung Zahlenverteilung Start" << '\n';
	init_list_zahlenverteilung();
	double x = 0.0;

	int max_exponent = pow(fl.getBase(), fl.getExponent_bits());
	int max_mantissa = pow(fl.getBase(), fl.getMantissa_bits());

	while (fl.getExponent() < max_exponent) {
		while (fl.getMantissa() < max_mantissa) {
			x = fl.calcX();
			if (x > this->maximum) {
				break;
			}
			// std::cout << "x: " << x << '\n';
			for (int i = 0; i < this->list_zahlenverteilung.size(); i++) {
				// std::cout << "checking ob zwischen: " << this->list_klassen[i] << " und " << this->list_klassen[i + 1] << '\n';
				if ((x >= this->list_klassen[i]) and (x < this->list_klassen[i + 1])) {
					this->list_zahlenverteilung[i]++;
					//std::cout << "Listenwert: " << this->list_zahlenverteilung[i] << '\n';
				}
			}
			fl.setMantissa(fl.getMantissa() + 1);
		}
		std::cout << "Exponent: " << fl.getExponent() << '\n';
		// this->print_zahlenverteilung();
		fl.setExponent(fl.getExponent() + 1);
		fl.setMantissa(0);
	}
	std::cout << "Liste Zahlenverteilung erstellt" << '\n';
}

// wegen Performanz alles in einer Methode
void Zahlenverteilung::berechne_zahlenverteilung(ExperimentalDefault fl) {
	std::cout << "Berechnung Zahlenverteilung Start" << '\n';
	init_list_zahlenverteilung();
	long double x = 0.0;

	long long max_exponent = pow(fl.getBase(), fl.getExponent_bits());
	long long max_mantissa = pow(fl.getBase(), fl.getMantissa_bits());

	while (fl.getExponent() < max_exponent) {
		while (fl.getMantissa() < max_mantissa) {
			x = fl.calcX();
			if (x > this->maximum) {
				break;
			}
			// std::cout << "x: " << x << '\n';
			for (int i = 0; i < this->list_zahlenverteilung.size(); i++) {
				// std::cout << "checking ob zwischen: " << this->list_klassen[i] << " und " << this->list_klassen[i + 1] << '\n';
				if ((x >= this->list_klassen[i]) and (x < this->list_klassen[i + 1])) {
					this->list_zahlenverteilung[i]++;
					//std::cout << "Listenwert: " << this->list_zahlenverteilung[i] << '\n';
				}
			}
			fl.setMantissa(fl.getMantissa() + 1);
		}
		std::cout << "Exponent: " << fl.getExponent() << '\n';
		this->print_zahlenverteilung();
		fl.setExponent(fl.getExponent() + 1);
		fl.setMantissa(0);
	}
	std::cout << "Liste Zahlenverteilung erstellt" << '\n';
}

// wegen Performanz alles in einer Methode
void Zahlenverteilung::berechne_zahlenverteilung(Default32squareroot fl) {
	std::cout << "Berechnung Zahlenverteilung Start" << '\n';
	init_list_zahlenverteilung();
	double x = 0.0;

	int max_exponent = pow(fl.getBase(), fl.getExponent_bits());
	int max_mantissa = pow(fl.getBase(), fl.getMantissa_bits());

	while (fl.getExponent() < max_exponent) {
		while (fl.getMantissa() < max_mantissa) {
			x = fl.calcX();
			// std::cout << std::setprecision(100000) << x << '\n';
			if (x > this->maximum) {
				break;
			}
			// std::cout << "x: " << x << '\n';
			for (int i = 0; i < this->list_zahlenverteilung.size(); i++) {
				// std::cout << "checking ob zwischen: " << this->list_klassen[i] << " und " << this->list_klassen[i + 1] << '\n';
				if ((x >= this->list_klassen[i]) and (x < this->list_klassen[i + 1])) {
					this->list_zahlenverteilung[i]++;
					// std::cout << "Listenwert: " << this->list_zahlenverteilung[i] << '\n';
				}
			}
			fl.setMantissa(fl.getMantissa() + 1);
		}
		std::cout << "Exponent: " << fl.getExponent() << '\n';
		// this->print_zahlenverteilung();
		fl.setExponent(fl.getExponent() + 1);
		fl.setMantissa(0);
	}
	std::cout << "Liste Zahlenverteilung erstellt" << '\n';
}

void Zahlenverteilung::berechne_zahlenverteilung(Default32squarerootOverlapping fl) {
	std::cout << "Berechnung Zahlenverteilung Start" << '\n';
	init_list_zahlenverteilung();
	double x = 0.0;

	int max_exponent = pow(fl.getBase(), fl.getExponent_bits());
	int max_mantissa = pow(fl.getBase(), fl.getMantissa_bits());

	while (fl.getExponent() < max_exponent) {
		while (fl.getMantissa() < max_mantissa) {
			x = fl.calcX();
			// std::cout << std::setprecision(100000) << x << '\n';
			if (x > this->maximum) {
				break;
			}
			// std::cout << "x: " << x << '\n';
			for (int i = 0; i < this->list_zahlenverteilung.size(); i++) {
				// std::cout << "checking ob zwischen: " << this->list_klassen[i] << " und " << this->list_klassen[i + 1] << '\n';
				if ((x >= this->list_klassen[i]) and (x < this->list_klassen[i + 1])) {
					this->list_zahlenverteilung[i]++;
					// std::cout << "Listenwert: " << this->list_zahlenverteilung[i] << '\n';
				}
			}
			fl.setMantissa(fl.getMantissa() + 1);
		}
		std::cout << "Exponent: " << fl.getExponent() << '\n';
		// this->print_zahlenverteilung();
		fl.setExponent(fl.getExponent() + 1);
		fl.setMantissa(0);
	}
	std::cout << "Liste Zahlenverteilung erstellt" << '\n';
}

void Zahlenverteilung::print_zahlenverteilung() {
	std::cout << this->name << '\n';
	// std::cout << "print size " << this->list_zahlenverteilung.size() << '\n';
	// std::cout << "Klassen " << this->list_klassen.size() << '\n';
	for (int i = 0; i < this->list_zahlenverteilung.size(); i++) {
		std::cout << this->list_zahlenverteilung[i] << " Vorkommen im Bereich: " << this->list_klassen[i] << " bis " << this->list_klassen[i + 1] << '\n';
	}
}

void Zahlenverteilung::print_zahlenverteilung_csv_format() {
	std::cout << this->name << '\n';
	std::cout << "CSV Zahlenverteilung" << '\n';
	for (int i = 0; i < this->list_klassen.size(); i++) {
		std::cout << this->list_klassen[i] << ',';
	}
	std::cout << '\n' << '\n';
	for (int i = 0; i < this->list_zahlenverteilung.size(); i++) {
		std::cout << this->list_zahlenverteilung[i] << ',';
	}
	std::cout << '\n' << "CSV Ende" << '\n';
}

std::vector<double> Zahlenverteilung::berechne_klassen() {
	std::vector<double> list;
	//std::cout << steps;
	list.push_back(this->minimum);
	while(list.back() < (this->maximum-this->steps)) {
		// std::cout << list.back() << " + " << this->steps << " = " << (list.back() + this->steps);
		list.push_back(list.back() + this->steps);
		// std::cout << "Klassen: " << list.back() << '\n';
	}
	std::cout << "Anzahl an Klassen: " << (list.size()-1) << '\n';
	return list;
}

// initialisiert bzw setzt die Liste der Zahlenverteilung auf 0
void Zahlenverteilung::init_list_zahlenverteilung() {
	if (!this->list_zahlenverteilung.empty()) {
		this->list_zahlenverteilung = {};
	}
	for (int i = 0; i < this->list_klassen.size()-1;i++) {
		this->list_zahlenverteilung.push_back(0);
	}
}