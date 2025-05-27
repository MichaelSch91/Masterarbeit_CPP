#include <cmath>
#include <iostream>
#include <random>
#include <tuple>
#include "Sqrt_helper.h"
#include "Default32squareroot.h"

Default32squareroot::Default32squareroot() : base(2), sign(0), exponent(0), mantissa(0) {};

Default32squareroot::Default32squareroot(int s, int e, int m) : base(2), sign(s), exponent(e), mantissa(m) {};

Default32squareroot::Default32squareroot(int ba) : base(ba), sign(0), exponent(0), mantissa(0) {};

Default32squareroot::Default32squareroot(int ba, int s, int e, int m) : base(ba), sign(s), exponent(e), mantissa(m) {};

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

long long Default32squareroot::getMantissa() {
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

double Default32squareroot::berechneMantisseDezimalwert() {
	if (this->getExponent() == 0) {
		return (this->getMantissa() * (sqrt(2) - 1)) / pow(this->base, this->mantissa_bits);
	}
	return (this->getMantissa() * (sqrt(2) - 1)) / pow(this->base, this->mantissa_bits) + 1;
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

long double Default32squareroot::calcX() {
	if (this->getExponent() > 254) { // Basis ^ Exponent kann hier nicht in unsigned long long gespeichert werden, daher muss hier alles in einer Funktion berechnet werden
		return calcX_highExponent();
	}
	if (this->getExponent() == 0) {
		return calcX_denormalized();
	}
	if (((this->getExponent() - this->getBias()) % 2) == 1) {
		return this->calcX_oddExponent();
	}
	if ((this->getExponent() - this->getBias()) < 0) {
		return this->calcX_negativeExponent();
	}
	return calcX_evenExponent();
}

long double Default32squareroot::calcX_highExponent() {
	if (((this->getExponent() - this->getBias()) % 2) == 1) {
		return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias) / 2) * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1)) * sqrt(this->getBase());
	}
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias) / 2) * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1));
}

long double Default32squareroot::calcX_oddExponent() {
	long double power = this->calc_pow_oddExponent();
	return pow(-1, this->sign) * power * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1.0));
}
long double Default32squareroot::calcX_evenExponent() {
	unsigned long long power = this->calc_pow_evenExponent();
	return pow(-1, this->sign) * power * (1 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1.0));
}

long double Default32squareroot::calcX_denormalized() {
	long double power = this->calc_pow_negativeExponent();
	return pow(-1, this->sign) * power * ((this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base)));
}

long double Default32squareroot::calcX_negativeExponent() {
	long double power = this->calc_pow_negativeExponent();
	return pow(-1, this->sign) * power * (1.0 + (this->mantissa / pow(this->base, this->mantissa_bits)) * (sqrt(this->base) - 1.0));
}

// Potenz (Base ^ Exponent) berechnen für ungerade Exponenten
long double Default32squareroot::calc_pow_oddExponent() {
	unsigned long long exp_helper = this->getExponent() - this->getBias() - 1;
	if (exp_helper == 0) {
		return sqrt(this->getBase());
	}
	return ((unsigned long long)pow(this->getBase(), (exp_helper / 2))) * sqrt(this->getBase());
}

// Potenz (Base ^ Exponent) berechnen für gerade Exponenten
unsigned long long Default32squareroot::calc_pow_evenExponent() {
	if ((this->getExponent() - this->getBias()) == 0) {
		return 1;
	}
	return (unsigned long long)pow(this->getBase(), ((this->getExponent() - this->getBias()) / 2));
}

// Potenz (Base ^ Exponent) berechnen für negative Exponenten
long double Default32squareroot::calc_pow_negativeExponent() {
	return pow(sqrt(this->getBase()), ((this->getExponent() - this->getBias())));
}

// Berechnet den Wert der in der Mantisse gespeichert ist (für sqrt(2) ein Wert im Bereich [1;sqrt(2)[)
long double Default32squareroot::calc_mantissaValue() {
	if (this->getExponent() == 0) {
		return (this->getMantissa() * (sqrt(2) - 1)) / pow(this->base, this->mantissa_bits);
	}
	return (this->getMantissa() * (sqrt(2) - 1)) / pow(this->base, this->mantissa_bits) + 1;
}

int Default32squareroot::convert_mantissaValue_to_memoryDecimal(long double mantissaValue, unsigned long long one_dot) {
	return ((mantissaValue - 1) * one_dot) / (sqrt(2) - 1);
}

int Default32squareroot::convert_mantissaValue_to_memoryDecimal_denormalized(long double mantissaValue, unsigned long long one_dot) {
	return ((mantissaValue)*one_dot) / (sqrt(2));
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
	throw std::invalid_argument("Vorzeichen und zugehöriger Operator konnte nicht ermittelt werden.");
}

// todo: funktioniert, aber beim Testen tritt auf, dass Mantisse um +-1 zu niedrig/ hoch ist (Rundungsfehler?)
// ::round (sollte das Runden des Rechenwerks eigentlich ganz gut darstellen?) führt zu Abweichungen der Mantisse,
// ::floor (äquivalent zum simplen Abschneiden der nicht mehr speicherbaren Bit durch das Rechenwerk) führt ebenfalls zu Abweichungen der Mantisse,
// ggf ist eine Logik mit ::ceil und ::floor einzuführen
Default32squareroot Default32squareroot::operator+(Default32squareroot a) {
	this->operatorBaseCheck(a);
	int exponent = 0;
	int sign = this->getSign();
	std::tuple<int, int> exp_mant;

	// Vorzeichen
	// 
	// prüfen und ggf. an anderen Operator übergeben
	if (this->getSign() != a.getSign()) {
		return this->plus_different_operator(a);
	}

	exp_mant = this->plus_operator_calc(a);

	this->operatorResultCheck(sign, exp_mant);

	return Default32squareroot(this->getBase(), sign, std::get<0>(exp_mant), std::get<1>(exp_mant));
}

std::tuple<int, int> Default32squareroot::plus_operator_calc(Default32squareroot a) {
	double mantissa_decimal;
	int exp = std::max(this->getExponent(), a.getExponent());
	int shift = this->getExponent() - a.getExponent();

	if (shift >= 0) {
		mantissa_decimal = this->berechneMantisseDezimalwert() + a.berechneMantisseDezimalwert() / Sqrt_helper::sqrt_power(2, abs(shift));
	}
	else {
		mantissa_decimal = a.berechneMantisseDezimalwert() + this->berechneMantisseDezimalwert() / Sqrt_helper::sqrt_power(2, abs(shift));
	}

	return this->plus_operator_mantissa_overflowcalc(exp, mantissa_decimal);
}

std::tuple<int, int> Default32squareroot::plus_operator_mantissa_overflowcalc(int exponent, double mantissa) {
	while (mantissa >= sqrt(this->getBase())) {
		mantissa /= sqrt(this->getBase());
		exponent++;
	}

	if (exponent == 0) {
		return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa, pow(2, this->getMantissa_bits())));
	}

	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal(mantissa, pow(2, this->getMantissa_bits())));
}

Default32squareroot Default32squareroot::minus_different_operator(Default32squareroot a) {
	if (this->getSign() == 0 and a.getSign() == 1) { // this - (-a) = this + a
		// std::cout << "this - (-a) = this + a" << '\n';
		return this->operator+(Default32squareroot(0, a.getExponent(), a.getMantissa())); // neues Objekt, um Objekt a nicht zu verändern
	}
	if (this->getSign() == 1 and a.getSign() == 1) { // - this - (-a) = a + (-this)
		// std::cout << "- this - (-a) = a - this" << '\n';
		return Default32squareroot(0, a.getExponent(), a.getMantissa()).operator+(*this); // neues Objekt, um Objekt a nicht zu verändern
	}
	if (this->getSign() == 1 and a.getSign() == 0) { // - this - (+a) = - this + (-a)
		// std::cout << "- this - (+a) = - this + (-a)" << '\n';
		return this->operator+(Default32squareroot(1, a.getExponent(), a.getMantissa())); // neues Objekt, um Objekt a nicht zu verändern
	}
	throw std::invalid_argument("Vorzeichen und zugehöriger Operator konnte nicht ermittelt werden.");
}

// ggf. hier nur Fälle mit Vorzeichenkombinationen abarbeiten und an Methode "minus()" oder "plus()" übergeben
// damit es übersichtlicher wird, aber vermutlich dadurch Performanz schlechter
// 
// nur "+this - (+a)" wird hier in der Methode berechnet, alle anderen Fälle werden übergeben
Default32squareroot Default32squareroot::operator-(Default32squareroot a) {
	this->operatorBaseCheck(a);
	// Fälle mit Vorzeichenkombinationen, die andere Methoden, oder die Methode anders aufrufen
	if (!(this->getSign() == 0 and a.getSign() == 0)) {
		return this->minus_different_operator(a);
	}

	if (this->equals(a)) {
		return Default32squareroot(this->getBase(), 0, 0, 0);
	}

	unsigned long long one_dot = (unsigned long long)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einfügen, damit die Berechnung entfällt
	int exponent = 0;
	std::tuple<int, int> exp_mant;

	// Exponentenverschiebung (für Mantissen)
	int shift = this->getExponent() - a.getExponent();

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

	exp_mant = this->minus_operator_calc(a);

	this->operatorResultCheck(sign, exp_mant);

	return Default32squareroot(this->getBase(), sign, std::get<0>(exp_mant), std::get<1>(exp_mant));
}

std::tuple<int, int> Default32squareroot::minus_operator_calc(Default32squareroot a) {
	double mantissa_decimal;
	int exp = std::max(this->getExponent(), a.getExponent());
	int shift = this->getExponent() - a.getExponent();

	if (shift >= 0) {
		mantissa_decimal = abs(this->berechneMantisseDezimalwert() - a.berechneMantisseDezimalwert() / Sqrt_helper::sqrt_power(2, abs(shift)));
	}

	else {
		mantissa_decimal = a.berechneMantisseDezimalwert() - this->berechneMantisseDezimalwert() / Sqrt_helper::sqrt_power(2, abs(shift));
	}

	return this->minus_operator_mantissa_overflowcalc(exp, mantissa_decimal);
}

std::tuple<int, int> Default32squareroot::minus_operator_mantissa_overflowcalc(int exponent, double mantissa) {
	if (mantissa == 0) {
		if (exponent <= 0) {
			return std::tuple<int, int>(0, 0);
		}
		return std::tuple<int, int>(exponent, 0);
	}

	while (mantissa < 1) {
		mantissa *= sqrt(this->getBase());
		exponent--;
	}

	if (exponent < 0) { // todo: multiplication_operator_normalize_exponent
		return std::tuple<int, int>(0, 0);
	}

	if (exponent == 0) {
		return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa, pow(2, this->getMantissa_bits())));
	}

	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal(mantissa, pow(2, this->getMantissa_bits())));
}

Default32squareroot Default32squareroot::operator*(Default32squareroot a) {
	this->operatorBaseCheck(a);

	unsigned long long one_dot = (long long int)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einfügen, damit die Berechnung entfällt
	unsigned long long mantissa = 0;
	int exponent = 0;
	int sign = 0;
	std::tuple<int, int> exp_mant;

	// Vorzeichen bestimmen
	if (this->getSign() != a.getSign()) {
		sign = 1;
	}

	exp_mant = this->multiplication_operator_calc(a);

	this->operatorResultCheck(sign, exp_mant);

	return Default32squareroot(this->getBase(), sign, std::get<0>(exp_mant), std::get<1>(exp_mant));
}

std::tuple<int, int> Default32squareroot::multiplication_operator_calc(Default32squareroot a) {
	int exp = multiplication_operator_exponent_calc(a);
	double mantissa_decimal = this->berechneMantisseDezimalwert() * a.berechneMantisseDezimalwert();
	if (exp < 0) {
		return this->multiplication_operator_normalize_exponent(exp, mantissa_decimal);
	}
	return this->multiplication_operator_mantissa_overflowcalc(exp, mantissa_decimal);
}

std::tuple<int, int> Default32squareroot::multiplication_operator_mantissa_overflowcalc(int exponent, double mantissa_decimal) {
	while (mantissa_decimal >= sqrt(this->getBase())) {
		mantissa_decimal /= sqrt(this->getBase());
		exponent++;
	}
	if (exponent == 0) {
		return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa_decimal, pow(2, this->getMantissa_bits())));
	}

	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal(mantissa_decimal, pow(2, this->getMantissa_bits())));
}

std::tuple<int, int> Default32squareroot::multiplication_operator_normalize_exponent(int exponent, double mantissa_decimal) {
	mantissa_decimal /= Sqrt_helper::sqrt_power(this->getBase(), abs(exponent));
	exponent = 0;

	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa_decimal, pow(2, this->getMantissa_bits())));
}

std::tuple<int, int> Default32squareroot::multiplication_operator_mantissa_overflowcalc_denormalized(int exponent, double mantissa_decimal) {
	while (mantissa_decimal >= sqrt(this->getBase())) {
		mantissa_decimal /= sqrt(this->getBase());
		exponent++;
	}
	if (exponent == 0) {
		return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal_denormalized(mantissa_decimal, pow(2, this->getMantissa_bits())));
	}

	return std::tuple<int, int>(exponent, convert_mantissaValue_to_memoryDecimal(mantissa_decimal, pow(2, this->getMantissa_bits())));
}

int Default32squareroot::multiplication_operator_exponent_calc(Default32squareroot a) {
	return this->getExponent() + a.getExponent() - this->getBias();
}

void Default32squareroot::operatorResultCheck(int sign, std::tuple<int, int> exp_mant) {
	int exp = std::get<0>(exp_mant);
	int mant = std::get<1>(exp_mant);
	checkSign(sign);
	this->checkExponent(exp);
	this->checkMantissa(mant);
}

void Default32squareroot::checkSign(int sign) {
	if (sign == 0 or sign == 1) {
		return;
	}
	std::cout << "invalid sign" << " - value saved as sign is invalid" << '\n';
	throw std::invalid_argument("invalid sign");
}

void Default32squareroot::checkExponent(int exponent) {
	if (exponent < this->getExponent_min() or exponent > this->getExponent_max()){
		return;
	}
	std::cout << "invalid exponent" << " - value saved as exponent is invalid" << '\n';
	throw std::invalid_argument("invalid exponent");
}

void Default32squareroot::checkMantissa(int mantissa) {
	if (mantissa < this->getMantissa_min() or exponent > this->getMantissa_max()) {
		return;
	}
	std::cout << "invalid mantissa" << " - value saved as mantissa is invalid" << '\n';
	throw std::invalid_argument("invalid mantissa");
}

bool Default32squareroot::equals(Default32squareroot a) {
	return ((this->getSign() == a.getSign()) && (this->getExponent() == a.getExponent()) && (this->getMantissa() == a.getMantissa()) && (this->getBase() == a.getBase()));
}

bool Default32squareroot::operator==(Default32squareroot a) {
	return this->equals(a);
}

bool Default32squareroot::operator!=(Default32squareroot a) {
	return !this->equals(a);
}

bool Default32squareroot::operator>(Default32squareroot a) {
	this->operatorBaseCheck(a);
	if (this->getSign() == 0) { 
		if (a.getSign() == 0) { // Both positive
			if (this->getExponent() > a.getExponent()) {
				return true;
			}
			else if (this->getExponent() < a.getExponent()) {
				return false;
			}
			else { // Exponents are equal
				return this->getMantissa() > a.getMantissa();
			}
		}
		else { // 'this' is positive, 'a' is negative
			if (((this->getExponent() == 0) && (a.getExponent() == 0)) && ((this->getMantissa() == 0) && (a.getMantissa() == 0))) {
				return false; // Not -0 > 0
			}
			else {
				return true;
			}
		}
	}
	else { // this->getSign() == 1, 'this' is negative
		if (a.getSign() == 0) { // 'this' is negative, 'a' is positive
			return false;
		}
		else { // Both negative
			if (this->getExponent() < a.getExponent()) {
				return true;
			}
			else if (this->getExponent() > a.getExponent()) {
				return false;
			}
			else { // Exponents are equal
				return this->getMantissa() < a.getMantissa();
			}
		}
	}
}

bool Default32squareroot::operator>=(Default32squareroot a) {
	this->operatorBaseCheck(a);
	return (*this > a) || (*this == a);
}

bool Default32squareroot::operator<(Default32squareroot a) {
	this->operatorBaseCheck(a);
	if (this->getSign() == 0) { // 'this' is positive
		if (a.getSign() == 0) { // 'a' is also positive
			if (this->getExponent() < a.getExponent()) {
				return true;
			}
			else if (this->getExponent() > a.getExponent()) {
				return false;
			}
			else { // Exponents are equal
				return this->getMantissa() < a.getMantissa();
			}
		}
		else { // 'a' is negative
			if (((this->getExponent() == 0) && (a.getExponent() == 0)) && ((this->getMantissa() == 0) && (a.getMantissa() == 0))) {
				return false; // Not 0 < -0
			}
			else {
				return false; // Positive is never less than negative (except potentially signed zero)
			}
		}
	}
	else { // this->getSign() == 1, 'this' is negative
		if (a.getSign() == 0) { // 'a' is positive
			return true; // Negative is always less than positive
		}
		else { // 'a' is also negative
			if (this->getExponent() > a.getExponent()) {
				return true;
			}
			else if (this->getExponent() < a.getExponent()) {
				return false;
			}
			else { // Exponents are equal
				return this->getMantissa() > a.getMantissa();
			}
		}
	}
}

bool Default32squareroot::operator<=(Default32squareroot a) {
	this->operatorBaseCheck(a);
	return (*this < a) || (*this == a);
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

Default32squareroot Default32squareroot::convert_to_Default32squareroot(int base, long double x) {
	Default32squareroot result(base, 0, 0, 0);

	if (x == 0.0) {
		return result;
	}

	int steps = 100; //fastApproximation Mantisse Schritte

	result.convert_setSign(x);
	result.setExponent(result.convert_findExponent(x));
	result.setMantissa(result.convert_findMantissa(x, steps));
	return result;
}

void Default32squareroot::convert_to_Default32squareroot_overwrite(int base, long double x) {
	if (x == 0.0) {
		this->setValues(0, 0, 0);
		return;
	}

	int steps = 100; //fastApproximation Mantisse Schritte

	this->convert_setSign(x);
	this->setExponent(this->convert_findExponent(x));
	this->setMantissa(this->convert_findMantissa(x, steps));
}

void Default32squareroot::convert_setSign(long double x) {
	if (x < 0) {
		this->setSign(1);
	}
	else {
		this->setSign(0);
	}
}

int Default32squareroot::convert_findExponent(long double x) {
	x = abs(x);
	for (int exp = this->getExponent_min(); exp <= this->getExponent_max(); exp++) {
		if ((x >= Default32squareroot(this->getBase(), 0, exp, this->getMantissa_min()).calcX()) and (x <= Default32squareroot(this->getBase(), 0, exp, this->getMantissa_max()).calcX())) {
			return exp;
		}
	}
	return 0;
}

int Default32squareroot::convert_findMantissa(long double x, int s) {
	x = abs(x);
	int mantissa_bigSteps = this->convert_mantissa_fastApproximation(x, s);
	return this->convert_Mantissa_fineApproximation(x, s, mantissa_bigSteps);
}

int Default32squareroot::convert_mantissa_fastApproximation(long double x, int s) {
	x = abs(x);
	int steps = s;
	for (int mant = this->getMantissa_min(); mant <= this->getMantissa_max(); mant += steps) {
		if ((x >= Default32squareroot(this->getBase(), 0, this->getExponent(), mant).calcX()) and (x <= Default32squareroot(this->getBase(), 0, this->getExponent(), mant + 100).calcX())) {
			return mant;
		}
	}
	return 0;
}

int Default32squareroot::convert_Mantissa_fineApproximation(long double x, int s, int mant_inaccurate) {
	x = abs(x);
	int m = mant_inaccurate;
	long double deviation = abs(Default32squareroot(this->getBase(), 0, this->getExponent(), m).calcX() - x);
	for (int mant = mant_inaccurate; mant <= mant_inaccurate + s; mant++) {
		if (deviation > abs(Default32squareroot(this->getBase(), 0, this->getExponent(), mant).calcX() - x)) {
			deviation = abs(Default32squareroot(this->getBase(), 0, this->getExponent(), mant).calcX() - x);
			m = mant;
		}
	}

	if (Default32squareroot(this->getBase(), 0, this->getExponent(), m).deviation_due_to_exp() < abs(Default32squareroot(this->getBase(), 0, this->getExponent(), m).calcX() - x)) {
		std::cout << "Fehler! Nicht im Rahmen der Abweichung mit dem jeweiligen Exponenten, MaxFehler: " << this->deviation_due_to_exp() << " erhaltener Fehler = " << abs(Default32squareroot(this->getBase(), this->getSign(), this->getExponent(), m).calcX() - x) << '\n';
		std::cout << "x = " << x << '\n';
	}
	return m;
}

void Default32squareroot::printAttributes() {
	std::cout << "Sign = " << this->getSign() << " Exponent = " << this->getExponent() << " Mantisse = " << this->getMantissa() << '\n';
}