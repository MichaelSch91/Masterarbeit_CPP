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


// todo: funktioniert nur für gleiche Exponenten
Float16 Float16::operator+(Float16 a) {
	int mantissa = this->getMantissa();
	int exponent = this->getExponent();
	int sign = this->getSign();
	
	int shift = this->getExponent() - a.getExponent();
	if (shift < 0) {

	}
	if (shift > 0) {

	}
	if (shift == 0) {
		mantissa = this->getMantissa() + a.getMantissa();
		exponent++;
		mantissa /= 2;
	}
	
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