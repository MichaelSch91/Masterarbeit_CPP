// default bezieht sich auf das Vorhandensein Exponent Bits und Mantissen Bits und ggf. Vorzeichen Bits
// squareroot => optimiert f�r Quadratwurzeln: zB base = sqrt(2), exponent = 8 => 2^4 , bei exponent = 9 => (2^4) * sqrt(2), 
// damit nur einmal mit der irrationalen Zahl multipliziert werden muss.
#ifndef DEFAULT32SQUAREROOT_H
#define DEFAULT32SQUAREROOT_H

#include <iostream>
#include <cmath>

class Default32squareroot {
public:
	// Konstruktoren
	// 
	// Standardkonstruktor, mit ba als Basis -> sqrt(ba), s, e, m mit 0 initialisiert
	Default32squareroot(int ba);
	// Konstruktor, mit ba als Basis -> sqrt(ba), s, e, m gem. Aufruf initialisiert
	Default32squareroot(int ba, int s, int e, int m);
	// Konstruktor mit Basis 2 -> sqrt(2), s, e, m gem. Aufruf initialisiert
	Default32squareroot(int s, int e, int m);

	void setValues(int s, int e, int m);

	// Berechnung des dargestellten Wertes
	long double calcX();
	long double calcX_highExponent();
	long double calcX_oddExponent();
	long double calcX_evenExponent();
	long double calcX_negativeExponent();
	long double calc_pow_oddExponent();
	unsigned long long int calc_pow_evenExponent();
	long double calc_pow_negativeExponent();
	// Berechnung des dargestellten Wertes ohne sqrt(ba)^e umzuformen, f�r Tests notwendig
	// l�sst die Gr��enordnung des Ergebnisses mit calcX() vergleichen und zeigt, wie viel 
	// genauer die Berechnung mit Umformen von sqrt(ba)^e ist
	long double simpleCalcX();
	// Redundant zu calcX(), aber wird in manchen Funktionen noch aufgerufen, da es in anderen Klassen n�tig war
	long double calcX_long_double();
	// nur f�r Tests notwendig
	double berechneMantisseDezimalwert() const;
	// gibt den Wert der Abweichung zur�ck, um den ein Mantissenbit (m+1) den Wert abh�ngig vom Exponenten steigert
	// Delta = Zahl(0,this->e,1) - Zahl(0,this->e,0)
	long double deviation_due_to_exp();

	// Operatoren
	// 
	// �berladene Operatoren
	Default32squareroot operator+(Default32squareroot a);
	Default32squareroot operator-(Default32squareroot a);
	Default32squareroot operator*(Default32squareroot a);
	bool operator==(Default32squareroot a);
	// F�lle, in denen es sinnvoller ist eine andere Methode aufzurufen (zB a.operator+(-b) soll a.operator-(+b) aufrufen)
	Default32squareroot plus_different_operator(Default32squareroot a);
	Default32squareroot minus_different_operator(Default32squareroot a);

	// Getter und Setter
	// 
	// R�ckgabedatentypen entsprechen nicht zwingend den Datentypen der Klassen-Attribute,
	// da der Compiler sonst, zB bei der Mantisse, (int * long long) = int interpretiert und so 
	// �berl�ufe erzeugt
	int getSign();
	void setSign(int s);
	unsigned long long getMantissa();
	void setMantissa(int m);
	int getExponent();
	void setExponent(int e);
	// nur Getter, da nicht mehr ver�nderbar
	long long getBase();
	int getBias();
	int getMantissa_bits();
	int getExponent_bits();
	// Min und Max Werte f�r Exponent und Mantisse
	int getExponent_max();
	int getExponent_min();
	unsigned long long getMantissa_max();
	unsigned long long getMantissa_min();

	// Tests
	// 
	// ggf in eigene Testklasse packen (todo)
	//
	// Operatoren
	void test_Default32squareroot_operator_plus();
	void test_Default32squareroot_operator_minus();
	void test_Default32squareroot_operator_multiply();
	// Tests f�r die Berechnung des dargestellten Werts
	void test_Default32squareroot_calcX();
	// Tests f�r den Converter von double (oder long double) Darstellung zur Zahlendarstellung der Klasse
	void test_Default32squareroot_convert_to_Default32squareroot();
	void test_Default32squareroot_convert_to_Default32squareroot_In_and_Out(); // Default32squareroot als Random-Eingabe und �berpr�fung, ob ein Default32squareroot-Objekt mit gleichen Wert raus kommt.

	// Converter
	//
	// double / long double wird in Default32Squareroot Zahlentyp konvertiert
	static Default32squareroot convert_to_Default32squareroot(int base, long double x);
	void convert_setSign(long double x);
	int convert_findExponent(long double x);
	int convert_findMantissa(long double x, int s);
	int convert_mantissa_fastApproximation(long double x, int s);
	int convert_Mantissa_fineApproximation(long double x, int s, int mant_inaccurate);

private:
	int sign;  // Vorzeichen
	int mantissa;  // Mantisse
	int exponent; // Exponent
	int base;  // Basis
	static constexpr int bias = 127;  // Biaswert f�r Exponent
	static constexpr int mantissa_bits = 23;  // Bits Mantisse
	static constexpr int exponent_bits = 8;  // Bits Mantisse
	int exponent_max = 255; // max Wert Exponent
	int exponent_min = 0; // min Wert Exponent
	unsigned long long mantissa_max = 8'388'607; // max Wert Mantisse
	unsigned long long mantissa_min = 0; // min Wert Mantisse
};

#endif