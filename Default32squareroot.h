// default bezieht sich auf das Vorhandensein Exponent Bits und Mantissen Bits und ggf. Vorzeichen Bits
// squareroot => optimiert für Quadratwurzeln: zB base = sqrt(2), exponent = 8 => 2^4 , bei exponent = 9 => (2^4) * sqrt(2), 
// damit nur einmal mit der irrationalen Zahl multipliziert werden muss.
#ifndef DEFAULT32SQUAREROOT_H
#define DEFAULT32SQUAREROOT_H

#include <iostream>
#include <cmath>
// todo
class Default32squareroot {
public:
	Default32squareroot(int ba, int bi, int mant_bits, int exp_bits);

	Default32squareroot(int ba, int bi, int mant_bits, int exp_bits, int s, int m, int e);

	void setValues(int s, int m, int e);

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
	int sign{};  // Vorzeichen
	int mantissa{};  // Mantisse
	int exponent{}; // Exponent
	const int base;  // Basis
	const int bias;  // Biaswert für Exponent
	const int mantissa_bits;  // Bits Mantisse
	const int exponent_bits;  // Bits Mantisse

	double berechneMantisseDezimalwert() const;
};

#endif