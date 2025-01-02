#ifndef ZAHLENVERTEILUNG_H
#define ZAHLENVERTEILUNG_H

#include <iostream>
#include <cmath>
#include <vector>
#include "Zahlendarstellung.h"
class Zahlenverteilung {
public:
	Zahlenverteilung(double min, double max, double st);

	void berechne_zahlenverteilung(Zahlendarstellung fl);

	void print_zahlenverteilung();

	void print_zahlenverteilung_csv_format();

	std::vector<double> getList_klassen();

private:
	int minimum;  // Untere Grenze, die dargestellt werden soll
	int maximum;  // Obere Grenze der Zahlen, die dargestellt werden sollen
	double steps; // Schritte für die Realisierung der einzelnen (Histogramm-)Klassen
	std::vector<int> list_zahlenverteilung; // Liste mit der Anzahl der Vorkommen in der jeweiligen Klasse
	std::vector<double> list_klassen; // Liste mit der Anzahl der Vorkommen in der jeweiligen Klasse

	std::vector<double> berechne_klassen();

	void init_list_zahlenverteilung();
};

#endif
