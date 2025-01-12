#include <cmath>
#include <iostream>
#include "Float16.h"


Float16::Float16(int s, int m, int e) : sign(s), mantissa(m), exponent(e) {
	this->sign = s;
	this->mantissa = m;
	this->exponent = e;
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

double Float16::berechneMantisseDezimalwert() {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}

int Float16::berechneMantisseBinärwert(double dezimalwert) {
	return (int)(dezimalwert * pow(this->base, this->mantissa_bits));
}

// Ein Test, der die Größenordnung des Ergebnisses miteinbezieht wäre sinnvoller, 
// da bei größerer Zahl nur noch wenige Nachkommastellen dargestellt werden können.
void Float16::test_Float16_operator_plus() {
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Float16 flA(0, m1, e1);
	Float16 flB(0, m2, e2);

	Float16 flC = flA + flB;

	for (int i = 0; i < 1000; i++) {
		e1 = rand() % 22;
		e2 = rand() % 22;
		m1 = rand() % 1023;
		m2 = rand() % 1023;

		Float16 flA(0, m1, e1);
		Float16 flB(0, m2, e2);

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
void Float16::test_Float16_operator_multiply() {
	int e1 = 0;
	int e2 = 0;
	int m1 = 0;
	int m2 = 0;

	Float16 flA(0, m1, e1);
	Float16 flB(0, m2, e2);

	Float16 flC = flA * flB;

	for (int i = 0; i < 1000; i++) {
		e1 = rand() % 22;
		e2 = rand() % 22;
		m1 = rand() % 1023;
		m2 = rand() % 1023;

		Float16 flA(0, m1, e1);
		Float16 flB(0, m2, e2);

		Float16 flC = flA * flB;
		std::cout << "A = " << flA.calcX() << " B = " << flB.calcX() << " A * B = " << flC.calcX() << '\n';
		if (abs(flC.calcX() - (flA.calcX() * flB.calcX())) > 0.0000005) {
			std::cout << "Abweichung!" << '\n';
			std::cout << " A + B = " << (flA.calcX() * flB.calcX()) << " Float16 A * B = " << flC.calcX() << '\n' << '\n' << '\n';
		}
	}
}

// todo: funktioniert, aber einmal beim Testen trat auf, dass Mantisse um 1 zu niedrig war (Rundungsfehler?)
// Tests schreiben?
// Vorzeichen muss bei beiden Summanden gleich sein (Implementierung von Addition negativer Zahlen ggf. über operator-)
// ::floor führt zu Abweichungen der Mantisse, weil es nicht das Runden der realen Hardware wiederspiegelt.
// sollte aber genau genug sein. Bei Float16 macht sich das bermerkbar, bei Float32 aber wahrscheinlich nur noch minimal
// ggf ist dazu eine weitere Logik mit ::ceil einzuführen, aber nach aktueller Überlegutn geht das Runden nur 
// sinnvoll, wenn man die letzten Bit kennt
Float16 Float16::operator+(Float16 a) {
	int one_dot = (int)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einfügen, damit die Berechnung entfällt
	int mantissa = this->getMantissa();
	int exponent = this->getExponent();
	int sign = this->getSign();

	// Exponentenverschiebung (für Mantissen)
	int shift = this->getExponent() - a.getExponent();

	if (shift < 0) {
		// std::cout << "a groesser, Shift = " << shift << '\n';
		mantissa = std::floor((this->getMantissa() + one_dot) / pow(2, abs(shift))) + a.getMantissa() + one_dot;
		exponent = a.getExponent();
		while (mantissa >= (2 * one_dot)) {
			mantissa /= 2;
			exponent++;
		}
		mantissa -= one_dot; // 1. wieder von Mantisse abziehen
	}
	if (shift > 0) {
		// std::cout << "a kleiner, Shift = " << shift << '\n';
		mantissa = std::floor((a.getMantissa() + one_dot) / pow(2, abs(shift))) + this->getMantissa() + one_dot;
		while (mantissa >= (2 * one_dot)) {
			mantissa /= 2;
			exponent++;
		}
		mantissa -= one_dot; // 1. wieder von Mantisse abziehen
	}
	if (shift == 0) {
		// std::cout << "kein Shift, Shift = " << shift << '\n';
		if (this->getExponent() == 0 and a.getExponent() == 0) {
			mantissa = this->getMantissa() + a.getMantissa();
			while (mantissa >= (2 * one_dot)) {
				mantissa /= 2;
				exponent++;
				// std::cout << '\n' << " == 0" << '\n';
			}
		}
		else {
			mantissa = this->getMantissa() + one_dot + a.getMantissa() + one_dot;
			while (mantissa >= (2 * one_dot)) {
				mantissa /= 2;
				exponent++;
			}
			mantissa -= one_dot; // 1. wieder von Mantisse abziehen
		}
	}

	std::cout << "Exponent = " << exponent << " Mantisse = " << mantissa << '\n';

	return Float16(sign, mantissa, exponent);
}

// todo
Float16 Float16::operator-(Float16 a) {
	// todo
	return Float16(0, 0, 0);
}

Float16 Float16::operator*(Float16 a) {
	int one_dot = (int)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse // ggf. als Klassenvariable einfügen, damit die Berechnung entfällt
	int mantissa = 0;
	int exponent = 0;
	int sign = 0;

	// Vorzeichen bestimmen
	if (this->getSign() != a.getSign()) {
		sign = 1;
	}

	// Exponent berechnen
	exponent = this->getExponent() + a.getExponent() - this->getBias();

	std::cout << "Exponent = " << exponent << " exp_1 = " << this->getExponent() << " exp_2 = " << a.getExponent() << '\n';

	// Mantisse berechnen
	if (this->getExponent() == 0 and a.getExponent() == 0) {
		mantissa = 0; // Wert ist für die Darstellung zu klein
	}
	else if (this->getExponent() == 0) {
		// todo, ggf Mock notwendig
		// keine Info, wie das berechnet wird
		// mantissa = 0;
		
		std::cout << "A Mantisse = " << a.getMantissa() << " this Mantisse = " << this->getMantissa() << '\n';
		mantissa = this->getMantissa() * (a.getMantissa() + one_dot);
		mantissa = std::floor(mantissa / one_dot);
		std::cout << "Mantisse = " << mantissa << '\n';
		// Komma verschieben, bis Mantisse größer 0,5 (512)
		mantissa *= 2;
		exponent--;
		while (mantissa >= one_dot) {
			mantissa -= one_dot;
			exponent++;
		}
	}
	else if (a.getExponent() == 0) {
		// todo, ggf Mock notwendig
		// keine Info, wie das berechnet wird
		// mantissa = 0;

		mantissa = (this->getMantissa() + one_dot) * a.getMantissa();
		mantissa = std::floor(mantissa / one_dot);
		std::cout << "Mantisse = " << mantissa << '\n';
		// Komma verschieben, bis Mantisse größer 0,5 (512)
		mantissa *= 2;
		exponent--;
		while (mantissa >= one_dot) {
			mantissa -= one_dot;
			exponent++;
		}
	}
	else {
		std::cout << "Mantissenberechnung Standard " << '\n';
		mantissa = (this->getMantissa() + one_dot) * (a.getMantissa() + one_dot);
		mantissa = std::ceil(mantissa / one_dot);
		// std::cout << "Mantisse = " << mantissa << " vor Nachberechnung " << '\n';
		while (mantissa >= (2 * one_dot)) { // Schleife eigentlich irrelevant, weil Wert nie größer 2 * one_dot wird
			mantissa /= 2;
			exponent++;
			std::cout << "Mantisse = " << mantissa << " in Nachberechnung " << '\n';
		}
		// std::cout << "Mantisse = " << mantissa << " nach Nachberechnung " << '\n';
		if (exponent < 0) {
			mantissa /= 2; // Mantisse wieder normalisieren (1. vorne wegnehmen)
		}
		else {
			mantissa -= one_dot;
		}
		// std::cout << "Mantisse = " << mantissa << " Endergebnis " << '\n';
	}

	// bei negativem Exponenten normalisieren
	// todo: noch fehlerhaft
	if (exponent < 0) {
		while (exponent < 0) {
			mantissa = std::ceil(mantissa/ 2);
			exponent++;
			std::cout << "Mantisse = " << mantissa << " in Exponent normalisieren " << '\n';
			std::cout << "Exponent = " << exponent << " in Exponent normalisieren " << '\n';
		}
	}

	std::cout << "Exponent = " << exponent << " Mantisse = " << mantissa << '\n';

	return Float16(sign, mantissa, exponent);
}
