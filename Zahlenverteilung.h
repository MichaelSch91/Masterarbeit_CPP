#ifndef ZAHLENVERTEILUNG_H
#define ZAHLENVERTEILUNG_H

#include <iostream>
#include <cmath>
#include <vector>
#include "Zahlendarstellung.h"
#include "Float16.h"
#include "Float32.h"
#include "ExperimentalDefault.h"
#include "Default32squareroot.h"
#include "Default32squarerootOverlapping.h"

class Zahlenverteilung {
public:
	Zahlenverteilung(double min, double max, double st, std::string name);
	Zahlenverteilung(double min, double max, int klassen, std::string name);

	void berechne_zahlenverteilung(Zahlendarstellung fl);
	void berechne_zahlenverteilung(Float32 fl);
	void berechne_zahlenverteilung(Float16 fl);
	void berechne_zahlenverteilung(ExperimentalDefault fl);
	void berechne_zahlenverteilung(Default32squareroot fl);
	void berechne_zahlenverteilung(Default32squarerootOverlapping fl);

	void print_zahlenverteilung();

	void print_zahlenverteilung_csv_format();

	std::vector<double> getList_klassen();

private:
	std::string name;
	double minimum;  // Untere Grenze, die dargestellt werden soll
	double maximum;  // Obere Grenze der Zahlen, die dargestellt werden sollen
	double steps; // Schritte für die Realisierung der einzelnen (Histogramm-)Klassen
	std::vector<int> list_zahlenverteilung; // Liste mit der Anzahl der Vorkommen in der jeweiligen Klasse
	std::vector<double> list_klassen; // Liste mit der Anzahl der Vorkommen in der jeweiligen Klasse

	std::vector<double> berechne_klassen();

	void init_list_zahlenverteilung();
};

#endif
