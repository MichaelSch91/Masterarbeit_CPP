#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <cmath>

#include "CSV_data.h"

int precision = 50000; // setzt die Genauigkeit (Anzahl der Nachkommazahlen) in der Ausgabe

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