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
	return (int)(dezimalwert*pow(this->base, this->mantissa_bits));
}

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


// todo: funktioniert, aber einmal beim Testen trat auf, dass Mantisse um 1 zu niedrig war (Rundungsfehler?)
// Tests schreiben?
Float16 Float16::operator+(Float16 a) {
	int one_dot = (int)(pow(this->base, this->mantissa_bits)); // 1. vor der Mantisse
	int mantissa = this->getMantissa();
	int exponent = this->getExponent();
	int sign = this->getSign();
	
	int shift = this->getExponent() - a.getExponent();
	if (shift < 0) {
		std::cout << "a groesser, Shift = " << shift << '\n';
		mantissa = std::floor((this->getMantissa() + one_dot )/ pow(2,abs(shift))) + a.getMantissa();
		exponent = a.getExponent();
		while (mantissa > one_dot) {
			mantissa -= one_dot;
			mantissa /= 2;
			exponent++;
		}
	}
	if (shift > 0) {
		std::cout << "a kleiner, Shift = " << shift << '\n';
		mantissa = std::floor((a.getMantissa() + one_dot) / pow(2, abs(shift))) + this->getMantissa();
		while (mantissa > one_dot) {
			mantissa -= one_dot;
			mantissa /= 2;
			exponent++;
		}
	}
	if (shift == 0) {
		mantissa = this->getMantissa() + a.getMantissa();
		exponent++;
		mantissa /= 2;
	}
	
	std::cout << "Exponent = " << exponent << " Mantisse = " << mantissa << '\n';

	Float16 sum(sign, mantissa, exponent);
	return sum;
}
/*
* vom Testen operator+
* 
// std::cout << "Mantisse = " << mantissa << '\n';


while (mantissa > pow(this->base, this->mantissa_bits)) {
	mantissa /= 2;
	exponent++;
	std::cout << "hier" << '\n';

mantissa_dezimal = this->berechneMantisseDezimalwert()+1 + a.berechneMantisseDezimalwert()+1;
while (mantissa_dezimal > 2) {
	mantissa_dezimal--;
	exponent++;
}
std::cout << "Mantisse = " << mantissa << '\n';
std::cout << "Mantisse Max = " << pow(this->base, this->mantissa_bits) << '\n';
mantissa-= (int)pow(this->base, this->mantissa_bits);
std::cout << "Mantisse = " << mantissa << '\n';
std::cout << "Exponent = " << exponent << '\n';
exponent++;
std::cout << "Exponent = " << exponent << '\n';
*/

// da bei gleichem Exponent immer mindestens 1 Bit überläuft (1.500 + 1.320 = 2.820 => Binär ca.: 10.1101001)