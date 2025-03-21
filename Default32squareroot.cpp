#include <cmath>
#include <iostream>
#include <random>
#include <tuple>
#include "Sqrt_helper.h"
#include "Default32squareroot.h"

// todo

Default32squareroot::Default32squareroot(int ba) : base(ba), sign(0), exponent(0), mantissa(0) {};

Default32squareroot::Default32squareroot(int ba, int s, int e, int m) : base(ba), sign(s), exponent(e), mantissa(m) {};

Default32squareroot::Default32squareroot(int s, int e, int m) : base(2), sign(s), exponent(e), mantissa(m) {};

void Default32squareroot::setValues(int s, int e, int m) {
	this->sign = s;
	this->exponent = e;
	this->mantissa = m;
}

int Default32squareroot::getSign() {
	return this->sign;
}
void Default32squareroot::setSign(int s) {
	this->sign = s;
}

unsigned long long Default32squareroot::getMantissa() {
	return this->mantissa;
}
void Default32squareroot::setMantissa(int m) {
	this->mantissa = m;
}

int Default32squareroot::getExponent() {
	return this->exponent;
}
void Default32squareroot::setExponent(int e) {
	this->exponent = e;
}

long long Default32squareroot::getBase() {
	return this->base;
}
int Default32squareroot::getBias() {
	return this->bias;
}
int Default32squareroot::getMantissa_bits() {
	return this->mantissa_bits;
}
int Default32squareroot::getExponent_bits() {
	return this->exponent_bits;
}

int Default32squareroot::getExponent_max() {
	return this->exponent_max;
}

int Default32squareroot::getExponent_min() {
	return this->exponent_min;
}

unsigned long long Default32squareroot::getMantissa_max() {
	return this->mantissa_max;
}

unsigned long long Default32squareroot::getMantissa_min() {
	return this->mantissa_min;
}

double Default32squareroot::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}

void Default32squareroot::operatorBaseCheck(Default32squareroot a) {
	if (this->getBase() == a.getBase()) {
		return;
	}
	std::cout << "invalid argument" << "tried to use operator on Objects with different bases" << '\n';
	throw std::invalid_argument("tried to use operator on Objects with different bases");
}

long double Default32squareroot::calcX_long_double() {
	return this->calcX();
}

// f�r Werte > 254 muss anders gerechnet werden, au�er man w�rde wie bei IEEE 754 definieren, dass 255 (Exponent_Hex: FF) = inf
// sollte aber zun�chst irrelevant sein
long double Default32squareroot::calcX() {
	if (this->getExponent() > 254) { // Basis ^ Exponent kann hier nicht in unsigned long long gespeichert werden, daher muss hier alles in einer Funktion berechnet werden
		return calcX_highExponent();
	}
	// std::cout << "Sign,Exponent,Mantisse: " << this->getSign() << " , " << this->getExponent() << " , " << this->getMantissa() << '\n';
	if (((this->getExponent() - this->getBias()) % 2) == 1) {
		// std::cout << "odd" << '\n';
		return this->calcX_oddExponent();
	}
	if ((this->getExponent() - this->getBias()) < 0) {
		// std::cout << "negative" << '\n';
		return this->calcX_negativeExponent();
	}
	// std::cout << "evenExponent" << '\n';
	return calcX_evenExponent();
}

long double Default32squareroot::calcX_highExponent() {
	if (((this->getExponent() - this->getBias()) % 2) == 1) {
		return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias) / 2) * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1)) *sqrt(this->getBase());
	}
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)/2) * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1));
}

long double Default32squareroot::calcX_oddExponent() {
	long double power = this->calc_pow_oddExponent();
	// std::cout << "odd, power: " << power << '\n';
	return pow(-1, this->sign) * power * (1 + (this->mantissa / pow(this->base, this->mantissa_bits))*(sqrt(this->base)-1));
}
long double Default32squareroot::calcX_evenExponent() {
	unsigned long long power = this->calc_pow_evenExponent();
	// std::cout << "even, power: " << power << '\n';
	if (this->getExponent() == 0) { // denormalisierte Mantisse
		return pow(-1, this->sign) * power * ((this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1));
	}
	return pow(-1, this->sign) * power * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1));
}

long double Default32squareroot::calcX_negativeExponent() {
	long double power = this->calc_pow_negativeExponent();
	// std::cout << "negative, power: " << power << '\n';
	return pow(-1, this->sign) * power * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1));
}

// Potenz (Base ^ Exponent) berechnen f�r ungerade Exponenten
long double Default32squareroot::calc_pow_oddExponent() {
	unsigned long long exp_helper = this->getExponent() - this->getBias() - 1;
	// std::cout << "Exp_Helper = " << exp_helper << '\n';
	if (exp_helper == 0) {
		return sqrt(this->getBase());
	}
	return ((unsigned long long)pow(this->getBase(), (exp_helper / 2))) * sqrt(this->getBase());
}

// Potenz (Base ^ Exponent) berechnen f�r gerade Exponenten
unsigned long long Default32squareroot::calc_pow_evenExponent() {
	if ((this->getExponent() - this->getBias()) == 0) {
		return 1;
	}
	return (unsigned long long)pow(this->getBase(), ((this->getExponent() - this->getBias()) / 2));
}

// Potenz (Base ^ Exponent) berechnen f�r negative Exponenten
long double Default32squareroot::calc_pow_negativeExponent() {
	return pow(sqrt(this->getBase()), ((this->getExponent() - this->getBias())));
}

// Berechnet den Wert der in der Mantisse gespeichert ist (f�r sqrt(2) ein Wert im Bereich [1;sqrt(2)[)
long double Default32squareroot::calc_mantissaValue() {
	if (this->getExponent() == 0) {
		return (this->getMantissa() * (sqrt(this->getBase() - 1)));
	}
	return ((this->getMantissa_max() + 1) + this->getMantissa() * (sqrt(this->getBase() - 1)));
}

int Default32squareroot::convert_mantissaValue_to_memoryDecimal(long double mantissaValue, unsigned long long one_dot) {
	return ((mantissaValue - 1) * one_dot) / (sqrt(2) - 1);
}

int Default32squareroot::convert_mantissaValue_to_memoryDecimal_denormalized(long double mantissaValue, unsigned long long one_dot) {
	return ((mantissaValue)*one_dot) / (sqrt(2) - 1);
}

Default32squareroot Default32squareroot::plus_different_operator(Default32squareroot a) {
	if (this->getSign() == 1) { // -this + a = a - (+this)
		// std::cout << "plus case 1";
		return a.operator-(Default32squareroot(0, this->getExponent(), this->getMantissa()));
	}
	if (a.getSign() == 1) { // this + (-a) = this - (+a)
		// std::cout << "plus case 2";
		return this->operator-(Default32squareroot(0, a.getExponent(), a.getMantissa()));
	}
	throw std::invalid_argument("Vorzeichen und zugeh�riger Operator konnte nicht ermittelt werden.");
}

// todo: funktioniert, aber beim Testen tritt auf, dass Mantisse um +-1 zu niedrig/ hoch ist (Rundungsfehler?)
// ::round (sollte das Runden des Rechenwerks eigentlich ganz gut darstellen?) f�hrt zu Abweichungen der Mantisse,
// ::floor (�quivalent zum simplen Abschneiden der nicht mehr speicherbaren Bit durch das Rechenwerk) f�hrt ebenfalls zu Abweichungen der Mantisse,
// ggf ist eine Logik mit ::ceil und ::floor einzuf�hren
Default32squareroot Default32squareroot::operator+(Default32squareroot a) {
	this->operatorBaseCheck(a);
	unsigned long long one_dot = (unsigned long long)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einf�gen, damit die Berechnung entf�llt
	int exponent = 0;
	int sign = this->getSign();
	std::tuple<int, int> exp_mant;

	// Vorzeichen
	// 
	// pr�fen und ggf. an anderen Operator �bergeben
	if (this->getSign() != a.getSign()) {
		return this->plus_different_operator(a);
	}

	// Exponentenverschiebung
	// 
	// zur Bestimmung der Menge an Rechtsverschiebungen und zur Bestimmung welche Zahl gr��er ist (this > a => shift > 0)
	int shift = this->getExponent() - a.getExponent();

	if (!(this->getExponent() == 0) != !(a.getExponent() == 0)) {
		std::cout << "Nur ein Exponent = 0, Berechnung funktioniert noch nicht" << '\n'; // todo: beide Exponenten �bergeben und dann in plus_operator_mantissa_addition �bergeben
	}

	// Berechnung
	//
	// denormalized this.exponent == a.exponent == 0
	if (shift == 0 && (this->getExponent() == 0 || a.getExponent() == 0)) {
		exponent = this->getExponent();
		exp_mant = this->plus_operator_mantissa_addition_denormalized(this->getMantissa(), a.getMantissa(), exponent, one_dot, abs(shift));
	}
	// this < a
	else if (shift < 0) {
		exponent = a.getExponent();
		exp_mant = this->plus_operator_mantissa_addition(a.getMantissa(), this->getMantissa(), exponent, one_dot, abs(shift));
	}
	// this >= a
	else if (shift >= 0) {
		exponent = this->getExponent();
		exp_mant = this->plus_operator_mantissa_addition(this->getMantissa(), a.getMantissa(), exponent, one_dot, abs(shift));
	}

	return Default32squareroot(this->getBase(), sign, std::get<0>(exp_mant), std::get<1>(exp_mant));
}

std::tuple<int, int> Default32squareroot::plus_operator_mantissa_addition(int m1, int m2, int exp, unsigned long long one_dot, int shift) {
	double mantissa_decimal = (m1 * (sqrt(2) - 1)) / one_dot + 1 + ((m2 * (sqrt(2) - 1)) / one_dot + 1) / Sqrt_helper::sqrt_power(2, shift);

	return this->plus_operator_mantissa_overflowcalc(exp, mantissa_decimal, one_dot);
}

std::tuple<int, int> Default32squareroot::plus_operator_mantissa_overflowcalc(int exponent, double mantissa, unsigned long long one_dot) {
	while (mantissa >= sqrt(this->getBase())) {
		mantissa /= sqrt(this->getBase());
		exponent++;
	}
	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal(mantissa, one_dot));
}

std::tuple<int, int> Default32squareroot::plus_operator_mantissa_addition_denormalized(int m1, int m2, int exp, unsigned long long one_dot, int shift) {
	double mantissa_decimal = (m1 * (sqrt(2) - 1)) / one_dot + ((m2 * (sqrt(2) - 1)) / one_dot);

	return this->plus_operator_mantissa_overflowcalc_denormalized(exp, mantissa_decimal, one_dot);
}

std::tuple<int, int> Default32squareroot::plus_operator_mantissa_overflowcalc_denormalized(int exponent, double mantissa, unsigned long long one_dot) {
	while (mantissa >= sqrt(this->getBase())) {
		mantissa /= sqrt(this->getBase());
		exponent++;
	}
	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa, one_dot));
}

Default32squareroot Default32squareroot::minus_different_operator(Default32squareroot a) {
	if (this->getSign() == 0 and a.getSign() == 1) { // this - (-a) = this + a
		// std::cout << "this - (-a) = this + a" << '\n';
		return this->operator+(Default32squareroot(0, a.getExponent(), a.getMantissa())); // neues Objekt, um Objekt a nicht zu ver�ndern
	}
	if (this->getSign() == 1 and a.getSign() == 1) { // - this - (-a) = a + (-this)
		// std::cout << "- this - (-a) = a - this" << '\n';
		return Default32squareroot(0, a.getExponent(), a.getMantissa()).operator+(*this); // neues Objekt, um Objekt a nicht zu ver�ndern
	}
	if (this->getSign() == 1 and a.getSign() == 0) { // - this - (+a) = - this + (-a)
		// std::cout << "- this - (+a) = - this + (-a)" << '\n';
		return this->operator+(Default32squareroot(1, a.getExponent(), a.getMantissa())); // neues Objekt, um Objekt a nicht zu ver�ndern
	}
	throw std::invalid_argument("Vorzeichen und zugeh�riger Operator konnte nicht ermittelt werden.");
}

// ggf. hier nur F�lle mit Vorzeichenkombinationen abarbeiten und an Methode "minus()" oder "plus()" �bergeben
// damit es �bersichtlicher wird, aber vermutlich dadurch Performanz schlechter
// 
// nur "+this - (+a)" wird hier in der Methode berechnet, alle anderen F�lle werden �bergeben
Default32squareroot Default32squareroot::operator-(Default32squareroot a) {
	this->operatorBaseCheck(a);
	// F�lle mit Vorzeichenkombinationen, die andere Methoden, oder die Methode anders aufrufen
	if (!(this->getSign() == 0 and a.getSign() == 0)) {
		return this->minus_different_operator(a);
	}

	if (this->equals(a)) {
		return Default32squareroot(this->getBase(),0,0,0);
	}

	unsigned long long one_dot = (unsigned long long)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einf�gen, damit die Berechnung entf�llt
	int exponent = 0;
	std::tuple<int, int> exp_mant;

	// Exponentenverschiebung (f�r Mantissen)
	int shift = this->getExponent() - a.getExponent();

	if (!(this->getExponent() == 0) != !(a.getExponent() == 0)) {
		std::cout << "Nur ein Exponent = 0, Berechnung funktioniert noch nicht" << '\n'; // todo: beide Exponenten �bergeben und dann in minus_operator_mantissa_subtraction �bergeben
	}

	// Vorzeichen:
	int sign = 0;
	if (shift < 0) {
		sign = 1;
	}
	if (shift == 0) {
		if (a.getMantissa() > this->getMantissa()) {
			sign = 1;
		}
	}
	
	// Berechnung
	//
	// denormalized this.exponent == a.exponent == 0
	if (shift == 0 && (this->getExponent() == 0 || a.getExponent() == 0)) {
		exponent = this->getExponent();
		exp_mant = this->minus_operator_mantissa_subtraction_denormalized(this->getMantissa(), a.getMantissa(), exponent, one_dot, abs(shift));
	}
	// this < a
	else if (shift < 0) {
		exponent = a.getExponent();
		exp_mant = this->minus_operator_mantissa_subtraction(a.getMantissa(), this->getMantissa(), exponent, one_dot, abs(shift));
	}
	// this >= a
	else if (shift > 0) {
		exponent = this->getExponent();
		exp_mant = this->minus_operator_mantissa_subtraction(this->getMantissa(), a.getMantissa(), exponent, one_dot, abs(shift));
	}
	else if (shift == 0) {
		exponent = this->getExponent();
		exp_mant = this->minus_operator_mantissa_subtraction(std::max(this->getMantissa(), a.getMantissa()), std::min(this->getMantissa(), a.getMantissa()), exponent, one_dot, abs(shift));
	}

	if (std::get<0>(exp_mant) > this->getExponent_max()) {
		std::cout << '\n' << "Exponent mit falschem Wert!" << '\n';
		std::cout << "Exponent = " << std::get<0>(exp_mant) << " Mantisse = " << std::get<1>(exp_mant) << '\n';
	}
	if (std::get<1>(exp_mant) > one_dot) {
		std::cout << '\n' << "Mantisse mit falschem Wert!" << '\n';
		std::cout << "Exponent = " << std::get<0>(exp_mant) << " Mantisse = " << std::get<1>(exp_mant) << '\n';
	}

	return Default32squareroot(this->getBase(), sign, std::get<0>(exp_mant), std::get<1>(exp_mant));
}

std::tuple<int, int> Default32squareroot::minus_operator_mantissa_subtraction(int m1, int m2, int exp, unsigned long long one_dot, int shift) {
	double mantissa_decimal = (m1 * (sqrt(2) - 1)) / one_dot + 1 - ((m2 * (sqrt(2) - 1)) / one_dot + 1) / Sqrt_helper::sqrt_power(2, shift);
	return this->minus_operator_mantissa_overflowcalc(exp, mantissa_decimal, one_dot);
}

std::tuple<int, int> Default32squareroot::minus_operator_mantissa_overflowcalc(int exponent, double mantissa, unsigned long long one_dot) {
	if (mantissa == 0) {
		return std::tuple<int, int>(exponent, 0);
	}

	while (mantissa < 1) {
		mantissa *= sqrt(this->getBase());
		exponent--;
	}

	if (exponent == 0) {
		return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa, one_dot));
	}

	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal(mantissa, one_dot));
}

std::tuple<int, int> Default32squareroot::minus_operator_mantissa_subtraction_denormalized(int m1, int m2, int exp, unsigned long long one_dot, int shift) {
	double mantissa_decimal = (m1 * (sqrt(2) - 1)) / one_dot - ((m2 * (sqrt(2) - 1)) / one_dot);

	return this->minus_operator_mantissa_overflowcalc_denormalized(exp, mantissa_decimal, one_dot);
}

std::tuple<int, int> Default32squareroot::minus_operator_mantissa_overflowcalc_denormalized(int exponent, double mantissa, unsigned long long one_dot) {
	while (mantissa < 1) {
		mantissa *= sqrt(this->getBase());
		exponent--;
	}
	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa, one_dot));
}

Default32squareroot Default32squareroot::operator*(Default32squareroot a) {
	this->operatorBaseCheck(a);
	unsigned long long one_dot = (long long int)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einf�gen, damit die Berechnung entf�llt
	unsigned long long mantissa = 0;
	int exponent = 0;
	int sign = 0;

	// Vorzeichen bestimmen
	if (this->getSign() != a.getSign()) {
		sign = 1;
	}

	// Exponent berechnen
	exponent = this->getExponent() + a.getExponent() - this->getBias();
	
	// kann nicht dargestellt werden und soll eine Darstellung mit Wert +-0 ausgeben
	if (exponent < 0) { 
		return Default32squareroot(this->getBase(),this->getSign(), 0, 0);
	}

	// std:cout << "Exponent = " << exponent << " exp_1 = " << this->getExponent() << " exp_2 = " << a.getExponent() << '\n';

	// Mantisse berechnen
	if (this->getExponent() == 0) {
		// std:cout << "A Mantisse = " << a.getMantissa() << " this Mantisse = " << this->getMantissa() << '\n';
		mantissa = this->getMantissa() * (a.getMantissa() + one_dot);
		mantissa = std::round(mantissa / one_dot);
		// std:cout << "Mantisse = " << mantissa << '\n';
		// Komma verschieben, bis Mantisse gr��er 0,5 (512)
		mantissa *= 2;
		exponent--;
		while (mantissa >= one_dot) {
			mantissa -= one_dot;
			exponent++;
		}
	}
	else if (a.getExponent() == 0) {
		mantissa = (this->getMantissa() + one_dot) * a.getMantissa();
		mantissa = std::round(mantissa / one_dot);
		// std:cout << "Mantisse = " << mantissa << '\n';
		// Komma verschieben, bis Mantisse gr��er 0,5 (512)
		mantissa *= 2;
		exponent--;
		while (mantissa >= one_dot) {
			mantissa -= one_dot;
			exponent++;
		}
	}
	else {
		// std:cout << "Mantissenberechnung Standard " << '\n';
		mantissa = (this->getMantissa() + one_dot) * (a.getMantissa() + one_dot);
		// std:cout << "Mantisse = " << mantissa << " vor Nachberechnung " << '\n';
		mantissa = std::round(mantissa / one_dot);
		// std:cout << "Mantisse = " << mantissa << " vor Nachberechnung " << '\n';
		while (mantissa >= (2 * one_dot)) { // Schleife eigentlich irrelevant, weil Wert nie gr��er 2 * one_dot wird
			mantissa /= 2;
			exponent++;
			// std:cout << "Mantisse = " << mantissa << " in Nachberechnung " << '\n';
		}
		// std:cout << "Mantisse = " << mantissa << " nach Nachberechnung " << '\n';
		if (exponent < 0) {
			mantissa /= 2; // Mantisse wieder normalisieren (1. vorne wegnehmen)
		}
		else {
			mantissa -= one_dot;
		}
		// std:cout << "Mantisse = " << mantissa << " Endergebnis " << '\n';
	}
	// bei negativem Exponenten normalisieren
	if (exponent < 0) {
		while (exponent < 0) {
			mantissa = std::round(mantissa / 2);
			exponent++;
			// std::cout << "Mantisse = " << mantissa << " in Exponent normalisieren " << '\n';
			// std::cout << "Exponent = " << exponent << " in Exponent normalisieren " << '\n';
		}
	}
	// std:cout << "Exponent = " << exponent << " Mantisse = " << mantissa << '\n';
	return Default32squareroot(sign, exponent, mantissa);
}

bool Default32squareroot::operator==(Default32squareroot a) {
	return this->equals(a);
}

bool Default32squareroot::equals(Default32squareroot a) {
	if ((this->getSign() == a.getSign()) and (this->getExponent() == a.getExponent()) and (this->getMantissa() == a.getMantissa()) and (this->getBase() == a.getBase())) {
		return 1;
	}
	return 0;
}

// Ein Test, der die Gr��enordnung des Ergebnisses miteinbezieht w�re sinnvoller, 
// da bei gr��erer Zahl nur noch wenige Nachkommastellen dargestellt werden k�nnen.
void Default32squareroot::test_Default32squareroot_operator_plus() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA - flB;

	for (int i = 0; i < 10000; i++) {
		s1 = 0; //rand() % 2;
		s2 = 0; //rand() % 2;
		//e1 = rand() % 254;
		//e2 = rand() % 254;
		e1 = 126 + rand() % 5; // Werte um 0
		e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;
		m2 = rand() % 8'388'608;


		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA + flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A + B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() + flB.calcX())) > 0.00005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() + flB.calcX())) << '\n';
			std::cout << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() + flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A + B = " << (flA.calcX() + flB.calcX()) << " Default32squareroot A + B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Plus: " << counter << " Fehler" << '\n';
}

// Ein Test, der die Gr��enordnung des Ergebnisses miteinbezieht w�re sinnvoller, 
// da bei gr��erer Zahl nur noch wenige Nachkommastellen dargestellt werden k�nnen.
void Default32squareroot::test_Default32squareroot_operator_minus() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA - flB;

	for (int i = 0; i < 100'000; i++) {
		s1 = rand() % 2;
		s2 = rand() % 2;
		e1 = rand() % 254;
		e2 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;
		m2 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA - flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A - B = " << flC.calcX() << '\n';
		if ((flC.calcX() < 0) and ((flA.calcX() - flB.calcX()) > 0) or (flC.calcX() > 0) and ((flA.calcX() - flB.calcX()) < 0)) {
			std::cout << "Falsches Vorzeichen!" << '\n';
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Default32squareroot A - B = " << flC.calcX() << '\n';
		}
		if (abs(flC.calcX() - (flA.calcX() - flB.calcX())) > 0.0005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() - flB.calcX())) << '\n';
			std::cout << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() - flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Default32squareroot A - B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Minus: " << counter << " Fehler" << '\n';
}

// Ein Test, der die Gr��enordnung des Ergebnisses miteinbezieht w�re sinnvoller, 
// da bei gr��erer Zahl nur noch wenige Nachkommastellen dargestellt werden k�nnen.
void Default32squareroot::test_Default32squareroot_operator_multiply() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA - flB;

	for (int i = 0; i < 10000; i++) {
		s1 = rand() % 2;
		s2 = rand() % 2;
		e1 = rand() % 254;
		e2 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;
		m2 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA * flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A * B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() * flB.calcX())) > 0.00005) {
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() * flB.calcX())) << '\n';
			std::cout << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() * flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A * B = " << (flA.calcX() * flB.calcX()) << " Default32squareroot A * B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
}

void Default32squareroot::test_Default32squareroot_calcX() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Default32squareroot flA(s1, e1, m1);

	for (int i = 0; i < 10000; i++) {
		s1 = rand() % 2;
		e1 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		std::cout << "A = " << flA.calcX() << '\n';
		if (abs(flA.calcX() - flA.simpleCalcX()) > 0.00005) {
			std::cout << "Abweichung!" << '\n';
			std::cout << " A simpleCalcX = " << flA.simpleCalcX() << " A calcX = " << flA.calcX() << '\n' << '\n' << '\n';
		}
	}
}

void Default32squareroot::test_Default32squareroot_convert_to_Default32squareroot() {
	int counter = 0;
	double a_random_double = (double)rand() / 10'000;
	Default32squareroot square(this->getBase());

	for (int i = 0; i < 1000; i++) {
		a_random_double = (double)rand() / (rand()%10000);
		// std::cout << "Random Number = " << a_random_double << '\n';
		square = Default32squareroot::convert_to_Default32squareroot(this->getBase(), a_random_double);
		if (abs(square.calcX() - a_random_double) > square.deviation_due_to_exp()) {
			counter++;
			std::cout << "Abweichung!" << '\n';
			std::cout << "Random Double = " << a_random_double << " Ergebnis nach Convert = " << square.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Convert: " << counter << " Fehler" << '\n';
}

void Default32squareroot::test_Default32squareroot_convert_to_Default32squareroot_In_and_Out() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot conversion(this->getBase());

	for (int i = 0; i < 10000; i++) {
		s1 = rand() % 2;
		e1 = rand() % 254;
		// e1 = 126 + rand() % 5; // Werte um 0
		// e2 = 126 + rand() % 5; // Werte um 0
		m1 = rand() % 8'388'608;

		Default32squareroot flA(s1, e1, m1);
		conversion = Default32squareroot::convert_to_Default32squareroot(this->getBase(),  flA.calcX());
		std::cout << "In = " << flA.calcX() << " Out = " << conversion.calcX() << '\n';

		if (!(flA == conversion)) { // todo != �berladen
			counter++;
			std::cout << "Abweichung!" << '\n';
			std::cout << "In Sign = " << flA.getSign() << " In Exp = " << flA.getExponent() << " In Mant = " << flA.getMantissa() << '\n'
				<< "Out Sign = " << conversion.getSign() << " Out Exp = " << conversion.getExponent() << " Out Mant = " << conversion.getMantissa() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Convert In Out: " << counter << " Fehler" << '\n';
}

long double Default32squareroot::simpleCalcX() {
	if (this->getExponent() == 0) {
		return pow(-1, this->sign) * pow(sqrt(this->base), (this->exponent - this->bias)) * ((this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1));
	}
	return pow(-1, this->sign) * pow(sqrt(this->base), (this->exponent - this->bias)) * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1));
}

long double Default32squareroot::deviation_due_to_exp() {
	return (Default32squareroot(this->getBase(), 0, this->getExponent(), 1).calcX() - Default32squareroot(this->getBase(), 0, this->getExponent(), 0).calcX());
}

// todo: f�r negative x
Default32squareroot Default32squareroot::convert_to_Default32squareroot(int base, long double x) {
	Default32squareroot result(base, 0, 0, 0);

	if (x == 0) {
		return result;
	}

	int steps = 100; //fastApproximation Mantisse Schritte

	result.convert_setSign(x);
	result.setExponent(result.convert_findExponent(x));
	result.setMantissa(result.convert_findMantissa(x, steps));
	return result;
}

void Default32squareroot::convert_setSign(long double x) {
	if (x < 0) {
		this->setSign(1);
	}
	else {
		this->setSign(0);
	}
}
// todo: genauer, aktuell ist der Exponent meist um 1 zu niedrig
int Default32squareroot::convert_findExponent(long double x) {
	x = abs(x);
	for (int exp = this->getExponent_min(); exp <= this->getExponent_max(); exp++) {
		if ((x >= Default32squareroot(this->getBase(), 0, exp, this->getMantissa_min()).calcX()) and (x <= Default32squareroot(this->getBase(), 0, exp, this->getMantissa_max()).calcX())) {
			return exp;
		}
	}
}

int Default32squareroot::convert_findMantissa(long double x, int s) {
	int mantissa_bigSteps = this->convert_mantissa_fastApproximation(x,s);
	return this->convert_Mantissa_fineApproximation(x, s, mantissa_bigSteps);
}

int Default32squareroot::convert_mantissa_fastApproximation(long double x, int s) {
	x = abs(x);
	int steps = s;
	for (int mant = this->getMantissa_min(); mant <= this->getMantissa_max(); mant += steps) {
		if ((x >= Default32squareroot(this->getBase(), 0, this->getExponent(), mant).calcX()) and (x <= Default32squareroot(this->getBase(), 0, this->getExponent(), mant + 100).calcX())) {
			// std::cout << mant << '\n';
			return mant;
		}
	}
}

int Default32squareroot::convert_Mantissa_fineApproximation(long double x, int s, int mant_inaccurate) {
	x = abs(x);
	int m = mant_inaccurate;
	long double deviation = abs(Default32squareroot(this->getBase(), 0, this->getExponent(), m).calcX() - x);
	for (int mant = mant_inaccurate; mant <= mant_inaccurate + s; mant++) {
		// std::cout << "Mant = " << mant << '\n';
		if (deviation > abs(Default32squareroot(this->getBase(), 0, this->getExponent(), mant).calcX() - x)) {
			deviation = abs(Default32squareroot(this->getBase(), 0, this->getExponent(), mant).calcX() - x);
			// std::cout << "Abweichung: " << abs(Default32squareroot(this->getBase(), this->getSign(), this->getExponent(), mant).calcX() - x) << '\n';
			// std::cout << "erwarteter maximaler Fehler: " << this->deviation_due_to_exp() << '\n';
			// std::cout << "fineApprox " << mant << '\n';
			m = mant;
		}
	}
	// std::cout << "m = " << m << '\n';

	if (Default32squareroot(this->getBase(), 0, this->getExponent(), m).deviation_due_to_exp() < abs(Default32squareroot(this->getBase(), 0, this->getExponent(), m).calcX() - x)) {
		std::cout << "Fehler, nicht im Rahmen der Abweichung mit dem jeweiligen Exponenten, MaxFehler: " << this->deviation_due_to_exp() << " erhaltener Fehler = " << abs(Default32squareroot(this->getBase(), this->getSign(), this->getExponent(), m).calcX() - x) << '\n';
	}
	return m;
}

void Default32squareroot::printAttributes() {
	std::cout << "Sign = " << this->getSign() << " Exponent = " << this->getExponent() << " Mantisse = " << this->getMantissa() << '\n';
}

// Ein Test, der die Gr��enordnung des Ergebnisses miteinbezieht w�re sinnvoller, 
// da bei gr��erer Zahl nur noch wenige Nachkommastellen dargestellt werden k�nnen.
void Default32squareroot::test_Default32squareroot_operator_plus_with_conversion() {
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister Engine mit Seed von random_device
	std::uniform_int_distribution<int> binary_dist(0, 1); // F�r s1 und s2
	std::uniform_int_distribution<int> exponent_dist(0, 253); // F�r e1 und e2 (0 bis 253)
	std::uniform_int_distribution<int> mantissa_dist(0, 8388607); // F�r m1 und m2
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;

	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC = flA + flB;

	Default32squareroot flCompare(0,0,0);

	for (int i = 0; i < 10000; i++) {
		// s1 = binary_dist(gen);
		// s2 = binary_dist(gen);
		//e1 = exponent_dist(gen);
		//e2 = exponent_dist(gen);
		e1 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		e2 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		m1 = mantissa_dist(gen);
		m2 = mantissa_dist(gen);

		std::cout << "m1 = " << m1 << " m2 = " << m2 << '\n';


		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA + flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A + B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() + flB.calcX())) > 0.00005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() + flB.calcX())) << '\n' << '\n' ;
			flCompare = flCompare.convert_to_Default32squareroot(2,(flA.calcX() + flB.calcX()));
			std::cout << "Should be: " << '\n';
			flCompare.printAttributes();
			std::cout << "But is: " << '\n';
			flC.printAttributes();
			std::cout << '\n' << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() + flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A + B = " << (flA.calcX() + flB.calcX()) << " Default32squareroot A + B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Plus: " << counter << " Fehler" << '\n';
}

// Ein Test, der die Gr��enordnung des Ergebnisses miteinbezieht w�re sinnvoller, 
// da bei gr��erer Zahl nur noch wenige Nachkommastellen dargestellt werden k�nnen.
void Default32squareroot::test_Default32squareroot_operator_minus_with_conversion() {
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister Engine mit Seed von random_device
	std::uniform_int_distribution<int> binary_dist(0, 1); // F�r s1 und s2
	std::uniform_int_distribution<int> exponent_dist(0, 253); // F�r e1 und e2 (0 bis 253)
	std::uniform_int_distribution<int> mantissa_dist(0, 8388607); // F�r m1 und m2
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	int counter = 0;
	
	Default32squareroot flA(s1, e1, m1);
	Default32squareroot flB(s2, e2, m2);

	Default32squareroot flC(0,0,0);

	Default32squareroot flCompare(0, 0, 0);
	
	for (int i = 0; i < 10000; i++) {
		// s1 = binary_dist(gen);
		// s2 = binary_dist(gen);
		//e1 = exponent_dist(gen);
		//e2 = exponent_dist(gen);
		e1 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		e2 = 126 + (gen() % 5); // Werte um 0 (alte rand() Variante)
		m1 = mantissa_dist(gen);
		m2 = mantissa_dist(gen);

		std::cout << "m1 = " << m1 << " m2 = " << m2 << '\n';


		Default32squareroot flA(s1, e1, m1);
		Default32squareroot flB(s2, e2, m2);

		Default32squareroot flC = flA - flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A - B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() - flB.calcX())) > 0.00005) {
			counter++;
			std::cout << "Abweichung!" << " Delta = " << abs(flC.calcX() - (flA.calcX() - flB.calcX())) << '\n' << '\n';
			flCompare = flCompare.convert_to_Default32squareroot(2, (flA.calcX() - flB.calcX()));
			std::cout << "Should be: " << '\n';
			flCompare.printAttributes();
			std::cout << "But is: " << '\n';
			flC.printAttributes();
			std::cout << '\n' << "Abweichung aufgrund Exponent = " << flC.deviation_due_to_exp() << " Exponent = " << flC.getExponent() << '\n';
			if ((abs(flC.calcX() - (flA.calcX() - flB.calcX()))) < flC.deviation_due_to_exp()) {
				std::cout << "Aber Abweichung ist in der Toleranz" << '\n';
			}
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Default32squareroot A - B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
	std::cout << "Operator Minus: " << counter << " Fehler" << '\n';
}