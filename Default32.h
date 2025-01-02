// default bezieht sich auf das Vorhandensein Exponent Bits und Mantissen Bits und ggf. Vorzeichen Bits
#ifndef DEFAULT32_H
#define DEFAULT32_H

#include <iostream>
#include <cmath>
class Default32 {
public:
	Default32(int base, int bias, int mantissa_bits, int exponent_bits);

	Default32(int base, int bias, int mantissa_bits, int exponent_bits, int s, int m, int e);

	double setValues(int s, int m, int e);

	double calcX() const;

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

private:
	int sign;  // Vorzeichen
	int mantissa;  // Mantisse
	int exponent; // Exponent
	const int base;  // Basis
	const int bias;  // Biaswert für Exponent
	const int mantissa_bits;  // Bits Mantisse
	const int exponent_bits;  // Bits Mantisse

	double berechneMantisseDezimalwert() const;
};

#endif