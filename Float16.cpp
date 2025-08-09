#include <cmath>
#include <iostream>
#include "Float16.h"
#include "Float16.h"


Float16::Float16(int s, int e, int m) : sign(s), exponent(e), mantissa(m) {
};

int Float16::getSign() {
	return this->sign;
}
void Float16::setSign(int s) {
	this->sign = s;
}

int Float16::getMantissa() {
	return this->mantissa;
}
void Float16::setMantissa(int m) {
	this->mantissa = m;
}

int Float16::getExponent() {
	return this->exponent;
}
void Float16::setExponent(int e) {
	this->exponent = e;
}

int Float16::getBase() {
	return this->base;
}
int Float16::getBias() {
	return this->bias;
}
int Float16::getMantissa_bits() {
	return this->mantissa_bits;
}
int Float16::getExponent_bits() {
	return this->exponent_bits;
}

double Float16::calcX() {
	if (this->getExponent() == 0) {
		return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
	}
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (1 + this->mantissa / pow(this->base, this->mantissa_bits));
}

// denormalisiert, sonst +1 für exp > 0
double Float16::berechneMantisseDezimalwert() {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}

int Float16::berechneMantisseBinärwert(double dezimalwert) {
	return (int)(dezimalwert * pow(this->base, this->mantissa_bits));
}


Float16 Float16::plus_different_operator(Float16 a) {
	if (this->getSign() == 1) { // -this + a = a - (+this)
		// std::cout << "plus case 1";
		return a.operator-(Float16(0, this->getExponent(), this->getMantissa()));
	}
	if (a.getSign() == 1) { // this + (-a) = this - (+a)
		// std::cout << "plus case 2";
		return this->operator-(Float16(0, a.getExponent(), a.getMantissa()));
	}
	throw std::invalid_argument("Vorzeichen und zugehöriger Operator konnte nicht ermittelt werden.");
}

// todo: funktioniert, aber einmal beim Testen trat auf, dass Mantisse um 1 zu niedrig war (Rundungsfehler?)
// Tests schreiben?
// Vorzeichen muss bei beiden Summanden gleich sein (Implementierung von Addition einer negativen Zahl über operator-)
// ::floor führt zu Abweichungen der Mantisse, weil es nicht das Runden der realen Hardware wiederspiegelt.
// sollte aber genau genug sein. Bei Float16 macht sich das bermerkbar, bei Float16 aber wahrscheinlich nur noch minimal
// ggf ist dazu eine weitere Logik mit ::ceil einzuführen, aber nach aktueller Überlegutn geht das Runden nur 
// sinnvoll, wenn man die letzten Bit kennt
Float16 Float16::operator+(Float16 a) {
	unsigned long long one_dot = (unsigned long long)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einfügen, damit die Berechnung entfällt
	unsigned long long mantissa = 0;
	int exponent = 0;
	int sign = this->getSign();

	// this->printAttributes();
	// a.printAttributes();
	// std::cout << "Plus Operator; this sign: " << this->getSign() << " a sign: " << a.getSign() << " Sign = " << sign << '\n';

	if (this->getSign() != a.getSign()) {
		return this->plus_different_operator(a);
	}

	// std::cout << "Plus Operator; this sign: " << this->getSign() << " a sign: " << a.getSign() << " Sign = " << sign << '\n';

	// Exponentenverschiebung (für Mantissen)
	int shift = this->getExponent() - a.getExponent();

	unsigned long long bit_shift = (unsigned long long)pow(this->base, abs(shift));

	if (shift < 0) {
		// denormalisierte Mantisse (Exponent = 0)
		if (this->getExponent() == 0) {
			// std::cout << "a groesser, Shift = " << shift << '\n';
			mantissa = std::round((this->getMantissa()) * 1.0 / bit_shift) + a.getMantissa() + one_dot;
			exponent = a.getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa >= (2 * one_dot)) {
				mantissa = (int)std::round(mantissa / 2.0);
				exponent++;
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
		else {
			// std::cout << "a groesser, Shift = " << shift << '\n';
			mantissa = std::round((this->getMantissa() * 1.0 + one_dot) / bit_shift) + a.getMantissa() + one_dot;
			exponent = a.getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa >= (2 * one_dot)) {
				mantissa = (int)std::round(mantissa / 2.0);
				exponent++;
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
	}
	if (shift > 0) {
		// denormalisierte Mantisse (Exponent = 0)
		if (a.getExponent() == 0) {
			// std::cout << "a kleiner, Shift = " << shift << '\n';
			mantissa = std::round((a.getMantissa() * 1.0) / bit_shift) + this->getMantissa() + one_dot;
			exponent = this->getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa >= (2 * one_dot)) {
				mantissa = (int)std::round(mantissa / 2.0);
				exponent++;
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
		else {
			// std::cout << "a kleiner, Shift = " << shift << '\n';
			mantissa = std::round((a.getMantissa() * 1.0 + one_dot) / bit_shift) + this->getMantissa() + one_dot;
			exponent = this->getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa >= (2 * one_dot)) {
				mantissa = (int)std::round(mantissa / 2.0);
				exponent++;
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
	}
	if (shift == 0) {
		// std::cout << "kein Shift, Shift = " << shift << '\n';
		// denormalisierte Mantisse (Exponent = 0)
		if (this->getExponent() == 0 and a.getExponent() == 0) {
			mantissa = this->getMantissa() + a.getMantissa();
			exponent = this->getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa >= (2 * one_dot)) {
				mantissa = (int)std::round(mantissa / 2.0);
				exponent++;
				// std::cout << '\n' << " == 0" << '\n';
			}
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
		else {
			mantissa = this->getMantissa() + one_dot + a.getMantissa() + one_dot;
			exponent = this->getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa >= (2 * one_dot)) {
				mantissa = (int)std::round(mantissa / 2.0);
				exponent++;
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
	}
	return Float16(sign, exponent, mantissa);
}


Float16 Float16::minus_different_operator(Float16 a) {
	if (this->getSign() == 0 and a.getSign() == 1) { // this - (-a) = this + a
		// std::cout << "this - (-a) = this + a" << '\n';
		return this->operator+(Float16(0, a.getExponent(), a.getMantissa())); // neues Objekt, um Objekt a nicht zu verändern
	}
	if (this->getSign() == 1 and a.getSign() == 1) { // - this - (-a) = a + (-this)
		// std::cout << "- this - (-a) = a - this" << '\n';
		return Float16(0, a.getExponent(), a.getMantissa()).operator+(*this); // neues Objekt, um Objekt a nicht zu verändern
	}
	if (this->getSign() == 1 and a.getSign() == 0) { // - this - (+a) = - this + (-a)
		// std::cout << "- this - (+a) = - this + (-a)" << '\n';
		return this->operator+(Float16(1, a.getExponent(), a.getMantissa())); // neues Objekt, um Objekt a nicht zu verändern
	}
	throw std::invalid_argument("Vorzeichen und zugehöriger Operator konnte nicht ermittelt werden.");
}

// ggf. hier nur Fälle mit Vorzeichenkombinationen abarbeiten und an Methode "minus()" oder "plus()" übergeben
// damit es übersichtlicher wird, aber vermutlich dadurch Performanz schlechter
// 
// nur "+this - (+a)" wird hier in der Methode berechnet, alle anderen Fälle werden übergeben
Float16 Float16::operator-(Float16 a) {
	// Fälle mit Vorzeichenkombinationen, die andere Methoden, oder die Methode anders aufrufen
	if (!(this->getSign() == 0 and a.getSign() == 0)) {
		return this->minus_different_operator(a);
	}

	unsigned long long one_dot = (int)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einfügen, damit die Berechnung entfällt
	unsigned long long mantissa = 0;
	int exponent = 0;

	// std::cout << "this sign: "<< this->getSign() << " a sign: "<< a.getSign() << '\n';

	// Exponentenverschiebung (für Mantissen)
	int shift = this->getExponent() - a.getExponent();

	// std::cout << "a Exponent " << a.getExponent() << " this Exponent " << this->getExponent() << '\n';

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
	// std::cout << "a Mantisse " << a.getMantissa() << " this Mantisse " << this->getMantissa() << '\n';
	// std::cout << "Sign = " << sign << '\n';

	if (shift < 0) {
		// std::cout << "a groesser, Shift = " << shift << '\n';

		// denormalisierte Mantisse (Exponent = 0)
		if (this->getExponent() == 0) {
			mantissa = (a.getMantissa() + one_dot) - std::round((this->getMantissa()) / pow(2, abs(shift)));
			exponent = a.getExponent();
			// std:cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa <= (one_dot)) {
				mantissa *= 2;
				exponent--;
				// std::cout << '\n' << " == 0" << '\n';
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std:cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
		else {
			mantissa = (a.getMantissa() + one_dot) - std::round((this->getMantissa() + one_dot) / pow(2, abs(shift)));
			exponent = a.getExponent();
			// std:cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa <= (one_dot)) {
				mantissa *= 2;
				exponent--;
				// std::cout << '\n' << " == 0" << '\n';
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std:cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
	}
	if (shift > 0) {
		// std::cout << "a kleiner, Shift = " << shift << '\n';

		// denormalisierte Mantisse (Exponent = 0)
		if (a.getExponent() == 0) {
			// std::cout << "if " << '\n';
			mantissa = (this->getMantissa() + one_dot) - std::round((a.getMantissa()) / pow(2, abs(shift)));
			exponent = this->getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa <= (one_dot)) {
				mantissa *= 2;
				exponent--;
				// std::cout << '\n' << " == 0" << '\n';
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
		}
		else {
			// std::cout << "else " << '\n';
			mantissa = (this->getMantissa() + one_dot) - std::round((a.getMantissa() + one_dot) / pow(2, abs(shift)));
			exponent = this->getExponent();
			// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			while (mantissa <= (one_dot)) {
				mantissa *= 2;
				exponent--;
				// std::cout << '\n' << " == 0" << '\n';
			}
			/*
			if (mantissa < one_dot) {
				mantissa += one_dot;
				exponent--;
			}
			*/			// std::cout << "Vor " << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			// std::cout << "Nach " << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';


		}
	}
	if (shift == 0) {
		// std::cout << "kein Shift, Shift = " << shift << '\n';
		// Mantisse: this > a
		if (this->getMantissa() > a.getMantissa()) { // Zahlen sortieren, dass von größerer Mantisse die kleinere abgezogen wird
			// std::cout << "this > a" << '\n';
			if (this->getExponent() == 0 and a.getExponent() == 0) {
				std::cout << "== 0" << '\n';
				mantissa = this->getMantissa() - a.getMantissa();
				exponent = this->getExponent();
				std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
				while (mantissa <= (one_dot)) {
					mantissa *= 2;
					exponent--;
					// std::cout << '\n' << " == 0" << '\n';
				}
			}
			else {
				//std::cout << "this < a" << '\n';
				mantissa = (this->getMantissa() + one_dot) - (a.getMantissa() + one_dot);
				exponent = this->getExponent();
				// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
				while (mantissa <= (one_dot)) {
					mantissa *= 2;
					exponent--;
					// std::cout << '\n' << " == 0" << '\n';
				}

				mantissa -= one_dot; // 1. wieder von Mantisse abziehen


			}
		}
		// Mantisse: a < this
		if (this->getMantissa() < a.getMantissa()) { // Zahlen sortieren, dass von größerer Mantisse die kleinere abgezogen wird
			// std::cout << "this < a" << '\n';
			if (this->getExponent() == 0 and a.getExponent() == 0) {
				// std::cout << "== 0" << '\n';
				mantissa = a.getMantissa() - this->getMantissa();
				exponent = this->getExponent();
				// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
				while (mantissa <= (one_dot)) {
					mantissa *= 2;
					exponent--;
					// std::cout << '\n' << " == 0" << '\n';
				}
			}
			else {
				mantissa = (a.getMantissa() + one_dot) - (this->getMantissa() + one_dot);
				exponent = this->getExponent();
				// std::cout << "Mantisse = " << mantissa << " Exponent = " << exponent << '\n';
				while (mantissa <= (one_dot)) {
					mantissa *= 2;
					exponent--;
					// std::cout << '\n' << " == 0" << '\n';
				}
				mantissa -= one_dot; // 1. wieder von Mantisse abziehen
			}
		}
	}
	// std::cout << "Exponent = " << exponent << " Mantisse = " << mantissa << '\n';
	if (exponent > 256) {
		std::cout << '\n' << "Exponent mit falschem Wert!" << '\n';
		std::cout << "Exponent = " << exponent << " Mantisse = " << mantissa << '\n';
	}
	if (mantissa > one_dot) {
		std::cout << '\n' << "Mantisse mit falschem Wert!" << '\n';
		std::cout << "Exponent = " << exponent << " Mantisse = " << mantissa << '\n';
	}


	return Float16(sign, exponent, mantissa);
}

Float16 Float16::operator*(Float16 a) {
	unsigned long long one_dot = (long long int)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einfügen, damit die Berechnung entfällt
	unsigned long long mantissa = 0;
	int exponent = 0;
	int sign = 0;

	// Vorzeichen bestimmen
	if (this->getSign() != a.getSign()) {
		sign = 1;
	}

	// Exponent berechnen
	exponent = this->getExponent() + a.getExponent() - this->getBias();

	// std:cout << "Exponent = " << exponent << " exp_1 = " << this->getExponent() << " exp_2 = " << a.getExponent() << '\n';

	// Mantisse berechnen
	if (this->getExponent() == 0 and a.getExponent() == 0) {
		mantissa = 0; // Wert ist für die Darstellung zu klein
	}
	else if (this->getExponent() == 0) {
		// std:cout << "A Mantisse = " << a.getMantissa() << " this Mantisse = " << this->getMantissa() << '\n';
		mantissa = this->getMantissa() * (a.getMantissa() + one_dot);
		mantissa = std::round(mantissa / one_dot);
		// std:cout << "Mantisse = " << mantissa << '\n';
		// Komma verschieben, bis Mantisse größer 0,5 (512)
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
		// Komma verschieben, bis Mantisse größer 0,5 (512)
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
		while (mantissa >= (2 * one_dot)) { // Schleife eigentlich irrelevant, weil Wert nie größer 2 * one_dot wird
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
	return Float16(sign, exponent, mantissa);
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Float16::test_Float16_operator_plus() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Float16 flA(s1, e1, m1);
	Float16 flB(s2, e2, m2);

	Float16 flC = flA + flB;

	for (int i = 0; i < 1000; i++) {
		s1 = rand() % 2;
		s2 = rand() % 2;
		e1 = rand() % 22;
		e2 = rand() % 22;
		m1 = rand() % 1023;
		m2 = rand() % 1023;

		Float16 flA(s1, e1, m1);
		Float16 flB(s2, e2, m2);

		Float16 flC = flA + flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A + B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() + flB.calcX())) > 0.05) {
			std::cout << "Abweichung!" << '\n';
			std::cout << " A + B = " << (flA.calcX() + flB.calcX()) << " Float16 A + B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Float16::test_Float16_operator_minus() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Float16 flA(s1, e1, m1);
	Float16 flB(s2, e2, m2);

	Float16 flC = flA - flB;

	for (int i = 0; i < 1000; i++) {
		s1 = rand() % 2;
		s2 = rand() % 2;
		e1 = rand() % 22;
		e2 = rand() % 22;
		m1 = rand() % 1023;
		m2 = rand() % 1023;

		Float16 flA(s1, e1, m1);
		Float16 flB(s2, e2, m2);

		Float16 flC = flA - flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A - B = " << flC.calcX() << '\n';
		if ((flC.calcX() < 0) and ((flA.calcX() - flB.calcX()) > 0) or (flC.calcX() > 0) and ((flA.calcX() - flB.calcX()) < 0)) {
			std::cout << "Falsches Vorzeichen!" << '\n';
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Float16 A - B = " << flC.calcX() << '\n';
		}
		if (abs(flC.calcX() - (flA.calcX() - flB.calcX())) > 0.0005) {
			std::cout << "Abweichung!" << '\n';
			std::cout << " A - B = " << (flA.calcX() - flB.calcX()) << " Float16 A - B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Float16::test_Float16_operator_multiply() {
	int s1 = 0;
	int s2 = 0;
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Float16 flA(s1, e1, m1);
	Float16 flB(s2, e2, m2);

	Float16 flC = flA * flB;

	for (int i = 0; i < 1000; i++) {
		s1 = rand() % 2;
		s2 = rand() % 2;
		e1 = rand() % 22;
		e2 = rand() % 22;
		m1 = rand() % 1023;
		m2 = rand() % 1023;

		Float16 flA(s1, e1, m1);
		Float16 flB(s2, e2, m2);

		Float16 flC = flA * flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A * B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() * flB.calcX())) > 0.0000005) {
			std::cout << "Abweichung!" << '\n';
			std::cout << " A + B = " << (flA.calcX() * flB.calcX()) << " Float16 A * B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
}

Float16 Float16::convert_to_Float16(long double x) {
	Float16 result(0, 0, 0);

	if (x == 0.0) {
		return result;
	}

	int steps = 20; //fastApproximation Mantisse Schritte

	result.convert_setSign(x);
	result.setExponent(result.convert_findExponent(x));
	result.setMantissa(result.convert_findMantissa(x, steps));
	if (result.getMantissa() >= 1024) {
		result.setMantissa(result.getMantissa() - 1024);
		result.setExponent(result.getExponent() + 1);
	}
	return result;
}

void Float16::convert_setSign(long double x) {
	if (x < 0) {
		this->setSign(1);
	}
	else {
		this->setSign(0);
	}
}

int Float16::convert_findExponent(long double x) {
	x = abs(x);
	for (int exp = 0; exp <= 16; exp++) {
		if ((x >= Float16(0, exp, 0).calcX()) and (x <= Float16(0, exp, 1024).calcX())) {
			return exp;
		}
	}
	return 0;
}

int Float16::convert_findMantissa(long double x, int s) {
	x = abs(x);
	int mantissa_bigSteps = this->convert_mantissa_fastApproximation(x, s);
	return this->convert_Mantissa_fineApproximation(x, s, mantissa_bigSteps);
}

int Float16::convert_mantissa_fastApproximation(long double x, int s) {
	x = abs(x);
	int steps = s;
	for (int mant = 0; mant <= 1024; mant += steps) {
		if ((x >= Float16( 0, this->getExponent(), mant).calcX()) and (x <= Float16( 0, this->getExponent(), mant + 20).calcX())) {
			return mant;
		}
	}
	return 0;
}

int Float16::convert_Mantissa_fineApproximation(long double x, int s, int mant_inaccurate) {
	x = abs(x);
	int m = mant_inaccurate;
	long double deviation = abs(Float16( 0, this->getExponent(), m).calcX() - x);
	for (int mant = mant_inaccurate; mant <= mant_inaccurate + s; mant++) {
		if (deviation > abs(Float16(0, this->getExponent(), mant).calcX() - x)) {
			deviation = abs(Float16(0, this->getExponent(), mant).calcX() - x);
			m = mant;
		}
	}
	return m;
}

void Float16::printAttributes() {
	std::cout << "Sign = " << this->getSign() << " Exponent = " << this->getExponent() << " Mantisse = " << this->getMantissa() << '\n';
}

bool Float16::operator==(Float16 a) {
	if ((this->getSign() == a.getSign()) and (this->getExponent() == a.getExponent()) and (this->getMantissa() == a.getMantissa())) {
		return 1;
	}
	return 0;
}