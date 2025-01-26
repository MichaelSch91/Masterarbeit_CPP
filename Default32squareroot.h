// default bezieht sich auf das Vorhandensein Exponent Bits und Mantissen Bits und ggf. Vorzeichen Bits
// squareroot => optimiert für Quadratwurzeln: zB base = sqrt(2), exponent = 8 => 2^4 , bei exponent = 9 => (2^4) * sqrt(2), 
// damit nur einmal mit der irrationalen Zahl multipliziert werden muss.
#ifndef DEFAULT32SQUAREROOT_H
#define DEFAULT32SQUAREROOT_H

#include <iostream>
#include <cmath>
#include "Default32squareroot.h"
// todo
class Default32squareroot {
public:
	Default32squareroot(int ba);

	Default32squareroot(int ba, int s, int e, int m);

	Default32squareroot(int s, int e, int m);

	void setValues(int s, int e, int m);

	double calcX();
	double calcX_highExponent();
	double calcX_oddExponent();
	double calcX_evenExponent();
	double calcX_negativeExponent();
	long double calc_pow_oddExponent();
	unsigned long long int calc_pow_evenExponent();
	long double calc_pow_negativeExponent();

	long double simpleCalcX();

	Default32squareroot operator+(Default32squareroot a);
	Default32squareroot plus_different_operator(Default32squareroot a);

	Default32squareroot operator-(Default32squareroot a);
	Default32squareroot minus_different_operator(Default32squareroot a);

	Default32squareroot operator*(Default32squareroot a);

	bool operator==(Default32squareroot a);

	int getSign();
	void setSign(int s);

	unsigned long long getMantissa();
	void setMantissa(int m);

	int getExponent();
	void setExponent(int e);

	long long getBase();
	int getBias();
	int getMantissa_bits();
	int getExponent_bits();

	// richtige Tests erstellen, zumindest für die Methoden der entwickelten Zahlendarstellung
	void test_Default32squareroot_operator_plus();
	void test_Default32squareroot_operator_minus();
	void test_Default32squareroot_operator_multiply();
	
	void test_Default32squareroot_calcX();



private:
	int sign;  // Vorzeichen
	int mantissa;  // Mantisse
	int exponent; // Exponent
	int base;  // Basis
	static constexpr int bias = 127;  // Biaswert für Exponent
	static constexpr int mantissa_bits = 23;  // Bits Mantisse
	static constexpr int exponent_bits = 8;  // Bits Mantisse

	double berechneMantisseDezimalwert() const;
};

#endif