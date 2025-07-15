#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <cmath>
#include <sstream>

#include "CSV_data.h"

int precision = 50000; // setzt die Genauigkeit (Anzahl der Nachkommazahlen) in der Ausgabe

void CSV_data::writeDefault32SquareRootListAsCalcXToCSV(Logisticmap_Default32squareroot d32s) {
    double r = d32s.getR().calcX();
    double s = d32s.getS().calcX();
    
    std::stringstream r_stream;
    r_stream << std::fixed << std::setprecision(2) << r;
    std::string r_str = r_stream.str();

    std::stringstream s_stream;
    s_stream << std::fixed << std::setprecision(2) << s;
    std::string s_str = s_stream.str();

    std::string filenameAddition = "_r_" + r_str + "_s_" + s_str;

    std::string filename = "CSV\\logistic_map_data" + filenameAddition + ".csv";

    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file: " << filename << std::endl;
        return;
    }

    outputFile << "r= " << d32s.getR().calcX() << ", s= " << d32s.getS().calcX() << std::endl;
    outputFile << "Index,Value" << std::endl;

    int counter = 0;
    for (Default32squareroot i : d32s.getList()) {
        outputFile << counter << ",";

        outputFile << std::setprecision(precision) << i.calcX();

        outputFile << '\n';
        counter++;
    }

    // Close the file
    outputFile.close();

    std::cout << "Data written to " << filename << " successfully." << std::endl;
}

void CSV_data::writeFloatListToCSV(std::list<float> list) {
    // create filename
    std::string filename = "\CSV\\float_precision.csv";
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

void CSV_data::writeDoubleListToCSV(std::list<double> list) {
    // create filename
    std::string filename = "\CSV\\double_precision.csv";
    // Open the output file in write mode
    std::ofstream outputFile(filename);
    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return;
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

void CSV_data::writeDoubleListToCSV(std::list<long double> list) {
    // create filename
    std::string filename = "\CSV\\long_double_precision.csv";
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

void CSV_data::writeLongDoubleListToCSV(std::list<long double> list) {
    // create filename
    std::string filename = "\CSV\\long_double_precision.csv";
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

void CSV_data::writeDeltaLongDoubleListToCSV(std::list<long double> list) {
    // create filename
    std::string filename = "\CSV\\delta_long_double_precision.csv";
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

void CSV_data::writeDeltaLongDoubleListToCSV_double_float(std::list<long double> list) {
    // create filename
    std::string filename = "\CSV\\delta_double_float_precision.csv";
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