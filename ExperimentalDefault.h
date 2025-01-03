// default bezieht sich auf das Vorhandensein Exponent Bits und Mantissen Bits und ggf. Vorzeichen Bits
#ifndef EXPERIMENTALDEFAULT_H
#define EXPERIMENTALDEFAULT_H

#include <iostream>
#include <cmath>
class ExperimentalDefault {
public:
	ExperimentalDefault(int ba, int bi, int mant_bits, int exp_bits);

	ExperimentalDefault(int ba, int mant_bits, int exp_bits, int s, long m, long e);

	ExperimentalDefault(int ba, int bi, int mant_bits, int exp_bits, int s, long m, long e);

	void setValues(int s, long m, long e);

	long double calcX() const;
	long double calcX_with_In_Out() const;

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

private:
	int sign{};  // Vorzeichen
	long mantissa{};  // Mantisse
	long exponent{}; // Exponent
	const int base;  // Basis
	const int bias;  // Biaswert für Exponent
	const int mantissa_bits;  // Bits Mantisse
	const int exponent_bits;  // Bits Mantisse

	double berechneMantisseDezimalwert() const;
	
	int berechneBias(int base, int exponent_bits);
};

#endif