// default32 bezieht sich auf das Vorhandensein von Vorzeichen Bits, Exponenten Bits und Mantissen Bits mit der IEEE754 Verteilung (1,8,23)
// squareroot => optimiert für Quadratwurzeln: zB base = sqrt(2), exponent-bias = 8 => 2^4 , bei exponent-bias = 9 => (2^4) * sqrt(2), 
// damit nur einmal mit der irrationalen Zahl multipliziert werden muss.
#ifndef DEFAULT32SQUAREROOT_TEST_H
#define DEFAULT32SQUAREROOT_TEST_H

#include <iostream>
#include <cmath>

class Default32squareroot_test { 
public:
	Default32squareroot_test(int ba);

	int getBase();
	
	void test_Default32squareroot_operator_plus();
	void test_Default32squareroot_operator_minus();
	void test_Default32squareroot_operator_multiply();
	// Tests für die Berechnung des dargestellten Werts
	void test_Default32squareroot_calcX();
	// Tests für den Converter von double (oder long double) Darstellung zur Zahlendarstellung der Klasse
	void test_Default32squareroot_convert_to_Default32squareroot();
	void test_Default32squareroot_convert_to_Default32squareroot_In_and_Out(); // Default32squareroot als Random-Eingabe und Überprüfung, ob ein Default32squareroot-Objekt mit gleichen Wert raus kommt.
	void test_Default32squareroot_operator_plus_with_conversion();
	void test_Default32squareroot_operator_minus_with_conversion();
	void test_Default32squareroot_operator_multiply_with_conversion();
	
	void test_Default32squareroot_operator_smaller();
	void test_Default32squareroot_operator_smaller_equal();
	void test_Default32squareroot_operator_greater();
	void test_Default32squareroot_operator_greater_equal();

private:
	int base;

};

#endif