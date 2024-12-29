// LogisticMap.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

// list::max_size
#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>

//config
static int precision = 50000; // setzt die Genauigkeit (Anzahl der Nachkommazahlen) in der Ausgabe
bool create_csv = 0;

class Logisticmap {
public:
    int i = 100'000;
    long double r = 3.9;
    long double s = 0.1;
    long double start_step = 0.01;
    long double r_step = 0.01;

public:
    // Getter for i
    int getI() const {
        return i;
    }

    // Setter for i
    void setI(int new_i) {
        i = new_i;
    }

    // Getter for r
    long double getR() const {
        return r;
    }

    // Setter for r
    void setR(long double new_r) {
        r = new_r;
    }

    // Getter for s
    long double getS() const {
        return s;
    }

    // Setter for s
    void setS(long double new_s) {
        s = new_s;
    }

    // Getter for start_step
    long double getStartStep() const {
        return start_step;
    }

    // Setter for start_step
    void setStartStep(long double new_start_step) {
        start_step = new_start_step;
    }

    // Getter for r_step
    long double getRStep() const {
        return r_step;
    }

    // Setter for r_step
    void setRStep(long double new_r_step) {
        r_step = new_r_step;
    }
};

class Logisticmap_float : public Logisticmap {
private:
    std::list<float> list = logistischeAbbildungFloat();
    std::list<long double> long_double_list = cast_list(this->list);

    std::list<float> logistischeAbbildungFloat() {
        float x = this->s;
        std::list<float> list = {};
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
    float logistischeAbbildungRechnerFloat(float x, float r) {
        return r * x * (1 - x);
    }

    std::list<long double> cast_list(std::list<float> floatList) {
        std::list<long double> list = {};
        for (float d : floatList) {
            list.push_back(d);
        }
        return list;
    }

public:
    std::list<float> getList() {
        return this->list;
    }
    std::list<long double> get_long_double_List() {
        return this->long_double_list;
    }
};

class Logisticmap_double : public Logisticmap {
private:
    std::list<double> list = logistischeAbbildungDouble(this->i, this->r, this->s);
    std::list<long double> long_double_list = cast_list(this->list);

    // mit Startwert s
    std::list<double> logistischeAbbildungDouble(int i, double r, double s) {
        double x = s;
        std::list<double> list = {};
        for (int j = 0; j <= i; j++) {
            list.push_back(logistischeAbbildungRechnerDouble(x, r));
            // std::cout << list.back() << '\n';
            x = list.back();
            // std::cout << x << '\n';
        }
        return list;
    }

    double logistischeAbbildungRechnerDouble(double x, double r) {
        return r * x * (1 - x);
    }

    std::list<long double> cast_list(std::list<double> doubleList) {
        std::list<long double> list = {};
        for (double d : doubleList) {
            list.push_back(d);
        }
        return list;
    }

public:
    std::list<double> getList() {
        return this->list;
    }
    std::list<long double> get_long_double_List() {
        return this->long_double_list;
    }
};

class Logisticmap_long_double : public Logisticmap {
private:
    std::list<long double> list = logistischeAbbildungLongDouble(this->i, this->r, this->s);
    std::list<long double> long_double_list = this->list;

    // mit Startwert s
    std::list<long double> logistischeAbbildungLongDouble(int i, long double r, long double s) {
        long double x = s;
        std::list<long double> list = {};
        for (int j = 0; j <= i; j++) {
            list.push_back(logistischeAbbildungRechnerLongDouble(x, r));
            x = list.back();
            // std::cout << x << '\n';
        }
        return list;
    }

    long double logistischeAbbildungRechnerLongDouble(long double x, long double r) {
        return r * x * (1 - x);
    }

public:
    std::list<long double> getList() {
        return this->list;
    }
    std::list<long double> get_long_double_List() {
        return this->long_double_list;
    }
};

static void writeFloatListToCSV(std::list<float> list) {
    // create filename
    std::string filename = "float_precision.csv";
    // Open the output file in write mode
    std::ofstream outputFile(filename);
    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return;
    }
    // Write data to the CSV file
    for (float d : list) {
        outputFile << std::setprecision(precision) << d << ',';
        outputFile << std::endl; // Add newline after each row
    }
    // Close the file
    outputFile.close();

    std::cout << "Data written to " << filename << " successfully." << std::endl;
}

static void writeDoubleListToCSV(std::list<double> list) {
    // create filename
    std::string filename = "double_precision.csv";
    // Open the output file in write mode
    std::ofstream outputFile(filename);
    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return ;
    }
    // Write data to the CSV file
    for (double d : list) {
        outputFile << std::setprecision(precision) << d << ',';
        outputFile << std::endl; // Add newline after each row
    }
    // Close the file
    outputFile.close();

    std::cout << "Data written to " << filename << " successfully." << std::endl;
}

static void writeLongDoubleListToCSV(std::list<long double> list) {
    // create filename
    std::string filename = "long_double_precision.csv";
    // Open the output file in write mode
    std::ofstream outputFile(filename);
    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return;
    }
    // Write data to the CSV file
    for (long double d : list) {
        outputFile << std::setprecision(precision) << d << ',';
        outputFile << std::endl; // Add newline after each row
    }
    // Close the file
    outputFile.close();

    std::cout << "Data written to " << filename << " successfully." << std::endl;
}

static void writeDeltaLongDoubleListToCSV(std::list<long double> list) {
    // create filename
    std::string filename = "delta_long_double_precision.csv";
    // Open the output file in write mode
    std::ofstream outputFile(filename);
    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return;
    }
    // Write data to the CSV file
    for (long double d : list) {
        outputFile << std::setprecision(precision) << d << ',';
        outputFile << std::endl; // Add newline after each row
    }
    // Close the file
    outputFile.close();

    std::cout << "Data written to " << filename << " successfully." << std::endl;
}

static void writeDeltaLongDoubleListToCSV_double_float(std::list<long double> list) {
    // create filename
    std::string filename = "delta_double_float_precision.csv";
    // Open the output file in write mode
    std::ofstream outputFile(filename);
    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return;
    }
    // Write data to the CSV file
    for (long double d : list) {
        outputFile << std::setprecision(precision) << d << ',';
        outputFile << std::endl; // Add newline after each row
    }
    // Close the file
    outputFile.close();

    std::cout << "Data written to " << filename << " successfully." << std::endl;
}

static std::list<long double> abweichungsRechner(std::list<long double> list_eval, std::list<long double> list_calc) {
    std::list<long double> list = {};
    long double d = 0;
    for (auto eval = list_eval.begin(), calc = list_calc.begin(); eval != list_eval.end() && calc != list_calc.end(); ++eval, ++calc) {
        // std::cout << std::setprecision(precision) << abs(*eval - *calc) << '/ n';
        list.push_back(abs(*eval - *calc));
    }
    return list;
}

static std::list<double> abweichungsRechnerDoubleFloat(std::list<double> list_eval, std::list<double> list_calc) {
    std::list<double> list = {};
    long double d = 0;
    for (auto eval = list_eval.begin(), calc = list_calc.begin(); eval != list_eval.end() && calc != list_calc.end(); ++eval, ++calc) {
        // std::cout << std::setprecision(precision) << abs(*eval - *calc) << '/ n';
        list.push_back(abs(*eval - *calc));
    }
    return list;
}

// Methode mit Hashtabelle
static bool hasDuplicatesWithHash(std::list<long double> list) {
    std::unordered_set<long double> seen;
    for (long double num : list) {
        if (seen.count(num)) {
            return true;
        }
        seen.insert(num);
    }
    return false;
   }

static bool list_check(std::list<long double> checked_list) {
    std::list<long double> list(checked_list);
    return hasDuplicatesWithHash(list);
}

static long double list_check_value(std::list<long double> list) {
    std::unordered_set<long double> seen;
    for (long double num : list) {
        if (seen.count(num)) {
            return num;
        }
        seen.insert(num);
    }
}

static int list_check_iteration(std::list<long double> list, long double value) {
    int twice = 0;
    int iteration = 0;
    for (long double d:list) {
        if (d == value) {
            if (twice > 0) {
                return iteration;
            }
            twice++;
        }
        iteration++;
    }
}

static void list_check_value_iteration(std::list<long double> list) {
    if (list_check(list)) {
        long double multiple_value = list_check_value(list);
        int multiple_iteration = list_check_iteration(list, multiple_value);
        std::cout << "Liste hat Wert doppelt: " << multiple_value << " after " << multiple_iteration << " iterations." << '\n';
    }
    else {
        std::cout << "Liste hat keinen Wert doppelt" << '\n';
    }
}
    

int main()
{
    // Logisticmap_float logisticmap_float;
    Logisticmap_double logisticmap_double;
    // Logisticmap_long_double logisticmap_long_double;

    // loop finder / Periodizität
    std::cout << "Float:" << '\n';
    // list_check_value_iteration(logisticmap_float.get_long_double_List());

    std::cout << "Double:" <<  '\n';
    list_check_value_iteration(logisticmap_double.get_long_double_List());
    
    std::cout << "Long Double:" << '\n';
    // list_check_value_iteration(logisticmap_long_double.get_long_double_List());
    /*
    // Abweichungen / Deltas / Vergleiche: 
    std::list<long double> eval_longDouble_double_list = abweichungsRechner(logisticmap_long_double.get_long_double_List(), logisticmap_double.get_long_double_List());
    std::list<long double> eval_double_float_list = abweichungsRechner(logisticmap_double.get_long_double_List(), logisticmap_float.get_long_double_List());
    
    // CSV-Dateien erstellen
    if (create_csv) {
        writeFloatListToCSV(logisticmap_float.getList());
        writeDoubleListToCSV(logisticmap_double.getList());
        writeLongDoubleListToCSV(logisticmap_long_double.getList());
        writeDeltaLongDoubleListToCSV(eval_longDouble_double_list);
        writeDeltaLongDoubleListToCSV_double_float(eval_double_float_list);
    }
    else {
        std::cout << "Es wurden keine CSV-Dateien erstellt.";
    }

    */
}
