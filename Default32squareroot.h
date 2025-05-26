// default32 bezieht sich auf das Vorhandensein von Vorzeichen Bits, Exponenten Bits und Mantissen Bits mit der IEEE754 Verteilung (1,8,23)
// squareroot => optimiert für Quadratwurzeln: zB base = sqrt(2), exponent-bias = 8 => 2^4 , bei exponent-bias = 9 => (2^4) * sqrt(2), 
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

	// Berechnung des dargestellten Wertes
	long double calcX();
	long double calcX_denormalized();
	long double calcX_highExponent();
	long double calcX_oddExponent();
	long double calcX_evenExponent();
	long double calcX_negativeExponent();
	long double calc_pow_oddExponent();
	unsigned long long int calc_pow_evenExponent();
	long double calc_pow_negativeExponent();
	// Berechnung des dargestellten Wertes ohne sqrt(ba)^e umzuformen, für Tests notwendig
	// lässt die Größenordnung des Ergebnisses mit calcX() vergleichen und zeigt, wie viel 
	// genauer die Berechnung mit Umformen von sqrt(ba)^e ist
	long double simpleCalcX();
	// Redundant zu calcX(), aber wird in manchen Funktionen noch aufgerufen, da es in anderen Klassen nötig war
	long double calcX_long_double();
	// nur für Tests notwendig
	double berechneMantisseDezimalwert();
	// gibt den Wert der Abweichung zurück, um den ein Mantissenbit (m+1) den Wert abhängig vom Exponenten steigert
	// Delta = Zahl(0,this->e,1) - Zahl(0,this->e,0)
	long double deviation_due_to_exp();

	// mantissaValue ist der dargestellte Wert [1;sqrt(2)[
	long double calc_mantissaValue();
	// memoryDecimal ist der Wert, der im Arbeitsspeicher als Mantissenanteil gespeichert würde
	static int convert_mantissaValue_to_memoryDecimal(long double mantissaValue, unsigned long long one_dot);
	static int convert_mantissaValue_to_memoryDecimal_denormalized(long double mantissaValue, unsigned long long one_dot);

	void printAttributes();

	// Operatoren
	// 
	// überladene Operatoren
	// Rechenoperatoren
	Default32squareroot operator+(Default32squareroot a);
	std::tuple<int, int> plus_operator_calc(Default32squareroot a);
	std::tuple<int, int> plus_operator_mantissa_overflowcalc(int exponent, double mantissa_decimal);
	// m1 ist die Mantisse mit dem größerem Exponenten (shift wird auf m2 angewendet), exp ist der aktuelle Exponent (in operator+ gespeichert / der größere)
	// returns tuple mit <int exponent, int mantisse>
	
	Default32squareroot operator-(Default32squareroot a);
	std::tuple<int, int> minus_operator_calc(Default32squareroot a);
	std::tuple<int, int> minus_operator_mantissa_overflowcalc(int exponent, double mantissa_decimal);

	Default32squareroot operator*(Default32squareroot a);
	std::tuple<int, int> multiplication_operator_calc(Default32squareroot a);
	std::tuple<int, int> multiplication_operator_mantissa_overflowcalc(int exponent, double mantissa_decimal);
	std::tuple<int, int> multiplication_operator_mantissa_overflowcalc_denormalized(int exponent, double mantissa_decimal);
	std::tuple<int, int> multiplication_operator_normalize_exponent(int exponent, double mantissa_decimal);
	int multiplication_operator_exponent_calc(Default32squareroot a);

	// Überprüfung des Ergebnisses der Rechenoperatoren
	void operatorResultCheck(int sign, std::tuple<int, int> exp_mant);
	static void checkSign(int sign);
	void checkExponent(int exponent);
	void checkMantissa(int mantissa);
	
	// Vergleichsoperatoren
	bool operator==(Default32squareroot a);
	bool operator!=(Default32squareroot a);
	bool operator>(Default32squareroot a);
	bool operator>=(Default32squareroot a);
	bool operator<(Default32squareroot a);
	bool operator<=(Default32squareroot a);

	bool equals(Default32squareroot a);

	void operatorBaseCheck(Default32squareroot a);

	// Fälle, in denen es sinnvoller ist eine andere Methode aufzurufen (zB a.operator+(-b) soll a.operator-(+b) aufrufen)
	Default32squareroot plus_different_operator(Default32squareroot a);
	Default32squareroot minus_different_operator(Default32squareroot a);

	// Getter und Setter
	// 
	// Rückgabedatentypen entsprechen nicht zwingend den Datentypen der Klassen-Attribute,
	// da der Compiler sonst, zB bei der Mantisse, (int * long long) = int interpretiert und so 
	// Überläufe erzeugt
	int getSign();
	void setSign(int s);
	long long getMantissa();
	void setMantissa(int m);
	int getExponent();
	void setExponent(int e);

	void setValues(int s, int e, int m);

	// nur Getter, da nicht mehr veränderbar
	long long getBase();
	int getBias();
	int getMantissa_bits();
	int getExponent_bits();
	// Min und Max Werte für Exponent und Mantisse
	int getExponent_max();
	int getExponent_min();
	unsigned long long getMantissa_max();
	unsigned long long getMantissa_min();

	// Converter
	//
	// double / long double wird in Default32Squareroot Zahlentyp konvertiert
	static Default32squareroot convert_to_Default32squareroot(int base, long double x);
	void convert_to_Default32squareroot_overwrite(int base, long double x);
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
	static constexpr int bias = 127;  // Biaswert für Exponent
	static constexpr int mantissa_bits = 23;  // Bits Mantisse
	static constexpr int exponent_bits = 8;  // Bits Mantisse
	int exponent_max = 255; // max Wert Exponent
	int exponent_min = 0; // min Wert Exponent
	unsigned long long mantissa_max = 8'388'607; // max Wert Mantisse
	unsigned long long mantissa_min = 0; // min Wert Mantisse
};

#endif