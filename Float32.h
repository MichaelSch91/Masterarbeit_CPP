#ifndef FLOAT32_H
#define FLOAT32_H

#include <iostream>
#include <cmath>
//todo
class Float32 {
public:
	Float32(int s, int e, int m);

	double calcX();

	Float32 operator+(Float32 a);
	Float32 operator-(Float32 a);
	Float32 operator*(Float32 a);

	int getSign();
	void setSign(int s);

	unsigned long long getMantissa();
	void setMantissa(int m);

	int getExponent();
	void setExponent(int e);

	int getBase();
	int getBias();
	int getMantissa_bits();
	int getExponent_bits();

	// richtige Tests erstellen, zumindest für die Methoden der entwickelten Zahlendarstellung
	void test_Float32_operator_plus();
	void test_Float32_operator_minus();
	void test_Float32_operator_multiply();

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