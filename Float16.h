#ifndef FLOAT16_H
#define FLOAT16_H

#include <iostream>
#include <cmath>
class Float16 {
public:
	Float16(int s, int m, int e);

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
	static constexpr int base = 2;  // Basis
	static constexpr int bias = 15;  // Biaswert für Exponent
	static constexpr int mantissa_bits = 10;  // Bits Mantisse
	static constexpr int exponent_bits = 5;  // Bits Mantisse

	double berechneMantisseDezimalwert() const;
};

#endif