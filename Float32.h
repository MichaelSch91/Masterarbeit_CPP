#ifndef FLOAT32_H
#define FLOAT32_H

#include <iostream>
#include <cmath>
//todo
class Float32 {
public:
	// Konstruktor
	Float32(int s, int e, int m);

	// Berechnung des dargestellten Wertes
	float calcX_float();
	double calcX();
	long double calcX_long_double();
	double berechneMantisseDezimalwert() const;

	// gibt den Wert der Abweichung zurück, um den ein Mantissenbit (m+1) den Wert abhängig vom Exponenten steigert
	// Delta = Zahl(0,e,1) - Zahl(0,e,0)
	long double deviation_due_to_exp();

	void printAttributes();

	// Operatoren
	// 
	// überladene Operatoren
	Float32 operator+(Float32 a);
	Float32 operator-(Float32 a);
	Float32 operator*(Float32 a);
	bool operator==(Float32 a);
	// Fälle, in denen es sinnvoller ist eine andere Methode aufzurufen (zB a.operator+(-b) soll a.operator-(+b) aufrufen)
	Float32 plus_different_operator(Float32 a);
	Float32 minus_different_operator(Float32 a);


	// Getter und Setter
	// 
	// Rückgabedatentypen entsprechen nicht zwingend den Datentypen der Klassen-Attribute,
	// da der Compiler sonst, zB bei der Mantisse, (int * long long) = int interpretiert und so 
	// Überläufe erzeugt
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

	// Tests für Operatoren
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
};

#endif