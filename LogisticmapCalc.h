#ifndef LOGISTICMAPCALC_H
#define LOGISTICMAPCALC_H

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>

class LogisticmapCalc {
public:
    int i = 10'000;
    long double r = 3.9;
    long double s = 0.1;
    long double start_step = 0.1;
    long double r_step = 0.01;

    // Getter for i
    int getI() const;

    // Setter for i
    void setI(int new_i);

    // Getter for r
    long double getR() const;

    // Setter for r
    void setR(long double new_r);

    // Getter for s
    long double getS() const;

    // Setter for s
    void setS(long double new_s);

    // Getter for start_step
    long double getStartStep() const;

    // Setter for start_step
    void setStartStep(long double new_start_step);

    // Getter for r_step
    long double getRStep() const;

    // Setter for r_step
    void setRStep(long double new_r_step);

    // in LogisticmapCalc
    static std::list<long double> abweichungsRechner(std::list<long double> list_eval, std::list<long double> list_calc);

    // Methode mit Hashtabelle
    static bool hasDuplicatesWithHash(std::list<long double> list);

    // returns true, wenn die Liste Duplikate enthält
    // kann eigentlich auch mit std::get<0>(list_screen_duplicates(std::list<long double> list)) geprüft werden
    static bool list_check_for_duplicates(std::list<long double> checked_list);

    static int search_first_occurrence(std::list<long double> list, long double value);

    // Tupel: <hat Dopplung, Wert der ersten Dopplung, Iteration erstes Vorkommen, Iteration zweites Vorkommen>
    static std::tuple<bool, long double, int, int> list_screen_duplicates(std::list<long double> list);

    // gibt die Daten aus, wann sich eine Liste, mit welchem Wert wiederholt
    static void list_screen(std::list<long double> checked_list);

    void list_screen_csv(std::list<long double> checked_list);

    // Listenwerte +1, falls Zählung nicht ab 0: std::cout << std::get<1>(tuple) << ',' << (std::get<2>(tuple)+1) << ',' << (std::get<3>(tuple)+1) << '\n';
    static void list_screen_csv_format(std::list<long double> checked_list);
};
#endif