// default bezieht sich auf das Vorhandensein Exponent Bits und Mantissen Bits und ggf. Vorzeichen Bits
#ifndef EXPERIMENTALDEFAULT_H
#define EXPERIMENTALDEFAULT_H

#include <iostream>
#include <cmath>
class ExperimentalDefault {
public:
	ExperimentalDefault(int ba, int mant_bits, int exp_bits);

	ExperimentalDefault(int ba, int mant_bits, int exp_bits, int s, long e, long m);

	ExperimentalDefault(int ba, int bi, int mant_bits, int exp_bits, int s, long e, long m);

	void setValues(int s, long e, long m);

	long double calcX();
	long double calcX_with_In_Out();

	int getSign();
	void setSign(int s);

	long getMantissa();
	void setMantissa(long m);

	long getExponent();
	void setExponent(long e);

	int getBase();
	int getBias();
	int getMantissa_bits();
	int getExponent_bits();
	unsigned long long getMantissa_max();
	unsigned long long getExponent_max();

	void printAttributes();

private:
	int sign;  // Vorzeichen
	long mantissa;  // Mantisse
	long exponent; // Exponent
	int base;  // Basis
	int bias;  // Biaswert für Exponent
	int mantissa_bits;  // Bits Mantisse
	int exponent_bits;  // Bits Mantisse
	int exponent_max; // max Wert Exponent
	int exponent_min = 0; // min Wert Exponent
	unsigned long long mantissa_max; // max Wert Mantisse
	unsigned long long mantissa_min = 0; // min Wert Mantisse

	long double berechneMantisseDezimalwert_denormalized();

	long double berechneMantisseDezimalwert_normalized();
	
	int berechneBias();

	unsigned long long berechneExponent_max();

	unsigned long long berechneMantissa_max();

};

#endif