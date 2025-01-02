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

double Float16::calcX() const {
	return pow(-1, this->sign) * pow(this->base, (this->exponent - this->bias)) * (this->mantissa / pow(this->base, this->mantissa_bits));
}

double Float16::berechneMantisseDezimalwert() const {
	return this->mantissa / pow(this->base, this->mantissa_bits);
}