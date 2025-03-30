#include "LogisticmapCalc.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>

    // Getter for i
    int LogisticmapCalc::getI() const {
        return i;
    }

    // Setter for i
    void LogisticmapCalc::setI(int new_i) {
        i = new_i;
    }

    // Getter for r
    long double LogisticmapCalc::getR() const {
        return r;
    }

    // Setter for r
    void LogisticmapCalc::setR(long double new_r) {
        r = new_r;
    }

    // Getter for s
    long double LogisticmapCalc::getS() const {
        return s;
    }

    // Setter for s
    void LogisticmapCalc::setS(long double new_s) {
        s = new_s;
    }

    // Getter for start_step
    long double LogisticmapCalc::getStartStep() const {
        return start_step;
    }

    // Setter for start_step
    void LogisticmapCalc::setStartStep(long double new_start_step) {
        start_step = new_start_step;
    }

    // Getter for r_step
    long double LogisticmapCalc::getRStep() const {
        return r_step;
    }

    // Setter for r_step
    void LogisticmapCalc::setRStep(long double new_r_step) {
        r_step = new_r_step;
    }

    // in LogisticmapCalc
    std::list<long double> LogisticmapCalc::abweichungsRechner(std::list<long double> list_eval, std::list<long double> list_calc) {
        std::list<long double> list = {};
        long double d = 0;
        for (auto eval = list_eval.begin(), calc = list_calc.begin(); eval != list_eval.end() && calc != list_calc.end(); ++eval, ++calc) {
            // std::cout << std::setprecision(precision) << abs(*eval - *calc) << '/ n';
            list.push_back(abs(*eval - *calc));
        }
        return list;
    }

    /*
    static std::list<double> abweichungsRechnerDoubleFloat(std::list<double> list_eval, std::list<double> list_calc) {
        std::list<double> list = {};
        long double d = 0;
        for (auto eval = list_eval.begin(), calc = list_calc.begin(); eval != list_eval.end() && calc != list_calc.end(); ++eval, ++calc) {
            // std::cout << std::setprecision(precision) << abs(*eval - *calc) << '/ n';
            list.push_back(abs(*eval - *calc));
        }
        return list;
    }
    */

    // Methode mit Hashtabelle
    bool LogisticmapCalc::hasDuplicatesWithHash(std::list<long double> list) {
        std::unordered_set<long double> seen;
        for (long double num : list) {
            if (seen.count(num)) {
                return true;
            }
            seen.insert(num);
        }
        return false;
    }

    // returns true, wenn die Liste Duplikate enthält
    // kann eigentlich auch mit std::get<0>(list_screen_duplicates(std::list<long double> list)) geprüft werden
    bool LogisticmapCalc::list_check_for_duplicates(std::list<long double> checked_list) {
        std::list<long double> list(checked_list);
        return hasDuplicatesWithHash(list);
    }

    int LogisticmapCalc::search_first_occurrence(std::list<long double> list, long double value) {
        int iteration = 0;
        for (long double num : list) {
            if (num == value) {
                return iteration;
            }
            iteration++;
        }
    }

    // Tupel: <hat Dopplung, Wert der ersten Dopplung, Iteration erstes Vorkommen, Iteration zweites Vorkommen>
    std::tuple<bool, long double, int, int> LogisticmapCalc::list_screen_duplicates(std::list<long double> list) {

        std::unordered_set<long double> seen;
        int iteration = 0;
        long double value = 0.0;
        bool has_duplicate = 0;
        int first_iteration = 0;
        int last_iteration = 0;

        for (long double num : list) {
            if (seen.count(num)) {
                value = num;
                has_duplicate = 1;
                last_iteration = iteration;
                break;
            }
            seen.insert(num);
            iteration++;
        }
        if (has_duplicate) {
            first_iteration = search_first_occurrence(list, value);
        }
        return std::tuple<bool, long double, int, int>(has_duplicate, value, first_iteration, last_iteration);
    }

    // gibt die Daten aus, wann sich eine Liste, mit welchem Wert wiederholt
    void LogisticmapCalc::list_screen(std::list<long double> checked_list) {
        std::list<long double> list(checked_list);
        std::tuple<bool, long double, int, int> tuple = list_screen_duplicates(list);
        if (std::get<0>(tuple)) {
            std::cout << "Liste hat Wert doppelt: " << std::get<1>(tuple) << " bei " << std::get<2>(tuple) << " und " << std::get<3>(tuple) << " iterations." << '\n';;
        }
        else {
            std::cout << "Liste hat keinen Wert doppelt" << '\n';
        }
    }

    void LogisticmapCalc::list_screen_csv(std::list<long double> checked_list) {
        std::list<long double> list(checked_list);
        std::tuple<bool, long double, int, int> tuple = list_screen_duplicates(list);
        if (std::get<0>(tuple)) {
            // start, r, X, erstes Vorkommen, zweites Vorkommen
            std::cout << this->getS() << ", " << this->getR() << ", " << std::get<1>(tuple) << ", " << std::get<2>(tuple) << ", " << std::get<3>(tuple) << '\n';
        }
        else {
            std::cout << this->getS() << ", " << this->getR() << ", " << "Liste hat keinen Wert doppelt" << '\n';
        }
    }

    // Listenwerte +1, falls Zählung nicht ab 0: std::cout << std::get<1>(tuple) << ',' << (std::get<2>(tuple)+1) << ',' << (std::get<3>(tuple)+1) << '\n';
    void LogisticmapCalc::list_screen_csv_format(std::list<long double> checked_list) {
        std::list<long double> list(checked_list);
        std::tuple<bool, long double, int, int> tuple = list_screen_duplicates(list);
        if (std::get<0>(tuple)) {
            std::cout << std::get<1>(tuple) << ',' << std::get<2>(tuple) << ',' << std::get<3>(tuple) << '\n';
        }
        else {
            std::cout << "Liste hat keinen Wert doppelt" << '\n';
        }
    }

    /* durch list_screen ersetzt
static long double list_check_value(std::list<long double> list) {
    std::unordered_set<long double> seen;
    for (long double num : list) {
        if (seen.count(num)) {
            return num;
        }
        seen.insert(num);
    }
}

static std::tuple<int, int> list_check_iteration(std::list<long double> list, long double value) {
    int twice = 0;
    int iteration = 0;
    int first_occur = 0;
    for (long double d:list) {
        if (d == value) {
            if (twice > 0) {
                return std::tuple<int,int>(first_occur,iteration);
            }
            first_occur = iteration;
            twice++;
        }
        iteration++;
    }
}

// check_value und check_iteration ggf in eine Methode packen, die ein Tupel zurück gibt, damit es nicht mehrfach durch die Liste iterieren muss.
// check_list eventuell auslassen und nur diese Methode aufrufen. Wenn keine Dopplung gefunden wird, einfach ausgeben.
// ggf testen, ob schneller
static void list_check_value_iteration(std::list<long double> list) {
    if (list_check_for_duplicates(list)) {
        long double multiple_value = list_check_value(list);
        std::tuple<int,int> multiple_iteration = list_check_iteration(list, multiple_value);
        std::cout << "Liste hat Wert doppelt: " << multiple_value << " bei " << std::get<0>(multiple_iteration) << " und " << std::get<1>(multiple_iteration) << " iterations." << '\n';
    }
    else {
        std::cout << "Liste hat keinen Wert doppelt" << '\n';
    }
}
*/