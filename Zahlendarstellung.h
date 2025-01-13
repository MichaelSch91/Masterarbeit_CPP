#ifndef ZAHLENDARSTELLUNG_H
#define ZAHLENDARSTELLUNG_H

#include <iostream>
#include <cmath>
//todo
class Zahlendarstellung {
public:
	Zahlendarstellung(int s, int e, int m);

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
	static constexpr int bias = 127;  // Biaswert für Exponent
	static constexpr int mantissa_bits = 23;  // Bits Mantisse
	static constexpr int exponent_bits = 8;  // Bits Mantisse

	double berechneMantisseDezimalwert() const;
};

#endif