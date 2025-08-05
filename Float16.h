#ifndef FLOAT16_H
#define FLOAT16_H

#include <iostream>
#include <cmath>
#include "Float32.h"

class Float16 {
public:
	Float16(int s, int e, int m);

	double calcX();

	Float16 operator+(Float16 a);
	Float16 operator-(Float16 a);
	Float16 operator*(Float16 a);

	int getSign();
	void setSign(int s);

	int getMantissa();
	void setMantissa(int m);

	int getExponent();
	void setExponent(int e);

	int getBase();
	int getBias();
	int getMantissa_bits();
	int getExponent_bits();

	Float32 convert_to_Float32();

	// richtige Tests erstellen, zumindest für die Methoden der entwickelten Zahlendarstellung
	void test_Float16_operator_plus();
	void test_Float16_operator_minus();
	void test_Float16_operator_multiply();
	static Float16 convert_to_Float16(long double x);
	void convert_setSign(long double x);
	int convert_findExponent(long double x);
	int convert_findMantissa(long double x, int s);
	int convert_mantissa_fastApproximation(long double x, int s);
	int convert_Mantissa_fineApproximation(long double x, int s, int mant_inaccurate);
	void printAttributes();
	bool operator==(Float16 a);

private:
	int sign;  // Vorzeichen
	int mantissa;  // Mantisse
	int exponent; // Exponent
	static constexpr int base = 2;  // Basis
	static constexpr int bias = 15;  // Biaswert für Exponent
	static constexpr int mantissa_bits = 10;  // Bits Mantisse
	static constexpr int exponent_bits = 5;  // Bits Exponent

	double berechneMantisseDezimalwert();

	int berechneMantisseBinärwert(double dezimalwert);
};

#endif